/*
 * debug.h
 *
 *  Created on: Oct 17, 2013
 *      Author: nvthanh
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <configs.h>
#ifdef __cplusplus
extern "C" {
#endif

#define dummy_funct(x...)
#if 0
//(PLATFORM_USED == PLATFORM_LINUX)
#define xprintf printf
#define xflush	fflush
#elif 1
//(PLATFORM_USED == PLATFORM_PIC24)
#define xprintf printf
#define xflush dummy_funct
#else
//(PLATFORM_USED == PLATFORM_ARM_CM3)
#define xprintf dummy_funct
#define xflush dummy_funct
#endif

#define BOLD_RED    	1
#define BOLD_GREEN  	2
#define BOLD_CYAN   	3
#define NORMAL_BLACK 	4

#if (PLATFORM_USED == PLATFORM_WINDOWS)
#include <stdio.h>
#include <windows.h>   // WinApi header
extern HANDLE  hConsole;
extern const char color_code_array[];
#define change_console_color(c) SetConsoleTextAttribute(hConsole, color_code_array[(c < 5)? c : 4])
#elif (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#include <stdio.h>
extern  const char * color_code_array[];
#define change_console_color(c) xprintf(color_code_array[(c < 5)? c : 4])
#else

#endif
#ifndef RDBG
#ifdef USE_DEBUG

#if (DEBUG_LEVEL == 1 || DEBUG_LEVEL == 0)
#define RFATAL(...) {change_console_color( BOLD_RED ); xprintf(__VA_ARGS__);change_console_color( NORMAL_BLACK );xflush(stdout);}
#define RDBG(...) { change_console_color( BOLD_GREEN );xprintf(__VA_ARGS__);change_console_color( NORMAL_BLACK );xflush(stdout);}
#elif (DEBUG_LEVEL == 2)
#define RFATAL(...) { xprintf("%s: <%d>", __FUNCTION__,__LINE__); xprintf(__VA_ARGS__);xflush(stdout);}
#define RDBG(...) { xprintf("%s: <%d>", __FUNCTION__,__LINE__); xprintf(__VA_ARGS__);xflush(stdout);}
#elif (DEBUG_LEVEL == 3)
#define RFATAL(...) {change_console_color( BOLD_RED ); xprintf("%s: <%d>", __FUNCTION__,__LINE__); change_console_color( NORMAL_BLACK );xprintf(__VA_ARGS__);xflush(stdout);}
#define RDBG(...) { change_console_color( BOLD_GREEN );xprintf("%s: <%d>", __FUNCTION__,__LINE__); change_console_color(NORMAL_BLACK);xprintf(__VA_ARGS__);xflush(stdout);}
#else
#define RFATAL(...) xflush(stdout);
#define RDBG(...)  xflush(stdout);
#endif

#else

#define RFATAL(...) xflush(stdout);
#define RDBG(...)  xflush(stdout);

#endif
#endif
#ifdef __cplusplus
}//extern "C" {
#endif

#endif /* DEBUG_H_ */

