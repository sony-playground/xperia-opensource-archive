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
 * DESCRIPTION:                                                               *
 *     The SIN Parser is responsible for parsing SIN files and by that        *
 *   guarantees that the SIN files have a correct format (SIN version 3),     *
 *   i.e. guarantees that all necessary fields of the SIN format are          *
 *   available.                                                               *
 *     It is  n o t  of the SIN Parser's responsibility to do the actual      *
 *   verification of the SIN signature, block hashes or other parts that      *
 *   requires cryptographic operations. The responsibility of the SIN Parser  *
 *   is merely to allow access to specific parts of the SIN content, e.g. the *
 *   static header fields, the block informations and the ASAHI signature.    *
 *     The SIN Parser guarantees that the format of the SIN file is correct,  *
 *   which means it checks static header fields, such as SIN version, SIN     *
 *   magic number, SIN header size, SIN payload type and SIN block hash type  *
 *   are correct. The SIN Parser also verifies that the sizes of the block    *
 *   informations are correct.                                                *
 *                                                                            *
 * HOW TO USE:                                                                *
 *                                                                            *
 *   required operation =   ------------------------>                         *
 *   optional operation =   ---------------------//->                         *
 *                                                                            *
 *   *--------------------*                           *--------------------*  *
 *   *      Client        *                           *     SIN Parser     *  *
 *   *--------------------*                           *--------------------*  *
 *   struct sin_header *handle;                                             *
 *   uint8_t sin_buffer[];                                                    *
 *   uint32_t length_sin_buffer;                                              *
 *   (1)---sinparser_init(&handle, sin_buffer, length_buffer)------------>    *
 *                                                                            *
 *   sin_header_static_field* s_header = NULL;                              *
 *   (2a)---sinparser_get_header(handle, &s_header)-------------------//->    *
 *                                                                            *
 *   sin_asahi_signature* asahi_signature = NULL;                           *
 *   (2b)---sinparser_get_asahi_data(handle, &asahi_signature)--------//->    *
 *                                                                            *
 *   uint32_t nof_blocks;                                                     *
 *   uint32_t i;                                                              *
 *   sin_block_info* block_info = NULL;                                     *
 *   (2c)---sinparser_get_nof_hash_blocks(handle, &nof_blocks)--------//->    *
 *   for(i=0; i<nof_blocks; i++){                                             *
 *     (2d)---sinparser_get_block_info(handle, i, &block_info)--------//->    *
 *   }                                                                        *
 *                                                                            *
 *   (3)---sinparser_deinit(handle)-------------------------------------->    *
 *                                                                            *
 * NOTE: All functions / methods returns a int status / error code,    *
 *       which indicates the outcome of the operation, thus all return values *
 *       should be checked with the s1 utility macros, i.e. as exemplified    *
 *       below.                                                               *
 *                                                                            *
 *       int res;                                                      *
 *                                                                            *
 *       res = sinparser_get_asahi_data(handle, &asahi_signature);            *
 *       if(SUCCEEDED(res)){                                                  *
 *         // Operation succeeded / is allowed, do something                  *
 *       }else{                                                               *
 *         // Operation failed / is not allowed, do something else            *
 *       }                                                                    *
 *                                                                            *
* NOTE: The SIN Parser operates directly on the SIN buffer provided when     *
*       creating the SIN Parser, thus this memory buffer must be kept intact *
*       during the hole session. Once sinparser_deinit(...) is called, the   *
*       client can destroy its SIN buffer.                                   *
*                                                                            *
* NOTE: As the SIN Parser operates directly on the SIN buffer provided at    *
*       creation time, it  d o e s  n o t  copies any data. This means that  *
*       when e.g. requesting ASAHI data, only a pointer to correct part in   *
*       the SIN buffer is given to the client, i.e. no copy of data is done  *
*       at any time.                                                         *
*                                                                            *
* NOTE: After done with the Security Manager, calling sinparser_deinit() is  *
*       crucial, as otherwise memory will leak                               *
*                                                                            *
*****************************************************************************/
#ifndef SIN_PARSER_H_
#define SIN_PARSER_H_

#include "sin_types.h"
#include <stddef.h>
#include <stdbool.h>

struct sin_header;

/**
 *  Initializes and gives back a handle to the SIN parser. The handle is
 *  allocated by the function and should be de-allocated by a call to
 *  sinparser_deinit().
 *
 *  NOTE: The SIN parser operates on the raw SIN buffer directly, thus the
 *  client must keep this buffer alive during the entire session.
 *
 *  The handler is retrieved if the sinbuffer contains a valid SIN header
 *  together with valid SIN data, otherwise the handler is NULL.
 *
 *  @param [out] handle         Session handle, which should be used in
 *                              consecutive calls to the parser
 *  @param [in]  sinbuffer      A pointer to the sin buffer binary data (The
 *                              client must keep the raw SIN buffer alive
 *                              during the entire session.)
 *  @param [in]  size_sinbuffer Size, in bytes, of the raw SIN buffer
 *
 *  @returns int
 */
int sinparser_init(
		struct sin_header **handle,
		uint8_t *sinbuffer,
		size_t size_sinbuffer);

/**
 *  Shuts down and de-allocates memory for a sin parser that was created and
 *  initialized by a call to sinparser_init(...). After this call, the client
 *  is free to remove (free memory used by) the raw SIN buffer.
 *
 *  @param [in] handle         Session handle
 *
 *  @returns int
 */
int sinparser_deinit(
		struct sin_header *handle);

/**
 * Retrieves the static fields of the SIN header, i.e: version, magic, length
 * of the header, type of payload, type of hash algorithm.
 *
 * @param [in]  handle             Session handle
 * @param [out] sin_static_header  Pointer to the SIN header data.
 *
 * @returns int
 */
int sinparser_get_header(
		struct sin_header *handle,
		struct sin_header_static_field **sin_static_header);

/**
 * Retrieves the ASAHI data.
 *
 * @param [in]  handle             Handle pointer
 * @param [out] asahi_signature    Pointer to the ASAHI data
 *
 * @returns int
 */
int sinparser_get_asahi_data(
		struct sin_header *handle,
		struct sin_asahi_signature **asahi_signature);

/**
 * Retrieves the number of payload/hash blocks in the SIN header.
 *
 * @param [in]  handle             session context
 * @param [out] nof_blocks         pointer to count variable (Must not be NULL)
 *
 *  @returns int
 */
int sinparser_get_nof_hash_blocks(
		struct sin_header *handle,
		uint32_t *nof_blocks);

/**
 * Retrieves information about a specific payload block stored in the SIN
 * header.
 *
 * @param [in]  handle             session context
 * @param [in]  idx_block          index of block (0, 1, ..., nof_blocks-1)
 * @param [out] block_info         Block information for the requested block.
 *                                 The information contains: length of hashed
 *                                 data together with the hash of the data.
 *
 *  @returns int
 */
int sinparser_get_hash_block_info(
		struct sin_header *handle,
		uint32_t idx_block,
		struct sin_block_info **block_info);

/**
 *  SIN Header verify segments, return the number of data segments for verify.
 *  This function is part of generation of verify hash which
 *  is used as input to ASAHI verification.
 *
 *  Example usage:
 *  [Begin-verify-hash-calculation]
 *  count = sinparser_get_header_hash_segments();
 *  for (i=0; i<count; i++){
 *    sinparser_get_header_hash_segment(...,i , &verify_data,
 *	&verify_data_length);
 *    <fkn-hash-update>(..., verify_data, verify_data_length)
 *  }
 *  [End-verify-hash-calculation]
 *  [Verify-asahi-with-verify-hash]
 *
 *  @returns uint32_t                      Number of segments
 */
uint32_t sinparser_get_header_hash_segments(void);

/**
 *  SIN Header verify segments, get location and size of a data segment for
 *  verify.
 *  This function is part of generation of verify hash which
 *  is used as input to ASAHI verification.
 *
 *  @param [in]  handle                    Session handle.
 *  @param [in]  index                     Index of segment
 *  @param [out] verify_data               Location of data segment.
 *  @param [out] verify_data_length        Size of data segment
 *
 *  @returns int
 */
int sinparser_get_header_hash_segment(
		struct sin_header *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length);

/**
 *  SIN Header verify segments, return the number of data segments for verify.
 *  This function is part of generation of verify hash which
 *  is used as input to ASAHI verification.
 *  This function normalises the output so it is not dependent of signature
 *
 *  Example usage:
 *  [Begin-verify-hash-calculation]
 *  count = sinparser_get_header_hash_segments();
 *  for (i=0; i<count; i++){
 *    sinparser_get_header_hash_segment(...,i , &verify_data,
 *	&verify_data_length);
 *    <fkn-hash-update>(..., verify_data, verify_data_length)
 *  }
 *  [End-verify-hash-calculation]
 *  [Verify-asahi-with-verify-hash]
 *
 *  @returns uint32_t                      Number of segments
 */
uint32_t sinparser_get_header_pair_hash_segments(void);

/**
 *  SIN Header verify segments, get location and size of a data segment for
 *  verify.
 *  This function is part of generation of verify hash which
 *  is used as input to ASAHI verification.
 *  This function normalises the output so it is not dependent of signature
 *
 *  @param [in]  handle                    Session handle.
 *  @param [in]  index                     Index of segment
 *  @param [out] verify_data               Location of data segment.
 *  @param [out] verify_data_length        Size of data segment
 *
 *  @returns int
 */
int sinparser_get_header_pair_hash_segment(
		struct sin_header *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length);

#endif /* SIN_PARSER_H_ */
