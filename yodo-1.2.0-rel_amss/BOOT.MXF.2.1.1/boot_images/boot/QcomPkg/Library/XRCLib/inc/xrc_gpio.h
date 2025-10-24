/*=============================================================================

                            XRC H2A GPIO

 XRC Communication GPIO interface

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1/QcomPkg/Library/SlvcomLib/inc/slvcom_gpio.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef XRC_GPIO_H
#define XRC_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "xrc_types.h"
#include "xrc_log.h"
#include "com_dtypes.h"
#include "DalDevice.h"
#include "DDITlmm.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/

#define XRC_TLMM_H2A_INT_DIR  DAL_GPIO_INPUT
#define H2A_INT_POLL_FREQUENCY       10
#define H2A_INT_COMMAND_POLL_TIME    1000 
#define H2A_INT_RUN_IMAGE_COMMAND_POLL_TIME    10000


typedef enum
{
  XRC_GPIO_VALUE_LOW  = DAL_GPIO_LOW_VALUE,
  XRC_GPIO_VALUE_HIGH = DAL_GPIO_HIGH_VALUE
}xrc_gpio_value_type;

typedef enum
{
  XRC_GPIO_DIR_IN  = DAL_GPIO_INPUT,
  XRC_GPIO_DIR_OUT = DAL_GPIO_OUTPUT
} xrc_gpio_dir_type;

typedef enum
{
  XRC_GPIO_INT_TRIGGER_HIGH      = 0,
  XRC_GPIO_INT_TRIGGER_LOW       = 1,
  XRC_GPIO_INT_TRIGGER_RISING    = 2,
  XRC_GPIO_INT_TRIGGER_FALLING   = 3,
  XRC_GPIO_INT_TRIGGER_DUAL_EDGE = 4,
} xrc_gpio_int_trigger_type;

typedef void (*xrc_gpio_isr_type)(void *);
typedef uint32 xrc_gpio_id_type;

typedef struct
{
  xrc_gpio_dir_type dir;
} xrc_gpio_cfg_type;

typedef struct
{
  xrc_gpio_id_type          id;
  xrc_gpio_value_type       value;
  xrc_gpio_dir_type         dir;
  xrc_gpio_int_trigger_type trigger;
  xrc_gpio_isr_type         isr;
  
  DALGpioSignalType  xrc_tlmm_config;
  DalDeviceHandle   *dal_gpio_handle;
} xrc_gpio_type;

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/


/*=============================================================================
  FUNCTION  xrc_gpio_h2a_init
=============================================================================*/
/* DESCRIPTION: 
 * Configures the TLMM to read/poll on a specific GPIO  
 *
 * INPUT PARAMETERS:
 * gpio_id: GPIO number
 * gpio_cfg: Configuration of GPIO
 * ret_handle: Handle to DAL GPIO
 * RETURN VALUE: 
 * SUCCESS if the configuration is done.
 * Otherwise returns error code (see status_codes enumeration).
*/
/*=============================================================================*/
status_codes xrc_gpio_h2a_init
(
  xrc_gpio_id_type     gpio_id,
  xrc_gpio_cfg_type    *gpio_cfg,
  xrc_gpio_type     **handle
);

/*=============================================================================
  FUNCTION  xrc_gpio_deinit
=============================================================================*/
/* DESCRIPTION: 
 * De-initilaise the TLMM to read/poll on a specific GPIO  
 *
 * INPUT PARAMETERS:
 * handle: Handle to DAL GPIO
 * RETURN VALUE: 
 * SUCCESS if the configuration is done.
 * Otherwise returns error code (see status_codes enumeration).
*/
/*=============================================================================*/
status_codes xrc_gpio_deinit(xrc_gpio_type *handle);

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
 * XRC_ERR_NONE if function is successful,
 * Otherwise returns error code (see xrc_err_type enumeration).
 *
 */
/*===========================================================================*/
status_codes xrc_gpio_out
(
  xrc_gpio_type       *handle,
  xrc_gpio_value_type  value
);

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
 * XRC_ERR_NONE if function is successful,
 * Otherwise returns error code (see xrc_err_type enumeration).
 *
 */
/*===========================================================================*/
status_codes xrc_gpio_in
(
  xrc_gpio_type       *handle,
  xrc_gpio_value_type  *value
);

/*=============================================================================
  FUNCTION  xrc_gpio_reg_int_isr
=============================================================================*/
/**
 *
 * @return
 * XRC_ERR_NONE if function is successful,
 * Otherwise returns error code (see xrc_err_type enumeration).
 *
 */
/*===========================================================================*/
static inline status_codes xrc_gpio_reg_int_isr
(
  xrc_gpio_id_type          gpio_id,
  xrc_gpio_int_trigger_type int_trigger,
  xrc_gpio_isr_type         isr,
  void                        *priv,
  xrc_gpio_type             **handle
)
{
  XRC_LOG_ERR(0, "xrc_gpio_reg_int_isr is not supported!");
  return FAIL_NOT_SUPPORTED;
}

/*=============================================================================
  FUNCTION  xrc_gpio_dereg_int_isr
=============================================================================*/
/**
 *
 * @return
 * XRC_ERR_NONE if function is successful,
 * Otherwise returns error code (see xrc_err_type enumeration).
 *
 */
/*===========================================================================*/
static inline status_codes xrc_gpio_dereg_int_isr
(
  xrc_gpio_type *handle
)
{
  XRC_LOG_ERR(0, "xrc_gpio_reg_int_isr is not supported!");
  return FAIL_NOT_SUPPORTED;
}

/*=============================================================================
  FUNCTION  xrc_gpio_poll_high
=============================================================================*/
/**
 *
 * Poll periodically with a given frequency on the H2A_INT line, until the timeout
 *
 * @param[in]  poll_time_out - Time out in milliseconds.
 * @param[in] *handle    - To indicate High/Low level
 *
 * @return
 * XRC_ERR_NONE if H2A_INT is HIGH,
 * FAIL_TIMEOUT if H2A_INT is LOW.

 *
 */
/*===========================================================================*/

status_codes xrc_gpio_poll_high
(
	const uint32_t poll_time_out_ms, 
	xrc_gpio_type *handle
) ;

/*=============================================================================
  FUNCTION  xrc_gpio_poll_low
=============================================================================*/
/**
 *
 * Poll periodically with a given frequency on the H2A_INT line, until the timeout
 *
 * @param[in]  poll_time_out - Time out in milliseconds.
 * @param[in] *handle - To indicate High/Low level
 *
 * @return
 * XRC_ERR_NONE if H2A_INT is LOW,
 * XRC_ERR_FAIL_TIMEOUT if H2A_INT is HIGH.

 *
 */
/*===========================================================================*/

status_codes xrc_gpio_poll_low
(
	const uint32_t poll_time_out_ms, 
	xrc_gpio_type *handle

);

/*=============================================================================
  FUNCTION  xrc_gpio_h2a_register
=============================================================================*/
/**
 *
 * Initialize and configures H2A GPIO
 *
 * @param: None
 *
 * @return
 * SUCCESS if the configuration is done.
 * Otherwise returns error code (see status_codes enumeration).
 */
/*===========================================================================*/
status_codes xrc_gpio_h2a_register(void);

/*=============================================================================
  FUNCTION  xrc_gpio_h2a_release
=============================================================================*/
/**
 * De-Initialize the H2A GPIO 
 *
 * @param: None
 * @return
 *
 */
/*===========================================================================*/
void xrc_gpio_h2a_release();


#ifdef __cplusplus
}
#endif

#endif /* XRC_GPIO_H */
