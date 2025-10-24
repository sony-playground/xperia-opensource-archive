/*===========================================================================

                    BOOT DDR IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external ddr drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who      what, where, why
--------   ---      ----------------------------------------------------------
01/22/21   rhy      Enabled One time training
07/22/20   dai      Added get_ddr_region_param API 
05/10/20   ds       move to edk2 arm mmu/cache lib
04/30/20   ck       Changed logic to size_in_bytes from size_in_kbytes
08/06/19   ep       Initial Creation.
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddr_common_params.h"
#include "ddr_test.h"
#include "boot_error_if.h"
#include "boot_ddr_if.h"
#include <Library/ArmMmuLib.h>
#include <ArmMmuLibEfiAttributesMap.h>

extern boolean ddr_post_init(void);

/* Flag for Dumping DDR Training to Host */
static boolean ddr_training_dump_allowed = FALSE;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/* ============================================================================
**  Function : boot_ddr_set_ddr_dump_allowed
** ============================================================================
*/
/*!
*   @brief
*   Function to share ddr related info to AOP
*
*   @details
*   Shares DDR Info required during runtime to AOP via SMEM
*   SMEM needs to be initialized before calling this function
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
void boot_ddr_set_ddr_dump_allowed(boolean flag)
{
    ddr_training_dump_allowed = flag;
}

/* ============================================================================
**  Function : boot_ddr_get_ddr_dump_allowed
** ============================================================================
*/
/*!
*   @brief
*   Function to share ddr related info to AOP
*
*   @details
*   Shares DDR Info required during runtime to AOP via SMEM
*   SMEM needs to be initialized before calling this function
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
boolean boot_ddr_get_ddr_dump_allowed()
{
    return ddr_training_dump_allowed;
}

/* ============================================================================
**  Function : boot_ddr_share_data_to_aop
** ============================================================================
*/
/*!
*   @brief
*   Function to share ddr related info to AOP
*
*   @details
*   Shares DDR Info required during runtime to AOP via SMEM
*   SMEM needs to be initialized before calling this function
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/
bl_error_boot_type boot_ddr_share_data_to_aop(boot_handle config_context_handle)
{
 ddr_share_data_to_aop(); 

 return BL_ERR_NONE;
}

/* ============================================================================
**  Function : boot_shrm_minidump_init
** ============================================================================
*/
/*!
*   @brief
*   Function to initiate SHRM mini dump
*
*   @details
*   initiate SHRM mini dump
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval if error, returns error code else BL_ERR_NONE
*
*   @sa None
*/
bl_error_boot_type boot_shrm_minidump_init(void)
{
  bl_error_boot_type status;
  status = ddr_shrm_mini_dump_init(); 

  if(status != TRUE)
      return GET_ERROR_CODE(BL_ERROR_GROUP_DDR , BL_ERR_MD_REGISTER_FAIL);
 return BL_ERR_NONE;
}

/* =============================================================================
**  Function : boot_ddr_test
** =============================================================================
*/
/**
*   @brief
*   This function invokes DDR Test Framework.
*
*   @param[in]  clk_speed  Clock speed (in KHz) DDR runs at
*
*   @retval  None
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void boot_ddr_test(uint32 clk_speed)
{
  /* These variables are modified by Trace32 */
  static volatile ddr_test_suite    test_suite = DDR_TEST_SUITE_EMPTY;
  static volatile uint32            test_level = 0;
  static volatile boolean           is_dcache_on = FALSE;
  static volatile boolean           is_test_all = TRUE;
  static volatile DDR_CHANNEL       interface = DDR_CH0;
  static volatile DDR_CHIPSELECT    chip_select = DDR_CS0;
  static volatile uint32            test_iterations = 1;

  if (test_suite != DDR_TEST_SUITE_EMPTY)
  {
    if (!is_dcache_on)
    {
      ddr_size_info ddr_size = ddr_get_size();

      uintnt base = (ddr_size.ddr_cs0_addr[0] < ddr_size.ddr_cs1_addr[0]) ?
                    ddr_size.ddr_cs0_addr[0] : ddr_size.ddr_cs1_addr[0];

      uint8 i;
      uintnt size = 0;
    uint32 max_ddr_channels = 0;
    max_ddr_channels = ddr_get_max_channels();
 
      for (i = 0; i < max_ddr_channels; i++)
      {
        size += ddr_size.ddr_cs0[i] + ddr_size.ddr_cs1[i];
      }
      
      size = size << 20;

      size -= (SCL_SBL1_DDR_DATA_BASE + SCL_SBL1_DDR_DATA_SIZE) - base;

      base = (SCL_SBL1_DDR_DATA_BASE + SCL_SBL1_DDR_DATA_SIZE);
      
      ArmSetMemoryAttributes(base, size, EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN);
    }

    /*Unlock the DDR region locked(XPU protected) by XBL_SEC*/
  ddr_unlock_xpu_protected_mem_region();
    if (is_test_all)
    {
      while (test_iterations--)
      {
        if (!ddr_test_all(test_suite, test_level, clk_speed))
        {
          break;
        }
      }
    }
    else
    {
      while (test_iterations--)
      {
        if (!ddr_test(test_suite, test_level, interface, chip_select, clk_speed))
        {
          break;
        }
      }
    }
    ddr_test_exit();
  }

} /* boot_ddr_test */


boot_ddr_if_type ddr_if = {
    ddr_set_params,
    ddr_initialize_device,
    ddr_get_size,
    ddr_get_partition,
    ddr_params_is_training_required,
    ddr_params_get_training_data,
    ddr_params_set_training_data,
    ddr_post_init,
    ddr_get_info,
    boot_ddr_share_data_to_aop,
    boot_ddr_test,
    ddr_debug,
    ddr_remapper,
    ddr_get_shared_info_details,
    ddr_get_max_channels,
    ddr_post_setup,
    ddr_get_granule_size,
    ddr_do_phy_training_init,
    ddr_do_phy_training_restore,
    ddr_post_training,
    ddr_is_shrm_load_required,
    ddr_params_get_data_buffer,
    get_num_of_ddr_regions,
    get_ddr_region_param,
    boot_ddr_set_ddr_dump_allowed,
    boot_ddr_get_ddr_dump_allowed,
    ddr_fw_exit,
    ddr_get_mte_syndrome_regions,
    boot_shrm_minidump_init,
    ddr_get_dare_syndrome_regions,
    ddr_get_tr_led_enable  
};
