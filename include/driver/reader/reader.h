/*
 * reader.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef READER_H_
#define READER_H_

#include <configs.h>
#include <rfid_types.h>

#include <stdbool.h>
struct rfid_reader_io{
	size_t (* read)(void * driver_handler, uint8_t * res, size_t szexp,uint32_t timeout);
	size_t (* write)(void * driver_handler, uint8_t * res, size_t szexp,uint32_t timeout);
};

typedef struct rfid_target{
	rfid_target_type type;
	uint8_t uid_len;
	uint8_t uid[MIFARE_MAX_UID_LEN];
}rfid_target;

typedef struct rfid_device{
	char 					name[MAX_NAME_LEN];
	void *					io_data;
	rfid_reader_type 		reader_type;
	rfid_reader_bus_type	bus_type;
	void * 					io_handler;
	rfid_reader_state		state;
	bool					support_auth_crypto_1;
	uint16_t 				max_eeprom_key;

//	struct rfid_reader_io 	io;
	rfid_status	(* rfid_reader_init)(struct rfid_device * thiz);
	rfid_status	(* rfid_reader_deinit)(struct rfid_device * thiz);
	rfid_status	(* rfid_poll_target)(struct rfid_device * thiz);
	rfid_status (* rfid_select_target)(struct rfid_device * thiz, rfid_target * target);
	rfid_status (* rfid_deselect_target)(struct rfid_device * thiz);
	rfid_status (* rfid_halt_target)(struct rfid_device * thiz);
	rfid_status (* rfid_wakeup_target)(struct rfid_device * thiz);
	rfid_status (* rfid_authenticate_mifare_classic)(struct rfid_device * thiz, rfid_target * tag, uint8_t block, uint8_t key_type,void * custom);
	rfid_status (* rfid_loadkey_from_eeprom)(struct rfid_device * thiz,uint8_t eeprom_index);
	rfid_status (* rfid_writekey_to_eeprom)(struct rfid_device * thiz,uint8_t eeprom_index, uint8_t key[6]);
	rfid_status (* rfid_set_properties_bool)(struct rfid_device * thiz, rfid_properties_bool prop, bool value);
	rfid_status (* rfid_set_properties_int)(struct rfid_device * thiz, rfid_properties_int prop, int value);
	rfid_status (* rfid_transceive_bytes)(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout);
	rfid_status (* rfid_transceive_bits)(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout);
}rfid_device;


rfid_device * 	rfid_new_device( rfid_reader_type reader_type,rfid_reader_bus_type bus_type, void * init_data);
rfid_status	  	rfid_init(rfid_device * rd);
rfid_status		rfid_deinit(rfid_device * rd);
rfid_status		rfid_poll_target(struct rfid_device * thiz);
rfid_status		rfid_select_target(struct rfid_device * thiz,rfid_target  * target);
rfid_status		rfid_deselect_target(struct rfid_device * thiz);
rfid_status		rfid_halt_target(struct rfid_device * thiz);
rfid_status		rfid_wakeup_target(struct rfid_device * thiz);
rfid_status		rfid_transceive_bytes(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout);
rfid_status		rfid_transceive_bits(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout);

rfid_status 	rfid_set_properties_bool(struct rfid_device * thiz, rfid_properties_bool prop, bool value);
rfid_status 	rfid_set_properties_int(struct rfid_device * thiz, rfid_properties_int prop, int value);

#endif /* READER_H_ */
