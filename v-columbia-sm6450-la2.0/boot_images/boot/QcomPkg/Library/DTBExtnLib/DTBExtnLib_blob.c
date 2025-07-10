/** @file DTBExtnLib_blob.c
  FdtLib (edk2) Extended APIs

  Copyright (c) 2021, 2023 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/07/23   sym     CR-3307011 security fixes
 09/28/21   tmt     Remove name from node_handle
 02/17/21   tmt     Add check on get_blob to return error if no blob set
 01/07/21   tmt     All dtb_blob[] references in this file

=============================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include <stdint.h>

#include <libfdt_env.h>
#include <fdt.h>
#include <libfdt.h>

#include "DTBExtnLib.h"
#include "DTBInternals.h"
#include "DTBExtnLib_env.h"

/*=========================================================================
     Default Defines
==========================================================================*/

/*=========================================================================
     Local Static Variables
==========================================================================*/
static void *dtb_blob[MAX_BLOB_ID] = {NULL, NULL, NULL, NULL, NULL};

/*=========================================================================
     Globals
==========================================================================*/
Config dtb_config = {0, 0, 0};

/*=========================================================================
      Public APIs
==========================================================================*/

/**
 * fdt_check_for_valid_blob - Sanity check blob pointer
 * @blob: pointer to the device tree blob
 * @bsize: size of blob
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_check_header()
 */
int fdt_check_for_valid_blob(void *blob, size_t bsize)
{
	int ret_value;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(blob);

	/* sanity check dtb blob */
	/* 1) passed in size must be >= FDT header */
	if (bsize < FDT_V17_SIZE) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}

	/* 2) use internal function to check header */
	ret_value = fdt_check_header(blob);
	if (0 != ret_value) {
		if (dtb_config.verbose) {
			 PUTS("blob failed fdt_check_header");
		}
		ret_value = -FDT_ERR_BADMAGIC;
		goto exit;
	}

	/* 3) Sanity check each field in header... */
	/* 3.a) confirm blob will fit into buffer (it isn't truncated) */
	if (bsize < fdt_totalsize(blob)) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}
	/* 3.b) confirm offset to structure is within bsize */
	if (bsize < fdt_off_dt_struct(blob)) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}
	/* 3.c) confirm offset to strings is within bsize */
	if (bsize < fdt_off_dt_strings(blob)) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}
	/* 3.d) confirm offset to memory reserve map is within bsize */
	if (bsize < fdt_off_mem_rsvmap(blob)) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}
	/* 3.e) confirm whole strings is within bsize */
	if (bsize < (fdt_off_dt_strings(blob)+fdt_size_dt_strings(blob))) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}
	/* 3.f) confirm whole structure is within bsize */
	if (bsize < (fdt_off_dt_struct(blob)+fdt_size_dt_struct(blob))) {
		ret_value = -FDT_ERR_NOSPACE;
		goto exit;
	}

exit:
	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d]..[%p][%ld]", __func__, ret_value, blob, bsize);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_set_blob_handle - init DTB handle to point to blob in memory
 * @blob: pointer to the device tree blob
 * @bsize: size of blob
 * @blob_id: index for requested blob
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_check_header()
 */
int fdt_set_blob_handle(void *blob, size_t bsize, int blob_id)
{
	int ret_value;
	fdt_node_handle node;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(blob);
	BLOBID_CHECK(blob_id);

	/* sanity check dtb blob */
	ret_value = fdt_check_for_valid_blob(blob, bsize);

	if (0 == ret_value) {
		/* blob passes checks... */
		ret_value = fdt_get_node_handle(&node, blob, "/sw/boot");
		if (0 == ret_value) {
			ret_value = fdt_get_uint32_prop_list(&node, "config", (void *)&dtb_config, sizeof(Config));
			if (0 == ret_value) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "DTBExtnLib config  client[%x].trace[%x].verbose[%x]",
						dtb_config.client, dtb_config.trace, dtb_config.verbose);
				PUTS(ibuffer);
			}
		}
		ret_value = 0;
		dtb_blob[blob_id] = blob;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d]..[%p][%ld][%d]", __func__, ret_value, blob, bsize, blob_id);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_blob_handle - return DTB handle
 * @blob: pointer to the device tree blob
 * @blob_id: index for requested blob
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_blob_handle(void **blob, int blob_id)
{
	int ret_value = 0;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(blob);
	BLOBID_CHECK(blob_id);

	if (NULL == dtb_blob[blob_id]) {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Requested Blob Handle is NULL [%d]", blob_id);
			PUTS(ibuffer);
		}
		ret_value = -FDT_ERR_QC_NULLPTR;
	} else {
		*blob = dtb_blob[blob_id];
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d]", __func__, ret_value);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_blob_size - return size of blob in memory
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold DTB size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_blob_size(fdt_node_handle *node, uint32_t *size)
{
	int ret_value = 0;
	struct fdt_header *fhdr;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(node->blob);
	PTR_CHECK(size);

	fhdr = (struct fdt_header *)node->blob;

	if (dtb_config.client) {
		dtb_hex_dump("fdt_header", fhdr, sizeof(struct fdt_header));
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tmagic[%x]", fdt_magic(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\ttotalsize[%d]", fdt_totalsize(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\toff_dt_struct[%x]", fdt_off_dt_struct(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\toff_dt_strings[%x]", fdt_off_dt_strings(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\toff_mem_rsvmap[%x]", fdt_off_mem_rsvmap(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tversion[%d]", fdt_version(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tlast_comp_version[%d]", fdt_last_comp_version(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tboot_cpuid_phys[%d]", fdt_boot_cpuid_phys(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tsize_dt_strings[%d]", fdt_size_dt_strings(fhdr));
		PUTS(ibuffer);
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "\tsize_dt_struct[%d]", fdt_size_dt_struct(fhdr));
		PUTS(ibuffer);
	}

	*size = fdt_totalsize(fhdr);

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d]..size[%d]", __func__, ret_value, (fdt32_t)*size);
		PUTS(ibuffer);
	}

	return ret_value;
}

/*
 * The fdt_init_root_handle APIs are included here because they
 * need access to the blob_id[] table that is static to this file.
 * 
 * Logically, these functions would be included in the _driver file.
 */

/**
 * fdt_init_root_handle_for_driver - return fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @blob: pointer to the device tree blob
 *
 * returns: 0 (success) else error indicator
 */
int fdt_init_root_handle_for_driver(fdt_node_handle *node, void *blob)
{
	PTR_CHECK(node);
	PTR_CHECK(blob);

	node->blob = blob;
	node->offset = -1;

	if (dtb_config.trace) {
		PUTS((char *)__func__);
	}

	return 0;
}

/**
 * fdt_init_root_handle_for_driver_by_id - return fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @blob_id: index into blob handle array
 *
 * returns: 0 (success) else error indicator
 */
int fdt_init_root_handle_for_driver_by_id(fdt_node_handle *node, int blob_id)
{
	BLOBID_CHECK(blob_id);

	if (dtb_config.trace) {
		PUTS((char *)__func__);
	}
	return fdt_init_root_handle_for_driver(node, dtb_blob[blob_id]);
}
