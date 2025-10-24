/*
===========================================================================

FILE:         ddr_sns_drivers.c

DESCRIPTION:
  This is the ddr drivers implementation for Qualcomm memory controller.

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
06/27/22   sym     remove fdt_get_blob_handle api
06/21/22   sairaj  enabled ddr initialization error support
12/08/20   rama    Ported error handler changes in get_ddr_region_param
07/21/20   rama    Added SecLib API for unlocking DDR XPU region
04/19/18   daison  Added ddr_get_granule_size API
09/18/17   qbz     Fix ddr_status update error in self-refresh APIs
07/18/14   tw      added support for passing highest bank bit information to ram
                   partition table
05/28/14   tw      Renamed lp4_share_data to ddrsns_share_data for code clarity
03/12/14   sr      Initial version

===========================================================================
*/


/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddr_internal.h"
#include "ddr_sync.h"
#include "ddr_params.h"
#include "HAL_SNS_DDR.h"
#include "ddr_hwio.h"
//#include "ddrss_init_sdi.h"  //DS_Enable
#include "ddr_target.h"
#include "boot_modes.h"
#include "ddr_sdi_log.h"
#include "core_sw_interface.h"
#include "ddr_fw_interface.h"
#include <boot_seclib_if.h>
#include "DTBExtnLib.h"
/*==============================================================================
                                  DATA
==============================================================================*/
ddr_interface_state ddr_status;

extern DDR_SDI_LOGS *ddr_sdi_logs_ptr;

/* internal variable to keep track of device specific bus width, 32bit vs 64 bit */
uint32 ddr_bus_width;

/*Indicates ddr initialization is done or not, FALSE by default*/
boolean ddr_init_done = FALSE;

/* Chip selects for selected ranks by ddr_enter/exit_self_refresh_all() */
static DDR_CHIPSELECT ddr_csel[DDR_MAX_NUM_CH_TEST];

ddr_info ddr_physical_size = {{{0}}};
ddr_size_info ddr_system_size = {{0}};

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

/* ============================================================================
**  Function : ddr_devicetree_helper_uint32
** ============================================================================
*/
 /*!
*   @brief
*   This is a helper function for extracting device tree entries
*
*   @details
*   This is a helper function for extracting device tree entries , we do call XBL DT APIs
*   inside this function.
*
*   @param
*   None
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

void ddr_devicetree_helper_uint32(const char *entry_name, char *dt_name, uint32 *retval)
{
	fdt_node_handle node;
	void *blob = NULL;
	uint32 entry_val; // Temp variable used to get the value from DT
	int ret_val;

	fdt_get_node_handle(&node, blob, dt_name);
	ret_val = fdt_get_boolean_prop(&node, entry_name, &entry_val);

	if(ret_val == 0){
		*retval = entry_val;
	}
	else{
		HAL_EXT_CORE_SW_DDR_printf (DDR_ERROR,  "ddr_devicetree_helper_uint32:  Error while reading DT entry, return value is %d", ret_val);
	}
}


/* ============================================================================
**  Function : ddr_extract_common_dt_entries
** ============================================================================
*/
/*!
*   @brief
*   This function extract the ddr common DT entries
*
*   @details
*   This function extract the ddr common DT entries
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

void ddr_extract_common_dt_entries(void){

	uint32 temp_ddr_log, temp_print_severity;

	ddr_devicetree_helper_uint32("ddr_log_level_dt", "/soc/ddr_common_dt", &temp_ddr_log);
	ddr_devicetree_helper_uint32("print_severity_dt", "/soc/ddr_common_dt", &temp_print_severity);

	dt_entries.ddr_log_level = temp_ddr_log;
	dt_entries.print_severity = temp_print_severity;
}

/* ============================================================================
**  Function : ddr_init
** ============================================================================
*/
/*!
*   @brief
*   Initialize ddr HAL with the correct ddr parameters
*   This must be done before calling any of the drivers functions
*
*   @details
*   Initialize ddr HAL with the correct ddr parameters
*   This must be done before calling any of the drivers functions
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

void ddr_init(boot_mode_type boot_mode)
{
	DDR_SYNC_INIT();

	ddr_extract_common_dt_entries();
	/* Initialize target specific functions */
	ddr_target_init(boot_mode);
    /* update DSF shared structure with value read from DT */
	ddr_shared_data->print_severity = dt_entries.print_severity;
} /* ddr_init */

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

boolean ddr_initialize_device(uint32 clk_speed, boot_mode_type boot_mode) //boolean dload_mode)
{
  struct detected_ddr_device_params *ddr_detected_param_interface[DDR_MAX_NUM_CH_TEST];
  uint8 i;

  if(!ddr_init_done)
  {
    /* Pass the ddr parameters to HAL */
    ddr_init(boot_mode);

    /* Update the ddr clock speed variable to the initialization clock */
    ddr_status.clk_speed = clk_speed;

    /* To-do: What are the possible cases for channel and chip select
    Here are the possible ones but need to sync up with DSF to see how they're handling them

    1. Channel: CH0, Rank: CS0
    2. Channel: CH0, Rank: CS_BOTH
    3. Channel: CH0 and CH1, Rank: CS0
    4. Channel: CH0 and CH1, Rank: CS_BOTH
    5. Channel: CH0, CH1 and CH2, Rank: CS0
    6. Channel: CH0, CH1 and CH2, Rank: CS_BOTH
    7. Channel: CH0, CH1, CH2 and CH3, Rank: CS0
    8. Channel: CH0, CH1, CH2 and CH3, Rank: CS_BOTH */

    /* If download mode is not set, i.e. cold boot path or if we have entered pass 3, then we need to fully initialize the DDR driver */
    //if ((!dload_mode) || (ddr_sdi_logs_ptr->pass3_cookie->p_cookie_value == DDR_WENT_INTO_PASS3))
    if (boot_mode != BOOT_MODE_RAMDUMP)//(!dload_mode)
    {
      HAL_CORE_SW_DCB_Init(ddr_shared_data);
      HAL_CORE_SW_DCB_Set_DDR_AOP_PARAMS(ddr_shared_data);
      ddr_get_shub_shrm_freq();
      HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "DDR_INIT with shrm.elf");
      /* In Device Programmer Path - PcdBuildType is 0x2 , use DDR_FW_Init_APPs for DDR Init without shrm dependency*/
      if (boot_mode == BOOT_MODE_DEVICEPROGRAMMER)//(PcdGet32 (PcdBuildType) == 2)
      {
        fptr_HAL_DDR_FW_Init = DDR_FW_Init_APPs;
        HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "DDR_FW_Init_APPs,Overriding DDR init func ptr API to not use shrm.elf ");
      }
      HAL_DDR_FW_Init();

      /* If DDR abort is observed, copy DDR abort info to OCIMEM and return */
      if(ddr_shared_data->ddr_abort_info.reason != UNCATEGORIZED)  /* DDR abort is observed */
      {
        copy_ddr_abortinfo_to_ocimem();
        HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "ddr_init = %d DDR ABORT",ddr_init_done);
        return ddr_init_done; /* return since DDR abort is observed */
      }

      ddr_init_done = TRUE;
      HAL_EXT_CORE_SW_DDR_printf (DDR_BOOTLOG, "ddr_init = %d cold boot",ddr_init_done);
    }
    else
    {
      ddr_init_done = ddr_target_sdi_pass_init(clk_speed);
    }

    /* Get DDR device parameters after detection during initialization and update the DDR status */
    for ( i = 0; i < ddr_get_max_channels(); i++)
    {
      ddr_detected_param_interface[i] = (ddr_get_detected_params(1<<i));

      //To do: Add a comment for num_rows 0 and 1
      ddr_status.ddr_cs0[i] = (ddr_detected_param_interface[i]->num_rows[0] != 0) ? DDR_ACTIVE : DDR_UNAVAILABLE;
      ddr_status.ddr_cs1[i] = (ddr_detected_param_interface[i]->num_rows[1] != 0) ? DDR_ACTIVE : DDR_UNAVAILABLE;
    }

    ddr_update_info();
    ddr_update_size();

  }
  return ddr_init_done;
} /* ddr_initialize_device */

/* =============================================================================
**  Function : ddr_enter_self_refresh_all
** =============================================================================
*/
/**
*   @brief
*   Put DDR into self refresh mode for all active ranks.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
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
void ddr_enter_self_refresh_all(uint32 clk_speed)
{
  uint8 i;
  //DDR_CHANNEL interface_name;

  DDR_SYNC_LOCK();

  /* Update DDR status and enter self refresh for selected ranks and channels */
  for (i = 0; i < ddr_get_max_channels(); i++)
  {
    //interface_name = (1 << i);
    ddr_csel[i] = DDR_CS_NONE;

    if (ddr_status.ddr_cs0[i] == DDR_ACTIVE)
    {
      ddr_status.ddr_cs0[i] = DDR_SELF_REFRESH;
      ddr_csel[i] |= DDR_CS0;
    }
    if (ddr_status.ddr_cs1[i] == DDR_ACTIVE)
    {
      ddr_status.ddr_cs1[i] = DDR_SELF_REFRESH;
      ddr_csel[i] |= DDR_CS1;
    }
    /* Enter self refresh for selected ranks */
    if (ddr_csel[i] != DDR_CS_NONE)
    {
      //HAL_DDR_Enter_Self_Refresh(interface_name,  ddr_csel[i]);
    }
  }

  DDR_SYNC_UNLOCK();

} /* ddr_enter_self_refresh_all */

/* =============================================================================
**  Function : ddr_exit_self_refresh_all
** =============================================================================
*/
/**
*   @brief
*   Take DDR out of self refresh mode for ranks that are active before
*   ddr_enter_self_refresh_all() is called.
*
*   @param[in]  clk_speed  Current clock speed (in KHz)
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
void ddr_exit_self_refresh_all(uint32 clk_speed)
{
  uint8 i;
  //DDR_CHANNEL interface_name;

  DDR_SYNC_LOCK();

  /* Update DDR status and exit self refresh for selected ranks and channels */
  for (i = 0; i < ddr_get_max_channels(); i++)
  {
    //interface_name = (1 << i);
    ddr_csel[i] = DDR_CS_NONE;

    if (ddr_status.ddr_cs0[i] == DDR_ACTIVE)
    {
      ddr_status.ddr_cs0[i] = DDR_SELF_REFRESH;
       ddr_csel[i] |= DDR_CS0;
    }
    if (ddr_status.ddr_cs1[i] == DDR_ACTIVE)
    {
      ddr_status.ddr_cs1[i] = DDR_SELF_REFRESH;
       ddr_csel[i] |= DDR_CS1;
    }
    /* Enter self refresh for selected ranks */
    if ( ddr_csel[i] != DDR_CS_NONE)
    {
      //HAL_DDR_Enter_Self_Refresh(interface_name,  ddr_csel[i]);
    }
  }

  DDR_SYNC_UNLOCK();

} /* ddr_exit_self_refresh_all */

/* ============================================================================
**  Function : ddr_enter_self_refresh
** ============================================================================
*/
/*!
*   @brief
*   This function will put the a particular ddr into self refresh mode, provided that it is currently active.
*
*   @details
*   This function will first check to see if the ddr specified by the caller is available and active, then put it into self
*   refresh mode. If it is not active or not available, simply do nothing.
*
*   @param interface_name   - [IN] The interface to put ddr into self refresh
*   @param chip_select      -     [IN] The chip select to put ddr into self refresh
*   @param clkspeed      -        [IN] The current clock speed

*
*   @par Dependencies
*   This code has to reside in IRAM
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
void ddr_enter_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_enter_self_refresh(interface_name,chip_select,clk_speed);
}

void ddrsns_enter_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;
  uint8 i = 0;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* update ddr status */
  for(i = 0; i < ddr_get_max_channels(); i++) {
    if(0 == (interface_name & (0x1<<i)) ) continue;

    /* Mark device status as self refresh for selected channel and rank */
    if ( (chip_select & DDR_CS0) && (ddr_status.ddr_cs0[i] == DDR_ACTIVE) ) {
      csel |= DDR_CS0;
      ddr_status.ddr_cs0[i] = DDR_SELF_REFRESH;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.ddr_cs1[i] == DDR_ACTIVE) ) {
      csel |= DDR_CS1;
      ddr_status.ddr_cs1[i] = DDR_SELF_REFRESH;
    }
  }

  if ( interface_name!=DDR_CH_NONE && csel!=DDR_CS_NONE )
    //HAL_DDR_Enter_Self_Refresh(interface_name, csel);

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();

} /* ddr_enter_self_refresh */

/* ============================================================================
**  Function : ddr_exit_self_refresh
** ============================================================================
*/
/*!
*   @brief
*   This function will put the particular ddr into active mode, provided that it is currently in self refresh.
*
*   @details
*   This function will first check to see if the ddr specified by the caller is available and in self refresh, then put it into active
*   mode. If it is not in self refresh, simply do nothing.
*
*   @param interface_name   -  [IN] The interface to put ddr into self refresh
*   @param chip_select      -  [IN] The chip select to put ddr into self refresh
*   @param clkspeed      -        [IN] The current clock speed
*
*   @par Dependencies
*   This code has to reside in IRAM
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_exit_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_exit_self_refresh(interface_name,chip_select,clk_speed);
}

void ddrsns_exit_self_refresh(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;
  uint8 i = 0;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* update ddr status */
  for(i = 0; i < ddr_get_max_channels(); i++) {
    if(0 == (interface_name & (0x1<<i)) ) continue;

    /* Mark device status as self refresh for selected channel and rank */
    if ( (chip_select & DDR_CS0) && (ddr_status.ddr_cs0[i] == DDR_SELF_REFRESH) ) {
      csel |= DDR_CS0;
      ddr_status.ddr_cs0[i] = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.ddr_cs1[i] == DDR_SELF_REFRESH) ) {
      csel |= DDR_CS1;
      ddr_status.ddr_cs1[i] = DDR_ACTIVE;
    }
  }

  if ( interface_name!=DDR_CH_NONE && csel!=DDR_CS_NONE )
    //HAL_DDR_Exit_Self_Refresh(interface_name, csel);

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();
} /* ddr_exit_self_refresh */

/* ============================================================================
**  Function : ddr_enter_deep_power_down
** ============================================================================
*/
/*!
*   @brief
*   This function will put ddr into deep power down mode.
*
*   @details
*   This function will put ddr into deep power down mode.
*
*   @param interface_name   -  [IN] The interface to put ddr into DPD
*   @param chip_select      -  [IN] The chip select to put ddr into DPD
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   After a device has entered Deep Power Down, it will be unavailable for use.
*   When it is necessary to bring device out of DPD, a full HW initialization must be
*   executed.
*
*   @retval  None
*
*   @sa None
*/
void ddr_enter_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select)
{
   ddrsns_enter_deep_power_down(interface_name, chip_select);
}

void ddrsns_enter_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;
  uint8 i = 0;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* update ddr status */
  for(i = 0; i < ddr_get_max_channels(); i++) {
    if(0 == (interface_name & (0x1<<i)) ) continue;

    /* Mark device status as self refresh for selected channel and rank */
    if ( (chip_select & DDR_CS0) && (ddr_status.ddr_cs0[i] == DDR_ACTIVE) ) {
      csel |= DDR_CS0;
      ddr_status.ddr_cs0[i] = DDR_DPD;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.ddr_cs1[i] == DDR_ACTIVE) ) {
      csel |= DDR_CS1;
      ddr_status.ddr_cs1[i] = DDR_DPD;
    }
  }

  if ( interface_name!=DDR_CH_NONE && csel!=DDR_CS_NONE )
    DDR_SYNC_LOCK();
    //HAL_DDR_Enter_Deep_Power_Down(interface_name, csel);

} /* ddr_enter_deep_power_down */

/* ============================================================================
**  Function : ddr_exit_deep_power_down
** ============================================================================
*/
/*!
*   @brief
*   This function will take the ddr out of deep power down mode.
*
*   @details
*   This function will take the ddr out of deep power down mode.
*
*   @param interface_name  -  [IN] The interface to take ddr out of DPD
*   @param chip_select         -  [IN] The chip select to take ddr out of DPD
*   @param clk_speed          -  [IN] The ddr speed to reinitialize for
*
*   @par Dependencies
*   ddr clock must be returned to an applicable initialization frequency
*   LPDDR1 - no restrictions
*   LPDDR2 - < 50Mhz
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
void ddr_exit_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
   ddrsns_exit_deep_power_down(interface_name,chip_select,clk_speed);
}

void ddrsns_exit_deep_power_down(DDR_CHANNEL interface_name, DDR_CHIPSELECT chip_select, uint32 clk_speed)
{
  DDR_CHIPSELECT csel = DDR_CS_NONE;
  uint8 i = 0;

  /*
    Issue a lock to prevent anyone else from updating ddr
    status while we are working here
  */
  DDR_SYNC_LOCK();

  /* update ddr status */
  for(i = 0; i < ddr_get_max_channels(); i++) {
    if(0 == (interface_name & (0x1<<i)) ) continue;

    /* Mark device status as self refresh for selected channel and rank */
    if ( (chip_select & DDR_CS0) && (ddr_status.ddr_cs0[i] == DDR_DPD) ) {
      csel |= DDR_CS0;
      ddr_status.ddr_cs0[i] = DDR_ACTIVE;
    }
    if ( (chip_select & DDR_CS1) && (ddr_status.ddr_cs1[i] == DDR_DPD) ) {
      csel |= DDR_CS1;
      ddr_status.ddr_cs1[i] = DDR_ACTIVE;
    }
  }

  if ( interface_name!=DDR_CH_NONE && csel!=DDR_CS_NONE )
    //HAL_DDR_Exit_Deep_Power_Down(interface_name, csel, clk_speed);

  /* Unlock now that we are done */
  DDR_SYNC_UNLOCK();

} /* ddr_exit_deep_power_down */

/* ============================================================================
**  Function : ddr_get_status
** ============================================================================
*/
/*!
*   @brief
*   Returns the status of DDR.
*
*   @details
*   Returns the ddr_status internal structure so that caller of this API can
*   see which devices are available and what state they are in.
*
*  @param  None
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval returns the status of the devices on all available interface
*   and chip select
*
*   @sa None
*/

ddr_interface_state ddr_get_status(void)
{
  return ddr_status;
} /* ddr_get_status */

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

void ddr_update_info(void)
{
  ddr_info ddr_physical_memory_size = {{{0}}};
  IOCTL_ARG data = {0};
  ddr_size_info *ddr_size = &(ddr_physical_memory_size.ddr_size);
  uint8 i;

  for (i = 0; i < ddr_get_max_channels(); i++)
  {
    ddr_size->ddr_cs0[i] = ddr_shared_data->ddr_size_info.ddr_cs0_mb[i];
    ddr_size->ddr_cs0_addr[i] = ddr_shared_data->ddr_size_info.ddr_cs0_addr[i];

    ddr_size->ddr_cs1[i] = ddr_shared_data->ddr_size_info.ddr_cs1_mb[i];
    ddr_size->ddr_cs1_addr[i] = ddr_shared_data->ddr_size_info.ddr_cs1_addr[i];
  }

  /* Check to see if interleave is turned on */
  ddr_physical_memory_size.interleaved_memory = ddr_param_interleaved();

  /*
    Parse for ddr type from ddr parameters
    it is assumed that interface 0 and interface 1 has to have
    the same ddr type
  */
  ddr_physical_memory_size.ddr_type = (DDR_TYPE)(ddr_shared_data->device_params.device_type);

  /* update for highest banked bit */
  /* populate highest bank bit field */
  //HAL_DDR_IOCTL(IOCTL_CMD_GET_HIGHEST_BANK_BIT, &data);
  ddr_size->highest_bank_bit = data.results;

  ddr_physical_size = ddr_physical_memory_size;
}/* ddr_update_info */

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
  struct detected_ddr_device_params *ddr_detected_param_interface_0 = (ddr_get_detected_params(DDR_CH0));
  /* to workaround drivers calling ddr_get_info prior to ddr init, always update
   * with correct ddr type from ddr params.
   */
  ddr_physical_size.ddr_type = (DDR_TYPE)(ddr_detected_param_interface_0->device_type);

  return ddr_physical_size;
}/* ddr_get_info */

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

void ddr_update_size(void)
{
  uint8 i;
  ddr_info ddr_physical_info = ddr_get_info();

  /* Check to see if interleave is turned on for CS0 */
  if(ddr_physical_info.interleaved_memory & DDR_CS0)
  {
    /* Interleave mode is on for CS0 , add all the sizes of CS0, assign it to interface 0 and do not populate remaining interfaces */
    for (i = 1; i < ddr_get_max_channels(); i++)
    {
      ddr_physical_info.ddr_size.ddr_cs0[0] += ddr_physical_info.ddr_size.ddr_cs0[i];
      ddr_physical_info.ddr_size.ddr_cs0[i] = 0;
    }
  }

  if(ddr_physical_info.interleaved_memory & DDR_CS1)
  {
    /* Interleave mode is on for CS1 , add all the sizes of CS1, assign it to interface 0 and do not populate remaining interfaces */
    for (i = 1; i < ddr_get_max_channels(); i++)
    {
      ddr_physical_info.ddr_size.ddr_cs1[0] += ddr_physical_info.ddr_size.ddr_cs1[i];
      ddr_physical_info.ddr_size.ddr_cs1[i] = 0;
    }
  }

  ddr_system_size = ddr_physical_info.ddr_size;
} /* ddr_update_size */

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
  return ddr_system_size;
} /* ddr_get_size */

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
  ddr_size_partition ddr_partitions = {{{0}}};
  uint8 i;

  /*
    because we only support segment masking due to bank interleaving,
    we always have 8 partitions per device
  */
  for (i = 0; i < ddr_get_max_channels(); i++)
  {
    if (ddr_system_size.ddr_cs0[i])
    {
      ddr_partitions.ddr_cs0[i].ddr_addr = ddr_system_size.ddr_cs0_addr[i];
      ddr_partitions.ddr_cs0[i].num_partitions = 8;
    }
    if (ddr_system_size.ddr_cs1[i])
    {
      ddr_partitions.ddr_cs1[i].ddr_addr = ddr_system_size.ddr_cs1_addr[i];
      ddr_partitions.ddr_cs1[i].num_partitions = 8;
    }
  }
  return ddr_partitions;
}

/* ============================================================================
**  Function : ddr_get_max_channels
** ============================================================================
*/
/**
* @brief
* Returns the max channel num.

  @return
  Max num of channels.

  @dependencies
  None.
*/
uint32 ddr_get_max_channels(void)
{
  return DDR_MAX_NUM_CH_TEST;
}

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


void ddr_unlock_xpu_protected_mem_region()
{
  boot_seclib_if_type *seclib_if = NULL;

  /*Get seclib interface */
  boot_seclib_get_interface(&seclib_if);

	if(seclib_if != NULL)
	{
  	/* Unlock xpu protected region */
  	seclib_if->unlock_xpu_prot_ddr_region();
	}

}

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

void ddr_get_granule_size(uint32* granule_size, uint32 ddr_rank)
{
    uint32 no_of_segments_per_rank = 0, per_channel_density_rank = 0;
    DDR_AOP_PARAMS *ddr_aop_params_ptr = ddr_shared_data->ddr_aop_params.ptr;
    per_channel_density_rank = (ddr_rank == 0) ? ddr_aop_params_ptr->ddr_part_info.per_ch_density_rank0 : ddr_aop_params_ptr->ddr_part_info.per_ch_density_rank1;
    /*Number of Segments for Rank X = (per_ch_density % 3 == 0) ? 6 : 8 */
    no_of_segments_per_rank = (per_channel_density_rank % 3 == 0) ? 6 : 8;
    /*Segment Size for Rank X in MB = ((per_ch_density for Rank X * num_channels) / Number of Segments for Rank X) * (1024 / 8)*/
    *granule_size = (((per_channel_density_rank * ddr_aop_params_ptr->ddr_part_info.num_channels) / no_of_segments_per_rank) * (1024/8));
}


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
uint32 get_num_of_ddr_regions()
{
    return ddr_driver_struct->ddr_regions_info.no_of_ddr_regions;
}


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
  TRUE -  return TRUE if values updated successfully.
  FALSE - returns FALSE if Error in updating values.
*/
bl_error_boot_type get_ddr_region_param(uint8 region_index, DDR_PARAMS_ID param_id,  void *paramptr_value, uint32 *param_size)
{
    bl_error_boot_type return_status = BL_ERR_NONE;
    uint64 *ptr_64 = NULL;
    uint32 *ptr_32 = NULL;
    uint8 *ptr_8 = NULL;


    /* Validate required pointers */
	if (param_size == NULL)
	{
	  return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_NULL_PTR_PASSED);
	  return return_status;
	}
    if (region_index >= ddr_driver_struct->ddr_regions_info.no_of_ddr_regions)
    {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_INVALID_REGION_IDX);
        return return_status;
    }
    if(paramptr_value == NULL && *param_size == 0)
    {
        if(param_id == REGION_START_ADDRESS)
        {
            *param_size = sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[0].start_address);
        }
        else if(param_id == REGION_SIZE)
        {
            *param_size = sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[0].size);
        }
        else if(param_id == HIGHEST_BANK_BIT)
        {
            *param_size = sizeof(ddr_driver_struct->ddr_regions_info.highest_bank_bit);
        }
        else if(param_id == DDR_REGION_RANK)
        {
            *param_size = sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[0].ddr_rank);
        }
        else if(param_id == MIN_PASR_SIZE)
        {
            *param_size = sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[0].granule_size);
        }
        else if(param_id == NUM_PARTITIONS)
        {
            *param_size = sizeof(uint32);
        }
        else if(param_id == DDR_RANK0_SIZE)
        {
            *param_size = sizeof(uint32);
        }
        else if(param_id == DDR_RANK1_SIZE)
        {
            *param_size = sizeof(uint32);
        }
        else
        {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_INVALID_PARAM_ID);
        }

		return return_status;
    }

    if(paramptr_value == NULL && *param_size != 0)
    {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_PARAM_BUFFER_NULL);
        return return_status;
    }

    /* Validate param_ptr_value before use */
	if (paramptr_value == NULL)
	{
	  return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_NULL_PTR_PASSED);
	  return return_status;
	}

    if(*param_size == sizeof(uint64)) /*uint64*/
    {
        ptr_64 = (uint64*)paramptr_value;
    }
    else if(*param_size == sizeof(uint32)) /*uint32*/
    {
        ptr_32 = (uint32*)paramptr_value;
    }
    else if(*param_size == sizeof(uint8)) /*uint8 */
    {
        ptr_8 = (uint8*)paramptr_value;
    }
    else
    {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
        return return_status;
    }

    if(param_id == REGION_START_ADDRESS)
    {
       if(*param_size != sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[region_index].start_address))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_64 = ddr_driver_struct->ddr_regions_info.ddr_region[region_index].start_address;
    }
    else if(param_id == REGION_SIZE)
    {
       if(*param_size != sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[region_index].size))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_64 = ddr_driver_struct->ddr_regions_info.ddr_region[region_index].size >> 20; /*Convert to MB*/
    }
    else if(param_id == HIGHEST_BANK_BIT)
    {
       if(*param_size != sizeof(ddr_driver_struct->ddr_regions_info.highest_bank_bit))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_32 = ddr_driver_struct->ddr_regions_info.highest_bank_bit;
    }
    else if(param_id == DDR_REGION_RANK)
    {
       if(*param_size != sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[region_index].ddr_rank))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_8 = ddr_driver_struct->ddr_regions_info.ddr_region[region_index].ddr_rank;
    }
    else if(param_id == MIN_PASR_SIZE)
    {
       if(*param_size != sizeof(ddr_driver_struct->ddr_regions_info.ddr_region[region_index].granule_size))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_32 = ddr_driver_struct->ddr_regions_info.ddr_region[region_index].granule_size;
    }
    else if(param_id == NUM_PARTITIONS)
    {
       if(*param_size != sizeof(uint32))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_32 = 8;
    }
    else if(param_id == DDR_RANK0_SIZE)
    {
       if(*param_size != sizeof(uint32))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_32 = ddr_driver_struct->ddr_regions_info.ddr_rank0_size >> 20; //Convert into MB
    }
    else if(param_id == DDR_RANK1_SIZE)
    {
       if(*param_size != sizeof(uint32))
       {
            return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_GET_PARAM_BUFFER_SMALL);
            return return_status;
       }
       *ptr_32 = ddr_driver_struct->ddr_regions_info.ddr_rank1_size >> 20; //Convert into MB
    }
    else
    {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DDR, BL_ERR_DDR_INVALID_PARAM_ID);
        return return_status;
    }
    return return_status;
}

/* ============================================================================
**  Function : ddr_fw_exit
** ============================================================================
*/
/*!
*   @brief
*   Function to call HAL_DDR_FW_Exit
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
void ddr_fw_exit()
{
  if(ddr_get_boot_mode()  !=  BOOT_MODE_RAMDUMP)
	HAL_DDR_FW_Exit();
}
