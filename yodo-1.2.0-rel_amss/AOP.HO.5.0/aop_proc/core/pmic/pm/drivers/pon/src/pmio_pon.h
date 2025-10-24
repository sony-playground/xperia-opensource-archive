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

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pon/src/pmio_pon.h#1 $
  $Author: pwbldsvc $
  $DateTime: 2021/10/26 22:03:12 $
  Copyright (c) 2013 - 2021 Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pon/src/pmio_pon.h#1 $
  $DateTime: 2021/10/26 22:03:12 $
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


#define PMIO_PON_PBS_PERPH_SUBTYPE_ADDR                                       (PON_PBS_BASE      + 0x00000005)



#define PMIO_PON_PBS_INT_SET_TYPE_ADDR                                        (PON_PBS_BASE      + 0x00000011)


#define PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR                                   (PON_PBS_BASE      + 0x00000012)


#define PMIO_PON_PBS_INT_POLARITY_LOW_ADDR                                    (PON_PBS_BASE      + 0x00000013)


#define PMIO_PON_PBS_INT_LATCHED_CLR_ADDR                                     (PON_PBS_BASE      + 0x00000014)


#define PMIO_PON_PBS_INT_EN_SET_ADDR                                          (PON_PBS_BASE      + 0x00000015)

#define PMIO_PON_PBS_INT_EN_CLR_ADDR                                          (PON_PBS_BASE      + 0x00000016)

#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR                             (PON_PBS_BASE      + 0x00000040)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_BMSK                           0xf

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR                             (PON_PBS_BASE      + 0x00000041)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_BMSK                           0x7

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR                            (PON_PBS_BASE      + 0x00000042)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RESET_TYPE_BMSK                       0xff

#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR                              (PON_PBS_BASE      + 0x00000043)
#define PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_BMSK                        0x80

#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR                              (PON_PBS_BASE      + 0x00000044)
#define PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_S1_TIMER_BMSK                            0xf

#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR                              (PON_PBS_BASE      + 0x00000045)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_S2_TIMER_BMSK                            0x7

#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR                                (PON_PBS_BASE      + 0x00000046)
#define PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RESET_TYPE_BMSK                           0xff

#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR                               (PON_PBS_BASE      + 0x00000047)
#define PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_BMSK                         0x80

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR                     (PON_PBS_BASE      + 0x00000048)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_BMSK                   0xf

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR                     (PON_PBS_BASE      + 0x00000049)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_BMSK                   0x7

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR                       (PON_PBS_BASE      + 0x0000004a)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RESET_TYPE_BMSK                  0xff

#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR                      (PON_PBS_BASE      + 0x0000004b)
#define PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_BMSK                0x80

#define PMIO_PON_PBS_PS_HOLD_SW_CTL_ADDR                                      (PON_PBS_BASE      + 0x00000052)
#define PMIO_PON_PBS_PS_HOLD_SW_CTL_RESET_TYPE_BMSK                                 0xff

#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_ADDR                                  (PON_PBS_BASE      + 0x00000053)
#define PMIO_PON_PBS_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK                            0x80

#define PMIO_PON_PBS_SW_RESET_SW_CTL_ADDR                                     (PON_PBS_BASE      + 0x00000056)
#define PMIO_PON_PBS_SW_RESET_SW_CTL_OFFS                                     0x00000056
#define PMIO_PON_PBS_SW_RESET_SW_CTL_RMSK                                           0xff

#define PMIO_PON_PBS_RESET_S3_SRC_ADDR                                        (PON_PBS_BASE      + 0x00000074)
#define PMIO_PON_PBS_RESET_S3_SRC_RMSK                                               0x3


#define PMIO_PON_PBS_RESET_S3_TIMER_ADDR                                      (PON_PBS_BASE      + 0x00000075)
#define PMIO_PON_PBS_RESET_S3_TIMER_RMSK                                             0xf


//PON GEN2 macros
#define PON_BASE                         0x00000800
#define PMIO_PON_REVISION2_ADDR (PON_BASE + 0x00000001)
#define PMIO_PON_PERPH_TYPE_ADDR (PON_BASE + 0x00000004) 
#define PMIO_PON_PERPH_SUBTYPE_ADDR (PON_BASE + 0x00000005)
#define PMIO_PON_WARM_RESET_REASON1_ADDR (PON_BASE + 0x0000000a)
#define PMIO_PON_DVDD_RB_SPARE_ADDR (PON_BASE + 0x0000008d) 

#define PMIO_PON_GP1_RESET_S1_TIMER_ADDR (PON_BASE + 0x00000050)
#define PMIO_PON_GP1_RESET_S1_TIMER_S1_TIMER_BMSK 0xf 
#define PMIO_PON_GP1_RESET_S2_TIMER_ADDR (PON_BASE + 0x00000051)
#define PMIO_PON_GP1_RESET_S2_TIMER_S2_TIMER_BMSK 0x7 
#define PMIO_PON_GP1_RESET_S2_CTL_ADDR (PON_BASE + 0x00000052) 
#define PMIO_PON_GP1_RESET_S2_CTL2_ADDR (PON_BASE + 0x00000053) 
#define PMIO_PON_GP1_RESET_S2_CTL2_S2_RESET_EN_BMSK 0x80 
#define PMIO_PON_GP1_RESET_S2_CTL_RESET_TYPE_BMSK 0xf

#define PMIO_PON_GP2_RESET_S1_TIMER_ADDR (PON_BASE + 0x0000004c) 
#define PMIO_PON_GP2_RESET_S1_TIMER_S1_TIMER_BMSK 0xf
#define PMIO_PON_GP2_RESET_S2_TIMER_ADDR (PON_BASE + 0x0000004d)
#define PMIO_PON_GP2_RESET_S2_TIMER_S2_TIMER_BMSK 0x7
#define PMIO_PON_GP2_RESET_S2_CTL_ADDR (PON_BASE + 0x0000004e)
#define PMIO_PON_GP2_RESET_S2_CTL2_ADDR (PON_BASE + 0x0000004f)
#define PMIO_PON_GP2_RESET_S2_CTL2_S2_RESET_EN_BMSK 0x80 
#define PMIO_PON_GP2_RESET_S2_CTL_RESET_TYPE_BMSK 0xf

#define PMIO_PON_PS_HOLD_RESET_CTL_ADDR (PON_BASE + 0x0000005a)
#define PMIO_PON_PS_HOLD_RESET_CTL2_ADDR (PON_BASE + 0x0000005b)
#define PMIO_PON_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK 0x80 
#define PMIO_PON_PS_HOLD_RESET_CTL_RESET_TYPE_BMSK 0xf 

#define PMIO_PON_PON_TRIGGER_EN_ADDR                                      (PON_BASE      + 0x00000080)
#define PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_BMSK                                   0x80
#define PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_SHFT                                    0x7
#define PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_BMSK                                   0x40
#define PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_SHFT                                    0x6
#define PMIO_PON_PON_TRIGGER_EN_PON1_BMSK                                       0x20
#define PMIO_PON_PON_TRIGGER_EN_PON1_SHFT                                        0x5
#define PMIO_PON_PON_TRIGGER_EN_USB_CHG_BMSK                                    0x10
#define PMIO_PON_PON_TRIGGER_EN_USB_CHG_SHFT                                     0x4
#define PMIO_PON_PON_TRIGGER_EN_DC_CHG_BMSK                                      0x8
#define PMIO_PON_PON_TRIGGER_EN_DC_CHG_SHFT                                      0x3
#define PMIO_PON_PON_TRIGGER_EN_RTC_BMSK                                         0x4
#define PMIO_PON_PON_TRIGGER_EN_RTC_SHFT                                         0x2
#define PMIO_PON_PON_TRIGGER_EN_SMPL_BMSK                                        0x2
#define PMIO_PON_PON_TRIGGER_EN_SMPL_SHFT                                        0x1
#endif /* __PM_PON_PBS_PMIO_H__ */