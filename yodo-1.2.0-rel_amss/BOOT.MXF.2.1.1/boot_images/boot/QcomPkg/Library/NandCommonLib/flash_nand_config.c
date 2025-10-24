/*====================================================================
 *
 * FILE: flash_nand_config.c
 *
 * SERVICES: Functions and data for Flash NAND Configurations
 *
 * DESCRIPTION: This file contain initialization and interface APIs
 *              of flash config data, which is used across all NAND
 *              like devices (NAND, OneNAND)
 *
 *
 * PUBLIC CLASSES AND STATIC FUNCTIONS:
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:
 *
 * Copyright (c) 2011-2015, 2017, 2018, 2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/flash_nand_config.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 12/04/20     sa      Added Hynix NAND part.
 * 08/11/20     sa      Ported changes for Xfer steps.
 * 08/01/20     sa      Workaround for Rumi.
 * 06/08/20     sa      Ported for Olympic.
 * 02/27/18     eo      Use 4 byte aligned read for BBM marker 
 * 05/25/17     eo      Add support for Toshiba Nand device
 * 04/18/17     eo      Add 16bit ECC support
 * 12/01/15     sb      Clean-up
 * 09/19/14     eo      Update to support 9x45
 * 06/04/14     sb      Update to support 9x45
 * 01/08/13     sv      Add Toshiba 2K Page 8 bit ECC NAND Support
 * 12/04/12     sv      Add 4K Page Micron NAND Support
 * 10/04/12     sv      Update the transfer step values for 9x25
 * 07/27/12     sv      Remove unused devices from supported dev table
 * 12/14/11     eo      Add optimized transfer steps values
 * 05/20/11     bb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_nand_config.h"

#define NUM_ARRAY_ELEMENTS(array, type)  (sizeof(array)/sizeof(type))

/* Transfer step values to use based on EBI2 clock frequency */
#define FLASH_EBI2_FREQ_CFG FLASH_EBI2_64MHZ
/*-----------------------------------------------------------------------
 *           Definitions and Constants
 *----------------------------------------------------------------------*/
/* x8, 2k or 4k page NAND devices */
static const struct nand_xfer_steps_val flash_nand_2k_4k_8bit_cfg[] =
{{7,       /* Number of transfer steps */
  /* Timing modes(TM): */
  /*   XFER 1           XFER 2          XFER 3         XFER 4          XFER 5          XFER 6         XFER 7  */          
  {
      {0x04E00480, 0x59F05998, 0x89E08980, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000},  /* TM 0 */
      {0x00E00080, 0x49F04D99, 0x85E08580, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000},  /* TM 1 */
      {0x00E00080, 0x45F0459A, 0x85E08580, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000},  /* TM 2 */
      {0x00E00080, 0x45F04599, 0x81E08180, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000},  /* TM 3 */
      {0x00E00080, 0x45F0459A, 0x81E08180, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000},  /* TM 4 */
      {0x00E00080, 0x45F04199, 0x81E08180, 0xD000D000, 0xC000C000, 0xC000C000, 0xC000C000}   /* TM 4 (boost mode)*/
 }}
};

/* Transfer step configuration based on EBI2 clock frequency */
static struct flash_nand_ebi2_cfg ebi2_cfg_table[] =
{
  /* ebi2 @ 100mhz */
  {
    flash_nand_2k_4k_8bit_cfg,  /* XFER steps for x8, 2k page */
    NULL,                       /* XFER steps for x16, 2k page */
    flash_nand_2k_4k_8bit_cfg   /* XFER steps for x8, 4k page */
  }
};

/* Spare Bytes info for 2K x8 Device */
static struct flash_spare_info spare_info_x8_2048 =
{
  { {0, 2048, 4},    /* Bad Block Info - Page 0 */
#if !defined(BUILD_RUMI_SLOW_NAND)
    {1, 2048, 4}     /* Bad Block Info - Page 1 */
#endif
  },
  16, 0, 16,         /* udata max, udata ecc max, udata corrected bytes */
  NULL,              /* Spare udata encode APIs */
  NULL               /* Spare udata decode APIs */
};

/* Spare Bytes info for 2K x16 Device */
static struct flash_spare_info spare_info_x16_2048 =
{
  { {0, 2048, 4},     /* Bad Block Info - Page 0 */
#if !defined(BUILD_RUMI_SLOW_NAND)
    {1, 2048, 4}      /* Bad Block Info - Page 1 */
#endif
  },
  16, 0, 16,          /* udata max, udata ecc max, udata corrected bytes */
  NULL,               /* Spare udata encode APIs */
  NULL                /* Spare udata decode APIs */
};

/* Spare Bytes info for 4K x8 Device */
static struct flash_spare_info spare_info_x8_4096 =
{
  { {0, 4096, 4},     /* Bad Block Info - Page 0 */
#if !defined(BUILD_RUMI_SLOW_NAND)
    {1, 4096, 4}      /* Bad Block Info - Page 1 */
#endif
  },
  32, 0, 32,          /* udata max, udata ecc max, udata corrected bytes */
  NULL,               /* Spare udata encode APIs */
  NULL                /* Spare udata decode APIs */
};

/* Spare Bytes info for 4K x16 Device */
static struct flash_spare_info spare_info_x16_4096 =
{
  { {0, 4096, 4},     /* Bad Block Info - Page 0 */
#if !defined(BUILD_RUMI_SLOW_NAND)
    {1, 4096, 4}      /* Bad Block Info - Page 1 */
#endif
  },
  40, 0, 24,          /* udata max, udata ecc max, udata corrected bytes */
  NULL,               /* Spare udata encode APIs */
  NULL                /* Spare udata decode APIs */
};

/* Supported Regular NAND devices */
static struct flash_nand_params supported_nand_devices[] =
{
  /* Hynix NAND Device: ONFI device.
   * This device is added here because this is 8 x 8 JSC MCP part and has 
   * 2 x 4Gbit NAND dies from Hynix and supports ONFI. But the ONFI page
   * paremeter returns the following: num_blocks_per_unit : 2048, 
   * num_units : 1, due to which the size of the NAND part is calculated as
   * num_blocks_per_unit * num_units = 4Gbit.
   * To use the device as 8 Gbit, hard coded the block size to 4096( 2 * 4Gbit).
   * To identify the device as 8Gbit part, can also check the read ID values 
   * (manufacture ID (0xAD), device ID(0xA3)).
   */
  {
    FLASH_HAL_8_BIT_WIDTH,         /*  Device width */
    NAND_4K_8_BIT_XFER_CFG,        /*  Device transfer steps */
    FLASH_NAND_OTP_SEQUENCE_CFG2,  /*  OTP Config ; legacy*/
    &spare_info_x8_4096,           /*  Device Spare Info  */
    "H27S4G8F2EKPB4",             /*   Device name */
    {0xAD, 0xA3},                  /*  Device ID */
    4096,                          /*  Block Count( 2*2048 ) */
    64,                            /*  Page Count */
    4096,                          /*  Page Size */
    256,                           /*  Spare Size */
    100,                           /*  tWB = 100 ns for Hynix */
    0xff,                          /*  Operation status mask */
    0x01,                          /*  Operation success status value */
    {                              /*  Device feature Flags1: */
      NAND_4BIT_HW_ECC,            /*  Note: use NAND_MAX_SUPPORTED_HW_ECC for 16bit ECC */
      FLASH_DEFAULT_READ_MPAGES,
      FLASH_DEFAULT_WRITE_MPAGES,
      FLASH_DEFAULT_READ_WRITE_CP
    },
    {0x0},                         /*  Device feature Flags2: */
    0x1                            /* Device Timing mode. */
  },
  /* Toshiba TC58NYG0S3HBAI6 flash (1.8V, x8 part)  
   * This device is added here because there was no way to identify the 
   * correct Spare size of this device since the Redundant Area Size 
   * specified in the Device IDs is not correct for this device.There are
   * 4 Bit ECC devices(64 byte spare area per page) in Toshiba as well with 
   * the same id(0xA1). We are hardcoding here to 8 Bit ECC part
   * (TC58NYG0S3HBAI6) for device id 0xA1. If support for 4 Bit ECC part is 
   * required, then this table needs to be updated with required values for 
   * the 4 Bit ECC part and 8 Bit ECC cannot be supported in the same build.
   * This needs to be added here to support TC58NYG0S3HBAI6 part unless there 
   * is a hardware fix from Toshiba.
   */
  {
    FLASH_HAL_8_BIT_WIDTH,         /*  Device width */
    NAND_2K_8_BIT_XFER_CFG,        /*  Device transfer steps */
    FLASH_NAND_OTP_SEQUENCE_CFG2,  /*  OTP Config */
    &spare_info_x8_2048,           /*  Device Spare Info  */
    "TC58NYG1S3HBAI6",             /*  Device name */
    {0x98, 0xAA},                  /*  Device ID */
    2048,                          /*  Block Count */
    64,                            /*  Page Count */
    2048,                          /*  Page Size */
    128,                           /*  Spare Size */
    100,                           /*  tWB = 100 ns for Toshiba */
    0xff,                          /*  Operation status mask */
    0x01,                          /*  Operation success status value */
    {                              /*  Device feature Flags1: */
      NAND_8BIT_HW_ECC,            /*  Note: use NAND_MAX_SUPPORTED_HW_ECC for 16bit ECC */
      FLASH_DEFAULT_READ_MPAGES,
      FLASH_DEFAULT_WRITE_MPAGES,
      FLASH_DEFAULT_READ_WRITE_CP
    },
    {0x0},                         /*  Device feature Flags2: */
    0x4                            /* Device Timing mode.  Default 4 */
  },
  /* Toshiba TC58NYG2S0HBA14 flash ( x8 part), non-ONFI1.0
     * This device is non-ONFI.
     * page size: 4096 + 256 = 4352 bytes
     * block size: 64 pages
     * total size = 2048 blocks = 4Gbit
     */ 
  {
    FLASH_HAL_8_BIT_WIDTH,	   /*  Device width */
    NAND_4K_8_BIT_XFER_CFG, 	   /*  Device transfer steps */
    FLASH_NAND_OTP_SEQUENCE_CFG2,  /*  OTP Config */
    &spare_info_x8_4096,	   /*  Device Spare Info  */
    "TC58NYG2S0HBAI4",		   /*  Device name */
    {0x98, 0xAC},		   /*  Device ID */
    2048,			   /*  Block Count */
    64, 			   /*  Page Count */
    4096,			   /*  Page Size */
    256,			   /*  Spare Size */
    100,			   /*  tWB = 100 ns for Toshiba */
    0xff,			   /*  Operation status mask */
    0x01,			   /*  Operation success status value */
    {				   /*  Device feature Flags1: */
      NAND_8BIT_HW_ECC,            /*  Note: use NAND_MAX_SUPPORTED_HW_ECC for 16bit ECC */
      FLASH_DEFAULT_READ_MPAGES,
      FLASH_DEFAULT_WRITE_MPAGES,
      FLASH_DEFAULT_READ_WRITE_CP
    },
    {0x0},                         /*  Device feature Flags2: */
    0x4                            /* Device Timing mode.  Default 4 */
  },

  /* Toshiba TC58NYG0S3HBAI6 flash (1.8V, x8 part)  
   * This device is added here because there was no way to identify the 
   * correct Spare size of this device since the Redundant Area Size 
   * specified in the Device IDs is not correct for this device.There are
   * 4 Bit ECC devices(64 byte spare area per page) in Toshiba as well with 
   * the same id(0xA1). We are hardcoding here to 8 Bit ECC part
   * (TC58NYG0S3HBAI6) for device id 0xA1. If support for 4 Bit ECC part is 
   * required, then this table needs to be updated with required values for 
   * the 4 Bit ECC part and 8 Bit ECC cannot be supported in the same build.
   * This needs to be added here to support TC58NYG0S3HBAI6 part unless there 
   * is a hardware fix from Toshiba.
   */
  {
    FLASH_HAL_8_BIT_WIDTH,         /*  Device width */
    NAND_2K_8_BIT_XFER_CFG,        /*  Device transfer steps */
    FLASH_NAND_OTP_SEQUENCE_CFG2,  /*  OTP Config */
    &spare_info_x8_2048,           /*  Device Spare Info  */
    "TC58NYG0S3HBAI6",             /*  Device name */
    {0x98, 0xA1},                  /*  Device ID */
    1024,                          /*  Block Count */
    64,                            /*  Page Count */
    2048,                          /*  Page Size */
    128,                           /*  Spare Size */
    100,                           /*  tWB = 100 ns for Toshiba */
    0xff,                          /*  Operation status mask */
    0x01,                          /*  Operation success status value */
    {                              /*  Device feature Flags1: */
      NAND_8BIT_HW_ECC,            /*  Note: use NAND_MAX_SUPPORTED_HW_ECC for 16bit ECC */
      FLASH_DEFAULT_READ_MPAGES,
      FLASH_DEFAULT_WRITE_MPAGES,
      FLASH_DEFAULT_READ_WRITE_CP
    },
    {0x0},                         /*  Device feature Flags2: */
    0x4                            /* Device Timing mode.  Default 4 */
  }
};

/* Supported Devices */
static struct flash_nand_cfg_data supported_nand_cfgs[] =
{
  {
    FLASH_HAL_DEVICE_NAND,
    FLASH_HAL_CS0,
    NUM_ARRAY_ELEMENTS(supported_nand_devices, flash_nand_params_type),
    supported_nand_devices,
    &ebi2_cfg_table[FLASH_EBI2_FREQ_CFG]
  },
  {
    FLASH_HAL_DEVICE_NONE,    /* TO MARK THE END -
                              Mandatory - Used in driver */
    FLASH_HAL_CS0,
    0,
    NULL,
    NULL
  }
};

/*
 * Return all supported NAND configurations
 */
void flash_nand_get_configs(struct flash_nand_cfg_data **cfg_data)
{
  (void)spare_info_x8_2048;
  (void)spare_info_x16_2048;
  (void)spare_info_x8_4096;
  (void)spare_info_x16_4096;
  *cfg_data = (struct flash_nand_cfg_data *) &supported_nand_cfgs;
}
