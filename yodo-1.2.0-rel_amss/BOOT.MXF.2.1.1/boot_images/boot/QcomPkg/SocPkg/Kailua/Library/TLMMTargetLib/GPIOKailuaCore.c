/*===========================================================================

FILE:      GPIOKailuaCore.c

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

/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/
HALgpioBlockDescType GPIOBlockDescriptors[MAX_GPIO_DEVICES];
uint32_t             gnNumBlockDescs = 0;
uint32 nHWRevisionAddr = (CORE_TOP_CSR_BASE + 0xC8000);

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
    GPIO_DeviceInitEx(&SoCPinctrlNode, 0);
  }
  
  return GPIO_SUCCESS;
}

