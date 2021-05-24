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


void internetConnectionThread(void const * arguments);


#ifdef __cplusplus
}
#endif
