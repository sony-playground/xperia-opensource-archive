/** @file PASRLib.h
  
  PASRLib interface

  Copyright (c) 2022 by Qualcomm Technologies, Inc. 
  All Rights Reserved.
 
**/

/*=======================================================================
                        Edit History

when      who      what, where, why
--------  ----     ---------------------------------------------------
04/25/22  ddk      Initital Version
========================================================================*/

#include <Uefi.h>
#include <MemRegionInfo.h>
#include <DDRDetails.h>
#include <Protocol/EFIPasr.h>

#define MAX_NUM_PASR_SEGMENTS 16
typedef struct _PASR_SEGMENT
{
   UINTN seg_start_addr;
   UINTN seg_size;
}PASR_SEGMENT;

/*==============================================================================

  FUNCTION      PasrConfig

  DESCRIPTION   See EFI_PASR_SETSTARTADDR in Protocol/EFIPasr.h

==============================================================================*/

EFI_STATUS
PasrConfig (IN UINT32 NumBlocks, IN PASR_BLOCK *PasrBlock);

/*==============================================================================

  FUNCTION      PASRActivate

  DESCRIPTION   See EFI_PASR_ACTIVATE in Protocol/EFIPasr.h

==============================================================================*/

EFI_STATUS PASRActivate (void) ;