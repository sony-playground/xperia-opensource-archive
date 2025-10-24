/*! @file PmicQg.h
 *
 *  PMIC-QG MODULE RELATED DECLARATION
 *  This file contains functions and variable declarations to support
 *  the PMIC FG module.
 *
 *  Copyright (c) 2018-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who    what, where, why
--------   ---    ----------------------------------------------------------
07/26/18   pbitra  New File.
===========================================================================*/

#ifndef __PMICQG_H__
#define __PMICQG_H__

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
/**
  EFI interfaces
 */

#include <Protocol/EFIPmicQg.h>

/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

EFI_STATUS EFIAPI EFI_PmicQgInit(IN UINT32 PmicDeviceIndex, IN EFI_PM_QG_CFGDATA_TYPE *pQgCfgData);

EFI_STATUS EFIAPI EFI_PmicQgGetBatteryStatus(IN UINT32 PmicDeviceIndex, OUT EFI_PM_QG_BATT_STATUS_INFO *BattStsInfo);

EFI_STATUS EFIAPI EFI_PmicQgExit(IN UINT32 PmicDeviceIndex);

EFI_STATUS EFIAPI EFI_PmicQgGetPmicInfo(OUT EFI_PM_QG_PMIC_INFO *QgPmicIndex);

EFI_STATUS EFIAPI EFI_PmicQgDumpPeripheral( VOID );



/*===========================================================================
                  LOCAL FUNCTION DECLARATIONS
===========================================================================*/

EFI_STATUS PmicQg_Init(UINT32 PmicDeviceIndex, IN EFI_PM_QG_CFGDATA_TYPE QgCfgData);

EFI_STATUS PmicQg_GetBatteryStatus(UINT32 PmicDeviceIndex, EFI_PM_QG_BATT_STATUS_INFO *BattStsInfo);

VOID       PmicQgPostExit(VOID);

#endif  /* __PMICQG_H__ */


