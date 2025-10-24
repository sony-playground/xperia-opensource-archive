/** @file DTBExtnLib.h
  FdtLib (edk2) Extended APIs

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/29/21   tmt     Move all struct/define to separate file for UEFI
 01/08/21   tmt     New APIs: fdt_get_blob_size() & fdt_get_parent_node()
 12/16/20   tmt     Initial support for QDI driver probing
 11/23/20   tmt     Add phandle API(s)
 09/22/20   tmt     Add sub-node APIs, create node_handle
 07/16/20   tmt     Initial creation of Library

=============================================================================*/

#ifndef DTBEXTNLIB_H_
#define DTBEXTNLIB_H_

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

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
	char *name;			/* string name of node */
} fdt_node_handle;


/*=========================================================================
     API Function Prototypes
==========================================================================*/
/**
 * fdt_get_node_handle_ex - return fdt_node_handle
 * If not found, will attempt to search one level down in tree
 * @node: pointer to fdt_node_handle object
 * @blob: pointer to the device tree blob
 * @name: pointer to node name (string)
 * @look_under: pointer to name of node to look under if not found (string)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_find_node(void *blob, char *name, int namelen, char *look_under);

/**
 * fdt_get_uint32_prop_list - return uint32 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint32 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop_list(void *blob, int offset, const char *prop_name, uint32_t *prop_list, uint32_t size);

/**
 * fdt_get_subnode_with_uint32_prop - return node offset w/ compatible string
 * @node: pointer to fdt_node_handle object
 * @prop_name: name of property to compare against
 * @prop_value: pointer to value of property comparing against
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_subnode_with_uint32_prop(void *blob, int offset, char *prop_name,  uint32_t prop_value);

#endif  /* DTBEXTNLIB_H_ */

