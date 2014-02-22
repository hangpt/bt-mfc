/*
 * rfid.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#include <driver/reader/reader.h>
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
#include <driver/reader/icdrec_hf_reader.h>
#endif
#if (READERS_SUPPORTED & READER_CLRC663)
#include <driver/reader/clrc663.h>
#endif
#include <utils/debug.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_READER_TYPE (\
		(READERS_SUPPORTED & READER_HF_READER_ICDREC) ? 1: 0 \
				+ (READERS_SUPPORTED & READER_CLRC663) ? 1: 0 \
						+ (READERS_SUPPORTED & READER_PN532) ? 1: 0 \
)


void * rfid_malloc(size_t sz)
{
	if(sz<=0) return NULL;
	void * ret = malloc(sz);
	if(!ret){
		RFATAL("Out of memory!!!\n");
		return NULL;
	}
	memset(ret,0,sz);
	return ret;
}

rfid_device * 	rfid_new_device( rfid_reader_type reader_type,rfid_reader_bus_type bus_type, void * init_data)
{
	rfid_device * 	rd = NULL;

	rd=(rfid_device*)rfid_malloc(sizeof(rfid_device));
	if(!rd) return NULL;
	switch (reader_type) {
#if (READERS_SUPPORTED & READER_HF_READER_ICDREC)
	case RFID_READER_HF_READER_ICDREC:
		register_icdrec_hf_reader_interface(rd,bus_type);
		break;
#endif
#if (READERS_SUPPORTED & READER_CLRC663)
	case RFID_READER_CLRC663:
		register_clrc663_reader_interface(rd,bus_type);
		break;
#endif
	default:
		break;
	}
	rd->io_data = init_data;
	return rd;
}

rfid_status	  	rfid_init(rfid_device * rd)
{
	if(rd && rd->rfid_reader_init){
		return rd->rfid_reader_init(rd);
	}
	return RFID_EIMPL;
}

rfid_status		rfid_deinit(rfid_device * rd)
{
	if(rd && rd->rfid_reader_deinit){
		return rd->rfid_reader_deinit(rd);
	}
	return RFID_EIMPL;
}

rfid_status	rfid_poll_target(struct rfid_device * thiz)
{
	if(thiz && thiz->rfid_poll_target){
		return thiz->rfid_poll_target(thiz);
	}
	return RFID_EIMPL;
}

rfid_status rfid_select_target(struct rfid_device * thiz, rfid_target * target)
{
	if(thiz && thiz->rfid_select_target){
		return thiz->rfid_select_target(thiz,target);
	}
	return RFID_EIMPL;
}

rfid_status  rfid_deselect_target(struct rfid_device * thiz)
{
	if(thiz && thiz->rfid_deselect_target){
		return thiz->rfid_deselect_target(thiz);
	}
	return RFID_EIMPL;
}

rfid_status rfid_halt_target(struct rfid_device * thiz)
{
	if(thiz && thiz->rfid_halt_target){
		return thiz->rfid_halt_target(thiz);
	}
	return RFID_EIMPL;
}

rfid_status  rfid_wakeup_target(struct rfid_device * thiz)
{
	if(thiz && thiz->rfid_wakeup_target){
		return thiz->rfid_wakeup_target(thiz);
	}
	return RFID_EIMPL;
}

rfid_status		rfid_transceive_bytes(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout)
{
	if(thiz && thiz->rfid_transceive_bytes){
		return thiz->rfid_transceive_bytes(thiz,wdata, wsz,rdata,szexp,rsz,timeout);
	}
	return RFID_EIMPL;
}

rfid_status     rfid_transceive_bits(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout)
{

	return RFID_EIMPL;
}

rfid_status 	rfid_set_properties_bool(struct rfid_device * thiz, rfid_properties_bool prop, bool value)
{

	return RFID_EIMPL;
}

rfid_status 	rfid_set_properties_int(struct rfid_device * thiz, rfid_properties_int prop, int value)
{

	return RFID_EIMPL;
}
