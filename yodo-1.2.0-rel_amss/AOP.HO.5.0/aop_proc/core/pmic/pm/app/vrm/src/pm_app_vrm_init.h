#ifndef __PM_APP_VRM_INIT_H__
#define __PM_APP_VRM_INIT_H__

/*! \file pm_app_vrm_init.h
 *  \n
 *  \brief This file contains PMIC VRM APP level initialization.   
 *  \n  
 *  \n &copy; Copyright 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/app/vrm/src/pm_app_vrm_init.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/24/17   kt      Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_utils.h"
#include "pm_app_vrm.h"
#include "pm_smps_driver.h"
#include "pm_ldo_driver.h"
#include "pm_bob_driver.h"
#include "pm_pstm_driver.h"
/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/
/* Array sizes */
#define PM_VREG_NUM_STATUS_REGS 2
#define PM_VREG_NUM_CFG_REGS    8
#define PM_VREG_NUM_INT_REGS    8
#define PM_VREG_SETTLE_ARR_SIZE 3
#define PM_VREG_OCP_ARR_SIZE    1
#define PM_VREG_INT_RT_OFFS     0x10

typedef struct
{
    uint64 time_stamp;
    uint32 pmic_index;
    pm_vrm_periph_type periph_type;
    uint32 periph_id;
} pm_vreg_ocp_status;

/* Rsrc status register dump info */
typedef struct
{
    uint64 time_stamp;
    uint8 slave_id;
    uint16 base_address;
    uint8 status1_base_reg_dump[PM_VREG_NUM_STATUS_REGS];
    uint8 vset_lb_base_reg_dump[PM_VREG_NUM_CFG_REGS];
    uint8 int_base_reg_dump[PM_VREG_NUM_INT_REGS];
}pm_vreg_register_status;

/* Settling errors log info */
typedef struct
{
    uint64 settle_start_time;
    uint64 settle_end_time;
    pm_vreg_register_status status;
    uint8 pshold_status;
}pm_vreg_settle_status;

/* Settling errors log info */
typedef struct
{
    uint64 time_stamp;
    uint8 slave_id;
    uint16 base_address;
    uint16 enable_status;
    uint16 clk_status;
    uint8 pshold_status;
}pm_clk_settle_status;


/* Settling errors log info */
typedef struct
{
    boolean initialized;
    rex_crit_sect_type lock;
    uint32 lock_count;
    uint32 vreg_settle_arr_index;
    pm_vreg_settle_status vreg_settle_arr[PM_VREG_SETTLE_ARR_SIZE];
    uint32 vreg_ocp_arr_index;
    pm_vreg_ocp_status vreg_ocp_arr[PM_VREG_OCP_ARR_SIZE]; 
    uint32 vreg_ocp_count;
    uint32 force_soft_start_count;
    pm_clk_settle_status clk_settle_status_info;
}pm_app_vrm_info_type;

/* Settling errors log info */
typedef struct
{
    pm_pwr_data_type *pwr_data;
    pm_comm_info_type *comm_ptr;
    char* rsrc_prop_id;
    char* dep_prop_id;
    char* rail_prop_id;
}pm_app_vrm_pwr_info;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
pm_err_flag_type pm_app_vrm_init(void);

pm_err_flag_type 
pm_app_vrm_vreg_get_pwr_info(uint32 pmic_index, pm_vrm_periph_type periph_type, pm_app_vrm_pwr_info *pwr_info);


#endif /* __PM_APP_VRM_INIT_H__ */
