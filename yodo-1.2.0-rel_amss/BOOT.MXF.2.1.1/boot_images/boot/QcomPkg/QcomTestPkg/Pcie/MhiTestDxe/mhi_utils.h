#ifndef MHI_UTILS_H
#define MHI_UTILS_H
/**
 *  @file mhi_utils.h
 *
 *  @brief This file contains the interface for MHI utilities.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_i.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Default alignment for memory allocation */
#define MHI_ALIGN_DEFAULT 4

/** Macro to check whether a uint32 value (val) is aligned to a specified power
 *  of two (align)
 */
#define MHI_IS_ALIGNED(val, align)  (((val) & (align) - 1) == 0)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
 * This function rounds up to the nearest power of two.
 *
 * @param[in]  num  Number to round up
 *
 * @return num rouned up to the nearest power of two
 */
uint32 mhi_round_up_pow_of_2(uint32 num);

/**
 * This function gets the state string name for a state enum value.
 *
 * @param[in]  state  MHI state
 *
 * @return Corresponding state string name
 */
const char *mhi_state_to_str(mhi_state_t state);

#endif

