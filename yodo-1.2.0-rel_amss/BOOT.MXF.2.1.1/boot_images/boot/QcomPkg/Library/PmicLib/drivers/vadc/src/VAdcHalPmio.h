#ifndef __VADCHALPMIO_H__
#define __VADCHALPMIO_H__

/*
===========================================================================
*/
/**
  @file AdcPmio.h
  @brief Auto-generated PMIO interface include file.

  This file contains PMIO register definitions for the following modules:
    ADC_FG1_USR

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2019 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc/src/VAdcHalPmio.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: ADC_FG1_USR
 *--------------------------------------------------------------------------*/

#define PMIO_REVISION1_ADDR(x)                                                ((x) + 0x00000000)
#define PMIO_REVISION1_RMSK                                                         0xff
#define PMIO_REVISION1_DIG_MINOR_BMSK                                               0xff
#define PMIO_REVISION1_DIG_MINOR_SHFT                                                0x0

#define PMIO_REVISION2_ADDR(x)                                                ((x) + 0x00000001)
#define PMIO_REVISION2_RMSK                                                         0xff
#define PMIO_REVISION2_DIG_MAJOR_BMSK                                               0xff
#define PMIO_REVISION2_DIG_MAJOR_SHFT                                                0x0

#define PMIO_PERPH_TYPE_ADDR(x)                                               ((x) + 0x00000004)
#define PMIO_PERPH_TYPE_RMSK                                                        0xff
#define PMIO_PERPH_TYPE_TYPE_BMSK                                                   0xff
#define PMIO_PERPH_TYPE_TYPE_SHFT                                                    0x0

#define PMIO_PERPH_SUBTYPE_ADDR(x)                                            ((x) + 0x00000005)
#define PMIO_PERPH_SUBTYPE_RMSK                                                     0xff
#define PMIO_PERPH_SUBTYPE_SUBTYPE_BMSK                                             0xff
#define PMIO_PERPH_SUBTYPE_SUBTYPE_SHFT                                              0x0

#define PMIO_STATUS1_ADDR(x)                                                  ((x) + 0x00000008)
#define PMIO_STATUS1_RMSK                                                            0x83
#define PMIO_STATUS1_CONV_FAULT_BMSK                                                 0x80
#define PMIO_STATUS1_CONV_FAULT_SHFT                                                 0x7
#define PMIO_STATUS1_CONV_FAULT_NO_CONV_FAULT_FVAL                                   0x0
#define PMIO_STATUS1_CONV_FAULT_CONV_FAULT_FVAL                                      0x1
#define PMIO_STATUS1_REQ_STS_BMSK                                                    0x2
#define PMIO_STATUS1_REQ_STS_SHFT                                                    0x1
#define PMIO_STATUS1_REQ_STS_REQ_NOT_IN_PROGRESS_FVAL                                0x0
#define PMIO_STATUS1_REQ_STS_REQ_IN_PROGRESS_FVAL                                    0x1
#define PMIO_STATUS1_EOC_BMSK                                                        0x1
#define PMIO_STATUS1_EOC_SHFT                                                        0x0
#define PMIO_STATUS1_EOC_CONV_NOT_COMPLETE_FVAL                                      0x0
#define PMIO_STATUS1_EOC_CONV_COMPLETE_FVAL                                          0x1

#define PMIO_INT_RT_STS_ADDR(x)                                               ((x) + 0x00000010)
#define PMIO_INT_RT_STS_RMSK                                                         0x1
#define PMIO_INT_RT_STS_EOC_INT_RT_STS_BMSK                                          0x1
#define PMIO_INT_RT_STS_EOC_INT_RT_STS_SHFT                                          0x0
#define PMIO_INT_RT_STS_EOC_INT_RT_STS_CONV_COMPLETE_INT_FALSE_FVAL                  0x0
#define PMIO_INT_RT_STS_EOC_INT_RT_STS_CONV_COMPLETE_INT_TRUE_FVAL                   0x1

#define PMIO_INT_SET_TYPE_ADDR(x)                                             ((x) + 0x00000011)
#define PMIO_INT_SET_TYPE_RMSK                                                       0x1
#define PMIO_INT_SET_TYPE_EOC_SET_INT_TYPE_BMSK                                      0x1
#define PMIO_INT_SET_TYPE_EOC_SET_INT_TYPE_SHFT                                      0x0
#define PMIO_INT_SET_TYPE_EOC_SET_INT_TYPE_EOC_LEVEL_FVAL                            0x0
#define PMIO_INT_SET_TYPE_EOC_SET_INT_TYPE_EOC_EDGE_FVAL                             0x1

#define PMIO_INT_POLARITY_HIGH_ADDR(x)                                        ((x) + 0x00000012)
#define PMIO_INT_POLARITY_HIGH_RMSK                                                  0x1
#define PMIO_INT_POLARITY_HIGH_EOC_INT_HIGH_BMSK                                     0x1
#define PMIO_INT_POLARITY_HIGH_EOC_INT_HIGH_SHFT                                     0x0
#define PMIO_INT_POLARITY_HIGH_EOC_INT_HIGH_EOC_INT_POL_HIGH_DISABLED_FVAL           0x0
#define PMIO_INT_POLARITY_HIGH_EOC_INT_HIGH_EOC_INT_POL_HIGH_ENABLED_FVAL            0x1

#define PMIO_INT_POLARITY_LOW_ADDR(x)                                         ((x) + 0x00000013)
#define PMIO_INT_POLARITY_LOW_RMSK                                                   0x1
#define PMIO_INT_POLARITY_LOW_EOC_INT_LOW_BMSK                                       0x1
#define PMIO_INT_POLARITY_LOW_EOC_INT_LOW_SHFT                                       0x0
#define PMIO_INT_POLARITY_LOW_EOC_INT_LOW_EOC_INT_POL_LOW_DISABLED_FVAL              0x0
#define PMIO_INT_POLARITY_LOW_EOC_INT_LOW_EOC_INT_POL_LOW_ENABLED_FVAL               0x1

#define PMIO_INT_LATCHED_CLR_ADDR(x)                                          ((x) + 0x00000014)
#define PMIO_INT_LATCHED_CLR_RMSK                                                    0x1
#define PMIO_INT_LATCHED_CLR_EOC_INT_LATCHED_CLR_BMSK                                0x1
#define PMIO_INT_LATCHED_CLR_EOC_INT_LATCHED_CLR_SHFT                                0x0

#define PMIO_INT_EN_SET_ADDR(x)                                               ((x) + 0x00000015)
#define PMIO_INT_EN_SET_RMSK                                                         0x1
#define PMIO_INT_EN_SET_EOC_INT_EN_SET_BMSK                                          0x1
#define PMIO_INT_EN_SET_EOC_INT_EN_SET_SHFT                                          0x0
#define PMIO_INT_EN_SET_EOC_INT_EN_SET_EOC_INT_DISABLED_FVAL                         0x0
#define PMIO_INT_EN_SET_EOC_INT_EN_SET_EOC_INT_ENBLED_FVAL                           0x1

#define PMIO_INT_EN_CLR_ADDR(x)                                               ((x) + 0x00000016)
#define PMIO_INT_EN_CLR_RMSK                                                         0x1
#define PMIO_INT_EN_CLR_EOC_INT_EN_CLR_BMSK                                          0x1
#define PMIO_INT_EN_CLR_EOC_INT_EN_CLR_SHFT                                          0x0
#define PMIO_INT_EN_CLR_EOC_INT_EN_CLR_EOC_INT_DISABLED_FVAL                         0x0
#define PMIO_INT_EN_CLR_EOC_INT_EN_CLR_EOC_INT_ENBLED_FVAL                           0x1

#define PMIO_INT_LATCHED_STS_ADDR(x)                                          ((x) + 0x00000018)
#define PMIO_INT_LATCHED_STS_RMSK                                                    0x1
#define PMIO_INT_LATCHED_STS_EOC_INT_LATCHED_STS_BMSK                                0x1
#define PMIO_INT_LATCHED_STS_EOC_INT_LATCHED_STS_SHFT                                0x0
#define PMIO_INT_LATCHED_STS_EOC_INT_LATCHED_STS_EOC_INT_LATCHED_FALSE_FVAL          0x0
#define PMIO_INT_LATCHED_STS_EOC_INT_LATCHED_STS_EOC_INT_LATCHED_TRUE_FVAL           0x1

#define PMIO_INT_PENDING_STS_ADDR(x)                                          ((x) + 0x00000019)
#define PMIO_INT_PENDING_STS_RMSK                                                    0x1
#define PMIO_INT_PENDING_STS_EOC_INT_PENDING_STS_BMSK                                0x1
#define PMIO_INT_PENDING_STS_EOC_INT_PENDING_STS_SHFT                                0x0
#define PMIO_INT_PENDING_STS_EOC_INT_PENDING_STS_EOC_INT_PENDING_FALSE_FVAL          0x0
#define PMIO_INT_PENDING_STS_EOC_INT_PENDING_STS_EOC_INT_PENDING_TRUE_FVAL           0x1

#define PMIO_INT_MID_SEL_ADDR(x)                                              ((x) + 0x0000001a)
#define PMIO_INT_MID_SEL_RMSK                                                        0x3
#define PMIO_INT_MID_SEL_INT_MID_SEL_BMSK                                            0x3
#define PMIO_INT_MID_SEL_INT_MID_SEL_SHFT                                            0x0

#define PMIO_INT_PRIORITY_ADDR(x)                                             ((x) + 0x0000001b)
#define PMIO_INT_PRIORITY_RMSK                                                       0x1
#define PMIO_INT_PRIORITY_INT_PRIORITY_BMSK                                          0x1
#define PMIO_INT_PRIORITY_INT_PRIORITY_SHFT                                          0x0
#define PMIO_INT_PRIORITY_INT_PRIORITY_SR_FVAL                                       0x0
#define PMIO_INT_PRIORITY_INT_PRIORITY_A_FVAL                                        0x1

#define PMIO_ADC_APP_SID_ADDR(x)                                              ((x) + 0x00000040)
#define PMIO_ADC_APP_SID_RMSK                                                        0x0f
#define PMIO_ADC_APP_SID_APP_SID_BMSK                                                    0x0f
#define PMIO_ADC_APP_SID_APP_SID_SHFT                                                    0x0

#define PMIO_ADC_DIG_PARAM_ADDR(x)                                            ((x) + 0x00000042)
#define PMIO_ADC_DIG_PARAM_RMSK                                                     0x7c
#define PMIO_ADC_DIG_PARAM_CAL_VAL_BMSK                                             0x40
#define PMIO_ADC_DIG_PARAM_CAL_VAL_SHFT                                              0x6
#define PMIO_ADC_DIG_PARAM_CAL_VAL_TIMER_CAL_FVAL                                    0x0
#define PMIO_ADC_DIG_PARAM_CAL_VAL_NEW_CAL_FVAL                                      0x1
#define PMIO_ADC_DIG_PARAM_CAL_SEL_BMSK                                             0x30
#define PMIO_ADC_DIG_PARAM_CAL_SEL_SHFT                                              0x4
#define PMIO_ADC_DIG_PARAM_CAL_SEL_NO_CAL_FVAL                                       0x0
#define PMIO_ADC_DIG_PARAM_CAL_SEL_RATIO_CAL_FVAL                                    0x1
#define PMIO_ADC_DIG_PARAM_CAL_SEL_ABS_CAL_FVAL                                      0x2
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_BMSK                                        0xc
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_SHFT                                        0x2
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_SHORT_FVAL                        0x0
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_MEDIUM_FVAL                       0x1
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_LONG_FVAL                         0x2

#define PMIO_FAST_AVG_CTL_ADDR(x)                                             ((x) + 0x00000043)
#define PMIO_FAST_AVG_CTL_RMSK                                                      0x87
#define PMIO_FAST_AVG_CTL_FAST_AVG_EN_BMSK                                          0x80
#define PMIO_FAST_AVG_CTL_FAST_AVG_EN_SHFT                                           0x7
#define PMIO_FAST_AVG_CTL_FAST_AVG_EN_FAST_AVG_DISABLED_FVAL                         0x0
#define PMIO_FAST_AVG_CTL_FAST_AVG_EN_FAST_AVG_ENABLED_FVAL                          0x1
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_BMSK                                      0x7
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_SHFT                                      0x0
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_AVG_1_SAMPLE_FVAL                         0x0
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_AVG_2_SAMPLES_FVAL                        0x1
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_AVG_4_SAMPLES_FVAL                        0x2
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_AVG_8_SAMPLES_FVAL                        0x3
#define PMIO_FAST_AVG_CTL_FAST_AVG_SAMPLES_AVG_16_SAMPLES_FVAL                       0x4

#define PMIO_ADC_CH_SEL_CTL_ADDR(x)                                           ((x) + 0x00000044)
#define PMIO_ADC_CH_SEL_CTL_RMSK                                                    0xff
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_BMSK                                         0xff
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_SHFT                                          0x0

#define PMIO_DELAY_CTL_ADDR(x)                                                ((x) + 0x00000045)
#define PMIO_DELAY_CTL_RMSK                                                          0xf
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_BMSK                                          0xf
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_SHFT                                          0x0
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_15US_FVAL                     0x0
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_100US_FVAL                    0x1
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_200US_FVAL                    0x2
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_300US_FVAL                    0x3
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_400US_FVAL                    0x4
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_500US_FVAL                    0x5
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_600US_FVAL                    0x6
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_700US_FVAL                    0x7
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_1MS_FVAL                      0x8
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_2MS_FVAL                      0x9
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_4MS_FVAL                      0xa
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_8MS_FVAL                      0xb
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_16MS_FVAL                     0xc
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_32MS_FVAL                     0xd
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_64MS_FVAL                     0xe
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_HW_SETTLE_DELAY_128MS_FVAL                    0xf

#define PMIO_EN_CTL1_ADDR(x)                                                  ((x) + 0x00000046)
#define PMIO_EN_CTL1_RMSK                                                           0x80
#define PMIO_EN_CTL1_ADC_EN_BMSK                                                    0x80
#define PMIO_EN_CTL1_ADC_EN_SHFT                                                     0x7
#define PMIO_EN_CTL1_ADC_EN_ADC_DISABLED_FVAL                                        0x0
#define PMIO_EN_CTL1_ADC_EN_ADC_ENABLED_FVAL                                         0x1

#define PMIO_CONV_REQ_ADDR(x)                                                 ((x) + 0x00000047)
#define PMIO_CONV_REQ_RMSK                                                          0x80
#define PMIO_CONV_REQ_REQ_BMSK                                                      0x80
#define PMIO_CONV_REQ_REQ_SHFT                                                       0x7
#define PMIO_CONV_REQ_REQ_NO_OPERATION_FVAL                                          0x0
#define PMIO_CONV_REQ_REQ_START_CONV_REQ_FVAL                                        0x1

#define PMIO_DATA0_ADDR(x)                                                    ((x) + 0x00000050)
#define PMIO_DATA0_RMSK                                                             0xff
#define PMIO_DATA0_DATA_7_0_BMSK                                                    0xff
#define PMIO_DATA0_DATA_7_0_SHFT                                                     0x0

#define PMIO_DATA1_ADDR(x)                                                    ((x) + 0x00000051)
#define PMIO_DATA1_RMSK                                                             0xff
#define PMIO_DATA1_DATA_15_8_BMSK                                                   0xff
#define PMIO_DATA1_DATA_15_8_SHFT                                                    0x0

#define PMIO_IBAT_DATA0_ADDR(x)                                              ((x) + 0x00000052)
#define PMIO_IBAT_DATA0_RMSK                                                         0xff
#define PMIO_IBAT_DATA0_DATA_7_0_BMSK                                                0xff
#define PMIO_IBAT_DATA0_DATA_7_0_SHFT                                                 0x0

#define PMIO_IBAT_DATA1_ADDR(x)                                              ((x) + 0x00000053)
#define PMIO_IBAT_DATA1_RMSK                                                         0xff
#define PMIO_IBAT_DATA1_DATA_15_8_BMSK                                               0xff
#define PMIO_IBAT_DATA1_DATA_15_8_SHFT                                                0x0

#define PMIO_PERPH_RESET_CTL3_ADDR(x)                                         ((x) + 0x000000da)
#define PMIO_PERPH_RESET_CTL3_RMSK                                                   0x5
#define PMIO_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK                                    0x4
#define PMIO_PERPH_RESET_CTL3_FOLLOW_WARM_RB_SHFT                                    0x2
#define PMIO_PERPH_RESET_CTL3_FOLLOW_WARM_RB_FOLLOW_WARM_RB_FALSE_FVAL               0x0
#define PMIO_PERPH_RESET_CTL3_FOLLOW_WARM_RB_FOLLOW_WARM_RB_TRUE_FVAL                0x1
#define PMIO_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_BMSK                               0x1
#define PMIO_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_SHFT                               0x0
#define PMIO_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_FOLLOW_SHUTDOWN2_RB_FALSE_FVAL        0x0
#define PMIO_PERPH_RESET_CTL3_FOLLOW_SHUTDOWN2_RB_FOLLOW_SHUTDOWN2_RB_TRUE_FVAL        0x1

#define PMIO_PERPH_RESET_CTL4_ADDR(x)                                         ((x) + 0x000000db)
#define PMIO_PERPH_RESET_CTL4_RMSK                                                   0x1
#define PMIO_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_BMSK                                  0x1
#define PMIO_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_SHFT                                  0x0
#define PMIO_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_LOCAL_SOFT_RESET_FALSE_FVAL           0x0
#define PMIO_PERPH_RESET_CTL4_LOCAL_SOFT_RESET_LOCAL_SOFT_RESET_TRUE_FVAL            0x1

#endif /* __VADCHALPMIO_H__ */

