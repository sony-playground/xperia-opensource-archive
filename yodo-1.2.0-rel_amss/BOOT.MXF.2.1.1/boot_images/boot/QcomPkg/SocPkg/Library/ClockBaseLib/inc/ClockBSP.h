#ifndef __CLOCKBSP_H__
#define __CLOCKBSP_H__

/*=========================================================================

                    C L O C K   D E V I C E   D R I V E R
               
        B O A R D   S U P P O R T   P A C K A G E   D E F I N I T I O N S

GENERAL DESCRIPTION
  This file contains the BSP interface definitions for the
  MSM DAL Clock Device Driver.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

      Copyright (c) 2010-2019 by QUALCOMM Technologies, Inc.  All Rights Reserved.

==========================================================================*/

/*=========================================================================
      Includes
==========================================================================*/


#include "ClockDefs.h"
#include "HALclkXBLInternal.h"
#include "ChipInfo.h"
#include "voltage_level.h"


/*=========================================================================
      Constants & Macros & Typedefs
==========================================================================*/

#define SIZEOF_ARRAY(a) (sizeof((a))/sizeof((a)[0]))


/*
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define CLOCK_BSP_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF


/*
 * Macros for consolidating PLL configuration in a single mask.
 */
#define CLOCK_CONFIG_PLL_FSM_MODE_ENABLE        (1 << 0)
#define CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE      (1 << 1)
#define CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE     (1 << 2)
#define CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE    (1 << 3)
#define CLOCK_CONFIG_PLL_XO_DOUBLER_DCC         (1 << 4)
#define CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE     (1 << 5)
#define CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE      (1 << 6)
#define CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL     (1 << 7)
#define CLOCK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL     (1 << 8)
#define CLOCK_CONFIG_PLL_ODD_OUTPUT_HW_CTL      (1 << 9)


/**
 * Unified flag bits
 *
 * NOTE: These flags can be used in any node that supports the
 * nFlags field.
 *
 *  LOG_STATE_CHANGE - Enable logging of enable/disable calls
 *    to a particular node.
 *  LOG_FREQ_CHANGE - Enable logging of frequency changes to
 *    a particular node.
 *  LOG_CONFIG_CHANGE - Enable logging of configuration changes
 *    to a particular node.
 *  LOG_RESET - Enable logging of resets to a particular node.
 *  DO_NOT_DISABLE - Ignore requests to disable a particular
 *    node.
 *  LOG_INVERT_CHANGE - Enables logging of clock inversion
 *    changes.
 *  SUPPRESSIBLE - Indicates XO shutdown will not be held off
 *    while the clock is on.
 *  DOMAIN_HOLD_VREG_REQUEST - Hold the voltage request even
 *    when the clock is off. When set this means the voltage
 *    request will be based solely on the configured clock
 *    frequency and will not be released when the clock is
 *    disabled.
 *  DOMAIN_DYNAMIC_CONFIG - Indicates if the mux configuration
 *    was set up dynamically so we free up the memory after
 *    switching to a new configuration.
 *  AUTOGATE - Allows hardware to automatically enable or
 *    disable the clock branch based on usage. When this
 *    flag is set, the CLK_ENABLE bit in the CBCR register
 *    is ignored.
 *  BIST_FAILURE_ANTICIPATED - Indicates that a clock is
 *    expected to fail the BIST. The BIST log will show
 *    that the clock failed, but that the failure is
 *    expected. The clock does not count towards the
 *    total number of failed clocks.
 *  INTERNAL_CONTROL - Indicates that this node (source/clock/etc)
 *    cannot be controlled by clients via the DAL API.
 *  INITIALIZED - Indicates that this node (source/clock/etc)
 *    has been initialized by the driver.
 *  STUB_HW_RUMI - Indicates that requests on this resource should
 *    avoid accessing HW on RUMI.
 *  CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF - Indicates that the SW should wait for 
 *    a root-off signal before disabling the clock source.
 *  EXPLICIT_ACCESS_ONLY - Indicates that this clock may not always be
 *    physically accessible and should only be access when a client explicitly
 *    requests it. Any internal functions that iterate over all clocks should
 *    skip these.
 *  READ_ONLY - Indicates that this clock is read-only and shouldn't be
 *    be configured by the driver.
 *  DFS_CONTROLLED - Indicates that this clock is being controlled by an
 *    enabled DFS instance.
 *  STUB_HW_VIRTIO - Indicates that requests on this resource should
 *    avoid accessing HW on Virtio.
 */
#define CLOCK_FLAG_LOG_STATE_CHANGE             0x00000001
#define CLOCK_FLAG_LOG_FREQ_CHANGE              0x00000002
#define CLOCK_FLAG_LOG_CONFIG_CHANGE            0x00000004
#define CLOCK_FLAG_LOG_RESET                    0x00000008
#define CLOCK_FLAG_LOG_INVERT_CHANGE            0x00000010
// Reserved for future logging                  0x00000020
// Reserved for future logging                  0x00000040
// Reserved for future logging                  0x00000080
#define CLOCK_FLAG_DO_NOT_DISABLE               0x00000100
#define CLOCK_FLAG_SUPPRESSIBLE                 0x00000200
#define CLOCK_FLAG_DOMAIN_HOLD_VREG_REQUEST     0x00000400
#define CLOCK_FLAG_DOMAIN_DYNAMIC_CONFIG        0x00000800
#define CLOCK_FLAG_AUTOGATE                     0x00001000
#define CLOCK_FLAG_BIST_FAILURE_ANTICIPATED     0x00002000
#define CLOCK_FLAG_INTERNAL_CONTROL             0x00004000
#define CLOCK_FLAG_NO_POLL_AFTER_ENABLE         0x00008000
#define CLOCK_FLAG_INITIALIZED                  0x00010000
#define CLOCK_FLAG_ENABLED                      0x00020000
// Unused                                       0x00040000
#define CLOCK_FLAG_STUB_HW_RUMI                 0x00080000
#define CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF     0x00100000
#define CLOCK_FLAG_EXPLICIT_ACCESS_ONLY         0x00200000
#define CLOCK_FLAG_READ_ONLY                    0x00400000
#define CLOCK_FLAG_DFS_CONTROLLED               0x00800000
#define CLOCK_FLAG_STUB_HW_VIRTIO               0x01000000

/*
 * Domain type flags
 */
#define CLOCK_DOMAIN_TYPE_RCG 0x1
#define CLOCK_DOMAIN_TYPE_MUX 0x2

/*
 * Common definition for a NULL entry in the BSP source array.
 */
#define SRC_IDX_NULL 0xFF

/*
 * Forward prototypes.
 */
typedef struct ClockSourceNodeType ClockSourceNodeType;


/*
 * ClockHWVersionType;
 *
 * HW version information.
 *
 *  Min             - Minimum supported HW Major/Minor revision
 *  Max             - Maximum supported HW Major/Minor revision
 *                    '0xFF' indicates all versions.
 *  eChipInfoFamily - Chip this configuration is for. '0' indicates all chips.
 *  aeChipInfoId    - Array of chip id's that the configuration supports.
 *                    NULL indicates all chips.
 */
typedef struct
{
  struct
  {
    uint8_t nMajor;
    uint8_t nMinor;
  } Min;

  struct
  {
    uint8_t nMajor;
    uint8_t nMinor;
  } Max;

  ChipInfoFamilyType eChipInfoFamily;

} ClockHWVersionType;


/*
 * ClockSourceFreqConfigType
 *
 * Frequency configuration information for a PLL.
 *
 *  nFreqHz     - Frequency in Hz for this configuration..
 *  HALConfig   - Configuration to pass to the HAL.
 *  eVRegLevel  - Voltage level for this configuration.
 *  HWVersion   - Version of the chip HW this configuration is for.
 */
typedef struct
{
  HAL_clk_xbl_PLLConfigType  HALConfig;
  ClockHWVersionType         HWVersion;
} ClockSourceFreqConfigType;


/*
 * ClockMuxConfigType
 *
 * Configuration information for a clock mux.
 *
 *  nFreqHz           - Frequency in Hz for this configuration.
 *  pSource           - Pointer to source used by this configuration.
 *  HALConfig         - Configuration to pass to the HAL.
 *  eVRegLevel        - Voltage level for this configuration.
 *  HWVersion         - Version of the chip HW this configuration is for.
 *  pSourceFreqConfig - Optional pointer to a PLL to configure for this.
 */
typedef struct
{
  uint32_t                         nFreqHz;
  rail_voltage_level               eVRegLevel;
  HAL_clk_xbl_ClockMuxConfigType   HALConfig;
  uint8_t                          nSourceIdx;
  uint8_t                          nSourceFreqConfigIdx;
  ClockHWVersionType               HWVersion;
} ClockMuxConfigType;


/**
 * Static source register settings type.
 */
typedef struct ClockSourceRegSettingsType
{
  HAL_clk_xbl_SourceRegSettingsType HALSettings;  /* Register settings. */
  ClockHWVersionType                HWVersion;    /* HW version these settings apply to. */
} ClockSourceRegSettingsType;

/* A type for domain masters */
typedef enum
{
  CLOCK_MASTER_APCS,
  CLOCK_MASTER_DEFAULT = CLOCK_MASTER_APCS,
  CLOCK_MASTER_RPMH,
  CLOCK_MASTER_AOSS,
  CLOCK_MASTER_MAX_SIZE
} ClockMasterType;

/**
 * Clock source type.
 */
struct ClockSourceNodeType
{
  const ClockSourceFreqConfigType   *aBSP;                          /**< Frequency configuration array. */
  const ClockSourceFreqConfigType   *pCalibrationFreqConfig;        /**< Pointer to calibration config */
  const ClockSourceRegSettingsType  *pRegSettings;                  /**< Static register settings. */
  HAL_clk_xbl_RegisterMaskType       VoterRegister;
  HAL_clk_xbl_SourceControlType     *pmControl;
  uint32_t                           nAddr;
  uint32_t                           nFlags;                        /**< Source flags. */
  uint32_t                           nConfigMask;                   /**< Configuration mask */
  uint8_t                            nCalibrationFreqConfigLen;
  uint8_t                            nBSPLen;                       /**< Length of aBSP. */
  uint8_t                            nRegSettingsLen;               /**< Length of pRegSettings. */
};


/**
 * Clock domain type.
 */
typedef struct
{
  ClockMuxConfigType              *aBSP;                          /**< Frequency configuration array. */
  const ClockMuxConfigType        *pActiveMuxConfig;              /**< Pointer to active config */
  uint32_t                         nCGRAddr;
  uint8_t                          nGenType;
  uint8_t                          nBSPLen;                       /**< Length of aBSP. */
  uint8_t                          eMaster;                       /**< Domain master. */
} ClockDomainNodeType;


/**
 * Clock type.
 */
// split this into two differnt structs one with name and one without
typedef struct
{
  const char                   *szName;                            /**< Clock name. */
  ClockDomainNodeType          *pDomain;                           /**< Domain this clock belongs to. */
  uint32_t                      nFlags;                            /**< Clock flags. */
  uint32_t                      nBranchAddr;
  HAL_clk_xbl_RegisterMaskType  mHWVotable;
} ClockNodeType;


/**
 * Power domain type.
 */
typedef struct
{
  const char                        *szName;                            /**< Power domain name. */
  HAL_clk_xbl_PowerDomainDescType    HALPowerDomain;                    /**< HAL power domain structure. */
} ClockPowerDomainNodeType;


/**
 * Clock divider type.
 */
typedef struct ClockDivider
{
  const char                  *szName;      /**< Clock divider name. */
  uint32_t                     nFlags;      /**< Divider flags. */
  HAL_clk_xbl_DividerDescType  HALDivider;  /**< HAL clock divider structure. */
} ClockDividerNodeType;


/**
 * Clock group type.
 */
typedef struct ClockGroup
{
  const char           *szName;              /**< Clock group name. */
  ClockNodeType        *aClocks;            /**< Array of clocks. */
  ClockDomainNodeType **aDomains;           /**< Array of clock domains. */
  uint32_t             *aPowerDomains;      /**< Array of power domains. */
  uint32_t              nResetAddr;
  uint8_t               nClocks;              /**< Length of aClocks. */
  uint8_t               nDomains;             /**< Length of aDomains. */
  uint8_t               nPowerDomains;        /**< Length of aPowerDomains. */
} ClockGroupType;


/**
 * Main clock BSP type.
 */
typedef struct ClockBSP
{
  ClockNodeType              *aClocks;           /**< Array of clocks. */
  ClockDomainNodeType       **aDomains;          /**< Array of clock domains. */
  ClockSourceNodeType       **aSources;          /**< Array of clock sources. */
  ClockPowerDomainNodeType   *aPowerDomains;     /**< Array of power domains. */
  ClockGroupType             *aClockGroups;      /**< Array of clock groups. */
  ClockDividerNodeType       *aDividers;         /**< Array of clock dividers .*/
  uint32_t                  *aPDEnable;
  uint32_t                  *aBranchEnable;
  HAL_clk_xbl_RegisterMaskType   *aBranchVote;
  HAL_clk_xbl_ClockMuxConfigType  SafeMuxConfig;     /**< Default safe mux configuration. */
  uint32_t                    nFlags;            /**< Clock driver flags. */
  uint8_t                     nNumClocks;        /**< Length of aClocks. */
  uint8_t                     nNumDomains;       /**< Length of aDomains. */
  uint8_t                     nNumSources;       /**< Length of aSources. */
  uint8_t                     nNumPDEnables;     /**< Length of aPDEnable. */
  uint8_t                     nNumBranchEnables; /**< Length of aBranchEnable. */
  uint8_t                     nNumBranchVotes;   /**< Length of aBranchEnable. */
  uint8_t                     nNumClockGroups;   /**< Length of aClockGroups. */
  uint8_t                     nNumPowerDomains;  /**< Length of aPowerDomains. */
  uint8_t                     nNumDividers;      /**< Length of aDividers. */
} ClockBSPType;


#endif  /* __CLOCKBSP_H__ */ 

