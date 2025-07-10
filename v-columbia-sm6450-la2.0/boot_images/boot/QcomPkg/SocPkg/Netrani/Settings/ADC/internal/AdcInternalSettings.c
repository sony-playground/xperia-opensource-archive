/*============================================================================
  FILE:         AdcInternalSettings.c

  OVERVIEW:     Internal settings for ADC.

  DEPENDENCIES: None

                Copyright (c) 2017-2022 Qualcomm Technologies, Inc.
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
  2017-11-16  jjo  Initial version.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "AdcBsp.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*
 * PMK8350, PM8350B
 */
static const AdcPhysicalDeviceType adcPhysicalDevices_PMK8350_PM8350B[] =
{
   {
      .pszDevName = "/vadc/pmk8350",
   },

   {
      .pszDevName = "/vadc/pm8350b",
   },
};

const AdcBspType AdcBsp_PMK8350_PM8350B[] =
{
   {
      .paAdcPhysicalDevices = adcPhysicalDevices_PMK8350_PM8350B,
      .uNumDevices          = ARRAY_LENGTH(adcPhysicalDevices_PMK8350_PM8350B)
   }
};

/*
 * PMK only
 */
static const AdcPhysicalDeviceType adcPhysicalDevices_PMK8350[] =
{
   {
      .pszDevName = "/vadc/pmk8350",
   },
};

const AdcBspType AdcBsp_PMK8350[] =
{
   {
      .paAdcPhysicalDevices = adcPhysicalDevices_PMK8350,
      .uNumDevices          = ARRAY_LENGTH(adcPhysicalDevices_PMK8350)
   }
};

