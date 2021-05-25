#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "cmsis_os.h"

TaskHandle_t internetTask;
extern _Noreturn void internetConnectionThread(void *argument);

void Network_Task_Init(){
    BaseType_t internetConnectionTask = xTaskCreate(
            internetConnectionThread,
            "internetConnectionTask",
            256 * 4,
            NULL,
            osPriorityNormal,
            &internetTask
    );

    if (internetConnectionTask == pdPASS)
        printf("Successfully created InternetConnectionTask\n");
    else if (internetConnectionTask == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
        printf("Allocation memory error during creating internetConnectionTask\n");
    else
        printf("Error creating internetConnectionTask\n");
}