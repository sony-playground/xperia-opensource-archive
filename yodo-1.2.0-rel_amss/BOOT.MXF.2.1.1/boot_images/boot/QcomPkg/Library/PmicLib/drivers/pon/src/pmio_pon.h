#ifndef __PM_PON_PBS_PMIO_H__
#define __PM_PON_PBS_PMIO_H__
/*
===========================================================================
*/
/**
  @file pmio_pon.h
  @brief Auto-generated PMIO interface include file.

  This file contains PMIO register definitions for the following modules:
    PON

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pon/src/pmio_pon.h#1 $
  $Author: pwbldsvc $
  $DateTime: 2022/08/18 10:15:46 $
  Copyright (c) 2013 - 2021 Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pon/src/pmio_pon.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ===========================================================================
*/

__PM_PON_PBS_PMIO_H__

/*----------------------------------------------------------------------------
 * PERIPHERAL: PON_PBS
 *--------------------------------------------------------------------------*/

#define PON_PBS_BASE                                                          0x00000800

#define PMIO_PON_PBS_REVISION1_ADDR                                           (PON_PBS_BASE      + 0x00000000)
#define PMIO_PON_PBS_REVISION1_OFFS                                           0x00000000
#define PMIO_PON_PBS_REVISION1_RMSK                                                 0xff
#define PMIO_PON_PBS_REVISION1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION1_ADDR, PMIO_PON_PBS_REVISION1_RMSK, 0, val)
#define PMIO_PON_PBS_REVISION1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_REVISION1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_REVISION1_ADDR, val, len)
#define PMIO_PON_PBS_REVISION1_DIG_MINOR_BMSK                                       0xff
#define PMIO_PON_PBS_REVISION1_DIG_MINOR_SHFT                                        0x0

#define PMIO_PON_PBS_REVISION2_ADDR                                           (PON_PBS_BASE      + 0x00000001)
#define PMIO_PON_PBS_REVISION2_OFFS                                           0x00000001
#define PMIO_PON_PBS_REVISION2_RMSK                                                 0xff
#define PMIO_PON_PBS_REVISION2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION2_ADDR, PMIO_PON_PBS_REVISION2_RMSK, 0, val)
#define PMIO_PON_PBS_REVISION2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_REVISION2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_REVISION2_ADDR, val, len)
#define PMIO_PON_PBS_REVISION2_DIG_MAJOR_BMSK                                       0xff
#define PMIO_PON_PBS_REVISION2_DIG_MAJOR_SHFT                                        0x0

#define PMIO_PON_PBS_REVISION3_ADDR                                           (PON_PBS_BASE      + 0x00000002)
#define PMIO_PON_PBS_REVISION3_OFFS                                           0x00000002
#define PMIO_PON_PBS_REVISION3_RMSK                                                 0xff
#define PMIO_PON_PBS_REVISION3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION3_ADDR, PMIO_PON_PBS_REVISION3_RMSK, 0, val)
#define PMIO_PON_PBS_REVISION3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_REVISION3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_REVISION3_ADDR, val, len)
#define PMIO_PON_PBS_REVISION3_ANA_MINOR_BMSK                                       0xff
#define PMIO_PON_PBS_REVISION3_ANA_MINOR_SHFT                                        0x0

#define PMIO_PON_PBS_REVISION4_ADDR                                           (PON_PBS_BASE      + 0x00000003)
#define PMIO_PON_PBS_REVISION4_OFFS                                           0x00000003
#define PMIO_PON_PBS_REVISION4_RMSK                                                 0xff
#define PMIO_PON_PBS_REVISION4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION4_ADDR, PMIO_PON_PBS_REVISION4_RMSK, 0, val)
#define PMIO_PON_PBS_REVISION4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REVISION4_ADDR, mask, shift, val)
#define PMIO_PON_PBS_REVISION4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_REVISION4_ADDR, val, len)
#define PMIO_PON_PBS_REVISION4_ANA_MAJOR_BMSK                                       0xff
#define PMIO_PON_PBS_REVISION4_ANA_MAJOR_SHFT                                        0x0

#define PMIO_PON_PBS_PERPH_TYPE_ADDR                                          (PON_PBS_BASE      + 0x00000004)
#define PMIO_PON_PBS_PERPH_TYPE_OFFS                                          0x00000004
#define PMIO_PON_PBS_PERPH_TYPE_RMSK                                                0xff
#define PMIO_PON_PBS_PERPH_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_TYPE_ADDR, PMIO_PON_PBS_PERPH_TYPE_RMSK, 0, val)
#define PMIO_PON_PBS_PERPH_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_TYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_TYPE_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_TYPE_TYPE_BMSK                                           0xff
#define PMIO_PON_PBS_PERPH_TYPE_TYPE_SHFT                                            0x0

#define PMIO_PON_PBS_PERPH_SUBTYPE_ADDR                                       (PON_PBS_BASE      + 0x00000005)
#define PMIO_PON_PBS_PERPH_SUBTYPE_OFFS                                       0x00000005
#define PMIO_PON_PBS_PERPH_SUBTYPE_RMSK                                             0xff
#define PMIO_PON_PBS_PERPH_SUBTYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_SUBTYPE_ADDR, PMIO_PON_PBS_PERPH_SUBTYPE_RMSK, 0, val)
#define PMIO_PON_PBS_PERPH_SUBTYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_SUBTYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_SUBTYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_SUBTYPE_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_SUBTYPE_SUBTYPE_BMSK                                     0xff
#define PMIO_PON_PBS_PERPH_SUBTYPE_SUBTYPE_SHFT                                      0x0

#define PMIO_PON_PBS_SOFT_TYPE_ADDR                                           (PON_PBS_BASE      + 0x00000006)
#define PMIO_PON_PBS_SOFT_TYPE_OFFS                                           0x00000006
#define PMIO_PON_PBS_SOFT_TYPE_RMSK                                                 0xff
#define PMIO_PON_PBS_SOFT_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, PMIO_PON_PBS_SOFT_TYPE_RMSK, 0, val)
#define PMIO_PON_PBS_SOFT_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_SOFT_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, val, len)
#define PMIO_PON_PBS_SOFT_TYPE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, val)
#define PMIO_PON_PBS_SOFT_TYPE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_SOFT_TYPE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_SOFT_TYPE_ADDR, val, len)
#define PMIO_PON_PBS_SOFT_TYPE_SOFTTYPE_BMSK                                        0xff
#define PMIO_PON_PBS_SOFT_TYPE_SOFTTYPE_SHFT                                         0x0

#define PMIO_PON_PBS_PON_PBL_STATUS_ADDR                                      (PON_PBS_BASE      + 0x00000007)
#define PMIO_PON_PBS_PON_PBL_STATUS_OFFS                                      0x00000007
#define PMIO_PON_PBS_PON_PBL_STATUS_RMSK                                            0xc0
#define PMIO_PON_PBS_PON_PBL_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PON_PBL_STATUS_ADDR, PMIO_PON_PBS_PON_PBL_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_PON_PBL_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PON_PBL_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PON_PBL_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PON_PBL_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_PON_PBL_STATUS_DVDD_RB_OCCURRED_BMSK                           0x80
#define PMIO_PON_PBS_PON_PBL_STATUS_DVDD_RB_OCCURRED_SHFT                            0x7
#define PMIO_PON_PBS_PON_PBL_STATUS_XVDD_RB_OCCURRED_BMSK                           0x40
#define PMIO_PON_PBS_PON_PBL_STATUS_XVDD_RB_OCCURRED_SHFT                            0x6

#define PMIO_PON_PBS_HW_FSM_STATUS_ADDR                                       (PON_PBS_BASE      + 0x00000008)
#define PMIO_PON_PBS_HW_FSM_STATUS_OFFS                                       0x00000008
#define PMIO_PON_PBS_HW_FSM_STATUS_RMSK                                              0x1
#define PMIO_PON_PBS_HW_FSM_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_HW_FSM_STATUS_ADDR, PMIO_PON_PBS_HW_FSM_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_HW_FSM_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_HW_FSM_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_HW_FSM_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_HW_FSM_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_HW_FSM_STATUS_FSM_STATE_BMSK                                    0x1
#define PMIO_PON_PBS_HW_FSM_STATUS_FSM_STATE_SHFT                                    0x0

#define PMIO_PON_PBS_PBS_FSM_STATUS_ADDR                                      (PON_PBS_BASE      + 0x00000009)
#define PMIO_PON_PBS_PBS_FSM_STATUS_OFFS                                      0x00000009
#define PMIO_PON_PBS_PBS_FSM_STATUS_RMSK                                            0xff
#define PMIO_PON_PBS_PBS_FSM_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, PMIO_PON_PBS_PBS_FSM_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_PBS_FSM_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PBS_FSM_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_PBS_FSM_STATUS_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, val)
#define PMIO_PON_PBS_PBS_FSM_STATUS_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PBS_FSM_STATUS_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PBS_FSM_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_PBS_FSM_STATUS_PBS_FSM_STATE_BMSK                              0xff
#define PMIO_PON_PBS_PBS_FSM_STATUS_PBS_FSM_STATE_SHFT                               0x0

#define PMIO_PON_PBS_PAR1_ADDR                                                (PON_PBS_BASE      + 0x0000000a)
#define PMIO_PON_PBS_PAR1_OFFS                                                0x0000000a
#define PMIO_PON_PBS_PAR1_RMSK                                                      0xff
#define PMIO_PON_PBS_PAR1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PAR1_ADDR, PMIO_PON_PBS_PAR1_RMSK, 0, val)
#define PMIO_PON_PBS_PAR1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PAR1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PAR1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PAR1_ADDR, val, len)
#define PMIO_PON_PBS_PAR1_KPD_TYPE_BMSK                                             0xc0
#define PMIO_PON_PBS_PAR1_KPD_TYPE_SHFT                                              0x6
#define PMIO_PON_PBS_PAR1_RESIN_TYPE_BMSK                                           0x30
#define PMIO_PON_PBS_PAR1_RESIN_TYPE_SHFT                                            0x4
#define PMIO_PON_PBS_PAR1_HAS_KPD_RESIN_BMSK                                         0x8
#define PMIO_PON_PBS_PAR1_HAS_KPD_RESIN_SHFT                                         0x3
#define PMIO_PON_PBS_PAR1_HAS_XVLO_BMSK                                              0x4
#define PMIO_PON_PBS_PAR1_HAS_XVLO_SHFT                                              0x2
#define PMIO_PON_PBS_PAR1_PSHOLD_TYPE_BMSK                                           0x2
#define PMIO_PON_PBS_PAR1_PSHOLD_TYPE_SHFT                                           0x1
#define PMIO_PON_PBS_PAR1_PON_RESET_N_TYPE_BMSK                                      0x1
#define PMIO_PON_PBS_PAR1_PON_RESET_N_TYPE_SHFT                                      0x0

#define PMIO_PON_PBS_PAR2_ADDR                                                (PON_PBS_BASE      + 0x0000000b)
#define PMIO_PON_PBS_PAR2_OFFS                                                0x0000000b
#define PMIO_PON_PBS_PAR2_RMSK                                                      0xb0
#define PMIO_PON_PBS_PAR2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PAR2_ADDR, PMIO_PON_PBS_PAR2_RMSK, 0, val)
#define PMIO_PON_PBS_PAR2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PAR2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PAR2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PAR2_ADDR, val, len)
#define PMIO_PON_PBS_PAR2_HAS_PMIC_WDOG_BMSK                                        0x80
#define PMIO_PON_PBS_PAR2_HAS_PMIC_WDOG_SHFT                                         0x7
#define PMIO_PON_PBS_PAR2_NUM_OF_RESET_TRIGGER_BMSK                                 0x30
#define PMIO_PON_PBS_PAR2_NUM_OF_RESET_TRIGGER_SHFT                                  0x4

#define PMIO_PON_PBS_INT_RT_STS_ADDR                                          (PON_PBS_BASE      + 0x00000010)
#define PMIO_PON_PBS_INT_RT_STS_OFFS                                          0x00000010
#define PMIO_PON_PBS_INT_RT_STS_RMSK                                                0xff
#define PMIO_PON_PBS_INT_RT_STS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_RT_STS_ADDR, PMIO_PON_PBS_INT_RT_STS_RMSK, 0, val)
#define PMIO_PON_PBS_INT_RT_STS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_RT_STS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_RT_STS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_RT_STS_ADDR, val, len)
#define PMIO_PON_PBS_INT_RT_STS_KPD_PWR_N_DEB_BMSK                                  0x80
#define PMIO_PON_PBS_INT_RT_STS_KPD_PWR_N_DEB_SHFT                                   0x7
#define PMIO_PON_PBS_INT_RT_STS_RESIN_N_DEB_BMSK                                    0x40
#define PMIO_PON_PBS_INT_RT_STS_RESIN_N_DEB_SHFT                                     0x6
#define PMIO_PON_PBS_INT_RT_STS_SW_RESET_BMSK                                       0x20
#define PMIO_PON_PBS_INT_RT_STS_SW_RESET_SHFT                                        0x5
#define PMIO_PON_PBS_INT_RT_STS_PS_HOLD_BMSK                                        0x10
#define PMIO_PON_PBS_INT_RT_STS_PS_HOLD_SHFT                                         0x4
#define PMIO_PON_PBS_INT_RT_STS_PMIC_WDOG_S2_BMSK                                    0x8
#define PMIO_PON_PBS_INT_RT_STS_PMIC_WDOG_S2_SHFT                                    0x3
#define PMIO_PON_PBS_INT_RT_STS_RESIN_AND_KPDPWR_S2_BMSK                             0x4
#define PMIO_PON_PBS_INT_RT_STS_RESIN_AND_KPDPWR_S2_SHFT                             0x2
#define PMIO_PON_PBS_INT_RT_STS_RESIN_N_S2_BMSK                                      0x2
#define PMIO_PON_PBS_INT_RT_STS_RESIN_N_S2_SHFT                                      0x1
#define PMIO_PON_PBS_INT_RT_STS_KPD_PWR_N_S2_BMSK                                    0x1
#define PMIO_PON_PBS_INT_RT_STS_KPD_PWR_N_S2_SHFT                                    0x0

#define PMIO_PON_PBS_INT_SET_TYPE_ADDR                                        (PON_PBS_BASE      + 0x00000011)
#define PMIO_PON_PBS_INT_SET_TYPE_OFFS                                        0x00000011
#define PMIO_PON_PBS_INT_SET_TYPE_RMSK                                              0xff
#define PMIO_PON_PBS_INT_SET_TYPE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, PMIO_PON_PBS_INT_SET_TYPE_RMSK, 0, val)
#define PMIO_PON_PBS_INT_SET_TYPE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_SET_TYPE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, val, len)
#define PMIO_PON_PBS_INT_SET_TYPE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, val)
#define PMIO_PON_PBS_INT_SET_TYPE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_SET_TYPE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_SET_TYPE_ADDR, val, len)
#define PMIO_PON_PBS_INT_SET_TYPE_KPD_PWR_N_DEB_BMSK                                0x80
#define PMIO_PON_PBS_INT_SET_TYPE_KPD_PWR_N_DEB_SHFT                                 0x7
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_N_DEB_BMSK                                  0x40
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_N_DEB_SHFT                                   0x6
#define PMIO_PON_PBS_INT_SET_TYPE_SW_RESET_BMSK                                     0x20
#define PMIO_PON_PBS_INT_SET_TYPE_SW_RESET_SHFT                                      0x5
#define PMIO_PON_PBS_INT_SET_TYPE_PS_HOLD_BMSK                                      0x10
#define PMIO_PON_PBS_INT_SET_TYPE_PS_HOLD_SHFT                                       0x4
#define PMIO_PON_PBS_INT_SET_TYPE_PMIC_WDOG_S2_BMSK                                  0x8
#define PMIO_PON_PBS_INT_SET_TYPE_PMIC_WDOG_S2_SHFT                                  0x3
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_AND_KPDPWR_S2_BMSK                           0x4
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_AND_KPDPWR_S2_SHFT                           0x2
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_N_S2_BMSK                                    0x2
#define PMIO_PON_PBS_INT_SET_TYPE_RESIN_N_S2_SHFT                                    0x1
#define PMIO_PON_PBS_INT_SET_TYPE_KPD_PWR_N_S2_BMSK                                  0x1
#define PMIO_PON_PBS_INT_SET_TYPE_KPD_PWR_N_S2_SHFT                                  0x0

#define PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR                                   (PON_PBS_BASE      + 0x00000012)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_OFFS                                   0x00000012
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RMSK                                         0xff
#define PMIO_PON_PBS_INT_POLARITY_HIGH_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, PMIO_PON_PBS_INT_POLARITY_HIGH_RMSK, 0, val)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, val, len)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, val)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, val, len)
#define PMIO_PON_PBS_INT_POLARITY_HIGH_KPD_PWR_N_DEB_BMSK                           0x80
#define PMIO_PON_PBS_INT_POLARITY_HIGH_KPD_PWR_N_DEB_SHFT                            0x7
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_N_DEB_BMSK                             0x40
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_N_DEB_SHFT                              0x6
#define PMIO_PON_PBS_INT_POLARITY_HIGH_SW_RESET_BMSK                                0x20
#define PMIO_PON_PBS_INT_POLARITY_HIGH_SW_RESET_SHFT                                 0x5
#define PMIO_PON_PBS_INT_POLARITY_HIGH_PS_HOLD_BMSK                                 0x10
#define PMIO_PON_PBS_INT_POLARITY_HIGH_PS_HOLD_SHFT                                  0x4
#define PMIO_PON_PBS_INT_POLARITY_HIGH_PMIC_WDOG_S2_BMSK                             0x8
#define PMIO_PON_PBS_INT_POLARITY_HIGH_PMIC_WDOG_S2_SHFT                             0x3
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_AND_KPDPWR_S2_BMSK                      0x4
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_AND_KPDPWR_S2_SHFT                      0x2
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_N_S2_BMSK                               0x2
#define PMIO_PON_PBS_INT_POLARITY_HIGH_RESIN_N_S2_SHFT                               0x1
#define PMIO_PON_PBS_INT_POLARITY_HIGH_KPD_PWR_N_S2_BMSK                             0x1
#define PMIO_PON_PBS_INT_POLARITY_HIGH_KPD_PWR_N_S2_SHFT                             0x0

#define PMIO_PON_PBS_INT_POLARITY_LOW_ADDR                                    (PON_PBS_BASE      + 0x00000013)
#define PMIO_PON_PBS_INT_POLARITY_LOW_OFFS                                    0x00000013
#define PMIO_PON_PBS_INT_POLARITY_LOW_RMSK                                          0xff
#define PMIO_PON_PBS_INT_POLARITY_LOW_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, PMIO_PON_PBS_INT_POLARITY_LOW_RMSK, 0, val)
#define PMIO_PON_PBS_INT_POLARITY_LOW_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_POLARITY_LOW_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, val, len)
#define PMIO_PON_PBS_INT_POLARITY_LOW_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, val)
#define PMIO_PON_PBS_INT_POLARITY_LOW_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_POLARITY_LOW_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, val, len)
#define PMIO_PON_PBS_INT_POLARITY_LOW_KPD_PWR_N_DEB_BMSK                            0x80
#define PMIO_PON_PBS_INT_POLARITY_LOW_KPD_PWR_N_DEB_SHFT                             0x7
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_N_DEB_BMSK                              0x40
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_N_DEB_SHFT                               0x6
#define PMIO_PON_PBS_INT_POLARITY_LOW_SW_RESET_BMSK                                 0x20
#define PMIO_PON_PBS_INT_POLARITY_LOW_SW_RESET_SHFT                                  0x5
#define PMIO_PON_PBS_INT_POLARITY_LOW_PS_HOLD_BMSK                                  0x10
#define PMIO_PON_PBS_INT_POLARITY_LOW_PS_HOLD_SHFT                                   0x4
#define PMIO_PON_PBS_INT_POLARITY_LOW_PMIC_WDOG_S2_BMSK                              0x8
#define PMIO_PON_PBS_INT_POLARITY_LOW_PMIC_WDOG_S2_SHFT                              0x3
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_AND_KPDPWR_S2_BMSK                       0x4
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_AND_KPDPWR_S2_SHFT                       0x2
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_N_S2_BMSK                                0x2
#define PMIO_PON_PBS_INT_POLARITY_LOW_RESIN_N_S2_SHFT                                0x1
#define PMIO_PON_PBS_INT_POLARITY_LOW_KPD_PWR_N_S2_BMSK                              0x1
#define PMIO_PON_PBS_INT_POLARITY_LOW_KPD_PWR_N_S2_SHFT                              0x0

#define PMIO_PON_PBS_INT_LATCHED_CLR_ADDR                                     (PON_PBS_BASE      + 0x00000014)
#define PMIO_PON_PBS_INT_LATCHED_CLR_OFFS                                     0x00000014
#define PMIO_PON_PBS_INT_LATCHED_CLR_RMSK                                           0xff
#define PMIO_PON_PBS_INT_LATCHED_CLR_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_LATCHED_CLR_ADDR, val)
#define PMIO_PON_PBS_INT_LATCHED_CLR_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_LATCHED_CLR_ADDR, val, len)
#define PMIO_PON_PBS_INT_LATCHED_CLR_KPD_PWR_N_DEB_BMSK                             0x80
#define PMIO_PON_PBS_INT_LATCHED_CLR_KPD_PWR_N_DEB_SHFT                              0x7
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_N_DEB_BMSK                               0x40
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_N_DEB_SHFT                                0x6
#define PMIO_PON_PBS_INT_LATCHED_CLR_SW_RESET_BMSK                                  0x20
#define PMIO_PON_PBS_INT_LATCHED_CLR_SW_RESET_SHFT                                   0x5
#define PMIO_PON_PBS_INT_LATCHED_CLR_PS_HOLD_BMSK                                   0x10
#define PMIO_PON_PBS_INT_LATCHED_CLR_PS_HOLD_SHFT                                    0x4
#define PMIO_PON_PBS_INT_LATCHED_CLR_PMIC_WDOG_S2_BMSK                               0x8
#define PMIO_PON_PBS_INT_LATCHED_CLR_PMIC_WDOG_S2_SHFT                               0x3
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_AND_KPDPWR_S2_BMSK                        0x4
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_AND_KPDPWR_S2_SHFT                        0x2
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_N_S2_BMSK                                 0x2
#define PMIO_PON_PBS_INT_LATCHED_CLR_RESIN_N_S2_SHFT                                 0x1
#define PMIO_PON_PBS_INT_LATCHED_CLR_KPD_PWR_N_S2_BMSK                               0x1
#define PMIO_PON_PBS_INT_LATCHED_CLR_KPD_PWR_N_S2_SHFT                               0x0

#define PMIO_PON_PBS_INT_EN_SET_ADDR                                          (PON_PBS_BASE      + 0x00000015)
#define PMIO_PON_PBS_INT_EN_SET_OFFS                                          0x00000015
#define PMIO_PON_PBS_INT_EN_SET_RMSK                                                0xff
#define PMIO_PON_PBS_INT_EN_SET_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, PMIO_PON_PBS_INT_EN_SET_RMSK, 0, val)
#define PMIO_PON_PBS_INT_EN_SET_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_EN_SET_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, val, len)
#define PMIO_PON_PBS_INT_EN_SET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, val)
#define PMIO_PON_PBS_INT_EN_SET_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_EN_SET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_EN_SET_ADDR, val, len)
#define PMIO_PON_PBS_INT_EN_SET_KPD_PWR_N_DEB_BMSK                                  0x80
#define PMIO_PON_PBS_INT_EN_SET_KPD_PWR_N_DEB_SHFT                                   0x7
#define PMIO_PON_PBS_INT_EN_SET_RESIN_N_DEB_BMSK                                    0x40
#define PMIO_PON_PBS_INT_EN_SET_RESIN_N_DEB_SHFT                                     0x6
#define PMIO_PON_PBS_INT_EN_SET_SW_RESET_BMSK                                       0x20
#define PMIO_PON_PBS_INT_EN_SET_SW_RESET_SHFT                                        0x5
#define PMIO_PON_PBS_INT_EN_SET_PS_HOLD_BMSK                                        0x10
#define PMIO_PON_PBS_INT_EN_SET_PS_HOLD_SHFT                                         0x4
#define PMIO_PON_PBS_INT_EN_SET_PMIC_WDOG_S2_BMSK                                    0x8
#define PMIO_PON_PBS_INT_EN_SET_PMIC_WDOG_S2_SHFT                                    0x3
#define PMIO_PON_PBS_INT_EN_SET_RESIN_AND_KPDPWR_S2_BMSK                             0x4
#define PMIO_PON_PBS_INT_EN_SET_RESIN_AND_KPDPWR_S2_SHFT                             0x2
#define PMIO_PON_PBS_INT_EN_SET_RESIN_N_S2_BMSK                                      0x2
#define PMIO_PON_PBS_INT_EN_SET_RESIN_N_S2_SHFT                                      0x1
#define PMIO_PON_PBS_INT_EN_SET_KPD_PWR_N_S2_BMSK                                    0x1
#define PMIO_PON_PBS_INT_EN_SET_KPD_PWR_N_S2_SHFT                                    0x0

#define PMIO_PON_PBS_INT_EN_CLR_ADDR                                          (PON_PBS_BASE      + 0x00000016)
#define PMIO_PON_PBS_INT_EN_CLR_OFFS                                          0x00000016
#define PMIO_PON_PBS_INT_EN_CLR_RMSK                                                0xff
#define PMIO_PON_PBS_INT_EN_CLR_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, PMIO_PON_PBS_INT_EN_CLR_RMSK, 0, val)
#define PMIO_PON_PBS_INT_EN_CLR_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_EN_CLR_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, val, len)
#define PMIO_PON_PBS_INT_EN_CLR_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, val)
#define PMIO_PON_PBS_INT_EN_CLR_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_EN_CLR_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_EN_CLR_ADDR, val, len)
#define PMIO_PON_PBS_INT_EN_CLR_KPD_PWR_N_DEB_BMSK                                  0x80
#define PMIO_PON_PBS_INT_EN_CLR_KPD_PWR_N_DEB_SHFT                                   0x7
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_N_DEB_BMSK                                    0x40
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_N_DEB_SHFT                                     0x6
#define PMIO_PON_PBS_INT_EN_CLR_SW_RESET_BMSK                                       0x20
#define PMIO_PON_PBS_INT_EN_CLR_SW_RESET_SHFT                                        0x5
#define PMIO_PON_PBS_INT_EN_CLR_PS_HOLD_BMSK                                        0x10
#define PMIO_PON_PBS_INT_EN_CLR_PS_HOLD_SHFT                                         0x4
#define PMIO_PON_PBS_INT_EN_CLR_PMIC_WDOG_S2_BMSK                                    0x8
#define PMIO_PON_PBS_INT_EN_CLR_PMIC_WDOG_S2_SHFT                                    0x3
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_AND_KPDPWR_S2_BMSK                             0x4
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_AND_KPDPWR_S2_SHFT                             0x2
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_N_S2_BMSK                                      0x2
#define PMIO_PON_PBS_INT_EN_CLR_RESIN_N_S2_SHFT                                      0x1
#define PMIO_PON_PBS_INT_EN_CLR_KPD_PWR_N_S2_BMSK                                    0x1
#define PMIO_PON_PBS_INT_EN_CLR_KPD_PWR_N_S2_SHFT                                    0x0

#define PMIO_PON_PBS_INT_LATCHED_STS_ADDR                                     (PON_PBS_BASE      + 0x00000018)
#define PMIO_PON_PBS_INT_LATCHED_STS_OFFS                                     0x00000018
#define PMIO_PON_PBS_INT_LATCHED_STS_RMSK                                           0xff
#define PMIO_PON_PBS_INT_LATCHED_STS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_LATCHED_STS_ADDR, PMIO_PON_PBS_INT_LATCHED_STS_RMSK, 0, val)
#define PMIO_PON_PBS_INT_LATCHED_STS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_LATCHED_STS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_LATCHED_STS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_LATCHED_STS_ADDR, val, len)
#define PMIO_PON_PBS_INT_LATCHED_STS_KPD_PWR_N_DEB_BMSK                             0x80
#define PMIO_PON_PBS_INT_LATCHED_STS_KPD_PWR_N_DEB_SHFT                              0x7
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_N_DEB_BMSK                               0x40
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_N_DEB_SHFT                                0x6
#define PMIO_PON_PBS_INT_LATCHED_STS_SW_RESET_BMSK                                  0x20
#define PMIO_PON_PBS_INT_LATCHED_STS_SW_RESET_SHFT                                   0x5
#define PMIO_PON_PBS_INT_LATCHED_STS_PS_HOLD_BMSK                                   0x10
#define PMIO_PON_PBS_INT_LATCHED_STS_PS_HOLD_SHFT                                    0x4
#define PMIO_PON_PBS_INT_LATCHED_STS_PMIC_WDOG_S2_BMSK                               0x8
#define PMIO_PON_PBS_INT_LATCHED_STS_PMIC_WDOG_S2_SHFT                               0x3
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_AND_KPDPWR_S2_BMSK                        0x4
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_AND_KPDPWR_S2_SHFT                        0x2
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_N_S2_BMSK                                 0x2
#define PMIO_PON_PBS_INT_LATCHED_STS_RESIN_N_S2_SHFT                                 0x1
#define PMIO_PON_PBS_INT_LATCHED_STS_KPD_PWR_N_S2_BMSK                               0x1
#define PMIO_PON_PBS_INT_LATCHED_STS_KPD_PWR_N_S2_SHFT                               0x0

#define PMIO_PON_PBS_INT_PENDING_STS_ADDR                                     (PON_PBS_BASE      + 0x00000019)
#define PMIO_PON_PBS_INT_PENDING_STS_OFFS                                     0x00000019
#define PMIO_PON_PBS_INT_PENDING_STS_RMSK                                           0xff
#define PMIO_PON_PBS_INT_PENDING_STS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_PENDING_STS_ADDR, PMIO_PON_PBS_INT_PENDING_STS_RMSK, 0, val)
#define PMIO_PON_PBS_INT_PENDING_STS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_PENDING_STS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_PENDING_STS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_PENDING_STS_ADDR, val, len)
#define PMIO_PON_PBS_INT_PENDING_STS_KPD_PWR_N_DEB_BMSK                             0x80
#define PMIO_PON_PBS_INT_PENDING_STS_KPD_PWR_N_DEB_SHFT                              0x7
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_N_DEB_BMSK                               0x40
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_N_DEB_SHFT                                0x6
#define PMIO_PON_PBS_INT_PENDING_STS_SW_RESET_BMSK                                  0x20
#define PMIO_PON_PBS_INT_PENDING_STS_SW_RESET_SHFT                                   0x5
#define PMIO_PON_PBS_INT_PENDING_STS_PS_HOLD_BMSK                                   0x10
#define PMIO_PON_PBS_INT_PENDING_STS_PS_HOLD_SHFT                                    0x4
#define PMIO_PON_PBS_INT_PENDING_STS_PMIC_WDOG_S2_BMSK                               0x8
#define PMIO_PON_PBS_INT_PENDING_STS_PMIC_WDOG_S2_SHFT                               0x3
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_AND_KPDPWR_S2_BMSK                        0x4
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_AND_KPDPWR_S2_SHFT                        0x2
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_N_S2_BMSK                                 0x2
#define PMIO_PON_PBS_INT_PENDING_STS_RESIN_N_S2_SHFT                                 0x1
#define PMIO_PON_PBS_INT_PENDING_STS_KPD_PWR_N_S2_BMSK                               0x1
#define PMIO_PON_PBS_INT_PENDING_STS_KPD_PWR_N_S2_SHFT                               0x0

#define PMIO_PON_PBS_INT_MID_SEL_ADDR                                         (PON_PBS_BASE      + 0x0000001a)
#define PMIO_PON_PBS_INT_MID_SEL_OFFS                                         0x0000001a
#define PMIO_PON_PBS_INT_MID_SEL_RMSK                                                0x3
#define PMIO_PON_PBS_INT_MID_SEL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, PMIO_PON_PBS_INT_MID_SEL_RMSK, 0, val)
#define PMIO_PON_PBS_INT_MID_SEL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_MID_SEL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, val, len)
#define PMIO_PON_PBS_INT_MID_SEL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, val)
#define PMIO_PON_PBS_INT_MID_SEL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_MID_SEL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_MID_SEL_ADDR, val, len)
#define PMIO_PON_PBS_INT_MID_SEL_INT_MID_SEL_BMSK                                    0x3
#define PMIO_PON_PBS_INT_MID_SEL_INT_MID_SEL_SHFT                                    0x0

#define PMIO_PON_PBS_INT_PRIORITY_ADDR                                        (PON_PBS_BASE      + 0x0000001b)
#define PMIO_PON_PBS_INT_PRIORITY_OFFS                                        0x0000001b
#define PMIO_PON_PBS_INT_PRIORITY_RMSK                                               0x1
#define PMIO_PON_PBS_INT_PRIORITY_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, PMIO_PON_PBS_INT_PRIORITY_RMSK, 0, val)
#define PMIO_PON_PBS_INT_PRIORITY_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_PRIORITY_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, val, len)
#define PMIO_PON_PBS_INT_PRIORITY_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, val)
#define PMIO_PON_PBS_INT_PRIORITY_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_PRIORITY_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_PRIORITY_ADDR, val, len)
#define PMIO_PON_PBS_INT_PRIORITY_INT_PRIORITY_BMSK                                  0x1
#define PMIO_PON_PBS_INT_PRIORITY_INT_PRIORITY_SHFT                                  0x0

#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR                             (PON_PBS_BASE      + 0x00000040)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_OFFS                             0x00000040
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_RMSK                                    0xf
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_BMSK                           0xf
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_SHFT                           0x0

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR                             (PON_PBS_BASE      + 0x00000041)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_OFFS                             0x00000041
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_RMSK                                    0x7
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_BMSK                           0x7
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_SHFT                           0x0

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR                            (PON_PBS_BASE      + 0x00000042)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_OFFS                            0x00000042
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RMSK                                  0xff
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RESET_TYPE_BMSK                       0xff
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RESET_TYPE_SHFT                        0x0

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR                              (PON_PBS_BASE      + 0x00000043)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_OFFS                              0x00000043
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_RMSK                                    0x80
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_RMSK, 0, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_BMSK                        0x80
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_SHFT                         0x7

#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR                              (PON_PBS_BASE      + 0x00000044)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_OFFS                              0x00000044
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_RMSK                                     0xf
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_S1_TIMER_BMSK                            0xf
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_S1_TIMER_SHFT                            0x0

#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR                              (PON_PBS_BASE      + 0x00000045)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_OFFS                              0x00000045
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_RMSK                                     0x7
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_S2_TIMER_BMSK                            0x7
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_S2_TIMER_SHFT                            0x0

#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR                                (PON_PBS_BASE      + 0x00000046)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_OFFS                                0x00000046
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RMSK                                      0xff
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RESET_TYPE_BMSK                           0xff
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RESET_TYPE_SHFT                            0x0

#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR                               (PON_PBS_BASE      + 0x00000047)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_OFFS                               0x00000047
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_RMSK                                     0x80
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_BMSK                         0x80
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_SHFT                          0x7

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR                     (PON_PBS_BASE      + 0x00000048)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_OFFS                     0x00000048
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_RMSK                            0xf
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_BMSK                   0xf
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_SHFT                   0x0

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR                     (PON_PBS_BASE      + 0x00000049)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_OFFS                     0x00000049
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_RMSK                            0x7
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_BMSK                   0x7
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_SHFT                   0x0

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR                       (PON_PBS_BASE      + 0x0000004a)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_OFFS                       0x0000004a
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RMSK                             0xff
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RESET_TYPE_BMSK                  0xff
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RESET_TYPE_SHFT                   0x0

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR                      (PON_PBS_BASE      + 0x0000004b)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_OFFS                      0x0000004b
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_RMSK                            0x80
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_RMSK, 0, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_BMSK                0x80
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_SHFT                 0x7

#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR                              (PON_PBS_BASE      + 0x0000004c)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_OFFS                              0x0000004c
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_RMSK                                    0x7f
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_S1_TIMER_BMSK                           0x7f
#define PMIO_PON_PBS_PMIC_WD_RESET_S1_TIMER_S1_TIMER_SHFT                            0x0

#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR                              (PON_PBS_BASE      + 0x0000004d)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_OFFS                              0x0000004d
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_RMSK                                    0x7f
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_S2_TIMER_BMSK                           0x7f
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_TIMER_S2_TIMER_SHFT                            0x0

#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR                                (PON_PBS_BASE      + 0x0000004e)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_OFFS                                0x0000004e
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_RMSK                                      0xff
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_RESET_TYPE_BMSK                           0xff
#define PMIO_PON_PBS_PMIC_WD_RESET_SW_CTL_RESET_TYPE_SHFT                            0x0

#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR                               (PON_PBS_BASE      + 0x0000004f)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_OFFS                               0x0000004f
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_RMSK                                     0x80
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_RMSK, 0, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_S2_RESET_EN_BMSK                         0x80
#define PMIO_PON_PBS_PMIC_WD_RESET_S2_CTL2_S2_RESET_EN_SHFT                          0x7

#define PMIO_PON_PBS_PMIC_WD_RESET_PET_ADDR                                   (PON_PBS_BASE      + 0x00000050)
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_OFFS                                   0x00000050
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_RMSK                                          0x1
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_PET_ADDR, val)
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PMIC_WD_RESET_PET_ADDR, val, len)
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_WATCHDOG_PET_BMSK                             0x1
#define PMIO_PON_PBS_PMIC_WD_RESET_PET_WATCHDOG_PET_SHFT                             0x0

#define PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR                                      (PON_PBS_BASE      + 0x00000052)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_OFFS                                      0x00000052
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_RMSK                                            0xff
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, PMIO_PON_PBS_PS_HOLD_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_RESET_TYPE_BMSK                                 0xff
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_RESET_TYPE_SHFT                                  0x0

#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR                                  (PON_PBS_BASE      + 0x00000053)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_OFFS                                  0x00000053
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_RMSK                                        0x80
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_RMSK, 0, val)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, val)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR, val, len)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK                            0x80
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_S2_RESET_EN_SHFT                             0x7

#define PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR                                     (PON_PBS_BASE      + 0x00000056)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_OFFS                                     0x00000056
#define PMIO_PON_PBS_SW_RESET_SW_CTL_RMSK                                           0xff
#define PMIO_PON_PBS_SW_RESET_SW_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, PMIO_PON_PBS_SW_RESET_SW_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, val)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR, val, len)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_RESET_TYPE_BMSK                                0xff
#define PMIO_PON_PBS_SW_RESET_SW_CTL_RESET_TYPE_SHFT                                 0x0

#define PMIO_PON_PBS_SW_RESET_GO_ADDR                                         (PON_PBS_BASE      + 0x00000057)
#define PMIO_PON_PBS_SW_RESET_GO_OFFS                                         0x00000057
#define PMIO_PON_PBS_SW_RESET_GO_RMSK                                               0xff
#define PMIO_PON_PBS_SW_RESET_GO_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_SW_RESET_GO_ADDR, val)
#define PMIO_PON_PBS_SW_RESET_GO_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_SW_RESET_GO_ADDR, val, len)
#define PMIO_PON_PBS_SW_RESET_GO_SW_RESET_GO_BMSK                                   0xff
#define PMIO_PON_PBS_SW_RESET_GO_SW_RESET_GO_SHFT                                    0x0

#define PMIO_PON_PBS_PON_SW_CFG_ADDR                                         (PON_PBS_BASE      + 0x00000060)
#define PMIO_PON_PBS_PON_SW_CFG_OFFS                                         0x00000060
#define PMIO_PON_PBS_PON_SW_CFG_WARM_RESET_RMSK                                    0x80

#define PMIO_PON_PBS_PULL_CTL_ADDR                                            (PON_PBS_BASE      + 0x00000070)
#define PMIO_PON_PBS_PULL_CTL_OFFS                                            0x00000070
#define PMIO_PON_PBS_PULL_CTL_RMSK                                                   0xf
#define PMIO_PON_PBS_PULL_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, PMIO_PON_PBS_PULL_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_PULL_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PULL_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PULL_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, val)
#define PMIO_PON_PBS_PULL_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PULL_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PULL_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PULL_CTL_PON1_PD_EN_BMSK                                        0x8
#define PMIO_PON_PBS_PULL_CTL_PON1_PD_EN_SHFT                                        0x3
#define PMIO_PON_PBS_PULL_CTL_CBLPWR_N_PU_EN_BMSK                                    0x4
#define PMIO_PON_PBS_PULL_CTL_CBLPWR_N_PU_EN_SHFT                                    0x2
#define PMIO_PON_PBS_PULL_CTL_KPDPWR_N_PU_EN_BMSK                                    0x2
#define PMIO_PON_PBS_PULL_CTL_KPDPWR_N_PU_EN_SHFT                                    0x1
#define PMIO_PON_PBS_PULL_CTL_RESIN_N_PU_EN_BMSK                                     0x1
#define PMIO_PON_PBS_PULL_CTL_RESIN_N_PU_EN_SHFT                                     0x0

#define PMIO_PON_PBS_DEBOUNCE_CTL_ADDR                                        (PON_PBS_BASE      + 0x00000071)
#define PMIO_PON_PBS_DEBOUNCE_CTL_OFFS                                        0x00000071
#define PMIO_PON_PBS_DEBOUNCE_CTL_RMSK                                               0xf
#define PMIO_PON_PBS_DEBOUNCE_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, PMIO_PON_PBS_DEBOUNCE_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_DEBOUNCE_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DEBOUNCE_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, val, len)
#define PMIO_PON_PBS_DEBOUNCE_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, val)
#define PMIO_PON_PBS_DEBOUNCE_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DEBOUNCE_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DEBOUNCE_CTL_ADDR, val, len)
#define PMIO_PON_PBS_DEBOUNCE_CTL_DEBOUNCE_BMSK                                      0xf
#define PMIO_PON_PBS_DEBOUNCE_CTL_DEBOUNCE_SHFT                                      0x0

#define PMIO_PON_PBS_RESET_S3_SRC_ADDR                                        (PON_PBS_BASE      + 0x00000074)
#define PMIO_PON_PBS_RESET_S3_SRC_OFFS                                        0x00000074
#define PMIO_PON_PBS_RESET_S3_SRC_RMSK                                               0x3
#define PMIO_PON_PBS_RESET_S3_SRC_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, PMIO_PON_PBS_RESET_S3_SRC_RMSK, 0, val)
#define PMIO_PON_PBS_RESET_S3_SRC_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESET_S3_SRC_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, val, len)
#define PMIO_PON_PBS_RESET_S3_SRC_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, val)
#define PMIO_PON_PBS_RESET_S3_SRC_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESET_S3_SRC_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESET_S3_SRC_ADDR, val, len)
#define PMIO_PON_PBS_RESET_S3_SRC_RESET_S3_SOURCE_BMSK                               0x3
#define PMIO_PON_PBS_RESET_S3_SRC_RESET_S3_SOURCE_SHFT                               0x0

#define PMIO_PON_PBS_RESET_S3_TIMER_ADDR                                      (PON_PBS_BASE      + 0x00000075)
#define PMIO_PON_PBS_RESET_S3_TIMER_OFFS                                      0x00000075
#define PMIO_PON_PBS_RESET_S3_TIMER_RMSK                                             0xf
#define PMIO_PON_PBS_RESET_S3_TIMER_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, PMIO_PON_PBS_RESET_S3_TIMER_RMSK, 0, val)
#define PMIO_PON_PBS_RESET_S3_TIMER_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESET_S3_TIMER_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESET_S3_TIMER_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, val)
#define PMIO_PON_PBS_RESET_S3_TIMER_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, mask, shift, val)
#define PMIO_PON_PBS_RESET_S3_TIMER_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, val, len)
#define PMIO_PON_PBS_RESET_S3_TIMER_S3_TIMER_BMSK                                    0xf
#define PMIO_PON_PBS_RESET_S3_TIMER_S3_TIMER_SHFT                                    0x0

#define PMIO_PON_PBS_UVLO_CTL_ADDR                                            (PON_PBS_BASE      + 0x00000084)
#define PMIO_PON_PBS_UVLO_CTL_UVLO_EN_SHIFT                                          0x7
#define PMIO_PON_PBS_UVLO_CTL_UVLO_HYST_SHIFT                                        0x5

#define PMIO_PON_PBS_UVLO_RB_STATUS_ADDR                                      (PON_PBS_BASE      + 0x00000085)
#define PMIO_PON_PBS_UVLO_RB_STATUS_OFFS                                      0x00000085
#define PMIO_PON_PBS_UVLO_RB_STATUS_RMSK                                            0x80
#define PMIO_PON_PBS_UVLO_RB_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_UVLO_RB_STATUS_ADDR, PMIO_PON_PBS_UVLO_RB_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_UVLO_RB_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_UVLO_RB_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_UVLO_RB_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_UVLO_RB_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_UVLO_RB_STATUS_UVLO_RB_BMSK                                    0x80
#define PMIO_PON_PBS_UVLO_RB_STATUS_UVLO_RB_SHFT                                     0x7


#define PMIO_PON_PBS_OVLO_CTL_ADDR                                            (PON_PBS_BASE      + 0x00000086)
#define PMIO_PON_PBS_OVLO_CTL_OVLO_EN_SHIFT                                          0x7
#define PMIO_PON_PBS_OVLO_CTL_OVLO_HYST_SHIFT                                        0x5

#define PMIO_PON_PBS_OVLO_RB_STATUS_ADDR                                      (PON_PBS_BASE      + 0x00000087)
#define PMIO_PON_PBS_OVLO_RB_STATUS_OFFS                                      0x00000087
#define PMIO_PON_PBS_OVLO_RB_STATUS_RMSK                                            0x80
#define PMIO_PON_PBS_OVLO_RB_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_OVLO_RB_STATUS_ADDR, PMIO_PON_PBS_OVLO_RB_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_OVLO_RB_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_OVLO_RB_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_OVLO_RB_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_OVLO_RB_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_OVLO_RB_STATUS_OVLO_RB_BMSK                                    0x80
#define PMIO_PON_PBS_OVLO_RB_STATUS_OVLO_RB_SHFT                                     0x7

#define PMIO_PON_PBS_PERPH_RB_SPARE_ADDR                                      (PON_PBS_BASE      + 0x0000008c)
#define PMIO_PON_PBS_PERPH_RB_SPARE_OFFS                                      0x0000008c
#define PMIO_PON_PBS_PERPH_RB_SPARE_RMSK                                            0xff
#define PMIO_PON_PBS_PERPH_RB_SPARE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, PMIO_PON_PBS_PERPH_RB_SPARE_RMSK, 0, val)
#define PMIO_PON_PBS_PERPH_RB_SPARE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RB_SPARE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RB_SPARE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, val)
#define PMIO_PON_PBS_PERPH_RB_SPARE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RB_SPARE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RB_SPARE_SPARE_BMSK                                      0xff
#define PMIO_PON_PBS_PERPH_RB_SPARE_SPARE_SHFT                                       0x0

#define PMIO_PON_PBS_DVDD_RB_SPARE_ADDR                                       (PON_PBS_BASE      + 0x0000008d)
#define PMIO_PON_PBS_DVDD_RB_SPARE_OFFS                                       0x0000008d
#define PMIO_PON_PBS_DVDD_RB_SPARE_RMSK                                             0xff
#define PMIO_PON_PBS_DVDD_RB_SPARE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, PMIO_PON_PBS_DVDD_RB_SPARE_RMSK, 0, val)
#define PMIO_PON_PBS_DVDD_RB_SPARE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DVDD_RB_SPARE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_DVDD_RB_SPARE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, val)
#define PMIO_PON_PBS_DVDD_RB_SPARE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DVDD_RB_SPARE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DVDD_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_DVDD_RB_SPARE_SPARE_BMSK                                       0xff
#define PMIO_PON_PBS_DVDD_RB_SPARE_SPARE_SHFT                                        0x0

#define PMIO_PON_PBS_XVDD_RB_SPARE_ADDR                                       (PON_PBS_BASE      + 0x0000008e)
#define PMIO_PON_PBS_XVDD_RB_SPARE_OFFS                                       0x0000008e
#define PMIO_PON_PBS_XVDD_RB_SPARE_RMSK                                             0xff
#define PMIO_PON_PBS_XVDD_RB_SPARE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, PMIO_PON_PBS_XVDD_RB_SPARE_RMSK, 0, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_XVDD_RB_SPARE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE_ADDR, val, len)
#define PMIO_PON_PBS_XVDD_RB_SPARE_SPARE_BMSK                                       0xff
#define PMIO_PON_PBS_XVDD_RB_SPARE_SPARE_SHFT                                        0x0

#define PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR                                      (PON_PBS_BASE      + 0x0000008f)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_OFFS                                      0x0000008f
#define PMIO_PON_PBS_XVDD_RB_SPARE2_RMSK                                            0xff
#define PMIO_PON_PBS_XVDD_RB_SPARE2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, PMIO_PON_PBS_XVDD_RB_SPARE2_RMSK, 0, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, val, len)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_XVDD_RB_SPARE2_ADDR, val, len)
#define PMIO_PON_PBS_XVDD_RB_SPARE2_SPARE_BMSK                                      0xff
#define PMIO_PON_PBS_XVDD_RB_SPARE2_SPARE_SHFT                                       0x0

#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR                                 (PON_PBS_BASE      + 0x00000091)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_OFFS                                 0x00000091
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_RMSK                                       0x40
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, PMIO_PON_PBS_FAULT_PBS_INTERFACE_RMSK, 0, val)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, val)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, mask, shift, val)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_INTERFACE_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_ACK_NACK_BMSK                              0x40
#define PMIO_PON_PBS_FAULT_PBS_INTERFACE_ACK_NACK_SHFT                               0x6

#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_ADDR                                  (PON_PBS_BASE      + 0x00000092)
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_OFFS                                  0x00000092
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_RMSK                                        0x80
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_WDOG_PET_ADDR, val)
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_FAULT_PBS_WDOG_PET_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_PBS_WATCHDOG_PET_BMSK                       0x80
#define PMIO_PON_PBS_FAULT_PBS_WDOG_PET_PBS_WATCHDOG_PET_SHFT                        0x7

#define PMIO_PON_PBS_DEBUG_CTL_ADDR                                           (PON_PBS_BASE      + 0x00000094)
#define PMIO_PON_PBS_DEBUG_CTL_OFFS                                           0x00000094
#define PMIO_PON_PBS_DEBUG_CTL_RMSK                                                 0x6f
#define PMIO_PON_PBS_DEBUG_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, PMIO_PON_PBS_DEBUG_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_DEBUG_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DEBUG_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, val, len)
#define PMIO_PON_PBS_DEBUG_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, val)
#define PMIO_PON_PBS_DEBUG_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DEBUG_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DEBUG_CTL_ADDR, val, len)
#define PMIO_PON_PBS_DEBUG_CTL_DEBUG_CLOCK_BMSK                                     0x40
#define PMIO_PON_PBS_DEBUG_CTL_DEBUG_CLOCK_SHFT                                      0x6
#define PMIO_PON_PBS_DEBUG_CTL_DEBUG_CLOCK_SRC_BMSK                                 0x20
#define PMIO_PON_PBS_DEBUG_CTL_DEBUG_CLOCK_SRC_SHFT                                  0x5
#define PMIO_PON_PBS_DEBUG_CTL_SEL_DEBUG_BMSK                                        0xf
#define PMIO_PON_PBS_DEBUG_CTL_SEL_DEBUG_SHFT                                        0x0

#define PMIO_PON_PBS_DEBUG_STATUS_ADDR                                        (PON_PBS_BASE      + 0x00000095)
#define PMIO_PON_PBS_DEBUG_STATUS_OFFS                                        0x00000095
#define PMIO_PON_PBS_DEBUG_STATUS_RMSK                                              0xff
#define PMIO_PON_PBS_DEBUG_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBUG_STATUS_ADDR, PMIO_PON_PBS_DEBUG_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_DEBUG_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DEBUG_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DEBUG_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DEBUG_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_DEBUG_STATUS_DEBUG_STATE_BMSK                                  0xff
#define PMIO_PON_PBS_DEBUG_STATUS_DEBUG_STATE_SHFT                                   0x0

#define PMIO_PON_PBS_VDD_RESET_CTL_ADDR                                       (PON_PBS_BASE      + 0x00000097)
#define PMIO_PON_PBS_VDD_RESET_CTL_OFFS                                       0x00000097
#define PMIO_PON_PBS_VDD_RESET_CTL_RMSK                                              0x3
#define PMIO_PON_PBS_VDD_RESET_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_VDD_RESET_CTL_ADDR, val)
#define PMIO_PON_PBS_VDD_RESET_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_VDD_RESET_CTL_ADDR, val, len)
#define PMIO_PON_PBS_VDD_RESET_CTL_DVDD_RB_BMSK                                      0x2
#define PMIO_PON_PBS_VDD_RESET_CTL_DVDD_RB_SHFT                                      0x1
#define PMIO_PON_PBS_VDD_RESET_CTL_XVDD_RB_BMSK                                      0x1
#define PMIO_PON_PBS_VDD_RESET_CTL_XVDD_RB_SHFT                                      0x0

#define PMIO_PON_PBS_SYS_RESET_CTL_ADDR                                       (PON_PBS_BASE      + 0x00000098)
#define PMIO_PON_PBS_SYS_RESET_CTL_OFFS                                       0x00000098
#define PMIO_PON_PBS_SYS_RESET_CTL_RMSK                                              0x7
#define PMIO_PON_PBS_SYS_RESET_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_SYS_RESET_CTL_ADDR, val)
#define PMIO_PON_PBS_SYS_RESET_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_SYS_RESET_CTL_ADDR, val, len)
#define PMIO_PON_PBS_SYS_RESET_CTL_WARM_RB_BMSK                                      0x4
#define PMIO_PON_PBS_SYS_RESET_CTL_WARM_RB_SHFT                                      0x2
#define PMIO_PON_PBS_SYS_RESET_CTL_SHUTDOWN1_RB_BMSK                                 0x2
#define PMIO_PON_PBS_SYS_RESET_CTL_SHUTDOWN1_RB_SHFT                                 0x1
#define PMIO_PON_PBS_SYS_RESET_CTL_SHUTDOWN2_RB_BMSK                                 0x1
#define PMIO_PON_PBS_SYS_RESET_CTL_SHUTDOWN2_RB_SHFT                                 0x0

#define PMIO_PON_PBS_PON_RESET_N_CTL_ADDR                                     (PON_PBS_BASE      + 0x00000099)
#define PMIO_PON_PBS_PON_RESET_N_CTL_OFFS                                     0x00000099
#define PMIO_PON_PBS_PON_RESET_N_CTL_RMSK                                           0x80
#define PMIO_PON_PBS_PON_RESET_N_CTL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, PMIO_PON_PBS_PON_RESET_N_CTL_RMSK, 0, val)
#define PMIO_PON_PBS_PON_RESET_N_CTL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PON_RESET_N_CTL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PON_RESET_N_CTL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, val)
#define PMIO_PON_PBS_PON_RESET_N_CTL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PON_RESET_N_CTL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PON_RESET_N_CTL_ADDR, val, len)
#define PMIO_PON_PBS_PON_RESET_N_CTL_PON_RESET_N_BMSK                               0x80
#define PMIO_PON_PBS_PON_RESET_N_CTL_PON_RESET_N_SHFT                                0x7

#define PMIO_PON_PBS_PS_HOLD_STATUS_ADDR                                      (PON_PBS_BASE      + 0x0000009a)
#define PMIO_PON_PBS_PS_HOLD_STATUS_OFFS                                      0x0000009a
#define PMIO_PON_PBS_PS_HOLD_STATUS_RMSK                                            0x80
#define PMIO_PON_PBS_PS_HOLD_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_STATUS_ADDR, PMIO_PON_PBS_PS_HOLD_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_PS_HOLD_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PS_HOLD_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PS_HOLD_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_PS_HOLD_STATUS_PS_HOLD_BMSK                                    0x80
#define PMIO_PON_PBS_PS_HOLD_STATUS_PS_HOLD_SHFT                                     0x7

#define PMIO_PON_PBS_FAULT_REASON1_ADDR                                       (PON_PBS_BASE      + 0x000000c7)
#define PMIO_PON_PBS_FAULT_REASON1_OFFS                                       0x000000c7
#define PMIO_PON_PBS_FAULT_REASON1_RMSK                                             0xff
#define PMIO_PON_PBS_FAULT_REASON1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON1_ADDR, PMIO_PON_PBS_FAULT_REASON1_RMSK, 0, val)
#define PMIO_PON_PBS_FAULT_REASON1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_FAULT_REASON1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON1_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_REASON1_AVDD_RB_BMSK                                     0x80
#define PMIO_PON_PBS_FAULT_REASON1_AVDD_RB_SHFT                                      0x7
#define PMIO_PON_PBS_FAULT_REASON1_UVLO_BMSK                                        0x40
#define PMIO_PON_PBS_FAULT_REASON1_UVLO_SHFT                                         0x6
#define PMIO_PON_PBS_FAULT_REASON1_OVLO_BMSK                                        0x20
#define PMIO_PON_PBS_FAULT_REASON1_OVLO_SHFT                                         0x5
#define PMIO_PON_PBS_FAULT_REASON1_MBG_FAULT_BMSK                                   0x10
#define PMIO_PON_PBS_FAULT_REASON1_MBG_FAULT_SHFT                                    0x4
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT3_BMSK                                    0x8
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT3_SHFT                                    0x3
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT2_BMSK                                    0x4
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT2_SHFT                                    0x2
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT1_BMSK                                    0x2
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT1_SHFT                                    0x1
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT0_BMSK                                    0x1
#define PMIO_PON_PBS_FAULT_REASON1_GP_FAULT0_SHFT                                    0x0

#define PMIO_PON_PBS_FAULT_REASON2_ADDR                                       (PON_PBS_BASE      + 0x000000c8)
#define PMIO_PON_PBS_FAULT_REASON2_OFFS                                       0x000000c8
#define PMIO_PON_PBS_FAULT_REASON2_RMSK                                             0xf8
#define PMIO_PON_PBS_FAULT_REASON2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON2_ADDR, PMIO_PON_PBS_FAULT_REASON2_RMSK, 0, val)
#define PMIO_PON_PBS_FAULT_REASON2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_FAULT_REASON2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON2_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_REASON2_OTST3_BMSK                                       0x80
#define PMIO_PON_PBS_FAULT_REASON2_OTST3_SHFT                                        0x7
#define PMIO_PON_PBS_FAULT_REASON2_RESTART_PON_BMSK                                 0x40
#define PMIO_PON_PBS_FAULT_REASON2_RESTART_PON_SHFT                                  0x6
#define PMIO_PON_PBS_FAULT_REASON2_PBS_NACK_BMSK                                    0x20
#define PMIO_PON_PBS_FAULT_REASON2_PBS_NACK_SHFT                                     0x5
#define PMIO_PON_PBS_FAULT_REASON2_PBS_WATCHDOG_TO_BMSK                             0x10
#define PMIO_PON_PBS_FAULT_REASON2_PBS_WATCHDOG_TO_SHFT                              0x4
#define PMIO_PON_PBS_FAULT_REASON2_FAULT_N_BMSK                                      0x8
#define PMIO_PON_PBS_FAULT_REASON2_FAULT_N_SHFT                                      0x3

#define PMIO_PON_PBS_FAULT_REASON3_ADDR                                       (PON_PBS_BASE      + 0x000000c9)
#define PMIO_PON_PBS_FAULT_REASON3_OFFS                                       0x000000c9
#define PMIO_PON_PBS_FAULT_REASON3_RMSK                                             0xff
#define PMIO_PON_PBS_FAULT_REASON3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON3_ADDR, PMIO_PON_PBS_FAULT_REASON3_RMSK, 0, val)
#define PMIO_PON_PBS_FAULT_REASON3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_FAULT_REASON3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_FAULT_REASON3_ADDR, val, len)
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT11_BMSK                                  0x80
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT11_SHFT                                   0x7
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT10_BMSK                                  0x40
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT10_SHFT                                   0x6
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT9_BMSK                                   0x20
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT9_SHFT                                    0x5
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT8_BMSK                                   0x10
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT8_SHFT                                    0x4
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT7_BMSK                                    0x8
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT7_SHFT                                    0x3
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT6_BMSK                                    0x4
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT6_SHFT                                    0x2
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT5_BMSK                                    0x2
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT5_SHFT                                    0x1
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT4_BMSK                                    0x1
#define PMIO_PON_PBS_FAULT_REASON3_GP_FAULT4_SHFT                                    0x0

#define PMIO_PON_PBS_S3_RESET_REASON_ADDR                                     (PON_PBS_BASE      + 0x000000ca)
#define PMIO_PON_PBS_S3_RESET_REASON_OFFS                                     0x000000ca
#define PMIO_PON_PBS_S3_RESET_REASON_RMSK                                           0xf0
#define PMIO_PON_PBS_S3_RESET_REASON_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_S3_RESET_REASON_ADDR, PMIO_PON_PBS_S3_RESET_REASON_RMSK, 0, val)
#define PMIO_PON_PBS_S3_RESET_REASON_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_S3_RESET_REASON_ADDR, mask, shift, val)
#define PMIO_PON_PBS_S3_RESET_REASON_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_S3_RESET_REASON_ADDR, val, len)
#define PMIO_PON_PBS_S3_RESET_REASON_KPDPWR_ANDOR_RESIN_BMSK                        0x80
#define PMIO_PON_PBS_S3_RESET_REASON_KPDPWR_ANDOR_RESIN_SHFT                         0x7
#define PMIO_PON_PBS_S3_RESET_REASON_PBS_NACK_BMSK                                  0x40
#define PMIO_PON_PBS_S3_RESET_REASON_PBS_NACK_SHFT                                   0x6
#define PMIO_PON_PBS_S3_RESET_REASON_PBS_WATCHDOG_TO_BMSK                           0x20
#define PMIO_PON_PBS_S3_RESET_REASON_PBS_WATCHDOG_TO_SHFT                            0x5
#define PMIO_PON_PBS_S3_RESET_REASON_FAULT_N_BMSK                                   0x10
#define PMIO_PON_PBS_S3_RESET_REASON_FAULT_N_SHFT                                    0x4

#define PMIO_PON_PBS_LOCKBIT_D1_ADDR                                          (PON_PBS_BASE      + 0x000000d1)
#define PMIO_PON_PBS_LOCKBIT_D1_OFFS                                          0x000000d1
#define PMIO_PON_PBS_LOCKBIT_D1_RMSK                                                 0x3
#define PMIO_PON_PBS_LOCKBIT_D1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, PMIO_PON_PBS_LOCKBIT_D1_RMSK, 0, val)
#define PMIO_PON_PBS_LOCKBIT_D1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_LOCKBIT_D1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PON_PBS_LOCKBIT_D1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, val)
#define PMIO_PON_PBS_LOCKBIT_D1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_LOCKBIT_D1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_LOCKBIT_D1_ADDR, val, len)
#define PMIO_PON_PBS_LOCKBIT_D1_LOCKBIT_D1_BMSK                                      0x3
#define PMIO_PON_PBS_LOCKBIT_D1_LOCKBIT_D1_SHFT                                      0x0

#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR                                (PON_PBS_BASE      + 0x000000d4)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_OFFS                                0x000000d4
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_RMSK                                       0x1
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, val)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_BMSK                            0x1
#define PMIO_PON_PBS_ILLEGAL_WRITE_STATUS_LOCKBIT_D1_SHFT                            0x0

#define PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR                                    (PON_PBS_BASE      + 0x000000da)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_OFFS                                    0x000000da
#define PMIO_PON_PBS_PERPH_RESET_CTL3_RMSK                                           0x5
#define PMIO_PON_PBS_PERPH_RESET_CTL3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, PMIO_PON_PBS_PERPH_RESET_CTL3_RMSK, 0, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                            0x4
#define PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                            0x2
#define PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                       0x1
#define PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                       0x0

#define PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR                                    (PON_PBS_BASE      + 0x000000db)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_OFFS                                    0x000000db
#define PMIO_PON_PBS_PERPH_RESET_CTL4_RMSK                                           0x1
#define PMIO_PON_PBS_PERPH_RESET_CTL4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, PMIO_PON_PBS_PERPH_RESET_CTL4_RMSK, 0, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, mask, shift, val)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_PERPH_RESET_CTL4_ADDR, val, len)
#define PMIO_PON_PBS_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                          0x1
#define PMIO_PON_PBS_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                          0x0

#define PMIO_PON_PBS_INT_TEST1_ADDR                                           (PON_PBS_BASE      + 0x000000e0)
#define PMIO_PON_PBS_INT_TEST1_OFFS                                           0x000000e0
#define PMIO_PON_PBS_INT_TEST1_RMSK                                                 0x80
#define PMIO_PON_PBS_INT_TEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, PMIO_PON_PBS_INT_TEST1_RMSK, 0, val)
#define PMIO_PON_PBS_INT_TEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_TEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, val, len)
#define PMIO_PON_PBS_INT_TEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, val)
#define PMIO_PON_PBS_INT_TEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_TEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_TEST1_ADDR, val, len)
#define PMIO_PON_PBS_INT_TEST1_INT_TEST_MODE_EN_BMSK                                0x80
#define PMIO_PON_PBS_INT_TEST1_INT_TEST_MODE_EN_SHFT                                 0x7

#define PMIO_PON_PBS_INT_TEST_VAL_ADDR                                        (PON_PBS_BASE      + 0x000000e1)
#define PMIO_PON_PBS_INT_TEST_VAL_OFFS                                        0x000000e1
#define PMIO_PON_PBS_INT_TEST_VAL_RMSK                                              0xff
#define PMIO_PON_PBS_INT_TEST_VAL_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, PMIO_PON_PBS_INT_TEST_VAL_RMSK, 0, val)
#define PMIO_PON_PBS_INT_TEST_VAL_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_TEST_VAL_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, val, len)
#define PMIO_PON_PBS_INT_TEST_VAL_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, val)
#define PMIO_PON_PBS_INT_TEST_VAL_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, mask, shift, val)
#define PMIO_PON_PBS_INT_TEST_VAL_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_INT_TEST_VAL_ADDR, val, len)
#define PMIO_PON_PBS_INT_TEST_VAL_KPD_PWR_N_DEB_BMSK                                0x80
#define PMIO_PON_PBS_INT_TEST_VAL_KPD_PWR_N_DEB_SHFT                                 0x7
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_N_DEB_BMSK                                  0x40
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_N_DEB_SHFT                                   0x6
#define PMIO_PON_PBS_INT_TEST_VAL_SW_RESET_BMSK                                     0x20
#define PMIO_PON_PBS_INT_TEST_VAL_SW_RESET_SHFT                                      0x5
#define PMIO_PON_PBS_INT_TEST_VAL_PS_HOLD_BMSK                                      0x10
#define PMIO_PON_PBS_INT_TEST_VAL_PS_HOLD_SHFT                                       0x4
#define PMIO_PON_PBS_INT_TEST_VAL_PMIC_WDOG_S2_BMSK                                  0x8
#define PMIO_PON_PBS_INT_TEST_VAL_PMIC_WDOG_S2_SHFT                                  0x3
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_AND_KPDPWR_S2_BMSK                           0x4
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_AND_KPDPWR_S2_SHFT                           0x2
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_N_S2_BMSK                                    0x2
#define PMIO_PON_PBS_INT_TEST_VAL_RESIN_N_S2_SHFT                                    0x1
#define PMIO_PON_PBS_INT_TEST_VAL_KPD_PWR_N_S2_BMSK                                  0x1
#define PMIO_PON_PBS_INT_TEST_VAL_KPD_PWR_N_S2_SHFT                                  0x0

#define PMIO_PON_PBS_DTEST1_ADDR                                              (PON_PBS_BASE      + 0x000000e2)
#define PMIO_PON_PBS_DTEST1_OFFS                                              0x000000e2
#define PMIO_PON_PBS_DTEST1_RMSK                                                    0x3f
#define PMIO_PON_PBS_DTEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, PMIO_PON_PBS_DTEST1_RMSK, 0, val)
#define PMIO_PON_PBS_DTEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, val, len)
#define PMIO_PON_PBS_DTEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, val)
#define PMIO_PON_PBS_DTEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DTEST1_ADDR, val, len)
#define PMIO_PON_PBS_DTEST1_SEL_BMSK                                                0x3f
#define PMIO_PON_PBS_DTEST1_SEL_SHFT                                                 0x0

#define PMIO_PON_PBS_DTEST2_ADDR                                              (PON_PBS_BASE      + 0x000000e3)
#define PMIO_PON_PBS_DTEST2_OFFS                                              0x000000e3
#define PMIO_PON_PBS_DTEST2_RMSK                                                    0x3f
#define PMIO_PON_PBS_DTEST2_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, PMIO_PON_PBS_DTEST2_RMSK, 0, val)
#define PMIO_PON_PBS_DTEST2_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST2_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, val, len)
#define PMIO_PON_PBS_DTEST2_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, val)
#define PMIO_PON_PBS_DTEST2_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST2_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DTEST2_ADDR, val, len)
#define PMIO_PON_PBS_DTEST2_SEL_BMSK                                                0x3f
#define PMIO_PON_PBS_DTEST2_SEL_SHFT                                                 0x0

#define PMIO_PON_PBS_DTEST3_ADDR                                              (PON_PBS_BASE      + 0x000000e4)
#define PMIO_PON_PBS_DTEST3_OFFS                                              0x000000e4
#define PMIO_PON_PBS_DTEST3_RMSK                                                    0x3f
#define PMIO_PON_PBS_DTEST3_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, PMIO_PON_PBS_DTEST3_RMSK, 0, val)
#define PMIO_PON_PBS_DTEST3_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST3_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, val, len)
#define PMIO_PON_PBS_DTEST3_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, val)
#define PMIO_PON_PBS_DTEST3_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST3_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DTEST3_ADDR, val, len)
#define PMIO_PON_PBS_DTEST3_SEL_BMSK                                                0x3f
#define PMIO_PON_PBS_DTEST3_SEL_SHFT                                                 0x0

#define PMIO_PON_PBS_DTEST4_ADDR                                              (PON_PBS_BASE      + 0x000000e5)
#define PMIO_PON_PBS_DTEST4_OFFS                                              0x000000e5
#define PMIO_PON_PBS_DTEST4_RMSK                                                    0x3f
#define PMIO_PON_PBS_DTEST4_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, PMIO_PON_PBS_DTEST4_RMSK, 0, val)
#define PMIO_PON_PBS_DTEST4_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST4_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, val, len)
#define PMIO_PON_PBS_DTEST4_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, val)
#define PMIO_PON_PBS_DTEST4_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, mask, shift, val)
#define PMIO_PON_PBS_DTEST4_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_DTEST4_ADDR, val, len)
#define PMIO_PON_PBS_DTEST4_SEL_BMSK                                                0x3f
#define PMIO_PON_PBS_DTEST4_SEL_SHFT                                                 0x0

#define PMIO_PON_PBS_TEST5_ADDR                                               (PON_PBS_BASE      + 0x000000e6)
#define PMIO_PON_PBS_TEST5_OFFS                                               0x000000e6
#define PMIO_PON_PBS_TEST5_RMSK                                                     0x18
#define PMIO_PON_PBS_TEST5_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, PMIO_PON_PBS_TEST5_RMSK, 0, val)
#define PMIO_PON_PBS_TEST5_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, mask, shift, val)
#define PMIO_PON_PBS_TEST5_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, val, len)
#define PMIO_PON_PBS_TEST5_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, val)
#define PMIO_PON_PBS_TEST5_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, mask, shift, val)
#define PMIO_PON_PBS_TEST5_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_TEST5_ADDR, val, len)
#define PMIO_PON_PBS_TEST5_MASK_SHUTDOWN2_RB_BMSK                                   0x10
#define PMIO_PON_PBS_TEST5_MASK_SHUTDOWN2_RB_SHFT                                    0x4
#define PMIO_PON_PBS_TEST5_MASK_WARM_RB_BMSK                                         0x8
#define PMIO_PON_PBS_TEST5_MASK_WARM_RB_SHFT                                         0x3

#define PMIO_PON_PBS_TEST7_ADDR                                               (PON_PBS_BASE      + 0x000000e8)
#define PMIO_PON_PBS_TEST7_OFFS                                               0x000000e8
#define PMIO_PON_PBS_TEST7_RMSK                                                      0x7
#define PMIO_PON_PBS_TEST7_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, PMIO_PON_PBS_TEST7_RMSK, 0, val)
#define PMIO_PON_PBS_TEST7_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, mask, shift, val)
#define PMIO_PON_PBS_TEST7_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, val, len)
#define PMIO_PON_PBS_TEST7_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, val)
#define PMIO_PON_PBS_TEST7_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, mask, shift, val)
#define PMIO_PON_PBS_TEST7_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_TEST7_ADDR, val, len)
#define PMIO_PON_PBS_TEST7_FAULT_N_LOOPBACK_BMSK                                     0x4
#define PMIO_PON_PBS_TEST7_FAULT_N_LOOPBACK_SHFT                                     0x2
#define PMIO_PON_PBS_TEST7_DISCONNECT_FAULT_N_BMSK                                   0x2
#define PMIO_PON_PBS_TEST7_DISCONNECT_FAULT_N_SHFT                                   0x1
#define PMIO_PON_PBS_TEST7_IGNORE_FAULT_N_BMSK                                       0x1
#define PMIO_PON_PBS_TEST7_IGNORE_FAULT_N_SHFT                                       0x0

#define PMIO_PON_PBS_UVLO_TEST1_ADDR                                          (PON_PBS_BASE      + 0x000000e9)
#define PMIO_PON_PBS_UVLO_TEST1_OFFS                                          0x000000e9
#define PMIO_PON_PBS_UVLO_TEST1_RMSK                                                0xc0
#define PMIO_PON_PBS_UVLO_TEST1_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, PMIO_PON_PBS_UVLO_TEST1_RMSK, 0, val)
#define PMIO_PON_PBS_UVLO_TEST1_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_UVLO_TEST1_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, val, len)
#define PMIO_PON_PBS_UVLO_TEST1_OUT(ctxt, pmic, val)\
        out_pmio(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, val)
#define PMIO_PON_PBS_UVLO_TEST1_OUTF(ctxt, pmic, mask, shift, val)\
        out_pmio_field(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, mask, shift, val)
#define PMIO_PON_PBS_UVLO_TEST1_OUTN(ctxt, pmic, val, len)\
        out_pmio_array(ctxt, pmic, PMIO_PON_PBS_UVLO_TEST1_ADDR, val, len)
#define PMIO_PON_PBS_UVLO_TEST1_UVLO_TEST_EN_BMSK                                   0x80
#define PMIO_PON_PBS_UVLO_TEST1_UVLO_TEST_EN_SHFT                                    0x7
#define PMIO_PON_PBS_UVLO_TEST1_OVLO_TEST_EN_BMSK                                   0x40
#define PMIO_PON_PBS_UVLO_TEST1_OVLO_TEST_EN_SHFT                                    0x6

#define PMIO_PON_PBS_REG_WRITE_STATUS_ADDR                                    (PON_PBS_BASE      + 0x000000ef)
#define PMIO_PON_PBS_REG_WRITE_STATUS_OFFS                                    0x000000ef
#define PMIO_PON_PBS_REG_WRITE_STATUS_RMSK                                          0x81
#define PMIO_PON_PBS_REG_WRITE_STATUS_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REG_WRITE_STATUS_ADDR, PMIO_PON_PBS_REG_WRITE_STATUS_RMSK, 0, val)
#define PMIO_PON_PBS_REG_WRITE_STATUS_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_REG_WRITE_STATUS_ADDR, mask, shift, val)
#define PMIO_PON_PBS_REG_WRITE_STATUS_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_REG_WRITE_STATUS_ADDR, val, len)
#define PMIO_PON_PBS_REG_WRITE_STATUS_WR_RDY_BMSK                                   0x80
#define PMIO_PON_PBS_REG_WRITE_STATUS_WR_RDY_SHFT                                    0x7
#define PMIO_PON_PBS_REG_WRITE_STATUS_WR_ILG_BMSK                                    0x1
#define PMIO_PON_PBS_REG_WRITE_STATUS_WR_ILG_SHFT                                    0x0

#define PMIO_PON_PBS_TRIM_NUM_ADDR                                            (PON_PBS_BASE      + 0x000000f0)
#define PMIO_PON_PBS_TRIM_NUM_OFFS                                            0x000000f0
#define PMIO_PON_PBS_TRIM_NUM_RMSK                                                  0xff
#define PMIO_PON_PBS_TRIM_NUM_IN(ctxt, pmic, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TRIM_NUM_ADDR, PMIO_PON_PBS_TRIM_NUM_RMSK, 0, val)
#define PMIO_PON_PBS_TRIM_NUM_INF(ctxt, pmic, mask, shift, val)\
        in_pmio_field(ctxt, pmic, PMIO_PON_PBS_TRIM_NUM_ADDR, mask, shift, val)
#define PMIO_PON_PBS_TRIM_NUM_INN(ctxt, pmic, val, len)\
        in_pmio(ctxt, pmic, PMIO_PON_PBS_TRIM_NUM_ADDR, val, len)
#define PMIO_PON_PBS_TRIM_NUM_TRIM_NUM_BMSK                                         0xff
#define PMIO_PON_PBS_TRIM_NUM_TRIM_NUM_SHFT                                          0x0


#endif /* __PM_PON_PBS_PMIO_H__ */
