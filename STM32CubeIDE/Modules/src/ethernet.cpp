#include "ethernet.hpp"
#include "weather.hpp"


extern struct netif gnetif;
constexpr uint32_t CITY_NAME_BUFFEL_LEN = 0x20;
static char cityNameBuffer[CITY_NAME_BUFFEL_LEN] = {};
static char cityNameBufferEscaped[CITY_NAME_BUFFEL_LEN * 3 + 1];
extern TaskHandle_t internetTask;

void dhcp_get_address() {
    struct dhcp *dhcp = netif_dhcp_data(&gnetif);
    do {
        printf("dhcp->state = %02X\n", dhcp->state);
        vTaskDelay(500);
    } while (dhcp->state != 0x0A);

    printf("Got IP addr: %s\n", ipaddr_ntoa(&gnetif.ip_addr));
}

void urlencode(const char* originalText)
{
    memset(cityNameBufferEscaped, 0, sizeof(cityNameBufferEscaped));

    const char *hex = "0123456789abcdef";

    int pos = 0;
    size_t originalLen = strlen(originalText);
    for (size_t i = 0; i < originalLen; i++) {
        if (('a' <= originalText[i] && originalText[i] <= 'z')
            || ('A' <= originalText[i] && originalText[i] <= 'Z')
            || ('0' <= originalText[i] && originalText[i] <= '9')) {
            cityNameBufferEscaped[pos++] = originalText[i];
        } else {
            cityNameBufferEscaped[pos++] = '%';
            cityNameBufferEscaped[pos++] = hex[originalText[i] >> 4];
            cityNameBufferEscaped[pos++] = hex[originalText[i] & 15];
        }
    }
    cityNameBufferEscaped[pos] = '\0';
}

int parse_OWM_data(const char *data) {
    printf("parse_OWM_data. data length: %i\n", strlen(data));

    JSON_Value *jsonValue = json_parse_string(data);
    JSON_Object *jsonObject = json_value_get_object(jsonValue);

    JSON_Object *main = json_object_get_object(jsonObject, "main");
    double temperature = json_object_get_number(main, "temp");
    double feels_like = json_object_get_number(main, "feels_like");
    double pressure = json_object_get_number(main, "pressure");
    double humidity = json_object_get_number(main, "humidity");

    double visibility = json_object_get_number(jsonObject, "visibility");
    double wind_speed = json_object_dotget_number(jsonObject, "wind.speed");

    JSON_Object *sys = json_object_get_object(jsonObject, "sys");
    long sunrise = (long) json_object_get_number(sys, "sunrise");
    long sunset = (long) json_object_get_number(sys, "sunset");

    const char *cityName = json_object_get_string(jsonObject, "name");

    JSON_Array *weather = json_object_get_array(jsonObject, "weather");
    JSON_Object *weather_entry = json_array_get_object(weather, 0);
    const char *weather_main = json_object_get_string(weather_entry, "main");
    const char *weather_description = json_object_get_string(weather_entry, "description");

    weather_t *w = &weatherForecast;
    w->temperature = temperature;
    w->feels_like = feels_like;
    w->pressure = (uint32_t) pressure;
    w->humidity = (uint32_t) humidity;
    w->visibility = (uint32_t) visibility / 1000.0;
    w->wind_speed = wind_speed;
    w->sunrise = (time_t) (sunrise + (3600 * 2));
    w->sunset = (time_t) (sunset + (3600 * 2));
    w->status = translate_main_to_enum(weather_main);
    strncpy(w->main, weather_main, MAX_MAIN_NAME);
    strncpy(w->desc, weather_description, MAX_DESCRIPTION_LEN);
    strncpy(w->city, cityName, MAX_CITY_NAME);

    if (strcmp(json_object_get_string(jsonObject, "message"), "city not found") == 0) {
    	const char * city_not_found_message = "Nie znaleziono miasta";
    	printf("$s\n", city_not_found_message);
    	strncpy(w->desc, city_not_found_message, strlen(city_not_found_message) + 1);
    	strncpy(w->city, "N/N", 4);
    	return NO_CITY;
    }

//    printf("temp: %0.2f feels: %0.2f pressure: %u humidity: %u\n", w->temperature, w->feels_like, w->pressure, w->humidity);
//    printf("visibility %0.2f wind_speed: %0.2f\n", w->visibility, w->wind_speed);
//    printf("sunrise: %ld | sunset: %ld\n", (long) w->sunrise, (long) w->sunset);
//    printf("city %s\n", w->city);
//    printf("weather: %s desc: %s\n", w->main, w->desc);
//    printf("-----------------------------------------\n");
    return 0;
}

void cleanup_socket(int sock) {
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

int get_OWM_data(const char *location) {
    if(strlen(location) == 0){
        return 1;
    }

    constexpr int RECV_BUFFER_SIZE = 1'600;
    static char recv_buffer[RECV_BUFFER_SIZE];
    static char url[0x100];
    urlencode(location);

    const char *firstPart = "GET http://api.openweathermap.org/data/2.5/weather?q=";
    const char *secondPart = "&units=metric&lang=pl&appid=839d6df972338bb98ae9a6dbf710ad81\r\n\r\n";

    snprintf(url, 0x100, "%s%s%s", firstPart, cityNameBufferEscaped, secondPart);
    printf("Getting data for %s\n", location);
//    printf("%s", url);

//    parse_OWM_data(
//            "{\"coord\":{\"lon\":19.9167,\"lat\":50.0833},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"ąłżźćsdasadd aasd asd\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temp\":16.48,\"feels_like\":15.85,\"temp_min\":15.84,\"temp_max\":18.26,\"pressure\":1021,\"humidity\":64},\"visibility\":10000,\"wind\":{\"speed\":0.45,\"deg\":134,\"gust\":3.13},\"clouds\":{\"all\":0},\"dt\":1621848228,\"sys\":{\"type\":2,\"id\":2009211,\"country\":\"PL\",\"sunrise\":1621824186,\"sunset\":1621881095},\"timezone\":7200,\"id\":3094802,\"name\":\"Kraków\",\"cod\":200}"
//    );
//    return;


    ip4_addr_t serverIP;
    constexpr u16_t serverPort = 80;

    if (netconn_gethostbyname("api.openweathermap.org", &serverIP) != ERR_OK) {
        printf("Error getting weather server IP address\n");
        return 2;
    }

    sockaddr_in tcp_server{.sin_family = AF_INET, .sin_port = htons(serverPort)};
    char serverIPString[16];
    strcpy(serverIPString, ipaddr_ntoa(&serverIP));

    inet_pton(tcp_server.sin_family, serverIPString, &(tcp_server.sin_addr));
    int serverSocket = socket(tcp_server.sin_family, SOCK_STREAM, 0);
    vTaskDelay(1'000);

    if (connect(serverSocket, (struct sockaddr *) &tcp_server, sizeof(tcp_server)) != 0) {
        printf("Error connecting to the server\n");
        return 3;
    }

    vTaskDelay(1'000);

    if (send(serverSocket, url, strlen(url), 0) < 0) {
        printf("Error sending URI)\n");
        return 4;
    }

    vTaskDelay(1'000);

    int receivedCharacters = recv(serverSocket, recv_buffer, RECV_BUFFER_SIZE, 0);
    if (receivedCharacters < 0) {
        printf("Error receiving message\n");
        cleanup_socket(serverSocket);
        return 5;
    }
    if (receivedCharacters == 0) {
        printf("Received empty response\n");
        cleanup_socket(serverSocket);
        return 6;
    }

    cleanup_socket(serverSocket);
    return parse_OWM_data(recv_buffer);
}

void clearStructure(){
    memset(&weatherForecast, 0, sizeof(weather_t));
    weatherForecast.error = EMPTY_LOCATION;
}

void updateCityName(const char *newName) {
    clearStructure();
    strncpy(cityNameBuffer, newName, CITY_NAME_BUFFEL_LEN);
    xTaskAbortDelay(internetTask);     //Wake up task immediately
}

extern "C"
[[noreturn]]
void internetConnectionThread(void *arguments) {
    printf("Internet Connection Thread started\n");

    clearStructure();
    MX_LWIP_Init();
    dhcp_get_address();

    while (true) {
        weatherForecast.error = DOWNLOADING;
        int res = get_OWM_data(cityNameBuffer);
        if(res){
            clearStructure();
        }
        weatherForecast.error = static_cast<Weather_Error_t>(res);

        vTaskDelay(15'000);
    }
}

