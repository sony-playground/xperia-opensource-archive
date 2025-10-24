/*! \file pm_rpmh_target.c
*  \n
*  \brief This file contains PMIC functions to run sleep enter and sleep exit settings.
*  \n
*  &copy; Copyright 2013-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/target/kailua/src/pm_rpmh_target.c#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/10/15    kt      Initial version.
18/11/22	bde		Broadcast all pmic interrupt after AOSS wake
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "CoreVerify.h"
#include "pm_comm.h"
#include "pm_target_information.h"
#include "pm_rpmh_target.h"
#include "pm_config.h"
#include "pm_config_target.h"
#include "pm_prm_init.h"
#include "pm_rpmh.h"
#include "pm_vrm.h"


/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

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
pm_err_flag_type pm_rpmh_enter_sleep (pm_sleep_mode_type sleep_mode)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    vrm_result result = VRM_SUCCESS;

    result = vrm_enter_sleep (sleep_mode);

    if (result != VRM_SUCCESS)
    {
       err_flag |= PM_ERR_FLAG_FAILURE;
    }

    return err_flag;
}

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
pm_err_flag_type pm_rpmh_exit_sleep (pm_sleep_mode_type sleep_mode)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    vrm_result result = VRM_SUCCESS;

    result = vrm_exit_sleep (sleep_mode);

	err_flag = pm_comm_write_byte (0xE, 0x540, 0x1, 0);												   
    if (result != VRM_SUCCESS)
    {
       err_flag |= PM_ERR_FLAG_FAILURE;
    }

    return err_flag;
}
