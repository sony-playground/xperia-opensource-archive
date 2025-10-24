/*============================================================================
  FILE:         VAdcFwkBoot.c

  OVERVIEW:     VADC Device Layer framework file (bare-metal)

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.1/QcomPkg/Library/PmicLib/adc/devices/vadc/src/DalVAdcFwk.c#1 $$DateTime: 2021/10/11 15:28:53 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DALSys.h"
#include "DDIAdcDevice.h"
#include "DalVAdc.h"
#include "CoreVerify.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
VAdcDrvCtxt gVAdcDrvCtxt =
{
   .VAdcDALVtbl   = {VAdc_DriverInit, VAdc_DriverDeInit},
   .dwNumDev      = VADC_MAX_NUM_DEVICES,
   .dwSizeDevCtxt = sizeof(VAdcDevCtxt),
   .bInit         = 0,
   .dwRefs        = 0,
   .VAdcDevCtxt   = {{0}}
};

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
static uint32
VAdc_DalAdcDevice_AddRef(DalAdcDeviceHandle *h)
{
   return 0;
}

/*------------------------------------------------------------------------------
Following functions are defined in DalDevice DAL Interface.
------------------------------------------------------------------------------*/
static uint32
VAdc_DalAdcDevice_Detach(DalDeviceHandle *h)
{
   return 0;
}

static DALResult
VAdc_DalAdcDevice_Init(DalDeviceHandle *h)
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_DeviceInit(pCtxt);
}

static DALResult
VAdc_DalAdcDevice_DeInit(DalDeviceHandle *h)
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_DeviceDeInit(pCtxt);
}

static DALResult
VAdc_DalAdcDevice_PowerEvent(
   DalDeviceHandle *h,
   DalPowerCmd PowerCmd,
   DalPowerDomain PowerDomain
   )
{
   return DAL_SUCCESS;
}

static DALResult
VAdc_DalAdcDevice_Open(
   DalDeviceHandle *h,
   uint32 mode
   )
{
   return DAL_SUCCESS;
}

static DALResult
VAdc_DalAdcDevice_Close(DalDeviceHandle *h)
{
   return DAL_SUCCESS;
}

static DALResult
VAdc_DalAdcDevice_Info(
   DalDeviceHandle *h,
   DalDeviceInfo* info,
   uint32 infoSize
   )
{
   info->Version = DALADCDEVICE_INTERFACE_VERSION;
   return DAL_SUCCESS;
}

static DALResult
VAdc_DalAdcDevice_SysRequest(
   DalDeviceHandle *h,
   DalSysReq ReqIdx,
   const void *SrcBuf,
   uint32 SrcBufLen,
   void *DestBuf,
   uint32 DestBufLen,
   uint32 *DestBufLenReq
   )
{
   return DAL_ERROR;
}

/*------------------------------------------------------------------------------
Following functions are extended in DalAdcDevice Interface.
------------------------------------------------------------------------------*/
static DALResult
VAdc_DalAdcDevice_SetDeviceIndex(
   DalDeviceHandle *h,
   uint32 uDeviceIndex
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_SetDeviceIndex(pCtxt,
                              uDeviceIndex);
}

static DALResult
VAdc_DalAdcDevice_GetInputProperties(
   DalDeviceHandle *h,
   const char *pChannelName,
   uint32 *puChannelIdx
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_GetChannel(pCtxt,
                          pChannelName,
                          puChannelIdx);
}

static DALResult
VAdc_DalAdcDevice_GetDeviceProperties(
   DalDeviceHandle *h,
   AdcDeviceDevicePropertiesType *pAdcDeviceProp
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_GetDeviceProperties(pCtxt, pAdcDeviceProp);
}

#ifndef ADC_LOADER_DRIVER
static DALResult
VAdc_DalAdcDevice_RecalibrateChannel(
   DalDeviceHandle *h,
   uint32 uChannelIdx,
   AdcDeviceRecalibrateResultType *pAdcDeviceRecalibrateResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_RecalibrateChannel(pCtxt,
                                  uChannelIdx,
                                  pAdcDeviceRecalibrateResult);
}
#endif

static DALResult
VAdc_DalAdcDevice_ReadChannel(
   DalDeviceHandle *h,
   uint32 uChannelIdx,
   AdcDeviceResultType *pAdcDeviceReadResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ReadChannel(pCtxt,
                           uChannelIdx,
                           pAdcDeviceReadResult);
}

#ifndef ADC_BOOT_DRIVER
static DALResult
VAdc_DalAdcDevice_TMGetInputProperties(
   DalDeviceHandle*h,
   const char *pInputName,
   uint32 *puMeasIdx
   )
{
   return ADC_DEVICE_ERROR_TM_NOT_SUPPORTED;
}

static DALResult
VAdc_DalAdcDevice_TMGetRange(
   DalDeviceHandle *h,
   uint32 uMeasIdx,
   AdcDeviceTMRangeType *pAdcDeviceTMRange
   )
{
   return ADC_DEVICE_ERROR_TM_NOT_SUPPORTED;
}

static DALResult
VAdc_DalAdcDevice_TMSetThreshold(
   DalDeviceHandle *h,
   uint32 uMeasIdx,
   const DALSYSEventHandle hEvent,
   AdcDeviceTMThresholdType eThreshold,
   const int32 *pnThresholdDesired,
   int32 *pnThresholdSet
   )
{
   return ADC_DEVICE_ERROR_TM_NOT_SUPPORTED;
}
#endif

static DALResult
VAdc_DalAdcDevice_ProcessConversionResult(
   DalDeviceHandle *h,
   uint32 uChannelIdx,
   uint32 uAdcCode,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ProcessConversionResult(pCtxt,
                                       uChannelIdx,
                                       uAdcCode,
                                       pAdcDeviceResult);
}

static DALResult
VAdc_DalAdcDevice_ProcessConversionResultInverse(
   DalDeviceHandle *h,
   uint32 uChannelIdx,
   int32 nPhysical,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ProcessConversionResultInverse(pCtxt,
                                              uChannelIdx,
                                              nPhysical,
                                              pAdcDeviceResult);
}

static void
VAdc_InitInterface(VAdcClientCtxt *pclientCtxt)
{
   static uint32 devCtxtIndex = 0;
   static const DalAdcDevice vtbl =
   {
      {
         VAdc_DalAdcDevice_Attach,
         VAdc_DalAdcDevice_Detach,
         VAdc_DalAdcDevice_Init,
         VAdc_DalAdcDevice_DeInit,
         VAdc_DalAdcDevice_Open,
         VAdc_DalAdcDevice_Close,
         VAdc_DalAdcDevice_Info,
         VAdc_DalAdcDevice_PowerEvent,
         VAdc_DalAdcDevice_SysRequest
      },
      VAdc_DalAdcDevice_SetDeviceIndex,
      VAdc_DalAdcDevice_GetInputProperties,
      VAdc_DalAdcDevice_GetDeviceProperties,
#ifndef ADC_LOADER_DRIVER
      VAdc_DalAdcDevice_RecalibrateChannel,
#endif
      VAdc_DalAdcDevice_ReadChannel,
#ifndef ADC_BOOT_DRIVER
      VAdc_DalAdcDevice_TMGetInputProperties,
      VAdc_DalAdcDevice_TMGetRange,
      VAdc_DalAdcDevice_TMSetThreshold,
#endif
      VAdc_DalAdcDevice_ProcessConversionResult,
      VAdc_DalAdcDevice_ProcessConversionResultInverse,
   };
   /*--------------------------------------------------------------------------
     Depending upon client type setup the vtables (entry points)
     --------------------------------------------------------------------------*/
   CORE_VERIFY(devCtxtIndex < gVAdcDrvCtxt.dwNumDev);
   pclientCtxt->pVAdcDevCtxt = &gVAdcDrvCtxt.VAdcDevCtxt[devCtxtIndex++];
   pclientCtxt->DalAdcDeviceHandle.dwDalHandleId = DALDEVICE_INTERFACE_HANDLE_ID;
   pclientCtxt->DalAdcDeviceHandle.pVtbl  = &vtbl;
   pclientCtxt->DalAdcDeviceHandle.pClientCtxt = pclientCtxt;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
DALResult
VAdc_DalAdcDevice_Attach(
   const char *pszArg,
   uint32 DeviceId,
   DalDeviceHandle **phDalDevice
   )
{
   DALResult nErr;
   VAdcClientCtxt *pClientCtxt = NULL;

   /* Allocate memory for the client context */
   nErr = DALSYS_Malloc(sizeof(VAdcClientCtxt), (void **)&pClientCtxt);
   if (DAL_SUCCESS != nErr || NULL == pClientCtxt)
   {
      return DAL_ERROR;
   }

   DALSYS_memset(pClientCtxt, 0, sizeof(VAdcClientCtxt));
   
   /* Initialize the Device Layer Interface and Client context */
   VAdc_InitInterface(pClientCtxt);
   pClientCtxt->pVAdcDevCtxt->DevId = DeviceId;
   *phDalDevice = (DalDeviceHandle *)&(pClientCtxt->DalAdcDeviceHandle);
   /* Call device_init now */
   VAdc_DalAdcDevice_Init((DalDeviceHandle *)&(pClientCtxt->DalAdcDeviceHandle));

   return nErr;
}

