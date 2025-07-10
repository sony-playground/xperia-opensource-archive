#ifndef CLOCKAPPS_H
#define CLOCKAPPS_H
/*
===========================================================================
*/
/**
  @file ClockApps.h

  Internal header file for the clock device driver on the apps image.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Library/ClockLib/ClockApps.h#1 $
  $DateTime: 2021/09/12 20:53:48 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockAppsBSP.h"
#include "../HALclkLib/HALclkAPCS.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * CPU context.
 */
typedef struct
{
  ClockNodeType                 *pClock;
  ClockAppsBSPCPUType           *pBSPConfig;
  ClockAppsPerfLevelConfigType  *pActiveConfig;
  ClockAppsPerfLevelConfigType  *pPreviousConfig;
  uint32                         nMinPerfLevel;
  uint32                         nMaxPerfLevel;
  ClockMuxConfigType             ActiveMuxConfig;
} ClockAppsCPUCtxt;

/*
 * Initial rail voltage BSP data.
 */
typedef struct
{
  char               *sName;
  rail_voltage_level  eBootCorner;
} ClockRailConfigType;

/**
 * Apps clock driver context.
 */
typedef struct
{
  ClockAppsCPUCtxt    aCPU[CLOCK_APPS_CPU_TOTAL];
} ClockAppsCtxtType;

/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_GetDrvCtxt
** =========================================================================*/
/*
  Returns a pointer to the Clock Driver Context data.

  @return
  Pointer to the Clock Driver Context data.

  @dependencies
  None.
*/

ClockDrvCtxt *Clock_GetDrvCtxt
(
  void
);

/* =========================================================================
**  Function : Clock_SetCPUConfig
** =========================================================================*/
/*
  This function handles performance level requests on a per cpu core/cluster
  level basis.

  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param eCPU [in] -- Which CPU domain to change.
  @param pPerfConfig [in] -- New configuration.

  @return
  CLOCK_SUCCESS - CPU clock configuration succeeded.
  CLOCK_ERROR - CPU clock configuration failed.

  @dependencies
  None.
*/

ClockResult Clock_SetCPUConfig
(
  ClockDrvCtxt                  *pDrvCtxt,
  ClockAppsCPUType               eCPU,
  uint32                         nPerfLevel
);

/* =========================================================================
**  Function : Clock_MapPerfLevelToFrequency
** =========================================================================*/
/**
  Maps a given CPU Perf Level to a frequency in Hz.

  This function takes in a given CPU Perf Level and returns the corresponding
  frequency in Hz.

  @param pDrvCtxt   [in] -- Pointer to the driver context.
  @param eCPU       [in] -- CPU/Cluster identifier.
  @param nPerfLevel [in] -- Desired Perf Level.

  @return
  Frequency in Hz.

  @dependencies
  None.
*/

uint32 Clock_MapPerfLevelToFrequency
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockAppsCPUType  eCPU,
  uint32            nPerfLevel
);


/* =========================================================================
**  Function : ClockApps_GetMaxPerfLevel
** =========================================================================*/
ClockResult
ClockApps_GetMaxPerfLevel
(
  uint32     nCPU,
  uint32    *pnPerfLevel
);


/* =========================================================================
**  Function : ClockApps_GetMinPerfLevel
** =========================================================================*/
ClockResult
ClockApps_GetMinPerfLevel
(
  uint32  nCPU,
  uint32  *pnPerfLevel
);


/* =========================================================================
**  Function : ClockApps_GetCpuPerfLevelFrequency
** =========================================================================*/
ClockResult
ClockApps_GetCpuPerfLevelFrequency(
  uint32  nCPU,
  uint32  nPerfLevel,
  uint32  *pnFrequencyHz,
  uint32  *pnRequiredVoltage
);


/* ===========================================================================
**  Function :  ClockApps_DetectCPUFrequency
** ======================================================================== */
ClockResult  ClockApps_DetectCPUFrequency
(
  uint32  nCPU,
  uint32  *nFreqHz
);


/* =========================================================================
**  Function : ClockApps_GetCPUFrequencyLevels
** =========================================================================*/
ClockResult
ClockApps_GetCPUFrequencyLevels (
  uint32  nCPU,
  uint32  *pnFrequencyLevels 
);


/* =========================================================================
**  Function : ClockApps_GetCPUFrequencyPlan
** =========================================================================*/
ClockResult
ClockApps_GetCPUFrequencyPlan (
  uint32  nCPU,
  ClockFreqPlanType *pCPUFreqPlan,
  uint32  nSize
);


/* =========================================================================
**  Function : ClockApps_SetCPUFrequency
** =========================================================================*/
ClockResult
ClockApps_SetCPUFrequency (
  uint32  nCPU,
  uint32  nFrequencyHz,
  uint32  *pnResultFreqHz
);


/* =========================================================================
**  Function : ClockApps_GetCPUFrequency
** =========================================================================*/
ClockResult
ClockApps_GetCPUFrequency (
  uint32  nCPU,
  uint32  *pnFrequencyHz
);


/* =========================================================================
**  Function : ClockApps_SetCpuPerfLevel
** =========================================================================*/
ClockResult
ClockApps_SetCpuPerfLevel (
  uint32  nCPU,
  uint32  nPerfLevel,
  uint32  *pnFrequencyHz
);


/* =========================================================================
**  Function : ClockApps_GetCpuPerfLevel
** =========================================================================*/
ClockResult
ClockApps_GetCpuPerfLevel (
  uint32  nCPU,
  uint32  *pnPerfLevel
);


/* =========================================================================
**  Function : Clock_MapPerfLevelToVoltage
** =========================================================================*/
/**
  Maps perf level index to a raw voltage.

  This function takes in perf level index and returns a raw voltage.

  @param pDrvCtxt          [in] -- Pointer to the driver context.
  @param eCPU              [in] -- CPU/Cluster identifier.
  @param nPerfLevel        [in] -- Perf Level index

  @return
  Raw voltage in uV.

  @dependencies
  None.
*/

uint32 Clock_MapPerfLevelToVoltage
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockAppsCPUType  eCPU,
  uint32            nPerfLevel
);

#endif /* !CLOCKAPPS_H */
