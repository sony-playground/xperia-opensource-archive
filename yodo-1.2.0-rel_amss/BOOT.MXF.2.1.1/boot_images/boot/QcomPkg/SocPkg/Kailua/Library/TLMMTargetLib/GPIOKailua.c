/*===========================================================================

FILE:      GPIOKailua.c

DESCRIPTION:
This file register GPIO device instances with all TLMM/GPIO device nodes. 

PUBLIC CLASSES:
  GPIO_DriverInit

===========================================================================
Copyright (c) 2021 QUALCOMM Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
========================================================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "GPIODT.h"
#include "msmhwiobase.h"

/*=========================================================================
      Externs
==========================================================================*/
extern HAL_tlmm_GpioCoreControlType HAL_gpio_CoreControl;
extern HAL_tlmm_GpioExtControlType  HAL_gpio_ExtControl;

/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/
HALgpioBlockDescType GPIOBlockDescriptors[MAX_GPIO_DEVICES] =
{
  {
    GPIO_DEVICE_TLMM,
    TLMM_BASE,
    0x1000,
    1,
    {
      0x100000,
      0,
      0,
      0,
      0
    },
    0,
    209,
    GPIO_HW_VERSION(1, 0, 0xFF, 0xFF),
    &HAL_gpio_CoreControl,
    &HAL_gpio_ExtControl
  },  
};
uint32 nHWRevisionAddr = (CORE_TOP_CSR_BASE + 0xC8000);

uint32 gnNumBlockDescs = 1;
GPIODriverCtxt_t GPIODrvCtxt;
/* 
 *  GPIO device node
 */
static fdt_node_handle SoCPinctrlNode;

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : GPIO_DriverInit
** =========================================================================*/
/*
  See GPIOInternal.h.
*/
GPIOResult GPIO_DriverInit (void)
{
  GPIODrvCtxt.nDeviceCnt = 0;
  /* Get the target specific pinctrl node */
  if (GPIO_SUCCESS == GPIO_GetDeviceNode(&SoCPinctrlNode, "/soc/pinctrl@f100000"))
  {
    GPIO_DeviceInit(&SoCPinctrlNode);
  }
  
  return GPIO_SUCCESS;
}

