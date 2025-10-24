#ifndef __PDC_GLOBAL_HWIO_H__
#define __PDC_GLOBAL_HWIO_H__
/*
===========================================================================
*/
/**
  @file pdc_global_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPMH_PDC_PDC_GLOBAL


  Generation parameters: 
  { u'filename': u'pdc_global_hwio.h',
    u'header': u'#include "msmhwiobase.h"',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [u'RPMH_PDC_PDC_GLOBAL']}
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

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/power/pdc/global/hal/hwio/kailua/pdc_global_hwio.h#1 $
  $DateTime: 2021/10/26 22:03:12 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: RPMH_PDC_PDC_GLOBAL
 *--------------------------------------------------------------------------*/

#define RPMH_PDC_PDC_GLOBAL_REG_BASE                                                                (AOSS_BASE      + 0x005e0000)
#define RPMH_PDC_PDC_GLOBAL_REG_BASE_SIZE                                                           0x10000
#define RPMH_PDC_PDC_GLOBAL_REG_BASE_USED                                                           0x2920

#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d)                                                  (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000020 + 0x4 * (d))
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_RMSK                                                           0x1f
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_MAXd                                                              3
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_APPS_DRV_ID_BMSK                                               0x1f
#define HWIO_RPMH_PDC_APPS_PDC_RSC_DRV_IDd_APPS_DRV_ID_SHFT                                                0x0

#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d)                                                    (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000060 + 0x4 * (d))
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_RMSK                                                             0x1f
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_MAXd                                                                0
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_SP_DRV_ID_BMSK                                                   0x1f
#define HWIO_RPMH_PDC_SP_PDC_RSC_DRV_IDd_SP_DRV_ID_SHFT                                                    0x0

#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000070 + 0x4 * (d))
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_MAXd                                                             0
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_AUDIO_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_AUDIO_PDC_RSC_DRV_IDd_AUDIO_DRV_ID_SHFT                                              0x0

#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000080 + 0x4 * (d))
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_MAXd                                                               0
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_AOP_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_AOP_PDC_RSC_DRV_IDd_AOP_DRV_ID_SHFT                                                  0x0

#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000090 + 0x4 * (d))
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_MAXd                                                             0
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_DEBUG_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_DEBUG_PDC_RSC_DRV_IDd_DEBUG_DRV_ID_SHFT                                              0x0

#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x000000a0 + 0x4 * (d))
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_MAXd                                                               0
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_GPU_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_GPU_PDC_RSC_DRV_IDd_GPU_DRV_ID_SHFT                                                  0x0

#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x000000b0 + 0x4 * (d))
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_DISPLAY_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_DISPLAY_PDC_RSC_DRV_IDd_DISPLAY_DRV_ID_SHFT                                          0x0

#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x000000c0 + 0x4 * (d))
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_COMPUTE_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_COMPUTE_PDC_RSC_DRV_IDd_COMPUTE_DRV_ID_SHFT                                          0x0

#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x000000d0 + 0x4 * (d))
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_MAXd                                                               1
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_TME_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_TME_PDC_RSC_DRV_IDd_TME_DRV_ID_SHFT                                                  0x0

#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d)                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x000000f0 + 0x4 * (d))
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_RMSK                                                          0x1f
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MAXd                                                             1
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MODEM_DRV_ID_BMSK                                             0x1f
#define HWIO_RPMH_PDC_MODEM_PDC_RSC_DRV_IDd_MODEM_DRV_ID_SHFT                                              0x0

#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000110 + 0x4 * (d))
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_WLAN_RF_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_WLAN_RF_PDC_RSC_DRV_IDd_WLAN_RF_DRV_ID_SHFT                                          0x0

#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_ADDR(d)                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000120 + 0x4 * (d))
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_RMSK                                                        0x1f
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_MAXd                                                           0
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_WLAN_BB_DRV_ID_BMSK                                         0x1f
#define HWIO_RPMH_PDC_WLAN_BB_PDC_RSC_DRV_IDd_WLAN_BB_DRV_ID_SHFT                                          0x0

#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00000130 + 0x4 * (d))
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_RMSK                                                            0x1f
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_MAXd                                                               2
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_ADDR(d), HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_RMSK)
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_ADDR(d), mask)
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_ADDR(d),val)
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_ADDR(d),mask,val,HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_INI(d))
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_CAM_DRV_ID_BMSK                                                 0x1f
#define HWIO_RPMH_PDC_CAM_PDC_RSC_DRV_IDd_CAM_DRV_ID_SHFT                                                  0x0

#define HWIO_RPMH_PDC_SYNC_RESET_ADDR                                                               (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00001000)
#define HWIO_RPMH_PDC_SYNC_RESET_RMSK                                                                   0x1fff
#define HWIO_RPMH_PDC_SYNC_RESET_IN          \
        in_dword(HWIO_RPMH_PDC_SYNC_RESET_ADDR)
#define HWIO_RPMH_PDC_SYNC_RESET_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_SYNC_RESET_ADDR, m)
#define HWIO_RPMH_PDC_SYNC_RESET_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_SYNC_RESET_ADDR,v)
#define HWIO_RPMH_PDC_SYNC_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_SYNC_RESET_ADDR,m,v,HWIO_RPMH_PDC_SYNC_RESET_IN)
#define HWIO_RPMH_PDC_SYNC_RESET_CAM_SYNC_RESET_BMSK                                                    0x1000
#define HWIO_RPMH_PDC_SYNC_RESET_CAM_SYNC_RESET_SHFT                                                       0xc
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_BB_SYNC_RESET_BMSK                                                 0x800
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_BB_SYNC_RESET_SHFT                                                   0xb
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_RF_SYNC_RESET_BMSK                                                 0x400
#define HWIO_RPMH_PDC_SYNC_RESET_WLAN_RF_SYNC_RESET_SHFT                                                   0xa
#define HWIO_RPMH_PDC_SYNC_RESET_MODEM_SYNC_RESET_BMSK                                                   0x200
#define HWIO_RPMH_PDC_SYNC_RESET_MODEM_SYNC_RESET_SHFT                                                     0x9
#define HWIO_RPMH_PDC_SYNC_RESET_TME_SYNC_RESET_BMSK                                                     0x100
#define HWIO_RPMH_PDC_SYNC_RESET_TME_SYNC_RESET_SHFT                                                       0x8
#define HWIO_RPMH_PDC_SYNC_RESET_COMPUTE_SYNC_RESET_BMSK                                                  0x80
#define HWIO_RPMH_PDC_SYNC_RESET_COMPUTE_SYNC_RESET_SHFT                                                   0x7
#define HWIO_RPMH_PDC_SYNC_RESET_DISPLAY_SYNC_RESET_BMSK                                                  0x40
#define HWIO_RPMH_PDC_SYNC_RESET_DISPLAY_SYNC_RESET_SHFT                                                   0x6
#define HWIO_RPMH_PDC_SYNC_RESET_GPU_SYNC_RESET_BMSK                                                      0x20
#define HWIO_RPMH_PDC_SYNC_RESET_GPU_SYNC_RESET_SHFT                                                       0x5
#define HWIO_RPMH_PDC_SYNC_RESET_DEBUG_SYNC_RESET_BMSK                                                    0x10
#define HWIO_RPMH_PDC_SYNC_RESET_DEBUG_SYNC_RESET_SHFT                                                     0x4
#define HWIO_RPMH_PDC_SYNC_RESET_AOP_SYNC_RESET_BMSK                                                       0x8
#define HWIO_RPMH_PDC_SYNC_RESET_AOP_SYNC_RESET_SHFT                                                       0x3
#define HWIO_RPMH_PDC_SYNC_RESET_AUDIO_SYNC_RESET_BMSK                                                     0x4
#define HWIO_RPMH_PDC_SYNC_RESET_AUDIO_SYNC_RESET_SHFT                                                     0x2
#define HWIO_RPMH_PDC_SYNC_RESET_SP_SYNC_RESET_BMSK                                                        0x2
#define HWIO_RPMH_PDC_SYNC_RESET_SP_SYNC_RESET_SHFT                                                        0x1
#define HWIO_RPMH_PDC_SYNC_RESET_APPS_SYNC_RESET_BMSK                                                      0x1
#define HWIO_RPMH_PDC_SYNC_RESET_APPS_SYNC_RESET_SHFT                                                      0x0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00001400)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_RMSK                                                       0xffff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_IN          \
        in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_EPCB_TIMEOUT_THRESHOLD_BMSK                                0xffff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_THRESHOLD_EPCB_TIMEOUT_THRESHOLD_SHFT                                   0x0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00001500)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_RMSK                                                    0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_CAM_EPCB_TIMEOUT_IRQ_EN_BMSK                            0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_CAM_EPCB_TIMEOUT_IRQ_EN_SHFT                               0xc
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_EN_BMSK                         0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_EN_SHFT                           0xb
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_EN_BMSK                         0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_EN_SHFT                           0xa
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_MODEM_EPCB_TIMEOUT_IRQ_EN_BMSK                           0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_MODEM_EPCB_TIMEOUT_IRQ_EN_SHFT                             0x9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_TME_EPCB_TIMEOUT_IRQ_EN_BMSK                             0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_TME_EPCB_TIMEOUT_IRQ_EN_SHFT                               0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_EN_BMSK                          0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_EN_SHFT                           0x7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_EN_BMSK                          0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_EN_SHFT                           0x6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_GPU_EPCB_TIMEOUT_IRQ_EN_BMSK                              0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_GPU_EPCB_TIMEOUT_IRQ_EN_SHFT                               0x5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_EN_BMSK                            0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_EN_SHFT                             0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AOP_EPCB_TIMEOUT_IRQ_EN_BMSK                               0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AOP_EPCB_TIMEOUT_IRQ_EN_SHFT                               0x3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_EN_BMSK                             0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_EN_SHFT                             0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SP_EPCB_TIMEOUT_IRQ_EN_BMSK                                0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_SP_EPCB_TIMEOUT_IRQ_EN_SHFT                                0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_APPS_EPCB_TIMEOUT_IRQ_EN_BMSK                              0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_EN_BANK0_APPS_EPCB_TIMEOUT_IRQ_EN_SHFT                              0x0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR                                            (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00001600)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_RMSK                                                0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_CAM_EPCB_TIMEOUT_IRQ_STATUS_BMSK                    0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_CAM_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       0xc
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_STATUS_BMSK                 0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_STATUS_SHFT                   0xb
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_STATUS_BMSK                 0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_STATUS_SHFT                   0xa
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_MODEM_EPCB_TIMEOUT_IRQ_STATUS_BMSK                   0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_MODEM_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     0x9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_TME_EPCB_TIMEOUT_IRQ_STATUS_BMSK                     0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_TME_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_STATUS_BMSK                  0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_STATUS_SHFT                   0x7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_STATUS_BMSK                  0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_STATUS_SHFT                   0x6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_GPU_EPCB_TIMEOUT_IRQ_STATUS_BMSK                      0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_GPU_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       0x5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_STATUS_BMSK                    0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AOP_EPCB_TIMEOUT_IRQ_STATUS_BMSK                       0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AOP_EPCB_TIMEOUT_IRQ_STATUS_SHFT                       0x3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_STATUS_BMSK                     0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_STATUS_SHFT                     0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SP_EPCB_TIMEOUT_IRQ_STATUS_BMSK                        0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_SP_EPCB_TIMEOUT_IRQ_STATUS_SHFT                        0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_APPS_EPCB_TIMEOUT_IRQ_STATUS_BMSK                      0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_STATUS_BANK0_APPS_EPCB_TIMEOUT_IRQ_STATUS_SHFT                      0x0

#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00001700)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_RMSK                                                 0x1fff
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_ADDR,m,v,HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_IN)
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_CAM_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                      0x1000
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_CAM_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         0xc
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                   0x800
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_BB_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                     0xb
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                   0x400
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_WLAN_RF_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                     0xa
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_MODEM_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                     0x200
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_MODEM_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       0x9
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_TME_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                       0x100
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_TME_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                    0x80
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_COMPUTE_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                     0x7
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                    0x40
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DISPLAY_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                     0x6
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_GPU_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                        0x20
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_GPU_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         0x5
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                      0x10
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_DEBUG_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AOP_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                         0x8
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AOP_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                         0x3
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                       0x4
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_AUDIO_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                       0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SP_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                          0x2
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_SP_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                          0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_APPS_EPCB_TIMEOUT_IRQ_CLEAR_BMSK                        0x1
#define HWIO_RPMH_PDC_EPCB_TIMEOUT_IRQ_CLEAR_BANK0_APPS_EPCB_TIMEOUT_IRQ_CLEAR_SHFT                        0x0

#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002200)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_RMSK                                                          0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_CAM_PDC_AOP_IRQ_EN_1_BMSK                                     0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_CAM_PDC_AOP_IRQ_EN_1_SHFT                                          0x19
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_CAM_PDC_AOP_IRQ_EN_0_BMSK                                     0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_CAM_PDC_AOP_IRQ_EN_0_SHFT                                          0x18
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_BB_PDC_AOP_IRQ_EN_1_BMSK                                  0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_BB_PDC_AOP_IRQ_EN_1_SHFT                                      0x17
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_BB_PDC_AOP_IRQ_EN_0_BMSK                                  0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_BB_PDC_AOP_IRQ_EN_0_SHFT                                      0x16
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_1_BMSK                                  0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_1_SHFT                                      0x15
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_0_BMSK                                  0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_WLAN_RF_PDC_AOP_IRQ_EN_0_SHFT                                      0x14
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_1_BMSK                                     0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_1_SHFT                                        0x13
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_0_BMSK                                     0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_MODEM_PDC_AOP_IRQ_EN_0_SHFT                                        0x12
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_1_BMSK                                       0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_1_SHFT                                          0x11
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_0_BMSK                                       0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_TME_PDC_AOP_IRQ_EN_0_SHFT                                          0x10
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_1_BMSK                                    0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_1_SHFT                                       0xf
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_0_BMSK                                    0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_COMPUTE_PDC_AOP_IRQ_EN_0_SHFT                                       0xe
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_1_BMSK                                    0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_1_SHFT                                       0xd
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_0_BMSK                                    0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DISPLAY_PDC_AOP_IRQ_EN_0_SHFT                                       0xc
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_1_BMSK                                         0x800
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_1_SHFT                                           0xb
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_0_BMSK                                         0x400
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_GPU_PDC_AOP_IRQ_EN_0_SHFT                                           0xa
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_1_BMSK                                       0x200
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_1_SHFT                                         0x9
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_0_BMSK                                       0x100
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_DEBUG_PDC_AOP_IRQ_EN_0_SHFT                                         0x8
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_1_BMSK                                          0x80
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_1_SHFT                                           0x7
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_0_BMSK                                          0x40
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AOP_PDC_AOP_IRQ_EN_0_SHFT                                           0x6
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_1_BMSK                                        0x20
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_1_SHFT                                         0x5
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_0_BMSK                                        0x10
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_AUDIO_PDC_AOP_IRQ_EN_0_SHFT                                         0x4
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_1_BMSK                                            0x8
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_1_SHFT                                            0x3
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_0_BMSK                                            0x4
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_SP_PDC_AOP_IRQ_EN_0_SHFT                                            0x2
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_1_BMSK                                          0x2
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_1_SHFT                                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_0_BMSK                                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_EN_BANK0_APPS_PDC_AOP_IRQ_EN_0_SHFT                                          0x0

#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR                                                     (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002210)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_RMSK                                                      0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_CAM_PDC_AOP_IRQ_STATUS_1_BMSK                             0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_CAM_PDC_AOP_IRQ_STATUS_1_SHFT                                  0x19
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_CAM_PDC_AOP_IRQ_STATUS_0_BMSK                             0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_CAM_PDC_AOP_IRQ_STATUS_0_SHFT                                  0x18
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_STATUS_1_BMSK                          0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_STATUS_1_SHFT                              0x17
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_STATUS_0_BMSK                          0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_STATUS_0_SHFT                              0x16
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_1_BMSK                          0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_1_SHFT                              0x15
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_0_BMSK                          0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_STATUS_0_SHFT                              0x14
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_1_BMSK                             0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_1_SHFT                                0x13
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_0_BMSK                             0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_MODEM_PDC_AOP_IRQ_STATUS_0_SHFT                                0x12
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_1_BMSK                               0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_1_SHFT                                  0x11
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_0_BMSK                               0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_TME_PDC_AOP_IRQ_STATUS_0_SHFT                                  0x10
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_1_BMSK                            0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_1_SHFT                               0xf
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_0_BMSK                            0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_STATUS_0_SHFT                               0xe
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_1_BMSK                            0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_1_SHFT                               0xd
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_0_BMSK                            0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_STATUS_0_SHFT                               0xc
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_1_BMSK                                 0x800
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_1_SHFT                                   0xb
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_0_BMSK                                 0x400
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_GPU_PDC_AOP_IRQ_STATUS_0_SHFT                                   0xa
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_1_BMSK                               0x200
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_1_SHFT                                 0x9
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_0_BMSK                               0x100
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_STATUS_0_SHFT                                 0x8
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_1_BMSK                                  0x80
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_1_SHFT                                   0x7
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_0_BMSK                                  0x40
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AOP_PDC_AOP_IRQ_STATUS_0_SHFT                                   0x6
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_1_BMSK                                0x20
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_1_SHFT                                 0x5
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_0_BMSK                                0x10
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_STATUS_0_SHFT                                 0x4
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_1_BMSK                                    0x8
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_1_SHFT                                    0x3
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_0_BMSK                                    0x4
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_SP_PDC_AOP_IRQ_STATUS_0_SHFT                                    0x2
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_1_BMSK                                  0x2
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_1_SHFT                                  0x1
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_0_BMSK                                  0x1
#define HWIO_RPMH_PDC_AOP_IRQ_STATUS_BANK0_APPS_PDC_AOP_IRQ_STATUS_0_SHFT                                  0x0

#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002214)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_RMSK                                                  0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_CAM_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                     0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_CAM_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                          0x19
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_CAM_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                     0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_CAM_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                          0x18
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                  0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                      0x17
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                  0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_BB_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                      0x16
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                  0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                      0x15
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                  0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_WLAN_RF_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                      0x14
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                     0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                        0x13
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                     0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_MODEM_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                        0x12
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                       0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                          0x11
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                       0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_TME_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                          0x10
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                    0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                       0xf
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                    0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_COMPUTE_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                       0xe
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                    0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                       0xd
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                    0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DISPLAY_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                       0xc
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                         0x800
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                           0xb
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                         0x400
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_GPU_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                           0xa
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                       0x200
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                         0x9
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                       0x100
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_DEBUG_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                         0x8
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                          0x80
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                           0x7
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                          0x40
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AOP_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                           0x6
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                        0x20
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                         0x5
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                        0x10
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_AUDIO_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                         0x4
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                            0x8
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                            0x3
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                            0x4
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_SP_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                            0x2
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_1_BMSK                          0x2
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_1_SHFT                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_0_BMSK                          0x1
#define HWIO_RPMH_PDC_AOP_IRQ_RAW_STATUS_BANK0_APPS_PDC_AOP_IRQ_RAW_STATUS_0_SHFT                          0x0

#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR                                                      (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002218)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_RMSK                                                       0x3ffffff
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_CAM_PDC_AOP_IRQ_CLEAR_1_BMSK                               0x2000000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_CAM_PDC_AOP_IRQ_CLEAR_1_SHFT                                    0x19
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_CAM_PDC_AOP_IRQ_CLEAR_0_BMSK                               0x1000000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_CAM_PDC_AOP_IRQ_CLEAR_0_SHFT                                    0x18
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_BB_PDC_AOP_IRQ_CLEAR_1_BMSK                            0x800000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_BB_PDC_AOP_IRQ_CLEAR_1_SHFT                                0x17
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_BB_PDC_AOP_IRQ_CLEAR_0_BMSK                            0x400000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_BB_PDC_AOP_IRQ_CLEAR_0_SHFT                                0x16
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_1_BMSK                            0x200000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_1_SHFT                                0x15
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_0_BMSK                            0x100000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_WLAN_RF_PDC_AOP_IRQ_CLEAR_0_SHFT                                0x14
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_1_BMSK                               0x80000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_1_SHFT                                  0x13
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_0_BMSK                               0x40000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_MODEM_PDC_AOP_IRQ_CLEAR_0_SHFT                                  0x12
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_1_BMSK                                 0x20000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_1_SHFT                                    0x11
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_0_BMSK                                 0x10000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_TME_PDC_AOP_IRQ_CLEAR_0_SHFT                                    0x10
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_1_BMSK                              0x8000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_1_SHFT                                 0xf
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_0_BMSK                              0x4000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_COMPUTE_PDC_AOP_IRQ_CLEAR_0_SHFT                                 0xe
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_1_BMSK                              0x2000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_1_SHFT                                 0xd
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_0_BMSK                              0x1000
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DISPLAY_PDC_AOP_IRQ_CLEAR_0_SHFT                                 0xc
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_1_BMSK                                   0x800
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_1_SHFT                                     0xb
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_0_BMSK                                   0x400
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_GPU_PDC_AOP_IRQ_CLEAR_0_SHFT                                     0xa
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_1_BMSK                                 0x200
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_1_SHFT                                   0x9
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_0_BMSK                                 0x100
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_DEBUG_PDC_AOP_IRQ_CLEAR_0_SHFT                                   0x8
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_1_BMSK                                    0x80
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_1_SHFT                                     0x7
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_0_BMSK                                    0x40
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AOP_PDC_AOP_IRQ_CLEAR_0_SHFT                                     0x6
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_1_BMSK                                  0x20
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_1_SHFT                                   0x5
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_0_BMSK                                  0x10
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_AUDIO_PDC_AOP_IRQ_CLEAR_0_SHFT                                   0x4
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_1_BMSK                                      0x8
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_1_SHFT                                      0x3
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_0_BMSK                                      0x4
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_SP_PDC_AOP_IRQ_CLEAR_0_SHFT                                      0x2
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_1_BMSK                                    0x2
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_1_SHFT                                    0x1
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_0_BMSK                                    0x1
#define HWIO_RPMH_PDC_AOP_IRQ_CLEAR_BANK0_APPS_PDC_AOP_IRQ_CLEAR_0_SHFT                                    0x0

#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR                                                     (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002220)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_RMSK                                                      0x3ffffff
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_CAM_PDC_AOP_SEQ_RESUME_1_BMSK                             0x2000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_CAM_PDC_AOP_SEQ_RESUME_1_SHFT                                  0x19
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_CAM_PDC_AOP_SEQ_RESUME_0_BMSK                             0x1000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_CAM_PDC_AOP_SEQ_RESUME_0_SHFT                                  0x18
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_1_BMSK                          0x800000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_1_SHFT                              0x17
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_0_BMSK                          0x400000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_0_SHFT                              0x16
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_1_BMSK                          0x200000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_1_SHFT                              0x15
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_0_BMSK                          0x100000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_0_SHFT                              0x14
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_1_BMSK                             0x80000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_1_SHFT                                0x13
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_0_BMSK                             0x40000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_MODEM_PDC_AOP_SEQ_RESUME_0_SHFT                                0x12
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_1_BMSK                               0x20000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_1_SHFT                                  0x11
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_0_BMSK                               0x10000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_TME_PDC_AOP_SEQ_RESUME_0_SHFT                                  0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_1_BMSK                            0x8000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_1_SHFT                               0xf
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_0_BMSK                            0x4000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_0_SHFT                               0xe
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_1_BMSK                            0x2000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_1_SHFT                               0xd
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_0_BMSK                            0x1000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_0_SHFT                               0xc
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_1_BMSK                                 0x800
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_1_SHFT                                   0xb
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_0_BMSK                                 0x400
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_GPU_PDC_AOP_SEQ_RESUME_0_SHFT                                   0xa
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_1_BMSK                               0x200
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_1_SHFT                                 0x9
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_0_BMSK                               0x100
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_0_SHFT                                 0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_1_BMSK                                  0x80
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_1_SHFT                                   0x7
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_0_BMSK                                  0x40
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AOP_PDC_AOP_SEQ_RESUME_0_SHFT                                   0x6
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_1_BMSK                                0x20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_1_SHFT                                 0x5
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_0_BMSK                                0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_0_SHFT                                 0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_1_BMSK                                    0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_1_SHFT                                    0x3
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_0_BMSK                                    0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_SP_PDC_AOP_SEQ_RESUME_0_SHFT                                    0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_1_BMSK                                  0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_1_SHFT                                  0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_0_BMSK                                  0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_BANK0_APPS_PDC_AOP_SEQ_RESUME_0_SHFT                                  0x0

#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002230)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_RMSK                                                 0x3ffffff
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_ADDR,m,v,HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_IN)
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_CAM_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                   0x2000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_CAM_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                        0x19
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_CAM_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                   0x1000000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_CAM_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                        0x18
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                0x800000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                    0x17
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                0x400000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_BB_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                    0x16
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                0x200000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                    0x15
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                0x100000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_WLAN_RF_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                    0x14
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                   0x80000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                      0x13
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                   0x40000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_MODEM_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                      0x12
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                     0x20000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                        0x11
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                     0x10000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_TME_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                        0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                  0x8000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                     0xf
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                  0x4000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_COMPUTE_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                     0xe
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                  0x2000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                     0xd
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                  0x1000
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DISPLAY_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                     0xc
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                       0x800
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                         0xb
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                       0x400
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_GPU_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                         0xa
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                     0x200
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                       0x9
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                     0x100
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_DEBUG_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                       0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                        0x80
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                         0x7
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                        0x40
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AOP_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                         0x6
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                      0x20
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                       0x5
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                      0x10
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_AUDIO_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                       0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                          0x8
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                          0x3
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                          0x4
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_SP_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                          0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_1_BMSK                        0x2
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_1_SHFT                        0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_0_BMSK                        0x1
#define HWIO_RPMH_PDC_AOP_SEQ_RESUME_ONCE_BANK0_APPS_PDC_AOP_SEQ_RESUME_ONCE_0_SHFT                        0x0

#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR                                                (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002300)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_RMSK                                                    0x1fff
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_CAM_SOC_SLEEP_LOCK_MASK_BMSK                            0x1000
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_CAM_SOC_SLEEP_LOCK_MASK_SHFT                               0xc
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_BB_SOC_SLEEP_LOCK_MASK_BMSK                         0x800
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_BB_SOC_SLEEP_LOCK_MASK_SHFT                           0xb
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_RF_SOC_SLEEP_LOCK_MASK_BMSK                         0x400
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_WLAN_RF_SOC_SLEEP_LOCK_MASK_SHFT                           0xa
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_MODEM_SOC_SLEEP_LOCK_MASK_BMSK                           0x200
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_MODEM_SOC_SLEEP_LOCK_MASK_SHFT                             0x9
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_TME_SOC_SLEEP_LOCK_MASK_BMSK                             0x100
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_TME_SOC_SLEEP_LOCK_MASK_SHFT                               0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_COMPUTE_SOC_SLEEP_LOCK_MASK_BMSK                          0x80
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_COMPUTE_SOC_SLEEP_LOCK_MASK_SHFT                           0x7
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DISPLAY_SOC_SLEEP_LOCK_MASK_BMSK                          0x40
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DISPLAY_SOC_SLEEP_LOCK_MASK_SHFT                           0x6
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_GPU_SOC_SLEEP_LOCK_MASK_BMSK                              0x20
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_GPU_SOC_SLEEP_LOCK_MASK_SHFT                               0x5
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DEBUG_SOC_SLEEP_LOCK_MASK_BMSK                            0x10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_DEBUG_SOC_SLEEP_LOCK_MASK_SHFT                             0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AOP_SOC_SLEEP_LOCK_MASK_BMSK                               0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AOP_SOC_SLEEP_LOCK_MASK_SHFT                               0x3
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AUDIO_SOC_SLEEP_LOCK_MASK_BMSK                             0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_AUDIO_SOC_SLEEP_LOCK_MASK_SHFT                             0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SP_SOC_SLEEP_LOCK_MASK_BMSK                                0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_SP_SOC_SLEEP_LOCK_MASK_SHFT                                0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_APPS_SOC_SLEEP_LOCK_MASK_BMSK                              0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_MASK_BANK0_APPS_SOC_SLEEP_LOCK_MASK_SHFT                              0x0

#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR                                              (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002310)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_RMSK                                                  0x1fff
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_CAM_SOC_SLEEP_LOCK_STATUS_BMSK                        0x1000
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_CAM_SOC_SLEEP_LOCK_STATUS_SHFT                           0xc
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_BB_SOC_SLEEP_LOCK_STATUS_BMSK                     0x800
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_BB_SOC_SLEEP_LOCK_STATUS_SHFT                       0xb
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_RF_SOC_SLEEP_LOCK_STATUS_BMSK                     0x400
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_WLAN_RF_SOC_SLEEP_LOCK_STATUS_SHFT                       0xa
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_MODEM_SOC_SLEEP_LOCK_STATUS_BMSK                       0x200
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_MODEM_SOC_SLEEP_LOCK_STATUS_SHFT                         0x9
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_TME_SOC_SLEEP_LOCK_STATUS_BMSK                         0x100
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_TME_SOC_SLEEP_LOCK_STATUS_SHFT                           0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_COMPUTE_SOC_SLEEP_LOCK_STATUS_BMSK                      0x80
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_COMPUTE_SOC_SLEEP_LOCK_STATUS_SHFT                       0x7
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DISPLAY_SOC_SLEEP_LOCK_STATUS_BMSK                      0x40
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DISPLAY_SOC_SLEEP_LOCK_STATUS_SHFT                       0x6
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_GPU_SOC_SLEEP_LOCK_STATUS_BMSK                          0x20
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_GPU_SOC_SLEEP_LOCK_STATUS_SHFT                           0x5
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DEBUG_SOC_SLEEP_LOCK_STATUS_BMSK                        0x10
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_DEBUG_SOC_SLEEP_LOCK_STATUS_SHFT                         0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AOP_SOC_SLEEP_LOCK_STATUS_BMSK                           0x8
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AOP_SOC_SLEEP_LOCK_STATUS_SHFT                           0x3
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AUDIO_SOC_SLEEP_LOCK_STATUS_BMSK                         0x4
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_AUDIO_SOC_SLEEP_LOCK_STATUS_SHFT                         0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SP_SOC_SLEEP_LOCK_STATUS_BMSK                            0x2
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_SP_SOC_SLEEP_LOCK_STATUS_SHFT                            0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_APPS_SOC_SLEEP_LOCK_STATUS_BMSK                          0x1
#define HWIO_RPMH_PDC_SOC_SLEEP_LOCK_STATUS_BANK0_APPS_SOC_SLEEP_LOCK_STATUS_SHFT                          0x0

#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR                                              (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002320)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_RMSK                                                  0x1fff
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_CAM_CX_COLLAPSE_LOCK_MASK_BMSK                        0x1000
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_CAM_CX_COLLAPSE_LOCK_MASK_SHFT                           0xc
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_BB_CX_COLLAPSE_LOCK_MASK_BMSK                     0x800
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_BB_CX_COLLAPSE_LOCK_MASK_SHFT                       0xb
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_MASK_BMSK                     0x400
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_MASK_SHFT                       0xa
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_MODEM_CX_COLLAPSE_LOCK_MASK_BMSK                       0x200
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_MODEM_CX_COLLAPSE_LOCK_MASK_SHFT                         0x9
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_TME_CX_COLLAPSE_LOCK_MASK_BMSK                         0x100
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_TME_CX_COLLAPSE_LOCK_MASK_SHFT                           0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_COMPUTE_CX_COLLAPSE_LOCK_MASK_BMSK                      0x80
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_COMPUTE_CX_COLLAPSE_LOCK_MASK_SHFT                       0x7
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DISPLAY_CX_COLLAPSE_LOCK_MASK_BMSK                      0x40
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DISPLAY_CX_COLLAPSE_LOCK_MASK_SHFT                       0x6
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_GPU_CX_COLLAPSE_LOCK_MASK_BMSK                          0x20
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_GPU_CX_COLLAPSE_LOCK_MASK_SHFT                           0x5
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DEBUG_CX_COLLAPSE_LOCK_MASK_BMSK                        0x10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_DEBUG_CX_COLLAPSE_LOCK_MASK_SHFT                         0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AOP_CX_COLLAPSE_LOCK_MASK_BMSK                           0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AOP_CX_COLLAPSE_LOCK_MASK_SHFT                           0x3
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AUDIO_CX_COLLAPSE_LOCK_MASK_BMSK                         0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_AUDIO_CX_COLLAPSE_LOCK_MASK_SHFT                         0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SP_CX_COLLAPSE_LOCK_MASK_BMSK                            0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_SP_CX_COLLAPSE_LOCK_MASK_SHFT                            0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_APPS_CX_COLLAPSE_LOCK_MASK_BMSK                          0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_MASK_BANK0_APPS_CX_COLLAPSE_LOCK_MASK_SHFT                          0x0

#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR                                            (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002330)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_RMSK                                                0x1fff
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_CAM_CX_COLLAPSE_LOCK_STATUS_BMSK                    0x1000
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_CAM_CX_COLLAPSE_LOCK_STATUS_SHFT                       0xc
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_BB_CX_COLLAPSE_LOCK_STATUS_BMSK                 0x800
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_BB_CX_COLLAPSE_LOCK_STATUS_SHFT                   0xb
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_STATUS_BMSK                 0x400
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_WLAN_RF_CX_COLLAPSE_LOCK_STATUS_SHFT                   0xa
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_MODEM_CX_COLLAPSE_LOCK_STATUS_BMSK                   0x200
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_MODEM_CX_COLLAPSE_LOCK_STATUS_SHFT                     0x9
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_TME_CX_COLLAPSE_LOCK_STATUS_BMSK                     0x100
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_TME_CX_COLLAPSE_LOCK_STATUS_SHFT                       0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_COMPUTE_CX_COLLAPSE_LOCK_STATUS_BMSK                  0x80
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_COMPUTE_CX_COLLAPSE_LOCK_STATUS_SHFT                   0x7
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DISPLAY_CX_COLLAPSE_LOCK_STATUS_BMSK                  0x40
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DISPLAY_CX_COLLAPSE_LOCK_STATUS_SHFT                   0x6
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_GPU_CX_COLLAPSE_LOCK_STATUS_BMSK                      0x20
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_GPU_CX_COLLAPSE_LOCK_STATUS_SHFT                       0x5
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DEBUG_CX_COLLAPSE_LOCK_STATUS_BMSK                    0x10
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_DEBUG_CX_COLLAPSE_LOCK_STATUS_SHFT                     0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AOP_CX_COLLAPSE_LOCK_STATUS_BMSK                       0x8
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AOP_CX_COLLAPSE_LOCK_STATUS_SHFT                       0x3
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AUDIO_CX_COLLAPSE_LOCK_STATUS_BMSK                     0x4
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_AUDIO_CX_COLLAPSE_LOCK_STATUS_SHFT                     0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SP_CX_COLLAPSE_LOCK_STATUS_BMSK                        0x2
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_SP_CX_COLLAPSE_LOCK_STATUS_SHFT                        0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_APPS_CX_COLLAPSE_LOCK_STATUS_BMSK                      0x1
#define HWIO_RPMH_PDC_CX_COLLAPSE_LOCK_STATUS_BANK0_APPS_CX_COLLAPSE_LOCK_STATUS_SHFT                      0x0

#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002340)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_RMSK                                                 0x1fff
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR,v)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_ADDR,m,v,HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_IN)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_CAM_DBG_RSRC_REL_LOCK_MASK_BMSK                      0x1000
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_CAM_DBG_RSRC_REL_LOCK_MASK_SHFT                         0xc
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_BB_DBG_RSRC_REL_LOCK_MASK_BMSK                   0x800
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_BB_DBG_RSRC_REL_LOCK_MASK_SHFT                     0xb
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_MASK_BMSK                   0x400
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_MASK_SHFT                     0xa
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_MODEM_DBG_RSRC_REL_LOCK_MASK_BMSK                     0x200
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_MODEM_DBG_RSRC_REL_LOCK_MASK_SHFT                       0x9
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_TME_DBG_RSRC_REL_LOCK_MASK_BMSK                       0x100
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_TME_DBG_RSRC_REL_LOCK_MASK_SHFT                         0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_MASK_BMSK                    0x80
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_MASK_SHFT                     0x7
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_MASK_BMSK                    0x40
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_MASK_SHFT                     0x6
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_GPU_DBG_RSRC_REL_LOCK_MASK_BMSK                        0x20
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_GPU_DBG_RSRC_REL_LOCK_MASK_SHFT                         0x5
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DEBUG_DBG_RSRC_REL_LOCK_MASK_BMSK                      0x10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_DEBUG_DBG_RSRC_REL_LOCK_MASK_SHFT                       0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AOP_DBG_RSRC_REL_LOCK_MASK_BMSK                         0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AOP_DBG_RSRC_REL_LOCK_MASK_SHFT                         0x3
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AUDIO_DBG_RSRC_REL_LOCK_MASK_BMSK                       0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_AUDIO_DBG_RSRC_REL_LOCK_MASK_SHFT                       0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SP_DBG_RSRC_REL_LOCK_MASK_BMSK                          0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_SP_DBG_RSRC_REL_LOCK_MASK_SHFT                          0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_APPS_DBG_RSRC_REL_LOCK_MASK_BMSK                        0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_MASK_BANK0_APPS_DBG_RSRC_REL_LOCK_MASK_SHFT                        0x0

#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR                                           (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002350)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_RMSK                                               0x1fff
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_ADDR, m)
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_CAM_DBG_RSRC_REL_LOCK_STATUS_BMSK                  0x1000
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_CAM_DBG_RSRC_REL_LOCK_STATUS_SHFT                     0xc
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_BB_DBG_RSRC_REL_LOCK_STATUS_BMSK               0x800
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_BB_DBG_RSRC_REL_LOCK_STATUS_SHFT                 0xb
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_STATUS_BMSK               0x400
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_WLAN_RF_DBG_RSRC_REL_LOCK_STATUS_SHFT                 0xa
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_MODEM_DBG_RSRC_REL_LOCK_STATUS_BMSK                 0x200
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_MODEM_DBG_RSRC_REL_LOCK_STATUS_SHFT                   0x9
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_TME_DBG_RSRC_REL_LOCK_STATUS_BMSK                   0x100
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_TME_DBG_RSRC_REL_LOCK_STATUS_SHFT                     0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_STATUS_BMSK                0x80
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_COMPUTE_DBG_RSRC_REL_LOCK_STATUS_SHFT                 0x7
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_STATUS_BMSK                0x40
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DISPLAY_DBG_RSRC_REL_LOCK_STATUS_SHFT                 0x6
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_GPU_DBG_RSRC_REL_LOCK_STATUS_BMSK                    0x20
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_GPU_DBG_RSRC_REL_LOCK_STATUS_SHFT                     0x5
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DEBUG_DBG_RSRC_REL_LOCK_STATUS_BMSK                  0x10
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_DEBUG_DBG_RSRC_REL_LOCK_STATUS_SHFT                   0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AOP_DBG_RSRC_REL_LOCK_STATUS_BMSK                     0x8
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AOP_DBG_RSRC_REL_LOCK_STATUS_SHFT                     0x3
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AUDIO_DBG_RSRC_REL_LOCK_STATUS_BMSK                   0x4
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_AUDIO_DBG_RSRC_REL_LOCK_STATUS_SHFT                   0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SP_DBG_RSRC_REL_LOCK_STATUS_BMSK                      0x2
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_SP_DBG_RSRC_REL_LOCK_STATUS_SHFT                      0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_APPS_DBG_RSRC_REL_LOCK_STATUS_BMSK                    0x1
#define HWIO_RPMH_PDC_DBG_RSRC_REL_LOCK_STATUS_BANK0_APPS_DBG_RSRC_REL_LOCK_STATUS_SHFT                    0x0

#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR                                                          (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002400)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_RMSK                                                               0x101
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR, m)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR,v)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_DBG_BUS_CONTROL_ADDR,m,v,HWIO_RPMH_PDC_DBG_BUS_CONTROL_IN)
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_GLOBAL_COUNTER_MASK_BMSK                                   0x100
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_GLOBAL_COUNTER_MASK_SHFT                                     0x8
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_ENABLE_BMSK                                                  0x1
#define HWIO_RPMH_PDC_DBG_BUS_CONTROL_DBG_BUS_ENABLE_SHFT                                                  0x0

#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002404 + 0x4 * (d))
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_RMSK                                                            0xff
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_MAXd                                                               7
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_ADDR(d), HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_RMSK)
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_ADDR(d), mask)
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_ADDR(d),val)
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_ADDR(d),mask,val,HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_INI(d))
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_CAM_BRANCH_EN_BMSK                                              0x80
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_CAM_BRANCH_EN_SHFT                                               0x7
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_MODEM_BRANCH_EN_BMSK                                            0x40
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_MODEM_BRANCH_EN_SHFT                                             0x6
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_TME_BRANCH_EN_BMSK                                              0x20
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_TME_BRANCH_EN_SHFT                                               0x5
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_COMPUTE_BRANCH_EN_BMSK                                          0x10
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_COMPUTE_BRANCH_EN_SHFT                                           0x4
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_DISPLAY_BRANCH_EN_BMSK                                           0x8
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_DISPLAY_BRANCH_EN_SHFT                                           0x3
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_GPU_BRANCH_EN_BMSK                                               0x4
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_GPU_BRANCH_EN_SHFT                                               0x2
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_SP_BRANCH_EN_BMSK                                                0x2
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_SP_BRANCH_EN_SHFT                                                0x1
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_APPS_BRANCH_EN_BMSK                                              0x1
#define HWIO_RPMH_PDC_GRP0_CGRP_BR_EVENTd_APPS_BRANCH_EN_SHFT                                              0x0

#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_ADDR(t)                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002454 + 0x4 * (t))
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_RMSK                                                      0xff
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_MAXt                                                         5
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_INI(t)        \
        in_dword_masked(HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_ADDR(t), HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_RMSK)
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_INMI(t,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_ADDR(t), mask)
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_ARB_GRANT_STATUS_BMSK                                     0xff
#define HWIO_RPMH_PDC_GRP0_GTCS_ARB_GRANT_tGTCS_ARB_GRANT_STATUS_SHFT                                      0x0

#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002484)
#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_RMSK                                                         0xffffffff
#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_IN          \
        in_dword(HWIO_RPMH_PDC_GRP0_GTCS_STATUS_ADDR)
#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_GRP0_GTCS_STATUS_ADDR, m)
#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_TCS_BUSY_BMSK                                                0xffffffff
#define HWIO_RPMH_PDC_GRP0_GTCS_STATUS_TCS_BUSY_SHFT                                                       0x0

#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_ADDR(d)                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002604 + 0x4 * (d))
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_RMSK                                                             0x3
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_MAXd                                                               3
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_INI(d)        \
        in_dword_masked(HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_ADDR(d), HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_RMSK)
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_INMI(d,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_ADDR(d), mask)
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_OUTI(d,val)    \
        out_dword(HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_ADDR(d),val)
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_ADDR(d),mask,val,HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_INI(d))
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_WLAN_BB_BRANCH_EN_BMSK                                           0x2
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_WLAN_BB_BRANCH_EN_SHFT                                           0x1
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_WLAN_RF_BRANCH_EN_BMSK                                           0x1
#define HWIO_RPMH_PDC_GRP2_CGRP_BR_EVENTd_WLAN_RF_BRANCH_EN_SHFT                                           0x0

#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_ADDR(t)                                             (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002654 + 0x4 * (t))
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_RMSK                                                       0x3
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_MAXt                                                         9
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_INI(t)        \
        in_dword_masked(HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_ADDR(t), HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_RMSK)
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_INMI(t,mask)    \
        in_dword_masked(HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_ADDR(t), mask)
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_ARB_GRANT_STATUS_BMSK                                      0x3
#define HWIO_RPMH_PDC_GRP2_GTCS_ARB_GRANT_tGTCS_ARB_GRANT_STATUS_SHFT                                      0x0

#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002684)
#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_RMSK                                                         0xffffffff
#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_IN          \
        in_dword(HWIO_RPMH_PDC_GRP2_GTCS_STATUS_ADDR)
#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_GRP2_GTCS_STATUS_ADDR, m)
#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_TCS_BUSY_BMSK                                                0xffffffff
#define HWIO_RPMH_PDC_GRP2_GTCS_STATUS_TCS_BUSY_SHFT                                                       0x0

#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_ADDR                                                 (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002900)
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_RMSK                                                        0x1
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_IN          \
        in_dword(HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_ADDR)
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_ADDR, m)
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_OUT(v)      \
        out_dword(HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_ADDR,v)
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_ADDR,m,v,HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_IN)
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_FORCE_CLK_EN_BMSK                                           0x1
#define HWIO_RPMH_PDC_TCS_POOL_CLK_GATING_CTRL_FORCE_CLK_EN_SHFT                                           0x0

#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_ADDR                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002904)
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_RMSK                                                       0x1fff
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_ADDR)
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_ADDR, m)
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_CAM_EPCB_RX_FIFO_EMPTY_BMSK                                0x1000
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_CAM_EPCB_RX_FIFO_EMPTY_SHFT                                   0xc
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_WLAN_BB_EPCB_RX_FIFO_EMPTY_BMSK                             0x800
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_WLAN_BB_EPCB_RX_FIFO_EMPTY_SHFT                               0xb
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_WLAN_RF_EPCB_RX_FIFO_EMPTY_BMSK                             0x400
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_WLAN_RF_EPCB_RX_FIFO_EMPTY_SHFT                               0xa
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_MODEM_EPCB_RX_FIFO_EMPTY_BMSK                               0x200
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_MODEM_EPCB_RX_FIFO_EMPTY_SHFT                                 0x9
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_TME_EPCB_RX_FIFO_EMPTY_BMSK                                 0x100
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_TME_EPCB_RX_FIFO_EMPTY_SHFT                                   0x8
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_COMPUTE_EPCB_RX_FIFO_EMPTY_BMSK                              0x80
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_COMPUTE_EPCB_RX_FIFO_EMPTY_SHFT                               0x7
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_DISPLAY_EPCB_RX_FIFO_EMPTY_BMSK                              0x40
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_DISPLAY_EPCB_RX_FIFO_EMPTY_SHFT                               0x6
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_GPU_EPCB_RX_FIFO_EMPTY_BMSK                                  0x20
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_GPU_EPCB_RX_FIFO_EMPTY_SHFT                                   0x5
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_DEBUG_EPCB_RX_FIFO_EMPTY_BMSK                                0x10
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_DEBUG_EPCB_RX_FIFO_EMPTY_SHFT                                 0x4
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_AOP_EPCB_RX_FIFO_EMPTY_BMSK                                   0x8
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_AOP_EPCB_RX_FIFO_EMPTY_SHFT                                   0x3
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_AUDIO_EPCB_RX_FIFO_EMPTY_BMSK                                 0x4
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_AUDIO_EPCB_RX_FIFO_EMPTY_SHFT                                 0x2
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_SP_EPCB_RX_FIFO_EMPTY_BMSK                                    0x2
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_SP_EPCB_RX_FIFO_EMPTY_SHFT                                    0x1
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_APPS_EPCB_RX_FIFO_EMPTY_BMSK                                  0x1
#define HWIO_RPMH_PDC_DBG_EPCB_RX_FIFO_EMPTY_APPS_EPCB_RX_FIFO_EMPTY_SHFT                                  0x0

#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_ADDR                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002908)
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_RMSK                                                       0x1fff
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_ADDR)
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_ADDR, m)
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_CAM_EPCB_TX_FIFO_EMPTY_BMSK                                0x1000
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_CAM_EPCB_TX_FIFO_EMPTY_SHFT                                   0xc
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_WLAN_BB_EPCB_TX_FIFO_EMPTY_BMSK                             0x800
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_WLAN_BB_EPCB_TX_FIFO_EMPTY_SHFT                               0xb
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_WLAN_RF_EPCB_TX_FIFO_EMPTY_BMSK                             0x400
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_WLAN_RF_EPCB_TX_FIFO_EMPTY_SHFT                               0xa
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_MODEM_EPCB_TX_FIFO_EMPTY_BMSK                               0x200
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_MODEM_EPCB_TX_FIFO_EMPTY_SHFT                                 0x9
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_TME_EPCB_TX_FIFO_EMPTY_BMSK                                 0x100
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_TME_EPCB_TX_FIFO_EMPTY_SHFT                                   0x8
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_COMPUTE_EPCB_TX_FIFO_EMPTY_BMSK                              0x80
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_COMPUTE_EPCB_TX_FIFO_EMPTY_SHFT                               0x7
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_DISPLAY_EPCB_TX_FIFO_EMPTY_BMSK                              0x40
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_DISPLAY_EPCB_TX_FIFO_EMPTY_SHFT                               0x6
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_GPU_EPCB_TX_FIFO_EMPTY_BMSK                                  0x20
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_GPU_EPCB_TX_FIFO_EMPTY_SHFT                                   0x5
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_DEBUG_EPCB_TX_FIFO_EMPTY_BMSK                                0x10
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_DEBUG_EPCB_TX_FIFO_EMPTY_SHFT                                 0x4
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_AOP_EPCB_TX_FIFO_EMPTY_BMSK                                   0x8
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_AOP_EPCB_TX_FIFO_EMPTY_SHFT                                   0x3
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_AUDIO_EPCB_TX_FIFO_EMPTY_BMSK                                 0x4
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_AUDIO_EPCB_TX_FIFO_EMPTY_SHFT                                 0x2
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_SP_EPCB_TX_FIFO_EMPTY_BMSK                                    0x2
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_SP_EPCB_TX_FIFO_EMPTY_SHFT                                    0x1
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_APPS_EPCB_TX_FIFO_EMPTY_BMSK                                  0x1
#define HWIO_RPMH_PDC_DBG_EPCB_TX_FIFO_EMPTY_APPS_EPCB_TX_FIFO_EMPTY_SHFT                                  0x0

#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_ADDR                                                   (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x0000290c)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_RMSK                                                   0xffffffff
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_ADDR)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_ADDR, m)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_DATA_OUT_BMSK                                          0xffffffff
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_DATA_OUT_DATA_OUT_SHFT                                                 0x0

#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_ADDR                                                    (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002910)
#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_RMSK                                                    0xffffffff
#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_ADDR)
#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_ADDR, m)
#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_DATA_IN_BMSK                                            0xffffffff
#define HWIO_RPMH_PDC_DBG_IPCB2EPCB_DATA_IN_DATA_IN_SHFT                                                   0x0

#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_ADDR                                                       (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002914)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_RMSK                                                       0xffffffff
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_ADDR)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_ADDR, m)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_ADDR_BMSK                                                  0xffffffff
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_ADDR_ADDR_SHFT                                                         0x0

#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_ADDR                                                       (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002918)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_RMSK                                                              0x7
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_ADDR)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_ADDR, m)
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_OUT_DATA_VALID_BMSK                                               0x4
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_OUT_DATA_VALID_SHFT                                               0x2
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_RD_DATA_VALID_BMSK                                                0x2
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_RD_DATA_VALID_SHFT                                                0x1
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_WR_RD_N_BMSK                                                      0x1
#define HWIO_RPMH_PDC_DBG_EPCB2IPCB_CTRL_WR_RD_N_SHFT                                                      0x0

#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x0000291c)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_RMSK                                                             0x1fff
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_ADDR)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_ADDR, m)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_CAM_IPCB_ARB_REQ_BMSK                                            0x1000
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_CAM_IPCB_ARB_REQ_SHFT                                               0xc
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_WLAN_BB_IPCB_ARB_REQ_BMSK                                         0x800
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_WLAN_BB_IPCB_ARB_REQ_SHFT                                           0xb
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_WLAN_RF_IPCB_ARB_REQ_BMSK                                         0x400
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_WLAN_RF_IPCB_ARB_REQ_SHFT                                           0xa
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_MODEM_IPCB_ARB_REQ_BMSK                                           0x200
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_MODEM_IPCB_ARB_REQ_SHFT                                             0x9
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_TME_IPCB_ARB_REQ_BMSK                                             0x100
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_TME_IPCB_ARB_REQ_SHFT                                               0x8
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_COMPUTE_IPCB_ARB_REQ_BMSK                                          0x80
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_COMPUTE_IPCB_ARB_REQ_SHFT                                           0x7
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_DISPLAY_IPCB_ARB_REQ_BMSK                                          0x40
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_DISPLAY_IPCB_ARB_REQ_SHFT                                           0x6
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_GPU_IPCB_ARB_REQ_BMSK                                              0x20
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_GPU_IPCB_ARB_REQ_SHFT                                               0x5
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_DEBUG_IPCB_ARB_REQ_BMSK                                            0x10
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_DEBUG_IPCB_ARB_REQ_SHFT                                             0x4
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_AOP_IPCB_ARB_REQ_BMSK                                               0x8
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_AOP_IPCB_ARB_REQ_SHFT                                               0x3
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_AUDIO_IPCB_ARB_REQ_BMSK                                             0x4
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_AUDIO_IPCB_ARB_REQ_SHFT                                             0x2
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_SP_IPCB_ARB_REQ_BMSK                                                0x2
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_SP_IPCB_ARB_REQ_SHFT                                                0x1
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_APPS_IPCB_ARB_REQ_BMSK                                              0x1
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_REQ_APPS_IPCB_ARB_REQ_SHFT                                              0x0

#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_ADDR                                                         (RPMH_PDC_PDC_GLOBAL_REG_BASE      + 0x00002920)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_RMSK                                                             0x1fff
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_IN          \
        in_dword(HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_ADDR)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_INM(m)      \
        in_dword_masked(HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_ADDR, m)
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_CAM_IPCB_ARB_GNT_BMSK                                            0x1000
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_CAM_IPCB_ARB_GNT_SHFT                                               0xc
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_WLAN_BB_IPCB_ARB_GNT_BMSK                                         0x800
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_WLAN_BB_IPCB_ARB_GNT_SHFT                                           0xb
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_WLAN_RF_IPCB_ARB_GNT_BMSK                                         0x400
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_WLAN_RF_IPCB_ARB_GNT_SHFT                                           0xa
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_MODEM_IPCB_ARB_GNT_BMSK                                           0x200
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_MODEM_IPCB_ARB_GNT_SHFT                                             0x9
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_TME_IPCB_ARB_GNT_BMSK                                             0x100
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_TME_IPCB_ARB_GNT_SHFT                                               0x8
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_COMPUTE_IPCB_ARB_GNT_BMSK                                          0x80
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_COMPUTE_IPCB_ARB_GNT_SHFT                                           0x7
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_DISPLAY_IPCB_ARB_GNT_BMSK                                          0x40
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_DISPLAY_IPCB_ARB_GNT_SHFT                                           0x6
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_GPU_IPCB_ARB_GNT_BMSK                                              0x20
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_GPU_IPCB_ARB_GNT_SHFT                                               0x5
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_DEBUG_IPCB_ARB_GNT_BMSK                                            0x10
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_DEBUG_IPCB_ARB_GNT_SHFT                                             0x4
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_AOP_IPCB_ARB_GNT_BMSK                                               0x8
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_AOP_IPCB_ARB_GNT_SHFT                                               0x3
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_AUDIO_IPCB_ARB_GNT_BMSK                                             0x4
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_AUDIO_IPCB_ARB_GNT_SHFT                                             0x2
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_SP_IPCB_ARB_GNT_BMSK                                                0x2
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_SP_IPCB_ARB_GNT_SHFT                                                0x1
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_APPS_IPCB_ARB_GNT_BMSK                                              0x1
#define HWIO_RPMH_PDC_DBG_IPCB_ARB_GNT_APPS_IPCB_ARB_GNT_SHFT                                              0x0


#endif /* __PDC_GLOBAL_HWIO_H__ */
