/** @file boot_config.c

  BootConfigLibNull is used to get boot configuration information

  Copyright (c) 2015-2020, 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     -----------------------------------------------------------
2022-08-08   cm      Added boot_from_network
2020-08-21   cm      Added boot_from_nand
2020-06-12   cm      Added boot_from_flashless
2020-03-05   am      Update for sd card 
2018-02-16   bd      Add API to read from boot config register
2017-12-01   jt      Update for NVMe  
2015-09-01   vk      Stub out for core
2015-06-03   plc     Added boot_from_spi_nor stub
2015-05-08   plc     Initial version

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
BOOLEAN boot_from_ufs (void)
{
  return TRUE;
}  

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
BOOLEAN boot_from_emmc (VOID)
{
  return FALSE;
}

/******************************************************************************
* FUNCTION      boot_from_sdcc
*
* DESCRIPTION   This function returns if device boots from sd card
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from sd card
*
******************************************************************************/
BOOLEAN boot_from_sdcc (VOID)
{
  return FALSE;
}

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
BOOLEAN boot_from_spi_nor (VOID)
{
   return FALSE;
}

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
BOOLEAN boot_from_nvme (VOID)
{
   return FALSE;
}

/******************************************************************************
* FUNCTION      boot_from_flashless
*
* DESCRIPTION   This function returns if device boots from flashless
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from flashless
*
******************************************************************************/
BOOLEAN boot_from_flashless (VOID)
{
   return FALSE;
}

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
BOOLEAN boot_from_nand (VOID)
{
   return FALSE;
}

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
BOOLEAN boot_from_emmc_network (void)
{
  return FALSE;
}

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
BOOLEAN boot_from_nand_network (void)
{
  return FALSE;
}

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
BOOLEAN boot_from_network (VOID)
{
   return (boot_from_emmc_network() || boot_from_nand_network());
}


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
EFI_STATUS GetSharedImemBootOption (FlashDeviceType *BootDeviceOption)
{
  if (BootDeviceOption == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  //use EFI_PCIE_FLASH_TYPE if using for flashless
  *BootDeviceOption = EFI_UFS_FLASH_TYPE;
  return EFI_SUCCESS;
}
