/**---------------------------------------------------------------------------
 *   @file        usb4_cm_iotcl.c
 *
 *   @brief   Client interface to Connection Manager
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include <Usb4Utils.h>
#include "Usb4Log.h"   // Logging utilities
#include "usb4_cm.h"
// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_timer.h"
// #include "VVHAL_usb4_utils.h"
// #include <new>


/*----------------------------------------------------------------------------
 * Global data structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * VVDRV_usb4_cm Class methods
 *--------------------------------------------------------------------------*/




int Usb4CmIoctl(usb4_cm_ctx_t* usb4_cm_ctx, USB4_ioctl_t* pIoctl)
{

    USB4_ASSERT(NULL != pIoctl)

    switch (pIoctl->ioctl)
    {
        case USB4_IOCTL_QUERY_NUMBER_OF_INTERDOMAIN_ROUTERS:
        {
            UINT32* pOutDword = (UINT32*)(pIoctl->out_data);
            Usb4Log(USB4_LOG_CM, Usb4CmIoctlDeprecatedCallCheckNumberInterdomainRoutersInstead__Warn, 0);
            // USB4_LOG_WARNING("IOCTL Deprecated, call CheckNumberInterdomainRouters instead\n");
            USB4_ASSERT(0 == Usb4CmCheckNumberInterdomainRouters(usb4_cm_ctx, pOutDword));
            break;
        }
        case USB4_IOCTL_SEND_HOT_PLUG_TEST_PACKET:
        {
            USB4_ASSERT(0 == Usb4CtrlIfaceSendHotPlugDummyPacket(Usb4CmControl(usb4_cm_ctx)))
            break;
        }
        case USB4_IOCTL_CONFIGURE_INTERDOMAIN_ADAPTER_PATH:
        {
            USB4_adapter_path_config_t* pPathConf = (USB4_adapter_path_config_t*)(pIoctl->in_data);
            USB4_ASSERT(sizeof(USB4_adapter_path_config_t)==pIoctl->in_size)

            USB4_ASSERT(0 == Usb4PathManagerSetUpInterdomainPath(Usb4CmPathManager(usb4_cm_ctx), pPathConf))
            //TODO: Activate / De-Activate adapter? May split to a separate function.
            break;
        }
        default:
            USB4_ERROR_STACK_MSG(-1, "Un-handled IOCTL");
            goto ErrorHandling;
    }

    return 0;
ErrorHandling:
    return -1;
}
