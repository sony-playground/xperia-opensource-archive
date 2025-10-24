/*=============================================================================

                            XRC Communication

 Communication between XBL-slvcom and XRC.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/
#ifndef XRC_COMM_H
#define XRC_COMM_H

#ifdef __cplusplus
extern "C" {
#endif
/*===========================================================================

                           INCLUDE FILES

=============================================================================*/
#include "xrc_types.h"
#include "xrc_log.h"
#include "slvcom.h"

/*==========================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/
/*===========================================================================
 FUNCTION: xrc_map_error_code
=============================================================================*/
/**
 DESCRIPTION:
 Return failure code of helios for respective failure returned by slvcom.

 INPUT PARAMETERS:
 slvcom_error: 32-bit register read.

 RETURN VALUE:
 SUCCESS.
*/
/*==========================================================================*/
status_codes xrc_map_error_code
(
	slvcom_err_type
);

/*==========================================================================
 FUNCTION: xrc_open_communication
============================================================================*/
/** DESCRIPTION:
 Registers helios as a client to slvcom.

 INPUT PARAMETERS:
 pHandle: Address of the memory where, slvcom handle will be written.

 RETURN VALUE:
 status_codes based on slvcom error.
*/
/*=============================================================================*/
status_codes xrc_open_communication
(
	slvcom_handle_type*
);

/*==============================================================================
 FUNCTION: xrc_close_communication
================================================================================*/
/**
 DESCRIPTION:
 Unregisters helios as a client to slvcom.

 INPUT PARAMETERS:
 pHandle: Adrress of slvcom handle.

 RETURN VALUE:
 SUCCESS.
*/
/*==============================================================================*/
status_codes xrc_close_communication
(
	slvcom_handle_type*
);


/*================================================================================
FUNCTION: xrc_read_register
================================================================================*/
/**
* DESCRIPTION:
* Read BG registers.
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
* register_addr: 8-bit address of the BG register.
* num_regs: # of continuous registers to be read.
* pRead: pointer to the memory, where contents BG register needs to be written.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*==================================================================================*/
status_codes xrc_read_register
(
	slvcom_handle_type, 
	uint8_t, 
	uint8_t, 
	uint32_t*
);

/*====================================================================================
FUNCTION: xrc_write_register
====================================================================================*/
/** DESCRIPTION:
 *  Write to BG registers.
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
* register_addr: 8-bit address of the BG register.
* num_regs: # of continuous registers to be Written.
* pWrite_buffer: pointer to the memory, whose contents needs to written to BG registers.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*=====================================================================================*/

status_codes xrc_write_register
(
	slvcom_handle_type, 
	uint8_t, 
	uint8_t, 
	uint32_t*
);


/*=====================================================================================
FUNCTION: xrc_read_ahb
=======================================================================================*/
/** DESCRIPTION:
* Read AHB memory.
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
* ahb_start_addr: address of the AHB memory to be read.
* num_words: # of words of memory to be read.
* read_buf: pointer to the memory, where contents AHB needs to be dumped.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*=======================================================================================*/
status_codes xrc_read_ahb
(
	slvcom_handle_type, 
	uint32_t, 
	uint32_t, 
	phys_addr_t
);


/*=======================================================================================*/
/** FUNCTION: xrc_write_ahb
*
* DESCRIPTION:
* Write to AHB memory.
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
* ahb_start_addr: address of the AHB memory to be Written.
* num_words: # of words of memory to be written.
* write_buf: pointer to the memory, whose contents needs to be written to AHB.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*=========================================================================================*/
status_codes xrc_write_ahb
(
	slvcom_handle_type, 
	uint32_t, 
	uint32_t, 
	phys_addr_t
);


/*==========================================================================================*/
/** FUNCTION: xrc_secmode_enable
*
* DESCRIPTION:
* Set NS=0
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*===========================================================================================*/
status_codes xrc_secmode_enable
(
	slvcom_handle_type
);

/*===========================================================================================*/
/** FUNCTION: xrc_secmode_disable
*
* DESCRIPTION:
* Set NS=1
*
* INPUT PARAMETERS:
* handle: slvcom handle of helios.
*
* RETURN VALUE:
* status_codes based on slvcom error.
*/
/*=============================================================================================*/
status_codes xrc_secmode_disable
(
	slvcom_handle_type
);

#ifdef __cplusplus
}
#endif

#endif
