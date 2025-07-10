#ifndef __I2C_DEFINES_H__
#define __I2C_DEFINES_H__


/*=============================================================================   
    @file  i2c_config.h
    @brief interface to device configuration
   
    Copyright (c) 2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/30/22   PS      Added new include file.
=============================================================================*/


// NOTE: QUPs are numbered starting from 0 as per the IO sheet
#define ENABLE_QUP_06 //PMIC I2C
#define ENABLE_QUP_08 //APSS I2C


// north [se0 - se5] [0:5]
#define QUPV3_0_CORE_BASE_ADDRESS        0x00900000
#define QUPV3_0_CORE_COMMON_BASE_ADDRESS 0x009C0000

// east [se0 - se5] [6:11]
#define QUPV3_1_CORE_BASE_ADDRESS        0x00A00000
#define QUPV3_1_CORE_COMMON_BASE_ADDRESS 0x00AC0000

#define TLMM_GPIO_CFG(gpio, func, dir, pull, drive) \
                          (((gpio) & 0x3FF) << 4  | \
                           ((func) & 0xF  ) << 0  | \
                           ((dir)  & 0x1  ) << 14 | \
                           ((pull) & 0x3  ) << 15 | \
                           ((drive)& 0xF  ) << 17)

#define TLMM_GPIO_INPUT     0x0
#define TLMM_GPIO_PULL_UP   0x3
#define TLMM_GPIO_2MA       0x0

#define QUP_0   0
#define QUP_1   1
#define QUP_2   2

//
// CONFIGURATION START ============================================
//
#define TOP_QUP_00_SDA TLMM_GPIO_CFG(4,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_00_SCL TLMM_GPIO_CFG(5,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_01_SDA TLMM_GPIO_CFG(10,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_01_SCL TLMM_GPIO_CFG(11,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_02_SDA TLMM_GPIO_CFG(14,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_02_SCL TLMM_GPIO_CFG(15,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_03_SDA TLMM_GPIO_CFG(18,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_03_SCL TLMM_GPIO_CFG(19,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_04_SDA TLMM_GPIO_CFG(8,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_04_SCL TLMM_GPIO_CFG(9,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_05_SDA TLMM_GPIO_CFG(0,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_05_SCL TLMM_GPIO_CFG(1,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_06_SDA TLMM_GPIO_CFG(50,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_06_SCL TLMM_GPIO_CFG(51,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_07_SDA TLMM_GPIO_CFG(31,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_07_SCL TLMM_GPIO_CFG(32,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_08_SDA TLMM_GPIO_CFG(24,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_08_SCL TLMM_GPIO_CFG(25,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#define TOP_QUP_09_SDA TLMM_GPIO_CFG(91,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)
#define TOP_QUP_09_SCL TLMM_GPIO_CFG(90,  1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA)

#endif
