/**
 *  @file mhi_tgt_config.c
 *
 *  @brief This file contains target-specific configuration.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_tgt_config.h"
#include "ChipInfoDefs.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
static const mhi_dev_cfg_t mhi_dev_cfgs[] =
{
   {
      .dev_id              = MHI_DEV_ID_SDX55,
      .pcie_vendor_id      = 0x17CB,
      .pcie_device_id      = 0x0306,
      .thread_name         = "MHIDEV",
      .thread_priority     = 0,
      .mhi_bar_idx         = 0x0,
      .mhi_bar_va          = 0xec000000,  // TODO
      .mhi_offset          = 0x0,
      .uses_bhie           = FALSE,
   },

   {
      .dev_id              = MHI_DEV_ID_MOSELLE,
      .pcie_vendor_id      = 0x17CB,
      .pcie_device_id      = 0x1105,
      .thread_name         = "MHIDEV",
      .thread_priority     = 0xD1,
      .mhi_bar_idx         = 0x0,
      .mhi_bar_va          = 0xec000000,  // TODO
      .mhi_offset          = 0x1E0E100,
      .mhi_msi_vector	   = 0,
      .bhi_msi_vector	   = 1,
      .m0_event_wait_time_out = 500000,
      .num_cr_elems            = 256,
      .num_chans           = 30, /* number of mhi channels */
      .chan_write_ack_time_out = 1000000,
   },

   {
      .dev_id                  = MHI_DEV_ID_HSP,
      .pcie_vendor_id          = 0x17CB,
      .pcie_device_id          = 0x1103,
      .thread_name             = "MHIDEV",
      .thread_priority         = 0x18,
      .mhi_bar_idx             = 0x0,
      .mhi_bar_va              = 0xec000000,  // TODO
      .mhi_offset              = 0x0,
      .mhi_msi_vector	       = 0,
      .bhi_msi_vector	       = 1,
      .m0_event_wait_time_out  = 500000,
      .num_cr_elems            = 256,
      .num_er_elems            = 256,
      .num_tr_elems            = 256,

      .num_ers                 = 2,
      .num_chans               = 30, /* number of mhi channels */
      .chan_write_ack_time_out = 1000000,
      .uses_bhie               = TRUE,
   },
};

const mhi_tgt_config_t mhi_tgt_cfg_palima =
{
   .target_chip_id = 0,  // will cover all chip SOC variants
   .target_chip_family = CHIPINFO_FAMILY_PALIMA,

   .log =
   {
      .name         = "mhi",
      .size         = 0x4000,
      .filter_level = PCIE_OSAL_LOG_LEVEL_LOW,
   },
   .profile_log =
   {
      .name         = "mhi_prof",
      .size         = 0x4000,
      .filter_level = PCIE_OSAL_LOG_LEVEL_MED,
   },
   .drv_thread_name       = "MHIDRV",
   .drv_thread_priority   = 0x18,
   .dev_cfgs              = mhi_dev_cfgs,
   .num_devs              = ARRAY_LENGTH(mhi_dev_cfgs),
};
