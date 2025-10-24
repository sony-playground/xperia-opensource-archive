/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <stdlib.h>
#include <string.h>
#include "sony_boot_customer_id.h"
#include "sony_boot_utils.h"
#include "sony_libc.h"
#include "xboot_glue.h"

/* Header files from loader */
#include "fcslog.h"
#include "fcserr.h"


/* Customer ID Length ('c' + 6 digit-number based on Carrier ID in ASCII code) */
#define TA_CUSTOMER_ID_MAXLEN  7

int bootconfig_append_customer_id(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	char customer_id[TA_CUSTOMER_ID_MAXLEN+1];
	const char skutag[] = " androidboot.hardware.sku=";
	const int bufsize = sizeof(skutag) + sizeof(customer_id);

	if (context == NULL ||
		config_data == NULL ||
		config_size == 0 ||
		context->bootconfig == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	context->bootconfig->taCustomerId = malloc(bufsize);
	if (context->bootconfig->taCustomerId == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}
	context->bootconfig->taCustomerId[0] = '\0';

	/* copy customer id from config_data */
	strlcpy(customer_id, (const char *)config_data,
		MIN(sizeof(customer_id), (config_size + 1)));
	customer_id[TA_CUSTOMER_ID_MAXLEN] = '\0'; /* set Null just in case */

	/* Append customer id to bootconfig */
	if (strlen(customer_id) != 0) {
		strlcat(context->bootconfig->taCustomerId,
			skutag, bufsize);
		strlcat(context->bootconfig->taCustomerId,
			customer_id, bufsize);
	} else {
		FCS_LOG_ERR("No Customer ID\n");
	}
	return FCSERR_OK;
}

int cmdline_append_customer_id(struct xboot_ctx *boot_context,
	const uint8_t *ta_buf, const size_t ta_Size)
{
	char customer_id[TA_CUSTOMER_ID_MAXLEN+1];
	char skutag[] = " androidboot.hardware.sku=";
	const int bufsize = sizeof(skutag) + sizeof(customer_id);
	char ta_cusromer[sizeof(skutag) + sizeof(customer_id)] = {0};

	if (boot_context == NULL ||
		ta_buf == NULL ||
		ta_Size == 0 ||
		boot_context->bootconfig == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* copy customer id from config_data */
	strlcpy(customer_id, (const char *)ta_buf,
		MIN(sizeof(customer_id), (ta_Size + 1)));
	customer_id[TA_CUSTOMER_ID_MAXLEN] = '\0'; /* set Null just in case */

	if (strlen(customer_id) != 0) {
		strlcat(ta_cusromer, skutag, bufsize);
		strlcat(ta_cusromer, customer_id, bufsize);
		boot_context->bootconfig->taCommandLineArgs = sony_alloc_strcat(
			boot_context->bootconfig->taCommandLineArgs, ta_cusromer);
	} else {
		FCS_LOG_ERR("No Customer ID\n");
	}
	return FCSERR_OK;
}



