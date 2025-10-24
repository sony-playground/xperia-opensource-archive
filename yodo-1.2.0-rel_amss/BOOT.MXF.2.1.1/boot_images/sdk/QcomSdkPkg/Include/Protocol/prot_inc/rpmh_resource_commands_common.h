#ifndef RPMH_RESOURCE_COMMANDS_COMMON_H
#define RPMH_RESOURCE_COMMANDS_COMMON_H

/*===========================================================================
                             rpmh_resource_commands_common.h

DESCRIPTION:
  Interface and type definitions for resource command state tracking, voting,
  and general handling.

  A resource command is treated as unique RPMh address on which a client has 
  issued a command. This layer only understands the address and corresponding 
  command details (it does not understand what the address corresponds to in 
  human readable form).

Copyright (c) 2016-2017 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "rpmh_common.h"
#include "npa_common.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------

/* 
 * resource command progress states 
 */
typedef enum
{
  RPMH_RC_STATE_IDLE = 0,
  RPMH_RC_STATE_IN_PROGRESS,
  RPMH_RC_STATE_MAX
} rpmh_rc_state_enum;

/* 
 * resource command dirtiness states 
 */
typedef enum
{
  RPMH_RC_CLEAN = 0,
  RPMH_RC_CLEAN_EXPLICIT_VOTE = 1,    //special case for explicit clients. 
  RPMH_RC_LAST_CLEAN = 1,             //special case for explicit clients. 
  RPMH_RC_DIRTY = 2,
  RPMH_RC_DIRTY_MOL = 3,              //special case for PDC sleep. Vote < MOL so use MOL instead (in RC) 
  RPMH_RC_DIRTY_USE_ACTIVE = 4,       //special case for wake. No wake vote but 
                                      //active and sleep votes that are different.    
  RPMH_RC_DIRTY_MAX
} rpmh_rc_dirty_enum;

/* 
 * resource command vote details 
 */
typedef struct
{
  UINT32             data;  //vote value
  BOOLEAN            valid; //whether or not the vote is valid
  rpmh_rc_dirty_enum dirty; //whether or not the vote is dirty (needs sending)
} rpmh_vote_t;

/* 
 * resource command priorities 
 */
typedef enum
{
  RPMH_RC_PRIORITY_USE_CASE = 0, //resource command needed for use case needs
  RPMH_RC_PRIORITY_SUBSYSTEM,    //resource command needed for subsystem SW to run
  RPMH_RC_PRIORITY_MAX
} rpmh_rc_priority_enum;

/* 
 * voter on a resource command details 
 */
typedef struct drv_votes
{
  RSCSW_DRV_MAPPING  drv_id;                     //RSC+DRV mapping for the voter	
  rpmh_rc_state_enum state;                      //state of the resource for the drv
  rpmh_rc_priority_enum priority;                //priority for this rc+drv
  rpmh_vote_t        vote_at_rpmh;               //vote details at rpmh
  rpmh_vote_t        local_votes[RPMH_NUM_SETS]; //local votes in the rpmh driver SW
  struct drv_votes   *next;                      //pointer to the next voter
} drv_votes_t;

typedef struct 
{
  UINT32            *votes;
  UINT32            size;
  npa_client_handle sleep_voter;
  char              *voter_name;
} pdc_votes_t;

/* 
 * resource command 
 */
typedef struct
{
  UINT32                address;    //concatenation of {slaveid, offset}
  drv_votes_t           *drv_votes; //list of voters on this rc
  pdc_votes_t           *pdc_votes; //list of vote values for the PDC
} rpmh_resource_command_t;

#endif /* RPMH_RESOURCE_COMMANDS_COMMON_H */

