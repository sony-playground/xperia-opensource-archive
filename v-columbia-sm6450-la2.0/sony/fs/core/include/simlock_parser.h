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
 *     The Simlock Parser is responsible for parsing simlock files            *
 *     simlock signature and data (partly).                                   *
 * USAGE:                                                                     *
 *     // Init parser                                                         *
 *     simlock_parser_init(&handle, ...);                                     *
 *                                                                            *
 *     // Get ASAHI signature                                                 *
 *     simlock_parser_get_parameters(handle, &asahi, &asahi_length);          *
 *                                                                            *
 *     // Build verify hash over simlock information and verify               *
 *     [Begin-verify-hash-calculation]                                        *
 *      count = simlock_parser_get_image_hash_segments();                     *
 *      for (i=0; i<count; i++)                                               *
 *      {                                                                     *
 *        simlock_parser_get_image_hash_segment(                              *
 *          ...,i , &verify_data, &verify_data_length);                       *
 *        <fkn-hash-update>(..., verify_data, verify_data_length)             *
 *      }                                                                     *
 *      [End-verify-hash-calculation]                                         *
 *      [Verify-asahi-with-verify-hash]                                       *
 *                                                                            *
 *      // Get simlock data                                                   *
 *      simlock_parser_get_parameters(                                        *
 *        handle,                                                             *
 *        &parameters,                                                        *
 *        &parameters_length);                                                *
 *                                                                            *
 *      // Use simlock data                                                   *
 *                                                                            *
 *      // Cleanup                                                            *
 *      simlock_parser_deinit(handle);                                        *
 *                                                                            *
 ******************************************************************************/
#ifndef SIMLOCK_PARSER_H_
#define SIMLOCK_PARSER_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#define SIMLOCK_PHONE_DATA_TYPE_IMEI (0)
#define SIMLOCK_PHONE_DATA_TYPE_MEID (1)

/**
 * Setup simlock parser session.
 * Caller should hold the input buffers during the session.
 * The function expects a phone id because it is part of the verify process.
 *
 * @param [out] handle                    Returned session handle.
 * @param [in]  phone_id_type             Phone id type
 * @param [in]  phone_id                  Phone id data
 * @param [in]  phone_id_length           Phone id length
 * @param [in]  simlock_data              Simlock data
 * @param [in]  simlock_data_length       Simlock data length
 * @param [in]  simlock_signature         Simlock signature
 * @param [in]  simlock_signature_length  Simlock signature length
 *
 * @returns int
 */
int simlock_parser_init(
		void **handle,
		uint8_t phone_id_type,
		uint8_t *phone_id,
		size_t phone_id_length,
		uint8_t *simlock_data,
		uint_fast32_t simlock_data_length,
		uint8_t *simlock_signature,
		uint_fast32_t simlock_signature_length);

/**
 * Clean up simlock parser session.
 *
 * @param [in]  handle                    Session handle.
 *
 * @returns none
 */
void simlock_parser_deinit(
		void *handle);

/**
 * Return the location and size of simlock parameter data.
 *
 * @param [in]  handle                    Session handle.
 * @param [out] parameters                Pointer to parameter buffer.
 * @param [out] parameters_length         Length of parameter buffer.
 *
 * @returns int
 */
int simlock_parser_get_parameters(
		void *handle,
		uint8_t **parameters,
		uint32_t *parameters_length);

/**
 * Return the location and size of asahi signature.
 *
 * @param [in]  handle                    Session handle.
 * @param [out] asahi                     Pointer to asahi buffer.
 * @param [out] asahi_length              Length of asahi buffer.
 *
 * @returns int
 */
int simlock_parser_get_asahi_signature(
		void *handle,
		uint8_t **asahi,
		uint32_t *asahi_length);

/**
 * Simlock image verify segments, return the number of data segments for verify.
 * This function is part of generation of verify hash which
 * is used as input to ASAHI verification.
 *
 * @param [out] n_segments               number of data segments.
 *
 * @returns int
 */
int simlock_parser_get_image_hash_segments(uint32_t *n_segments);

/**
 * Simlock image verify segments, get location and size of a data segment for
 * verify.
 * This function is part of generation of verify hash which
 * is used as input to ASAHI verification.
 *
 * @param [in]  handle                    Session handle.
 * @param [in]  index                     Index of segment
 * @param [out] verify_data               Location of data segment.
 * @param [out] verify_data_length        Size of data segment
 *
 * @returns int
 */
int simlock_parser_get_image_hash_segment(
		void *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length);

#endif /* SIMLOCK_PARSER_H_ */
