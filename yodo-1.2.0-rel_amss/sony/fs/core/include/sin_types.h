/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 *                                                                            *
 * [Bytes]Group    Field                      Value / Comment                 *
 * ************************************************************************** *
 * ********************** SIN VERSION 3 - HEADER **************************** *
 * ************************************************************************** *
 * [1]           uint8_t   version            0x03                            *
 * [3]           uint8_t   magic[3]           "SIN"                           *
 * [4]           uint32_t  size_header                                        *
 * [4]           uint32_t  type_payload       e.g. SIN_PAYLOAD_TYPE__PLT_BOOT *
 * [4]           uint32_t  type_payload_hash  e.g. SIN_HASH_TYPE__SHA_256     *
 * [4]           uint32_t  reserved                                           *
 * -------------------------------------------------------------------------- *
 * [4]           uint32_t  size_block_info_list                               *
 *   [4]b1         uint32_t payload_block_length  How many bytes of payload   *
 *                                            data on which the calculated    *
 *                                            hash is based upon              *
 *   [*]b1         uint8_t payload_block_hash[*]  Length depends on           *
 *                                           type_payload_hash                *
 *   [4]b2         uint32_t payload_block_length  How many bytes of payload   *
 *                                            data on which the calculated    *
 *                                            hash is based upon              *
 *   [*]b2         uint8_t payload_block_hash[*]  Length depends on           *
 *                                           type_payload_hash                *
 *                       ...                                                  *
 *                                                                            *
 *                                                                            *
 *   [4]bN         uint32_t payload_block_length  How many bytes of payload   *
 *                                            data on which the calculated    *
 *                                            hash is based upon              *
 *   [*]bN         uint8_t payload_block_hash[*]  Length depends on           *
 *                                           type_payload_hash                *
 * -------------------------------------------------------------------------- *
 * [4]           uint32_t  length_signature   e.g. 256 in case of 2048bits key*
 *   [*]           uint8_t signature[*]       e.g. length_signature bytes     *
 * ************************************************************************** *
 * ********************** SIN VERSION 3 - PAYLOAD *************************** *
 * ************************************************************************** *
 * [*]           uint8_t payload_data[*]      Payload data                    *
 * ************************************************************************** *
 *****************************************************************************/
#ifndef SIN_TYPES_H__
#define SIN_TYPES_H__

#include "sin_payload_types.h"
#include <stdlib.h>
#include <stdint.h>

#define SIN_NONE       (0)
#define SIN_SHA1_RSA   (1)
#define SIN_SHA256_RSA (2)

struct sin_block_info {
	uint32_t  payload_block_length;         /* Number of payload data bytes
						   this hash is based on */
	uint8_t *payload_block_hash;           /* Hash of payload data */
};

struct sin_asahi_signature {
	uint32_t size_asahi_signature;          /* Total size of the ASAHI
						   signature data */
	uint8_t *asahi_signature;               /* ASAHI signature data */
};

struct sin_header_static_field {
	uint32_t size_header;                   /* Size [bytes] of the S1
						   Header, i.e. size_header =
						   sin_header +
						   size_block_info_list +
						   length_signature */
	uint32_t type_payload;			/* Type of payload carried in
						   this SIN package */
	unsigned int type_payload_hash;		/* Type of hash algorithm used
						   for the calculated block
						   hashes, typical
						   SIN_SHA256_HASH */
};

#endif
