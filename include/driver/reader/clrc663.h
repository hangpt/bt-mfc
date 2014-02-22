/*
 * clrc663.h
 *
 *  Created on: Feb 20, 2014
 *      Author: nvthanh
 */

#ifndef CLRC663_H_
#define CLRC663_H_

#include <driver/reader/reader.h>
#if (READERS_SUPPORTED & READER_CLRC663)
void register_clrc663_reader_interface(rfid_device * device, rfid_reader_bus_type bus_type);
#endif
#endif /* CLRC663_H_ */
