/*
 * rfid_types.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef RFID_TYPES_H_
#define RFID_TYPES_H_

#define MAX_NAME_LEN 32
#include <configs.h>
#include <stdint.h>
#include <stdio.h>
#define UNIMPLEMENTED_FUNCTION (NULL)
typedef enum {
	RFID_ESUCCESS=0,
	RFID_EIO,
	RFID_EACK,
	RFID_ENAK,
	RFID_EIMPL,
	RFID_EINARG,
	RFID_ERESP,
	RFID_ETIMEOUT
}rfid_status ;

typedef enum{
	RFID_READER_UNAVAILABLE=0,
	RFID_READER_AVAILABLE,
}rfid_reader_state;
typedef enum{
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
	RFID_READER_HF_READER_ICDREC = 0,
#endif
#if (READERS_SUPPORTED & READER_CLRC663)
	RFID_READER_CLRC663,
#endif
#if (READERS_SUPPORTED & READER_PN532)
	RFID_READER_PN532,
#endif
}rfid_reader_type;

typedef enum{
#if (BUS_READER_USED & BUS_UART)
	RFID_READER_BUS_UART=0,
#endif
#if (BUS_READER_USED & BUS_I2C)
	RFID_READER_BUS_I2C
#endif
}rfid_reader_bus_type;

typedef enum{
	PROERTIES_BOOL_CRC_TX = 0,
	PROERTIES_BOOL_CRC_RX,
	PROERTIES_BOOL_PARITY_TX,
	PROERTIES_BOOL_PARITY_RX,
}rfid_properties_bool;

typedef enum{
	PROPERTIES_INT_TX_LASTBITS=0,
	PROPERTIES_INT_RX_LASTBITS,
}rfid_properties_int;

typedef enum{
	MIFARE_UNKNOWN=0,
	MIFARE_CLASSIC_1K,
	MIFARE_CLASSIC_2K,
	MIFARE_CLASSIC_4K,
	MIFARE_CLASSIC_MINI,
	MIFARE_PLUS_1K,
	MIFARE_PLUS_2K,
	MIFARE_PLUS_4K,
	MIFARE_ULTRALIGHT,
	MIFARE_DESFIRE,
	MIFARE_DESFIRE_EV1,
}rfid_target_type;

#define MIFARE_MAX_UID_LEN 10

#endif /* RFID_TYPES_H_ */
