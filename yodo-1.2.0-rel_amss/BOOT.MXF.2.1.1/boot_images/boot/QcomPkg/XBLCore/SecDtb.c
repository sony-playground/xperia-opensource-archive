/** @file UefiDtb.c
  SEC DTB glue code.

  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.

  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/07/21   tmt     Add uint16_t, cache & slice APIs
 07/28/21   cm      Changes to print statments
 04/22/21   tmt     Add new DTBExtnLib APIs
 03/24/21   tmt     FdtLib convention is to return errors as negative
 01/21/21   tmt     Created

=============================================================================*/

#include <Uefi.h>
#include <Library/boot_shared_imem_cookie.h>
#include <Library/DebugLib.h>
#include <Library/PrePiLib.h>
#include <Protocol/EFIDtbExtn.h>

#include <DTBWrapper.h>
#include <Library/DTBExtnLib.h>

struct boot_shared_imem_cookie_type *BootSharedImemCookiePtr = NULL;

extern EFI_GUID gEfiDtbExtnIntfHobGuid;

VOID *DTBBlob  = NULL;

INT32 SecFdtInitRootHandleForDriver (
  IN OUT FdtNodeHandle *Node
  )
{
  if (NULL == DTBBlob)
  {
    DEBUG((EFI_D_ERROR, "SecFdtInitRootHandle: DTBBlob NULL!\n"));
    return -FDT_ERR_QC_NULLPTR;
  }

  return fdt_init_root_handle_for_driver(Node, DTBBlob);
}

INT32 SecFdtGetNodeHandle (
  IN OUT FdtNodeHandle *Node,
  IN CHAR8* Name
  )
{
  if (NULL == DTBBlob)
  {
    DEBUG((EFI_D_ERROR, "SecFdtGetNodeHandle: DTBBlob NULL!\n"));
    return -FDT_ERR_QC_NULLPTR;
  }

  return fdt_get_node_handle(Node, DTBBlob, Name);
}

EFI_DTB_EXTN_PROTOCOL DtbExtnIntf =
{
   .Version                           = EFI_DTB_EXTN_PROTOCOL_VERSION,
   .FdtInitRootHandleForDriver        = SecFdtInitRootHandleForDriver,
   .FdtGetNextNodeHandleForCompatible = fdt_get_next_node_handle_for_compatible,
   .FdtGetReg                         = fdt_get_reg,
   .FdtGetNameIndex					  = fdt_get_name_index,
   .FdtGetCountOfSubnodes             = fdt_get_count_of_subnodes,
   .FdtGetNodeHandle                  = SecFdtGetNodeHandle,
   .FdtGetParentNode                  = fdt_get_parent_node,
   .FdtGetPhandleNode                 = fdt_get_phandle_node,
   .FdtGetPropNamesOfNode             = fdt_get_prop_names_of_node,
   .FdtGetPropNamesSizeOfNode         = fdt_get_prop_names_size_of_node,
   .FdtGetPropValuesOfNode            = fdt_get_prop_values_of_node,
   .FdtGetPropValuesSizeOfNode        = fdt_get_prop_values_size_of_node,
   .FdtGetSizeOfSubnodeNames          = fdt_get_size_of_subnode_names,
   .FdtGetSubnodeNames                = fdt_get_subnode_names,
   .FdtNodeCmp						  = fdt_node_cmp,
   .FdtNodeCopy						  = fdt_node_copy,
   .FdtGetBooleanProp                 = fdt_get_boolean_prop,
   .FdtGetPropSize                    = fdt_get_prop_size,
   .FdtGetStringPropList              = fdt_get_string_prop_list,
   .FdtGetUint32Prop                  = fdt_get_uint32_prop,
   .FdtGetUint32PropList              = fdt_get_uint32_prop_list,
   .FdtGetUint32PropListSlice		  = fdt_get_uint32_prop_list_slice,
   .FdtGetUint64Prop                  = fdt_get_uint64_prop,
   .FdtGetUint64PropList              = fdt_get_uint64_prop_list,
   .FdtGetUint8Prop                   = fdt_get_uint8_prop,
   .FdtGetUint8PropList               = fdt_get_uint8_prop_list,
   .FdtGetUint8PropListSlice		  = fdt_get_uint8_prop_list_slice,
   .FdtGetUint16Prop                  = fdt_get_uint16_prop,
   .FdtGetUint16PropList              = fdt_get_uint16_prop_list,
   .FdtGetUint16PropListSlice		  = fdt_get_uint16_prop_list_slice,
   .FdtGetUint64PropListSlice		  = fdt_get_uint64_prop_list_slice,
   .FdtGetCacheOfSubnodes             = fdt_get_cache_of_subnodes,
};

EFI_STATUS
DtbInit (VOID)
{
  UINT32          DTBConfig[3];
  fdt_node_handle Node;
  EFI_STATUS      Status = EFI_DEVICE_ERROR;
  INTN            Ret    = -1;

  BootSharedImemCookiePtr = (struct boot_shared_imem_cookie_type *)((UINT64)PcdGet32(PcdIMemCookiesBase));
  ASSERT(BootSharedImemCookiePtr != NULL);

  DTBBlob = (VOID *)BootSharedImemCookiePtr->boot_devtree_addr;
  Ret = fdt_set_blob_handle(DTBBlob, DEFAULT_BLOB_ID);
  if (Ret)
  {
    DEBUG((EFI_D_ERROR, "fdt_set_blob_handle: %d\n", Ret));
    goto Exit;
  }

  Ret = fdt_get_node_handle(&Node, DTBBlob, "/sw/boot");
  if (Ret)
  {
    DEBUG((EFI_D_ERROR, "fdt_get_node_handle: %d\n", Ret));
    goto Exit;
  }

  Ret = fdt_get_uint32_prop_list(&Node, "config", (VOID *)&DTBConfig, sizeof(DTBConfig));
  if (Ret)
  {
    DEBUG((EFI_D_ERROR, "fdt_get_uint32_prop_list: %d\n", Ret));
    goto Exit;
  }

  //DTBconfig - /sw/boot/config
  DEBUG((EFI_D_WARN, "DTB config    : client[%x]..trace[%x]..verbose[%x]\n",
          DTBConfig[0], DTBConfig[1], DTBConfig[2]));
  //DEBUG((EFI_D_WARN, "DtbInit has published DEFAULT_BLOB_ID @[%p]\n", DTBBlob));

  Status = EFI_SUCCESS;

Exit:
  return Status;
}

VOID
DtbExtnIntfInit (VOID)
{
  UINTN Data = (UINTN)&DtbExtnIntf;

  /* Asserts on failure */
  BuildGuidDataHob (&gEfiDtbExtnIntfHobGuid, &Data, sizeof(Data));
}
