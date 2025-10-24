/*! \file pm_target_information.c
*  
*  \brief This file contains functions to return target specific and common PMIC settings.
*  \n   
*  &copy; Copyright 2010-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/framework/src/pm_target_information.c#1 $ 

when       who          what, where, why
--------   ---         ----------------------------------------------------------
06/11/13    hs          Adding settling time for regulators.
06/04/13    aks         Remove range related hacks
05/29/13    aks         Clk driver input check (do not disable critical clocks)
05/29/13    kt          Added Peripheral Probe fix.
05/20/13    aks         Clk driver code re-architecture
04/23/13    hs          Fixed the naming convention in \config.
04/16/13    hs          Added workaround for 8110 L1.
04/12/13    hs          Code refactoring.
02/27/13    hs          Code refactoring.
08/07/12    hs          Added support for 5V boost.
04/16/12    hs          Removed irq files.
04/03/10    wra         Creating file for MSM8960
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
#include "aop_settings.h"

/*===========================================================================

                        STATIC/EXTERN VARIABLES 

===========================================================================*/
static aop_settings_handle dev_id = NULL;
/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

void pm_target_information_init(void)
{
  dev_id = get_settings_handle("pmic");
  CORE_VERIFY(dev_id != NULL);
}


void* pm_target_information_get_specific_info(char* prop_id)
{
  void *info = NULL;
  
  info = (void*)get_aop_settings_prop_val(dev_id, prop_id); 

  return info;
}


uint32 pm_target_information_get_periph_count_info(char* prop_id, uint8 pmic_index)
{
  uint32 *peripheral_count = NULL;

  peripheral_count = (uint32 *)get_aop_settings_prop_val(dev_id,prop_id); 

  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return peripheral_count[pmic_index];
  }

  return 0;
}

