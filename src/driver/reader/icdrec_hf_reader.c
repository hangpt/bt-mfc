/*
 * icdrec_hf_reader.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */


#include <configs.h>
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
#include <driver/reader/icdrec_hf_reader.h>
#include <driver/reader/common.h>
#include <utils/debug.h>
#include <utils/utils.h>
#include <utils/endian.h>
#include <string.h>
#if (BUS_ENABLE & BUS_UART)
#include <driver/uart.h>
#endif

uint8_t * dummy_ptr;
size_t dummy_len;
size_t dummy_n;

static rfid_status  icdrec_hf_reader_transceive_bytes(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout);

static char icdrec_hf_reader_checksum(char * pdata, size_t len)
{
	char sum=0;
	for (int i=0;i<len;i++){
		sum += pdata[i];
	}
	sum = ~(sum);
	sum+=1;
	return sum;
}

static inline void icdrec_hf_reader_update_checksum(char * pack, size_t pkglen)
{
	if(pack && pkglen > 0){
		pack[pkglen-1]=icdrec_hf_reader_checksum(pack,pkglen-1);
	}
}

static size_t icdrec_hf_reader_build_package(uint8_t cmd, uint8_t * pmeta, size_t metalen, uint8_t * ppack, size_t szexp)
{
	if(!ppack || ((sizeof(ihr_header) + (pmeta?metalen:0) + 1 + 2) != szexp)){
		return 0;
	}
	ihr_header * hdr = (ihr_header*)ppack;
	uint16_t pkglen;
	hdr->cmd =cmd;
	hdr->from = PACKAGE_FROM_HOST;
	pkglen = sizeof(ihr_header);
	if(pmeta && metalen >0){
		memcpy(ppack+ sizeof(ihr_header),pmeta,metalen);
		pkglen += (metalen) ;
	}
	pkglen += 1; //checksum byte
	hdr->length = htobe16(pkglen);
	icdrec_hf_reader_update_checksum((char*)ppack,pkglen);
	ppack[pkglen] ='\r';
	ppack[pkglen+1] ='\n';
	return (size_t)(pkglen+2);
}

static inline rfid_status  icdrec_hf_reader_write(rfid_device * thiz ,uint8_t * wdata, size_t wsz)
{
	return generic_reader_write(thiz,wdata,wsz);
}

static inline rfid_status  icdrec_hf_reader_read(rfid_device * thiz ,uint8_t * rdata, size_t * rsz, size_t szexp,uint32_t timeout)
{
	return generic_reader_read(thiz,rdata,rsz,szexp,timeout);
}


static inline rfid_status	icdrec_hf_reader_init(struct rfid_device * thiz)
{
	return generic_rfid_reader_init(thiz);
}

static inline rfid_status	icdrec_hf_reader_deinit(struct rfid_device * thiz)
{
	return generic_rfid_reader_deinit(thiz);
}


/*static */rfid_status	icdrec_hf_reader_generic_command(struct rfid_device * thiz, uint8_t cmd,uint8_t * pmeta,size_t metalen,size_t resp_metalen)
{
	if(!thiz || thiz->state != RFID_READER_AVAILABLE) {
		return RFID_EINARG;
	}
	rfid_status status= RFID_ESUCCESS ;
	//TODO: Test

	HF_READER_NEW_REQ_PACKAGE(req,metalen);
	GET_SZ_BUILT(req) = icdrec_hf_reader_build_package(cmd,pmeta,metalen,GET_PTR(req),GET_LEN(req));
	RDBG(" CMD: 0x%X\n",cmd);
	RFID_HEXDUMP(GET_PTR(req),GET_LEN(req),"pkg",0);
	HF_READER_NEW_RESP_PACKAGE(res,resp_metalen);
	status = icdrec_hf_reader_transceive_bytes(thiz,GET_PTR(req),GET_SZ_BUILT(req),GET_PTR(res),GET_LEN(res),&GET_SZ_RES(res),20);
	switch (status) {
	case RFID_ESUCCESS:
	case RFID_EACK:
		RDBG("Success\n");
		break;
#if 1
	case RFID_EIO:
		RFATAL("IO error\n");
		break;
	case RFID_ENAK:
		RFATAL("NAK error\n");
		break;
	case RFID_ETIMEOUT:
		RFATAL("Time out\n");
		break;
	case RFID_ERESP:
		RFATAL("Failed responding\n");
		break;

#endif
	default:
		RFATAL("Unknown error\n");
		break;
	}
	CLEAR_WARNING(req);
	return  status;
}

static inline rfid_status	icdrec_hf_reader_generic_command_no_meta(struct rfid_device * thiz, uint8_t cmd)
{
	return icdrec_hf_reader_generic_command(thiz,cmd,NULL,0,0);
}

static rfid_status	icdrec_hf_reader_poll_target(struct rfid_device * thiz)
{
	if(!thiz || thiz->state != RFID_READER_AVAILABLE) {
		return RFID_EINARG;
	}
	//TODO: Test
#if 0
	uint8_t pbtTx[1]={0x7F | 0x80},pbtRx[1];
	size_t rxsz;
	icdrec_hf_reader_write(thiz,pbtTx,1);
	icdrec_hf_reader_read(thiz,pbtRx,&rxsz,1,1);
	if(rxsz > 0){
		RDBG("0x%X\n",pbtRx[0]);
	}
#else
	return icdrec_hf_reader_generic_command_no_meta(thiz,HF_READER_CMD_REQA);
#endif
}

static rfid_status	icdrec_hf_reader_select_target(struct rfid_device * thiz, rfid_target * target)
{

	rfid_status status= RFID_ESUCCESS ;
#if 1
	HF_READER_NEW_REQ_PACKAGE(req,0);
	GET_SZ_BUILT(req) = icdrec_hf_reader_build_package(HF_READER_CMD_ANTICOLLISION,NULL,0,GET_PTR(req),GET_LEN(req));
	RFID_HEXDUMP(GET_PTR(req),GET_LEN(req),"pkg",0);
	HF_READER_NEW_RESP_PACKAGE(res,1+MIFARE_MAX_UID_LEN);
	status = icdrec_hf_reader_transceive_bytes(thiz,GET_PTR(req),GET_SZ_BUILT(req),GET_PTR(res),GET_LEN(res),&GET_SZ_RES(res),2);
	uint8_t uid_len;
	switch (status) {
	case RFID_ESUCCESS:
	case RFID_EACK:
//		hdr = (ihr_header_response*)GET_PTR(res);
		uid_len = GET_PTR(res)[sizeof(ihr_header_response)];
		if(uid_len && target){
			memcpy(target->uid,GET_PTR(res)+sizeof(ihr_header_response),uid_len);
			target->uid_len = uid_len;
			if(uid_len==4){
				target->type= MIFARE_CLASSIC_1K;
			}else	if(uid_len==7){
				target->type= MIFARE_DESFIRE_EV1;
			}
		}
		break;
#if 1
	case RFID_EIO:
		RFATAL("IO error\n");
		break;
	case RFID_ENAK:
		RFATAL("NAK error\n");
		break;
	case RFID_ETIMEOUT:
		RFATAL("Time out\n");
		break;
	case RFID_ERESP:
		RFATAL("Failed responding\n");
		break;
#endif
	default:
		RFATAL("Unknown error\n");
		break;
	}
	CLEAR_WARNING(req);
	return  status;
#else
	status = icdrec_hf_reader_generic_command(thiz,HF_READER_CMD_ANTICOLLISION,NULL,0,1+10);
#endif
}

static rfid_status	icdrec_hf_reader_deselect_target(struct rfid_device * thiz)
{
	return icdrec_hf_reader_generic_command_no_meta(thiz,HF_READER_CMD_HALT);
}

static rfid_status	icdrec_hf_reader_halt_target(struct rfid_device * thiz)
{
	return icdrec_hf_reader_generic_command_no_meta(thiz,HF_READER_CMD_HALT);
}

static rfid_status	icdrec_hf_reader_wakeup_target(struct rfid_device * thiz)
{
	return icdrec_hf_reader_generic_command_no_meta(thiz,HF_READER_CMD_WAKEUP);
}

static rfid_status	icdrec_hf_reader_check_resp_package(uint8_t * rdata, size_t rsz)
{
	if(rdata && rsz > (sizeof(ihr_header_response)+1+2)){
		ihr_header_response * hdr =(ihr_header_response *) rdata;

		uint16_t length = htobe16(hdr->length);
		if(length != rsz-2 || rdata[rsz-2]!='\r'|| rdata[rsz-1]!='\n'){
			return RFID_ERESP;
		}
		if(hdr->resp == HF_READER_ACK){
			return RFID_EACK;
		}else{
			return RFID_ENAK;
		}
	}else{
		RFATAL("Failed responding\n");
		return RFID_ERESP;
	}
}

static rfid_status  icdrec_hf_reader_transceive_bytes(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout)
{
	rfid_status status= RFID_ESUCCESS ;
	if(!thiz || !wdata || wsz <=0 ){
		return RFID_EINARG;
	}
	status = icdrec_hf_reader_write(thiz,wdata,wsz);
	if(status != RFID_ESUCCESS) return status;
	size_t rlen;
	status = icdrec_hf_reader_read(thiz,rdata,&rlen,szexp,timeout);
	if(status != RFID_ESUCCESS) return status;
	RFID_HEXDUMP(rdata,rlen,"resp",0);
	if((status = icdrec_hf_reader_check_resp_package(rdata,rlen))==RFID_ESUCCESS){
		if(rsz) * rsz=rlen;
	}
	return  status;
}

static rfid_status icdrec_hf_reader_loadkey_from_eeprom(struct rfid_device * thiz, uint8_t eeprom_index)
{
	if(!thiz || eeprom_index >= HF_READER_MAX_EEPROM_KEY_STORED) return RFID_EINARG;
	RDBG("\n");
	return icdrec_hf_reader_generic_command(thiz,HF_READER_CMD_LOADKEYEEPROM_MFC,&eeprom_index,1,0);
}

static rfid_status icdrec_hf_reader_writekey_to_eeprom(struct rfid_device * thiz, uint8_t eeprom_index, uint8_t key[6])
{
	RDBG("\n");
	if(!thiz || !key || eeprom_index >= HF_READER_MAX_EEPROM_KEY_STORED) return RFID_EINARG;
	uint8_t metadata[7];
	memcpy(metadata,key,6);
	metadata[6]= eeprom_index;
	return icdrec_hf_reader_generic_command(thiz,HF_READER_CMD_WRITEKEYEEPROM_MFC,metadata,7,0);
}

static rfid_status icdrec_hf_reader_authenticate_mifare_classic(struct rfid_device * thiz, rfid_target * tag,uint8_t block, uint8_t key_type,void * custom)
{
	rfid_status status= RFID_ESUCCESS;
	RDBG("\n");

	return status;
}

void register_icdrec_hf_reader_interface(rfid_device * device, rfid_reader_bus_type bus_type)
{
	if(!device) return ;
	strcpy(device->name, 				"HF READER - ICDREC");
	device->reader_type					= RFID_READER_HF_READER_ICDREC;
	device->bus_type 					= bus_type;
	device->io_handler 					= NULL;
	device->io_data						= NULL;
	device->support_auth_crypto_1		= true;
	device->max_eeprom_key				= HF_READER_MAX_EEPROM_KEY_STORED;
	device->rfid_reader_init 			= icdrec_hf_reader_init;
	device->rfid_reader_deinit 			= icdrec_hf_reader_deinit;
	device->rfid_set_properties_bool 	= UNIMPLEMENTED_FUNCTION;
	device->rfid_set_properties_int 	= UNIMPLEMENTED_FUNCTION;
	device->rfid_poll_target 			= icdrec_hf_reader_poll_target;
	device->rfid_loadkey_from_eeprom	= icdrec_hf_reader_loadkey_from_eeprom;
	device->rfid_writekey_to_eeprom		= icdrec_hf_reader_writekey_to_eeprom;
	device->rfid_authenticate_mifare_classic = icdrec_hf_reader_authenticate_mifare_classic;
	device->rfid_select_target 			= icdrec_hf_reader_select_target;
	device->rfid_deselect_target 		= icdrec_hf_reader_deselect_target;
	device->rfid_halt_target 			= icdrec_hf_reader_halt_target;
	device->rfid_wakeup_target 			= icdrec_hf_reader_wakeup_target;
	device->rfid_transceive_bytes 		= icdrec_hf_reader_transceive_bytes;
	//FIXME: Support future
	device->rfid_transceive_bits 		= UNIMPLEMENTED_FUNCTION;
}

#endif

