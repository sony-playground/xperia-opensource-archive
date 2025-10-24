
/*! \file pm_sbl_boot_cpucp.c
*  \n
*  \brief This file contains CPUCP related functions
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: $
$Author:  $
$DateTime: $
when       who     what, where, why
--------   ---     ----------------------------------------------------------

========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_sbl_boot_target.h"
#include "railway.h"
#include <stdio.h>
#include "boot_logger.h"
#include "pm_device.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "pm_log_utils.h"
#include "cpr.h"
#include "CoreVerify.h"

#define CPUCP_RAIL_VDDCX PM_SMPS_6
#define CPUCP_RAIL_PMIC_INDEX 0x5

#define CPUCP_RAILWAY_TYPE 1

typedef struct
{
    uint32          corners_count;
    railway_corner corner[RAILWAY_CORNERS_COUNT];
} pm_railway_corners;


pm_err_flag_type 
pm_config_cpucp_uls(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 i = 0;
  uint32 corner_volt = 0;
  uint32 max_corner_volt = 0;
  pm_volt_level_type set_volt = 0;
  pm_railway_corners *corners = NULL;
  DALResult status;
  pm_malloc(sizeof(pm_railway_corners), (void**)&corners);
  
  //find the supported corners for this rail
  corners->corner[0] = RAILWAY_NO_REQUEST;
  cpr_railway_get_supported_corners(CPUCP_RAILWAY_TYPE, &(corners->corner[1]), &(corners->corners_count));

  //Get voltage for all corners and find the highest voltage
  for (i = 0; i <= corners->corners_count; i++)
  {
    corner_volt =  railway_get_corner_voltage(CPUCP_RAILWAY_TYPE,corners->corner[i]);
    //if voltage for current corner is higher than the previous one, update max voltage
    if(corner_volt > max_corner_volt)
    {
      max_corner_volt = corner_volt;
    }
  }

  //Get the uls(MAX) voltage setting for this particular rail. Not current voltage programmed.
  err_flag = pm_smps_get_uls (CPUCP_RAIL_PMIC_INDEX, CPUCP_RAIL_VDDCX,&set_volt);
  
  if (set_volt < max_corner_volt)
  {
    err_flag =  pm_smps_set_uls(CPUCP_RAIL_PMIC_INDEX, CPUCP_RAIL_VDDCX, max_corner_volt);
    if(err_flag == PM_ERR_FLAG_SUCCESS )
    {
      pm_log_message ("ULS for VDDCX is updated from %d to %d", set_volt, max_corner_volt);
    }
    else
    {
      pm_log_message ("Unable to update ULS for VDDCX from %d to %d", set_volt, max_corner_volt);
    }
  }
  
  status = DALSYS_Free(corners);
  CORE_VERIFY(status==DAL_SUCCESS);

  return err_flag;
}
