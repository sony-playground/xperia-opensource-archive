/*=============================================================================

                       Common Boot A53 Handler

GENERAL DESCRIPTION
  This file contains definitions of functions for reset and powerdown routines.

Copyright 2010-2015,2019-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ------------------------------------------------------------
11/18/22   amaji   Remove pmic_if and add direct calls to PMIC APIs for size optimization of devprg image
07/02/22   ck      Corrected set_pwrkey_reset_type and set_pshold_reset_type return values
03/30/22   ck      Added reset separation workaround for Lassen
01/05/22   rama    Remove boot_log_deinit_uart
07/08/21   ck      Updated all functions to return error code
06/16/21   ds      remove reset dload cookie 
01/19/21   rama    Removed jtag_term_putc
06/24/20   ds      waipio update for memmap and hwio
05/29/20   rama    Replace boot_dload.h with boot_crashdump.h
02/24/20   rama    Moved APIs from boot_a53.c to boot_reset.c
05/24/18   vk      Add UART deinit before reset
10/05/15   kpa     Changed boot_pm_ps_hold_cfg() API to boot_pm_app_pon_pshold_cfg() to match pmic API name
03/03/15   kpa     Correctly configure boot_pm_pon_ps_hold_cfg for hard reset.
02/12/15   ck      Removed boot_switch_to_aarch64
01/07/15   aab     Updated boot_pm_pon_ps_hold_cfg() API call
10/29/14   kpa     Support 64 bit memory map
03/18/14   ck      Removed boot_hw_warm_reset as it is redundant
03/18/14   ck      boot_hw_reset now takes a parameter specifying what kind of reset to perform
02/05/14   ck      Added A53 logic to switch from 32 to 64 bit mode.
12/06/13   ck      Removed GCC_WDOG_DEBUG as this does not exist on A53
12/06/13   ck      Initial creation from boot_krait.c, preserving change log
07/31/13   dh      backed out pmic hard reset per windows request
07/24/13   aus     Added boot_hw_warm_reset
07/09/13   dh      Perform hard pmic reset in boot_hw_reset if sbl is in dload mode  
04/02/13   dh      Add boot_pm_pon_ps_hold_cfg to properly configure reset and shutdown 
01/22/13   dh      Disable watchdog debug feature in boot_hw_reset
12/10/12   plc     Fix Klockwork Errors
10/25/12   dh      Remove pragma to surpass inline assemly since armct5.01 allows it
09/19/12   dh      enable ps hold reset
08/08/12   dh      use self loop in boot_hw_reset ps hold doesn't work
06/26/12   dh      use ps hold in boot_hw_reset
08/05/11   kpa     Relocated boot_hw_powerdown() here from boothw_target.c.
05/19/11   kpa     1. Remove inclusion of boot_scorpion_mmu.h, code common to
                   boot_page_table.c. 
                   2. Check the jtag debug disable fuse before output to jtag
                   terminal to avoid crash
5/11/11    plc     Change to include boot_page_table_armv7.h
01/25/11   dh      fixed l2 page table overflow issue
09/10/10   aus     Enabling data cache and MMU in boot
07/22/10   aus     Intial creation.
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <boot_busywait_if.h>
#include <boot_crashdump.h>
#include "boot_logger_uart.h"
#include <boot_error_if.h>
#include <boot_reset_if.h>
#include <boot_config_context.h>
#include <boot_platforminfo_if.h>
#include <pm.h>


/**
 * Infinite loop
 */
#define INFINITE_LOOP() while(1)



/*===========================================================================
**  Function :  hw_reset
** ==========================================================================
*/
/*!
* 
* @brief
*   This function resets the processor.  Parameter specifies what kind
*   of reset to perform.
* 
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   Target is reset
* 
*/
static bl_error_boot_type hw_reset(boot_hw_reset_type reset_type)
{
  bl_error_boot_type status = BL_ERR_NONE;

#ifdef HWIO_AOSS_CC_PCIE_RESET_CTRL_ADDR
  boot_platforminfo_if_type * platforminfo_if = NULL;
  DALResult dal_result = DAL_SUCCESS;
  DalChipInfoFamilyType chip_family = CHIPINFO_FAMILY_UNKNOWN;
#endif


  /* Set the PMIC to do the requested type of reset when PS_HOLD is asserted */
  switch (reset_type)
  {
    case BOOT_WARM_RESET_TYPE:
      /* Configure PS_HOLD to do warm reset */
      pm_app_pon_pshold_cfg(PM_APP_PON_CFG_WARM_RESET);
      break;

    case BOOT_APQ_COLD_DEBUG_RESET:
      pm_app_pon_debug_hard_reset();
      break;

    case BOOT_HARD_RESET_TYPE:
    default:
      /* Configure PS_HOLD to do hard reset.  This is also the default type.*/
      pm_app_pon_pshold_cfg(PM_APP_PON_CFG_HARD_RESET);
      break;
  }


#ifdef HWIO_AOSS_CC_PCIE_RESET_CTRL_ADDR
  /* Acquire platforminfo interface */
  status =  boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE,
                                        CONFIG_CONTEXT_PLATFORMINFO_INTERFACE,
                                        (void **)&platforminfo_if);

  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (platforminfo_if == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_RESET, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  /* Acquire chip family */
  dal_result = platforminfo_if->ChipFamily((void *)&chip_family);
  if (dal_result != DAL_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* If chip family is Lassen then apply reset separation workaround. */
  if (chip_family == CHIPINFO_FAMILY_LASSEN)
  {
    HWIO_OUTF(AOSS_CC_PCIE_RESET_CTRL, OVERRIDE_FULL_RESET, 1);
    __asm("DSB SY");
  }
#endif


  /* pull down pmic PS_HOLD */
  HWIO_OUTF(MPM_PS_HOLD, PSHOLD_MPM, 0x0 );

  /* Loop forever */
  INFINITE_LOOP();
  
  /* Execution should never reach here, but just in case it does return a failure */
  status = GET_ERROR_CODE(BL_ERROR_GROUP_RESET, BL_ERR_HW_RESET_FAILURE);

 exit:
  return status;
}


/*===========================================================================
**  Function :  hw_powerdown
** ==========================================================================
*/
/*!
* 
* @brief
*   This function powers off the PMIC
* 
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   Target is switched off
* 
*/
static bl_error_boot_type hw_powerdown(void)
{

  /* Configure PS_HOLD to shutdown */
  pm_app_pon_pshold_cfg(PM_APP_PON_CFG_NORMAL_SHUTDOWN);

    
  /* pull down pmic PS_HOLD */
  HWIO_OUTF(MPM_PS_HOLD, PSHOLD_MPM, 0x0 );

  /* Loop forever */
  INFINITE_LOOP();

  return GET_ERROR_CODE(BL_ERROR_GROUP_RESET, BL_ERR_HW_POWERDOWN_FAILURE);
}


/*===========================================================================
**  Function :  set_pwrkey_reset_type
** ==========================================================================
*/
/*!
* 
* @brief
*   This function sets the power key reset to hardreset
*   or warmreset as per the provided argument
* 
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
static bl_error_boot_type set_pwrkey_reset_type(boot_hw_reset_type reset_type)
{
  bl_error_boot_type status = BL_ERR_NONE;
  pm_err_flag_type  pmic_status = PM_ERR_FLAG_SUCCESS;


  switch (reset_type)
  {
    case BOOT_WARM_RESET_TYPE:
      // PON KPDPWR PON Reset configuration to WARM_RESET
      pmic_status = pm_app_pon_reset_cfg(PM_APP_PON_RESET_SOURCE_KPDPWR,
                                                 PM_APP_PON_CFG_WARM_RESET,
                                                 10256,
                                                 2000); 
      break;

    case BOOT_HARD_RESET_TYPE:
    default:
      // PON KPDPWR PON Reset configuration to HARD_RESET
      pmic_status = pm_app_pon_reset_cfg(PM_APP_PON_RESET_SOURCE_KPDPWR,
                                                 PM_APP_PON_CFG_HARD_RESET,
                                                 10256,
                                                 2000); 
      break;
  } 


  if (pmic_status != PM_ERR_FLAG_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_RESET, BL_ERR_PWRKEY_RESET_FAILURE);
  }


  return status;
}


/*===========================================================================
**  Function :  set_pshold_reset_type
** ==========================================================================
*/
/*!
* 
* @brief
*   This function sets the pshold reset to hardreset
*   or warmreset as per the provided argument
* 
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   None
* 
*/
static bl_error_boot_type set_pshold_reset_type(boot_hw_reset_type reset_type)
{
  bl_error_boot_type status = BL_ERR_NONE;
  pm_err_flag_type  pmic_status = PM_ERR_FLAG_SUCCESS;


  switch (reset_type)
  {
    case BOOT_WARM_RESET_TYPE:
      /* Configure PS_HOLD to do warm reset */
      pmic_status = pm_app_pon_pshold_cfg(PM_APP_PON_CFG_WARM_RESET);
      break;

    case BOOT_HARD_RESET_TYPE:
    default:
      /* Configure PS_HOLD to do hard reset.  This is also the default type.*/
      pmic_status = pm_app_pon_pshold_cfg(PM_APP_PON_CFG_HARD_RESET);
      break;
  }


  if (pmic_status != PM_ERR_FLAG_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_RESET, BL_ERR_PSHOLD_RESET_FAILURE);
  }


  return status;
}


bl_error_boot_type boot_hw_powerdown(void)
{
  return hw_powerdown();
}


bl_error_boot_type boot_hw_reset(boot_hw_reset_type reset_type)
{
  return hw_reset(reset_type);
}


bl_error_boot_type boot_set_pshold_reset_type(boot_hw_reset_type reset_type)
{
  return set_pshold_reset_type(reset_type);
}


bl_error_boot_type boot_set_pwrkey_reset_type(boot_hw_reset_type reset_type)
{
  return set_pwrkey_reset_type(reset_type);
}


boot_reset_if_type reset_if = {
  hw_reset,
  hw_powerdown,
  set_pwrkey_reset_type,
  set_pshold_reset_type
};
