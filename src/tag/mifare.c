/*
 * mifare.c
 *
 *  Created on: Feb 22, 2014
 *      Author: nvthanh
 */


#include <tag/mifare.h>

rfid_status mifare_get_tag(rfid_device * thiz, mifare_tag * tag)
{
	if(!thiz || !tag) return RFID_EINARG;
	rfid_status status=RFID_ESUCCESS;
	status = rfid_select_target(thiz,&tag->tag);
	return status;
}
