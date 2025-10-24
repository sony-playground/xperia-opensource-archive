#ifndef PCIE_HOST_LOG_H
#define PCIE_HOST_LOG_H
/**
 *  pcie_host_log.h
 *
 *  PCIE Host RC logging interface.
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Derived from ADSP implementation

*/
/*============================================================================
               Copyright (c) 2019 - 2021 Qualcomm Technologies, Inc.
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
#define LOG_LEVEL_LOW         0
#define LOG_LEVEL_MED         1
#define LOG_LEVEL_LOADER      2
#define LOG_LEVEL_HIGH        3
#define LOG_LEVEL_ERROR       4
#define LOG_LEVEL_FATAL       5
#define LOG_LEVEL_ALWAYS      5
#define LOG_LEVEL_NO_LOGS     6

/** The following macros wrap pcie_osal_log_* to avoid having to specify the
 *  client ID. Additinally, these macros allow for logging less than
 *  PCIE_HOST_LOG_LEVEL to be compiled out. FATAL messages cannot be compiled out.
 *
 *  The macros include:
 *  - PCIE_HOST_LOG_LOW(fmt, ...)
 *  - PCIE_HOST_LOG_MED(fmt, ...)
 *  - PCIE_HOST_LOG_HIGH(fmt, ...)
 *  - PCIE_HOST_LOG_LOADER(fmt, ...)
 *  - PCIE_HOST_LOG_ERROR(fmt, ...)
 *  - PCIE_HOST_LOG_ALWAYS(fmt, ...)
 *  - PCIE_HOST_LOG_FATAL(fmt, ...)
 *
 *  - PCIE_HOST_LOG_PERF(fmt, ...)
 *
 */

#if PCIE_HOST_LOG_LEVEL <= LOG_LEVEL_LOW
#define PCIE_HOST_LOG_LOW(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_LOW(fmt, ...) do { } while(0)
#endif

#if PCIE_HOST_LOG_LEVEL <= LOG_LEVEL_MED
#define PCIE_HOST_LOG_MED(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_MED(fmt, ...) do { } while(0)
#endif

#if PCIE_HOST_LOG_LEVEL <= LOG_LEVEL_HIGH
#define PCIE_HOST_LOG_HIGH(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_HIGH(fmt, ...) do { } while(0)
#endif

#if PCIE_HOST_LOG_LEVEL <= LOG_LEVEL_LOADER
#define PCIE_HOST_LOG_LOADER(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_LOADER(fmt, ...) do { } while(0)
#endif

#if PCIE_HOST_LOG_LEVEL <= LOG_LEVEL_ERROR
#define PCIE_HOST_LOG_ERROR(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_ERROR(fmt, ...) do { } while(0)
#endif

#ifdef PCIE_ENABLE_PERF_LOGS
#define PCIE_HOST_LOG_PERF(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_PERF(fmt, ...) do { } while(0)
#endif

#if PCIE_HOST_LOG_LEVEL < LOG_LEVEL_NO_LOGS
#define PCIE_HOST_LOG_FATAL(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_FATAL(fmt, ...)   do { } while(1)
#endif

#if PCIE_HOST_LOG_LEVEL < LOG_LEVEL_NO_LOGS
#define PCIE_HOST_LOG_ALWAYS(fmt, ...) \
   pcie_osal_log_msg((fmt), ## __VA_ARGS__)
#else
#define PCIE_HOST_LOG_ALWAYS(fmt, ...)   do { } while(0)
#endif

#endif

