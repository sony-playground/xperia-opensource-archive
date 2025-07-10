#ifndef __PM_DEFINES_H__
#define __PM_DEFINES_H__

/*===========================================================================

                 Boot Loader Error Handler Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for boot sw settings.
    
Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/13/20   alal    Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/
/*=========================================================================
                Generic PMIC MACROS
===========================================================================*/
#include "../../QcomPkg/Include/api/pmic/pm/pm_dt.h"

#define PM_ENABLE  (0x1)
#define PM_DISABLE (0x0)
#define PM_TRUE   (1)
#define PM_FALSE  (0)

#define PM_OFF (0x0)
#define PM_ON  (0x1)

#define PMIC_A (0)
#define PMIC_B (1)
#define PMIC_C (2)
#define PMIC_D (3)
#define PMIC_E (4)
#define PMIC_F (5)
#define PMIC_G (6)
#define PMIC_H (7)
#define PMIC_I (8)
#define PMIC_J (9)
#define PMIC_K (10)
#define PMIC_L (11)
#define PMIC_M (12)
#define PMIC_N (13)
#define PMIC_O (14)

#define PM_BUSID_0 (0)
#define PM_BUSID_1 (1)

#define PM_WARM_RESET  (0)
#define PM_HARD_RESET  (1)
#define PM_SHUTDOWN    (2)

#define PM_DELAY(x) PM_SET_DELAY 0 0 0 x

/*=========================================================================
                PMIC Clock MACROS
===========================================================================*/

#define  PM_CLK_SLEEP (0)
#define  PM_CLK_XO    (1)
#define  PM_CLK_RF_1  (2)
#define  PM_CLK_RF_2  (3)
#define  PM_CLK_RF_3  (4)
#define  PM_CLK_RF_4  (5)
#define  PM_CLK_RF_5  (6)
#define  PM_CLK_LN_BB (7)
#define  PM_CLK_BB_1  PM_CLK_LN_BB
#define  PM_CLK_BB_2  (8)
#define  PM_CLK_BB_3  (9)
#define  PM_CLK_BB_4  (10)
#define  PM_CLK_BB_5  (11)
#define  PM_CLK_DIV_1 (12)
#define  PM_CLK_DIV_2 (13)
#define  PM_CLK_DIV_3 (14)
#define  PM_CLK_DIST  (15)
#define  PM_ALL_CLKS  (16)

/*=========================================================================
                PON MACROS
===========================================================================*/
#define PM_PON_RESET_SOURCE_KPDPWR            (0)
#define PM_PON_RESET_SOURCE_RESIN             (1)
#define PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR  (2)
#define PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR   (3)

/*=========================================================================
                RAILS MACROS
===========================================================================*/
#define PM_LDO_1  (0)
#define PM_LDO_2  (1)
#define PM_LDO_3  (2)
#define PM_LDO_4  (3)
#define PM_LDO_5  (4)
#define PM_LDO_6  (5)
#define PM_LDO_7  (6)
#define PM_LDO_8  (7)
#define PM_LDO_9  (8)
#define PM_LDO_10 (9)
#define PM_LDO_11 (10)
#define PM_LDO_12 (11)
#define PM_LDO_13 (12)
#define PM_LDO_14 (13)
#define PM_LDO_15 (14)

#define PM_SMPS_1  (0)
#define PM_SMPS_2  (1)
#define PM_SMPS_3  (2)
#define PM_SMPS_4  (3)
#define PM_SMPS_5  (4)
#define PM_SMPS_6  (5)
#define PM_SMPS_7  (6)
#define PM_SMPS_8  (7)
#define PM_SMPS_9  (8)
#define PM_SMPS_10 (9)
#define PM_SMPS_11 (10)
#define PM_SMPS_12 (11)
#define PM_SMPS_13 (12)
#define PM_SMPS_14 (13)
#define PM_SMPS_15 (14)

#define PM_BOB_1 (0)
#define PM_BOB_2 (1)
#define PM_BOB_3 (2)

#define PM_SW_MODE_LPM        (0)
#define PM_SW_MODE_BYPASS     (1)
#define PM_SW_MODE_AUTO       (2)
#define PM_SW_MODE_NPM        (3)
#define PM_SW_MODE_RETENTION  (4)
							  
/*=========================================================================
                DISPLAY MACROS
===========================================================================*/
#define MAP_A (0)
#define MAP_B (1)
#define MAP_C (2)
#define MAP_D (3)
#define MAP_E (4)
#define MAP_F (5)
#define MAP_G (6)
#define MAP_H (7)
#define MAP_I (8)
#define MAP_INVALID (9)

#define ASWIRE_MAP_SEL_0 (0)
#define ASWIRE_MAP_SEL_1 (1)
#define ASWIRE_MAP_SEL_2 (2)
#define ASWIRE_MAP_SEL_3 (3)
#define ASWIRE_MAP_SEL_4 (4)
#define ASWIRE_MAP_SEL_5 (5)
#define ASWIRE_MAP_SEL_6 (6)
#define ASWIRE_MAP_SEL_7 (7)
#define ASWIRE_MAP_SEL_INVALID (8)


#define ESWIRE_MAP_SEL_0 (0)
#define ESWIRE_MAP_SEL_1 (1)
#define ESWIRE_MAP_SEL_2 (2)
#define ESWIRE_MAP_SEL_3 (3)
#define ESWIRE_MAP_SEL_4 (4)
#define ESWIRE_MAP_SEL_5 (5)
#define ESWIRE_MAP_SEL_6 (6)
#define ESWIRE_MAP_SEL_7 (7)
#define ESWIRE_MAP_SEL_8 (8)
#define ESWIRE_MAP_SEL_INVALID (9)



/*=========================================================================
                BMD MACROS
===========================================================================*/
#define PM_BMD_SRC_ID (0)
#define PM_BMD_SRC_THERM (1)

/*=========================================================================
                Charger USB peripheral MACROS
===========================================================================*/
#define PM_INPUT_PRIORITY_WLS (0)
#define PM_INPUT_PRIORITY_USB (1)

#define PM_EXT_RSNS_SCALE_1x (0)
#define PM_EXT_RSNS_SCALE_2x (1)
#define PM_EXT_RSNS_SCALE_2P5x (2)

/*=========================================================================
                LOCKBIT MACROS
===========================================================================*/
#define PM_IMG_NONE    				(0)
#define PM_IMG_LOADER  				(1)
#define PM_IMG_CORE    				(2)
#define PM_IMG_RAMDUMP		             	(3)
#define PM_IMG_INVALID 				(4)
#define PM_IMG_DEVPROG    			(5)

#define LOCKED_NONE   (0)
#define LOCKED_OPEN   (2)
#define LOCKED_CLOSED (3)

/*=========================================================================
                MGPI_PVC MACROS
===========================================================================*/
#define APPS0_PORT               (0)  
#define APPS1_PORT               (1)  
#define MGPI_PVC_PORT            (3)  
#define SPMI_ACCESS_PRIORITY_LOW (0) 

/*=========================================================================
                ACCESS CTRL MACROS
===========================================================================*/
#define REMOVE           (0)
#define APPEND           (1)
#define APPEND_WITH_IRQ  (2)

/*=========================================================================
                MISC MACROS
===========================================================================*/
#define PM_THERM_PULL_UP_30K (0)
#define PM_THERM_PULL_UP_100K (1)
#define PM_THERM_PULL_UP_400K (2)

#endif /*__PM_DEFINES_H__*/
