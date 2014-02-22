/*
 * mifare_classic.h
 *
 *  Created on: Feb 21, 2014
 *      Author: nvthanh
 */

#ifndef MIFARE_CLASSIC_H_
#define MIFARE_CLASSIC_H_

#include <tag/mifare.h>
#define MAX_BLK_NUMBER_1K	64
#define MFC_BLOCK_SZ 		16
#define MFC_KEY_SZ 			6
typedef uint8_t mifare_classic_key[MFC_KEY_SZ];
typedef uint8_t mifare_classic_block_number;
typedef uint8_t mifare_classic_block_base;
typedef mifare_classic_block_base mifare_classic_block[MFC_BLOCK_SZ];

#define NEXT_DATA_BLK(x) ( ((x%4)==2)?(x+2):(x+1) )
#define PREV_DATA_BLK(x) ( (x==0)?x: (((x%4)==0) ? (x-2):(x-1)) )
#define TRAILER_BLK(x) (x+ (3-(x%4)))

#define MFC_TRAILER_BLK(input)   (((input)/4)*4+3) /**< Get trailer block for a certain block.\nEx: for block 2, the trailer block must be 3*/
#define MFC_BEGIN_BLK(input)  	(((input)/4)*4) /**< Get begin block for a certain block \nEx: for block 2, the trailer block must be 0*/
#define MFC_SECTOR_OF_BLK(input) (((input)/4)) /**< Get sector number of certain block*/

#if 1
/*!
 * \brief Mifare classic block information
 */
typedef union mifare_classic_global_block {
    unsigned char data[16]; /**< Data of normal data block */
    struct {
    	uint32_t value; /**< Value*/
		uint32_t value_;/**< Value inverted*/
		uint32_t value__; /**< Value */
		mifare_classic_block_number address; /**< Address block*/
		mifare_classic_block_number address_;  /**< Address block inverted*/
		mifare_classic_block_number address__; /**< Address block */
		mifare_classic_block_number address___; /**< Address block inverted*/
    } value; /**< Info of Value block*/
    struct {
    	mifare_classic_key key_a; /**<Key A 6 bytes*/
    	uint8_t access_bits[3]; /**<Access bits*/
    	uint8_t gpb; /**<General purpose byte*/
    	mifare_classic_key key_b; /**<Key B 6 bytes*/
    } trailer; /**< Info of trailer block*/
}mifare_classic_global_block;
#endif

/*!
 * \brief Enumarate key type
 */
typedef enum{
	MFC_KEY_A=0, /**<Key A*/
	MFC_KEY_B, /**<Key B*/
}mifare_classic_key_type;

rfid_status mifare_classic_register_eeprom_key(mifare_tag * tag, mifare_classic_block_number  block,mifare_classic_key_type key_type,uint8_t eeprom_index);
rfid_status mifare_classic_deregister_eeprom_key(mifare_tag * tag, mifare_classic_block_number  block,mifare_classic_key_type key_type);

/*!
 * \brief Connect to a Mifare Classic tag
 * \param[in] tag Information of tag (UID, SAK, ...)
 * \return #rfid_status_code
 */

rfid_status	 mifare_classic_connect(mifare_tag * tag);

/*!
 * \brief Disconnect MFC tag
 * \param[in] tag Information of tag (UID, SAK, ...)
 * \return #rfid_status_code
 */

rfid_status 	 mifare_classic_disconnect(mifare_tag * tag);


/*!
 * \brief Authentication with a block of MFC tag
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[in] Key data for authentication block
 * \param[in] key_type Type of key, #MFC_KEY_A, #MFC_KEY_B
 * \return #rfid_status
 */

rfid_status	 mifare_classic_authenticate (mifare_tag *tag, const mifare_classic_block_number block, const mifare_classic_key key, const mifare_classic_key_type key_type);

/*!
 * \brief Read data from a block of MFC tag
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[out] data Retreived data from block.
 * \return #rfid_status
 */

rfid_status	 mifare_classic_read (mifare_tag *tag, const mifare_classic_block_number block, mifare_classic_block data);

/*!
 * \brief Initial a value block and write the init value to this block
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[in] addr Block number from 00h to 0x3Fh
 * \param[in] value Init value for value block
 * \return #rfid_status
 */

rfid_status	 mifare_classic_init_value (mifare_tag *tag, const mifare_classic_block_number block, const int32_t value, const mifare_classic_block_number adr);

/*!
 * \brief Read value and address of block from value block
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[out] value Retreived value from value block
 * \param[out] adr Retreived address of block from value block
 * \return #rfid_status
 */

rfid_status	 mifare_classic_read_value (mifare_tag *tag, const mifare_classic_block_number block, int32_t *value, mifare_classic_block_number *adr);

/*!
 * \brief Write data to a data block
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[in] data 16 bytes data will be written to block
 * \return #rfid_status
 */

rfid_status	 mifare_classic_write (mifare_tag *tag, const mifare_classic_block_number block, const mifare_classic_block data);

/*!
 * \brief Increase value that is stored in value block
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[in] amount Value will be increased
 * \return #rfid_status
 */

rfid_status	 mifare_classic_increment (mifare_tag *tag, const mifare_classic_block_number block, const uint32_t amount);

/*!
 * \brief Decrease value that is stored in value block
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \param[in] amount Value will be decreased
 * \return #rfid_status
 */

rfid_status	 mifare_classic_decrement (mifare_tag *tag, const mifare_classic_block_number block, const uint32_t amount);

/*!
 * \brief Restore value from a block to volatile memory.
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \return #rfid_status
 */

rfid_status	 mifare_classic_restore (mifare_tag *tag, const mifare_classic_block_number block);

/*!
 * \brief Transfer value from volatile memory to a block.
 * \param[in] tag Information of tag
 * \param[in] block Block number from 00h to 0x3Fh
 * \return #rfid_status
 */

rfid_status	 mifare_classic_transfer (mifare_tag *tag, const mifare_classic_block_number block);

#endif /* MIFARE_CLASSIC_H_ */
