/** 
  @file  EFIRpmh.h
  @brief RPMH API.
*/
/*=============================================================================
  Copyright (c) 2015 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
07/23/15   rli     Initial revision.

=============================================================================*/
#ifndef __EFIRPMH_H__
#define __EFIRPMH_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include <rpmh_client_common.h>
#include <rpmh_resource_commands_common.h>

/** @defgroup EFI_RPMH_PROTOCOL  EFI_RPMH_PROTOCOL 
 *  @ingroup POWER 
 */
 /** @defgroup  EFI_RPMH_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_RPMH_PROTOCOL 
 */ 
 /** @defgroup  EFI_RPMH_PROTOCOL_apis APIs
 *  @ingroup EFI_RPMH_PROTOCOL 
 */ 

/** @defgroup  EFI_RPMH_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_RPMH_PROTOCOL 
 */

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @addtogroup EFI_RPMH_PROTOCOL_data 
@{ */
/**
  Protocol version.
*/
#define EFI_RPMH_PROTOCOL_REVISION 0x0000000000010001
/** @} */ /* end_addtogroup efi_rpmh_constants */

/*  Protocol GUID definition */
/** @ingroup EFI_RPMH_PROTOCOL_data */
#define EFI_RPMH_PROTOCOL_GUID \
  { 0xe1d0b573, 0xf29f, 0x495d, { 0x93, 0x52, 0xca, 0x0d, 0xd4, 0x2a, 0x0a, 0x74 } }

  


/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the RPMH API Protocol GUID.
 */
extern EFI_GUID gEfiRpmhProtocolGuid;
/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/* EFI_RPMH_INIT */
/** @ingroup EFI_RPMH_PROTOCOL_apis 
  @par Summary
  Initializes the RPMH subsystem.
  to this function.

  @return
  EFI_SUCCESS -- Function completed successfully.
 */
typedef EFI_STATUS (EFIAPI* EFI_RPMH_INIT)(void);


/* EFI_RPMH_POST_REQUEST */
/** @ingroup EFI_RPMH_PROTOCOL_apis 
  @par Summary
  RPM Request Service API
  Post a request to the *local* request state.  This will eventually synchronize with the RPM copy.
  @param[in]  set        The RPM "set" which receives this request, affecting what scenarios it applies to.
  @param[in]  resource   The class of resource being requested (different resource classes accept different data).
  @param[in]  id         The particular resource being addressed (i.e., if 'resource' tells us we're talking to a clock, this identifies *which* clock).
  @param[in]  kvps       The data being sent in this request; the data is overlaid on previous kvps, so incremental updates are acceptable.
  @param[out] pMsg_id    Pointer to unique identifier by which this request can be identified later.

  @return
  EFI_SUCCESS -- Function completed successfully. \n
 */
typedef EFI_STATUS (EFIAPI* EFI_RPMH_IS_DRV_ID_VALID)(
  RSCSW_DRV_MAPPING drv_id,
  BOOLEAN *drv_id_valid
 );

/* EFI_RPMH_CHURN_QUEUE */
/** @ingroup EFI_RPMH_PROTOCOL_apis 
  @par Summary
  Polls the RPM message queue until ACK for specified message received.
  @param[in]  message_id

  @return
  EFI_SUCCESS -- Function completed successfully. \n
 */
typedef EFI_STATUS (EFIAPI* EFI_RPMH_TCS_NUM_CMDS)(
  RSCSW_DRV_MAPPING drv_id,
  UINT32 *drv_id_size
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CREATE_HANDLE_INTERNAL)(
  RSCSW_DRV_MAPPING drv_id,
  const char *client_name,
  BOOLEAN explicit_client,
  rpmh_client_handle *client_handle
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CREATE_HANDLE_EXPLICIT)(
  RSCSW_DRV_MAPPING drv_id,
  const char *client_name,
  rpmh_client_handle *client_handle
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CREATE_HANDLE)(
  RSCSW_DRV_MAPPING drv_id,
  const char *client_name,
  rpmh_client_handle *client_handle
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_INVALIDATE_EXPLICIT_CMDS)(
  rpmh_client_handle client_handle
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CLIENT_REGISTER_COMPLETION_CALLBACK)(
  rpmh_client_handle client_handle,
  rpmh_completion_cb callback
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_DELETE_HANDLE)(
 rpmh_client_handle client_handle
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_FIND_RESOURCE_COMMAND)(
  UINT32 address,
  rpmh_resource_command_t **resource_command
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CHURN_ALL)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_CHURN_SINGLE)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_BARRIER_ALL)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_BARRIER_SINGLE)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_WAIT_FOR_READ)(
  struct rpmh_client_t *handle,
  UINT32 req_id,
  BOOLEAN polling,
  UINT32 *data
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_FINISH_AMC)(
  RSCSW_DRV_MAPPING drv_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_FINISH_SLEEP_WAKE_AMC)(
  RSCSW_DRV_MAPPING drv_id,
  rpmh_set_enum set
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_ISSUE_COMMAND_SET)(
  rpmh_client_handle client_handle,
  rpmh_command_set_t *cmd_set,
  UINT32 *req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_INVALIDATE_SLEEP_COMMAND)(
  rpmh_client_handle client_handle,
  UINT32 address
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_INVALIDATE_WAKE_COMMAND)(
  rpmh_client_handle client_handle,
  UINT32 address
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_ISSUE_READ_COMMAND)(
  rpmh_client_handle client_handle,
  UINT32 address,
  BOOLEAN polling,
  UINT32 *data
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_ISSUE_COMMAND)(
  rpmh_client_handle client_handle,
  rpmh_set_enum set,
  BOOLEAN completion,
  UINT32 address,
  UINT32 data,
  UINT32 *req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_ENTER_SLEEP)(
  RSCSW_DRV_MAPPING drv_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_EXIT_SLEEP)(
  RSCSW_DRV_MAPPING drv_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_BARRIER_ALL)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/** @ingroup EFI_RPMH_PROTOCOL_apis 
**/
typedef EFI_STATUS (EFIAPI* EFI_RPMH_BARRIER_SINGLE)(
  rpmh_client_handle client_handle,
  UINT32 req_id
);

/* EFI_RPMH_DEINIT */
/** @ingroup EFI_RPMH_PROTOCOL_apis
  @par Summary
  RPMH destructor.

  @return
  EFI_SUCCESS -- Function completed successfully. \n
  Other values -- Failure.
 */
typedef EFI_STATUS (EFIAPI* EFI_RPMH_DEINIT)(void);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_RPMH_PROTOCOL_prot
  @par Summary
  Rpm Api Protocol interface.

  @par Parameters
*/
typedef struct _EFI_RPMH_PROTOCOL {
  UINT64                           Revision;
  EFI_RPMH_INIT                    RpmhInit;
  EFI_RPMH_IS_DRV_ID_VALID             rpmh_is_drv_id_valid;
  EFI_RPMH_TCS_NUM_CMDS                rpmh_tcs_num_cmds;
  EFI_RPMH_CREATE_HANDLE_INTERNAL      rpmh_create_handle_internal;
  EFI_RPMH_CREATE_HANDLE_EXPLICIT      rpmh_create_handle_explicit;
  EFI_RPMH_CREATE_HANDLE               rpmh_create_handle;
  EFI_RPMH_INVALIDATE_EXPLICIT_CMDS    rpmh_invalidate_explicit_cmds;
  EFI_RPMH_CLIENT_REGISTER_COMPLETION_CALLBACK        rpmh_client_register_completion_callback;
  EFI_RPMH_DELETE_HANDLE               rpmh_delete_handle;
  EFI_RPMH_FIND_RESOURCE_COMMAND       rpmh_find_resource_command;
  EFI_RPMH_CHURN_ALL                   rpmh_churn_all;
  EFI_RPMH_CHURN_SINGLE                rpmh_churn_single;
  EFI_RPMH_FINISH_AMC                  rpmh_finish_amc;
  EFI_RPMH_FINISH_SLEEP_WAKE_AMC       rpmh_finish_sleep_wake_amc;
  EFI_RPMH_ISSUE_COMMAND_SET           rpmh_issue_command_set;
  EFI_RPMH_INVALIDATE_SLEEP_COMMAND    rpmh_invalidate_sleep_command;
  EFI_RPMH_INVALIDATE_WAKE_COMMAND     rpmh_invalidate_wake_command;
  EFI_RPMH_ISSUE_READ_COMMAND          rpmh_issue_read_command;
  EFI_RPMH_ISSUE_COMMAND               rpmh_issue_command;
  EFI_RPMH_ENTER_SLEEP                 rpmh_enter_sleep;
  EFI_RPMH_EXIT_SLEEP                  rpmh_exit_sleep;
  EFI_RPMH_DEINIT                      RpmhDeInit;
  EFI_RPMH_BARRIER_ALL                 rpmh_barrier_all;
  EFI_RPMH_BARRIER_SINGLE              rpmh_barrier_single;
  
 }EFI_RPMH_PROTOCOL;

#endif /* __EFIRPMH_H__ */
