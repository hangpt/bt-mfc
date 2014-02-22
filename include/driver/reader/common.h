/*
 * common.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef COMMON_H_
#define COMMON_H_
#include <driver/reader/reader.h>

rfid_status generic_rfid_reader_init(rfid_device * thiz);
rfid_status	generic_rfid_reader_deinit(struct rfid_device * thiz);
rfid_status  generic_reader_write(rfid_device * thiz ,	uint8_t * wdata, size_t wsz
);
rfid_status  generic_reader_read(rfid_device * thiz,uint8_t * rdata, size_t * rsz, size_t szexp,uint32_t timeout
);

#endif /* COMMON_H_ */
