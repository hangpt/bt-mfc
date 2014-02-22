/*
 * icdrec_hf_reader.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef ICDREC_HF_READER_H_
#define ICDREC_HF_READER_H_

#include <driver/reader/reader.h>
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
#define PACKAGE_FROM_READER	0xA1
#define PACKAGE_FROM_HOST	0xA0

#define HF_READER_ACK				0x00
#define HF_READER_NAK				0x01
#define HF_READER_NAK_NO_CMD		0x02
#define HF_READER_NAK_NO_TAG		0x03
#define HF_READER_NAK_BLK_EXIT		0x04
#define HF_READER_NAK_BLK_LOCK		0x05
#define HF_READER_NAK_LCK_UNSUCCESS	0x06
#define HF_READER_NAK_OPT_SUP		0x07
#define HF_READER_NAK_TIMEOUT_TAG	0x08
#define HF_READER_NAK_RCV_CODE		0x09
#define HF_READER_NAK_NON_PAC		0x0A
#define HF_READER_NAK_LEN_PAC		0x0B
#define HF_READER_NAK_UNSEL_USB		0x0C
#define HF_READER_NAK_HEADER_ERR	0x0D
#define HF_READER_NAK_CMD_ERR		0x0E
#define HF_READER_NAK_UNSUP_SINGLE	0x0F
#define HF_READER_NAK_AUTHERR		0x10
#define HF_READER_NAK_KEYERR		0x11
#define HF_READER_NAK_NOTAGERR		0x12
#define HF_READER_NAK_CRCERR		0x13
#define HF_READER_NAK_PARITYERR		0x14
#define HF_READER_NAK_CODEERR		0x15
#define HF_READER_NAK_BITCOUNTERR	0x16
#define HF_READER_NAK_OVERFLOW		0x17
#define HF_READER_NAK_FRAMINGERR	0x18
#define HF_READER_NAK_VALERR		0x19
#define HF_READER_NAK_NOTAUTHERR	0x1A
#define HF_READER_NAK_TIMEOUT		0x1B
#define HF_READER_NAK_CMD_ISO		0x1C
#define HF_READER_NAK_UNSEL_RS232	0x1D
#define HF_READER_NAK_CON_TYPE		0x1E

#define HF_READER_CMD_ANTICOLLISION	0x30
#define HF_READER_CMD_REQA			0x31
#define HF_READER_CMD_WAKEUP		0x32
#define HF_READER_CMD_HALT			0x33

#define HF_READER_CMD_WRITE_MFC		0x34
#define HF_READER_CMD_READ_MFC		0x35
#define HF_READER_CMD_PRIVATE_MFC	0x36
#define HF_READER_CMD_AUTH_MFC		0x37
#define HF_READER_CMD_FVALUE_MFC	0x38
#define HF_READER_CMD_LOADKEY_MFC	0x39
#define HF_READER_CMD_LOADKEYEEPROM_MFC		0x3A
#define HF_READER_CMD_WRITEKEYEEPROM_MFC	0x3B
#define HF_READER_CMD_WRITEKEY2TAG_MFC		0x3C

#define HF_READER_MAX_EEPROM_KEY_STORED	32
#define HF_READER_NEW_REQ_PACKAGE(name,metalen) uint8_t __##name[sizeof(ihr_header)+metalen+1+2];\
		size_t	__##name##_sz =  sizeof(ihr_header)+metalen+1+2;\
		size_t	__##name##_n = 0;

#define HF_READER_NEW_RESP_PACKAGE(name,metalen) HF_READER_NEW_REQ_PACKAGE(name,(metalen+1))

#define GET_PTR(name)  		(__##name)
#define GET_LEN(name)		(__##name##_sz)
#define GET_POSIT(name)		(__##name##_n)
#define GET_SZ_BUILT(name)	(__##name##_n)
#define GET_SZ_RES(name)	(__##name##_n)
extern uint8_t * dummy_ptr;
extern size_t dummy_len;
extern size_t dummy_n;
#define CLEAR_WARNING(name) dummy_ptr = GET_PTR(name); \
		dummy_len=GET_LEN(name); \
		dummy_n=GET_POSIT(name);

typedef struct ihr_header{
	//TODO: ihr = ICDREC HF Reader
	uint8_t 	from ;
	uint16_t 	length;
	uint8_t 	cmd;
} __attribute__((packed)) ihr_header ;

typedef struct ihr_header_response{
	uint8_t 	from ;
	uint16_t 	length;
	uint8_t 	cmd;
	uint8_t		resp;
}__attribute__((packed)) ihr_header_response;


void register_icdrec_hf_reader_interface(rfid_device * device, rfid_reader_bus_type bus_type);
#endif

#endif /* ICDREC_HF_READER_H_ */
