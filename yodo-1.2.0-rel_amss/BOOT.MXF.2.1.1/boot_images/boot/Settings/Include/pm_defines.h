#ifndef __PM_DEFINES_H__
#define __PM_DEFINES_H__

/*===========================================================================

                 Boot Loader Error Handler Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for boot sw settings.
    
Copyright 2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
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

/*************WARNING********************************************

***Below section needs to match with pm_dt.h ****

*********WARNING************************************************/

//LDO
#define PM_LDO_SET_ENABLE        0
#define PM_LDO_SET_VOLT          1
#define PM_LDO_SET_MODE          2
#define PM_LDO_SET_PD_CTRL       3
#define PM_LDO_SET_PIN_CTRL      4
#define PM_LDO_SET_OCP_BROADCAST 5
#define PM_LDO_SET_AHC           6
#define PM_LDO_LPM_OCP_RESP	     7
#define PM_LDO_OCP_RESP_CFG      8
#define PM_LDO_SET_ULS           9

//SMPS
#define PM_SMPS_SET_ENABLE        20
#define PM_SMPS_SET_VOLT          21
#define PM_SMPS_SET_MODE          22
#define PM_SMPS_SET_PD_CTRL       23
#define PM_SMPS_SET_PIN_CTRL      24
#define PM_SMPS_SET_OCP_BROADCAST 25
#define PM_SMPS_SET_AHC           26
#define PM_SMPS_SET_AHC_HR		  27
#define PM_SMPS_SET_ULS           28

//BOB
#define PM_BOB_SET_ENABLE         40
#define PM_BOB_SET_VOLT           41
#define PM_BOB_SET_MODE           42

//GPIO  
#define PM_GPIO_SET_ENABLE          60
#define PM_GPIO_SET_CFG_MODE        61
#define PM_GPIO_SET_OUTPUT_LVL      62
#define PM_GPIO_SET_VOLT_SRC        63
#define PM_GPIO_SET_OUT_BUFF_CONFIG 64
#define PM_GPIO_SET_OUT_DRV_STR     65
#define PM_GPIO_SET_OUT_SRC_CFG     66
#define PM_GPIO_SET_PULL_SEL        67  

//CLK
#define PM_CLK_ENABLE  				80
#define PM_CLK_DRV_STR 				81

//MISC  
#define PM_SET_DELAY 				100
#define PM_SPMI_CLK_DATA_CFG 		101
#define PM_SPMI1_CLK_DATA_CFG 		102


//EPM
#define PM_EPM_EN            130
#define PM_EPM_MODE          131
#define PM_EPM_CONFIG        132
/************WARNING END************/

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
#define  PM_CLK_LN_6  PM_CLK_LN_BB
#define  PM_CLK_LN_7  (8)
#define  PM_CLK_LN_8  (9)
#define  PM_CLK_LN_9  (10)

/*=========================================================================
                PON MACROS
===========================================================================*/
#define PM_PON_RESET_SOURCE_KPDPWR            (0)
#define PM_PON_RESET_SOURCE_RESIN             (1)
#define PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR  (2)
#define PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR   (3)


#define PON_EVENT_LOG_LEVEL_MIN (0)
#define PON_EVENT_LOG_LEVEL_VERBOSE (1)
#define PON_EVENT_LOG_LEVEL_RAWDATA (2)
#define PON_EVENT_LOG_LEVEL_MAX (0x7F)

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

/*==================================================================
                GPIO MACROS
====================================================================*/
#define PM_GPIO_1  (0)
#define PM_GPIO_2  (1)
#define PM_GPIO_3  (2)
#define PM_GPIO_4  (3)
#define PM_GPIO_5  (4)
#define PM_GPIO_6  (5)
#define PM_GPIO_7  (6)
#define PM_GPIO_8  (7)
#define PM_GPIO_9  (8)
#define PM_GPIO_10 (9)
#define PM_GPIO_11 (10)
#define PM_GPIO_12 (11)
#define PM_GPIO_13 (12)
#define PM_GPIO_14 (13)
#define PM_GPIO_15 (14)
#define PM_GPIO_16 (15)
#define PM_GPIO_17 (16)
#define PM_GPIO_18 (17)
#define PM_GPIO_19 (18)
#define PM_GPIO_20 (19)
#define PM_GPIO_21 (20)
#define PM_GPIO_22 (21)
#define PM_GPIO_23 (22)
#define PM_GPIO_24 (23)
#define PM_GPIO_25 (24)
#define PM_GPIO_26 (25)
#define PM_GPIO_27 (26)
#define PM_GPIO_28 (27)
#define PM_GPIO_29 (28)
#define PM_GPIO_30 (29)
#define PM_GPIO_31 (30)
#define PM_GPIO_32 (31)
#define PM_GPIO_33 (32)
#define PM_GPIO_34 (33)
#define PM_GPIO_35 (34)
#define PM_GPIO_36 (35)
#define PM_GPIO_37 (36)
#define PM_GPIO_38 (37)
#define PM_GPIO_39 (38)
#define PM_GPIO_40 (39)
#define PM_GPIO_41 (40)
#define PM_GPIO_42 (41)
#define PM_GPIO_43 (42)
#define PM_GPIO_44 (43)
							  
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

/*=========================================================================
                SDAM MACROS
===========================================================================*/
#define PM_SDAM_1 (0)

/*=========================================================================
                EPM MACROS
===========================================================================*/
//EPM
#define PM_EPM_MODE_RCM  1
#define PM_EPM_MODE_ACAT 0

#define PM_EPM_EN_SET(enable)                      PM_EPM_EN 0 0 0 enable /*enable can be TRUE or FALSE*/
#define PM_EPM_MODE_SET(mode)                      PM_EPM_MODE 0 0 0 mode /*mode can be PM_EPM_MODE_RCM or PM_EPM_MODE_ACAT*/
#define PM_EPM_CONFIG_SET(enable, gang, sid, ppid) PM_EPM_CONFIG enable gang sid ppid

/*=========================================================================
                PSI OEM MACROS
===========================================================================*/
#define PM_SBL_WRITE (0)
#define PM_SBL_DELAY (1)
#define PM_SBL_NOP   (4)

#define  EQUAL               (0)
#define  GREATER             (1)
#define  GREATER_OR_EQUAL    (2)
#define  LESS                (3)
#define  LESS_OR_EQUAL       (4)
#define  REV_ID_OPERATION_I  (5)

#endif /*__PM_DEFINES_H__*/
