/*
 * main.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */


#include <utils/debug.h>
#include <rfid.h>
#include <driver/uart.h>
#include <driver/reader/common.h>
#include <tag/mifare_classic.h>
#include <utils/utils.h>
#include <stdlib.h>
uint8_t const busticket_hf_reader_eeprom_index[]={
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
};

int main(int argc,char ** argv)
{
	RDBG("\n");
	rfid_device * rd= rfid_new_device(RFID_READER_HF_READER_ICDREC,RFID_READER_BUS_UART,(void *)argv[1]);
	if(rd){
		RDBG("\n");
		if(rfid_init(rd) != RFID_ESUCCESS) return -1;
		rfid_poll_target(rd);
#if 1
		mifare_tag  tag;
		memset(&tag,0,sizeof(mifare_tag));
		mifare_get_tag(rd,&tag);
		tag.tag.type = MIFARE_CLASSIC_1K;
		tag.tag.uid_len =4;
		tag.reader_handler = rd;
		mifare_classic_register_eeprom_key(&tag,1,MFC_KEY_A,31);
//		mifare_classic_deregister_eeprom_key(&tag,1,MFC_KEY_A);
		mifare_classic_authenticate(&tag,1,NULL,MFC_KEY_A);
#endif
		rfid_deinit(rd);
	}
	RDBG("\n");
	return 0;
}
