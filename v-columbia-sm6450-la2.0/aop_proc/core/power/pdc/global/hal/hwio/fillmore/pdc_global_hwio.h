#ifndef __PDC_GLOBAL_HWIO_H__
#define __PDC_GLOBAL_HWIO_H__
/*
===========================================================================
*/
/**
    @file pdc_global_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM7xxx (Fillmore) [fillmore_v1.0_p3q1r61]
 
    This file contains HWIO register definitions for the following modules:
        RPMH_PDC_PDC_GLOBAL


    Generation parameters: 
    { 'filename': 'pdc_global_hwio.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': ['RPMH_PDC_PDC_GLOBAL']}
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

    $Header: //components/rel/aop.ho/4.0/aop_proc/core/power/pdc/global/hal/hwio/fillmore/pdc_global_hwio.h#2 $
    $DateTime: 2021/02/23 02:17:01 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: RPMH_PDC_PDC_GLOBAL
 *--------------------------------------------------------------------------*/

#define RPMH_PDC_PDC_GLOBAL_REG_BASE                                                                (AOSS_BASE            + 0x005e0000)
#define RPMH_PDC_PDC_GLOBAL_REG_BASE_SIZE                                                           0x20000
#define RPMH_PDC_PDC_GLOBAL_REG_BASE_USED                                                           0x2400

#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d)                                                  (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X20 + (0x4*(d)))
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_RMSK                                                           0x1f
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_MAXd                                                              3
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_APPS_DRV_ID_BMSK                                               0x1f
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_APPS_DRV_ID_SHFT                                                  0

#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d)                                                    (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X60 + (0x4*(d)))
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_RMSK                                                             0x1f
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_MAXd                                                                0
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_SP_DRV_ID_BMSK                                                   0x1f
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_SP_DRV_ID_SHFT                                                      0

#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X70 + (0x4*(d)))
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_MAXd                                                             0
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_AUDIO_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_AUDIO_DRV_ID_SHFT                                                0

#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X80 + (0x4*(d)))
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_SENSORS_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_SENSORS_PDC_RSC_DRV_IDd_SENSORS_DRV_ID_SHFT                                            0

#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X90 + (0x4*(d)))
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_MAXd                                                               0
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_AOP_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_AOP_DRV_ID_SHFT                                                    0

#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0XA0 + (0x4*(d)))
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_MAXd                                                             0
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_DEBUG_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_DEBUG_DRV_ID_SHFT                                                0

#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0XB0 + (0x4*(d)))
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_MAXd                                                               0
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_GPU_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_GPU_DRV_ID_SHFT                                                    0

#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0XC0 + (0x4*(d)))
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_DISPLAY_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_DISPLAY_DRV_ID_SHFT                                            0

#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0XD0 + (0x4*(d)))
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_COMPUTE_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_COMPUTE_DRV_ID_SHFT                                            0

#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0XE0 + (0x4*(d)))
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_MAXd                                                               1
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_TME_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_TME_DRV_ID_SHFT                                                    0

#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_ADDR(d)                                                  (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X100 + (0x4*(d)))
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_RMSK                                                           0x1f
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_MAXd                                                              0
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_WPSS_DRV_ID_BMSK                                               0x1f
#define HWIO_RPMH_PDC_WPSS_PDC_RSC_DRV_IDd_WPSS_DRV_ID_SHFT                                                  0

#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X110 + (0x4*(d)))
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MAXd                                                             1
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MODEM_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MODEM_DRV_ID_SHFT                                                0

#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0X130 + (0x4*(d)))
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INI(d)                \
                in_dword_masked(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INMI(d,mask)        \
                in_dword_masked(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_OUTI(d,val)        \
                out_dword(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_WLAN_RF_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_WLAN_RF_DRV_ID_SHFT                                            0

#define HWIO_RPMH_PDC_SYNC_RESET_ADDR                                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x1000)
#define HWIO_RPMH_PDC_SYNC_RESET_RMSK                                                                   0x1fff
#define HWIO_RPMH_PDC_SYNC_RESET_IN                    \
                in_dword(HWIO_RPMH_PDC_SYNC_RESET_ADDR)
#define HWIO_RPMH_PDC_SYNC_RESET_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_SYNC_RESET_ADDR, m)
#define HWIO_RPMH_PDC_SYNC_RESET_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_SYNC_RESET_ADDR,v)
#define HWIO_RPMH_PDC_SYNC_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_SYNC_RESET_ADDR,m,v,HWIO_RPMH_PDC_SYNC_RESET_IN)
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_RF_SYNC_RESET_BMSK                                                0x1000
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_RF_SYNC_RESET_SHFT                                                    12
#define HWIO_RPMH_PDC_SYNC_RESET_MODEM_SYNC_RESET_BMSK                                                   0x800
#define HWIO_RPMH_PDC_SYNC_RESET_MODEM_SYNC_RESET_SHFT                                                      11
#define HWIO_RPMH_PDC_SYNC_RESET_WPSS_SYNC_RESET_BMSK                                                    0x400
#define HWIO_RPMH_PDC_SYNC_RESET_WPSS_SYNC_RESET_SHFT                                                       10
#define HWIO_RPMH_PDC_SYNC_RESET_TME_SYNC_RESET_BMSK                                                     0x200
#define HWIO_RPMH_PDC_SYNC_RESET_TME_SYNC_RESET_SHFT                                                         9
#define HWIO_RPMH_PDC_SYNC_RESET_COMPUTE_SYNC_RESET_BMSK                                                 0x100
#define HWIO_RPMH_PDC_SYNC_RESET_COMPUTE_SYNC_RESET_SHFT                                                     8
#define HWIO_RPMH_PDC_SYNC_RESET_DISPLAY_SYNC_RESET_BMSK                                                  0x80
#define HWIO_RPMH_PDC_SYNC_RESET_DISPLAY_SYNC_RESET_SHFT                                                     7
#define HWIO_RPMH_PDC_SYNC_RESET_GPU_SYNC_RESET_BMSK                                                      0x40
#define HWIO_RPMH_PDC_SYNC_RESET_GPU_SYNC_RESET_SHFT                                                         6
#define HWIO_RPMH_PDC_SYNC_RESET_DEBUG_SYNC_RESET_BMSK                                                    0x20
#define HWIO_RPMH_PDC_SYNC_RESET_DEBUG_SYNC_RESET_SHFT                                                       5
#define HWIO_RPMH_PDC_SYNC_RESET_AOP_SYNC_RESET_BMSK                                                      0x10
#define HWIO_RPMH_PDC_SYNC_RESET_AOP_SYNC_RESET_SHFT                                                         4
#define HWIO_RPMH_PDC_SYNC_RESET_SENSORS_SYNC_RESET_BMSK                                                   0x8
#define HWIO_RPMH_PDC_SYNC_RESET_SENSORS_SYNC_RESET_SHFT                                                     3
#define HWIO_RPMH_PDC_SYNC_RESET_AUDIO_SYNC_RESET_BMSK                                                     0x4
#define HWIO_RPMH_PDC_SYNC_RESET_AUDIO_SYNC_RESET_SHFT                                                       2
#define HWIO_RPMH_PDC_SYNC_RESET_SP_SYNC_RESET_BMSK                                                        0x2
#define HWIO_RPMH_PDC_SYNC_RESET_SP_SYNC_RESET_SHFT                                                          1
#define HWIO_RPMH_PDC_SYNC_RESET_APPS_SYNC_RESET_BMSK                                                      0x1
#define HWIO_RPMH_PDC_SYNC_RESET_APPS_SYNC_RESET_SHFT                                                        0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x1400)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_RMSK                                                       0xffff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_IN                    \
                in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_EPCB_TIMEOUT_THRESHOLD_BMSK                                0xffff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_EPCB_TIMEOUT_THRESHOLD_SHFT                                     0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x1500)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_RMSK                                                    0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_EN_BMSK                        0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_EN_SHFT                            12
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_MODEM_EPCB_TIMEOUT_IRQ_EN_BMSK                           0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_MODEM_EPCB_TIMEOUT_IRQ_EN_SHFT                              11
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WPSS_EPCB_TIMEOUT_IRQ_EN_BMSK                            0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WPSS_EPCB_TIMEOUT_IRQ_EN_SHFT                               10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_TME_EPCB_TIMEOUT_IRQ_EN_BMSK                             0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_TME_EPCB_TIMEOUT_IRQ_EN_SHFT                                 9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_EN_BMSK                         0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_EN_SHFT                             8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_EN_BMSK                          0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_EN_SHFT                             7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_GPU_EPCB_TIMEOUT_IRQ_EN_BMSK                              0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_GPU_EPCB_TIMEOUT_IRQ_EN_SHFT                                 6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_EN_BMSK                            0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_EN_SHFT                               5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AOP_EPCB_TIMEOUT_IRQ_EN_BMSK                              0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AOP_EPCB_TIMEOUT_IRQ_EN_SHFT                                 4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_EN_BMSK                           0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_EN_SHFT                             3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_EN_BMSK                             0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_EN_SHFT                               2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SP_EPCB_TIMEOUT_IRQ_EN_BMSK                                0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SP_EPCB_TIMEOUT_IRQ_EN_SHFT                                  1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_APPS_EPCB_TIMEOUT_IRQ_EN_BMSK                              0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_APPS_EPCB_TIMEOUT_IRQ_EN_SHFT                                0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR                                            (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x1600)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_RMSK                                                0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_STATUS_BMSK                0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_STATUS_SHFT                    12
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_MODEM_EPCB_TIMEOUT_IRQ_STATUS_BMSK                   0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_MODEM_EPCB_TIMEOUT_IRQ_STATUS_SHFT                      11
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WPSS_EPCB_TIMEOUT_IRQ_STATUS_BMSK                    0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WPSS_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_TME_EPCB_TIMEOUT_IRQ_STATUS_BMSK                     0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_TME_EPCB_TIMEOUT_IRQ_STATUS_SHFT                         9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_STATUS_BMSK                 0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_STATUS_BMSK                  0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_GPU_EPCB_TIMEOUT_IRQ_STATUS_BMSK                      0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_GPU_EPCB_TIMEOUT_IRQ_STATUS_SHFT                         6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_STATUS_BMSK                    0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AOP_EPCB_TIMEOUT_IRQ_STATUS_BMSK                      0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AOP_EPCB_TIMEOUT_IRQ_STATUS_SHFT                         4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_STATUS_BMSK                   0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_STATUS_BMSK                     0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SP_EPCB_TIMEOUT_IRQ_STATUS_BMSK                        0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SP_EPCB_TIMEOUT_IRQ_STATUS_SHFT                          1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_APPS_EPCB_TIMEOUT_IRQ_STATUS_BMSK                      0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_APPS_EPCB_TIMEOUT_IRQ_STATUS_SHFT                        0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x1700)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_RMSK                                                 0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                  0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                      12
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_MODEM_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                     0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_MODEM_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                        11
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WPSS_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                      0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WPSS_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_TME_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                       0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_TME_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                           9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                   0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                    0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_GPU_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                        0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_GPU_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                           6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                      0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AOP_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                        0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AOP_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                           4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                     0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SENSORS_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                       0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SP_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                          0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SP_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                            1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_APPS_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                        0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_APPS_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                          0

#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2200)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_RMSK                                                          0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_1_BMSK                                 0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_1_SHFT                                        25
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_0_BMSK                                 0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_0_SHFT                                        24
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_1_BMSK                                    0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_1_SHFT                                          23
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_0_BMSK                                    0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_0_SHFT                                          22
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WPSS_PDC_AOP_IRQ_EN_1_BMSK                                     0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WPSS_PDC_AOP_IRQ_EN_1_SHFT                                           21
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WPSS_PDC_AOP_IRQ_EN_0_BMSK                                     0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WPSS_PDC_AOP_IRQ_EN_0_SHFT                                           20
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_1_BMSK                                       0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_1_SHFT                                            19
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_0_BMSK                                       0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_0_SHFT                                            18
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_1_BMSK                                   0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_1_SHFT                                        17
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_0_BMSK                                   0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_0_SHFT                                        16
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_1_BMSK                                    0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_1_SHFT                                        15
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_0_BMSK                                    0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_0_SHFT                                        14
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_1_BMSK                                        0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_1_SHFT                                            13
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_0_BMSK                                        0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_0_SHFT                                            12
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_1_BMSK                                       0x800
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_1_SHFT                                          11
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_0_BMSK                                       0x400
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_0_SHFT                                          10
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_1_BMSK                                         0x200
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_1_SHFT                                             9
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_0_BMSK                                         0x100
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_0_SHFT                                             8
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SENSORS_PDC_AOP_IRQ_EN_1_BMSK                                      0x80
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SENSORS_PDC_AOP_IRQ_EN_1_SHFT                                         7
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SENSORS_PDC_AOP_IRQ_EN_0_BMSK                                      0x40
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SENSORS_PDC_AOP_IRQ_EN_0_SHFT                                         6
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_1_BMSK                                        0x20
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_1_SHFT                                           5
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_0_BMSK                                        0x10
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_0_SHFT                                           4
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_1_BMSK                                            0x8
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_1_SHFT                                              3
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_0_BMSK                                            0x4
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_0_SHFT                                              2
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_1_BMSK                                          0x2
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_1_SHFT                                            1
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_0_BMSK                                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_0_SHFT                                            0

#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR                                                     (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2210)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_RMSK                                                      0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_1_BMSK                         0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_1_SHFT                                25
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_0_BMSK                         0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_0_SHFT                                24
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_1_BMSK                            0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_1_SHFT                                  23
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_0_BMSK                            0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_0_SHFT                                  22
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WPSS_PDC_AOP_IRQ_STATUS_1_BMSK                             0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WPSS_PDC_AOP_IRQ_STATUS_1_SHFT                                   21
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WPSS_PDC_AOP_IRQ_STATUS_0_BMSK                             0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WPSS_PDC_AOP_IRQ_STATUS_0_SHFT                                   20
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_1_BMSK                               0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_1_SHFT                                    19
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_0_BMSK                               0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_0_SHFT                                    18
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_1_BMSK                           0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_1_SHFT                                17
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_0_BMSK                           0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_0_SHFT                                16
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_1_BMSK                            0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_1_SHFT                                15
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_0_BMSK                            0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_0_SHFT                                14
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_1_BMSK                                0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_1_SHFT                                    13
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_0_BMSK                                0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_0_SHFT                                    12
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_1_BMSK                               0x800
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_1_SHFT                                  11
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_0_BMSK                               0x400
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_0_SHFT                                  10
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_1_BMSK                                 0x200
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_1_SHFT                                     9
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_0_BMSK                                 0x100
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_0_SHFT                                     8
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_STATUS_1_BMSK                              0x80
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_STATUS_1_SHFT                                 7
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_STATUS_0_BMSK                              0x40
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_STATUS_0_SHFT                                 6
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_1_BMSK                                0x20
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_1_SHFT                                   5
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_0_BMSK                                0x10
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_0_SHFT                                   4
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_1_BMSK                                    0x8
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_1_SHFT                                      3
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_0_BMSK                                    0x4
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_0_SHFT                                      2
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_1_BMSK                                  0x2
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_1_SHFT                                    1
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_0_BMSK                                  0x1
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_0_SHFT                                    0

#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2214)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_RMSK                                                  0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                 0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                        25
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                 0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                        24
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                    0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                          23
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                    0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                          22
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WPSS_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                     0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WPSS_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                           21
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WPSS_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                     0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WPSS_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                           20
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                       0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                            19
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                       0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                            18
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                   0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                        17
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                   0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                        16
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                    0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                        15
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                    0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                        14
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                        0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                            13
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                        0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                            12
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                       0x800
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                          11
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                       0x400
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                          10
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                         0x200
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                             9
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                         0x100
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                             8
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                      0x80
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                         7
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                      0x40
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SENSORS_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                         6
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                        0x20
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                           5
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                        0x10
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                           4
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                            0x8
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                              3
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                            0x4
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                              2
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                          0x2
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                            1
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                            0

#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR                                                      (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2218)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_RMSK                                                       0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_1_BMSK                           0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_1_SHFT                                  25
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_0_BMSK                           0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_0_SHFT                                  24
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_1_BMSK                              0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_1_SHFT                                    23
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_0_BMSK                              0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_0_SHFT                                    22
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WPSS_PDC_AOP_IRQ_CLEAR_1_BMSK                               0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WPSS_PDC_AOP_IRQ_CLEAR_1_SHFT                                     21
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WPSS_PDC_AOP_IRQ_CLEAR_0_BMSK                               0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WPSS_PDC_AOP_IRQ_CLEAR_0_SHFT                                     20
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_1_BMSK                                 0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_1_SHFT                                      19
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_0_BMSK                                 0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_0_SHFT                                      18
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_1_BMSK                             0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_1_SHFT                                  17
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_0_BMSK                             0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_0_SHFT                                  16
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_1_BMSK                              0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_1_SHFT                                  15
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_0_BMSK                              0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_0_SHFT                                  14
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_1_BMSK                                  0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_1_SHFT                                      13
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_0_BMSK                                  0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_0_SHFT                                      12
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_1_BMSK                                 0x800
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_1_SHFT                                    11
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_0_BMSK                                 0x400
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_0_SHFT                                    10
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_1_BMSK                                   0x200
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_1_SHFT                                       9
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_0_BMSK                                   0x100
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_0_SHFT                                       8
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SENSORS_PDC_AOP_IRQ_CLEAR_1_BMSK                                0x80
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SENSORS_PDC_AOP_IRQ_CLEAR_1_SHFT                                   7
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SENSORS_PDC_AOP_IRQ_CLEAR_0_BMSK                                0x40
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SENSORS_PDC_AOP_IRQ_CLEAR_0_SHFT                                   6
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_1_BMSK                                  0x20
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_1_SHFT                                     5
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_0_BMSK                                  0x10
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_0_SHFT                                     4
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_1_BMSK                                      0x8
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_1_SHFT                                        3
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_0_BMSK                                      0x4
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_0_SHFT                                        2
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_1_BMSK                                    0x2
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_1_SHFT                                      1
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_0_BMSK                                    0x1
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_0_SHFT                                      0

#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR                                                     (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2220)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_RMSK                                                      0x3ffffff
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_1_BMSK                         0x2000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_1_SHFT                                25
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_0_BMSK                         0x1000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_0_SHFT                                24
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_1_BMSK                            0x800000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_1_SHFT                                  23
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_0_BMSK                            0x400000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_0_SHFT                                  22
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WPSS_PDC_AOP_SEQ_RESUME_1_BMSK                             0x200000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WPSS_PDC_AOP_SEQ_RESUME_1_SHFT                                   21
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WPSS_PDC_AOP_SEQ_RESUME_0_BMSK                             0x100000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WPSS_PDC_AOP_SEQ_RESUME_0_SHFT                                   20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_1_BMSK                               0x80000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_1_SHFT                                    19
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_0_BMSK                               0x40000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_0_SHFT                                    18
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_1_BMSK                           0x20000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_1_SHFT                                17
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_0_BMSK                           0x10000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_0_SHFT                                16
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_1_BMSK                            0x8000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_1_SHFT                                15
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_0_BMSK                            0x4000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_0_SHFT                                14
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_1_BMSK                                0x2000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_1_SHFT                                    13
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_0_BMSK                                0x1000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_0_SHFT                                    12
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_1_BMSK                               0x800
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_1_SHFT                                  11
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_0_BMSK                               0x400
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_0_SHFT                                  10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_1_BMSK                                 0x200
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_1_SHFT                                     9
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_0_BMSK                                 0x100
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_0_SHFT                                     8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_1_BMSK                              0x80
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_1_SHFT                                 7
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_0_BMSK                              0x40
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_0_SHFT                                 6
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_1_BMSK                                0x20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_1_SHFT                                   5
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_0_BMSK                                0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_0_SHFT                                   4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_1_BMSK                                    0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_1_SHFT                                      3
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_0_BMSK                                    0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_0_SHFT                                      2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_1_BMSK                                  0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_1_SHFT                                    1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_0_BMSK                                  0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_0_SHFT                                    0

#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2230)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_RMSK                                                 0x3ffffff
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK               0x2000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                      25
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK               0x1000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                      24
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                  0x800000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                        23
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                  0x400000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                        22
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WPSS_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                   0x200000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WPSS_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                         21
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WPSS_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                   0x100000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WPSS_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                         20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                     0x80000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                          19
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                     0x40000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                          18
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                 0x20000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                      17
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                 0x10000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                      16
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                  0x8000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                      15
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                  0x4000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                      14
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                      0x2000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                          13
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                      0x1000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                          12
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                     0x800
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                        11
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                     0x400
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                        10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                       0x200
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                           9
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                       0x100
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                           8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                    0x80
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                       7
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                    0x40
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SENSORS_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                       6
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                      0x20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                         5
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                      0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                         4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                          0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                            3
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                          0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                            2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                        0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                          1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                        0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                          0

#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2300)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_RMSK                                                    0x1fff
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_RF_SOC_SLEEP_LOCK_MASK_BMSK                        0x1000
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_RF_SOC_SLEEP_LOCK_MASK_SHFT                            12
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_MODEM_SOC_SLEEP_LOCK_MASK_BMSK                           0x800
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_MODEM_SOC_SLEEP_LOCK_MASK_SHFT                              11
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WPSS_SOC_SLEEP_LOCK_MASK_BMSK                            0x400
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WPSS_SOC_SLEEP_LOCK_MASK_SHFT                               10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_TME_SOC_SLEEP_LOCK_MASK_BMSK                             0x200
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_TME_SOC_SLEEP_LOCK_MASK_SHFT                                 9
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_COMPUTE_SOC_SLEEP_LOCK_MASK_BMSK                         0x100
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_COMPUTE_SOC_SLEEP_LOCK_MASK_SHFT                             8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DISPLAY_SOC_SLEEP_LOCK_MASK_BMSK                          0x80
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DISPLAY_SOC_SLEEP_LOCK_MASK_SHFT                             7
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_GPU_SOC_SLEEP_LOCK_MASK_BMSK                              0x40
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_GPU_SOC_SLEEP_LOCK_MASK_SHFT                                 6
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DEBUG_SOC_SLEEP_LOCK_MASK_BMSK                            0x20
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DEBUG_SOC_SLEEP_LOCK_MASK_SHFT                               5
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AOP_SOC_SLEEP_LOCK_MASK_BMSK                              0x10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AOP_SOC_SLEEP_LOCK_MASK_SHFT                                 4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SENSORS_SOC_SLEEP_LOCK_MASK_BMSK                           0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SENSORS_SOC_SLEEP_LOCK_MASK_SHFT                             3
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AUDIO_SOC_SLEEP_LOCK_MASK_BMSK                             0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AUDIO_SOC_SLEEP_LOCK_MASK_SHFT                               2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SP_SOC_SLEEP_LOCK_MASK_BMSK                                0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SP_SOC_SLEEP_LOCK_MASK_SHFT                                  1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_APPS_SOC_SLEEP_LOCK_MASK_BMSK                              0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_APPS_SOC_SLEEP_LOCK_MASK_SHFT                                0

#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR                                              (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2310)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_RMSK                                                  0x1fff
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_RF_SOC_SLEEP_LOCK_STATUS_BMSK                    0x1000
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_RF_SOC_SLEEP_LOCK_STATUS_SHFT                        12
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_MODEM_SOC_SLEEP_LOCK_STATUS_BMSK                       0x800
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_MODEM_SOC_SLEEP_LOCK_STATUS_SHFT                          11
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WPSS_SOC_SLEEP_LOCK_STATUS_BMSK                        0x400
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WPSS_SOC_SLEEP_LOCK_STATUS_SHFT                           10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_TME_SOC_SLEEP_LOCK_STATUS_BMSK                         0x200
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_TME_SOC_SLEEP_LOCK_STATUS_SHFT                             9
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_COMPUTE_SOC_SLEEP_LOCK_STATUS_BMSK                     0x100
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_COMPUTE_SOC_SLEEP_LOCK_STATUS_SHFT                         8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DISPLAY_SOC_SLEEP_LOCK_STATUS_BMSK                      0x80
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DISPLAY_SOC_SLEEP_LOCK_STATUS_SHFT                         7
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_GPU_SOC_SLEEP_LOCK_STATUS_BMSK                          0x40
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_GPU_SOC_SLEEP_LOCK_STATUS_SHFT                             6
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DEBUG_SOC_SLEEP_LOCK_STATUS_BMSK                        0x20
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DEBUG_SOC_SLEEP_LOCK_STATUS_SHFT                           5
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AOP_SOC_SLEEP_LOCK_STATUS_BMSK                          0x10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AOP_SOC_SLEEP_LOCK_STATUS_SHFT                             4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SENSORS_SOC_SLEEP_LOCK_STATUS_BMSK                       0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SENSORS_SOC_SLEEP_LOCK_STATUS_SHFT                         3
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AUDIO_SOC_SLEEP_LOCK_STATUS_BMSK                         0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AUDIO_SOC_SLEEP_LOCK_STATUS_SHFT                           2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SP_SOC_SLEEP_LOCK_STATUS_BMSK                            0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SP_SOC_SLEEP_LOCK_STATUS_SHFT                              1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_APPS_SOC_SLEEP_LOCK_STATUS_BMSK                          0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_APPS_SOC_SLEEP_LOCK_STATUS_SHFT                            0

#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR                                              (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2320)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_RMSK                                                  0x1fff
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_MASK_BMSK                    0x1000
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_MASK_SHFT                        12
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_MODEM_CX_COLLAPSE_LOCK_MASK_BMSK                       0x800
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_MODEM_CX_COLLAPSE_LOCK_MASK_SHFT                          11
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WPSS_CX_COLLAPSE_LOCK_MASK_BMSK                        0x400
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WPSS_CX_COLLAPSE_LOCK_MASK_SHFT                           10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_TME_CX_COLLAPSE_LOCK_MASK_BMSK                         0x200
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_TME_CX_COLLAPSE_LOCK_MASK_SHFT                             9
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_COMPUTE_CX_COLLAPSE_LOCK_MASK_BMSK                     0x100
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_COMPUTE_CX_COLLAPSE_LOCK_MASK_SHFT                         8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DISPLAY_CX_COLLAPSE_LOCK_MASK_BMSK                      0x80
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DISPLAY_CX_COLLAPSE_LOCK_MASK_SHFT                         7
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_GPU_CX_COLLAPSE_LOCK_MASK_BMSK                          0x40
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_GPU_CX_COLLAPSE_LOCK_MASK_SHFT                             6
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DEBUG_CX_COLLAPSE_LOCK_MASK_BMSK                        0x20
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DEBUG_CX_COLLAPSE_LOCK_MASK_SHFT                           5
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AOP_CX_COLLAPSE_LOCK_MASK_BMSK                          0x10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AOP_CX_COLLAPSE_LOCK_MASK_SHFT                             4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SENSORS_CX_COLLAPSE_LOCK_MASK_BMSK                       0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SENSORS_CX_COLLAPSE_LOCK_MASK_SHFT                         3
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AUDIO_CX_COLLAPSE_LOCK_MASK_BMSK                         0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AUDIO_CX_COLLAPSE_LOCK_MASK_SHFT                           2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SP_CX_COLLAPSE_LOCK_MASK_BMSK                            0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SP_CX_COLLAPSE_LOCK_MASK_SHFT                              1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_APPS_CX_COLLAPSE_LOCK_MASK_BMSK                          0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_APPS_CX_COLLAPSE_LOCK_MASK_SHFT                            0

#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR                                            (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2330)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_RMSK                                                0x1fff
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_STATUS_BMSK                0x1000
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_STATUS_SHFT                    12
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_MODEM_CX_COLLAPSE_LOCK_STATUS_BMSK                   0x800
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_MODEM_CX_COLLAPSE_LOCK_STATUS_SHFT                      11
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WPSS_CX_COLLAPSE_LOCK_STATUS_BMSK                    0x400
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WPSS_CX_COLLAPSE_LOCK_STATUS_SHFT                       10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_TME_CX_COLLAPSE_LOCK_STATUS_BMSK                     0x200
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_TME_CX_COLLAPSE_LOCK_STATUS_SHFT                         9
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_COMPUTE_CX_COLLAPSE_LOCK_STATUS_BMSK                 0x100
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_COMPUTE_CX_COLLAPSE_LOCK_STATUS_SHFT                     8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DISPLAY_CX_COLLAPSE_LOCK_STATUS_BMSK                  0x80
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DISPLAY_CX_COLLAPSE_LOCK_STATUS_SHFT                     7
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_GPU_CX_COLLAPSE_LOCK_STATUS_BMSK                      0x40
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_GPU_CX_COLLAPSE_LOCK_STATUS_SHFT                         6
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DEBUG_CX_COLLAPSE_LOCK_STATUS_BMSK                    0x20
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DEBUG_CX_COLLAPSE_LOCK_STATUS_SHFT                       5
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AOP_CX_COLLAPSE_LOCK_STATUS_BMSK                      0x10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AOP_CX_COLLAPSE_LOCK_STATUS_SHFT                         4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SENSORS_CX_COLLAPSE_LOCK_STATUS_BMSK                   0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SENSORS_CX_COLLAPSE_LOCK_STATUS_SHFT                     3
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AUDIO_CX_COLLAPSE_LOCK_STATUS_BMSK                     0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AUDIO_CX_COLLAPSE_LOCK_STATUS_SHFT                       2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SP_CX_COLLAPSE_LOCK_STATUS_BMSK                        0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SP_CX_COLLAPSE_LOCK_STATUS_SHFT                          1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_APPS_CX_COLLAPSE_LOCK_STATUS_BMSK                      0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_APPS_CX_COLLAPSE_LOCK_STATUS_SHFT                        0

#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2340)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_RMSK                                                 0x1fff
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_MASK_BMSK                  0x1000
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_MASK_SHFT                      12
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_MODEM_DBG_RSRC_REL_LOCK_MASK_BMSK                     0x800
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_MODEM_DBG_RSRC_REL_LOCK_MASK_SHFT                        11
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WPSS_DBG_RSRC_REL_LOCK_MASK_BMSK                      0x400
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WPSS_DBG_RSRC_REL_LOCK_MASK_SHFT                         10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_TME_DBG_RSRC_REL_LOCK_MASK_BMSK                       0x200
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_TME_DBG_RSRC_REL_LOCK_MASK_SHFT                           9
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_MASK_BMSK                   0x100
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_MASK_SHFT                       8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_MASK_BMSK                    0x80
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_MASK_SHFT                       7
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_GPU_DBG_RSRC_REL_LOCK_MASK_BMSK                        0x40
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_GPU_DBG_RSRC_REL_LOCK_MASK_SHFT                           6
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DEBUG_DBG_RSRC_REL_LOCK_MASK_BMSK                      0x20
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DEBUG_DBG_RSRC_REL_LOCK_MASK_SHFT                         5
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AOP_DBG_RSRC_REL_LOCK_MASK_BMSK                        0x10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AOP_DBG_RSRC_REL_LOCK_MASK_SHFT                           4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SENSORS_DBG_RSRC_REL_LOCK_MASK_BMSK                     0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SENSORS_DBG_RSRC_REL_LOCK_MASK_SHFT                       3
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AUDIO_DBG_RSRC_REL_LOCK_MASK_BMSK                       0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AUDIO_DBG_RSRC_REL_LOCK_MASK_SHFT                         2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SP_DBG_RSRC_REL_LOCK_MASK_BMSK                          0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SP_DBG_RSRC_REL_LOCK_MASK_SHFT                            1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_APPS_DBG_RSRC_REL_LOCK_MASK_BMSK                        0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_APPS_DBG_RSRC_REL_LOCK_MASK_SHFT                          0

#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR                                           (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2350)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_RMSK                                               0x1fff
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_IN                    \
                in_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_STATUS_BMSK              0x1000
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_STATUS_SHFT                  12
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_MODEM_DBG_RSRC_REL_LOCK_STATUS_BMSK                 0x800
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_MODEM_DBG_RSRC_REL_LOCK_STATUS_SHFT                    11
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WPSS_DBG_RSRC_REL_LOCK_STATUS_BMSK                  0x400
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WPSS_DBG_RSRC_REL_LOCK_STATUS_SHFT                     10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_TME_DBG_RSRC_REL_LOCK_STATUS_BMSK                   0x200
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_TME_DBG_RSRC_REL_LOCK_STATUS_SHFT                       9
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_STATUS_BMSK               0x100
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_STATUS_SHFT                   8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_STATUS_BMSK                0x80
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_STATUS_SHFT                   7
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_GPU_DBG_RSRC_REL_LOCK_STATUS_BMSK                    0x40
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_GPU_DBG_RSRC_REL_LOCK_STATUS_SHFT                       6
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DEBUG_DBG_RSRC_REL_LOCK_STATUS_BMSK                  0x20
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DEBUG_DBG_RSRC_REL_LOCK_STATUS_SHFT                     5
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AOP_DBG_RSRC_REL_LOCK_STATUS_BMSK                    0x10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AOP_DBG_RSRC_REL_LOCK_STATUS_SHFT                       4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SENSORS_DBG_RSRC_REL_LOCK_STATUS_BMSK                 0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SENSORS_DBG_RSRC_REL_LOCK_STATUS_SHFT                   3
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AUDIO_DBG_RSRC_REL_LOCK_STATUS_BMSK                   0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AUDIO_DBG_RSRC_REL_LOCK_STATUS_SHFT                     2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SP_DBG_RSRC_REL_LOCK_STATUS_BMSK                      0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SP_DBG_RSRC_REL_LOCK_STATUS_SHFT                        1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_APPS_DBG_RSRC_REL_LOCK_STATUS_BMSK                    0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_APPS_DBG_RSRC_REL_LOCK_STATUS_SHFT                      0

#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR                                                          (RPMH_PDC_PDC_GLOBAL_REG_BASE            + 0x2400)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_RMSK                                                               0x101
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_IN                    \
                in_dword(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_INM(m)            \
                in_dword_masked(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR, m)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_OUT(v)            \
                out_dword(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR,v)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR,m,v,HWIO_RPMH_PDC_DBG_BUS_CONTROL_IN)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_GLOBAL_COUNTER_MASK_BMSK                                   0x100
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_GLOBAL_COUNTER_MASK_SHFT                                       8
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_ENABLE_BMSK                                                  0x1
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_ENABLE_SHFT                                                    0


#endif /* __PDC_GLOBAL_HWIO_H__ */
