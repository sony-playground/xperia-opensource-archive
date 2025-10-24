/**
  @file pcie_osal_uefi.c
  @brief Internal interface include file for the PCIe target specific
  configuration layer.

  This file contains definitions of constants, data structures, and
  interfaces that provide target specific configuration data.

*/
/*
===============================================================================

                             Edit History


   when       who     what, where, why
   --------   ---     ------------------------------------------------------------
   11/15/19   Yg      Ported to ADSP
   10/18/18   MK      Created

===============================================================================
                   Copyright (c) 2018 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include <stdarg.h>    
#include <stdio.h>     
#include <string.h>
#include "pcie_osal.h"
#include "pcie_host_log.h"
#include "pcie_cfg_types.h"
#include "pcie_host.h"
#include "DALDeviceId.h"
#include "DDIChipInfo.h"
#include "DDITlmm.h"
#include <api/boot/boot_logger.h>
#include <api/pmic/pm/pm_lib.h>
#include <api/systemdrivers/ClockBoot.h>
#include <api/systemdrivers/busywait.h> 
#include <Library/ArmLib.h> 

/** Max size of the log message */
#define PCIE_OSAL_LOG_BUFSIZE                    64

/** Temporary buffer for the log message */
static char pcierc_log_buffer[PCIE_OSAL_LOG_BUFSIZE];


void pcie_osal_log_msg(const char *fmt, ...)
{
    va_list arg_list;

    va_start (arg_list, fmt);

    memset (pcierc_log_buffer,0,PCIE_OSAL_LOG_BUFSIZE);
    va_start (arg_list, fmt);
    vsnprintf (pcierc_log_buffer, PCIE_OSAL_LOG_BUFSIZE, fmt, arg_list);
    va_end (arg_list);
    boot_log_message (pcierc_log_buffer);
}

void* pcie_osal_malloc (size_t size)
{
   return NULL;
}

void pcie_osal_free (void *ptr)
{
}

void* pcie_osal_malloc_aligned (size_t size, uint8 align)
{
   return NULL;
}

void pcie_osal_free_aligned (void *ptr)
{
//   FreePages (ptr, number of pages);
}

pcie_status_t pcie_ldo_op (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_pwr_rails_config_t *pwr_config, int enable)
{
    int i;

    for (i=0; i < pwr_config->num_ldos; i++)
    {
       if (enable == TRUE)
       {
          if (pm_ldo_sw_enable(pwr_config->ldo_cfg[i].pmic_chip, pwr_config->ldo_cfg[i].ldo_num, PM_ON, TRUE) != PM_ERR_FLAG_SUCCESS)
          {
             PCIE_HOST_LOG_ERROR("ON fail : L%d%c", pwr_config->ldo_cfg[i].ldo_num + 1, 'A' + pwr_config->ldo_cfg[i].pmic_chip);
             // return PCIE_ERROR;   Keep it commented until PMIC adds support on real chip
          }
       }
       // off is not really required
    }

    return PCIE_SUCCESS;
}



pcie_status_t pcie_disable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config)
{
   return PCIE_SUCCESS;
}

pcie_status_t pcie_enable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config)
{
   Clock_PCIEInit (clock_config->clk_idx, CLOCK_BOOT_PERF_NOMINAL); 

   return PCIE_SUCCESS;
}

/*******************************************************************************
 * GPIO related
********************************************************************************/
static DalDeviceHandle           *TLMMHandle = NULL;

pcie_status_t pcie_osal_gpio_set (uint32 pin, boolean level)
{
   DALGpioSignalType   dal_gpio_config     = 0;
   DALResult eStatus;

   dal_gpio_config = (DALGpioSignalType)DAL_GPIO_CFG(pin, 0, 0, 0, 0);  // WARNING: Verify if this doesn't mess up

   eStatus = DalTlmm_GpioOut(TLMMHandle, dal_gpio_config, level);
   if (eStatus != DAL_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set GPIO failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_osal_init_gpio(const pcie_gpio_cfg_t *gpio_cfg)
{
    DALGpioSignalType   dal_gpio_config     = 0;
    const tlmm_gpio_cfg_t *tlmm_cfg;
    DALResult eStatus;
  
    if (gpio_cfg == NULL)
        return PCIE_SUCCESS;

    if (TLMMHandle == NULL)
	{
	    eStatus = DAL_DeviceAttach(DALDEVICEID_TLMM, &TLMMHandle);     
        if(eStatus != DAL_SUCCESS)
            return(PCIE_ERROR);
    }
  
    switch (gpio_cfg->cfg_type)
    {
       case MSM_GPIO:
           tlmm_cfg = &gpio_cfg->pcie_pin.tlmm;
           dal_gpio_config = (DALGpioSignalType)DAL_GPIO_CFG(tlmm_cfg->gpio_num, tlmm_cfg->func_sel, tlmm_cfg->direction, tlmm_cfg->pull, tlmm_cfg->drive_strength);

           eStatus = DalTlmm_ConfigGpio(TLMMHandle, dal_gpio_config, DAL_TLMM_GPIO_ENABLE);
           if (eStatus != DAL_SUCCESS)
               return PCIE_ERROR;

           if (tlmm_cfg->value != 0)
               eStatus = DalTlmm_GpioOut(TLMMHandle,dal_gpio_config, tlmm_cfg->value);
           break;

       case DELAY:
           busywait(gpio_cfg->pcie_pin.delay_us);
           break;

       default:
          break;
    }

    return PCIE_SUCCESS;
}

pcie_status_t pcie_initialize_gpios (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_gpio_cfg_t *gpio_cfg)
{
   EFI_STATUS Status = EFI_DEVICE_ERROR;
   int i;

   if ((gpio_cfg == NULL) || (rsrc_ctxt == NULL))
      return PCIE_ERROR;

   if (rsrc_ctxt->gpio_initialized == TRUE)
      return PCIE_SUCCESS;

   for (i = 0; gpio_cfg[i].cfg_type != NONE; ++i)
   {
      Status = pcie_osal_init_gpio (&gpio_cfg[i]);

      if (Status != EFI_SUCCESS)
         break;
   }

   if (Status == EFI_SUCCESS)
      rsrc_ctxt->gpio_initialized = TRUE;

   return PCIE_SUCCESS;
}

pcie_status_t enable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pwr_rails_cfg, ENABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn ON ldos\n");
      return PCIE_ERROR;
   }

   res = pcie_enable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg);
   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock init failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t disable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   res = pcie_disable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg);
   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock deinit failed\n");
      return PCIE_ERROR;
   }

   if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pwr_rails_cfg, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF ldos\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}


