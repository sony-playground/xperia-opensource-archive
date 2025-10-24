#ifndef __WATCHDOGLIBHWIO_H__
#define __WATCHDOGLIBHWIO_H__
/*
===========================================================================
*/
/**
  @file WatchDogLibHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SM8350 (Lahaina) [lahaina_v1.0_rtl_partition_p3q3r25.3_func_MTO]
 
  This file contains HWIO register definitions for the following modules:
    APSS_WDT_TMR1_APSS_WDT


  Generation parameters: 
  { 'filename': 'WatchDogLibHWIO.h',
    'header': '#include "HALhwio.h"\n#include "msmhwiobase.h"',
    'module-filter-exclude': {},
    'module-filter-include': {},
    'modules': ['APSS_WDT_TMR1_APSS_WDT'],
    'output-fvals': True}
*/
/*
  ===========================================================================

  Copyright (c) 2020 Qualcomm Technologies, Inc.
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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Include/WatchDogLibHWIO.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "HALhwio.h"
#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: APSS_WDT_TMR1_APSS_WDT
 *--------------------------------------------------------------------------*/

#define APSS_WDT_TMR1_APSS_WDT_REG_BASE                                    (APSS_HM_BASE      + 0x00410000)
#define APSS_WDT_TMR1_APSS_WDT_REG_BASE_SIZE                               0x1000
#define APSS_WDT_TMR1_APSS_WDT_REG_BASE_USED                               0x20

#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_ADDR                                (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000000)
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_RMSK                                       0x1
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_SECURE_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_SECURE_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_SECURE_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_WDT_TMR1_WDOG_SECURE_ADDR,m,v,HWIO_APSS_WDT_TMR1_WDOG_SECURE_IN)
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_BMSK                                   0x1
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_SHFT                                   0x0
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_SEC_FVAL                               0x0
#define HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_NSEC_FVAL                              0x1

#define HWIO_APSS_WDT_TMR1_WDOG_RESET_ADDR                                 (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000004)
#define HWIO_APSS_WDT_TMR1_WDOG_RESET_RMSK                                        0x1
#define HWIO_APSS_WDT_TMR1_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_RESET_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_RESET_RESET_BMSK                                  0x1
#define HWIO_APSS_WDT_TMR1_WDOG_RESET_RESET_SHFT                                  0x0

#define HWIO_APSS_WDT_TMR1_WDOG_CTL_ADDR                                   (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000008)
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_RMSK                                          0x3
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_CTL_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_BMSK                      0x2
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_SHFT                      0x1
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_DISABLE_FVAL              0x0
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_ENABLE_FVAL               0x1
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_BMSK                               0x1
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_SHFT                               0x0
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_DISABLE_FVAL                       0x0
#define HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_ENABLE_FVAL                        0x1

#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_ADDR                                (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x0000000c)
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_RMSK                                0x801fffff
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_STATUS_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_STATUS_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_FROZEN_BMSK                         0x80000000
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_FROZEN_SHFT                               0x1f
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_FROZEN_NO_FVAL                             0x0
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_FROZEN_YES_FVAL                            0x1
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_COUNT_BMSK                            0x1ffffe
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_COUNT_SHFT                                 0x1
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_BMSK                        0x1
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_SHFT                        0x0
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_NO_FVAL                     0x0
#define HWIO_APSS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_YES_FVAL                    0x1

#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_ADDR                             (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000010)
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_RMSK                                0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_ADDR,m,v,HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_IN)
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_DATA_BMSK                           0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_BARK_TIME_DATA_SHFT                               0x0

#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_ADDR                             (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000014)
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_RMSK                                0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_ADDR,m,v,HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_IN)
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_DATA_BMSK                           0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_DATA_SHFT                               0x0

#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR                      (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000018)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_RMSK                             0x1
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_SYNC_STATUS_BMSK                 0x1
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_SYNC_STATUS_SHFT                 0x0

#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_ADDR                             (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x0000001c)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_RMSK                                    0x1
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_LOAD_BMSK                               0x1
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_LOAD_SHFT                               0x0

#define HWIO_APSS_WDT_TMR1_WDOG_TEST_ADDR                                  (APSS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000020)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_RMSK                                     0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_IN          \
        in_dword(HWIO_APSS_WDT_TMR1_WDOG_TEST_ADDR)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_APSS_WDT_TMR1_WDOG_TEST_ADDR, m)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_APSS_WDT_TMR1_WDOG_TEST_ADDR,v)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_WDT_TMR1_WDOG_TEST_ADDR,m,v,HWIO_APSS_WDT_TMR1_WDOG_TEST_IN)
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_VALUE_BMSK                          0xfffff
#define HWIO_APSS_WDT_TMR1_WDOG_TEST_LOAD_VALUE_SHFT                              0x0


#endif /* __WATCHDOGLIBHWIO_H__ */
