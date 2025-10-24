/*! \file pm_spmi.c
*   \n
*   \brief This file contains PMIC access control function protects pmic arb
*   \n address regions 
*   \n
*   \n &copy; Copyright 2010-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header:  $
$Author: pwbldsvc $
$DateTime: 2022/02/22 18:53:09 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/27/22   cgoel     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_device.h"
#include "pm_config_target.h"
#include "SpmiCfg.h"
#include "SpmiBus.h"
#include "seclib_ac.h"

/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
#define PM_TARGET_MAX_NUM_RGS 18
#define SDARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

SpmiBusCfg_RGConfig pm_spmi_rg_cfg [PM_TARGET_MAX_NUM_RGS] ={0};
uint32 pm_spmi_rg_sz = sizeof(pm_spmi_rg_cfg) / sizeof(SpmiCfg_RGConfig);

ACSecDomainPerm sdArray_AOP[] = {
{ .sdId = AC_SD_AOP, .perm = AC_READ_WRITE, .lock = 0},
};

ACSecDomainPerm sdArray_APP_S[] = {
{ .sdId = AC_SD_AP_SEC, .perm = AC_READ_WRITE, .lock = 0},
};

ACSecDomainPerm sdArray_MODEM[] = {
{ .sdId = AC_SD_MODEM, .perm = AC_READ_WRITE, .lock = 0},
};

/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/

pm_err_flag_type 
pm_spmi_ac_cfg()
{
  pm_err_flag_type err_flag           = PM_ERR_FLAG_SUCCESS;
  SpmiCfg_RGConfig* rg_cfg            = NULL;
  uint32 index                        = 0;
  uint8 bus_id                        = 0;
  ACSecDomainPerm *sdArray = sdArray_AOP;
  uint32 sdCount = 0;
 
  //Divide number of available RG's equally
  //Check if SPMI can return actual number of RG's used and do the math
  pm_spmi_rg_sz = pm_spmi_rg_sz/PM_MAX_BUSES_SUPPORTED;
  
  for (bus_id = 0; bus_id < PM_MAX_BUSES_SUPPORTED; bus_id++)
  {
    //Clear configuration for each bus iteration
    for (index = 0; index < PM_TARGET_MAX_NUM_RGS; index++)
    {
      pm_spmi_rg_cfg[index].ownerMask = SPMI_OWNER_NONE;
      pm_spmi_rg_cfg[index].startAddr = 0;
      pm_spmi_rg_cfg[index].size      = 0;
      pm_spmi_rg_cfg[index].startIdx  = 0;
      pm_spmi_rg_cfg[index].endIdx    = 0;
    }
  
    //Populate RG cfg table
    if(SpmiBusCfg_CalculateRGConfig(bus_id, pm_spmi_rg_cfg, &pm_spmi_rg_sz) != SPMI_SUCCESS)
    {
      return PM_ERR_FLAG_BUS_ERR;
    }
  
    // For each RG configure its MPU region.
    for (index = 0; index < pm_spmi_rg_sz; index ++)
    {
      rg_cfg = &pm_spmi_rg_cfg[index];
  
      if(rg_cfg->ownerMask != SPMI_OWNER_NONE)
      {
        switch(rg_cfg->ownerMask)
        {
          case SPMI_OWNER_TZ:
            sdArray = sdArray_APP_S;
            sdCount = SDARRAY_SIZE(sdArray_APP_S);
          break;
          case SPMI_OWNER_MSS:
            sdArray = sdArray_MODEM;
            sdCount = SDARRAY_SIZE(sdArray_MODEM);
          break;
          case SPMI_OWNER_AOP:
            sdArray = sdArray_AOP;
            sdCount = SDARRAY_SIZE(sdArray_AOP);
          break;
          case SPMI_OWNER_INVALID:
          case SPMI_OWNER_NONE:
          default:
            return PM_ERR_FLAG_INVALID_PARAMETER;
          break;
        }

        if(ACxBLSCxPUProtectRegion(rg_cfg->startAddr, rg_cfg->startAddr + rg_cfg->size, sdArray, sdCount, false) != SECLIB_SUCCESS )
        {
          return PM_ERR_FLAG_FAILURE;
        }
      }
    }
  }
  
  return err_flag;
}




