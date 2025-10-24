/*===========================================================================

                    BOOT CLK WRAPPER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for clock drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/19/20   rama    Updated Clock APIs
08/02/19   ep      Created the file.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "MIprogressive.h"
#include "boot_error_if.h"
#include <boot_clk_if.h>
#include <voltage_level.h>

/*===========================================================================
                     Globals
===========================================================================*/
static ClockHandle nClkHandle;

#define CLOCK_BOOT_CORNER RAIL_VOLTAGE_LEVEL_NOM
/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


/*===========================================================================

**  Function :  boot_clock_init

** ==========================================================================
*/
/*!
*
*  This function initializes the apps processor clocks and ramps up
*  the processor speed to the initial one specified in the BSP.
*  It should be invoked from the apps boot loader code.
*
* 
*
* @par Dependencies Shared memory must be ready.
*
* @return  FALSE if initialization failed.
*
* @par Side Effects  The core clock and MSMC2 voltage are switched.
*
*/
static bl_error_boot_type boot_clock_init(void)
{
  if (Clock_Init() != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  if(Clock_Attach(&nClkHandle, NULL) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }

  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  boot_clock_init_group

** ==========================================================================
*/
/*!
*
*  This function initializes a Clock Group
*
* 
*
* @par Dependencies Shared memory must be ready.
*
* @return  FALSE if initialization failed.
*
* @par None
*
*/
static bl_error_boot_type boot_clock_init_group(const char *szName)
{
  ClockIdType nCLkId;
  
  if(Clock_GetId(nClkHandle, szName, &nCLkId) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  
  if(Clock_SetFrequency(nClkHandle,
                        nCLkId,
            CLOCK_BOOT_CORNER,
            CLOCK_FREQUENCY_FMAX,
            NULL) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  
  if(Clock_Enable(nClkHandle, nCLkId) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  
  return BL_ERR_NONE;
}
/*===========================================================================
**  Function :  boot_clock_set_freq
** ==========================================================================
*/
/*!
*
* This function sets the frequency for a clock group
*
* @param
*   None
*
* @return
*   True : Success
*   False : Failure
*
* @dependencies
*   None
*
*/
static bl_error_boot_type boot_clock_set_freq(const char *szName, uint32_t nFreq, ClockFrequencyType eMatch)
{
  ClockIdType nCLkId;

  if(Clock_GetId(nClkHandle, szName, &nCLkId) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }

  if(Clock_SetFrequency(nClkHandle, nCLkId, nFreq, eMatch, NULL) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  
  if(Clock_Enable(nClkHandle, nCLkId) != CLOCK_SUCCESS)
  {
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  }
  return BL_ERR_NONE;
}


/*===========================================================================
**  Function :  boot_clock_get_freq_khz
** ==========================================================================
*/
/*!
*
* This function returns the frequency of a particular clock.
*
* @param
*  core - group to get the clock
*
* @return
*  Apps clock speed in KHz
*
* @dependencies
*   None
*
*/
static uint32 boot_clock_get_freq_khz(const char *szName)
{
  uint32 nFreqHz = 0;
  ClockIdType nCLkId;
  
  Clock_GetId(nClkHandle, szName, &nCLkId);
  Clock_GetFrequency(nClkHandle, nCLkId, &nFreqHz);
  
  return nFreqHz / 1000;
}

/*===========================================================================
**  Function :  boot_clock_init_rpm
** ==========================================================================
*/
/*!
*
* This function initializes clocks required for RPM.
*
* @param
*  None
*
* @return
*  TRUE    Initialization successful
*  FALSE   Initialization failed
*
* @dependencies
*   None
*
*/
static bl_error_boot_type boot_clock_init_rpm()
{
  if(Clock_InitRPM() != CLOCK_SUCCESS)
    return BL_ERR_CPU_CLK_INIT_FAIL|BL_ERROR_GROUP_BOOT;
  else
    return BL_ERR_NONE;
}



/*===========================================================================
**  Function :  boot_clk_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_clk_get_interface
*
* @par Dependencies
*   None 
* 
*/
/*
bl_error_boot_type boot_clk_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_clk_if_type *clk_if = (boot_clk_if_type *)ptr;
    if(clk_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CLK, BL_ERR_INVALID_PARAMETER);
      break;
    }


    clk_if->init = boot_clock_init;
    clk_if->pre_ddr_clock_init = Clock_PreDDRInit;
    clk_if->pre_i2c_clock_init = Clock_I2CInit;
    clk_if->dload_clock_init = Clock_InitForDownloadMode;
    clk_if->exit_boot = Clock_ExitBoot;
    clk_if->debug_init = Clock_DebugInit;
    clk_if->set_cpu_perf_level = Clock_SetCPUPerfLevel;
    clk_if->set_sys_perf_level = Clock_SetSysPerfLevel;
    clk_if->get_ddr_speed = Clock_DDRSpeed;
    clk_if->init_rpm = boot_clock_init_rpm;
    clk_if->get_apps_speed = boot_clock_get_apps_speed;
    clk_if->SetBIMCSpeed = Clock_SetBIMCSpeed;


  } while(FALSE);

  return return_status;
}
*/

boot_clk_if_type clk_if = {
    boot_clock_init,             // init
    boot_clock_init_group,       // init_group
    Clock_ExitBoot,              // exit_boot
    boot_clock_get_freq_khz,     // get_freq
    boot_clock_set_freq,         // set_freq
    boot_clock_init_rpm          // Init RPM clocks
};
