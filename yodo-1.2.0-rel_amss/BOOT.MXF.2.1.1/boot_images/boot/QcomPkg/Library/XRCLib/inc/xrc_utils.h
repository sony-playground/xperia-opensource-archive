/*=============================================================================

                            XRC UTILS

 Methods that parse the register bits.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#ifndef XRC_UTILS_H
#define XRC_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/

#include "xrc_types.h"
#include "xrc_comm.h"
#include "xrc_os.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/

#define BREAKIFFAIL(eRetVal) \
    if (SUCCESS != eRetVal)  \
    {                        \
	break;               \
    }

#define BREAKIFNULL(ptr, eRetVal) \
    if (ptr == NULL)              \
    {                             \
	eRetVal = FAIL_MEM_ALLOC; \
	break;                    \
    }

#define EXITIFFAIL(eRetVal) \
    if (SUCCESS != eRetVal) \
    {                       \
	goto exit;          \
    }

#define EXITIFNULL(ptr, eRetVal)  \
    if (ptr == NULL)              \
    {                             \
	eRetVal = FAIL_MEM_ALLOC; \
	goto exit;                \
    }

#define FREEIF(ptr)         \
    {                       \
	if (ptr != NULL)    \
	{                   \
	    xrc_os_free(ptr); \
	    ptr = NULL;     \
	}                   \
    \
}
/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

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
	uint32_t, 
	uint32_t *, 
	uint32_t *, 
	uint32_t *
);

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
	uint32_t *
);

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
	uint32_t, 
	uint32_t *
);

#ifdef __cplusplus
}
#endif

#endif
