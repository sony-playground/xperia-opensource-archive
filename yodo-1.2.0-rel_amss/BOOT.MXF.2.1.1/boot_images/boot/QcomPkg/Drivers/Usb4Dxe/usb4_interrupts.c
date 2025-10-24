/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_interrupts.c
 *
 *  @brief :  usb4 core Driver
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include "usb4_interrupts.h"
// #include "VVHAL_usb4_mem.h"      /**< DMA API declaration, and structs */
// #include "VVHAL_usb4_logger.h"   /**< Logging utilities */
// #include "VVDRV_deo.h"           /**< DEO mempool and dma */
// #include "VVHAL_usb4_platform.h"
// #include "VVHAL_usb4_platform_defs.h"
// #include "VVDRV_usb4_cm.h"
// #include "VVDRV_usb4_qdrv.h"
// #include "VVDRV_usb4_pd.h"
// #include "VVDRV_usb4_power_manager.h"

/*----------------------------------------------------------------------------
 * Macro Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Globals
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions
 *--------------------------------------------------------------------------*/
// void VVDRV_usb4_generic_isr_CONTROL_PACKET(uint32 int_source, void *user_data)
// {
//     VVDRV_usb4_cm* pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
//     if (NULL == pCm)
//     {
//         return;
//     }
// 
//     if (0 == pCm->ControlPacketHandler(FALSE, NULL))
//     {
//         //clear interrupt source
//         pCm->Control().m_rxRing.PlatformClearInterrupt();
//     }
//     else
//     {
//         pCm->m_logger.StoreEvent(USB4_CM_EVENT_CONTROL_ADAPTER_FAIL);
//     }
// }

/*------------------------------------------------------------------------*/

// static UINT32 s_usb4_pd_attach_timeout_ms = 1000;
void VVDRV_usb4_interrupts_isr_pd_connect(UINT32 int_source, void *user_data)
{
#if 0 // TODO: AC Defer porting, use polling mode
    VVDRV_usb4_cm* pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
    USB4_pd_info pdInfo = { };

    if ((NULL == pCm) || (NULL == pCm->m_pQdrv))
    {
        return;
    }

    // TODO Need to determine based on SPMI PIC int status which core is it...
    
    // TODO need to handle this in interrupt mode instead polling
    if (0 != pCm->m_pQdrv->m_Platform->PD()->Attach(s_usb4_pd_attach_timeout_ms, &pdInfo))
    {
        USB4_ERROR_STACK_MSG(-1, "Error in PD Attach\n");
        return;
    }

    if (USB4_PD_CC_ORIENTATION_OPEN == pdInfo.cc_orientation)
    {
        if (0 != pCm->m_pQdrv->PhysicalDisconnectUc())
        {
            USB4_ERROR_STACK_MSG(-1, "Error in signaling physical cable disconnect ot uC\n");
            return;
        }
    }
    else
    {
        if (0 != pCm->HandleHostRouterCableConnect(0, &pdInfo))
        {
            USB4_ERROR_STACK_MSG(-1, "Error in cable connection handling\n");
            return;
        }
    }
#endif // TODO: AC Defer porting, use polling mode
}

/*------------------------------------------------------------------------*/

void VVDRV_usb4_interrupts_isr_uc(UINT32 int_source, void *user_data)
{
#if 0 // TODO: AC Defer porting, use polling mode
    VVDRV_usb4_cm* pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
    if ((NULL == pCm) || (NULL == pCm->m_pQdrv))
    {
        return;
    }
    pCm->m_pQdrv->m_Platform->uC()->HandleUcEvents();
#endif // TODO: AC Defer porting, use polling mode
}

/*------------------------------------------------------------------------*/
void VVDRV_usb4_interrupts_isr_hia_rings(UINT32 int_source, void *user_data)
{
#if 0 // TODO: AC Defer porting, use polling mode
    VVDRV_usb4_cm* pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
    boolean bIdle = FALSE;
    if ((NULL == pCm) || (NULL == pCm->m_pQdrv))
    {
        return;
    }
    if (0 != pCm->HIA().IsrHanlder(int_source))
    {
        return;
    }

    if (0 != pCm->ControlPacketHandler(TRUE, &bIdle))
    {
        return;
    }

    if (FALSE == bIdle)
    {
        pCm->HIA().SetIntStatus(USB4_HI_ISR_RX(0)); /* This is a trick to re-enter ISR context later */
    }
#endif // TODO: AC Defer porting, use polling mode
}

/*------------------------------------------------------------------------*/
void VVDRV_usb4_interrupts_isr_wake(UINT32 int_source, void *user_data)
{
#if 0 // TODO: AC Defer porting, use polling mode
    VVDRV_usb4_cm* pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
    if ((NULL == pCm) || (NULL == pCm->m_pQdrv))
    {
        return;
    }

    if (0 != pCm->TryLockCm())
    {
        return; /* Let some other thread to complete handling */
    }
    pCm->UnlockCm(); /* Lock will happen again in the flow. TODO: Rewrite */

    pCm->m_logger.StoreEvent(USB4_CM_EVENT_WAKE_ISR);

    if (0 != pCm->WakeFlow(USB4_uc_wake_reason_DEVICE))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }

    pCm->m_bWakeInterruptHappened = TRUE;

ErrorHandling:
    /* Clear interrupt status - necessary for edge interrupt */
    VVDRV_deo_interrupt_clear(int_source);
#endif // TODO: AC Defer porting, use polling mode
}

void VVDRV_usb4_interrupts_isr_dp_aux(UINT32 int_source, void *user_data)
{
#if 0 // TODO: AC Defer porting, use polling mode
    /* Get pointer to class */
    VVDRV_usb4_cm* pCm;
    VVDRV_usb4_dp_aux *pDpAux;
    
    pCm = reinterpret_cast<VVDRV_usb4_cm*>(user_data);
    if (NULL == pCm)
    {
        return;
    }
    
    pDpAux = pCm->m_pQdrv->m_Platform->DpAux();
    if (0 != pDpAux->IsrHandler(int_source))
    {
        return;
    }
#endif // TODO: AC Defer porting, use polling mode
}


/*------------------------------------------------------------------------*/
