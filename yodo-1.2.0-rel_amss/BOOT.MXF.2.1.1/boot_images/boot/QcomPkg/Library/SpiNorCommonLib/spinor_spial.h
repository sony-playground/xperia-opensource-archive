#ifndef __SPINOR_SPIAL__H
#define __SPINOR_SPIAL__H
/**********************************************************************
 * spinor_spial.h
 *
 * This file provides an interface to spi buses driver
 *
 * Copyright (c) 2017,2019,2020 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE


when        who  what, where, why
----------  ---  -----------------------------------------------
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2020-04-08  wek  Add SFDP support.
2019-03-12  wek  Expose the SPI power state to upper layers.
2017-05-25  md   Initial Release based on SPI-NOR driver from Quartz.

==================================================================*/
#include "quadspi.h"
#include "spinor_api.h"

typedef enum
{
   qspi_read_mode = 1,
   qspi_write_mode = 2,
   qspi_erase_mode = 3,
   qspi_erase_bulk_mode = 5,
   qspi_write_enable_mode = 6,
   qspi_register_read = 7,
   qspi_register_write = 8,
   qspi_read_sfdp_mode = 9,
} SPI_COMMAND_TYPE;

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

SPINOR_STATUS spial_init(bool ini_status);
SPINOR_STATUS spial_deinit(void *handle);
SPINOR_STATUS spial_enter_working_state(void);
SPINOR_STATUS spial_enter_low_power_state(void);
SPINOR_STATUS spial_transfer(SPI_COMMAND_TYPE cmd_mode, uint32_t addr, uint8 *reg_value, uint32 len, uint8_t opcode );




#endif /* __SPINOR_SPIAL__H */
