/** @file PILProxyDxe.c

  PIL proxy vote driver for all subsystem

  Copyright (c) 2019,2022  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 03/28/19     ai      Initial revision 
 10/30/19     yw      unify cdspdxe and npudxe,changing to general proxy vote for all subsystem,
                      adding unvote timer for 3 sec delay
 04/21/21     yw      add support unvoting by ssr
 10/21/22     vencha  add PIL proxy vote for WPSS
 
=============================================================================*/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIPILProxy.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFISSR.h>
#include <scm_sip_interface.h>
#include <libfdt_env.h>
#include "pil_proxy_vote_config.h"
#include "pil_proxy_vote.h"

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES FOR TARGET LIB                      */
/*===========================================================================*/

STATIC EFI_CHIPINFO_PROTOCOL *pChipInfoProtocol = NULL;

/* for debugging, will do timer-based unvote if set to 0, 
otherwise do unvote by ssr if ssr drv installed */
UINT32    AllowUnvoteBySmp2p = 1;                   

/*===========================================================================*/
/*                  FUNCTIONS DEFINITIONS                                    */
/*===========================================================================*/

STATIC EFI_STATUS GetDefectivePart(EFIChipInfoPartType ePart)
{
    EFI_STATUS     Status;
    UINT32        nMask = 0;
    
    if (pChipInfoProtocol == NULL)
    {
        Status = gBS->LocateProtocol(
                    &gEfiChipInfoProtocolGuid,
                    NULL,
                    (VOID**)&pChipInfoProtocol
                    );
                    
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "Failed to locate chipinfo protocol\n"));
            return EFI_PROTOCOL_ERROR;
        }
    }
    
    Status = pChipInfoProtocol->GetDefectivePart(pChipInfoProtocol, ePart, &nMask);
    return (EFI_ERROR(Status) || nMask != 0)? EFI_UNSUPPORTED:EFI_SUCCESS;
}

STATIC 
BOOLEAN DetectInSubsysDebug(VOID)
{
    EFI_STATUS  Status;
    UINT32 CookieAddr, CookieVal;
    
    Status = GetConfigValue("PilSubsysDbgCookieAddr", &CookieAddr);
    if (EFI_ERROR(Status))
        return FALSE;
    
    Status = GetConfigValue("PilSubsysDbgCookieVal", &CookieVal);
    if (EFI_ERROR(Status))
        return FALSE;
    
    return (*((UINT32 *)(UINTN)CookieAddr) == CookieVal);
}


VOID EFIAPI    PILProxyUnvoteCb(
    IN  EFI_EVENT                Event,
    IN  VOID                     *Context
    )
{
    EFI_STATUS  Status=EFI_SUCCESS;
    UINT32        SubsysId = (UINT32)(uintptr_t)Context;
        
    Status = PILProxyUnvote(SubsysId);
    if (EFI_ERROR (Status)) 
    {
       DEBUG(( EFI_D_ERROR, "PILProxyUnvoteCb: failed to unvote for proc 0x%x\n\n", SubsysId));
    }
    
    gBS->CloseEvent ( Event );
}

EFI_STATUS PILProxyUnvote_SSR_Cb(SSR_EVENT_TYPE Evt, VOID* Arg)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    UINT32        SubsysId = (UINT32)(uintptr_t)Arg;
    
    if (Evt == SSR_PROXY_UNVOTE)
    {
        Status = PILProxyUnvote(SubsysId);
    }
    return Status;
}

EFI_STATUS PilProxyHandleEvent (
   UINT32                           PILEvent,
   UINT32                           SubsysId
   )
{
  EFI_STATUS     Status = EFI_SUCCESS;
  EFI_EVENT        UnvoteTimer;    
  STATIC UINT32      UnvoteDelay = 0;
  STATIC BOOLEAN     UseSmp2pForUnvote = FALSE;
  EFI_SSR_PROTOCOL*      pSSRProtocol = NULL;

  switch(PILEvent)
  {
    case PIL_EVENT_PRE_AUTH_AND_RESET:

      if (AllowUnvoteBySmp2p)
      {
          /* if ssr installed, register unvote callback */
          Status = gBS->LocateProtocol(&gEfiSSRProtocolGuid, NULL, (VOID**)&pSSRProtocol);
          if (!EFI_ERROR(Status) && pSSRProtocol != NULL)
          {
              SSR_DRIVER_CB_TYPE DriverCb = {PILProxyUnvote_SSR_Cb, (VOID*)(UINTN)SubsysId};      
              
              Status = pSSRProtocol->RegisterCbForSubsys("proxy_unvote",\
                                                        SubsysId, \
                                                        &DriverCb,
                                                        0);
              if (Status!=EFI_SUCCESS&&Status!=EFI_ALREADY_STARTED)
              {
                  DEBUG(( EFI_D_ERROR, "Failed to register unvote ssr callback %r.\n", Status));
                  UseSmp2pForUnvote = FALSE;
              }
              else
                  UseSmp2pForUnvote = TRUE;
          }
          else
              UseSmp2pForUnvote = FALSE;
      }
      Status = PILProxyVote(SubsysId);
      break;

    case PIL_EVENT_POST_AUTH_AND_RESET:
    
      /* skip unvoting if do unvote by ssr, or use timer but in debugging,*/
      if (UseSmp2pForUnvote || (!UseSmp2pForUnvote && DetectInSubsysDebug()))
          break;
    
      if (UnvoteDelay == 0)
      {
          UnvoteDelay = PcdGet32(ProxyUnvoteTimeout);
          if (UnvoteDelay==0)
          {
              DEBUG(( EFI_D_ERROR, "ProxyUnvoteTimeout is undefined in PCD.\n"));
              return EFI_UNSUPPORTED;
          }
      }

      Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  PILProxyUnvoteCb,
                  (VOID*)((UINTN)SubsysId),
                  &UnvoteTimer
                  );
                  
      if (EFI_ERROR (Status))
          break;

      Status = gBS->SetTimer (
                  UnvoteTimer,
                  TimerRelative,
                  UnvoteDelay
                  );
                  
      if (EFI_ERROR (Status))
          break;
                  
      break;
      
    case PIL_EVENT_PRE_SHUTDOWN:
      Status = PILProxyVote(SubsysId);
      break;
      
    case PIL_EVENT_POST_SHUTDOWN:
      Status = PILProxyUnvote(SubsysId);
      break;

    default:
      /* return success for unhandled events */
      break;
  }

  return Status;
}

EFI_STATUS PilProxyHandleEvent_Adsp (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_AUDIO))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_QDSP6_PROC);
}

EFI_STATUS PilProxyHandleEvent_Cdsp (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_COMP))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_CDSP_PROC);
}

EFI_STATUS PilProxyHandleEvent_Slpi (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_SENSORS))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_SSC_PROC);
}

EFI_STATUS PilProxyHandleEvent_Wpss (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_WLAN))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_WLAN_PROC);
}

EFI_STATUS PilProxyHandleEvent_Modem (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_MODEM))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_MODEM_SW_PROC);
}

/*
EFI_STATUS PilProxyHandleEvent_Cdsp1 (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_COMP))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_CDSP1_PROC);
}
*/

/**
  PIL proxy protocol definition

**/
STATIC EFI_PIL_PROXY_PROTOCOL mCdspPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Cdsp
};

STATIC EFI_PIL_PROXY_PROTOCOL mWpssPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Wpss
};

STATIC EFI_PIL_PROXY_PROTOCOL mAdspPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Adsp
};

STATIC EFI_PIL_PROXY_PROTOCOL mSlpiPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Slpi
};

STATIC EFI_PIL_PROXY_PROTOCOL mModemPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Modem
};

/*
STATIC EFI_PIL_PROXY_PROTOCOL mCdsp1PilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Cdsp1
};
*/

/*

  PILProxyDxeEntry ()

  @brief
  Initialize Proxy Driver
 */
EFI_STATUS PILProxyDxeEntry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_HANDLE mHandle = NULL;
  EFI_STATUS         Status   = EFI_SUCCESS;

  Status = gBS->InstallMultipleProtocolInterfaces(
                    &mHandle,
                    &gPILProxyCDSPGuid,
                    (VOID **)&mCdspPilProxyProtocol,
                    &gPILProxyModemGuid,
                    (VOID **)&mModemPilProxyProtocol,
                    &gPILProxyWPSSGuid,
                    (VOID **)&mWpssPilProxyProtocol,
                    &gPILProxyAdspGuid,
                    (VOID **)&mAdspPilProxyProtocol,
                    &gPILProxySlpiGuid,
                    (VOID **)&mSlpiPilProxyProtocol,
                    //&gPILProxyCDSP1Guid,
                    //(VOID **)&mCdsp1PilProxyProtocol,
                    NULL );
  return Status;
}
