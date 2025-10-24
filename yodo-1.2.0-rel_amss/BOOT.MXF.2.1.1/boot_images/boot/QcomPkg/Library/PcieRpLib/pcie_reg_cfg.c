/**
 *
 *  Implements the Pcie Register configuration utility
*/
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created new

===============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "pcie_cfg_types.h"
#include "pcie_reg_cfg.h"
#include "pcie_host_log.h"
#include <Library/IoLib.h>

pcie_status_t apply_reg_write_seq (const pcie_reg_write_val_t* reg_wr_seq, void* base_addr)
{
   volatile uint32* reg_addr;
   uint32 val;

   if ((reg_wr_seq == NULL) || (base_addr == NULL))
      return PCIE_ERROR;

   while (reg_wr_seq->offset != PCIE_REG_OP_STOP)
   {
      reg_addr = base_addr + reg_wr_seq->offset;
      val = reg_wr_seq->val;

      *reg_addr = val;   // MmioWrite32

      ++reg_wr_seq;
   }

   return PCIE_SUCCESS;
}

BOOLEAN pcie_poll_field_val (uint64 addr, uint32 mask, uint32 match_val, uint32 poll_us, uint32 timeout_ms)
{
   uint32 loop_cnt = timeout_ms * 1000;
   uint32 reg_field;
   uint32 shift = __builtin_ctz((mask));

   loop_cnt /= poll_us;
   if (loop_cnt == 0)
      ++loop_cnt;

   while (loop_cnt > 0)
   {
      reg_field = MmioRead32 (addr);
      reg_field = (reg_field & (mask)) >> shift;
     
      if (reg_field == match_val)
         return TRUE;
     
      pcie_osal_busywait_us (poll_us);
     
      loop_cnt--;
   }

   return FALSE;
}

/* Base addr here should be VA */
pcie_status_t apply_reg_init_seq (const pcie_reg_op_t* reg_seq, void* base_addr)
{
   volatile uint32* reg_addr;
   pcie_status_t result = PCIE_SUCCESS;
   uint32 temp, val;

   if ((reg_seq == NULL) || (base_addr == NULL))
      return PCIE_ERROR;

   while (reg_seq->opflag != PCIE_REG_OP_STOP)
   {
      reg_addr = base_addr + reg_seq->offset;
      val = reg_seq->val;

      switch (reg_seq->opflag)
      {
         case PCIE_REG_OP_WRITE:
            PCIE_HOST_LOG_LOW ("WR  0x%X %X\r\n", reg_addr, val);
            *reg_addr = val;
            break;

         case PCIE_REG_OP_RMW:
            temp = *reg_addr;
            PCIE_HOST_LOG_LOW ("RMW  0x%X %X => %X\r\n", reg_addr, temp, val);
            temp = temp & (~(reg_seq->mask));
            temp = temp | (val);
            *reg_addr = temp;
            break;

         case PCIE_REG_OP_DELAY:
            pcie_osal_busywait_us (val);
            break;

         case PCIE_REG_OP_DSB:
            pcie_osal_memory_barrier ();
            break;

         case PCIE_REG_OP_SET_GPIO:
            pcie_drive_gpio_pin (reg_seq->offset, val);
            break;

         case PCIE_REG_OP_POLL:
            {
               uint32 mask = reg_seq->mask;

#define POLL_US_1_ms        1000
#define TIMEOUT_MS_100_ms    100

               if (pcie_poll_field_val ((uint64)reg_addr, mask, val, POLL_US_1_ms, TIMEOUT_MS_100_ms))
                  result = PCIE_SUCCESS;
               else
               {
                  uint32 rval = *reg_addr;
                  (void)rval;
                  PCIE_HOST_LOG_ERROR ("Poll Result Failed 0x%X %X %X\n", reg_addr, rval, mask);
                  result = PCIE_ERROR;
               }
            }
            break;

         case PCIE_REG_OP_STOP:
         case PCIE_REG_OP_NOP:
         default:
            break;
      }

      /* TODO: Should we break here if poll result failed? If poll
       * is in the middle of the sequences and/or if multiple polls
       * are in the sequences then we need to exit on failure */
      ++reg_seq;
   }

   return result;
}

pcie_status_t apply_reg_init_cfg (const pcie_reg_init_cfg_t* reg_cfg_spec, const mem_region_t* mem_rgn)
{
   const pcie_reg_init_cfg_t* reg_init_seq;
   uint32 chip_ver = 0x10000;  // TODO: get it from chipinfo
   uint64_t va;
   const pcie_reg_op_t *reg_op_seq;
   const pcie_reg_write_val_t *reg_write_cfg;

   if ((reg_cfg_spec == NULL) || (mem_rgn == NULL))
      return PCIE_ERROR;

   reg_init_seq = reg_cfg_spec;
   for (;reg_init_seq->version != PcieSeq_Stop; ++reg_init_seq)
   {
      if (chip_ver < reg_init_seq->version)
         continue;

      /* TODO: Optimize this by storing VA mem region in the context */
      va = OSAL_CONVERT_PA_TO_VA(mem_rgn[reg_init_seq->mem_rgn_idx].pa);

      switch (reg_init_seq->seq_type)
      {
         case PCIE_REG_WRITE_SEQ:
            reg_write_cfg = reg_init_seq->seq_spec.reg_write_val_seq;
            if (reg_write_cfg == NULL)
               break;

            if (apply_reg_write_seq (reg_write_cfg, (void*)va) != PCIE_SUCCESS)
            {
               PCIE_HOST_LOG_ERROR ("Reg seq programming failed\n");
               return PCIE_ERROR;
            }
            break;

         case PCIE_REG_OP_SEQ:
            reg_op_seq = reg_init_seq->seq_spec.reg_op_seq;
            if (reg_op_seq == NULL)
               break;

            if (apply_reg_init_seq (reg_op_seq, (void*)va) != PCIE_SUCCESS)
            {
               PCIE_HOST_LOG_ERROR ("Reg seq programming failed\n");
               return PCIE_ERROR;
            }
            break;

         default:
            PCIE_HOST_LOG_ERROR ("Unsupported reg init seqence\n");
      }
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_drive_gpio_pin (uint32 pin, uint32 val)
{
   if (pin == 0)
   {
      PCIE_HOST_LOG_ERROR ("Invalid PERST pin config..!!\n");
      return PCIE_ERROR;
   }

   if (pcie_osal_gpio_set (pin, val) != EFI_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("PERST set failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}


