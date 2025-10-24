/*! \file pm_resource_manager.c
 *  
 *  \brief  This file contains the initialization functions for PMIC resource manager.
 *  
 *  &copy; Copyright 2011-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/framework/src/init/pm_resource_manager.c#2 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "pm_comm.h"
#include "pm_config_interface.h"
/* PMIC Driver includes */
#include "pm_smps_driver.h"
#include "pm_ldo_driver.h"
#include "pm_bob_driver.h"
#include "pm_clk_driver.h"
#include "pm_pstm_driver.h"
#include "pm_app_vrm_init.h"

#include "hw_module_type.h"
#include "device_info.h"

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

/*! \brief This function returns the parameter specified pmic resource.
 *
 *  \param[in] comm_ptr The comm object of the pmic resource.
 *
 *  \param[in] peripheral_info The peripheral info of the pmic resource.
 */
static void pm_resource_manager_create_pmic_resource
       (pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

//__attribute__((section("rinit_code_sec_pool1")))
void pm_resource_manager_init(void)
{
  peripheral_info_type peripheral_info;
  uint32 pmic_index = 0;
  uint32 sid_index = 0;
  uint32 peripheral_index = 0;
  pm_comm_info_type *comm_ptr = NULL;

  uint8 *bitmap_ptr;
  uint8  bit_index;      /* index into 8 bits bitmap value */
  uint32 bitmap_index = 0;
  uint32  array_index; /* index into bit map array */
  boolean  bit_set = FALSE;
  uint8  slaves_count = 0;
  pm_model_type pmic_model = PMIC_IS_UNKNOWN;

  boolean arch_pre7 = pm_is_pmiclib_arch_pre7();


  memset(&peripheral_info, 0, sizeof(peripheral_info_type));

  for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    pmic_model = pm_get_pmic_model(pmic_index);

    if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
    {
      continue;
    }

    slaves_count = pm_get_num_of_sid_supported(pmic_index);

    for(sid_index = 0; sid_index < slaves_count; sid_index++)
    {
      comm_ptr = pm_comm_get_comm_info(pmic_index, sid_index);

      CORE_VERIFY_PTR(comm_ptr);

      peripheral_index = 0;

      bitmap_ptr = pm_target_information_get_specific_info(PM_PROP_PERIPH_BITMAP);

      if(bitmap_ptr == NULL)
      {
        for(peripheral_index = 0; peripheral_index < 256; peripheral_index++)
        {
            peripheral_info.base_address = peripheral_index * 0x0100;
            //read revision information here
            if(pm_target_information_read_peripheral_rev(comm_ptr, &peripheral_info) == PM_ERR_FLAG_SUCCESS)
           {
                pm_resource_manager_create_pmic_resource(comm_ptr, &peripheral_info, pmic_index);
           }
        }
      }
      else
      {
       for(array_index = 0; array_index < PM_MAX_BITMAP_ENTRIES; array_index++)
        {
          CORE_VERIFY((pmic_index + sid_index) <= PM_MAX_NUM_SLAVE_IDS);

          if(TRUE == arch_pre7)
          {
            bitmap_index = bitmap_ptr[(pmic_index * (slaves_count * PM_MAX_BITMAP_ENTRIES)) + (sid_index * PM_MAX_BITMAP_ENTRIES) + array_index];
          }
          else
          {
            bitmap_index = *(bitmap_ptr + ((pmic_index + sid_index) * PM_MAX_BITMAP_ENTRIES) + array_index);
          }

          for(bit_index = 0; bit_index < 8; bit_index++)
          {
            /*look for set bit*/
            bit_set = (bitmap_index & (0x1 << bit_index)) ? TRUE : FALSE;

            if(bit_set == TRUE)
            {
              //read revision information here
              peripheral_info.base_address = peripheral_index * 0x0100;
              if(pm_target_information_read_peripheral_rev(comm_ptr, &peripheral_info) == PM_ERR_FLAG_SUCCESS)
              {
                pm_resource_manager_create_pmic_resource(comm_ptr, &peripheral_info, pmic_index);
              }
            }
            peripheral_index++;
          } // bit_index
        } // array_index
      }      
    } // for sid index    
  } /* for pmic_index */
  // initialize app layer
  pm_app_vrm_init();
}

__attribute__((section("rinit_code_sec_pool1")))
void pm_resource_manager_create_pmic_resource(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{    
    switch((pm_hw_module_type)peripheral_info->peripheral_type)
    {
        case PM_HW_MODULE_FTS:
        case PM_HW_MODULE_HF_BUCK:
        case PM_HW_MODULE_ULT_BUCK:
            pm_smps_driver_init(comm_ptr, peripheral_info, pmic_index);
            break;
        case PM_HW_MODULE_LDO:
        case PM_HW_MODULE_ULT_LDO:
            pm_ldo_driver_init(comm_ptr, peripheral_info, pmic_index);
            break;
        case PM_HW_MODULE_BOB:
            pm_bob_driver_init(comm_ptr, peripheral_info, pmic_index);
            break;
        case PM_HW_MODULE_CLOCK:
            pm_clk_driver_init(comm_ptr, peripheral_info, pmic_index);
            break;
        case PM_HW_MODULE_MISC:
            if (peripheral_info->peripheral_subtype == PM_HW_MODULE_MISC_PSTM)
            {
                pm_pstm_driver_init(comm_ptr, peripheral_info, pmic_index);
            }
            break;
        default:
            break;
    }
}
