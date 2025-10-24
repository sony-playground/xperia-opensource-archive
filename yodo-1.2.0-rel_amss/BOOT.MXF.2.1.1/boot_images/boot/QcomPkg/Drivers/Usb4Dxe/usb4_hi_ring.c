/**---------------------------------------------------------------------------
 *   @file usb4_hi_ring.h
 *
 *   @brief   
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Log.h>
#include <HALhwio.h>
#include <Usb4Utils.h>   /* USB4_LOWER32, USB4_UPPER32 */
#include "usb4_hwio.h"    // required for in_dword, out_dword only
#include "usb4_mem.h"     /* usb4_mem_memcpy */

// #include "usb4_timer.h"   // timers

#include "usb4_hi_ring.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
#define USB4_HI_RING_NUM_RINGS          (0x3)
#define USB4_HI_RING_DESC_SIZE_BYTES    (0x10)

/** 
 * @brief USB4 1.0 spec Table 12-10 section 12.6.2
 *      All offsets are based on this table
 */


#define IO_TRANSMIT_BASE_ADDR_LOW(base, n)                ((UINT32*)((UINT8*)(base) + (0x00000 + (n * 0x10))))
#define IO_TRANSMIT_BASE_ADDR_HIGH(base, n)               ((UINT32*)((UINT8*)(base) + (0x00004 + (n * 0x10))))
#define IO_TRANSMIT_PRODUCER_CONSUMER_INDEXES(base, n)    ((UINT32*)((UINT8*)(base) + (0x00008 + (n * 0x10))))
#define IO_TRANSMIT_RING_SIZE(base, n)                    ((UINT32*)((UINT8*)(base) + (0x0000C + (n * 0x10))))
#define IO_TRANSMIT_RING_CONTROL(base, n)                 ((UINT32*)((UINT8*)(base) + (0x19800 + (n * 0x20))))

#define IO_RECIEVE_BASE_ADDR_LOW_REG(base, n)             ((UINT32*)((UINT8*)(base) + (0x08000 + (n * 0x10))))
#define IO_RECIEVE_BASE_ADDR_HIGH(base, n)                ((UINT32*)((UINT8*)(base) + (0x08004 + (n * 0x10))))
#define IO_RECIEVE_PRODUCER_CONSUMER_INDEXES(base, n)     ((UINT32*)((UINT8*)(base) + (0x08008 + (n * 0x10))))
#define IO_RECIEVE_RING_SIZE(base, n)                     ((UINT32*)((UINT8*)(base) + (0x0800C + (n * 0x10))))
#define IO_RECIEVE_RING_CONTROL(base, n)                  ((UINT32*)((UINT8*)(base) + (0x29800 + (n * 0x20))))
#define IO_RECIEVE_PDF_BIT_MASKS(base, n)                 ((UINT32*)((UINT8*)(base) + (0x29804 + (n * 0x20))))

#define IO_CONTROL_STANDARD(base)                         ((UINT32*)((UINT8*)(base) + 0x39864))
#define IO_ISR_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x37800))
#define IO_ISC_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x37808))
#define IO_ISS_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x37810))
#define IO_IMR_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x38200))
#define IO_IMC_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x38208))
#define IO_IMS_STANDARD(base)                             ((UINT32*)((UINT8*)(base) + 0x38210))
#define IO_RRVC_STANDARD(base)                            ((UINT32*)((UINT8*)(base) + 0x18c00))
#define IO_RRVS_STANDARD(base)                            ((UINT32*)((UINT8*)(base) + 0x19400))
#define IO_HI_CGC_PROP(base)                              ((UINT32*)((UINT8*)(base) - 0x40000 + 0x8000))

#pragma pack(push)
#pragma pack(1)

/** 
 * @brief USB4 1.0 spec 
 *      Producer and consumer indexes sections 12.6.3.2.3 and 12.6.3.3.3 
 */
typedef union
{
  struct prodConsIndexs_fields_t
  {
    UINT32 consumer_idx : 16;
    UINT32 producer_idx : 16;
  } prodConsIndexs_fields;
  UINT32 raw;
} USB4_hi_ring_prodConsIndexs_reg;

/** 
 * @brief USB4 1.0 spec
 *      Ring size section 12.6.3.2.4
 *      Ring and Buffer size section 12.6.3.3.4 
 */
typedef union
{
  struct size_fields_t
  {
    UINT32 ring_size        : 16;  /* number of descriptors in ring */
    UINT32 data_buffer_size : 12;  /* receieve ring only*/
    UINT32 reserved0        : 4;
  } size_fields;
  UINT32 raw;
} USB4_hi_ring_size_reg;

/** 
 * @brief USB4 1.0 spec
 *      Ring Control sections 12.6.3.2.5 and 12.6.3.3.5 
 */
typedef union
{
  struct control_fields_t
  {
    UINT32 reserved0                : 12;
    UINT32 transmit_e2e_hopid       : 11; // valid for recieve ring only
    UINT32 reserved1                : 5;
    UINT32 e2e_flow_control_enable  : 1;
    UINT32 no_snoop_flag            : 1;
    UINT32 raw_mode                 : 1; // 0 for frame, 1 for raw
    UINT32 valid                    : 1;         
  } control_fields;
  UINT32 raw;
} USB4_hi_ring_control_reg;

/** 
 * @brief USB4 1.0 spec
 *      PDF Bit Masks 12.6.3.2.6
 */
typedef union
{
  struct pdfBitMask_fields_t
  {
    UINT32 eof_pdf_bitmask          : 16;
    UINT32 sof_pdf_bitmask          : 16;
  } pdfBitMask_fields;
  UINT32 raw;
} USB4_hi_ring_pdfBitMask_reg;


#pragma pack(pop)



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

int Usb4HiRingInit(usb4_hi_ring_ctx_t* ring_ctx, UINT8* hiBase, UINT32 ringIdx, USB4_HI_RING_TYPE type)
{
  ring_ctx->m_id = 0;
  ring_ctx->m_type = USB4_HI_RING_TYPE_UNINITIALIZED;
  ring_ctx->m_producer = 0;
  ring_ctx->m_lastPostedProducer = 0;
  ring_ctx->m_consumer = 0;
  ring_ctx->m_lastPostedConsumer = 0;
  ring_ctx->m_numQueuedDesc = 0;
  ring_ctx->m_bValid = FALSE;
  ring_ctx->m_bOverrideActive = FALSE;
  ring_ctx->m_interruptEnableOverride = 0;
  ring_ctx->m_requestStatusOverride = 0;

  if ((NULL == hiBase) || (ringIdx >= USB4_HI_RING_NUM_RINGS))
  {
    USB4_ERROR_STACK_MSG(-1, "Invalid input");
    return -1;
  }

  ring_ctx->m_type = type;
  ring_ctx->m_id = ringIdx;

  if (USB4_HI_RING_TYPE_TRANSMIT == ring_ctx->m_type)
  {
    ring_ctx->m_addr.addr_low = IO_TRANSMIT_BASE_ADDR_LOW(hiBase, ringIdx);
    ring_ctx->m_addr.addr_high = IO_TRANSMIT_BASE_ADDR_HIGH(hiBase, ringIdx);
    ring_ctx->m_addr.indexes = IO_TRANSMIT_PRODUCER_CONSUMER_INDEXES(hiBase, ringIdx);
    ring_ctx->m_addr.sizes = IO_TRANSMIT_RING_SIZE(hiBase, ringIdx);
    ring_ctx->m_addr.control = IO_TRANSMIT_RING_CONTROL(hiBase, ringIdx);
    ring_ctx->m_addr.pdf_bitmasks = NULL;

    ring_ctx->m_addr.isr = IO_ISR_STANDARD(hiBase);
    ring_ctx->m_addr.isc = IO_ISC_STANDARD(hiBase);
    ring_ctx->m_addr.iss = IO_ISS_STANDARD(hiBase);
    ring_ctx->m_addr.imr = IO_IMR_STANDARD(hiBase);
    ring_ctx->m_addr.imc = IO_IMC_STANDARD(hiBase);
    ring_ctx->m_addr.ims = IO_IMS_STANDARD(hiBase);
    ring_ctx->m_addr.rrvc = NULL;
    ring_ctx->m_addr.rrvs = NULL;
  }
  else if (USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
  {
    ring_ctx->m_addr.addr_low = IO_RECIEVE_BASE_ADDR_LOW_REG(hiBase, ringIdx);
    ring_ctx->m_addr.addr_high = IO_RECIEVE_BASE_ADDR_HIGH(hiBase, ringIdx);
    ring_ctx->m_addr.indexes = IO_RECIEVE_PRODUCER_CONSUMER_INDEXES(hiBase, ringIdx);
    ring_ctx->m_addr.sizes = IO_RECIEVE_RING_SIZE(hiBase, ringIdx);
    ring_ctx->m_addr.control = IO_RECIEVE_RING_CONTROL(hiBase, ringIdx);
    ring_ctx->m_addr.pdf_bitmasks = IO_RECIEVE_PDF_BIT_MASKS(hiBase, ringIdx);

    ring_ctx->m_addr.isr = IO_ISR_STANDARD(hiBase);
    ring_ctx->m_addr.isc = IO_ISC_STANDARD(hiBase);
    ring_ctx->m_addr.iss = IO_ISS_STANDARD(hiBase);
    ring_ctx->m_addr.imr = IO_IMR_STANDARD(hiBase);
    ring_ctx->m_addr.imc = IO_IMC_STANDARD(hiBase);
    ring_ctx->m_addr.ims = IO_IMS_STANDARD(hiBase);
    ring_ctx->m_addr.rrvc = IO_RRVC_STANDARD(hiBase);
    ring_ctx->m_addr.rrvs = IO_RRVS_STANDARD(hiBase);
  }
  else
  {
    USB4_ERROR_STACK_MSG(-1, "Invaid ring type");
    return -1;
  }
  ring_ctx->m_addr.HI_CGC = IO_HI_CGC_PROP(hiBase);
  return 0;
}

int Usb4HiRingDeInit(usb4_hi_ring_ctx_t* ring_ctx)
{
    usb4_mem_dma_free(&ring_ctx->m_descBuff);
    return 0;
}

int Usb4HiRingSetValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8 valid)
{
    USB4_hi_ring_control_reg reg;
    usb4_utils_timer timer;

    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    
    if (NULL == ring_ctx->m_addr.control)
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }
    reg.raw = in_dword(ring_ctx->m_addr.control);             // read
    reg.control_fields.valid = (0 != valid) ? 0x1 : 0x0;    // modify
    out_dword_usb(ring_ctx->m_addr.control, reg.raw);             // write
    
    ring_ctx->m_bValid = (0 != valid) ? TRUE : FALSE;
    
    if (FALSE == ring_ctx->m_bValid) /* Allow packets to get flushed */
    {
        usb4_timer_Sleep_ms(&timer, 1);
    }

    return 0;
}

int Usb4HiRingGetValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8* pValid)
{
    if (NULL == pValid)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }

    *pValid = (FALSE != ring_ctx->m_bValid) ? 0x1 : 0x0;
    
    return 0;
}

int Usb4HiRingGetHwValid(usb4_hi_ring_ctx_t* ring_ctx, UINT8* pValid)
{
    USB4_hi_ring_control_reg reg;
    
    // no need to check for NULLs since initialize will set the addresses
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }
    
    if (NULL == pValid)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL Input");
        return -1;
    }

    reg.raw = in_dword(ring_ctx->m_addr.control);     // read
    *pValid = (reg.control_fields.valid & 0xFF);
    
    return 0;
}

int Usb4HiRingConfig(usb4_hi_ring_ctx_t* ring_ctx, const USB4_hi_ring_cfg* cfg)
{
    USB4_hi_ring_control_reg control_reg;
    USB4_hi_ring_size_reg size_reg;
    BOOLEAN valid;
    int result;
    
    // no need to check for NULLs since initialize will set the addresses
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }
    
    if ((0x0 == cfg->ring_size) || (cfg->ring_size > USB4_HI_RING_MAX_RING_DESC))
    {
        USB4_ERROR_STACK_MSG(-1, "Required 0 < ring_size <= USB4_HI_RING_MAX_RING_DESC");
        return -1;
    }
    
    if (cfg->ring_size > USB4_HI_RING_MAX_RING_DESC)
    {
        USB4_ERROR_STACK_MSG(-1, "Invlaid: ring_size > USB4_HI_RING_MAX_RING_DESC");
        return -1;
    }
    
    control_reg.raw = 0x0;
    size_reg.raw = 0x0;
    
    result = usb4_mem_memcpy(&ring_ctx->m_cfg, cfg, sizeof(USB4_hi_ring_cfg));
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    //if (USB4_HI_RING_TYPE_RECEIVE == m_type)
    {
       out_dword_usb(ring_ctx->m_addr.HI_CGC, 0x7F); /* By the HPG: Surrount RX ring configuration with clock gating disable: QCTDD06794375 */
    }
    valid = ring_ctx->m_bValid; // Store the value to set it again later if needed
    if (TRUE == valid)
    {
        result = Usb4HiRingSetValid(ring_ctx, 0);
        if (0 != result)
        {
            USB4_ERROR_STACK(result);
            return -1;
        }
    }
    
    usb4_mem_dma_free(&ring_ctx->m_descBuff);
    
    control_reg.control_fields.e2e_flow_control_enable = 
        (TRUE == cfg->b_e2e_flow_ontrol_enabled) ? 0x1 : 0x0;
    
    control_reg.control_fields.no_snoop_flag = 
        (TRUE == cfg->b_no_snoop_flag) ? 0x1 : 0x0;
    
    control_reg.control_fields.raw_mode =
        (USB4_HI_RING_MODE_RAW == cfg->mode) ? 0x1 : 0x0;
    
    control_reg.control_fields.valid = (FALSE != cfg->b_ring_valid) ? 0x1 : 0x0;
    
    if (USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    {
        control_reg.control_fields.transmit_e2e_hopid = cfg->rcv_transmit_e2e_hopid;
    }
        
    size_reg.size_fields.ring_size = 
        (USB4_HI_RING_MAX_RING_DESC == cfg->ring_size) ? 0x0 : cfg->ring_size;
    
    if (USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    {
        USB4_hi_ring_pdfBitMask_reg pdf_reg;
        
        if ((0x0 == cfg->rcv_data_buffer_size_bytes) || 
           (cfg->rcv_data_buffer_size_bytes > USB4_HI_RING_MAX_SIZE_BYTES))
        {
            USB4_ERROR_STACK_MSG(-1, "Required 0 < rcv_data_buffer_size_bytes <= USB4_HI_RING_MAX_SIZE_BYTES");
            return -1;
        }
        
        if (USB4_HI_RING_MAX_SIZE_BYTES == cfg->rcv_data_buffer_size_bytes)
        {
            size_reg.size_fields.data_buffer_size = 0x0;
        }
        else
        {
            size_reg.size_fields.data_buffer_size = cfg->rcv_data_buffer_size_bytes;
        }
        
        pdf_reg.raw = 0x0;
        pdf_reg.pdfBitMask_fields.eof_pdf_bitmask = cfg->eof_pdf_bmsk;
        pdf_reg.pdfBitMask_fields.sof_pdf_bitmask = cfg->sof_pdf_bmsk;
        
        
        out_dword_usb(ring_ctx->m_addr.pdf_bitmasks, pdf_reg.raw); // Write PDF bitmasks
    }
    
    ring_ctx->m_descBuff.size_bytes = cfg->ring_size * USB4_HI_RING_DESC_SIZE_BYTES;
    result = usb4_mem_dma_alloc(&ring_ctx->m_descBuff);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return -1;
    }
    
    // Write descirptors address
    out_dword_usb(ring_ctx->m_addr.addr_low, USB4_LOWER32(ring_ctx->m_descBuff.paddr));
    out_dword_usb(ring_ctx->m_addr.addr_high, USB4_UPPER32(ring_ctx->m_descBuff.paddr));
    
    // Write Sizes register - should reset indexes
    out_dword_usb(ring_ctx->m_addr.sizes, size_reg.raw);          
    ring_ctx->m_producer = 0;
    ring_ctx->m_consumer = 0;
    ring_ctx->m_lastPostedProducer = 0;
    ring_ctx->m_lastPostedConsumer = 0;
    ring_ctx->m_numQueuedDesc = 0;
    
    out_dword_usb(ring_ctx->m_addr.control, control_reg.raw);     // Write control register
    ring_ctx->m_bValid = cfg->b_ring_valid;
    //if (USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    {
        out_dword_usb(ring_ctx->m_addr.HI_CGC, 0x0);
    }
    return 0;
}

int Usb4HiRingGetConfig(usb4_hi_ring_ctx_t* ring_ctx, USB4_hi_ring_cfg* pCfg)
{
    int result;
    
    if (NULL == pCfg)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }
    
    result = usb4_mem_memcpy(pCfg, &ring_ctx->m_cfg, sizeof(USB4_hi_ring_cfg));
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    return 0;
}

int Usb4HiRingGetHwConfig(usb4_hi_ring_ctx_t* ring_ctx, USB4_hi_ring_cfg* pCfg)
{
    if (NULL == pCfg)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }
    
    USB4_ERROR_STACK_MSG(-1, "Not implemented yet...");
    return -1;
}

int Usb4HiRingGetProducerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx)
{
    if (NULL == pIdx)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }
    
    *pIdx = ring_ctx->m_producer;
    return 0;
}

int Usb4HiRingGetConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx)
{
    if (NULL == pIdx)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }
    
    *pIdx = ring_ctx->m_consumer;
    return 0;
}

int Usb4HiRingGetHwProducerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx)
{
    USB4_hi_ring_prodConsIndexs_reg indexes;
    
    // no need to check for NULLs since initialize will set the addresses
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    if (NULL == pIdx)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }
    
    indexes.raw = in_dword(ring_ctx->m_addr.indexes);
    
    *pIdx = indexes.prodConsIndexs_fields.producer_idx;
    return 0;
}

int Usb4HiRingGetHwConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pIdx)
{
    USB4_hi_ring_prodConsIndexs_reg indexes;
    
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    if (NULL == pIdx)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }
    
    indexes.raw = in_dword(ring_ctx->m_addr.indexes);
    
    *pIdx = indexes.prodConsIndexs_fields.consumer_idx;
    return 0;
}


int Usb4HiRingSetHwConsumerIndex(usb4_hi_ring_ctx_t* ring_ctx, UINT32 Idx)
{
    USB4_hi_ring_prodConsIndexs_reg indexes;

    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type)
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    indexes.raw = in_dword(ring_ctx->m_addr.indexes);
    indexes.prodConsIndexs_fields.consumer_idx = Idx;
    out_dword_usb(ring_ctx->m_addr.indexes, indexes.raw);

    return 0;
}

// int Usb4HiRingGetNumQueuedDesc(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pNum)
// {
//     if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
//     {
//         USB4_ERROR_STACK_MSG(-1, "Not initizlized");
//         return -1;
//     }
//     
//     if (NULL == pNum)
//     {
//         USB4_ERROR_STACK_MSG(-1, "Null Input");
//         return -1;
//     }
//     
//     *pNum = ring_ctx->m_numQueuedDesc;
//     // if (USB4_HI_RING_TYPE_TRANSMIT == ring_ctx->m_type)
//     // {
//     //     if (ring_ctx->m_producer >= ring_ctx->m_lastPostedProducer)
//     //     {
//     //         *pNum = (ring_ctx->m_producer - ring_ctx->m_lastPostedProducer);
//     //     }
//     //     else if (ring_ctx->m_lastPostedProducer > ring_ctx->m_producer)
//     //     {
//     //         *pNum = (ring_ctx->m_cfg.ring_size - ring_ctx->m_lastPostedProducer) + ring_ctx->m_producer;
//     //     }
//     // }
//     // else // if (USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
//     // {
//     //     if (ring_ctx->m_consumer >= ring_ctx->m_lastPostedConsumer)
//     //     {
//     //         *pNum = (ring_ctx->m_consumer - ring_ctx->m_lastPostedConsumer);
//     //     }
//     //     else if (ring_ctx->m_lastPostedConsumer > ring_ctx->m_consumer)
//     //     {
//     //         *pNum = (ring_ctx->m_cfg.ring_size - ring_ctx->m_lastPostedConsumer) + ring_ctx->m_consumer;
//     //     }
//     // }
//     
//     return 0;
// }

int Usb4HiRingGetNumAvailableSlots(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pNum)
{
    if (NULL == pNum)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }

    *pNum = (ring_ctx->m_cfg.ring_size - ring_ctx->m_numQueuedDesc);
    
    return 0;
}

int Usb4HiRingPostProducer(usb4_hi_ring_ctx_t* ring_ctx, UINT32 num)
{
    USB4_hi_ring_prodConsIndexs_reg indexes_reg;
    UINT32 to_post_producer;
    
    if (USB4_HI_RING_TYPE_TRANSMIT != ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Increment supported only for transmit ring");
        return -1;
    }
    
    if (num > ring_ctx->m_numQueuedDesc)
    {
        USB4_ERROR_STACK_MSG(-1, "Not enough descriptors are queued");
        return -1;
    }
    
    if (0 == num)
    {
        num = ring_ctx->m_numQueuedDesc;
    }
    
    to_post_producer = ring_ctx->m_lastPostedProducer + num;
    if (to_post_producer >= ring_ctx->m_cfg.ring_size)
    {
        to_post_producer -= ring_ctx->m_cfg.ring_size;
    }

    indexes_reg.raw = 0x0;
    indexes_reg.prodConsIndexs_fields.producer_idx = to_post_producer;
    out_dword_usb(ring_ctx->m_addr.indexes, indexes_reg.raw);
    ring_ctx->m_lastPostedProducer = to_post_producer;
    
    ring_ctx->m_numQueuedDesc -= num;
    return 0;
}

int Usb4HiRingPostConsumer(usb4_hi_ring_ctx_t* ring_ctx, UINT32 num)
{
    USB4_hi_ring_prodConsIndexs_reg indexes_reg;
    UINT32 to_post_cosumer;
    
    if (USB4_HI_RING_TYPE_RECEIVE != ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Increment supported only for transmit ring");
        return -1;
    }
    
    if (num > ring_ctx->m_numQueuedDesc)
    {
        USB4_ERROR_STACK_MSG(-1, "Not enough descriptors are queued");
        return -1;
    }
    
    if (0 == num)
    {
        num = ring_ctx->m_numQueuedDesc;
    }
    
    to_post_cosumer = ring_ctx->m_lastPostedConsumer + num;
    if (to_post_cosumer >= ring_ctx->m_cfg.ring_size)
    {
        to_post_cosumer -= ring_ctx->m_cfg.ring_size;
    }
    
	indexes_reg.raw = 0x0;
    indexes_reg.prodConsIndexs_fields.consumer_idx = to_post_cosumer;
    out_dword_usb(ring_ctx->m_addr.indexes, indexes_reg.raw);
    ring_ctx->m_lastPostedConsumer = to_post_cosumer;
    
    ring_ctx->m_numQueuedDesc -= num;
    return 0;
}

/**
 * @brief Wait for producer to reach last posted consumer
 * @param [timeout_ms] timeout in ms
 * @return 0 on success, other on failure
 */
int Usb4HiRingWaitAllProduced(usb4_hi_ring_ctx_t* ring_ctx, UINT64 timeout_ms)
{
    usb4_utils_timer timer;
    int result;
    UINT32 elapsed_ms = 0;
    USB4_hi_ring_prodConsIndexs_reg indexes;

    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    
    // USB4_LOG_INFO("Ring: %u, transmit: %u\n", ring_ctx->m_id, 
    //                 (ring_ctx->m_type == USB4_HI_RING_TYPE_TRANSMIT) ? 1: 0);
                    
    result = usb4_timer_Start(&timer);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    while ((elapsed_ms < timeout_ms) && (ring_ctx->m_producer != ring_ctx->m_lastPostedConsumer))
    {
        indexes.raw = in_dword(ring_ctx->m_addr.indexes);
        ring_ctx->m_producer = indexes.prodConsIndexs_fields.producer_idx;
        
        result = usb4_timer_GetElapsed_ms(&timer, &elapsed_ms);
        if (0 != result)
        {
            USB4_ERROR_STACK(result);
            return result;
        }
    }
    
    if (ring_ctx->m_producer != ring_ctx->m_lastPostedConsumer)
    {
        USB4_ERROR_STACK_MSG(-1, "Timeout waiting for prodcuer to reach consumer");
        return -1;
    }
    
    return 0;
}

/**
 * @brief Get number of produced descriptors; Modifies m_producer, so returned values need to be used
 * @param[out] Slot of first produced
 * @param[out] number of produced
 * @return 0 on success, other on failure
 */
int Usb4HiRingGetNumberOfProduced(usb4_hi_ring_ctx_t* ring_ctx, UINT32* pSlotId, UINT32* pNum)
{
    USB4_hi_ring_prodConsIndexs_reg indexes;

    if ((NULL == pSlotId)||(NULL == pNum))
    {
        USB4_ERROR_STACK_MSG(-1, "Output argument pointers can't be NULL");
        return -1;
    }

    indexes.raw = in_dword(ring_ctx->m_addr.indexes);
    if (ring_ctx->m_producer <= indexes.prodConsIndexs_fields.producer_idx)
    {
        *pNum = indexes.prodConsIndexs_fields.producer_idx - ring_ctx->m_producer;
    }
    else
    {
        *pNum = ring_ctx->m_cfg.ring_size - ring_ctx->m_producer + indexes.prodConsIndexs_fields.producer_idx;
    }
    *pSlotId = ring_ctx->m_producer;
    ring_ctx->m_producer = indexes.prodConsIndexs_fields.producer_idx;
    return 0;
}


#ifdef USB4_COMPILING_GEN_EMU
int VVHAL_usb4_copss_getDutBase(UINT32 dutIndex,
                                UINT8** dutBaseVirt,
                                UINT64 *dutBasePhys);

static void trigger_veloce(UINT32 val)
{
    UINT8 *coreBaseAddress, *pGeBaseAddr;
    (void)VVHAL_usb4_copss_getDutBase(0, &coreBaseAddress, NULL);
#define GE_DUT_USER_REGS_REG_BASE_OFFS                                         0x01f80000
    pGeBaseAddr = coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;
    out_dword_usb(pGeBaseAddr + 0x14, val);
}
#endif

int Usb4HiRingWaitAllConsumed(usb4_hi_ring_ctx_t* ring_ctx, UINT64 timeout_ms)
{
    usb4_utils_timer timer;
    int result;
    UINT32 elapsed_ms = 0;
    USB4_hi_ring_prodConsIndexs_reg indexes;

    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    
    result = usb4_timer_Start(&timer);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    while ((elapsed_ms < timeout_ms) && (ring_ctx->m_consumer != ring_ctx->m_lastPostedProducer))
    {
        indexes.raw = in_dword(ring_ctx->m_addr.indexes);
        ring_ctx->m_consumer = indexes.prodConsIndexs_fields.consumer_idx;
        ring_ctx->m_producer = indexes.prodConsIndexs_fields.producer_idx;

        if (ring_ctx->m_producer != ring_ctx->m_lastPostedProducer)
        {
            ring_ctx->m_lastPostedProducer = ring_ctx->m_producer;
        }
        
        result = usb4_timer_GetElapsed_ms(&timer, &elapsed_ms);
        if (0 != result)
        {
            USB4_ERROR_STACK(result);
            return result;
        }
    }
    
    if (ring_ctx->m_consumer != ring_ctx->m_lastPostedProducer)
    {
        USB4_hi_ring_control_reg reg;
        reg.raw = in_dword(ring_ctx->m_addr.control);
        if (0 == reg.control_fields.e2e_flow_control_enable)
        {
            USB4_ERROR_STACK_MSG(-1, "Timeout waiting for consumer to reach producer - despite flow control being disabled");
        }

        if (5555 == timeout_ms)
        {
            /* Keep waiting */
            while (ring_ctx->m_consumer != ring_ctx->m_lastPostedProducer)
            {
                indexes.raw = in_dword(ring_ctx->m_addr.indexes);
                ring_ctx->m_consumer = indexes.prodConsIndexs_fields.consumer_idx;
                ring_ctx->m_producer = indexes.prodConsIndexs_fields.producer_idx;
            }
            #ifdef USB4_COMPILING_GEN_EMU
            trigger_veloce(5);
            #endif
        }
        return -1;
    }

    return 0;    
}

int Usb4HiRingQueueDescriptor(usb4_hi_ring_ctx_t* ring_ctx, const UINT8* desc, UINT32* pSlot)
{
    UINT32 num_available;
    UINT8* pDescBuff;
    int result;
    UINT32* pProdCons;
    UINT32 slot;
    
    if ((NULL == desc) || (NULL == pSlot))
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }

    result = Usb4HiRingGetNumAvailableSlots(ring_ctx, &num_available);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return -1;
    }
    
    if (0 == num_available)
    {
        USB4_ERROR_STACK_MSG(-1, "No available slot");
        return -1;
    }
    
    pProdCons = (USB4_HI_RING_TYPE_TRANSMIT == ring_ctx->m_type) ? &ring_ctx->m_producer : &ring_ctx->m_consumer;
    slot = *pProdCons;

    pDescBuff = ring_ctx->m_descBuff.vaddr + (slot * USB4_HI_RING_DESC_SIZE_BYTES);
    result = usb4_mem_memcpy(pDescBuff, desc, USB4_HI_RING_DESC_SIZE_BYTES);
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    desc += USB4_HI_RING_DESC_SIZE_BYTES;
    *pSlot = slot;
    
    // increase producer/consumer index
    ++slot;
    if (slot >= ring_ctx->m_cfg.ring_size)
    {
        slot = 0;
    }
    *pProdCons = slot;
    ++ring_ctx->m_numQueuedDesc;
    
    return 0;
}


int Usb4HiRingReadDescriptor(usb4_hi_ring_ctx_t* ring_ctx, UINT8* desc, UINT32 i)
{
    UINT8* pDesc;
    int result;
    
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    if (i >= ring_ctx->m_cfg.ring_size)
    {
        USB4_ERROR_STACK_MSG(-1, "Invalid index");
        return -1;
    }
    
    pDesc = ring_ctx->m_descBuff.vaddr + (i * USB4_HI_RING_DESC_SIZE_BYTES);
    
    result = usb4_mem_memcpy(desc, pDesc, USB4_HI_RING_DESC_SIZE_BYTES);
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    return 0;
}

int Usb4HiRingGetDescriptorPtr(usb4_hi_ring_ctx_t* ring_ctx, UINT8** ppDesc, UINT32 i)
{
    if (USB4_HI_RING_TYPE_UNINITIALIZED == ring_ctx->m_type) 
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    if (NULL == ppDesc)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }
    
    if (i >= ring_ctx->m_cfg.ring_size)
    {
        USB4_ERROR_STACK_MSG(-1, "Invalid index");
        return -1;
    }
    
    *ppDesc = ring_ctx->m_descBuff.vaddr + (i * USB4_HI_RING_DESC_SIZE_BYTES);
    
    return 0;
}

int Usb4HiRingSetVacancyThreshold(usb4_hi_ring_ctx_t* ring_ctx, UINT32 threshold)
{
    UINT32 val, shift;
    USB4_ASSERT(threshold <= 0xf) /* Only 4 bits are used for threshold */
    if(USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    {
        val = in_dword(ring_ctx->m_addr.rrvc);
        shift  = ring_ctx->m_id*4;
        val &= ~(0xf<<shift);
        val |= (threshold<<shift);
        out_dword_usb(ring_ctx->m_addr.rrvc, val);
    }
    return 0;
}

int Usb4HiRingGetVacancyThresholdStatus(usb4_hi_ring_ctx_t* ring_ctx, BOOLEAN* pStatus)
{
    UINT32 val;
    if(USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    {
        val = in_dword(ring_ctx->m_addr.rrvs);
        *pStatus = (0 != (0x1 & (val>>ring_ctx->m_id)));
    }
    return 0;
}

int Usb4HiRingGetVacancyInterruptStatus(usb4_hi_ring_ctx_t* ring_ctx, BOOLEAN* pStatus)
{
    UINT32 mask, value;
    USB4_ASSERT(NULL != pStatus)
    USB4_ASSERT(USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    mask = (0x1 << ring_ctx->m_id)<<6;

    value = in_dword(ring_ctx->m_addr.isr);
    *pStatus = (0 != (value & mask));
    return 0;
}

int Usb4HiRingClearVacancyInterrupt(usb4_hi_ring_ctx_t* ring_ctx)
{
    UINT32 mask, value;
    USB4_ASSERT(USB4_HI_RING_TYPE_RECEIVE == ring_ctx->m_type)
    mask = (0x1 << ring_ctx->m_id)<<6;

    out_dword_usb(ring_ctx->m_addr.isc, mask);
    value = in_dword(ring_ctx->m_addr.isr);
    USB4_ASSERT(0 == (value & mask))
    return 0;
}

int Usb4HiRingFlushRing(usb4_hi_ring_ctx_t* ring_ctx, UINT32 timeout_ms)
{
    UINT32 clear_mask, old_mask, new_mask;
    USB4_hi_ring_control_reg reg;
    int result = 0;

    if (NULL == ring_ctx->m_addr.control)
    {
        USB4_ERROR_STACK_MSG(-1, "Not initizlized");
        return -1;
    }

    if (USB4_HI_RING_TYPE_TRANSMIT != ring_ctx->m_type)
    {
        USB4_ERROR_STACK_MSG(-1, "Can't call on RX ring");
        return -1;
    }

    out_dword_usb(ring_ctx->m_addr.HI_CGC, 0x7F);

    reg.raw = in_dword(ring_ctx->m_addr.control);
    if (reg.control_fields.e2e_flow_control_enable)
    {
        old_mask = in_dword(ring_ctx->m_addr.imr);
        clear_mask = (((0x1 << ring_ctx->m_id)<<6)|
                     ((0x1 << ring_ctx->m_id)<<3)|
                      (0x1 << ring_ctx->m_id));

        out_dword_usb(ring_ctx->m_addr.imc, clear_mask);
        new_mask = in_dword(ring_ctx->m_addr.imr);
        USB4_ASSERT(0 == (new_mask & clear_mask))

        reg.control_fields.e2e_flow_control_enable = 0x0;
        out_dword_usb(ring_ctx->m_addr.control, reg.raw);

        result = Usb4HiRingWaitAllConsumed(ring_ctx, timeout_ms);

        reg.control_fields.valid = 0;
        out_dword_usb(ring_ctx->m_addr.control, reg.raw);

        if (new_mask != old_mask)
        {
            out_dword_usb(ring_ctx->m_addr.ims, old_mask);
        }
    }
    else
    {
        reg.control_fields.valid = 0;
        out_dword_usb(ring_ctx->m_addr.control, reg.raw);
    }
    ring_ctx->m_bValid = FALSE;
    out_dword_usb(ring_ctx->m_addr.HI_CGC, 0x0);

    return result;
}
