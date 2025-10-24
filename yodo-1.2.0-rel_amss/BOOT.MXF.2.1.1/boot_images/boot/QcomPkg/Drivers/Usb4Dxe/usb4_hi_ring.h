/**---------------------------------------------------------------------------
 *   @file usb4_hi_ring.h
 *
 *   @brief   
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
#ifndef __USB4_HI_RING_H__
#define __USB4_HI_RING_H__

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"
#include "usb4_mem.h"         // usb4_buff


/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
/** @brief maximun bytes per desc */
#define USB4_HI_RING_MAX_SIZE_BYTES 0x1000

/** @brief maximun number of descriptors in ring */
#define USB4_HI_RING_MAX_RING_DESC 0x1000

/** @brief ring configuration */
typedef enum
{
  USB4_HI_RING_TYPE_UNINITIALIZED,
  USB4_HI_RING_TYPE_TRANSMIT,
  USB4_HI_RING_TYPE_RECEIVE,
} USB4_HI_RING_TYPE;

/** @brief ring mode */
typedef enum
{
  USB4_HI_RING_MODE_RAW,
  USB4_HI_RING_MODE_FRAMED,
} USB4_HI_RING_MODE;

typedef struct
{
  USB4_HI_RING_MODE mode;

  /* note sofPdf and eofPdf should be 0 in case of raw mode */
  UINT16 eof_pdf_bmsk;  /* pdf values that shall be interpreated as end of frame */
  UINT16 sof_pdf_bmsk;  /* pdf values that shall be interpreated as start of frame */

  UINT32 ring_size;               /* max 4096 descriptors */
  UINT32 rcv_data_buffer_size_bytes;  /* max 4096 bytes */

  UINT32 rcv_transmit_e2e_hopid;  /* valid only for rcv if b_e2e_flow_ontrol_enabled  */
  BOOLEAN b_e2e_flow_ontrol_enabled;
  BOOLEAN b_no_snoop_flag;

  BOOLEAN b_ring_valid; /* TRUE to set the ring valid */
} USB4_hi_ring_cfg;

typedef struct
{
  UINT32* addr_low;
  UINT32* addr_high;
  UINT32* indexes;
  UINT32* sizes;
  UINT32* control;
  UINT32* pdf_bitmasks;
  UINT32* isr;
  UINT32* isc;
  UINT32* iss;
  UINT32* imr;
  UINT32* imc;
  UINT32* ims;
  UINT32* rrvc;
  UINT32* rrvs;
  UINT32* HI_CGC;
} USB4_hi_ring_addr;

typedef struct
{
  USB4_hi_ring_addr m_addr;       /* Ring address */
  USB4_hi_ring_cfg m_cfg;         /* configuration */
  usb4_buff m_descBuff;           /* buffer of descriptors */
  UINT32 m_id;                    /* ring index, used for vacancy and interrupts */
  USB4_HI_RING_TYPE m_type;       /* ring type */
  UINT32 m_producer;              /* producer index */
  UINT32 m_lastPostedProducer;    /* last producer index which was posted */
  UINT32 m_consumer;              /* consumer index */
  UINT32 m_lastPostedConsumer;    /* last consumer index which was posted */
  UINT32 m_numQueuedDesc;         /* number of queued descriptors */
  BOOLEAN m_bValid;               /* valid settings */

  BOOLEAN m_bOverrideActive;
  UINT32 m_interruptEnableOverride;
  UINT32 m_requestStatusOverride;
} usb4_hi_ring_ctx_t;

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
 * @brief initialzie the ring and allocate descriptors
 * @param [in] hostBase HI base address
 * @param [in] ringIdx ring index (0, 1 or 2)
 * @param [in] type transmit or recieve ring
 * @return 0 on success, other on failure
 */
int Usb4HiRingInit(usb4_hi_ring_ctx_t* ring_ctx, UINT8* hiBase, UINT32 ringIdx, USB4_HI_RING_TYPE type);

/**
 * @brief release all descriptors
 * @return 0 on success, other on failure
 */
int Usb4HiRingDeInit(usb4_hi_ring_ctx_t* ring_ctx);

/**
 * @brief sets/unset the ring valid  bit
 * @param [in] valid 1 to set valid, 0 for unsetting valid
 * @return 0 on success, other on failure
 */ 
int Usb4HiRingSetValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8 valid);

/**
 * @brief Gets the valid value
 * @param [out] pValid 1 if ring is valid, 0 otherwise
 * @return 0 on success, other on failure
 */ 
int Usb4HiRingGetValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8* pValid);

/**
 * @brief Gets the valid value from AHB
 * @param [out] pValid 1 if ring is valid, 0 otherwise
 * @return 0 on success, other on failure
 */ 
int Usb4HiRingGetHwValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8* pValid);

/**
 * @brief configures the ring (disables it before configuration)
 * @param [in] cfg see #USB4_hi_ring_cfg for details
 * @return 0 on success, other on failure
 */
int Usb4HiRingConfig(usb4_hi_ring_ctx_t* ring_ctx, const USB4_hi_ring_cfg* cfg);

/**
 * @brief Get rings configuration in the SW data structure
 * @param [in] cfg see #USB4_hi_ring_cfg for details
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetConfig(usb4_hi_ring_ctx_t* ring_ctx, USB4_hi_ring_cfg* cfg);

/**
 * @brief Get rings configuration directly from AHB
 * @param [in] cfg see #USB4_hi_ring_cfg for details
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetHwConfig(usb4_hi_ring_ctx_t* ring_ctx, USB4_hi_ring_cfg* cfg);

/**
 * @brief gets the producer index
 * @param [out] pIdx holds the producer index on success
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetProducerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx);

/**
 * @brief gets the producer index
 * @param [out] pIdx holds the producer index on success
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx);


/**
 * @brief gets the producer index from data structure
 * @param [out] pIdx holds the producer index on success
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetHwProducerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx);

/**
 * @brief gets the consumer index from AHB
 * @param [out] pIdx holds the consumer index on success
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetHwConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx);

/**
 * @brief Sets the producer index through AHB
 * @param [in] Idx holds the consumer index on success
 * @return 0 on success, other on failure
 */
int Usb4HiRingSetHwConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32 Idx);

/**
 * @brief Get the number of queued descriptors (not posted yet)
 * @param [out] pNum number of queued descriptors, valid on success
 * @return 0 on success, other on failure
 */
// int Usb4HiRingGetNumQueuedDesc(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pNum);

/**
 * @brief Get the number of available free slots to use
 * @param [out] pNumSlots number of available to use slots
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetNumAvailableSlots(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pNumSlots);

/**
 * @brief post new producer index, 
 * @param [num] number to add to producer, 0 for all
 * @return 0 on success, other on failure
 */
int Usb4HiRingPostProducer(usb4_hi_ring_ctx_t* ring_ctx, UINT32 num);

/**
 * @brief adds to consumer index, assuming it allows
 * @param [num] number to add to consumer, 0 for all
 * @return 0 on success, other on failure
 */
int Usb4HiRingPostConsumer(usb4_hi_ring_ctx_t* ring_ctx, UINT32 num);
   
/**
 * @brief Wait for producer to reach last posted consumer
 * @param [timeout_ms] timeout in ms
 * @return 0 on success, other on failure
 */
int Usb4HiRingWaitAllProduced(usb4_hi_ring_ctx_t* ring_ctx, UINT64 timeout_ms);

/**
 * @brief Get number of produced descriptors; Modifies m_producer, so returned values need to be used
 * @param[out] Slot of first produced
 * @param[out] number of produced
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetNumberOfProduced(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pSlotId, UINT32* pNum);

/**
 * @brief Wait for consumer to reach last posted producer
 * @param [timeout_ms] timeout in ms
 * @return 0 on success, other on failure
 */
int Usb4HiRingWaitAllConsumed(usb4_hi_ring_ctx_t* ring_ctx, UINT64 timeout_ms);

/**
 * @brief Queue descriptos to ring without setting producer/consumer
 * @param [in] desc pointer to descriptors array
 * @param [out] slot descriptor slot index
 * @return 0 on success, other on failure
 */
int Usb4HiRingQueueDescriptor(usb4_hi_ring_ctx_t* ring_ctx, const UINT8* desc, UINT32* slot);

/**
 * @brief Get the descriptor pointer from index i of the ring 
 * @param [out] desc will hold the desc pointer
 * @param [in] i index of the descriptor to get
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetDescriptorPtr(usb4_hi_ring_ctx_t* ring_ctx, UINT8** desc, UINT32 i);

/**
 * @brief Read the descriptor from index i of the ring to buffer
 * @param [out] desc will hold the desc
 * @param [in] i index of the descriptor to get
 * @return 0 on success, other on failure
 */
int Usb4HiRingReadDescriptor(usb4_hi_ring_ctx_t* ring_ctx, UINT8* desc, UINT32 i);

/**
 * @brief HW accessor function
 * @param[in] threshold - new vacancy threshold value for the ring
 * A value of j (j > 0) corresponds to 2(j-1) available Receive Descriptors.
 * @return 0 on success other on failure
 */
int Usb4HiRingSetVacancyThreshold(usb4_hi_ring_ctx_t* ring_ctx, UINT32 threshold);

/**
 * @brief Gets vacancy threshold status per ring. TRUE means the number of free descriptors fell below the threshold
 * If set, vacancy interrupt status will also be set
 * @param[out] pStatus - status of threshold
 * @return 0 on success other on failure
 */
int Usb4HiRingGetVacancyThresholdStatus(usb4_hi_ring_ctx_t* ring_ctx, BOOLEAN* pStatus);

/**
 * @brief Gets vacancy interrupt status per RX ring.
 * @param[out] pStatus - status of interrupt
 * @return 0 on success other on failure
 */
int Usb4HiRingGetVacancyInterruptStatus(usb4_hi_ring_ctx_t* ring_ctx, BOOLEAN* pStatus);

/**
* @brief Clear vacancy interrupt status per RX ring.
* @return 0 on success other on failure
*/
int Usb4HiRingClearVacancyInterrupt(usb4_hi_ring_ctx_t* ring_ctx);

/**
* @brief Mask interrupts, disable flow control and wait for indexes to become equal
* @return 0 on success other on failure
*/
int Usb4HiRingFlushRing(usb4_hi_ring_ctx_t* ring_ctx, UINT32 ms_timeout);

#endif /* __USB4_HI_RING_H__ */
