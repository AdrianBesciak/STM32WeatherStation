#include "../include/ethernet.h"
#include "task.h"

extern struct netif gnetif;

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

void internetConnectionThread(void const * arguments) {
	MX_LWIP_Init();

	printf("Internet Connection Thread started\n");
	DHCPGetAddress(&gnetif);
	while (1) {
		printf("Internet Connection Thread infinite loop\n");
		vTaskDelay(500);
	}
}
