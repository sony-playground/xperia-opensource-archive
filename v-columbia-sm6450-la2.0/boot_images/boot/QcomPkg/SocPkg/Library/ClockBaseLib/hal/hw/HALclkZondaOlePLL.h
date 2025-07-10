#ifndef __HALCLKZONDAOLEPLL_H__
#define __HALCLKZONDAOLEPLL_H__
/*
==============================================================================

FILE:         HALclkZondaOlePLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================
    Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * Registers for programming operational mode
 */
#define HAL_PLL_OPMODE_STANDBY  0x0
#define HAL_PLL_OPMODE_RUN      0x1
#define HAL_PLL_OPMODE_FREEZE   0x3

/*
 * PLL register offsets.
 */
#define HWIO_PLL_MODE_OFFS                                              0x00000000
#define HWIO_PLL_L_VAL_OFFS                                             0x00000004
#define HWIO_PLL_ALPHA_VAL_OFFS                                         0x00000008
#define HWIO_PLL_USER_CTL_OFFS                                          0x0000000C
#define HWIO_PLL_USER_CTL_U_OFFS                                        0x00000010
#define HWIO_PLL_CONFIG_CTL_OFFS                                        0x00000014
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                      0x00000018
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                                     0x0000001C
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                                     0x00000020
#define HWIO_PLL_TEST_CTL_OFFS                                          0x00000024
#define HWIO_PLL_TEST_CTL_U_OFFS                                        0x00000028
#define HWIO_PLL_TEST_CTL_U1_OFFS                                       0x0000002C
#define HWIO_PLL_OPMODE_OFFS                                            0x00000030

/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                 0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                       0x1f
#define HWIO_PLL_MODE_FREQ_LOCK_DET_BMSK                                0x40000000
#define HWIO_PLL_MODE_FREQ_LOCK_DET_SHFT                                      0x1e
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_BMSK                            0x20000000
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_SHFT                                  0x1d
#define HWIO_PLL_MODE_PLL_PLLTEST_BMSK                                      0x8000
#define HWIO_PLL_MODE_PLL_PLLTEST_SHFT                                         0xf
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                                  0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                     0xe
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                    0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                       0xd
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_BMSK                                    0x80
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_SHFT                                     0x7
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_BMSK                                     0x40
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_SHFT                                      0x6
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                    0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                     0x4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                     0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                     0x3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                         0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                         0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_BMSK                                        0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_SHFT                                        0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                         0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                         0x0

/*
 * PLL_ALPHA_VAL register definitions.
 *   These fields are defined implicitly here because the bits in this register
 *   are overloaded depending on the value of PLL_USER_CTL[FRAC_FORMAT_SEL].
 */
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_BMSK                               0xffff
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_SHFT                                  0x0
#define HWIO_PLL_ALPHA_VAL_M_VAL_BMSK                                         0xff
#define HWIO_PLL_ALPHA_VAL_M_VAL_SHFT                                          0x8
#define HWIO_PLL_ALPHA_VAL_N_VAL_BMSK                                         0xff
#define HWIO_PLL_ALPHA_VAL_N_VAL_SHFT                                          0x0

/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_BMSK                          0x4000000
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_SHFT                               0x1a
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                           0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                                0x19
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_BMSK                             0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_SHFT                              0x4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_BMSK                               0x8
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_SHFT                               0x3
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_BMSK                              0x4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_SHFT                              0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_BMSK                              0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_SHFT                              0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_BMSK                              0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_SHFT                              0x0

/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_BMSK                     0x10000000
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_SHFT                           0x1c
#define HWIO_PLL_USER_CTL_U_DCO_FREQ_STEP_BMSK                           0x8000000
#define HWIO_PLL_USER_CTL_U_DCO_FREQ_STEP_SHFT                                0x1b
#define HWIO_PLL_USER_CTL_U_SSC_MODE_ENABLE_BMSK                         0x4000000
#define HWIO_PLL_USER_CTL_U_SSC_MODE_ENABLE_SHFT                              0x1a
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_BMSK                    0x2000000
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_SHFT                         0x19
#define HWIO_PLL_USER_CTL_U_CTUNE_MIN_ENABLE_BMSK                        0x1000000
#define HWIO_PLL_USER_CTL_U_CTUNE_MIN_ENABLE_SHFT                             0x18
#define HWIO_PLL_USER_CTL_U_L_VAL_CHANGE_TM_ENABLE_BMSK                   0x800000
#define HWIO_PLL_USER_CTL_U_L_VAL_CHANGE_TM_ENABLE_SHFT                       0x17
#define HWIO_PLL_USER_CTL_U_OLC_EXIT_COUNT_BMSK                           0x400000
#define HWIO_PLL_USER_CTL_U_OLC_EXIT_COUNT_SHFT                               0x16
#define HWIO_PLL_USER_CTL_U_ADC_STATE_SYNC_DISABLE_BMSK                   0x200000
#define HWIO_PLL_USER_CTL_U_ADC_STATE_SYNC_DISABLE_SHFT                       0x15
#define HWIO_PLL_USER_CTL_U_ADC_LOCK_SYNC_DISABLE_BMSK                    0x100000
#define HWIO_PLL_USER_CTL_U_ADC_LOCK_SYNC_DISABLE_SHFT                        0x14
#define HWIO_PLL_USER_CTL_U_DROOP_BYPASS_IN_CFA_FFA_BMSK                   0x80000
#define HWIO_PLL_USER_CTL_U_DROOP_BYPASS_IN_CFA_FFA_SHFT                      0x13
#define HWIO_PLL_USER_CTL_U_CFA_MIN_TIME_DISABLE_BMSK                      0x40000
#define HWIO_PLL_USER_CTL_U_CFA_MIN_TIME_DISABLE_SHFT                         0x12
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_BMSK                          0x20000
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_SHFT                             0x11
#define HWIO_PLL_USER_CTL_U_FREQ_PLL_LOCK_BMSK                             0x10000
#define HWIO_PLL_USER_CTL_U_FREQ_PLL_LOCK_SHFT                                0x10
#define HWIO_PLL_USER_CTL_U_ADC_CAL_EXIT_BMSK                               0x8000
#define HWIO_PLL_USER_CTL_U_ADC_CAL_EXIT_SHFT                                  0xf
#define HWIO_PLL_USER_CTL_U_PLLOUT_AUX2_ENABLE_BMSK                         0x4000
#define HWIO_PLL_USER_CTL_U_PLLOUT_AUX2_ENABLE_SHFT                            0xe
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_BMSK                           0x3000
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_SHFT                              0xc
#define HWIO_PLL_USER_CTL_U_TEST_OUTPUT_SEL_BMSK                             0x800
#define HWIO_PLL_USER_CTL_U_TEST_OUTPUT_SEL_SHFT                               0xb
#define HWIO_PLL_USER_CTL_U_INV_DIV_PLLOUT_BMSK                              0x400
#define HWIO_PLL_USER_CTL_U_INV_DIV_PLLOUT_SHFT                                0xa
#define HWIO_PLL_USER_CTL_U_INV_MAIN_PLLOUT_BMSK                             0x200
#define HWIO_PLL_USER_CTL_U_INV_MAIN_PLLOUT_SHFT                               0x9
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS40_37_BMSK                           0x1e0
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS40_37_SHFT                             0x5
#define HWIO_PLL_USER_CTL_U_DN_CONTROL_BMSK                                   0x18
#define HWIO_PLL_USER_CTL_U_DN_CONTROL_SHFT                                    0x3
#define HWIO_PLL_USER_CTL_U_PRE_CHARGE_DISABLE_BMSK                            0x4
#define HWIO_PLL_USER_CTL_U_PRE_CHARGE_DISABLE_SHFT                            0x2
#define HWIO_PLL_USER_CTL_U_ATEST_MSB_BMSK                                     0x2
#define HWIO_PLL_USER_CTL_U_ATEST_MSB_SHFT                                     0x1
#define HWIO_PLL_USER_CTL_U_ICP_LEAK_DISABLE_BMSK                              0x1
#define HWIO_PLL_USER_CTL_U_ICP_LEAK_DISABLE_SHFT                              0x0

#endif  /* __HALCLKZONDAOLEPLL_H__ */
