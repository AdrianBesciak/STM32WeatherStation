#include "../include/ethernet.h"
#include "../include/weather.h"
#include "task.h"
#include <string.h>

extern struct netif gnetif;

extern weather_t weatherForecast;

void DHCPGetAddress(struct netif *gnetif) {
    vTaskDelay(500);

    printf("Started DHCP connection\n");

    struct dhcp *dhcp = netif_dhcp_data(gnetif);
    do
    {
        printf("dhcp->state = %02X\n",dhcp->state);
        vTaskDelay(500);
    }while(dhcp->state != 0x0A);
    printf("DHCP bound with address %s\n", ipaddr_ntoa(&(gnetif->ip_addr)));
}

void processDataFromOWM(const char * data) {
	printf("\n\n\nProcess Data Function, data length: %i\n", strlen(data));
	vTaskDelay(1000);
	printf("%s\n", data);

	int index = 0;
	while (index < strlen(data) && data[index] != '}') {	//miss "coord" field
		index++;
	}
	index++;
	if (index+1 < strlen(data) && data[index] == ',' && data[index+1] == '"') {
		index += 2;
	} else
		return;

	if (strncmp(&(data[index]), "weather", 7) == 0) {
		index += 7;
		while(index < strlen(data) && data[index] != 'm')
			index++;
		if (strncmp(&(data[index]), "main\":\"", 7) == 0) {
			index += 7;
			char weatherType[20];
			int j = 0;
			while (data[index] != '"') {
				weatherType[j] = data[index];
				j++;
				index++;
			}
			weatherType[j] = '\0';
			printf("\nMain Weather: %s\n", weatherType);
			weatherForecast.weatherMainName = getMainWeather(weatherType);
		}

		while(data[index] != 'd')
			index++;
		if (strncmp(&(data[index]), "description\":\"", 14) == 0) {
			index += 14;
			int j = 0;
			while (data[index] != '"') {
				weatherForecast.weatherDescription[j] = data[index];
				j++;
				index++;
			}
			weatherForecast.weatherDescription[j] = '\0';
			printf("\nWeather description: %s\n", weatherForecast.weatherDescription);
		}
		while (data[index] != ']')
			index++;
	} else
		return;

	while (index < strlen(data)) {
		index++;
		if (data[index] == 'm' && strncmp(&(data[index]), "main\":{\"", 8) == 0) {
			index += 8;
			break;
		}
	}
	if (strncmp(&(data[index]), "temp\":", 6) == 0) {
		index += 6;
		weatherForecast.temp = getFloatValue(&(data[index]));
		printf("Temperature: %f\n", weatherForecast.temp);
	}

	//ToDo: parse rest of weatherForecast values
	//Some dummy values:
	weatherForecast.pressure = 1021;
	weatherForecast.visibility = 1200;
	weatherForecast.windSpeed = 1.03;
	strcpy(weatherForecast.city, "Krakow");

}

void pullDataFromOWMServer() {
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

	if (connect(serverSocket, (struct sockaddr * ) &tcp_server, sizeof(tcp_server)) != 0) {
		printf("Error connecting to the server\n");
		return;
	}
	printf("Connection with server created succesfully\n");

	const int IObufferSize = 1600;
	static char recv_buffer[1600];
	//char sendBuffer[IObufferSize];

	const char * uri = "GET http://api.openweathermap.org/data/2.5/weather?q=Krakow&lang=pl&appid=839d6df972338bb98ae9a6dbf710ad81\r\n\r\n";;

	if (send(serverSocket, (void*) uri, strlen(uri), 0) < 0) {
		printf("Error sending URI)\n");
		return;
	}
	printf("Sent request to server\n");

	vTaskDelay(1000);

	printf("\nWaiting for response from the server\n");
	int receivedCharacters = recv(serverSocket, recv_buffer, IObufferSize, 0);
	if (receivedCharacters < 0) {
		printf("Error receiving message\n");
		return;
	}
	if (receivedCharacters == 0){
		printf("Received empty response\n");
		return;
	}
	processDataFromOWM(recv_buffer);
}

void internetConnectionThread(void const * arguments) {
	MX_LWIP_Init();

	printf("Internet Connection Thread started\n");
	DHCPGetAddress(&gnetif);

	pullDataFromOWMServer();

	while (1) {
		printf("Internet Connection Thread infinite loop\n");
		vTaskDelay(4000);
	}
}
