#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "FreeRTOS.h"
#include <api.h>
#include <string.h>
#include <sockets.h>
#include <sys.h>
#include "lwip.h"
#include "cmsis_os.h"


typedef struct weather_t {
	char * temp; //temperature in celsius
	char * weatherMainName;
	char * weatherDescription;
	char * pressure;
	char * humidity;
	char * visibility;
	char * windSpeed;
	char * rainAmount;
	char * city;
} weather_t;

extern weather_t weatherForecast;

void internetConnectionThread(void const * arguments);


#ifdef __cplusplus
}
#endif
