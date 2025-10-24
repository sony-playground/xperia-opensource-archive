/*====================================================================
 *
 * FILE:        flash_hal_osal_loader.c
 *
 * SERVICES:    Image wrapper function declarations for nand HAL driver
 *
 * DESCRIPTION: Image wrapper functions declarations for nand HAL driver
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2020 QUALCOMM Technologies Incorporated.
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
 *  $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandCommonLib/NandHalLib/flash_hal_osal_loader.c#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/15/20     bb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_hal_osal.h"
#include "flashi_hal_common.h"
#include "flashi_hal_nand.h"
#include "QpicLib/flashi_hal_nandc.h"


/*===================================================================
 *
 *                     Image Specific Functions
 *
 ====================================================================*/

/*
 * BAM Enable from DCPU mode
 */
uint32 flash_hal_enable_bam(void)
{
   /* Setting the NAND controller in BAM mode is done in SBL */
   //*((volatile uint32*)HAL_QPIC_NANDC_NAND_CTRL_DCPU_PADDR) =
   //   FLASH_NAND_CTRL_BAM_MODE_EN;

  //TODO Generate HWIO with QPIC_NAND_CTRL register
  *((volatile uint32*)(0x1CC8F00)) =
      FLASH_NAND_CTRL_BAM_MODE_EN;

   /* Set the VLD register */
   //*((volatile uint32*)HAL_QPIC_NANDC_FLASH_DEV_CMD_VLD_DCPU_PADDR) =
   //   0xEC00001D;

  //TODO Generate HWIO with FLASH_DEV_CMD_VLD register
   *((volatile uint32*)(0x1CCF0AC)) =
      0xEC00001D;
   return FLASH_HAL_SUCCESS;
}

