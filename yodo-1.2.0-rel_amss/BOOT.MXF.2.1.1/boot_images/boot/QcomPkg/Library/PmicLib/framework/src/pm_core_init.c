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


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_core_init.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
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
#include "pm_config_setting.h"

#define PM_PRIMARY_PMIC_INDEX  0

boolean bPMICStub = FALSE;

static volatile boolean is_standalone = FALSE;

void pm_print_all_pmic(void)
{
  uint8 pmic_index = 0;
  uint8 bus_id = 0;
  pm_model_type pmic_model = PMIC_IS_INVALID;

  /*print pmic revision*/
  for(bus_id = 0; bus_id < PM_MAX_BUSES_SUPPORTED; bus_id++)
  {
    PM_LOG_MSG("BUS_ID %d: ", bus_id);
    while (pmic_index < PM_MAX_NUM_PMICS)
    {
      pmic_model = pm_get_pmic_model_ex(bus_id, pmic_index);
      if (pmic_model != PMIC_IS_UNKNOWN && pmic_model != PMIC_IS_INVALID)
      {
        PM_LOG_MSG("PM%d: %d, ",pmic_index, pmic_model);
      }
      pmic_index++;
    }
    pmic_index = 0;
    PM_LOG_MSG("\n");
  }
}


pm_err_flag_type pm_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_device_setup();

  if (pm_get_pmic_model(PM_PRIMARY_PMIC_INDEX) == PMIC_IS_UNKNOWN)
  {
    return PM_ERR_FLAG_FAILURE;
  }

  err_flag |= pm_target_information_init();
  pm_utils_get_time("pm_target_information_init");

  err_flag |= pm_config_img_settings_init();
  pm_utils_get_time("pm_config_img_settings_init");

#ifdef FEATURE_XBOOT
  err_flag |= pm_comm_write_byte_ex(0, 1, 0x1546, 0x00); // Put PM8550 VREG_COIN to 0x0
#endif /* FEATURE_XBOOT */

  pm_comm_info_init();
  pm_utils_get_time("pm_comm_info_init");

  pm_resource_manager_init();
  pm_utils_get_time("pm_resource_manager_init");

  if (is_standalone)
  {
    return err_flag;
  }

  pm_rpmh_init();
  pm_utils_get_time("pm_rpmh_init");

  pm_prm_init();
  pm_utils_get_time("pm_prm_init");

  pm_print_all_pmic();
  pm_utils_get_time("pm_print_all_pmic");

  return err_flag;

}

uint32 pm_get_img_type(void)
{
  return PM_IMG_CORE;
}
