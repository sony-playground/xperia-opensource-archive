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
#include "asahi_parser.h"
#include "fcs_endian.h"
#include <stdint.h>
#include <string.h>
#include "fcslog.h"
#include "fcserr.h"

/**
 * Type definitions and defines
 */

#define ASAHI_VERSION 1

/* ASAHI format, see "Advanced Signature Approach for High Integrity"
 * 27/159 35-LXE 108 116 Uen PA3
 * for reference:
 typedef struct
 {
 uint16_t version;
 uint16_t cert_list_len;
 uint8_t cert_list[cert_list_len];
 uint8_t algorithm; // SignatureAlgorithm_t
 uint16_t signature_len;
 uint8_t signature[signature_len];
 } asahi_signature_t;
 */

/**
 * Constructor / Destructor
 */
int asahiparser_init(void  **handle,
		uint8_t *asahibuffer,
		size_t asahibuffer_size)
{
	uint16_t version = 0;
	uint16_t cert_chain_length = 0;
	uint16_t signature_length = 0;
	uint8_t *data = asahibuffer;

	/* Check in parameters
	   7 is the size of the static parts in the signature */
	if ((NULL == handle) || (NULL == asahibuffer) ||
			(asahibuffer_size < 7)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* Convert since format in ASAHI signature is Big Endian */
	version = bytes_to_uint16(*(data+1), *data);

	if (ASAHI_VERSION != version) {
		FCS_LOG_ERR("Only asahi version %d supported\n", ASAHI_VERSION);
		return -FCSERR_EVER;
	}

	/* version tag */
	data += 2;

	/* Convert since format in ASAHI signature is Big Endian */
	cert_chain_length = bytes_to_uint16(*(data+1), *data);

	/* certificate chain length */
	data += 2;

	/* 3 = version + length */
	if ((data + cert_chain_length + 3) > (asahibuffer + asahibuffer_size)) {
		FCS_LOG_ERR("Format fail\n");
		return -FCSERR_EINFOR;
	}

	data += cert_chain_length;

	if ((ASAHI_SHA256_RSA != *data) && (ASAHI_SHA1_RSA != *data)) {
		FCS_LOG_ERR("Wrong SHA type\n");
		return -FCSERR_EINFOR;
	}

	/* signature algorithm */
	data++;
	signature_length = bytes_to_uint16(*(data+1), *data);

	/* signature length */
	data += 2;

	/* We check that the buffer size is big enough,
	   it does not have to be exactly the right size */
	if ((data + signature_length) > (asahibuffer + asahibuffer_size)) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_EINFOR;
	}

	*handle = (void *)asahibuffer;

	return FCSERR_OK;
}

int asahiparser_deinit(void *handle)
{
	(void)(handle); /* Unused parameter */
	/* there is nothing to free from call to init */
	return FCSERR_OK;
}

/**
 * Implemented methods
 */
int asahiparser_get_certificate_chain(void *handle,
		uint8_t **certificate_chain,
		size_t *certificate_chain_size)
{
	int res = -FCSERR_EINVAL;
	uint8_t *data = NULL;
	uint8_t *data_end = NULL;
	uint8_t *buffer = NULL;
	uint8_t *buffer_ptr = NULL;
	uint16_t chain_size = 0;
	uint16_t cert_size = 0;

	/* Check in parameters */
	if ((NULL == handle) ||
			(NULL == certificate_chain) ||
			(NULL == certificate_chain_size)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto err_function;
	}

	/* Sanity checks are made in init
	   skip version info */
	data = ((uint8_t *) handle) + 2;

	/* Convert since format in ASAHI signature is Big Endian */
	chain_size = bytes_to_uint16(*(data+1), *data);

	if (0 == chain_size) {
		FCS_LOG_ERR("Certificate chain-size 0\n");
		res = -FCSERR_EINFOR;
		goto err_function;
	}

	/* skip chain size */
	data += 2;

	buffer = malloc(chain_size);
	if (NULL == buffer) {
		FCS_LOG_ERR("Failed to allocate certchain buffer\n");
		res = -FCSERR_ENOMEM;
		goto err_function;
	}

	data_end = data + chain_size;
	buffer_ptr = buffer;
	while (data < data_end) {
		/* Convert since format in ASAHI signature is Big Endian */
		cert_size = bytes_to_uint16(*(data+1), *data);
		data += 2;
		if (0 == cert_size) {
			FCS_LOG_ERR("Certificate size 0\n");
			res = -FCSERR_EINFOR;
			goto err_function;
		}

		if (data + cert_size > data_end) {

			res = -FCSERR_ENOBUFS;
			goto err_function;
		}
		memcpy(buffer_ptr, data, cert_size);
		buffer_ptr += cert_size;
		data += cert_size;
	}

	*certificate_chain_size = (size_t)(buffer_ptr - buffer);
	*certificate_chain = buffer;

	return FCSERR_OK;

err_function:
	free(buffer);
	return res;
}

int asahiparser_get_signature_algorithm(void *handle,
		uint8_t *algorithm)
{
	uint8_t *data = (uint8_t *)handle;
	size_t cert_chain_length = 0;

	/* Check in parameters */
	if ((NULL == handle) || (NULL == algorithm)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* version tag */
	data += 2;

	/* Convert since format in ASAHI signature is Big Endian */
	cert_chain_length = bytes_to_uint16(*(data+1), *data);

	/* certificate chain length */
	data += 2;

	data += cert_chain_length;

	*algorithm = *data;

	return FCSERR_OK;
}

int asahiparser_get_rsa_signature(void *handle,
		uint8_t **rsa_signature,
		size_t *rsa_signature_size)
{
	uint8_t *data = NULL;
	uint16_t chain_size = 0;
	uint16_t signature_size = 0;

	/* Check in parameters */
	if ((NULL == handle) || (NULL == rsa_signature) ||
			(NULL == rsa_signature_size)) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* Sanity checks are made in init
	   skip version info */
	data = ((uint8_t *)handle) + 2;

	/* Convert since format in ASAHI signature is Big Endian */
	chain_size = bytes_to_uint16(*(data+1), *data);

	/* skip chainlength + size + algorithm type size */
	data += (2 + chain_size + 1);

	/* Convert since format in ASAHI signature is Big Endian */
	signature_size = bytes_to_uint16(*(data+1), *data);

	if (0 == signature_size) {
		FCS_LOG_ERR("Signature size is 0\n");
		return -FCSERR_EINFOR;
	}

	/* skip signature size */
	data += 2;

	*rsa_signature_size = (size_t)signature_size;
	*rsa_signature = data;

	return FCSERR_OK;
}

