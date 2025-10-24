/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_interrupts.c
 *
 *  @brief :  usb4 platform implementation
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVDRV_deo.h"           // DEO mempool and dma
#include "usb4_platform.h"
#include "usb4_interrupts.h"


/**
 * @brief   Maximal number of ISRs that can be attached simultaneously
 */
#ifndef DEO_INT_MAX_ISR_ATTACH
#if defined(DEO_DRIVER_CONCURRENT_EXECUTION)
#define DEO_INT_MAX_ISR_ATTACH  64
#else /* DEO_DRIVER_CONCURRENT_EXECUTION */
#define DEO_INT_MAX_ISR_ATTACH  20
#endif /* DEO_DRIVER_CONCURRENT_EXECUTION */
#endif /* DEO_INT_MAX_ISR_ATTACH */

/**
 * @brief   Used as invalid interrupt source number - must not match any
 *          valid interrupt line number on any interrupt controller
 */
#define DEO_INT_INVALID_IRQ_NUM (0xFFFFFFFFU)

/**
 * @brief   Used when targeting a specific CPU core is not supported by the 
 *          interrupt controllers. For example, NVIC and L6VIC don't support
 *          targeting CPU cores and this MACRO should be for NVIC and L6VIC.
 */
#define DEO_INT_TARGETS_NOT_APPLICABLE (0x0U)

/** 
 * @brief   Used for targeting only the current CPU core when the 
 *          interrupt controller supports targeting a specific CPU core.
 *          This define can be used with combination of other defines such as
 *          #DEO_INT_TARGETS_CPU_ID() by using bitwise or "|" operation.
 *          For NVIC/L2VIC (doesn't support targeting cpu), this will behave
 *          same as #DEO_INT_TARGETS_NOT_APPLICABLE.
 *          For QGIC (support targeting cpu) this will target the current cpu
 *          core and using it will be same as using #DEO_INT_TARGETS_CPU_ID() 
 *          with current cpu id.
 *           
 */
#define DEO_INT_TARGETS_SELF_CPU (0x20000000U)

/** 
 * @brief   Used for targeting a specific CPU core when the 
 *          interrupt controller supports targeting a specific CPU core.
 *          This define can be used with combination of other defines such as
 *          #DEO_INT_TARGETS_SELF_CPU by using bitwise or "|"  operation.
 *          If the target core is the current core #DEO_INT_TARGETS_SELF_CPU 
 *          may be used instead.
 *          For example, QGIC supports targeting CPU cores and this define may
 *          be used for QGIC. 
 */
#define DEO_INT_TARGETS_CPU_ID(x) (1 << x)

/** @brief   Used for trigger method - when IRQ trigger is level  */
#define DEO_INT_TRIGGER_LEVEL (0x0U)

/** @brief   Used for trigger method - when IRQ trigger is edge */
#define DEO_INT_TRIGGER_EDGE (0x1U)

/**
 * @brief   Used when secure level is not applicable for the interrupt 
 *          controller. This MACRO must be used for NVIC and L6VIC.
 */
#define DEO_INT_SECURE_LEVEL_NOT_APPLICABLE (0x0U)

/** 
 * @brief   Used for secure level - non secured interrupt for supported 
 *          interrupt controllers, 
 *          This MACRO can be used for QGIC non secure interrupt.
 */
#define DEO_INT_SECURE_LEVEL_NON_SECURE (0x1U)

/** @brief   Used for secure level - secured interrupt */
#define DEO_INT_SECURE_LEVEL_SECURE (0x2U)

/** @brief   Used for secure level - secure group 0 */
#define DEO_INT_SECURE_LEVEL_SECURE_GROUP0 (0x3U)



#define IRQ_LEVEL(ISR, SRC) \
    {\
        /** @brief Interrupt service routine */\
        ISR,\
\
        /** @brief Argument passed to ISR */\
        NULL, /*Will be filled in on the driver level */\
\
        /** Interrupt source number */\
        SRC, /* Will be updated to the known value from IPCAT */\
\
        /**
         * @brief Interrupt priority.
         *        See #deo_interrupt_priority_t for further details.
         */\
        0x0,\
\
        /**
         * @brief Interrupt target CPU cores.
         *        See #deo_interrupt_targets_t for further details.
         */\
        DEO_INT_TARGETS_SELF_CPU,\
\
        /**
         * @brief Interrupt trigger method.
         *        See #deo_interrupt_trigger_t for further details.
         */\
        DEO_INT_TRIGGER_LEVEL,\
\
        /**
         * @brief Interrupt secure level.
         *        See #deo_interrupt_secure_t for further details.
         */\
        DEO_INT_SECURE_LEVEL_SECURE\
    }


#define IRQ_EDGE(ISR, SRC) \
{\
    /** @brief Interrupt service routine */\
    ISR,\
\
    /** @brief Argument passed to ISR */\
    NULL, /*Will be filled in on the driver level */\
\
    /** Interrupt source number */\
    SRC, /* Will be updated to the known value from IPCAT */\
\
    /**
     * @brief Interrupt priority.
     *        See #deo_interrupt_priority_t for further details.
     */\
    0x0,\
\
    /**
     * @brief Interrupt target CPU cores.
     *        See #deo_interrupt_targets_t for further details.
     */\
    DEO_INT_TARGETS_SELF_CPU,\
\
    /**
     * @brief Interrupt trigger method.
     *        See #deo_interrupt_trigger_t for further details.
     */\
    DEO_INT_TRIGGER_EDGE,\
\
    /**
     * @brief Interrupt secure level.
     *        See #deo_interrupt_secure_t for further details.
     */\
    DEO_INT_SECURE_LEVEL_SECURE\
}

// From GenEmu
// 0 : usb4_pcie_ap_int
// 1 : usb4_clx_exit_int
// 2 : usb4_wake_sleep_int
// 3 : usb4_uc_int
// 4 : usb4_hia_int_ring_data
// 6 : usb4_dp_ap_int
// 7 : emu PDPHY irq    

#if defined(USB4_COMPILING_GEN_EMU)
USB4_intDesc g_usb4_platform_interrupts_core0[] =
{
#if !defined(RUMI)
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  , IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,       2) },
    { USB4_intType_UC_INT      , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        3) },
    { USB4_intType_HIA_RINGS   , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 4) },
    { USB4_intType_DP_AP       , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    6) },
    { USB4_intType_PD_CONNECT  , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_pd_connect,7) },
#else /* RUMI */
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  , IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,       658) },
    { USB4_intType_UC_INT      , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        882) },
    { USB4_intType_HIA_RINGS   , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 883) },
    { USB4_intType_DP_AP       , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    885)},
    //{ USB4_intType_PD_CONNECT, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_pd_connect,   7) },
#endif /* !defined(RUMI) */
};
USB4_intDesc g_usb4_platform_interrupts_core1[] =
{
#if !defined(RUMI)
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  , IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,       64 + 2)},
    { USB4_intType_UC_INT      , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        64 + 3)},
    { USB4_intType_HIA_RINGS   , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 64 + 4)},
    { USB4_intType_DP_AP       , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    64 + 6)},
    { USB4_intType_PD_CONNECT  , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_pd_connect,64 + 7) },
#else /* RUMI */
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  ,IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,        657) },
    { USB4_intType_UC_INT      , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        875) },
    { USB4_intType_HIA_RINGS   , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 876) },
    { USB4_intType_DP_AP       , IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    878)},
    //{ USB4_intType_PD_CONNECT, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_pd_connect,   7) },
#endif /* !defined(RUMI) */
};

#else /* !USB4_COMPILING_GEN_EMU */
USB4_intDesc g_usb4_platform_interrupts_core0[] =
{
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  /*, IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,       881)*/ },
    { USB4_intType_UC_INT      /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        882)*/ },
    { USB4_intType_HIA_RINGS   /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 883)*/ },
    { USB4_intType_DP_AP       /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    885)*/},
    { USB4_intType_PD_CONNECT  /*, IRQ_EDGE(VVDRV_usb4_interrupts_isr_pd_connect, 512)*/ },
    // 512  - during system sleep/wake up it acts as rpmh_wake and during system active it acts as QGIC interrupt
    // 514 - need to understand what is it
};
USB4_intDesc g_usb4_platform_interrupts_core1[] =
{
    //{ USB4_intType_PCIE_AP   ,
    //{ USB4_intType_CLX_EXIT  ,
    { USB4_intType_WAKE_SLEEP  /*, IRQ_EDGE(VVDRV_usb4_interrupts_isr_wake,       874)*/ },
    { USB4_intType_UC_INT      /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_uc,        875)*/},
    { USB4_intType_HIA_RINGS   /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_hia_rings, 876)*/},
    { USB4_intType_DP_AP       /*, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_dp_aux,    878)*/},
    //{ USB4_intType_PD_CONNECT, IRQ_LEVEL(VVDRV_usb4_interrupts_isr_pd_connect,   ) },
};

#endif /* USB4_COMPILING_GEN_EMU */

uint32 g_usb4_platform_interrupts_core0_size = ARR_SIZE(g_usb4_platform_interrupts_core0);
uint32 g_usb4_platform_interrupts_core1_size = ARR_SIZE(g_usb4_platform_interrupts_core1);
