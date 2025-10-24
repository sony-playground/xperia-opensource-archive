#ifndef __HALCLKEPSS_H__
#define __HALCLKEPSS_H__
/*
==============================================================================

FILE:         HALCLKEPSS.h

DESCRIPTION:
  Register Offsets for EPSS HAL Module.
=============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/HALclkLib/HALclkEPSS.h#1 $

==============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*============================================================================
                     INCLUDE FILES FOR MODULE
============================================================================*/

#include "HALhwio.h"

/* ============================================================================
**    Definitions
** ==========================================================================*/

/*----------------------------------------------------------------------------
 * MODULE: EPSSTOP_EPSS_TOP
 *--------------------------------------------------------------------------*/
#define EPSSTOP_EPSS_TOP_REG_BASE_OFFS                              0x00d98000

/*----------------------------------------------------------------------------
 * MODULE: EPSS_TOP
 *--------------------------------------------------------------------------*/
#define HWIO_L3_VOTING_EN_OFFS         (EPSSTOP_EPSS_TOP_REG_BASE_OFFS + 0x24)
#define HWIO_L3_VOTING_EN_RMSK                                             0x1
#define HWIO_L3_VOTING_EN_L3_VOTING_ENABLE_BMSK                            0x1
#define HWIO_L3_VOTING_EN_L3_VOTING_ENABLE_SHFT                            0x0
#define HWIO_L3_VOTING_EN_L3_VOTING_ENABLE_DISABLE_FVAL                    0x0
#define HWIO_L3_VOTING_EN_L3_VOTING_ENABLE_ENABLE_FVAL                     0x1

/*----------------------------------------------------------------------------
 * MODULE: EPSS_CLKDOM
 *--------------------------------------------------------------------------*/

#define HWIO_CC_DCVS_OFFS                                                  0xc
#define HWIO_CC_DCVS_RMSK                                                  0x1
#define HWIO_CC_DCVS_EN_BMSK                                               0x1
#define HWIO_CC_DCVS_EN_SHFT                                               0x0

#define HWIO_DOMAIN_STATE_OFFS                                            0x20
#define HWIO_DOMAIN_STATE_RMSK                                      0xfff03fff
#define HWIO_DOMAIN_STATE_OLV_BMSK                                  0xfff00000
#define HWIO_DOMAIN_STATE_OLV_SHFT                                        0x14
#define HWIO_DOMAIN_STATE_VC_IDX_BMSK                                   0x3f00
#define HWIO_DOMAIN_STATE_VC_IDX_SHFT                                      0x8
#define HWIO_DOMAIN_STATE_FREQ_BMSK                                       0xff
#define HWIO_DOMAIN_STATE_FREQ_SHFT                                        0x0

#define HWIO_COREd_L3_VOTING_OFFS(d)                          (0x90 + (0x4*d))
#define HWIO_COREd_L3_VOTING_RMSK                                         0x3f
#define HWIO_COREd_L3_VOTING_VC_BMSK                                      0x3f
#define HWIO_COREd_L3_VOTING_VC_SHFT                                       0x0

#define HWIO_DCVS_LUT_r_FREQUENCY_OFFS(r)                    (0x100 + (0x4*r))
#define HWIO_DCVS_LUT_r_FREQUENCY_RMSK                              0x400f00ff
#define HWIO_DCVS_LUT_r_FREQUENCY_CLKSRC_BMSK                       0x40000000
#define HWIO_DCVS_LUT_r_FREQUENCY_CLKSRC_SHFT                             0x1e
#define HWIO_DCVS_LUT_r_FREQUENCY_CC_BMSK                              0xf0000
#define HWIO_DCVS_LUT_r_FREQUENCY_CC_SHFT                                 0x10
#define HWIO_DCVS_LUT_r_FREQUENCY_LVAL_BMSK                               0xff
#define HWIO_DCVS_LUT_r_FREQUENCY_LVAL_SHFT                                0x0

#define HWIO_DCVS_LUT_r_VOLTAGE_OFFS(r)                      (0x200 + (0x4*r))
#define HWIO_DCVS_LUT_r_VOLTAGE_RMSK                                  0x3f0fff
#define HWIO_DCVS_LUT_r_VOLTAGE_VC_BMSK                               0x3f0000
#define HWIO_DCVS_LUT_r_VOLTAGE_VC_SHFT                                   0x10
#define HWIO_DCVS_LUT_r_VOLTAGE_OLV_BMSK                                 0xfff
#define HWIO_DCVS_LUT_r_VOLTAGE_OLV_SHFT                                   0x0

#define HWIO_DCVS_IN_PROGRESS_OFFS                                       0x300
#define HWIO_DCVS_IN_PROGRESS_RMSK                                         0x1
#define HWIO_DCVS_IN_PROGRESS_STATUS_BMSK                                  0x1
#define HWIO_DCVS_IN_PROGRESS_STATUS_SHFT                                  0x0


#define HWIO_COREd_PERF_STATE_DESIRED_OFFS(d)                (0x320 + (0x4*d))
#define HWIO_COREd_PERF_STATE_DESIRED_RMSK                                0x3f
#define HWIO_COREd_PERF_STATE_DESIRED_SW_INDEX_BMSK                       0x3f
#define HWIO_COREd_PERF_STATE_DESIRED_SW_INDEX_SHFT                        0x0


/* ============================================================================
**    External Definitions
** ==========================================================================*/

#define HAL_CLK_EPSS_TIMEOUT_COUNTER  200

#define HAL_CLK_HWIO_ADDR(ctxt, reg)          (ctxt->nAddr + HWIO_OFFS(reg))
#define HAL_CLK_HWIO_ADDRI(ctxt, reg, index)  (ctxt->nAddr + HWIO_OFFSI(reg, index))

#define HAL_CLK_HWIO_IN(ctxt, reg)            inpdw(HAL_CLK_HWIO_ADDR(ctxt, reg))
#define HAL_CLK_HWIO_INI(ctxt, reg, index)    inpdw(HAL_CLK_HWIO_ADDRI(ctxt, reg, index))

#define HAL_CLK_HWIO_INF(ctxt, reg, fld) \
  ((inpdw(HAL_CLK_HWIO_ADDR(ctxt, reg)) & HWIO_FMSK(reg, fld)) >> HWIO_SHFT(reg, fld))
#define HAL_CLK_HWIO_INFI(ctxt, reg, index, fld) \
  ((inpdw(HAL_CLK_HWIO_ADDRI(ctxt, reg, index)) & HWIO_FMSK(reg, fld)) >> HWIO_SHFT(reg, fld))

#define HAL_CLK_HWIO_OUT(ctxt, reg, val) \
  outpdw(HAL_CLK_HWIO_ADDR(ctxt, reg), val)
#define HAL_CLK_HWIO_OUTI(ctxt, reg, index, val) \
  outpdw(HAL_CLK_HWIO_ADDRI(ctxt, reg, index), val)

#define HAL_CLK_HWIO_OUTF(ctxt, reg, fld, val)           \
  outpdw(HAL_CLK_HWIO_ADDR(ctxt, reg),                   \
   (HAL_CLK_PLL_HWIO_IN(ctxt, reg) & ~HWIO_FMSK(reg, fld))   \
   | (((val) << HWIO_SHFT(reg, fld)) & HWIO_FMSK(reg, fld)))

#define HAL_CLK_HWIO_OUTFI(ctxt, reg, index, fld, val)           \
  outpdw(HAL_CLK_HWIO_ADDRI(ctxt, reg, index),                   \
   (HAL_CLK_HWIO_INI(ctxt, reg, index) & ~HWIO_FMSK(reg, fld))   \
   | (((val) << HWIO_SHFT(reg, fld)) & HWIO_FMSK(reg, fld)))

/* ============================================================================
**    Functions
** ==========================================================================*/

boolean  HAL_clk_PerCoreL3VottingEnabled(void);

#endif  /* __HALCLKEPSS_H__ */
 

