/*
 * endian.h
 *
 *  Created on: Oct 31, 2013
 *      Author: nvthanh
 */

#ifndef ENDIAN_H_
#define ENDIAN_H_

#include <stdio.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 	4321

#define __BYTE_ORDER	__LITTLE_ENDIAN


#define __bswap16(A) ((((uint16_t)(A) & 0xff00) >> 8) | \
(((uint16_t)(A) & 0x00ff) << 8))

#define __bswap32(A) (((((uint32_t)(A) & 0xff000000) >> 24) | \
(((uint32_t)(A) & 0x00ff0000) >> 8) | \
(((uint32_t)(A) & 0x0000ff00) << 8) | \
(((uint32_t)(A) & 0x000000ff) << 24)))

#if (__BYTE_ORDER  == __LITTLE_ENDIAN)

#define htobe16(x) __bswap16(x)
#define htole16(x) (x)
#define be16toh(x) __bswap16(x)
#define le16toh(x) (x)

#define htobe32(x) __bswap32(x)
#define htole32(x) (x)
#define be32toh(x) __bswap32(x)
#define le32toh(x) (x)

#else
//__BIG_ENDIAN

#define htobe16(x) (x)
#define htole16(x) __bswap16(x)
#define be16toh(x) (x)
#define le16toh(x) __bswap16(x)

#define htobe32(x) (x)
#define htole32(x) __bswap32(x)
#define be32toh(x) (x)
#define le32toh(x) __bswap32(x)
#endif

#ifdef __cplusplus
}//extern "C" {
#endif

#endif /* ENDIAN_H_ */
