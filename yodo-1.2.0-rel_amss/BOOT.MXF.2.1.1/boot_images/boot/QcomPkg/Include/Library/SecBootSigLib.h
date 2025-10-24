/** @file
   
 Declaration of SecBootSigLib Library Interfaces.

 Copyright (c) 2011, 2020, 2022 Qualcomm Technologies, Inc. All rights reserved.
   
**/


/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---    -----------------------------------------------------------
 05/14/20    shl     Added measure boot test event.
 05/14/12    shl     Added OEM FW update event.
 12/16/11    shl     Added MorPpi feature 
 11/28/11    shl     Separate BdsPlatform from library lingking.
 09/18/11    shl     Initial version.

=============================================================================*/

#ifndef __SEC_BOOT_SIG_LIB_H__
#define __SEC_BOOT_SIG_LIB_H__
  
extern EFI_GUID gQcomSecBootRegEventGuid;
extern EFI_GUID gQcomMeasureBootRegEventGuid;
extern EFI_GUID gQcomMeasureBootStartEventGuid;
extern EFI_GUID gQcomMeasureBootTestEventGuid;
extern EFI_GUID gQcomMeasureReturnFromEfiAppFromBootOptionEventGuid;
extern EFI_GUID gQcomMorPpiEventGuid;
extern EFI_GUID gQcomOemFwUpdateEventGuid;

EFI_STATUS EFIAPI SetSecBootRegSignal(VOID);
EFI_STATUS EFIAPI SetMeasureBootRegSignal(VOID);
EFI_STATUS EFIAPI SetMeasureBootStartSignal(VOID);
EFI_STATUS EFIAPI SetMeasureBootTestSignal(VOID);
EFI_STATUS EFIAPI SetMeasureReturnFromEfiAppFromBootOptionSignal(VOID);
EFI_STATUS EFIAPI SetMorPpiSignal(VOID);
EFI_STATUS EFIAPI SetOemFwUpdateSignal(VOID);

#endif
