/*=============================================================================

                            XRC GPIO

Methods for polling H2A_INT.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#include "xrc_gpio.h"
#include "xrc_log.h"
#include "xrc_os.h"
#include "xrc_types.h"
#include "boot_timer_if.h"

#define XRC_TLMM_H2A_INT_NUM 30

xrc_gpio_type       *g_xrc_gpio_h2a_handle = NULL;

/*====================================================================================================================
 FUNCTION: xrc_gpio_h2a_init
====================================================================================================================*/
/**
* DESCRIPTION: 
* Configures the TLMM to read/poll on a specific GPIO (H2A_INT)
*
* INPUT PARAMETERS:
* gpio_id: GPIO number
* gpio_cfg: Configuration of GPIO
* ret_handle: Handle to DAL GPIO
* RETURN VALUE: 
* SUCCESS if the configuration is done.
* Otherwise returns error code (see status_codes enumeration).
*/
/*====================================================================================================================*/

status_codes xrc_gpio_h2a_init
( 
	xrc_gpio_id_type      gpio_id,
  	xrc_gpio_cfg_type    *gpio_cfg,
	xrc_gpio_type       **ret_handle
) 
{
	xrc_gpio_type	   *handle;
	DALResult			   dRes;
	
	if (ret_handle == NULL || gpio_cfg == NULL)
	{
	  return FAIL_INVALID_PARAM;
	}
	
	handle = xrc_os_malloc(sizeof(xrc_gpio_type));
	if (handle == NULL)
	{
	  XRC_LOG_ERR(1, "xrc_os_malloc failed, size=%d.", sizeof(xrc_gpio_type));
	  return FAIL_MEM_ALLOC;
	}
	
	handle->id			 = gpio_id;
	handle->dir 		 = gpio_cfg->dir;
	
	dRes = DAL_DeviceAttach(DALDEVICEID_TLMM, &handle->dal_gpio_handle);
	if(dRes != DAL_SUCCESS)
	{
		XRC_LOG_ERR(1, "DAL_DeviceAttach with DALDEVICEID_TLMM failed with err=%d.", dRes);
		xrc_os_free(handle);
		return FAIL_GPIO_ERR;
	}
	
	if(NULL == handle->dal_gpio_handle)
	{
		XRC_LOG_ERR(0, "h_xrc_tlmm_handle is NULL");
		xrc_os_free(handle);
		return FAIL_GPIO_ERR;
	}
	
	dRes = DalDevice_Open(handle->dal_gpio_handle, DAL_OPEN_SHARED);
	if(dRes != DAL_SUCCESS)
	{
		XRC_LOG_ERR(1, "DalDevice_Open failed with err=%d.", dRes);
		xrc_os_free(handle);
		return FAIL_GPIO_ERR;
	}
	
	handle->xrc_tlmm_config = DAL_GPIO_CFG(
	   (uint32)gpio_id, 
		0, 
		DAL_GPIO_INPUT, 
		DAL_GPIO_NO_PULL,
		DAL_GPIO_2MA);
	
	dRes = DalTlmm_ConfigGpio(handle->dal_gpio_handle, handle->xrc_tlmm_config, DAL_TLMM_GPIO_ENABLE);
	if(dRes != DAL_SUCCESS)
	{
	  XRC_LOG_ERR(1, "DalTlmm_ConfigGpio failed with err=%d.", dRes);
	  xrc_os_free(handle);
	  return FAIL_GPIO_ERR;
	}
	
	*ret_handle = handle;
	return SUCCESS;


}


/*=============================================================================
  FUNCTION  xrc_gpio_deinit
=============================================================================*/
/**
 * Makes calls to TLMM driver deinit function.
 *
 * @param[in] handle: Handle to GPIO
 *
 * @return
 * SUCCESS if the deinit is done.
 * Otherwise returns error code (see status_codes enumeration).
 *
 */
/*===========================================================================*/
status_codes xrc_gpio_deinit(xrc_gpio_type *handle)
{
  DALResult  dRes;
  
  if (handle == NULL)
  {
    return FAIL_INVALID_PARAM;
  }
  
  dRes = DalTlmm_ConfigGpio(handle->dal_gpio_handle, handle->xrc_tlmm_config, DAL_TLMM_GPIO_DISABLE);
  if(dRes != DAL_SUCCESS)
  {
    XRC_LOG_ERR(1, "DalTlmm_ConfigGpio failed with err=%d.", dRes);
  }
  
  dRes = DalDevice_Close(handle->dal_gpio_handle);
  if(dRes != DAL_SUCCESS)
  {
      XRC_LOG_ERR(1, "DalDevice_Close failed with err=%d.", dRes);
  }
  
  xrc_os_free(handle);
  
  return SUCCESS;
}

/*=============================================================================
  FUNCTION  xrc_gpio_out
=============================================================================*/
/**
 * Configures the GPIO line with given settings.
 *
 * @param[in] gpio  - To indicate which gpio to be toggled
 * @param[in] level - To indicate High/Low level
 *
 * @return
 * SUCCESS if function is successful,
 * Otherwise returns error code (see status_codes enumeration).
 *
 */
/*===========================================================================*/
status_codes xrc_gpio_out
(
  xrc_gpio_type       *handle,
  xrc_gpio_value_type  value
)
{
  DALResult  dRes;
  
  if (handle == NULL)
  {
    return FAIL_INVALID_PARAM;
  }
  
  dRes = DalTlmm_GpioOut(handle->dal_gpio_handle, handle->xrc_tlmm_config, (DALGpioValueType)value);
  if(dRes != DAL_SUCCESS)
  {
    XRC_LOG_ERR(1, "DalTlmm_GpioOut failed with err=%d.", dRes);
    return FAIL_GPIO_ERR;
  }
  
  return SUCCESS;
}

/*=============================================================================
  FUNCTION  xrc_gpio_in
=============================================================================*/
/**
 * Reads the status on given GPIO pin
 *
 * @param[in] tlmm_id   - To indicate which gpio to be toggled
 * @param[out] level    - To indicate High/Low level
 *
 * @return
 * SUCCESS if function is successful,
 * Otherwise returns error code (see status_codes enumeration).
 *
 */
/*===========================================================================*/
status_codes xrc_gpio_in
(
  xrc_gpio_type        *handle,
  xrc_gpio_value_type  *value
)

{
	DALResult  dRes;
	
	if (handle == NULL || value == NULL)
	{
	  return FAIL_INVALID_PARAM;
	}

		
	dRes = DalTlmm_GpioIn(handle->dal_gpio_handle, handle->xrc_tlmm_config, (DALGpioValueType *)value);

	if(dRes != DAL_SUCCESS)
	{
	  XRC_LOG_ERR(1, "DalTlmm_GpioIn failed with err=%d.", dRes);
	  return FAIL_GPIO_ERR;
	}
	
	return SUCCESS;

}

/*====================================================================================================================
 FUNCTION: xrc_gpio_poll_high
======================================================================================================================*/
/** DESCRIPTION: 
* Poll periodically with a given frequency on the H2A_INT line, until the timeout. 
*
* INPUT PARAMETERS:
* poll_time_out: Time out in milliseconds.
* poll_frequency: Frequency with which polling is done (in msec).
*
* RETURN VALUE: 
* SUCCESS if H2A_INT is HIGH.
* FAIL_TIMEOUT if H2A_INT is LOW.
*/
/*====================================================================================================================*/
status_codes xrc_gpio_poll_high
(
	const uint32_t poll_time_out_ms, 
	xrc_gpio_type *handle
) 
{

    unsigned long long before = boot_get_time_count();
	unsigned long long difference = 0;
	const uint32_t timeout_us = poll_time_out_ms * 1000;
    uint32_t gpio_status = XRC_GPIO_VALUE_LOW;

	if (handle == NULL || poll_time_out_ms == 0)
	{
	  return FAIL_INVALID_PARAM;
	}

	do 
	{
        if (xrc_gpio_in(handle, &gpio_status) != SUCCESS) 
		{
            XRC_LOG_ERR(0, "DalTlmm_GpioIn failed");
	  		return FAIL_GPIO_ERR;
        }
		
        if (gpio_status == XRC_GPIO_VALUE_HIGH) 
		{
            break;
        }

        difference = boot_get_time_count() - before;
		
    } while (difference < timeout_us);
	
    if (gpio_status == XRC_GPIO_VALUE_HIGH)
    {
        return SUCCESS;
    }
	
    return FAIL_TIMEOUT;
}

/*====================================================================================================================
 FUNCTION: xrc_gpio_poll_low
====================================================================================================================*/
/** DESCRIPTION: 
* Poll periodically with a given frequency on the H2A_INT line, until the timeout. 
*
* INPUT PARAMETERS:
* poll_time_out: Time out in milliseconds.
* poll_frequency: Frequency with which polling is done (in msec).
*
* RETURN VALUE: 
* SUCCESS if H2A_INT is HIGH.
* FAIL_TIMEOUT if H2A_INT is LOW.
*/
/*====================================================================================================================*/
status_codes xrc_gpio_poll_low
(
	const uint32_t poll_time_out_ms, 
	xrc_gpio_type *handle

) 
{
    unsigned long long before = boot_get_time_count();
	unsigned long long difference = 0;
	const uint32_t timeout_us = poll_time_out_ms * 1000;
    uint32_t gpio_status = XRC_GPIO_VALUE_HIGH;

	if (handle == NULL || poll_time_out_ms == 0)
	{
	  return FAIL_INVALID_PARAM;
	}

	do 
	{
        if (xrc_gpio_in(handle, &gpio_status) != SUCCESS) 
		{
            XRC_LOG_ERR(0, "DalTlmm_GpioIn failed");
	  		return FAIL_GPIO_ERR;
        }
		
        if (gpio_status == XRC_GPIO_VALUE_LOW) 
		{
            break;
        }

        difference = boot_get_time_count() - before;
		
    } while (difference < timeout_us);
	
    if (gpio_status == XRC_GPIO_VALUE_LOW)
    {
        return SUCCESS;
    }
	
  	return FAIL_TIMEOUT;
}

/*=============================================================================
  FUNCTION  xrc_gpio_h2a_register
=============================================================================*/
/** Initialize and configures H2A GPIO
*
* @param: None
*
* @return
* SUCCESS if the configuration is done.
*/
/*=============================================================================*/
status_codes xrc_gpio_h2a_register(void)
{


	status_codes err;
    xrc_gpio_cfg_type gpio_cfg;

    /* Initialize H2A GPIO */
    memset(&gpio_cfg, 0, sizeof(xrc_gpio_cfg_type));
	gpio_cfg.dir = (xrc_gpio_dir_type)DAL_GPIO_INPUT;
	
    err = xrc_gpio_h2a_init((xrc_gpio_id_type)XRC_TLMM_H2A_INT_NUM, &gpio_cfg, 
                          &g_xrc_gpio_h2a_handle);
    if (err != SUCCESS)
    {
      XRC_LOG_ERR(0, "xrc_gpio_h2a_init(H2A) failed! err=%d", err);
	  return FAILURE;
    }

    return SUCCESS;
}

/*=============================================================================
  FUNCTION  xrc_gpio_h2a_release
=============================================================================*/
/**  De-Initialize the H2A GPIO 
*
* @param: None
*
* @return
* SUCCESS if the configuration is done.
*/
/*=============================================================================*/
void xrc_gpio_h2a_release()
{
	status_codes err;
	
    err = xrc_gpio_deinit(g_xrc_gpio_h2a_handle);
	if (err != SUCCESS)
    {
      XRC_LOG_ERR(0, "xrc_gpio_deinit(H2A) failed! err=%d", err);
    }

	g_xrc_gpio_h2a_handle = NULL;
}

