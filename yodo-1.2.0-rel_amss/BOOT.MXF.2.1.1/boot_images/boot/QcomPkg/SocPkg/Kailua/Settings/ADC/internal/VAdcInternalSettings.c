/*============================================================================
  FILE:         VAdcInternalSettings.c

  OVERVIEW:     Internal settings for VADC.

  DEPENDENCIES: None

                Copyright (c) 2017-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/dev/core.boot/6.1/hadigal.core.boot.6.1.kai_pmic_adc_boot/QcomPkg/SocPkg/Kailua/Settings/ADC/internal/VAdcInternalSettings.c#1 $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-11-10  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "VAdcBsp.h"
#include "AdcInputs.h"

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
#if 0
extern VAdcChannelConfigType gVAdcChannelsPMK8550[];
extern uint32 guNumVAdcChannelsPMK8550;

extern const char gVAdcDTPathPM8550b[];

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * PMK8550 Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPMK8550[] =
{
   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_1,
      .uPmicId      = 0,
   },

   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_2,
      .uPmicId      = 0,
   },

   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_3,
      .uPmicId      = 0,
   },

   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_4,
      .uPmicId      = 0,
   },
   
   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_5,
      .uPmicId      = 0,
   },

   {
      .paucChannels = NULL,
      .uNumChannels = 0,
      .eGpio        = PM_GPIO_6,
      .uPmicId      = 0,
   },
};

const VAdcBspType VAdcBspPMK8550[] =
{
   {
      .pszDTPath               = gVAdcDTPathPM8550b,
      .paChannels              = gVAdcChannelsPMK8550,
      .puNumChannels           = &guNumVAdcChannelsPMK8550,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPMK8550,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPMK8550),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x4000,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 0,
      .uPeripheralId           = 0x90,
      .uMasterID               = 0,
      .ucPmicDevice            = 0,
   }
};
#endif
