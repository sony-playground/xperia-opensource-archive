/*! \file pm_vrm_pstm.c
 *  \n
 *  \brief This file contains implementation for PMIC PSTM resource registration to RPMh VRM.
 *  \n  
 *  \n &copy; Copyright 2016 - 2020 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/src/init/pm_vrm_pstm.c#2 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#include "pm_vrm.h"
#include "pm_app_vrm_init.h"
#include "pm_rpmh_target.h"
#include "device_info.h"
#include "pm_config_interface.h"

#define PSTM_PBS_READY_EN 0x01

// making this static variable instead of local variable to avoid stack overflow
__attribute__((section("pm_dram_reclaim_pool")))
static vrm_pmic_rsrc_data pstm_rsrc_data;

__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_pstm_register_resources(uint8 pmic_index, pm_vrm_periph_type pstm_type, uint32 num_pstm)
{

  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  vrm_result result = VRM_SUCCESS;
  pm_vrm_pstm_rsrc_info_type** pstm_rsrc_info = NULL;
  pm_vrm_pstm_rsrc_info_type* rsrc_info = NULL;
  pm_pstm_data_type *pstm_ptr = NULL;
  uint32 slave_id = 0;
  uint16 base_addr = 0;
  uint32 rsrc_len = 0;
  uint32 index = 0;
  uint8 access_allowed = 0;  
  uint32 drv_owner_mask = 0;

  if(num_pstm > 0)
  {
      pstm_rsrc_info = (pm_vrm_pstm_rsrc_info_type**)pm_target_information_get_specific_info(PM_PROP_PSTM_INFO);
      CORE_VERIFY_PTR(pstm_rsrc_info);
      
      for (index = 0; index < num_pstm ; index++)
      {
         access_allowed = 0;

         // get local AOP address for the corresponding DDR address
         rsrc_info = (pm_vrm_pstm_rsrc_info_type*)set_ddr_access((uint64_t)pstm_rsrc_info[pmic_index]);

         if(rsrc_info == NULL)
         {
            err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
         }
         else
         {
            access_allowed = rsrc_info[index].AccessAllowed;
         }
         if ((access_allowed) && (rsrc_info != NULL))
         {
            memset(&pstm_rsrc_data, 0, sizeof(vrm_pmic_rsrc_data));

            // pmic rsrc info
            if (rsrc_info[index].pbs_name != NULL)
            {
               rsrc_len = strlen(rsrc_info[index].pbs_name)+1;
               if (rsrc_len <= VRM_MAX_RSRC_NAME_LEN)
               {
                 strlcpy(pstm_rsrc_data.rsrc_name, rsrc_info[index].pbs_name, rsrc_len);
               }
               else
               {
                  err_flag |= PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
               }
            }
            else
            {
               err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
            }

            pstm_rsrc_data.periph_info.pmic_index = pmic_index;
            pstm_rsrc_data.periph_info.periph_type = pstm_type;
            pstm_rsrc_data.periph_info.periph_index = index;

            pstm_rsrc_data.pstm_low_val = rsrc_info[index].LowVal;
            pstm_rsrc_data.pstm_high_val = rsrc_info[index].HighVal;
            err_flag |= pm_vrm_get_drv_mask(rsrc_info[index].DrvOwnMask, &drv_owner_mask);
            pstm_rsrc_data.drv_owner_mask = drv_owner_mask;
            pstm_rsrc_data.pstm_default_val = rsrc_info[index].DefaultVal;
            pstm_rsrc_data.rsrc_category = (vrm_rsrc_category)rsrc_info[index].RsrcCategory;
            pstm_rsrc_data.enable_info.seq_type = (vrm_seq_type)rsrc_info[index].EnableSeqType;
            pstm_rsrc_data.enable_info.fixed_time_usec = rsrc_info[index].SettlingTime;
            pstm_rsrc_data.pstm_pbs_ready_en = PSTM_PBS_READY_EN;
         }

         // DDR access complete
         set_page_select(0);

         // abort after ddr access is done
         CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);

         err_flag = pm_rpmh_update_rsrc_config(&pstm_rsrc_data, &access_allowed);

         if (access_allowed)
         {
            //abort if there was no driver initialized for this pmic 
            pstm_ptr = pm_pstm_get_data(pmic_index);
            CORE_VERIFY_PTR(pstm_ptr);

            //*****SPMI COMM ACCESS START FROM HERE****
            slave_id  = pstm_ptr->comm_ptr->slave_id;
            base_addr = pstm_ptr->base_address;
            pstm_rsrc_data.base_addr = base_addr;
            pstm_rsrc_data.base_addr = (slave_id << 16) | pstm_rsrc_data.base_addr;

            pstm_rsrc_data.enable_info.addr_offset = pstm_ptr->pstm_reg_table->SW_ARG;
            
            // Get VRM arbiter id
            if (pstm_rsrc_data.rsrc_category != VRM_RSRC_LOCAL)
            {
               err_flag = pm_comm_get_vrm_id (slave_id, base_addr, &pstm_rsrc_data.vrm_arb_id); 
               CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
            }

            result = vrm_register_rsrc(&pstm_rsrc_data);
            CORE_VERIFY(result == VRM_SUCCESS);
         }
      
      }
     
  }

}

