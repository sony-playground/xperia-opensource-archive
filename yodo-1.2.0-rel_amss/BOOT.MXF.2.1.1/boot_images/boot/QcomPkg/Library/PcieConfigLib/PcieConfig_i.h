#ifndef __PCIE_CONFIG_INTERNAL_H___
#define __PCIE_CONFIG_INTERNAL_H___
/*
 *
 *  PCIe internal public interface
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Moved old lib implementation to new design/interface

*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                 All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include <Uefi.h>

/* Bus address space */
#define PCIE_SINGLE_BUS_ADDR_SPACE_SIZE                  (0x100000)
#define PCIE_CONFIG_SPACE_LENGTH                         (0x1000)

EFI_STATUS PcieConfigLibSetupBattChargingHandler (VOID);

EFI_STATUS PcieConfigLibSetACPIPlatCallback (UINT32 HwPortIndex);

BOOLEAN IsDeviceInOffModeCharging (VOID);

#endif    /* __PCIE_CONFIG_INTERNAL_H___ */

