/*
 * debug.c
 *
 *  Created on: Oct 17, 2013
 *      Author: nvthanh
 */


#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <configs.h>
#if (PLATFORM_USED == PLATFORM_WINDOWS)
const char color_code_array[]={0,12,2,14,7};
#else
const char * color_code_array[]={ "\033[0m", "\033[1;31m","\033[1;34m","\033[1;35m", "\033[0m"};
#endif
