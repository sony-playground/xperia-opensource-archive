/**---------------------------------------------------------------------------
 *   @file        usb4_cm_logger.c
 *
 *   @brief   Logger for CM level events like HPE, Errors, etc...
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/

#include "usb4_cm.h"
#include "Usb4Log.h"   // Logging utilities
#include "usb4_platform_target.h"
// #include "VVHAL_usb4_utils.h"

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

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


int Usb4CmLoggerLockMutex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
    if (NULL == pCm) return 0;
    USB4_ASSERT(0 != pCm->m_pQdrv);
    USB4_ASSERT(0 != pCm->m_pQdrv->m_Platform);
    // TODO: AC mutex is a virtual constructor without an implementation, finish later
    // USB4_ASSERT(0 == pCm->m_pQdrv->m_Platform->LockMutex());
    return 0;
}

int Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    // usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
    // TODO: AC mutex is a virtual constructor without an implementation, finish later
    // USB4_ASSERT(0 == pCm->m_pQdrv->m_Platform->UnlockMutex());
    return 0;
}

int Usb4CmLoggerInit(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, void* pCm, UINT8 coreIndex)
{
    // m_cmEvents(),
    usb4_cm_logger_ctx->m_pCm = pCm; // Actual type usb4_cm_ctx_t*
    usb4_cm_logger_ctx->m_freeIndex = 0;
    usb4_cm_logger_ctx->m_printIndex = 0;
    usb4_cm_logger_ctx->m_prevFreeIndex = 0;
    return 0;
}

int Usb4CmLoggerDeInit(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
    if (NULL != pCm)
    {
        pCm = NULL;
    }
    return 0;
}

int Usb4CmLoggerReset(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    usb4_mem_memset(usb4_cm_logger_ctx->m_cmEvents, 0, sizeof(usb4_cm_logger_ctx->m_cmEvents));
    usb4_cm_logger_ctx->m_freeIndex = 0;
    usb4_cm_logger_ctx->m_printIndex = 0;
    usb4_cm_logger_ctx->m_prevFreeIndex = 0;
    return 0;
}

int Usb4CmLoggerIsIdle(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, BOOLEAN* bIdle)
{
    if (NULL != bIdle)
    {
        if (usb4_cm_logger_ctx->m_prevFreeIndex != usb4_cm_logger_ctx->m_freeIndex)
        {
            *bIdle = FALSE;
        }
        else
        {
            *bIdle = TRUE;
        }
        usb4_cm_logger_ctx->m_prevFreeIndex = usb4_cm_logger_ctx->m_freeIndex;
        return 0;
    }
    else
    {
        return -1;
    }
}

int Usb4CmLoggerPrintUcEvents(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
  usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
	if (NULL == pCm) return 0;
	if (NULL == pCm->m_pQdrv) return 0;
	if (NULL == pCm->m_pQdrv->m_Platform) return 0;
	if (NULL == pCm->m_pQdrv->m_Platform->m_uC) return 0;
	USB4_ASSERT(0 == Usb4PlatformUcPrintUcMsgs(pCm->m_pQdrv->m_Platform->m_uC));
	return 0;
}

int Usb4CmLoggerStoreEvent(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_event_type type)
{
    USB4_ASSERT(0 == Usb4CmLoggerLockMutex(usb4_cm_logger_ctx));
    usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;

    if (usb4_cm_logger_ctx->m_freeIndex >= USB4_MAX_CM_LOGGER_EVENTS)
    {
    	return 0;
    }
    usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].router_index = pCm->m_pHotplug->router_index;
    usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].adapter_number = pCm->m_pHotplug->modifiedAdapter;
    usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].eventType = type;
    switch(type)
    {
        case USB4_CM_EVENT_SM_TRANSITION:
            usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].event.hpState = pCm->m_pHotplug->hotplug_state;
            break;
        case USB4_CM_EVENT_HPE:
            if (pCm->m_pHotplug->modifiedAdapter == pCm->m_pHotplug->adapter_first)
            {
                usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].event.hpParsed = pCm->m_pHotplug->adapter_first_action;
            }
            else
            {
                usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].event.hpParsed = pCm->m_pHotplug->adapter_second_action;
            }
            break;
        case USB4_CM_EVENT_NOTIFICATION:
            //usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].event.notificationEvent = ;
            break;
        default:
            break;

    }
    usb4_cm_logger_ctx->m_freeIndex++;

    USB4_ASSERT(0 == Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx));
    return 0;
}

int Usb4CmLoggerStoreHotPlugStateMachineState(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    return Usb4CmLoggerStoreEvent(usb4_cm_logger_ctx, USB4_CM_EVENT_SM_TRANSITION);
}

int Usb4CmLoggerStoreHpe(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    return Usb4CmLoggerStoreEvent(usb4_cm_logger_ctx, USB4_CM_EVENT_HPE);
}
int Usb4CmLoggerStoreNotification(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    return Usb4CmLoggerStoreEvent(usb4_cm_logger_ctx, USB4_CM_EVENT_NOTIFICATION);
}

#define STATE_NAME(X) {X, #X}

typedef struct 
{
    USB4_hotplug_state state;
    const char* name;
} USB4_HPE_state_names_t;

static USB4_HPE_state_names_t state_names[] =
{
    STATE_NAME(USB4_SINGLE_LANE_CL0),
    STATE_NAME(USB4_L1_IN_CL0),
    STATE_NAME(USB4_HOTPLUG_ENUMERATE_NEW_ROUTER),
    STATE_NAME(USB4_HOTPLUG_DISABLE_LANE1),
    STATE_NAME(USB4_HOTPLUG_BOND_LANES),
    STATE_NAME(USB4_HOTPLUG_CHECK_LANES_BONDED),
    STATE_NAME(USB4_HOTPLUG_BUILD_PATHS),
    STATE_NAME(USB4_HOTPLUG_DOWNSTREAM_PORT_RESET),
    STATE_NAME(USB4_HOTPLUG_INTDOM_HANDLE_ERR_ENUM),
    STATE_NAME(USB4_HOTPLUG_INTDOM_PROCESS_UUIDS),
    STATE_NAME(USB4_HOTPLUG_INTDOM_CHECK_X2_SUPPORT),
    STATE_NAME(USB4_HOTPLUG_INTDOM_SLAVE),
    STATE_NAME(USB4_HOTPLUG_INTDOM_MASTER),
    STATE_NAME(USB4_HOTPLUG_INTDOM_MASTER_BOND),
    STATE_NAME(USB4_L0_IN_CLd),
};

typedef struct 
{
    USB4_HPE_parsed hpe;
    const char* name;
} USB4_HPE_action_names_t;

static USB4_HPE_action_names_t action_names[] =
{
    STATE_NAME(USB4_HPE_NO_ACTION),
    STATE_NAME(USB4_HPE_IN),
    STATE_NAME(USB4_HPE_OUT)
};

static const char* usb4_find_action_name(USB4_HPE_parsed hpe)
{
    UINT32 i;
    for (i = 0; i < ARR_SIZE(action_names); i++)
    {
        if (action_names[i].hpe == hpe)
        {
            return action_names[i].name;
        }
    }
    return "";
}

static const char* usb4_find_state_name(USB4_hotplug_state state)
{
    UINT32 i;
    for (i = 0; i < ARR_SIZE(state_names); i++)
    {
        if (state_names[i].state == state)
        {
            return state_names[i].name;
        }
    }
    return "";
}

int Usb4CmLoggerPrintEvents(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, BOOLEAN bResetLogger)
{
    UINT32 i, coreIndex;

    USB4_ASSERT(0 == Usb4CmLoggerLockMutex(usb4_cm_logger_ctx));

    usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
    
    coreIndex = Usb4PlatformGetCoreIndex(pCm->m_pQdrv->m_Platform);
    for (i = usb4_cm_logger_ctx->m_printIndex; i < usb4_cm_logger_ctx->m_freeIndex; i++)
    {
        switch(usb4_cm_logger_ctx->m_cmEvents[i].eventType)
        {
            case USB4_CM_EVENT_SM_TRANSITION:
                USB4_ASSERT(usb4_cm_logger_ctx->m_cmEvents[i].event.hpState < ARR_SIZE(state_names));
                Usb4Log4(USB4_LOG_CM, Usb4CmLoggerPrintEvents__Params__CoreIndex_R_A_hpState, 0,
                		coreIndex,
                    usb4_cm_logger_ctx->m_cmEvents[i].router_index,
                    usb4_cm_logger_ctx->m_cmEvents[i].adapter_number,
                    usb4_cm_logger_ctx->m_cmEvents[i].event.hpState
                    );
                // USB4_LOG_INFO("CM[%u] R: %d, A: %d, %s\n",
                // 		coreIndex,
                //         usb4_cm_logger_ctx->m_cmEvents[i].router_index,
                //         usb4_cm_logger_ctx->m_cmEvents[i].adapter_number,
                //         usb4_find_state_name(usb4_cm_logger_ctx->m_cmEvents[i].event.hpState));
                break;
            case USB4_CM_EVENT_HPE:
                USB4_ASSERT(usb4_cm_logger_ctx->m_cmEvents[i].event.hpParsed < ARR_SIZE(action_names));
                Usb4Log4(USB4_LOG_CM, Usb4CmLoggerPrintEvents__Params__CoreIndex_R_A_hpParsed, 0,
                    coreIndex,
                    usb4_cm_logger_ctx->m_cmEvents[i].router_index,
                    usb4_cm_logger_ctx->m_cmEvents[i].adapter_number,
                    usb4_cm_logger_ctx->m_cmEvents[i].event.hpParsed);
                // USB4_LOG_INFO("CM[%u] R: %d, A: %d, %s\n",
                // 		coreIndex,
                //         usb4_cm_logger_ctx->m_cmEvents[i].router_index,
                //         usb4_cm_logger_ctx->m_cmEvents[i].adapter_number,
                //         usb4_find_action_name(usb4_cm_logger_ctx->m_cmEvents[i].event.hpParsed));
                break;
            case USB4_CM_EVENT_NOTIFICATION:
                //usb4_cm_logger_ctx->m_cmEvents[usb4_cm_logger_ctx->m_freeIndex].event.notificationEvent = ;
                break;
            case USB4_CM_EVENT_WAKE_ISR:
                Usb4Log1(USB4_LOG_CM, Usb4CmLoggerPrintEvents__Params__CoreIndexWakeISRhappened, 0, coreIndex);
                // USB4_LOG_INFO("CM[%u] Wake ISR happened\n", coreIndex);
                break;
            default:
                break;

        }
    }
    usb4_cm_logger_ctx->m_printIndex = usb4_cm_logger_ctx->m_freeIndex;
    if (bResetLogger)
    {
        USB4_ASSERT(0 == Usb4CmLoggerReset(usb4_cm_logger_ctx));
    }
    USB4_ASSERT(0 == Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx));
    return 0;
}

UINT32 Usb4CmLoggerGetCoreIndex(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx)
{
    usb4_cm_ctx_t* pCm = usb4_cm_logger_ctx->m_pCm;
    if (NULL == pCm) return 0;
    if (NULL == pCm->m_pQdrv) return 0;
    if (NULL == pCm->m_pQdrv->m_Platform) return 0;
    return Usb4PlatformGetCoreIndex(pCm->m_pQdrv->m_Platform);
}

int Usb4CmLoggerFindTransition(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_event* pEvent, UINT32* pIndex)
{
	UINT32 i;
	BOOLEAN isEventFound = FALSE;

	USB4_ASSERT(NULL != pIndex);
	USB4_ASSERT(NULL != pEvent);
	USB4_ASSERT(0 == Usb4CmLoggerLockMutex(usb4_cm_logger_ctx));

	/* Search the logger for the event given type */
	for (i = 0; i <= usb4_cm_logger_ctx->m_freeIndex; i++)
	{
		isEventFound = ((pEvent->router_index == usb4_cm_logger_ctx->m_cmEvents[i].router_index)&&
		                (pEvent->eventType == usb4_cm_logger_ctx->m_cmEvents[i].eventType) &&
					    (pEvent->event.raw == usb4_cm_logger_ctx->m_cmEvents[i].event.raw));
		if (isEventFound)
		{
			*pIndex = i;
			break;
		}
	}

    USB4_ASSERT(0 == Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx));
    return 0;
}

/*--------------------------------------------------------------------*/

int Usb4CmLoggerCountHotplugEvent(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx, USB4_cm_hotlug_event_params* pParams, UINT32* pCounter)
{
    UINT32 i;
    BOOLEAN isEventFound = FALSE;

    USB4_ASSERT(0 == Usb4CmLoggerLockMutex(usb4_cm_logger_ctx));

    *pCounter = 0;

    /* Search the logger for the event given type */
    for (i = 0; i < usb4_cm_logger_ctx->m_freeIndex; i++)
    {
        /* Check if this type of event was found */   
        isEventFound = ((USB4_CM_EVENT_HPE == usb4_cm_logger_ctx->m_cmEvents[i].eventType) &&
                       (pParams->adapter == usb4_cm_logger_ctx->m_cmEvents[i].adapter_number) &&
                       (pParams->router ==  usb4_cm_logger_ctx->m_cmEvents[i].router_index) &&
                       (pParams->hotplugState == usb4_cm_logger_ctx->m_cmEvents[i].event.hpParsed));

        /* Update counter */
        if (isEventFound)
        {
            (*pCounter)++;
        }
    }
    

    USB4_ASSERT(0 == Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx));
    return 0;
}

/*--------------------------------------------------------------------*/
int Usb4CmLoggerFindEventByType(usb4_cm_logger_ctx_t* usb4_cm_logger_ctx,
                                          USB4_cm_event_type type,
                                          USB4_cm_event* pEvent, 
                                          UINT32* pStartFromIndex)
{
    UINT32 i;
    BOOLEAN isEventFound = FALSE;

    USB4_ASSERT(0 == Usb4CmLoggerLockMutex(usb4_cm_logger_ctx));

    /* Search the logger for the event given type */
    for (i = (*pStartFromIndex); i < usb4_cm_logger_ctx->m_freeIndex; i++)
    {
        /* Check if this type of event was found */   
        isEventFound = (type == usb4_cm_logger_ctx->m_cmEvents[i].eventType);

        /* Update counter */
        if (isEventFound)
        {
            (*pStartFromIndex) = i + 1;
            break;
        }
    }
    
    USB4_ASSERT(TRUE == isEventFound);
    pEvent = &usb4_cm_logger_ctx->m_cmEvents[i];

    USB4_ASSERT(0 == Usb4CmLoggerUnlockMutex(usb4_cm_logger_ctx));
    return 0;
}
