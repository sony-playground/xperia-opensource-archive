/*=============================================================================
 *
 * FILE:      flash_hal_pagescope.c
 *
 * DESCRIPTION: This file contains implementation for PageScope reads.
 *
 *
 * Copyright (c) 2018-2020, 2022 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *===========================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/NandHalLib/QpicLib/flash_hal_nandc_pagescope.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ---------   ---     ----------------------------------------------
 * 08/10/20     sa      Erase CW status fixed in HW.
 * 06/08/20     sa      Ported for Olympic.
 * 07/13/19	sa      Added descriptor to disable auto status register.
 * 06/11/19     sa      Check erase CW status based on QPIC step version.
 * 10/20/18     sa      Initial Revision
 *==================================================================*/

/*===================================================================
 *                     Include Files
 ====================================================================*/

#include "flashi_hal_nandc_predef_bam.h"

#if defined(FLASH_ENABLE_PAGESCOPE)

/* Variable to enable/disable the pagescope feature runtime */
boolean flash_qpic_pagescope_enabled = TRUE;

/*
 * Does the post processing for pagescope read.
 */
void hal_nandc_bam_00_30_x1_pagescope_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status *status)
{
  int32 cw_count, erase_cw_count = 0;
  uint32 status_val = 0, mask = FLASH_NANDC_STATUS_MASK;
  volatile uint32 status_buff[2] = {0};
  uintnt *status_buffer;//, *erased_cw_det_status_buffer;
  volatile uintnt status_var = 0,erased_cw_det_status_var = 0;//,flag = 0;
  struct nandc_predef_reg_read_buff *reg_read_buff;
  uint32 erase_cw_mask = FLASH_NANDC_ERASED_CW_DET_STATUS_MASK;
  uint32 erase_cw_status = FLASH_ERASED_CW_DETECT_STATUS;

  *status = FLASH_HAL_SUCCESS;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;

  //TODO Fix the address corrections

  status_buffer = (uintnt *)(uintnt) reg_read_buff->multipage_status_buffer;

  //status_buff[0] = (uint32)*status_buffer;
  //status_buff[1] = (uint32)((*status_buffer & 0xFFFFFFFF00000000) >> 32);
 
  cw_count = priv_data->cw_cnt - 1;

  /* For each page,
   - Check for status bytes
   - Check for Erase page
   - Check for ECC bytes
   - Check for Spare Udata bytes (if applicable)
   - Check for Erased CW detect status register
  */

  while (cw_count >= 0)
  {
    status_buff[0] = (uint32)*status_buffer;
    status_buff[1] = (uint32)((*status_buffer & 0xFFFFFFFF00000000) >> 32);

    /* Check for flash status bytes */
    status_val = (cw_count << FLASH_NAND_STATUS_CW_CNTR_SHFT) |
     FLASH_NAND_STATUS_OP_DONE;

	if(IS_AARCH_64)
	{
		status_var = (uint32) (status_buff[0]);
		erased_cw_det_status_var = (uint32) (status_buff[1]);
	}
	else /* Changes for 32 bit : Girjesh*/
	{
		status_var = *status_buffer;
		erased_cw_det_status_var = *(status_buffer + 1);
	}

    /* If there is an error, look for erased page */
    if ((status_var & mask) != status_val)
    {
      if (FLASH_NAND_STATUS_MPU_ERROR_MASK ==
       (status_var & (FLASH_NAND_STATUS_MPU_ERROR_MASK & mask)))
      {
        *status = FLASH_HAL_FAIL_MPU_ERR;
        break;
      }

      if((erased_cw_det_status_var & erase_cw_mask) == erase_cw_status) 
      {
        *status = FLASH_HAL_ERASED_PAGE;
		erase_cw_count++;
      }
      else
      {
        *status = FLASH_HAL_CHECK_ECC;
		break;
      }
    }
 
    memset((void *)status_buffer, 0x0, sizeof(uint32));
       
	if(IS_AARCH_64)
	{
		status_buffer +=  NO_STATUS_BUFFER_ENABLED-1;
	}
	else /* Changes for 32 bit : Girjesh*/
	{
		status_buffer +=  NO_STATUS_BUFFER_ENABLED;
	}

    cw_count--;
  }

  if (erase_cw_count == priv_data->cw_cnt)
  {
   *status = FLASH_HAL_ERASED_PAGE;
  }
}

/* Single read: Pagescope.
 *
 * Note: Please make sure that you pass enough memory to this
 *       API. We are determining the memory used only at the
 *       end of this function. This may lead to memory corruption.
 */

enum flash_hal_status hal_nandc_bam_00_30_x1_pagescope_init(
  struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_init_data *init_data,
  struct flash_hal_mem_data *mem_data, uintnt *used_buff_size)
{
	  uintnt buff_vaddr = 0;
	  uintnt buff_paddr = 0;
	  struct nandc_predef_cmd_list *cmd_list;
	  struct nandc_predef_cmdptr_mem_data *cmdptr_mem_data;
	  struct flash_hal_predef_op_list *op_list;
	  struct flash_hal_op_desc	*cmd_desc_vaddr_ptr;
	
	  cmd_list = &nandc_predef_bam_data.cmd_list;
	  cmdptr_mem_data =
		&nandc_predef_bam_data.mem_info.cmd_ptr[NANDC_00_30_x1_READ];
	  op_list = &nandc_predef_bam_data.cmd_ptr_list[NANDC_00_30_x1_READ];
	
	  /* Flash HAL creates a list which is BAM friendly. ie,
		 All the buffers and addresses in the pre-allocated list
		 will be with physical addresses. And all the command
		 pointer list and command list are aligned to 32 byte
		 boundary. Please note that the command pointer list
		 is virtual. */
	
	  /* Get a 32 byte aligned buffer for the command pointer list */
	
	  buff_paddr = mem_data->buff_paddr;
	  buff_paddr = FLASH_ALIGN_32(buff_paddr);
	
	  buff_vaddr = mem_data->buff_vaddr;
	  buff_vaddr = FLASH_ALIGN_32(buff_vaddr);
	
	  cmdptr_mem_data->mem_data.buff_vaddr = buff_vaddr;
	  cmdptr_mem_data->mem_data.buff_paddr = buff_paddr;
	  cmdptr_mem_data->seq_id = NANDC_00_30_x1_READ;
	
	  cmd_desc_vaddr_ptr = (struct flash_hal_op_desc *)buff_vaddr;
	
	  /*--------------------------------------------------------------
	   |  The command pointer list for read is have the following
	   |  format,
	   |
	   |  - config (cfg0/cfg1/ecc buf/cs/erased cw det cfg) + Lock Pipe
	   |  - Set Auto Status enable
	   |  - Set Locate Registers
	   |  - Exec + unlock
	   *-------------------------------------------------------------*/
	  
	  /* Lock Pipe and Set config registers */
	  cmd_desc_vaddr_ptr->buf_pa = GET_PHYS_ADDR(&cmd_list->cfg_list[0]);
	  cmd_desc_vaddr_ptr->buf_size = sizeof(struct flash_hal_op_cmd) * 
		(nandc_predef_bam_data.reg_count.total_nandc_config_list_registers-2); /* Do not include the exec command.*/ 
	  cmd_desc_vaddr_ptr->flags = FLASH_BAM_DESC_FLAG_CMD | FLASH_BAM_DESC_FLAG_LCK;
	  cmd_desc_vaddr_ptr++;
      
	  /* Pagescope*/
	  cmd_desc_vaddr_ptr->buf_pa = GET_PHYS_ADDR(&cmd_list->auto_status_list[0]);
	  cmd_desc_vaddr_ptr->buf_size = sizeof(struct flash_hal_op_cmd) ;
	  cmd_desc_vaddr_ptr->flags = FLASH_BAM_DESC_FLAG_CMD;
	  cmd_desc_vaddr_ptr++;
	
	  /* Configure Locate Register for Data Read and set cmd - exec registers */
	  cmd_desc_vaddr_ptr->buf_pa = GET_PHYS_ADDR(&cmd_list->locate_list[3]);
	  cmd_desc_vaddr_ptr->buf_size = sizeof(struct flash_hal_op_cmd) * 3; 
	  cmd_desc_vaddr_ptr->flags = FLASH_BAM_DESC_FLAG_CMD | FLASH_BAM_DESC_FLAG_NWD;
	  cmd_desc_vaddr_ptr++;

	  /* Clear the auto status and unlock the pipe */
 	 cmd_desc_vaddr_ptr->buf_pa = GET_PHYS_ADDR(&cmd_list->auto_status_list[1]);
     cmd_desc_vaddr_ptr->buf_size = sizeof(struct flash_hal_op_cmd) ; 
  	 cmd_desc_vaddr_ptr->flags = FLASH_BAM_DESC_FLAG_CMD | 
  		FLASH_BAM_DESC_FLAG_UNLCK | FLASH_BAM_DESC_FLAG_INT ;
  cmd_desc_vaddr_ptr++;
		 
	  /* Get the memory use and store it */
	  *used_buff_size = (uintnt)cmd_desc_vaddr_ptr - mem_data->buff_vaddr;
	  cmdptr_mem_data->mem_data.buff_size = *used_buff_size;
	
	  /* Initialize the BAM list for read */
	  op_list->op_list = (uintnt *)(uintnt) cmdptr_mem_data->mem_data.buff_paddr;
	  op_list->op_list_count = ((uintnt)cmd_desc_vaddr_ptr - buff_vaddr) /
		sizeof(struct flash_hal_op_desc);
	  op_list->seq_id = NANDC_00_30_x1_READ;
	  op_list->prev_op_count = 1;
		
	  /* If memory used is more than given, return failure. */
	  return ((*used_buff_size > mem_data->buff_size) ?
		FLASH_HAL_NO_MEM_ERROR : FLASH_HAL_SUCCESS);

}

/* Enable the pagescope feature bit in the registers */
static void nandc_set_ps_mode()
{
  
  struct flash_hal_op_cmd *op_cmd  = NULL;

  op_cmd	= &nandc_predef_bam_data.cmd_list.locate_list[4];  

  /* Added here to enable pagescope */
  op_cmd->data = op_cmd->data | HWIO_NAND_FLASH_CMD_PAGE_SCOPE_CMD_BMSK ;
	
}

/*
 * Prepare the exec descriptors for pagescope read.
 */
void hal_nandc_bam_00_30_x1_pagescope_exec(flash_hal_dev_info *dev_info,
	  struct flash_hal_predef_page_data *page_data,
	  struct flash_hal_predef_op_list **op_list, enum flash_hal_status *status)
{
  
	uint32 cmd = 0, cw_count = 0;
	struct flash_hal_page_layout *page_layout;
	struct flash_hal_ctlr_data *priv_data;
	struct flash_hal_op_cmd *op_cmd;
	uintnt addr0, addr1;
	uintnt num_read_desc = 0;
	struct flash_bam_xfer_desc_list tx_cmd_list;
	struct flash_bam_xfer_desc_list tx_read_list;
	struct flash_bam_xfer_desc_list tx_status_list;
	struct flash_hal_predef_op_list *cmd_op_list;
	
	int result;
  
	*status = FLASH_HAL_SUCCESS;
	priv_data = &dev_info->config;
  
	if (1 != page_data->total_pages)
	{
	  *status = FLASH_HAL_FAIL;
	  return;
	}
  
	cmd_op_list = &nandc_predef_bam_data.cmd_ptr_list[NANDC_00_30_x1_READ];
	dev_info->ctlr_ops.flash_hal_configure(priv_data, status);
  
	/* Get page layout */
	dev_info->ctlr_ops.flash_hal_get_page_layout(priv_data, &page_layout);
  
	/* Set address bytes */
	op_cmd = &nandc_predef_bam_data.cmd_list.cfg_list[nandc_predef_bam_data.
	  index_list.nandc_bam_raddr0_cfg_cmd_list];
	//addr0 = (uintnt *)(uintnt) &(op_cmd->data);
	//op_cmd++;
	//addr1 = (uintnt *)(uintnt) &(op_cmd->data);
  
	//hal_nandc_bam_set_addr(priv_data, page_data->start_page, addr0, addr1, 1);
  
	//addr0 = (uintnt *)&(op_cmd->data);
	//op_cmd++;
	//addr1 = (uintnt *)&(op_cmd->data);

	hal_nandc_bam_set_addr(priv_data, page_data->start_page, &addr0, &addr1, 1);

	op_cmd->data = (uint32) addr0;
	op_cmd++;
	op_cmd->data = (uint32) addr1;

	/*---- Set config registers -----*/
	cw_count = priv_data->cw_cnt - 1;
  
	/* Set the codeword count */
	FLASH_CW_PER_PAGE(priv_data, cw_count);
  
	/* Set the number of address cycles */
	FLASH_NUM_ADDR_CYCLES(priv_data, (priv_data->row_count +
	  priv_data->col_count));
  
	hal_nandc_bam_set_cfg(priv_data);
  
	/* Set command registers */
	cmd = (priv_data->ecc_state == FLASH_HAL_HW_ECC_ON_MAIN_AND_SPARE)?
	  FLASH_NAND_PAGE_READ_ECC_CMD:FLASH_NAND_PAGE_READ_ALL_CMD;
  
	hal_nandc_bam_set_cmd(cmd, NANDC_PAGE_READ_CMD, priv_data);

	/* Set the pagescope feature bit */
	nandc_set_ps_mode();
  
	/* Configure buffer pointers */
	hal_nandc_bam_set_read_buffers(page_data, page_layout, 
	  nandc_predef_bam_data.desc.read_copy_desc, priv_data, &num_read_desc);
  
	/* Command descriptor list */
	tx_cmd_list.desc_list_ptr = (bam_iovec_type *)cmd_op_list->op_list;
	tx_cmd_list.desc_count = cmd_op_list->op_list_count;
	
	/* Data Descriptor list */
	tx_read_list.desc_list_ptr = (bam_iovec_type *)
	  nandc_predef_bam_data.desc.read_copy_desc;
	tx_read_list.desc_count = num_read_desc;

	/* Status descriptor list */
	tx_status_list.desc_list_ptr = (bam_iovec_type *)
	  nandc_predef_bam_data.desc.auto_status_desc;
	tx_status_list.desc_count = priv_data->cw_cnt; 
  
	result = hal_nandc_bam_exec_op(&tx_cmd_list, &tx_read_list, NULL, &tx_status_list);
  
	if (result != FLASH_BAM_SUCCESS)
	{
	  *status = FLASH_HAL_FAIL;
	}
	else
	{
	  hal_nandc_bam_00_30_x1_pagescope_pprocess(priv_data, cmd_op_list, status);
	}
  
  
}
#else
  boolean flash_qpic_pagescope_enabled = FALSE;
#endif
