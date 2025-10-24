/*! \file pm_vrm_init.c
 *  \n
 *  \brief This file contains implementation for PMIC VRM initialization.
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/src/init/pm_vrm_init.c#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#include "pm_vrm.h"
#include "pm_app_vrm_init.h"
#include "device_info.h"
#include "page_select.h"
#include "pm_config_interface.h"


/*===========================================================================

                  LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                         LOCAL FUNCTION PROTOTYPES

===========================================================================*/

/*===========================================================================

                           VARIABLES DEFINITIONS

===========================================================================*/


/*===========================================================================

                            FUNCTION DEFINITIONS

===========================================================================*/

// initialize VRM and register PMIC resources to VRM
__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_init (void)
{
    vrm_init();
                     
    pm_vrm_register_resources ();

    vrm_post_init();
} 

__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_register_resources (void)
{
    uint8  pmic_count = 0;
    uint32 num_of_peripherals = 0;
    uint32 num_seq =0;
    uint8  num_of_pmics = PM_MAX_NUM_PMICS;
    pm_model_type pmic_model = PMIC_IS_INVALID;

    for(pmic_count = 0; pmic_count < num_of_pmics; pmic_count++)
    {
        pmic_model = pm_get_pmic_model(pmic_count);

        if((pmic_model == PMIC_IS_INVALID) || (pmic_model == PMIC_IS_UNKNOWN))
        {
            continue;
        }

        num_of_peripherals = pm_smps_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_pre_register_resource_dependencies(pmic_count, PM_VRM_PERIPH_SMPS, num_of_peripherals);
        }

        num_of_peripherals = pm_ldo_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_pre_register_resource_dependencies(pmic_count, PM_VRM_PERIPH_LDO, num_of_peripherals);
        }

        num_of_peripherals = pm_bob_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_pre_register_resource_dependencies(pmic_count, PM_VRM_PERIPH_BOB, num_of_peripherals);
        }

        num_of_peripherals = pm_clk_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           num_of_peripherals = num_of_peripherals - 1; //XO is not regisreted as one of the clk buffer resources
           pm_vrm_pre_register_resource_dependencies(pmic_count, PM_VRM_PERIPH_CLK, num_of_peripherals);
        }
    }

    //To rgister pre dependcency info for target specific resources
    pm_vrm_target_pre_register_resource_dependencies();

    for(pmic_count = 0; pmic_count < num_of_pmics; pmic_count++)
    {
        pmic_model = pm_get_pmic_model(pmic_count);

        if((pmic_model == PMIC_IS_INVALID) || (pmic_model == PMIC_IS_UNKNOWN))
        {
            continue;
        }

        num_seq = pm_target_information_get_periph_count_info(PM_PROP_PSTM_SEQ, pmic_count);
        if(num_seq > 0)
        {
           pm_vrm_pstm_register_resources(pmic_count, PM_VRM_PERIPH_PSTM, num_seq);
        }

        num_of_peripherals = pm_smps_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_vreg_register_resources(pmic_count, PM_VRM_PERIPH_SMPS, num_of_peripherals);
        }

        num_of_peripherals = pm_ldo_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_vreg_register_resources(pmic_count, PM_VRM_PERIPH_LDO, num_of_peripherals);
        }

        num_of_peripherals = pm_bob_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           pm_vrm_vreg_register_resources(pmic_count, PM_VRM_PERIPH_BOB, num_of_peripherals);
        }

        num_of_peripherals = pm_clk_get_num_peripherals(pmic_count);
        if(num_of_peripherals > 0)
        {
           num_of_peripherals = num_of_peripherals - 1; //XO is not regisreted as one of the clk buffer resources
           pm_vrm_clk_register_resources(pmic_count, PM_VRM_PERIPH_CLK, num_of_peripherals);
        }
    }

    // Target specific resources that needs to be registered in VRM (example: pbs, gpio)
    pm_vrm_target_register_resources();
   
}

__attribute__((section("rinit_code_sec_pool1")))
void pm_vrm_pre_register_resource_dependencies(uint8 pmic_index, pm_vrm_periph_type rsrc_type, uint32 num_rsrc)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   vrm_result result = VRM_SUCCESS;
   pm_app_vrm_pwr_info pwr_info = {0};
   pm_pwr_resource** rsrc_info = NULL;
   pm_pwr_resource* pm_rsrc_info = NULL;
   pm_pwr_resource_dependency_info** dep_info = NULL;
   pm_pwr_resource_dependency_info* pm_dep_info = NULL;
   char parent_name[VRM_MAX_RSRC_NAME_LEN] = {0};
   char alias_name[VRM_MAX_RSRC_NAME_LEN] = {0};
   char *alias_name_ptr = NULL;
   vrm_rsrc_category rsrc_category = VRM_RSRC_INVALID_CATEGORY;
   uint32 vreg_child_cnt = 0;
   uint32 xob_child_cnt = 0;
   uint32 rsrc_index = 0;
   uint32 rsrc_len = 0;
   char* rsrc_prop_id = NULL;
   char* dep_prop_id = NULL;
   pm_vrm_clk_info_type** clk_info = NULL;
   pm_vrm_clk_info_type* pm_clk_info = NULL;
           
   if(num_rsrc > 0)
   {
      if(rsrc_type == PM_VRM_PERIPH_CLK)
      {
         rsrc_prop_id = PM_PROP_CLK_RSRC;
         dep_prop_id = PM_PROP_CLK_DEP;
      }
      else
      {
         //abort if there was no driver initialized for this pmic
         err_flag = pm_app_vrm_vreg_get_pwr_info(pmic_index, rsrc_type, &pwr_info);
         CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);
         
         rsrc_prop_id = pwr_info.rsrc_prop_id;
         dep_prop_id = pwr_info.dep_prop_id;
      }

      rsrc_info = (pm_pwr_resource**)pm_target_information_get_specific_info(rsrc_prop_id);
      CORE_VERIFY_PTR(rsrc_info);

      dep_info = (pm_pwr_resource_dependency_info**)pm_target_information_get_specific_info(dep_prop_id);
      CORE_VERIFY_PTR(dep_info);

      clk_info = (pm_vrm_clk_info_type**)pm_target_information_get_specific_info(PM_PROP_CLK_INFO);
      CORE_VERIFY_PTR(clk_info);

      for( rsrc_index = 0; rsrc_index < num_rsrc; rsrc_index++)
      {
         memset(&parent_name, 0, VRM_MAX_RSRC_NAME_LEN);
         memset(&alias_name, 0, VRM_MAX_RSRC_NAME_LEN);
         vreg_child_cnt = 0;
         xob_child_cnt = 0;

         // *****GROUP ALL THE TARGET CONFIG ACCESSES TO ALLOW MOVING CONFIG DATA TO DDR*****
         
         // get local AOP address for the corresponding DDR address
         pm_rsrc_info = (pm_pwr_resource*)set_ddr_access((uint64_t)rsrc_info[pmic_index]);

         pm_dep_info = (pm_pwr_resource_dependency_info*)set_ddr_access((uint64_t)dep_info[pmic_index]);

         pm_clk_info = (pm_vrm_clk_info_type*)set_ddr_access((uint64_t)clk_info[pmic_index]);


         if((pm_rsrc_info != NULL) && (pm_dep_info != NULL) && (pm_dep_info[rsrc_index+1].children != NULL))
         {
            if(rsrc_type == PM_VRM_PERIPH_CLK && pm_clk_info != NULL)
            {
               rsrc_category = pm_clk_info[rsrc_index].RsrcCategory;
            }
            else
            {
               rsrc_category = VRM_RSRC_REGULATOR;
            }

            if(pm_rsrc_info[rsrc_index+1].name != NULL)
            {
               rsrc_len = strlen(pm_rsrc_info[rsrc_index+1].name)+1;
               if (rsrc_len <= VRM_MAX_RSRC_NAME_LEN)
               {
                  strlcpy(parent_name, pm_rsrc_info[rsrc_index+1].name, rsrc_len);
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
            vreg_child_cnt = pm_dep_info[rsrc_index+1].vreg_child_cnt;
            xob_child_cnt = pm_dep_info[rsrc_index+1].xob_child_cnt;
             if(pm_rsrc_info[rsrc_index+1].alias_name != NULL)
            {
               rsrc_len = strlen(pm_rsrc_info[rsrc_index+1].alias_name)+1;
               if (rsrc_len <= VRM_MAX_RSRC_NAME_LEN)
               {
                  strlcpy(alias_name, pm_rsrc_info[rsrc_index+1].alias_name, rsrc_len);
               }
               else
               {
                  err_flag |= PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
               }
               alias_name_ptr = alias_name;
             }
            else
            {
                alias_name_ptr = NULL;
            }
         }

         // DDR access complete for rsrc_info, dep_info
         set_page_select(0);
         set_page_select(0);

         // abort after ddr access is done
         CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);

         if((vreg_child_cnt > 0) || (xob_child_cnt > 0))
         {
            result = vrm_pre_register_parent_rsrc_names(rsrc_category, parent_name, alias_name_ptr, vreg_child_cnt, xob_child_cnt);
            CORE_VERIFY(result == VRM_SUCCESS);
         }
      }
   }
}
