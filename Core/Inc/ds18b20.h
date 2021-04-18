#pragma once

#ifdef	__cplusplus
extern "C" {
#endif
//--------------------------------------------------
#include "stm32f7xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "main.h"
#include "cmsis_os.h"
//--------------------------------------------------
#define SKIP_ROM 		0
#define NO_SKIP_ROM 	1
//--------------------------------------------------
#define RESOLUTION_9BIT 	0x1F
#define RESOLUTION_10BIT 	0x3F
#define RESOLUTION_11BIT 	0x5F
#define RESOLUTION_12BIT 	0x7F
//--------------------------------------------------
#define COM_SEARCH_ROM 			0xF0
#define COM_READ_ROM   			0x33
#define COM_MATCH_ROM			0x55
#define COM_SKIP_ROM			0xCC
#define COM_ALARM_SEARCH		0xEC
#define COM_CONVERT_T			0x44
#define COM_WRITE_SCRATCHPAD	0x4E
#define COM_READ_SCRATCHPAD		0xBE
#define COM_COPY_SCRATCHPAD		0x48
#define COM_RECALL_EE			0xB8
#define COM_READ_POWER_SUPPLY	0xB4
//--------------------------------------------------
#define DS18B20_PORT	DS18B20_PIN_GPIO_Port
#define DS18B20_PIN		DS18B20_PIN_Pin
//--------------------------------------------------

uint8_t ds18b20Init(uint8_t mode);
void ds18b20DevConTemp(uint8_t mode, uint8_t deviceNumber);
void ds18b20ReadScratchpad(uint8_t mode, uint8_t *Data, uint8_t deviceNumber);
uint8_t ds18b20ReadSign(uint16_t dt);
float ds18b20GetTemp(uint16_t dt);
//--------------------------------------------------

#ifdef	__cplusplus
}
#endif

