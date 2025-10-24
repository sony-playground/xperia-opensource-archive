/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright 2016, 2022 Sony Corporation.                                     *
 * All rights, including trade secret rights, reserved.                       *
 *****************************************************************************/
#include "sin_types.h"
#include "sin_parser.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"
#include "fcs_endian.h"
#include "fcslog.h"

/* This implementation supports only SIN version 3, should probably be set from
   a build/configuration parameter */

#define SIN_VERSION_SUPPORTED	3
#define SHA1_HASH		1
#define SHA256_HASH		2

#define SINPARSER_HEADER_STATIC_SIZE		20
#define SINPARSER_HEADER_MAGIC_SIZE		3
#define SINPARSER_HEADER_VERSION_IDX		0
#define SINPARSER_HEADER_MAGIC_IDX		1
#define SINPARSER_HEADER_SIZE_IDX		4
#define SINPARSER_HEADER_PAYLOAD_TYPE_IDX	8
#define SINPARSER_HEADER_PAYLOAD_HASH_TYPE_IDX	12
#define SINPARSER_HEADER_VERIFY_SEGMENT_COUNT	1

struct sin_header {
	struct sin_header_static_field header;/* Static fields of the SIN
						   header */
	uint32_t size_block_info_list;          /* Total size [bytes] of the
						   block */
	/* hash list */
	uint32_t nof_blocks;                    /* Number of hash block
						   informations */
	struct sin_block_info *block_info_list;      /* Block information(s)*/
	struct sin_asahi_signature asahi_signature;  /* ASAHI signature data*/

	uint8_t *hash_data;                     /* Hash data pointer */
	uint32_t hash_data_length;              /* Hash datalength */
	uint8_t hash_extra[4];
};

static int check_idx(uint32_t idx, uint32_t inc, size_t maximum_idx);
static void sinparser_destroy(struct sin_header *handle);

int sinparser_init(
		struct sin_header **handle,
		uint8_t *sinbuffer,
		size_t size_sinbuffer)
{
	struct sin_header *sinne = NULL;
	uint32_t idx = 0;
	uint32_t error = 0;
	uint32_t nof_blocks, i = 0;
	size_t length_hash;

	if ((!handle) || (!sinbuffer) || (size_sinbuffer < 28)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}
	/* Sanity check of version and magic */
	if (check_idx(idx + SINPARSER_HEADER_VERSION_IDX, sizeof(uint8_t),
			size_sinbuffer-1))
		goto exit_error;
	if (sinbuffer[idx+SINPARSER_HEADER_VERSION_IDX]
			!= SIN_VERSION_SUPPORTED) {
		FCS_LOG_ERR("Only sin version %d supported\n",
				SIN_VERSION_SUPPORTED);
		error = -FCSERR_EVER;
		goto exit_error;
	}
	if (check_idx(idx + SINPARSER_HEADER_MAGIC_IDX,
			SINPARSER_HEADER_MAGIC_SIZE, size_sinbuffer-1))
		goto exit_error;
	if (0 != memcmp(&sinbuffer[idx+SINPARSER_HEADER_MAGIC_IDX],
				"SIN",
				SINPARSER_HEADER_MAGIC_SIZE)) {
		FCS_LOG_ERR("Wrong sin-magic\n");
		error = -FCSERR_EMAGIC;
		goto exit_error;
	}

	sinne = (struct sin_header *)malloc(sizeof(struct sin_header));
	if (NULL == sinne) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}
	sinne->block_info_list = NULL;

	/**********************************************************************
	 * Static SIN header part
	 **********************************************************************/
	sinne->hash_data = (uint8_t *)&sinbuffer[idx];
	if (check_idx(idx + SINPARSER_HEADER_SIZE_IDX, sizeof(uint32_t),
			size_sinbuffer-1))
		goto exit_error;
	sinne->header.size_header =
		read_be_u32(&sinbuffer[idx+SINPARSER_HEADER_SIZE_IDX]);
	if (check_idx(idx + SINPARSER_HEADER_PAYLOAD_TYPE_IDX, sizeof(uint32_t),
			size_sinbuffer-1))
		goto exit_error;
	sinne->header.type_payload = (uint32_t)read_be_u32(
			&sinbuffer[idx+SINPARSER_HEADER_PAYLOAD_TYPE_IDX]);
	if (check_idx(idx + SINPARSER_HEADER_PAYLOAD_HASH_TYPE_IDX,
			sizeof(uint32_t), size_sinbuffer-1))
		goto exit_error;
	sinne->header.type_payload_hash = (unsigned int)read_be_u32(
			&sinbuffer[idx+SINPARSER_HEADER_PAYLOAD_HASH_TYPE_IDX]);
	idx += SINPARSER_HEADER_STATIC_SIZE;


	/* Sanity check of header size */
	if (sinne->header.size_header > size_sinbuffer) {
		/* SIN header length is wrong */
		FCS_LOG_ERR("SIN header length is wrong\n");
		error = -FCSERR_ESIZE;
		goto exit_error;
	}

	/* Sanity check of header parameters */
	switch (sinne->header.type_payload) {
	case SIN_PAYLOAD_TYPE__PLT_LOADER:
	case SIN_PAYLOAD_TYPE__PLT_BOOT:
	case SIN_PAYLOAD_TYPE__PLT_HWCONFIG:
	case SIN_PAYLOAD_TYPE__PLT_RAMETS:
	case SIN_PAYLOAD_TYPE__PLT_SYS_PART_IMG:
	case SIN_PAYLOAD_TYPE__PLT_INT_ELF_PART:
	case SIN_PAYLOAD_TYPE__PLT_INT_ELF_FS:
	case SIN_PAYLOAD_TYPE__PLT_MMC_FLASH_DATA:
	case SIN_PAYLOAD_TYPE__PLT_FOTA:
	case SIN_PAYLOAD_TYPE__PLT_LICKEY:
	case SIN_PAYLOAD_TYPE__PLT_RAW:
		break;

	default:
		FCS_LOG_ERR("Unsupported payload type\n");
		error = -FCSERR_EINVAL;
		goto exit_error;
	}

	switch (sinne->header.type_payload_hash) {
	case SHA1_HASH:
	case SHA256_HASH:
		break;

	default:
		FCS_LOG_ERR("Unsupported hash type\n");
		error = -FCSERR_EHASH;
		goto exit_error;
	}

	/**********************************************************************
	 * Block information part
	 **********************************************************************/
	if (check_idx(idx, sizeof(uint32_t), size_sinbuffer-1))
		goto exit_error;
	sinne->size_block_info_list = read_be_u32(&sinbuffer[idx]);
	idx += sizeof(uint32_t);

	/* Swap length variables and re-direct hash pointers */
	if (sinne->header.type_payload_hash == SHA1_HASH)
		length_hash = 20;
	else if (sinne->header.type_payload_hash == SHA256_HASH)
		length_hash = 32;
	else
		length_hash = 0;

	nof_blocks = sinne->size_block_info_list /
		(sizeof(uint32_t) + length_hash);

	sinne->block_info_list =
		(struct sin_block_info *)malloc(
				sizeof(struct sin_block_info)*nof_blocks);
	if (NULL == sinne->block_info_list) {
		FCS_LOG_ERR("Out of memory\n");
		error = -FCSERR_ENOMEM;
		goto exit_error;
	}

	for (i = 0; i < nof_blocks; i++) {
		if (check_idx(idx, sizeof(uint32_t), size_sinbuffer-1))
			goto exit_error;
		sinne->block_info_list[i].payload_block_length =
			read_be_u32(&sinbuffer[idx]);
		idx += sizeof(uint32_t);

		if (check_idx(idx, length_hash, size_sinbuffer-1))
			goto exit_error;
		sinne->block_info_list[i].payload_block_hash =
			(uint8_t *)&sinbuffer[idx];
		idx += length_hash;
	}
	sinne->nof_blocks = nof_blocks;

	/**********************************************************************
	 * ASAHI signature part
	 **********************************************************************/
	if (check_idx(idx, sizeof(uint32_t), size_sinbuffer-1))
		goto exit_error;
	sinne->asahi_signature.size_asahi_signature =
		read_be_u32(&sinbuffer[idx]);
	idx += sizeof(uint32_t);
	sinne->hash_data_length = idx;
	if (check_idx(idx, sinne->asahi_signature.size_asahi_signature,
			size_sinbuffer-1))
		goto exit_error;
	sinne->asahi_signature.asahi_signature = (uint8_t *)&sinbuffer[idx];
	idx += sinne->asahi_signature.size_asahi_signature;


	/**********************************************************************
	 * Sanity check of all SIN header parts (lengths etc.)
	 **********************************************************************/

	if (sinne->size_block_info_list >= sinne->header.size_header) {
		/* SIN size_block_info_list is wrong */
		FCS_LOG_ERR("SIN size_block_info_list is wrong\n");
		error = -FCSERR_ESIZE;
		goto exit_error;
	} else if (sinne->size_block_info_list % (sizeof(uint32_t)
				+ length_hash)) {
		/* SIN size_block_info_list is wrong */
		FCS_LOG_ERR("SIN size_block_info_list is wrong\n");
		error = -FCSERR_ESIZE;
		goto exit_error;
	}
	*handle = (struct sin_header *)sinne;
	return FCSERR_OK;

exit_error:
	/* De-allocate memory and return error code */
	sinparser_destroy(sinne);
	*handle = NULL;
	return error;
}


int sinparser_deinit(
		struct sin_header *handle)
{
	sinparser_destroy(handle);
	return FCSERR_OK;
}


int sinparser_get_header(
		struct sin_header *handle,
		struct sin_header_static_field **sin_static_header)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!sin_static_header)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*sin_static_header = &sinne->header;
	return FCSERR_OK;
}


int sinparser_get_asahi_data(
		struct sin_header *handle,
		struct sin_asahi_signature **asahi_signature)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!asahi_signature)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*asahi_signature = &sinne->asahi_signature;
	return FCSERR_OK;
}


int sinparser_get_nof_hash_blocks(
		struct sin_header *handle,
		uint32_t *block_count)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!block_count)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*block_count = sinne->nof_blocks;
	return FCSERR_OK;
}


int sinparser_get_hash_block_info(
		struct sin_header *handle,
		uint32_t idx_block,
		struct sin_block_info **block_info)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!block_info) || (!sinne->block_info_list) ||
			(idx_block >= sinne->nof_blocks)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	*block_info = &sinne->block_info_list[idx_block];
	return FCSERR_OK;
}

uint32_t sinparser_get_header_hash_segments(void)
{
	return SINPARSER_HEADER_VERIFY_SEGMENT_COUNT;
}

int sinparser_get_header_hash_segment(
		struct sin_header *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!verify_data) || (!verify_data_length)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}
	if (0 != index) {
		FCS_LOG_ERR("Incorrect index\n");
		return -FCSERR_EINDEX;
	}

	*verify_data = sinne->hash_data;
	*verify_data_length = sinne->hash_data_length;

	return FCSERR_OK;
}

uint32_t sinparser_get_header_pair_hash_segments(void)
{
	return 3;
}

int sinparser_get_header_pair_hash_segment(
		struct sin_header *handle,
		uint32_t index,
		uint8_t **verify_data,
		uint32_t *verify_data_length)
{
	struct sin_header *sinne = (struct sin_header *)handle;

	if ((!sinne) || (!verify_data) || (!verify_data_length)) {
		FCS_LOG_ERR("Wrong input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (0 == index) {
		*verify_data = sinne->hash_data;
		*verify_data_length = 4;
	} else if (1 == index) {
		sinne->hash_extra[0] =
			(((sinne->hash_data_length-4) >> 24) & 0xFF);
		sinne->hash_extra[1] =
			(((sinne->hash_data_length-4) >> 16) & 0xFF);
		sinne->hash_extra[2] =
			(((sinne->hash_data_length-4) >>  8) & 0xFF);
		sinne->hash_extra[3] =
			(((sinne->hash_data_length-4) >>  0) & 0xFF);
		*verify_data = sinne->hash_extra;
		*verify_data_length = 4;
	} else if (2 == index) {
		*verify_data = sinne->hash_data + 8;
		*verify_data_length = sinne->hash_data_length - 12;
	} else {
		FCS_LOG_ERR("Index should not exist\n");
		return -FCSERR_EINDEX;
	}
	return FCSERR_OK;
}

static void sinparser_destroy(struct sin_header *handle)
{
	if (handle && handle->block_info_list)
		free(handle->block_info_list);

	if (handle)
		free(handle);
}

static int check_idx(uint32_t idx, uint32_t inc, size_t maximum_idx)
{
	if (((uint64_t)idx + inc - 1) > maximum_idx) {
		FCS_LOG_ERR("Index too large\n");
		return -FCSERR_ESIZE;
	}

	return FCSERR_OK;
}

