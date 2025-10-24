#ifndef __ADCHALPMIO_H__
#define __ADCHALPMIO_H__
/*
===========================================================================
*/
/**
    @file AdcHalPmio.h
    @brief Auto-generated PMIO interface include file.

    This file contains PMIO register definitions for the following modules:
        ADC_ADSP_SDAM

    'Include' filters applied: <none>
    'Exclude' filters applied: RESERVED DUMMY 
*/
/*
    ===========================================================================
  
  Copyright (c) 2022 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
  
  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.
  
  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly 
  reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.
  
===========================================================================

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc_sdam/src/AdcHalPmio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: ADC_ADSP_SDAM
 *--------------------------------------------------------------------------*/
#define PMIO_INT_RT_STS_ADDR                                         (0            + 0x00000010)
#define PMIO_INT_RT_STS_OFFS                                         0x00000010

#define PMIO_INT_SET_TYPE_ADDR                                       (0            + 0x00000011)
#define PMIO_INT_SET_TYPE_OFFS                                       0x00000011

#define PMIO_INT_POLARITY_HIGH_ADDR                                  (0            + 0x00000012)
#define PMIO_INT_POLARITY_HIGH_OFFS                                  0x00000012

#define PMIO_INT_POLARITY_LOW_ADDR                                   (0            + 0x00000013)
#define PMIO_INT_POLARITY_LOW_OFFS                                   0x00000013

#define PMIO_INT_LATCHED_CLR_ADDR                                    (0            + 0x00000014)
#define PMIO_INT_LATCHED_CLR_OFFS                                    0x00000014

#define PMIO_INT_EN_SET_ADDR                                         (0            + 0x00000015)
#define PMIO_INT_EN_SET_OFFS                                         0x00000015

#define PMIO_INT_EN_CLR_ADDR                                         (0            + 0x00000016)
#define PMIO_INT_EN_CLR_OFFS                                         0x00000016

#define PMIO_INT_LATCHED_STS_ADDR                                    (0            + 0x00000018)
#define PMIO_INT_LATCHED_STS_OFFS                                    0x00000018

#define PMIO_INT_PENDING_STS_ADDR                                    (0            + 0x00000019)
#define PMIO_INT_PENDING_STS_OFFS                                    0x00000019

#define PMIO_INT_MID_SEL_ADDR                                        (0            + 0x0000001A)
#define PMIO_INT_MID_SEL_OFFS                                        0x0000001A
#define PMIO_INT_MID_SEL_INT_MID_SEL_BMSK                                   0x3
#define PMIO_INT_MID_SEL_INT_MID_SEL_SHFT                                   0x0

#define PMIO_INT_PRIORITY_ADDR                                       (0            + 0x0000001B)
#define PMIO_INT_PRIORITY_OFFS                                       0x0000001B

#define PMIO_REGISTER_MAP_ID_ADDR                                    (0            + 0x00000040)
#define PMIO_REGISTER_MAP_ID_OFFS                                    0x00000040
#define PMIO_REGISTER_MAP_ID_RMSK                                          0xff
#define PMIO_REGISTER_MAP_ID_REGISTER_MAP_ID_BMSK                          0xff
#define PMIO_REGISTER_MAP_ID_REGISTER_MAP_ID_SHFT                           0x0

#define PMIO_REGISTER_MAP_VERSION_ADDR                               (0            + 0x00000041)
#define PMIO_REGISTER_MAP_VERSION_OFFS                               0x00000041
#define PMIO_REGISTER_MAP_VERSION_RMSK                                     0xff
#define PMIO_REGISTER_MAP_VERSION_REGISTER_MAP_VERSION_BMSK                0xff
#define PMIO_REGISTER_MAP_VERSION_REGISTER_MAP_VERSION_SHFT                 0x0

#define PMIO_PBS_ARG_ADDR                                            (0            + 0x00000042)
#define PMIO_PBS_ARG_OFFS                                            0x00000042
#define PMIO_PBS_ARG_RMSK                                                  0xff
#define PMIO_PBS_ARG_PBS_ARG_BMSK                                          0xff
#define PMIO_PBS_ARG_PBS_ARG_SHFT                                           0x0

#define PMIO_PBS_RET_ADDR                                            (0            + 0x00000043)
#define PMIO_PBS_RET_OFFS                                            0x00000043
#define PMIO_PBS_RET_RMSK                                                  0xff
#define PMIO_PBS_RET_PBS_RET_BMSK                                          0xff
#define PMIO_PBS_RET_PBS_RET_SHFT                                           0x0

#define PMIO_SDAM_SIZE_ADDR                                          (0            + 0x00000044)
#define PMIO_SDAM_SIZE_OFFS                                          0x00000044
#define PMIO_SDAM_SIZE_RMSK                                                0xff
#define PMIO_SDAM_SIZE_SDAM_SIZE_BMSK                                      0xff
#define PMIO_SDAM_SIZE_SDAM_SIZE_SHFT                                       0x0

#define PMIO_HS_ADDR                                                 (0            + 0x00000045)
#define PMIO_HS_OFFS                                                 0x00000045
#define PMIO_HS_RMSK                                                       0xff
#define PMIO_HS_HS_BMSK                                                    0xff
#define PMIO_HS_HS_SHFT                                                     0x0

#define PMIO_STATUS1_ADDR                                            (0            + 0x00000046)
#define PMIO_STATUS1_OFFS                                            0x00000046
#define PMIO_STATUS1_RMSK                                                  0xff
#define PMIO_STATUS1_STATUS1_BMSK                                          0xff
#define PMIO_STATUS1_STATUS1_SHFT                                           0x0
#define PMIO_STATUS1_CONV_FAULT_BMSK                                       0x80
#define PMIO_STATUS1_CONV_FAULT_SHFT                                        0x7
#define PMIO_STATUS1_CONV_FAULT_NO_CONV_FAULT_FVAL                          0x0
#define PMIO_STATUS1_CONV_FAULT_CONV_FAULT_FVAL                             0x1
#define PMIO_STATUS1_THR_CROSS_BMSK                                        0x40
#define PMIO_STATUS1_THR_CROSS_SHFT                                         0x6
#define PMIO_STATUS1_THR_CROSS_REQ_NOT_IN_PROGRESS_FVAL                     0x0
#define PMIO_STATUS1_THR_CROSS_REQ_IN_PROGRESS_FVAL                         0x1
#define PMIO_STATUS1_EOC_BMSK                                               0x1
#define PMIO_STATUS1_EOC_SHFT                                               0x0
#define PMIO_STATUS1_EOC_CONV_NOT_COMPLETE_FVAL                             0x0
#define PMIO_STATUS1_EOC_CONV_COMPLETE_FVAL                                 0x1

#define PMIO_TM_EN_STS_ADDR                                          (0            + 0x00000047)
#define PMIO_TM_EN_STS_OFFS                                          0x00000047
#define PMIO_TM_EN_STS_RMSK                                                0xff
#define PMIO_TM_EN_STS_TM_EN_STS_BMSK                                      0xff
#define PMIO_TM_EN_STS_TM_EN_STS_SHFT                                       0x0

#define PMIO_TM_HIGH_STS_ADDR                                        (0            + 0x00000048)
#define PMIO_TM_HIGH_STS_OFFS                                        0x00000048
#define PMIO_TM_HIGH_STS_RMSK                                              0xff
#define PMIO_TM_HIGH_STS_TM_HIGH_STS_BMSK                                  0xff
#define PMIO_TM_HIGH_STS_TM_HIGH_STS_SHFT                                   0x0

#define PMIO_TM_LOW_STS_ADDR                                         (0            + 0x00000049)
#define PMIO_TM_LOW_STS_OFFS                                         0x00000049
#define PMIO_TM_LOW_STS_RMSK                                               0xff
#define PMIO_TM_LOW_STS_TM_LOW_STS_BMSK                                    0xff
#define PMIO_TM_LOW_STS_TM_LOW_STS_SHFT                                     0x0

#define PMIO_EOC_STS_ADDR                                            (0            + 0x0000004a)
#define PMIO_EOC_STS_OFFS                                            0x0000004a
#define PMIO_EOC_STS_RMSK                                                  0xff
#define PMIO_EOC_STS_EOC_STS_BMSK                                          0xff
#define PMIO_EOC_STS_EOC_STS_SHFT                                           0x0

#define PMIO_EOC_CLR_ADDR                                            (0            + 0x0000004b)
#define PMIO_EOC_CLR_OFFS                                            0x0000004b
#define PMIO_EOC_CLR_RMSK                                                  0xff
#define PMIO_EOC_CLR_EOC_CLR_BMSK                                          0xff
#define PMIO_EOC_CLR_EOC_CLR_SHFT                                           0x0

#define PMIO_TM_HIGH_STS_CLR_ADDR                                    (0            + 0x0000004c)
#define PMIO_TM_HIGH_STS_CLR_OFFS                                    0x0000004c
#define PMIO_TM_HIGH_STS_CLR_RMSK                                          0xff
#define PMIO_TM_HIGH_STS_CLR_TM_HIGH_STS_CLR_BMSK                          0xff
#define PMIO_TM_HIGH_STS_CLR_TM_HIGH_STS_CLR_SHFT                           0x0

#define PMIO_TM_LOW_STS_CLR_ADDR                                     (0            + 0x0000004d)
#define PMIO_TM_LOW_STS_CLR_OFFS                                     0x0000004d
#define PMIO_TM_LOW_STS_CLR_RMSK                                           0xff
#define PMIO_TM_LOW_STS_CLR_TM_LOW_STS_CLR_BMSK                            0xff
#define PMIO_TM_LOW_STS_CLR_TM_LOW_STS_CLR_SHFT                             0x0

#define PMIO_SID_ADDR                                                (0            + 0x0000004f)
#define PMIO_SID_OFFS                                                0x0000004f
#define PMIO_SID_RMSK                                                      0xff
#define PMIO_SID_SID_BMSK                                                   0xf
#define PMIO_SID_SID_SHFT                                                   0x0

#define PMIO_PERPH_CH_ADDR                                           (0            + 0x00000050)
#define PMIO_PERPH_CH_OFFS                                           0x00000050
#define PMIO_PERPH_CH_RMSK                                                 0xff
#define PMIO_PERPH_CH_PERPH_CH_BMSK                                        0xff
#define PMIO_PERPH_CH_PERPH_CH_SHFT                                         0x0

#define PMIO_TIMER_SEL_ADDR                                          (0            + 0x00000051)
#define PMIO_TIMER_SEL_OFFS                                          0x00000051
#define PMIO_TIMER_SEL_RMSK                                                0xff
#define PMIO_TIMER_SEL_TIMER_SEL_BMSK                                      0xff
#define PMIO_TIMER_SEL_TIMER_SEL_SHFT                                       0x0

#define PMIO_ADC_DIG_PARAM_ADDR                                      (0            + 0x00000052)
#define PMIO_ADC_DIG_PARAM_OFFS                                      0x00000052
#define PMIO_ADC_DIG_PARAM_RMSK                                            0xff
#define PMIO_ADC_DIG_PARAM_ADC_DIG_PARAM_BMSK                              0xff
#define PMIO_ADC_DIG_PARAM_ADC_DIG_PARAM_SHFT                               0x0
#define PMIO_ADC_DIG_PARAM_CAL_VAL_BMSK                                    0x40
#define PMIO_ADC_DIG_PARAM_CAL_VAL_SHFT                                     0x6
#define PMIO_ADC_DIG_PARAM_CAL_VAL_TIMER_CAL_FVAL                           0x0
#define PMIO_ADC_DIG_PARAM_CAL_VAL_NEW_CAL_FVAL                             0x1
#define PMIO_ADC_DIG_PARAM_CAL_SEL_BMSK                                    0x30
#define PMIO_ADC_DIG_PARAM_CAL_SEL_SHFT                                     0x4
#define PMIO_ADC_DIG_PARAM_CAL_SEL_NO_CAL_FVAL                              0x0
#define PMIO_ADC_DIG_PARAM_CAL_SEL_RATIO_CAL_FVAL                           0x1
#define PMIO_ADC_DIG_PARAM_CAL_SEL_ABS_CAL_FVAL                             0x2
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_BMSK                               0xc
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_SHFT                               0x2
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_SHORT_FVAL               0x0
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_MEDIUM_FVAL              0x1
#define PMIO_ADC_DIG_PARAM_DEC_RATIO_SEL_DEC_RATIO_LONG_FVAL                0x2

#define PMIO_FAST_AVG_ADDR                                           (0            + 0x00000053)
#define PMIO_FAST_AVG_OFFS                                           0x00000053
#define PMIO_FAST_AVG_RMSK                                                 0xff
#define PMIO_FAST_AVG_FAST_AVG_BMSK                                        0xff
#define PMIO_FAST_AVG_FAST_AVG_SHFT                                         0x0
#define PMIO_FAST_AVG_FAST_AVG_EN_BMSK                                     0x80
#define PMIO_FAST_AVG_FAST_AVG_EN_SHFT                                      0x7
#define PMIO_FAST_AVG_FAST_AVG_EN_FAST_AVG_DISABLED_FVAL                    0x0
#define PMIO_FAST_AVG_FAST_AVG_EN_FAST_AVG_ENABLED_FVAL                     0x1
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_BMSK                                 0x7
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_SHFT                                 0x0
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_AVG_1_SAMPLE_FVAL                    0x0
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_AVG_2_SAMPLES_FVAL                   0x1
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_AVG_4_SAMPLES_FVAL                   0x2
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_AVG_8_SAMPLES_FVAL                   0x3
#define PMIO_FAST_AVG_FAST_AVG_SAMPLES_AVG_16_SAMPLES_FVAL                  0x4


#define PMIO_ADC_CH_SEL_CTL_ADDR                                     (0            + 0x00000054)
#define PMIO_ADC_CH_SEL_CTL_OFFS                                     0x00000054
#define PMIO_ADC_CH_SEL_CTL_RMSK                                           0xff
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_CTL_BMSK                            0xff
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_CTL_SHFT                             0x0
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_BMSK                                0xff
#define PMIO_ADC_CH_SEL_CTL_ADC_CH_SEL_SHFT                                 0x0


#define PMIO_DELAY_CTL_ADDR                                          (0            + 0x00000055)
#define PMIO_DELAY_CTL_OFFS                                          0x00000055
#define PMIO_DELAY_CTL_RMSK                                                0xff
#define PMIO_DELAY_CTL_DELAY_CTL_BMSK                                      0xff
#define PMIO_DELAY_CTL_DELAY_CTL_SHFT                                       0x0
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_BMSK                                 0xf
#define PMIO_DELAY_CTL_HW_SETTLE_DELAY_SHFT                                 0x0


#define PMIO_THRESHOLD_EN_ADDR                                       (0            + 0x00000056)
#define PMIO_THRESHOLD_EN_OFFS                                       0x00000056
#define PMIO_THRESHOLD_EN_RMSK                                             0xff
#define PMIO_THRESHOLD_EN_THRESHOLD_EN_BMSK                                0xff
#define PMIO_THRESHOLD_EN_THRESHOLD_EN_SHFT                                 0x0

#define PMIO_THRESH_LOW_0_ADDR                                       (0            + 0x00000057)
#define PMIO_THRESH_LOW_0_OFFS                                       0x00000057
#define PMIO_THRESH_LOW_0_RMSK                                             0xff
#define PMIO_THRESH_LOW_0_THRESH_LOW_0_BMSK                                0xff
#define PMIO_THRESH_LOW_0_THRESH_LOW_0_SHFT                                 0x0

#define PMIO_THRESH_LOW_1_ADDR                                       (0            + 0x00000058)
#define PMIO_THRESH_LOW_1_OFFS                                       0x00000058
#define PMIO_THRESH_LOW_1_RMSK                                             0xff
#define PMIO_THRESH_LOW_1_THRESH_LOW_1_BMSK                                0xff
#define PMIO_THRESH_LOW_1_THRESH_LOW_1_SHFT                                 0x0

#define PMIO_THRESH_HIGH_0_ADDR                                      (0            + 0x00000059)
#define PMIO_THRESH_HIGH_0_OFFS                                      0x00000059
#define PMIO_THRESH_HIGH_0_RMSK                                            0xff
#define PMIO_THRESH_HIGH_0_THRESH_HIGH_0_BMSK                              0xff
#define PMIO_THRESH_HIGH_0_THRESH_HIGH_0_SHFT                               0x0

#define PMIO_THRESH_HIGH_1_ADDR                                      (0            + 0x0000005a)
#define PMIO_THRESH_HIGH_1_OFFS                                      0x0000005a
#define PMIO_THRESH_HIGH_1_RMSK                                            0xff
#define PMIO_THRESH_HIGH_1_THRESH_HIGH_1_BMSK                              0xff
#define PMIO_THRESH_HIGH_1_THRESH_HIGH_1_SHFT                               0x0

#define PMIO_CH_0_DATA0_ADDR                                         (0            + 0x0000005c)
#define PMIO_CH_0_DATA0_OFFS                                         0x0000005c
#define PMIO_CH_0_DATA0_RMSK                                               0xff
#define PMIO_CH_0_DATA0_CH_0_DATA0_BMSK                                    0xff
#define PMIO_CH_0_DATA0_CH_0_DATA0_SHFT                                     0x0

#define PMIO_CH_0_DATA1_ADDR                                         (0            + 0x0000005d)
#define PMIO_CH_0_DATA1_OFFS                                         0x0000005d
#define PMIO_CH_0_DATA1_RMSK                                               0xff
#define PMIO_CH_0_DATA1_CH_0_DATA1_BMSK                                    0xff
#define PMIO_CH_0_DATA1_CH_0_DATA1_SHFT                                     0x0

#define PMIO_CH_1_DATA0_ADDR                                         (0            + 0x0000005e)
#define PMIO_CH_1_DATA0_OFFS                                         0x0000005e
#define PMIO_CH_1_DATA0_RMSK                                               0xff
#define PMIO_CH_1_DATA0_CH_1_DATA0_BMSK                                    0xff
#define PMIO_CH_1_DATA0_CH_1_DATA0_SHFT                                     0x0

#define PMIO_CH_1_DATA1_ADDR                                         (0            + 0x0000005f)
#define PMIO_CH_1_DATA1_OFFS                                         0x0000005f
#define PMIO_CH_1_DATA1_RMSK                                               0xff
#define PMIO_CH_1_DATA1_CH_1_DATA1_BMSK                                    0xff
#define PMIO_CH_1_DATA1_CH_1_DATA1_SHFT                                     0x0

#define PMIO_CH_2_DATA0_ADDR                                         (0            + 0x00000060)
#define PMIO_CH_2_DATA0_OFFS                                         0x00000060
#define PMIO_CH_2_DATA0_RMSK                                               0xff
#define PMIO_CH_2_DATA0_CH_2_DATA0_BMSK                                    0xff
#define PMIO_CH_2_DATA0_CH_2_DATA0_SHFT                                     0x0

#define PMIO_CH_2_DATA1_ADDR                                         (0            + 0x00000061)
#define PMIO_CH_2_DATA1_OFFS                                         0x00000061
#define PMIO_CH_2_DATA1_RMSK                                               0xff
#define PMIO_CH_2_DATA1_CH_2_DATA1_BMSK                                    0xff
#define PMIO_CH_2_DATA1_CH_2_DATA1_SHFT                                     0x0

#define PMIO_CH_3_DATA0_ADDR                                         (0            + 0x00000062)
#define PMIO_CH_3_DATA0_OFFS                                         0x00000062
#define PMIO_CH_3_DATA0_RMSK                                               0xff
#define PMIO_CH_3_DATA0_CH_3_DATA0_BMSK                                    0xff
#define PMIO_CH_3_DATA0_CH_3_DATA0_SHFT                                     0x0

#define PMIO_CH_3_DATA1_ADDR                                         (0            + 0x00000063)
#define PMIO_CH_3_DATA1_OFFS                                         0x00000063
#define PMIO_CH_3_DATA1_RMSK                                               0xff
#define PMIO_CH_3_DATA1_CH_3_DATA1_BMSK                                    0xff
#define PMIO_CH_3_DATA1_CH_3_DATA1_SHFT                                     0x0

#define PMIO_CH_4_DATA0_ADDR                                         (0            + 0x00000064)
#define PMIO_CH_4_DATA0_OFFS                                         0x00000064
#define PMIO_CH_4_DATA0_RMSK                                               0xff
#define PMIO_CH_4_DATA0_CH_4_DATA0_BMSK                                    0xff
#define PMIO_CH_4_DATA0_CH_4_DATA0_SHFT                                     0x0

#define PMIO_CH_4_DATA1_ADDR                                         (0            + 0x00000065)
#define PMIO_CH_4_DATA1_OFFS                                         0x00000065
#define PMIO_CH_4_DATA1_RMSK                                               0xff
#define PMIO_CH_4_DATA1_CH_4_DATA1_BMSK                                    0xff
#define PMIO_CH_4_DATA1_CH_4_DATA1_SHFT                                     0x0

#define PMIO_CH_5_DATA0_ADDR                                         (0            + 0x00000066)
#define PMIO_CH_5_DATA0_OFFS                                         0x00000066
#define PMIO_CH_5_DATA0_RMSK                                               0xff
#define PMIO_CH_5_DATA0_CH_5_DATA0_BMSK                                    0xff
#define PMIO_CH_5_DATA0_CH_5_DATA0_SHFT                                     0x0

#define PMIO_CH_5_DATA1_ADDR                                         (0            + 0x00000067)
#define PMIO_CH_5_DATA1_OFFS                                         0x00000067
#define PMIO_CH_5_DATA1_RMSK                                               0xff
#define PMIO_CH_5_DATA1_CH_5_DATA1_BMSK                                    0xff
#define PMIO_CH_5_DATA1_CH_5_DATA1_SHFT                                     0x0

#define PMIO_CH_6_DATA0_ADDR                                         (0            + 0x00000068)
#define PMIO_CH_6_DATA0_OFFS                                         0x00000068
#define PMIO_CH_6_DATA0_RMSK                                               0xff
#define PMIO_CH_6_DATA0_CH_6_DATA0_BMSK                                    0xff
#define PMIO_CH_6_DATA0_CH_6_DATA0_SHFT                                     0x0

#define PMIO_CH_6_DATA1_ADDR                                         (0            + 0x00000069)
#define PMIO_CH_6_DATA1_OFFS                                         0x00000069
#define PMIO_CH_6_DATA1_RMSK                                               0xff
#define PMIO_CH_6_DATA1_CH_6_DATA1_BMSK                                    0xff
#define PMIO_CH_6_DATA1_CH_6_DATA1_SHFT                                     0x0

#define PMIO_CH_7_DATA0_ADDR                                         (0            + 0x0000006a)
#define PMIO_CH_7_DATA0_OFFS                                         0x0000006a
#define PMIO_CH_7_DATA0_RMSK                                               0xff
#define PMIO_CH_7_DATA0_CH_7_DATA0_BMSK                                    0xff
#define PMIO_CH_7_DATA0_CH_7_DATA0_SHFT                                     0x0

#define PMIO_CH_7_DATA1_ADDR                                         (0            + 0x0000006b)
#define PMIO_CH_7_DATA1_OFFS                                         0x0000006b
#define PMIO_CH_7_DATA1_RMSK                                               0xff
#define PMIO_CH_7_DATA1_CH_7_DATA1_BMSK                                    0xff
#define PMIO_CH_7_DATA1_CH_7_DATA1_SHFT                                     0x0

#define PMIO_STATUS2_ADDR                                            (0            + 0x0000006C)
#define PMIO_STATUS2_OFFS                                            0x0000006c
#define PMIO_STATUS2_RMSK                                                  0xff
#define PMIO_STATUS2_STATUS2_BMSK                                          0xff
#define PMIO_STATUS2_STATUS2_SHFT                                           0x0

#define PMIO_STATUS3_ADDR                                            (0            + 0x0000006D)
#define PMIO_STATUS3_OFFS                                            0x0000006d
#define PMIO_STATUS3_RMSK                                                  0xff
#define PMIO_STATUS3_STATUS3_BMSK                                          0xff
#define PMIO_STATUS3_STATUS3_SHFT                                           0x0

#define PMIO_PBS_TRIG_SET_ADDR                                       (0            + 0x000000E5)
#define PMIO_PBS_TRIG_SET_OFFS                                       0x000000E5

#define PMIO_PBS_TRIG_CLR_ADDR                                       (0            + 0x000000E6)
#define PMIO_PBS_TRIG_CLR_OFFS                                       0x000000E6


#endif /* __ADCHALPMIO_H__ */

