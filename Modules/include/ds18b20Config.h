#pragma once

#include "main.h"
//	 72 MHz cpu >>> Prescaler=(72-1)      counter period=Max
#define    _DS18B20_MAX_SENSORS                 1
#define    _DS18B20_GPIO                        DS18B20_PIN_GPIO_Port
#define    _DS18B20_PIN                         DS18B20_PIN_Pin

#define    _DS18B20_CONVERT_TIMEOUT_MS          5000
#define    _DS18B20_UPDATE_INTERVAL_MS          5000

#define    _DS18B20_TIMER                       htim13


