/** @file DTBExtnLib_overlay.c
  FdtLib (edk2) Extended APIs

  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/21/22   tmt     Initial creation of file

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

/*=========================================================================
     Globals
==========================================================================*/

/*=========================================================================
      Public APIs
==========================================================================*/

/**
 * fdt_merge_overlay - Merge overlay into primary blob
 * @primary_blob:    Primary DTB tree
 * @overlay_blob:    Overlay DTB tree
 * @merge_blob:      Merged  DTB tree
 * @size_merge_blob: size of merge blob
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls:
 * 		fdt_totalsize()
 * 		fdt_open_into()
 * 		fdt_overlay_apply() 
 */
int fdt_merge_overlay(void *primary_blob, void *overlay_blob, void *merge_blob, int size_merge_blob)
{
	int ret_value;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(primary_blob);
	PTR_CHECK(overlay_blob);
	PTR_CHECK(merge_blob);

	if ( (fdt_totalsize(primary_blob) + fdt_totalsize(overlay_blob)) > size_merge_blob ) {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Merge Buffer too small[%d]", size_merge_blob);
			PUTS(ibuffer);
		}
		ret_value = -FDT_ERR_QC_BUF2SMALL;
	} else {
		ret_value = fdt_open_into(primary_blob, merge_blob, size_merge_blob);
		if (0 != ret_value) {
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "fdt_open_into ERROR[%d]", ret_value);
				PUTS(ibuffer);
			}
		} else {
			ret_value = fdt_overlay_apply(merge_blob, overlay_blob);
			if (0 != ret_value) {
				if (dtb_config.verbose) {
					SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "fdt_overlay_apply ERROR[%d]", ret_value);
					PUTS(ibuffer);
				}
			}
		}
	}

	if (0 == ret_value) {
		/* sanity check dtb blob */
		ret_value = fdt_check_header(merge_blob);
		if (0 != ret_value) {
			if (dtb_config.verbose) {
				PUTS("merge_blob failed fdt_check_header");
			}
			ret_value = -FDT_ERR_BADMAGIC;
		}
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d]", __func__, ret_value);
		PUTS(ibuffer);
	}

	return ret_value;
}
