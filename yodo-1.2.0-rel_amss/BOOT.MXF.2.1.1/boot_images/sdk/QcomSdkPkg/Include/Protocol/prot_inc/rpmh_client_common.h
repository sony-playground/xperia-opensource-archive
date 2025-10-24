#ifndef RPMH_CLIENT_COMMON_H
#define RPMH_CLIENT_COMMON_H

/*===========================================================================
                             rpmh_client_common.h

DESCRIPTION:
  RPMh Command Services APIs

  This is the main interface for issuing commands to RPMh. It will be used by
  resource owners who need to issue commands to RPMh HW. It interacts with 
  RSC hardware underneath to facilitate RPMh commands to the proper RPMh HW 
  block. The driver stores each command locally and synchronizes the desired 
  state with the state at RPMh.

  Commands can be issued either as fire-and-forget or as completion. In order
  to confirm a command has been applied at the HW, commands must be issued as
  completion, AND an rpmh_barrier API must be called (which blocks until the
  command(s) have finished).

  This interface also provides sleep interaction to prepare for entering and 
  exiting sleep. This is necessary to configure the RSC TSC contents as desired
  by clients.

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//==========================================================================
//                   Includes and Public Data Declarations
//==========================================================================

//--------------------------------------------------------------------------
// Include Files 
//--------------------------------------------------------------------------
#include <rpmh_common.h>
#include <rpmh_image_config.h>

//--------------------------------------------------------------------------
// Constant /Define Declarations 
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Type Declarations 
//--------------------------------------------------------------------------

/*************************************//**
 * RPMh Command Structures
 *
 * These structures are used along with the RPMh APIs to issue commands to RPMh blocks.
 ****************************************/

/* 
 * Client callback for completion 
 */
typedef void ( *rpmh_completion_cb )( UINT32 req_id );

/**
 * Individual command
 */
typedef struct
{
  UINT32 address;     // address for the given resource command. Concatenation of {slaveID, offset}
  UINT32 data;        // data to be sent 
  BOOLEAN completion; // TRUE for a completion request, FALSE for a fire and forget request
} rpmh_command_t;

/**
 * Command set structure used to send multiple commands in parallel
 */
typedef struct
{
  rpmh_set_enum set;                 // The set associated with these commands
  UINT32 num_commands;               // The number of commands being sent
  UINT32 reserved;                   // reserved
  rpmh_command_t commands[IMAGE_TCS_SIZE]; // An array of commands to be sent
} rpmh_command_set_t;

/** 
 * opaque client handle (one per client) used to 
 *      differentiate between RSCs
 *      help parallelize between clients
 */
typedef struct rpmh_client_t *rpmh_client_handle;

#ifdef __cplusplus
}
#endif //__cplusplus


#endif /* RPMH_CLIENT_COMMON_H */

