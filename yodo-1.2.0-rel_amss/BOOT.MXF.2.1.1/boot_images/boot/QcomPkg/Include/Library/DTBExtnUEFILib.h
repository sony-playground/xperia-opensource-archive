/** @file
 * Shared lib for DTB Extension lib in UEFI
 *  
 * Copyright (c) 2021 Qualcomm Technologies Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/12/21   tmt     Add new APIs: cache, uint16 & slice
 06/25/21   tmt     Update Performance info on certain APIs
 04/22/21   tmt     Wrap all APIs
 03/18/21   tmt     Initial version

=============================================================================*/

#include <Protocol/EFIDtbExtn.h>

#ifndef __DTB_EXTN_UEFI_LIB_H__
#define __DTB_EXTN_UEFI_LIB_H__

/*
 *  NOTE: Refer to the protocol header EFIDtbExtn.h for additional
 *   documentation of the API's and data types/macros etc
 *
 *  PERFORMANCE NOTE:
 *    When retrieving property values from a node that easily maps to a C struct
 *    the best performing API is: FdtGetPropValuesOfNode().  The first consecutive
 *    N properties of a node can be retrieved by this API.  If you retrieve fewer
 *    properties than are present in the node, this call will return with
 *    -FDT_ERR_QC_TRUNCATED.  This is really a warning that the provided buffer is
 *    not large enough to hold all of the property values.
 *
 * WARNING:
 *    The FdtGetPropValuesOfNode() is a potentially dangerous API to use because
 *    the C struct has to be in perfect synchronicity with the DTB node layout.
 *    If there is a deviation you can expect a bug!!
 *
 */

/* DTBExtnLib_blob.c Entry Points */
/**********************************/
INT32 FdtGetBlobHandle(VOID **Blob, INT32 BlobId);
INT32 FdtGetBlobSize(FdtNodeHandle *Node, UINT32 *Size);
INT32 FdtInitRootHandleForDriver(FdtNodeHandle *Node);
INT32 FdtInitRootHandleForDriverById(FdtNodeHandle *Node, INT32 BlobId);
INT32 FdtSetBlobHandle(VOID *blob, INT32 BlobId);

/* DTBExtnLib_driver.c Entry Points */
/************************************/
INT32 FdtGetNameIndex(FdtNodeHandle *Node, CHAR8 *PName, CHAR8 *TName, INT32 *Index);
INT32 FdtGetNextNodeHandleForCompatible(FdtNodeHandle *Node, const CHAR8 *Compatible);
INT32 FdtGetReg(FdtNodeHandle *Node, CHAR8 *RegName, INT32 RegIndex, INT32 AddrCode,
				INT32 SizeCode, UINT64 *RegPaddr, UINT64 *RegSize);

/* DTBExtnLib_node.c Entry Points */
/**********************************/
INT32 FdtGetCacheOfSubnodes(FdtNodeHandle *Node, FdtNodeHandle *Cache, UINT32 Count);
INT32 FdtGetCountOfSubnodes(FdtNodeHandle *Node, UINT32 *Count);
INT32 FdtGetNodeHandle(FdtNodeHandle *Node, CHAR8 *Name);
INT32 FdtGetParentNode(FdtNodeHandle *Node, FdtNodeHandle *Pnode);
INT32 FdtGetPhandleNode(FdtNodeHandle *Node, INT32 Phandle, FdtNodeHandle *Pnode);
INT32 FdtGetPropNamesOfNode(FdtNodeHandle *Node, CHAR8 *PropNames, UINT32 Size);
INT32 FdtGetPropNamesSizeOfNode(FdtNodeHandle *Node, UINT32 *Size);
INT32 FdtGetPropValuesOfNode(FdtNodeHandle *Node, CHAR8 *Format, VOID *PackedPropValues, UINT32 Size);
INT32 FdtGetPropValuesSizeOfNode(FdtNodeHandle *Node, UINT32 *Size);
INT32 FdtGetSizeOfSubnodeNames(FdtNodeHandle *Node, UINT32 *Names, UINT32 Count);
INT32 FdtGetSubnodeNames(FdtNodeHandle *Node, VOID *Names, UINT32 Size);
INT32 FdtNodeCmp(FdtNodeHandle *NodeA, FdtNodeHandle *NodeB);
INT32 FdtNodeCopy(FdtNodeHandle *Dst, FdtNodeHandle *Src);

/* DTBExtnLib_prop.c Entry Points */
/**********************************/
INT32 FdtGetBooleanProp(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Value);
INT32 FdtGetPropSize(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Size);
INT32 FdtGetStringPropList(FdtNodeHandle *Node, const CHAR8 *PropName, CHAR8 *StringList, UINT32 Size);
INT32 FdtGetUint32Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Value);
INT32 FdtGetUint32PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *PropList, UINT32 Size);
INT32 FdtGetUint32PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *PropList, UINT32 Index, UINT32 Count);
INT32 FdtGetUint64Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *Value);
INT32 FdtGetUint64PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *PropList, UINT32 Size);
INT32 FdtGetUint64PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *PropList, UINT32 Index, UINT32 Count);
INT32 FdtGetUint8Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *Value);
INT32 FdtGetUint8PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *PropList, UINT32 Size);
INT32 FdtGetUint8PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *PropList, UINT32 Index, UINT32 Count);
INT32 FdtGetUint16Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *Value);
INT32 FdtGetUint16PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *PropList, UINT32 Size);
INT32 FdtGetUint16PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *PropList, UINT32 Index, UINT32 Count);

#endif  /* __DTB_EXTN_UEFI_LIB_H__*/
