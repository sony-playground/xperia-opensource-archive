#ifndef CLOCKDEFS_H
#define CLOCKDEFS_H
/*
===========================================================================
*/
/**
  @file ClockDefs.h
  @brief Public definitions include file for accessing the clock device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      The Clock_Driver_API_mainpage.dox file contains all file/group
      descriptions that are in the output PDF generated using Doxygen and
      LaTeX. To edit or update any of the file/group text in the PDF, edit the
      Clock_Driver_mainpage.dox file or contact Tech Pubs.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2020 QUALCOMM Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/ClockDefs.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  06/19/20   rama    Added CLOCK_FREQUENCY_FMAX
  05/17/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "stdint.h"
#include "stdbool.h"
#include "com_dtypes.h"
#include "voltage_level.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/

/**
 * Size that should be large enough to store any clock name.
 */
#define CLOCK_MAX_NAME_LEN 128

/*
 * Flags for Clock_EnableEx.
 */
#define CLOCK_ENABLE_FLAG_DONT_WAIT_FOR_CLOCK_ON  0x00000001

/*
 * Flags for Clock_DisableEx.
 */
#define CLOCK_DISABLE_FLAG_WAIT_FOR_CLOCK_OFF     0x00000001


/*=========================================================================
      Type Definitions
==========================================================================*/

/** @addtogroup clock_functions
@{ */

/**
 * Public logging flags for individual clocks
 *
 *  LOG_STATE_CHANGE - Enable logging of enable/disable calls
 *    to a particular node.
 *  LOG_FREQ_CHANGE - Enable logging of frequency changes to
 *    a particular node.
 *  LOG_CONFIG_CHANGE - Enable logging of configuration changes
 *    to a particular node.
 *  LOG_RESET - Enable logging of resets to a particular node.
 *  LOG_INVERT_CHANGE - Enables logging of clock inversion
 *    changes.
 *  LOG_SLEEP_CHANGE - Enable logging of sleep state changes.
 */
#define PUBLIC_CLOCK_FLAG_LOG_STATE_CHANGE           0x00000001
#define PUBLIC_CLOCK_FLAG_LOG_FREQ_CHANGE            0x00000002
#define PUBLIC_CLOCK_FLAG_LOG_CONFIG_CHANGE          0x00000004
#define PUBLIC_CLOCK_FLAG_LOG_RESET                  0x00000008
#define PUBLIC_CLOCK_FLAG_LOG_INVERT_CHANGE          0x00000010
#define PUBLIC_CLOCK_FLAG_LOG_SLEEP_CHANGE           0x00000020
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000040        0x00000040
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000080        0x00000080
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000100        0x00000100
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000200        0x00000200
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000400        0x00000400
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00000800        0x00000800
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00001000        0x00001000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00002000        0x00002000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00004000        0x00004000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00008000        0x00008000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00010000        0x00010000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00020000        0x00020000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00040000        0x00040000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00080000        0x00080000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00100000        0x00100000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00200000        0x00200000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00400000        0x00400000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x00800000        0x00800000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x01000000        0x01000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x02000000        0x02000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x04000000        0x04000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x08000000        0x08000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x10000000        0x10000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x20000000        0x20000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x40000000        0x40000000
#define PUBLIC_CLOCK_FLAG_RESERVED_0x80000000        0x80000000

/**
 * Public global logging flags
 *
 *  LOG_x_STATE_CHANGE - Enable logging of enable/disable
 *    calls to all clocks, sources, or power domains as
 *    specified by x.
 *  LOG_CLOCK_FREQ_CHANGE - Enable logging of frequency changes
 *    to all clocks.
 *  LOG_CLOCK_CONFIG_CHANGE - Enable logging of configuration
 *    changes to all clocks.
 *  LOG_CLOCK_RESET - Enable logging of resets to all clocks.
 *  LOG_VOLTAGE_CHANGE - Enable logging of vdd requirement changes.
 *  LOG_CLOCK_SLEEP_CHANGE - Enable logging of sleep state changes.
 *  BIST_IN_PROGRESS - Indicates that a Built-In Self Test is running.
 *  LOG_MISC_STATUS - Enable logging of miscellaneous status info.
 *  CPU_BYPASS_RANGE_CHECKING - Bypass DCVS requests range checking.
 */
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_STATE_CHANGE          0x00000001
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE           0x00000002
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_CONFIG_CHANGE         0x00000004
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_RESET                 0x00000008
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE         0x00000010
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_POWER_DOMAIN_STATE_CHANGE   0x00000020
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_VOLTAGE_CHANGE              0x00000040
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_SOURCE_FREQ_CHANGE          0x00000080
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000100             0x00000100
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000200             0x00000200
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000400             0x00000400
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000800             0x00000800
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_SLEEP_CHANGE          0x00001000
#define PUBLIC_CLOCK_GLOBAL_FLAG_BIST_IN_PROGRESS                0x00002000
#define PUBLIC_CLOCK_GLOBAL_FLAG_CPU_TEST_IN_PROGRESS            0x00004000
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_MISC_STATUS                 0x00008000
#define PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_INVERT_CHANGE         0x00010000
#define PUBLIC_CLOCK_GLOBAL_FLAG_CPU_BYPASS_RANGE_CHECKING       0x00020000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00040000             0x00040000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00080000             0x00080000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00100000             0x00100000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00200000             0x00200000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00400000             0x00400000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00800000             0x00800000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x01000000             0x01000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x02000000             0x02000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x04000000             0x04000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x08000000             0x08000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x10000000             0x10000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x20000000             0x20000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x40000000             0x40000000
#define PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x80000000             0x80000000

/**
  Clock handle.
 */
typedef uintnt ClockIdType;


/**
  Handle to clock client.
 */
typedef uintptr_t ClockHandle;

/**
  Clock Domain handle.
 */
typedef uintnt ClockDomainIdType;


/**
  Source handle.
 */
typedef uintnt SourceIdType;


/**
  Divider handle.
 */
typedef uintnt ClockDividerIdType;


/**
  Debug mux handle.
 */
typedef uintnt ClockDebugMuxIdType;

/**
  Handle to clock client.
 */
typedef uintptr_t ClockHandle;


/**
  Clock return values.
 */
typedef enum ClockResult
{
  CLOCK_SUCCESS                         = 0,
  CLOCK_ERROR                           = -1,
  CLOCK_ERROR_INVALID_PARAMETER         = -2,
  CLOCK_ERROR_INSUFFICIENT_MEMORY       = -3,
  CLOCK_ERROR_NOT_FOUND                 = -4,
  CLOCK_ERROR_INTERNAL                  = -5,
  CLOCK_ERROR_NOT_ALLOWED               = -6,
  CLOCK_ERROR_NOT_SUPPORTED             = -7,
  CLOCK_ERROR_NOT_INITIALIZED           = -8,
  CLOCK_ERROR_OUT_OF_RANGE_PARAMETER    = -9,
  CLOCK_ERROR_INVALID_ADDRESS           = -10,
  CLOCK_ERROR_INSUFFICIENT_BUFFER_LEN   = -11,
} ClockResult;


/**
  Callback handle for resource state change.
 */
typedef uintnt ClockCallbackIdType;

/**
 * Event types supported for resource state change callbacks
 */
typedef enum
{
  CLOCK_CALLBACK_EVENT_PRE_ENABLE,   /* Before a resource is enabled */
  CLOCK_CALLBACK_EVENT_POST_ENABLE,  /* After a resource is enabled */
  CLOCK_CALLBACK_EVENT_PRE_DISABLE,  /* Before a resource is disabled */
  CLOCK_CALLBACK_EVENT_POST_DISABLE, /* After a resource is disabled */
  CLOCK_CALLBACK_EVENT_PRE_FREQ_CHANGE,  /* Before a resource frequency changes */
  CLOCK_CALLBACK_EVENT_POST_FREQ_CHANGE, /* After a resource frequency changes */
  CLOCK_CALLBACK_EVENT_NUM_TYPES
} ClockCallbackEventType;

typedef void * ClockCallbackData;
typedef void * ClockCallbackCtxt;  /**< Client callback parameter. */
typedef void * (*ClockCallbackFn)(
                 ClockCallbackCtxt, ClockCallbackEventType,
                 ClockIdType, ClockCallbackData); /**< Client callback. */

typedef struct ClockEventDataFreqChange
{
  struct
  {
    uint32_t           nFreqHz;
    rail_voltage_level eCorner;
  } PreChange;
  
  struct
  {
    uint32_t           nFreqHz;
    rail_voltage_level eCorner;
  } PostChange;
} ClockEventDataFreqChange;


/**
  Used to search for a matching frequency input. This type describes how
  frequency matching is done for the clock frequency selection function. It
  also indicates units in Hz, kHz, or MHz.
 */
typedef enum
{
  CLOCK_FREQUENCY_HZ_AT_LEAST         = 0x00,  /**< Frequency is the minimum allowed in Hz. */
  CLOCK_FREQUENCY_HZ_AT_MOST          = 0x01,  /**< Frequency is the maximum allowed in Hz. */
  CLOCK_FREQUENCY_HZ_CLOSEST          = 0x02,  /**< Closest match in Hz. */
  CLOCK_FREQUENCY_HZ_EXACT            = 0x03,  /**< Exact match only in Hz. */
  CLOCK_FREQUENCY_HZ_AT_LEAST_OR_MAX  = 0x04,  /**< Frequency is the minimum allowed in Hz, capped to maximum supported frequency. */

  CLOCK_FREQUENCY_KHZ_AT_LEAST = 0x10,  /**< Frequency is the minimum allowed in kHz. */
  CLOCK_FREQUENCY_KHZ_AT_MOST  = 0x11,  /**< Frequency is the maximum allowed in kHz. */
  CLOCK_FREQUENCY_KHZ_CLOSEST  = 0x12,  /**< Closest match in kHz. */
  CLOCK_FREQUENCY_KHZ_EXACT    = 0x13,  /**< Exact match only in kHz. */
  CLOCK_FREQUENCY_KHZ_AT_LEAST_OR_MAX = 0x14,  /**< Frequency is the minimum allowed in kHz, capped to the maximum supported frequency. */

  CLOCK_FREQUENCY_MHZ_AT_LEAST = 0x20,  /**< Frequency is the minimum allowed in MHz. */
  CLOCK_FREQUENCY_MHZ_AT_MOST  = 0x21,  /**< Frequency is the maximum allowed in MHz. */
  CLOCK_FREQUENCY_MHZ_CLOSEST  = 0x22,  /**< Closest match in MHz. */
  CLOCK_FREQUENCY_MHZ_EXACT    = 0x23,  /**< Exact match only in MHz. */
  CLOCK_FREQUENCY_MHZ_AT_LEAST_OR_MAX = 0x24,  /**< Frequency is the minimum allowed in MHz, capped to the maximum supported frequency. */
  
  CLOCK_FREQUENCY_FMAX = 0X30  /**< Frequency is the corner fmax. */
} ClockFrequencyType;


/**
  Type of clock reset. This defines how the reset to the clock domain
  is to be handled.
 */
typedef enum
{
  CLOCK_RESET_DEASSERT = 0,  /**< Deassert the reset signal. */
  CLOCK_RESET_ASSERT   = 1,  /**< Assert and hold the reset signal. */
  CLOCK_RESET_PULSE    = 2   /**< Assert and immediately deassert. */
} ClockResetType;


/**
  Clock queries.
 */
typedef enum
{
  CLOCK_QUERY_NUM_PERF_LEVELS,      /**< Query the number of performance levels. */
  CLOCK_QUERY_PERF_LEVEL_FREQ_HZ,   /**< Query performance level frequency. */
  CLOCK_QUERY_PERF_LEVEL_CORNER,    /**< Query performance level corner. */
  CLOCK_QUERY_PERF_LEVEL_DFS_IDX,   /**< Query performance level DFS index. 0xFF if none. */
  CLOCK_QUERY_PERF_LEVEL_SRC_NAME,  /**< Query performance level source name. */
  CLOCK_QUERY_RAIL_NAME,            /**< Query name of the clock's voltage rail. */
  CLOCK_QUERY_DFS_ENABLED,          /**< Query if DFS is enabled for this clock. */
  CLOCK_QUERY_REF_COUNT,            /**< Query the clock's reference count. */
} ClockQueryType;


/**
  Query result structure.
 */
typedef struct ClockQueryResult
{
  ClockQueryType eType; /**< Query type this result is for. */
  union
  {
    uint32_t            nNumPerfLevels;     /**< CLOCK_QUERY_NUM_PERF_LEVELS */
    uint32_t            nPerfLevelFreqHz;   /**< CLOCK_QUERY_PERF_LEVEL_FREQ_HZ */
    rail_voltage_level  ePerfLevelCorner;   /**< CLOCK_QUERY_PERF_LEVEL_CORNER */
    uint32_t            nPerfLevelDFSIdx;   /**< CLOCK_QUERY_PERF_LEVEL_DFS_IDX */
    char                szPerfLevelSrcName[CLOCK_MAX_NAME_LEN]; /* CLOCK_QUERY_PERF_LEVEL_SRC_NAME */
    char                szRailName[CLOCK_MAX_NAME_LEN];         /* CLOCK_QUERY_RAIL_NAME */
    bool                bDFSEnabled;        /* CLOCK_QUERY_DFS_ENABLED */
    uint32_t            nRefCount;          /* CLOCK_QUERY_REF_COUNT */
  } Data;
} ClockQueryResultType;



/**
  Type of clock data request. This type identifies miscellaneous clock data, including
  configuration values stored in a row of BSP data for each clock frequency.
 */
typedef enum
{
  CLOCK_REQUEST_DATA_NUMBER_OF_FREQUENCY_LEVELS       = 0,  /**< Clock Request: Number of frequency levels */
  CLOCK_REQUEST_DATA_FREQUENCY_HZ                     = 1,  /**< Clock Request: Frequency in Hz */
  CLOCK_REQUEST_DATA_VOLTAGE_CORNER                   = 2,  /**< Clock Request: Voltage Corner */
  CLOCK_REQUEST_DATA_VOLTAGE_UV                       = 3,  /**< Clock Request: Voltage uV */
  CLOCK_REQUEST_DATA_DFS_STATE                        = 4,  /**< Clock Request: DFS state */

  /** @cond
  */
  CLOCK_REQUEST_DATA_TOTAL = 5
  /** @endcond */
} ClockRequestDataType;

/**
 * Clock QDSS levels used for the /clk/qdss NPA resource.
 */
typedef enum
{
  CLOCK_QDSS_LEVEL_OFF,      /**< Clock rate set to CXO and disabled. */
  CLOCK_QDSS_LEVEL_DEBUG,    /**< Clock rate follows VDD_CX. */
  CLOCK_QDSS_LEVEL_HSDEBUG,  /**< Clock rate set to high speed. */
} ClockQDSSLevelType;

/** @addtogroup power_domain_functions
@{ */


/**
  Options for the DalClock_LogState API.
 */
typedef enum
{
  CLOCK_LOG_STATE_CLOCK_FREQUENCY = (1 << 0),
} ClockLogStateFlags;

/** @} */ /* end_addtogroup clock_functions */

/**
  Type of clock configuration.  This type describes how a clock is
  configured.
 */
typedef uintnt ClockPowerDomainIdType;


/** @} */ /* end_addtogroup power_domain_functions */

/** @addtogroup topology_functions
@{ */

/**
 * Enumeration of clusters comprising the APSS.
 */
/**
 * Enumeration of clusters comprising the APSS.
 */
typedef enum
{
  CLOCK_APPS_CLUSTER_A7,
  CLOCK_APPS_CLUSTER_A53,
  CLOCK_APPS_CLUSTER_A57,
  CLOCK_APPS_CLUSTER_CCI,
  CLOCK_APPS_CLUSTER_HYDRA_0,
  CLOCK_APPS_CLUSTER_HYDRA_1,
  CLOCK_APPS_CLUSTER_CBF,
  CLOCK_APPS_CLUSTER_SILVER,
  CLOCK_APPS_CLUSTER_GOLD,
  CLOCK_APPS_CLUSTER_L3,
  CLOCK_APPS_CLUSTER_TOTAL
} ClockAppsClusterIdType;

typedef enum
{
  CLOCK_CONFIG_HW_CTL_ON                  = 0, /**< Enable HW control */
  CLOCK_CONFIG_HW_CTL_OFF                 = 1, /**< Disable HW control. */
  CLOCK_CONFIG_MEM_CORE_FORCE_ON          = 2, /**< Force core memories on. */
  CLOCK_CONFIG_MEM_CORE_DONT_FORCE_ON     = 3, /**< Don't force core memories on. */
  CLOCK_CONFIG_MEM_PERIPH_FORCE_ON        = 4, /**< Force peripheral memories on. */
  CLOCK_CONFIG_MEM_PERIPH_DONT_FORCE_ON   = 5, /**< Don't force peripheral memories on. */
  CLOCK_CONFIG_MEM_PERIPH_FORCE_OFF       = 6, /**< Force peripheral memories off. */
  CLOCK_CONFIG_MEM_PERIPH_DONT_FORCE_OFF  = 7, /**< Don't force peripheral memories off. */
  CLOCK_CONFIG_DFS_ENABLE                 = 8, /**< Enable DFS control. */

  /** @cond
 */
  CLOCK_CONFIG_TOTAL
  /** @endcond */
} ClockConfigType;

/**
  Power domain handle.
 */
typedef uintnt ClockPowerDomainIdType;

/** @} */ /* end_addtogroup clock_functions */

/** @addtogroup misc_functions
@{ */

/**
  Processor Sleep mode. This type defines the different kinds of sleep modes
  that can be entered.
 */
typedef enum
{
  CLOCK_SLEEP_MODE_HALT,            /**< Processor halt only. */
  CLOCK_SLEEP_MODE_POWER_COLLAPSE   /**< Processor power collapse. */
} ClockSleepModeType;

/*
 * Voltage regulator ID Type.
 */
typedef enum
{
  CLOCK_VREG_VDD_CX,
  CLOCK_VREG_VDD_MSS,
  CLOCK_VREG_VDD_APC,
  CLOCK_VREG_VDD_APC0,
  CLOCK_VREG_VDD_APC1,
  CLOCK_VREG_VDD_CBF,
  CLOCK_VREG_VDD_GFX,
  CLOCK_VREG_TOTAL
} ClockVRegIdType;

/**
 Processor Sleep mode flag masks:
  RAMP_DOWN_CPU
   Triggers frequency switching to a lower performance level before SWFI.

  L2CACHE_FLUSH
   Flushes the contents of L2 cache when entering power collapse.

  RAMP_DOWN_L2CACHE
   In some cases, the L2 cache frequency needs to be lowered with the CPU
   frequency. In other cases, the L2 cache frequency needs to remain untouched.
   This is when the RAMP_DOWN_L2CACHE flag becomes useful.

  PLL_OFF
   Configures the PLL to a state where it is ready for the SPM to power it off.
   It also preloads any configuration registers necessary such that it is ready
   to be used once the SPM powers it back on.
 */
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_CPU          0x00000001
#define CLOCK_SLEEP_FLAG_L2CACHE_FLUSH          0x00000002
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_L2CACHE      0x00000004
#define CLOCK_SLEEP_FLAG_PLL_OFF                0x00000008

/*
 * ClockInfoType
 *
 * Structure to hold information about a clock.
 */
typedef struct ClockInfo
{
  const char *szRail;   /* Voltage rail powering this clock. */
} ClockInfoType;


/*
 * ClockFreqPlanType
 *
 * Structure to hold a frequency plan entry.
 */
typedef struct ClockFreqPlanType
{
  uint32 nFreqHz;    /* Clock frequency in Hz */
  uint32 eVRegLevel; /* Voltage corner requirement. */
} ClockFreqPlanType;


/** @} */ /* end_addtogroup misc_functions */


/** @addtogroup npa_functions
@{ */
/** @name NPA Query Requests
@{ */

/**
  NPA Node: /clk/cpu [ALL]
  NPA query ID for the primary clock name associated with the node.
 */
#define CLOCK_NPA_QUERY_CLOCK_NAME \
  (NPA_QUERY_RESERVED_END + 1)

/** @} */ /* end_addtogroup npa_functions*/


#endif /* !CLOCKDEFS_H */
