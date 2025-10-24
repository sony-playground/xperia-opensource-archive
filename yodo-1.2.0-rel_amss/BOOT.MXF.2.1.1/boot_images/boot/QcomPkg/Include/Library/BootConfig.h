#ifndef BOOTCONFIG_H
#define BOOTCONFIG_H

/** @file BootConfig.h
   
  This file is header file for BootConfigLib

  Copyright (c) 2015-2018, 2020, 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
    
**/

/*=============================================================================
                              EDIT HISTORY


when         who    what, where, why
----------   ---    --------------------------------------------------------------
2022-08-08   cm     Added boot_from_network
2020-04-08   cm     Added boot_from_nand
2020-06-12   cm     Added boot_from_flashless
2018-04-03   kpa    Added GetSharedImemBootOption
2018-02-16   bd     Add API to read from boot config register
2017-12-01   jt     Add NVMe support 
2015-04-30   as     Add SPI NOR functionality.
2015-03-31   rm     Initial version

=============================================================================*/

#include <Uefi.h>
#include <Protocol/EFIBootConfig.h>

/******************************************************************************
* FUNCTION      boot_from_ufs
*
* DESCRIPTION   This function returns if device boots from UFS
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from UFS
*
******************************************************************************/
BOOLEAN boot_from_ufs (void);
/******************************************************************************
* FUNCTION      boot_from_emmc
*
* DESCRIPTION   This function returns if device boots from eMMC
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from eMMC
*
******************************************************************************/
BOOLEAN boot_from_emmc (void);

/******************************************************************************
* FUNCTION      boot_from_sdcc
*
* DESCRIPTION   This function returns if device boots from sdcc
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from sdcc
*
******************************************************************************/
BOOLEAN boot_from_sdcc (void);

/******************************************************************************
* FUNCTION      boot_from_spi_nor
*
* DESCRIPTION   This function returns if device boots from SPI NOR
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from SPI NOR
*
******************************************************************************/
BOOLEAN boot_from_spi_nor (void);

/******************************************************************************
* FUNCTION      boot_from_nvme
*
* DESCRIPTION   This function returns if device boots from NVMe
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from NVMe
*
******************************************************************************/
BOOLEAN boot_from_nvme (void);

/******************************************************************************
* FUNCTION      boot_from_flashless
*
* DESCRIPTION   This function returns if device boots from flashless
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from Flashless
*
******************************************************************************/
BOOLEAN boot_from_flashless (void);

/******************************************************************************
 * FUNCTION      boot_from_nand
 *
 * DESCRIPTION   This function returns if device boots from nand
 *
 * PARAMETERS    NONE
 *
 * RETURN VALUE  TRUE if device boots from nand
 *
  ******************************************************************************/
BOOLEAN boot_from_nand (void);

/******************************************************************************
* FUNCTION      boot_from_emmc_network
*
* DESCRIPTION   This function returns if device boots from Network
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from Network
*
 *****************************************************************************/
BOOLEAN boot_from_emmc_network (void);

/******************************************************************************
* FUNCTION      boot_from_nand_network
*
* DESCRIPTION   This function returns if device boots from Network
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from Network
*
 *****************************************************************************/
BOOLEAN boot_from_nand_network (void);

/******************************************************************************
 * FUNCTION      boot_from_network
 *
 * DESCRIPTION   This function returns if device boots from network
 *
 * PARAMETERS    NONE
 *
 * RETURN VALUE  TRUE if device boots from network
 *
  ******************************************************************************/
BOOLEAN boot_from_network (void);


/******************************************************************************
* FUNCTION      GetSharedImemBootOption
*
* DESCRIPTION   This function returns boot option passed on by xbl Loader 
*               via shared imem
*
* PARAMETERS    BootDeviceOption  Boot Device option shared by XBL loader
*                                 mapped to UEFI equivalent type
*
* RETURN VALUE  EFI_SUCCESS if success
*
******************************************************************************/
EFI_STATUS GetSharedImemBootOption (FlashDeviceType *BootDeviceOption);


#endif /* #ifndef BOOTCONFIG_H */

