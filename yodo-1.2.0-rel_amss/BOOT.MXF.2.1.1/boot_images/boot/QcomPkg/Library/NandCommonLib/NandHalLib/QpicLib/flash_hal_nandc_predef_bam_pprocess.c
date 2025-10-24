/*====================================================================
 *
 * FILE:        flash_hal_nandc_predef_bam_pprocess.c
 *
 * SERVICES:    Postprocess APIs for predefined bam support in QPIC
 *              nandc HAL
 *
 * DESCRIPTION: The perdefined BAM support in flash HAL is to improve
 *              throughput with pre-allocated BAM lists.
 *
 *
 * PUBLIC CLASSES AND STATIC FUNCTIONS:
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:
 *
 * Copyright (c) 2012, 2015, 2020, 2022 Qualcomm Technologies, Inc. All Rights Reserved
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NandCommonLib/NandHalLib/QpicLib/flash_hal_nandc_predef_bam_pprocess.c#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 30/06/22     gml     Added hack to perform erase even if ecc is enabled
 * 07/20/20     sa      Ported changes for Xfer steps.
 * 06/08/20     sa      Ported for Olympic.
 * 11/12/15     sb      ECC bit flip check support
 * 08/03/15     sb      Enhance ONFI param page read to read multiple copies
 * 11/06/12     sv      Update Flash Status check
 * 09/04/12     sv      Initial Revision
 *===================================================================*/

#include "flashi_hal_nandc_predef_bam.h"

/*
 * Routine to check common errors in status buffer
 */
static void hal_nandc_bam_check_status_error(uintnt *status_buffer,
  uint32 num_status, enum flash_hal_status *status)
{
  uint64 status_val[2];
  uint32 mask = FLASH_NANDC_STATUS_MASK;
  uintnt *status_ptr;
  
  if (IS_AARCH_64)
  {
	  status_val[0] = (*status_buffer & 0xFFFFFFFF);
	  status_val[1] = (*status_buffer >> 32);
	  status_ptr = (uintnt *)status_val; 
  }
  else
  {
	  status_ptr = (uintnt *)status_buffer;
  }

  *status = FLASH_HAL_SUCCESS;

  while ((num_status) && (FLASH_HAL_SUCCESS == *status))
  {
    /* Check for status bytes */
    if ((*status_ptr & mask) != FLASH_NAND_STATUS_OP_DONE)
    {
      if (FLASH_NAND_STATUS_MPU_ERROR_MASK ==
        (*status_ptr & (FLASH_NAND_STATUS_MPU_ERROR_MASK & mask)))
      {
        *status = FLASH_HAL_FAIL_MPU_ERR;
      }
      else
      {
        *status = FLASH_HAL_FAIL;
      }

      break;
    }

    num_status--;
    status_ptr++;
  }
}

/*
 * This API does the post processing check for an erased page.
 */
static void hal_nandc_bam_erased_page_pprocess(
  struct flash_hal_ctlr_data *priv_data, uintnt *ecc_read_buff,
  uintnt *erased_cw_det_status_buff, enum flash_hal_status *status)
{
  *status = FLASH_HAL_FAIL;

  if ((*erased_cw_det_status_buff & 
       FLASH_NANDC_ERASED_CW_DET_STATUS_MASK) ==
       FLASH_ERASED_CW_DETECT_STATUS)
  {
    *status = FLASH_HAL_ERASED_PAGE;
  }
  else
  {
    *status = FLASH_HAL_CHECK_ECC;
  }
}

/*
 * Does the post processing for single read.
 */
void hal_nandc_bam_00_30_x1_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status *status)
{
  int32 cw_count, erase_cw_count = 0;
  uint32 status_val = 0, mask = FLASH_NANDC_STATUS_MASK;
  uintnt status_var = 0,erased_cw_det_status_var = 0,flag = 0;
  uintnt *status_buffer, *erased_cw_det_status_buffer;
  struct nandc_predef_reg_read_buff *reg_read_buff;
  enum flash_hal_status tmp_status = FLASH_HAL_SUCCESS;

  *status = FLASH_HAL_SUCCESS;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;

  status_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  erased_cw_det_status_buffer = (uintnt *)(uintnt)reg_read_buff->erased_cw_det_status_buffer;



  /* For each page,
       - Check for status bytes
       - Check for Erase page
          - Check for ECC bytes
          - Check for Spare Udata bytes (if applicable)
          - Check for Erased CW detect status register
  */
  cw_count = priv_data->cw_cnt - 1;

  while (cw_count >= 0)
  {
    
    /* Check for status bytes */
    status_val = (cw_count << FLASH_NAND_STATUS_CW_CNTR_SHFT) |
      FLASH_NAND_STATUS_OP_DONE;
	if (IS_AARCH_64)
	{
		 if (flag == 0)
	    {
	        status_var = (uint32) (*status_buffer & (0xFFFFFFFF));
	        erased_cw_det_status_var = (uint32) (*erased_cw_det_status_buffer & (0xFFFFFFFF));
	        flag = 1;
	    }
	    else
	    {
	        status_var = (uint32) ((*status_buffer & (0xFFFFFFFF00000000)) >> 32);
	        erased_cw_det_status_var = (uint32) ((*erased_cw_det_status_buffer & (0xFFFFFFFF00000000)) >> 32);
	        flag = 0;
	    }
		
	}
	else  //Code changes to support 32 Bit compilation
	{
		status_var = *status_buffer;
		erased_cw_det_status_var = *erased_cw_det_status_buffer;
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
      else if(((status_var & mask) >> FLASH_NAND_STATUS_CW_CNTR_SHFT) != cw_count)
      {
        *status = FLASH_HAL_CW_MISMATCH_ERR;
        break;
      }

      /* Look for Erased page, if it is not an erased page then flag it as a real failure 
       * currently we are checking for each CW. Update to use page erased status bit 
       */
      hal_nandc_bam_erased_page_pprocess(priv_data, NULL,
        &erased_cw_det_status_var, &tmp_status);

      if (FLASH_HAL_ERASED_PAGE == tmp_status)
      {
        erase_cw_count++;
      }
      else if (FLASH_HAL_CHECK_ECC == tmp_status)
      {
        //TODO Hack to skip checking of ECC need to be fixed
        //*status = FLASH_HAL_CHECK_ECC;
        *status = FLASH_HAL_ERASED_PAGE;
        break;
      }
      else if (FLASH_HAL_FAIL == tmp_status)
      {
        *status = FLASH_HAL_FAIL;
        break;
      }
    }

    if (flag == 0)
    {
        status_buffer++;
        erased_cw_det_status_buffer++;
    }
    cw_count--;
  }
  if (erase_cw_count == priv_data->cw_cnt)
  {
    *status = FLASH_HAL_ERASED_PAGE;
  }
}


/*
 * Does the post processing for single erase.
 */
void hal_nandc_bam_60_D0_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  uintnt *status_buffer,  block_count = 0;
  struct nandc_predef_reg_read_buff *reg_read_buff;
  uint32  mask = FLASH_NANDC_STATUS_MASK;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  status_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;
  block_count = op_list->prev_op_count;

  while (block_count) 
  {
    /* Check for status bytes */
    if ((*status_buffer & mask) != FLASH_NAND_STATUS_OP_DONE)
    {
      if (FLASH_NAND_STATUS_MPU_ERROR_MASK ==
        (*status_buffer & (FLASH_NAND_STATUS_MPU_ERROR_MASK & mask)))
      {
        *status = FLASH_HAL_FAIL_MPU_ERR;
      }
      else
      {
        *status = FLASH_HAL_FAIL;
      }

      break;
    }

    block_count--;
    status_buffer++;
  }
}

/*
 * Does the post processing for single write.
 */
void hal_nandc_bam_80_10_x1_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  int32 cw_count = 0;
  uint32 status_val = 0,flag=0;
  uint32 status_tmp = 0;
  uintnt *status_buffer = NULL;
  uint32  mask = FLASH_NANDC_STATUS_MASK;
  struct nandc_predef_reg_read_buff *reg_read_buff;

  *status = FLASH_HAL_SUCCESS;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;

  status_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  /* For each page, Check for status bytes */
  cw_count = priv_data->cw_cnt - 1;

  while (cw_count >= 0)
  {
    /* Check for status bytes */

	if (IS_AARCH_64)
	{
		if (flag == 0)
	    {
	        status_tmp = (uint32)(*status_buffer & 0xFFFFFFFF);
	        flag = 1;
	    }
	    else
	    {
	        status_tmp = (uint32)((*status_buffer & 0xFFFFFFFF00000000) >> 32);
	        flag = 0;
	    }
	
	}
	else
	{
		status_tmp = (*status_buffer);
	}
	
    status_val = (cw_count << FLASH_NAND_STATUS_CW_CNTR_SHFT) |
      FLASH_NAND_STATUS_OP_DONE;

    /* If there is an error, look for MPU error */
    if ((status_tmp & mask) != status_val)
    {
      if (FLASH_NAND_STATUS_MPU_ERROR_MASK ==
        (status_tmp & (FLASH_NAND_STATUS_MPU_ERROR_MASK & mask)))
      {
        *status = FLASH_HAL_FAIL_MPU_ERR;
      }
      else if(((status_tmp & mask) >> FLASH_NAND_STATUS_CW_CNTR_SHFT) != cw_count)
      {
        *status = FLASH_HAL_CW_MISMATCH_ERR;
      }
      else
      {
        *status = FLASH_HAL_FAIL;
      }

      break;
    }
    else if ((cw_count == 0) && 
      ((status_tmp & FLASH_NAND_DEV_STATUS_WP_MASK) ==
      FLASH_NAND_DEV_STATUS_WP_ENABLED))
    {
      /* The check for WP bits after last Code Word write shows that 
       * Write Protect is enabled. The check is made only on the 
       * last code word because the device status is read only 
       * after the last code word write */
      *status = FLASH_HAL_WP_ENABLED;
    }

    if (flag == 0)
    {
        status_buffer++;
    }
    cw_count--;
  }
}

/*
 * Does the post processing for read bad block marker.
 */
void hal_nandc_bam_00_30_bb_marker_pprocess(
  struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  uintnt *status_buffer;
  struct nandc_predef_reg_read_buff *reg_read_buff;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  status_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  hal_nandc_bam_check_status_error(status_buffer, 1, status);

}

/*
 * Does the post processing for probe.
 */
void hal_nandc_bam_FF_90_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  uintnt *tmp_buffer;
  struct nandc_predef_reg_read_buff *reg_read_buff;
 
  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  tmp_buffer = (uintnt *)(uintnt)reg_read_buff->status_buffer;

  hal_nandc_bam_check_status_error(tmp_buffer, 2, status);
}

/*
 * Does the post processing for ONFI ID read.
 */
void hal_nandc_bam_90_onfi_id_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  uintnt *tmp_buffer;
  struct nandc_predef_reg_read_buff *reg_read_buff;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  tmp_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  hal_nandc_bam_check_status_error(tmp_buffer, 1, status);

}

/*
 * Does the post processing for read parameter page.
 */
void hal_nandc_bam_00_EC_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  int32 cw_count = 0;
  uint32 status_val = 0;
  uintnt *status_buffer;
  uint32  mask = FLASH_NANDC_STATUS_MASK;
  struct nandc_predef_reg_read_buff *reg_read_buff;

  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  status_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  cw_count = priv_data->cw_cnt - 1;

  while (cw_count >= 0)
  {
    /* Check for status bytes */
    status_val = (cw_count << FLASH_NAND_STATUS_CW_CNTR_SHFT) |
      FLASH_NAND_STATUS_OP_DONE;

    if ((*status_buffer & mask) != status_val)
    {
      if (FLASH_NAND_STATUS_MPU_ERROR_MASK ==
        (*status_buffer & (FLASH_NAND_STATUS_MPU_ERROR_MASK & mask)))
      {
        *status = FLASH_HAL_FAIL_MPU_ERR;
      }
      else
      {
        *status = FLASH_HAL_FAIL;
      }
      break;
    }
    status_buffer++;
    cw_count--;
  }
}

/*
 * Does the post processing for feature cmd.
 */
void hal_nandc_bam_EF_EE_pprocess(struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_op_list *op_list, enum flash_hal_status  *status)
{
  uintnt *tmp_buffer;
  struct nandc_predef_reg_read_buff *reg_read_buff;
 
  reg_read_buff = &nandc_predef_bam_data.reg_read_buff;
  tmp_buffer = (uintnt *)(uintnt) reg_read_buff->status_buffer;

  hal_nandc_bam_check_status_error(tmp_buffer, 1, status);
}

