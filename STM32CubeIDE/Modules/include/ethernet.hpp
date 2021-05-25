#pragma once

#if defined __cplusplus
extern "C" {
#endif

#include <api.h>
#include <string.h>
#include <sockets.h>
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

#include "parson.h"
#include "lwip.h"

void updateCityName(const char *newName);

#if defined __cplusplus
}
#endif