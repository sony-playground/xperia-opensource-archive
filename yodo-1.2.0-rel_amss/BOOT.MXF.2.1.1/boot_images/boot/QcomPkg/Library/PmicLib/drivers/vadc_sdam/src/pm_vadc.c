/*============================================================================
  FILE:         pm_vadc.c

  OVERVIEW:     Implementation of a Physical ADC device DAL for the
                PMIC VADC peripheral.

  DEPENDENCIES: None

                Copyright (c) 2009-2016, 2018-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc_sdam/src/pm_vadc.c#2 $$DateTime: 2022/09/06 16:40:40 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2019-09-09  rh   Split low level vadc read into pm driver
  2018-02-06  jjo  Enhance RUMI check.
  2018-01-31  jjo  Remove latency vote.
  2016-03-23  jjo  Add HW supported checks.
  2015-08-12  jjo  Updated for VADC refresh.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "pm_vadc.h"
#include "VAdcBsp.h"
#include "VAdcHal.h"
#include "pm_comm.h"

#ifndef ADC_BOOT_DRIVER
#include "DALFramework.h"
#include "DalDevice.h"
#include "timer.h"
#else
#include "busywait.h"
#endif


/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/* Logging function wrappers */
#define VAdc_LogEOC(x)                 {if(pDevCtxt->log.EOC != NULL)(pDevCtxt->log.EOC)(x);}
#define VAdc_LogError(x,y,z)           {if(pDevCtxt->log.Error != NULL)(pDevCtxt->log.Error)(x,y,z);}
#define VAdc_LogInterrupt(x)           {if(pDevCtxt->log.Interrupt != NULL)(pDevCtxt->log.Interrupt)(x);}
#define VAdc_LogDumpRegisters(x,y)     {if(pDevCtxt->log.DumpRegisters != NULL)(pDevCtxt->log.DumpRegisters)(x,y);}

#define VADC_MAX_NUM_DEV    8   /* Number of PMICs using ADCTM */

#ifndef ADC_BOOT_DRIVER
#define SYNC_ENTER()       DALSYS_SyncEnter (ghSyncDevice)
#define SYNC_LEAVE()       DALSYS_SyncLeave (ghSyncDevice)
#else
#define SYNC_ENTER() 
#define SYNC_LEAVE()
#endif

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
struct pm_vadc_device 
{
   VAdcHalInterfaceType iVAdcHalInterface;          /* VADC HAL interface */
   const VAdcBspType *pBsp;                         /* pointer to the BSP */
#ifndef ADC_BOOT_DRIVER
   DALSYSEventHandle ahEocEvent[_VADC_NUM_EVENTS];  /* end-of-conversion event - EOC signal & a timeout */
#endif
   struct pm_vadc_log_inf log;
   VAdcDebugInfoTypeLoc *debug;
};

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/
struct pm_vadc_device g_vadc_device_ctxt[VADC_MAX_NUM_DEV];
static uint32 g_vadc_device_ctxt_idx = 0;
// Switch to pointer and dynamically allocate the structure off heap
#ifndef ADC_BOOT_DRIVER
static DALSYS_SYNC_OBJECT(syncObject);

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
DALSYSSyncHandle ghSyncDevice;
#endif

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*======================================================================

  FUNCTION        pm_vadc_start_conversion

  DESCRIPTION     This function starts the ADC conversion

  DEPENDENCIES    None

  PARAMETERS
      pDevCtxt          [in] pointer to the VADC device context
      pChConfig         [in] the channel configuration
      puConvTime_us     [out] conversion time

  RETURN VALUE    DAL_SUCCESS or an error code

  SIDE EFFECTS    DAL_SUCCESS if conversion was started successfully
                  Otherwise, returns a DAL error code.

======================================================================*/
pm_err_flag_type
pm_vadc_start_conversion (struct pm_vadc_device *pDevCtxt,
                          const pm_vadc_channel_cfg *pChConfig,
                          uint32 *puConvTime_us)
{
   VAdcConversionParametersType conversionParams;
   pm_err_flag_type result;
#ifndef ADC_BOOT_DRIVER
   DALResult ret;
#endif

#ifndef ADC_BOOT_DRIVER
   /* Reset the EOC events prior to starting the conversion */
   ret = DALSYS_EventCtrl(pDevCtxt->ahEocEvent[VADC_EVENT_DEFAULT],
                          DALSYS_EVENT_CTRL_RESET);
   if (ret != DAL_SUCCESS)
   {
      return PM_ERR_FLAG_OS_ERR;
   }

   ret = DALSYS_EventCtrl(pDevCtxt->ahEocEvent[VADC_EVENT_TIMEOUT],
                          DALSYS_EVENT_CTRL_RESET);
   if (ret != DAL_SUCCESS)
   {
      return PM_ERR_FLAG_OS_ERR;
   }
#endif

   /* Initialize conversion parameter variables */
   conversionParams.uChannel = pChConfig->uChannel;
   conversionParams.eCalMethod = pChConfig->eCalMethod;
   conversionParams.eDecimationRatio = pChConfig->eDecimationRatio;
   conversionParams.eAverageMode = pChConfig->eAverageMode;
   conversionParams.eSettlingDelay = pChConfig->eSettlingDelay;
   conversionParams.uSid = pChConfig->uAdcSID;

   /* ADC PMIC 5 Gen 3 access common config register within CS */
   SYNC_ENTER();
   result = VAdcHalRequestConversion(&pDevCtxt->iVAdcHalInterface,
                                     &conversionParams,
                                     puConvTime_us);
   SYNC_LEAVE();
   return result;
}

/*======================================================================

  FUNCTION        pm_vadc_wait_eoc

  DESCRIPTION
      This function waits for the EOC and gets the conversion status.

  DEPENDENCIES
      None

  PARAMETERS
      pDevCtxt     [in]
      pChConfig    [in]
      uConvTime_us [in]

  RETURN VALUE
      DAL_SUCCESS or an error

  SIDE EFFECTS
      Be careful not to make the wait time too small or EOC may
      time out too early.

======================================================================*/
static pm_err_flag_type
pm_vadc_eoc_clear (struct pm_vadc_device *pDevCtxt, 
                   const pm_vadc_channel_cfg *pChConfig)
{
   SYNC_ENTER();
   pm_err_flag_type status = VAdcHalClearEoc (&pDevCtxt->iVAdcHalInterface, 0);
   SYNC_LEAVE();
   return status;
}

pm_err_flag_type
pm_vadc_wait_eoc (struct pm_vadc_device *pDevCtxt,
                  const pm_vadc_channel_cfg *pChConfig,
                  uint32 uConvTime_us)
{
   uint32 uReadTimeout_us = pDevCtxt->pBsp->uReadTimeout_us;
   VAdcStatusType convStatus;
   pm_err_flag_type status = PM_ERR_FLAG_FAILURE;
   uint32 uTimeWaited_us;
   uint32 uReadTime_us;
   struct pm_vadc_reg_dump rd = { .vadc_regs = NULL, 
                                  .reg_size  = 0
                                };

#ifndef ADC_BOOT_DRIVER
   DALResult result;
   uint32 uEventIdx;
#endif

   uReadTime_us = uConvTime_us + pDevCtxt->pBsp->uLDOSettlingTime_us;

#ifndef ADC_BOOT_DRIVER
   if (pDevCtxt->pBsp->bUsesInterrupts)
   {
      result = DALSYS_EventMultipleWait(pDevCtxt->ahEocEvent,
                                        _VADC_NUM_EVENTS,
                                        uReadTimeout_us,
                                        &uEventIdx);
      if (result != DAL_SUCCESS && result != DAL_ERROR_TIMEOUT)
      {
         return PM_ERR_FLAG_INVALID_PERIPHERAL;
      }

      if (result == DAL_ERROR_TIMEOUT)
      {
         VAdc_LogError(pDevCtxt->debug, "VAdc - missed interrupt", FALSE);
         VAdcHalDumpRegisters(&pDevCtxt->iVAdcHalInterface, (VAdcHalRegDumpType *)&rd);
         VAdc_LogDumpRegisters(pDevCtxt->debug, &rd);
      }

      status = VAdcHalGetStatus(&pDevCtxt->iVAdcHalInterface, &convStatus);
      if (status != PM_ERR_FLAG_SUCCESS)
      {
         return status;
      }

      if (convStatus.eConversionStatus == VADC_CONVERSION_STATUS_COMPLETE)
      {
         VAdc_LogEOC(pDevCtxt->debug);
         return pm_vadc_eoc_clear (pDevCtxt, pChConfig);  
      }
   }
   else
#endif
   {
      uTimeWaited_us = 0;

      while (uTimeWaited_us < uReadTimeout_us)
      {
#ifndef ADC_BOOT_DRIVER
         timer_sleep(uReadTime_us, T_USEC, TRUE);
#else
         busywait(uReadTime_us);
#endif
         status = VAdcHalGetStatus(&pDevCtxt->iVAdcHalInterface, &convStatus);
         if (status != PM_ERR_FLAG_SUCCESS)
         {
            return status;
         }

         if (convStatus.eConversionStatus == VADC_CONVERSION_STATUS_COMPLETE)
         {
            pm_vadc_eoc_clear (pDevCtxt, pChConfig);
            VAdc_LogEOC(pDevCtxt->debug);
            return PM_ERR_FLAG_SUCCESS;
         }

         if (uTimeWaited_us == 0)
         {
            uTimeWaited_us += uReadTime_us;

            /* Only wait the full read time for the first try and
               then poll at a faster rate */
            uReadTime_us = uReadTime_us / 5;
         }
         else
         {
            uTimeWaited_us += uReadTime_us;
         }
      }
   }

   /* Conversion did not complete */
   VAdc_LogError(pDevCtxt->debug, "VAdc - conversion timed out", FALSE);
   VAdcHalDumpRegisters(&pDevCtxt->iVAdcHalInterface, (VAdcHalRegDumpType *)&rd);
   VAdc_LogDumpRegisters(pDevCtxt->debug, &rd);

   return PM_ERR_FLAG_FAILURE;
}

/*======================================================================

  FUNCTION        pm_vadc_read_adc_code

  DESCRIPTION
      This function reads the ADC result.

  DEPENDENCIES
      None

  PARAMETERS
      pDevCtxt [in]
      puCode   [out]

  RETURN VALUE
      DAL_SUCCESS or an error

  SIDE EFFECTS
      None

======================================================================*/
pm_err_flag_type
pm_vadc_read_adc_code (struct pm_vadc_device *pDevCtxt, int32 *puCode)
{
   pm_err_flag_type result;
   uint32 uCode;

   result = VAdcHalGetConversionCode(&pDevCtxt->iVAdcHalInterface, &uCode);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   if (uCode == VADC_INVALID_ADC_CODE)
   {
      /* After every peripheral disable the data registers are set to an invalid code */
      VAdc_LogError(pDevCtxt->debug, "VAdc - invalid ADC code read", FALSE);
      return PM_ERR_FLAG_INVALID_PERIPHERAL;
   }

   *puCode = ((int16)uCode);

   return PM_ERR_FLAG_SUCCESS;
}

/*======================================================================

  FUNCTION        pm_vadc_read_adc

  DESCRIPTION
      This function reads an ADC channel.

  DEPENDENCIES
      None

  PARAMETERS
      pDevCtxt    [in]
      pChConfig   [in]
      puCode      [out]

  RETURN VALUE
      DAL_SUCCESS or an error

  SIDE EFFECTS
      None

======================================================================*/
pm_err_flag_type
pm_vadc_read_adc (struct pm_vadc_device *pDevCtxt,
                  const pm_vadc_channel_cfg *pChConfig,
                  uint32 *puCode)
{
   pm_err_flag_type status;
   pm_err_flag_type result;
   uint32 uConvTime_us;
   struct pm_vadc_reg_dump rd = { .vadc_regs = NULL, 
                                  .reg_size  = 0
                                }; 

   result = pm_vadc_start_conversion(pDevCtxt, pChConfig, &uConvTime_us);

   if (result != PM_ERR_FLAG_SUCCESS)
   {
      goto error;
   }

   result = pm_vadc_wait_eoc(pDevCtxt, pChConfig, uConvTime_us);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      goto error;
   }

   result = pm_vadc_read_adc_code(pDevCtxt, (int32 *)puCode);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      goto error;
   }

#ifdef VADC_DUMP_REGISTERS_AFTER_READS
   VAdcHalDumpRegisters(&pDevCtxt->iVAdcHalInterface, (VAdcHalRegDumpType *)&rd);
   VAdc_LogDumpRegisters(pDevCtxt->debug, &rd);
#endif

   status = VAdcHalSetEnable(&pDevCtxt->iVAdcHalInterface, VADC_DISABLE);
   return status;

error:
   VAdcHalDumpRegisters(&pDevCtxt->iVAdcHalInterface, (VAdcHalRegDumpType *)&rd);
   VAdc_LogDumpRegisters(pDevCtxt->debug, &rd);
   (void)VAdcHalSetEnable(&pDevCtxt->iVAdcHalInterface, VADC_DISABLE);
   return result;
}


/*======================================================================

  FUNCTION        pm_vadc_interrupt_cb

  DESCRIPTION
      This function is the callback to process the conversion complete
      interrupt from the arbiter. It sets the EOC signal.

  DEPENDENCIES    None

  PARAMETERS
      pArg            [in]
      uIntrStatusMask [in]

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
#ifndef ADC_BOOT_DRIVER
static void* 
pm_vadc_interrupt_cb (void *pArg, uint32 uIntrStatusMask)
{
   struct pm_vadc_device *pDevCtxt = (struct pm_vadc_device *)pArg;
   DALResult result;
   pm_err_flag_type status;

   VAdc_LogInterrupt(pDevCtxt->debug);

   /* Clear all pending interrupts */
   status = VAdcHalClearInterrupts(&pDevCtxt->iVAdcHalInterface, VADC_INT_MASK_EOC);
   if (status != PM_ERR_FLAG_SUCCESS)
   {
      VAdc_LogError(pDevCtxt->debug, "VAdc - failed to clear EOC interrupt", FALSE);
   }

   /* Set the EOC signal */
   result = DALSYS_EventCtrlEx(pDevCtxt->ahEocEvent[VADC_EVENT_DEFAULT],
                               DALSYS_EVENT_CTRL_TRIGGER,
                               0,
                               NULL,
                               0);
   if (result != DAL_SUCCESS)
   {
      VAdc_LogError(pDevCtxt->debug, "VAdc - failed to set EOC signal", FALSE);
   }

   return NULL;
}

static DALResult 
pm_vadc_sync_object_init (struct pm_vadc_device *pDevCtxt)
{
   static boolean bSyncObjInit = FALSE;
   DALResult ret = DAL_SUCCESS;

   if (!bSyncObjInit)
   {
      ret = DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, 
                              &ghSyncDevice, 
                              &syncObject);

      if (ret != DAL_SUCCESS)
      {
         VAdc_LogError(pDevCtxt->debug, "VAdc - failed to create the sync object", TRUE);
         return DAL_ERROR;
      }
      bSyncObjInit = TRUE;
   }

   return ret;
}

#endif

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
pm_err_flag_type 
pm_vadc_device_init (struct pm_vadc_device **ppDevCtxt, const VAdcBspType *pBsp)
{
   struct pm_vadc_device *pDevCtxt;
   pm_err_flag_type status;
#ifndef ADC_BOOT_DRIVER
   DALResult ret;
   VAdcInterruptConfigType eInterruptConfig;
#endif

   if (g_vadc_device_ctxt_idx >= VADC_MAX_NUM_DEV) 
   {
      /* Out of available Ctxt */
      return PM_ERR_FLAG_FAILURE;
   }

   pDevCtxt = &g_vadc_device_ctxt[g_vadc_device_ctxt_idx];
   g_vadc_device_ctxt_idx++;
   *ppDevCtxt = pDevCtxt;

   /* Initialize the HAL interface */
   pDevCtxt->iVAdcHalInterface.spmi_peripheral_id = pBsp->uPeripheralId;
   pDevCtxt->iVAdcHalInterface.spmi_slave_id = pBsp->uSlaveId;
   pDevCtxt->iVAdcHalInterface.spmi_bus_id = pBsp->uBusId;
   pDevCtxt->pBsp = pBsp;

   status = VAdcHalGetRevisionInfo(&pDevCtxt->iVAdcHalInterface);
   if (status != PM_ERR_FLAG_SUCCESS)
   {
      return status;
   }

#ifndef ADC_BOOT_DRIVER
   /* ADC PMIC 5 Gen 3 - Init shared lock to access common config registers */
   if (DAL_SUCCESS != (ret = pm_vadc_sync_object_init (pDevCtxt)))
   {
      return PM_ERR_FLAG_OS_ERR;
   }

   if (pDevCtxt->pBsp->bUsesInterrupts)
   {
      status = pm_comm_register_isr(pBsp->uSlaveId,
                                    (pBsp->uPeripheralId << 8),
                                    VADC_INT_MASK_EOC,
                                    pm_vadc_interrupt_cb,
                                    (uint32)pDevCtxt);
      if (status != PM_ERR_FLAG_SUCCESS)
      {
         VAdc_LogError(pDevCtxt->debug, "VAdc - failed to register ISR", TRUE);
         return status;
      }

      /* Configure peripheral interrupts */
      eInterruptConfig = VADC_INTERRUPT_CONFIG_RISING_EDGE;

      status = VAdcHalConfigInterrupts(&pDevCtxt->iVAdcHalInterface,
                                       VADC_INT_MASK_EOC,
                                       eInterruptConfig);

      if (status != PM_ERR_FLAG_SUCCESS)
      {
         return status;
      }

      status = VAdcHalSetInterruptMid(&pDevCtxt->iVAdcHalInterface,
                                      pDevCtxt->pBsp->uMasterID);
      if (status != PM_ERR_FLAG_SUCCESS)
      {
         return status;
      }

      status = VAdcHalClearInterrupts(&pDevCtxt->iVAdcHalInterface,
                                      VADC_INT_MASK_EOC);
      if (status != PM_ERR_FLAG_SUCCESS)
      {
         return status;
      }

      status = VAdcHalEnableInterrupts(&pDevCtxt->iVAdcHalInterface,
                                       VADC_INT_MASK_EOC);
      if (status != PM_ERR_FLAG_SUCCESS)
      {
         return status;
      }
   }

   /* Configure the EOC event & timeout event */
   ret = DALSYS_EventCreate(DALSYS_EVENT_ATTR_CLIENT_DEFAULT,
                            &pDevCtxt->ahEocEvent[VADC_EVENT_DEFAULT],
                            NULL);
   if (ret != DAL_SUCCESS)
   {
      VAdc_LogError(pDevCtxt->debug, "VAdc - failed to create the EOC event", TRUE);
      return PM_ERR_FLAG_OS_ERR;
   }

   ret = DALSYS_EventCreate(DALSYS_EVENT_ATTR_TIMEOUT_EVENT,
                            &pDevCtxt->ahEocEvent[VADC_EVENT_TIMEOUT],
                            NULL);
   if (ret != DAL_SUCCESS)
   {
      VAdc_LogError(pDevCtxt->debug, "VAdc - failed to create the EOC timeout event", TRUE);
      return PM_ERR_FLAG_OS_ERR;
   }
#endif
   pDevCtxt->log.EOC = NULL;
   pDevCtxt->log.Error = NULL;
   pDevCtxt->log.Interrupt = NULL;
   pDevCtxt->log.DumpRegisters = NULL;

   return PM_ERR_FLAG_SUCCESS;
}


/* Register log interface */
void 
pm_vadc_register_log_inf(struct pm_vadc_device *pDevCtxt,
                         struct pm_vadc_log_inf *pLogInf)
{
   pDevCtxt->debug = pLogInf->debugCtxt;
   pDevCtxt->log.EOC = pLogInf->EOC;
   pDevCtxt->log.Error = pLogInf->Error;
   pDevCtxt->log.Interrupt = pLogInf->Interrupt;
   pDevCtxt->log.DumpRegisters = pLogInf->DumpRegisters;
}

