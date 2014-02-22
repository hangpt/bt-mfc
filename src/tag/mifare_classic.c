/*
 * mifare_classic.c
 *
 *  Created on: Feb 21, 2014
 *      Author: nvthanh
 */


#include <tag/mifare_classic.h>
#include <utils/utils.h>
#include <utils/debug.h>

#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)


#define ADDR_EEPROM_AUTH_BLOCK(blk)

#endif

rfid_status mifare_classic_register_eeprom_key(mifare_tag * tag, mifare_classic_block_number  block,mifare_classic_key_type key_type,uint8_t eeprom_index)

{
	MIFARE_CLASSIC_ASSERT(tag);
	if(		 tag->reader_handler->support_auth_crypto_1 == false
			|| eeprom_index > MAX_EEPROM_KEY_NUMBER-1
			|| eeprom_index >= tag->reader_handler->max_eeprom_key ){
		RFATAL("Invalid arguments\n");
		return RFID_EINARG;
	}
	//	tag->num_key_eeprom +=1;
	tag->use_hw_crypto_1 = true;
	uint8_t sector = MFC_SECTOR_OF_BLK(block);

	if(key_type == MFC_KEY_A){
		tag->eeprom_used[sector*2] = 1;
		tag->eeprom_index[sector*2] = eeprom_index;
	}else{
		tag->eeprom_used[sector*2+1] = 1;
		tag->eeprom_index[sector*2 + 1] = eeprom_index;
	}
	return RFID_ESUCCESS;
}

rfid_status mifare_classic_deregister_eeprom_key(mifare_tag * tag, mifare_classic_block_number  block,mifare_classic_key_type key_type)
{
	MIFARE_CLASSIC_ASSERT(tag);
	if(		 tag->reader_handler->support_auth_crypto_1 == false	){
		RFATAL("Invalid arguments\n");
		return RFID_EINARG;
	}
	uint8_t sector = MFC_SECTOR_OF_BLK(block);
	if(key_type == MFC_KEY_A){
		tag->eeprom_used[sector*2] = 0;
	}else{
		tag->eeprom_used[sector*2+1] = 0;
	}
	return RFID_ESUCCESS;
}

rfid_status	 mifare_classic_connect(mifare_tag * tag)
{
	MIFARE_CLASSIC_ASSERT(tag);
	rfid_status	 status = RFID_ESUCCESS;
	rfid_target new_tag;
	switch (tag->reader_handler->reader_type) {
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
	case RFID_READER_HF_READER_ICDREC:
		new_tag.uid_len = 0;
		new_tag.type = MIFARE_UNKNOWN;
		tag->status = MF_TAG_DEACTIVE;
		status =  rfid_select_target(tag->reader_handler,&new_tag);
		if((status == RFID_ESUCCESS || status == RFID_EACK) && new_tag.uid_len == tag->tag.uid_len && (memcmp(new_tag.uid,tag->tag.uid,new_tag.uid_len) == 0)){
			tag->status = MF_TAG_ACTIVE;
			status = RFID_ESUCCESS;
		}
		break;
#endif
#if (READERS_SUPPORTED & READER_CLRC663)
	case RFID_READER_CLRC663:

		break;
#endif
	default:
		break;
	}
	return status;
}

rfid_status	 mifare_classic_disconnect(mifare_tag * tag)
{
	MIFARE_CLASSIC_ACTIVE_ASSERT(tag);
	rfid_status	 status = RFID_ESUCCESS;
	switch (tag->reader_handler->reader_type) {
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
	case RFID_READER_HF_READER_ICDREC:
		status = rfid_deselect_target(tag->reader_handler);
		if((status == RFID_ESUCCESS || status == RFID_EACK) ){
			tag->status = MF_TAG_DEACTIVE;
			status = RFID_ESUCCESS;
		}
		break;
#endif
#if (READERS_SUPPORTED & READER_CLRC663)
	case RFID_READER_CLRC663:

		break;
#endif
	default:
		break;
	}
	return status;
}

rfid_status	 mifare_classic_authenticate (mifare_tag *tag, const mifare_classic_block_number block, const mifare_classic_key key, const mifare_classic_key_type key_type)
{
	MIFARE_CLASSIC_ACTIVE_ASSERT(tag);
	rfid_status	 status = RFID_ESUCCESS;
	uint8_t sector =0;
	//	uint8_t trailer_blk =0;
	switch (tag->reader_handler->reader_type) {
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
	case RFID_READER_HF_READER_ICDREC:
		//FIXME: Only support mifare classic 1K
		sector = MFC_SECTOR_OF_BLK(block);
		if(		tag->reader_handler->support_auth_crypto_1
				&& tag->eeprom_used[sector + (key_type == MFC_KEY_A) ? 0:1] == 1
				&& tag->eeprom_index[sector + (key_type == MFC_KEY_A) ? 0:1] < tag->reader_handler->max_eeprom_key
				&& tag->reader_handler->rfid_authenticate_mifare_classic
				&& tag->reader_handler->rfid_loadkey_from_eeprom
		)
		{
			status=tag->reader_handler->rfid_loadkey_from_eeprom(tag->reader_handler,tag->eeprom_index[sector + (key_type == MFC_KEY_A) ? 0:1]);
			if(status == RFID_ESUCCESS || status == RFID_EACK){
				RDBG("%d, %d, %d, %d\n",block,sector,tag->eeprom_index[sector + (key_type == MFC_KEY_A) ? 0:1], key_type);
				return tag->reader_handler->rfid_authenticate_mifare_classic(tag->reader_handler,&tag->tag,block,key_type,(void*)&tag->eeprom_index[sector + (key_type == MFC_KEY_A) ? 0:1]);
			}
			return status;
		}else{
			//FIXME: Custom command
		}
		break;
#endif

#if (READERS_SUPPORTED & READER_CLRC663)
	case RFID_READER_CLRC663:
		break;
#endif
	default:
		break;
	}
	return status;
}
#include <configs.h>
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
#include <reader/icdrec_hf_reader.h>
rfid_status	icdrec_hf_reader_generic_command(struct rfid_device * thiz, uint8_t cmd,uint8_t * pmeta,size_t metalen,size_t resp_metalen);
#endif

rfid_status	 mifare_classic_read (mifare_tag *tag, const mifare_classic_block_number block, mifare_classic_block data)
{
	MIFARE_CLASSIC_ACTIVE_ASSERT(tag);

	rfid_status status= RFID_ESUCCESS;
	switch (tag->reader_handler->reader_type) {
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
		case RFID_READER_HF_READER_ICDREC:
			HF_READER_NEW_REQ_PACKAGE(req,1);
			GET_PTR(req)[sizeof(ihr_header)] = block;
			HF_READER_NEW_RESP_PACKAGE(resp,0);
			status = rfid_transceive_bytes(tag->reader_handler,GET_PTR(req),GET_LEN(req),GET_PTR(resp),GET_LEN(resp),&GET_SZ_RES(resp),5);
			switch (status) {
				case RFID_ESUCCESS:
				case RFID_EACK:

					break;

				default:
					break;
			}
			break;
#endif
		default:
			break;
	}
}
