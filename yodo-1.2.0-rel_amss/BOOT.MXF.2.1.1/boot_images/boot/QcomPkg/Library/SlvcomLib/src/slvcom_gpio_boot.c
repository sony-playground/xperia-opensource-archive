/*=============================================================================

                            SLVCOM GPIO TZ

 Slave Communication GPIO interface.

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/src/slvcom_gpio_boot.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "slvcom.h"
#include "slvcom_log.h"
#include "slvcom_os.h"
#include "slvcom_gpio.h"
#include "slvcom_cfg.h"
#include "DDITlmm.h"
#include "DALDeviceId.h"
#include <stdlib.h>

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
#undef  SLVCOM_LOG_TAG
#define SLVCOM_LOG_TAG "GPIO"

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                       LOCAL DATA DECLARATIONS

=============================================================================*/

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/


/*=============================================================================

                     LOCAL FUNCTION DEFINATION

=============================================================================*/


/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_gpio_init
=============================================================================*/
/**
 * Acquire the required GPIO. This takes the config for a given gpio
 * indicated by tlmm_str from config header file for each GPIO.
 *
 * @param[in] None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_gpio_init
(
  slvcom_gpio_id_type      gpio_id,
  slvcom_gpio_cfg_type    *gpio_cfg,
  slvcom_gpio_type       **ret_handle
)
{
  slvcom_gpio_type       *handle;
  DALResult              dRes;

  if (ret_handle == NULL || gpio_cfg == NULL)
  {
    return SLVCOM_ERR_INVALID_PARAM;
  }
  
  handle = slvcom_os_calloc(1, sizeof(slvcom_gpio_type));
  if (handle == NULL)
  {
    SLVCOM_LOG_ERR(1, "slvcom_os_calloc failed, size=%d.", sizeof(slvcom_gpio_type));
    return SLVCOM_ERR_OUT_OF_RESOURCES;
  }
  
  handle->id           = gpio_id;
  handle->dir          = gpio_cfg->dir;
  
  dRes = DAL_DeviceAttach(DALDEVICEID_TLMM, &handle->dal_gpio_handle);
  if(dRes != DAL_SUCCESS)
  {
      SLVCOM_LOG_ERR(1, "DAL_DeviceAttach with DALDEVICEID_TLMM failed with err=%d.", dRes);
      slvcom_os_free(handle);
      return SLVCOM_ERR_GPIO_ERR;
  }

  if(NULL == handle->dal_gpio_handle)
  {
      SLVCOM_LOG_ERR(0, "h_slvcom_tlmm_handle is NULL");
      slvcom_os_free(handle);
      return SLVCOM_ERR_GPIO_ERR;
  }
  
  dRes = DalDevice_Open(handle->dal_gpio_handle, DAL_OPEN_SHARED);
  if(dRes != DAL_SUCCESS)
  {
      SLVCOM_LOG_ERR(1, "DalDevice_Open failed with err=%d.", dRes);
      slvcom_os_free(handle);
      return SLVCOM_ERR_GPIO_ERR;
  }

  handle->slvcom_tlmm_config = DAL_GPIO_CFG(
     (uint32)gpio_id, 
      0, 
      DAL_GPIO_OUTPUT, 
      DAL_GPIO_NO_PULL,
      DAL_GPIO_2MA);

  dRes = DalTlmm_ConfigGpio(handle->dal_gpio_handle, handle->slvcom_tlmm_config, DAL_TLMM_GPIO_ENABLE);
  if(dRes != DAL_SUCCESS)
  {
    SLVCOM_LOG_ERR(1, "DalTlmm_ConfigGpio failed with err=%d.", dRes);
    slvcom_os_free(handle);
    return SLVCOM_ERR_GPIO_ERR;
  }

  *ret_handle = handle;
  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_tlmm_release
=============================================================================*/
/**
 * Makes calls to TLMM driver deinit function.
 *
 * @param[in] None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_gpio_deinit(slvcom_gpio_type *handle)
{
  DALResult  dRes;
  
  if (handle == NULL)
  {
    return SLVCOM_ERR_INVALID_PARAM;
  }
  
  dRes = DalTlmm_ConfigGpio(handle->dal_gpio_handle, handle->slvcom_tlmm_config, DAL_TLMM_GPIO_DISABLE);
  if(dRes != DAL_SUCCESS)
  {
    SLVCOM_LOG_ERR(1, "DalTlmm_ConfigGpio failed with err=%d.", dRes);
    //return SLVCOM_ERR_GPIO_ERR;    //no need to return as we want to deinit.. Todo: check once
  }
  
  dRes = DalDevice_Close(handle->dal_gpio_handle);
  if(dRes != DAL_SUCCESS)
  {
      SLVCOM_LOG_ERR(1, "DalDevice_Close failed with err=%d.", dRes);
      //return SLVCOM_ERR_GPIO_ERR;    //no need to return as we want to deinit.. Todo: check once
  }
  
  slvcom_os_free(handle);
  
  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_gpio_out
=============================================================================*/
/**
 * Configures the GPIO line with given settings.
 *
 * @param[in] gpio  - To indicate which gpio to be toggled
 * @param[in] level - To indicate High/Low level
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_gpio_out
(
  slvcom_gpio_type       *handle,
  slvcom_gpio_value_type  value
)
{
  DALResult  dRes;
  
  if (handle == NULL)
  {
    return SLVCOM_ERR_INVALID_PARAM;
  }
  
  dRes = DalTlmm_GpioOut(handle->dal_gpio_handle, handle->slvcom_tlmm_config, (DALGpioValueType)value);
  if(dRes != DAL_SUCCESS)
  {
    SLVCOM_LOG_ERR(1, "DalTlmm_GpioOut failed with err=%d.", dRes);
    return SLVCOM_ERR_GPIO_ERR;
  }
  
  return SLVCOM_ERR_NONE;
}

/*=============================================================================
  FUNCTION  slvcom_gpio_in
=============================================================================*/
/**
 * Reads the status on given GPIO pin
 *
 * @param[in] tlmm_id   - To indicate which gpio to be toggled
 * @param[out] level    - To indicate High/Low level
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_gpio_in
(
  slvcom_gpio_type        *handle,
  slvcom_gpio_value_type  *value
)
{
  return SLVCOM_ERR_NOT_SUPPORTED;
}

