/** @file
 * Lib interface for EFI_DTB_EXTN_PROTOCOL protocol interface in UEFI
 *  
 * Copyright (c) 2021 Qualcomm Technologies Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/07/21   tmt     Add new uint16, slice & cache APIs
 07/28/21   cm      Commenting DTBLibInit print statement
 04/22/21   tmt     Add missing APIs
 03/15/21   tmt     Initial version (copied from KernelLib.c)

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Protocol/EFIDtbExtn.h>

static EFI_DTB_EXTN_PROTOCOL  *DtbIntf = NULL;

/********************************************************************************
      Setup function
********************************************************************************/
EFI_STATUS
EFIAPI
DtbLibInit (VOID)
{
  EFI_STATUS Status = EFI_NOT_FOUND;
  
  if (DtbIntf == NULL)
  {
	Status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL, (VOID **)&DtbIntf);

	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Locate DTBExtnProtocol failed: %r \n", Status));
		DtbIntf = NULL;
	}
  }

  /* Return success regardless. We can't have constructor function fail */
  //DEBUG((EFI_D_WARN, "DtbLibInit is Initialized\n"));
  return EFI_SUCCESS;
}

/* DTBExtnLib_blob.c Entry Points */
/**********************************/
INT32 FdtGetBlobHandle(VOID **Blob, INT32 BlobId)
{
	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetBlobSize(FdtNodeHandle *Node, UINT32 *Size)
{
	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtInitRootHandleForDriver(FdtNodeHandle *Node)
{
	if (DtbIntf)
		return DtbIntf->FdtInitRootHandleForDriver(Node);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtInitRootHandleForDriverById(FdtNodeHandle *Node, INT32 BlobId)
{
	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtSetBlobHandle(VOID *blob, INT32 BlobId)
{
	return -FDT_ERR_QC_NOTREADY;
}

/* DTBExtnLib_driver.c Entry Points */
/************************************/
INT32 FdtGetNameIndex(FdtNodeHandle *Node, CHAR8 *PName, CHAR8 *TName, INT32 *Index)
{
	if (DtbIntf)
		return DtbIntf->FdtGetNameIndex(Node, PName, TName, Index);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetNextNodeHandleForCompatible(FdtNodeHandle *Node, const CHAR8 *Compatible)
{
	if (DtbIntf)
		return DtbIntf->FdtGetNextNodeHandleForCompatible(Node, Compatible);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetReg(FdtNodeHandle *Node, CHAR8 *RegName, INT32 RegIndex, INT32 AddrCode,
				INT32 SizeCode, UINT64 *RegPaddr, UINT64 *RegSize)
{
	if (DtbIntf)
		return DtbIntf->FdtGetReg(Node, RegName, RegIndex, AddrCode, SizeCode, RegPaddr, RegSize);

	return -FDT_ERR_QC_NOTREADY;
}

/* DTBExtnLib_node.c Entry Points */
/**********************************/
INT32 FdtGetCacheOfSubnodes(FdtNodeHandle *Node, FdtNodeHandle *Cache, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetCacheOfSubnodes(Node, Cache, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetCountOfSubnodes(FdtNodeHandle *Node, UINT32 *Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetCountOfSubnodes(Node, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetNodeHandle(FdtNodeHandle *Node, CHAR8 *Name)
{
	if (DtbIntf)
		return DtbIntf->FdtGetNodeHandle(Node, Name);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetParentNode(FdtNodeHandle *Node, FdtNodeHandle *Pnode)
{
	if (DtbIntf)
		return DtbIntf->FdtGetParentNode(Node, Pnode);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPhandleNode(FdtNodeHandle *Node, INT32 Phandle, FdtNodeHandle *Pnode)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPhandleNode(Node, Phandle, Pnode);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPropNamesOfNode(FdtNodeHandle *Node, CHAR8 *PropNames, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPropNamesOfNode(Node, PropNames, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPropNamesSizeOfNode(FdtNodeHandle *Node, UINT32 *Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPropNamesSizeOfNode(Node, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPropValuesOfNode(FdtNodeHandle *Node, CHAR8 *Format, VOID *PackedPropValues, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPropValuesOfNode(Node, Format, PackedPropValues, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPropValuesSizeOfNode(FdtNodeHandle *Node, UINT32 *Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPropValuesSizeOfNode(Node, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetSizeOfSubnodeNames(FdtNodeHandle *Node, UINT32 *Names, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetSizeOfSubnodeNames(Node, Names, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetSubnodeNames(FdtNodeHandle *Node, VOID *Names, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetSubnodeNames(Node, Names, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtNodeCmp(FdtNodeHandle *NodeA, FdtNodeHandle *NodeB)
{
	if (DtbIntf)
		return DtbIntf->FdtNodeCmp(NodeA, NodeB);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtNodeCopy(FdtNodeHandle *Dst, FdtNodeHandle *Src)
{
	if (DtbIntf)
		return DtbIntf->FdtNodeCopy(Dst, Src);

	return -FDT_ERR_QC_NOTREADY;
}

/* DTBExtnLib_prop.c Entry Points */
/**********************************/
INT32 FdtGetBooleanProp(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Value)
{
	if (DtbIntf)
		return DtbIntf->FdtGetBooleanProp(Node, PropName, Value);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetPropSize(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetPropSize(Node, PropName, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetStringPropList(FdtNodeHandle *Node, const CHAR8 *PropName, CHAR8 *StringList, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetStringPropList(Node, PropName, StringList, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint32Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *Value)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint32Prop(Node, PropName, Value);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint32PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *PropList, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint32PropList(Node, PropName, PropList, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint32PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT32 *PropList, UINT32 Index, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint32PropListSlice(Node, PropName, PropList, Index, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint64Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *Value)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint64Prop(Node, PropName, Value);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint64PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *PropList, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint64PropList(Node, PropName, PropList, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint64PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT64 *PropList, UINT32 Index, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint64PropListSlice(Node, PropName, PropList, Index, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint8Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *Value)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint8Prop(Node, PropName, Value);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint8PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *PropList, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint8PropList(Node, PropName, PropList, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint8PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT8 *PropList, UINT32 Index, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint8PropListSlice(Node, PropName, PropList, Index, Count);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint16Prop(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *Value)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint16Prop(Node, PropName, Value);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint16PropList(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *PropList, UINT32 Size)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint16PropList(Node, PropName, PropList, Size);

	return -FDT_ERR_QC_NOTREADY;
}

INT32 FdtGetUint16PropListSlice(FdtNodeHandle *Node, const CHAR8 *PropName, UINT16 *PropList, UINT32 Index, UINT32 Count)
{
	if (DtbIntf)
		return DtbIntf->FdtGetUint16PropListSlice(Node, PropName, PropList, Index, Count);

	return -FDT_ERR_QC_NOTREADY;
}

