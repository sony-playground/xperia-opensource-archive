#ifndef __PCIE_BOOT_H__
#define __PCIE_BOOT_H__
/**
 * @file pcie_boot.h
 *
 * @brief This file contains the PCIe boot interface.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "com_dtypes.h"

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
 * Dumps the PCIe registers at the dump_addr specified.
 *
 * @param[in]  dump_addr   Address where the registers are dumped.
 * @param[in]  max_size    Maximum allowed size for the dump.
 *
 * @return None
 */
void pcie_reg_dump(void *dump_addr, uint32 max_size);

#endif

