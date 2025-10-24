/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <string.h>
#include "der_parser.h"
#include "../../core/rm/asn1pdu_rule.h"
#include "fcserr.h"
#include "fcslog.h"

int execute_module_derparser(FILE *fd_out, uint8_t *data_p, size_t size)
{
	int res;
	struct iterator_info *iterator = NULL;
	/*  extension: flash "boot" flash "system" flash "userdata" */
	uint8_t DER1[] = {
		0x30, 0x18, 0x0C, 0x04, 0x62, 0x6F, 0x6F, 0x74, 0x0C,
		0x06, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x0C, 0x08,
		0x75, 0x73, 0x65, 0x72, 0x64, 0x61, 0x74, 0x61
	};
	/*  attribute: flash "boot" */
	uint8_t DER2[] = {
		0x30, 0x06, 0x0c, 0x04, 0x62, 0x6f, 0x6f, 0x74
	};
	/*  attribute: flash "boot" bound to devid */
	uint8_t DER3[] = {
		0x30, 0x0c, 0x0c, 0x04, 0x62, 0x6f, 0x6f, 0x74,
		0x04, 0x04, 0x01, 0x02, 0x03, 0x04
	};
	/*  attribute: keystore with sequence (no bind) */
	uint8_t DER4[] = {
		0x30, 0x08, 0xa1, 0x03, 0x0a, 0x01, 0x02, 0x02,
		0x01, 0x01
	};
	/*  attribute: keystore with bind and sequence */
	uint8_t DER5[] = {
		0x30, 0x0e, 0xa1, 0x03, 0x0a, 0x01, 0x02, 0x04,
		0x04, 0x12, 0x34, 0x56, 0x78, 0x02, 0x01, 0x03
	};
	uint8_t DER5_binding[] = { 0x12, 0x34, 0x56, 0x78 };
	int DER5_sequence = 0x03;
	/*  attribute: keystore with bind (imei) and sequence */
	uint8_t DER6[] = {
		0x30, 0x11, 0xa1, 0x03, 0x0a, 0x01, 0x02, 0x0C,
		0x07, 0x00, 0x44, 0x12, 0x34, 0x56, 0x78, 0x91,
		0x02, 0x01, 0x03
	};
	struct derparser_object *buf_field = NULL;
	uint8_t *buf_data = NULL;
	size_t buf_len = 0;
	struct derparser_object *int_field = NULL;

	if (0 == strncmp("derparser:extkeyusage", (char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_keyusage,
				sizeof(DER1),
				DER1,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract key usage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp("derparser:sigusage", (char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER2),
				DER2,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-bind-noseq",
			(char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER3),
				DER3,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-nobind-seq",
			(char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER4),
				DER4,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-bind-seq",
			(char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER5),
				DER5,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-bind-seq-get-devid",
			(char *)data_p, size)) {
		buf_field = derparser_create_buffer();
		if (buf_field == NULL) {
			FCS_LOG_ERR("Failed to create buffer object\n");
			res = -FCSERR_ENOMEM;
			goto execute_module_derparser_error;
		}
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER5),
				DER5,
				(const char **)ASN1PDU_MATCH_BINDING_DEV_ID);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, buf_field);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		} else if (0 == res) {
			FCS_LOG_ERR("Failed to find binding\n");
			res = -FCSERR_ENOTF;
			goto execute_module_derparser_error;
		}
		buf_len = derparser_get_buffer(buf_field, &buf_data);
		if ((buf_len == 0) || (buf_data == NULL)) {
			FCS_LOG_ERR("No buffer for binding\n");
			res = -FCSERR_ENOTF;
			goto execute_module_derparser_error;
		}
		if ((buf_len != sizeof(DER5_binding)) ||
				0 != memcmp(buf_data, DER5_binding, buf_len)) {
			FCS_LOG_ERR("Unexpected value for binding\n");
			res = -FCSERR_EDATA;
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-bind-seq-get-seq",
			(char *)data_p, size)) {
		int_field = derparser_create_integer();
		if (int_field == NULL) {
			FCS_LOG_ERR("Failed to create buffer object\n");
			res = -FCSERR_ENOMEM;
			goto execute_module_derparser_error;
		}
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER5),
				DER5,
				(const char **)ASN1PDU_MATCH_SEQUENCE);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, int_field);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		} else if (0 == res) {
			FCS_LOG_ERR("Failed to find binding\n");
			res = -FCSERR_ENOTF;
			goto execute_module_derparser_error;
		}
		if (DER5_sequence != derparser_get_integer(int_field)) {
			FCS_LOG_ERR("Unexpected value for sequence\n");
			res = -FCSERR_EDATA;
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else if (0 == strncmp(
			"derparser:sigusage-bind-imei-seq",
			(char *)data_p, size)) {
		res = derparser_create_iterator(
				&iterator,
				asn1pdu_signatureusage,
				sizeof(DER6),
				DER6,
				(const char **)NULL);
		if (FCSERR_OK != res) {
			FCS_LOG_ERR("Failed to create iterator\n");
			goto execute_module_derparser_error;
		}
		res = derparser_next(iterator, NULL);
		if (0 > res) {
			FCS_LOG_ERR("Failed to extract signusage\n");
			goto execute_module_derparser_error;
		}
		fprintf(fd_out, "OKAY");
	} else {
		fprintf(fd_out, "ERRORunknown testcase:%s", data_p);
	}
	derparser_delete_iterator(iterator);
	return FCSERR_OK;

execute_module_derparser_error:
	fprintf(fd_out, "ERRORres:%d", res);
	derparser_delete_object(int_field);
	derparser_delete_object(buf_field);
	derparser_delete_iterator(iterator);
	return FCSERR_OK;
}
