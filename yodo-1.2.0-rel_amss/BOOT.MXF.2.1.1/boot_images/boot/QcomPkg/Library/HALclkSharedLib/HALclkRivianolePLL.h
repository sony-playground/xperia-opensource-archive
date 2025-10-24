#ifndef __HALCLKRIVIANOLEPLL_H__
#define __HALCLKRIVIANOLEPLL_H__
/*
==============================================================================

FILE:         HALclkRivianOlePLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================
             Copyright (c) 2021 QUALCOMM Technologies Incorporated. All Rights Reserved.
                    QUALCOMM Proprietary and Confidential.
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
#define HWIO_PLL_MODE_OFFS                                                         0x0
#define HWIO_PLL_OPMODE_OFFS                                                       0x4
#define HWIO_PLL_STATE_OFFS                                                        0x8
#define HWIO_PLL_STATUS_OFFS                                                       0xc
#define HWIO_PLL_L_VAL_OFFS                                                       0x10
#define HWIO_PLL_USER_CTL_OFFS                                                    0x14
#define HWIO_PLL_USER_CTL_U_OFFS                                                  0x18
#define HWIO_PLL_CONFIG_CTL_OFFS                                                  0x1c
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                                0x20
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                                               0x24
#define HWIO_PLL_TEST_CTL_OFFS                                                    0x28
#define HWIO_PLL_TEST_CTL_U_OFFS                                                  0x2c

/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_RMSK                                                  0xffffffff
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                     0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                             31
#define HWIO_PLL_MODE_FREQ_LOCK_DET_BMSK                                    0x40000000
#define HWIO_PLL_MODE_FREQ_LOCK_DET_SHFT                                            30
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_BMSK                                0x20000000
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_SHFT                                        29
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                                      0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                          14
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                        0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                            13
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_BMSK                                         0x40
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_SHFT                                            6
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                        0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                           4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                         0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                           3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                             0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                               2
#define HWIO_PLL_MODE_PLL_BYPASSNL_BMSK                                            0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_SHFT                                              1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                             0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                               0

/*
 * PLL_L_VAL register definitions.
 */
#define HWIO_PLL_L_VAL_PLL_L_VAL_BMSK                                             0xff
#define HWIO_PLL_L_VAL_PLL_L_VAL_SHFT                                                0

/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_RMSK                                              0xffffffff
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_BMSK                        0x8000000
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_SHFT                               27
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_BMSK                              0x4000000
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_SHFT                                     26
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                               0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                                      25
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                 0x1c00000
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                        22
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                              0x3c00
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                                  10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_BMSK                                     0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_SHFT                                        4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_EN_BMSK                                       0x8
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_EN_SHFT                                         3
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_BMSK                                      0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_SHFT                                        1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_BMSK                                      0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_SHFT                                        0
/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_RMSK                                            0xffffffff
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_LOW_BMSK                           0x1000000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_LOW_SHFT                                  24
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_HIGH_BMSK                           0x800000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_HIGH_SHFT                                 23
#define HWIO_PLL_USER_CTL_U_FREQ_BAND_BMSK                                     0xc0000
#define HWIO_PLL_USER_CTL_U_FREQ_BAND_SHFT                                          18
#define HWIO_PLL_USER_CTL_U_LOCK_DET_SEL_BMSK                                  0x30000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_SEL_SHFT                                       16
#define HWIO_PLL_USER_CTL_U_VCO_DIVIDER_BMSK                                    0x8000
#define HWIO_PLL_USER_CTL_U_VCO_DIVIDER_SHFT                                        15
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_EVEN_BMSK                                0x7800
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_EVEN_SHFT                                    11
#define HWIO_PLL_USER_CTL_U_POST_DIV_RATIO_AUX_BMSK                              0x780
#define HWIO_PLL_USER_CTL_U_POST_DIV_RATIO_AUX_SHFT                                  7
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_BMSK                                   0x78
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_SHFT                                      3

#endif  /* __HALCLKRIVIANOLEPLL_H__ */
