/*
 * uart.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef UART_H_
#define UART_H_
#include <configs.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#include <driver/linux/linux_uart.h>
typedef struct linux_uart_data uart_data;
#define CALL_FUNC_UART(func,x...) linux##_##func(x)
#elif (PLATFORM_USED == PLATFORM_PIC)
#include <driver/PIC/picmcu>
#define CALL_FUNC_UART(func) picmcu##_##func
typedef struct picmcu_uart_data uart_data;
typedef void uart_irq_data;
#elif (PLATFORM_USED == PLATFORM_ARM_STA)
#define CALL_FUNC_UART(func) armmcu##_##func
typedef struct armmcu_uart_data uart_data;
typedef void uart_irq_data;
#elif (PLATFORM_USED == PLATFORM_WINDOWS)
#define CALL_FUNC_UART(func) windows##_##func
#include <driver/windows/windows_uart.h>
typedef struct windows_uart_data uart_data;
#endif




#define uart_open(s_portname) 									CALL_FUNC_UART(uart_open,(s_portname))
#define uart_close(p_udata) 									CALL_FUNC_UART(uart_close,p_udata)
#define uart_flush(p_udata) 									CALL_FUNC_UART(uart_flush,p_udata)
#define uart_read(p_udata,a_res,u32_size_exp,u32_timeout) 		CALL_FUNC_UART(uart_read,p_udata,a_res,u32_size_exp,u32_timeout)
#define uart_write(p_udata,a_res,u32_u32_size_wrt) 				CALL_FUNC_UART(uart_write,p_udata,a_res,u32_u32_size_wrt)
#define uart_set_speed(p_udata,u32_baud)						CALL_FUNC_UART(uart_set_speed,p_udata,u32_baud)

#ifdef __cplusplus
}//extern "C" {
#endif

#endif /* UART_H_ */
