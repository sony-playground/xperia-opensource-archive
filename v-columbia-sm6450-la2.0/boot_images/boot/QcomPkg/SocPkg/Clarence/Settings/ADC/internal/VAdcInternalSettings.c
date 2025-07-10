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

  $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Settings/ADC/internal/VAdcInternalSettings.c#1 $

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
extern VAdcChannelConfigType gVAdcChannelsPM8350[];
extern VAdcChannelConfigType gVAdcChannelsPM8350B[];
extern VAdcChannelConfigType gVAdcChannelsPM7250B[];
extern VAdcChannelConfigType gVAdcChannelsPMI632[];

extern uint32 guNumVAdcChannelsPMK8350;
extern uint32 guNumVAdcChannelsPM8350;
extern uint32 guNumVAdcChannelsPM8350B;
extern uint32 guNumVAdcChannelsPM7250B;
extern uint32 guNumVAdcChannelsPMI632;

extern const char gVAdcDTPathPM8350b[];

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
/*
 * This table is a mapping of ADC channels to GPIO inputs.
 */
static uint8 aucAmux5GpioChans[] = {0x5, 0x25, 0x45, 0x65};
static uint8 aucAmux6GpioChans[] = {0x6, 0x26, 0x46, 0x66};
static uint8 aucAmux7GpioChans[] = {0x7, 0x27, 0x47, 0x67};
static uint8 aucAmux8GpioChans[] = {0x8, 0x28, 0x48, 0x68};
static uint8 aucAmux9GpioChans[] = {0x9, 0x29, 0x49, 0x69};
static uint8 aucAmuxaGpioChans[] = {0xa, 0x2a, 0x4a, 0x6a};
static uint8 aucAmuxbGpioChans[] = {0xb, 0x2b, 0x4b, 0x6b};
static uint8 aucAmuxcGpioChans[] = {0xc, 0x2c, 0x4c, 0x6c};
static uint8 aucAmuxdGpioChans[] = {0xd, 0x2d, 0x4d, 0x6d};

/*----------------------------------------------------------------------------
 * PMK8350 Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPMK8350[] =
{
   {
      .paucChannels = aucAmux5GpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmux5GpioChans),
      .eGpio        = PM_GPIO_1,
      .uPmicId      = 0,
   },

   {
      .paucChannels = aucAmux6GpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmux6GpioChans),
      .eGpio        = PM_GPIO_2,
      .uPmicId      = 0,
   },

   {
      .paucChannels = aucAmux7GpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmux7GpioChans),
      .eGpio        = PM_GPIO_3,
      .uPmicId      = 0,
   },

   {
      .paucChannels = aucAmux8GpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmux8GpioChans),
      .eGpio        = PM_GPIO_4,
      .uPmicId      = 0,
   },
};

const VAdcBspType VAdcBspPMK8350[] =
{
   {
      .pszDTPath               = NULL,
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

/*----------------------------------------------------------------------------
 * PM8350 Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPM8350[] =
{
   {
      .paucChannels = aucAmux8GpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmux8GpioChans),
      .eGpio        = PM_GPIO_1,
      .uPmicId      = 1,
   },

   {
      .paucChannels = aucAmuxaGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxaGpioChans),
      .eGpio        = PM_GPIO_2,
      .uPmicId      = 1,
   },

   {
      .paucChannels = aucAmuxbGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxbGpioChans),
      .eGpio        = PM_GPIO_3,
      .uPmicId      = 1,
   },

   {
      .paucChannels = aucAmuxcGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxcGpioChans),
      .eGpio        = PM_GPIO_4,
      .uPmicId      = 1,
   },

   {
      .paucChannels = aucAmuxdGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxdGpioChans),
      .eGpio        = PM_GPIO_5,
      .uPmicId      = 1,
   },
};

const VAdcBspType VAdcBspPM8350[] =
{
   {
      .pszDTPath               = NULL,
      .paChannels              = gVAdcChannelsPM8350,
      .puNumChannels           = &guNumVAdcChannelsPM8350,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPM8350,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPM8350),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x4000,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 0,
      .uPeripheralId           = 0x31,
      .uMasterID               = 0,
      .ucPmicDevice            = 1,
   }
};

/*----------------------------------------------------------------------------
 * PM8350B Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPM8350B[] =
{
   {
      .paucChannels = aucAmuxaGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxaGpioChans),
      .eGpio        = PM_GPIO_1,
      .uPmicId      = 3,
   },

   {
      .paucChannels = aucAmuxbGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxbGpioChans),
      .eGpio        = PM_GPIO_2,
      .uPmicId      = 3,
   },

   {
      .paucChannels = aucAmuxcGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxcGpioChans),
      .eGpio        = PM_GPIO_3,
      .uPmicId      = 3,
   },

   {
      .paucChannels = aucAmuxdGpioChans,
      .uNumChannels = ARRAY_LENGTH(aucAmuxdGpioChans),
      .eGpio        = PM_GPIO_4,
      .uPmicId      = 3,
   },
};

const VAdcBspType VAdcBspPM8350B[] =
{
   {
      .pszDTPath               = NULL, //gVAdcDTPathPM8350b,
      .paChannels              = gVAdcChannelsPM8350B,
      .puNumChannels           = &guNumVAdcChannelsPM8350B,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPM8350B,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPM8350B),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x4000,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 0,
      .uPeripheralId           = 0x31,
      .uMasterID               = 0,
      .ucPmicDevice            = 3,
   }
};

/*----------------------------------------------------------------------------
 * PM7250B Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPM7250B[] =
{
   
};

const VAdcBspType VAdcBspPM7250B[] =
{
   {
	  .pszDTPath               = NULL, 
      .paChannels              = gVAdcChannelsPM7250B,
      .puNumChannels           = &guNumVAdcChannelsPM7250B,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPM7250B,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPM7250B),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x70E4,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 8,
      .uPeripheralId           = 0x31,
      .uMasterID               = 0,
      .ucPmicDevice            = 8,
   }
};

/*----------------------------------------------------------------------------
 * PMI632 Settings
 * -------------------------------------------------------------------------*/
static VAdcGpioChannelMappingType vAdcGpioChannelMappingsPMI632[] =
{
   
};

const VAdcBspType VAdcBspPMI632[] =
{
   {
	  .pszDTPath               = NULL, 
      .paChannels              = gVAdcChannelsPMI632,
      .puNumChannels           = &guNumVAdcChannelsPMI632,
      .paAveragedChannels      = NULL,
      .puNumAveragedChannels   = NULL,
      .paGpioChannelMappings   = vAdcGpioChannelMappingsPMI632,
      .uNumGpioChannelMappings = ARRAY_LENGTH(vAdcGpioChannelMappingsPMI632),
      .bUsesInterrupts         = FALSE,
      .uFullScale_code         = 0x70E4,
      .uFullScale_uV           = 1875000,
      .uFullRatiometric_code   = 0x70E4,
      .uReadTimeout_us         = 500000,
      .uLDOSettlingTime_us     = 67,
      .uSlaveId                = 2,
      .uPeripheralId           = 0x31,
      .uMasterID               = 0,
      .ucPmicDevice            = 2,
   }
};