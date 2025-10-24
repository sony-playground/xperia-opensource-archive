/** @file DTBDefs.h
  FdtLib (edk2) Extended APIs

  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/07/21   tmt     Add support for generic get_uintX_prop API
 09/28/21   tmt     Remove name from node_handle
 04/22/21   tmt     New error codes for new APIs
 03/24/21   tmt     Add error code for UEFI Protocol wrapper library
 02/17/21   tmt     Adjusted two QC error codes
 01/29/21   tmt     All struct/define from DTBExtnLib.h moved here (for UEFI)

=============================================================================*/

#ifndef DTBDEFS_H_
#define DTBDEFS_H_

/*===========================================================================
                        MACROS
===========================================================================*/

/* FdtLib error codes end here: #define FDT_ERR_MAX 17 (see libfdt.h) */
/* QC added error codes */
#define FDT_ERR_QC_NULLPTR 1000
#define FDT_ERR_QC_TRUNCATED 1001
#define FDT_ERR_QC_BUF2SMALL 1002
#define FDT_ERR_QC_NILVALUE 1003
#define FDT_ERR_QC_SDNULL 1004
#define FDT_ERR_QC_BADFORMAT 1005
#define FDT_ERR_QC_BADID 1006
#define FDT_ERR_QC_INPUT_ARG_ERR 1007
#define FDT_ERR_QC_REGIDX 1008
#define FDT_ERR_QC_TARGETIDX 1009
#define FDT_ERR_QC_MEMALLOC 1010
#define FDT_ERR_QC_BLOBID 1011
#define FDT_ERR_QC_NOTSUPPORTED 1012
#define FDT_ERR_QC_NOTREADY 1013
#define FDT_ERR_QC_NODE_DIFFERENT 1014
#define FDT_ERR_QC_SLICE_RANGE 1015
#define FDT_ERR_QC_SLICE_COUNT 1016
#define FDT_ERR_QC_BAD_SELECTOR 1017

/* Blob ID */
#define DEFAULT_BLOB_ID 0
#define MAX_BLOB_ID 5

/* fdt_get_reg() size code */
#define SIZE_NIL  0
#define SIZE_32   1
#define SIZE_64   2
#define SIZE_BLOB -1

/*===========================================================================
                        STRUCTS
===========================================================================*/

/* All Client APIs require following struct pointer as first parameter */
typedef struct {
	const void *blob;	/* pointer to DTB blob, opaque to client */
	int offset;			/* offset of this node within DTB blob */
} fdt_node_handle;

#endif  /* DTBDEFS_H_ */
