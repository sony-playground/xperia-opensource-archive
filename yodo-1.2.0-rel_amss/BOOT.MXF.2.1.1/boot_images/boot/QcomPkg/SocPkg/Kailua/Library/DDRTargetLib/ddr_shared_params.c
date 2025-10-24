/**
 * @file ddr_shared_params.c
 * @brief
 * DDR related shared data between BOOT and AOP
 */
/*==============================================================================
                                EDIT HISTORY

================================================================================
when       who      what, where, why
--------   ---      -------------------------------------------------------------
05/05/22   sairajma added shrm minidump support
02/04/21   mmohamme MTE is enabled in DSF, so remove MTE enable call
01/22/21   mmohamme update highest_bank_bit field
06/04/18   daisond  PASR table share with AOP
05/24/17   rp       Initial version
================================================================================
                   Copyright 2014-2018,2020-2022 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>
#include "ddr_drivers.h"
#include "ddr_params.h"
#include "HAL_SNS_DDR.h"
#include "CoreVerify.h"
#include "ddr_shared_params.h"
#include "ddr_fw_interface.h"
#include "smem.h"
#include "CoreMsgRam.h"
#include "ddr_sdi_log.h"
#include "boot_minidump.h"


/*==============================================================================
                                  MACROS
==============================================================================*/
#define SAME_PAGE_SYN_ADDR  0x19A58028
#define SHRM_MD_SS_TOC_MAGIC              0xDEEDBEEF
#define NUM_OF_REGIONS_COUNT 			  1
#define SHRM_MINIDUMP_SMEM_ID 			  614
/*==============================================================================
                                  DATA
==============================================================================*/


/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

/* ============================================================================
**  Function : ddr_clock_query
** ============================================================================
*/
/*!
*   @brief
*   This function is called by clock driver to query ddr clock info
*
*   @details
*   Clock driver queries DDR driver to get all the MC and SHUB clock plan related info
*
*   @param
*   ddr_clock_query_type
*
*   @par Dependencies
*   Needs to be called after HAL_DDR_Init once DCB is parsed
*
*   @par Side Effects
*   None
*
*   @retval  struct ddr_clock_plan
*
*   @sa None
*/
ddr_clock_plan ddr_clock_query(ddr_clock_query_type query)
{
	ddr_clock_plan mc_shub_plan;
	switch (query)
	{
		case MC_CLOCK_PLAN:
			mc_shub_plan.num_levels = ddr_shared_data->num_ddr_levels;
			mc_shub_plan.state = &ddr_driver_struct->aop_params->mc_states[0];
			break;
		
		case SHUB_CLOCK_PLAN:
			mc_shub_plan.num_levels = ddr_shared_data->num_shub_levels;
			mc_shub_plan.state =  &ddr_driver_struct->aop_params->shub_states[0];
			break;
			
		default:
			mc_shub_plan.num_levels = 0;
			mc_shub_plan.state = NULL;
	}
	return mc_shub_plan;
} /* ddr_clock_query */

/* ============================================================================
**  Function : ddr_clock_query_vddq_plan
** ============================================================================
*/
/*!
*   @brief
*   This function is called by clock driver to get vddq clock plan information
*
*   @details
*   Clock driver queries DDR driver to get vddq clock plan information
*
*   @param
*   ddr_clock_query_type
*
*   @par Side Effects
*   None
*
*   @retval  struct vddq_clock_plan
*
*   @sa None
*/
ddr_vddq_plan ddr_clock_query_vddq_plan(ddr_clock_query_type query)
{
	ddr_vddq_plan vddq_clock_plan;
	switch (query)
	{
		case VDDQ_CLOCK_PLAN:
			vddq_clock_plan.num_levels = ddr_shared_data->num_ddr_levels;
			vddq_clock_plan.vddq_state = &ddr_driver_struct->vddq_plan[0];
			break;
			
		default:
			vddq_clock_plan.num_levels = 0;
			vddq_clock_plan.vddq_state = NULL;
	}
	return vddq_clock_plan;
} /* ddr_clock_query_vddq_plan */

/* ============================================================================
**  Function : ddr_share_data_to_aop
** ============================================================================
*/
/*!
*   @brief
*   This function is called to copy all the ddr related info required by AOP
*
*   @details
*   All the DDR related information required by AOP during runtime is copied 
*   into SMEM in this function
*
*   @param
*   None
*
*   @par Dependencies
*   SMEM should have been initialized before calling this function
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
void ddr_share_data_to_aop(void)
{
  uint8 i = 0;
  DDR_AOP_PARAMS *ddr_aop_params_ptr = ddr_shared_data->ddr_aop_params.ptr;
  void *smem_ptr = smem_alloc(DDR_AOP_SMEM_ID, sizeof(md_ss_region)+sizeof(DDR_AOP_PARAMS));
  CORE_VERIFY(smem_ptr != NULL); 

  /* Fill the ddr_regions in aop params */
  for(i=0; i < get_num_of_ddr_regions(); i++)
  {
      ddr_aop_params_ptr->ddr_regions[i].start_address = ddr_driver_struct->ddr_regions_info.ddr_region[i].start_address;
      ddr_aop_params_ptr->ddr_regions[i].size = ddr_driver_struct->ddr_regions_info.ddr_region[i].size;
      ddr_aop_params_ptr->ddr_regions[i].mc_address = ddr_driver_struct->ddr_regions_info.ddr_region[i].mc_address;
      ddr_aop_params_ptr->ddr_regions[i].ddr_rank = ddr_driver_struct->ddr_regions_info.ddr_region[i].ddr_rank;
  }  
  ddr_aop_params_ptr->ddr_smem_info_header.shared_table_header[DDR_REGIONS].size =  sizeof(ddr_aop_params_ptr->ddr_regions);
  ddr_aop_params_ptr->ddr_smem_info_header.shared_table_header[DDR_REGIONS].offset = offsetof(DDR_AOP_PARAMS, ddr_regions); 
  
  /* Store smem address in AOP msg_ram */
  msg_ram_set_smem_address((uint32)DDR_AOP_SMEM_ID, (uint32)(uintptr_t)smem_ptr);
  
  ddr_driver_struct->ddr_regions_info.highest_bank_bit = ddr_shared_data->device_params.highest_bank_bit;
  HAL_CORE_SW_Set_PASR_DDR_INFO_TABLE(ddr_shared_data);
  
  memscpy(smem_ptr, sizeof(DDR_AOP_PARAMS), ddr_shared_data->ddr_aop_params.ptr, sizeof(DDR_AOP_PARAMS));
  
  /* Fill the ddr_regions_info */
  for(i=0; i < get_num_of_ddr_regions(); i++)
  {
	  ddr_driver_struct->ddr_regions_info.ddr_region[i].granule_size = ddr_aop_params_ptr->ddr_regions[i].granule_size;
	  ddr_driver_struct->ddr_regions_info.ddr_region[i].segments_start_index = ddr_aop_params_ptr->ddr_regions[i].segments_start_index;
	  ddr_driver_struct->ddr_regions_info.ddr_region[i].segments_start_offset = ddr_aop_params_ptr->ddr_regions[i].segments_start_offset;
  }

} /* ddr_share_data_to_aop */


/**
  Shares SHRM Info to minidump via SMEM

  This function copies SHRM info into a structure to be available for mini dump thru SMEM

  @param[in] None

  @return None

  @dependencies
  Needs to be called after SMEM has been initialized.
*/
const md_ss_region shrm_md_ss_regions[NUM_OF_REGIONS_COUNT] =
{
    {
    /* MSG_RAM */
      "SHRM",
      0,                    
      MD_REGION_VALID,      
      SHRM_IMEM_SHRM_IRAM_BASE, //0x19040000,
      SHRM_TOTAL_DUMP_MEM_SIZE, //0x20000,
    },
};
boolean ddr_shrm_mini_dump_init(void)
{
   md_global_toc *md_gtoc = NULL;
   md_ss_toc *ss_toc =  NULL;
   uint64 smem_global_addr;
   uint64 *shrm_smem_base = NULL;
   smem_global_addr = (*((uint32* )MD_SHARED_IMEM_BASE));
   shrm_smem_base = (uint64 *)smem_alloc( DDR_AOP_SMEM_ID, sizeof(md_ss_region)+sizeof(DDR_AOP_PARAMS));
   if(shrm_smem_base == NULL)
	   return 0;
   shrm_smem_base = shrm_smem_base + sizeof(DDR_AOP_PARAMS);   
   memscpy(shrm_smem_base, sizeof(md_ss_region), &shrm_md_ss_regions, sizeof(md_ss_region));

   md_gtoc = (md_global_toc*)smem_global_addr;

   if (md_gtoc->md_toc_init != TRUE)
		return 0;

   ss_toc = &md_gtoc->md_ss_toc[MD_SS_SHRM];
   ss_toc->md_ss_toc_init             = SHRM_MD_SS_TOC_MAGIC;
   ss_toc->md_ss_enable_status        = MD_SS_ENABLED;
   /*qsee md blobs will be encrypted in SDI pass#1.*/
   ss_toc->encryption_required        = MD_SS_ENCR_REQ;
   ss_toc->encryption_status          = MD_SS_ENCR_START;
   ss_toc->ss_region_count            = NUM_OF_REGIONS_COUNT;
   ss_toc->md_ss_smem_regions_baseptr = (uint64)shrm_smem_base;
   return 1;
}/* ddr_shrm_mini_dump_init */

