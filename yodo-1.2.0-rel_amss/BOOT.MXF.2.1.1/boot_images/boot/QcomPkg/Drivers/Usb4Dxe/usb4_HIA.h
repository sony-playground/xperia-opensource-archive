/**---------------------------------------------------------------------------
 *   @file        usb4_HIA.h
 *
 *   @brief   Header file for HIA implementation
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef __USB4_HIA_H_
#define __USB4_HIA_H_

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVDRV_usb4_ap_host.h"
// #include "VVDRV_usb4_hi_ring.h"
// #include "usb4_frames_seg_calc.h"

#include "usb4_hi_ring.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

#define USB4_MAX_HIA_RINGS 2 /* @deprecated use new rings apis */


#define USB4_HI_TOTAL_RINGS 3
#define USB4_HI_MAX_TR_SIZE 0x1000 /* 4KB per desc */

#define USB4_HI_RING_STOP_TIMEOUT_MS 1000

/** @brief the ring Interrupt masks based on the USB4 spec */
#define USB4_HI_ISR_TX(ringid)      (1 << ringid)
#define USB4_HI_ISR_RX(ringid)      ((1 << ringid) << USB4_HI_TOTAL_RINGS)
#define USB4_HI_ISR_RX_VAC(ringid)  ((1 << ringid) << (2 * USB4_HI_TOTAL_RINGS))

typedef struct
{
    UINT32 ringIdx;     /* ring index */
    UINT32 size_bytes;  /* transfer size bytes; Will contain actually received data size for control ring.
                           Can be compared to buff.size_bytes to identify the difference if needed.*/
    UINT64 timeout_ms;  /* timeout to wait for blocking transfers */
    usb4_buff buff;     /* data buffer */
    UINT8 sof_pdf;      /* sof should match ring configuration */
    UINT8 eof_pdf;      /* eof should match ring configuration; Will contain actually received value for control ring. */
    BOOLEAN rs;         /* request status */
    BOOLEAN ie;         /* interrupt enable */
    UINT8 offset;       /* transfer offset from buffer */
    
    BOOLEAN randSeg;    /* Frame mode only, FALSE: max seg size, TRUE: rand */   
    UINT32 slotId;      /* updated by #QueueTransmit() / #QueueReceive() */
    BOOLEAN bInUseByHW;
    BOOLEAN bInUseBySW;
    BOOLEAN bReferenceDone;
    BOOLEAN bPostingPostponed; /* Flag for testing - normal driver flow will be interrupted until an explicit API call to post */
} USB4_hi_xfer;

/** @brief Struct is output #VerifyTransmited() and #VerifyRecieved() */
typedef struct
{
    /* info updated by host iface adapter */
    BOOLEAN dd;         /* desc done */
    
    /* the following fields are valid only for receive */
    BOOLEAN crcErr;     /* crc err */
    BOOLEAN bo;         /* buff overflow */
} USB4_hi_xfer_status;

typedef struct
{
  UINT8* m_pModuleBaseAddr;
  // usb4_frames_seg_calc m_calc;
  UINT32* m_pSlots;
  UINT32 m_num_slots;

//  usb4_cm_logger_ctx_t* m_pLogger;
//  usb4_ap_host m_ap_config_space; // Read/Write access to configuration space registers

  usb4_hi_ring_ctx_t m_transmit[USB4_HI_TOTAL_RINGS];
  usb4_hi_ring_ctx_t m_recieve[USB4_HI_TOTAL_RINGS];

  UINT32 m_interrupt_status;
  UINT32 m_interrupt_mask;
  BOOLEAN m_isr_autoclear;
} usb4_hia_ctx_t;


/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

/**
 * @brief Initialize the Host interface with base address
 *        it will also call init function for submodules (where applicable)
 * @return 0 on success, other on failure
 */
int Usb4HiaInit(usb4_hia_ctx_t* hia_ctx, UINT8* pModuleBaseAddr);

/**
 * @brief configures the ring
 * @param [in] cfg see #USB4_hi_ring_cfg for details
 * @return 0 on success, other on failure
 */
int Usb4HiaConfigRing(usb4_hia_ctx_t* hia_ctx, 
               UINT32 ringId, 
               USB4_HI_RING_TYPE type,
               const USB4_hi_ring_cfg* cfg);

/**
 * @brief Make sure ring is idle.
 * @param [in] timeout - time interval to wait for the ring to become idle
 * @return 0 on success, other on failure
 */
int Usb4HiaStopRing(usb4_hia_ctx_t* hia_ctx,
             UINT32 ringId,
             USB4_HI_RING_TYPE type,
             UINT32 timeout_ms);

/**
 * @brief Get rings configuration in the SW data structure
 * @param [in] cfg see #USB4_hi_ring_cfg for details
 * @return 0 on success, other on failure
 */
int Usb4HiaGetRingConfig(usb4_hia_ctx_t* hia_ctx,
                  UINT32 ringId,
                  USB4_HI_RING_TYPE type, 
                  USB4_hi_ring_cfg* pCfg);

/**
 * @brief prepares a descriptor and queue it to transfer ring.
 *       dont increase producer yet.
 * @param [in/out] xfer see #USB4_hi_xfer for details
 *                      will set the slotid
 * @return 0 on success, other on failure
 */
int Usb4HiaQueueTransmit(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* xfer);

/**
 * @brief prepares a descriptor and queue it to consumer ring.
 *        dont increase consumer yet
 * @param [in/out] xfer see #USB4_hi_xfer for details
 *                      will set the slotid
 * @return 0 on success, other on failure
 */
int Usb4HiaQueueReceive(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* xfer);

/**
 * @brief start all transfers on a transmit ring
 * @param [in] ringId the ringId to start all transfers on
 * @param [in] num number of queued transfers to transmit, 0 for all
 * @param [in] timeout_ms timeout to wait for completion, 0 for none
 * @return 0 on success, other on failure
 */
int Usb4HiaTransmit(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32 num, UINT64 timeout_ms);

/**
 * @brief start all transfers on a receive ring
 * @param [in] ringId the ringId to start all transfers on
 * @param [in] num number of queued transfers to receive, 0 for all
 * @return 0 on success, other on failure
 */
int Usb4HiaReceive(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32 num);

/**
 * @brief wait for the transmit transfers which were started to be consumed
 * @param [in] ringId the ringId to start all transfers on
 * @param [in] timeout_ms timeout in ms to wait for completion
 * @return 0 on success, other on failure / timeout
 */
int Usb4HiaWaitTransmited(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT64 timeout_ms);

/**
 * @brief wait for the receive transfers which were started
 * @param [in] ringId the ringId to start all transfers on
 * @param [in] timeout_ms timeout in ms to wait for completion
 * @return 0 on success, other on failure / timeout
 */
int Usb4HiaWaitReceived(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT64 timeout_ms);

/**
 * @brief Peek into RX ring
 * @param [in] ringId the ringId to work on
 * @param [out] slot ID for the first received descriptor
 * @param [out] number of received descriptors
 * @return 0 if new descriptor is present, other if not present.
 */
int Usb4HiaPeek(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32* pSlotId, UINT32* pNum);

/**
 * @brief Used in a test. Update offset in currently queued descriptor
 * @param [in] ringId the ringId to start all transfers on
 * @param [in] num number of queued transfers to transmit, 0 for all
 * @param [in] timeout_ms timeout to wait for completion, 0 for none
 * @return 0 on success, other on failure
 */
int Usb4HiaUpdateOffsetInRxDescriptor(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* pXfer, UINT32 offset);


/**
 * @brief Verify the transfer descriptor
 * @note function should be called after #WaitTrasmited() completed
 *       succesfully and indicated this transfer is completed
 * @param [in] pXfer see #USB4_hi_xfer for details
 * @param [out] pStatus see #USB4_hi_xfer_status for details
 * @return 0 on success, other on failure / timeout
 */
int Usb4HiaVerifyTransmited(usb4_hia_ctx_t* hia_ctx,
                     USB4_hi_xfer* pXfer,
                     USB4_hi_xfer_status* pStatus);

/**
 * @brief Verify the transfer descriptor
 * @note function should be called after #WaitTrasmited() completed
 *       succesfully and indicated this transfer is completed
 * @param [in] pXfer see #USB4_hi_xfer for details
 * @param [out] pStatus see #USB4_hi_xfer_status for details
 * @return 0 on success, other on failure / timeout
 */                         
int Usb4HiaVerifyRecieved(usb4_hia_ctx_t* hia_ctx,
                   USB4_hi_xfer* pXfer,
                   USB4_hi_xfer_status* pStatus);


/** 
 * @brief ISR handler called on HIA IRQ (if in IRQ mode)
 * @param [in] int_num interrupt number from gic
 * @return 0 on success, other on failure
 */
int Usb4HiaIsrHanlder(usb4_hia_ctx_t* hia_ctx, UINT32 int_num);

/**
 * @brief Get ISR status from the HW
 * @param [out] pStatus see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaGetHwIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32* pMask);

/**
 * @brief Get ISR status mask, based on mode (HW/ shaddow)
 * @param [out] pStatus see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaGetIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32* pMask);

/**
 * @brief Clear status by writing mask to ISC reg
 * @param [in] mask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaClearIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32 mask);

/**
 * @brief Sets the status by writing mask to ISS reg
 * @param [in] mask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaSetIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32 mask);

/**
 * @brief Get the interrupt enabled mask by reading IMR
 * @param [out] pMask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaGetIntMask(usb4_hia_ctx_t* hia_ctx, UINT32* pMask);

/**
 * @brief Sets the interrupt mask by writing to IMR
 * @param [in] mask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaSetIntMask(usb4_hia_ctx_t* hia_ctx, UINT32 mask);

/**
 * @brief Sets the Int Mask Clear by writing IMC
 * @param [int] mask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaSetIntMaskClear(usb4_hia_ctx_t* hia_ctx, UINT32 mask);

/**
 * @brief Sets the interrupt mask by writing to IMS
 * @param [int] mask see #USB4_HI_ISR_*
 * @return 0 on success, other on failure
 */
int Usb4HiaSetIntMaskSet(usb4_hia_ctx_t* hia_ctx, UINT32 mask);

/**
 * @brief Configures autoclear on read mode
 * @param [in] mask Irq enabled mask
 * @param [in] autoclear TRUE to autoclear on read, FALSE do not clear on read
 * @return 0 on success, other on failure
 */
int Usb4HiaConfigureAutoclear(usb4_hia_ctx_t* hia_ctx, BOOLEAN autoclear);


/**
 * @brief Reset the Host Interface registers and the
 * E2E flow control counters to their default values.
 * @return 0 on success, other on failure
 */
int Usb4HiaPlatformReset(usb4_hia_ctx_t* hia_ctx);

/**
 * @brief Global configuration impacting all rings - interrupts are self clearing on read or not.
 * @param[in] bDisableIsrAutoClear - Prohibit self clearing of interruts
 * @return 0 on success other on failure
 */
int Usb4HiaPlatformSetDisableIsrAutoClear(usb4_hia_ctx_t* hia_ctx, BOOLEAN bDisableIsrAutoClear); 


/**
 * @brief Get Global configuration impacting all rings - interrupts are self clearing on read or not.
 * @param[out] pbDisableIsrAutoClear - Prohibit self clearing of interruts
 * @return 0 on success other on failure
 */
int Usb4HiaPlatformGetDisableIsrAutoClear(usb4_hia_ctx_t* hia_ctx, UINT32* pDisableIsrAutoClear);

/**
 * @brief Set new ring size for the recieve and transmit rings
 * @param[in] size - New size for the ring
 * @param[in] ringIndex - Index to the ring 
 * @return 0 on success other on failure
 */
int Usb4HiaChangeRingSizeConfig(usb4_hia_ctx_t* hia_ctx, UINT32 size, UINT32 ringIndex, USB4_HI_RING_TYPE ringType);

/**
 * @brief Set new mode for the recieve and transmit rings
 * @param[in] mode - New ring mode
 * @param[in] ringIndex - Index to the ring 
 * @return 0 on success other on failure
 */
int Usb4HiaChangeRingMode(usb4_hia_ctx_t* hia_ctx, USB4_HI_RING_MODE mode, UINT32 ringIndex, USB4_HI_RING_TYPE ringType);

/**
 * @brief For direct control of control ring - useful in a tests
 */
usb4_hi_ring_ctx_t* Usb4HiaCtrlRingTx(usb4_hia_ctx_t* hia_ctx);
usb4_hi_ring_ctx_t* Usb4HiaCtrlRingRx(usb4_hia_ctx_t* hia_ctx);

#endif /* __USB4_HIA_H_ */
