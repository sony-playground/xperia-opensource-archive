/*! \file pm_comm_spmi_lite_init.c
*  \n
*  \brief pmic spmi lite driver
*  \n
* *  \n &copy; Copyright 2014-2016 Qualcomm Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/comm/spmi_lite/src/init/pm_comm_spmi_lite_init.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/04/14   aks     created  
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_comm.h"  
#include "SpmiBus.h"
#include "CoreVerify.h"

extern boolean spmi_initialized;

pm_err_flag_type pm_comm_channel_init_internal(void)
{
    Spmi_Result spmi_result = SPMI_SUCCESS;
    pm_err_flag_type err = PM_ERR_FLAG_SUCCESS ;
    
    // initialize the SPMI BUS
    spmi_result = SpmiBus_Init();

    if(SPMI_SUCCESS  == spmi_result )
    {
        spmi_initialized = TRUE;
    }
    else
    {
        CORE_VERIFY(0); //if spmi_bus init fails err_fatal
    }
    
    return err;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_comm_get_vrm_id (uint32 slave_id, uint16 addr, uint16* vrm_id) 
{
    pm_err_flag_type err = PM_ERR_FLAG_SUCCESS;
    Spmi_Result spmi_result = SPMI_SUCCESS;
    uint8 periph_id = 0;

   
    if(TRUE == spmi_initialized)
    {
        /* check for out-of-bounds index */
        if ( addr > PM_MAX_REGS)
        { 
            err = PM_ERR_FLAG_BUS_ERR ;
        }
        else
        {
            periph_id = ((addr>>8)&0xFF);

            spmi_result = SpmiBus_GetVrmId(slave_id, periph_id, vrm_id);

            if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG_BUS_ERR; }
        }
    }
    else
    {
        err = PM_ERR_FLAG_BUS_ERR;
    }

    return err;
}
