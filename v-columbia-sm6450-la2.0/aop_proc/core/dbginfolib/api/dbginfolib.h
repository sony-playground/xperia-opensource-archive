/* ====================================================================
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * ====================================================================
 */
#ifndef _DBGINFOLIB_H
#define _DBGINFOLIB_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file dbginfolib.h
 * @brief Definition of the debug info library API
 *
 * This header file provides the debug info library API for use by subsystems to
 * query system debug status. The APIs are divided into three classes:
 *
 *   - Basic system-wide debug status queries for such things as crash-dump settings
 *     and whether a debug policy was loaded that is serial-number bound.
 *
 *   - Subsystem debug option queries where the caller passes in a subsystem identifier,
 *     and the information is returned for *that* subsystem.  Such APIs can be utilized
 *     for use cases where the the caller knows which image it is calling from or where
 *     the debug status of other or multiple subsystems needs to be obtained.
 *
 *   - Subsystem debug option queries for the build-time-configured default subsystem.
 *     In this case the caller does not need to know what the underlying image is to
 *     make use of the API.
 *
 *  Additional background for this last class of APIs: There is a use-case for the debug
 *  info library API in the Q6 environment where it is difficult for the user of the API 
 *  to "know" which image the code is running on.  There was a request that we provide
 *  interfaces that are configured at build time (i.e. library compile time) to have
 *  a default subsystem set.  To be clear: this would be something that is set in the
 *  build environment when the API is ported for use with a particular image.
 *
 */


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 * Definitions and Type Declarations.
 * -------------------------------------------------------------------------*/

/**
   Crash Dump Options.  Note that with Non-Secure Dump, sensitive areas are encrypted or cleared.
 */
#define DBGIL_CDO_MINI_DUMP      UINT32_C(0x01)  /**< MiniDump */
#define DBGIL_CDO_NS_DUMP        UINT32_C(0x02)  /**< Non-Secure Dump - see note below */
#define DBGIL_CDO_SEC_FULL_DUMP  UINT32_C(0x04)  /**< Full Dump - no encryption */

/**
   Note that with Non-Secure Dump, sensitive areas are encrypted or cleared.
 */


/**
   Subsystem Identifiers for Wildcat Debug Info query APIs
 */
typedef enum
{
  DBGIL_SUBSYS_NONE          = 0, /* Possible return from dbgil_get_configured_image_subsystem() */
  DBGIL_SUBSYS_XBLSC         = 1,
  DBGIL_SUBSYS_AOP           = 2,
  DBGIL_SUBSYS_SHRM          = 3,
  DBGIL_SUBSYS_CPUCP         = 4,
  DBGIL_SUBSYS_APPS_SEC      = 5,
  DBGIL_SUBSYS_APPS_NSEC     = 6,
  DBGIL_SUBSYS_HYP           = 7,
  DBGIL_SUBSYS_MODEM_VECTOR  = 8,
  DBGIL_SUBSYS_MODEM_SCALAR  = 9,
  DBGIL_SUBSYS_ADSP          = 10,
  DBGIL_SUBSYS_CDSP          = 11,
  DBGIL_SUBSYS_SLPI          = 12, 
  DBGIL_SUBSYS_CAMERA        = 13,
  DBGIL_SUBSYS_GPU           = 14, 
  DBGIL_SUBSYS_WLAN          = 15, 
  DBGIL_NUMBER_SUBSYS        /* Must be last entry */
} dbgil_subsys_t;


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

  ===========================================================================*/


/* ========================================================================================
 * Basic system-wide debug status queries for such things as crash-dump settings
 */

/**
    Gets the crashdump_options value, a set of bit flags, indicating which crash dump options
    have been enabled on the system
  
    @returns A bit flag value representing the crashdump_options as specified by the 
             DBGIL_CDO_* #define values
  
    @details Internally, this function gets the globally configured Crash Dump Vector
             and converts this to the API define DBGIL_CDO_* values
 */
uint32_t
dbgil_get_crashdump_options(
  void
);


/**
    Tests whether a debug policy was loaded bound to the chip's Serial Number
    also known as Chip Unique ID binding.
  
    @param   none
  
    @returns A boolean answering whether a debug policy was loaded that is bound to the
             chip's serial number.
 */
bool
dbgil_is_serial_number_bound(
  void
);



/* ========================================================================================
 * Subsystem debug option queries where the caller passes in a subsystem identifier,
 * and the information is returned for *that* subsystem.
 */

/**
    Tests whether invasive debug is enabled for a given subsystem.
  
    @param [in]  subsystem          Subsystem (DBGIL_SS_*) whose debug vector value
                                      is being queried

    @returns A boolean answering whether invasive debug is enabled for a given subsystem
  
    @details This function accesses the debug vector using the TME_CONSOLIDATED_DEBUG_VECTOR_*
             CSRs.  The bit associated with invasive debug for the subsystem specified by
             the input parameter is tested and the result is returned.
 */
bool
dbgil_is_subsys_invasive_debug_enabled(
  dbgil_subsys_t subsystem
);


/**
    Tests whether non-invasive debug is enabled for a given subsystem.
 
    @param [in]  subsystem          Subsystem (DBGIL_SS_*) whose debug vector value
                                      is being queried

    @returns A boolean answering whether non-invasive debug is enabled for a given subsystem
  
    @details This function accesses the debug vector using the TME_CONSOLIDATED_DEBUG_VECTOR_*
             CSRs.  The bit associated with non-invasive debug for the subsystem
             specified by the input parameter is tested, and the result is returned.
 */
bool
dbgil_is_subsys_non_invasive_debug_enabled(
  dbgil_subsys_t subsystem
);


/**
    Gets Subsystem Debug Options for a subsytem identified by the input parameter.
  
    @param [in]  subsystem          Subsystem (DBGIL_SS_*) whose Subsystem Debug
                                      Options are being queried.

    @returns A 32-bit value representing the SubsystemDebugOptions that have been configured.
  
    @details This function queries, based on the subsystem parameter, the SubsystemDebugOptions
             that have been set in the active debug policies.  If no SubsystemDebugOptions are
             found for the specified subsystem, 0 is returned.
 */
uint32_t
dbgil_get_subsystem_debug_options(
  dbgil_subsys_t subsystem
);



/* ========================================================================================
 * Subsystem debug option queries for the *build-time-configured* default subsystem. See
 * the description at the top of this file to understand more about the motivation for
 * and high-level description of this set of APIs.
 */


/**
    Gets the subsystem identifier associated with the loaded image as configured during
    library build time.
  
    @param   none

    @returns A subsystem identifier associated with the loaded image as configured during
             library build time. If none configured, DBGIL_SUBSYS_NONE is returned.

    @details As part of library configuration / build, a default subsystem identifier can be
             associated with the image.  This allows the use of the dbgil_is_image_subsys*
             apis. The dbgil_get_configured_image_subsystem() API can be used to get which
             subsystem was configured.
 */
dbgil_subsys_t
dbgil_get_configured_image_subsystem(
  void
);



/**
    Tests whether non-invasive debug is enabled for the subsystem associated with the
    loaded image as configured during library build time.
 
    @returns A boolean answering whether non-invasive debug is enabled for the loaded image
             subsystem
  
    @details This function accesses the debug vector using the TME_CONSOLIDATED_DEBUG_VECTOR_*
             CSRs.  The bit associated with non-invasive debug for the subsystem specified by
             the input parameter is tested and the result is returned.
 */
bool
dbgil_is_image_subsys_non_invasive_debug_enabled(
  void
);


/**
    Tests whether invasive debug is enabled for the subsystem associated with the
    loaded image as configured during library build time
  
    @returns A boolean answering whether invasive debug is enabled for the loaded image
             subsystem
  
  
    @details This function accesses the debug vector using the TME_CONSOLIDATED_DEBUG_VECTOR_*
             CSRs.  The bit associated with invasive debug for the subsystem specified by the
             input parameter is tested and the result is returned.
 */
bool
dbgil_is_image_subsys_invasive_debug_enabled(
  void
);


/**
    Gets Subsystem Debug Options for the subsystem associated with the loaded image as
    configured during library build time.
  
    @returns A 32-bit value representing the SubsystemDebugOptions that have been configured.
  
    @details This function queries, based on the subsystem configured during library build time,
             the SubsystemDebugOptions that have been set in the active debug policies.  If no
             SubsystemDebugOptions are found for the specified subsystem, 0 is returned.
 */
uint32_t
dbgil_get_image_subsystem_debug_options(
  void
);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /* _DBGINFOLIB_H */
