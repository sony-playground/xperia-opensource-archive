/*
==============================================================================

FILE:         ClockTargetBSP.c

DESCRIPTION:
  This file contains the CPU Clock driver BSP data.
  
==============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockTargetBSP.c#1 $

==============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include "Drivers/ClockDxe/ClockBSP.h"
#include "../HALclkLib/HALclkHWIO.h"


/*=========================================================================
      Externs
==========================================================================*/


/*
 * CPU Cluster control structures.
 */

extern HAL_clk_ClusterControlType         HAL_clk_GenericEPSSControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Clusters
==========================================================================*/


ClockAppsClusterNodeType aClusters[] =
{
    {
        .szName               = "SILVER",
        .nCoreCount           = 3,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM1_CD1_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "GOLD",
        .nCoreCount           = 4,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM2_CD2_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "GOLD-PLUS",
        .nCoreCount           = 1,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM3_CD3_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "L3",
        .nCoreCount           = 1,            // TODO: figure out when is L3 CoreCount set to 0, one that is resolved remove all decltation of nCoreCount in Here.
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM0_CD0_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
};

/*=========================================================================
      Main Image BSP
==========================================================================*/
ClockAppsBSPType ClockAppsBSP = 
{
    .aClusters     = aClusters,
    .nNumClusters  = SIZEOF_ARRAY(aClusters),
    .nFlags        = CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE,
};
