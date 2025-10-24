#ifndef __VRM_H__
#define __VRM_H__

/*! \file vrm.h
*
*  \brief This header file contains VRM driver related definitions.
*  \n
*  &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/inc/vrm/vrm.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/06/16   kt      Initial version
===========================================================================*/

#include "comdef.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define VRM_LSHIFT(pos) (0x1 << pos)

/**
 * @brief VRM API error return type
 */
typedef enum 
{
    VRM_SUCCESS               = 0,
    VRM_FAILURE               = VRM_LSHIFT(0),
    VRM_NOT_INITIALIZED       = VRM_LSHIFT(1),
    VRM_NULL_PTR_ERROR        = VRM_LSHIFT(2),
    VRM_INVALID_PARAM         = VRM_LSHIFT(3),
    VRM_OUT_OF_BOUND_ERROR    = VRM_LSHIFT(4),
    VRM_DEP_MAP_ERROR         = VRM_LSHIFT(5),
    VRM_SEQ_NOT_SUPPORTED     = VRM_LSHIFT(6),
    VRM_CMD_DB_ERROR          = VRM_LSHIFT(7),
    VRM_SETTLING_ERROR        = VRM_LSHIFT(8),
    VRM_RINIT_ERROR           = VRM_LSHIFT(9),
    VRM_RESULT_INVALID        = VRM_LSHIFT(30),
}vrm_result;


/**
 * @brief VRM resource categories.
 */
typedef enum 
{
    VRM_RSRC_REGULATOR,
    VRM_RSRC_XO_BUFFER,
    VRM_RSRC_LOCAL,
    VRM_RSRC_PSTM,
    VRM_RSRC_INVALID_CATEGORY,
}vrm_rsrc_category;

/**
 * @brief Supported VRM settings.
 */
typedef enum 
{
   VRM_ENABLE,
   VRM_VOLTAGE,
   VRM_MODE,
   VRM_NUM_SETTINGS,
}vrm_settings;

/**
 * @brief VRM sequence types supported. Client can use this enum
 *        to send the required sequence for VRM HW to follow per
 *        PMIC resource and per setting (enable, voltage, hr and
 *        mode).
 *  
 * VRM_GENERIC_SEQ: Generic sequence used for all regulators and 
 * XO buffers which writes proper aggregated votes to PMIC and 
 * different types of settling along with work-arounds 
 *  
 * VRM_NO_PMIC_SEQ: Just does settling and no PMIC/SPMI 
 * interaction. This is used for LVS voltage, mode and so on. 
 *  
 * VRM_PMIC_WRITE_SEQ: Writes the aggregated vote to PMIC and 
 * does fixed settling. This is used for cases like PBS force 
 * trigger and so on 
 *  
 * VRM_SPMI_BYTE_WRITE_SEQ: Does one customized SPMI single byte
 * write followed by fixed settling time
 *  
 */
typedef enum 
{
    VRM_GENERIC_SEQ,
    VRM_NO_PMIC_SEQ,
    VRM_PMIC_WRITE_SEQ,
    VRM_SPMI_BYTE_WRITE_SEQ,
    VRM_MAX_SEQ,
}vrm_seq_type;

/**
 * @brief VRM watchdog settling time multiplier for maximum 
 *        settling time given by VRM before triggering an error
 *        interrupt
 */
typedef enum
{
   VRM_1X_SETTLING_TIMER  = 0,
   VRM_2X_SETTLING_TIMER  = 1,
   VRM_4X_SETTLING_TIMER  = 2,
   VRM_8X_SETTLING_TIMER  = 3,
   VRM_16X_SETTLING_TIMER = 4,
   VRM_INVALID_SETTLING_TIMER,
}vrm_settling_wdog_timer;

/**
 * @brief PMIC VRM API used peripheral types 
 *       (might make more sense to make this part of VRM API headers. Revisit this)
 */
typedef enum 
{
    PM_VRM_PERIPH_NONE,
    PM_VRM_PERIPH_SMPS,
    PM_VRM_PERIPH_LDO,
    PM_VRM_PERIPH_BOB,
    PM_VRM_PERIPH_VS,
    PM_VRM_PERIPH_CLK,
    PM_VRM_PERIPH_PBS_CLIENT,
    PM_VRM_PERIPH_GPIO,
    PM_VRM_PERIPH_SOC,  // dummy periph just for VRM SOC resource
    PM_VRM_PERIPH_SPMI, // dummy periph just for work-around
    PM_VRM_PERIPH_VREF, 
    PM_VRM_PERIPH_XO,
    PM_VRM_PERIPH_VREG,
    PM_VRM_PERIPH_PSTM,
    PM_VRM_PERIPH_INVALID,
}pm_vrm_periph_type;


//******************************************************************************
// Public API Functions
//******************************************************************************
                            
/**
 * @brief Updates ARC DRV mode vote in VRM votetable for the 
 *        given resource.
 * 
 * @param[in] rsrc_name: VRM resource name (used in CmdDB) 
 * 
 * @param[in] mode: Mode value to be updated 
 *
 * @return  VRM_SUCCESS on success, error code on error
 */
vrm_result vrm_arc_drv_mode_update(const char* rsrc_name, uint32 mode);

#endif
