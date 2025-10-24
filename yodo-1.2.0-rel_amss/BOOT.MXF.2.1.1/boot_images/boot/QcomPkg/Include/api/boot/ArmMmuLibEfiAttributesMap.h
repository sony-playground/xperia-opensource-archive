/*===========================================================================

  GENERAL DESCRIPTION
  This module contains defines for memory attributes that map to uefi spe
  for the ArmSetMemoryAttributes API.

  Copyright (c) 2020,2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

 ==============================================================================*/
 
/*===========================================================================
                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        -------------------------------------------------------
07/07/22   rama       Set XP bit for DEVICE attribute type
05/10/20   ds         initial revision
===========================================================================*/

#ifndef ARMMMULIBEFIATTRIBUTESMAP_H
#define ARMMMULIBEFIATTRIBUTESMAP_H


#include <Uefi.h>

/* Below defines are used for ArmSetMemoryAttributes API since it takes attributes from uefi spec*/

#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_DEVICE (EFI_MEMORY_UC | EFI_MEMORY_XP)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_RO (EFI_MEMORY_UC | EFI_MEMORY_RO)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_XN_RO (EFI_MEMORY_UC | EFI_MEMORY_XP | EFI_MEMORY_RO)

#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED (EFI_MEMORY_WC)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN (EFI_MEMORY_WC | EFI_MEMORY_XP)

#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK (EFI_MEMORY_WB)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_RO (EFI_MEMORY_WB | EFI_MEMORY_RO)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN_RO (EFI_MEMORY_WB | EFI_MEMORY_XP | EFI_MEMORY_RO)
#define EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN (EFI_MEMORY_WB | EFI_MEMORY_XP)

#endif