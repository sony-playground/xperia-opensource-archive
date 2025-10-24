/*
 * Copyright 2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sony_boot_color_id.h"
#include "sony_boot_utils.h"
#include "sony_libc.h"
#include "xboot_glue.h"

/* Header files from loader */
#include "fcslog.h"
#include "fcserr.h"


/* Color ID Length (4 digit-number based on Color ID in ASCII code) */
#define TA_COLOR_ID_MAXLEN  4

int bootconfig_append_color_id(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size)
{
	char color_id[TA_COLOR_ID_MAXLEN+1];
	const char colortag[] = " androidboot.hardware.color=";
	const int bufsize = sizeof(colortag) + sizeof(color_id);

	if (context == NULL ||
		config_data == NULL ||
		config_size == 0 ||
		context->bootconfig == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	context->bootconfig->taColorId = malloc(bufsize);
	if (context->bootconfig->taColorId == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}
	context->bootconfig->taColorId[0] = '\0';

	/* set color id from config_data */
	snprintf(color_id, sizeof(color_id), "%u", (uint8_t)*config_data);
	color_id[TA_COLOR_ID_MAXLEN] = '\0'; /* set Null just in case */

	/* Append color id to bootconfig */
	if (strlen(color_id) != 0) {
		strlcat(context->bootconfig->taColorId,
			colortag, bufsize);
		strlcat(context->bootconfig->taColorId,
			color_id, bufsize);
	} else {
		FCS_LOG_ERR("No Color ID\n");
	}
	return FCSERR_OK;
}

int cmdline_append_color_id(struct xboot_ctx *boot_context,
	const uint8_t *ta_buf, const size_t ta_size)
{
	char color_id[TA_COLOR_ID_MAXLEN+1];
	char colortag[] = " androidboot.hardware.color=";
	const int bufsize = sizeof(colortag) + sizeof(color_id);
	char ta_color_id[sizeof(colortag) + sizeof(color_id)] = {0};

	if (boot_context == NULL ||
		ta_buf == NULL ||
		ta_size == 0 ||
		boot_context->bootconfig == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* copy color id from config_data */
	snprintf(color_id, sizeof(color_id), "%u", (uint8_t)*ta_buf);
	color_id[TA_COLOR_ID_MAXLEN] = '\0'; /* set Null just in case */

	if (strlen(color_id) != 0) {
		strlcat(ta_color_id, colortag, bufsize);
		strlcat(ta_color_id, color_id, bufsize);
		boot_context->bootconfig->taCommandLineArgs = sony_alloc_strcat(
			boot_context->bootconfig->taCommandLineArgs, ta_color_id);
	} else {
		FCS_LOG_ERR("No Color ID\n");
	}
	return FCSERR_OK;
}
