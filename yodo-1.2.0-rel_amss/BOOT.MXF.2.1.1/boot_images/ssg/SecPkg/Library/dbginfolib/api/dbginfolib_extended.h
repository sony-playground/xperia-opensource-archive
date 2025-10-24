/* ====================================================================
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * ====================================================================
 */
#ifndef _DBGINFOLIB_EXTENDED_H
#define _DBGINFOLIB_EXTENDED_H
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file dbginfolib_extended.h
 * @brief Definition of the extended debug info library API
 *
 * This header file provides the extended debug info library APIs for use by
 * subsystems to query system debug status. It is expected that the use of this
 * extended API would be limited to XBLSC and MODEM, execution environments that
 * have an atypical need to access such things as AUTH_EN and EUD enablement.
 */


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stdbool.h>

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

  ===========================================================================*/

/**
 *  @brief This function returns the state of auth enabled fuse.
  
    @returns A boolean answering whether AUTH is Enabled (i.e. whether this is a secure
             boot device)
  
    @details Returns whether the auth enabled fuse bit is set indicating a secure boot device.
 */
bool
dbgil_is_auth_enabled(void);

/**
 *  @brief This function returns the state of EUD Enablement
  
    @returns A boolean answering whether EUD is Enabled (on Wildcat platforms this is
             reflected in the "EUD DISABLE re-enable" bit located in the consolidated
             debug vector.
 */
bool
dbgil_is_eud_enabled(void);


/**
 *  @brief This function returns whether the OEM LCS is in the DEVELOPMENT state
  
    @returns A boolean answering whether the OEM Security Policy Fuses indicate that
             the device is in the DEVELOPMENT state (rather than the PRODUCTION state).
 */
bool
dbgil_is_oem_lcs_development_state(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /* _DBGINFOLIB_EXTENDED_H */
