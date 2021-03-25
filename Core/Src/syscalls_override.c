#include "main.h"

extern UART_HandleTypeDef huart1;

int _write(int file, char *ptr, int len)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 10);
    return (status == HAL_OK ? len : 0);
}
