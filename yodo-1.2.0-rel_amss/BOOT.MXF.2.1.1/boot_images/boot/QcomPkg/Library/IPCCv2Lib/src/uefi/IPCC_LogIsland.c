/*
================================================================================
*/
/**
  @file IPCC_LogIsland.c

  This module implements the island-resident portion of the QDSP6 OS logging
  module for the IPCC driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/dev/core.tz/2.0/shantonu.core.tz.2.0.ipccHwMemOpt_tz/systemdrivers/ipcc/src/tz/IPCC_LogTZ.c#1 $
  $DateTime: 2022/04/13 23:13:14 $
  $Author: shantonu $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#ifndef IPCC_NO_LOG
#include <stdarg.h>
#include "IPCC_Log.h"


/*==============================================================================
  Functions
==============================================================================*/

/* =============================================================================
**  Function : IPCCLog_Out
** ===========================================================================*/
/**
  See IPCC_Log.h
*/

void IPCCLog_Out
(
  uint32_t    nArgs,
  const char *szMsg,
  ...
)
{
  /* No logging capability on this image */
  return;
}
#endif