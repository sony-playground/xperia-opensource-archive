/**
 * @file smp2p_dxe.c
 *
 * DXE driver for Smp2p device in UEFI
 */

/*==============================================================================
     Copyright (c) 2020 Qualcomm Technologies, Inc. 
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/02/15   ar      Created UEFI support code for Smp2p
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFISmp2p.h>
#include "com_dtypes.h"
#include <Library/smp2p.h>


extern void smp2p_init(void);


/*===========================================================================
                        INTERNAL FUNCTION DEFINITIONS
===========================================================================*/
static EFI_STATUS EFI_smp2p_create
(
  smp2p_context_type ** ctx,
  smem_host_type        dest,
  char *                name,
  uint32				*ret
)
{
  *ret = smp2p_create(ctx,dest,name);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_write
(
  smp2p_context_type * ctx,
  uint32               data,
  uint32				*ret
)
{
  *ret = smp2p_write(ctx,data);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_modify
(
  smp2p_context_type * ctx,
  uint32               clr_mask,
  uint32               set_mask,
  uint32				*ret
)
{
  *ret = smp2p_modify(ctx,clr_mask,set_mask);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_modify_ex
(
  smp2p_context_type * ctx,
  uint32               clr_mask,
  uint32               set_mask,
  uint32               flags,
  uint32				*ret
)
{
  *ret = smp2p_modify_ex(ctx,clr_mask,set_mask,flags);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_register
(
  smp2p_context_type ** ctx,
  smem_host_type        source,
  char *                name,
  uint32				*ret
)
{
  *ret = smp2p_register(ctx,source,name);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_deregister
(
  smp2p_context_type *ctx,
  uint32			 *ret
)
{
  *ret = smp2p_deregister(ctx);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_read
(
  smp2p_context_type * ctx,
  uint32 *             data,
  uint32				*ret
)
{
  *ret = smp2p_read(ctx,data);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_wait
(
  smp2p_context_type * ctx,
  uint32				*ret
)
{
  *ret = smp2p_wait(ctx);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_wait_multiple
(
  smp2p_context_type ** ctx_arr,
  uint32                ctx_count,
  uint32              * trigger_idx,
  uint32				*ret
)
{
  *ret = smp2p_wait_multiple(ctx_arr,ctx_count,trigger_idx);
  
  if(*ret == SMP2P_STATUS_SUCCESS) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_smp2p_get_evt
(
  smp2p_context_type*   ctx,
  Event**               Evt
)
{
  *Evt = smp2p_get_evt(ctx);
  return (*Evt==NULL)?EFI_COMPROMISED_DATA:EFI_SUCCESS;
}

/*===========================================================================
                           INTERNAL DATA STRUCTURES
===========================================================================*/

static EFI_SMP2P_PROTOCOL SMP2PProtocol =
{
  EFI_SMP2P_PROTOCOL_REVISION,
  EFI_smp2p_create,
  EFI_smp2p_write,
  EFI_smp2p_modify,
  EFI_smp2p_modify_ex,
  EFI_smp2p_register,
  EFI_smp2p_deregister,
  EFI_smp2p_read,
  EFI_smp2p_wait,
  EFI_smp2p_wait_multiple,
  EFI_smp2p_get_evt
};

/*===========================================================================
                        EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/
/**
 * Entry point for the Smp2p DXE driver.
 */
EFI_STATUS EFIAPI Smp2pEntryPoint
(
  EFI_HANDLE            ImageHandle,
  EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_HANDLE handle = NULL;
  EFI_STATUS status;
  
  /* Init Smp2p  */
  smp2p_init();


  status = gBS->InstallMultipleProtocolInterfaces(&handle,
      &gEfiSMP2PProtocolGuid, (void **)&SMP2PProtocol, NULL, NULL, NULL );

  return status;
}
