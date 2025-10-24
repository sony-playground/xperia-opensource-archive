#ifndef __GPIO_DT_COMMON_H__
#define __GPIO_DT_COMMON_H__
/*
===========================================================================
*/
/**
  @file GPIODT.h

  This file contains GPIO device tree strcuture definitions and function prototype.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/TLMMHWLib/fwk/dt/GPIODT.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/

/*==========================================================================

INCLUDE FILES FOR MODULE

==========================================================================*/
#include "HALtlmm.h"
#include "DTBExtnLib.h"

/*=========================================================================
      Macros
==========================================================================*/

/* 
 * only SOC TLMM support is present in loader/uefi
 */
#define MAX_GPIO_DEVICES 1

#define GPIO_DIRECTION(config) (((config) >> 4) & 0x1)
#define GPIO_PULL(config)      (((config) >> 5) & 0x3)
#define GPIO_DRIVE(config)     (((config) >> 7) & 0x1FFF)
#define GPIO_FUNC(config)      ((config)  & 0xF)
#define GPIO_OUTVAL(config)    (((config)  >> 21) & 0x1)
#define FDT_SUCCESS 0

/*
 * GPIO device tree property macros
 */
#define GPIO_PROP_NAME_LEN            20
#define GPIO_REG_PROP_ADDR_INDEX       0
#define GPIO_REG_PROP_SIZE_INDEX       1
#define GPIO_REG_PROP_LEN              2
#define GPIO_MAX_CONFIG_LIST           8
#define GPIO_MAX_DT_CONFIG            64
/*
 * Allow GPIO driver to call DALHWIO APIs to map memory
 */
#define GPIO_USE_REG_MAP               1

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * GPIO device context. 
 */
typedef struct {
  boolean                init;            /* GPIO device node initialized or not */
  HALgpioBlockDescType  *pHal;            /* pointer to GPIO HAL stcuture */
  uint32_t              *pSleepSettings;  /* GPIO device sleep settings */
  uint32_t               nSleepSettingsSize;  /* GPIO sleep settings size */
  fdt_node_handle       *pDevnode;        /* GPIO device node */
}GPIODeviceCtxt_t;

  
/*
 * GPIO driver context.
 */
typedef struct {
  boolean               init;
  uint32_t              nDeviceCnt;
  GPIODeviceCtxt_t      GPIODevCtxt[MAX_GPIO_DEVICES];  /* All supported GPIO devices context */
} GPIODriverCtxt_t;

/*
 * GPIO config node type.
 */
typedef struct  {
   int32_t        phandle;   /* phandle of GPIO mux node */
   uint32_t       nConfig;    /* GPIO configuration s*/
}GPIOConfigNodeCtxt_t;

/*
 * GPIO mux node type.
 */
typedef struct  {
   uint32_t       nPin;      /* GPIO pin number */
   uint32_t       nFuncsel;  /* GPIO function selection */ 
}GPIOMuxNodeCtxt_t;

/*
 * GPIO Pin type.
 */
typedef struct  {
   int32_t        phandle;   /* phandle of GPIO device node */
   uint32_t       nPin;       /* GPIO pin number */
   uint32_t       nConfig;    /* GPIO configuration */
}GPIOPinNodeCtxt_t;

/*
 * GPIO Pin type.
 */
typedef struct  {
   uint32_t       nPin;       /* GPIO pin number */
   uint32_t       nConfig;    /* GPIO configuration */
}GPIOActiveConfigNodeCtxt_t;


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : GPIO_DriverInit
** =========================================================================*/
/**
  This will initialize the GPIO driver

  This function register the GPIO device for each GPIO node exist in device tree.

  @return
  GPIO_SUCCESS -- configuration success.
  GPIO_ERROR   -- configuration failed.

  @dependencies
  None.
*/
GPIOResult GPIO_DriverInit 
(
  void
);

/* =========================================================================
**  Function : GPIO_DeviceInit
** =========================================================================*/
/**
  This will initialize the GPIO device

  initialize GPIO BSP from device tree node.
  
  @param pDevnode [in] -- pointer to device node.
  @param nSleepSupport [in] -- sleep config enable/disable
  
  @return
  GPIO_SUCCESS / GPIO_ERROR.

  @dependencies
  None.
*/
GPIOResult GPIO_DeviceInitEx
(
  fdt_node_handle *pDevnode,
  uint32_t         nSleepSupport
);

/*
 * nSleepsupport to added specific to UEFI.
 * Loader/UEFI use same blob so we need to ignore
 * sleep settings property while initialized UEFI driver
 */
#define GPIO_DeviceInit(pDevnode) \
         GPIO_DeviceInitEx(pDevnode, 1)

/* =========================================================================
**  Function : GPIO_GetDeviceNode
** =========================================================================*/
/**
  Get the device tree node from device tree blob

  This function get the given name device tree node from device tree blob.

  @param pDevnode [in] -- pointer to device node.
  @param szName   [in] -- pointer name.
  
  @return
  GPIO_SUCCESS / GPIO_ERROR.

  @dependencies
  None.
*/
GPIOResult GPIO_GetDeviceNode
(
  fdt_node_handle *pDevnode,
  const char      *szName
);

/* =========================================================================
**  Function : GPIO_ConfigPinctrl
** =========================================================================*/
/**
  Configure GPIO pins using GPIO key

  @param Handle      [in] -- GPIO device handle.
  @param GPIOkey     [in] -- GPIO Key which has client configuration information.
  
  @return
  GPIO_SUCCESS/GPIO_ERROR.

  @dependencies
  None.
*/
GPIOResult GPIO_ConfigPinctrl
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOkey
);

/* =========================================================================
**  Function : GPIO_ConfigPinctrlInactive
** =========================================================================*/
/**
  Configure GPIO pins specified in GPIOKey with Inactive configuration

  @param Handle      [in] -- GPIO device handle.
  @param GPIOkey     [in] -- GPIO Key which has client configuration information.
  
  @return
  GPIO_SUCCESS/GPIO_ERROR.

  @dependencies
  None.
*/
GPIOResult GPIO_ConfigPinctrlInactive
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOkey
);


#endif //__GPIO_DT_COMMON_H__