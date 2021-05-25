#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include "FreeRTOS.h"
#include <api.h>
#include <string.h>
#include <sockets.h>
#include "lwip.h"
#include "cmsis_os.h"

_Noreturn void internetConnectionThread(void * arguments);


#ifdef __cplusplus
}
#endif
