#ifndef __PM_PON_HLOS_H__
#define __PM_PON_HLOS_H__
/*! \file pm_pon_hlos.h
 *  \n
 *  \brief This file contains functions and variable declarations to support 
 *   the pon hlos driver module.
 *
 *  \n &copy; Copyright (c) 2012-2020 by Qualcomm Technologies Inc.  All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
20/10/29   cg      creation of pon hlos driver apis
===========================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/*! \enum pm_pon_irq_type
   \brief different types of irq bit fields of pon irq module
 */
typedef enum {
  PM_PON_HLOS_IRQ_KPDPWR_N_S1        , /* S1 PowerKey */
  PM_PON_HLOS_IRQ_RESIN_N_S1         , /* S1 Resin*/
  PM_PON_HLOS_IRQ_RESIN_AND_KPDPWR_S1, /* S1 Resin and PowerKey */
  PM_PON_HLOS_IRQ_PMIC_WDOG_S1       , /* S1 Watchdog */
  PM_PON_HLOS_IRQ_PS_HOLD            , /* PS HOLD */
  PM_PON_HLOS_IRQ_SW_RESET           , /* SW Reset */
  PM_PON_HLOS_IRQ_RESIN_N_DEB        , /* Resin Debounce */
  PM_PON_HLOS_IRQ_KPD_PWR_N_DEB      , /* */
  PM_PON_HLOS_IRQ_INVALID                   /* */
}pm_pon_hlos_irq_type;


 
  
/*===========================================================================

                        HEADER FILES

===========================================================================*/


/**
 * @brief This function enables or disables pon irq
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[in] irq:  
 *                PON irq type. Refer enum pm_pon_hlos_irq_type.
 *  
 * @param[in] enable:  
 *                TRUE: Enable corresponding PON interrupt 
 *                FALSE:Disable corresponding PON interrupt
 *
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_INVALID_PARAMETER
 *          PM_ERR_FLAG_SUCCESS
 *
 */
pm_err_flag_type 
pm_pon_hlos_irq_enable(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, boolean enable);


/**
 * @brief This function clears the PON irq 
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[in] irq:  
 *                PON irq type. Refer enum pm_pon_hlos_irq_type.  
 *
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_INVALID_PARAMETER
 *          PM_ERR_FLAG_SUCCESS
 *
 */
pm_err_flag_type 
pm_pon_hlos_irq_clear(uint32  pmic_device_index, pm_pon_hlos_irq_type irq);


/**
 * @brief This function configures the PON irq trigger 
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[in] irq:  
 *                PON irq type. Refer enum pm_pon_hlos_irq_type.  
 * @param[in] trigger:  
 *                One of different irq triggers. Refer enum pm_irq_trigger_type 
 *                from pm_resources_and_types.h for more details
 *
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_INVALID_PARAMETER
 *          PM_ERR_FLAG_SUCCESS
 *
 */
pm_err_flag_type 
pm_pon_hlos_irq_set_trigger(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, pm_irq_trigger_type trigger);


/**
 * @brief This function configures the PON for irq 
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[in] irq:  
 *                PON irq type. Refer enum pm_pon_hlos_irq_type. 
 * @param[in] type:  
 *                Type of IRQ status to read. Refer enum pm_irq_status_type 
 *                from pm_resources_and_types.h for more details
 * @param[out] status:  
 *                IRQ status.
 *
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_INVALID_PARAMETER
 *          PM_ERR_FLAG_SUCCESS
 *
 */
pm_err_flag_type 
pm_pon_hlos_irq_status(uint32 pmic_device_index, pm_pon_hlos_irq_type irq, pm_irq_status_type type, boolean *status);

#endif // __PM_PON_HLOS_H__
