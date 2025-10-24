#ifndef __PM_PMBUS_DRIVER_H__
#define __PM_PMBUS_DRIVER_H__

/*! \file pm_ldo_driver.h
 *  \n
 *  \brief This file contains LDO peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2012-2014 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/dev/aop.csm/1.0/nvelugu.aop.csm.1.0.Lassen_PMBus_support/aop_proc/core/pmic/pm/drivers/ldo/src/pm_ldo_driver.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/25/13   aks     Code Refactoring: Removing PMIC_SubRsc from pwr algs  
04/12/13   hs      Code refactoring.
12/06/12   hw      Rearchitecturing module driver to peripheral driver
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_pwr_alg.h"
#include "pm_comm.h"
#include "Pmbus.h"
/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/



/*===========================================================================

                     PMBUS  TYPES AND STRUCTURES 

===========================================================================*/
typedef struct 
{
  unsigned mantisa:11;
  unsigned exponent:5;
}slinea11_format_t;


/** 
  @struct pm_pmbus_device_info_type
  @brief Stores the PMBUS PMIC's lave id,  device ID
  Revision number and the Metal Revision number. Please refer
  and device revision id.
 */
typedef struct
{
  uint64          deviceId;               /**< PMBUS PMIC DEVICE ID */
  uint16          deviceRevision;         /**< PMBUS PMIC revision ID */
  uint8           voutModeParamN;         /**< Vout Mode param N*/
  uint64          stepSizeMicoVolt;       /**< Step size in uV -  each LSB*/
  uint32          slaveId;                /**< PMBUS PMIC slave ID */
  uint8           operation;
  uint8           on_off_config;
} pm_pmbus_device_info_type;


#define PM_PMBUS_MANTISA_MASK  0x7FF
#define PM_PMBUS_EXPONENT_MASK 0x1F

#define PM_PMBUS_MANTISA_SIGN_MASK  0x400
#define PM_PMBUS_EXPONENT_SIGN_MASK 0x10

typedef struct
{
   uint32 dbuId;                 // PMIC index as per PG
   uint32 slaveId;               // slave id
}pm_pmbus_rsrc_info_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/

void pm_pmbus_covert_slinear11_to_int32(slinea11_format_t *slinear11, int32 *signed_int);

pm_err_flag_type pm_pmbus_volt_level(uint8 dbu_id, pm_volt_level_type volt_level);

pm_err_flag_type pm_pmbus_volt_level_status(uint8 dbu_id, pm_volt_level_type *volt_level);

pm_err_flag_type pm_pmbus_get_vout_max(uint8 dbu_id, pm_volt_level_type *volt_level);

pm_err_flag_type pm_pmbus_get_vout_min(uint8 dbu_id, pm_volt_level_type *volt_level);

pm_err_flag_type pm_pmbus_iout_status(uint8 dbu_id, int32 *iout);

pm_err_flag_type pm_pmbus_temp_status(uint8 dbu_id, int32 *temp);

pm_err_flag_type pm_pmbus_get_stepper_rate(uint8 dbu_id, uint32 *stepper_rate_uV_uS);

pm_err_flag_type pm_get_pmbus_handle(void ** pm_pmbus_handle);

uint64 pm_get_pmbus_pmic_device_id(uint8 dbu_id);

pm_err_flag_type pm_get_pmbus_slave_id(uint8 dbu_id, uint8 *slave_id_ptr);

pm_err_flag_type pm_get_pmbus_vout_mode_param(uint8 dbu_id, uint8 *vou_mode_parm_n);

pm_err_flag_type pm_get_pmbus_step_size(uint8 dbu_id, uint64 *step_size_uV);

pm_err_flag_type pm_pmbus_version_detect(void) ;


#endif /* __PM_PMBUS_DRIVER_H__ */
