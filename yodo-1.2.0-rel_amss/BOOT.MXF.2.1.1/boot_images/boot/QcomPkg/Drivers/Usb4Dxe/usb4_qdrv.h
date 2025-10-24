/**---------------------------------------------------------------------------
 *   @file        usb4_qdrv.h
 *
 *   @brief   Header file for a Qualcomm USB4 API
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#ifndef ___USB4_QDRV_H__
#define ___USB4_QDRV_H__

#include <Protocol/EFIUsb4Config.h>
#include "usb4_platform.h"




/*----------------------------------------------------------------------------
 * Defines
 *--------------------------------------------------------------------------*/

typedef enum
{
    USB4_CM_WAKE_DO_PLATFORM_ACTIONS = 0,
    USB4_CM_WAKE_DO_WRITE_BACK_PERSISTENT_DATA = 1,
    USB4_CM_WAKE_DO_LAUNCH_UC = 2,
} USB4_cm_wake_stage_type;

/*----------------------------------------------------------------------------
 * Type Definitions
 *--------------------------------------------------------------------------*/

// class VVDRV_usb4_cm;

/**
 * @brief Core context structure.
 *        Keeps core's base addresses,configuration data,core state and
 *        debug data
 */
typedef struct
{
    BOOLEAN m_bPollingMode;
    void* m_cm; // usb4_cm_ctx_t*
    usb4_platform_ctx_t* m_Platform;
} usb4_qdrv_ctx_t;

#if 0
    VVDRV_usb4_qdrv(VVDRV_usb4_cm& cm) :
                                        m_bPollingMode(TRUE),
                                        m_cm(cm),
                                        m_Platform(NULL)
    {

    }
#endif

// TODO: AC Destructor invokes DeInit, ensure code calls DeInit
#if 0
    ~VVDRV_usb4_qdrv()
    {
        DeInit();
    }
#endif

    /**
     * @brief construct class members and prepare the driver for usage
     * @param[in] coreIndex core index
     * @return 0 on success, other on failure
     */
    int Usb4QDrvInit(usb4_qdrv_ctx_t* usb4_qdrv_ctx, void* cm, UINT32 coreIndex);

    /** @brief un-initialize the core driver */
    void Usb4QDrvDeInit(usb4_qdrv_ctx_t* usb4_qdrv_ctx);

    /**
     * @brief This function prepares platform HW to accept connections over USB4 cable
     * @return 0 on success, other on failure
     */
    int Usb4QDrvOpen(usb4_qdrv_ctx_t* usb4_qdrv_ctx);

    /**
     * @brief This function implements first part of SW_Bringup.signalling sequence
     * @param [in] bUseTBT3Mode 0x0 for USB4, 0x1 for TBT3
     * @param [in] numLanes 0x0 or 0x1 phy lanes
     * @return 0 on success, other on failure
     */
    int Usb4QDrvCableConnectedHandler(usb4_qdrv_ctx_t* usb4_qdrv_ctx, BOOLEAN bUseTBT3Mode, UINT32 numLanes);

    /**
     * @brief This function implements second part of SW_Bringup.signalling sequence
     * @param [in] pInfo PD information
     * @return 0 on success, other on failure
     */
    int Usb4QDrvEstablishHsConnection(usb4_qdrv_ctx_t* usb4_qdrv_ctx, const USB4_PD_INFO* pInfo);

    /**
     * @brief Update USB4 Core to operational state
     * @return 0 on success, other on failure
     */
    int Usb4QDrvActivateUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx);

    /**
     * @brief Signal physical cable disconnect to uC
     * @return 0 on success, other on failure
     */
    int Usb4QDrvPhysicalDisconnectUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx);

    /**
     * @brief Configure presets that uC will try during HS establishment
     * @return 0 on success, other on failure
     */
    int Usb4QDrvConfigurePresetBitsUc(usb4_qdrv_ctx_t* usb4_qdrv_ctx, UINT32 presetBits);

    /**
     * @brief This function configures the driver to operate in Polling or Interrupt mode
     * This function may be called at any time,
     * @return 0 on success, other on failure
     */
    int Usb4QDrvSetPollingMode(usb4_qdrv_ctx_t* usb4_qdrv_ctx, BOOLEAN bPollingMode);

    /**
     * @brief Turn off USB4 domain, by setting Init Sleep.
     * Will generate "Sleep Done" interrupt.
     * @return 0 on success, other on failure
     */
    int Usb4QDrvInitSleep(usb4_qdrv_ctx_t* usb4_qdrv_ctx);

    /**
     * @brief Wake USB4 domain
     * @param[in] wakeStage - stage to perform
     * @param[in] reason    - wake reason for the uC activation stage
     * @return 0 on success, other on failure
     */
    int Usb4QDrvWake(usb4_qdrv_ctx_t* usb4_qdrv_ctx, USB4_cm_wake_stage_type wakeStage, USB4_uc_wake_reason reason);

#endif //___USB4_QDRV_H__
