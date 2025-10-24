/*=============================================================================

                            XRC UTILS

 Methods that parse the register bits.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/
#include "xrc_utils.h"

/*
    TZ_TO_MASTER_STATUS register
------------------------------------------    
|    Bit      |            Name                 |
|---------|------------------------------|    
|   31:29 |  Boot Loader status             |
|   28:26 |  Main Image status             |
|   23:16 |  TZ_TO_MASTER_DATA contents  |
-----------------------------------------
*/

/*==============================================================================================================*/
/** FUNCTION: xrc_parse_master_command
*
* DESCRIPTION: 
* Parsing the information from a 32-bit register read to respective components, based on the above bit-mapping. 
*
* INPUT PARAMETERS:
* uRead: 32-bit register read.
* pBoot_loader_status: pointer to the memory, where boot loader status needs to be populated.
* pMain_image_status: pointer to the memory, where main image status needs to be populated.
* pTz_to_master_data_contents: pointer to the memory, where TZ_TO_MASTER_DATA contents needs to be populated.
*
* RETURN VALUE: 
* SUCCESS.
*/
/*====================================================================================================================*/
status_codes xrc_parse_master_command
(
	uint32_t uRead,
	uint32_t* pBoot_loader_status, 
	uint32_t* pMain_image_status, 
	uint32_t* pTz_to_master_data_contents
)
{
    *pBoot_loader_status = uRead>>29;
    *pMain_image_status = (uRead<<3)>>29;
    *pTz_to_master_data_contents = (uRead<<8)>>24;
    XRC_LOG_ERR(3, "pBoot_loader_status:[0x%x] pMain_image_status:[0x%x] pTz_to_master_data_contents:[0x%x]",
        *pBoot_loader_status, *pMain_image_status, *pTz_to_master_data_contents);
    return SUCCESS;
}

/*====================================================================================================================*/
/** FUNCTION: xrc_parse_slave_command
*
* DESCRIPTION: 
* Rearranging the bits properly to align with the TZ_TO_SLAVE_COMMAND register contents. 
*
* INPUT PARAMETERS:
* pWrite: pointer to the memory, where 32-bit write command which needs to be aligned is there.
*
* RETURN VALUE: 
* Success.
*/
/*====================================================================================================================*/
status_codes xrc_parse_slave_command
(
	uint32_t* pWrite
)
{
    *pWrite = (*pWrite)<<24; //31:24 command_code
    return SUCCESS;
}

/*====================================================================================================================*/
/** FUNCTION: xrc_get_reset_reason
*
* DESCRIPTION: 
* Returns the reset reason of helios
*
* INPUT PARAMETERS:
* nRead: 32-bit register read
* reset_reason: Pointer to the reset reason of helios
* RETURN VALUE: 
* Success.
*/
/*====================================================================================================================*/
status_codes xrc_get_reset_reason
(
	uint32_t nRead, 
	uint32_t* reset_reason
)
{
    //TODO: Change to get Helios reset reason
    *reset_reason = (nRead<<24)>>24;
    XRC_LOG_ERR(1, "reset_reason:[0x%x]", *reset_reason);
    return SUCCESS;
}
