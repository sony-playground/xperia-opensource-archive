#ifndef __HALCLKZondaolePLL_H__
#define __HALCLKZondaolePLL_H__
/*
==============================================================================

FILE:         HALclkZondaolePLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.
  
    Copyright (c) 2020-2022 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "stdbool.h"
#include "HALclkInternal.h"


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
#define HWIO_PLL_MODE_OFFS                                                  0x0
#define HWIO_PLL_L_VAL_OFFS                                                 0x4
#define HWIO_PLL_ALPHA_VAL_OFFS                                             0x8
#define HWIO_PLL_USER_CTL_OFFS                                              0xc
#define HWIO_PLL_USER_CTL_U_OFFS                                           0x10
#define HWIO_PLL_CONFIG_CTL_OFFS                                           0x14
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                         0x18
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                                        0x1c
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                                        0x20
#define HWIO_PLL_TEST_CTL_OFFS                                             0x24
#define HWIO_PLL_TEST_CTL_U_OFFS                                           0x28
#define HWIO_PLL_TEST_CTL_U1_OFFS                                          0x2c
#define HWIO_PLL_OPMODE_OFFS                                               0x30
#define HWIO_PLL_SSC_OFFS                                                  0x34
#define HWIO_PLL_DROOP_CTL_OFFS                                            0x38
#define HWIO_PLL_STATUS_OFFS                                               0x3c
#define HWIO_PLL_STATE_OFFS                                                0x40


/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                              0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                      31
#define HWIO_PLL_MODE_FREQ_LOCK_DET_BMSK                             0x40000000
#define HWIO_PLL_MODE_FREQ_LOCK_DET_SHFT                                     30
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                               0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                   14
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                 0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                     13
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                      0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                        2
#define HWIO_PLL_MODE_PLL_BYPASSNL_BMSK                                     0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_SHFT                                       1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                      0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                        0


/*
 * PLL_L_VAL register definitions.
 */
#define HWIO_PLL_L_VAL_PLL_L_BMSK                                          0xff
#define HWIO_PLL_L_VAL_PLL_L_SHFT                                             0


/*
 * PLL_ALPHA_VAL register definitions.
 */
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_BMSK                            0xffff
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_SHFT                                 0


/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                        0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                               25
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_BMSK                          0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_SHFT                             4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_BMSK                            0x8
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_SHFT                              3
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_BMSK                           0x4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_SHFT                             2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_BMSK                           0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_SHFT                             1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_BMSK                           0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_SHFT                             0


/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_BMSK                  0x10000000
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_SHFT                          28
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_BMSK                 0x2000000
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_SHFT                        25
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_BMSK                       0x20000
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_SHFT                            17
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_BMSK                        0x3000
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_SHFT                            12


/* ============================================================================
**    External Definitions
** ==========================================================================*/


/* ============================================================================
**    External Definitions
** ==========================================================================*/

#endif  /* __HALCLKZondaolePLL_H__ */

