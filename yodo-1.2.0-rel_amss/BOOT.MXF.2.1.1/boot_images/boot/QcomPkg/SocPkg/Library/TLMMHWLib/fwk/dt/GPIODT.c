/*
===========================================================================
*/
/**
  @file GPIODT.c

  Interface implementation file for the GPIO device tree driver.
*/
/*
  ====================================================================

  Copyright (c) 2021-22 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/TLMMHWLib/fwk/dt/GPIODT.c#2 $
  $DateTime: 2022/11/24 21:28:29 $
  $Author: pwbldsvc $

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include "GPIOCore.h"
#include "GPIODT.h"
#include "GPIO.h"
#include "HALtlmm.h"
#include "GPIOSvcSync.h"
/* header files required for HWIO */
#include "DDIHWIO.h"
#include "DalDevice.h"
#include "DALDeviceId.h"

/*=========================================================================
      Externs
==========================================================================*/
extern HAL_tlmm_GpioCoreControlType HAL_gpio_CoreControl;
extern HAL_tlmm_GpioExtControlType  HAL_gpio_ExtControl;
extern boolean GPIO_CoreInit(void);
extern boolean GPIO_ExtInit(void);
extern boolean GPIO_SvcDeviceInit(HALgpioBlockDescType *pDesc, uint32_t *pSleepArr);
/* custom configuration to support strong pull support */
extern HAL_tlmm_GpioCoreControlType HAL_gpio_StrongPullControl;

/*=========================================================================
      Macros
==========================================================================*/
  
/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/
extern GPIODriverCtxt_t            GPIODrvCtxt;
/* 
 * HAL descriptors used in the GPIOCore.c
 */
extern HALgpioBlockDescType GPIOBlockDescriptors[MAX_GPIO_DEVICES];
extern uint32_t             gnNumBlockDescs;

extern GPIOPinInfoType ganGpioAccess[GPIO_MAX_ARR_SIZE];


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : GPIO_GetDeviceId
** =========================================================================*/
/**
  This function identify give GPIO device and return its HAL device ID

  @param pDevnode [in] -- pointer to GPIO device node.
  @param pId     [in] -- pointer to store GPIO device id.
  
  @return
  GPIO_SUCCESS / GPIO_ERROR.

  @dependencies
  None.
*/
static GPIOResult GPIO_GetDeviceId(fdt_node_handle *pDevnode, uint32_t *pId)
{
  int32_t i;
  GPIOResult eResult = GPIO_ERROR;

  for(i = 0; i < GPIODrvCtxt.nDeviceCnt; i++)
  {
    /* fdt_node_cmp API is not working because phandle node name is setting to "" instead of actual name of node */
    //if (FDT_SUCCESS == fdt_node_cmp(pDevnode, GPIODrvCtxt.GPIODevCtxt[i].pDevnode))
    if (pDevnode->offset == GPIODrvCtxt.GPIODevCtxt[i].pDevnode->offset)
    {
      *pId = GPIODrvCtxt.GPIODevCtxt[i].pHal->eDeviceId;
      eResult = GPIO_SUCCESS;
    }
  }
  return eResult;
}

/* =========================================================================
**  Function : GPIO_MapRegSpace
** =========================================================================*/
/**
  Map the GPIO register space with MMU

  This function read reg property from device tree node and map to with MMU.

  @param pDevnode [in] -- pointer to device node.
  @param pAddr    [in/out] -- pointer to virtual address.
  @param pSize    [in/out] -- pointer to nSize/len reg address.
  
  @return
  GPIO_SUCCESS -- Address map is success.
  GPIO_ERROR   -- Address map is failed.

  @dependencies
  None.
*/
static GPIOResult GPIO_MapRegSpace
(
  fdt_node_handle *pDevnode,
  uint32_t        *pAddr,
  uint32_t        *pSize
)
{
  int32_t nFdtResult;
  uint32_t nReg[GPIO_REG_PROP_LEN];
  uint32_t nSize;
  
  /* Input arguments check */
  if (pDevnode == NULL || pAddr == NULL || pSize == NULL)
  {
    return GPIO_INTERNAL_ERROR;
  }

  nFdtResult = fdt_get_prop_size(pDevnode, "reg", &nSize);
  if (nFdtResult == FDT_SUCCESS)
  {
      /* Get the reg property which contains base address and size*/
	  nFdtResult = fdt_get_uint32_prop_list(pDevnode, "reg", nReg, nSize);
	  if (nFdtResult == FDT_SUCCESS)
    { 
      /* if Mapping not required, use below code */
#if GPIO_USE_REG_MAP
      *pSize = nReg[GPIO_REG_PROP_SIZE_INDEX];
      *pAddr = nReg[GPIO_REG_PROP_ADDR_INDEX];
#else
      DalDeviceHandle* pHWIOHandler;
      /* Map to virtual address */
      if(DAL_DeviceAttach(DALDEVICEID_HWIO, &pHWIOHandler) == DAL_SUCCESS)
      {
         DalHWIO_MapRegionByAddress(pHWIOHandler, (uint8_t *) &nReg[GPIO_REG_PROP_ADDR_INDEX], (uint8_t**)&(pAddr));
         return GPIO_SUCCESS;
      }
#endif
	  }
  }
  return GPIO_INTERNAL_ERROR;
}

/* =========================================================================
**  Function : GPIO_ParseConfig
** =========================================================================*/
/**
  Parse Device tree config property and store it in GPIO internal memory

  @param Handle      [in] -- GPIO device handle.
  @param pConfigNode [in] -- Device tree config property handle
  @param pGpiokey    [in] -- pointer to GPIO key.
  
  @return
  GPIO_SUCCESS/GPIO_ERROR.

  @dependencies
  None.
*/
static GPIOResult GPIO_ParseConfig
(
  GPIOClientHandleType  Handle,
  fdt_node_handle      *pConfigNode,
  GPIOKeyType          *PGpiokey
)
{
  int32_t              nFdtResult;
  GPIOResult           eResult = GPIO_SUCCESS;
  GPIOConfigNodeCtxt_t ConfigNodeCtxt[GPIO_MAX_CONFIG_LIST];
  fdt_node_handle      hMuxnode, hDevnode;
  GPIOMuxNodeCtxt_t    MuxNodeCtxt;
  uint32_t             nIndex = 0, nLen = 0;
  uint32_t             nSlotIdx, nId, nSize, i;

  if (pConfigNode == NULL || PGpiokey == NULL)
  {
    return GPIO_ERROR;
  }

  GPIO_SyncEnter();
  /* Get tlmm config property */
  if (FDT_SUCCESS == fdt_get_prop_size(pConfigNode, "config", &nSize))
  {
    nLen = nSize / (sizeof(GPIOConfigNodeCtxt_t));
    for (nSlotIdx = 0; nSlotIdx < GPIO_MAX_ARR_SIZE; nSlotIdx++)
    {
      if (ganGpioAccess[nSlotIdx].nInUse == 0 )
      {
        break;
      }
    }
    /* safe check to make sure max 8 GPIO configurations allowed under one pinctrl property */
    if(nLen == 0 || nLen > GPIO_MAX_CONFIG_LIST || (nSlotIdx + nLen >= GPIO_MAX_ARR_SIZE))
    {
      return GPIO_INTERNAL_ERROR;
    }
    nIndex = nSlotIdx;
    nFdtResult = fdt_get_uint32_prop_list(pConfigNode, "config", (uint32_t *)&ConfigNodeCtxt[0], nSize);
    for (i=0; i < nLen && nSlotIdx < GPIO_MAX_ARR_SIZE; i++)
    {
      nFdtResult = fdt_get_phandle_node(pConfigNode, ConfigNodeCtxt[i].phandle, &hMuxnode);
      if (nFdtResult != FDT_SUCCESS)
      {
        eResult = GPIO_INTERNAL_ERROR;
        break;
      }
      nFdtResult = fdt_get_uint32_prop_list(&hMuxnode, "mux", (uint32_t *)&MuxNodeCtxt, sizeof(GPIOMuxNodeCtxt_t));
      if (nFdtResult != FDT_SUCCESS)
      {
        eResult = GPIO_INTERNAL_ERROR;
        break;
      }
      fdt_get_parent_node(&hMuxnode, &hDevnode);
      GPIO_GetDeviceId(&hDevnode, &nId);
      ganGpioAccess[nSlotIdx].nPin = MuxNodeCtxt.nPin;
      ganGpioAccess[nSlotIdx].nDeviceId = nId;
      
      ganGpioAccess[nSlotIdx].nDir = GPIO_DIRECTION(ConfigNodeCtxt[i].nConfig);
      ganGpioAccess[nSlotIdx].nPull = GPIO_PULL(ConfigNodeCtxt[i].nConfig);
      ganGpioAccess[nSlotIdx].nDrive =GPIO_DRIVE(ConfigNodeCtxt[i].nConfig);
      ganGpioAccess[nSlotIdx].nFunc = MuxNodeCtxt.nFuncsel;
      ganGpioAccess[nSlotIdx].nInUse    = 1;
      nSlotIdx++;
    }
  }
  if (eResult == GPIO_SUCCESS)
  {
    *PGpiokey = GPIO_MAKE_KEY(GPIO_ID_CATEGORY_PINCTRL, nIndex, nLen);
  }
  
  GPIO_SyncExit();
  return eResult;
}

/* =========================================================================
**  Function : GPIO_ConfigPinctrl
** =========================================================================*/
/*
  See GPIODT.h.
 */
GPIOResult GPIO_ConfigPinctrl
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey
)
{
  uint32_t nIndex, nCount, i;
  GPIOPinInfoType  PinInfo;
  GPIOConfigType   Config = {0};

  nIndex = GPIO_KEY_GET_INDEX(GPIOKey);
  nCount = GPIO_KEY_GET_LEN(GPIOKey);

  if (nIndex >= GPIO_MAX_ARR_SIZE || nCount > GPIO_MAX_CONFIG_LIST)
  {
    return GPIO_ERROR;
  }

  for(i = 0; i < nCount && nIndex < GPIO_MAX_ARR_SIZE; i++)
  {
    PinInfo = ganGpioAccess[nIndex++];
    Config.dir = PinInfo.nDir;
    Config.func = PinInfo.nFunc;
    Config.pull = PinInfo.nPull;
    Config.drive = PinInfo.nDrive;
    HAL_tlmm_ConfigPin(&GPIOBlockDescriptors[PinInfo.nDescIdx], GPIOBlockDescriptors[PinInfo.nDescIdx].aTiles[0], PinInfo.nPin, Config);
  }
  return GPIO_SUCCESS;
}

/* =========================================================================
**  Function : GPIO_ConfigPinctrlInactive
** =========================================================================*/
/*
  See GPIODT.h.
 */
GPIOResult GPIO_ConfigPinctrlInactive
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey
)
{
  uint32_t nIndex, nCount, i;
  GPIOResult       eResult = GPIO_SUCCESS;
  GPIOPinInfoType  PinInfo;
  GPIOConfigType   Config = {0};
  GPIOValueType    eValue;

  nIndex = GPIO_KEY_GET_INDEX(GPIOKey);
  nCount = GPIO_KEY_GET_LEN(GPIOKey);

  for(i = 0; i < nCount; i++)
  {
    PinInfo = ganGpioAccess[nIndex + i];
    /*
     * Get the offset from the base address and program the GPIO.
     */
    HAL_tlmm_GetInactiveConfig(&GPIOBlockDescriptors[PinInfo.nDescIdx], GPIOBlockDescriptors[PinInfo.nDescIdx].aTiles[0], PinInfo.nPin, &Config, &eValue);
    if ( Config.dir == GPIO_OUT )
    {
      HAL_tlmm_WritePin(&GPIOBlockDescriptors[PinInfo.nDescIdx], GPIOBlockDescriptors[PinInfo.nDescIdx].aTiles[0], PinInfo.nPin, eValue);
    }
    HAL_tlmm_ConfigPin(&GPIOBlockDescriptors[PinInfo.nDescIdx], GPIOBlockDescriptors[PinInfo.nDescIdx].aTiles[0], PinInfo.nPin, Config);

    /* Update active config in local memory */
    PinInfo.nDir = Config.dir;
    PinInfo.nPull = Config.pull;
    PinInfo.nDrive = Config.drive;
    PinInfo.nFunc = Config.func;
  }
  return eResult;
}

/* =========================================================================
**  Function : GPIO_RegisterDeviceConfig
** =========================================================================*/
/*
  See GPIO.h.
*/
GPIOResult GPIO_RegisterDeviceConfig
(
  GPIOClientHandleType Handle,
  fdt_node_handle     *pClientnode,
  const char          *szName,
  GPIOKeyType         *pGpiokey
)
{
  GPIOResult result = GPIO_INVALID_PARAMETER;
  fdt_node_handle    hConfignode;
  char pinctrlName[GPIO_PROP_NAME_LEN];
  uint32_t phandle;
  int32_t  nFdtResult, nIndex;
  
  if (pClientnode == NULL || szName == NULL || pGpiokey == NULL)
  {
    result = GPIO_INVALID_PARAMETER;
  }
  else
  {
    if (FDT_SUCCESS == fdt_get_name_index(pClientnode, "pinctrl-names", (char *)szName, &nIndex))
    {
      snprintf(pinctrlName, GPIO_PROP_NAME_LEN, "pinctrl-%d", nIndex);
      nFdtResult = fdt_get_uint32_prop(pClientnode, (const char *)pinctrlName, &phandle);
      if (nFdtResult == FDT_SUCCESS)
      {
        nFdtResult = fdt_get_phandle_node(pClientnode, phandle, &hConfignode);
        if (nFdtResult == FDT_SUCCESS)
        {
          result =  GPIO_ParseConfig(Handle, &hConfignode, pGpiokey);
        }
      }
      result = (nFdtResult == FDT_SUCCESS) ? GPIO_SUCCESS : GPIO_RESOURCE_NOT_FOUND;
    }
    else
    {
      result = GPIO_RESOURCE_NOT_FOUND;
    }
    
  }
  return result;
}

/* =========================================================================
**  Function : GPIO_RegisterDevicePin
** =========================================================================*/
/*
 see GPIO.h
*/
GPIOResult GPIO_RegisterDevicePin
(
  GPIOClientHandleType  Handle,
  fdt_node_handle      *pClientnode,
  const char           *szName,
  GPIOKeyType          *pGpiokey
)
{
  GPIOPinNodeCtxt_t PinNodeCtxt;
  GPIOResult        eResult = GPIO_SUCCESS;
  GPIOConfigType    GPIOConfig = {0};
  int32_t           nFdtResult;
  uint32_t          nDeviceId;
  fdt_node_handle   hDevnode;
  GPIOClientHandleType  HandleInternal;
  char              szPropName[GPIO_PROP_NAME_LEN] = "\0";
  
  if (pClientnode == NULL || szName == NULL || pGpiokey == NULL)
  {
    return eResult;
  }
  snprintf(szPropName, GPIO_PROP_NAME_LEN, "%s-gpios", szName);
  nFdtResult = fdt_get_uint32_prop_list(pClientnode, szPropName, (uint32_t *)&PinNodeCtxt, sizeof(GPIOPinNodeCtxt_t));
  
  if (nFdtResult == FDT_SUCCESS)
  {
    fdt_get_phandle_node(pClientnode, PinNodeCtxt.phandle, &hDevnode);
    /* Get HAL Device ID from devnode */
    GPIO_GetDeviceId(&hDevnode, &nDeviceId);
    HandleInternal.DeviceId = nDeviceId;
    /* Below line is added to fix klockwork error */
    HandleInternal.ClientId = 0;
    eResult = GPIO_RegisterPinExplicit(HandleInternal, PinNodeCtxt.nPin,  GPIO_ACCESS_SHARED, pGpiokey);
    if (eResult == GPIO_SUCCESS)
      {
        /* Update GPIO default configuration */
        if (PinNodeCtxt.nConfig != 0)
        {
          GPIOConfig.dir = GPIO_DIRECTION(PinNodeCtxt.nConfig);
          GPIOConfig.pull = GPIO_PULL(PinNodeCtxt.nConfig);
          GPIOConfig.drive =GPIO_DRIVE(PinNodeCtxt.nConfig);
        eResult = GPIO_ConfigPin(Handle, *pGpiokey, GPIOConfig);
        }
      }
    }
  else  
  {
    eResult = GPIO_RESOURCE_NOT_FOUND;
  }
  return eResult;
}

/* =========================================================================
**  Function : GPIO_GetDeviceNode
** =========================================================================*/
/*
  See GPIOInternal.h.
*/
GPIOResult GPIO_GetDeviceNode
(
  fdt_node_handle *pDevnode,
  const char      *szName
)
{
  void    *pBlob = NULL;
  int32_t  nFdtResult;

  /* Input arguments check */
  if (pDevnode == NULL || szName == NULL)
  {
    return GPIO_INTERNAL_ERROR;
  }

  nFdtResult = fdt_get_node_handle(pDevnode, pBlob, (char *)szName);

  return nFdtResult == FDT_SUCCESS ? GPIO_SUCCESS : GPIO_RESOURCE_NOT_FOUND;
}

/* =========================================================================
**  Function : GPIO_DeviceInit
** =========================================================================*/
/*
  See GPIODT.h.
*/
GPIOResult GPIO_DeviceInitEx
(
  fdt_node_handle      *pDevnode,
  uint32_t              nSleepSupport
)
{
  uint32_t nGpios, nSize, nDescIdx;
  uint32_t nDeviceId;
  GPIODeviceCtxt_t *pGPIODevCtxt;
  GPIODriverCtxt_t *pDrvCtxt = &GPIODrvCtxt;
  GPIOActiveConfigNodeCtxt_t  *pActiveSettings = NULL;
  uint32_t nActiveSettingSize = 0;
  uint32_t nVersion;
  
  /* Initlaize GPIO core and other modules */  
  if (pDrvCtxt->init == FALSE)
  {
    GPIO_CoreInit();
    GPIO_ExtInit();
    pDrvCtxt->init = TRUE;
  }
  
  GPIO_SyncEnter();
  
  if (FDT_SUCCESS == fdt_get_uint32_prop(pDevnode, "id", &nDeviceId))
  {
    for (nDescIdx = 0; nDescIdx < pDrvCtxt->nDeviceCnt; nDescIdx++)
      if (nDeviceId == pDrvCtxt->GPIODevCtxt[nDescIdx].pHal->eDeviceId)
    {
      {
        /* Already this device is initialized */
        break;
      }
    }
    if(nDescIdx == pDrvCtxt->nDeviceCnt)
    {
      /* This is new device, update device count */
      pDrvCtxt->nDeviceCnt++;
      gnNumBlockDescs = pDrvCtxt->nDeviceCnt;
    }
  }
  else
  {
    /* FDT node is not GPIO device node */
    return GPIO_ERROR;
  }
  
  /* Initilize the device node */
  pGPIODevCtxt = &pDrvCtxt->GPIODevCtxt[nDescIdx];
  pGPIODevCtxt->pHal = &GPIOBlockDescriptors[nDescIdx];
  pGPIODevCtxt->pDevnode = pDevnode;

  /* Get the device tree configuration and populate the HAL strcuture */
  /* TODO: GPIO_MapRegSpace will be replaced by qdi-lite API */
  GPIO_MapRegSpace(pDevnode, &pGPIODevCtxt->pHal->nBaseAddr, &pGPIODevCtxt->pHal->nSize);
  fdt_get_uint32_prop(pDevnode, "ngpios", &nGpios);
  fdt_get_uint32_prop(pDevnode, "width", &pGPIODevCtxt->pHal->nPinRegWidth);
  fdt_get_uint32_prop(pDevnode, "id", &pGPIODevCtxt->pHal->eDeviceId);
  
  /* Read HAL custom configuration version. */
  if (FDT_SUCCESS != fdt_get_uint32_prop(pDevnode, "version", &nVersion))
  {
    nVersion = 0;
  }

  /* NOTE: Assuming all latest targets removed Tiles concept */
  pGPIODevCtxt->pHal->nNumTiles = 1;
  pGPIODevCtxt->pHal->aTiles[0] = 0;
  pGPIODevCtxt->pHal->nMinPinNumber = 0;
  pGPIODevCtxt->pHal->nMaxPinNumber = nGpios - 1;
  pGPIODevCtxt->pHal->nHWVersion = 0;

  /* Initialize control function pointers */
  pGPIODevCtxt->pHal->pmCoreControl = &HAL_gpio_CoreControl;
  pGPIODevCtxt->pHal->pmExtControl = &HAL_gpio_ExtControl;
  
  /* Reassign custom HAL version if it is set */
  if (nVersion == 1)
  {
    pGPIODevCtxt->pHal->pmCoreControl = &HAL_gpio_StrongPullControl;
  }

  /* Get sleep settings, these are optional settings. */
  if (nSleepSupport == 1)
  {
    if (fdt_get_prop_size(pDevnode, (const char *)"qcom,sleep-config", &nSize) == FDT_SUCCESS)
    {
      if (DAL_SUCCESS == DALSYS_Malloc(nSize,(void **)(&pGPIODevCtxt->pSleepSettings)))
      {
         fdt_get_uint32_prop_list(pDevnode, (const char *)"qcom,sleep-config", pGPIODevCtxt->pSleepSettings, nSize);
         pGPIODevCtxt->nSleepSettingsSize = nSize;
      }
      else
      {
        return GPIO_INTERNAL_ERROR;
      }
    }
    if (fdt_get_prop_size(pDevnode, (const char*)"qcom,active-config", &nActiveSettingSize) == FDT_SUCCESS)
    {
      if (DAL_SUCCESS == DALSYS_Malloc(nActiveSettingSize,(void **)(&pActiveSettings)))
      {
        fdt_get_uint32_prop_list(pDevnode, (const char *)"qcom,active-config", (uint32_t *)pActiveSettings, nActiveSettingSize);
      }
      else
      {
        return GPIO_INTERNAL_ERROR;
      }
    }
  }
  else
  {
    pGPIODevCtxt->pSleepSettings = NULL;
    pGPIODevCtxt->pSleepSettings = 0;
  }
  /* Initialize HAL */
  HAL_tlmm_Init(pGPIODevCtxt->pHal);
  
  /* Initialize sleep settings */
  GPIO_SvcDeviceInit(pGPIODevCtxt->pHal, pGPIODevCtxt->pSleepSettings);

  /* Set active configuration */
  if(pActiveSettings != NULL)
  {
    GPIOConfigType   Config = {0};
    uint32_t         i;
    for (i=0; i < nActiveSettingSize/sizeof(GPIOActiveConfigNodeCtxt_t); i++)
    {
      Config.dir = GPIO_DIRECTION(pActiveSettings[i].nConfig);
      Config.func = GPIO_FUNC(pActiveSettings[i].nConfig);
      Config.pull = GPIO_PULL(pActiveSettings[i].nConfig);
      Config.drive = GPIO_DRIVE(pActiveSettings[i].nConfig);
      HAL_tlmm_ConfigPin(&GPIOBlockDescriptors[nDescIdx], GPIOBlockDescriptors[nDescIdx].aTiles[0], pActiveSettings[i].nPin, Config);
      
      if (Config.dir == GPIO_OUT)
      {
        HAL_tlmm_WritePin(&GPIOBlockDescriptors[nDescIdx], GPIOBlockDescriptors[nDescIdx].aTiles[0], pActiveSettings[i].nPin, GPIO_OUTVAL(pActiveSettings[i].nConfig));
      }
    }
    DALSYS_Free(pActiveSettings);
  }
  /*NOTE: device tree is specific to each chip file so no need to maintain chipversion */
 
  /* Mark this device is initialized */
  pGPIODevCtxt->init = TRUE;

  GPIO_SyncExit();

  return GPIO_SUCCESS;
}
