/*
 * buzzer.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <configs.h>
#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#include <driver/linux/linux_buzzer.h>
typedef struct linux_buzzer_data buzzer_data;
#define CALL_FUNC_BUZZER(func,x...) linux##_##func(x)
#elif (PLATFORM_USED == PLATFORM_PIC)
#include <driver/PIC/picmcu>
typedef struct picmcu_buzzer_data buzzer_data;
typedef void buzzer_irq_data;
#elif (PLATFORM_USED == PLATFORM_ARM_STA)
typedef struct armmcu_buzzer_data buzzer_data;
typedef void buzzer_irq_data;
#elif (PLATFORM_USED == PLATFORM_WINDOWS)
#include <driver/windows/windows_buzzer.h>
typedef struct windows_buzzer_data buzzer_data;
#endif

#define buzzer_open(s_name) 		CALL_FUNC_BUZZER(buzzer_open,p_bdata)
#define buzzer_close(p_bdata) 		CALL_FUNC_BUZZER(buzzer_close,p_bdata)
#define buzzer_stop(p_bdata) 		CALL_FUNC_BUZZER(buzzer_stop,p_bdata)
#define buzzer_set_freq(p_bdata,u32_freq) 	CALL_FUNC_BUZZER(buzzer_set_freq,p_bdata,u32_freq)

#endif /* BUZZER_H_ */
