/** 
 * Internal test interface header
 *  
 * Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/26/21   yg      Initial version

=============================================================================*/
#ifndef __PCIE_TEST_I_H___
#define __PCIE_TEST_I_H___

#include <Uefi.h>
#include <Library/BaseLib.h>
#include "Library/pcie_dtypes.h"
#include "pcie_host_r.h"

EFI_STATUS TargetPlatformOptionSelect (UINTN Argc, CHAR8** Argv, UINT32* ArgsConsumedPtr);

EFI_STATUS RunLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr, UINTN LoopBackOption);

void run_all_predefined (void);

void run_all_remote (void);
void run_all_local_digital (void);
void run_all_local_analog (void);

#endif
