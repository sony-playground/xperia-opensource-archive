/*! \file  pmic_config_sbl_coderam.c
 *
 *  \brief  File Contains the PMIC Set Mode Implementation
 *  \details Set Mode implementation is responsible for setting
 *  all mode settings such as Register values, memory values, etc.
 *  This version stores the PSI data in Code Ram
 *
 *    This file contains code for Target specific settings and modes.
 *
 *  &copy; Copyright 2013-2022 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_config_sbl_coderam.c#1 $
$DateTime: 2022/08/18 10:15:46 $  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/17   aab     Added update to use xblconfig image
08/03/16   akm     Changed pm_clk_busy_wait to pm_busy_wait
03/03/16   aab     Updated driver to support Mask write
10/22/15   al      KW fix
10/12/15   al      Adding API to set PMIC ELF start address
09/01/15   aab     Updated driver to support SBL Conditional configuration feature
07/13/15   pb      Moved out Settings validation test code to separate file
04/17/15   aab     Added pm_sbl_config2 to support msm8996 V2/V1 compatibility
11/10/14   aab     Updated driver to get pbs data size from sbl config data
07/16/14   akm     Comm change Updates
06/17/14   akm     Added PSI support
08/07/13   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_sbl_boot.h"
#include "pm_config_sbl.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "XBLConfig.h"
#include "pm_sdam.h"
#include "pm_log_utils.h"
#include "pm_sbl_boot_target.h"
#include "pm_sdam_driver.h"
#include "pm_config_target_size.h"
#include "DALHeap.h"
#include "pm_config_sbl_common.h"

#define DEFAULT_PBS_PERIPH_ID   0x70 //Support for older PMICs (PMIC5 and below)

extern pm_sbl_pdm_data_type      pm_psi_data_hdr;
extern pm_sbl_pdm_config_type    pm_psi_header;

pm_err_flag_type
pm_sbl_config()
{
  pm_err_flag_type        err_flag              = PM_ERR_FLAG_SUCCESS;
  pm_sbl_seq_type         *rc                   = NULL; //Reg config ptr
  boolean                 valid_sid             = FALSE;
  uint32                  rev_id_read           = 0;
  boolean                 valid_config_flag     = TRUE;
  pm_sbl_seq_type         *sbl_reg_config_ds    = NULL;
  pm_sbl_cond_seq_type    *sbl_cond_config_ds   = NULL;
  pm_pbs_ram_data_type    *pbs_ram_config_ds     = NULL;
  pm_pbs_ram_data_type    **pbs_ram_config_ds_v2 = NULL;
  uint8                   *sdam_swire_config_ds = NULL;
  pm_sbl_config_info_type *sbl_config_info_ds   = NULL;
  pm_err_flag_type        pbs_err = PM_ERR_FLAG_SUCCESS;
  int                     i                     = 0;
  uint8                   sdam_pm_index         = 0;
  pm_sdam_data_type       *sdam_data            = NULL;
  uint32                  sdam_rsrc_index       = 0;
  pm_pbs_ram_data_type    *pbs_ram_buffer       = NULL;
  boolean                 version_good          = FALSE;
  uint8                   reload_pbs_state      = RELOAD_PBS_STATE_RELOAD;

  pm_sbl_pdm_config_type  *pm_sbl_pdm_config_ds = NULL;

  // *** Process of loading statically compiled PSI data
  pm_sbl_pdm_config_ds   =  &pm_psi_header;

  //PSI: Get PDM data pointer from xblconfig data image
  pm_psi_set_base_address((uintnt)pm_sbl_pdm_config_ds);

  CORE_VERIFY_PTR(pm_sbl_pdm_config_ds);
  CORE_VERIFY_PTR(pm_sbl_pdm_config_ds->pdm_data);
  CORE_VERIFY_PTR(pm_sbl_pdm_config_ds->pm_psi_info);
  sbl_config_info_ds   = pm_sbl_pdm_config_ds->pm_psi_info ;

  // If the config is reading fragmented data, make sure the config version can support this
  if(sbl_config_info_ds->signature != PSI_SIGNATURE) 
  {
    return err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  // For non-fragmented loading
  if( sbl_config_info_ds->major_ver == 1 && 
           sbl_config_info_ds->minor_ver >= 3 && sbl_config_info_ds->minor_ver <= 5)   //ver 2 - Added mask write support; ver 3 xml file gen, reg 0x52
  {
    version_good = TRUE;
  }
  if( sbl_config_info_ds->major_ver == 2)   //ver 2 - Added mask write support; ver 3 xml file gen, reg 0x52
  {
    version_good = TRUE;
  }

  CORE_VERIFY(version_good); // Make sure the version number is good

  sbl_reg_config_ds    = pm_sbl_pdm_config_ds->pdm_data->pm_sbl_seq ;
  pbs_ram_config_ds_v2 = pm_sbl_pdm_config_ds->pdm_data->pm_pbs_ram_seq_v2;
  pbs_ram_config_ds = pm_sbl_pdm_config_ds->pdm_data->pm_pbs_ram_seq;
  sbl_cond_config_ds   = pm_sbl_pdm_config_ds->pdm_data->pm_sbl_cond_seq ;

  if ((sbl_reg_config_ds == NULL)||(sbl_cond_config_ds == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    return err_flag;
  }

  for(rc = sbl_reg_config_ds; (rc->reg_operation != PM_SBL_OPERATION_INVALID); rc++)
  {
    if (rc->reg_operation != PM_SBL_DELAY )
    {
      pm_resolve_chip_revision_ex(rc->busid, rc->sid, &valid_sid, &rev_id_read);
      if (valid_sid == FALSE)
      {
        continue;  //This configuration does NOT apply to this SID (PMIC does not exist)
      }
    }

    if ( (rc->cond_start_index == 0) && (rc->cond_end_index == 0) )
    {
      valid_config_flag = TRUE; //Normal configuration
    }
    else
    {
      valid_config_flag = TRUE;
      err_flag |= pm_sbl_validate_cond_config(sbl_config_info_ds,
                                              sbl_cond_config_ds,
                                              rc->cond_start_index,
                                              rc->cond_end_index,
                                              &valid_config_flag);
    }

    if( valid_config_flag == TRUE )
    {
      switch(rc->reg_operation)
      {
        case PM_SBL_WRITE:
          if(rc->mask == 0xFF)
          {
            err_flag |= pm_comm_write_byte_ex(rc->busid, rc->sid, rc->address, rc->data);
          }
          else
          {
            err_flag |= pm_comm_write_byte_mask_ex(rc->busid, rc->sid, rc->address,
                                                rc->mask, rc->data);
          }
          break;

        case PM_SBL_DELAY:
          pm_busy_wait(rc->address); //Address field contains delay in us
          break;

        case PM_SBL_PBS_RAM:
          for(i=0; i<2; i++)
          {
            //data: Index in PBS RAM Table; address: Size of PBS RAM
            if( (sbl_config_info_ds->major_ver == 2) ||  // Major ver 2 - Fragmented loading
               ((sbl_config_info_ds->major_ver == 1) && (sbl_config_info_ds->minor_ver == 4)) ||
               ((sbl_config_info_ds->major_ver == 1) && (sbl_config_info_ds->minor_ver == 5)) ) //ver 2 - Lahaina and newer
            {
              if (pbs_ram_config_ds_v2 == NULL)
              {
                err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
                break;
              }
              pbs_ram_buffer = pbs_ram_config_ds_v2[rc->data];
              
              // Check the PSI CRC to see if PSI loading can be skipped
              pm_sbl_config_check_psi_crc_v2(&reload_pbs_state, rc->sid, rc->data, (void*)pbs_ram_buffer);

              if (reload_pbs_state == RELOAD_PBS_STATE_SKIP)
              {
                 break;
              }

              pbs_err = pm_pbs_ram_image_load(rc->sid, pbs_ram_buffer, rc->address, rc->mask);
            }
            else if( (sbl_config_info_ds->major_ver == 1) && (sbl_config_info_ds->minor_ver == 3) ) //ver 2 - Added mask write support; ver 3 xml file gen, reg 0x52
            {
              if (pbs_ram_config_ds == NULL)
              {
                err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
                break;
              }
              pbs_ram_buffer = &pbs_ram_config_ds[PBS_RAM_DATA_SIZE * rc->data];

              pbs_err = pm_pbs_ram_image_load(rc->sid, pbs_ram_buffer, rc->address, DEFAULT_PBS_PERIPH_ID);
            }
            /* Exit if first load was SUCCESS */
            i = (pbs_err == PM_ERR_FLAG_SUCCESS) ? 2 : i;
          }
          if (err_flag != PM_ERR_FLAG_SUCCESS) {
            return err_flag;
          }
          err_flag |= pbs_err;
          break;

        case PM_SBL_NOP:
          break;

        case PM_SBL_SDAM:
          /*SID, arr_index, addr,    length, operation,   start, end condition
          { 0,   0(A),      0x0B740, 128,    PM_SBL_SDAM,  46,   46},*/
          sdam_pm_index = 0;
          sdam_data = NULL;
          sdam_rsrc_index = 0;

          err_flag |= pm_get_pmic_index_from_slave(rc->sid, &sdam_pm_index);
          sdam_data = pm_sdam_get_data(sdam_pm_index);
          if(sdam_data == NULL)
          {
            CORE_VERIFY(0);
          }
 
          sdam_swire_config_ds = pm_sbl_pdm_config_ds->pdm_data->pm_sdam_seq;

          sdam_rsrc_index = (((uint32)(rc->address)) & 0xFF00) - ((uint32)(sdam_data->base_address));
          sdam_rsrc_index >>= 8;
          err_flag |= pm_sdam_mem_write ( sdam_pm_index, sdam_rsrc_index,
                      (rc->address & 0xf),
                      (uint32)rc->mask,
                      &(sdam_swire_config_ds[rc->data * SDAM_DATA_SIZE_MAX]) );

          if(err_flag != PM_ERR_FLAG_SUCCESS)
          {
            pm_log_message("Sdam Write Failed");
          }
          break;

        default:
          err_flag |= PM_ERR_FLAG_FAILURE;
          break;
      }
    }
  }

  return err_flag;
}

sbl_config_info_t *pm_psi_get_sbl_config_info(void)
{
  return NULL;
}

pm_err_flag_type 
pm_psi_get_heap_buffer_info(void **base_addr, uint32 *buf_size)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   pm_sbl_pdm_config_type  *pm_sbl_pdm_config_ds = NULL;
   uintptr_t ptend;
   uintptr_t ptstart;
   pm_sbl_pdm_data_type *ptpdm;

   //Giving address directly instead of using the get/set APIs 
   //On RUMIs set API will not be called
   pm_sbl_pdm_config_ds = &pm_psi_header;

   // Start address of the buffer is pm_sbl_pdm_config_ds->pdm_data
   // End address is the highest of all the buffer used
   ptpdm = pm_sbl_pdm_config_ds->pdm_data;
   ptend = (uintptr_t)ptpdm->pm_sbl_seq;
   if (ptend < ((uintptr_t)ptpdm->pm_pbs_ram_seq_v2 + ptpdm->pm_pbs_ram_seq_v2_size))
        ptend = (uintptr_t)ptpdm->pm_pbs_ram_seq_v2 + ptpdm->pm_pbs_ram_seq_v2_size;
   if (ptend < ((uintptr_t)ptpdm->pm_sbl_cond_seq + ptpdm->pm_sbl_cond_seq_size))
        ptend = (uintptr_t)ptpdm->pm_sbl_cond_seq + ptpdm->pm_sbl_cond_seq_size;
   if (ptend < ((uintptr_t)ptpdm->pm_sdam_seq + ptpdm->pm_sdam_seq_size)) 
        ptend = (uintptr_t)ptpdm->pm_sdam_seq + ptpdm->pm_sdam_seq_size;
   ptstart = (uintptr_t)ptpdm->pm_sbl_seq;
   if (ptstart > ((uintptr_t)ptpdm->pm_pbs_ram_seq_v2)) ptstart = (uintptr_t)ptpdm->pm_pbs_ram_seq_v2;
   if (ptstart > ((uintptr_t)ptpdm->pm_sbl_cond_seq)) ptstart = (uintptr_t)ptpdm->pm_sbl_cond_seq;

   if ((ptstart > ((uintptr_t)ptpdm->pm_sdam_seq)) && (((uintptr_t)ptpdm->pm_sdam_seq) != 0))
     ptstart = (uintptr_t)ptpdm->pm_sdam_seq;

   *buf_size = ptend - ptstart;
   *base_addr = (void *)ptstart;

   return err_flag;
}