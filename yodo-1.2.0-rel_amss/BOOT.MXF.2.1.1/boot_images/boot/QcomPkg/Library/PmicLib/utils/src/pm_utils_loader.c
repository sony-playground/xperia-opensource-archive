/*! \file
*
*  \brief  pm_utils_loader.c
*  &copy; Copyright 2016-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/src/pm_utils_loader.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/15/17   aab      Added pm_sbl_set_batt_id_forced_mode()
02/02/17   cs       SBL needs to do a fresh reading of batt id
08/03/16   akm      Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/

#include "DALSys.h"
#include "adc.h"
#include "busywait.h"
#include "boot_reset_if.h"

#include "pm_utils.h"
#include "pm_log_utils.h"

#include "pm_dump.h"
#include "pm_resource_manager.h"
#include "device_info.h"
#include "pm_target_information.h"
#include "pm_prop_ids.h"
#include "CoreVerify.h"
#include <WatchDogTimerLib.h>


pm_err_flag_type
pm_busy_wait(uint32 us)
{
  busywait(us);
  return PM_ERR_FLAG_SUCCESS;
}

void pm_watch_dog_pet(void)
{
  WatchDog_Pet();
}

pm_err_flag_type
pm_get_adc_code_of_battery_id(pm_adc_pull_up_type type, uint32 ohms, uint32* code)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  DALResult result = DAL_SUCCESS;
  AdcResultType adcResult;
  static boolean batt_id_channel_init = FALSE;
  static DalDeviceHandle *phAdcDev = NULL;
  static AdcInputPropertiesType adcInputProps;

  if(NULL == code || type >= PM_BATT_ID_PU_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(!batt_id_channel_init)
  {
    /* Attach to ADC */
    result = DAL_AdcDeviceAttach(DALDEVICEID_ADC, &phAdcDev);
    if(result != DAL_SUCCESS)
    {
      pm_log_message("ERROR: DAL_AdcDeviceAttach()");
      return err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }

    char *channel = NULL;
    uint32 chan_size;
    switch(type)
    {
    case PM_ADC_PU_30K:
      channel = ADC_INPUT_BATT_ID_OHMS_PU_30K;
      chan_size = sizeof(ADC_INPUT_BATT_ID_OHMS_PU_30K);
      break;
    case PM_ADC_PU_100K:
      channel = ADC_INPUT_BATT_ID_OHMS;
      chan_size = sizeof(ADC_INPUT_BATT_ID_OHMS);
      break;
    case PM_ADC_PU_400K:
      channel = ADC_INPUT_BATT_ID_OHMS_PU_400K;
      chan_size = sizeof(ADC_INPUT_BATT_ID_OHMS_PU_400K);
      break;
    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    /* Get the channel's input properties */
    result = DalAdc_GetAdcInputProperties(phAdcDev,
                            channel,
                            chan_size,
                            &adcInputProps);
    if(result != DAL_SUCCESS)
    {
      pm_log_message("ERROR: DalAdc_GetAdcInputProperties()");
      return PM_ERR_FLAG_PERIPHERAL_ERR;
    }

    batt_id_channel_init = TRUE;
  }

  result = DalAdc_ProcessConversionResultInverse(phAdcDev, &adcInputProps, ohms, &adcResult);
  if(result != DAL_SUCCESS)
  {
    pm_log_message("ERROR: DalAdc_Read()");
    return PM_ERR_FLAG_PERIPHERAL_ERR;
  }

  *code = adcResult.nCode;

  return err_flag;
}


void pm_log_message(const char* format, ...)
{
  char buffer[PM_STATUS_MSG_LEN] = "PM: ";
  va_list args = {0};

  va_start(args, format);
  vsnprintf(buffer + PM_STATUS_MSG_HEAD_LEN, PM_STATUS_MSG_LEN - PM_STATUS_MSG_HEAD_LEN, format, args);
  va_end(args);
  LogMsg(buffer);
}


pm_err_flag_type
pm_device_shutdown(void)
{
  boot_hw_powerdown();

  /*should not return*/
  return PM_ERR_FLAG_SUCCESS;
}
