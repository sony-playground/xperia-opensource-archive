/*=============================================================================

                            SLVCOM GPIO

 Slave Communication GPIO interface

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/inc/slvcom_gpio.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_GPIO_H
#define SLVCOM_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "slvcom.h"
#include "DalDevice.h"
#include "DDITlmm.h"


/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
typedef enum
{
  SLVCOM_GPIO_VALUE_LOW  = DAL_GPIO_LOW_VALUE,
  SLVCOM_GPIO_VALUE_HIGH = DAL_GPIO_HIGH_VALUE
} slvcom_gpio_value_type;

typedef enum
{
  SLVCOM_GPIO_DIR_IN  = DAL_GPIO_INPUT,
  SLVCOM_GPIO_DIR_OUT = DAL_GPIO_OUTPUT
} slvcom_gpio_dir_type;

typedef enum
{
  SLVCOM_GPIO_INT_TRIGGER_HIGH      = 0,
  SLVCOM_GPIO_INT_TRIGGER_LOW       = 1,
  SLVCOM_GPIO_INT_TRIGGER_RISING    = 2,
  SLVCOM_GPIO_INT_TRIGGER_FALLING   = 3,
  SLVCOM_GPIO_INT_TRIGGER_DUAL_EDGE = 4,
} slvcom_gpio_int_trigger_type;

typedef void (*slvcom_gpio_isr_type)(void *);
typedef uint32 slvcom_gpio_id_type;

typedef struct
{
  slvcom_gpio_dir_type dir;
} slvcom_gpio_cfg_type;

typedef struct
{
  slvcom_gpio_id_type          id;
  slvcom_gpio_value_type       value;
  slvcom_gpio_dir_type         dir;
  slvcom_gpio_int_trigger_type trigger;
  slvcom_gpio_isr_type         isr;
  
  DALGpioSignalType  slvcom_tlmm_config;
  DalDeviceHandle   *dal_gpio_handle;
} slvcom_gpio_type;

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

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
  slvcom_gpio_id_type     gpio_id,
  slvcom_gpio_cfg_type    *gpio_cfg,
  slvcom_gpio_type     **handle
);

/*=============================================================================
  FUNCTION  slvcom_gpio_deinit
=============================================================================*/
/**
 *
 * @param[in] None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_gpio_deinit(slvcom_gpio_type *handle);

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
);

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
  slvcom_gpio_type       *handle,
  slvcom_gpio_value_type  *value
);

/*=============================================================================
  FUNCTION  slvcom_gpio_reg_int_isr
=============================================================================*/
/**
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
static inline slvcom_err_type slvcom_gpio_reg_int_isr
(
  slvcom_gpio_id_type          gpio_id,
  slvcom_gpio_int_trigger_type int_trigger,
  slvcom_gpio_isr_type         isr,
  void                        *priv,
  slvcom_gpio_type             **handle
)
{
  SLVCOM_LOG_ERR(0, "slvcom_gpio_reg_int_isr is not supported!");
  return SLVCOM_ERR_NOT_SUPPORTED;
}

/*=============================================================================
  FUNCTION  slvcom_gpio_dereg_int_isr
=============================================================================*/
/**
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
static inline slvcom_err_type slvcom_gpio_dereg_int_isr
(
  slvcom_gpio_type *handle
)
{
  SLVCOM_LOG_ERR(0, "slvcom_gpio_reg_int_isr is not supported!");
  return SLVCOM_ERR_NOT_SUPPORTED;
}

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_GPIO_H */
