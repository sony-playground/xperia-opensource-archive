/*==============================================================================
  FILE:         rsc_config.c

  OVERVIEW:     This file contains target specific data/configuration for rsc
                instances.

  DEPENDENCIES: None

                Copyright (c) 2018, 2021 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================*/

#include "rsc.h"
#include "rsc_seq_hal.h"
#include "rsc_hal_bsp.h"
#include "msmhwiobase.h"

/*==========================================================================
 *                           INTERNAL MACROS
 *=========================================================================*/

/**
 * @brief Common macro to fill out structure members for array followed by
 *        its size.
 */
#define RSC_ARRAY(arr) arr, ARRAY_SIZE(arr)

static rsc_cmd_t cam_rsc_rsc_sleep[] =
{
//MAIN:
  0x21022004,  //0x000: 0x2004   BEQ       channel_to_use_0=0            CHANNEL_1
               //0x002: 0x2102   BEQ       channel_switch_active=0       CHECK_ACTIVE_PULSE_CH_0
  0x40045004,  //0x004: 0x5004   SET1      channel_busy
               //0x006: 0x4004   SET0      channel_busy
//ACTIVE_CH_O:
  0x70005000,  //0x008: 0x5000   SET1      active_tcs_trigger_ch0
               //0x00a: 0x7000   WAIT1     active_tcs_complete_ch0
  0x18004000,  //0x00c: 0x4000   SET0      active_tcs_trigger_ch0
               //0x00e: 0x1800   JMP       MAIN
//CHECK_ACTIVE_PULSE_CH_0:
  0x18012083,  //0x010: 0x2083   BEQ       active_tcs_vote=0             CHECK_IDLE_CH_0
               //0x012: 0x1801   JMP       ACTIVE_CH_O
//CHECK_IDLE_CH_0:
  0x500120c8,  //0x014: 0x20c8   BEQ       idle_tcs_vote=0               END
               //0x016: 0x5001   SET1      idle_tcs_trigger_ch0
  0x40017001,  //0x018: 0x7001   WAIT1     idle_tcs_complete_ch0
               //0x01a: 0x4001   SET0      idle_tcs_trigger_ch0
  0x20481800,  //0x01c: 0x1800   JMP       MAIN
//CHANNEL_1:
               //0x01e: 0x2048   BEQ       channel_to_use_1=0            END
  0x50042106,  //0x020: 0x2106   BEQ       channel_switch_active=0       CHECK_ACTIVE_PULSE_CH_1
               //0x022: 0x5004   SET1      channel_busy
  0x50024004,  //0x024: 0x4004   SET0      channel_busy
//ACTIVE_CH_1:
               //0x026: 0x5002   SET1      active_tcs_trigger_ch1
  0x40027002,  //0x028: 0x7002   WAIT1     active_tcs_complete_ch1
               //0x02a: 0x4002   SET0      active_tcs_trigger_ch1
  0x20871800,  //0x02c: 0x1800   JMP       MAIN
//CHECK_ACTIVE_PULSE_CH_1:
               //0x02e: 0x2087   BEQ       active_tcs_vote=0             CHECK_IDLE_CH_1
  0x20c81805,  //0x030: 0x1805   JMP       ACTIVE_CH_1
//CHECK_IDLE_CH_1:
               //0x032: 0x20c8   BEQ       idle_tcs_vote=0               END
  0x70035003,  //0x034: 0x5003   SET1      idle_tcs_trigger_ch1
               //0x036: 0x7003   WAIT1     idle_tcs_complete_ch1
  0x18004003,  //0x038: 0x4003   SET0      idle_tcs_trigger_ch1
               //0x03a: 0x1800   JMP       MAIN
//END:
  0x00001000   //0x03c: 0x1000   RETURN
               //0x03e: 0x0000


};

static rsc_hal_br_info_t cam_rsc_seq_br_info[] =
{
  {0x0}, // MAIN
  {0x8}, // ACTIVE_CH_O
  {0x10}, // CHECK_ACTIVE_PULSE_CH_0
  {0x14}, // CHECK_IDLE_CH_0
  {0x1e}, // CHANNEL_1
  {0x26}, // ACTIVE_CH_1
  {0x2e}, // CHECK_ACTIVE_PULSE_CH_1
  {0x32}, // CHECK_IDLE_CH_1
  {0x3c}  // END
};

/**
 * @brief CAM mode configurations
 */
static rsc_hal_bsp_mode_t cam_rsc_modes[] =
{
  {
    {RSC_ARRAY(cam_rsc_rsc_sleep)},
    0,
    0,
    0,
    0,
    cam_rsc_seq_br_info,
     ARRAY_SIZE(cam_rsc_seq_br_info),
    NULL,
    0
  },
};

/**
 * @brief Array containing necessary information of each rsc instance on a
 *        given subsystem.
 */
rsc_t g_rsc_instances[] =
{
  {
    "cam",
	EXTENDED_32BIT_MODE,
    cam_rsc_modes,
    ARRAY_SIZE(cam_rsc_modes),
    (uint8 *)(TITAN_SS_BASE + 0x001d9000),
    0x0
  }

};

/**
 * @brief Variable to indicate rsc instance counts.
 *
 * @note This will be externed in to rsc target file.
 */
size_t g_rsc_count =
  sizeof(g_rsc_instances)/sizeof(g_rsc_instances[0]);

