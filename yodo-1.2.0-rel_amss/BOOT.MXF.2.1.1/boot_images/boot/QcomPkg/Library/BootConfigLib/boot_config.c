/** @file boot_config.c

  Get boot configuration information from Shared IMEM

  Copyright (c) 2018, 2020, 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
 08/08/22    cm      Added boot_from_network
 08/04/20    cm      Added boot_from_flashless and nand support
 06/13/20    cm      Added boot_from_flashless function as a stub
 04/02/18    kpa     Get boot device option from xbl loader via shared imem
 02/16/18    bd      Initial version

=============================================================================*/

#include <Uefi.h>
#include "BootConfig.h"

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
  FlashDeviceType Val = EFI_MAX_FLASH_TYPE;
  
  if (GetSharedImemBootOption(&Val) != EFI_SUCCESS)
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to Get Shared Imem Boot Device type \n"));

  if (Val == EFI_UFS_FLASH_TYPE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
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
  FlashDeviceType Val = EFI_MAX_FLASH_TYPE;

  if (GetSharedImemBootOption(&Val) != EFI_SUCCESS)
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to Get Shared Imem Boot Device type \n"));

  if (Val == EFI_SDC_FLASH_TYPE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
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
  FlashDeviceType Val = EFI_MAX_FLASH_TYPE;
  
  if (GetSharedImemBootOption(&Val) != EFI_SUCCESS)
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to Get Shared Imem Boot Device type \n"));

  if ((Val == EFI_SPI_FLASH_TYPE)||(Val == EFI_NOR_FLASH_TYPE))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
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
   return boot_from_spi_nor(); 
}

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
BOOLEAN boot_from_flashless (VOID)
{
  EFI_STATUS Status;
  FlashDeviceType BootDeviceOption;
  Status = GetSharedImemBootOption (&BootDeviceOption);

  if ((BootDeviceOption == EFI_PCIE_FLASH_TYPE) ||
      (BootDeviceOption == EFI_USB_FLASH_TYPE))
    return TRUE;
  else
    return FALSE;
}


/******************************************************************************
* FUNCTION      boot_from_nand
*
* DESCRIPTION   This function returns if device boots from NAND
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from NAND
*
 *****************************************************************************/
BOOLEAN boot_from_nand (void)
{
  EFI_STATUS Status;
  FlashDeviceType BootDeviceOption;
  Status = GetSharedImemBootOption (&BootDeviceOption);

  if (BootDeviceOption == EFI_NAND_FLASH_TYPE)
    return TRUE;
  else
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
* DESCRIPTION   This function returns if device boots from Network
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from Network
*
 *****************************************************************************/
BOOLEAN boot_from_network (void)
{
  return (boot_from_emmc_network() || boot_from_nand_network());
}

