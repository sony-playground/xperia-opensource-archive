/** @file DTBExtnLib_env.h
  Environment header file

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/16/20   tmt     INSTRUMENTAION build flag added
 11/23/20   tmt     Initial port of Library to 2nd architecture

=============================================================================*/

#ifndef DTBEXTNLIB_ENV_H_
#define DTBEXTNLIB_ENV_H_

/*=========================================================================
     Instrumentation
==========================================================================*/

#ifdef INSTRUMENTATION
#include <stdio.h>
#define SNPRINTF(a,b,c, ...) snprintf(a, b, c, ##__VA_ARGS__)
#define PUTS(a) puts(a)
#define DTB_HEX_DUMP(a,b,c) dtb_hex_dump(a, b, c)
#else
#define SNPRINTF(a,b,c, ...)
#define PUTS(a)
#define DTB_HEX_DUMP(a,b,c)
#endif

/*=========================================================================
     Supported Architectures
==========================================================================*/

// #define PORT_ARMv8
// #define PORT_Q6

/*========================================================================*/
#ifdef PORT_ARMv8

#ifdef INSTRUMENTATION

#ifndef BUILD_X86
#include "boot_logger_if.h"
#else
#include "../../../Settings/Tools/Training/x86-prototype/examples/junkdrawer.h"
#endif

#define puts boot_log_message

#endif

#endif

/*========================================================================*/
#ifdef PORT_Q6

#include "libfdt_env.h"

#endif

#endif  /* DTBEXTNLIB_ENV_H_ */
