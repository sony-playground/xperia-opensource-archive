#ifndef __HALCLKINTERNALLOADER_H__
#define __HALCLKINTERNALLOADER_H__
/*
==============================================================================

FILE:         HALclkInternal.h

DESCRIPTION:
  Internal definitions for the clock HAL module.

==============================================================================
      Copyright (c) 2020 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include <HALclkXBL.h>
#include "stdbool.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * ENCODE_NOT_2D / ENCODE_NOT_N_MINUS_M
 *
 * Macros to return the inverted value of the 2D field or (N - M)
 * in a type 1 mux structure.  Used to prepare the value for writing
 * to the hardware register field.
 */
#define ENCODE_NOT_2D(mux)         (~(mux)->nN)
#define ENCODE_NOT_N_MINUS_M(mux)  (~((mux)->nN - (mux)->nM))

/*
 * DECODE_NOT_2D / DECODE_NOT_N_MINUS_M
 *
 * Macros to  unwind the inverted value of the 2D field or (N - M)
 * read from a type 1 mux register.  Used to find a match for a mux
 * config with a BSP entry.
 */
#define DECODE_NOT_2D(nNot2DVal)                     (~(nNot2DVal))
#define DECODE_NOT_N_MINUS_M(nNotNMinusMVal, nMVal)  (~(nNotNMinusMVal) + nMVal)

/*
 * DIVIDER
 *
 * Macro to return the normalized divider for a given mux structure.
 * Just subtracts 1 unless the value is already 0.
 */
#define DIVIDER(mux)  ((mux)->nDivider ? (mux)->nDivider - 1 : 0)

/*
 * HALF_DIVIDER
 *
 * Macro to return the normalized half divider for a given mux structure.
 * NOTE: Expecting (2 * divider) value as input.
 */
#define HALF_DIVIDER(mux)  ((mux)->nDiv2x ? (((mux)->nDiv2x) - 1) : 0)

/*
 * HAL_CLK_FMSK
 *
 * Define a register mask data structure given the register name
 * and field.
 */
#define HAL_CLK_FMSK(io, field)   \
  {                               \
    HWIO_ADDR(io),                \
    HWIO_FMSK(io, field)          \
  }


/*
 * HAL_CLK_FMSKI
 *
 * Define a register mask data structure given the index, register name
 * and field.
 */
#define HAL_CLK_FMSKI(io,index,field)   \
  {                               \
    HWIO_ADDR(io,index),         \
    HWIO_FMSK(io, field)          \
  }


/*
 * HAL_CLK_FMSKM
 *
 * Define a register mask data structure given the register name
 * and a mask.
 */
#define HAL_CLK_FMSKM(io, mask)   \
  {                               \
    HWIO_ADDR(io),                \
    mask                          \
  }


/*
 * Define an invalid source index for error detection.
 */
#define HAL_CLK_SOURCE_INDEX_INVALID 0xFFFFFFFF

/* HAL specific flags */
#define HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL         0x01

/* ============================================================================
**    Typedefs
** ==========================================================================*/

/*
 * HAL_clk_xbl_RegisterMaskType
 *
 * Contains a register address and mask, used for setting and clearing
 * a given set of bits.
 *
 * nAddr - Address of the register (32-bit).
 * nMask - 32-bit mask.
 */
typedef struct
{
  uintptr_t nAddr;
  uint32_t  nMask;
} HAL_clk_xbl_RegisterMaskType;


/*
 * HAL_clk_xbl_ClockRegistersType
 *
 * nBranchAddr  - Clock branch address/offset.
 * nResetAddr   - Clock block reset address/offset.
 * mHWVotable   - Register/mask for HW votable configuration setup.
 */
typedef struct
{
  uint32_t                     nBranchAddr;
  HAL_clk_xbl_RegisterMaskType mHWVotable;
} HAL_clk_xbl_ClockRegistersType;

typedef uint8 HAL_clk_xbl_ClockControlType;

/*
 * HAL_clk_xbl_SourceControlType
 *
 * Set of function pointers used to control a clock source.
 *
 * Enable          - Enable the given source.
 * Disable         - Disable the given source.
 * IsEnabled       - Check if the given source is enabled.
 * Config          - Configure the given source.
 * ConfigPLL       - Configure the given PLL source parameters.
 * DetectPLLConfig - Get the current configuration for the source.
 * EnableVote      - Enable vote the given source.
 * DisableVote     - Disable vote the given source.
 * IsVoteEnabled   - Check if the given source vote is enabled.
 */
typedef struct
{
  bool (*Enable)             ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
  bool (*IsEnabled)          ( HAL_clk_xbl_SourceDescType *pSource );
  void (*Config)             ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
  bool (*ConfigPLL)          ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
  bool (*EnableVote)         ( HAL_clk_xbl_SourceDescType *pSource );
  bool (*IsVoteEnabled)      ( HAL_clk_xbl_SourceDescType *pSource );
  bool (*SetCalConfig)       ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig);
  void (*SetRegSettings)     ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );
} HAL_clk_xbl_SourceControlType;


/*
 * HAL_clk_xbl_ClockDomainControlType
 *
 * ConfigMux         - Configure the given clock mux.
 * DetectMuxConfig   - Return the current configuration of the mux for the clock.
 * IsOn              - Returns whether the RCG domain is on or not.
 * RootEnable        - Assert/deassert the given clock mux CGR_ROOT_EN bit.
 */
typedef struct
{
  void    (*ConfigMux)          ( HAL_clk_xbl_ClockDomainDescType *pmClkDomainDesc, const HAL_clk_xbl_ClockMuxConfigType *pmConfig );
} HAL_clk_xbl_ClockDomainControlType;


typedef uint8 HAL_clk_xbl_PowerDomainControlType;

typedef uint8 HAL_clk_xbl_DividerControlType;

typedef uint8 HAL_clk_xbl_DebugMuxControlType;


/*
 * HAL_clk_xbl_ClockDescType
 *
 * Description of a clock, including required data to control the
 * clock.
 *
 * mRegisters  - (optional) Set of registers used by the
 *               common clock control functions (HAL_clk_xbl_ClockControl*).
 * pmControl   - Pointer to the control functions for this clock.  If NULL
 *               then the clock is not supported.
 * nDebugMuxSel - Input select value for this clock on its debug mux.
 *
 */
struct HAL_clk_xbl_ClockDescType
{
  HAL_clk_xbl_ClockRegistersType  mRegisters;
};


/*
 * HAL_clk_xbl_ClockDomainDescType
 *
 * Description of a clock domain, including required data to control the
 * clock domain.
 *
 * nCGRAddr          - (First) Clock generation register address/offset.
 * pmControl         - Pointer to the control functions for this domain.
 * nMNDWidth         - Width of MND counter.
 * nDFSStates        - Max number of DFS states.
 * nFlags            - Domain flags
 */
// struct HAL_clk_xbl_ClockDomainDescType
// {
//   uint32_t                            nCGRAddr;
//   HAL_clk_xbl_ClockDomainControlType  *pmControl;
// };


/*
 * HAL_clk_xbl_SourceDescType
 *
 * Description of a clock source, including control functions.
 *
 * nAddr          - Source base address.
 * VoterRegister  - Register/mask for HW votable configuration setup.
 * pmControl      - Pointer to the control functions for this source.  If NULL
 *                  then the source is not supported.
 */
struct HAL_clk_xbl_SourceDescType
{
  HAL_clk_xbl_RegisterMaskType   VoterRegister;
  HAL_clk_xbl_SourceControlType *pmControl;
  uintptr_t                      nAddr;
};


/*
 * HAL_clk_xbl_PowerDomainDescType
 *
 * Description of a power domain, including control functions.
 *
 * nGDSCRAddr           - Global distributed switch controller (GDSC) register address.
 * VoterRegister        - Register/mask for HW votable configuration setup.
 * pmControl            - Pointer to the control functions for this power domain.  If
 *                        NULL then the power domain is not supported.
 * pmClockMemCore       - Pointer to the optional list of clocks used to control MEM CORE
 *                        sleep behavior.
 * pmClockMemPeriph     - Pointer to the optional list of clocks used to control MEM PERIPH
 *                        sleep behavior.
 */
struct HAL_clk_xbl_PowerDomainDescType
{
  uint32_t nGDSCRAddr;
};


/*
 * HAL_clk_xbl_DividerDescType
 *
 * Description of a clock divider, including control functions.
 *
 * nAddr      - Clock divider base address.
 * pmControl  - Pointer to the control functions for this power domain. If
 *              NULL then the power domain is not supported.
 */
struct HAL_clk_xbl_DividerDescType
{
  uintptr_t nAddr;
};


/*
 * HAL_clk_xbl_DebugMuxDescType
 *
 * Description of a debug mux, including required data to control the
 * clock.
 *
 * pmControl   - Pointer to the control functions for this debug mux. If NULL
 *               then the debug mux is not supported.
 */
struct HAL_clk_xbl_DebugMuxDescType
{
  HAL_clk_xbl_DebugMuxControlType *pmControl;
};

#endif /* !HALCLKINTERNALLOADER_H */
