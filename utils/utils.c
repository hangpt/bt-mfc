/*
 * utils.c
 *
 *  Created on: Oct 17, 2013
 *      Author: nvthanh
 */


#include "utils.h"
#include <configs.h>
#if (PLATFORM_USED == PLATFORM_ARM_LINUX || PLATFORM_USED == PLATFORM_X86_LINUX || PLATFORM_USED == PLATFORM_WINDOWS)
#include  <sys/time.h>
#endif
#include <utils/debug.h>
void rfid_calculate_crc16(uint8_t*blk,uint32_t sz,uint32_t preset,uint8_t * out)
{
	if(!blk || !out) return;
	  uint8_t  bt;
	  do {
	    bt = *blk++;
	    bt = (bt ^ (uint8_t)(preset & 0x00FF));
	    bt = (bt ^ (bt << 4));
	    preset = (preset >> 8) ^ ((uint32_t) bt << 8) ^ ((uint32_t) bt << 3) ^ ((uint32_t) bt >> 4);
	  } while (--sz);

	  *out++ = (uint8_t)(preset & 0xFF);
	  *out = (uint8_t)((preset >> 8) & 0xFF);
}

#if (PLATFORM_USED == PLATFORM_WINDOWS)
#include <windows.h>
void uSleep(int waitTime){
	__int64 time1 = 0, time2 = 0, sysFreq = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	//QueryPerformanceFrequency((LARGE_INTEGER *)&sysFreq);
	do{
		QueryPerformanceCounter((LARGE_INTEGER *)&time2);
	//  }while((((time2-time1)*1.0)/sysFreq)<waitTime);
	}while( (time2-time1) < waitTime);
}

#endif

#ifndef RAND_MAX
#define RAND_MAX 0xFFFFFFFF
#endif
void rfid_rand_bytes(uint8_t * out, size_t sz,uint8_t min, uint8_t max)
{
	if(!out || sz==0 || min >= max) return;
#if (PLATFORM_USED == PLATFORM_LINUX || PLATFORM_USED == PLATFORM_WINDOWS)
	//srand (time(NULL));
	struct timeval tm;
	gettimeofday(&tm,NULL);
	srand (tm.tv_usec);
#endif

	while(sz){
		out[sz-1] = min + (uint8_t ) (  rand()%(max-min+1) );
		sz--;
	}
}

void rfid_hexdump(const void *ptr, int length, const char *hdr, int flags)
{

#if 1
	int i, j, k;
	int cols;
	const unsigned char *cp;
	char delim;

	if ((flags & NFC_HD_DELIM_MASK) != 0)
		delim = (flags & NFC_HD_DELIM_MASK) >> 8;
	else
		delim = ' ';

	if ((flags & NFC_HD_COLUMN_MASK) != 0)
		cols = flags & NFC_HD_COLUMN_MASK;
	else
		cols = 20;
	cp = ptr;

	change_console_color( BOLD_CYAN );
	xprintf("%s(%02d)\r\n",hdr ? hdr:"",length);
	change_console_color( NORMAL_BLACK );
	for (i = 0; i < length; i+= cols) {
//		if ((flags & NFC_HD_OMIT_COUNT) == 0)
//			xprintf("[%04X]  ", i);
		if ((flags & NFC_HD_OMIT_HEX) == 0) {
			for (j = 0; j < cols; j++) {
				k = i + j;
				if (k < length)
					xprintf("%c%02X", delim, cp[k]);
				else
					xprintf("   ");
			}
		}

		if ((flags & NFC_HD_OMIT_CHARS) == 0) {
			xprintf(" |");
			for (j = 0; j < cols; j++) {
				k = i + j;
				if (k >= length)
					xprintf(" ");
				else if (cp[k] >= ' ' && cp[k] <= '~')
					xprintf("%c", cp[k]);
				else
					xprintf(".");
			}
			xprintf("|");
		}
		xprintf("\r\n");
	}
#else
	int j;
	uint8_t *cptr =(uint8_t *) ptr;
	xprintf("\033[1;35m%s\033[0m (%02d bytes) |",hdr ? hdr:"",length);
	for(j=0;j<length;j++){\
		xprintf(" %02X", cptr[j]);
	}
	xprintf(" | === |");
	for(j=0;j<length;j++){
		if (cptr[j] >= ' ' && cptr[j] <= '~')
			xprintf("%c", cptr[j]);
		else
			xprintf(".");
	}
	xprintf("|");
	xprintf("\r\n");
#endif
}

