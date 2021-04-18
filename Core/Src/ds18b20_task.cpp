#include <cstdio>
#include "cmsis_os.h"
#include "ds18b20.h"

extern "C"
[[noreturn]]
void v_ds19b20_task(void* pvParameters){
    uint8_t status = 0;
    uint8_t buffer[8] = {0};
    uint16_t readDataRaw = 0;
    float tempValue = 0.0;
    char c = ' ';

    status = ds18b20Init(SKIP_ROM);

    printf("In task %d\n", status);
    int i = 0;
    for(;;){
        i++;
        ds18b20DevConTemp(SKIP_ROM, 0);
        ds18b20ReadScratchpad(SKIP_ROM, buffer, 0);
        printf("SCRATCHPAD: [0]:%02X [1]:%02X [2]:%02X [3]:%02X [4]:%02X [5]:%02X [6]:%02X [7]:%02X;\n",
                buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
        readDataRaw = ((uint16_t)buffer[1]<<8) | buffer[0];

        if(ds18b20ReadSign(readDataRaw))	{	c='-';	}
        else								{	c='+';	}

        tempValue = ds18b20GetTemp(readDataRaw);

        printf("RegVal%d: 0x%04X - %c%.2f\r\n", i, readDataRaw, c, tempValue);

        vTaskDelay(1000);
    }
}
