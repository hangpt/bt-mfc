/*!
 * @file utils.h
 * Created on: Oct 17, 2013
 * @brief Some Utilities for project.
 * @authors Thanh Nguyen, thanhnv@centic.vn or thanh_bk05@yahoo.com
 * @copyright CENTIC (http://www.centic.vn) & ICDREC (http://www.icdrec.edu.vn)
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#define	NFC_HD_COLUMN_MASK		0xff
#define	NFC_HD_DELIM_MASK		0xff00
#define	NFC_HD_OMIT_COUNT		(1 << 16)
#define	NFC_HD_OMIT_HEX			(1 << 17)
#define	NFC_HD_OMIT_CHARS		(1 << 18)

#define RFID_HEXDUMP(ptr,len,header,flags) rfid_hexdump(ptr,len,header,flags)

void rfid_hexdump(const void *ptr, int length, const char *hdr, int flags);
void rfid_calculate_crc16(uint8_t*blk,uint32_t sz,uint32_t preset,uint8_t * out);
void rfid_rand_bytes(uint8_t * out, size_t sz,uint8_t min, uint8_t max);

#ifdef __cplusplus
}//extern "C" {
#endif

#endif /* UTILS_H_ */
