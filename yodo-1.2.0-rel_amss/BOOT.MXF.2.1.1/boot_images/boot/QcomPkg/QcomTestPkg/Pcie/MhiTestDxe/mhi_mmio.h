#ifndef MHI_MMIO_H
#define MHI_MMIO_H
/**
 *  @file mhi_mmio.h
 *
 *  @brief This file contains the MHI MMIO interface.
 */
/*=============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_i.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/** This value is returned for reads when the link is down */
#define MHI_MMIO_INVALID_VAL 0xffffffff

#define MMIO_IN(addr)                  (*((volatile uint32 *)(addr)))
#define MMIO_INX(base, offset)         (*((volatile uint32 *)((base) + (offset))))

#define MMIO_OUT(addr, val)            (*((volatile uint32 *)(addr)) = ((uint32)(val)))
#define MMIO_OUTX(base, offset, val)   (*((volatile uint32 *)((base) + (offset))) = ((uint32)(val)))

#define MMIO_OUTD(addr, val)            (*((volatile uint64 *)(addr)) = ((uint64)(val)))
#define MMIO_OUTDX(base, offset, val)   (*((volatile uint64 *)((base) + (offset))) = ((uint64)(val)))

#define MHIVER_OFFSET    8

#define BHI_VERSION_OFFSET 0x100

#define BHI_IMGADDR_OFFSET 0x108

#define BHI_IMGSIZE_OFFSET 0x110

#define BHI_IMGTXDB_OFFSET 0x118

#define BHI_INTVEC_OFFSET  0x120

#define BHI_EXECENV_OFFSET 0x128

#define DEVICE_WAKE_OFFSET  0x6F8
#define DEVICE_RESET_OFFSET 0xB0

#define BHI_STATUS_OFFSET  0x12c
#define BHI_STATUS_STATUS_MASK 0xc0000000
#define BHI_STATUS_STATUS_SHIFT       0x1e
#define BHI_STATUS_SEQNUM_MASK 0x3fffffff
#define BHI_STATUS_SEQNUM_SHIFT        0x0

#define BHI_ERRCODE_OFFSET 0x130

#define BHI_ERRDBG1_OFFSET 0x134
#define BHI_ERRDBG2_OFFSET 0x138
#define BHI_ERRDBG3_OFFSET 0x13c

#define MHICTRL_OFFSET		   0x38
#define MHICTRL_MHISTATE_MASK	0xff00
#define MHICTRL_MHISTATE_SHIFT	0x8
#define MHICTRL_RESET_MASK		0x2
#define MHICTRL_RESET_SHIFT		0x1

#define MHISTATUS_OFFSET		   0x48
#define MHISTATUS_MHISTATE_MASK	0xff00
#define MHISTATUS_MHISTATE_SHIFT	0x8
#define MHISTATUS_SYSERR_MASK	   0x4
#define MHISTATUS_SYSERR_SHIFT	   0x2
#define MHISTATUS_READY_MASK	   0x1
#define MHISTATUS_READY_SHIFT	   0x0

#define MHICFG              0x10
#define MHICFG_NHWER_MASK   0xff000000
#define MHICFG_NHWER_SHIFT  0x18
#define MHICFG_NER_MASK     0xff0000
#define MHICFG_NER_SHIFT    0x10
#define MHICFG_NCH_MASK     0xff
#define MHICFG_NCH_SHIFT    0x0

#define CCABAP_LOWER	 0x58
#define CCABAP_UPPER  0x5C

#define ECABAP_LOWER  0x60
#define ECABAP_UPPER  0x64

#define CRCBAP_LOWER  0x68
#define CRCBAP_UPPER  0x6C

#define CRDB_LOWER    0x70
#define CRDB_UPPER    0x74

#define MHICTRLBASE_LOWER  0x80
#define MHICTRLBASE_UPPER  0x84

#define MHICTRLLIMIT_LOWER 0x88
#define MHICTRLLIMIT_UPPER 0x8C

#define MHIDATABASE_LOWER  0x98
#define MHIDATABASE_UPPER  0x9C

#define MHIDATALIMIT_LOWER 0xA0
#define MHIDATALIMIT_UPPER 0xA4

/* MHI qtimer register offsets for time sync */
#define PCIE_MHI_QTIMER_LOW_OFFSET        0xA28
#define PCIE_MHI_QTIMER_HIGH_OFFSET       0xA2C

#define CHDBOFF_OFFSET   24

#define CHDB_OFFSET(ch)  (8 * (ch))

#define ERDBOFF 32

#define ERDB_OFFSET(er)  (8 * (er))

#define DB_LOW_OFFSET  0
#define DB_HIGH_OFFSET 4

#define MHI_CHANNEL_ACK_MASK            0x80000000

/* BHIe registers */

#define BHIEOFF                               0x2C

#define BHIE_MSMSOCID_OFFSET                  0x0000

#define BHIE_TXVECADDR_LOW_OFFSET             0x002C
#define BHIE_TXVECADDR_HIGH_OFFSET            0x0030

#define BHIE_TXVECSIZE_OFFSET                 0x0034

#define BHIE_TXVECDB_OFFSET                   0x003C
#define BHIE_TXVECDB_SEQNUM_MASK              0x3FFFFFFF
#define BHIE_TXVECDB_SEQNUM_SHIFT             0

#define BHIE_TXVECSTATUS_OFFSET               0x0044
#define BHIE_TXVECSTATUS_SEQNUM_MASK          0x3FFFFFFF
#define BHIE_TXVECSTATUS_SEQNUM_SHIFT         0
#define BHIE_TXVECSTATUS_STATUS_MASK          0xC0000000
#define BHIE_TXVECSTATUS_STATUS_SHIFT         30
#define BHIE_TXVECSTATUS_STATUS_RESET         0x00
#define BHIE_TXVECSTATUS_STATUS_XFER_COMPL    0x02
#define BHIE_TXVECSTATUS_STATUS_ERROR         0x03

#define BHIE_RXVECADDR_LOW_OFFSET             0x0060
#define BHIE_RXVECADDR_HIGH_OFFSET            0x0064

#define BHIE_RXVECSIZE_OFFSET                 0x0068

#define BHIE_RXVECDB_OFFSET                   0x0070
#define BHIE_RXVECDB_SEQNUM_MASK              0x3FFFFFFF
#define BHIE_RXVECDB_SEQNUM_SHIFT             0

#define BHIE_RXVECSTATUS_OFFSET               0x0078
#define BHIE_RXVECSTATUS_SEQNUM_MASK          0x3FFFFFFF
#define BHIE_RXVECSTATUS_SEQNUM_SHIFT         0
#define BHIE_RXVECSTATUS_STATUS_MASK          0xC0000000
#define BHIE_RXVECSTATUS_STATUS_SHIFT         30
#define BHIE_RXVECSTATUS_STATUS_RESET         0x00
#define BHIE_RXVECSTATUS_STATUS_XFER_COMPL    0x02
#define BHIE_RXVECSTATUS_STATUS_ERROR         0x03

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** BHI status values */
typedef enum
{
   BHI_STATUS_RESET    = 0x0,  /**< Reset state */
   BHI_STATUS_COMPLETE = 0x2,  /**< Image transfer completed */
   BHI_STATUS_ERROR    = 0x3,   /**< Error state */
   _BHI_STATUS_I32     = 0x7fffffff, /**< Force enum size to 32-bit */
} bhi_status_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
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
int32 mhi_mmio_get_ver(uintptr_t bar_va, uint32 *ver);

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
int32 mhi_mmio_get_ch_db_base_addr(mhi_va_t bar_va, mhi_va_t *va);

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
int32 mhi_mmio_get_er_db_base_addr(mhi_va_t bar_va, mhi_va_t *va);

/**
 * This function gets the channel doorbell virtual address.
 *
 * @param[in]  base   Channel doorbell base virtual address
 * @param[in]  ch_id  Channel ID
 *
 * @return Doorbell virtual address
 */
mhi_va_t mhi_mmio_get_ch_db_addr(mhi_va_t base, uint32 ch_id);

/**
 * This function gets the event ring doorbell virtual address.
 *
 * @param[in]  base   Event ring doorbell base virtual address
 * @param[in]  er_id  Event ring ID
 *
 * @return Doorbell virtual address
 */
mhi_va_t mhi_mmio_get_er_db_addr(mhi_va_t base, uint32 er_id);

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
void mhi_mmio_ring_db(mhi_va_t db_va, uint64 wp);

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
void mhi_mmio_bhi_set_addr(uintptr_t bar_va, uint64 addr);

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
void mhi_mmio_bhi_set_size(uintptr_t bar_va, uint32 size);

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
void mhi_mmio_bhi_ring_db(uintptr_t bar_va, uint32 val);

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
void mhi_mmio_device_wake_db(uintptr_t bar_va, uint32 val);

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
void mhi_mmio_device_reset_db(uintptr_t bar_va, uint32 val);

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
int32 mhi_mmio_bhi_get_status(uintptr_t bar_va, bhi_status_t *status, uint32 *seq_num);

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
void mhi_mmio_bhi_set_int_vec(uintptr_t bar_va, uint32 vector);

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
int32 mhi_mmio_bhi_get_exe_ee(uintptr_t bar_va, uint32 *rdata);

/**
 * This function gets the current MHI state of the device.
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[out] rdata    read data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_get_dev_state(uintptr_t bar_va, uint32 *rdata);

/**
 * This function requests device to enter a particular MHI state
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  rdata    requesting MHI state
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_set_dev_state(uintptr_t bar_va, uint32 rdata);

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
int32 mhi_mmio_read(uintptr_t bar_va, uint32 offset, uint32 *rdata);

int32 mhi_mmio_read_reg_field(uintptr_t bar_va, uint32 offset, uint32 mask, uint32 shift, uint32 *rdata);

/**
 * This function is used of mhi mmio write
 *
 * @attention The link must be on
 *
 * @param[in]  bar_va   BAR virtual address
 * @param[in]  offset   Register offset in MHI space
 * @param[out] wdata    write data
 *
 * @return SUCCESS or an error code
 */
int32 mhi_mmio_write(uintptr_t bar_va, uint32 offset, uint32 wdata);

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
int32 mhi_mmio_write_reg_field (uintptr_t bar_va, uint32 offset, uint32 mask, uint32 shift, uint32 field_val);

#endif

