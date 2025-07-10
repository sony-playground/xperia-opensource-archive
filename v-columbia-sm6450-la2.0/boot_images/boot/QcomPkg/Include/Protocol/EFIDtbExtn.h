/** @file
 *
 * UEFI DTB Ext Protocol
 *
 * Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/12/21   tmt     Add new APIs: cache, uint16 & slice
 01/28/21   ai      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/DTBDefs.h>

#ifndef ___EFI_DTB_EXTN_PROTOCOL_H__
#define ___EFI_DTB_EXTN_PROTOCOL_H__

/* External global reference to the DTB Ext Protocol GUID */
extern EFI_GUID gEfiDtbExtnProtocolGuid;

/* Protocol GUID definition. */
#define EFI_DTB_EXTN_PROTOCOL_GUID \
  { 0x0389b776, 0x625f, 0x11eb, { 0x83, 0xbe, 0xc7, 0x41, 0xa9, 0x13, 0xde, 0x34 } }

/*
 *   Document the version changes here
 *   V 1.0
 *      Initial version
 *
 * */
#define EFI_DTB_EXTN_PROTOCOL_VER_INIT               0x00010000
#define EFI_DTB_EXTN_PROTOCOL_VER_REV1               0x00010001

/* Current protocol version */
#define EFI_DTB_EXTN_PROTOCOL_VERSION                EFI_DTB_EXTN_PROTOCOL_VER_REV1

/*******************************************************************************
 *
 *   Interface type definitions
 *
 ******************************************************************************/

/* See DTBExtnLib.h for API documentation
   See DTBDefs.h for error codes */
typedef fdt_node_handle  FdtNodeHandle;

/* DTBExtnLib_blob.c EntryPoints */
typedef INT32 (*FDT_INIT_ROOT_HANDLE_FOR_DRIVER) \
  (IN OUT FdtNodeHandle *Node);

/* These EntryPoints explicitly omitted from UEFI Interface:
 * 		int fdt_get_blob_handle(void **blob, int blob_id)
 * 		int fdt_get_blob_size(fdt_node_handle *node, uint32_t *size)
 * 		int fdt_init_root_handle_for_driver_by_id(fdt_node_handle *node, int blob_id)
 * 		int fdt_set_blob_handle(void *blob, int blob_id)
 */

typedef INT32 (*FDT_GET_NAME_INDEX) \
	(IN FdtNodeHandle *Node, IN CHAR8 *PName, IN CHAR8 *TName, OUT INT32 *Index);

typedef INT32 (*FDT_GET_NEXT_NODE_HANDLE_FOR_COMPATIBLE) \
  (IN OUT FdtNodeHandle *Node, IN CONST CHAR8 *Compatible);

typedef INT32 (*FDT_GET_REG) \
  (IN FdtNodeHandle *Node, IN CHAR8 *RegName, IN INT32 RegIndex, IN INT32 AddrCode, \
   IN INT32 SizeCode, IN OUT UINT64 *RegPaddr, IN OUT UINT64 *RegSize);

typedef INT32 (*FDT_GET_COUNT_OF_SUBNODES) \
  (IN FdtNodeHandle *Node, IN OUT UINT32 *Count);

typedef INT32 (*FDT_GET_NODE_HANDLE) \
  (IN OUT FdtNodeHandle *Node, IN CHAR8 *Name);

typedef INT32 (*FDT_GET_PARENT_NODE) \
  (IN FdtNodeHandle *Node, IN OUT FdtNodeHandle *Pnode);

typedef INT32 (*FDT_GET_PHANDLE_NODE) \
  (IN FdtNodeHandle *Node, IN INT32 Phandle, IN OUT FdtNodeHandle *Pnode);

typedef INT32 (*FDT_GET_PROP_NAMES_OF_NODE) \
  (IN FdtNodeHandle *Node, IN OUT CHAR8 *PropNames, IN UINT32 Size);

typedef INT32 (*FDT_GET_PROP_NAMES_SIZE_OF_NODE) \
  (IN FdtNodeHandle *Node, IN UINT32 *Size);

typedef INT32 (*FDT_GET_PROP_VALUES_OF_NODE) \
  (IN FdtNodeHandle *Node, IN CHAR8 *Format, IN OUT VOID *PackedPropValues, IN UINT32 Size);

typedef INT32 (*FDT_GET_PROP_VALUES_SIZE_OF_NODE) \
  (IN FdtNodeHandle *Node, IN OUT UINT32 *Size);

typedef INT32 (*FDT_GET_SIZE_OF_SUBNODE_NAMES) \
  (IN FdtNodeHandle *Node, IN OUT UINT32 *NameSizes, IN UINT32 Count);

typedef INT32 (*FDT_GET_SUBNODE_NAMES) \
  (IN FdtNodeHandle *Node, IN OUT VOID *Names, IN UINT32 Size);

typedef INT32 (*FDT_NODE_CMP) \
  (IN FdtNodeHandle *NodeA, IN FdtNodeHandle *NodeB);

typedef INT32 (*FDT_NODE_COPY) \
  (IN OUT FdtNodeHandle *Dst, IN FdtNodeHandle *Src);

typedef INT32 (*FDT_GET_BOOLEAN_PROP) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT32 *Value);

typedef INT32 (*FDT_GET_PROP_SIZE) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT32 *Size);

typedef INT32 (*FDT_GET_STRING_PROP_LIST) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT CHAR8 *StringList, IN UINT32 Size);

typedef INT32 (*FDT_GET_UINT32_PROP) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT32 *Value);

typedef INT32 (*FDT_GET_UINT32_PROP_LIST) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT32 *PropList, IN UINT32 Size);

typedef INT32 (*FDT_GET_UINT32_PROP_LIST_SLICE) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT32 *PropList, IN UINT32 Index, IN UINT32 Count);

typedef INT32 (*FDT_GET_UINT64_PROP) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT64 *Value);

typedef INT32 (*FDT_GET_UINT64_PROP_LIST) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT64 *PropList, IN UINT32 Size);

typedef INT32 (*FDT_GET_UINT8_PROP) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT8 *Value);

typedef INT32 (*FDT_GET_UINT8_PROP_LIST) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT8 *PropList, IN UINT32 Size);

typedef INT32 (*FDT_GET_UINT8_PROP_LIST_SLICE) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT8 *PropList, IN UINT32 Index, IN UINT32 Count);

typedef INT32 (*FDT_GET_UINT16_PROP) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT16 *Value);

typedef INT32 (*FDT_GET_UINT16_PROP_LIST) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT16 *PropList, IN UINT32 Size);

typedef INT32 (*FDT_GET_UINT16_PROP_LIST_SLICE) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT16 *PropList, IN UINT32 Index, IN UINT32 Count);

typedef INT32 (*FDT_GET_CACHE_OF_SUBNODES) \
  (IN FdtNodeHandle *Node, IN OUT FdtNodeHandle *Cache, IN UINT32 Count);

typedef INT32 (*FDT_GET_UINT64_PROP_LIST_SLICE) \
  (IN FdtNodeHandle *Node, IN CONST CHAR8 *PropName, IN OUT UINT64 *PropList, IN UINT32 Index, IN UINT32 Count);

typedef struct {
  UINT64                                  Version;
  FDT_INIT_ROOT_HANDLE_FOR_DRIVER         FdtInitRootHandleForDriver;
  FDT_GET_NAME_INDEX                      FdtGetNameIndex;
  FDT_GET_NEXT_NODE_HANDLE_FOR_COMPATIBLE FdtGetNextNodeHandleForCompatible;
  FDT_GET_REG                             FdtGetReg;
  FDT_GET_COUNT_OF_SUBNODES               FdtGetCountOfSubnodes;
  FDT_GET_NODE_HANDLE                     FdtGetNodeHandle;
  FDT_GET_PARENT_NODE                     FdtGetParentNode;
  FDT_GET_PHANDLE_NODE                    FdtGetPhandleNode;
  FDT_GET_PROP_NAMES_OF_NODE              FdtGetPropNamesOfNode;
  FDT_GET_PROP_NAMES_SIZE_OF_NODE         FdtGetPropNamesSizeOfNode;
  FDT_GET_PROP_VALUES_OF_NODE             FdtGetPropValuesOfNode;
  FDT_GET_PROP_VALUES_SIZE_OF_NODE        FdtGetPropValuesSizeOfNode;
  FDT_GET_SIZE_OF_SUBNODE_NAMES           FdtGetSizeOfSubnodeNames;
  FDT_GET_SUBNODE_NAMES                   FdtGetSubnodeNames;
  FDT_NODE_CMP                            FdtNodeCmp;
  FDT_NODE_COPY                           FdtNodeCopy; 
  FDT_GET_BOOLEAN_PROP                    FdtGetBooleanProp;
  FDT_GET_PROP_SIZE                       FdtGetPropSize;
  FDT_GET_STRING_PROP_LIST                FdtGetStringPropList;
  FDT_GET_UINT32_PROP                     FdtGetUint32Prop;
  FDT_GET_UINT32_PROP_LIST                FdtGetUint32PropList;
  FDT_GET_UINT32_PROP_LIST_SLICE          FdtGetUint32PropListSlice;
  FDT_GET_UINT64_PROP                     FdtGetUint64Prop;
  FDT_GET_UINT64_PROP_LIST                FdtGetUint64PropList;
  FDT_GET_UINT8_PROP                      FdtGetUint8Prop;
  FDT_GET_UINT8_PROP_LIST                 FdtGetUint8PropList;
  FDT_GET_UINT8_PROP_LIST_SLICE           FdtGetUint8PropListSlice;
  FDT_GET_UINT16_PROP                     FdtGetUint16Prop;
  FDT_GET_UINT16_PROP_LIST                FdtGetUint16PropList;
  FDT_GET_UINT16_PROP_LIST_SLICE          FdtGetUint16PropListSlice;
  FDT_GET_CACHE_OF_SUBNODES               FdtGetCacheOfSubnodes;
  FDT_GET_UINT64_PROP_LIST_SLICE          FdtGetUint64PropListSlice;
} EFI_DTB_EXTN_PROTOCOL;

#endif  /* ___EFI_DTB_EXTN_PROTOCOL_H__ */

