/*
 * clrc663.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */


#include <configs.h>
#if (READERS_SUPPORTED & READER_CLRC663)
#include <driver/reader/clrc663.h>
#include <driver/reader/common.h>
#include <utils/debug.h>
#include <utils/utils.h>
#include <string.h>

static inline rfid_status  clrc663_reader_write(rfid_device * thiz ,uint8_t * wdata, size_t wsz)
{
	return generic_reader_write(thiz,wdata,wsz);
}

static inline rfid_status  clrc663_reader_read(rfid_device * thiz ,	uint8_t * rdata, size_t * rsz, size_t szexp,uint32_t timeout)
{
	return generic_reader_read(thiz,rdata,rsz,szexp,timeout);
}

static inline  rfid_status	clrc663_reader_init(struct rfid_device * thiz)
{
	return generic_rfid_reader_init(thiz);
}

static inline rfid_status	clrc663_reader_deinit(struct rfid_device * thiz)
{
	return generic_rfid_reader_deinit(thiz);
}

static rfid_status	clrc663_poll_target(struct rfid_device * thiz)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

static rfid_status	clrc663_select_target(struct rfid_device * thiz, rfid_target * target)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

static rfid_status	clrc663_deselect_target(struct rfid_device * thiz)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

static rfid_status	clrc663_halt_target(struct rfid_device * thiz)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

static rfid_status	clrc663_wakeup_target(struct rfid_device * thiz)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

rfid_status  clrc663_transceive_bytes(struct rfid_device * thiz, uint8_t * wdata, size_t wsz, uint8_t * rdata,size_t szexp, size_t * rsz, uint32_t timeout)
{
	rfid_status status= RFID_ESUCCESS ;

	return  status;
}

void register_clrc663_reader_interface(rfid_device * device, rfid_reader_bus_type bus_type)
{
	if(!device) return ;
	strcpy(device->name, "CLRC663 - NXP");
	device->reader_type= RFID_READER_CLRC663;
	device->bus_type = bus_type;
	device->io_handler = NULL;

	device->rfid_reader_init = clrc663_reader_init;
	device->rfid_reader_deinit = clrc663_reader_deinit;
	device->rfid_set_properties_bool = UNIMPLEMENTED_FUNCTION;
	device->rfid_set_properties_int = UNIMPLEMENTED_FUNCTION;
	device->rfid_poll_target = clrc663_poll_target;
	device->rfid_select_target = clrc663_select_target;
	device->rfid_deselect_target = clrc663_deselect_target;
	device->rfid_halt_target = clrc663_halt_target;
	device->rfid_wakeup_target = clrc663_wakeup_target;
	device->rfid_transceive_bytes = clrc663_transceive_bytes;
	device->rfid_transceive_bits 		= UNIMPLEMENTED_FUNCTION;
	//FIXME: Support future
}


#endif

