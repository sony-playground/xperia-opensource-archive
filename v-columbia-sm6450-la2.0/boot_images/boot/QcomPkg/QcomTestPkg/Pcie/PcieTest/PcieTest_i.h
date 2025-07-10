/** 
 * Internal test interface header
 *  
 * Copyright (c) 2021, 2023 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/20/23   ms      Added enums for supported device IDs and vendor IDs
 04/26/21   yg      Initial version

=============================================================================*/
#ifndef __PCIE_TEST_I_H___
#define __PCIE_TEST_I_H___

#include <Uefi.h>
#include <Library/BaseLib.h>
#include "Library/pcie_dtypes.h"
#include "pcie_host_r.h"

/** PCIe device IDs */
enum pcie_dev_id_t
{	
   PCIE_DEV_ID_CHITWAN                  = 0X307,
   PCIE_DEV_ID_MOSELLE      			    = 0x1105,
   PCIE_DEV_ID_HSP          			    = 0x1103,
   PCIE_NVME_DEV_ID_KIOXIA     			 = 0x0001,
   PCIE_NVME_DEV_ID_PHISON              = 0x5021,
   
};

/** PCIe device IDs */
enum pcie_vendor_id_t
{
   PCIE_VENDOR_ID_QCOM       		      = 0x17CB,
   PCIE_NVME_VENDOR_ID_PHISON 			= 0x1987,	
   PCIE_NVME_VENDOR_ID_KIOXIA    		= 0x1E0F,
};

EFI_STATUS TargetPlatformOptionSelect (UINTN Argc, CHAR8** Argv, UINT32* ArgsConsumedPtr);

EFI_STATUS RunLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr, UINTN LoopBackOption);

void run_all_predefined (void);

void run_all_remote (void);
void run_all_local_digital (void);
void run_all_local_analog (void);

#endif
