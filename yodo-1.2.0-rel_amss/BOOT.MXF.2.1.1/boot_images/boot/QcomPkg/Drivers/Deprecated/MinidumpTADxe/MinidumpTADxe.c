/** @file MinidumpTADxe.c
   
  Implementation for Minidump TA Loading.

#  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
**/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/smem.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIDebug.h>
#include <Protocol/EFIScm.h>
#include <Library/MinidumpTALib.h>

#define MDTA_SMEM_ID 0x274 //628


EFI_STATUS
EFIAPI
MinidumpTADxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 * md_ta_addr = NULL;
  UINT32 md_ta_size = 0;
  UINT32 md_ta_cfg = 0;
  
  md_ta_addr = (UINT32 *)smem_get_addr(MDTA_SMEM_ID, (uint32*)&md_ta_size);

  if(md_ta_addr)
  {
    md_ta_cfg = *md_ta_addr;
  }
  
  //DEBUG((EFI_D_ERROR, "MinidumpTADxe: Minidump TA CFG is %d \n", md_ta_cfg));

  /* Check if Minidump TA loading enabled */
  if ( md_ta_cfg == 0)
  {
    DEBUG((EFI_D_ERROR, "MinidumpTADxe: Minidump TA loading not enabled.\n"));
    return EFI_LOAD_ERROR;
  }
  
    /* Load and initialize the MinidumpTALoad */
    Status = MinidumpTALoad();
    if (EFI_ERROR(Status))
    {
       DEBUG((EFI_D_ERROR, "MinidumpTADxe: Minidump TA loading failed.\n"));
       return Status;
    }
  return Status;
}
