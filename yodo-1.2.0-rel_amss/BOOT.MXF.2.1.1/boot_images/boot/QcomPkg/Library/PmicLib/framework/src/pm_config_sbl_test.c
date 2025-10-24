/*! \file  pm_config_sbl_test.c
 *  
 *  \brief  File Contains the PMIC Set Mode validation Implementation
 *  \details Set Mode implementation is responsible for setting  
 *  all mode settings such as Register values, memory values, etc.
    Validation implementation here confirms all the register values written as expected 
    and PBS RAM version is also correct.
 *  
 *  
 *  &copy; Copyright 2013-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_config_sbl_test.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/01/18   pbarot  Added condition to match mask as well trying to find last write
05/09/17   pbarot  Added pm_find_last_write() 
04/03/17   aab     Added update to use xblconfig image
07/08/16   pbarot  Adding pm_read_sbl_version() to read PDM SBL version flashed, also added mask read
03/23/16   pbarot  Adding condition check on lastwrite and correcting print for violation log
10/22/15   al      KW fix
09/08/15   pbarot  Update test based on CLogic implementation
08/18/15   pbarot  Updated PBS RAM version validation
06/23/15   pbarot  Creation, Moved Settings validation test code to this file
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_sbl_boot.h"                /* Needed for pm_clk_busy_wait and sbi_mini initialization */
#include "pm_config_sbl.h"              /* Contains the type definitions and static register tables */
#include "pm_config_sbl_test.h"         /* Contains the type definitions and static register tables */
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "pm_pbs_driver.h"
#include "pm_log_utils.h"
#include "XBLConfig.h"

/* Global Variables */
static uint8 max_pmic_index; /* For settings validation test */
static uint16 total_settings=0;

/* function prototypes */
static pm_err_flag_type pm_run_settings_validation();
static pm_err_flag_type pm_read_sbl_version();
static pm_err_flag_type pm_find_last_write(pm_sbl_config_info_type *sbl_config_info_ds, pm_sbl_cond_seq_type *sbl_cond_config_ds, pm_sbl_seq_type *rc, pm_sbl_seq_type **last_write);

/* Read and log SBL version which was flashed */
pm_err_flag_type 
pm_read_sbl_version()
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   uint8 read_data;   
   uint32 slave_id =  0;
   pm_get_slave_id (PM_PRIMARY_PMIC_INDEX, 0, &slave_id);
   
   err_flag |= pm_comm_read_byte_ex(0, slave_id, PM_SBL_TEST_REVID_SBL_ID_0, &read_data);
   pm_log_message("REVID_SBL_ID_0:0x%X",read_data); 
   
   err_flag |= pm_comm_read_byte_ex(0, slave_id, PM_SBL_TEST_REVID_SBL_ID_1, &read_data);
   pm_log_message("REVID_SBL_ID_1:0x%X",read_data); 
   
   return err_flag;
}


pm_err_flag_type 
pm_find_last_write(pm_sbl_config_info_type *sbl_config_info_ds, pm_sbl_cond_seq_type *sbl_cond_config_ds, pm_sbl_seq_type *rc, pm_sbl_seq_type **last_write)
{
   pm_sbl_seq_type   *rc_copy             = NULL ;
   boolean           valid_config_flag    = TRUE;   
   pm_err_flag_type  err_flag             = PM_ERR_FLAG_SUCCESS;
   
   if ((sbl_config_info_ds == NULL)||(sbl_cond_config_ds == NULL)|| (rc == NULL))
   {
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }
   
   for(rc_copy=rc+1 ; (rc_copy->reg_operation != PM_SBL_OPERATION_INVALID); rc_copy++) /*start last write search from next entry */
   {  
      /*perform write if PBS_CORE_CTL registers detected in order to support OTP based CLOGIC while going down table*/
      if (rc_copy->address == PBS_CORE_MEM_INTF_CFG || rc_copy->address == PBS_CORE_MEM_INTF_CTL || rc_copy->address == PBS_CORE_MEM_INTF_ADDR_LSB || rc_copy->address == PBS_CORE_MEM_INTF_ADDR_MSB)
      {
         //perform write
         err_flag |= pm_comm_write_byte_mask_ex(rc_copy->busid, rc_copy->sid, rc_copy->address, rc_copy->mask, rc_copy->data);
         // pm_log_message("LASTWRITE:%d,0x%X,data:0x%X,sindx:%d,eindx:%d",rc_copy->sid, rc_copy->address, rc_copy->data, rc_copy->cond_start_index, rc_copy->cond_end_index);
         continue;
      }
      // First check if this write is meeting conditional logic
      if ( (rc_copy->cond_start_index == 0) && (rc_copy->cond_end_index == 0) ) 
      {
         valid_config_flag = TRUE; //Normal configuration
      }
      else
      {
         valid_config_flag = TRUE;
         err_flag |= pm_sbl_validate_cond_config(sbl_config_info_ds, sbl_cond_config_ds, rc_copy->cond_start_index, rc_copy->cond_end_index, &valid_config_flag); //check conditional config
      }
      
      if((rc_copy->busid == rc->busid) &&  (rc_copy->sid == rc->sid) && (rc_copy->address == rc->address) && (rc_copy->mask == rc->mask) && (valid_config_flag == TRUE ))
      { 
         *last_write = rc_copy; // getting pointer to last write of same register that we are on at current stage
         // pm_log_message("--CHECK-TRUE:%d,0x%X,data:0x%X,sindx:%d,eindx:%d",rc_copy->sid, rc_copy->address, rc_copy->data, rc_copy->cond_start_index, rc_copy->cond_end_index);
      }
      else
      {  
         continue;
      }
   }
   
   return err_flag;
}

pm_err_flag_type 
pm_run_settings_validation()
{
    uint32            rev_id_read;
    boolean           valid_sid            = FALSE;
    boolean           valid_config_flag    = TRUE;
    //pm_err_flag_type  err_flag             = PM_ERR_FLAG_SUCCESS;
    //pm_err_flag_type  err_flag_chip_rev    = PM_ERR_FLAG_SUCCESS;
    pm_sbl_seq_type   *rc                  = NULL;  //reg config data ptr
    pm_sbl_seq_type   *last_write          = NULL; 
    pm_sbl_seq_type   *last_pbs_ctl_cfg[4] = {NULL,NULL,NULL,NULL}; 
    pm_pbs_ram_data_type *pm_pbs_ram_data  = NULL;
    //struct sbl_config_info *sbl_cfg_info;
   
    uint8 read_data;
    uint16 offset;
   
    void *pm_sbl_pdm_config_ds_buff = NULL;
    pm_sbl_pdm_config_type  *pm_sbl_pdm_config_ds = NULL;
    uintnt pmic_elf_start_addr = 0;
   
   
    pm_psi_get_base_address(&pmic_elf_start_addr);
    //sbl_cfg_info = pm_psi_get_sbl_config_info();
    pm_sbl_pdm_config_ds_buff = (void*)pmic_elf_start_addr;

    //PSI: Get PDM data pointer from xblconfig data image
    pm_sbl_pdm_config_ds   = (pm_sbl_pdm_config_type*)pm_sbl_pdm_config_ds_buff;
   
    CORE_VERIFY_PTR(pm_sbl_pdm_config_ds);
    CORE_VERIFY_PTR(pm_sbl_pdm_config_ds->pdm_data);
	
    pm_sbl_seq_type         *sbl_reg_config_ds      = pm_sbl_pdm_config_ds->pdm_data->pm_sbl_seq; 
    pm_sbl_cond_seq_type    *sbl_cond_config_ds     = pm_sbl_pdm_config_ds->pdm_data->pm_sbl_cond_seq;
    pm_pbs_ram_data_type    *pbs_ram_config_ds      = pm_sbl_pdm_config_ds->pdm_data->pm_pbs_ram_seq;
    pm_pbs_ram_data_type    **pbs_ram_config_ds_v2  = pm_sbl_pdm_config_ds->pdm_data->pm_pbs_ram_seq_v2;
    pm_sbl_config_info_type *sbl_config_info_ds     = pm_sbl_pdm_config_ds->pm_psi_info; 
   
    if ((sbl_reg_config_ds == NULL)||(sbl_cond_config_ds == NULL)|| ((pbs_ram_config_ds == NULL) && (pbs_ram_config_ds_v2 == NULL)))
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }
   
    if(sbl_config_info_ds->signature != PSI_SIGNATURE) 
    { 
      CORE_VERIFY(0); //Error fatal if the pmic image signature doesn't match 
    } 
   
    for(rc = sbl_reg_config_ds; (rc->reg_operation != PM_SBL_OPERATION_INVALID); rc++)  
    {
       /* Handle chip revision check for each entry*/
       if (rc->reg_operation != PM_SBL_DELAY ) 
       {
         /*err_flag_chip_rev |=*/ pm_resolve_chip_revision_ex(rc->busid, rc->sid, &valid_sid, &rev_id_read);
         if (valid_sid == FALSE)
         {
          continue;  //This current configuation does not apply to this SID (PMIC does not exist)
         }
         if ((rc->address == PBS_CORE_MEM_INTF_WR_DATA0) || (rc->address == PBS_CORE_MEM_INTF_WR_DATA1) || (rc->address == PBS_CORE_MEM_INTF_WR_DATA2) || (rc->address == PBS_CORE_MEM_INTF_WR_DATA3))
         {
          continue; //This configuation does not need to be tested
         }
       }    

       /* If condition start and end index is 0 then its must write otherwise validate condition*/
       if ( (rc->cond_start_index == 0) && (rc->cond_end_index == 0) ) 
       {
         valid_config_flag = TRUE; //Normal configuration
       }
       else
       {
          valid_config_flag = TRUE;
          /*err_flag |=*/ pm_sbl_validate_cond_config(sbl_config_info_ds, sbl_cond_config_ds, rc->cond_start_index, rc->cond_end_index, &valid_config_flag); //check conditional config
       }
      
       /* If condition is TRUE then proceed for further validation*/
       if( valid_config_flag == TRUE )
       { 
        switch(rc->reg_operation)  
        {
           case PM_SBL_WRITE:  
           {
              /*perform write if PBS_CORE_CTL registers detected in order to support OTP based CLOGIC*/
              if ((rc->address == PBS_CORE_MEM_INTF_CFG) || (rc->address == PBS_CORE_MEM_INTF_CTL) || (rc->address == PBS_CORE_MEM_INTF_ADDR_LSB) || (rc->address == PBS_CORE_MEM_INTF_ADDR_MSB))
              {
                   
                 /*err_flag |=*/ pm_comm_write_byte_mask_ex(rc->busid, rc->sid, rc->address, rc->mask, rc->data);
                 pm_log_message("WRITE:bus:%d,sid:%d,0x%X,data:0x%X,sindx:%d,eindx:%d",rc->busid, rc->sid, rc->address, rc->data, rc->cond_start_index, rc->cond_end_index);
                
                 /* store entry pointer for PBS_CORE_CTL configureation which needs to be re programmed at very end of processing current entry*/
                 /* When we go down table to look for last write this may change and hence reprogram will need to be done as we move our original pointer in table*/
                 switch (rc->address)
                 { 
                    case PBS_CORE_MEM_INTF_CFG:
                        last_pbs_ctl_cfg[0]=rc;
                    break;
                    case PBS_CORE_MEM_INTF_CTL:
                        last_pbs_ctl_cfg[1]=rc;
                    break;
                    case PBS_CORE_MEM_INTF_ADDR_LSB:
                        last_pbs_ctl_cfg[2]=rc;
                    break;   
                    case PBS_CORE_MEM_INTF_ADDR_MSB:
                        last_pbs_ctl_cfg[3]=rc;
                    break;
                 }
                  continue;
             }
             
              // pm_log_message("---- ENTRY:%d,0x%X,data:0x%X,sindx:%d,eindx:%d ----",rc->sid, rc->address, rc->data, rc->cond_start_index, rc->cond_end_index);
             
              /* find last write for same register if exists in table */
              last_write = rc;
              /*err_flag |= */ pm_find_last_write(sbl_config_info_ds, sbl_cond_config_ds, rc, &last_write);
             
              // pm_log_message("---- LAST_WRITE:%d,0x%X,data:0x%X,sindx:%d,eindx:%d ----",last_write->sid, last_write->address, last_write->data, last_write->cond_start_index, last_write->cond_end_index);

              offset = rc->address & 0x00FF;
              if ( (offset != PM_SBL_TEST_OFFSET_SEC_ACCESS) && (offset != PM_SBL_TEST_OFFSET_INT_EN) ) // not covering entries with with selected offset of SEC_ACCESS and INT_EN
              { 
                pm_comm_read_byte_mask_ex(rc->busid, rc->sid, rc->address, rc->mask, &read_data); //address data at original location is being changed in sbl write function so not adding offset in base address

                if (read_data == last_write->data) // comparing current read data from register and comparing it to last write data from structure 
                {
                  pm_log_message("PASS:%d,%d,0x%X,set:0x%X,get:0x%X",rc->busid, rc->sid, rc->address, last_write->data, read_data); // remove to save some memory 
                }
                else
                {
                  pm_log_message("VIOLATION:%d,%d,0x%X,set:0x%X,get:0x%X",rc->busid, rc->sid, rc->address, last_write->data, read_data);
                }
                total_settings++;
              }
            }
             break;
            case PM_SBL_PBS_RAM:
            {
                max_pmic_index = rc->data; // reading data section for PM_SBL_PBS_RAM gives particular pmic its intended for and last pmic index stored will give idea on max pmics available.                  
               // max_pmic_index = (rc->sid /2); // changing logic to determine max pmic index due to pmk sbl is seperately generated and rc->data is 0 for pmk reg cfg.

              if( (sbl_config_info_ds->major_ver == 1) && (sbl_config_info_ds->minor_ver == 4) ) //ver 2 - Lahaina and newer
              {
                 //pm_pbs_ram_data = (pm_pbs_ram_data_type*)(&pbs_ram_config_ds[PBS_RAM_DATA_SIZE *rc->data] + (rc->address-1));
                 //pm_log_message("PBS:%d:0x%X,0x%X",(rc->sid), (pm_pbs_ram_data)->word2, (pm_pbs_ram_data)->word1 ); need to check with systems team to place pbs ram version in header
                 break;
                 
              }
              if( (sbl_config_info_ds->major_ver == 1) && (sbl_config_info_ds->minor_ver == 3) ) //ver 2 - Added mask write support; ver 3 xml file gen, reg 0x52
              {
                 pm_pbs_ram_data = (pm_pbs_ram_data_type*)((uint64)pbs_ram_config_ds_v2[rc->data] + (uint64)pm_sbl_pdm_config_ds_buff + (rc->address-1));
                 pm_log_message("PBS:%d:0x%X,0x%X",(rc->sid/2), (pm_pbs_ram_data)->word2, (pm_pbs_ram_data)->word1 );
              }
              
            }
             break;
            case PM_SBL_DELAY: 
            case PM_SBL_NOP:
             break;
            default:
              //err_flag |= PM_ERR_FLAG_FAILURE;
              break;
        }
       
        // program PBS_CTL registers back to initial setting what we programmed while entering in to processing for individual entry
        if (last_pbs_ctl_cfg[0] && last_pbs_ctl_cfg[1] && last_pbs_ctl_cfg[2] && last_pbs_ctl_cfg[3]) // null pointer check
        {
         if (last_pbs_ctl_cfg[0]->data != 0 || last_pbs_ctl_cfg[1]->data != 0)
           {
              // pm_log_message("REPROGRAM:0x%X,0x%X,0x%X,0x%X",last_pbs_ctl_cfg[0]->data, last_pbs_ctl_cfg[1]->data, last_pbs_ctl_cfg[2]->data, last_pbs_ctl_cfg[3]->data);
               pm_comm_write_byte_mask(last_pbs_ctl_cfg[0]->sid, last_pbs_ctl_cfg[0]->address, last_pbs_ctl_cfg[0]->mask, last_pbs_ctl_cfg[0]->data);
               pm_comm_write_byte_mask(last_pbs_ctl_cfg[1]->sid, last_pbs_ctl_cfg[1]->address, last_pbs_ctl_cfg[1]->mask, last_pbs_ctl_cfg[1]->data);
               pm_comm_write_byte_mask(last_pbs_ctl_cfg[2]->sid, last_pbs_ctl_cfg[2]->address, last_pbs_ctl_cfg[2]->mask, last_pbs_ctl_cfg[2]->data);
               pm_comm_write_byte_mask(last_pbs_ctl_cfg[3]->sid, last_pbs_ctl_cfg[3]->address, last_pbs_ctl_cfg[3]->mask, last_pbs_ctl_cfg[3]->data);
           }
        }
     }
    }
   return 0;//err_flag;
}


pm_err_flag_type 
pm_sbl_config_test()
{   
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   uint8 flag;
   
   err_flag |= pm_utils_settings_validation_flag(&flag, 0); // to verify if flag register bit is set to run this test function
   if(flag)
   {     
      pm_log_message("PM_SET_VAL:Start");
      err_flag |= pm_run_settings_validation(); // Run through settings validation
      err_flag |= pm_read_sbl_version(); // Read and log SBL version which was flashed  
      pm_log_message("PM_SET_VAL:End:%d",total_settings);
   }
   else
   {
      pm_log_message("SET_VAL:Skip");
   }    
   return err_flag;
}

pm_err_flag_type pm_pbs_ram_version_validation_test(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   pm_pbs_info_type pbs_info_ptr;
   uint8 pmic_device_index=0;
   uint8 flag;
   //uint8 pbs_periph_count;
   // char str[PM_SBL_TEST_MAX_STR_LENGTH]; made it global
   
   err_flag |= pm_utils_settings_validation_flag(&flag, 1); // to verify if flag register bit is set to run this test function
   if(flag){
      /* go through all available PMIC and print out PBS RAM version for each */
      for (pmic_device_index = 0; pmic_device_index < PM_MAX_NUM_PMICS; pmic_device_index++)
      {
         if (pm_get_pmic_model(pmic_device_index) != PMIC_IS_INVALID && pm_get_pmic_model(pmic_device_index) != PMIC_IS_UNKNOWN)
         {
            err_flag = pm_get_pbs_info(pmic_device_index, &pbs_info_ptr);
            if(err_flag == PM_ERR_FLAG_SUCCESS)
	        {
               pm_log_message("PBS_GET:%d:0x%X",pmic_device_index, pbs_info_ptr.ram_version);
            }
         }
         else
         {
            continue;
         }
      }
   }
   return PM_ERR_FLAG_SUCCESS;
}


