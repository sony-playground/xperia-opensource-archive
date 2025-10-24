#ifndef __CLOCKAPPS_H__
#define __CLOCKAPPS_H__
/*
==============================================================================

FILE:       ClockApps.h  

DESCRIPTION:
  Internal header file for the clock device driver on the apps image.

==============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Include/ClockApps.h#1 $

==============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*============================================================================
      Include Files
============================================================================*/

#include <HALcomdef.h>
#include <ClockDefs.h>
#include <ULogFront.h>

/*============================================================================
      Macro Definitions
============================================================================*/

#define CLOCK_APSS_TOTAL_PERF_LEVELS          40
#define CLOCK_APSS_MIN_PERF_LEVEL             0
#define CLOCK_APSS_MAX_PERF_LEVEL             (CLOCK_APSS_TOTAL_PERF_LEVELS-1)
#define CLOCK_APPS_XO_FREQ                    19200000            // 19.2 MHz
#define CLOCK_APSS_MIN_PERF_LEVEL_FREQ        300000000           // 300  MHz
#define MILLI_VOLT_TO_MICRO_VOLT(mV)          (mV*1000)


/*
 * HAL_clk_ClusterConfigType
 *
 *  DCVS_ENABLED   - Allow to Check if DCVS is Enabled
 *                   for a CPU Cluster.
 */
typedef enum
{
  HAL_CLK_APSS_DCVS_ENABLED,

  HAL_ENUM_32BITS(CLK_CLUSTER_CONFIG)
} HAL_clk_ClusterConfigType;


/*
 * Forward declaration of structs b/c of the cross references within these structs
 */
typedef struct HAL_clk_ClusterDescType    HAL_clk_ClusterDescType;


/*
 * HAL_clk_ClusterPerfLevel
 *
 * Description of a CPU Perf-Level
 *
 * nL      - The L value for the PLL.
 * nSource - The source to used.
 *           nSource=0 refer's to GPLL0, anything else denotes APSS internal PLL number.
 */
typedef struct HAL_clk_ClusterPerfLevel
{
  uint32_t        nL;
  uint32_t        nSource;
  uint32_t        nOpenLoopVoltage;
} HAL_clk_ClusterPerfLevelType;


/*
 * HAL_clk_SourceControlType
 *
 * Set of function pointers used to control a clock source.
 *
 * GetCorePerfLevel    - Queries the Perf-Level set on a Core.
 * GetL3PerfLevel      - Queries the Perf-Level vote on L3 from a Core.
 * SetCorePerfLevel    - Configure's the Core to run at a Perf-Level.
 * SetL3PerfLevel      - Updated the Perf-Level vote on L3 from a Core.
 * GetActivePerfLevel  - Queries the Perf-Level at which entire cluster is running.
 * ReadPerfLevelConfig - Read the Perf-Level settings programmed in TZ or CPUCP.
 * GetConfig           - Misc function for reading any details from cluster registers.
 */
typedef struct
{
  boolean  (*GetCorePerfLevel)       ( const HAL_clk_ClusterDescType *pCluster, const uint32_t nClusterIndex, uint32_t *pnVcIndex);
  boolean  (*GetL3PerfLevel)         ( const HAL_clk_ClusterDescType *pCluster, const uint32_t nClusterIndex, uint32_t *pnVcIndex);
  boolean  (*SetCorePerfLevel)       ( const HAL_clk_ClusterDescType *pCluster, const uint32_t nClusterIndex, const uint32_t nVcIndex);
  boolean  (*SetL3PerfLevel)         ( const HAL_clk_ClusterDescType *pCluster, const uint32_t nClusterIndex, const uint32_t nVcIndex);
  boolean  (*GetActivePerfLevel)     ( const HAL_clk_ClusterDescType *pCluster, uint32_t *pnVcIndex);
  boolean  (*ReadPerfLevelConfig)    ( const HAL_clk_ClusterDescType *pCluster, const uint32_t nVcIndex,   HAL_clk_ClusterPerfLevelType *pPerfLevel);
  boolean  (*GetConfig)              ( const HAL_clk_ClusterDescType *pCluster, const HAL_clk_ClusterConfigType eConfig, void *pConfigValue);
} HAL_clk_ClusterControlType;

/*
 * HAL_clk_ClusterDescType
 *
 * Description of a CPU Cluster's, including control functions.
 *
 * nAddr      - Cluster base address.
 * pmControl  - Pointer to the control functions that cna operate on Cluster.
 */
struct HAL_clk_ClusterDescType
{
  uintptr_t                   nAddr;
  HAL_clk_ClusterControlType *pmControl;
};


/*
 * Initial rail voltage BSP data.
 */
typedef struct
{
  char                    *sName;
  rail_voltage_level       eBootCorner;
} ClockRailConfigType;


/*
 * ClockAppsPerfLevelType
 *
 * Configuration parameters for a performance level.
 *
 *  nFreqHz             - Frequency in Hz for this PerfLevel.
 *  nVoltageUV          - Voltage in micro-volt.
 */

typedef struct
{
  uint32_t                  nFreqHz;
  uint32_t                  nVoltageUV;
} ClockAppsPerfLevelType;

/*
 * Main BSP type for Apps Cluster.
 */
typedef struct
{
  const char               *szName;                              /* Cluster Name used for Debug prints only. No Practical Significance */
  uint32_t                  nMinPerfLevel;                       /* Number of Perf-Levels Defined by CPUCP/TZ */
  uint32_t                  nMaxPerfLevel;                       /* Number of Perf-Levels Defined by CPUCP/TZ */
  uint32_t                  nActivePerfLevel;                    /* Perf-Level at which a Cluster is running */
  uint32_t                  nFlags;                              /* Flags */
  uint32_t                  nCoreCount;                          /* Compute units (a.k.a Cores) Present in this Cluster. Typicaly its 1 or 2 or 4 */
  HAL_clk_ClusterDescType   HALCluster;                          /* structure with HAL detials of Cluster  */
  ClockAppsPerfLevelType    aBSP[CLOCK_APSS_TOTAL_PERF_LEVELS];  /* Array to Store Details of Perf-Level Defined by CPUCP/TZ */
} ClockAppsClusterNodeType;

/*
 * Main BSP type for Apps.
 */
typedef struct {
  uint32_t                  nFlags;           /* Flags */
  ClockAppsClusterNodeType *aClusters;        /* Array of Clusters. */
  uint32_t                  nNumClusters;     /* Length of aClusters. */
} ClockAppsBSPType;

/**
 * CPU Clock driver context.
 */
typedef struct
{
  ClockAppsBSPType        *pBSP;
  ULogHandle               hClockAppsULog;
  uint32_t                 nLogSize;
  boolean                  bImageBISTEnabled;
} ClockAppsCtxtType;


/**
  Type of CPU Core data request. This type identifies miscellaneous CPU Core data.
 */
typedef enum
{
  CLOCKAPPS_REQUEST_DATA_VOLTAGE_UV = 0,                  /**< Clock Request: Voltage uV */
  CLOCKAPPS_REQUEST_DATA_FREQUENCY_HZ,                    /**< Clock Request: Frequency in Hz */
  CLOCKAPPS_REQUEST_DATA_MIN_PERF_LEVEL,                  /**< Clock Request: Minimum Perf-Level programmed by CPUCP/TZ */
  CLOCKAPPS_REQUEST_DATA_MAX_PERF_LEVEL,                  /**< Clock Request: Minimum Perf-Level programmed by CPUCP/TZ */
  CLOCKAPPS_REQUEST_DATA_ACTIVE_PERF_LEVEL,               /**< Clock Request: Per-Level at which a Core is running */
  CLOCKAPPS_REQUEST_DATA_NUMBER_OF_PERF_LEVELS,           /**< Clock Request: Number of Perf-Levels */

  CLOCKAPPS_REQUEST_DATA_TOTAL,
} ClockApps_RequestDataType;


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : ClockApps_Query
** =========================================================================*/
/**
  Query information about about a CPU Cluster.

  This function queries information about a CPU Cluster or one of its performance
  levels.

  @param nClusterIndex  [in] Cluster for which to query the frequency plan.
  @param nIndex         [in] Index based on query type.
  @param eQuery         [in] Query to perform.
  @param pnResult      [out] Query result.

  @return
  CLOCK_ERROR_OUT_OF_RANGE_PARAMETER -- Query type or performance level not supported.
  CLOCK_ERROR_INVALID_PARAMETER -- Clock identifier was invalid, or pResult was NULL.
  CLOCK_SUCCESS -- Query result successfully placed in pResult.

*/

ClockResult ClockApps_Query
(
  uint32_t                   nClusterIndex,
  uint32_t                   nIndex,
  ClockApps_RequestDataType  eQuery,
  uint32_t                  *pnResult
);


/* =========================================================================
**  Function : ClockApps_GetCPUFrequency
** =========================================================================*/
/**
  Get Frequency at which a core is running at the moment.

  @param nClusterIndex    [in] -- Core identifier.
  @param pnFreqHz     [out] -- Pointer to store Frequency Value.

  @return
  CLOCK_SUCCESS - Valid Core Frequency is found and output parameters are Valid.
  CLOCK_ERROR_INVALID_PARAMETER - One or more Input Parameters are Invalid.
  CLOCK_ERROR   - Unable to find Frequency of Core.

  @dependencies
  None.
*/

ClockResult ClockApps_GetCPUFrequency (
  uint32_t  nClusterIndex,
  uint32_t  *pnFreqHz
);


/* =========================================================================
**  Function : ClockApps_GetCPUPerfLevel
** =========================================================================*/
/**
  Get Perf-Level at which a core is running at the moment.

  @param nClusterIndex    [in] -- Core identifier.
  @param pnPerfLevel  [out] -- Pointer to store Perf-Level Value.

  @return
  CLOCK_SUCCESS - Valid Core Perf-Level is found and output parameters are Valid.
  CLOCK_ERROR_INVALID_PARAMETER - One or more Input Parameters are Invalid.
  CLOCK_ERROR   - Unable to find Perf-Level of Core.

  @dependencies
  None.
*/

ClockResult ClockApps_GetCPUPerfLevel (
  uint32_t  nClusterIndex,
  uint32_t  *pnPerfLevel
);


/* =========================================================================
**  Function : ClockApps_SetCPUFrequency
** =========================================================================*/
/**
  Set the Frequency at which a particular Core is running.

  @param nClusterIndex      [in] -- Core identifier.
  @param nFreqHz         [in] -- Frequency to set.
  @param pnResultFreqHz [out] -- Pointer for storing the Frequency,
                                   actually set by Driver.

  @return
  CLOCK_SUCCESS - Successfully set frequency of core and output parameters are Valid.
  CLOCK_ERROR_INVALID_PARAMETER      - One or more Input Parameters are Invalid.
  CLOCK_ERROR_OUT_OF_RANGE_PARAMETER - nFreqHz is not Valid.
  CLOCK_ERROR   - Failed to Set Frequency.

  @dependencies
  None.
*/

ClockResult ClockApps_SetCPUFrequency (
  uint32_t  nClusterIndex,
  uint32_t  nFreqHz,
  uint32_t  *pnResultFreqHz
);


/* =========================================================================
**  Function : ClockApps_SetCPUPerfLevel
** =========================================================================*/
/**
  Set the Perf-Level at which a particular Core is running.

  @param nClusterIndex    [in] -- Core identifier.
  @param nPerfLevel    [in] -- Perf-Level to set.
  @param pnPerfLevel  [out] -- Pointer for storing the Perf-Level,
                                 actually set by Driver.

  @return
  CLOCK_SUCCESS - Successfully set Perf-Level of core and output parameters are Valid.
  CLOCK_ERROR_INVALID_PARAMETER      - One or more Input Parameters are Invalid.
  CLOCK_ERROR_OUT_OF_RANGE_PARAMETER - nPerfLevel is not Valid.
  CLOCK_ERROR   - Failed to Set Perf-Level.

  @dependencies
  None.
*/

ClockResult ClockApps_SetCPUPerfLevel(
  uint32_t nClusterIndex,
  uint32_t nPerfLevel,
  uint32_t *pnFreqHz
);


#endif /* __CLOCKAPPS_H__ */

