#ifndef __CLOCKSWEVT_H__
#define __CLOCKSWEVT_H__
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

  Copyright (c) 2011-2020 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockSWEVT.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  11/02/12   frv     Created.

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


#ifdef CLOCK_TRACER_SWEVT
#include "tracer.h"
#include "ClockSWEventId.h"
#endif


/*=========================================================================
      Macros
==========================================================================*/


#ifdef CLOCK_TRACER_SWEVT
#define Clock_SWEvent(...)  \
  tracer_event_simple_vargs(__VA_ARGS__);
#else
#define Clock_SWEvent(...)
#endif


#endif // __CLOCKSWEVT_H__

