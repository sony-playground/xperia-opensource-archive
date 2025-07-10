/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                  PMIC Startup Services

GENERAL DESCRIPTION
  This file contains initialization functions and corresponding variable
  declarations to support interaction with the Qualcomm Pmic chips.

  Copyright (c) 2013-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
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

#include "i2c_api.h"
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
static pm_err_flag_type pm_i2c_sid_config(void);

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

  /* 
    PON peripheral interrupts are routed to Master PMIC such that PBS can receive PON interrupts. 
    Once UEFI boot reaches the point of pwr key hold check function, after the check passes,
    it needs to change the PON MID back to MSM which is 0 so that APPS can resume receiving the interrupts.
    INT is disabled at the UEFI exit. CR - 2157004
    */
   //commenting below one since it can't be written from UEFI anymore
 // err_flag = pm_comm_write_byte(PMICA_SLAVE_ID_0, PON_INT_MID_SEL_REG, INT_MID_0_VAL);

  err_flag |= pm_dead_battery_status_check();

  err_flag |= pm_i2c_sid_config();
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
  uint32 device_index_charger = PMIC_D;
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

  platform_type = DalPlatformInfo_Platform();
  pmic_model = pm_get_pmic_model(device_index_charger);
  if( ((platform_type == DALPLATFORMINFO_TYPE_MTP)
    || (platform_type == DALPLATFORMINFO_TYPE_FLUID)
    || (platform_type == DALPLATFORMINFO_TYPE_LIQUID)
    || (platform_type == DALPLATFORMINFO_TYPE_QRD)
    || (platform_type == DALPLATFORMINFO_TYPE_HDK)) &&
       (pmic_model == PMIC_IS_PM8350B))
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

static pm_err_flag_type pm_i2c_sid_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  i2c_status istatus       = I2C_SUCCESS;
  void *i2c_handle        = NULL;
  uint32 read_write_count  = 0;
  UINT32 config_LEA, config_LEB;
  uint8  packet_data[] = {0x06, 0x44, 0x03};      /* peripheral id, register address, register value */
  const uint32 packet_size = sizeof(packet_data);
  EFI_TLMM_PROTOCOL *TLMMProtocol = NULL;
  EFI_STATUS Status = EFI_SUCCESS;
  pm_model_type pmic = pm_get_pmic_model(PMIC_I);

  if(pmic != PMIC_IS_UNKNOWN && pmic != PMIC_IS_INVALID)
  {
    return PM_ERR_FLAG_SUCCESS;
  }

  /* Locate the TLMM protocol & then configure the GPIO 50 */
  if(EFI_SUCCESS != (Status = gBS->LocateProtocol( &gEfiTLMMProtocolGuid, NULL, (void**)&TLMMProtocol)))
  {
    pm_log_message("*** Locate TLMM Protocol Failed! ***\n");
  }
  
  /* Configure MSM GPIO and chip Enable */
  if (Status == EFI_SUCCESS)
  {
    config_LEA = EFI_GPIO_CFG( 7, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA );
    Status = TLMMProtocol->ConfigGpio((UINT32)config_LEA, TLMM_GPIO_ENABLE);
    if (Status != EFI_SUCCESS)
    {
      pm_log_message("*** Unable to Configure MSM GPIO 7! ***\n");
    }
  }

  if (Status == EFI_SUCCESS)
  {
    config_LEB = EFI_GPIO_CFG( 11, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA );
    Status = TLMMProtocol->ConfigGpio((UINT32)config_LEB, TLMM_GPIO_ENABLE);
    if (Status != EFI_SUCCESS)
    {
      pm_log_message("*** Unable to Configure MSM GPIO 11! ***\n");
    }
  }

  /* Drive LEICA_A EN pin low while keeping LEICA_B EN pin high */
  if (Status == EFI_SUCCESS)
  {
    Status = TLMMProtocol->GpioOut(config_LEA, GPIO_LOW_VALUE);
    if (Status != EFI_SUCCESS)
    {
      pm_log_message("*** Unable to drive Leica_A EN pin low ***\n");
    }
  }
  if (Status == EFI_SUCCESS)
  {
    Status = TLMMProtocol->GpioOut(config_LEB, GPIO_HIGH_VALUE);
    if (Status != EFI_SUCCESS)
    {
      pm_log_message("*** Unable to drive Leica_B EN pin high ***\n");
    }
  }

  gBS->Stall(1000); /* Wait for LEICA to power up, 1mS */

  i2c_slave_config  cfg = {
    .bus_frequency_khz          = 400,
    .slave_address              = 0x08,
    .mode                       = I2C,
    .slave_max_clock_stretch_us = 500,
    .core_configuration1        = 0,
    .core_configuration2        = 0
  };

  istatus = i2c_open(I2C_INSTANCE_006, &i2c_handle);

  if (istatus != I2C_SUCCESS)
  {
     pm_log_message("*** Failed to open i2c instance. (i2c status : %d) *** \n", istatus);
  }
  if ((istatus == I2C_SUCCESS) && (i2c_handle != NULL))
  {
    istatus |= i2c_write(i2c_handle, &cfg, 0, 0, packet_data, packet_size, &read_write_count, TIMEOUT_MAX);
  }

  /* Any error experienced should cause the boot to stop */
  if (istatus != I2C_SUCCESS)
  {
     pm_log_message("*** Failed to detect external I2C PMIC. PMIC is left at default state. (i2c status : %d) *** \n", istatus);
  }

  i2c_close(i2c_handle);

  return err_flag;
}
