/** @file DTBExtnLib.h
  FdtLib (edk2) Extended APIs

  Copyright (c) 2020-2022 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/19/22   yps     New API:fdt_merge_overlay()
 10/12/21   tmt     Add uint16, cache & slice APIs
 06/25/21   tmt     Update Performance info on certain APIs
 04/22/21   tmt     New APIs: fdt_node_copy, fdt_node_cmp, fdt_get_uint32_prop_list_slice, fdt_get_name_index
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

#include "DTBDefs.h"

/*=========================================================================
     API Function Prototypes
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
int fdt_merge_overlay(void *primary_blob, void *overlay_blob, void *merge_blob, int size_merge_blob);
/**
 * fdt_set_blob_handle - init DTB handle to point to blob in memory
 * @blob: pointer to the device tree blob
 * @blob_id: index for requested blob
 *
 * returns: 0 (success) else error indicator
 */
int fdt_set_blob_handle(void *blob, int blob_id);

/**
 * fdt_get_blob_handle - return DTB handle
 * @blob: pointer to the device tree blob
 * @blob_id: index for requested blob
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_blob_handle(void **blob, int blob_id);

/**
 * fdt_init_root_handle_for_driver - return fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @blob: pointer to the device tree blob
 *
 * returns: 0 (success) else error indicator
 */
int fdt_init_root_handle_for_driver(fdt_node_handle *node, void *blob);

/**
 * fdt_init_root_handle_for_driver_by_id - return fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @blob_id: index into blob handle array
 *
 * returns: 0 (success) else error indicator
 */
int fdt_init_root_handle_for_driver_by_id(fdt_node_handle *node, int blob_id);

/**
 * fdt_get_node_handle - return fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @blob: pointer to the device tree blob
 * @name: pointer to node name (string)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_node_handle(fdt_node_handle *node, void *blob, char *name);

/**
 * fdt_node_copy - copy fdt_node_handle_object
 * @dst: pointer to destination fdt_node_handle object
 * @src: pointer to source fdt_node_handle object
 *
 * returns: 0 (success) else error indicator
 */
int fdt_node_copy(fdt_node_handle *dst, fdt_node_handle *src);

/**
 * fdt_node_cmp - compare 2 fdt_node_handle_objects
 * @node_a: pointer to fdt_node_handle object A
 * @node_b: pointer to fdt_node_handle object B
 *
 * returns:
 *  0 if nodes match
 *  -FDT_ERR_QC_NODE_DIFFERENT if nodes DO NOT match
 *  else error indicator, e.g. NULL PTR
 */
int fdt_node_cmp(fdt_node_handle *node_a, fdt_node_handle *node_b);

/**
 * fdt_get_phandle_node - return phandle fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @phandle: phandle reference in blob
 * @pnode: pointer to fdt_node_handle for new phandle node
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_phandle_node(fdt_node_handle *node, int phandle, fdt_node_handle *pnode);

/**
 * fdt_get_parent_node - return parent node fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @pnode: pointer to fdt_node_handle for new parent node
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_parent_node(fdt_node_handle *node, fdt_node_handle *pnode);

/**
 * fdt_get_blob_size - return size of blob in memory
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold DTB size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_blob_size(fdt_node_handle *node, uint32_t *size);

/**
 * fdt_get_prop_size - return required buffer size for uint32 list
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_prop_size(fdt_node_handle *node, const char *prop_name, uint32_t *size);

/**
 * fdt_get_boolean_prop - return boolean property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint32 to hold property value
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_boolean_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value);

/**
 * fdt_get_uint8_prop - return uint8 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint8 to hold property value
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint8_prop(fdt_node_handle *node, const char *prop_name, uint8_t *value);

/**
 * fdt_get_uint8_prop_list - return uint8 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint8 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint8_prop_list(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t size);

/**
 * fdt_get_uint8_prop_list_slice - return slice of uint8 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint8 list values
 * @index: starting index to extract
 * @count: number of values to extract
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint8_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t index, uint32_t count);

/**
 * fdt_get_uint16_prop - return uint16 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint16 to hold property value
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint16_prop(fdt_node_handle *node, const char *prop_name, uint16_t *value);

/**
 * fdt_get_uint16_prop_list - return uint16 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint16 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint16_prop_list(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t size);

/**
 * fdt_get_uint16_prop_list_slice - return slice of uint16 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint16 list values
 * @index: starting index to extract
 * @count: number of values to extract
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint16_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t index, uint32_t count);

/**
 * fdt_get_uint32_prop - return uint32 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint32 to hold property value
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value);

/**
 * fdt_get_uint32_prop_list - return uint32 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint32 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop_list(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t size);

/**
 * fdt_get_uint32_prop_list_slice - return slice of uint32 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint32 list values
 * @index: starting index to extract
 * @count: number of values to extract
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t index, uint32_t count);

/**
 * fdt_get_uint64_prop - return uint64 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint64 to hold property value
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint64_prop(fdt_node_handle *node, const char *prop_name, uint64_t *value);

/**
 * fdt_get_uint64_prop_list - return uint64 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint64 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint64_prop_list(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t size);

/**
 * fdt_get_uint64_prop_list_slice - return slice of uint64 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint64 list values
 * @index: starting index to extract
 * @count: number of values to extract
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint64_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t index, uint32_t count);

/**
 * fdt_get_string_prop_list - return string list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @string_list: buffer pointer to hold string list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_string_prop_list(fdt_node_handle *node, const char *prop_name, char *string_list, uint32_t size);

/**
 * fdt_get_prop_values_size_of_node - return required buffer size to hold all properties of node
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * Performance Note: if you are using this API in a loop or calling it repeatedly to pull
 *                   values from a single node you may want to use fdt_get_prop_values_of_node() instead
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_prop_values_size_of_node(fdt_node_handle *node, uint32_t *size);

/**
 * fdt_get_prop_values_of_node - return packed buffer of all properties of node
 * @node: pointer to fdt_node_handle object
 * @format: required for endianess, [b|B] = string/byte,
 *                                  [h|H] = half-word (16),
 *                                  [w|W] = word (32),
 *                                  [d|D] = double-word (64)
 * @packed_prop_values: buffer pointer to hold packed node properties
 * @size: buffer size (in bytes)
 *
 * Performance Impact: When retrieving property values from a node that easily maps to a C struct
 *                     this is the best performing API.  The first consecutive N properties of a node
 *                     can be retrieved by this API.  If you retrieve fewer properties than are present
 *                     in the node, this call will return with -FDT_ERR_QC_TRUNCATED.  This is really a
 *                     warning that the provided buffer is not large enough to hold all of the property values.
 *
 * WARNING: This is a potentially dangerous API to use because the C struct has to be in perfect
 *          synchronicity with the DTB node layout.  If there is a deviation you can expect a bug!!
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_prop_values_of_node(fdt_node_handle *node, char *format, void *packed_prop_values, uint32_t size);

/**
 * fdt_get_prop_names_size_of_node - return required buffer size to hold all property names in node
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_prop_names_size_of_node(fdt_node_handle *node, uint32_t *size);

/**
 * fdt_get_prop_names_of_node - return buffer of all property names in node
 * @node: pointer to fdt_node_handle object
 * @prop_names: buffer pointer to hold all property names
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_prop_names_of_node(fdt_node_handle *node, char *prop_names, uint32_t size);

/**
 * fdt_get_cache_of_subnodes - return cache of all subnodes of node
 * @node: pointer to fdt_node_handle object
 * @cache: pointer to fdt_node_handle array of size @count
 * @count: uint32 to hold count of subnodes
 * 
 * Performance Impact: This API is added specifically to address a
 *                     known performance issue.  When a node has sub-nodes
 *                     this API returns an array of fdt_node_handles
 *                     with the DTB offset for each sub-node, so no string
 *                     lookup of the sub-node is required.
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_cache_of_subnodes(fdt_node_handle *node, fdt_node_handle *cache, uint32_t count);

/**
 * fdt_get_count_of_subnodes - return count of all subnodes of node
 * @node: pointer to fdt_node_handle object
 * @count: pointer to uint32 to hold count of subnodes
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_count_of_subnodes(fdt_node_handle *node, uint32_t *count);

/**
 * fdt_get_size_of_subnode_names - return size of subnode names
 * @node: pointer to fdt_node_handle object
 * @names: pointer to uint32_t array to hold sizes
 * @count: uint32 to hold count of array items
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_size_of_subnode_names(fdt_node_handle *node, uint32_t *names, uint32_t count);

/**
 * fdt_get_subnode_names - return buffer of all subnode names
 * @node: pointer to fdt_node_handle object
 * @prop_names: buffer pointer to hold all subnode names
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_subnode_names(fdt_node_handle *node, void *names, uint32_t size);

/**
 * fdt_get_next_node_handle_for_compatible - return node offset w/ compatible string
 * @node: pointer to fdt_node_handle object
 * @compatible: pointer to compatible string to search for
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_next_node_handle_for_compatible(fdt_node_handle *node, const char *compatible);

/**
 * fdt_get_reg - return specific reg entry
 * @node: pointer to fdt_node_handle object
 * @reg_name:  NULL or name of index in range to return
 * @reg_index: index of range to return
 * @addr_code: indicate address size [-1..2]
 * @size_code: indicate cell size [-1..2]
 * @reg_paddr: (return) physical address
 * @reg_size:  (return) size of this region
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_reg(fdt_node_handle *node,
                           char *reg_name,
                            int  reg_index,
                            int  addr_code,
                            int  size_code,
                       uint64_t *reg_paddr,
                       uint64_t *reg_size);

/**
 * fdt_get_name_index - return index of target
* @node: pointer to fdt_node_handle object
* @pname: Name of string-list property
* @tname: Target name in string-list property
* @index: (return) index of target in list
*
* returns 0 (success) else error indicator
*/
int fdt_get_name_index(fdt_node_handle *node, char *pname, char *tname, int *index);


#endif  /* DTBEXTNLIB_H_ */
