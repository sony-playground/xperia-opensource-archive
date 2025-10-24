#ifndef __HALCLKPONGOEKAPLL_H__
#define __HALCLKPONGOEKAPLL_H__
/*
==============================================================================

FILE:         HALclkPongoEkaPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================
    Copyright (c) 2020 QUALCOMM Technologies Incorporated.
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
#define HWIO_PLL_MODE_OFFS                                  0x00000000
#define HWIO_PLL_OPMODE_OFFS                                0x00000004
#define HWIO_PLL_STATE_OFFS                                 0x00000008
#define HWIO_PLL_L_VAL_OFFS                                 0x00000010
#define HWIO_PLL_USER_CTL_OFFS                              0x00000014
#define HWIO_PLL_USER_CTL_U_OFFS                            0x00000018
#define HWIO_PLL_CONFIG_CTL_OFFS                            0x0000001C
#define HWIO_PLL_CONFIG_CTL_U_OFFS                          0x00000020
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                         0x00000024
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                         0x00000028
#define HWIO_PLL_TEST_CTL_OFFS                              0x0000002C
#define HWIO_PLL_TEST_CTL_U_OFFS                            0x00000030
#define HWIO_PLL_TEST_CTL_U1_OFFS                           0x00000034
#define HWIO_PLL_TEST_CTL_U2_OFFS                           0x00000038
#define HWIO_PLL_TEST_CTL_U3_OFFS                           0x0000003C

/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_LOCK_DET_BMSK                         0x80000000
#define HWIO_PLL_MODE_LOCK_DET_SHFT                               0x1f
#define HWIO_PLL_MODE_LOCK_DET_COARSE_BMSK                  0x40000000
#define HWIO_PLL_MODE_LOCK_DET_COARSE_SHFT                        0x1e
#define HWIO_PLL_MODE_CLOCK_SELECT_BMSK                         0x1000
#define HWIO_PLL_MODE_CLOCK_SELECT_SHFT                            0xc
#define HWIO_PLL_MODE_REQUESTS_CAL_BMSK                          0x800
#define HWIO_PLL_MODE_REQUESTS_CAL_SHFT                            0xb
#define HWIO_PLL_MODE_CAL_XO_PRESENT_BMSK                        0x400
#define HWIO_PLL_MODE_CAL_XO_PRESENT_SHFT                          0xa
#define HWIO_PLL_MODE_IN_CALIBRATION_BMSK                        0x200
#define HWIO_PLL_MODE_IN_CALIBRATION_SHFT                          0x9
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_BMSK                        0x80
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_SHFT                         0x7
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                        0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                         0x4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                         0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                         0x3
#define HWIO_PLL_MODE_RESET_N_BMSK                                 0x4
#define HWIO_PLL_MODE_RESET_N_SHFT                                 0x2
#define HWIO_PLL_MODE_OUTCTRL_BMSK                                 0x1
#define HWIO_PLL_MODE_OUTCTRL_SHFT                                 0x0

/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_11_BMSK            0xfffff800
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_11_SHFT                   0xb
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK               0x400
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                 0xa
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_MAIN_BMSK               0x3c0
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_MAIN_SHFT                 0x6
#define HWIO_PLL_USER_CTL_RESERVE_BIT5_BMSK                       0x20
#define HWIO_PLL_USER_CTL_RESERVE_BIT5_SHFT                        0x5
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_BMSK                     0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_SHFT                      0x4
#define HWIO_PLL_USER_CTL_RESERVE_BITS3_2_BMSK                     0xc
#define HWIO_PLL_USER_CTL_RESERVE_BITS3_2_SHFT                     0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_BMSK                      0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_SHFT                      0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_BMSK                      0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_SHFT                      0x0

/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_ENABLE_32KHZ_FAST_LOCK_BMSK     0x80000000
#define HWIO_PLL_USER_CTL_U_ENABLE_32KHZ_FAST_LOCK_SHFT           0x1f
#define HWIO_PLL_USER_CTL_U_OUT_CLK_POLARITY_BMSK           0x40000000
#define HWIO_PLL_USER_CTL_U_OUT_CLK_POLARITY_SHFT                 0x1e
#define HWIO_PLL_USER_CTL_U_USR_FULL_SAVE_BMSK              0x20000000
#define HWIO_PLL_USER_CTL_U_USR_FULL_SAVE_SHFT                    0x1d
#define HWIO_PLL_USER_CTL_U_USR_SAVE_SELECT_BMSK            0x18000000
#define HWIO_PLL_USER_CTL_U_USR_SAVE_SELECT_SHFT                  0x1b
#define HWIO_PLL_USER_CTL_U_ENABLE_LOW_LATENCY_CLK_BMSK      0x4000000
#define HWIO_PLL_USER_CTL_U_ENABLE_LOW_LATENCY_CLK_SHFT           0x1a
#define HWIO_PLL_USER_CTL_U_ENABLE_STANDBY_CLK_BMSK          0x2000000
#define HWIO_PLL_USER_CTL_U_ENABLE_STANDBY_CLK_SHFT               0x19
#define HWIO_PLL_USER_CTL_U_SET_MAX_COMP_RATE_BMSK           0x1000000
#define HWIO_PLL_USER_CTL_U_SET_MAX_COMP_RATE_SHFT                0x18
#define HWIO_PLL_USER_CTL_U_ENABLE_CONT_CAL_BMSK              0x800000
#define HWIO_PLL_USER_CTL_U_ENABLE_CONT_CAL_SHFT                  0x17
#define HWIO_PLL_USER_CTL_U_XO_FREQUENCY_SELECT_BMSK          0x400000
#define HWIO_PLL_USER_CTL_U_XO_FREQUENCY_SELECT_SHFT              0x16
#define HWIO_PLL_USER_CTL_U_INTERNAL_CLOCK_SELECTION_BMSK     0x300000
#define HWIO_PLL_USER_CTL_U_INTERNAL_CLOCK_SELECTION_SHFT         0x14
#define HWIO_PLL_USER_CTL_U_INITIAL_OUTPUT_CLOCK_MUX_BMSK      0x18000
#define HWIO_PLL_USER_CTL_U_INITIAL_OUTPUT_CLOCK_MUX_SHFT          0xf
#define HWIO_PLL_USER_CTL_U_KEEP_BIAS_ON_IN_STBY_BMSK           0x4000
#define HWIO_PLL_USER_CTL_U_KEEP_BIAS_ON_IN_STBY_SHFT              0xe
#define HWIO_PLL_USER_CTL_U_XO_CLK_AT_OUT_BMSK                  0x2000
#define HWIO_PLL_USER_CTL_U_XO_CLK_AT_OUT_SHFT                     0xd
#define HWIO_PLL_USER_CTL_U_CALIBRATION_SETTING_BMSK            0x1000
#define HWIO_PLL_USER_CTL_U_CALIBRATION_SETTING_SHFT               0xc
#define HWIO_PLL_USER_CTL_U_USE_RESTORE_BMSK                     0x800
#define HWIO_PLL_USER_CTL_U_USE_RESTORE_SHFT                       0xb
#define HWIO_PLL_USER_CTL_U_REQUEST_CAL_BMSK                     0x400
#define HWIO_PLL_USER_CTL_U_REQUEST_CAL_SHFT                       0xa
#define HWIO_PLL_USER_CTL_U_CAL_SCALING_BMSK                       0x6
#define HWIO_PLL_USER_CTL_U_CAL_SCALING_SHFT                       0x1
#define HWIO_PLL_USER_CTL_U_USE_EXTERNAL_CLK_REF_BMSK              0x1
#define HWIO_PLL_USER_CTL_U_USE_EXTERNAL_CLK_REF_SHFT              0x0


#endif  /* __HALCLKPONGOEKAPLL_H__ */
