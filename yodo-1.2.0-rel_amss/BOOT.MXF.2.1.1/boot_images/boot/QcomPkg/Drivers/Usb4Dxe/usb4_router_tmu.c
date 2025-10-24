/**---------------------------------------------------------------------------
 *   @file        usb4_router_tmu.c
 *   @brief       router TMU driver module
 *
 *   Copyright (c) 2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include "usb4_router.h"
#include "usb4_port.h"
#include "Usb4Log.h"
#include <string.h>
/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetPortUnidirectionalMode(usb4_router_ctx_t* router_ctx, UINT32 lane0Number, BOOLEAN enabled)
{
    usb4_port_ctx_t *pAdapter;

    /* Set lane 0 */
    pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, lane0Number);
    USB4_ASSERT(NULL != pAdapter);

    USB4_ASSERT(0 == Usb4PortTmuUniDirectionalMode(pAdapter, enabled));

    /* Repeat for lane 1 */
    if (pAdapter->m_OtherLaneGroupNumber > pAdapter->m_Number)
    {
        pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, pAdapter->m_OtherLaneGroupNumber);
        USB4_ASSERT(NULL != pAdapter);

        USB4_ASSERT(0 == Usb4PortTmuUniDirectionalMode(pAdapter, enabled));
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetRate(usb4_router_ctx_t* router_ctx, USB4_tmu_packet_interval interval)
{
    USB4_router_tmu_capability routerTmuCapability;

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, NULL));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8*)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));

    routerTmuCapability.TMU_RTR_CS_3.TSPacketInterval = interval;

    /* Write TMU capability */
    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8*)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetRouterUnidirectionalMode(usb4_router_ctx_t* router_ctx, BOOLEAN enableUnidirectionalMode)
{
    usb4_port_ctx_t *pAdapter;
    BOOLEAN isUniDirectionalSupported;

    /* Get uni mode support */
    USB4_ASSERT(0 == Usb4RouterTMUCheckUniModeSupported(router_ctx, &isUniDirectionalSupported));

    if (TRUE == enableUnidirectionalMode)
    {
        /* Make sure we can set port to uni-directional mode */
        if (FALSE == isUniDirectionalSupported)
        {
            // USB4_LOG_WARNING("Router %x doesn't support unidirectional TMU mode\n", USB4_LOWER32(router_ctx->m_topologyID));
            Usb4Log1(USB4_LOG_CM, Usb4RouterTMUSetRouterUnidirectionalModeDoesNotSupportUnidirectionalTMUMode__Params__Router, 0, USB4_LOWER32(router_ctx->m_topologyID)); 
            return 0;
        }
    }

    /* Scan all adapters */
    pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, 0);

    while (NULL != pAdapter)
    {
        /* Update uni mode */
        USB4_ASSERT(0 == Usb4RouterTMUSetPortUnidirectionalMode(router_ctx, pAdapter->m_Number, enableUnidirectionalMode));

        pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, pAdapter->m_Number + 1);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetMode(usb4_router_ctx_t* router_ctx, USB4_tmu_mode mode)
{

    /* Notify the system time is not reliable */
    USB4_ASSERT(0 == Usb4RouterTMUSetTimeDisruption(router_ctx, TRUE));

    switch (mode)
    {
    case USB4_TMU_MODE_UNI_DIRECTIONAL_HIFI:
        USB4_ASSERT(0 == Usb4RouterTMUSetRouterUnidirectionalMode(router_ctx, TRUE));
        USB4_ASSERT(0 == Usb4RouterTMUSetRate(router_ctx, USB4_TMU_PACKET_INTERVAL_HIFI));
        router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_UNI_DIRECTIONAL_HIFI;
        break;

    case USB4_TMU_MODE_BI_DIRECTIONAL_HIFI:
        USB4_ASSERT(0 == Usb4RouterTMUSetRouterUnidirectionalMode(router_ctx, FALSE));
        USB4_ASSERT(0 == Usb4RouterTMUSetRate(router_ctx, USB4_TMU_PACKET_INTERVAL_HIFI));
        router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_BI_DIRECTIONAL_HIFI;
        break;

    case USB4_TMU_MODE_UNI_DIRECTIONAL_LOW:
        USB4_ASSERT(0 == Usb4RouterTMUSetRouterUnidirectionalMode(router_ctx, TRUE));
        USB4_ASSERT(0 == Usb4RouterTMUSetRate(router_ctx, USB4_TMU_PACKET_INTERVAL_LOWRES));
        router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_UNI_DIRECTIONAL_LOW;
        break;

    case USB4_TMU_MODE_OFF:
        USB4_ASSERT(0 == Usb4RouterTMUSetRouterUnidirectionalMode(router_ctx, FALSE));
        USB4_ASSERT(0 == Usb4RouterTMUSetRate(router_ctx, USB4_TMU_PACKET_INTERVAL_OFF));
        router_ctx->m_tmuCurrentMode = USB4_TMU_MODE_OFF;
        break;

    default:
        goto ErrorHandling;
    }

    USB4_ASSERT(0 == Usb4RouterTMUSetTimeDisruption(router_ctx, FALSE));
    return 0;

ErrorHandling:

    USB4_ASSERT(0 == Usb4RouterTMUSetTimeDisruption(router_ctx, FALSE));
    return -1;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUGetCurrentMode(usb4_router_ctx_t* router_ctx, USB4_tmu_mode *pMode)
{
    *pMode = router_ctx->m_tmuCurrentMode;
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUCheckUniModeSupported(usb4_router_ctx_t* router_ctx, BOOLEAN *pIsSupported)
{
    USB4_router_tmu_capability routerTmuCapability;
    UINT32 capSize; /* TMU may have undocumented registers */
    /* Try to get result from cache */
    if (1 == router_ctx->m_tmuCachedUniSupport)
    {
        *pIsSupported = TRUE;
        return 0;
    }
    else if (0 == router_ctx->m_tmuCachedUniSupport)
    {
        *pIsSupported = FALSE;
        return 0;
    }

    memset((UINT8 *)(&routerTmuCapability), 0, sizeof(routerTmuCapability));

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, &capSize));
    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         MIN(capSize, sizeof(routerTmuCapability))));

    *pIsSupported = routerTmuCapability.TMU_RTR_CS_0.UniDirectionalCapability_UCAP;

    if (*pIsSupported)
    {
        router_ctx->m_tmuCachedUniSupport = 1;
    }
    else
    {
        router_ctx->m_tmuCachedUniSupport = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUPostLocalTime(usb4_router_ctx_t* router_ctx, UINT64 localTime)
{
    USB4_router_tmu_capability routerTmuCapability;

    UINT32 localTimeHigh = (localTime >> 32) & 0xFF;
    UINT32 localTimeLow = (localTime)&0xFF;
    UINT32 capSize; /* TMU may have undocumented registers */

    USB4_ASSERT(0 == Usb4RouterTMUSetTimeDisruption(router_ctx, TRUE));

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, &capSize));
    capSize = MIN(capSize, sizeof(routerTmuCapability));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    routerTmuCapability.TMU_RTR_CS_22.PostLocalTimeLow = localTimeLow;
    routerTmuCapability.TMU_RTR_CS_23.PostLocalTimeHigh = localTimeHigh;

    /* Set new local time */
    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    /* Post time */
    routerTmuCapability.TMU_RTR_CS_24.PostTimeLow = 1;
    routerTmuCapability.TMU_RTR_CS_25.PostTimeHigh = 0;

    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    /* Clear post time registers */
    routerTmuCapability.TMU_RTR_CS_24.PostTimeLow = 0;
    routerTmuCapability.TMU_RTR_CS_25.PostTimeHigh = 0;

    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    /* Periodically read the Post Time field of the Router to determine when the
    Router is done updating its local time. The Router sets the Post Time field
    to 0x0 after it has updated its local time.*/



    USB4_ASSERT(0 == Usb4RouterTMUSetTimeDisruption(router_ctx, FALSE));
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUGetLocalTime(usb4_router_ctx_t* router_ctx, UINT64 *pNanoSeconds, UINT16 *pFractionalNanoSeconds)
{
    USB4_router_tmu_capability routerTmuCapability;
    UINT32 capSize; /* TMU may have undocumented registers */

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, &capSize));
    capSize = MIN(capSize, sizeof(routerTmuCapability));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    /* Get local time */
    *pFractionalNanoSeconds = routerTmuCapability.TMU_RTR_CS_1.LocalTimeLow & 0xFFFF;

    *pNanoSeconds = ((UINT64)(routerTmuCapability.TMU_RTR_CS_1.LocalTimeLow >> 16) & 0xFFFF) +
                    ((UINT64)(routerTmuCapability.TMU_RTR_CS_2.LocalTimeMiddle) << 16) +
                    ((UINT64)(routerTmuCapability.TMU_RTR_CS_3.LocalTimeHigh) << 48);

    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetTimeDisruption(usb4_router_ctx_t* router_ctx, BOOLEAN enable)
{
    USB4_router_tmu_capability routerTmuCapability;
    UINT32 capSize; /* TMU may have undocumented registers */
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, &capSize));
    capSize = MIN(capSize, sizeof(routerTmuCapability));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         capSize));

    routerTmuCapability.TMU_RTR_CS_0.TimeDisruption_TD = enable;

    /* Write TMU capability */
    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));

    /* In case the disruption was finished, wait 50ms to allow TMU to converge - CM Guide 7.3.3.1, Router Connection */
    if (FALSE == enable)
    {
        USB4_ASSERT(0 == usb4_timer_Sleep_ms(&timer, 50))
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUTimeSync(usb4_router_ctx_t* router_ctx, BOOLEAN enable)
{
    UINT32 i;
    UINT32 lastAdapterFound = 0;
    usb4_port_ctx_t *pAdapter;

    /* Scan all adapters */
    for (i = 0; i < USB4_MAX_PORTS_PER_ROUTER; i++)
    {
        /* Get lane 0*/
        pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, lastAdapterFound);

        /* Nothing to do if we didn't find an adapter */
        if (NULL == pAdapter)
        {
            break;
        }
        /* Remember last adapter found */
        lastAdapterFound = pAdapter->m_Number;

        if ((lastAdapterFound == router_ctx->m_cs.ROUTER_CS_1.upstreamAdapter) || (USB4_HPE_IN == pAdapter->m_hotplug.adapter_first_action))
        {
            /* Configure time sync */ /* TODO: Prevent duplicate enables */
            USB4_ASSERT(0 == Usb4PortTmuTimeSync(pAdapter, enable));
            if (pAdapter->m_OtherLaneGroupNumber)
            {
                pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, pAdapter->m_OtherLaneGroupNumber);
                USB4_ASSERT(NULL != pAdapter)
                USB4_ASSERT(0 == Usb4PortTmuTimeSync(pAdapter, enable));
            }
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUEnableInterdomain(usb4_router_ctx_t* router_ctx, BOOLEAN enable)
{
    USB4_router_tmu_capability routerTmuCapability;

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, NULL));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));

    routerTmuCapability.TMU_RTR_CS_0.InterDomainEnable_IDE = enable;

    /* Write TMU capability */
    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetInterdomainInterval(usb4_router_ctx_t* router_ctx, UINT32 TSInterDomainInterval)
{
    USB4_router_tmu_capability routerTmuCapability;

    /* Find TMU capabiliy */
    USB4_ASSERT(0 == Usb4RouterSearchCapability(router_ctx, USB4_ROUTER_CAP_TMU, NULL));

    /* Read TMU capability */
    USB4_ASSERT(0 == Usb4RouterReadCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));

    routerTmuCapability.TMU_RTR_CS_15.TSInterDomainInterval = TSInterDomainInterval;

    /* Write TMU capability */
    USB4_ASSERT(0 == Usb4RouterWriteCapability(router_ctx,
                         (UINT8 *)(&routerTmuCapability),
                         sizeof(routerTmuCapability)));
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetAllInterdomainPortsAsMaster(usb4_router_ctx_t* router_ctx)
{
    usb4_port_ctx_t *pAdapter;

    pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, 0);

    while (NULL != pAdapter)
    {
        /* Check if interdomain */
        if (pAdapter->m_bIsInterdomain)
        {
            USB4_ASSERT(0 == Usb4RouterTMUAssignInterdomainMasterPort(router_ctx, pAdapter->m_Number));
        }

        /* Get next adapter */
        pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0,
                                        pAdapter->m_Number + 1);
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUSetAllInterdomainPortsAsSlave(usb4_router_ctx_t* router_ctx)
{
    usb4_port_ctx_t *pAdapter;

    pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0, 0);

    while (NULL != pAdapter)
    {
        /* Check if interdomain */
        if (pAdapter->m_bIsInterdomain)
        {
            USB4_ASSERT(0 == Usb4RouterTMUAssignInterdomainSlavePort(router_ctx, pAdapter->m_Number));
        }

        /* Get next adapter */
        pAdapter = Usb4RouterGetAdapterPortByType(router_ctx, USB4_portType_LANE0,
                                        pAdapter->m_Number + 1);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUAssignInterdomainMasterPort(usb4_router_ctx_t* router_ctx, UINT32 lane0AdapterNumber)
{

    usb4_port_ctx_t *pAdapter;

    /* Get lane 0*/
    pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, lane0AdapterNumber);

    /* Nothing to do if we didn't find an adapter */
    USB4_ASSERT(NULL != pAdapter);

    USB4_ASSERT(0 == Usb4PortTMUSetInterdomainMaster(pAdapter));

    /* Update lane 1*/
    pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, lane0AdapterNumber + 1);

    USB4_ASSERT(0 == Usb4PortTMUSetInterdomainMaster(pAdapter));

    return 0;
}

/*---------------------------------------------------------------------------*/

int Usb4RouterTMUAssignInterdomainSlavePort(usb4_router_ctx_t* router_ctx, UINT32 lane0AdapterNumber)
{

    usb4_port_ctx_t *pAdapter;

    /* Get lane 0*/
    pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, lane0AdapterNumber);

    /* Nothing to do if we didn't find an adapter */
    USB4_ASSERT(NULL != pAdapter);

    USB4_ASSERT(0 == Usb4PortTMUSetInterdomainSlave(pAdapter));

    /* Update lane 1*/
    pAdapter = Usb4RouterGetAdapterPortByNumber(router_ctx, lane0AdapterNumber + 1);

    USB4_ASSERT(0 == Usb4PortTMUSetInterdomainSlave(pAdapter));

    return 0;
}

/*---------------------------------------------------------------------------*/
