#ifndef __PM_VADC_H__
#define __PM_VADC_H__
/*============================================================================
  @file pm_vadc.h

  Function and data structure declarations for pm_vadc


                Copyright (c) 2008-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc_sdam/src/pm_vadc.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "comdef.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "VAdcBsp.h"



/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
enum
{
   VADC_EVENT_DEFAULT = 0,
   VADC_EVENT_TIMEOUT,
   _VADC_NUM_EVENTS
};

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
struct pm_vadc_device;

struct pm_vadc_reg
{
   uint8 offset;
   uint8 val;
};

struct pm_vadc_reg_dump
{
   struct pm_vadc_reg *vadc_regs;
   int32 reg_size;
};

/* Must be identical to the HAL VAdcConversionParameterType*/
typedef struct
{
   uint32 uChannel;
   uint32 eCalMethod;
   uint32 eDecimationRatio;
   uint32 eAverageMode;
   uint32 eSettlingDelay;
   uint32 uAdcSID;
} pm_vadc_channel_cfg;

typedef void VAdcDebugInfoTypeLoc;
struct pm_vadc_log_inf
{
   void (*EOC)(VAdcDebugInfoTypeLoc *);
   void (*Error)(VAdcDebugInfoTypeLoc *, const char *, DALBOOL);
   void (*Interrupt)(VAdcDebugInfoTypeLoc *);
   void (*DumpRegisters)(VAdcDebugInfoTypeLoc *, struct pm_vadc_reg_dump *);
   VAdcDebugInfoTypeLoc *debugCtxt;
};

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
void pm_vadc_register_log_inf(struct pm_vadc_device *,struct pm_vadc_log_inf *);
pm_err_flag_type pm_vadc_device_init(struct pm_vadc_device **,const VAdcBspType *);
pm_err_flag_type pm_vadc_read_adc(struct pm_vadc_device *, const pm_vadc_channel_cfg *, uint32 *);

#endif /* #ifndef __PM_VADC_H__ */

