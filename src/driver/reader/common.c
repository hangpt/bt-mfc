/*
 * common.c
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */


#include <driver/reader/clrc663.h>
#include <driver/reader/icdrec_hf_reader.h>
#include <utils/debug.h>
#if (BUS_ENABLE & BUS_UART)
#include <driver/uart.h>
#endif

rfid_status generic_rfid_reader_init(rfid_device * thiz)
{
	if(!thiz || !thiz->io_data) {
		RFATAL("Invalid arguments\n");
		return RFID_EINARG;
	}
	switch (thiz->bus_type) {
#if (BUS_READER_USED & BUS_UART)
		case RFID_READER_BUS_UART:
			thiz->io_handler = (void*) uart_open((uint8_t*) thiz->io_data);
			if(!thiz->io_handler){
				RFATAL("Can not open IO Port\n");
				return RFID_EIO;
			}
			uart_set_speed(thiz->io_handler,ICDREC_HF_READER_BAUDRATE_DEFAULT);
			break;
#endif
		default:
			RFATAL("IO error\n");
			return RFID_EIO;
			break;
	}
	thiz->state = RFID_READER_AVAILABLE;
	return  RFID_ESUCCESS;
}

rfid_status	generic_rfid_reader_deinit(struct rfid_device * thiz)
{
	if(!thiz ) {
		RFATAL("Invalid arguments\n");
		return RFID_EINARG;
	}
	switch (thiz->bus_type) {
#if (BUS_READER_USED & BUS_UART)
		case RFID_READER_BUS_UART:
			 uart_close((uart_data*) thiz->io_handler);
			 thiz->io_handler = NULL;
			break;
#endif
		default:
			RFATAL("IO error\n");
			return RFID_EIO;
			break;
	}
	thiz->state = RFID_READER_UNAVAILABLE;
	return  RFID_ESUCCESS;
}

rfid_status  generic_reader_write(rfid_device * thiz ,
		uint8_t * wdata, size_t wsz
)
{
	//TODO:
	rfid_status status= RFID_ESUCCESS ;
	switch (thiz->bus_type) {
#if (BUS_READER_USED & BUS_UART)
		case RFID_READER_BUS_UART:
			uart_write((uart_data*)thiz->io_handler,wdata,wsz);
			break;
#endif
		default:
			RFATAL("Bus type is not supported\n");
			status = RFID_EIO;
			break;
	}
	return  status;
}

rfid_status  generic_reader_read(rfid_device * thiz ,
		uint8_t * rdata, size_t * rsz, size_t szexp,uint32_t timeout
)
{
	if(!thiz) return RFID_EINARG;
	//TODO:
	rfid_status status= RFID_ESUCCESS ;
	size_t sz_read;
	switch (thiz->bus_type) {
#if (BUS_READER_USED & BUS_UART)
		case RFID_READER_BUS_UART:
			sz_read = uart_read((uart_data*)thiz->io_handler,rdata,szexp,timeout);
			if(sz_read <=0){
				return RFID_ETIMEOUT;
			}
			if(rsz) * rsz = sz_read;
			break;
#endif
		default:
			RFATAL("Bus type is not supported\n");
			status = RFID_EIO;
			break;
	}
	return  status;
}


