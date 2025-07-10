/*
===========================================================================
*/
/**
  @file ClockAppsVDD.c

  CPR support for the Apps clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Netrani/Library/ClockLib/ClockAppsVDD.c#1 $
  $DateTime: 2021/08/30 01:42:17 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  02/06/13   sr      Ported from MSS.
  02/17/12   vs      Created.

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockDriver.h"
#include "ClockApps.h"

extern ClockResult  Clock_GetPropertyHandle(const char* str, void** handle );

/*=========================================================================
      Functions
==========================================================================*/
/* =========================================================================
**  Function : Clock_MapPerfLevelToVoltage
** =========================================================================*/
/**
  Maps The given perf level to its associated voltage

  This function takes in an APC voltage rail corner index and returns a raw voltage.

  @param pDrvCtxt          [in] -- Pointer to the driver context.
  @param eCPU              [in] -- CPU/Cluster identifier.
  @param nPerfLevel        [in] -- Perf level that is used as an index to retrieve voltage

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
)
{
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Get the associated voltage with the perf level                                            */
  /*-----------------------------------------------------------------------*/
  if(pAppsCtxt)
  {
	  return pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel].nVoltageUV;
  }

  return 0;

} /* END Clock_MapPerfLevelToVoltage */


/* =========================================================================
**  Function : Clock_GetBootCorner
** =========================================================================*/
/**
  Returns the configured boot voltage corner for the given rail stored in a
  BSP data structure.

  @param szRailName  [in] -- Name of the rail.
  @param eBootCorner [out] -- The configured boot corner to return.

  @return
  CLOCK_SUCCESS if the value was found and retrieved, CLOCK_ERROR otherwise.

  @dependencies
  None.
*/

ClockResult Clock_GetBootCorner
(
  const char         *szRailName,
  rail_voltage_level *eBootCorner
)
{
  ClockResult              eResult;
  void* RailConfigHandle = NULL;
  ClockRailConfigType   *ClockRailConfig;
  uint32                 nIndex;

  if (szRailName == NULL || eBootCorner == NULL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the boot voltage corner table.                                    */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyHandle("ClockRailConfig", &RailConfigHandle);

  if (eResult == CLOCK_SUCCESS)
  {
    ClockRailConfig = (ClockRailConfigType *)RailConfigHandle;

    for (nIndex = 0; ClockRailConfig[nIndex].sName != NULL; nIndex++)
    {
      if (strcmp(ClockRailConfig[nIndex].sName, szRailName) == 0)
      {
        *eBootCorner = ClockRailConfig[nIndex].eBootCorner;
        return CLOCK_SUCCESS;
      }
    }
    *eBootCorner = RAIL_VOLTAGE_LEVEL_OFF;
    return CLOCK_ERROR_NOT_FOUND;
  }

  return eResult;

} /* END Clock_GetBootCorner */



