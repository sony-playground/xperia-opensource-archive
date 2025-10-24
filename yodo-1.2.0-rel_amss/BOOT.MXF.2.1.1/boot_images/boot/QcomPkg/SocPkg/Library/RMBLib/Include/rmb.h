/****************************************************************************** 
**  
**   Qualcomm Technologies Incorporated
** 
**   Copyright (c) 2020 Qualcomm Technologies, Inc.
**   All rights reserved.
**   Qualcomm Technologies, Inc. Confidential and Proprietary.
** 
******************************************************************************/

#ifndef RMB_H
#define RMB_H

 /**===========================================================================
 **
 ** FILE 
 **     rmb.h
 ** 
 ** GENERAL DESCRIPTION 
 **     This file declares APIs, status/error enum for RMB communication  
 **     between APPS-TME subsystems.
 **
 **==========================================================================*/


/*=============================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/RMBLib/Include/rmb.h#1 $

  when       who            what, where, why
  --------   ----------     ---------------------------------------------------
  09/18/20   ds             Add alignment error code
  07/06/20   dhaval         Initial version for Waipio
=============================================================================*/


/******************************************************************************
                                MODULE INCLUDES
                         ADD NEW ONES UNDER THIS LINE
******************************************************************************/
#include "boot_comdef.h"
#include "comdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
                             PUBLIC MACROS/DEFINES
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/


/******************************************************************************
                         PUBLIC TYPES and TYPE-DEFINES
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/
typedef enum
{
  RMB_SUCCESS			  = 0x00000000, 	        /* same as PBL_NO_ERR=0*/
  RMB_CMD_DISPATCHED_BUSY, 	                /* BUSY, Queued command is dispatched for 
                                              processing */
  RMB_CMD_EXEC_COMPLETED, 	                /* Queued command execution is completed */
  RMB_QUEUE_FULL, 			                    /* Command Queue is full, release 
								                              previously used command once status is read */
  RMB_ERR_CMD_EXEC_RESULT_ALREADY_UPDATED,	/* EXEC result is already updated*/
  RMB_ERR_CMD_INVALID_EXEC_STATE,	/* result can't be set, cmd exec
                                       state is !=busy && !=updated*/
  RMB_ERR_CMD_HANDLE_NOT_FOUND,
  RMB_NO_NEW_CMD_QUEUED,
  RMB_ERR_INVALID_CLIENT_ID,
  RMB_ERR_CLIENT_NOT_INITIALIZED,
  RMB_ERR_INVALID_QUEUE_SIZE,
  RMB_ERR_TME_CLIENT_NOT_INITIALIZED,
  RMB_ERR_APPS_CLIENT_NOT_INITIALIZED,
  RMB_ERR_INVALID_APPS_TME_RMB_CLIENT_COMBO,
  RMB_CMD_RESP_HAS_NOT_BEEN_READ,
  RMB_ERR_APPS_CMD_ALREADY_RELEASED,
  RMB_ERR_HANDLE_OVERFLOW_RMB_INIT_REQD,
  RMB_ERR_NULL_POINTER,
  RMB_ERR_ALLIGNMENT_FAULT,
  RMB_FORCE32BITS    		= 0x7FFFFFFF/* To ensure it's 32 bits wide */
}rmb_status_type;

typedef enum
{
  RMB_TME_PBL_CLIENT_ID			= 0x4C425054, /* "TPBL" */
  RMB_APPS_PBL_CLIENT_ID		= 0x4C425041, /* "APBL" */
  RMB_TME_FW_CLIENT_ID			= 0x57464D54, /* "TMFW" */
  RMB_APPS_XBLSC_CLIENT_ID		= 0x43535841, /* "AXSC" */
}rmb_client_id_type;



/******************************************************************************
                            PUBLIC DATA DECLARATION
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/


/******************************************************************************
                         PUBLIC FUNCTION DECLARATIONS
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/

/*************************** Common APIs **************************/

/*===========================================================================
**  Function : rmb_init 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   TME and APPS uses this function to zero initializes TME/APPS client owned 
*   RMB HW-reg space based on client_id.
*   RMB driver operates for allowed client-id pairs between TME and APPS.
*   TME_PBL and APPS_PBL vs TME_FW and XBL_SC client IDs are supported combos.
*   For example, if APPS RMB space is initialized with APPS_PBL client ID and
*   if TME RMB space is intialized with TME_FW client ID then RMB driver will 
*   return RMB_ERR_INVALID_APPS_TME_RMB_CLIENT_COMBO for other APIs.
*   TME_FW can act like TME_PBL and process last issued command from APPS_PBL
*   however TME_FW is reuired to call rmb_init with RMB_TME_FW_CLIENT_ID
*   before retriving commands queued by XBL_SC for processing.
* 
* @param[in] client_id = rmb_client_id_type. 
*                 TME client IDs: RMB_TME_PBL_CLIENT_ID, RMB_TME_FW_CLIENT_ID
*                 APPS client IDs: RMB_APPS_PBL_CLIENT_ID, RMB_APPS_XBLSC_CLIENT_ID
*             log_buff_addr = NULL (not used in this version of driver). 
*             log_buff_size = NULL (not used in this version of driver).
*
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS 
* 
* @par Side Effects
*   Zero initializes respective RMB space as per client ID.
*/
uint32 rmb_init(uint32 client_id, uint32 log_buff_addr, uint32 log_buff_size);

/*===========================================================================
**  Function : rmb_get_cmd_queue_size 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   TME and APPS uses this function to retrieve command queue size for it's
*   RMB space. RMB driver retrives command_queue_size bsaed on input client_id
*   passed to locate APPS vs TME RMB command queue size.
* 
* @param[in] client_id = rmb_client_id_type. 
*                 TME client IDs: RMB_TME_PBL_CLIENT_ID, RMB_TME_FW_CLIENT_ID
*                 APPS client IDs: RMB_APPS_PBL_CLIENT_ID, RMB_APPS_XBLSC_CLIENT_ID
* @param[out] cmd_queue_size = command queue size for input client_id RMB space
*
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS 
* 
* @par Side Effects
*   None
*/
uint32 rmb_get_cmd_queue_size(uint32 client_id, uint32* cmd_queue_size);



/*************************** APIs to be used by TME **************************/

/*===========================================================================
**  Function : rmb_get_next_cmd 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   TME uses this function to retrieve next command in the queue to be 
*   processed. Output arguments format etc is as per agreement between APPS
*   and TME SW. RMB driver just allows this information to be passed across.
*   APPS SW will queue commands and TME SW processes commands from the queue.
* 
* @param[out] cmd_id = COMMAMD_ID as per agreement between APPS (command 
*             queuer) and TME (command processor). For example for auth, hash
*             etc services provided by TME, there would be unique command_id
*             assigned for each command.
*             cmd_args_addr = Address where all input arguments are stored.
*             Input args format is as per agreement between APPS and TME SW.
*             cmd_args_size = size of input stored at cmd_args_addr, again
*             as per agreement between APPS and TME SW.
*             cmd_handle = unique cmd_handle for each command to be processed
*
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_NO_NEW_CMD_QUEUED or 
*   RMB_QUEUE_FULL
* 
* @par Side Effects
*   None
*/
uint32 rmb_get_next_cmd(uint32* cmd_id, uint32* cmd_args_addr,
                             uint32* cmd_args_size, uint32* cmd_handle);

/*===========================================================================
**  Function : rmb_set_cmd_exec_result 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   TME uses this API to populate return result from command_handler for 
*   specific command. For example, for RMB_CMD_AUTH_HASH_TABLE it would be 
*   return value of secureboot driver API handling authentication command.
* 
* @param[in] cmd_handle = input to locate specific command in the queue
* @param[in] cmd_exec_result = command execution result 
*     
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_ERR_CMD_HANDLE_NOT_FOUND or 
*   RMB_ERR_CMD_EXEC_RESULT_ALREADY_UPDATED or RMB_ERR_CMD_INVALID_EXEC_STATE
* 
* @par Side Effects
*   None
*/
uint32 rmb_set_cmd_exec_result(uint32 cmd_handle, uint32 cmd_exec_result);

/*===========================================================================
**  Function : rmb_has_result_been_read 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   TME uses this function to know whether APPS has read result for command
*   with cmd_handle so it can use that command slot for round-robin command
*   processing queue.
* 
* @param[in] cmd_handle = input to locate specific command in the queue
*
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS if command result has been read by APPS client 
*   otherwise RMB_CMD_RESP_HAS_NOT_BEEN_READ or RMB_ERR_CMD_HANDLE_NOT_FOUND.
* 
* @par Side Effects
*   None
*/
uint32 rmb_has_result_been_read(uint32 cmd_handle);


/*************************** APIs to be used by APPS *************************/
/*===========================================================================
**  Function : rmb_queue_next_cmd 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   APPS_PBL & XBL_SC uses this function to queue next command to be 
*   processed. Input arguments format etc is as per agreement between APPS
*   and TME SW. RMB driver just allows this information to be passed across.
*   TME SW will process commands queued by APPS SW.
* 
* @param[in] cmd_id = COMMAMD_ID as per agreement between APPS (command 
*            queuer) and TME (command processor). For example for auth, hash
*            etc services provided by TME, there would be unique command_id
*            assigned for each command.
*            cmd_args_addr = Address where all input arguments are stored.
*            Input args format is as per agreement between APPS and TME SW.
*            cmd_args_size = size of input stored at cmd_args_addr, again
*            as per agreement between APPS and TME SW.
* @param[out] cmd_handle = unique cmd_handle for each queued command
*
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_CMD_QUEUE_FULL or 
*   RMB_ERR_HANDLE_OVERFLOW_RMB_INIT_REQD
* 
* @par Side Effects
*   None
*/
uint32 rmb_queue_next_cmd(uint32 cmd_id, uint32 cmd_args_addr,
                             uint32 cmd_args_size, uint32* cmd_handle);

/*===========================================================================
**  Function : rmb_get_cmd_status 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   APPS_PBL and XBL_SC uses this function to get execution status of command
*   for a given command_handle.
* 
* @param[in] cmd_handle = input to locate specific command in the queue
* @param[out] cmd_status = RMB_CMD_EXEC_COMPLETED or RMB_CMD_DISPATCHED_BUSY
*     
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_ERR_CMD_HANDLE_NOT_FOUND or 
*          RMB_CMD_DISPATCHED_BUSY
* 
* @par Side Effects
*   None
*/
uint32 rmb_get_cmd_status(uint32 cmd_handle, uint32* cmd_status);

/*===========================================================================
**  Function : rmb_get_cmd_exec_result 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   APPS_PBL and XBL_SC uses this API to retrieve return result from TME's 
*   command_handler return result for a specific command. For example, for 
*   RMB_CMD_AUTH_HASH_TABLE it would be return value of secureboot driver  
*   API handling authentication command.
* 
* @param[in] cmd_handle = input to locate specific command in the queue
* @param[out] cmd_exec_result = command execution result
*     
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_ERR_CMD_HANDLE_NOT_FOUND
*   or RMB_ERR_CMD_INVALID_EXEC_STATE
* 
* @par Side Effects
*   None
*/
uint32 rmb_get_cmd_exec_result(uint32 cmd_handle, uint32* cmd_exec_result);

/*===========================================================================
**  Function : rmb_release_cmd 
** ==========================================================================
*/
/*!
* 
* @brief
*
*   APPS_PBL and XBL_SC uses this function to inform TME that it has read result
*   and command handle is released for future use in this round-robin queue.
* 
* @param[in] cmd_handle = input to locate specific command in the queue
*     
* @par Dependencies
*   None
*   
* @retval
*   return RMB_CMD_SUCCESS or RMB_ERR_CMD_HANDLE_NOT_FOUND
*   or RMB_ERR_APPS_CMD_ALREADY_RELEASED
* 
* @par Side Effects
*   None
*/
uint32 rmb_release_cmd(uint32 cmd_handle);

#ifdef __cplusplus
}
#endif

#endif /* RMB_H */
/*=============================================================================
                                  END OF FILE
=============================================================================*/
