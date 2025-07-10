/**
 *  @file mhi_link.c
 *
 *  @brief This file contains the MHI link-level implementation.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_link.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function enables the underlying link for this MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_link_enable(mhi_dev_t *dev)
{
   return NOT_SUPPORTED;
}

/**
 * This function disables the underlying link for this MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_link_disable(mhi_dev_t *dev)
{
   return NOT_SUPPORTED;
}

