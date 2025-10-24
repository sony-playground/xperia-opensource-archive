#ifndef __VRM_INC_H__
#define __VRM_INC_H__

/*! \file vrm_inc.h
*
*  \brief This header file contains VRM driver related definitions used internally by PMIC PM
*  \n
*  &copy; Copyright 2016 - 2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/vrm/inc/vrm_inc.h#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/06/16   kt      Initial version
===========================================================================*/

#include "vrm.h"
#include "rpmh_client.h"
#include "cmd_db_aop.h"
#include "pm_app_vrm.h"
#include "pm_sleep.h"
#include "drv_lookup.h"
//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define VRM_MAX_NUM_VOTES            IMAGE_TCS_SIZE
#define VRM_MAX_RSRC_NAME_LEN        CMD_DB_MAX_RES_ID_LEN+1
#define VRM_RSC_DRV_MAX              RSC_DRV_GLOBAL_MAX


/**
 * @brief struct containing VRM setting and data to be voted. 
 */
typedef struct
{
   uint32 rsrc_id;
   vrm_settings setting; 
   uint32 data;
}vrm_vote_data;

/**
 * @brief struct containing VRM rsrc vote data. 
 */
typedef struct
{
   rpmh_client_handle rpmh_handle;
   vrm_rsrc_category rsrc_category;
   rpmh_set_enum set_type;
   boolean completion;
   uint32 num_votes;
   vrm_vote_data vote_data[VRM_MAX_NUM_VOTES];
}vrm_rpmh_vote_data;


/**
 * @brief VRM resource setting data to consolidate the common 
 *        setting data in one structure. Supported settings are
 *        enable, voltage, hr and mode.
 */
typedef struct
{
    uint32 addr_offset;
    uint32 current_state;
    uint32 min_state;
    uint32 fixed_time_usec;
    vrm_seq_type seq_type;
}vrm_setting_data;

/**
 * @brief pmic resource data that needs to be passed by the user
 *        when registering a resource in VRM.
 */
typedef struct
{
    char rsrc_name[VRM_MAX_RSRC_NAME_LEN];
    char rsrc_alias_name[VRM_MAX_RSRC_NAME_LEN];
    char rsrc_parent_name[VRM_MAX_RSRC_NAME_LEN];
    vrm_rsrc_category rsrc_category;
    pm_vrm_periph_info periph_info;
    uint32 base_addr;
    uint16 vrm_arb_id;
    uint16 vrm_clx_arb_id;
    uint32 drv_owner_mask;
    vrm_setting_data volt_info;
    vrm_setting_data enable_info;
    vrm_setting_data mode_info;
    boolean enable_pin_ctrl;
    boolean settling_en;
    boolean settling_err_en;
    boolean dep_en;
    boolean aop_handling;
    boolean ahc_en;
    vrm_settling_wdog_timer settling_wdog_timer;
    uint32 settling_clr_addr_offset;
    uint32 settling_clr_data;
    uint32 enable_stepper_rate_uv_us;
    uint32 enable_stepper_warm_up_time_usec;
    uint32 hr_min_state;
    uint32 volt_max_state;
    uint32 volt_fixed_down_time_usec;
    uint32 volt_stepper_rate_uv_us;
    uint32 volt_stepper_extra_up_time_usec;
    uint32 volt_stepper_extra_down_time_usec;
    uint32 volt_discharge_time_usec;
    uint32 pstm_low_val;
    uint32 pstm_high_val;
    uint32 pstm_default_val;
    uint32 pstm_pbs_ready_en;
}vrm_pmic_rsrc_data;

//******************************************************************************
// Public API Functions
//******************************************************************************
                            
/**
 * @brief Initializes the VRM driver
 *
 * This function initializes the VRM driver and does the basic 
 * VRM HW configuration. This function also does the command DB 
 * initialization for VRM entries. It is mandatory to call this 
 * function before using any other APIs of this driver. 
 * 
 * @param none
 *
 * @return  VRM_SUCCESS on success, error code on error
 */
vrm_result vrm_init(void);
                            
/**
 * @brief Pre-register the parent resource names.
 *
 * This function assigns (or reserves) a resource id for the 
 * parent resource name and saves the number of children 
 * information per parent. This is purely for memory and latency
 * optimization purposes for AOP parent-child dependency. User 
 * has to pre-register any parent resource name before 
 * registering any child resource of that parent. This function 
 * also adds the command db entry for parent resource. 
 * 
 * @param[in] rsrc_category Resource category 
 * @param[in] rsrc_name Parent resource name which needs 
 *                      pre-assigned resource id.
 * @param[in] alias_name of Parent resource which needs 
 *                      pre-assigned resource id.
 * @param[in] vreg_child_cnt Number of vreg children for the 
 *                         parent resource name being sent
 * @param[in] xob_child_cnt Number of xob children for the 
 *                         parent resource name being sent
 *
 * @return  VRM_SUCCESS on success, error code on error
 * 
 * @see vrm_register_rsrc
 */
vrm_result 
vrm_pre_register_parent_rsrc_names(vrm_rsrc_category rsrc_category, char* rsrc_name, char* alias_name,uint32 vreg_child_cnt, uint32 xob_child_cnt);
                            
/**
 * @brief Registers the resource in VRM.
 *
 * This function assigns a resource id for the resource name and 
 * configures the resource data and corresponding type data in 
 * the VRM HW. If the resource has parent resource name in the
 * pmic_rsrc_data then the dependency interrupt of the resource 
 * will be enabled in VRM HW and the dependency mapping will be 
 * maintained within VRM driver for run time parent-child 
 * dependency interrupt handling. This functions also adds a 
 * command DB entry for the registered resource. 
 * 
 * @param[in] pmic_rsrc_data PMIC resource data that needs to be
 *                           configured in VRM HW.
 *
 * @return  VRM_SUCCESS on success, error code on error
 * 
 * @see vrm_pre_register_parent_rsrc_names
 */
vrm_result vrm_register_rsrc(vrm_pmic_rsrc_data* pmic_rsrc_data);
                            
/**
 * @brief VRM post initialization for enabling VRM and 
 *        completion of command DB init. This function needs to
 *        be called at the end after registering all the
 *        resources.
 *
 * This function completes the command DB initialization and 
 * enables the VRM. This function also does error checking 
 * mainly to ensure correct parent-child dependency mapping. 
 * 
 * @param None
 *
 * @return  VRM_SUCCESS on success, error code on error
 * 
 * @see vrm_init, vrm_register_rsrc
 */
vrm_result vrm_post_init(void);
                            
/**
 * @brief Sends the vote on requested resource setting and data 
 *        through rpmh client driver after checking for minimum
 *        requirements on the resource.
 * 
 * @param[in] rsrc_vote Pointer to resource vote info like id, 
 *                      setting, data, rpmh set and completion.
 * 
 * @param[out] msg_id rpmh client driver message id after 
 *                    sending the vote.
 *
 * @return  VRM_SUCCESS on success, error code on error
 */
vrm_result vrm_send_rpmh_vote(vrm_rpmh_vote_data* rsrc_vote, uint32 *msg_id);

/**
 * @brief Returns VRM resource id for given resource category 
 *        type and vrm address offset.
 * 
 * @param[in] rsrc_category Resource category REG, XOB or XO 
 * 
 * @param[in] vrm_addr_offset VRM address offset returned from 
 *                            cmd db.
 * 
 * @param[out] rsrc_id VRM resource id corresponding to the VRM 
 *                     address offset.
 *
 * @return  VRM_SUCCESS on success, error code on error
 */
vrm_result vrm_get_rsrc_id(vrm_rsrc_category rsrc_category, uint32 vrm_addr_offset, uint32 *rsrc_id);

/**
 * @name vrm_enter_sleep
 *
 * @brief This function calls the driver layer RPMh VRM calls to
 *        configure the state prior to entering sleep.
 *
 * @param sleep_mode: can be AOSS sleep
 *
 * @return VRM error code.
 *
 * @sideeffects Will over-write any client configuration
 *              requests. Any additions to the below function
 *              should be cautiously be added.
 *
 */
vrm_result vrm_enter_sleep (pm_sleep_mode_type sleep_mode);

/**
 * @name vrm_exit_sleep
 *
 * @brief This function calls the driver layer RPMh VRM calls to
 *        configure back to the state prior to entering sleep.
 *
 * @param sleep_mode: can be AOSS sleep
 *
 * @return VRM error code.
 *
 * @sideeffects Will over-write any client configuration
 *              requests. Any additions to the below function
 *              should be cautiously be added.
 *
 */
vrm_result vrm_exit_sleep (pm_sleep_mode_type sleep_mode);

#endif
