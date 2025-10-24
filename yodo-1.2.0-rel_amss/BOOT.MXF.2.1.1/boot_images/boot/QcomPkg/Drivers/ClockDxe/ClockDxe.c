/** @file ClockDxe.c

  This file implements clock EFI protocol interface.
  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/10/21   am      Removed support for DDIClock Interface.
 01/08/18   op      Update Clock Register Exit Boot Service Callback
 03/14/17   op      Add Dump Clock's state
 10/18/14   jb      Added DAL initialization
 05/01/14   asmitp  Renamed header file DALSYSProtocol.h to EFIDALSYSProtocol.h
 12/23/10   vs      Created.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include "Clock.h"
#include "ClockDriverImage.h"
#include "ClockFileLog.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Mapping of ClockResults for EFIClock.h Users
 */
static __inline EFI_STATUS CLOCK_RESULT__TO__EFI_STATUS
(
  ClockResult Status
)
{
    switch (Status)
    {
        case CLOCK_SUCCESS:
            return EFI_SUCCESS;

        case CLOCK_ERROR_NOT_FOUND:
            return EFI_NOT_FOUND;

        case CLOCK_ERROR_NOT_ALLOWED:
            return EFI_ACCESS_DENIED;

        case CLOCK_ERROR_NOT_SUPPORTED:
            return EFI_UNSUPPORTED;

        case CLOCK_ERROR_NOT_INITIALIZED:
            return EFI_NOT_STARTED;

        case CLOCK_ERROR_INSUFFICIENT_MEMORY:
            return EFI_BUFFER_TOO_SMALL;

        case CLOCK_ERROR_INSUFFICIENT_BUFFER_LEN:
            return EFI_BAD_BUFFER_SIZE;

        case CLOCK_ERROR_OUT_OF_RANGE_PARAMETER:
        case CLOCK_ERROR_INVALID_PARAMETER:
            return EFI_INVALID_PARAMETER;

        case CLOCK_ERROR:
        case CLOCK_ERROR_INTERNAL:
        case CLOCK_ERROR_INVALID_ADDRESS:
        default:
            return EFI_PROTOCOL_ERROR;
    }
}


/*=========================================================================
      Function Prototypes
==========================================================================*/

EFI_STATUS EFI_GetID(IN EFI_CLOCK_PROTOCOL *This,
                     IN CONST CHAR8 *Name, OUT UINTN *ClockId);
EFI_STATUS EFI_Enable(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId);
EFI_STATUS EFI_Disable(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId);
EFI_STATUS EFI_IsEnabled(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                              OUT BOOLEAN *IsEnabled);
EFI_STATUS EFI_IsOn(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                         OUT BOOLEAN *IsOn);
EFI_STATUS EFI_SetClockFreqHz(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                              IN UINT32 FreqHz,
                              IN EFI_CLOCK_FREQUENCY_TYPE  Match,
                              OUT UINT32 *ResultFreqHz);
EFI_STATUS EFI_GetClockFreqHz(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                              OUT UINT32 *FreqHz);
EFI_STATUS EFI_CalcClockFreqHz(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                               OUT UINT32 *FreqHz);
EFI_STATUS EFI_MeasureFreqHz(IN  EFI_CLOCK_PROTOCOL *This,
                             IN  UINTN              ClockId,
                             IN  UINTN              DebugMuxSel,
                             OUT UINT32             *FreqHz);
EFI_STATUS EFI_SelectExternalSource(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                                    IN UINT32 FreqHz, IN UINT32 Source,
                                    IN UINT32 Divider, IN UINT32 VAL_M,
                                    IN UINT32 VAL_N, IN UINT32 VAL_2D);
EFI_STATUS EFI_EnterLowPowerMode(IN EFI_CLOCK_PROTOCOL *This);
EFI_STATUS EFI_ExitLowPowerMode(IN EFI_CLOCK_PROTOCOL *This);
EFI_STATUS EFI_SetClockDivider(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                               IN UINT32 Divider);
EFI_STATUS EFI_ResetClock(IN EFI_CLOCK_PROTOCOL *This, IN UINTN ClockId,
                          IN EFI_CLOCK_RESET_TYPE eReset);

EFI_STATUS EFI_GetMaxPerfLevel(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU, OUT UINT32 *pnPerfLevel);
EFI_STATUS EFI_GetMinPerfLevel(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU, OUT UINT32 *pnPerfLevel);
EFI_STATUS EFI_GetCpuPerfLevelFrequency(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU,
                                        IN UINT32 nPerfLevel, OUT UINT32 *pnFrequencyHz,
                                        OUT UINT32 *pnRequiredVoltage);
EFI_STATUS EFI_SetCpuPerfLevel(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU,
                               IN UINT32 nPerfLevel, OUT UINT32 *pnFrequencyHz);
EFI_STATUS EFI_GetCpuPerfLevel(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU, OUT UINT32 *pnPerfLevel);
EFI_STATUS EFI_GetCPUFrequencyLevels(IN  EFI_CLOCK_PROTOCOL *This, IN  UINT32 nCPU,
                                        OUT UINT32 *pnFrequencyLevels);
EFI_STATUS EFI_GetCPUFrequencyPlan(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU,
                                      IN EFI_CLOCK_FREQ_PLAN_TYPE  *pCPUFreqPlan, IN UINT32 nSize);
EFI_STATUS EFI_SetCPUFrequency(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU, IN UINT32 nFrequencyHz, OUT UINT32 *pnResultFreqHz);
EFI_STATUS EFI_GetCPUFrequency(IN EFI_CLOCK_PROTOCOL *This, IN UINT32 nCPU, OUT UINT32 *pnFrequencyHz);
EFI_STATUS EFI_PostInit(IN EFI_CLOCK_PROTOCOL *This);
EFI_STATUS EFI_ResetClockBranch(IN EFI_CLOCK_PROTOCOL *This,IN UINTN ClockId,IN EFI_CLOCK_RESET_TYPE   eReset);
EFI_STATUS EFI_InvertClock(IN EFI_CLOCK_PROTOCOL *This,IN UINTN ClockId,IN BOOLEAN invert);


EFI_STATUS EFI_LogClocksState(IN EFI_TEST_CLOCK_PROTOCOL *This, IN UINT32 nFlag);

EFI_STATUS EFI_DumpClocksState(IN EFI_TEST_CLOCK_PROTOCOL *This, IN UINT32 nFlag);



/*=========================================================================
      Data Declarations
==========================================================================*/

// Clock Public Protocol
static EFI_CLOCK_PROTOCOL ClockProtocol =
{
   EFI_CLOCK_PROTOCOL_VERSION,
   EFI_GetID,
   EFI_Enable,
   EFI_Disable,
   EFI_IsEnabled,
   EFI_IsOn,
   EFI_SetClockFreqHz,
   EFI_GetClockFreqHz,
   EFI_CalcClockFreqHz,
   EFI_SelectExternalSource,
   EFI_GetID,
   EFI_Enable,
   EFI_Disable,
   EFI_EnterLowPowerMode,
   EFI_ExitLowPowerMode,
   EFI_SetClockDivider,
   EFI_ResetClock,
   EFI_GetMaxPerfLevel,
   EFI_GetMinPerfLevel,
   EFI_GetCpuPerfLevelFrequency,
   EFI_SetCpuPerfLevel,
   EFI_GetCpuPerfLevel,
   EFI_GetCPUFrequencyLevels,
   EFI_GetCPUFrequencyPlan,
   EFI_SetCPUFrequency,
   EFI_GetCPUFrequency,
   EFI_PostInit,
   EFI_GetID,
   EFI_ResetClockBranch,
   EFI_InvertClock,
   EFI_MeasureFreqHz,
   EFI_GetID,
 };


// Clock Public Protocol
static EFI_TEST_CLOCK_PROTOCOL TestClockProtocol =
{
   EFI_TEST_CLOCK_PROTOCOL_VERSION,
   EFI_LogClocksState,
   EFI_DumpClocksState
};

static ClockHandle      hClient = (ClockHandle)NULL;

/*==============================================================================

                     GLOBAL VARIABLES FOR THIS MODULE

==============================================================================*/

/* Exit Boot Services vars */
extern EFI_GUID gEfiEventExitBootServicesGuid;

EFI_EVENT  ClockExitBSEvent             = (EFI_EVENT)NULL;

VOID      *VarProtocolNotificationToken =  NULL;
EFI_EVENT  VarProtocolNotificationEvent = (EFI_EVENT) NULL;


/*=========================================================================
      Functions
==========================================================================*/


/**
  Looks up a ID for clock component specified with name.
  Component can be: Source, PowerDomain, Clock, Divider, Debug Mux.

  This function takes the name of a component and returns a handle that
  can be used for making requests on that component.
  The string name of the clock can be found in the software frequency plan,
  e.g., cc_uart2_clk.

  @param  This      [in]        The EFI_CLOCK_PROTOCOL instance.
  @param  Name      [in]        String name of the clock.
  @param  ClockId   [out]       Pointer to fill in with the clock id.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_GetID(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  CONST CHAR8        *Name,
   OUT UINTN              *ClockId)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetId(hClient, Name, (ClockIdType *)ClockId)
  );
}


/**
  Enables a clock.

  This function will enable the given clock.  It does not reference count
  recursive calls, but does do tracking between multiple clients.

  @param  This    [in]          The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId [in]          Clock to enable.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_Enable(
   IN EFI_CLOCK_PROTOCOL *This,
   IN UINTN              ClockId)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_Enable(hClient, (ClockIdType)ClockId)
  );
}


/**
  Disables a clock.

  This function will remove the client's vote to enable the given clock.
  There is no support for reference counting recursive calls, however the
  driver will not disable the clock if a different client has made an
  "enable" request.

  @param  This    [in]          The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId [in]          Clock to disable.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_Disable(
   IN EFI_CLOCK_PROTOCOL *This,
   IN UINTN              ClockId)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_Disable(hClient, (ClockIdType)ClockId)
  );
}


/**
  Check the enabled state of a clock.

  This function checks if the given clock is enabled or disabled.  Note
  that this is not necessarily equivalent to the clock being active.  A
  clock may be disabled by the local processor, but enabled by another one.
  Or if the hardware is misconfigured the clock may be enabled, but not
  actively toggling.

  @param  This      [in]        The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId   [in]        Clock to check.
  @param  IsEnabled [out]       Return 1 if clock is enabled, 0 otherwise.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_IsEnabled(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  UINTN              ClockId,
   OUT BOOLEAN            *IsEnabled)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_IsEnabled(hClient, (ClockIdType)ClockId, (bool*)IsEnabled)
  );
}


/**
  Check if a clock is on or not.

  This function checks if the given clock is on or not.  "On"
  means the clock is not just enabled, but is actually toggling.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId  [in]         Clock to check.
  @param  IsOn     [out]        Return 1 if clock is ON, 0 otherwise.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_IsOn(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  UINTN              ClockId,
   OUT BOOLEAN            *IsOn)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_IsOn(hClient, (ClockIdType)ClockId, (bool*)IsOn)
  );
}


/**
  Sets the frequency of a clock.

  This function will request a frequency change for the given clock.  The
  driver will select the exact frequency based on the matching argument,
  which allows requesting a minimum or approximate frequency for
  example. There is no support for concurrent requests - the
  last request will be serviced and override any other minimum
  frequency requests.

  @param  This         [in]     The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId      [in]     Clock to set frequency of.
  @param  Freq         [in]     Clock frequency
  @param  Match        [in]     Type of match request:
                                0 - Frequency is a minimum allowed
                                1 - Frequency is a maximum allowed
                                2 - Closest match
                                3 - Exact match only
  @param  ResultFreq   [out]    The programmed clock frequency,
                                can be NULL if resulting
                                frequency does not need to be
                                checked.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_SetClockFreqHz(
   IN  EFI_CLOCK_PROTOCOL        *This,
   IN  UINTN                     ClockId,
   IN  UINT32                    Freq,
   IN  EFI_CLOCK_FREQUENCY_TYPE  Match,
   OUT UINT32                   *ResultFreq)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_SetFrequency(hClient, (ClockIdType)ClockId, Freq,
                       (ClockFrequencyType)Match, ResultFreq)
  );
}


/**
  Get the frequency of a clock.

  This function retrieves the current frequency of a clock in Hertz.  This
  is independent of if the clock is running or not.  Note only clocks
  controlled on the local processor can have the frequency retrieved.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId  [in]         Clock to check.
  @param  FreqHz   [out]        Pointer to uint32 to fill
                                in with the frequency. A value
                                of zero indicates the frequency
                                could not be determined.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_GetClockFreqHz(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  UINTN              ClockId,
   OUT UINT32             *FreqHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetFrequency (hClient, (ClockIdType)ClockId, FreqHz)
  );
}


/**
  Calculate the frequency of a clock.

  This function calculates the current frequency of a clock in Hertz using
  hardware counting circuits.  This functionality depends on this hardware
  support being present, as well as available on the current processor.  It
  also requires that the clock be enabled, which must be possible from
  the current environment.
  The frequency calculation is accurrate to within a few KHz.
  The calculation takes a long time (at least a few milliseconds) and
  is intended only for testing purposes, not any real modes of operation.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId  [in]         Clock to check.
  @param  FreqHz   [out]        Pointer to uint32 to fill
                                in with the frequency. A value
                                of zero indicates the frequency
                                could not be determined.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_CalcClockFreqHz(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  UINTN              ClockId,
   OUT UINT32             *FreqHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_MeasureFrequency(hClient, (ClockIdType)ClockId, FreqHz)
  );
}


/**
  Calculates the frequency of a clock.

  This function calculates(Probe) the current frequency of a clock in hertz using
  hardware counting circuits. This functionality depends on the hardware
  support being present, as well as available on the current processor. It
  also requires that the clock be enabled.
  This function is only for measure those clock 
  which are not managed by current processor.
  The frequency calculation is accurate to within a few kilohertz.
  The calculation takes a long time (at least a few milliseconds) and
  is intended only for testing purposes, not any real modes of operation.

  @param[in]  This                  Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]  ClockId               Clock to check.
  @param[in]  DebugMuxSel           Debug-mux Line/Pin number.
  @param[out] FreqHz                Pointer to the UINT32 to be filled
                                    in with the frequency. A value
                                    of zero indicates that the frequency
                                    could not be determined.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_MeasureFreqHz(
   IN  EFI_CLOCK_PROTOCOL *This,
   IN  UINTN              ClockId,
   IN  UINTN              DebugMuxSel,
   OUT UINT32             *FreqHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_MeasureFrequencyEx(hClient, (ClockIdType)ClockId, DebugMuxSel, FreqHz)
  );
}


/**
  Select an external source for a clock.

  This function will select an external source for a clock, and configure
  the clock generator dividers.  This is only necessary for clock domains
  that can be derived from a source outside of the clock block such that
  EFI_SetClockFreqHz cannot be used.
  Note that the caller must specify a non-zero value for the source clock's
  frequency if the caller expects the clock driver to provide voltage scaling
  support.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId  [in]         Clock to check.
  @param  FreqHz   [in]         Source frequency in Hz. The value '0' indicates that
                                voltage scaling is not expected for this source.
  @param  Source   [in]         Source to use.  Pass the following values:
                                0 - to select the first (or only) external source.
                                1 - to select the second external source.
                                2 - etc.
  @param  Divider  [in]         The integer divider to use.
  @param  VAL_M    [in]         The "M" value for any M/N counter (0 to bypass).
                                Not all clock domains have M/N counters,and these values
                                will be ignored.
  @param  VAL_N    [in]         The "N" value for any M/N counter.
  @param  VAL_2D   [in]         Twice the "D" value for any M/N counter.
                                The raw value is doubled to allow for
                                half-integer duty cycles.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
*/

EFI_STATUS
EFI_SelectExternalSource(
    IN EFI_CLOCK_PROTOCOL *This,
    IN UINTN              ClockId,
    IN UINT32             FreqHz,
    IN UINT32             Source,
    IN UINT32             Divider,
    IN UINT32             VAL_M,
    IN UINT32             VAL_N,
    IN UINT32             VAL_2D)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_SelectExternalSource(hClient, (ClockIdType)ClockId, FreqHz,
                               Source, Divider, VAL_M, VAL_N, VAL_2D)
  );
}


/**
  Enter the low power mode.

  This function is used to enter a low power state that facilitates
  rapid battery charging.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
*/

EFI_STATUS
EFI_EnterLowPowerMode(
    IN EFI_CLOCK_PROTOCOL *This)
{
  return CLOCK_RESULT__TO__EFI_STATUS(CLOCK_ERROR_NOT_SUPPORTED);
}


/**
  Exit the low power mode.

  This function restores the state of the SoC to the state it was in before
  it entered a low power state that facilitates rapid battery charging.

  @param  This     [in]         The EFI_CLOCK_PROTOCOL instance.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
*/

EFI_STATUS
EFI_ExitLowPowerMode(
    IN EFI_CLOCK_PROTOCOL *This)
{
  return CLOCK_RESULT__TO__EFI_STATUS(CLOCK_ERROR_NOT_SUPPORTED);
}


/**
  Sets the divider for a clock.

  This function programs the divider for a specified clock. This
  functionality only applies to a small subset of clocks that have
  independent dividers off the main domain.

  @param  This         [in]     The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId      [in]     Clock to set divider of.
  @param  Divider      [in]     Clock divider.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_SetClockDivider(
   IN  EFI_CLOCK_PROTOCOL        *This,
   IN  UINTN                     ClockId,
   IN  UINT32                    Divider)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_SetDivider(hClient, (ClockIdType)ClockId, Divider)
  );
}


/**
  Resets a specified clock's hardware.

  This function allows resetting the hardware in a specified clock domain. The
  resetting is destructive to the hardware and requires reconfiguration
  after the reset is deasserted.

  @param  This    [in]          The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId [in]          Clock to reset.
  @param  eReset  [in]          Type of reset: assert, deassert, or pulse.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_ResetClock(
   IN EFI_CLOCK_PROTOCOL   *This,
   IN UINTN                 ClockId,
   IN EFI_CLOCK_RESET_TYPE  eReset)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_ResetBlock(hClient, (ClockIdType)ClockId, (ClockResetType)eReset)
  );
}

/**
  Returns the maximum perf level supported for the given CPU Core or Cluster.

  @param[in]   This               Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU               CPU Core or Cluster ID
  @param[out]  pnPerfLevel        Pointer to the UINT32 to be filled
                                  in with the maximum perf level supported
                                  for this Core or Cluster.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetMaxPerfLevel(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINT32              nCPU,
  OUT UINT32             *pnPerfLevel)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetMaxPerfLevel(nCPU, pnPerfLevel)
  );
}

/**
  Returns the minimum perf level supported for the given CPU Core or Cluster.

  @param[in]   This               Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU               CPU Core or Cluster ID
  @param[out]  pnPerfLevel        Pointer to the UINT32 to be filled
                                  in with the minimum perf level supported
                                  for this Core or Cluster.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetMinPerfLevel(
   IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINT32               nCPU,
  OUT UINT32              *pnPerfLevel)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetMinPerfLevel(nCPU, pnPerfLevel)
  );
}

/**
  Returns the frequency and voltage associated with the given perf level for
  the given CPU Core or Cluster.

  @param[in]   This               Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU               CPU Core or Cluster ID
  @param[in]   nPerfLevel         Perf Level under query.
  @param[out]  pnFrequencyHz      Pointer to the associated frequency.
  @param[out]  pnRequiredVoltage  Pointer to the associated voltage.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetCpuPerfLevelFrequency(
  IN  EFI_CLOCK_PROTOCOL *This,
  IN  UINT32              nCPU,
  IN  UINT32              nPerfLevel,
  OUT UINT32             *pnFrequencyHz,
  OUT UINT32             *pnRequiredVoltage)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetCpuPerfLevelFrequency(nCPU, nPerfLevel, pnFrequencyHz, pnRequiredVoltage)
  );
}

/**
  Sets the desired perf level for the given CPU Core or Cluster.

  @param[in]   This               Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU               CPU Core or Cluster ID
  @param[in]   nPerfLevel         Desired Perf Level.
  @param[out]  pnFrequencyHz      Pointer to the actual frequency achieved.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_SetCpuPerfLevel(
  IN  EFI_CLOCK_PROTOCOL  *This,
  IN  UINT32               nCPU,
  IN  UINT32               nPerfLevel,
  OUT UINT32              *pnFrequencyHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_SetCpuPerfLevel(nCPU, nPerfLevel, pnFrequencyHz)
  );
}

/**
  Gets the current perf level of the given CPU Core or Cluster.

  @param[in]   This               Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU               CPU Core or Cluster ID
  @param[out]  pnPerfLevel        Pointer to the current Perf Level.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetCpuPerfLevel(
  IN  EFI_CLOCK_PROTOCOL  *This,
  IN  UINT32               nCPU,
  OUT UINT32              *pnPerfLevel)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetCpuPerfLevel(nCPU, pnPerfLevel)
  );
}

/**
  Gets the number of frequency levels available for the given CPU Core or Cluster.

  @param[in]   This                 Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU                 CPU Core or Cluster ID
  @param[out]  pnFrequencyLevels     Pointer to the number of frequency levels.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetCPUFrequencyLevels(
  IN  EFI_CLOCK_PROTOCOL  *This,
  IN  UINT32               nCPU,
  OUT UINT32              *pnFrequencyLevels)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetCPUFrequencyLevels(nCPU, pnFrequencyLevels)
  );
}

/** 
  Dumps the frequency plan for the specified CPU in the Table passed as pointer.

  @param[in]   This                 Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU                 CPU Core or Cluster ID
  @param[in]   pCPUFreqPlan         Pointer to the table storing the frequency plan.
  @param[in]   nSize                Size of the Frequency plan table, expected value to be: (No. of Perf Levels * sizeof(ClockFreqPlanType))
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetCPUFrequencyPlan(
  IN  EFI_CLOCK_PROTOCOL        *This,
  IN  UINT32                     nCPU,
  IN  EFI_CLOCK_FREQ_PLAN_TYPE  *pCPUFreqPlan,
  IN  UINT32                     nSize)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetCPUFrequencyPlan(nCPU, (ClockFreqPlanType*)pCPUFreqPlan, nSize)
  );
}


/** 
  Changes the processor clock speed and voltage.
  
  @param[in]   This                 Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU                 CPU Core or Cluster ID
  @param[in]   nFrequencyHz         User requested frequency
  @param[out]  pnFrequencyHz        Pointer to the actual frequency achieved.(It is an optional parameter)

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/


EFI_STATUS
EFI_SetCPUFrequency(
  IN  EFI_CLOCK_PROTOCOL    *This,
  IN  UINT32                 nCPU,
  IN  UINT32                 nFrequencyHz,
  OUT  UINT32               *pnResultFreqHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_SetCPUFrequency(nCPU, nFrequencyHz, pnResultFreqHz)
  );
}

/**
  Gets the current clock speed in Hz of the given processor.

  @param[in]   This                 Pointer to the EFI_CLOCK_PROTOCOL instance.
  @param[in]   nCPU                 CPU Core or Cluster ID
  @param[out]  pnFrequencyHz        Pointer to the actual frequency achieved.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

EFI_STATUS
EFI_GetCPUFrequency(
  IN  EFI_CLOCK_PROTOCOL   *This,
  IN  UINT32                nCPU,
  OUT UINT32               *pnFrequencyHz)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_GetCPUFrequency(nCPU, pnFrequencyHz)
  );
}

/**
  Allow flush of all zero bandwidth nodes.

  @par Description
    @param  This      [in]  The EFI_CLOCK_PROTOCOL instance.
 
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
EFI_STATUS
EFI_PostInit(
  IN EFI_CLOCK_PROTOCOL *This
)
{
  return CLOCK_RESULT__TO__EFI_STATUS(CLOCK_ERROR_NOT_SUPPORTED);
}

/**
  Resets a specified clock's branch.

  @param  This    [in]          The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId [in]          Clock to reset.
  @param  eReset  [in]          Type of reset: assert, deassert, or pulse.

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_ResetClockBranch(
   IN EFI_CLOCK_PROTOCOL   *This,
   IN UINTN                 ClockId,
   IN EFI_CLOCK_RESET_TYPE  eReset)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_Reset(hClient, (ClockIdType)ClockId, (ClockResetType)eReset)
  );
}

/**
  Sets the Inversion state for a clock.

  This function allows inverting or uninverting a clock. This is rarely used. It
  is generally used just to overcome timing problems in the hardware.

  @param  This    [in]          The EFI_CLOCK_PROTOCOL instance.
  @param  ClockId [in]          Clock to invert
  @param  Invert  [in]          true or false

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_InvertClock(
   IN EFI_CLOCK_PROTOCOL   *This,
   IN UINTN                 ClockId,
   IN BOOLEAN               Invert)
{
  return CLOCK_RESULT__TO__EFI_STATUS(
    Clock_Invert(hClient, (ClockIdType)ClockId, (bool)Invert)
  );
}

/**
  EFI_LogClocksState

  Read BDSClockLogState in EFI_VARIABLE_NON_VOLATILE. Based on the current BDSClockLogState setting, whether or not
  the clocks states will be dumpped

    @param  This      [in]  The EFI_TEST_CLOCK_PROTOCOL instance.
    @param nLogMask   [in]  used to select clock Characteristic to be dumpped
                            0                               : not dump the Clock frequency
                            CLOCK_LOG_STATE_CLOCK_FREQUENCY : dump the Clock frequency
  @return
  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_LogClocksState(
   IN  EFI_TEST_CLOCK_PROTOCOL *This,
   IN  UINT32                   nLogMask)
{
  return CLOCK_RESULT__TO__EFI_STATUS(CLOCK_ERROR_NOT_SUPPORTED);
}

/**
  EFI_DumpClocksState

  Read BDSClockLogState in ESB menu. Based on the current BDSClockLogState setting, whether or not
  the clocks states will be dumpped

    @param  This      [in]  The EFI_TEST_CLOCK_PROTOCOL instance.
    @param nLogMask   [in]  used to select clock Characteristic to be dumpped
                            0                               : not dump the Clock frequency
                            CLOCK_LOG_STATE_CLOCK_FREQUENCY : dump the Clock frequency
  @return
  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_PROTOCOL_ERROR    The function had a protocol error.
**/

EFI_STATUS
EFI_DumpClocksState(
   IN  EFI_TEST_CLOCK_PROTOCOL *This,
   IN  UINT32                   nLogMask)
{
  return CLOCK_RESULT__TO__EFI_STATUS(CLOCK_ERROR_NOT_SUPPORTED);
}
/**
 * <!-- Exit Boot service CB -->
 *
 * @brief Call Clock destructor
 *
 * @return       VOID
 */
VOID
EFIAPI
ClockRegisterExitBSCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context)
{
  EFI_TEST_CLOCK_PROTOCOL    *pTestClockProtocol;
  BDS_CLOCKLOG_STATE          eEBSClockLogSetting;

  ClockFileLog_GetEBSClockLogSetting(&eEBSClockLogSetting);
  if (eEBSClockLogSetting != BDSClockLogStateDisable)
  {

    gBS->LocateProtocol(&gEfiTestClockProtocolGuid,NULL,
                        (VOID **)&pTestClockProtocol );

    if (pTestClockProtocol == NULL)
    {
      DEBUG((EFI_D_ERROR, "ClockDxe:: %a Error locating Test Clock Protocol \r\n"));
      return;
    }

    if (pTestClockProtocol->LogClocksState(pTestClockProtocol, 0) !=  EFI_SUCCESS)
    {
      DEBUG((EFI_D_ERROR, "ClockDxe:: %a Error locating Test Clock Protocol \r\n"));
    }
  }
}

/**
  VarProtocolInstalledNotification()

  @brief
  Notify  when the variable installed
**/
VOID EFIAPI VarProtocolInstalledNotification
(
  IN EFI_EVENT Event,
  IN VOID     *Context
)
{
  BDS_CLOCKLOG_STATE eLogState;

  ClockFileLog_GetEBSClockLogSetting(&eLogState);
}

/**
  ClockBDSmenuInit

  @brief
  Init Clock BDS menu
**/

VOID EFIAPI ClockBDSmenuInit(void)
{
  EFI_STATUS  status;

  // Set up to be notified when the Var protocol is installed.
  status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL,
                             TPL_CALLBACK,
                             VarProtocolInstalledNotification,
                             NULL,
                             &VarProtocolNotificationEvent);
  ASSERT_EFI_ERROR (status);

  status = gBS->RegisterProtocolNotify (&gEfiVariableServicesProtocolGuid,
                                        VarProtocolNotificationEvent,
                                        (VOID *)&VarProtocolNotificationToken);
  ASSERT_EFI_ERROR (status);


  //Register to Exit Boot Service Event
  gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK,
                        ClockRegisterExitBSCallback,
                        NULL,
                        &gEfiEventExitBootServicesGuid,
                        &ClockExitBSEvent);
}


/**
  Clock DXE driver entry point.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
ClockDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_HANDLE  handle = NULL;
  EFI_STATUS  status;
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();

  /*
    Init DALSys
    DALSYS_InitMod is needed to initlize the gpDALSYSFncPtr otherwise all DALSYS_* api (like  DALSYS_SyncCreate, DALSYS_LogEvent, etc) will stop working
    becouse of check DALMOD_CHECK_UNINIT(gpDALSYSFncPtr, DAL_ERROR) in QcomPkg/Library/DALModEnvLib/DALModEnv.c file
  */
  DALSYS_InitMod(NULL);

  clk_regime_init();
  clk_regime_bist();            // in Q6, the clk_regime_init, clk_regime_bist will be registers as Init api's in build system.
                                // Here, just call init mannually.
  hClient = pDrvCtxt->hClient;

  if (!RETAIL)
  {
       ClockBDSmenuInit();

       // Publish the EFIClock Protocol
       status = gBS->InstallMultipleProtocolInterfaces(
                    &handle,
                    &gEfiClockProtocolGuid,
                    (void **)&ClockProtocol,
                    &gEfiTestClockProtocolGuid,
                    (void **)&TestClockProtocol,
                     NULL );
    }
    else
    {
      // Publish the EFIClock Protocol
       status = gBS->InstallMultipleProtocolInterfaces(
                    &handle,
                    &gEfiClockProtocolGuid,
                    (void **)&ClockProtocol,
                     NULL );
    }

  return status;
}

