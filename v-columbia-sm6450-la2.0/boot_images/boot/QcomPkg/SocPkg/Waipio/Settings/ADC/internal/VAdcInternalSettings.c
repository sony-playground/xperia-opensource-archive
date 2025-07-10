/*============================================================================
  FILE:         VAdcInternalSettings.c

  OVERVIEW:     Internal settings for VADC.

  DEPENDENCIES: None

                Copyright (c) 2017-2021 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Settings/ADC/internal/VAdcInternalSettings.c#4 $

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
extern VAdcChannelConfigType gVAdcChannelsPMK8350[];
extern uint32 guNumVAdcChannelsPMK8350;

extern const char gVAdcDTPathPM8350b[];

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * PMK8350 Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPMK8350[] =
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
};

const VAdcBspType VAdcBspPMK8350[] =
{
   {
      .pszDTPath               = gVAdcDTPathPM8350b,
      .paChannels              = gVAdcChannelsPMK8350,
      .puNumChannels           = &guNumVAdcChannelsPMK8350,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPMK8350,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPMK8350),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x4000,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 0,
      .uPeripheralId           = 0x31,
      .uMasterID               = 0,
      .ucPmicDevice            = 0,
   }
};

