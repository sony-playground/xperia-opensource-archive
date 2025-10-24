/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "hwconf_x_parser.h"
#include "asn1pdu_hwconf_x.h"
#include "der_parser_utils.h"
#include "fcslog.h"
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"

#define HWCX_VERSION_MIN	1
#define HWCX_VERSION_MAX	1
#define HWCX_IMEI_BCD_SIZE	8
#define HWCX_IMEI_SIZE_MIN	14
#define HWCX_IMEI_SIZE_MAX	14
#define HWCX_DK_SIZE_MIN	16
#define HWCX_DK_SIZE_MAX	16
/**
 * Parser Data
 */
struct hwconf_x_data {
	int version;

	bool isprototype;

	uint8_t imei_1[HWCX_IMEI_BCD_SIZE];
	size_t imei_1_size;
	uint8_t imei_2[HWCX_IMEI_BCD_SIZE];
	size_t imei_2_size;

	uint8_t dk[HWCX_DK_SIZE_MAX];
	size_t dk_size;
};

/*****************************************************************************
 *              Internal utility functions                                   *
 *****************************************************************************/
static int utf8_to_bcd(
	uint8_t *dest, size_t dest_len,
	uint8_t *src, size_t src_len)
{
	size_t i, j;

	for (i = 0; i < src_len; i++) {
		if (src[i] < '0' || src[i] > '9')
			return -FCSERR_EINVAL;
	}
	memset(dest, 0, dest_len);
	i = 0;
	for (j = 0; j < dest_len; j++) {
		if (i >= src_len)
			break;
		dest[j] = (src[i++] - '0') & 0x0F;
		dest[j] <<= 4;
		if (i >= src_len)
			break;
		dest[j] |= (src[i++] - '0') & 0x0F;
	}
	return FCSERR_OK;
}

static int hwconf_x_get_imei_list_cb(
	void *callback_context,
	int res,
	int index,
	struct derparser_object **current,
	bool *stop)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)callback_context;
	uint8_t *buf;
	size_t buf_len;

	if (index == 0) {
		/* Setup dest object for the search */
		/* The dest obj is the context */
		*current = derparser_create_buffer();
		*stop = false;
	} else {
		/* Check the result of the search */
		if (res == 1) {
			/* Got hit */
			buf_len = derparser_get_buffer(*current, &buf);
			if ((buf_len == 0) || (buf == NULL)) {
				FCS_LOG_ERR("Failed to get buffer\n");
				res = -FCSERR_ENOTF;
				goto failure;
			}
			/* Check field size */
			if ((buf_len < HWCX_IMEI_SIZE_MIN) ||
					(buf_len > HWCX_IMEI_SIZE_MAX)) {
				FCS_LOG_ERR("Wrong field size\n");
				res = -FCSERR_EINVAL;
				goto failure;
			}
			if (index == 1) {
				/* Is first entry */
				res = utf8_to_bcd(data->imei_1,
						sizeof(data->imei_1),
						buf, buf_len);
				if (res != FCSERR_OK) {
					FCS_LOG_ERR(
						"Format of IMEI not valid\n");
					goto failure;
				}
				data->imei_1_size = sizeof(data->imei_1);
			} else if (index == 2) {
				/* Is second entry */
				res = utf8_to_bcd(data->imei_2,
						sizeof(data->imei_2),
						buf, buf_len);
				if (res != FCSERR_OK) {
					FCS_LOG_ERR(
						"Format of IMEI not valid\n");
					goto failure;
				}
				data->imei_2_size = sizeof(data->imei_2);
			} else {
				/* To many entries */
				FCS_LOG_ERR("Too large imei list count\n");
				res = -FCSERR_EINVAL;
				goto failure;
			}
			/* As long as we find entries we continue */
			*stop = false;
		} else if (res == 0) {
			/* No hit */
			if (index == 1) {
				/* We did not find any list entry */
				FCS_LOG_ERR("Too low imei list count\n");
				res = -FCSERR_ENOTF;
				goto failure;
			}
			*stop = true;
			derparser_delete_object(*current);
		} else {
			/* Error */
			FCS_LOG_ERR("Search returned error %d\n", res);
			goto failure;
		}
	}
	return res;

failure:
	*stop = true;
	derparser_delete_object(*current);
	return res;
}

/******************************************************************************
 *                Implementation of interface functions                       *
 ******************************************************************************/
int hwconf_x_parser_init(hwconf_x_handle_t *phandle,
		uint8_t *hwconf,
		size_t hwconf_size)
{
	struct hwconf_x_data *data = NULL;
	int res;
	struct iterator_info *root_iterator = NULL;
	struct iterator_info *iterator = NULL;

	/* Sanity checks */
	if (phandle == NULL || hwconf == NULL || hwconf_size == 0) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Allocate the hwconf parsing structure */
	data = malloc(sizeof(struct hwconf_x_data));
	if (data == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	/* Reset the parsing structure */
	memset(data, 0, sizeof(struct hwconf_x_data));

	/* Create a base iterator for use in other iterators */
	res = derparser_create_iterator(
			&root_iterator,
			asn1pdu_hwconf_x,
			hwconf_size,
			hwconf,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}

	/* Sanity check on content */
	res = derparser_create_subset_iterator(
			&iterator,
			root_iterator,
			(const char **)(NULL));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create iterator\n");
		goto exit;
	}
	res = derparser_next(iterator, NULL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to parse hwconfig\n");
		goto exit;
	}
	derparser_delete_iterator(iterator);
	iterator = NULL;

	/* Extract and check version */
	res = derparser_util_get_integer(
			root_iterator,
			ASN1PDU_MATCH_HWCONF_X_VERSION,
			&(data->version),
			HWCX_VERSION_MIN,
			HWCX_VERSION_MAX);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to extract version\n");
		goto exit;
	}

	/* Extract and check isprototype */
	res = derparser_util_get_boolean(
			root_iterator,
			ASN1PDU_MATCH_HWCONF_X_ISPROTOTYPE,
			&(data->isprototype));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to extract isprototype\n");
		goto exit;
	}

	/* Extract and check IMEI list */
	res = derparser_util_get_object(
			root_iterator,
			ASN1PDU_MATCH_HWCONF_X_IMEILIST_ENTRY,
			data,
			hwconf_x_get_imei_list_cb);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to extract IMEI list\n");
		goto exit;
	}

	/* Extract and check DeviceKey */
	res = derparser_util_get_buffer(
			root_iterator,
			ASN1PDU_MATCH_HWCONF_X_DK,
			data->dk,
			HWCX_DK_SIZE_MIN,
			HWCX_DK_SIZE_MAX,
			&(data->dk_size));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to extract DeviceKey\n");
		goto exit;
	}

	*phandle = (hwconf_x_handle_t *)data;

exit:
	if ((res != FCSERR_OK) && (data != NULL))
		hwconf_x_parser_deinit(data);
	derparser_delete_iterator(root_iterator);
	derparser_delete_iterator(iterator);

	return res;
}


void hwconf_x_parser_deinit(hwconf_x_handle_t handle)
{
	/* Deinit the whole parsing structure */
	free(handle);
}

int hwconf_x_parser_get_version(hwconf_x_handle_t handle, int *version)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)handle;

	/* Sanity checks */
	if (data == NULL || version == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Set output to the caller */
	*version = data->version;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	 * to version or handle.
	 */
	return -FCSERR_EINVAL;
}

int hwconf_x_parser_get_isprototype(
		hwconf_x_handle_t handle,
		bool *is_prototype)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)handle;

	/* Sanity checks */
	if (data == NULL || is_prototype == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Set output to the caller */
	*is_prototype = data->isprototype;

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	 * to is_prototype or handle.
	 */
	return -FCSERR_EINVAL;
}

int hwconf_x_parser_get_imei_count(hwconf_x_handle_t handle, uint8_t *count)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)handle;

	/* Sanity checks */
	if (data == NULL || count == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	*count = 0;
	if (data->imei_1_size > 0) {
		(*count)++;
		if (data->imei_2_size > 0)
			(*count)++;
	}

	return FCSERR_OK;

failed:
	/* Caller has provided incorrect pointer
	 * to count or handle.
	 */
	return -FCSERR_EINVAL;
}

int hwconf_x_parser_get_imei(hwconf_x_handle_t handle,
		uint8_t index,
		uint8_t **buffer,
		size_t *buffer_size)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)handle;

	/* Sanity checks */
	if (data == NULL || index > 1 ||
			buffer == NULL || buffer_size == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Set the output */
	if (index == 0) {
		if (data->imei_1_size == 0) {
			FCS_LOG_ERR("No imei at index 0\n");
			goto failed;
		}
		*buffer = data->imei_1;
		*buffer_size = data->imei_1_size;
	} else {
		if (data->imei_2_size == 0) {
			goto failed;
		}
		*buffer = data->imei_2;
		*buffer_size = data->imei_2_size;
	}

	return FCSERR_OK;

failed:
	/* Something went wrong here */
	return -FCSERR_ENOTF;
}

int hwconf_x_parser_get_hwc_dk(hwconf_x_handle_t handle,
		uint8_t **buffer,
		size_t *buffer_size)
{
	struct hwconf_x_data *data = (struct hwconf_x_data *)handle;

	/* Sanity checks */
	if (data == NULL || buffer == NULL || buffer_size == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		goto failed;
	}

	/* Set the output */
	*buffer = data->dk;
	*buffer_size = data->dk_size;

	return FCSERR_OK;

failed:
	/* Instances not found, caller has provided
	 * incorrect buffer, buffer_size or handle.
	 */
	return -FCSERR_EINVAL;
}

