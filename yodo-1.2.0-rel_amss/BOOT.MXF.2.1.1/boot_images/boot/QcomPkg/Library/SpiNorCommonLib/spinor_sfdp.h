/**********************************************************************
 * spinor_sfdp.h
 *
 * Serial Flash Discoverable Parameters
 *
 * Copyright (c) 2020 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE

when        who  what, where, why
----------  ---  -------------------------------------------------------
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2020-04-08  wek  Create.

======================================================================*/
#ifndef __SPINOR_SFDP__H
#define __SPINOR_SFDP__H

#include "spinor_api.h"
#include "spinor_init_config.h"

/**********************************************************
 * Read the SFDP Data and populate the spinor configuration structure.
 *
 * @param config [IN/OUT]
 *   SPI-NOR device configuration structure.
 *
 * @param manufacturer [IN]
 *   Manufacturer ID, least significant byte of spinor_core_read_device_id()
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_read_sfdp(spinor_config_data *config, uint8 manufacturer);


#endif /* __SPINOR_SFDP__H */
