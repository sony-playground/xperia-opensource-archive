#ifndef SDCC_BSP_CONFIG_H
#define SDCC_BSP_CONFIG_H
 /**********************************************************************
 * sdcc_bsp_config.h
 *
 * SDCC driver BSP.
 *
 * Copyright (c) 2021-2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************

                             Edit History

when         who     what, where, why
----------   ---     -------------------------------------------------------------- 
2022-04-22   ssb     Updated Speed mode values as per DT 
2022-02-07   cm      Move default values to Target Files
2021-09-24   ss      Created the file 
-----------------------------------------------------------------------------*/
#include "SdccBsp.h"
#include "msmhwiobase.h"
#include "HALhwio.h"
#include "Target_cust.h"
#include "DDIPlatformInfo.h"
#include <stdio.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/ArmLib.h>

/* Important Note: */
/* For every new target, verify with the SWI document. */
/* Ensure the SDCC base physical addresses are mapped correct */

#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_0_ADDR    0x0F191000
#define HWIO_TLMM_SDC1_HDRV_PULL_CTL_1_ADDR    0x0F191004

#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR      0x0F194000 	

#define HWIO_TCSR_SOC_EMULATION_TYPE           0x01FC8004

#define HWIO_SDC1_SDCC5_HC_ADDR                0x007C4000
#define HWIO_SDC2_SDCC5_HC_ADDR                0x08804000

/******************************************************************************
                           e M M C    B S P
******************************************************************************/

#define SDC1_BSP_DLL_CONFIG_DEFAULT_VAL                      0x000F642C
#define SDC1_BSP_DLL_CONFIG_2_DEFAULT_VAL     			     0xA001
#define SDC1_BSP_DLL_CONFIG_3_DEFAULT_VAL    				 0x01
#define SDC1_BSP_DDR_CONFIG_DEFAULT_VAL          			 0x80040868
#define SDC1_BSP_DLL_USER_CTRL_DEFAULT_VAL                   0x2C010800
#define SDC1_BSP_DLL_TEST_CTRL_DEFAULT_VAL                   0x1400000
#define SDC1_BSP_DLL_CONFIG_DEFAULT_VAL_HS200_VAL            0x0007642C
#define SDC1_BSP_DLL_CONFIG_2_DEFAULT_VAL_HS200_VAL     	 0xA000
#define SDC1_BSP_DLL_CONFIG_3_DEFAULT_VAL_HS200_VAL    	     0x10
#define SDC1_BSP_DLL_TEST_CTRL_DEFAULT_VAL_HS200_VAL         0x1800000
#define SDC1_BSP_DEFAULT_DRIVE_STRENGTH_CTL0            	 0x1FDB
#define SDC1_BSP_DEFAULT_DRIVE_STRENGTH_CTL1            	 0x35



/******************************************************************************
                           S D C C    B S P
******************************************************************************/
#define SDC2_BSP_DLL_CONFIG_DEFAULT_VAL                     0x0007642C
#define SDC2_BSP_DLL_CONFIG_2_DEFAULT_VAL     				0xA800
#define SDC2_BSP_DLL_CONFIG_3_DEFAULT_VAL    				0x10
#define SDC2_BSP_DDR_CONFIG_DEFAULT_VAL          			0x80040868
#define SDC2_BSP_DLL_USER_CTRL_DEFAULT_VAL                  0x2C010800
#define SDC2_BSP_DLL_TEST_CTRL_DEFAULT_VAL                  0x1800000
#define SDC2_BSP_DEFAULT_DRIVE_STRENGTH_CTL                 0x1FFF



/* Max number of slots supported by the Board */
#define SDCC_BSP_NUM_SLOTS         4
/* Todo: Query from pcd or allow query this info. */
/* Used for slot number validation*/
#define SDCC_BSP_INVALID_SLOT      SDCC_BSP_NUM_SLOTS
/* Cache line size */
#define SDCC_BSP_CACHE_LINE_SIZE   32

/* Slot configuration information for the board */
static sdcc_bsp_slot_type sdcc_bsp_slot_config [SDCC_BSP_NUM_SLOTS] = {
   (SDCC_BSP_EMBEDDED_MEM_SLOT | SDCC_BSP_8BIT_SLOT),
   SDCC_BSP_SD_SLOT,
   SDCC_BSP_NO_SLOT,
   SDCC_BSP_NO_SLOT
};

/* Slot internal or external configuration information */
static sdcc_bsp_slot_access_type sdcc_bsp_slot_access_config [SDCC_BSP_NUM_SLOTS] = {
   SDCC_BSP_SLOT_INTERNAL,
   SDCC_BSP_SLOT_EXTERNAL,
   SDCC_BSP_SLOT_INVALID,
   SDCC_BSP_SLOT_INVALID
};


static UINT8 enable_dt_logging = 0; 

#endif /* #ifndef SDCC_BSP_CONFIG */

