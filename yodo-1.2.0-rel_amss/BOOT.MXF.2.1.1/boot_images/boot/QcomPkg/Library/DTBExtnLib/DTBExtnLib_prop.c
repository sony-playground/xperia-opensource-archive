/** @file DTBExtnLib_prop.c
  FdtLib (edk2) Extended APIs

  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/12/21   tmt     Refactore get_prop_value APIs to have single common get_uintX_ call,
                    add uint16 and slice support
 09/28/21   tmt     Remove name from node_handle
 04/22/21   tmt     Add fdt_get_uint32_prop_list_slice()
 02/17/21   tmt     Always return underlying library error code, when possible
 01/07/21   tmt     All prop APIs in this file

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

typedef enum dt_data_type {
	dt_uint8 = 1,
	dt_uint16 = 2,
	dt_uint32 = 4,
	dt_uint64 = 8
} dt_data_type;

typedef union dt_ptr_type {
	uint8_t  *u8;
	uint16_t *u16;
	uint32_t *u32;
	uint64_t *u64;
} dt_ptr_type;

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
 * fdt_get_prop_size - return size of property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_getprop()
 */
int fdt_get_prop_size(fdt_node_handle *node, const char *prop_name, uint32_t *size)
{
	int len;							/* FdtLib: return errors & size */
	const void *prop_value;				/* FdtLib: return property value */
	int ret_value = 0;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(prop_name);
	PTR_CHECK(size);

	prop_value = fdt_getprop(node->blob, node->offset, prop_name, &len);
	if (NULL == prop_value) {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, prop_name);
			PUTS(ibuffer);
		}
		ret_value = len;
	} else
		*size = len;

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%s].[%d]",
			__func__, ret_value, prop_name, (fdt32_t)*size);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * _fdt_get_uintX_prop_list - return uintX list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uintX list values
 * @size: buffer size (in bytes)
 * @index: start index in list to extract (0 for whole range)
 * @count: count of slice to extract (0 for whole range)
 * @selector: enum, specifying type/size of actual value
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_getprop()
 *               fdt16_to_cpu()
 *               fdt32_to_cpu()
 *               fdt64_to_cpu()
 */
static int _fdt_get_uintX_prop_list(fdt_node_handle *node, const char *prop_name, void *prop_list, uint32_t size, uint32_t index, uint32_t count, dt_data_type selector)
{
	int len;							/* FdtLib: return errors & size */
	const void *vptr = NULL;			/* FdtLib: return property value */
	int ret_value = 0;

	dt_ptr_type src, dst;
	int elem_count, data_count;
	int i;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(prop_name);
	PTR_CHECK(prop_list);

	/* pull out property value from node */
	vptr = fdt_getprop(node->blob, node->offset, prop_name, &len);
	if (NULL != vptr) {
		elem_count = size/selector;		/* count of elements to extract */
		data_count = len/selector;		/* count of data elements in DTB */
		if (index > data_count) {
			/* First check: start index beyond range */
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Slice index[%d].out of range[%d]", (fdt32_t)index, elem_count);
				PUTS(ibuffer);
			}
			ret_value = -FDT_ERR_QC_SLICE_RANGE;
		} else if ((index+count) > data_count) {
			/* Second check: start index+count out of range */
			/* (index+count) = starting location in DTB property */
			/* data_count = number of elements in DTB property */
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Slice count[%d].out of range[%d]", (fdt32_t)(index+count), elem_count);
				PUTS(ibuffer);
			}
			ret_value = -FDT_ERR_QC_SLICE_COUNT;
		} else if ((len-(index*selector)) > (size+(count*selector))) {
			/* Third check: size of buffer too small for data to extract */
			/* len = size of data in DTB property */
			/* (index*selector) takes away list elements in front of slice */
			/* (count*selector) is size of slice being requested */
			/* size is length of passed in buffer for extraction */
			/* This check takes advantage of index=0 and count=0 when no slice */
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Buf[%d].too small[%d]", (fdt32_t)size, len);
				PUTS(ibuffer);
			}
			ret_value = -FDT_ERR_QC_BUF2SMALL;
		} else {
			/* all checks complete, let's grab the property value(s) */
			switch (selector) {
				case dt_uint8:
					src.u8 = (uint8_t *)vptr;
					dst.u8 = (uint8_t *)prop_list;
					break;
				case dt_uint16:
					src.u16 = (uint16_t *)vptr;
					dst.u16 = (uint16_t *)prop_list;
					break;
				case dt_uint32:
					src.u32 = (uint32_t *)vptr;
					dst.u32 = (uint32_t *)prop_list;
					break;
				case dt_uint64:
					src.u64 = (uint64_t *)vptr;
					dst.u64 = (uint64_t *)prop_list;
					break;
				default:
					return -FDT_ERR_QC_BAD_SELECTOR;
			}
			if (dtb_config.trace) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Selector[%d]..Size[%d]..Elem_Count[%d]",
						 selector, (fdt32_t)size, elem_count);
				PUTS(ibuffer);
			}

			for (i=0; i<elem_count; i++) {
				switch (selector) {
					case dt_uint8:
						dst.u8[i] = src.u8[i+index];
						break;
					case dt_uint16:
						dst.u16[i] = fdt16_to_cpu(src.u16[i+index]);
						break;
					case dt_uint32:
						dst.u32[i] = fdt32_to_cpu(src.u32[i+index]);
						break;
					case dt_uint64:
						dst.u64[i] = fdt64_to_cpu(src.u64[i+index]);
						break;
				}
			}
		}
	} else {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, prop_name);
			PUTS(ibuffer);
		}
		ret_value = len;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%s].[%d]",
			__func__, ret_value, prop_name, (fdt32_t)size);
		PUTS(ibuffer);
	}
	return ret_value;
}

/**
 * fdt_get_uint8_prop_list - return uint8 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint8 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint8_prop_list(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t size)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, size, 0, 0, dt_uint8);
}

/**
 * fdt_get_uint8_prop - return uint8 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint8 to hold property value
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint8_prop(fdt_node_handle *node, const char *prop_name, uint8_t *value)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return fdt_get_uint8_prop_list(node, prop_name, value, 1);
}

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
int fdt_get_uint8_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t index, uint32_t count)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, (count*dt_uint8), index, count, dt_uint8);
}

/**
 * fdt_get_uint16_prop_list - return uint16 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint16 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint16_prop_list(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t size)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, size, 0, 0, dt_uint16);
}

/**
 * fdt_get_uint16_prop - return uint16 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint16 to hold property value
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint16_prop(fdt_node_handle *node, const char *prop_name, uint16_t *value)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return fdt_get_uint16_prop_list(node, prop_name, value, 2);
}

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
int fdt_get_uint16_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t index, uint32_t count)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, (count*dt_uint16), index, count, dt_uint16);
}

/**
 * fdt_get_uint32_prop_list - return uint32 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint32 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop_list(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t size)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, size, 0, 0, dt_uint32);
}

/**
 * fdt_get_uint32_prop - return uint32 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint32 to hold property value
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint32_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return fdt_get_uint32_prop_list(node, prop_name, value, 4);
}

/**
 * fdt_get_uint64_prop_list - return uint64 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint64 list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint64_prop_list(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t size)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, size, 0, 0, dt_uint64);
}

/**
 * fdt_get_uint64_prop - return uint64 property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint64 to hold property value
 *
 * returns: 0 (success) else error indicator
 */
int fdt_get_uint64_prop(fdt_node_handle *node, const char *prop_name, uint64_t *value)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return fdt_get_uint64_prop_list(node, prop_name, value, 8);
}

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
int fdt_get_uint64_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t index, uint32_t count)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, (count*dt_uint64), index, count, dt_uint64);
}

/**
 * fdt_get_boolean_prop - return boolean property value
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @value: pointer to uint32 to hold property value
 *
 * returns: 0 (success) else error indicator
 * 
 */
int fdt_get_boolean_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return fdt_get_uint32_prop_list(node, prop_name, value, 4);
}

/**
 * fdt_get_uint32_prop_list_slice - return slice of uint32 list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @prop_list: buffer pointer to hold uint32 list values
 * @index: starting index to extract
 * @count: number of values to extract
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_getprop()
 *               fdt32_to_cpu()
 */
int fdt_get_uint32_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t index, uint32_t count)
{
	if (dtb_config.trace)
		PUTS((char *)__func__);

	return _fdt_get_uintX_prop_list(node, prop_name, prop_list, (count*dt_uint32), index, count, dt_uint32);
}

/**
 * fdt_get_string_list - return string list property values
 * @node: pointer to fdt_node_handle object
 * @prop_name: property name
 * @string_list: buffer pointer to hold string list values
 * @size: buffer size (in bytes)
 *
 * returns: 0 (success) else error indicator
 * 
 * FdtLib calls: fdt_getproperty()
 */
int fdt_get_string_prop_list(fdt_node_handle *node, const char *prop_name, char *string_list, uint32_t size)
{
	int len;							/* FdtLib: return errors & size */
	const struct fdt_property *fdtp;	/* FdtLib: return raw prop data */
	int ret_value = 0;

	int i;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(prop_name);
	PTR_CHECK(string_list);

	/* pull out property value from node */
	fdtp = fdt_get_property(node->blob, node->offset, prop_name, &len);
	if (NULL != fdtp) {
		if (len > size) {
			/* buffer size passed in is too small for data */
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Buf[%d].too small[%d]", (fdt32_t)size, len);
				PUTS(ibuffer);
			}
			return -FDT_ERR_QC_BUF2SMALL;
		} else {
			for (i=0; i<len; i++)
				string_list[i] = fdtp->data[i];
			string_list[len-1] = '\0';	
		}
	} else {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, prop_name);
			PUTS(ibuffer);
		}
		ret_value = len;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%s].[%d]",
			__func__, ret_value, prop_name, (fdt32_t)size);
		PUTS(ibuffer);
	}

	return ret_value;
}
