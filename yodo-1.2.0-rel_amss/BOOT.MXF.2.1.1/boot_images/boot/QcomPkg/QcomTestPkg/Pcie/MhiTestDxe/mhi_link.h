#ifndef MHI_LINK_H
#define MHI_LINK_H
/**
 *  @file mhi_link.h
 *
 *  @brief This file contains the link-level MHI interface.
 */
/*=============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_i.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
 * This function enables the underlying link for this MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_link_enable(mhi_dev_t *dev);

/**
 * This function disables the underlying link for this MHI device.
 *
 * @param[in]  dev  Device context
 *
 * @return SUCCESS or an error code
 */
int32 mhi_link_disable(mhi_dev_t *dev);

#endif

