#ifndef __HWIO_SLP_CNTR_H__
#define __HWIO_SLP_CNTR_H__
/*
===========================================================================
*/
/**
    @file hwio_slp_cntr.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8475 (Palima) [palima_v1.0_p3q2r43_MTO]
 
    This file contains HWIO register definitions for the following modules:
        SLP_CNTR


    Generation parameters: 
    {'filename': 'hwio_slp_cntr.h', 'modules': ['SLP_CNTR']}
*/
/*
    ===========================================================================

    Copyright (c) 2021 Qualcomm Technologies, Inc.
    All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.

    Export of this technology or software is regulated by the U.S. Government.
    Diversion contrary to U.S. law prohibited.

    All ideas, data and information contained in or disclosed by
    this document are confidential and proprietary information of
    Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
    By accepting this material the recipient agrees that this material
    and the information contained therein are held in confidence and in
    trust and will not be used, copied, reproduced in whole or in part,
    nor its contents revealed in any manner to others without the express
    written permission of Qualcomm Technologies, Inc.

    ===========================================================================

    $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Settings/UFS/inc/hwio_slp_cntr.h#2 $
    $DateTime: 2021/10/18 05:12:34 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: SLP_CNTR
 *--------------------------------------------------------------------------*/

#define SLP_CNTR_REG_BASE                                    (AOSS_BASE      + 0x01221000)
#define SLP_CNTR_REG_BASE_SIZE                               0x1000
#define SLP_CNTR_REG_BASE_USED                               0x0

#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR               (SLP_CNTR_REG_BASE      + 0x0)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_RMSK               0xffffffff
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_IN                    \
                in_dword(HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_INM(m)            \
                in_dword_masked(HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR, m)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_BMSK          0xffffffff
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_SHFT                   0


#endif /* __HWIO_SLP_CNTR_H__ */
