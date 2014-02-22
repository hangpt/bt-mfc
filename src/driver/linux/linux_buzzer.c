/*
 * linux_buzzer.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */


#include <configs.h>
#include <driver/linux/linux_buzzer.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#define PWM_IOCTL_SET_FREQ		1
#define PWM_IOCTL_STOP			0

struct linux_buzzer_data * linux_buzzer_open(char * port)
{
	struct linux_buzzer_data * new_buzzer= (struct linux_buzzer_data *)malloc(sizeof(struct linux_buzzer_data ));
	if(!new_buzzer){
		perror("out of memory\n");
		return NULL;
	}

	new_buzzer->fd = open((const char*)port, 0);
	if (new_buzzer->fd < 0) {
		perror("open pwm_buzzer device");
		free(new_buzzer);
		new_buzzer = NULL;
		return NULL;
	}
	return new_buzzer;
}

int linux_buzzer_close(struct linux_buzzer_data* buzzer)
{
	if(!buzzer|| buzzer->fd <=0) return -1;
	linux_buzzer_stop(buzzer);
	close(buzzer->fd);
	buzzer->fd=-1;
	free(buzzer);
	return 0;
}

int linux_buzzer_set_freq(struct linux_buzzer_data* buzzer, int freq)
{

	if(!buzzer|| buzzer->fd <=0) return -1;
	buzzer->freq = freq;
	//printf("Set: %d\n",freq);
	int ret = ioctl(buzzer->fd, PWM_IOCTL_SET_FREQ, freq);
	if(ret < 0) {
		perror("set the frequency of the buzzer");
		exit(1);
	}
	return 0;
}

int linux_buzzer_stop(struct linux_buzzer_data* buzzer)
{
	if(!buzzer || buzzer->fd <=0) return -1;
	int ret = ioctl(buzzer->fd, PWM_IOCTL_STOP);
	if(ret < 0) {
		perror("stop the buzzer");
		return 1;
	}
#if 0
	if (ioctl(buzzer->fd, 2) < 0) {
		perror("ioctl 2:");
	}
#endif
	return 0;
}

#endif
