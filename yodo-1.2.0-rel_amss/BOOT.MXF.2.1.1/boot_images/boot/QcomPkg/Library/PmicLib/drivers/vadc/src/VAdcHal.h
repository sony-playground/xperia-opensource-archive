#ifndef __VADCHAL_H__
#define __VADCHAL_H__
/*============================================================================
  @file VAdcHal.h

  Function and data structure declarations for VADC HAL


                Copyright (c) 2012, 2015, 2017-2019 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc/src/VAdcHal.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "VAdcBsp.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define VADC_INVALID_ADC_CODE 0x8000

#define VADC_INT_MASK_EOC 0x1


/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef struct
{
   uint16 usDigitalRev;
   uint8 ucType;
   uint8 ucSubType;
} VAdcRevisionInfoType;

typedef enum
{
   VADC_CONVERSION_STATUS_INVALID = 0,
   VADC_CONVERSION_STATUS_COMPLETE,
   VADC_CONVERSION_STATUS_PENDING,
   VADC_CONVERSION_STATUS_WAITING
} VAdcConversionStatusType;

typedef struct
{
   VAdcConversionStatusType eConversionStatus;
} VAdcStatusType;

typedef enum
{
   VADC_INTERRUPT_CONFIG_LEVEL_HIGH = 0,
   VADC_INTERRUPT_CONFIG_LEVEL_LOW,
   VADC_INTERRUPT_CONFIG_RISING_EDGE,
   VADC_INTERRUPT_CONFIG_FALLING_EDGE
} VAdcInterruptConfigType;

typedef struct
{
   uint32 uChannel;
   VAdcCalMethodType eCalMethod;
   VAdcDecimationRatioType eDecimationRatio;
   VAdcAverageModeType eAverageMode;
   VAdcSettlingDelay eSettlingDelay;
	uint32 uSid;
} VAdcConversionParametersType;

typedef enum
{
   VADC_DISABLE = 0,
   VADC_ENABLE
} VAdcEnableType;

typedef struct
{
   uint8 ucOffset;
   uint8 ucVal;
} VAdcHalRegType;

typedef struct
{
   VAdcHalRegType *aVAdcReg;
	int32 reg_size;
} VAdcHalRegDumpType;

typedef struct
{
   VAdcRevisionInfoType revisionInfo;        /* VADC revision info */
   uint16 spmi_slave_id;                     /* SID that VADC is on */
   uint16 spmi_peripheral_id;                /* VADC Peripheral ID */
   uint8  spmi_bus_id;                       /* SPMI bus id */
} VAdcHalInterfaceType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
pm_err_flag_type VAdcHalGetRevisionInfo(VAdcHalInterfaceType *piVAdcHal);
pm_err_flag_type VAdcHalGetStatus(VAdcHalInterfaceType *piVAdcHal, VAdcStatusType *pStatus);
pm_err_flag_type VAdcHalConfigInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask, VAdcInterruptConfigType eConfig);
pm_err_flag_type VAdcHalGetPendingInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 *pucIntrMask);
pm_err_flag_type VAdcHalClearInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask);
pm_err_flag_type VAdcHalEnableInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask);
pm_err_flag_type VAdcHalSetInterruptMid(VAdcHalInterfaceType *piVAdcHal, uint32 uIntrMid);
pm_err_flag_type VAdcHalSetEnable(VAdcHalInterfaceType *piVAdcHal, VAdcEnableType eEnable);
pm_err_flag_type VAdcHalRequestConversion(VAdcHalInterfaceType *piVAdcHal, VAdcConversionParametersType *pParams, uint32 *puConvTimeUs);
pm_err_flag_type VAdcHalGetConversionCode(VAdcHalInterfaceType *piVAdcHal, uint32 *puCode);
pm_err_flag_type VAdcHalDumpRegisters(VAdcHalInterfaceType *piVAdcHal, VAdcHalRegDumpType *pVAdcRegDump);

#endif /* #ifndef __VADCHAL_H__ */

