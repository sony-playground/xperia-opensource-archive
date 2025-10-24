#ifndef __CLOCK_H__
#define __CLOCK_H__

/*
================================================================================
*/
/**
  @file clock.h
  @brief Public interface include file for accessing the clock driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/api/systemdrivers/clock/clock.h#4 $
  $DateTime: 2022/04/08 11:44:05 $
  $Author: pwbldsvc $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include "ClockDefs.h"
#include "qmp_msg_driver.h"
#include "clock_target.h"


/*==============================================================================
  Prototypes
==============================================================================*/

/** @addtogroup clock_functions
@{ */

/* =============================================================================
**  Function : Clock_Init
** ===========================================================================*/
/**
  Performs AOP clock driver initialization. Should be invoked directly from
  target_main.

  @param
  None.

  @return
  None.

  @dependencies
  SMEM should to be initialized.
*/

void Clock_Init
(
  void
);

/* =============================================================================
**  Function : Clock_PostInit
** ===========================================================================*/
/**
  Performs AOP clock driver initialization at a later stage. Should be invoked
  directly from target_main.

  @param
  None.

  @return
  None.

  @dependencies
  Below driver initialization routines should have been completed
    qmp_msg_init
    aop_server_init
    aop_sleep_init
*/

void Clock_PostInit
(
  void
);

/* =============================================================================
**  Function : Clock_SwitchToHWCtrlMode
** ===========================================================================*/
/**
  Switches power domain and PLLs from SW to HW controlled mode. Should be invoked
  directly from icb_post_init.

  @param
  None.

  @return
  None.

  @dependencies
  BCM should be initialized.
*/

void Clock_SwitchToHWCtrlMode
(
  void
);

/* =============================================================================
**  Function : Clock_QDSSSetPerfLevel
** ===========================================================================*/
/**
  Set QDSS clocks' performance level.

  @param[in]  eLevel   QDSS performance level
  @param[in]  eSubsys  Subsystem ID that is voting for QDSS resources. If any
                       local AOP client is voting, then use the corresponding
                       EDGE enum from qmp_msg_driver.h.

  @return
  None.

  @dependencies
  None.
*/

void Clock_QDSSSetPerfLevel
(
  ClockQDSSLevelType eLevel,
  EDGE               eSubsys
);

/* =============================================================================
**  Function : Clock_ProcessorReduce
** ===========================================================================*/
/**
  This function is used for doing clock related changes around AOP WFI/DLITE.

  @param[in]  bEnable   Boolean flag to indicate sleep/restore

  @return
  None.

  @dependencies
  None.
*/

void Clock_ProcessorReduce
(
  bool bEnable
);

/* =============================================================================
**  Function : Clock_ProcessorShutdown
** ===========================================================================*/
/**
  This function is used for doing clock related changes around CX min.

  @param[in]  bEnable   Boolean flag to indicate sleep/restore

  @return
  None.

  @dependencies
  None.
*/

void Clock_ProcessorShutdown
(
  bool bEnable
);

/* =============================================================================
**  Function : Clock_GetBootConfigCP
** ===========================================================================*/
/**
  Gets the clock performance level settings shared from bootloader.

  @param
  None.

  @return
  Pointer to clock settings structure.

  @dependencies
  SMEM should be initialized.
*/

ClockCfgCPType* Clock_GetBootConfigCP
(
  void
);

/* =============================================================================
**  Function : Clock_GetBootConfigDDR
** ===========================================================================*/
/**
  Gets the DDR configuration settings shared from bootloader. This has been a
  stub function for a few generations and will be cleaned up soon.

  @param
  None.

  @return
  Pointer to DDR settings structure

  @dependencies
  None.
*/

DDRCfgType* Clock_GetBootConfigDDR
(
  void
);

/** @} */ /* end_addtogroup clock_functions */

#endif /* __CLOCK_H__ */
