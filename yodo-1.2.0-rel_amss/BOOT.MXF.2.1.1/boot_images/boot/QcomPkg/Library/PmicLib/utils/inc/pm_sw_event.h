#ifndef __PMICSWEVT_H__
#define __PMICSWEVT_H__
/*
===========================================================================
*/
/**
  @file ClockSWEVT.h

  This header provides a variety of preprocessor definitions, type, data, and
  function declarations for QDSS event logging.

  This file provides an abstraction layer for QDSS tracer features.

*/
/*
  ====================================================================

  Copyright (c) 2011-2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  Qualcomm Technologies, Inc Proprietary and Confidential.

  ====================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/inc/pm_sw_event.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  02/08/13   vk     Created.

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


#ifdef PMIC_NPA_LOGGING
#include "tracer.h"
#include "pm_sw_event_id.h"
#endif


/*=========================================================================
      Macros
==========================================================================*/


#ifdef PMIC_NPA_LOGGING
#define pm_sw_event(...)  \
  tracer_event_simple_vargs(__VA_ARGS__);
#else
#define pm_sw_event(...)
#endif


#endif // __PMICSWEVT_H__

