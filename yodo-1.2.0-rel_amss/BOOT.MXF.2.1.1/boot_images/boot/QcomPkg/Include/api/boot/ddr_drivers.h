#ifndef DDR_DRIVERS_H
#define DDR_DRIVERS_H

#define DDR_DRIVERS_H_MAJOR  01
#define DDR_DRIVERS_H_MINOR  05
#define NUM_OF_SYNDROME_REGIONS 5
/**
  @file ddr_drivers.h
  @brief
  Function headers of DDR drivers on all targets.
*/
/*=============================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      The ddr_mainpage.dox file contains all file/group descriptions that
      are in the output PDF generated using Doxygen and Latex. To edit or
      update any of the file/group text in the PDF, edit the
      ddr_mainpage.dox file or contact Tech Pubs.

	  The above description for this file is part of the xxx group
      description in the ddr_mainpage.dox file. 
=============================================================================*/
/*=============================================================================
  Copyright (c) 2009-2022 Qualcomm Technologies, Inc.
  All rights reserved.
  Qualcomm Technolgoies, Inc. Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                                EDIT HISTORY


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/11/21   mkma    ddr_get_syndrome_regions API added
04/19/18   daison  Added ddr_get_granule_size API
09/26/17   daison  Added ddr_get_max channels to get maximum ddr channels
11/18/15   tw      added api for remapping for 32bit target
10/25/13   tw      Reworked ddr size api to support LPAE
05/06/11   tw      Added API to support extended ram partition table.
03/02/11   sd      (Tech Pubs) Edited/added Doxygen markup and comments.
11/17/10   dxiang  Doxygen grouping changes for API auto-generation
10/27/10   tw      Added API to turn on and off hw based self refresh
06/23/10   sl      Moved ddr_device_detection() to ddr_devices.h
06/11/10   sl      Doxygenated comments
05/05/10   tw      Added API for retriving ddr type
04/23/10   sl      Added pre/post XO shutdown
04/19/10   tw      Updated to support lpddr2 ram size detection
03/01/10   tw      Updated to perform ficdc calibration for all interfaces when
                   performing voltage switch
02/25/10   tw      Added API for voltage switch sequence
02/19/10   tw      Added api to convert from desired bandwidth to frequency
02/08/10   tw      updated ddr drivers to use dalsys instead of deprecated api
12/11/09   tw      update self refresh routine to pass in clock speed
06/27/09   tw      Initial revision.
=============================================================================*/

#include <ddr_common.h>
#include <ddr_aop_params.h>
#include <DDRDetails.h>
#include "boot_framework.h"
#include "boot_modes.h"
#include <boot_error_if.h>


#define DDI_OUTPUT_SECTION_START_IN_DDR SIZE_320KB
#define DDI_OUTPUT_SECTION_END_IN_DDR SIZE_1MB


/** @addtogroup ddr_apis
@{ */

typedef enum
{
	MC_CLOCK_PLAN,
	SHUB_CLOCK_PLAN,
	VDDQ_CLOCK_PLAN
}ddr_clock_query_type;


typedef struct
{
	uint8 num_levels;
	FREQ_STATE *state;
}ddr_clock_plan;

/**
 DDR Info partition API return types.
 */
typedef enum
{
  DDR_PART_SUCCESS = 0,             /**< Successful return from API */
  DDR_PART_NULL_PTR_ERR,            /**< Partition table/entry null pointer */
  DDR_PART_OUT_OF_BOUND_PTR_ERR,    /**< Partition table pointer is not in SMEM */
  DDR_PART_TABLE_EMPTY_ERR,         /**< Trying to delete entry from empty table */
  DDR_PART_TABLE_FULL_ERR,          /**< Trying to add entry to full table */
  DDR_PART_CATEGORY_NOT_EXIST_ERR,  /**< Partition doesn't belong to any memory category */
  DDR_PART_OTHER_ERR,               /**< Unknown error */
} ddr_partition_return_type;

#define MAX_MEMMAP_BLOCKS 4
#define MAX_DDR_REGIONS   4
typedef struct
{
  uint64 start_address;
  uint64 size;
}MEMMAP_DESC;

typedef struct
{
  uint8 no_of_blocks;
  MEMMAP_DESC memmap[MAX_MEMMAP_BLOCKS];
}MEMMAP_BLOCKS;

typedef struct
{
  uint32 no_of_ddr_regions;   /* No of DDR regions */
  uint64 ddr_rank0_size;     /*Size in bytes */
  uint64 ddr_rank1_size;     /*Size in bytes */
  uint64 ddr_cs0_start_addr; /* DDR rank0 start address */
  uint64 ddr_cs1_start_addr; /* DDR rank1 start address */
  uint32 highest_bank_bit;   /* highest address bit for bank address */
  DDR_REGIONS_STRUCT ddr_region[MAX_DDR_REGIONS];
}DDR_REGIONS_DATA;
  
typedef struct
{
    DDR_AOP_PARAMS *aop_params;
    vddq_state vddq_plan[MAX_NUM_CLOCK_PLAN_IDX];
    DDR_REGIONS_DATA ddr_regions_info;
    MEMMAP_BLOCKS memmap_info; 
}DDR_DRIVER_STRUCT;

typedef enum
{
REGION_START_ADDRESS = 0x0,     /* DDR Region start address uint64 */
REGION_SIZE,                    /* DDR region length in MB uint64 */
HIGHEST_BANK_BIT,               /* Highest Bank Bit uint32 */
DDR_REGION_RANK,                 /* DDR Rank0 or DDR Rank1 uint8 */
MIN_PASR_SIZE,                  /* Min PASR size uint32 */
NUM_PARTITIONS,                 /* num_partitions uint32 */
DDR_RANK0_SIZE,                 /* DDR rank0 size in MB uint32 */
DDR_RANK1_SIZE,                 /* DDR rank1 size in MB uint32 */
}DDR_PARAMS_ID;


/**
 @brief
 Holds information for DDR Info details needed in UEFI/SMEM partition.
 */

/* With the new SMEM architecture, SMEM IDs need to be defined in individual driver files */
#define DDRINFO_UEFI_SMEM_ID 0x25B	//603

typedef struct ddr_details_entry_info *ddr_details_entry_ptr_type;

typedef struct ddr_dt_entries_struct {
	uint32 ddr_log_level;
	uint32 print_severity;
}ddr_dt_entries_struct ;
	
ddr_dt_entries_struct dt_entries;

/*=============================================================================
    Function : ddr_init
=============================================================================*/

/**
  Initializes the DDR HAL with the correct DDR parameters. 

  @return
  None.

  @dependencies
  This function must be called before any DDR driver functions are called.
*/
void ddr_init(boot_mode_type boot_mode);

/*=============================================================================
    Function : get_num_of_ddr_regions
=============================================================================*/

/**
  Returns number of DDR regions. 

  @return
  Number of DDR regions.

  @dependencies
  This function must be called after DDR Init
*/
uint32 get_num_of_ddr_regions();


/*=============================================================================
    Function : get_ddr_region_param
=============================================================================*/

/**
  Sets up the DDR parameters in the HAL and initializes the DDR device.

  This function returns the DDR config parameters based on the DDR_PARAM_ID
  passed

  @param[in]     region_index    Region Index.
  @param[in]     param_id        Parameter ID.
  @param[in-out] param_value     Parameter Value.
  @param[in]     param_size      sizeof parameter in bytes
  
  @return
  bl_error_boot_type  - BL_ERR_NONE for success, error code for failure
*/
bl_error_boot_type get_ddr_region_param(uint8 region_index, DDR_PARAMS_ID param_id,  void *param_value, uint32 *param_size);

/*=============================================================================
    Function : ddr_initialize_device
=============================================================================*/

/**
  Sets up the DDR parameters in the HAL and initializes the DDR device.

  This function passes the currently used DDR parameters to the HAL and
  then initializes the DDR device per the specified clock speed.

  @param[in] clk_speed    Clock speed.

  @return
  None.

  @dependencies
  None.
*/
boolean ddr_initialize_device
(
  uint32  clk_speed,
  boot_mode_type boot_mode
);

/*=============================================================================
    Function : ddr_clock_query
=============================================================================*/

/**
  Returns MC or SHUB clock plan information to clock driver

  This function returns the number of levels in the clock plan and the clock plan
  table.

  @param[in] ddr_clock_query_type    Query type.

  @return
  struct ddr_clock_plan.

  @dependencies
  Needs to be called after HAL_DDR_Init.
*/

ddr_clock_plan ddr_clock_query
(
  ddr_clock_query_type query
);

/* ============================================================================
**  Function : ddr_clock_query_vddq_plan
** ============================================================================
*/
/*!
*   @brief
*   This function is called by clock driver to get vddq clock plan information
*
*   @details
*   Clock driver queries DDR driver to get vddq clock plan information
*
*   @param
*   ddr_clock_query_type
*
*   @par Side Effects
*   None
*
*   @retval  struct vddq_clock_plan
*
*   @sa None
*/
ddr_vddq_plan ddr_clock_query_vddq_plan(ddr_clock_query_type query);
/*=============================================================================
    Function : ddr_share_data_to_aop
=============================================================================*/

/**
  Shares Info to AOP via SMEM

  This function copies DDR info, needed by AOP during runtime, into SMEM

  @param[in] None

  @return None

  @dependencies
  Needs to be called after SMEM has been initialized.
*/
void ddr_share_data_to_aop ( void );

/**
  Shares SHRM Info to minidump via SMEM

  This function copies SHRM info into a structure to be available for mini dump thru SMEM

  @param[in] None

  @return None

  @dependencies
  Needs to be called after SMEM has been initialized.
*/
boolean ddr_shrm_mini_dump_init(void);

/*=============================================================================
    Function : ddr_pre_clock_switch
=============================================================================*/

/**
  Stalls a DDR device and loads new timing parameters into shadow registers 
  to prevent data loss during clock switching. Depending on whether the clock 
  speed is increased or decreased, this function loads the shadow registers to 
  actual registers before or after clock switching. 

  This function is called before the clock is switched.

  @param[in] curr_clk        Current clock speed.
  @param[in] new_clk         New speed to which the clock is switched.
  @param[in] interface_name  Interface for which the clock is switched.

  @return
  None.
  
  @dependencies
  The HAL_SDRAM_Pre_Clock_Switch() function must be called after this function 
  is called.

  @sa
  ddr_post_clock_switch
*/
void ddr_pre_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);

void ddrsns_pre_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);


/*=============================================================================
    Function : ddr_clock_switch
=============================================================================*/

/**
  Stalls a DDR device and loads new timing parameters into shadow registers 
  to prevent data loss during clock switching. Depending on whether the clock 
  speed is increased or decreased, this function loads the shadow registers to 
  actual registers before or after clock switching. 

  This function is called before the clock is switched.

  @param[in] curr_clk        Current clock speed.
  @param[in] new_clk         New speed to which the clock is switched.
  @param[in] interface_name  Interface for which the clock is switched.

  @return
  None.
  
  @dependencies
  The HAL_DDR_Clock_Switch() function must be called after this function 
  is called.

  @sa
  ddr_post_clock_switch
*/
void ddr_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);

void ddrsns_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);


/*=============================================================================
    Function : ddr_post_clock_switch
=============================================================================*/

/**
  Reactivates (unstalls) a DDR device. Depending on whether the clock 
  speed is increased or decreased, this function loads the shadow registers to 
  actual registers before or after clock switching.

  This function is called right after the clock is switched.

  @param[in] curr_clk        Current clock speed.
  @param[in] new_clk         New speed to which the clock is switched.
  @param[in] interface_name  Interface for which the clock is switched.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Post_Clock_Switch() function must be called before this 
  function is called.

  @sa
  ddr_pre_clock_switch
*/
void ddr_post_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);

void ddrsns_post_clock_switch
(
  uint32           curr_clk,
  uint32           new_clk
);

/*=============================================================================
    Function : ddr_pre_xo_shutdown
=============================================================================*/

/**
  Puts a DDR device into Self Refresh mode and disables the CDC and I/O 
  calibration.

  This function is called right before XO shutdown. 

  @param[in] clk_speed    Clock speed.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Pre_XO_Shutdown() function must be called after this function 
  is called.

  @sa
  ddr_post_xo_shutdown
*/
void ddr_pre_xo_shutdown
(
  uint32  clk_speed
);

/*=============================================================================
    Function : ddr_post_xo_shutdown
=============================================================================*/

/**
  Takes a DDR device out of Self Refresh mode and enables the CDC and I/O 
  calibration.

  This function is called right after XO wakeup. 

  @param[in] clk_speed    Clock speed.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Post_XO_Shutdown() function must be called before this function 
  is called.

  @sa
  ddr_pre_xo_shutdown
*/
void ddr_post_xo_shutdown
(
  uint32  clk_speed
);

/*=============================================================================
    Function : ddr_pre_voltage_switch
=============================================================================*/

/**
  Stalls a DDR device to prevent data loss during voltage switching. 

  This function is called right before voltage switching.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Pre_Voltage_Switch() function must be called after this 
  function is called.

  @sa
  ddr_post_voltage_switch
*/
void ddr_pre_voltage_switch( void );

/*=============================================================================
    Function : ddr_post_voltage_switch
=============================================================================*/

/**
  Reactivates (unstalls) a DDR device to prevent data loss after voltage 
  switching. 

  This function is called right after voltage switching.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Post_Voltage_Switch() function must be called before this 
  function is called.

  @sa
  ddr_pre_voltage_switch
*/
void ddr_post_voltage_switch( void );

/*=============================================================================
    Function : ddr_enter_self_refresh_all
=============================================================================*/

/**
  Puts one or more DDR devices into Self Refresh mode.

  When there is more than one DDR device, this function first
  reads the device status to make sure the device is in Active mode before
  putting it into Self Refresh mode.

  @param[in] clk_speed    Clock speed.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Enter_Self_Refresh_All() function must be called after this 
  function is called.

  @sa
  ddr_exit_self_refresh_all
*/
void ddr_enter_self_refresh_all
(
  uint32  clk_speed
);

/*=============================================================================
   Function : ddr_exit_self_refresh_all
=============================================================================*/

/**
  Takes one or more DDR devicess out of Self Refresh mode.

  When there is more than one DDR device, this function first reads
  the device status to make sure the device is in Self Refresh mode before
  taking it out of Self Refresh mode.

  @param[in] clk_speed    Clock speed.

  @return
  None.

  @dependencies
  The HAL_SDRAM_Exit_Self_Refresh_All() function must be called before this 
  function is called.

  @sa
  ddr_enter_self_refresh_all
*/
void ddr_exit_self_refresh_all
(
  uint32 clk_speed
);

/*=============================================================================
    Function : ddr_enter_self_refresh
=============================================================================*/

/**
  Puts into Self Refresh mode a DDR device that is currently in Active mode.

  This function first checks to see if the DDR device specified by the caller
  is available and active, and then puts it into Self Refresh mode. If the
  device is not active or not available, this function does nothing.

  @param[in] interface_name  Interface for which the DDR device is put in
                             Self Refresh mode.
  @param[in] chip_select     Chip select for which the DDR device is put in
                             Self Refresh mode.
  @param[in] clk_speed       Clock speed.

  @return
  None.

  @dependencies
  None.

  @sa
  ddr_exit_self_refresh
*/
void ddr_enter_self_refresh
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select,
  uint32            clk_speed
);

void ddrsns_enter_self_refresh
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select,
  uint32            clk_speed
);

/*=============================================================================
    Function : ddr_exit_self_refresh
=============================================================================*/

/**
  Takes a DDR device out of Self Refresh mode.

  @param[in] interface_name  Interface for which the DDR device is taken out of
                             Self Refresh mode.
  @param[in] chip_select     Chip select for which the DDR device is taken out
                             of Self Refresh mode.
  @param[in] clk_speed       Clock speed.

  @return
  None.

  @dependencies
  None.

  @sa
  ddr_enter_self_refresh
*/
void ddr_exit_self_refresh
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select,
  uint32            clk_speed
);

void ddrsns_exit_self_refresh
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select,
  uint32            clk_speed
);

/*=============================================================================
    Function : ddr_stall
=============================================================================*/

/**
  Stalls DDR devices on a specified DDR interface.
   
  Only the DDR devices in Active status are stalled. Devices with any other 
  status, such as Self Refresh, Deep Power Down or Unavailable, are ignored.
  
  @param[in] interface_name    Interface for which the DDR devices are stalled.

  @return
  None.
   
  @dependencies
  None.
   
  @sideeffects
  The DDR devices are unavailable after they have been stalled.
   
  @sa
  ddr_unstall
*/
void ddr_stall
(
  DDR_CHANNEL  interface_name
);

/*=============================================================================
    Function : ddr_unstall
=============================================================================*/

/**
  Reactivates (unstalls) all stalled DDR devices.

  DDR devices with a Stalled status are reactivated (unstalled). Devices with 
  any other status are ignored.

  @return
  None.

  @dependencies
  None.

  @sa
  ddr_stall
*/
void ddr_unstall( void );

/*=============================================================================
    Function : ddr_enter_deep_power_down
=============================================================================*/

/**
  Puts a DDR device in Deep Power Down mode.

  @param[in] interface_name  Interface for which the DDR device is put in DPD
                             mode.
  @param[in] chip_select     Chip select for which the DDR device is put in DPD
                             mode.

  @return
  None.

  @dependencies
  None.

  @sideeffects
  After a device has entered DPD mode, it is unavaiable for use. When bring a
  device out of DPD mode, a full hardware intialization must be executed.

  @sa
  ddr_exit_deep_power_down
*/
void ddr_enter_deep_power_down
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select
);

void ddrsns_enter_deep_power_down
(
  DDR_CHANNEL   interface_name,
  DDR_CHIPSELECT  chip_select
);

/*=============================================================================
    Function : ddr_exit_deep_power_down
=============================================================================*/

/**
  Takes a DDR device out of Deep Power Down mode.
   
  @param[in] interface_name  Interface for which the DDR device is taken out of
                             DPD mode.
  @param[in] chip_select     Chip select for which the DDR device is taken out
                             of DPD mode.
  @param[in] clk_speed       Clock speed to reinitialize the DDR device.

  @return
  None.

  @dependencies
  The DDR clock must be returned to an applicable initialization frequency:\n
  - LPDDR1 -- No restrictions.\n
  - LPDDR2 -- < 50 MHz.

  @sa
  ddr_enter_deep_power_down
*/
void ddr_exit_deep_power_down
(
  DDR_CHANNEL interface_name,
  DDR_CHIPSELECT chip_select,
  uint32 clk_speed
);

void ddrsns_exit_deep_power_down
(
  DDR_CHANNEL interface_name,
  DDR_CHIPSELECT chip_select,
  uint32 clk_speed
);


/*=============================================================================
    Function : ddr_enable_hw_based_self_refresh
=============================================================================*/

/**
  Enables the hardware-triggered Self Refresh feature.

  @param[in] interface_name   Interface to turn on the hardware-triggered self
                              refresh.

  @return
  None.

  @dependencies
  None.
*/
void ddr_enable_hw_based_self_refresh(DDR_CHANNEL interface_name);

/*=============================================================================
    Function : ddr_disable_hw_based_self_refresh
=============================================================================*/

/**
  Disables the hardware-triggered Self Refresh feature.

  @param[in] interface_name    Interface to turn off the hardware-triggered
                               self refresh.

  @return
  None.

  @dependencies
  None.
*/
void ddr_disable_hw_based_self_refresh(DDR_CHANNEL interface_name);

/*=============================================================================
    Function : ddr_set_hw_based_self_refresh_timer
=============================================================================*/

/**
  Updates the hardware-triggered self refresh timer.

  @param [in] interface_name      Interface to turn off the hardware-triggered
                                  self refresh.
  @param [in] self_refresh_timer  New timer value for the hardware-triggered
                                  self refresh.

  @return
  None.

  @dependencies
  None.
*/
void ddr_set_hw_based_self_refresh_timer(DDR_CHANNEL interface_name, uint16 self_refresh_timer);

/*=============================================================================
    Function : ddr_get_status
=============================================================================*/

/**
  Gets the status of a DDR device. This function returns the ddr_status 
  internal structure so the caller of this function can see the devices that 
  are available and the states the devices are in.

  @return
  Status of the devices on all available interfaces and chip selects.

  @dependencies
  None.
*/
ddr_interface_state ddr_get_status( void );

/* ============================================================================
**  Function : ddr_update_info
** ============================================================================
*/
/*!
*   @brief
*   update the internal ddr info variable with the latest detected settings
*
*   @details
*   update the internal ddr info variable with the latest detected settings
*
*   @param  None.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval
*   None
*
*   @sa None
*/

void ddr_update_info(void);

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

ddr_info ddr_get_info(void);

/* ============================================================================
**  Function : ddr_update_size
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

void ddr_update_size(void);

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

ddr_size_info ddr_get_size(void);

ddr_sns_size_info ddr_sns_get_size(void);
/* ============================================================================
**  Function : ddr_get_partition
** ============================================================================
*/
/*!
*   @brief
*   Returns the ddr partitions and base address
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
*   @retval ddr_size_partitioning contains the ddr partitions and base address
*   
*   @sa None
*/

ddr_size_partition ddr_get_partition(void);
/* ============================================================================
**  Function : ddr_fw_exit
** ============================================================================
*/
/*!
*   @brief
*   Function to call HAL_DDR_FW_Exit, This is the last function in DDRSS sequence that needs to be called by SW. Prior to this function there shouldn't be any access to DDR.
*
*   @details
*   call HAL_DDR_FW_Exit
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
void ddr_fw_exit();

/**
*   @brief
*   return the LCP(MTE) tag area start and size .. NOTE : MTE Tag area has to be a contiguous chunk of memory
*
*   @param  syndrome_start_addr[out]  - start address 
*   @param  syndrome_size[out]        - cumulative size of all tag regions (contiguous)
*   @param  region_count[out]         - if MTE is not enabled, then region_count will be zero, otherwise non-zero.
*
*   @retval  BL_ERR_NONE   if MTE is enabled, error otherwise
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
typedef struct syndrome_struct
{
	uint64 start_addr;  //syndrome region start address
	uint64 size;        //syndrom region size
} syndrome_struct;

bl_error_boot_type ddr_get_mte_syndrome_regions(struct syndrome_struct *tag, uint32 *region_count);


/* ============================================================================
**  Function : ddr_get_tr_led_enable
** ============================================================================
*/
/**
*   @brief
*   checks the device tree setting to enable/disable the green led during DDR training
*   this flag if set to '1' will blink the green LED when DDR training is happening
*
*   @param  none
*
*   @retval Returns the device tree setting to enable/disable LED light during DDR training.
*
*   @dependencies
*   None
*
*   @sideeffects
*   none
*
*   @sa
*   None
*/
uint32 ddr_get_tr_led_enable( void );

/**
*   @brief
*   return the LCP(DARE) tag area start and size .. NOTE : DARE Tag area has to be a contiguous chunk of memory
*
*   @param  syndrome_start_addr[out]  - start address 
*   @param  syndrome_size[out]        - cumulative size of all tag regions (contiguous)
*   @param  region_count[out]         - if DARE is not enabled, then region_count will be zero, otherwise non-zero.
*
*   @retval  BL_ERR_NONE   if DARE is enabled, error otherwise
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
bl_error_boot_type ddr_get_dare_syndrome_regions(struct syndrome_struct *tag, uint32 *region_count);

/* ============================================================================
**  Function : ddr_get_dare_region
** ============================================================================
*/
/**
*   @brief
*   xbl_sc needs LCP DARE regions based on region ID
*
*   @param  dare_region[out] - dare_regions_struct  
*   @param  region_id[in]    - based on region id, return the syndrome struct
*
*   @retval  BL_ERR_NONE   if DARE is enabled, error otherwise
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
typedef struct dare_regions_struct
{
	uint64 start_addr;  //syndrome region start address
	uint64 end_addr;        //syndrom region size
	uint64 metadata;
	uint32 metadata_size;
} dare_regions_struct;

bl_error_boot_type ddr_get_dare_region(struct dare_regions_struct *dare_region, DARE_REGION_ID region_id);

/* ============================================================================
**  Function : ddr_get_dare_regions
** ============================================================================
*/
/**
*   @brief
*   xbl_sc needs LCP DARE regions 
*
*   @param  dare_regions[out]    - dare_regions_struct  
*   @param  no_of_regions[out]   - number of configured DARE regions 
*
*   @retval  BL_ERR_NONE   if DARE is configured correctly, error otherwise
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

bl_error_boot_type ddr_get_dare_regions(struct dare_regions_struct *dare_regions, uint32 *no_of_regions);

/* ============================================================================
**  Function : ddr_populate_lcp_dare_regions_cfg
** ============================================================================
*/
/**
*   @brief
*   program the LCP(DARE) areas 
*
*   @param  lcp_region_cfg[in]  - structure 
*   @param  no_of_regions[in]   - number of lcp regions to be configured
*
*   @retval  BL_ERR_NONE   if DARE is configured correctly, any other value otherwise
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
bl_error_boot_type ddr_populate_lcp_dare_regions_cfg(LCP_REGION_CONFIG_STRUCT *lcp_region_cfg, uint8 no_of_regions);


/* ============================================================================
**  Function : ddr_get_frequency
** ============================================================================
*/
/**
*   @brief
*   Returns the corresponding frequency to the bandwidth desired.
*
*   This function takes the given bandwidth and converts it to the appropriate
*   frequency in terms of KHz 

  @param[in] bandwidth    Bandwidth desired in megabits.

  @return
  Corresponding frequency in kHz.

  @dependencies
  None.
*/
uint32 ddr_get_frequency
(
  uint32 bandwidth
);

/*=============================================================================
    Function : ddr_get_ddr_type
=============================================================================*/

/**
  Gets the DDR device type. This function reads the MSM&reg;&nbsp; hardware ID 
  to determine the type of DDR device.

  @return
  Type of DDR device.

  @dependencies
  None.
*/
DDR_TYPE ddr_get_ddr_type( void );

/*=============================================================================
    Function : ddr_get_temperature_status
=============================================================================*/

/**
  Gets the temperature status.
   
  This function reads the MR4 register or SRR register depending on the DDR
  type and returns the temperature status.

  @return 
  Temperature status, as specified in JEDEC.

  @dependencies
  None.
*/
uint8 ddr_get_temperature_status(void);

/* =============================================================================
**  Function : ddr_configure_lpae
** =============================================================================
*/
/**
*   @brief
*   configures ddr for LPAE by statically splitting the memory in half.
*
*   @param high_mem_enabled     -  [IN] partition guid for high mem is enabled
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
void ddr_configure_lpae(boolean high_mem_enabled);

/* ============================================================================
**  Function : ddr_remapper
** ============================================================================
*/
/*!
*   @brief
*   Reconfigures ddr to a different memory map than the physical address
*   
*   @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval void
*   
*   @sa None
*/
void ddr_remapper(void);

/* ============================================================================
**  Function : ddr_remap_to_lower_32bit
** ============================================================================
*/
/*!
*   @brief
*   Reconfigures ddr to a different memory map than the physical address
*   
*   @param  None
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval void
*   
*   @sa None
*/
void ddr_remap_to_lower_32bit(void);

/* =============================================================================
**  Function : ddr_check_remapping
** =============================================================================
*/
/**
*   @brief
*   check remapping status to restore in download mode to the same configuration
*   as before warm reset
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   ddrsns structure is either retained or wiped out.
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_check_remapping(void);

/* ============================================================================
**  Function : ddr_get_extended_cdt_params
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters.
*
*   @param[in]  interface_name  Interface to get DDR device parameters for
*
*   @return
*   DDR device parameters
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
void *ddr_get_extended_cdt_params(void);

/* =============================================================================
**  Function : ddr_get_shared_info_details
** =============================================================================
*/
/**
*   @brief
*   Get the ddr details from detected ddr device params
*
*   @param
*   ddr_det_entry_ptr_type
*
*   @return
*   status
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


boolean ddr_get_shared_info_details(ddr_details_entry_ptr_type ddr_details_entry_ptr);

/* ============================================================================
**  Function : ddr_get_max_channels
** ============================================================================
*/
/**
*   @brief
*   Returns the no of DDR channels.
*
*   @param 
*
*   @return
*   returns value of data requested
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   ddr_get_max_channels
*/

uint32 ddr_get_max_channels();

/*===========================================================================

**  Function :  ddr_unlock_xpu_protected_mem_region

** ==========================================================================
*/
/*!
* 
* @brief
*    Function unlock the DDR region locked(XPU protected) by XBL_SEC 
* 
* @par Dependencies
*   None
*   
* @retval. 
*    None
* @par Side Effects
*   None
*/


void ddr_unlock_xpu_protected_mem_region();

/*===========================================================================

**  Function :  ddr_post_setup

** ==========================================================================
*/
/*!
* 
* @brief
*    Function which gets executed after DDR setup operations are complete
* 
* @par Dependencies
*   None
*   
* @retval. 
*    None
* @par Side Effects
*   None
*/

void ddr_post_setup();

/*===========================================================================

**  Function :  ddr_get_granule_size

** ==========================================================================
*/
/*!
* 
* @brief
*    Function which returns the granule size
* 
* @par Dependencies
*   None
*   
* @retval. 
*    None
* @par Side Effects
*   None
*/

void ddr_get_granule_size(uint32* granule_size, uint32 ddr_rank);


/*===========================================================================

**  Function :  ddr_unlock_xpu_protected_mem_region

** ==========================================================================
*/
/*!
* 
* @brief
*    Function unlock the DDR region locked(XPU protected) by XBL_SEC 
* 
* @par Dependencies
*   None
*   
* @retval. 
*    None
* @par Side Effects
*   None
*/


void ddr_unlock_xpu_protected_mem_region();

/* ============================================================================
**
**  get_ddr_temperature
**
**  Description:
**    Get the DDR temperature.
**
**  Parameters:
**    None
**
**  Return:
**    TRUE  - Temperature retrieved successfully
**    FALSE - Temperature API failed to retrieve temperature
**
**  Dependencies:
**    None
**
** ========================================================================= */
boolean get_ddr_temperature(uint32 *tempDegC);


/* ============================================================================
**
**  get_clk_period_regaddr
**
**  Description:
**    Get the MCCC clock period register.
**
**  Parameters:
**    None
**
**  Return:
**    clk_period_regaddr
**
**  Dependencies:
**    None
**
** ========================================================================= */
uint32* get_clk_period_regaddr();

/* =============================================================================
**  Function : get_ssr_cookie_addr
** =============================================================================
*/
/**
*   @brief
*   Get the SSR cookie addr
*
*   @param void
*
*   @retval  void
*
*   @dependencies
*   SSR cookie address
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32* get_ssr_cookie_addr();

/* =============================================================================
**  Function : copy_ddrinfo_to_ocimem
** =============================================================================
*/
/**
*   @brief
*   Copy DDR info to OCIMEM
*
*   @param void
*
*   @retval  void
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
void copy_ddrinfo_to_ocimem(void);

/* =============================================================================
**  Function : copy_ddr_abortinfo_to_ocimem
** =============================================================================
*/
/**
*   @brief
*   Copy DDR abort info to OCIMEM
*
*   @param void
*
*   @retval  void
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
void copy_ddr_abortinfo_to_ocimem(void);

/** @} */ /* end_addtogroup ddr_apis */

#endif /* DDR_DRIVERS_H */
