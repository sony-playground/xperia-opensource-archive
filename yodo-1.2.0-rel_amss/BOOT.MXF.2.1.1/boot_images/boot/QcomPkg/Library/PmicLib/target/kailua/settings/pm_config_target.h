#ifndef __PM_CONFIG_TARGET_H__
#define __PM_CONFIG_TARGET_H__
/*! \file 
 *  \n
 *  \brief  pm_config_target.h ---- PMIC CONFIG TARGET 
 *  \n
 *  \n This header file contains enums and API definitions for PMIC version 
 *      detection
 *  \n
 *  \n &copy; Copyright 2015 - 2019 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/dev/core.boot/6.1/dvaddem.core.boot.6.1.config_part1/QcomPkg/SocPkg/Kailua/Settings/PMIC/pm_config_target.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/10/15   aab     New file 
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/


/* Maximum number of PMIC DEVICES */
#define PM_MAX_NUM_PMICS       14 //current SPMI spec supports 16 slave id
 /* Maximum number of PMIC SLAVE IDs */
#define PM_MAX_NUM_SLAVE_IDS     14 //max slaves per spmi bus

#define PM_MAX_BUSES_SUPPORTED 2
// Global sids
#define PM_GLOBAL_PRIMARY_SID     14
#define PM_GLOBAL_SECONDARY_SID   15

#define PM_MAX_NUM_SLAVE_IDS_PER_PMIC     2 //max SID per PMIC

#define INVALID_SLAVE_ID         0xFF 

/* PMIC A Primary SlaveID */
#define PMIC_A_SLAVEID_PRIM      0x00 

/* PMIC MAX PBS RAM SIZE */
#define PBS_RAM_DATA_SIZE        4100

#define PM_PRIMARY_PMIC_INDEX    0

#define PMICLIB_ARCH_PRE7     FALSE

#endif // __PM_CONFIG_TARGET_H__
