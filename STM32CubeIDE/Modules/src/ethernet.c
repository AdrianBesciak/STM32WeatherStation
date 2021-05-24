#include "../include/ethernet.h"
#include "../include/weather.h"
#include "task.h"
#include <string.h>
#include "parson.h"

extern struct netif gnetif;

void dhcp_get_address() {
    vTaskDelay(500);

    struct dhcp *dhcp = netif_dhcp_data(&gnetif);
    do {
        printf("dhcp->state = %02X\n", dhcp->state);
        vTaskDelay(500);
    } while (dhcp->state != 0x0A);

    printf("Got IP addr: %s\n", ipaddr_ntoa(&gnetif.ip_addr));
}

void processDataFromOWM(const char *data) {
    printf("Process Data Function, data length: %i\n", strlen(data));
    vTaskDelay(1000);
	printf("%s\n", data);

    JSON_Value *jsonValue = json_parse_string(data);
    JSON_Object *jsonObject = json_value_get_object(jsonValue);
    double lon = json_object_dotget_number(jsonObject, "coord.lon");
    double lat = json_object_dotget_number(jsonObject, "coord.lat");

    JSON_Object *main = json_object_get_object(jsonObject, "main");
    double temperature = json_object_get_number(main, "temperature");
    double feels_like = json_object_get_number(main, "feels_like");
    double pressure = json_object_get_number(main, "pressure");
    double humidity = json_object_get_number(main, "humidity");

    double visibility = json_object_get_number(jsonObject, "visibility");
    double wind_speed = json_object_dotget_number(jsonObject, "wind.speed");

    JSON_Object *sys = json_object_get_object(jsonObject, "sys");
    double sunrise = json_object_get_number(sys, "sunrise");
    double sunset = json_object_get_number(sys, "sunset");

    const char *cityName = json_object_get_string(jsonObject, "name");

    JSON_Array *weather = json_object_get_array(jsonObject, "weather");
    JSON_Object *weather_entry = json_array_get_object(weather, 0);
    const char *weather_main = json_object_get_string(weather_entry, "main");
    const char *weather_description = json_object_get_string(weather_entry, "description");

    weather_t *w = &weatherForecast;
    w->lon = lon;
    w->lat = lat;
    w->temperature = temperature;
    w->feels_like = feels_like;
    w->pressure = (uint32_t) pressure;
    w->humidity = (uint32_t) humidity;
    w->visibility = (uint32_t) visibility;
    w->wind_speed = wind_speed;
    w->sunrise = (uint32_t) sunrise;
    w->sunset = (uint32_t) sunset;
    w->status = getMainWeather(weather_main);
    strncpy(w->main, weather_main, MAX_MAIN_NAME);
    strncpy(w->desc, weather_description, MAX_DESCRIPTION_LEN);
    strncpy(w->city, cityName, MAX_CITY_NAME);

    printf("lon: %0.2f lat: %0.2f\n", w->lon, w->lat);
    printf("temp: %0.2f feels: %0.2f pressure: %u humidity: %u\n", w->temperature, w->feels_like, w->pressure, w->humidity);
    printf("visibility %u wind_speed: %0.2f\n", w->visibility, w->wind_speed);
    printf("sunrise: %u | sunset: %u\n", w->sunrise, w->sunset);
    printf("city %s\n", w->city);
    printf("weather: %s desc: %s\n", w->main, w->desc);
}

void pullDataFromOWMServer() {
//    processDataFromOWM(
//            "{\"coord\":{\"lon\":19.9167,\"lat\":50.0833},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"bezchmurnie\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temperature\":16.48,\"feels_like\":15.85,\"temp_min\":15.84,\"temp_max\":18.26,\"pressure\":1021,\"humidity\":64},\"visibility\":10000,\"wind\":{\"speed\":0.45,\"deg\":134,\"gust\":3.13},\"clouds\":{\"all\":0},\"dt\":1621848228,\"sys\":{\"type\":2,\"id\":2009211,\"country\":\"PL\",\"sunrise\":1621824186,\"sunset\":1621881095},\"timezone\":7200,\"id\":3094802,\"name\":\"Kraków\",\"cod\":200}"
//    );
//    return;


    ip4_addr_t serverIP;
    u16_t serverPort = 80;

    if (netconn_gethostbyname("api.openweathermap.org", &serverIP) != ERR_OK) {
        printf("Error getting weather server IP addreess\n");
        return;
    }

    printf("Received server IP: %s\n", ipaddr_ntoa(&serverIP));

    struct sockaddr_in tcp_server;
    char serverIPString[16];
    strcpy(serverIPString, ipaddr_ntoa(&serverIP));
    tcp_server.sin_family = AF_INET;
    tcp_server.sin_port = htons(serverPort);

    inet_pton(tcp_server.sin_family, serverIPString, &(tcp_server.sin_addr));
    const int serverSocket = socket(tcp_server.sin_family, SOCK_STREAM, 0);

    if (connect(serverSocket, (struct sockaddr *) &tcp_server, sizeof(tcp_server)) != 0) {
        printf("Error connecting to the server\n");
        return;
    }
    printf("Connection with server created succesfully\n");

    const int IObufferSize = 1600;
    static char recv_buffer[1600];
    //char sendBuffer[IObufferSize];

    const char *uri = "GET http://api.openweathermap.org/data/2.5/weather?q=Krakow&units=metric&lang=pl&appid=839d6df972338bb98ae9a6dbf710ad81\r\n\r\n";;

    if (send(serverSocket, (void *) uri, strlen(uri), 0) < 0) {
        printf("Error sending URI)\n");
        closesocket(serverSocket);
        return;
    }
    printf("Sent request to server\n");

    vTaskDelay(1000);

    printf("\nWaiting for response from the server\n");
    int receivedCharacters = recv(serverSocket, recv_buffer, IObufferSize, 0);
    if (receivedCharacters < 0) {
        printf("Error receiving message\n");
        closesocket(serverSocket);
        return;
    }
    if (receivedCharacters == 0) {
        printf("Received empty response\n");
        closesocket(serverSocket);
        return;
    }
    processDataFromOWM(recv_buffer);
    closesocket(serverSocket);
}

_Noreturn
void internetConnectionThread(void const *arguments) {
    MX_LWIP_Init();

    printf("Internet Connection Thread started\n");
    dhcp_get_address();

    pullDataFromOWMServer();

    while (1) {
//        printf("Internet Connection Thread infinite loop\n");
        vTaskDelay(10000);
    }
}
