#ifndef __QUP_ADRESSES_H__
#define __QUP_ADRESSES_H__

/*=============================================================================   
    @file  qup_address_ranges.h
    @brief interface to device configuration
   
    Copyright (c) 2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/11/22   RK      Added for Kailua.
=============================================================================*/

#include "msmhwiobase.h"

#define QUP_0   0
#define QUP_1   1
#define QUP_2   2

#define QUP0_BASE_ADDRESS_START		I2C_MASTER_0_BASE
#define QUP0_BASE_ADDRESS_END		(QUP0_BASE_ADDRESS_START + I2C_MASTER_0_BASE_SIZE)
#define QUP0_COMMON_ADDRESS			(QUP0_BASE_ADDRESS_START + 0xC0000)

#define QUP1_BASE_ADDRESS_START		QUPV3_1_QUPV3_ID_1_BASE
#define QUP1_BASE_ADDRESS_END		(QUP1_BASE_ADDRESS_START + QUPV3_1_QUPV3_ID_1_BASE_SIZE)
#define QUP1_COMMON_ADDRESS			(QUP1_BASE_ADDRESS_START + 0xC0000)

#define QUP2_BASE_ADDRESS_START		QUPV3_2_QUPV3_ID_1_BASE
#define QUP2_BASE_ADDRESS_END		(QUP2_BASE_ADDRESS_START + QUPV3_2_QUPV3_ID_1_BASE_SIZE)
#define QUP2_COMMON_ADDRESS			(QUP2_BASE_ADDRESS_START + 0xC0000)

#define TCSR_TCSR_REG_ADDRESS_START	0x01FC0000
#define TCSR_TCSR_REG_ADDRESS_END	(TCSR_TCSR_REG_ADDRESS_START + 0x30000)

#endif // __QUP_ADRESSES_H__

