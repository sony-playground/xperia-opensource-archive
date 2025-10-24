/**---------------------------------------------------------------------------
 *   @file usb4_dp_aux_platform.c
 *
 *   @brief   Implements dp aux apis
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Usb4Utils.h>
#include <HALhwio.h>
#include "msmhwio_usb4.h"
// #include "VVHAL_usb4_logger.h"          // logger apis
// #include "VVHAL_usb4_mem.h"             // memcpy
// #include "VVHAL_usb4_timer.h"           // timer apis
#include "usb4_platform_defs.h"   // USB4_NUM_OF_CORES
// 
// #include "VVHAL_usb4_hwioreg_core.h"    // HWIO symbols
#include "usb4_hwio.h"            // HWIO macros
#include "usb4_dp_aux.h"          // APIs implemented in this file
#include "Usb4Log.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/
typedef struct
{
    USB4_DP_AUX_PACKET_TYPE type;
    UINT32 pdf;
} USB4_packet_to_pdf;


#pragma pack(push)
#pragma pack(1)


/** @brief USB4 v1 spec, Figure 10-8. HPD Packet Format */
typedef struct
{
    UINT32 ecc           : 8;          
    UINT32 reserved      : 23;   
    UINT32 plug          : 1;
} USB4_dp_aux_hpd_packet;

/** 
  * @brief USB4 v1 spec, Figure 10-9. SET_CONFIG Packet Format is partially
  *       written by HW, this descriptor is matching the SWI
  */
typedef struct
{
    UINT32 msg_data                 : 8;
    UINT32 msg_type                 : 8;
    UINT32 link_rate_0              : 1;
    UINT32 lane_cnt                 : 3;
    UINT32 reserved_0               : 1;
    UINT32 link_rate_1              : 1;
    UINT32 training_pattern_support : 2;
    UINT32 ecc                      : 8;
} USB4_dp_aux_set_config_packet;

/** @brief USB4 v1 spec, Figure 10-10. Ack Packet Format */
typedef struct
{
    UINT32 ecc           : 8;          
    UINT32 reserved      : 20;   
    UINT32 type          : 4;  
} USB4_dp_aux_ack_packet;

#pragma pack(pop)

/* --------------------------------------------------------------------------
 * Static variables
 *--------------------------------------------------------------------------*/
/** @brief mapping according to USB4.0 ver 1 table 10-3 */
static const USB4_packet_to_pdf s_type_pdf_map[] =
{
    {USB4_DP_AUX_PACKET_TYPE_AUX,           0x0},
    {USB4_DP_AUX_PACKET_TYPE_HPD_STATUS,    0x1},
    {USB4_DP_AUX_PACKET_TYPE_SET_CONFIG,    0x2},
    {USB4_DP_AUX_PACKET_TYPE_ACK_PACKET,    0x3}, 
    {USB4_DP_AUX_PACKET_TYPE_RES0,          0x4}, 
    {USB4_DP_AUX_PACKET_TYPE_RES1,          0x5}, 
    {USB4_DP_AUX_PACKET_TYPE_RES2,          0x6}, 
    {USB4_DP_AUX_PACKET_TYPE_RES3,          0x7}, 
    {USB4_DP_AUX_PACKET_TYPE_RES4,          0x8}, 
    {USB4_DP_AUX_PACKET_TYPE_RES5,          0x9}, 
    {USB4_DP_AUX_PACKET_TYPE_RES6,          0xA}, 
    {USB4_DP_AUX_PACKET_TYPE_RES7,          0xB}, 
    {USB4_DP_AUX_PACKET_TYPE_RES8,          0xC}, 
    {USB4_DP_AUX_PACKET_TYPE_RES9,          0xD}, 
    {USB4_DP_AUX_PACKET_TYPE_RES10,         0xE}, 
    {USB4_DP_AUX_PACKET_TYPE_RES11,         0xF}, 

};

/* --------------------------------------------------------------------------
 * Static functions
 *--------------------------------------------------------------------------*/
static int typeToPdf(USB4_DP_AUX_PACKET_TYPE type, UINT32* pPdf)
{
    for (UINT32 i = 0; i < ARR_SIZE(s_type_pdf_map); ++i)
    {
        if (type == s_type_pdf_map[i].type)
        {
            *pPdf = s_type_pdf_map[i].pdf;
            return 0;
        }
    }
    
    USB4_ERROR_STACK_MSG(-1, "Could not find pdf");
    return -1;
}

static int pdfToType(UINT32 pdf, USB4_DP_AUX_PACKET_TYPE* pType)
{
    for (UINT32 i = 0; i < ARR_SIZE(s_type_pdf_map); ++i)
    {
        if (pdf == s_type_pdf_map[i].pdf)
        {
            *pType = s_type_pdf_map[i].type;
            return 0;
        }
    }
    
    USB4_ERROR_STACK_MSG(-1, "Could not find type");
    return -1;
}

#define REG_MAP(reg, status)  { HWIO_FMSK(USB4_DP_AUX_SW_INT_STATUS, reg), USB4_DP_AUX_STATUS_##status }
typedef struct
{
    UINT32 regbit;
    UINT32 status;
} IntRegToSwMap;

static const IntRegToSwMap s_pIrqMap[] =
{
    REG_MAP(TX_PKT_DONE_IRQ,            TX_PKT_DONE_IRQ),
    REG_MAP(RX_PKT_RECEIVED_IRQ,        RX_PKT_RECEIVED_IRQ),
    REG_MAP(ACK_TIMEOUT_IRQ,            ACK_TIMEOUT_IRQ),
    REG_MAP(CLK_SYNC_N_PKTS_IRQ,        CLK_SYNC_N_PKTS_IRQ),
    REG_MAP(RST_ACK_IRQ,                RST_ACK_IRQ),
    REG_MAP(BLOCK_TX_ACK_IRQ,           BLOCK_TX_ACK_IRQ),
    REG_MAP(PATH_TEARDOWN_IRQ,          PATH_TEARDOWN_IRQ),
    REG_MAP(ACK_RECEIVED_IRQ,           ACK_RECEIVED_IRQ),
    REG_MAP(HPD_UNPLUG_RECEIVED_IRQ,    HPD_UNPLUG_RECEIVED_IRQ),
    REG_MAP(HPD_PLUG_RECEIVED_IRQ,      HPD_PLUG_RECEIVED_IRQ),
    REG_MAP(IRQ_RECEIVED_IRQ,           HPD_IRQ_RECEIVED_IRQ),
};

static int regValToStatus(UINT32 regVal, UINT32* pStatus)
{
    const IntRegToSwMap* pMap;
    
    *pStatus = 0;
    
    for (UINT32 i = 0; i < ARR_SIZE(s_pIrqMap); ++i)
    {
        pMap = s_pIrqMap + i;
        if (0x0 != (regVal & pMap->regbit))
        {
            *pStatus |= pMap->status;
        }
    }
    
    return 0;
}

int Usb4DpAuxClearRxBuffer(usb4_dp_aux_ctx_t* usb4_dp_aux)
{

    /* Pop entry */
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_RX_BUFFER_CLR, -1);

    /* Clear the status */
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_CLR, HWIO_FMSK(USB4_DP_AUX_SW_INT_CLR, RX_PKT_RECEIVED_CLR));

    return 0;
}

int Usb4DpAuxEnableAdapter(usb4_dp_aux_ctx_t* usb4_dp_aux)
{
    UINT8* pBase = usb4_dp_aux->m_moduleBase - DP_IN_AP_AUX_PROP_REG_BASE_OFFS +
                                  DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS;
    
    HWIO_OUTX(pBase, USB4_DPINAP_ADP_DP_CS_0_STANDARD , 0xC0000000); 
    return 0;
} 

static int statusToRegVal(UINT32 status, UINT32* pVal)
{
    const IntRegToSwMap* pMap;
    
    *pVal = 0;
    
    for (UINT32 i = 0; i < ARR_SIZE(s_pIrqMap); ++i)
    {
        pMap = s_pIrqMap + i;
        if (0x0 != (status & pMap->status))
        {
            *pVal |= pMap->regbit;
        }
    }
    
    return 0;
}

/* --------------------------------------------------------------------------
 * Class Functions implementation
 *--------------------------------------------------------------------------*/
 
int Usb4DpAuxInit(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT8* dutBase, UINT32 coreId)
{
    if ((coreId >= USB4_NUM_OF_CORES) || (NULL == dutBase))
    {
        USB4_ERROR_STACK_MSG(-1, "Invalid input");
        return -1;
    }

    usb4_dp_aux->m_moduleBase = NULL;
    usb4_dp_aux->m_coreId = 0;
    usb4_dp_aux->m_swIntStatus = 0;
    // m_cfg()

    usb4_dp_aux->m_moduleBase = dutBase + DP_IN_AP_AUX_PROP_REG_BASE_OFFS;
    usb4_dp_aux->m_coreId = coreId;

    return 0;
}

int Usb4DpAuxConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const USB4_dp_aux_cfg* pCfg)
{
    UINT32 mask;
    
    usb4_dp_aux->m_cfg.interrupt_mode = pCfg->interrupt_mode;
    mask = (TRUE == usb4_dp_aux->m_cfg.interrupt_mode) ? 0xFFF : 0x0;
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_EN, mask);
    
    usb4_dp_aux->m_cfg.auto_ack = pCfg->auto_ack;
    // TODO write auto ack
    
    usb4_dp_aux->m_cfg.hw_ctrl_hpd_status = pCfg->hw_ctrl_hpd_status;
    // TODO write hpd status
    
    return 0;
}

int Usb4DpAuxGetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_cfg* pCfg)
{
    pCfg->interrupt_mode = usb4_dp_aux->m_cfg.interrupt_mode;
    pCfg->auto_ack = usb4_dp_aux->m_cfg.auto_ack;
    pCfg->hw_ctrl_hpd_status = usb4_dp_aux->m_cfg.hw_ctrl_hpd_status;
    return 0;
}

int Usb4DpAuxWrite(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_xfer* pXfer)
{
    UINT8* payload_addr;
    UINT32* buff;
    UINT32 hdr = 0x0;
    UINT32 pdf;
    UINT32 num_dwords = USB4_DP_AUX_MAX_PACKET_BYTES >> 2;
    UINT32 length = 0;
    UINT32 mask;

    if (NULL == pXfer)
    {
        USB4_ERROR_STACK_MSG(-1, "Input error");
        return -1;
    }
    
    if ((0 == pXfer->size_bytes) || (pXfer->size_bytes > USB4_DP_AUX_MAX_PACKET_BYTES)) 
    {
        USB4_ERROR_STACK_MSG(-1, "Num bytes between 1 and 20");
        return -1;
    }
    
    // Make sure status is cleared before sending
    if (0 != Usb4DpAuxGetStatus(usb4_dp_aux, &mask))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    if (0x0 != (USB4_DP_AUX_STATUS_TX_PKT_DONE_IRQ & mask))
    {
        USB4_ERROR_STACK_MSG(-1, "Can't issue TX before clearing TX PKT done");
        return -1;
    }
        
    // Fill up payload registers (all 5 of theme)
    payload_addr = HWIO_ADDRX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_TX_PAYLOAD_0);
    buff = (UINT32*)(pXfer->buff);
    for (UINT32 i = 0; i < num_dwords; ++i)
    {
        out_dword(payload_addr, buff[i]);
        payload_addr += sizeof(UINT32);
    }
    
    if (0 != typeToPdf(pXfer->type, &pdf)) // table 10-3
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    length = pXfer->size_bytes;
    if (USB4_DP_AUX_PACKET_TYPE_AUX == pXfer->type)
    {
        length += 5;
    }
    
    hdr = HWIO_FVAL(USB4_DP_AUX_TX_HDR, TRIGGER, 0x1) |
          HWIO_FVAL(USB4_DP_AUX_TX_HDR, LENGTH, length) |
          // HWIO_FVAL(USB4_DP_AUX_TX_HDR, HOPID, 0x0) | this is read only
          HWIO_FVAL(USB4_DP_AUX_TX_HDR, SUPPID, 0x0) | // 0x0 in tunneled packets table 5-1
          HWIO_FVAL(USB4_DP_AUX_TX_HDR, PDF, pdf); // table 10-3
    
    // Write the header
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_TX_HDR, hdr);
    
    if (pXfer->timeout_ms > 0)
    {
        if (0 != Usb4DpAuxWaitWriteDone(usb4_dp_aux, pXfer->timeout_ms))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    
    return 0;
}

int Usb4DpAuxWaitWriteDone(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 timeout_ms)
{
    UINT32 mask;
    
    mask = USB4_DP_AUX_STATUS_TX_PKT_DONE_IRQ;
    if (0 != Usb4DpAuxWaitForStatus(usb4_dp_aux, mask, timeout_ms))
    {
        USB4_ERROR_STACK(-1);
        return 1;
    }
    
    if (0 != Usb4DpAuxClearStatus(usb4_dp_aux, mask))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    return 0;
}

int Usb4DpAuxIsRcvPending(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_DP_AUX_RX_STATUS* pPending)
{
    UINT32 pending_mask;
    UINT32 error_mask;
    UINT32 status;
    
    if (NULL == pPending)
    {
        USB4_ERROR_STACK_MSG(-1, "NULL input");
        return -1;
    }
    
    if (0 != Usb4DpAuxGetStatus(usb4_dp_aux, &status))
    {
        USB4_ERROR_STACK_MSG(-1, "Timed out waiting for TX sent status");
        return -1;
    }
    
    pending_mask = USB4_DP_AUX_STATUS_RX_PKT_RECEIVED_IRQ;
    
    error_mask = USB4_DP_AUX_STATUS_UNCORRECT_ERROR;
    
    if (0x0 != (status & pending_mask))
    {
        *pPending = USB4_DP_AUX_RX_STATUS_PENDING;
    }
    else if (0x0 != (status & error_mask))
    {
        *pPending = USB4_DP_AUX_RX_STATUS_UNCORRECTABLE_ERROR;
    }
    else
    {
        *pPending = USB4_DP_AUX_RX_STATUS_NOT_PENDING;
    }
    
    return 0;
}


int Usb4DpAuxRead(usb4_dp_aux_ctx_t* usb4_dp_aux, USB4_dp_aux_xfer* pXfer)
{
    UINT32 elapsed_ms;
    UINT32* buff;
    UINT8* payload_addr;
    UINT32 val;
    UINT32 hdr;
    UINT32 pdf;
    UINT32 num_dwords = USB4_DP_AUX_MAX_PACKET_BYTES >> 2;
    USB4_DP_AUX_RX_STATUS pending = USB4_DP_AUX_RX_STATUS_NOT_PENDING;
    BOOLEAN interruptMode;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    
    if (0 != usb4_timer_Start(&timer))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    /* Save current configuration */
    USB4_dp_aux_cfg cfg;

    if(0 != Usb4DpAuxGetConfig(usb4_dp_aux, &cfg))
    {
        USB4_ERROR_STACK_MSG(-1, "No packet is pending");
        return -1;            
    }
    
    /* Save interrupt mode */
    interruptMode = cfg.interrupt_mode;

    elapsed_ms = 0;
    
    /* Wait for Rx fifo to fill up */
    while (USB4_DP_AUX_RX_STATUS_NOT_PENDING == pending)
    {
        if (elapsed_ms > pXfer->timeout_ms)
        {
            USB4_ERROR_STACK_MSG(-1, "Timed out waiting for TX sent status");
            return -1;
        }
        
        if (0 != Usb4DpAuxIsRcvPending(usb4_dp_aux, &pending))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
        
        /* No more packets to read */
        if (0 != usb4_timer_GetElapsed_ms(&timer, &elapsed_ms))
        {
            /* Resotre configuration */
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    

    if (USB4_DP_AUX_RX_STATUS_UNCORRECTABLE_ERROR == pending)
    {
        USB4_ERROR_STACK_MSG(-1, "Uncorrectable error");
        return -1;
    }
    else if (USB4_DP_AUX_RX_STATUS_PENDING != pending)
    {
        USB4_ERROR_STACK_MSG(-1, "No packet is pending");
        return -1;
    } 
    
    cfg.interrupt_mode = FALSE;
    
    /* Mask all interrupts */
    if(0 != Usb4DpAuxConfig(usb4_dp_aux, &cfg))
    {
        USB4_ERROR_STACK_MSG(-1, "Failed to set config");
        return -1;            
    }    
    
    /* Resotre the interrupt field but don't write back yet */
    cfg.interrupt_mode = interruptMode;

    /* Read the payload registers */
    payload_addr = HWIO_ADDRX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_RX_BUF_PAYLOAD_0);
    buff = (UINT32*)(pXfer->buff);

    for (UINT32 i = 0; i < num_dwords; ++i)
    {
        buff[i] = in_dword(payload_addr); 
        payload_addr += sizeof(UINT32);
    }
   
    
    /* Read the header */
    hdr = HWIO_INX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_RX_BUF_HDR);
    pdf = USB4_HWIO_FVAL_FROM_RVAL(USB4_DP_AUX_RX_BUF_HDR, PDF, hdr);
    
    if (0 != pdfToType(pdf, &(pXfer->type)))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    
    pXfer->size_bytes = USB4_HWIO_FVAL_FROM_RVAL(USB4_DP_AUX_RX_BUF_HDR, LENGTH, hdr);
    if (USB4_DP_AUX_PACKET_TYPE_AUX == pXfer->type)
    {
        pXfer->size_bytes -= 5;
    }
    
    // Verify number of bytes received are matching expectation
    switch(pXfer->type)
    {
        case USB4_DP_AUX_PACKET_TYPE_HPD_STATUS:
        case USB4_DP_AUX_PACKET_TYPE_SET_CONFIG:
        case USB4_DP_AUX_PACKET_TYPE_ACK_PACKET:
            if (4 != pXfer->size_bytes)
            {
                Usb4Log1(USB4_LOG_CFG, Usb4DpAuxReadExpected4BytesError__Params__ReceivedNumBytes, 0, pXfer->size_bytes);
                // USB4_LOG_ERROR("Received %u bytes, expected 4 bytes\n", pXfer->size_bytes);
                USB4_ERROR_STACK(-1);
                return -1;
            }
        case USB4_DP_AUX_PACKET_TYPE_AUX:
           break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unknown type");
            return -1;
    }
    
    /* Pop top entry */
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_RX_BUFFER_CLR, 0x1);

    /* Clear the status */
    val = USB4_DP_AUX_STATUS_RX_PKT_RECEIVED_IRQ;
    if (0 != Usb4DpAuxClearStatus(usb4_dp_aux, val))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    /* Check if we have more enries in the FIFO*/
    if (0 != Usb4DpAuxIsRcvPending(usb4_dp_aux, &pending))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    /* If we are done resotre the interrupts */    
    if(USB4_DP_AUX_RX_STATUS_NOT_PENDING == pending)
    {
        if(0 != Usb4DpAuxConfig(usb4_dp_aux, &cfg))
        {
            USB4_ERROR_STACK_MSG(-1, "Failed to set config");
            return -1;            
        }    
    }
        
    return 0;
}

int Usb4DpAuxSendSetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const USB4_dp_aux_set_config* pCfg)
{
    USB4_dp_aux_xfer xfer = {};
    USB4_dp_aux_set_config_packet* pPkt;
        
    // Fill up buffer with data
    pPkt = (USB4_dp_aux_set_config_packet*)(xfer.buff);
    
    pPkt->ecc = 0x0;
    
    pPkt->link_rate_0 = (pCfg->link_rate & 0x1);
    pPkt->lane_cnt = pCfg->lane_cnt;
    pPkt->reserved_0 = 0x1; // reserved should be set to 0x1 according to spec
    pPkt->link_rate_1 = (pCfg->link_rate & 0x2) >> 1;
    pPkt->training_pattern_support = pCfg->tps;
    
    pPkt->msg_type = pCfg->msg_type;
    pPkt->msg_data = pCfg->msg_data;
    
    // Write set config
    xfer.type = USB4_DP_AUX_PACKET_TYPE_SET_CONFIG;
    xfer.timeout_ms = pCfg->timeout_ms;
    xfer.size_bytes = 0x4;
    if (0 != Usb4DpAuxWrite(usb4_dp_aux, &xfer))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    return 0;
}

int Usb4DpAuxParseSetConfig(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, 
                                      USB4_dp_aux_set_config* pCfg)
{
    const USB4_dp_aux_set_config_packet* pPkt;
    UINT32 linkrate;
    
    // cast buffer to packet
    pPkt = (const USB4_dp_aux_set_config_packet*)(pBuff);
    linkrate = (pPkt->link_rate_1 << 1) | pPkt->link_rate_0;
    
    // Parse packet
    pCfg->msg_data = pPkt->msg_data;
    pCfg->msg_type = (USB4_DP_AUX_SET_CFG_MSG_TYPE)(pPkt->msg_type);
    pCfg->link_rate = (USB4_DP_AUX_SET_CFG_LINK_RATE)(linkrate);
    pCfg->lane_cnt = (USB4_DP_AUX_SET_CFG_LANE_CNT)(pPkt->lane_cnt);    
    pCfg->tps = (USB4_DP_AUX_SET_CFG_TPS)(pPkt->training_pattern_support);
    
    return 0;
}

int Usb4DpAuxParseHpdEvent(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, BOOLEAN* pPlug)
{
    const USB4_dp_aux_hpd_packet* pPkt;
    
    pPkt = (const USB4_dp_aux_hpd_packet*)(pBuff);
    
    *pPlug = (0x1 == pPkt->plug) ? TRUE : FALSE;
    
    return 0;
}

int Usb4DpAuxParseAckPacket(usb4_dp_aux_ctx_t* usb4_dp_aux, const UINT8* pBuff, 
                                      USB4_DP_AUX_ACK_TYPE* pType)
{
    const USB4_dp_aux_ack_packet* pPkt;
    
    pPkt = (const USB4_dp_aux_ack_packet*)(pBuff);
    
    *pType = (USB4_DP_AUX_ACK_TYPE)(pPkt->type);
    
    return 0;
}

int Usb4DpAuxGetHpdStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT8* pPlug)
{
    UINT32 plug = 0;
       
    plug = HWIO_INXF(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_HPD_STATUS, HPD_STATUS);
    
    *pPlug = (0x1 == plug) ? TRUE : FALSE;
    
    return 0;
}

int Usb4DpAuxGetStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32* pStatus)
{
    UINT32 regval = 0x0;
    if (NULL == pStatus)
    {
        USB4_ERROR_STACK_MSG(-1, "Null Input");
        return -1;
    }
    
    if (FALSE == usb4_dp_aux->m_cfg.interrupt_mode)
    {
        regval = HWIO_INX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_STATUS);
        if (0 != regValToStatus(regval, pStatus))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
        
        regval = HWIO_INX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_STATUS);
        if (0x0 != (regval & HWIO_FMSK(USB4_DP_AUX_STATUS, UNCORRECT_ERROR)))
        {
            *pStatus |= USB4_DP_AUX_STATUS_UNCORRECT_ERROR;
        }
    }
    else
    {
        *pStatus = usb4_dp_aux->m_swIntStatus;
    }
    
    return 0;
}

int Usb4DpAuxClearStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 mask)
{
    UINT32 regval = 0x0;
    
    if (0 != statusToRegVal(mask, &regval))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    if (FALSE == usb4_dp_aux->m_cfg.interrupt_mode)
    {
        HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_CLR, regval);
    }
    else
    {
        usb4_dp_aux->m_swIntStatus &= ~regval;
    }
    
    return 0;
}

int Usb4DpAuxIsrHandler(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 int_source)
{
    UINT32 regval;
    UINT32 status;
    
    (void) int_source;
    
    regval = HWIO_INX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_STATUS);
    
    /* Clear the interrupt */
    HWIO_OUTX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_SW_INT_CLR, regval);
    
    if (0 != regValToStatus(regval, &status))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    regval = HWIO_INX(usb4_dp_aux->m_moduleBase, USB4_DP_AUX_STATUS);
    if (0x0 != (regval & HWIO_FMSK(USB4_DP_AUX_STATUS, UNCORRECT_ERROR)))
    {
        status |= USB4_DP_AUX_STATUS_UNCORRECT_ERROR;
    }

    /* Append interrupt status */
    usb4_dp_aux->m_swIntStatus |= status;
    
    return 0;
}

int Usb4DpAuxWaitForStatus(usb4_dp_aux_ctx_t* usb4_dp_aux, UINT32 mask, UINT32 timeout_ms)
{
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    UINT32 elapsed_ms;
    UINT32 status = 0;

    if (0 != usb4_timer_Start(&timer))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    /* Wait for the mask status */
    while ((mask) != (status & mask))
    {
        if (0 != Usb4DpAuxGetStatus(usb4_dp_aux, &status))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
        
        if (0 != usb4_timer_GetElapsed_ms(&timer, &elapsed_ms))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }

        if (elapsed_ms > timeout_ms)
        {
            USB4_ERROR_STACK_MSG(-1, "Timed out waiting for sent update");
            goto ErrorHandling;
        }
    }

    return 0;

ErrorHandling:
    return -1;
}
