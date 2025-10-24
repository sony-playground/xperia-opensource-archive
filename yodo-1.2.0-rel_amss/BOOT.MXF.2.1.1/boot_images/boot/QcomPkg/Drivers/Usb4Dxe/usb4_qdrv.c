/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_qdrv.c
 *
 *  @brief :  usb4 core Driver
 *
 *   Copyright (c) 2019-2021 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
// #include "VVHAL_usb4_mem.h"      //< DMA API declaration, and structs
// #include "VVHAL_usb4_logger.h"   //< Logging utilities
#include "usb4_platform.h"
#include "usb4_platform_target.h"
#include "usb4_platform_ahb_access.h"
// #include "VVHAL_usb4_utils.h"
// #include "VVHAL_usb4_timer.h"
#include "usb4_cm.h"
#include "usb4_qdrv.h"
#include "usb4_gcc.h"
#include "usb4_platform_defs.h"
// #include "VVDRV_usb4_pd.h"

/*----------------------------------------------------------------------------
 * Macro Definitions
 *--------------------------------------------------------------------------*/

#define USB4_CONNECTION_DETECT_TIMEOUT_MS (30000)
#define USB4_LINK_ESTABLISH_TIMEOUT_MS (30000)

/* Yiftach : 100ms is more then enough */
#define USB4_SLEEP_DONE_TIMEOUT_MSEC (100) 

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions
 *--------------------------------------------------------------------------*/

// Invoked by CM init
int Usb4QDrvInit(usb4_qdrv_ctx_t* usb4_qdrv_ctx, void* cm, UINT32 coreIndex)
{
    if (USB4_NUM_OF_CORES < coreIndex)
    {
        USB4_ERROR_STACK_MSG(-1, "Core index out of range");
        return -1;
    }

    if (NULL != usb4_qdrv_ctx->m_Platform)
    {
        /* Already Intialized, exit gracefully */
        return 0;
    }

    //+++ UEFI specific
    usb4_qdrv_ctx->m_bPollingMode = TRUE;
    usb4_qdrv_ctx->m_cm = cm;
    //--- UEFI specific

    usb4_qdrv_ctx->m_Platform = Usb4PlatformCreate(coreIndex);
    if (NULL == usb4_qdrv_ctx->m_Platform)
    {
        USB4_ERROR_STACK_MSG(-1, "Failed creating platform");
        return -1;
    }

#if 0 // UEFI, moved inside Usb4PlatformCreate()
    if (0 != Usb4PlatformInit(usb4_qdrv_ctx->m_Platform, coreIndex))
    {
        USB4_ERROR_STACK(-1);
        goto ErrorHandling;
    }
#endif

    return 0;
#if 0
ErrorHandling:
    return -1;
#endif
}

/* Prepare platform to accept connection */
int Usb4QDrvOpen(usb4_qdrv_ctx_t* usb4_qdrv_ctx)
{
    UINT32 mask = USB4_GCC_RESET_ALL;
//    usb4_cm_ctx_t* cm = usb4_qdrv_ctx->m_cm;

//    USB4_ASSERT(NULL != usb4_qdrv_ctx->m_Platform->GCC()); // GCC is absorbed by usb4_platform_ctx_t
    USB4_ASSERT(NULL != usb4_qdrv_ctx->m_Platform);
    
    if (TRUE == usb4_qdrv_ctx->m_Platform->m_bSkipLoadingFirmware)
    {
        mask = USB4_GCC_WAKE_SPECIFIC_RESET;
    }
    else
    {
        /* Initialization from POR */
        //USB4_ASSERT(0 == Usb4PlatformSideBandConfigure(usb4_qdrv_ctx->m_Platform, USB4_PD_CC_ORIENTATION_CC2 == cm->m_pdInfo.cc_orientation))
        USB4_ASSERT(0 == Usb4PlatformSideBandConfigure(usb4_qdrv_ctx->m_Platform, 0));
    }
    
    USB4_ASSERT(0 == Usb4PlatformPlatformPreReset(usb4_qdrv_ctx->m_Platform));
    USB4_ASSERT(0 == Usb4PlatformUcDeActivateUc(usb4_qdrv_ctx->m_Platform->m_uC));
    //USB4_ASSERT(0 == m_Platform->PHY()->PowerDown())
    USB4_ASSERT(0 == Usb4GccConfigureGccMUXs(usb4_qdrv_ctx->m_Platform, 2));
#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM
    USB4_ASSERT(0 == Usb4GccAssertReset(usb4_qdrv_ctx->m_Platform, mask));
    USB4_ASSERT(0 == Usb4GccDeAssertReset(usb4_qdrv_ctx->m_Platform, mask));
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM
    USB4_ASSERT(0 == Usb4GccConfigureGccMUXs(usb4_qdrv_ctx->m_Platform, 0));
    USB4_ASSERT(0 == Usb4PlatformPlatformPostReset(usb4_qdrv_ctx->m_Platform));

    if (FALSE == usb4_qdrv_ctx->m_Platform->m_bSkipLoadingFirmware)
    {
        mask = USB4_GCC_USB3_INIT_SPECIFIC_RESET;

       USB4_ASSERT(0 == Usb4PlatformAhbAccessAssertUSBAPReset(usb4_qdrv_ctx->m_Platform->m_ahbAccess, 0x1));
#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM
       USB4_ASSERT(0 == Usb4GccAssertReset(usb4_qdrv_ctx->m_Platform, mask));
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM
       USB4_ASSERT(0 == Usb4PlatformAhbAccessUSBAPPHYStatusEnable(usb4_qdrv_ctx->m_Platform->m_ahbAccess, 0x1));
#ifndef USB4_USE_ENABLE_ALL_CLKS_CMM
       USB4_ASSERT(0 == Usb4GccDeAssertReset(usb4_qdrv_ctx->m_Platform, mask));
#endif // ~USB4_USE_ENABLE_ALL_CLKS_CMM
       USB4_ASSERT(0 == Usb4PlatformAhbAccessAssertUSBAPReset(usb4_qdrv_ctx->m_Platform->m_ahbAccess, 0x0));
    }

    if (FALSE == usb4_qdrv_ctx->m_Platform->m_bSkipLoadingFirmware)
    {
        if (0 != Usb4PlatformUcLoadFW(usb4_qdrv_ctx->m_Platform->m_uC))
        {
            USB4_ERROR_STACK(-1);
            goto ErrorHandling;
        }
    }
    else
    {
        usb4_qdrv_ctx->m_Platform->m_bSkipLoadingFirmware = FALSE;
    }

    if (FALSE == usb4_qdrv_ctx->m_Platform->m_bDoSidebandOverride)
    {
        usb4_qdrv_ctx->m_Platform->m_bDoSidebandOverride = TRUE; /* This is a normal behavior */
        usb4_qdrv_ctx->m_Platform->m_sidebandOverrideValue = USB4_platform_sb_ctrl_sw_pulldown;
    }
    return 0;

ErrorHandling:
    return -1;

}

uint32 g_usb4_preset = (1<<6);

/* Implements SW_Bringup.signalling sequence */
int Usb4QDrvCableConnectedHandler(usb4_qdrv_ctx_t* usb4_qdrv_ctx, boolean bIsUsb4Device, UINT32 numLanes)
{
    USB4_phyConfig phyConfig = {0};

    USB4_ASSERT(0 == Usb4GccConfigureUSB3toUSB4mode(usb4_qdrv_ctx->m_Platform));
    USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_usbap_usb4_mode(usb4_qdrv_ctx->m_Platform->m_ahbAccess))
    USB4_ASSERT(0 == Usb4PlatformAhbAccess_configure_tmu_clocks(usb4_qdrv_ctx->m_Platform->m_ahbAccess))

    phyConfig.bIsUsb4Device = bIsUsb4Device;
    phyConfig.numLanes = numLanes;
    phyConfig.bSscEnabled = TRUE; //Needed?
    phyConfig.dpPllCfg = USB4_DpPll_Config_Disable;
#ifdef USB4_EXPECT_DP_OPERATIONS
    phyConfig.dpPllCfg = USB4_DpPll_Config_8p1;
#endif
    //phyConfig.bUseDiffClock; // Default FALSE
    //phyConfig.pipeClockDisableInC3IndependentOfPowerdown; // Default FALSE
    USB4_ASSERT(0 == Usb4PlatformCioPhyConfigure(usb4_qdrv_ctx->m_Platform->m_PHY, &phyConfig)); // TODO: AC Fix code not compatible with emulation PHY, polymorphism

    USB4_ASSERT_MSG(0 == Usb4QDrvActivateUc(usb4_qdrv_ctx), "uC activation failed\n");

    if (g_usb4_preset > 0)
    {
        /* Use a single preset - TODO: Why do we need this? */
        USB4_ASSERT(0 == Usb4QDrvConfigurePresetBitsUc(usb4_qdrv_ctx, g_usb4_preset));
    }
    return 0;
}

/* Implements SW_Bringup.signalling sequence */
// TODO: AC compatibility porting with USB4 PD
int Usb4QDrvEstablishHsConnection(usb4_qdrv_ctx_t* usb4_qdrv_ctx, const USB4_PD_INFO* pInfo)
{
    usb4_uc_ioctl_t ucIoctlCableInformation = {0};
    boolean bSwap;
    USB4_ASSERT(USB4_PD_CC_ORIENTATION_OPEN != pInfo->cc_orientation);

    bSwap = (USB4_PD_CC_ORIENTATION_CC2 == pInfo->cc_orientation) ? TRUE : FALSE;
    USB4_ASSERT(0 == Usb4PlatformSideBandSetOrientation(usb4_qdrv_ctx->m_Platform, bSwap));

    /* start HSE */
    ucIoctlCableInformation.beginHSE.cmd = USB4_uc_ioctl_cmd_BEGIN_HSE;
    
    ucIoctlCableInformation.beginHSE.device_type = 
        (USB4_PD_ATTACH_MODE_USB4 == pInfo->current_mode) ? 0x1 : 0x0;
    
    ucIoctlCableInformation.beginHSE.cc_orientation = 
        (USB4_PD_CC_ORIENTATION_CC1 == pInfo->cc_orientation) ? 0x0 : 0x1;

    ucIoctlCableInformation.beginHSE.cable_type = pInfo->cable_type;
        
    ucIoctlCableInformation.beginHSE.cable_gen = 
        (USB4_PD_CABLE_GEN_2 == pInfo->CableGen) ? 0x0 : 0x1;

    //TODO: Temporary forcing cable to Gen3
    ucIoctlCableInformation.beginHSE.cable_gen = 1;
        
    ucIoctlCableInformation.beginHSE.polarity_l0tx = 0x0;
    ucIoctlCableInformation.beginHSE.polarity_l0rx = 0x0;
    ucIoctlCableInformation.beginHSE.polarity_l1tx = 0x0;
    ucIoctlCableInformation.beginHSE.polarity_l1rx = 0x0;
    
    USB4_ASSERT(0 == Usb4PlatformUcIoctl(usb4_qdrv_ctx->m_Platform->m_uC, &ucIoctlCableInformation))
    
    return 0;
}

int Usb4QDrvActivateUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx)
{
    return Usb4PlatformUcActivateUc(usb4_qdrv_ctx->m_Platform->m_uC);
}

int Usb4QDrvPhysicalDisconnectUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx)
{
    usb4_uc_ioctl_t ucIoctlPhysicalDisconnect = {0};
    ucIoctlPhysicalDisconnect.physicalDisconnect.cmd = USB4_uc_ioctl_cmd_PHYSICAL_DISCONNECT;
    ucIoctlPhysicalDisconnect.physicalDisconnect.reserved = 0;
    USB4_ASSERT(0 == Usb4PlatformUcIoctl(usb4_qdrv_ctx->m_Platform->m_uC, &ucIoctlPhysicalDisconnect))

    return 0;
}

int Usb4QDrvConfigurePresetBitsUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx, UINT32 presetBits)
{
    usb4_uc_ioctl_t ucIoctlPhyPresets = {0};
    ucIoctlPhyPresets.enablePhyPresets.cmd = USB4_uc_ioctl_cmd_ENABLE_PHY_PRESETS;
    ucIoctlPhyPresets.enablePhyPresets.presetBits = presetBits;
    USB4_ASSERT(0 == Usb4PlatformUcIoctl(usb4_qdrv_ctx->m_Platform->m_uC, &ucIoctlPhyPresets))

    return 0;
}

void Usb4QDrvDeInit(usb4_qdrv_ctx_t* usb4_qdrv_ctx)
{
    if (NULL != usb4_qdrv_ctx->m_Platform)
    {
        /* detach interrupts and free all platform dependencies */
        usb4_mem_free(usb4_qdrv_ctx->m_Platform);
        usb4_qdrv_ctx->m_Platform = NULL;
    }    
}

int Usb4QDrvSetPollingMode(usb4_qdrv_ctx_t* usb4_qdrv_ctx, boolean bPollingMode)
{
    usb4_cm_ctx_t* cm = usb4_qdrv_ctx->m_cm;
    usb4_qdrv_ctx->m_bPollingMode = bPollingMode;

    /* In case of an early call, just exit. Polling will be taken into account later */
    if (NULL == usb4_qdrv_ctx->m_Platform)
    {
        return 0;
    }

    if (bPollingMode)
    {
        /* De-register interrupts */
        if (0 != Usb4PlatformInterruptsDetachInterrupts(usb4_qdrv_ctx->m_Platform->m_interrupts))
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
    }
    else
    {
        /* Register for interrupts, CM address is passed in as a parameter */
        //Don't need ot attach all interrupts at this time
        USB4_ASSERT(0 == Usb4PlatformInterruptsAttachInterrupts(usb4_qdrv_ctx->m_Platform->m_interrupts, cm));
#if 0
        // TODO: AC check &m_cm or m_cm
        USB4_ASSERT(0 == Usb4PlatformInterruptsAttachInterrupt(usb4_qdrv_ctx->m_Platform->m_interrupts, USB4_intType_UC_INT, &cm));
        USB4_ASSERT(0 == Usb4PlatformInterruptsAttachInterrupt(usb4_qdrv_ctx->m_Platform->m_interrupts, USB4_intType_HIA_RINGS, &cm));
        USB4_ASSERT(0 == Usb4PlatformInterruptsAttachInterrupt(usb4_qdrv_ctx->m_Platform->m_interrupts, USB4_intType_WAKE_SLEEP, &cm));
        if (0 != (cm->m_quirks & USB4_CM_QUIRK_REGISTER_PD_INTERRUPT))
        {
            USB4_ASSERT(0 == Usb4PlatformInterruptsAttachInterrupt(usb4_qdrv_ctx->m_Platform->m_interrupts, USB4_intType_PD_CONNECT, &cm));
        }
#endif
    }

    return 0;
}

int Usb4QDrvInitSleep(usb4_qdrv_ctx_t* usb4_qdrv_ctx)
{
    usb4_uc_ioctl_t ucIoctlSleep = {0};
    UINT32 oldNumSleepDoneEvents, numSleepDoneEvents;
    int rc = 0;

    //USB4_ASSERT(0 == m_Platform->GetCablePluggedStatus()) // Needed to determine SB override configuration

    USB4_ASSERT(0 == Usb4PlatformUcGetSleepDoneCounter(usb4_qdrv_ctx->m_Platform->m_uC, &oldNumSleepDoneEvents))
    ucIoctlSleep.completeSleep.cmd=USB4_uc_ioctl_cmd_COMPLETE_SLEEP;
    USB4_ASSERT(0 == Usb4PlatformUcIoctl(usb4_qdrv_ctx->m_Platform->m_uC, &ucIoctlSleep))

    //Wait for interrupt to shut down the system - maximum 101msec
    /* waiting for USB4_SLEEP_DONE_TIMEOUT_MSEC for numSleepDoneEvents to get updated*/
    USB4_WHILE_WITH_TIMEOUT((0 == Usb4PlatformUcGetSleepDoneCounter(usb4_qdrv_ctx->m_Platform->m_uC, &numSleepDoneEvents)) &&
                            (numSleepDoneEvents <= oldNumSleepDoneEvents),
                            USB4_SLEEP_DONE_TIMEOUT_MSEC,
                            rc);
    while((0 == Usb4PlatformUcGetSleepDoneCounter(usb4_qdrv_ctx->m_Platform->m_uC, &numSleepDoneEvents)) &&
                            (numSleepDoneEvents <= oldNumSleepDoneEvents)){};
    USB4_ASSERT(0 == rc);

    /* Store data that needs to persist through sleep */
    USB4_ASSERT(0 == Usb4PlatformStorePersistentData(usb4_qdrv_ctx->m_Platform))

    /* Platform specific actions */
    USB4_ASSERT(0 == Usb4PlatformPutPlatformToSleep(usb4_qdrv_ctx->m_Platform))

    USB4_ASSERT(0 == Usb4PlatformUcDeActivateUc(usb4_qdrv_ctx->m_Platform->m_uC))
    return 0;
}

int Usb4QDrvWake(usb4_qdrv_ctx_t* usb4_qdrv_ctx, USB4_cm_wake_stage_type wakeStage, USB4_uc_wake_reason reason)
{
   // reason = USB4_uc_wake_reason_UNDEFINED is the default argument, not supported by C
    switch(wakeStage)
    {
        case USB4_CM_WAKE_DO_PLATFORM_ACTIONS:
            /* Platform specific actions */
            USB4_ASSERT(0 == Usb4PlatformWakePlatformFromSleep(usb4_qdrv_ctx->m_Platform))
            break;
        case USB4_CM_WAKE_DO_WRITE_BACK_PERSISTENT_DATA:
            /* Platform specific actions */
            USB4_ASSERT(0 == Usb4PlatformWriteBackPersistentData(usb4_qdrv_ctx->m_Platform))

            
            break;
        case USB4_CM_WAKE_DO_LAUNCH_UC:
        {
            usb4_uc_ioctl_t ucIoctlWake = {0};

            if (USB4_uc_wake_reason_UNDEFINED != reason)
            {
                ucIoctlWake.completeSleep.cmd=USB4_uc_ioctl_cmd_WAKE;
                ucIoctlWake.wake.wakeUpReason = reason;
                USB4_ASSERT(0 == Usb4PlatformUcIoctl(usb4_qdrv_ctx->m_Platform->m_uC, &ucIoctlWake))
            }
            break;
        }
        default:
            break;
    }

    return 0;
}
