/** @file DTBInternals.h
  FdtLib (edk2) Extended APIs

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/12/21   tmt     Support split of source into multiple files
 12/16/20   tmt     Q6 build system changes
 11/23/20   tmt     Config fields should use fdt typedefs (for ease of porting)
 08/04/20   tmt     Initial creation of Library

=============================================================================*/

#ifndef DTBINTERNALS_H_
#define DTBINTERNALS_H_

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

/*=========================================================================
     Default Defines
==========================================================================*/

#define PTR_CHECK(ptr) do { \
	if (NULL == ptr) return -FDT_ERR_QC_NULLPTR; \
} while(0)

#define BLOBID_CHECK(id) do { \
	if ((id < 0) || (id >= MAX_BLOB_ID)) return -FDT_ERR_QC_BLOBID; \
} while(0)

/* All lookups are string-based */
/* Convenient buffer size for static or dynamic allocation */
#define DTB_LINE_BUF_SIZE 0x100

/* Config settings for library, controls debug output */
typedef struct {
	int	client;
	int	trace;
	int	verbose;
} Config;
extern Config dtb_config;

extern void dtb_hex_dump(char *title, void *addr, int len);

#endif  /* DTBINTERNALS_H_ */
