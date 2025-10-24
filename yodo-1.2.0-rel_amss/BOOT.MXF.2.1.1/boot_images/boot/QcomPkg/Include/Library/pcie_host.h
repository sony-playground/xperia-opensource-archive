#ifndef __PCIE_HOST_H__
#define __PCIE_HOST_H__
/**
 *  @file pcie_host.h
 *
 *  @brief This header file defines the public interface for PCIe host.
 */
/*============================================================================
               Copyright (c) 2020 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "pcie_dtypes.h"
#include "com_dtypes.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
 * Enumerates the PCIe device(s) attached to the specified root port.
 *
 * @param[in]  rc_index    Root complex index on which the enumeration must be
 *                         performed.
 *
 * @return PCIE_SUCCESS       : the operation succeeded
 *         PCIE_ERROR         : the operation failed
 *         PCIE_INVALID_PARAM : an invalid parameter was passed
 */
pcie_status_t pcie_enumerate(uint32 rc_index);

#endif

