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
 *****************************************************************************/

#include "simlock_parser.h"
#include "fcserr.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fcslog.h"

struct simlock_parser_internal {
	uint8_t *converted_phone_id;
	size_t converted_phone_id_length;
	uint8_t *simlock_data;
	uint_fast32_t simlock_data_length;
	uint8_t *simlock_signature;
	uint_fast32_t simlock_signature_length;
	uint8_t *asahi;
	size_t asahi_length;
	size_t hash_data_start;
	size_t hash_data_length;
};

#define SIMLOCK_SIGNATURE_HEADER_LEN 14

/* Expected Simlock field values */
#define SIMLOCK_VERSION         2
#define SIMLOCK_HASH_LIST_LEN   9

/* Simlock Field index */
#define SIMLOCK_VERSION_IDX         0
#define SIMLOCK_HASH_LIST_LEN_IDX   1
#define SIMLOCK_HASH_DATA_START_IDX 7
#define SIMLOCK_HASH_DATA_LEN_IDX   9
#define SIMLOCK_HASH_DATA_TYPE_IDX  11
#define SIMLOCK_ASAHI_SIGN_LEN_IDX  12

#define SIMLOCK_IMAGE_HASH_SEGMENT_COUNT 3   /* Data, Ascii_phone_id,
						Signature header */

static void simlock_parser_int_cleanup(struct simlock_parser_internal *parser)
{
	if (NULL != parser->converted_phone_id)
		free(parser->converted_phone_id);
	free(parser);
}

/**
 * cnvstr - Convert nibble to ASCII Hex.
 */
static char cnvstr(int val)
{
	if (val < 10)
		return 0x30+(char)val;
	else
		return 0x37+(char)val;
}

/**
 * SECMGR_SL_Convert - Convert Phone ID to ASCII 14 char and store in
 * parser struct.
 */
static int simlock_parser_int_set_ascii_phone_id(
		struct simlock_parser_internal *parser,
		uint8_t *phone_id,
		size_t phone_id_length)
{
	int i, j;

	if (phone_id_length < 7) {
		FCS_LOG_ERR("Invalid parameter, phone id length is %d\n",
			phone_id_length);
		return -FCSERR_EINVAL;
	}

	parser->converted_phone_id = (uint8_t *)malloc((size_t)14);
	parser->converted_phone_id_length = 14;
	if (NULL == parser->converted_phone_id) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	j = 0;
	for (i = 0; i < 7; i++)	{
		parser->converted_phone_id[j++] =
			(uint8_t)cnvstr((phone_id[i] & 0xF0) >> 4);
		parser->converted_phone_id[j++] =
			(uint8_t)cnvstr((phone_id[i] & 0x0F));
	}
	return FCSERR_OK;
}

/**
 * Dereferences data and checks that its address is inside a specified border.
 *
 * @param[in] adr         Pointer to the desired data
 * @param[in] end_adr     Pointer to the border
 * @param[out] success    Pointer to a boolean that will be written as TRUE
 *                        if the data was returned, FALSE otherwise.
 *
 * @returns the data at adr.
 */
static uint16_t simlock_parser_int_get_uint16(
		const uint8_t *adr,
		const uint8_t *end_adr,
		bool *success)
{
	/* endadr == first byte that is not allowed to be read */
	uint16_t a = 0;

	if (adr + 2 > end_adr) {
		*success = false;
		return 0;
	}
	a = adr[0] << 8;
	a |= adr[1];
	*success = true;

	return a;
}

/**
 * Dereferences data and and checks that its address is inside a specified
 * border.
 *
 * @param[in] adr         Pointer to the desired data
 * @param[in] end_adr     Pointer to the border
 * @param[out] success    Pointer to a boolean that will be written as TRUE
 *                        if the data was returned, FALSE otherwise.
 *
 * @returns the data at adr.
 */
static int simlock_parser_int_get_uchar(
		const uint8_t *adr,
		const uint8_t *end_adr,
		bool *success)
{
	/* end_adr == first byte that is not allowed to be read */
	if (adr + 1 > end_adr) {
		*success = false;
		return 0;
	}
	*success = true;

	return adr[0];
}

static int simlock_parser_int_parse_signature(
		struct simlock_parser_internal *parser,
		uint8_t *signature,
		uint_fast32_t signature_length,
		uint_fast32_t data_length)
{
	bool rval = false;
	uint8_t *signature_end = (uint8_t *)&(signature[signature_length]);

	if (SIMLOCK_VERSION != signature[SIMLOCK_VERSION_IDX]) {
		/* only warning due to we could have a
		 * different signature blob
		 */
		FCS_LOG_WRN("Invalid simlock version\n");
		return -FCSERR_EVER;
	}

	if ((SIMLOCK_HASH_LIST_LEN != simlock_parser_int_get_uint16(
					&signature[SIMLOCK_HASH_LIST_LEN_IDX],
					signature_end,
					&rval)) || (!rval)) {
		FCS_LOG_ERR("Wrong hash list length\n");
		return -FCSERR_EINFOR;
	}

	parser->hash_data_start = simlock_parser_int_get_uint16(
			&signature[SIMLOCK_HASH_DATA_START_IDX],
			signature_end,
			&rval);
	if ((parser->hash_data_start == 0) || (!rval)) {
		FCS_LOG_ERR("Invalid format\n");
		return -FCSERR_EINFOR;
	}

	parser->hash_data_start -= 1;

	parser->hash_data_length = (int)simlock_parser_int_get_uint16(
			&(signature[SIMLOCK_HASH_DATA_LEN_IDX]),
			signature_end,
			&rval);
	if ((!rval) || ((uint32_t)(parser->hash_data_start +
					parser->hash_data_length) >
				data_length)) {
		FCS_LOG_ERR("Invalid format\n");
		return -FCSERR_EINFOR;
	}

	if ((0 != simlock_parser_int_get_uchar(
					&signature[SIMLOCK_HASH_DATA_TYPE_IDX],
					signature_end,
					&rval)) || (!rval)) {
		FCS_LOG_ERR("Invalid format\n");
		return -FCSERR_EINFOR;
	}

	parser->asahi_length = simlock_parser_int_get_uint16(
			&signature[SIMLOCK_ASAHI_SIGN_LEN_IDX],
			signature_end,
			&rval);

	if ((!rval) | ((parser->asahi_length+SIMLOCK_SIGNATURE_HEADER_LEN) >
				signature_length)) {
		FCS_LOG_ERR("Invalid format\n");
		return -FCSERR_EINFOR;
	}

	parser->asahi = (uint8_t *)&(signature[SIMLOCK_SIGNATURE_HEADER_LEN]);

	return FCSERR_OK;
}

int simlock_parser_init(
		void **handle,
		uint8_t phone_id_type,
		uint8_t *phone_id,
		size_t phone_id_length,
		uint8_t *simlock_data,
		uint_fast32_t simlock_data_length,
		uint8_t *simlock_signature,
		uint_fast32_t simlock_signature_length)
{
	int status = FCSERR_OK;
	struct simlock_parser_internal *parser = NULL;

	if ((NULL == handle) ||
			((SIMLOCK_PHONE_DATA_TYPE_IMEI != phone_id_type) &&
			 (SIMLOCK_PHONE_DATA_TYPE_MEID != phone_id_type)) ||
			(NULL == phone_id) ||
			(8 != phone_id_length) ||
			(NULL == simlock_data) ||
			(0 == simlock_data_length) ||
			(NULL == simlock_signature) ||
			(0 == simlock_signature_length)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	parser = (struct simlock_parser_internal *)malloc(
			sizeof(struct simlock_parser_internal));
	if (NULL == parser) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	memset(parser, 0, sizeof(struct simlock_parser_internal));
	parser->simlock_data = simlock_data;
	parser->simlock_data_length = simlock_data_length;
	parser->simlock_signature = simlock_signature;
	parser->simlock_signature_length = simlock_signature_length;

	status = simlock_parser_int_set_ascii_phone_id(
					parser,
					phone_id,
					phone_id_length);
	if (status)
		goto simlock_parser_init_fail_cleanup;

	status = simlock_parser_int_parse_signature(
					parser,
					simlock_signature,
					simlock_signature_length,
					simlock_data_length);
	if (status)
		goto simlock_parser_init_fail_cleanup;

	*handle = (void *)parser;

	return FCSERR_OK;

simlock_parser_init_fail_cleanup:
	simlock_parser_int_cleanup(parser);
	return status;
}

void simlock_parser_deinit(void *handle)
{
	struct simlock_parser_internal *parser =
		(struct simlock_parser_internal *)handle;

	if (NULL != parser)
		simlock_parser_int_cleanup(parser);
}

int simlock_parser_get_parameters(
		void *handle,
		uint8_t **parameters,
		uint32_t *parameters_length)
{
	struct simlock_parser_internal *parser =
		(struct simlock_parser_internal *)handle;

	if ((NULL == parser) || (NULL == parameters) ||
			(NULL == parameters_length)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	*parameters = &(parser->simlock_data[parser->hash_data_start]);
	*parameters_length = parser->hash_data_length;

	return FCSERR_OK;
}

int simlock_parser_get_asahi_signature(
		void *handle,
		uint8_t **asahi,
		uint32_t *asahi_length)
{
	struct simlock_parser_internal *parser =
		(struct simlock_parser_internal *)handle;

	if ((NULL == parser) || (NULL == asahi) || (NULL == asahi_length)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	*asahi = parser->asahi;
	*asahi_length = parser->asahi_length;

	return FCSERR_OK;
}

int simlock_parser_get_image_hash_segments(uint32_t *n_segments)
{
	*n_segments = SIMLOCK_IMAGE_HASH_SEGMENT_COUNT;

	return FCSERR_OK;
}

int simlock_parser_get_image_hash_segment(
		void *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length)
{
	struct simlock_parser_internal *parser =
		(struct simlock_parser_internal *)handle;

	if ((NULL == parser) ||	(NULL == verify_data) ||
			(0 == verify_data_length)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	switch (index) {
	case 0:
		*verify_data = &(parser->simlock_data[parser->hash_data_start]);
		*verify_data_length = parser->hash_data_length;
		break;
	case 1:
		*verify_data = parser->converted_phone_id;
		*verify_data_length = parser->converted_phone_id_length;
		break;
	case 2:
		*verify_data = parser->simlock_signature;
		*verify_data_length = SIMLOCK_SIGNATURE_HEADER_LEN;
		break;
	default:
		FCS_LOG_ERR("Invalid index\n");
		return -FCSERR_EINDEX;
	}

	return FCSERR_OK;
}

