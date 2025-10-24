/** @file DDRTargetLibNull.c
  
  Stub functions for DDRTargetLib

  Copyright (c) 2014-2017,2020-2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/11/21   mkma    ddr_get_syndrome_regions API added
 06/24/20   ds      waipio update for null lib and hwio
 02/19/20   ck      Updated ddr_get_granule_size argument list
 05/18/17   vk      Add missing stubs
 06/20/16   kpa     Added ddr training stubs
 05/12/15   plc     Updated with sdi_exit/init api's
 09/23/14   ck      Removed ddr_restore_from_wdog_reset.  Not needed in HoneyBadger
 05/30/14   kedara  Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "ddr_drivers.h"
#include "ddr_common.h"
#include "ddr_test.h"
#include "boot_framework.h"
#include "boot_modes.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

ddr_size_partition ddr_partitions_stub = {{{0}}};
ddr_info ddr_info_stub = {{{0}}};
ddr_size_info ddr_size_info_stub = {{0},{0},{0},{0}};

/* ============================================================================
**  Function : ddr_set_params
** ============================================================================
*/
/**
*   @brief
*   This function sets the DDR driver's device table to an external device table.
*   It will also update the interleaving mode information according to the parameter
*   header that's passed in.
*   User should append ddr_device_params_header_v1 header in front of their own DDR device 
*   table and pass  a pointer points to the beginning of this header via the this API to 
*   force DDR driver to utilize the user defined parameters.
*   The user defined ddr device table must contain a minimal number of entries to 
*   match the system's ddr devices.
*   For example if a system has two ddr devices attached then the external table must 
*   define at least two entries to match those two devices.
*   However, more entries can be added to the end of table to support other ddr devices
*   with different parameters.
*
*   @param[in]  ddr_params_ptr   Pointer to the external ddr parameters. It should
*                                point to the user defined ddr device table with ddr
*                                parameters header appended in front. This pointer must
*                                points to a 4 bytes aligned address.
*                         
*
*   @return
*   TRUE if DDR device table is updated, FALSE if an error happens and this operation
*   is aborted
*
*   @dependencies
*   Must be called prior to ddr_initialize_device. 
*   This API will take no effect after ddr_initialize_device
*
*   @sa
*   None
*
*   @sa
*   None
*/
boolean ddr_set_params(void *ddr_params_ptr, uint32 ddr_params_size)
{
  return TRUE;
}

/* ============================================================================
**  Function : ddr_initialize_device
** ============================================================================
*/
/*!
*   @brief
*   This function will setup the ddr parameter in HAl and initialize the ddr
*   
*   @details
*   This function will first pass the currently used ddr device parameter
*   to the HAL. Then it will initialize the ddr as per specified speed
*   
*   @param clkspeed   -  [IN] clk speed to initialize for
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

boolean ddr_initialize_device(uint32 clk_speed, boot_mode_type boot_mode)
{
return TRUE;
}

/* ============================================================================
**  Function : ddr_get_info
** ============================================================================
*/
/*!
*   @brief
*   Returns the physical configuration of ddr on target
*
*   @details
*   This function will return the physical configuration of the ddr on target
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval ddr_size_infor contains the ddr size and base address
*
*   @sa None
*/

ddr_info ddr_get_info(void)
{
  uint8 i;
  ddr_info_stub.ddr_type = 0x7; //LP4 0x7, LP5 0x8
  ddr_info_stub.interleaved_memory = 0x1;

  /* Check to see if interleave is turned on for CS0 */
  if(ddr_info_stub.interleaved_memory & DDR_CS0)
  {
    for (i = 0; i < 4; i++)
    {
      ddr_info_stub.ddr_size.ddr_cs0[i] = 0x600;
      ddr_info_stub.ddr_size.ddr_cs0_addr[i] = 0x0;
    }
  }

  if(ddr_info_stub.interleaved_memory & DDR_CS1)
  {
    for (i = 0; i < 4; i++)
    {
      ddr_info_stub.ddr_size.ddr_cs1[i] = 0;
      ddr_info_stub.ddr_size.ddr_cs1_addr[i] = 0x0;
    }
  }
  
  return ddr_info_stub;
}

/* ============================================================================
**  Function : ddr_get_size
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr size and base address
*   
*   @details
*
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval ddr_size_infor contains the ddr size and base address
*   
*   @sa None
*/
ddr_size_info ddr_get_size(void)
{
  uint8 i;
  ddr_info ddr_physical_info = ddr_get_info();

  /* Check to see if interleave is turned on for CS0 */
  if(ddr_physical_info.interleaved_memory & DDR_CS0)
  {
    /* Interleave mode is on for CS0 , add all the sizes of CS0, assign it to interface 0 and do not populate remaining interfaces */
    for (i = 1; i < 4; i++)
    {
      ddr_physical_info.ddr_size.ddr_cs0[0] += ddr_physical_info.ddr_size.ddr_cs0[i];
      ddr_physical_info.ddr_size.ddr_cs0[i] = 0;
    }
  }

  if(ddr_physical_info.interleaved_memory & DDR_CS1)
  {
    /* Interleave mode is on for CS1 , add all the sizes of CS1, assign it to interface 0 and do not populate remaining interfaces */
    for (i = 1; i < 4; i++)
    {
      ddr_physical_info.ddr_size.ddr_cs1[0] += ddr_physical_info.ddr_size.ddr_cs1[i];
      ddr_physical_info.ddr_size.ddr_cs1[i] = 0;
    }
  }
 
  ddr_size_info_stub = ddr_physical_info.ddr_size;  
  return ddr_size_info_stub;
}

/* ============================================================================
**  Function : ddr_get_partition
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr partitions and base address
*   
*   @details
*	This API will return the number of partitions on each interface along with the 
*	base address
*   
*  @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval ddr_size_partition contains the ddr partitions and base address
*   
*   @sa None
*/
ddr_size_partition ddr_get_partition(void)
{
  uint8 i;
  /* 
    because we only support segment masking due to bank interleaving,
    we always have 8 partitions per device
  */  
  for (i = 0; i < 4; i++)
  {
    if (ddr_size_info_stub.ddr_cs0[i])
    {
      ddr_partitions_stub.ddr_cs0[i].ddr_addr = ddr_size_info_stub.ddr_cs0_addr[i];
      ddr_partitions_stub.ddr_cs0[i].num_partitions = 8;
    }
    if (ddr_size_info_stub.ddr_cs1[i])
    {
      ddr_partitions_stub.ddr_cs1[i].ddr_addr = ddr_size_info_stub.ddr_cs1_addr[i];
      ddr_partitions_stub.ddr_cs1[i].num_partitions = 8;
    }
  } 
  return ddr_partitions_stub;
}

/* =============================================================================
**  Function : ddr_params_is_training_required
** =============================================================================
*/
/**
*   @brief
*   Indicate whether DDR parameter training is required or not. Training is
*   required if and only if DDR itself (e.g. PCDDR3) requires parameter training
*   and DDR parameter partition is invalid. LPDDR3 will always require training syncronization
*   to be done between rpm and sbl
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
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
boolean ddr_params_is_training_required( void )
{
  return FALSE;
}

/* =============================================================================
**  Function : ddr_params_get_training_data
** =============================================================================
*/
/**
*   @brief
*   Get DDR parameter partition: partition base is returned, and partition size
*   is updated through pointer.
*
*   @param[out]  size  DDR parameter partition size
*
*   @return
*   DDR parameter partition base
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
void *ddr_params_get_training_data(uint32 *size)
{
  return NULL;
}

/* =============================================================================
**  Function : ddr_params_set_training_data
** =============================================================================
*/
/**
*   @brief
*   Set DDR parameter partition.
*
*   @param[in]  base  DDR parameter partition base
*   @param[in]  size  DDR parameter partition size
*
*   @retval  TRUE   Partition set successfully
*   @retval  FALSE  Partition set unsuccessfully
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
boolean ddr_params_set_training_data(void *base, uint32 size)
{
  return TRUE;
}

/* ============================================================================
**  Function : ddr_post_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @details
*   This function is called after ddr is initialized. It will take care of any
*   post initialization activities such as ddr training.
*
*   @param
*   boolean -
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
boolean ddr_post_init()
{
  return TRUE;
}

/* =============================================================================
**  Function : ddr_test_all
** =============================================================================
*/
/**
*   @brief
*   Test DDR located at each interface/CS.
*
*   This function tests DDR with the test suite specified by 'test_suit':
*
*   DDR_TEST_SUITE_EMPTY: empty test suite;
*   DDR_TEST_SUITE_ACCESS: test suite for DDR access;
*   DDR_TEST_SUITE_SELF_REFRESH: test suite for DDR self refresh;
*   DDR_TEST_SUITE_DEEP_POWER_DOWN: test suite for DDR deep power down.
*
*   In addition, for each test suite, test level is specified by 'test_level' to
*   tune how stressful test suite would be. Level 0 is the least stressful.
*
*   @param[in]  test_suite     DDR test suite
*   @param[in]  test_level     DDR test level
*   @param[in]  clk_speed      Clock speed (in KHz) DDR runs at
*
*   @retval  TRUE     Test passed for all attached DDR
*   @retval  FALSE    Test failed for some attached DDR
*
*   @dependencies
*   None
*
*   @sideeffects
*   Memory is corrupted after this function is called. Error is logged if any.
*
*   @sa
*   None
*/
boolean ddr_test_all
(
  ddr_test_suite  test_suite,
  uint32          test_level,
  uint32          clk_speed
)
{
  return TRUE;
}

/* =============================================================================
**  Function : ddr_test
** =============================================================================
*/
/**
*   @brief
*   Test DDR located at specific interface/CS.
*
*   This function tests DDR with the test suite specified by 'test_suit':
*
*   DDR_TEST_SUITE_EMPTY: empty test suite;
*   DDR_TEST_SUITE_ACCESS: test suite for DDR access;
*   DDR_TEST_SUITE_SELF_REFRESH: test suite for DDR self refresh;
*   DDR_TEST_SUITE_DEEP_POWER_DOWN: test suite for DDR deep power down.
*
*   In addition, for each test suite, test level is specified by 'test_level' to
*   tune how stressful test suite would be. Level 0 is the least stressful.
*
*   @param[in]  test_suite     DDR test suite
*   @param[in]  test_level     DDR test level
*   @param[in]  interface      Interface where DDR is located
*   @param[in]  chip_select    Chip select where DDR is located
*   @param[in]  clk_speed      Clock speed (in KHz) DDR runs at
*
*   @retval  TRUE     Test passed or no DDR attached at the interface/CS
*   @retval  FALSE    Test failed
*
*   @dependencies
*   None
*
*   @sideeffects
*   Memory is corrupted after this function is called. Error is logged if any.
*
*   @sa
*   None
*/
boolean ddr_test
(
  ddr_test_suite    test_suite,
  uint32            test_level,
  DDR_CHANNEL       interface,
  DDR_CHIPSELECT    chip_select,
  uint32            clk_speed
)
{
  return TRUE;
}

/* =============================================================================
**  Function : ddr_test_exit
** =============================================================================
*/
/**
*   @brief
*   Exit point of DDR Test Framework: an infinite loop.
*
*   @param  None
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

void ddr_test_exit( void )
{
}

/* =============================================================================
**  Function : ddr_do_phy_training
** =============================================================================
*/
/**
*   @brief
*   Indicates that PHY training needs to be done in SBL1.
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
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
boolean ddr_do_phy_training( void )
{
  return FALSE;
}

void ddr_sdi_exit(void)
{
  return;
}

void ddr_sdi_init(void)
{
  return;
}


/* =============================================================================
**  Function : ddr_remapper
** =============================================================================
*/
/**
*   @brief
*   configures ddr to be remapped to lower 32bit addresss
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   ddr initialization has already finished
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void ddr_remapper(void)
{
}

/* =============================================================================
**  Function : ddr_do_phy_training_init
** =============================================================================
*/
/**
*   @brief
*   Indicates that PHY training needs to be done in SBL1.
*
*   @param  None
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
void ddr_do_phy_training_init( void )
{
}

/* =============================================================================
**  Function : ddr_do_phy_training_restore
** =============================================================================
*/
/**
*   @brief
*   Restore training data results, if phy training is already done
*
*   @param  None
*
*   @retval  TRUE   Training required
*   @retval  FALSE  Training not required
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
boolean ddr_do_phy_training_restore( void )
{
  return TRUE;
}

uint32 ddr_get_tr_led_enable( void )
{
    return 1;
}

/* =============================================================================
**  Function : ddr_post_training
** =============================================================================
*/
/**
*   @brief
*   This function is called after ddr training. It will take care of all post
*   training activities such as computing checksum over training data.
*
*   @param  None
*
*   @retval  TRUE If one time training is enabled
*   @retval  FALSE If one time training is disabled
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
boolean ddr_post_training(void)
{
  return TRUE;
}


ddr_clock_plan ddr_clock_query(ddr_clock_query_type plan)
{
 ddr_clock_plan current_plan = {0,0};
 return current_plan;
}


void ddr_pre_clock_switch(uint32 curr_clk, uint32 new_clk)
{
}

void ddr_clock_switch(uint32 curr_clk, uint32 new_clk)
{
}

void ddr_post_clock_switch(uint32 curr_clk, uint32 new_clk)
{
}

uint32 ddr_get_max_channels(void)
{
  return 0x4;
}

void ddr_share_data_to_aop(void)
{
}

void ddr_unlock_xpu_protected_mem_region()
{
}

boolean ddr_get_shared_info_details(ddr_details_entry_ptr_type ddr_details_entry_ptr)
{
  return TRUE;
}

void ddr_post_setup()
{
}

void ddr_get_granule_size(uint32* granule_size, uint32 ddr_rank)
{
  *granule_size = 512;  
}

boolean ddr_is_shrm_load_required()
{
  return FALSE;
}

ddr_vddq_plan ddr_clock_query_vddq_plan(ddr_clock_query_type query)
{
  ddr_vddq_plan vddq_clock_plan;
  vddq_clock_plan.num_levels = 0;
  vddq_clock_plan.vddq_state = NULL;
  return vddq_clock_plan;
} /* ddr_clock_query_vddq_plan */

/* =============================================================================
**  Function : ddr_params_get_data_buffer
** =============================================================================
*/
/**
*   @brief
*   Get DDR parameter partition: buffer base is returned, and buffer size
*   is updated through pointer.
*
*   @param[out]  size  buffer size
*
*   @return
*   buffer base
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
void *ddr_params_get_data_buffer(uint32 *size, uint8 index)
{
  return NULL;
}

uint32 get_num_of_ddr_regions()
{
  return 0;
}

bl_error_boot_type get_ddr_region_param(uint8 region_index, DDR_PARAMS_ID param_id,  void *param_value, uint32 *param_size)
{
  return 0;
}

void ddr_fw_exit()
{
}

bl_error_boot_type ddr_get_mte_syndrome_regions(struct syndrome_struct *tag, uint32 *region_count)
{
  bl_error_boot_type status = BL_ERR_NONE;
	return status;
}

bl_error_boot_type ddr_get_dare_syndrome_regions(struct syndrome_struct *tag, uint32 *region_count)
{
  bl_error_boot_type status = BL_ERR_NONE;
	return status;
}

uint32 DDR_GetFreqInKhz()
{
  return 200000;
}

uint32 DDR_GetPerfLevel()
{
  return 1;
}

boolean ddr_shrm_mini_dump_init(void)
{
   return 1;
}
