#ifndef RPMH_RESOURCE_COMMANDS_H
#define RPMH_RESOURCE_COMMANDS_H

/*===========================================================================
                             rpmh_resource_commands.h

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
#include "comdef.h"
#include "rpmh_resource_commands_common.h"

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//===========================================================================
//                             Function Definitions
//===========================================================================

/**
 * <!-- rpmh_resource_command_init -->
 *
 * @brief Initialize a resource command
 *
 * @param self    : The resource command pointer to initialize
 * @param address : The address to associate with the resource command
 */
void rpmh_resource_command_init (rpmh_resource_command_t *self, uint32 address);

/**
 * <!-- rpmh_resource_command_update -->
 *
 * @brief Updated the data for a given command 
 *
 * @param self         : The resource command pointer
 * @param set          : The set associated with the data
 * @param data         : The new data
 * @param drv_id       : The RSCSW_DRV_MAPPING associated with the voter
 * @param explicit_cmd : If this is a command from an explicit client. If so, we ignore sleep/wake details
 *
 * @return TRUE if the given resource and set (for the given drv_id) is dirty after the update
 */
boolean rpmh_resource_command_update (rpmh_resource_command_t *rc, rpmh_set_enum set, uint32 data, 
                                      RSCSW_DRV_MAPPING drv_id, boolean explicit_cmd);


/**
 * <!-- rpmh_resource_command_val_at_rpmh -->
 *
 * @brief Sets the "val_at_rpmh" for the given rc. Updates the resource state to in progress 
 * for an AMC. This is called when a new vote has been sent to the HW. 
 *
 * @param self   : The resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 * @param set    : The set associated with the command 
 * @param amc    : whether or not the command is an AMC
 *
 * @return The data corresponding to val_at_rpmh
 */
uint32 rpmh_resource_command_val_at_rpmh (uint32 address, RSCSW_DRV_MAPPING drv_id, rpmh_set_enum set, 
                                          boolean amc);

/**
 * <!-- rpmh_resource_command_finish -->
 *
 * @brief A command has finished, clean up at the resource level 
 *
 * @param address : The address associated with the resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 */
void rpmh_resource_command_finish (uint32 address, RSCSW_DRV_MAPPING drv_id);

/**
 * <!-- rpmh_resource_command_get_voter -->
 *
 * @brief Retireve a voter for the resource command
 *
 * @param self   : The resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 */
drv_votes_t *rpmh_resource_command_get_voter (rpmh_resource_command_t *rc, 
                                              RSCSW_DRV_MAPPING drv_id);

/**
 * <!-- rpmh_resource_command_get_priority -->
 *
 * @brief Retrieve this voters priority for the given resource command
 *
 * @param self   : The resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 *
 * @return The priority value associated with this rc+drv
 */
rpmh_rc_priority_enum rpmh_resource_command_get_priority(rpmh_resource_command_t *self, RSCSW_DRV_MAPPING drv_id);


/**
 * <!-- rpmh_resource_command_exit_sleep -->
 *
 * @brief Exit sleep processing for the given rc/drv: 
 *             -set active vote as wake value
 *             -clear out wake value
 *             -update val at rpmh 
 *
 * @param self   : The resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 */
void rpmh_resource_command_exit_sleep (rpmh_resource_command_t *rc, RSCSW_DRV_MAPPING drv_id);

/**
 * <!-- rpmh_resource_command_sets_dirty -->
 *
 * @brief Check which sets are dirty for the given resource command and voter
 *
 * @param self   : The resource command pointer
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 *
 * @return A bitmask of which sets are dirty
 */
uint32 resource_command_sets_dirty (rpmh_resource_command_t *rc, RSCSW_DRV_MAPPING drv_id);

/**
 * <!-- rpmh_resource_command_invalidate -->
 *
 * @brief Invlidate the vote for a given set. 
 *
 * NOTE: ACTIVE IS NOT ALLOWED. There is no "invalidate" at the HW level, so if a request has 
 *       been sent to RPMh it will persist. Thus we can only invalidate sleep/wake.
 *
 * @param self   : The resource command pointer
 * @param set    : The set on which to invalidate
 * @param drv_id : The RSCSW_DRV_MAPPING associated with the voter
 */
void rpmh_resource_command_invalidate (rpmh_resource_command_t *rc, rpmh_set_enum set, RSCSW_DRV_MAPPING drv_id);

#ifdef RPMH_OFFTARGET_TEST

/**
 * <!-- print_resource_commands -->
 *
 * @brief Prints current resource command list and associated details
 *
 * @param self     : list of resource commands
 * @param num_cmds : # of resource commands in the list
 */
void print_resource_commands (rpmh_resource_command_t *self, uint32 num_cmds);

/**
 * <!-- print_resource_votes -->
 *
 * @brief Prints current votes from all DRVs on the given resource command 
 *
 * @param self     : list of resource commands
 */
void print_resource_votes (rpmh_resource_command_t *self);
#endif //RPMH_OFFTARGET_TEST

#endif /* RPMH_RESOURCE_COMMANDS_H */

