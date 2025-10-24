/**
 *  @file mhi_tgt_config.c
 *
 *  @brief This file contains the implementation of MHI target config routines.
 */
/*============================================================================
               Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

#include "mhi_i.h"

extern mhi_tgt_config_t mhi_tgt_cfg_lahaina;
extern mhi_tgt_config_t mhi_tgt_cfg_makena;
extern mhi_tgt_config_t mhi_tgt_cfg_waipio;
extern mhi_tgt_config_t mhi_tgt_cfg_palima;
extern mhi_tgt_config_t mhi_tgt_cfg_kailua;

mhi_tgt_config_t *mhi_tgt_cfg_data[] = 
{
   &mhi_tgt_cfg_lahaina,
   &mhi_tgt_cfg_makena,
   &mhi_tgt_cfg_waipio,
   &mhi_tgt_cfg_palima,
   &mhi_tgt_cfg_kailua,
};

/**
   @brief
   Initializes target specific config data

   @details
   Initializes target specific configuration data to be used by the MHI host
   driver

   @return
   pointer to target configuration data, or NULL if there was an error

*/
mhi_tgt_config_t* mhi_get_tgt_cfg(void)
{
   uint32 chip_id, chip_ver, plat_info, i, chip_family;
   mhi_tgt_config_t *family_match_cfg = NULL, *id_match_cfg = NULL;
   mhi_tgt_config_t *cfg_ptr = NULL;

   if (pcie_get_target_platform_info (&chip_id, &chip_ver, &chip_family, &plat_info) != PCIE_SUCCESS)
   {
      MHI_LOG_HIGH("Could not get chip/platform info");
      return NULL;
   }

   if ((chip_id == 0) || (chip_family == 0))
   {
      MHI_LOG_HIGH("Could not get chip/platform info");
      return NULL;
   }

   for (i = 0; i < ARRAY_SIZE(mhi_tgt_cfg_data); ++i)
   {
      if ((mhi_tgt_cfg_data[i]->target_chip_id == 0) && (mhi_tgt_cfg_data[i]->target_chip_family == 0))
         continue; // Bad config skip over

      if (mhi_tgt_cfg_data[i]->target_chip_id == 0)
      {
         if (mhi_tgt_cfg_data[i]->target_chip_family == chip_family)
            family_match_cfg = mhi_tgt_cfg_data[i];
      }
      else
      {
         if (mhi_tgt_cfg_data[i]->target_chip_family != 0)
         {
            if ((mhi_tgt_cfg_data[i]->target_chip_id == chip_id) &&
                (mhi_tgt_cfg_data[i]->target_chip_family == chip_family))
            {
               cfg_ptr = mhi_tgt_cfg_data[i];
               break;  // This would be the best fit, stop search
            }
         }
         else if (mhi_tgt_cfg_data[i]->target_chip_id == chip_id)
            id_match_cfg = mhi_tgt_cfg_data[i];
      }
   }

   if (cfg_ptr == NULL)
   {
      if (id_match_cfg != NULL)
         cfg_ptr = id_match_cfg;
      else if (family_match_cfg != NULL)
         cfg_ptr = family_match_cfg;
   }

   return cfg_ptr;
}
