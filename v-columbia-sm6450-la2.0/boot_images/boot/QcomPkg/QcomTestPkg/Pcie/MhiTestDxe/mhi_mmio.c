/**
 *  @file mhi_device.c
 *
 *  @brief This file contains the device-level MHI implementation.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_mmio.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function gets the MHI version.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va  BAR virtual address
 * @param[out] ver     Version
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_get_ver(uintptr_t bar_va, uint32 *ver)
{
   uint32 val = MMIO_INX(bar_va, MHIVER_OFFSET);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *ver = val;

   return SUCCESS;
}

/**
 * This function gets the channel doorbell base virtual address.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va  BAR virtual address
 * @param[out] va      Doorbell base virtual address
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_get_ch_db_base_addr(mhi_va_t bar_va, mhi_va_t *va)
{
   uintptr_t offset;

   offset = MMIO_INX(bar_va, CHDBOFF_OFFSET);
   if (offset == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *va = bar_va + offset;

   return SUCCESS;
}

/**
 * This function gets the event ring doorbell base virtual address.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va  BAR virtual address
 * @param[out] va      Doorbell base virtual address
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_get_er_db_base_addr(mhi_va_t bar_va, mhi_va_t *va)
{
   uintptr_t offset;

   offset = MMIO_INX(bar_va, ERDBOFF);
   if (offset == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *va = bar_va + offset;

   return SUCCESS;
}

/**
 * This function gets the channel doorbell virtual address.
 *
 * @param[in]  base   Channel doorbell base virtual address
 * @param[in]  ch_id  Channel ID
 *
 * @return Doorbell virtual address
 */
mhi_va_t mhi_mmio_get_ch_db_addr(mhi_va_t base, uint32 ch_id)
{
   return base + CHDB_OFFSET(ch_id);
}

/**
 * This function gets the event ring doorbell virtual address.
 *
 * @param[in]  base   Event ring doorbell base virtual address
 * @param[in]  er_id  Event ring ID
 *
 * @return Doorbell virtual address
 */
mhi_va_t mhi_mmio_get_er_db_addr(mhi_va_t base, uint32 er_id)
{
   return base + ERDB_OFFSET(er_id);
}

/**
 * This function rings a doorbell.
 *
 * @attention The link must be on
 *
 * @param[in]  db_va  Doorbell virtual address
 * @param[in]  wp     Write pointer
 *
 * @return None
 */
void mhi_mmio_ring_db(uintptr_t db_va, uint64 wp)
{
   MMIO_OUTX(db_va, DB_HIGH_OFFSET, U64_UPPER(wp));
   MMIO_OUTX(db_va, DB_LOW_OFFSET, U64_LOWER(wp));
}

/**
 * This function sets BHI image address, which must be 4K aligned.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  addr     Image address
 *
 * @return None
 */
void mhi_mmio_bhi_set_addr(uintptr_t bar_va, uint64 addr)
{
   MMIO_OUTX(bar_va, BHI_IMGADDR_OFFSET, U64_LOWER(addr));

   MMIO_OUTX(bar_va, BHI_IMGADDR_OFFSET + 4, U64_UPPER(addr));
}

/**
 * This function sets BHI image size.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  size     Image size in bytes
 *
 * @return None
 */
void mhi_mmio_bhi_set_size(uintptr_t bar_va, uint32 size)
{
   MMIO_OUTX(bar_va, BHI_IMGSIZE_OFFSET, U64_LOWER(size));
}

/**
 * This function rings the BHI doorbell.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  val      Doorbell value
 *
 * @return None
 */
void mhi_mmio_bhi_ring_db(uintptr_t bar_va, uint32 val)
{
   MMIO_OUTX(bar_va, BHI_IMGTXDB_OFFSET, val);
}

/**
 * This function rings the Device wake doorbell.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  val      Doorbell value
 *
 * @return None
 */
void mhi_mmio_device_wake_db(uintptr_t bar_va, uint32 val)
{
   MMIO_OUTX(bar_va, DEVICE_WAKE_OFFSET, val);
}

/**
 * This function rings the Device reset doorbell.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  val      Doorbell value
 *
 * @return None
 */
void mhi_mmio_device_reset_db(uintptr_t bar_va, uint32 val)
{
   MMIO_OUTX(bar_va, DEVICE_RESET_OFFSET, val);
}

/**
 * This function gets the BHI status.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[out] status   BHI status
 * @param[out] seq_num  Corresponding sequence number
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_bhi_get_status(uintptr_t bar_va, bhi_status_t *status, uint32 *seq_num)
{
   uint32 val = MMIO_INX(bar_va, BHI_STATUS_OFFSET);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *seq_num = (val & BHI_STATUS_SEQNUM_MASK) >> BHI_STATUS_SEQNUM_SHIFT;
   *status = (bhi_status_t)((val & BHI_STATUS_STATUS_MASK) >> BHI_STATUS_STATUS_SHIFT);

   return SUCCESS;
}

/**
 * This function gets the current execution environment of the device.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[out] rdata    read data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_bhi_get_exe_ee(uintptr_t bar_va, uint32 *rdata)
{
   uint32 val = MMIO_INX(bar_va, BHI_EXECENV_OFFSET);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *rdata = val;

   return SUCCESS;
}

/**
 * This function gets the current execution environment of the device.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[out] rdata    read data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_get_dev_state(uintptr_t bar_va, uint32 *rdata)
{
   uint32 val = MMIO_INX(bar_va, MHISTATUS_OFFSET);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *rdata = val;

   return SUCCESS;
}

/**
 * This function gets the current execution environment of the device.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[out] rdata    read data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_set_dev_state(uintptr_t bar_va, uint32 rdata)
{
   uint32 val = MMIO_INX(bar_va, MHICTRL_OFFSET);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   val &= ~MHICTRL_MHISTATE_MASK;
   rdata = (rdata << MHICTRL_MHISTATE_SHIFT) & MHICTRL_MHISTATE_MASK;

   MMIO_OUTX(bar_va, MHICTRL_OFFSET, rdata | val);

   return SUCCESS;
}

/**
 * This function sets BHI interrupt vector number.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  vector   BHI MSI Int vec number
 *
 * @return None
 */
void mhi_mmio_bhi_set_int_vec(uintptr_t bar_va, uint32 vector)
{
   MMIO_OUTX(bar_va, BHI_INTVEC_OFFSET, vector);
}

/**
 * This function is used of mhi mmio read
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  offset   Register offset in MHI space
 * @param[out] rdata    read data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_read(uintptr_t bar_va, uint32 offset, uint32 *rdata)
{
   uint32 val = MMIO_INX(bar_va, offset);

   if (val == MHI_MMIO_INVALID_VAL)
   {
      return SYSERR;
   }

   *rdata = val;

   return SUCCESS;
}

int32 mhi_mmio_read_reg_field(uintptr_t bar_va, uint32 offset, uint32 mask, uint32 shift, uint32 *rdata)
{
   uintnt addr = bar_va + offset;
   uint32 regval = (*((volatile uint32 *)(addr)));

   regval &= mask;
   regval >>= shift;
   *rdata = regval;

   return SUCCESS;
}

/**
 * This function is used of mhi mmio write
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  offset   Register offset in MHI space
 * @param[in]  wdata    write data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_write(uintptr_t bar_va, uint32 offset, uint32 wdata)
{
   MMIO_OUTX(bar_va, offset, wdata);

   return SUCCESS;
}

/**
 * This function is used to write to a specific MHI register field.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va     BAR virtual address
 * @param[in]  offset     Register offset in MHI space
 * @param[in]  mask       Mask associated with the field
 * @param[in]  shift      Shift position of the field
 * @param[in]  field_val  Field value to write
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_write_reg_field (uintptr_t bar_va, uint32 offset, uint32 mask, uint32 shift, uint32 field_val)
{
   uint32 regval = MMIO_INX(bar_va, offset);
   uint32 newval = 0;

   regval &= ~mask;
   newval = regval | (field_val << shift);

   MMIO_OUTX(bar_va, offset, newval);

   return SUCCESS;
}
