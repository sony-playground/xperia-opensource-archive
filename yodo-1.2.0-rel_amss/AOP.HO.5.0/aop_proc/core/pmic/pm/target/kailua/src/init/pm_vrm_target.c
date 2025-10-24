/*! \file pm_vrm_target.c
 *  \n
 *  \brief This file contains implementation for PMIC TARGET specific resources registration to RPMh VRM.
 *  \n  
 *  \n &copy; Copyright 2017 - 2018 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/target/kailua/src/init/pm_vrm_target.c#2 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/06/17   kt      Created.
===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#include "pm_vrm.h"
#include "device_info.h"
#include "pm_target_information.h"
#include "page_select.h"
#include "pm_rpmh_target.h"
#include "pm_config_interface.h"

// PBS software seq trigger argument to get the wait time 0x5
#define PM_PBS_SEQ_WAIT_TIME_ARG 0x5
// 1 sleep clock cycle in micro secs
#define PM_PBS_SEQ_1SLP_CLK_USEC 30

// making this static variable instead of local variable to avoid stack overflow
__attribute__((section("pm_dram_reclaim_pool")))
static vrm_pmic_rsrc_data pmic_rsrc_data;

__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_target_register_resources(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   vrm_result result = VRM_SUCCESS;
   uint32 slave_id = 0;
   uint16 base_addr = 0;
   pm_vrm_target_rsrc_info_type* target_rsrc_info = NULL;
   pm_vrm_target_rsrc_info_type* rsrc_info = NULL;
   uint32* num_rsrc = NULL;
   uint32 rsrc_len = 0;
   uint32 index = 0;
   pm_on_off_type enable_status = PM_OFF;
   uint8 enable_data = 0;
   uint8 mode_data = 0;
   uint8 access_allowed = 0;
   pm_vrm_periph_info periph_info;
   pm_vrm_pbs_seq_status seq_status;
   uint32 drv_owner_mask = 0;

   memset(&pmic_rsrc_data, 0, sizeof(vrm_pmic_rsrc_data));
   memset(&periph_info, 0, sizeof(pm_vrm_periph_info));
   memset(&seq_status, 0, sizeof(pm_vrm_pbs_seq_status));

   // *****GROUP ALL THE TARGET CONFIG ACCESSES TO ALLOW MOVING CONFIG DATA TO DDR*****

   target_rsrc_info = (pm_vrm_target_rsrc_info_type*)pm_target_information_get_specific_info(PM_PROP_TARGET_RSRC_INFO);

   num_rsrc = (uint32*)pm_target_information_get_specific_info(PM_PROP_TARGET_RSRC_NUM);
   CORE_VERIFY_PTR(num_rsrc);

   for (index = 0; index < *num_rsrc; index++)
   {
      access_allowed = 0;
      // *****GROUP ALL THE TARGET CONFIG ACCESSES TO ALLOW MOVING CONFIG DATA TO DDR*****

      // get local AOP address for the corresponding DDR address
      rsrc_info = (pm_vrm_target_rsrc_info_type*)set_ddr_access((uint64_t)target_rsrc_info);

      if(rsrc_info == NULL)
      {
         err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
      }
      else
      {
         access_allowed = rsrc_info[index].config.AccessAllowed;
      }

      if ((access_allowed) && (rsrc_info != NULL))
      {
         memset(&pmic_rsrc_data, 0, sizeof(vrm_pmic_rsrc_data));

         // make all the sequence types as dummy sequence for the resource
         pmic_rsrc_data.mode_info.seq_type = VRM_NO_PMIC_SEQ;
         pmic_rsrc_data.volt_info.seq_type = VRM_NO_PMIC_SEQ;
         pmic_rsrc_data.enable_info.seq_type = VRM_NO_PMIC_SEQ;

         // pmic rsrc info
         if (rsrc_info[index].name != NULL)
         {
            rsrc_len = strlen(rsrc_info[index].name)+1;
            if (rsrc_len <= VRM_MAX_RSRC_NAME_LEN)
            {
              strlcpy(pmic_rsrc_data.rsrc_name, rsrc_info[index].name, rsrc_len);
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

         slave_id = rsrc_info[index].config.SlaveId;
         base_addr = rsrc_info[index].config.BaseAddr;

         pmic_rsrc_data.periph_info.pmic_index = rsrc_info[index].PmicIndex;
         pmic_rsrc_data.periph_info.periph_type = rsrc_info[index].PeriphType;
         pmic_rsrc_data.base_addr = base_addr;
         pmic_rsrc_data.base_addr = (slave_id << 16) | pmic_rsrc_data.base_addr;

         // periph id has to be >= 1
         if (rsrc_info[index].PeriphId >= 1)
         {
            pmic_rsrc_data.periph_info.periph_index = rsrc_info[index].PeriphId - 1;
         }

         pmic_rsrc_data.rsrc_category = (vrm_rsrc_category)rsrc_info[index].config.RsrcCategory;
         err_flag |= pm_vrm_get_drv_mask(rsrc_info[index].config.DrvOwnMask, &drv_owner_mask);
         pmic_rsrc_data.drv_owner_mask = drv_owner_mask;

         // mode info
         if (rsrc_info[index].config.ModeAddrOff != 0)
         {
            pmic_rsrc_data.mode_info.addr_offset = rsrc_info[index].config.ModeAddrOff;
            pmic_rsrc_data.mode_info.fixed_time_usec = rsrc_info[index].config.ModeFixedTime;
            pmic_rsrc_data.mode_info.seq_type = (vrm_seq_type)rsrc_info[index].config.ModeSeqType;
         }

         // enable info
         if (rsrc_info[index].config.EnableAddrOff != 0)
         {
            pmic_rsrc_data.enable_info.addr_offset = rsrc_info[index].config.EnableAddrOff;
            pmic_rsrc_data.enable_info.fixed_time_usec = rsrc_info[index].config.EnableFixedTime;
            pmic_rsrc_data.enable_info.seq_type = (vrm_seq_type)rsrc_info[index].config.EnableSeqType;
         }

         // volt info
         if (rsrc_info[index].config.VoltAddrOff != 0)
         {
            pmic_rsrc_data.volt_info.addr_offset = rsrc_info[index].config.VoltAddrOff;
            pmic_rsrc_data.volt_info.fixed_time_usec = rsrc_info[index].config.VoltFixedTime;
            pmic_rsrc_data.volt_info.seq_type = (vrm_seq_type)rsrc_info[index].config.VoltSeqType;
            pmic_rsrc_data.volt_max_state = rsrc_info[index].config.MaxVoltage;
         }
      }

      // DDR access complete
      set_page_select(0);

      // abort after ddr access is done
      CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);

      err_flag = pm_rpmh_update_rsrc_config(&pmic_rsrc_data, &access_allowed);

      if (access_allowed)
      {
         //*****SPMI COMM ACCESS START FROM HERE*****


         // Get VRM arbiter id
         err_flag = pm_comm_get_vrm_id (slave_id, base_addr, &pmic_rsrc_data.vrm_arb_id); 
         //CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
         // temp hack to unblock dependencies
         if (err_flag != PM_ERR_FLAG_SUCCESS)
         {
            err_flag = PM_ERR_FLAG_SUCCESS;
            continue;
         }

         // mode info
         if (pmic_rsrc_data.mode_info.addr_offset != 0)
         {
            if (slave_id < PM_MAX_NUM_SLAVE_IDS)
            {
               err_flag = pm_comm_read_byte(slave_id, base_addr + pmic_rsrc_data.mode_info.addr_offset, &mode_data, 0);
               CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
               pmic_rsrc_data.mode_info.current_state = mode_data;
            }
         }

         // enable info
         if (pmic_rsrc_data.enable_info.addr_offset != 0)
         {
            if (slave_id < PM_MAX_NUM_SLAVE_IDS)
            {
               err_flag = pm_comm_read_byte(slave_id, base_addr + pmic_rsrc_data.enable_info.addr_offset, &enable_data, 0);
               CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);

               if (enable_data & 0x80)
               {
                  enable_status = PM_ON;
               }
               else
               {
                  enable_status = PM_OFF;
               }

               pmic_rsrc_data.enable_info.current_state = enable_status;
            }
         }

         if (pmic_rsrc_data.periph_info.periph_type == PM_VRM_PERIPH_SOC)
         {
            pmic_rsrc_data.enable_info.current_state = PM_ON;
            pmic_rsrc_data.dep_en = TRUE;
         }

         result = vrm_register_rsrc(&pmic_rsrc_data);
         CORE_VERIFY(result == VRM_SUCCESS);
      }
   }
}

__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_target_pre_register_resource_dependencies()
{
	
}
