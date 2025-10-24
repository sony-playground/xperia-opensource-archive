/*===========================================================================

GENERAL DESCRIPTION
  This module contains the common BootMemMapLib functions.

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

 ==============================================================================*/
/*=============================================================================
                          EDIT HISTORY

when       who     what, where, why
--------   ---     -----------------------------------------------------------
02/08/22   ck      Initial revision

=============================================================================*/

#include <boot_error_if.h>
#include <boot_config_context.h>
#include <boot_edk2_mmu_if.h>


bl_error_boot_type xbl_uncached_memmap_init(boot_handle config_context,
                                            uintnt base,
                                            uintnt size)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_edk2_mmu_if_type * edk2_mmu_if = NULL;


  ARM_MEMORY_REGION_DESCRIPTOR current_entry[] =
  {
    { base, base, size, EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN},
    {    0,    0,    0, 0}  /* Last Region Marker */
  };


  /* Obtain EDK2 MMU interface */
  status = boot_config_context_get_ptr(config_context,
                                       CONFIG_CONTEXT_EDK2_MMU_INTERFACE,
                                       (void **)&edk2_mmu_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (edk2_mmu_if == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
    goto exit;
  }


  /* Set memory region as uncached */
  if (edk2_mmu_if->ArmSetMemoryAttributes(current_entry->PhysicalBase,
                                          current_entry->Length,
                                          current_entry->Attributes) != EFI_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_MMU_PGTBL_MAPPING_FAIL);
    goto exit;
  }


 exit:
  return status;
}
