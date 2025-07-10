/*! \file pm_init.c
*   \n
*   \brief This file contains PMIC initialization function which initializes the PMIC Comm
*   \n layer, PMIC drivers and PMIC applications.
*   \n
*   \n &copy; Copyright 2010-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/framework/src/pm_core_init.c#5 $
$Author: pwbldsvc $
$DateTime: 2023/03/06 07:47:59 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/13/17    al     Add support to read pbs info in core
08/08/15   aab     Added pm_device_setup()
07/23/15   al      Removing NPA from common
12/06/14   al      enabling npa
11/12/14   al      adding for compilation
07/16/14   akm     Comm change Updates
03/31/14   akm     Cleanup
01/15/13   aab     Fixed KW error
05/10/11   jtn     Fix RPM init bug for 8960
07/01/10   umr     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_device.h"
#include "pm_target_information.h"
#include "pm_rpmh.h"
#include "pm_prm_init.h"
#include "pm_prm_os.h"
#include "pm_log_utils.h"
#include "DDIPlatformInfo.h"
#include "pm_dt_parser.h"

#define PM_PRIMARY_PMIC_INDEX  0

boolean bPMICStub = FALSE;

static volatile boolean is_standalone = FALSE;

static pm_err_flag_type 
pm_update_charger_pmic_index(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = NULL;
  
  if(NULL == charger_dt_config)
  {
    charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
    CORE_VERIFY_PTR(charger_dt_config);
  }
  
  if(pm_get_pmic_model(charger_dt_config->charger_pmic_index) == PMIC_IS_UNKNOWN)
  {
    if(pm_get_pmic_model(PMIC_I) == PMIC_IS_PM7250B)
    {
      charger_dt_config->charger_pmic_index = PMIC_I;
    }
    else if(pm_get_pmic_model(PMIC_C) == PMIC_IS_PMI632)
    {
      charger_dt_config->charger_pmic_index = PMIC_C;
    }
    else if(pm_get_pmic_model(PMIC_D) == PMIC_IS_PM8350B)
    {
      charger_dt_config->charger_pmic_index = PMIC_D;
    }
    err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  return err_flag;
}

void pm_print_all_pmic(void)
{
  int i = 0;
  /*print pmic revision*/
  while (i < PM_MAX_NUM_PMICS)
  {
    if (pm_get_pmic_model(i) != PMIC_IS_UNKNOWN)
    {
      PM_LOG_MSG("PM%d: %d, ",i, pm_get_pmic_model(i));
    }
    i += 1;
  }
  PM_LOG_MSG("\n");
}


pm_err_flag_type pm_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_device_setup();

  if (pm_get_pmic_model(PM_PRIMARY_PMIC_INDEX) == PMIC_IS_UNKNOWN)
  {
    return PM_ERR_FLAG_FAILURE;
  }
  
  if(CHIPINFO_FAMILY_CLARENCE == DalChipInfo_ChipFamily() 
                  || CHIPINFO_FAMILY_NETRANI == DalChipInfo_ChipFamily())
  {
    err_flag |= pm_update_charger_pmic_index();
  }

  err_flag |= pm_target_information_init();

  pm_comm_info_init();

  pm_resource_manager_init();

  if (is_standalone)
  {
    return err_flag;
  }

  pm_rpmh_init();

  pm_prm_init();

  pm_print_all_pmic();

  return err_flag;

}

uint32 pm_get_img_type(void)
{
  return PM_IMG_CORE;
}
