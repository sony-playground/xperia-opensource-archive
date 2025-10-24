#ifndef __HALCLKTAYCANPLL_H__
#define __HALCLKTAYCANPLL_H__
/*
==============================================================================

FILE:         HALclkTaycanPLL.h

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
#define HWIO_PLL_MODE_OFFS                                              0x00000000
#define HWIO_PLL_OPMODE_OFFS                                            0x00000004
#define HWIO_PLL_STATE_OFFS                                             0x00000008
#define HWIO_PLL_L_VAL_OFFS                                             0x00000010
#define HWIO_PLL_ALPHA_VAL_OFFS                                         0x00000014
#define HWIO_PLL_USER_CTL_OFFS                                          0x00000018
#define HWIO_PLL_USER_CTL_U_OFFS                                        0x0000001C
#define HWIO_PLL_CONFIG_CTL_OFFS                                        0x00000020
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                      0x00000024
#define HWIO_PLL_TEST_CTL_OFFS                                          0x00000028
#define HWIO_PLL_TEST_CTL_U_OFFS                                        0x0000002C

/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                 0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                       0x1f
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_BMSK                            0x20000000
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_SHFT                                  0x1d
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                                  0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                     0xe
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                    0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                       0xd
#define HWIO_PLL_MODE_PCAL_NOT_DONE_BMSK                                     0x100
#define HWIO_PLL_MODE_PCAL_NOT_DONE_SHFT                                       0x8
#define HWIO_PLL_MODE_OUT_ODD_HW_CTL_BMSK                                     0x20
#define HWIO_PLL_MODE_OUT_ODD_HW_CTL_SHFT                                      0x5
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                    0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                     0x4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                     0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                     0x3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                         0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                         0x2
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                         0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                         0x0

/*
 * PLL_L_VAL register definitions.
 */
#define HWIO_PLL_L_VAL_PLL_CAL_L_VAL_BMSK                                 0xff0000
#define HWIO_PLL_L_VAL_PLL_CAL_L_VAL_SHFT                                     0x10
#define HWIO_PLL_L_VAL_PLL_L_VAL_BMSK                                         0xff
#define HWIO_PLL_L_VAL_PLL_L_VAL_SHFT                                          0x0

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
#define HWIO_PLL_USER_CTL_FRAC_FORMAT_SEL_BMSK                          0x10000000
#define HWIO_PLL_USER_CTL_FRAC_FORMAT_SEL_SHFT                                0x1c
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_BMSK                    0x8000000
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_SHFT                         0x1b
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_BMSK                          0x4000000
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_SHFT                               0x1a
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                           0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                                0x19
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                             0x1c00000
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                  0x16
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_ODD_BMSK                          0x3c000
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_ODD_SHFT                              0xe
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                          0x3c00
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                             0xa
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_BMSK                                 0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_SHFT                                  0x4
#define HWIO_PLL_USER_CTL_PLLOUT_ODD_EN_BMSK                                   0x4
#define HWIO_PLL_USER_CTL_PLLOUT_ODD_EN_SHFT                                   0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_BMSK                                  0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_SHFT                                  0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_BMSK                                  0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_SHFT                                  0x0

/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_BB_MODE_BMSK                                       0x8
#define HWIO_PLL_USER_CTL_U_BB_MODE_SHFT                                       0x3
#define HWIO_PLL_USER_CTL_U_FDC_MODE_BMSK                                      0x4
#define HWIO_PLL_USER_CTL_U_FDC_MODE_SHFT                                      0x2
#define HWIO_PLL_USER_CTL_U_FLL_MODE_BMSK                                      0x2
#define HWIO_PLL_USER_CTL_U_FLL_MODE_SHFT                                      0x1
#define HWIO_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                                0x1
#define HWIO_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                0x0

#endif  /* __HALCLKTAYCANPLL_H__ */
