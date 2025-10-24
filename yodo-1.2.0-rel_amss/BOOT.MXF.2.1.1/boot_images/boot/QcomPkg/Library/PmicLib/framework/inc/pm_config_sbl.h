#ifndef __PMIC_SBL_CONFIG_H__
#define __PMIC_SBL_CONFIG_H__

/*! \file  pm_sbl_config.h
 *
 *  \brief  Contains PMIC Setttings Initialisation 
 *  \details  This file contains the PSI APIs. 
 *
 *  &copy; Copyright 2018 - 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/inc/pm_config_sbl.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/07/19   yps     Added pm_psi_free_config_buffer
03/23/16   aab     Updated driver to support Mask write
09/01/15   aab     Updated driver to support SBL Conditional configuration feature
07/13/15   pb      Moved Settings validation content to separate test file
06/23/15   aab     Added support for msm8996 V2/V3 and dropped support for V1
04/29/15   aab     Added support for PMK8001
04/17/15   aab     Added support for msm8996 V2/V1 compatibility
11/10/14   aab     updated PSI data location (Entry point) address
07/03/14   plc     Update PM_BL_PSI_ADDR to be in RPM CODE RAM, not DATA_RAM
06/24/14   akm     Updates for PSI image Creation
08/07/13   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_qc_pmic.h"
#include "com_dtypes.h"         /* Containse basic type definitions */
#include "pm_err_flags.h"     /* Containse the error definitions */
#include "pm_pbs_driver.h"
#include "Target_cust.h"
#include "pm_config_target.h"

#ifdef CUST_H
  #include CUST_H
#endif

//This signature is to verify that pmic.mbn is loaded before
//configuring the registers: Value of 0x31495350 is PSI2
#define PSI_SIGNATURE 0x32495350

#define PM_SBL_16BITADD_8BITDATA_REGULAR 2
#define REV_ID_COMMON 0xFFFFFFFF

//PSI data location(Entry point)
#define PM_BL_PSI_ADDR SCL_PMIC_CONFIG_BUF_BASE

#define PM_BUS_TYPE_SPMI   0x0
#define PM_BUS_TYPE_I2C    0x1
#define PM_BUS_TYPE_PMBUS  0x2

/*=============================================================================

DEFINITIONS

=============================================================================*/
#define SDAM_DATA_SIZE_MAX 128

typedef enum
{
  PM_SBL_WRITE,
  PM_SBL_DELAY,
  PM_SBL_PBS_RAM,
  PM_SBL_SDAM,
  PM_SBL_NOP,
  PM_SBL_OPERATION_INVALID
}pm_sbl_reg_operation_type;

typedef enum
{
  EQUAL,
  GREATER,
  GREATER_OR_EQUAL,
  LESS,
  LESS_OR_EQUAL,
  REV_ID_OPERATION_INVALID
}pm_sbl_cond_operation_type;

//Table A: Main Sbl sequence
typedef struct
{
  uint8  bustype :2;
  uint8  busid :2;
  pm_sbl_reg_operation_type reg_operation : 4; 
  uint8  sid :8;
  uint16 address :16;
  uint8  data :8;
  uint8 mask :8;
  uint8  cond_start_index :8;
  uint8  cond_end_index :8;
}pm_sbl_seq_type;

//Table B: Conditional config table
typedef struct
{
  uint8  cond_bustype : 8;
  uint8  cond_busid : 8;
  uint8  cond_sid :8 ;
  uint8  cond_data :8;
  uint8  cond_mask:8;
  uint16 cond_address :16;
  pm_sbl_cond_operation_type cond_operation : 8;
}pm_sbl_cond_seq_type;



//SBL config info
typedef struct
{
  uint32 signature;          // PSI_SIGNATURE
  uint8  major_ver;          // PSI Major Version
  uint8  minor_ver;          // PSI Minor Version
  uint8  num_target_config;  // Number of target configurations
  uint8  cond_num_entries;      // Total number of conditional entries on pm_sbl_cond_seq_type table
}pm_sbl_config_info_type;

typedef struct
{
  pm_sbl_seq_type*           pm_sbl_seq;
  pm_pbs_ram_data_type*      pm_pbs_ram_seq;
  pm_pbs_ram_data_type**     pm_pbs_ram_seq_v2;
  pm_sbl_cond_seq_type*      pm_sbl_cond_seq;
  uint8*                     pm_sdam_seq;
  uint32                     pm_sbl_seq_size;
  uint32                     pm_pbs_ram_seq_size;
  uint32                     pm_pbs_ram_seq_v2_size;
  uint32                     pm_sbl_cond_seq_size;
  uint32                     pm_sdam_seq_size;
}pm_sbl_pdm_data_type;

typedef struct
{
  pm_sbl_config_info_type* pm_psi_info;
  pm_sbl_pdm_data_type* pdm_data;
}pm_sbl_pdm_config_type;

/**
  @struct pm_pdm_chip_info_type
  @brief Stores the PMIC's chip revision.
 */
typedef struct
{
  uint32         pdmChipRevision;          /**< chip Revision in a format that PDM configuration is generated*/
} pm_pdm_chip_info_type;

struct sbl_config_info;

/*=============================================================================

                              FUNCTION PROTOTYPES

=============================================================================*/

/*Generic function that reads SBL Config data and PBS RAM data from DAL Config and writes it to PMIC */
pm_err_flag_type
pm_sbl_config(void);

pm_err_flag_type
pm_resolve_chip_revision_ex(uint32 bus_id, uint32 slave_id,
                         boolean* valid_slave_id,
                         uint32* pmic_revision );

pm_err_flag_type
pm_resolve_chip_revision(uint32 slave_id,
                         boolean* valid_slave_id,
                         uint32* pmic_revision );

pm_err_flag_type
pm_sbl_validate_cond_config(pm_sbl_config_info_type *sbl_config_info_ds,
                            pm_sbl_cond_seq_type   *cond_ds_ptr,
                            uint8    cond_start_index,
                            uint8    cond_end_index,
                            boolean  *valid_config_flag);

pm_err_flag_type 
pm_psi_free_config_buffer(void);

pm_err_flag_type 
pm_get_pmic_index_from_slave(uint8 sid_index, uint8 *pmic_index);


pm_err_flag_type 
pm_get_pmic_index_from_slave_ex(uint32 bus_id, uint8 sid_index, uint8 *pmic_index);

struct 
sbl_config_info *pm_psi_get_sbl_config_info(void);

void 
pm_config_read_into_pbs_ram_buf(struct sbl_config_info *info, 
                                     uint32 offset, 
                                     uint32 size, 
                                     void **pbs_ram_buff);

#endif // __PMIC_SBL_CONFIG_H__
