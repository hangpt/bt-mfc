/*
 * mifare.h
 *
 *  Created on: Feb 21, 2014
 *      Author: nvthanh
 */

#ifndef MIFARE_H_
#define MIFARE_H_

#include <rfid.h>

typedef enum{
	MF_TAG_ACTIVE=0,
	MF_TAG_DEACTIVE
}tag_status;

#define MAX_EEPROM_KEY_NUMBER	256
typedef struct mifare_tag{
	rfid_device * 	reader_handler;
	rfid_target 	tag;
	bool			use_hw_crypto_1;
	uint8_t			num_key_eeprom;
	uint8_t			eeprom_used[MAX_EEPROM_KEY_NUMBER];
	uint8_t			eeprom_index[MAX_EEPROM_KEY_NUMBER];
	tag_status		status;
}mifare_tag;

#define MIFARE_VALID(tag) (tag && tag->reader_handler)
#define MIFARE_CLASSIC_VALID(tag) (MIFARE_VALID(tag) \
		&& (tag->tag.type == MIFARE_CLASSIC_1K || tag->tag.type == MIFARE_CLASSIC_2K || tag->tag.type == MIFARE_CLASSIC_4K))
#define MIFARE_CLASSIC_ACTIVE(tag) (MIFARE_CLASSIC_VALID(tag) \
		&& tag->status==MF_TAG_ACTIVE)

#define MIFARE_ASSERT(tag) if(!MIFARE_VALID(tag)) return RFID_EINARG;
#define MIFARE_CLASSIC_ASSERT(tag) if(!MIFARE_CLASSIC_VALID(tag)) return RFID_EINARG;
#define MIFARE_CLASSIC_ACTIVE_ASSERT(tag) if(!MIFARE_CLASSIC_ACTIVE(tag)) return RFID_EINARG;

rfid_status mifare_get_tag(rfid_device * thiz, mifare_tag * tag);

#endif /* MIFARE_H_ */
