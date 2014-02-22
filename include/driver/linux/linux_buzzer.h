/*
 * linux_buzzer.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef LINUX_BUZZER_H_
#define LINUX_BUZZER_H_

#include <configs.h>
#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
 struct linux_buzzer_data
{
	int fd;
	int freq;
};

struct linux_buzzer_data * linux_buzzer_open(char * port);
int linux_buzzer_close(struct linux_buzzer_data* buzzer);
int linux_buzzer_stop(struct linux_buzzer_data* buzzer);
int linux_buzzer_set_freq(struct linux_buzzer_data* buzzer, int freq);

#ifdef __cplusplus
};//extern "C" {
#endif

#endif //#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)

#endif /* LINUX_BUZZER_H_ */
