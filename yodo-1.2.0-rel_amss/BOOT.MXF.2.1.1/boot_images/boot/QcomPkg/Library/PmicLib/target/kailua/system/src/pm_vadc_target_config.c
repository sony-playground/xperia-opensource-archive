/*============================================================================
  FILE:         pm_vadc_target_config.c

  OVERVIEW:     VADC target config data (bare-metal)

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------

============================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_vadc_target_config.h"
#include "CoreVerify.h"
#include "pm_utils.h"
#include "pm_dt_parser.h"

/*===========================================================================

                        MACRO AND TYPE DECLARATIONS 

===========================================================================*/
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))
#define MAX_DEVICES     2

enum {
  ADC_BSP_DEFAULT,
  ADC_BSP_PMK8550 = ADC_BSP_DEFAULT,
  ADC_BSP_PMK8550_PM8550B,
};

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
static const AdcPhysicalDeviceType adcPhysicalDevices_PMK8550_PM8550B[] =
{
   {
      .eDeviceId = ADC_BSP_PMK8550,
   },

   {
      .eDeviceId = ADC_BSP_PMK8550_PM8550B,
   },
};

const AdcBspType AdcBsp_PMK8550_PM8550B[] =
{
   {
      .paAdcPhysicalDevices = adcPhysicalDevices_PMK8550_PM8550B,
      .uNumDevices          = ARRAY_LENGTH(adcPhysicalDevices_PMK8550_PM8550B)
   }
};

/*
 * PMK only
 */
static const AdcPhysicalDeviceType adcPhysicalDevices_PMK8550[] =
{
   {
      .eDeviceId = ADC_BSP_PMK8550,
   }
};

const AdcBspType AdcBsp_PMK8550[] =
{
   {
      .paAdcPhysicalDevices = adcPhysicalDevices_PMK8550,
      .uNumDevices          = ARRAY_LENGTH(adcPhysicalDevices_PMK8550)
   }
};

const char* vadcDTPath[MAX_DEVICES] = {
                                        "/sw/pmic/adc/vadc/spmi-vadc@7",
                                      };

/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/
AdcBspType* 
pm_vadc_target_get_adc_bsp (uint32 bspId)
{
  static AdcBspType* adcBsp = NULL;
  DALResult rst;
  
  if (!adcBsp)
  {
    rst = DALSYS_Malloc(sizeof(*adcBsp),(VOID **)&adcBsp);

    if (rst != DAL_SUCCESS)
    {
      return NULL;
    }

    switch (bspId)
    {
      case ADC_BSP_PMK8550:
        adcBsp->paAdcPhysicalDevices = adcPhysicalDevices_PMK8550;
        adcBsp->uNumDevices = ARRAY_LENGTH(adcPhysicalDevices_PMK8550);
        break;
      case ADC_BSP_PMK8550_PM8550B:
        adcBsp->paAdcPhysicalDevices = adcPhysicalDevices_PMK8550_PM8550B;
        adcBsp->uNumDevices = ARRAY_LENGTH(adcPhysicalDevices_PMK8550_PM8550B);
        break;
      default:
        adcBsp->paAdcPhysicalDevices = NULL;
        adcBsp->uNumDevices = 0;
        break;
    }
  }

  return adcBsp;
}

uint32 
pm_vadc_target_get_adc_bsp_id (void)
{
  /*TODO: probably read value from DT if OEM wants to pick other supported
   * device config BSP data */
  return ADC_BSP_PMK8550;
}

const char* 
pm_vadc_target_get_dt_path (uint32 deviceId)
{
  return vadcDTPath[deviceId];
}

