#include <Uefi.h>
#include <Library/DTBExtnUEFILib.h>
#include "libfdt.h"
#include "DTBExtnLib.h"

/* DTBExtnLib_blob.c EntryPoints */
int fdt_get_blob_handle(void **blob, int blob_id)
{
	// Need to assign blob to something otherwise it will cause static analysis issue
	static int stub;
	*blob = (void *) &stub;
	return 0;  // Blob is not used in UEFI APIs
}

int fdt_get_blob_size(fdt_node_handle *node, uint32_t *size)
{
	return FdtGetBlobSize((FdtNodeHandle *)node, (UINT32 *)size);
}

int fdt_init_root_handle_for_driver(fdt_node_handle *node, void *blob)
{
	return FdtInitRootHandleForDriver((FdtNodeHandle *)node);
}

int fdt_init_root_handle_for_driver_by_id(fdt_node_handle *node, int blob_id)
{
	return FdtInitRootHandleForDriverById((FdtNodeHandle *)node, (INT32)blob_id);
}

int fdt_set_blob_handle(void *blob, int blob_id)
{
	return -FDT_ERR_QC_NOTSUPPORTED;
}

/* DTBExtnLib_driver.c EntryPoints */
int fdt_get_name_index(fdt_node_handle *node, char *pname, char *tname, int *index)
{
	return FdtGetNameIndex((FdtNodeHandle *)node, (CHAR8 *)pname, (CHAR8 *)tname, (INT32 *)index);
}

int fdt_get_next_node_handle_for_compatible(fdt_node_handle *node, const char *compatible)
{
	return FdtGetNextNodeHandleForCompatible((FdtNodeHandle *)node, (const CHAR8 *)compatible);
}

int fdt_get_reg(fdt_node_handle *node, char *reg_name, int  reg_index, int  addr_code,
                int  size_code, uint64_t *reg_paddr, uint64_t *reg_size)
{
	return FdtGetReg((FdtNodeHandle *)node, (CHAR8 *)reg_name, (INT32)reg_index, (INT32)addr_code,
	                  (INT32)size_code, (UINT64 *)reg_paddr, (UINT64 *)reg_size);
}

/* DTBExtnLib_node.c EntryPoints */
int fdt_get_cache_of_subnodes(fdt_node_handle *node, fdt_node_handle *cache, uint32_t count)
{
	return FdtGetCacheOfSubnodes((FdtNodeHandle *)node, (FdtNodeHandle *)cache, (UINT32)count);
}

int fdt_get_count_of_subnodes(fdt_node_handle *node, uint32_t *count)
{
	return FdtGetCountOfSubnodes((FdtNodeHandle *)node, (UINT32 *)count);
}

int fdt_get_node_handle(fdt_node_handle *node, void *blob, char *name)
{
	return FdtGetNodeHandle((FdtNodeHandle *)node, (CHAR8 *)name);
}

int fdt_get_parent_node(fdt_node_handle *node, fdt_node_handle *pnode)
{
	return FdtGetParentNode((FdtNodeHandle *)node, (FdtNodeHandle *)pnode);
}

int fdt_get_phandle_node(fdt_node_handle *node, int phandle, fdt_node_handle *pnode)
{
	return FdtGetPhandleNode((FdtNodeHandle *)node, (INT32)phandle, (FdtNodeHandle *)pnode);
}

int fdt_get_prop_names_of_node(fdt_node_handle *node, char *prop_names, uint32_t size)
{
	return FdtGetPropNamesOfNode((FdtNodeHandle *)node, (CHAR8 *)prop_names, (UINT32) size);
}

int fdt_get_prop_names_size_of_node(fdt_node_handle *node, uint32_t *size)
{
	return FdtGetPropNamesSizeOfNode((FdtNodeHandle *)node, (UINT32 *)size);
}

int fdt_get_prop_values_of_node(fdt_node_handle *node, char *format, void *packed_prop_values, uint32_t size)
{
	return FdtGetPropValuesOfNode((FdtNodeHandle *)node, (CHAR8 *)format, packed_prop_values, (UINT32) size);
}

int fdt_get_prop_values_size_of_node(fdt_node_handle *node, uint32_t *size)
{
	return FdtGetPropValuesSizeOfNode((FdtNodeHandle *)node, (UINT32 *)size);
}

int fdt_get_size_of_subnode_names(fdt_node_handle *node, uint32_t *names, uint32_t count)
{
	return FdtGetSizeOfSubnodeNames((FdtNodeHandle *)node, (UINT32 *)names, (UINT32) count);
}

int fdt_get_subnode_names(fdt_node_handle *node, void *names, uint32_t size)
{
	return FdtGetSubnodeNames((FdtNodeHandle *)node, names, (UINT32) size);
}

int fdt_node_cmp(fdt_node_handle *node_a, fdt_node_handle *node_b)
{
	return FdtNodeCmp((FdtNodeHandle *)node_a, (FdtNodeHandle *)node_b);
}

int fdt_node_copy(fdt_node_handle *dst, fdt_node_handle *src)
{
	return FdtNodeCopy((FdtNodeHandle *)dst, (FdtNodeHandle *)src);
}

/* DTBExtnLib_prop.c EntryPoints */
int fdt_get_boolean_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value)
{
   return FdtGetBooleanProp((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT32 *)value);
}

int fdt_get_prop_size(fdt_node_handle *node, const char *prop_name, uint32_t *size)
{
   return FdtGetPropSize((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT32 *)size);
}

int fdt_get_string_prop_list(fdt_node_handle *node, const char *prop_name, char *string_list, uint32_t size)
{
	return FdtGetStringPropList((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (CHAR8 *)string_list, (UINT32) size);
}

int fdt_get_uint32_prop(fdt_node_handle *node, const char *prop_name, uint32_t *value)
{
	return FdtGetUint32Prop((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT32 *)value);
}

int fdt_get_uint32_prop_list(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t size)
{
	return FdtGetUint32PropList((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT32 *)prop_list, (UINT32)size);
}

int fdt_get_uint32_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint32_t *prop_list, uint32_t index, uint32_t count)
{
	return FdtGetUint32PropListSlice((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT32 *)prop_list, (UINT32)index, (UINT32)count);
}

int fdt_get_uint64_prop(fdt_node_handle *node, const char *prop_name, uint64_t *value)
{
	return FdtGetUint64Prop((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT64 *)value);
}

int fdt_get_uint64_prop_list(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t size)
{
	return FdtGetUint64PropList((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT64 *)prop_list, (UINT32) size);
}

int fdt_get_uint64_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint64_t *prop_list, uint32_t index, uint32_t count)
{
	return FdtGetUint64PropListSlice((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT64 *)prop_list, (UINT32)index, (UINT32)count);
}

int fdt_get_uint8_prop(fdt_node_handle *node, const char *prop_name, uint8_t *value)
{
	return FdtGetUint8Prop((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT8 *)value);
}

int fdt_get_uint8_prop_list(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t size)
{
	return FdtGetUint8PropList((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT8 *)prop_list, (UINT32) size);
}

int fdt_get_uint8_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint8_t *prop_list, uint32_t index, uint32_t count)
{
	return FdtGetUint8PropListSlice((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT8 *)prop_list, (UINT32)index, (UINT32)count);
}

int fdt_get_uint16_prop(fdt_node_handle *node, const char *prop_name, uint16_t *value)
{
	return FdtGetUint16Prop((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT16 *)value);
}

int fdt_get_uint16_prop_list(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t size)
{
	return FdtGetUint16PropList((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT16 *)prop_list, (UINT32)size);
}

int fdt_get_uint16_prop_list_slice(fdt_node_handle *node, const char *prop_name, uint16_t *prop_list, uint32_t index, uint32_t count)
{
	return FdtGetUint16PropListSlice((FdtNodeHandle *)node, (const CHAR8 *)prop_name, (UINT16 *)prop_list, (UINT32)index, (UINT32)count);
}
