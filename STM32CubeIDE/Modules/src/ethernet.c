#include "../include/ethernet.h"
#include "task.h"

extern struct netif gnetif;

weather_t weatherForecast;

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

	const char * uri = "GET http://api.openweathermap.org/data/2.5/weather?q=Krakow&appid=839d6df972338bb98ae9a6dbf710ad81\r\n\r\n";;

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
