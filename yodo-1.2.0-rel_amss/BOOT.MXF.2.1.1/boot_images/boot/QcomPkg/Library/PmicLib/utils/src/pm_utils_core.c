/*! \file
*  
*  \brief  pm_utils_core.c 
*  
*  &copy; Copyright 2016-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/src/pm_utils_core.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/03/16   akm      Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SerialPortShLib.h>
#include <Library/TimerLib.h>
#include <Library/KernelLib.h>

#include "pm_utils.h"
#include "SpmiBus.h"
#include "SpmiCfg.h"
#include "SpmiBusCfg.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_dt_parser.h"

#include <Include/scm_sip_interface.h>
#include <Library/BootConfig.h>
#include <Protocol/EFIScm.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "pm_log_utils.h"
#include <stdarg.h>

#define INT_LATCHED_CLR_OFFSET 0x0014
#define INT_EN_CLR_OFFSET      0x0016
#define INT_CLEAR_VAL          0xFF
#define BROADCAST_SLAVE_ID     14

void pm_watch_dog_pet(void)
{
  WatchDogForcePet();
}

pm_err_flag_type pm_busy_wait(uint32 req_wait_usec)
{
  uint32 actual_wait_usec = 0;
	
  /*the MicroSecondDelay API returns wait_usec as return value*/
  actual_wait_usec = MicroSecondDelay(req_wait_usec);

  if(actual_wait_usec < req_wait_usec)
  {
   return PM_ERR_FLAG_INVALID_PARAMETER; 
  }
  else
  {
    return PM_ERR_FLAG_SUCCESS;
  }
	
}

pm_err_flag_type 
pm_device_shutdown(void)
{
  /*flush UART before shutdown*/
  SerialPortFlush();
  gRT->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
  /*control should not return from here*/
  return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
}

extern EFI_GUID gQcomScmProtocolGuid;
static QCOM_SCM_PROTOCOL *ScmProtocol = NULL;

/*
 * Revoke SMMU access for UEFI accessible peripherals
 */
pm_err_flag_type
pm_revoke_channel_access(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  SpmiCfg_ChannelCfg *spmi_cfg_ptr      = NULL;
  uint32 spmi_cfg_size = 0;
  uint32 i = 0;
  uint16 channel = 0;
  uint32 version = 0x10000;

  EFI_STATUS status;
  UINT64 parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64 results[SCM_MAX_NUM_RESULTS] = {0};


  /*Locate QCOM_SCM_PROTOCOL.*/
  status = gBS->LocateProtocol(&gQcomScmProtocolGuid, NULL,
                               (VOID **)&ScmProtocol);

  if (EFI_SUCCESS != status)
  {
    return err_flag;
  }

  err_flag = pm_utils_get_spmi_channels(&spmi_cfg_ptr, &spmi_cfg_size);

  for(i = 0; i < spmi_cfg_size; i++)
  { 
    /*if periph and irq Ownermask is APPS and slave id and not broadcast*/
    if(spmi_cfg_ptr[i].periphOwnerMask == SPMI_OWNER_UEFI)
    {
      if (SpmiBus_GetChannel(spmi_cfg_ptr[i].busId, (uint8)spmi_cfg_ptr[i].slaveId, (uint8)spmi_cfg_ptr[i].periphId, &channel) != SPMI_SUCCESS)
      {
        continue;
      }

      parameters[0] = 0;
      parameters[1] = channel;
      parameters[2] = version;
      status = ScmProtocol->ScmSipSysCall(ScmProtocol, TZ_SPMI_REVOKE_ACCESS_ID,TZ_SPMI_REVOKE_ACCESS_PARAM_ID,
                                      parameters, results);
    }
  }

  return err_flag;
}



pm_err_flag_type
pm_utils_irq_disable_clr_all(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  SpmiCfg_ChannelCfg *spmi_cfg_ptr      = NULL;
  uint32 spmi_cfg_size = 0;
  uint32 periph_base_address = 0x0;
  uint32 i = 0;

  err_flag = pm_utils_get_spmi_channels(&spmi_cfg_ptr, &spmi_cfg_size);

  for(i = 0; i < spmi_cfg_size; i++)
  { 
    /*if periph and irq Ownermask is APPS and slave id and not broadcast*/
    if((spmi_cfg_ptr[i].periphOwnerMask & SPMI_OWNER_APPS)
       && (spmi_cfg_ptr[i].irqOwnerMask & SPMI_OWNER_APPS)
       && (spmi_cfg_ptr[i].slaveId != BROADCAST_SLAVE_ID)
       )
    {
      periph_base_address = spmi_cfg_ptr[i].periphId * 0x100;
      if(periph_base_address != 0x800) //temp changes not the clear PON peripheral irq
      {
        err_flag |= pm_comm_write_byte(spmi_cfg_ptr[i].slaveId, periph_base_address + INT_EN_CLR_OFFSET, INT_CLEAR_VAL);
        err_flag |= pm_comm_write_byte(spmi_cfg_ptr[i].slaveId, periph_base_address + INT_LATCHED_CLR_OFFSET, INT_CLEAR_VAL);
      }
    }
  }
  /*clear all SPMI irq*/
  err_flag |=  pm_comm_spmi_irq_clear_all();

  return err_flag;
}

void pm_log_message(const char* format, ...)
{
  char buffer[PM_STATUS_MSG_LEN] = "PM: ";
  va_list args = {0};

  va_start(args, format);
  vsnprintf(buffer + PM_STATUS_MSG_HEAD_LEN, PM_STATUS_MSG_LEN - PM_STATUS_MSG_HEAD_LEN, format, args);
  va_end(args);DEBUG((EFI_D_WARN, buffer)); 
  DEBUG((EFI_D_WARN, "\r\n"));
}
