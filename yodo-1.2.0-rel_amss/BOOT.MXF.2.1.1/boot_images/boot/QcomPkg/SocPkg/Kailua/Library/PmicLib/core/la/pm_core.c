/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                  PMIC Startup Services

GENERAL DESCRIPTION
  This file contains initialization functions and corresponding variable
  declarations to support interaction with the Qualcomm Pmic chips.

  Copyright (c) 2013-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/04/18   sb      Added API for target specific cleanup
04/12/17   va      Enable FG,schg protocol
07/07/16   cm      Remove Gold cluster enable.
06/01/16   sm      Removed EFI_QCOM_CHARGER_EX_PROTOCOL related changes
05/10/16   al      Adding PON protocol 
05/06/16   sm      Added Pmic Charger Protocol to install 
04/09/16   al      Enable Gold cluster
03/30/16   va      enable protocol 
03/09/16   va      Moved common protocol install to pmic.c
03/08/16   al      Moving NPA to common
07/23/15   al      Adding NPA
07/21/14   va      Adding Fuel Gauge Protocol
07/03/14   al      Adding MIPI-BIF, RGB. Removing SW workaround since it doesn't solve issue
06/06/14   al      Adding workaround for HW issue 
04/28/14   va      Expose Npa Test protocol
05/09/14   al      Adding IBB and LAB 
04/18/14   al      Added SMBCHG 
11/22/13   va      PmicLib Dec Addition
10/02/13   al      New File
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "com_dtypes.h"
#include "pm_uefi.h"
#include <Library/UefiBootServicesTableLib.h>

/**
  PMIC PROTOCOL interface
*/
#include "Protocol/EFIPmicSchg.h"
#include "Protocol/EFIPmicFg.h"
#include "Protocol/EFIPmicVreg.h"
#include "Protocol/EFIPmicPwrOn.h"
#include "pm_comm.h"
#include "CoreVerify.h"

#include "pmapp_npa.h"
#include "npa_resource.h"
#include "pm_sdam.h"
#include "pm_log_utils.h"
#include "pm_version.h"

#include <Protocol/EFITlmm.h>

#include "DDIPlatformInfo.h"
#include "pm_dt_parser.h"
#include "pm_chg.h"
#include "pm_app_chg.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

#define PON_INT_MID_SEL_REG  0x81A
#define PMICA_SLAVE_ID_0     0x0
#define INT_MID_0_VAL        0x0
#define SPMI_PRIORITY        0x0

#define SDAM_MEM_013_ADDR    13
#define GPIO_GROUNDED        0x0
#define SINGLE_BYTE          1

#define TIMEOUT_MAX          2500
/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/
extern EFI_QCOM_PMIC_SCHG_PROTOCOL        PmicSchgProtocolImplementation;
extern EFI_QCOM_PMIC_FG_BASIC_PROTOCOL    PmicFgBasicProtocolImplementation;
extern EFI_QCOM_PMIC_PON_PROTOCOL         PmicPonProtocolImplementation;


/*===========================================================================

                LOCAL FUNCTION PROTOTYPES

===========================================================================*/
static pm_err_flag_type pm_core_is_charging_applicable(boolean* applicable);
static pm_err_flag_type pm_dead_battery_status_check(void);

/*===========================================================================

                EXTERNAL FUNCTION PROTOTYPES

===========================================================================*/

pm_err_flag_type pm_install_target_protocols(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{

  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  EFI_STATUS  Status = EFI_SUCCESS;

  Status = gBS->InstallMultipleProtocolInterfaces(
    &ImageHandle,
    &gQcomPmicPonProtocolGuid,  &PmicPonProtocolImplementation,       /*installing gQcomPmicPonProtocolGuid for open source*/
    &gQcomPmicSchgProtocolGuid, &PmicSchgProtocolImplementation,
    &gQcomPmicFgProtocolGuid,   &PmicFgBasicProtocolImplementation,
    NULL
    );

  err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;

  return err_flag;
}


pm_err_flag_type pm_post_pmic_initialization(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
#ifdef FEATURE_XBOOT
  uint32 chgr_pmic_index = PMIC_INDEX_MAX;
#endif /* FEATURE_XBOOT */

  err_flag = pm_dead_battery_status_check();

#ifdef FEATURE_XBOOT
  err_flag |= pm_chg_get_primary_charger_pmic_index(&chgr_pmic_index);
  if (err_flag == PM_ERR_FLAG_SUCCESS) {
    err_flag |= pm_comm_write_byte(chgr_pmic_index, 0x2659, 0x58);  // Set SCPQ_P_CHGR_VFLT_MAX  to 4.48 V
  }
#endif /* FEATURE_XBOOT */

#ifdef FEATURE_XBOOT
  err_flag |= pm_comm_write_byte(7, 0xF046, 0x00); // PMIC Haptics disable
#endif /* FEATURE_XBOOT */

  return err_flag;
}


pm_err_flag_type pm_uefi_exit_target_specific_cleanup(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

static pm_err_flag_type 
pm_core_is_charging_applicable(boolean* applicable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  DalPlatformInfoPlatformType platform_type = DALPLATFORMINFO_TYPE_UNKNOWN;
  pm_model_type pmic_model = PMIC_IS_UNKNOWN;
  uint32 device_index_charger = PM_MAX_NUM_PMICS;
  *applicable = FALSE;

  if (pm_is_target_pre_silicon() == TRUE)
  {
    pm_log_message("Pre-SIL. No CHG Support");
    return PM_ERR_FLAG_SUCCESS; 
  }

  if(FALSE == pm_driver_init_status())
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_chg_get_primary_charger_pmic_index(&device_index_charger);
  if(PM_ERR_FLAG_SUCCESS != err_flag)
  {
    return err_flag;
  }

  platform_type = DalPlatformInfo_Platform();
  pmic_model = pm_get_pmic_model(device_index_charger);
  if( ((platform_type == DALPLATFORMINFO_TYPE_MTP)
    || (platform_type == DALPLATFORMINFO_TYPE_FLUID)
    || (platform_type == DALPLATFORMINFO_TYPE_LIQUID)
    || (platform_type == DALPLATFORMINFO_TYPE_QRD)
    || (platform_type == DALPLATFORMINFO_TYPE_HDK)) &&
       (pmic_model == PMIC_IS_KOHALA))
  {
    *applicable = TRUE;
  }

  return err_flag;
}

static pm_err_flag_type pm_dead_battery_status_check(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean applicable = FALSE;

  err_flag |= pm_core_is_charging_applicable(&applicable);
  if(TRUE == applicable)
  {
    err_flag |= pm_app_chg_init();

    err_flag |= pm_app_chg_dead_battery_charging();
  }

  return err_flag;
}
