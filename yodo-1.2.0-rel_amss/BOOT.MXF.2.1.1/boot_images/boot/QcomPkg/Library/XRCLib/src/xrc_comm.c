/*=============================================================================

                            XRC COMM

Communication between XBL-slvcom and XRC (Helios).

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#include "xrc_comm.h"
#include "xrc_log.h"
#include "xrc_utils.h"
#include "slvcom.h"

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
	slvcom_err_type slvcom_error
) 
{
    status_codes helios_error;
    helios_error = FAILURE;
    switch (slvcom_error) {
    case SLVCOM_ERR_NONE:
        helios_error = SUCCESS;
        break;
    case SLVCOM_ERR_RESET:
        helios_error = FAIL_slvcom_BG_RESET;
        break;
    case SLVCOM_ERR_SPI_ERR:
        helios_error = FAIL_slvcom_SPI_TRANSFER;
        break;
    case SLVCOM_ERR_INVALID_PARAM:
        helios_error = FAILURE;
        break;
    case SLVCOM_ERR_OUT_OF_RESOURCES:
        helios_error = FAILURE;
        break;
    case SLVCOM_ERR_NOT_RESPONSIVE:
        helios_error = FAIL_slvcom_BG_NOT_RESPONDING;
        break;
    case SLVCOM_ERR_GPIO_ERR:
        helios_error = FAIL_slvcom_GPIO_ERROR;
        break;
    case SLVCOM_ERR_INVALID_SECMODE_ERR:
        helios_error = FAIL_SECMODE_DISABLE;
        break;
    case SLVCOM_ERR_DUPLICATE_CLIENT:
        helios_error = FAIL_slvcom_CLIENT_EXISTS;
        break;
    default:
        helios_error = FAILURE;
        break;
    }
    return helios_error;
}

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
/*=============================================================================*/status_codes xrc_open_communication
(
	slvcom_handle_type *pHandle
) 
{
    slvcom_err_type nReturn_val = SLVCOM_ERR_NONE;
    slvcom_open_config_type* open_config = NULL;

    open_config = (slvcom_open_config_type*) xrc_os_malloc(
            sizeof(slvcom_open_config_type));

	  if (open_config == NULL) 
	  {
        XRC_LOG_ERR(1, "xrc_os_malloc fail %d ", FAIL_MEM_ALLOC);
        return FAIL_MEM_ALLOC;
    }
	
    memset(open_config, 0, sizeof(slvcom_open_config_type));

    slvcom_init();
   
	  SLVCOM_OPEN_CONFIG_INIT(open_config); 
	  
	  open_config->name = "Slate";
	  
	  nReturn_val = slvcom_open(open_config, pHandle);
    XRC_LOG_ERR(1, "slvcom_open fail %d ", nReturn_val);
	
    xrc_os_free(open_config);
	
    return xrc_map_error_code(nReturn_val);
}

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
	slvcom_handle_type *pHandle
) 
{
    slvcom_deinit();
    return SUCCESS;
}

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
	slvcom_handle_type handle, 
	uint8_t register_addr,
    uint8_t num_regs, 
	uint32_t* pRead
) 
{
    uint32_t uRead_buff_size = 0;
    slvcom_err_type eReturn_val;

    uRead_buff_size = num_regs * sizeof(uint32_t);
    eReturn_val = slvcom_reg_read(handle, register_addr, num_regs, pRead,
            uRead_buff_size);

	return xrc_map_error_code(eReturn_val);
}

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
	slvcom_handle_type handle, 
	uint8_t register_addr,
    uint8_t num_regs, 
	uint32_t* pWrite_buffer
) 
{
    uint32_t nWrite_buff_size = 0;

    slvcom_err_type nReturn_val;

    nWrite_buff_size = num_regs * sizeof(uint32_t);
    nReturn_val = slvcom_reg_write(handle, register_addr, num_regs,
            pWrite_buffer, nWrite_buff_size);
	
    return xrc_map_error_code(nReturn_val);
}

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
	slvcom_handle_type handle, 
	uint32_t ahb_start_addr,
    uint32_t num_words, 
	phys_addr_t read_buf
) 
{
    uint32_t nRead_buff_size = 0;

    slvcom_err_type nReturn_val;

    nRead_buff_size = num_words * sizeof(phys_addr_t);
    nReturn_val = slvcom_ahb_read(handle, ahb_start_addr, num_words,
            (void*)(uintptr_t) read_buf, nRead_buff_size);

	return xrc_map_error_code(nReturn_val);
}

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
	slvcom_handle_type handle, 
	uint32_t ahb_start_addr,
    uint32_t num_words, 
	phys_addr_t write_buf
) 
{
    uint32_t nWrite_buff_size = 0;
    slvcom_err_type nReturn_val;

	nWrite_buff_size = num_words * sizeof(phys_addr_t);
     nReturn_val = slvcom_ahb_write(handle, ahb_start_addr, num_words,
            (void *)(uintptr_t) write_buf, nWrite_buff_size);

	return xrc_map_error_code(nReturn_val);
}

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
	slvcom_handle_type handle
) 
{
    slvcom_err_type nReturn_val;

    nReturn_val = slvcom_secmode_enable(handle);

	return xrc_map_error_code(nReturn_val);
}

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
	slvcom_handle_type handle
) 
{
    slvcom_err_type nReturn_val;

    nReturn_val = slvcom_secmode_disable(handle);

	return xrc_map_error_code(nReturn_val);
}

