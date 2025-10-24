/*====================================================================
 *
 * FILE:        flash_hal_osal_core.c
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
 *  $Header: //components/dev/core.boot/5.1.1/glosch.core.boot.5.1.1.nand_cfg_olympic/QcomPkg/Library/NandCommonLib/NandHalLib/flash_hal_osal_core.c#1 $ $DateTime: 2022/04/04 03:16:28 $ $Author: glosch $
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
   return FLASH_HAL_SUCCESS;
}


