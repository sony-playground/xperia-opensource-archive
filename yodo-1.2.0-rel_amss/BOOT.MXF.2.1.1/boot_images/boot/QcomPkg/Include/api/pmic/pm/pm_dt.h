#ifndef __PM_DT_H__
#define __PM_DT_H__
/*===========================================================================


                  P M    H E A D E R    F I L E

DESCRIPTION
  This file contains prototype definitions to support interaction
  with the QUALCOMM Power Management ICs.

Copyright (c) 2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/17/21   al      Initial Draft

===========================================================================*/

/*************WARNING********************************************

***Any changes to this file also needs to be added in pm_defines.h ***

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
#define PM_LDO_OCP_RESP_CFG	     8
#define PM_LDO_SET_ULS           9

//SMPS
#define PM_SMPS_SET_ENABLE        20
#define PM_SMPS_SET_VOLT          21
#define PM_SMPS_SET_MODE          22
#define PM_SMPS_SET_PD_CTRL       23
#define PM_SMPS_SET_PIN_CTRL      24
#define PM_SMPS_SET_OCP_BROADCAST 25
#define PM_SMPS_SET_AHC           26
#define PM_SMPS_SET_AHC_HR        27
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
#define PM_EPM_EN                   130
#define PM_EPM_MODE                 131
#define PM_EPM_CONFIG               132

#endif /* __PM_DT_H__ */
