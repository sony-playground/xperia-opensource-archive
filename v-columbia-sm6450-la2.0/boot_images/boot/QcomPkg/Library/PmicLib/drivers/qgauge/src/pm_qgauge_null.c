/*! \file
*
*  \brief  pm_qgauge.c driver implementation.
*  \details qguage driver implementation.
*  &copy;
*  Copyright (c) 2018-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/drivers/qgauge/src/pm_qgauge_null.c#1 $
$Author: pwbldsvc $
$DateTime: 2021/12/20 11:02:36 $
when        who    what, where, why
--------    ---    ----------------------------------------------------------
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_qgauge.h"
#include "pm_qgauge_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/



pm_err_flag_type pm_qgauge_irq_enable(uint32 device_index, pm_qgauge_irq_type irq, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qgauge_irq_clear(uint32  device_index, pm_qgauge_irq_type irq)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qgauge_irq_set_trigger(uint32 device_index, pm_qgauge_irq_type irq, pm_irq_trigger_type trigger)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qgauge_irq_status(uint32 device_index, pm_qgauge_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}



pm_err_flag_type pm_qgauge_get_status(uint32 device_index, pm_qgauge_status_type* qgauge_status)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qgauge_get_vbat(uint32 device_index, uint32* vbat_inmv)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qgauge_get_ibat(uint32 device_index, int32* ibat_inma)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qgauge_set_vbat_empty_threshold(uint32 device_index, uint32 vbatEmptyThreshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qgauge_set_vbat_low_threshold(uint32 device_index, uint32 vbatlowThreshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qgauge_get_qgauge_pmic_info(uint8 *pmic_index, uint8 *slave_id)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qgauge_get_pon_ocv_acc_data(uint32 device_index, pm_qg_acc_index_type acc_index, uint16* data)
{
  return PM_ERR_FLAG_SUCCESS;
}
