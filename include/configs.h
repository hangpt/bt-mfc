/*
 * configs.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef CONFIGS_H_
#define CONFIGS_H_

#define PLATFORM_ARM_LINUX 		0 /**<Indicate Linux platform*/
#define PLATFORM_X86_LINUX 		1/**<Indicate Linux platform*/
#define PLATFORM_WINDOWS		2 /**<Indicate Windows platform*/

#define PLATFORM_PIC 			3 /**<Indicate PIC platform*/
#define PLATFORM_ARM_STA		4 /**<Indicate ARM Stand-alone platform*/
#define PLATFORM_USED			PLATFORM_ARM_LINUX /**<Configure used platform for project*/

#if (PLATFORM_USE== PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX)
#define PLATFORM_NAME linux
#elif (PLATFORM_USE== PLATFORM_WINDOWS)
#define PLATFORM_NAME windows //- Tested
#elif (PLATFORM_USE== PLATFORM_ARM_STA)
#define ARMMCU_V4	0	//- Tested
#define ARMMCU_V5	1	//- non-Tested
#define ARMMCU_V6	2	//- non-Tested
#define ARMMCU_V7	3	//- non-Tested
#define ARMMCU_VERSION_USED ARMMCU_V4 /**< ARM7-TDMIS LPC2148 from NXP */

#define PLATFORM_NAME armmcu
#elif (PLATFORM_USE== PLATFORM_ARM_PIC24)
#define PICMCU_V16 0	//- non-Tested
#define PICMCU_V18 1	//- non-Tested
#define PICMCU_V24 2	//- Tested
#define PICMCU_V32 3	//- non-Tested

#define PICMCU_VERSION_USED PICMCU_V24
#define PLATFORM_NAME picmcu

#endif
#define DYNAMIC_ALLOC_MEM	1 /**<Indicate dynamic memory allocation, with MMU (memory management unit) base system*/
#define STATIC_ALLOC_MEM	0 /**<Indicate static memory allocation, without MMU base system*/
#if ((PLATFORM_USED == PLATFORM_ARM_LINUX)||(PLATFORM_USED == PLATFORM_WINDOWS)|| (PLATFORM_USED == PLATFORM_X86_LINUX))
#define ALLOC_MEM DYNAMIC_ALLOC_MEM /**<Configure supporting memory allocation*/
#else
#define ALLOC_MEM STATIC_ALLOC_MEM /**<Configure supporting memory allocation*/
#endif

#define BUS_UART 			(1<<0)  /**<Indicate UART bus*/
#define BUS_I2C 			(1<<1) /**<Indicate I2C bus*/
#define BUS_SPI 			(1<<2) /**<Indicate SPI bus*/
#define BUS_ENABLE			(BUS_UART | BUS_I2C)  /**<Configure building uart module and I2C*/
#define UART_BUFF_SZ		(1024)  /**<Define UART Rx/Tx maximum buffer size*/
#define BUS_READER_USED		BUS_UART  /**<Configure used bus for Reader IC*/

#define READER_HF_READER_ICDREC	(1<<0)
#define READER_CLRC663			(1<<1)
#define READER_PN532			(1<<2)
#define READERS_SUPPORTED		(READER_HF_READER_ICDREC | READER_CLRC663)

#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
#define	ICDREC_HF_READER_BAUDRATE_DEFAULT (19200)
#endif

#if (READERS_SUPPORTED & READER_CLRC663)
#define	CLRC663_BAUDRATE_DEFAULT (115200)
#endif

#define USE_DEBUG  /**<Configure building with debug version*/
#define DEBUG_LEVEL 3 /**<Configure debug level for building
							\n 0: Only print debug information
							\n 1: Only print debug information + data of Rx/Tx
							\n 2: Print debug information and line+function
							\n 3: Print debug information and line+function with color
 	 	 	 	 	 	 	*/

#define PROJECT_BUS_TICKET		0 /**<Indicate the bus ticket using RFID technology project*/
#define PROJECT_DESFIRE_EV1		1 /**<Indicate the Desfire EV1 functionalities project*/
#define PROJECT_IMPLEMENT		PROJECT_BUS_TICKET  /**<Configure implemented project*/

#if (PROJECT_IMPLEMENT == PROJECT_BUS_TICKET)
#define FUNCTION_ALLOCATE_USER 				(1<<0)
#define FUNCTION_TRANSACTION				(1<<1)
#define FUNCTION_TRANSACTION_AND_RECOVERY	(1<<2)
#define FUNCTION_TEST_BUZZER 				(1<<3)
#define FUNCTION_CHARGE_ACCOUNT				(1<<4)

#define FUNCTION_CHOICE FUNCTION_TRANSACTION_AND_RECOVERY


#endif


#endif /* CONFIGS_H_ */
