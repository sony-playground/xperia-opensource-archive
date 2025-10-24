#ifndef BOOT_MEDIA_TYPE_H
#define BOOT_MEDIA_TYPE_H

/*===========================================================================

                                Boot Media Type
                                Header File
Copyright 2019-2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ------------------------------------------------------
07/21/20   ck           Adjusted boot_media_type to provide true number of entries
05/13/20   ck           Added EEPROM_FLASH
05/07/20   ck           Added PBL_MEDIA
09/08/19   ds           Initial creation
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/* Define the media types.*/
typedef enum
{
  NO_FLASH         = 0,
  NOR_FLASH        = 1,
  NAND_FLASH       = 2,
  ONENAND_FLASH    = 3,
  SDC_FLASH        = 4,
  MMC_FLASH        = 5,
  SPI_FLASH        = 6,
  PCIE_FLASHLESS   = 7,
  UFS_FLASH        = 8,
  NVME_FLASH       = 9,
  RESERVED_1_FLASH = 10,
  USB_FLASHLESS    = 11,                /* this is not a real flash type, it's used only for sw_type */
  EEPROM_FLASH     = 29,
  PBL_MEDIA        = 30,                /* Special, used by XBL to indicate MediaInterface to use PBL passed value */
  MEDIA_TYPE_MAX   = 31,                /* Used to know max number of unique medias */
  MEDIA_TYPE_FORCE_ALIGN = 0x7FFFFFFF   /* Force 4 byte alignment */
} boot_media_type;

#endif /* BOOT_MEDIA_TYPE_H */