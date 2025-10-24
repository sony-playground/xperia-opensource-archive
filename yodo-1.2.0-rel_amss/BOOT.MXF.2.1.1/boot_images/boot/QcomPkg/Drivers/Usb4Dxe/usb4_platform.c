/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform.c
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
// #include "VVHAL_usb4_mem.h"      // DMA API declaration, and structs
// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVDRV_deo.h"           // DEO mempool and dma
#include "usb4_platform.h"
// #include "VVHAL_usb4_platform_defs.h"

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

void Usb4PlatformDeInit(usb4_platform_ctx_t* usb4_platform_ctx)
{
    if (usb4_platform_ctx->m_interrupts)
    {
        usb4_mem_free(usb4_platform_ctx->m_interrupts);
        usb4_platform_ctx->m_interrupts = NULL;
    }

    if (usb4_platform_ctx->m_ahbAccess)
    {
        usb4_mem_free(usb4_platform_ctx->m_ahbAccess);
        usb4_platform_ctx->m_ahbAccess = NULL;
    }

#if 0 // Absorbed into usb4_platform_ctx
    if (usb4_platform_ctx->m_GCC)
    {
        usb4_mem_free(usb4_platform_ctx->m_GCC);
        usb4_platform_ctx->m_GCC = NULL;
    }
#endif

    if (usb4_platform_ctx->m_PHY)
    {
        usb4_mem_free(usb4_platform_ctx->m_PHY);
        usb4_platform_ctx->m_PHY = NULL;
    }

    if (usb4_platform_ctx->m_uC)
    {
        usb4_mem_free(usb4_platform_ctx->m_uC);
        usb4_platform_ctx->m_uC = NULL;
    }

#if 0 // PD does not have data structure, pass the CoreIdx each time, the API names are VVDRV_pd_api_*
    if (usb4_platform_ctx->m_PD)
    {
        delete usb4_platform_ctx->m_PD;
        usb4_platform_ctx->m_PD = NULL;
    }
#endif
    
    if (usb4_platform_ctx->m_pDpAux)
    {
        usb4_mem_free(usb4_platform_ctx->m_pDpAux);
        usb4_platform_ctx->m_pDpAux = NULL;
    }
}





///////////////////////////////
///////////////////////////////
///////////////////////////////
// Platform Interrupt
///////////////////////////////
///////////////////////////////
///////////////////////////////
void Usb4PlatformInterruptsInit(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx)
{
#if 0 // TODO: AC defer porting
  usb4_platform_interrupts_ctx->m_interrupt_vectors = NULL;
  usb4_platform_interrupts_ctx->m_interrupt_vectors_size = 0;
#endif
}
void Usb4PlatformInterruptsDeInit(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx) // In place of destructor
{
#if 0 // TODO: AC defer porting
  Usb4PlatformInterruptsDetachInterrupts(usb4_platform_interrupts_ctx);
#endif
}

USB4_intDesc* Usb4PlatformInterruptsGetIntDescFromIntSource(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, UINT32 intSource)
{
#if 0 // TODO: AC defer porting
    /*TODO: Consider adding cache for the few most frequent interrupt numbers, to avoid searching the array every time */
    for (UINT32 i = 0; i < usb4_platform_interrupts_ctx->m_interrupt_vectors_size; i++)
    {
        if (intSource == usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source)
        {
            return &(usb4_platform_interrupts_ctx->m_interrupt_vectors[i]);
        }
    }
#endif
    return NULL;
}

USB4_intDesc* Usb4PlatformInterruptsGetIntDescFromIntType(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType)
{
#if 0 // TODO: AC defer porting
    /*TODO: Consider adding cache for the few most frequent interrupt numbers, to avoid searching the array every time */
    for (UINT32 i = 0; i < usb4_platform_interrupts_ctx->m_interrupt_vectors_size; i++)
    {
        if (intType == usb4_platform_interrupts_ctx->m_interrupt_vectors[i].intType)
        {
            return &usb4_platform_interrupts_ctx->m_interrupt_vectors[i];
        }
    }
#endif
    return NULL;
}

int Usb4PlatformInterruptsAttachInterrupt(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType, void* userData)
{
#if 0 // TODO: AC defer porting
    USB4_intDesc* pDesc;

    pDesc = GetIntDesc(intType);
    if (NULL == pDesc)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    /* Avoid re-registration (for example in case of sleep - wake scenario )*/
    if (pDesc->deo_interrupt.user_data == userData)
    {
        return 0;
    }

    /* Populate user data pointer */
    pDesc->deo_interrupt.user_data = userData;

    (void) VVDRV_deo_interrupt_detach(pDesc->deo_interrupt.int_source);

    /* Attaching the interrupt */
    if (DEO_ERROR == VVDRV_deo_interrupt_attach(&pDesc->deo_interrupt))
    {
        USB4_ERROR_STACK_MSG(-1, "DEO interrupt attach failed\n");
        return -1;
    }

    /* Clear interrupt status */
    VVDRV_deo_interrupt_clear(pDesc->deo_interrupt.int_source);

    /* Enable the interrupt */
    if (DEO_ERROR == VVDRV_deo_interrupt_enable(pDesc->deo_interrupt.int_source))
    {
        USB4_ERROR_STACK_MSG(-1, "DEO interrupt enable failed\n");
        return -1;
    }
#endif
    return 0;
}

int Usb4PlatformInterruptsDetachInterrupt(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, USB4_intType intType)
{
#if 0 // TODO: AC defer porting
    USB4_intDesc* pDesc;
    pDesc = GetIntDesc(intType);
    if (NULL == pDesc)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    if (USB4_intType_UNUSED_INT_SOURCE != pDesc->intType)
    {
        /* Disable the interrupt */
        VVDRV_deo_interrupt_disable(pDesc->deo_interrupt.int_source);

        /* Clear interrupt status*/
        VVDRV_deo_interrupt_clear(pDesc->deo_interrupt.int_source);

        pDesc->deo_interrupt.user_data = 0;

        (void) VVDRV_deo_interrupt_detach(pDesc->deo_interrupt.int_source);
    }
#endif
    return 0;
}

int Usb4PlatformInterruptsAttachInterrupts(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx, void* userData)
{
#if 0 // TODO: AC defer porting
    UINT32 i;

    for (i = 0; i < usb4_platform_interrupts_ctx->m_interrupt_vectors_size; i++)
    {
        /* Populate user data pointer */
        usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.user_data = userData;

        (void) VVDRV_deo_interrupt_detach(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source);

        /* Attaching the interrupt */
        if (DEO_ERROR == VVDRV_deo_interrupt_attach(&usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt))
        {
            USB4_ERROR_STACK_MSG(-1, "DEO interrupt attach failed\n");
            break;
        }

        /* Clear interrupt status */
        VVDRV_deo_interrupt_clear(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source);

        /* Enable the interrupt */
        if (DEO_ERROR == VVDRV_deo_interrupt_enable(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source))
        {
            USB4_ERROR_STACK_MSG(-1, "DEO interrupt enable failed\n");
            break;
        }
    }

    /* error handling if not all interrupts are attached */
    if (i != usb4_platform_interrupts_ctx->m_interrupt_vectors_size)
    {
        (void) DetachInterrupts();
        return -1;
    }
#endif
    return 0;
}

int Usb4PlatformInterruptsDetachInterrupts(usb4_platform_interrupts_ctx_t* usb4_platform_interrupts_ctx)
{
#if 0 // TODO: AC defer porting
    UINT32 i;

    for (i = 0; i < usb4_platform_interrupts_ctx->m_interrupt_vectors_size; i++)
    {
        if (USB4_intType_UNUSED_INT_SOURCE != usb4_platform_interrupts_ctx->m_interrupt_vectors[i].intType)
        {
            /* Disable the interrupt */
            VVDRV_deo_interrupt_disable(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source);

            /* Clear interrupt status*/
            VVDRV_deo_interrupt_clear(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source);

            usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.user_data = 0;

            (void) VVDRV_deo_interrupt_detach(usb4_platform_interrupts_ctx->m_interrupt_vectors[i].deo_interrupt.int_source);

        }
    }
#endif
    return 0;
}
