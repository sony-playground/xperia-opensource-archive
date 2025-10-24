/**---------------------------------------------------------------------------
 *   @file        usb4_HIA.cpp
 *
 *   @brief   Implements host interface adapter
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Utils.h>
#include <Usb4Log.h>

// #include "VVHAL_usb4_logger.h"  // Logging utilities
// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
#include "HALhwio.h"

#include "usb4_mem.h"
#include "usb4_hwio.h"    /* in_dword, out_dword for ISR regs */
#include "usb4_frames_seg_calc.h"

#include "usb4_HIA.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
/** @brief helper for more readabilty mappings */
#define IO_ADDR(base, offset)   ((UINT32*)((UINT8*)(base) + offset))

/** @brief ISR addres offset based on the USB4 spec */
#define IO_ISR_ADDR(base)   IO_ADDR(base, 0x37800)

/** @brief ISC addres offset based on the USB4 spec */
#define IO_ISC_ADDR(base)   IO_ADDR(base, 0x37808)

/** @brief ISS addres offset based on the USB4 spec */
#define IO_ISS_ADDR(base)   IO_ADDR(base, 0x37810)

/** @brief IMR addres offset based on the USB4 spec */
#define IO_IMR_ADDR(base)   IO_ADDR(base, 0x38200)

/** @brief IMC addres offset based on the USB4 spec */
#define IO_IMC_ADDR(base)   IO_ADDR(base, 0x38208)

/** @brief IMS addres offset based on the USB4 spec */
#define IO_IMS_ADDR(base)   IO_ADDR(base, 0x38210)

/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/
#pragma pack(push)
#pragma pack(1)

/** @brief USB4 1.0 - Figure 12-4 */
typedef union
{
  struct
  {
    // dword0
    UINT32 addr_low         : 32;

    // dword1
    UINT32 addr_high        : 32;

    // dword2
    UINT32 data_length      : 12;       // 0:11
    UINT32 eof_pdf          :  4;       // 12:15
    UINT32 sof_pdf          :  4;       // 16:19
    UINT32 reserved_0       :  1;       // 20
    UINT32 descriptor_done  :  1;       // 21
    UINT32 request_status   :  1;       // 22
    UINT32 interrupt_enable :  1;       // 23
    UINT32 offset           :  8;       // 24:31

    // dword3
    UINT32 reserved_1       : 32;
  } transmit_fields;
  UINT8 raw[16];
} USB4_hi_trasmit_desc;

/** @brief USB4 1.0 - Figure 12-5 */
typedef union
{
  struct
  {
    // dword0
    UINT32 addr_low         : 32;

    // dword1
    UINT32 addr_high        : 32;

    // dword2
    UINT32 reserved_0       : 21;       // 0:20
    UINT32 descriptor_done  :  1;       // 21
    UINT32 request_status   :  1;       // 22
    UINT32 interrupt_enable :  1;       // 23
    UINT32 offset           :  8;       // 24:31

    // dword3
    UINT32 reserved_1       : 32;
  } receive_fields;
  UINT8 raw[32];
} USB4_hi_recieve_hia_desc;

/** @brief USB4 1.0 - Figure 12-6 */
typedef union
{
  struct
  {
    // dword0
    UINT32 addr_low         : 32;

    // dword1
    UINT32 addr_high        : 32;

    // dword2
    UINT32 data_length      : 12;       // 0:11
    UINT32 eof_pdf          :  4;       // 12:15
    UINT32 sof_pdf          :  4;       // 16:19
    UINT32 crc_error        :  1;       // 20
    UINT32 descriptor_done  :  1;       // 21
    UINT32 buffer_overflow  :  1;       // 22
    UINT32 interrupt_enable :  1;       // 23
    UINT32 offset           :  8;       // 24:31

    // dword3
    UINT32 reserved_1       : 32;
  } receive_host_fields;
  UINT8 raw[32];
} USB4_hi_recieve_host_desc;

#pragma pack(pop)

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

int Usb4HiaInit(usb4_hia_ctx_t* hia_ctx, UINT8* pModuleBaseAddr)
{
  UINT32 i;

  hia_ctx->m_pModuleBaseAddr = NULL;
  hia_ctx->m_pSlots = NULL;
  hia_ctx->m_num_slots = 0;
  hia_ctx->m_interrupt_status = 0;
  hia_ctx->m_interrupt_mask = 0;
  hia_ctx->m_isr_autoclear = FALSE;

  if (NULL == pModuleBaseAddr)
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }    

  hia_ctx->m_pModuleBaseAddr = pModuleBaseAddr;
  hia_ctx->m_interrupt_status = 0x0;
  hia_ctx->m_interrupt_mask = 0x0;
  hia_ctx->m_isr_autoclear = TRUE;

  for (i = 0; i < USB4_HI_TOTAL_RINGS; ++i)
  {
    if (0 != Usb4HiRingInit(&hia_ctx->m_transmit[i], hia_ctx->m_pModuleBaseAddr, i, USB4_HI_RING_TYPE_TRANSMIT))
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
    if (0 != Usb4HiRingInit(&hia_ctx->m_recieve[i], hia_ctx->m_pModuleBaseAddr, i, USB4_HI_RING_TYPE_RECEIVE))
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
  }

  return 0;
}

int Usb4HiaStopRing(usb4_hia_ctx_t* hia_ctx,
             UINT32 ringId,
             USB4_HI_RING_TYPE type,
             UINT32 timeout_ms)
{
  int result;
  UINT8 valid;

  if (USB4_HI_TOTAL_RINGS <= ringId)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  if (timeout_ms < 10)
  {
    timeout_ms = 10;
  }

  /* Check if ring is idle already */
  if (USB4_HI_RING_TYPE_TRANSMIT == type)
  {
    result = Usb4HiRingGetValid(&hia_ctx->m_transmit[ringId], &valid);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
    if (0 == valid)
    {
      return 0;
    }

    /* Check if ring is idle already */
    result = Usb4HiRingWaitAllConsumed(&hia_ctx->m_transmit[ringId], timeout_ms);
    if (-1 == result) /* Ring is not idle */
    {
      result = Usb4HiRingFlushRing(&hia_ctx->m_transmit[ringId], timeout_ms);
      if (0 != result)
      {
        USB4_ERROR_STACK(result);
        return -1;
      }
    }
    else
    {
      result = Usb4HiRingSetValid(&hia_ctx->m_transmit[ringId], 0);
      if (0 != result)
      {
        USB4_ERROR_STACK(result);
        return -1;
      }
    }
  }
  else
  {
    result = Usb4HiRingSetValid(&hia_ctx->m_recieve[ringId], 0);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
  }

  // TOOD: AC CRITICAL   DeInit to free memory.  Need to find a place to free the rings, it seems to accumulate upon each wake and enable
  return 0;
}

int Usb4HiaConfigRing(usb4_hia_ctx_t* hia_ctx,
               UINT32 ringId, 
               USB4_HI_RING_TYPE type,
               const USB4_hi_ring_cfg* pCfg)
{
  int result;


  if (USB4_HI_TOTAL_RINGS <= ringId)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  result = Usb4HiaStopRing(hia_ctx, ringId, type, USB4_HI_RING_STOP_TIMEOUT_MS); /* Ring needs to be properly flushed prior to re-configuration */
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  if (USB4_HI_RING_TYPE_TRANSMIT == type)
  {
    result = Usb4HiRingConfig(&hia_ctx->m_transmit[ringId], pCfg);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
  }
  else
  {
    result = Usb4HiRingConfig(&hia_ctx->m_recieve[ringId], pCfg);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
  }

  // allocations here if needed to handle transfers queues...
  if (hia_ctx->m_num_slots < pCfg->ring_size)
  {
    if (NULL != hia_ctx->m_pSlots)
    {
      usb4_mem_free(hia_ctx->m_pSlots);
      hia_ctx->m_pSlots = NULL;
      hia_ctx->m_num_slots = 0;
    }
  }

  if (NULL == hia_ctx->m_pSlots)
  {
    UINT32 alloc_bytes = pCfg->ring_size * sizeof(UINT32);
    hia_ctx->m_pSlots = (UINT32*)usb4_mem_alloc(alloc_bytes, 0);
    if (NULL == hia_ctx->m_pSlots)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
    hia_ctx->m_num_slots = pCfg->ring_size;
  }

  return 0;
}
    
int Usb4HiaGetRingConfig(usb4_hia_ctx_t* hia_ctx,
                  UINT32 ringId,
                  USB4_HI_RING_TYPE type, 
                  USB4_hi_ring_cfg* pCfg)
{
  int result;

  if (USB4_HI_TOTAL_RINGS <= ringId)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  if (USB4_HI_RING_TYPE_TRANSMIT == type)
  {
    result = Usb4HiRingGetConfig(&hia_ctx->m_transmit[ringId], pCfg);
    if (0 != result)
    {
      USB4_ERROR_STACK(result);
      return -1;
    }
  }

  result = Usb4HiRingGetConfig(&hia_ctx->m_recieve[ringId], pCfg);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  return 0;
}

////// int calc_random_descs(uint* pNums, UINT32 num_desc, UINT32 size_bytes)
////// {
////// }

///// static int getValidI(UINT16 mask, UINT16* val)
///// {
/////     UINT16 arr[16] = { 0x0 };
/////     UINT32 size = 0;
/////     
/////     if (0x0 == mask)
/////     {
/////         USB4_ERROR_STACK_MSG("0x0 mask");
/////         return -1;
/////     }
/////     
/////     for (UINT32 i = 0; i < ARR_SIZE(arr); ++i)
/////     {
/////         if (mask & (1 << i))
/////         {
/////             arr[size] = i;
/////             ++size;
/////         }
/////     }
/////     
/////     if (0 != VVHAL_usb4_utils_rand(0, size-1, val))
/////     {
/////         USB4_ERROR_STACK(-1);
/////         return -1;
/////     }
/////     return 0;
///// }

int Usb4HiaQueueTransmit(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* pXfer)
{
  USB4_hi_ring_cfg cfg = {};
  USB4_hi_trasmit_desc desc;
  UINT64 paddr;
  UINT32 numDesc;
  UINT32 freeDesc;
  UINT32 total_bytes;
  UINT8 sof_pdf;
  UINT8 eof_pdf;
  int result;

  usb4_hi_ring_ctx_t* pRing = NULL; 

  if (NULL == pXfer)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  result = Usb4HiaGetRingConfig(hia_ctx, pXfer->ringIdx, USB4_HI_RING_TYPE_TRANSMIT, &cfg);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  if (pXfer->buff.size_bytes < (pXfer->offset + pXfer->size_bytes))
  {
    USB4_ERROR_STACK_MSG(-1, "Buff size should be bigger than xfer size");
    return -1;
  }

  sof_pdf = pXfer->sof_pdf;
  eof_pdf = pXfer->eof_pdf;

  if (USB4_HI_RING_MODE_FRAMED == cfg.mode)
  {
    UINT32 sof_bmsk;
    UINT32 eof_bmsk;


    if ((0x0 == sof_pdf) || (0x0 == eof_pdf) || ((sof_pdf == eof_pdf)))
    {
      USB4_ERROR_STACK_MSG(-1, "sod and eof cant be 0x0 or equal");
      return -1;
    }

    sof_bmsk = (0x1 << sof_pdf);
    eof_bmsk = (0x1 << eof_pdf);

    if (0x0 == (cfg.sof_pdf_bmsk & sof_bmsk))
    {
      // USB4_LOG_WARNING("SOF = 0%02X not matching mask: 0x%02X\n", 
      //    sof_pdf, cfg.sof_pdf_bmsk);
      USB4_LOG_WARNING_2(USB4_LOG_CM, Usb4CmHiaQueueTransmitSofNotMatching__Params__Sof_Mask, 0, sof_pdf, cfg.sof_pdf_bmsk);
    }

    if (0x0 == (cfg.eof_pdf_bmsk & eof_bmsk))
    {
      // USB4_LOG_WARNING("EOF = 0%02X not matching mask: 0x%02X\n", 
      //    eof_pdf, cfg.eof_pdf_bmsk);
      USB4_LOG_WARNING_2(USB4_LOG_CM, Usb4CmHiaQueueTransmitSofNotMatching__Params__Eof_Mask, 0, eof_pdf, cfg.eof_pdf_bmsk);
    }
  }

  pRing = hia_ctx->m_transmit + pXfer->ringIdx;

  result = Usb4HiRingGetNumAvailableSlots(pRing, &freeDesc);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  if (0 == freeDesc)
  {
    USB4_ERROR_STACK_MSG(-1, "No empty slots");
    return -1;
  }

  if (USB4_HI_RING_MODE_RAW == cfg.mode)
  {
    if (pXfer->size_bytes > 256)
    {
      USB4_ERROR_STACK_MSG(-1, "Trying to send raw data > 256\n");
      return -1;
    }

    // Prepare number of bytes for a single descriptor (slot0)
    hia_ctx->m_pSlots[0] = pXfer->size_bytes;
    numDesc = 1;
  }
  else
  {
    if (FALSE == pXfer->randSeg)
    {
      result = Usb4FramesSegCalcMaxSizeSegments(pXfer->size_bytes,  
          USB4_HI_MAX_TR_SIZE, 
          freeDesc, 
          hia_ctx->m_pSlots, 
          &numDesc);
      if (0 != result)
      {
        USB4_ERROR_STACK(result);
        return -1;
      }
    }
    else
    {
      result = Usb4FramesSegCalcRandom(pXfer->size_bytes, 
          USB4_HI_MAX_TR_SIZE, 
          freeDesc, 
          hia_ctx->m_pSlots, 
          &numDesc);
      if (0 != result)
      {
        USB4_ERROR_STACK(result);
        return -1;
      }
    }
  }

  total_bytes = pXfer->size_bytes;
  paddr = pXfer->buff.paddr;
  for (UINT32 i = 0; i < numDesc; ++i)
  {
    UINT32 iter_bytes = hia_ctx->m_pSlots[i];
    // Create descriptors
    for (UINT32 j = 0 ; j < ARR_SIZE(desc.raw); ++j)
    {
      desc.raw[j] = 0x0;
    }

    desc.transmit_fields.addr_low = USB4_LOWER32(paddr);
    desc.transmit_fields.addr_high = USB4_UPPER32(paddr);
    desc.transmit_fields.data_length =  iter_bytes;
    desc.transmit_fields.sof_pdf = (0 == i) ? sof_pdf : 0x0;
    desc.transmit_fields.eof_pdf = ((numDesc - 1) == i) ? eof_pdf : 0x0;
    desc.transmit_fields.descriptor_done = 0;
    desc.transmit_fields.request_status = pXfer->rs;
    desc.transmit_fields.interrupt_enable = pXfer->ie;
    desc.transmit_fields.offset = (0 == i) ? pXfer->offset : 0x0;

#if defined(USB4_WA_CR_QCTDD06702880_TX_RS_ALWAYS_SET)
    desc.transmit_fields.request_status = 0x1;
#endif /* USB4_WA_CR_QCTDD06702880_TX_RS_ALWAYS_SET */

    if (pRing->m_bOverrideActive)
    {
      desc.transmit_fields.interrupt_enable = pRing->m_interruptEnableOverride;
      desc.transmit_fields.request_status = pRing->m_requestStatusOverride;
    }


    result = Usb4HiRingQueueDescriptor(pRing, desc.raw, &(pXfer->slotId));
    if (0 != result)
    {
      // TODO real recovery here releases the queued descriptros...
      USB4_ERROR_STACK(result);
      return -1;
    }

    total_bytes -= iter_bytes;
    paddr += iter_bytes;
  }
  pXfer->bInUseByHW = TRUE;
  return 0;
}


int Usb4HiaQueueReceive(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* pXfer)
{
  USB4_hi_ring_cfg cfg = {};
  USB4_hi_trasmit_desc desc;
  UINT64 paddr;
  UINT32 numSlots;
  UINT32 freeSlots;
  UINT32 total_bytes;
  int result;

  usb4_hi_ring_ctx_t* pRing = NULL; 

  if (NULL == pXfer)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  result = Usb4HiaGetRingConfig(hia_ctx, pXfer->ringIdx, USB4_HI_RING_TYPE_TRANSMIT, &cfg);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  pRing = hia_ctx->m_recieve + pXfer->ringIdx;

  result = Usb4HiRingGetNumAvailableSlots(pRing, &freeSlots);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  if (0 == freeSlots)
  {
    USB4_ERROR_STACK_MSG(-1, "No empty slots");
    return -1;
  }

  result = Usb4FramesSegCalcMaxSizeSegments(pXfer->size_bytes, 
      USB4_HI_MAX_TR_SIZE, 
      freeSlots, 
      hia_ctx->m_pSlots, 
      &numSlots);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  total_bytes = pXfer->size_bytes;
  paddr = pXfer->buff.paddr;
  for (UINT32 i = 0; i < numSlots; ++i)
  {
    UINT32 iter_bytes = USB4_HI_MAX_TR_SIZE; // hardcoding

    // Create descriptors
    for (UINT32 j = 0 ; j < ARR_SIZE(desc.raw); ++j)
    {
      desc.raw[j] = 0x0;
    }

    desc.transmit_fields.addr_low = USB4_LOWER32(paddr);
    desc.transmit_fields.addr_high = USB4_UPPER32(paddr);
    desc.transmit_fields.descriptor_done = 0;
    desc.transmit_fields.request_status = pXfer->rs;
    desc.transmit_fields.interrupt_enable = pXfer->ie;
    desc.transmit_fields.offset = pXfer->offset;

    if (pRing->m_bOverrideActive)
    {
      desc.transmit_fields.interrupt_enable = pRing->m_interruptEnableOverride;
      desc.transmit_fields.request_status = pRing->m_requestStatusOverride;
    }

    result = Usb4HiRingQueueDescriptor(pRing, desc.raw, &(pXfer->slotId));
    if (0 != result)
    {
      // TODO real recovery here releases the queued descriptros...
      USB4_ERROR_STACK(result);
      return -1;
    }

    total_bytes -= iter_bytes;
    paddr += iter_bytes;

    // Wrapping buffer ....
    if (paddr > (pXfer->buff.paddr + pXfer->buff.size_bytes))
    {
      paddr = pXfer->buff.paddr;
    }
  }
  pXfer->bInUseByHW = TRUE;
  return 0;
}

int Usb4HiaTransmit(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32 num, UINT64 timeout_ms)
{
  usb4_hi_ring_ctx_t* pRing = NULL; 
//  usb4_utils_timer timer;
//
//  timer.m_source = USB4_TIMER_SOURCE_QTIMER;

  int result;

  if (ringId >= USB4_HI_TOTAL_RINGS)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  pRing = hia_ctx->m_transmit + ringId;

  // function will check there are enough queued descriptors 
  result = Usb4HiRingPostProducer(pRing, num);
  if (0 != result)
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  if (timeout_ms > 0)
  {
    result = Usb4HiRingWaitAllConsumed(pRing, timeout_ms);
    if (0 != result)
    {
      USB4_ERROR_STACK(-1);
      return result;
    }
  }

  return 0;
}

int Usb4HiaReceive(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32 num)
{
  usb4_hi_ring_ctx_t* pRing;    
  int result;

  if (ringId >= USB4_HI_TOTAL_RINGS)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  pRing = hia_ctx->m_recieve + ringId;

  // function will check there are enough queued descriptors 
  result = Usb4HiRingPostConsumer(pRing, num);
  if (0 != result)
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  return 0;
}

int Usb4HiaWaitTransmited(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT64 timeout_ms)
{
  usb4_hi_ring_ctx_t* pRing; 
  int result;

  if (ringId >= USB4_HI_TOTAL_RINGS)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  if (0 == timeout_ms)
  {
    USB4_ERROR_STACK_MSG(-1, "timeout_ms must be > 0");
    return -1;
  }

  pRing = hia_ctx->m_transmit + ringId;

  if (timeout_ms > 0)
  {
    result = Usb4HiRingWaitAllConsumed(pRing, timeout_ms);
    if (0 != result)
    {
      USB4_ERROR_STACK(-1);
      return result;
    }
  }

  return 0;
}

int Usb4HiaWaitReceived(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT64 timeout_ms)
{
  usb4_hi_ring_ctx_t* pRing; 
  int result;

  if (ringId >= USB4_HI_TOTAL_RINGS)
  {
    USB4_ERROR_STACK_MSG(-1, "Invlaid ring id");
    return -1;
  }

  if (0 == timeout_ms)
  {
    USB4_ERROR_STACK_MSG(-1, "timeout_ms must be > 0");
    return -1;
  }

  pRing = hia_ctx->m_recieve + ringId;

  if (timeout_ms > 0)
  {
    result = Usb4HiRingWaitAllProduced(pRing, timeout_ms);
    if (0 != result)
    {
      USB4_ERROR_STACK(-1);
      return result;
    }
  }

  return 0;
}

/**
 * @brief Peek into RX ring
 * @param [in] ringId the ringId to work on
 * @param [out] slot ID for the first received descriptor
 * @param [out] number of received descriptors
 * @return 0 if new descriptor is present, other if not present.
 */
int Usb4HiaPeek(usb4_hia_ctx_t* hia_ctx, UINT32 ringId, UINT32* pSlotId, UINT32* pNum)
{
  usb4_hi_ring_ctx_t* pRing;
  int result;
  pRing = hia_ctx->m_recieve + ringId;
  result = Usb4HiRingGetNumberOfProduced(pRing, pSlotId, pNum);
  if (0 != result)
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }
  if (0 == *pNum)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

int Usb4HiaUpdateOffsetInRxDescriptor(usb4_hia_ctx_t* hia_ctx, USB4_hi_xfer* pXfer, UINT32 offset)
{
  usb4_hi_ring_ctx_t* pRing;
  USB4_hi_recieve_hia_desc* descriptor;
  pRing = hia_ctx->m_recieve + pXfer->ringIdx;
  USB4_ASSERT(TRUE == pXfer->bInUseByHW);
  USB4_ASSERT(0 == Usb4HiRingGetDescriptorPtr(pRing, (UINT8**)(&descriptor), pXfer->slotId));
  descriptor->receive_fields.offset = offset;
  pXfer->offset = offset;
  return 0;
}

int Usb4HiaVerifyTransmited(usb4_hia_ctx_t* hia_ctx,
                     USB4_hi_xfer* pXfer,
                     USB4_hi_xfer_status* pStatus)
{
  const USB4_hi_trasmit_desc* pDesc = NULL;
  UINT8* pBuff = NULL;
  int result;

  if ((NULL == pXfer) || (NULL == pStatus))
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  // Verify DD
  result = Usb4HiRingGetDescriptorPtr(&hia_ctx->m_transmit[pXfer->ringIdx], &pBuff, pXfer->slotId);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return result;
  }

  pDesc = (const USB4_hi_trasmit_desc*)(pBuff);

  // when it is splitted, we cant verify transfer size and buffer since these
  // are aggregated in multiple descriptors...
  if (FALSE == pXfer->randSeg)
  {
    UINT32 exp_bytes = pXfer->size_bytes % USB4_HI_MAX_TR_SIZE;
    UINT32 last_desc_byte = (exp_bytes == 0) ? 4096 : exp_bytes;

    UINT64 desc_paddr = USB4_GET_UINT64(pDesc->transmit_fields.addr_high, pDesc->transmit_fields.addr_low);

    if(desc_paddr != (pXfer->buff.paddr + pXfer->size_bytes - last_desc_byte))
    {
      // USB4_LOG_ERROR("desc->addr (high = 0x%08X ; low = 0x%08X)\n", 
      //     pDesc->transmit_fields.addr_high, pDesc->transmit_fields.addr_low);
      // USB4_LOG_ERROR(" - expected = 0x%lluX\n", 
      //     (UINT64)(pXfer->buff.paddr));
      USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedDescAddr__Params__highaddr_lowaddr, 0,
          pDesc->transmit_fields.addr_high, pDesc->transmit_fields.addr_low);
      USB4_LOG_ERROR_1(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedDescAddr__Params__ExpectedAddr, 0, 
          (UINT64)(pXfer->buff.paddr));
      USB4_ERROR_STACK_MSG(-1, "Addr not expected");
      return -1;
    }

    // Checking is always done to the last desc ...
    if (pDesc->transmit_fields.data_length != exp_bytes)
    {
      // USB4_LOG_ERROR("desc->data_length = 0x%02X, expected = 0x%02X\n", 
      //     pDesc->transmit_fields.data_length, exp_bytes);
      USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedDataLen__Params__DescDataLength_Expected, 0,
          pDesc->transmit_fields.data_length, exp_bytes);
      USB4_ERROR_STACK_MSG(-1, "data length not expected");
      return -1;
    }
  }

#if !defined(USB4_WA_CR_QCTDD06702880_TX_RS_ALWAYS_SET)
  if (((TRUE == pXfer->rs) && (0x1 != pDesc->transmit_fields.request_status)) ||
      ((FALSE == pXfer->rs) && (0x0 != pDesc->transmit_fields.request_status)))
  {
    // USB4_LOG_ERROR("RS = 0x%X, exp = 0x%X\n", 
    //     pDesc->transmit_fields.request_status, 
    //     (UINT32)(pXfer->rs));
    USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedNotDefWaTxRsAlwaysSet__Params__RS_exp, 0, 
        pDesc->transmit_fields.request_status, 
        (UINT32)(pXfer->rs));
    USB4_ERROR_STACK(-1);
    return -1;
  }
#endif /* USB4_WA_CR_QCTDD06702880_TX_RS_ALWAYS_SET */

  if (pDesc->transmit_fields.offset != pXfer->offset)
  {
    // USB4_LOG_ERROR("desc->offset = 0x%02X, expected = 0x%02X\n", 
    //     pDesc->transmit_fields.offset, pXfer->offset);
    USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedErr__Params__DescOffset_Expected, 0, 
        pDesc->transmit_fields.offset, pXfer->offset);
    USB4_ERROR_STACK(-1);
    return -1;
  }

  // Verify DD if needed
  pStatus->dd = (0x0 == pDesc->transmit_fields.descriptor_done) ? FALSE : TRUE;
  pStatus->crcErr = 0;    // na for send transfer
  pStatus->bo = 0;        // na for send transfer

  if (pDesc->transmit_fields.request_status != pDesc->transmit_fields.descriptor_done)
  {
    // USB4_LOG_ERROR("RS=0x%X, DD=0x%X\n", pDesc->transmit_fields.request_status, 
    //    pDesc->transmit_fields.descriptor_done);
    USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyTransmitedErr__Params__RS_DD, 0, pDesc->transmit_fields.request_status, 
        pDesc->transmit_fields.descriptor_done);
    USB4_ERROR_STACK(-1);
    return -1;
  }

  pXfer->bInUseByHW = FALSE;
  return 0;
}

int Usb4HiaVerifyRecieved(usb4_hia_ctx_t* hia_ctx,
                   USB4_hi_xfer* pXfer,
                   USB4_hi_xfer_status* pStatus)
{
  const USB4_hi_recieve_host_desc* pDesc = NULL;
  UINT8* pBuff = NULL;
  // UINT8 buff[16];
  int result;
  UINT32 addr_low;
  UINT32 addr_high;

  if ((NULL == pXfer) || (NULL == pStatus))
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  addr_low = USB4_LOWER32(pXfer->buff.paddr);
  addr_high = USB4_UPPER32(pXfer->buff.paddr);

  // result = hia_ctx->m_recieve[pXfer->ringIdx].ReadDescriptor(buff, pXfer->slotId);
  // if (0 != result)
  // {
  //     USB4_ERROR_STACK(result);
  //     return -1;
  // }

  result = Usb4HiRingGetDescriptorPtr(&hia_ctx->m_recieve[pXfer->ringIdx], &pBuff, pXfer->slotId);
  if (0 != result)
  {
    USB4_ERROR_STACK(result);
    return -1;
  }

  // if (0 != memcmp(buff, pBuff, 16))
  // {
  //     USB4_ERROR_STACK_MSG(-1, "Comparison error");
  //     return -1;
  // }

  pDesc = (const USB4_hi_recieve_host_desc*)(pBuff);


  // Can check this only if size_bytes < 4096, otherwise it might got splitted
  if (pXfer->size_bytes <= USB4_HI_MAX_TR_SIZE)
  {
    UINT32 exp_bytes = 
      (pXfer->size_bytes < USB4_HI_MAX_TR_SIZE) ? pXfer->size_bytes : 0x0;

    // Verify fields are not modified and matching expectation
    if ((addr_low != pDesc->receive_host_fields.addr_low) || 
        (addr_high != pDesc->receive_host_fields.addr_high))
    {
      // USB4_LOG_ERROR("desc->addr (high = 0x%08X ; low = 0x%08X)\n", 
      //     pDesc->receive_host_fields.addr_high, pDesc->receive_host_fields.addr_low);
      // USB4_LOG_ERROR(" - expected = 0x%llX\n", 
      //     (UINT64)(pXfer->buff.paddr));
      USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyRecievedErr__Params__DescAddrHigh_Low, 0,
          pDesc->receive_host_fields.addr_high, pDesc->receive_host_fields.addr_low);
      USB4_LOG_ERROR_1(USB4_LOG_CM, Usb4CmHiaVerifyRecievedErr__Params__Expected, 0,
          (UINT64)(pXfer->buff.paddr));
      USB4_ERROR_STACK_MSG(-1, "Addr not expected");
      result = -1;
    }

    if (pXfer->ringIdx > 0) /* Any data length is OK for control */
    {
      if (pDesc->receive_host_fields.data_length != exp_bytes)
      {
        // USB4_LOG_ERROR("desc->data_length: %u, expected: %u\n",
        //     pDesc->receive_host_fields.data_length, exp_bytes);
        USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyRecievedErr__Params_DataLength_Expected, 0,
            pDesc->receive_host_fields.data_length, exp_bytes);
        USB4_ERROR_STACK_MSG(-1, "data length not expected");
        result = -1;
      }
    }
    else
    {
      pXfer->size_bytes = pDesc->receive_host_fields.data_length;
      pXfer->eof_pdf = pDesc->receive_host_fields.eof_pdf;
    }
  }

  if (pDesc->receive_host_fields.offset != pXfer->offset)
  {
    // USB4_LOG_ERROR("desc->offset = 0x%02X, expected = 0x%02X\n", 
    //     pDesc->receive_host_fields.offset, pXfer->offset);
    USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyRecievedErr__Params_DescOffset_Expected, 0, 
        pDesc->receive_host_fields.offset, pXfer->offset);
    USB4_ERROR_STACK(-1);
    result = -1;
  }

  // Store the data for the response
  pStatus->crcErr = (0x0 == pDesc->receive_host_fields.crc_error) ? FALSE : TRUE;
  pStatus->dd = (0x0 == pDesc->receive_host_fields.descriptor_done) ? FALSE : TRUE;
  pStatus->bo = (0x0 == pDesc->receive_host_fields.buffer_overflow) ? FALSE : TRUE;

  // Verify DD if needed
  if (pXfer->rs != pStatus->dd) // rs should always be 1 according to spec ...
  {
    // USB4_LOG_ERROR("RS=0x%X, DD=0x%X", (UINT32)(pXfer->rs), 
    //     pDesc->receive_host_fields.descriptor_done);
    USB4_LOG_ERROR_2(USB4_LOG_CM, Usb4CmHiaVerifyRecievedErr__Params__RS_DD, 0, (UINT32)(pXfer->rs), 
        pDesc->receive_host_fields.descriptor_done);
    USB4_ERROR_STACK(-1);
    result = -1;
  }

  if (TRUE == pStatus->crcErr)
  {
    USB4_ERROR_STACK_MSG(-1, "CRC Error");
    result = -1;
  }

  if (TRUE == pStatus->bo)
  {
    USB4_ERROR_STACK_MSG(-1, "Buffer overflow");
    result = -1;
  }

  if (0 == result)
  {
    pXfer->bInUseByHW = FALSE;
  }
  return result;
}

int Usb4HiaIsrHanlder(usb4_hia_ctx_t* hia_ctx, UINT32 int_num)
{
  UINT32* addr;
  UINT32 val;

  addr = IO_ISR_ADDR(hia_ctx->m_pModuleBaseAddr);
  val = in_dword(addr);

  hia_ctx->m_interrupt_status |= val;

  if (FALSE == hia_ctx->m_isr_autoclear)
  {
    addr = IO_ISC_ADDR(hia_ctx->m_pModuleBaseAddr);
    out_dword_usb(addr, val);
  }

  return 0;
}

int Usb4HiaGetHwIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32* pMask)
{
  UINT32* addr;

  if (NULL == pMask)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  addr = IO_ISR_ADDR(hia_ctx->m_pModuleBaseAddr);
  *pMask = in_dword(addr);

  return 0;
}

int Usb4HiaGetIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32* pStatus)
{
  if (NULL == pStatus)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  if (0x0 != hia_ctx->m_interrupt_mask)
  {
    *pStatus = hia_ctx->m_interrupt_status;
  }
  else /* polling mode */
  {
    UINT32* addr;
    addr = IO_ISR_ADDR(hia_ctx->m_pModuleBaseAddr);;
    *pStatus = in_dword(addr);
  }

  return 0;
}

int Usb4HiaClearIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32 mask)
{
  if (0x0 != hia_ctx->m_interrupt_mask)
  {
    hia_ctx->m_interrupt_status &= ~mask;
  }
  else /* polling mode */
  {
    UINT32* addr;
    addr = IO_ISC_ADDR(hia_ctx->m_pModuleBaseAddr);
    out_dword_usb(addr, mask);
  }

  return 0;
}

int Usb4HiaSetIntStatus(usb4_hia_ctx_t* hia_ctx, UINT32 mask)
{
  UINT32* addr;

  addr = IO_ISS_ADDR(hia_ctx->m_pModuleBaseAddr);
  out_dword_usb(addr, mask);

  return 0;
}

int Usb4HiaGetIntMask(usb4_hia_ctx_t* hia_ctx, UINT32* pMask)
{
  UINT32* addr;
  UINT32 val;

  if (NULL == pMask)
  {
    USB4_ERROR_STACK_MSG(-1, "NULL input");
    return -1;
  }

  addr = IO_IMR_ADDR(hia_ctx->m_pModuleBaseAddr);
  val = in_dword(addr);

  *pMask = val;

  if (hia_ctx->m_interrupt_mask != val)
  {
    USB4_ERROR_STACK_MSG(-1, "hia_ctx->m_interrupt_mask is different from actual register value in IMR");
    return -1;
  }

  return 0;

}

// Note the similar name, this one has = logic
int Usb4HiaSetIntMask(usb4_hia_ctx_t* hia_ctx, UINT32 mask)
{
  UINT32* addr;

  addr = IO_IMR_ADDR(hia_ctx->m_pModuleBaseAddr);
  out_dword_usb(addr, mask);

  hia_ctx->m_interrupt_mask = mask;

  return 0;
}


int Usb4HiaSetIntMaskClear(usb4_hia_ctx_t* hia_ctx, UINT32 mask)
{
  UINT32* addr;

  addr = IO_IMC_ADDR(hia_ctx->m_pModuleBaseAddr);
  out_dword_usb(addr, mask);

  hia_ctx->m_interrupt_mask &= ~mask;

  return 0;
}


// Note the similar name, this one has |= logic
int Usb4HiaSetIntMaskSet(usb4_hia_ctx_t* hia_ctx, UINT32 mask)
{
  UINT32* addr;

  addr = IO_IMS_ADDR(hia_ctx->m_pModuleBaseAddr);
  out_dword_usb(addr, mask);

  hia_ctx->m_interrupt_mask |= mask;

  return 0;

}
    
int Usb4HiaChangeRingSizeConfig(usb4_hia_ctx_t* hia_ctx, 
                         UINT32 size, UINT32 ringIndex,
                         USB4_HI_RING_TYPE ringType)
{
  USB4_hi_ring_cfg ringCfg = {};

  if(0 == size)
  {
    USB4_ERROR_STACK_MSG(-1, "invalid size 0");
    return -1;
  }

  if (0 != Usb4HiaGetRingConfig(hia_ctx, ringIndex, ringType, &ringCfg))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }
  ringCfg.ring_size = size;
  ringCfg.b_ring_valid = TRUE;

  if (0 != Usb4HiaConfigRing(hia_ctx, ringIndex, ringType, &ringCfg))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }
  return 0;
}

int Usb4HiaChangeRingMode(usb4_hia_ctx_t* hia_ctx,
                   USB4_HI_RING_MODE mode, UINT32 ringIndex,
                   USB4_HI_RING_TYPE ringType)
{
  USB4_hi_ring_cfg ringCfg = {};

  if (0 != Usb4HiaGetRingConfig(hia_ctx, ringIndex, ringType, &ringCfg))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  ringCfg.mode = mode;
  if (USB4_HI_RING_MODE_FRAMED == mode)
  {
    ringCfg.sof_pdf_bmsk = 0x2;
    ringCfg.eof_pdf_bmsk = 0x4;
  }
  else
  {   
    /* TODO: find out real values for the data rings */
    ringCfg.sof_pdf_bmsk = 0x0;
    ringCfg.eof_pdf_bmsk = 0x0;
  }

  if (0 != Usb4HiaConfigRing(hia_ctx, ringIndex, ringType, &ringCfg))
  {
    USB4_ERROR_STACK(-1);
    return -1;
  }

  return 0;
}

usb4_hi_ring_ctx_t* Usb4HiaCtrlRingTx(usb4_hia_ctx_t* hia_ctx)
{
  return &hia_ctx->m_transmit[0];
}

usb4_hi_ring_ctx_t* Usb4HiaCtrlRingRx(usb4_hia_ctx_t* hia_ctx)
{
  return &hia_ctx->m_recieve[0];
}
