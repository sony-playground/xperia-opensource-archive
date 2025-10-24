#ifndef _PM_SLEEP__H
#define _PM_SLEEP__H
/*! \file 
 *  \n
 *  \brief  pm_sleep.h ---- PMIC RPMh sleep APIs
 *  \n
 *  \n This header file contains functions and variable declarations to support RPMh sleep.
 *  \n
 *  \n &copy; Copyright 2018 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/inc/pm/pm_sleep.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/22/18   kt      Created.
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_resources_and_types.h"
#include "pm_err_flags.h"

/*===========================================================================

                        TYPE DEFINE AND ENUMS

===========================================================================*/

/** @addtogroup pm_sleep
@{ */

 /**
 *  Sleep mode.
 */
typedef enum
{
  PM_SLEEP_MODE_AOSS_SLEEP,  /**< AOSS sleep. */
  PM_SLEEP_MODE_INVALID
} pm_sleep_mode_type;


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/**
 * @name pm_rpmh_enter_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails to the state prior to entering sleep.
 *
 * @param  sleep_mode: can be AOSS sleep
 *
 * @return PMIC error code.
 *
 * @sideeffects Will over-write any client configuration
 *              requests. Any additions to the below function
 *              should be cautiously be added.
 *
 */
pm_err_flag_type pm_rpmh_enter_sleep (pm_sleep_mode_type sleep_mode);

/**
 * @name pm_rpmh_exit_sleep
 *
 * @brief This function calls the driver layer PMIC calls to set
 *        the Rails back to the prior state of entering sleep.
 *
 * @param sleep_mode: can be AOSS sleep
 *
 * @return PMIC error code.
 *
 * @sideeffects Will restore any client configuration requests.
 *              Any additions to the below function should be
 *              cautiously be added.
 *
 */
pm_err_flag_type pm_rpmh_exit_sleep (pm_sleep_mode_type sleep_mode);

pm_err_flag_type pm_rpmh_target_core_rail_en_ctnl( uint8 rail ,boolean on_off);

#endif // _PM_SLEEP__H
