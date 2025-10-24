#ifndef MHI_LOG_H
#define MHI_LOG_H
/**
 *  @file mhi_log.h
 *
 *  @brief This file contains the MHI logging interface.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "pcie_osal.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Log levels (enum values cannot be used with the preprocessor) */
#define MHI_LOG_LEVEL_LOW   0
#define MHI_LOG_LEVEL_MED   1
#define MHI_LOG_LEVEL_HIGH  2
#define MHI_LOG_LEVEL_ERROR 3
#define MHI_LOG_LEVEL_FATAL 4

/** Default log levels */
#ifndef MHI_LOG_LEVEL
#define MHI_LOG_LEVEL MHI_LOG_LEVEL_MED
#endif

/** Default profiling log levels */
#ifndef MHI_PROFILE_LEVEL
#define MHI_PROFILE_LEVEL MHI_LOG_LEVEL_MED
#endif

/** The following macros wrap pcie_osal_log_* to avoid having to specify the
 *  client ID. Additinally, these macros allow for logging less than
 *  MHI_LOG_LEVEL to be compiled out. FATAL messages cannot be compiled out.
 *
 *  The macros include:
 *  - MHI_LOG_LOW(fmt, ...)
 *  - MHI_LOG_MED(fmt, ...)
 *  - MHI_LOG_HIGH(fmt, ...)
 *  - MHI_LOG_ERROR(fmt, ...)
 *  - MHI_LOG_FATAL(fmt, ...)
 *
 */
#if MHI_LOG_LEVEL <= MHI_LOG_LEVEL_LOW
#define MHI_LOG_LOW(fmt, ...) \
   pcie_osal_log_low(PCIE_OSAL_LOG_MHI, (fmt), ## __VA_ARGS__)
#else
#define MHI_LOG_LOW(fmt, ...) do { } while(0)
#endif

#if MHI_LOG_LEVEL <= MHI_LOG_LEVEL_MED
#define MHI_LOG_MED(fmt, ...) \
   pcie_osal_log_med(PCIE_OSAL_LOG_MHI, (fmt), ## __VA_ARGS__)
#else
#define MHI_LOG_MED(fmt, ...) do { } while(0)
#endif

#if MHI_LOG_LEVEL <= MHI_LOG_LEVEL_HIGH
#define MHI_LOG_HIGH(fmt, ...) \
   pcie_osal_log_high(PCIE_OSAL_LOG_MHI, (fmt), ## __VA_ARGS__)
#else
#define MHI_LOG_HIGH(fmt, ...) do { } while(0)
#endif

#if MHI_LOG_LEVEL <= MHI_LOG_LEVEL_ERROR
#define MHI_LOG_ERROR(fmt, ...) \
   pcie_osal_log_error(PCIE_OSAL_LOG_MHI, (fmt), ## __VA_ARGS__)
#else
#define MHI_LOG_ERROR(fmt, ...) do { } while(0)
#endif

#define MHI_LOG_FATAL(fmt, ...) \
   pcie_osal_log_fatal(PCIE_OSAL_LOG_MHI, (fmt), ## __VA_ARGS__)

/** Profiling macros
 *
 *  The macros include:
 *  - MHI_PROFILE_LOW(fmt, ...)
 *  - MHI_PROFILE_MED(fmt, ...)
 *  - MHI_PROFILE_HIGH(fmt, ...)
 */
#if defined(MHI_PROFILING_ENABLED) && MHI_PROFILE_LEVEL <= MHI_LOG_LEVEL_LOW
#define MHI_PROFILE_LOW(fmt, ...) \
   pcie_osal_log_low(PCIE_OSAL_LOG_MHI_PROFILING, (fmt), ## __VA_ARGS__)
#else
#define MHI_PROFILE_LOW(fmt, ...) do { } while(0)
#endif

#if defined(MHI_PROFILING_ENABLED) && MHI_PROFILE_LEVEL <= MHI_LOG_LEVEL_MED
#define MHI_PROFILE_MED(fmt, ...) \
   pcie_osal_log_med(PCIE_OSAL_LOG_MHI_PROFILING, (fmt), ## __VA_ARGS__)
#else
#define MHI_PROFILE_MED(fmt, ...) do { } while(0)
#endif

#if defined(MHI_PROFILING_ENABLED) && MHI_PROFILE_LEVEL <= MHI_LOG_LEVEL_HIGH
#define MHI_PROFILE_HIGH(fmt, ...) \
   pcie_osal_log_high(PCIE_OSAL_LOG_MHI_PROFILING, (fmt), ## __VA_ARGS__)
#else
#define MHI_PROFILE_HIGH(fmt, ...) do { } while(0)
#endif

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#endif

