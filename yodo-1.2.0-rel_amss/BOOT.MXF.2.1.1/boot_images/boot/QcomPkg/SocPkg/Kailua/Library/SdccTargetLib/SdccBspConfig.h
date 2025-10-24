#ifndef SDCC_BSP_CONFIG_H
#define SDCC_BSP_CONFIG_H
 /**********************************************************************
 * sdcc_bsp_config.h
 *
 * SDCC driver BSP.
 *
 * Copyright (c) 2008-2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************

                             Edit History

when         who     what, where, why
----------   ---     --------------------------------------------------------------  
2022-04-12   gml     Updated Speed mode values as per DT
2021-09-24   ss      Created the file 
-----------------------------------------------------------------------------*/
#include "SdccBsp.h"
#include "msmhwiobase.h"
#include "HALhwio.h"
#include "Target_cust.h"
#include "DDIPlatformInfo.h"
#include <Library/CacheMaintenanceLib.h>
#include <Library/ArmLib.h>
#include <stdio.h>

/* Important Note: */
/* For every new target, verify with the SWI document. */
/* Ensure the SDCC base physical addresses are mapped correct */

#define HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR  0xF1D6000 	

#define HWIO_TCSR_SOC_EMULATION_TYPE       0x1FC8004

#define HWIO_SDC2_SDCC5_HC_ADDR            0x8804000
#define HWIO_SDC4_SDCC5_HC_ADDR            0x8844000

/******************************************************************************
                           S D C C    B S P
******************************************************************************/

/* Max number of slots supported by the Board */
#define SDCC_BSP_NUM_SLOTS         4
/* Todo: Query from pcd or allow query this info. */
/* Used for slot number validation*/
#define SDCC_BSP_INVALID_SLOT      SDCC_BSP_NUM_SLOTS
/* Cache line size */
#define SDCC_BSP_CACHE_LINE_SIZE   32


/* Slot configuration information for the board */
static sdcc_bsp_slot_type sdcc_bsp_slot_config [SDCC_BSP_NUM_SLOTS] = {
   SDCC_BSP_NO_SLOT,
   SDCC_BSP_SD_SLOT,
   SDCC_BSP_NO_SLOT,
   SDCC_BSP_NO_SLOT
};

/* Slot internal or external configuration information */
static sdcc_bsp_slot_access_type sdcc_bsp_slot_access_config [SDCC_BSP_NUM_SLOTS] = {
   SDCC_BSP_SLOT_INVALID,
   SDCC_BSP_SLOT_EXTERNAL,
   SDCC_BSP_SLOT_INVALID,
   SDCC_BSP_SLOT_INVALID
};

static UINT8 enable_dt_logging = 0; 

#endif /* #ifndef SDCC_BSP_CONFIG */

