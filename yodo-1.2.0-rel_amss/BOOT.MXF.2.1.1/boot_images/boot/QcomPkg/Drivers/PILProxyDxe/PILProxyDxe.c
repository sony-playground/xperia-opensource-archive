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
 03/01/22     jj      WPSS & SSR related changes
 06/29/22     yw      add DTB image support
 
=============================================================================*/
#include <Uefi.h>
#include <Library/UefiLib.h>
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
	PIL_PROXY_VOTE_CFG_TYPE* Cfg = (PIL_PROXY_VOTE_CFG_TYPE*)Context;
        
    Status = PILProxyUnvote(Cfg, Cfg->LastSeq);
    if (EFI_ERROR (Status)) 
    {
       DEBUG(( EFI_D_ERROR, "PILProxyUnvoteCb: failed to unvote for proc 0x%x\n\n", Cfg->SubsysId));
    }
    
    gBS->CloseEvent ( Event );
}

EFI_STATUS PILProxyUnvote_SSR_Cb(SSR_EVENT_TYPE Evt, VOID* Arg)
{
    EFI_STATUS    Status = EFI_SUCCESS;
	PIL_PROXY_VOTE_CFG_TYPE* Cfg = (PIL_PROXY_VOTE_CFG_TYPE*)Arg;
    
    if (Evt == SSR_PROXY_UNVOTE)
    {
        Status = PILProxyUnvote(Cfg, Cfg->LastSeq);
		if (EFI_ERROR(Status))
			DEBUG((EFI_D_ERROR, "Failed to do proxy unvote by ssr subsys_id=%d\n", Cfg->SubsysId));
		//else
		//	DEBUG((EFI_D_ERROR, "proxy unvote done by ssr subsys_id=%d\n", Cfg->SubsysId));
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
  VOTING_SEQUENCE_TYPE	Seq;
  
  PIL_PROXY_VOTE_CFG_TYPE* pProxyVoteCfg = LoadPilProxyVoteConfigFromDT(SubsysId);
  if (pProxyVoteCfg == NULL)
  {
	DEBUG(( EFI_D_ERROR, "PilProxyDxe failed to load DT for subsysId %d\n", SubsysId));
	return EFI_UNSUPPORTED;
  }

  switch(PILEvent)
  {
    case PIL_EVENT_PRE_AUTH_AND_RESET:
	
	  Seq = BRINGUP_SEQUENCE;
      if (AllowUnvoteBySmp2p && !IS_DTB_IMAGE(pProxyVoteCfg->Flag[Seq]))
      {
          /* if ssr installed, register unvote callback */
          Status = gBS->LocateProtocol(&gEfiSSRProtocolGuid, NULL, (VOID**)&pSSRProtocol);
          if (!EFI_ERROR(Status) && pSSRProtocol != NULL)
          {
			  pProxyVoteCfg->LastSeq = Seq;
              SSR_DRIVER_CB_TYPE DriverCb = {PILProxyUnvote_SSR_Cb, (VOID*)pProxyVoteCfg};      
              
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
      Status = PILProxyVote(pProxyVoteCfg, Seq);
      break;

    case PIL_EVENT_POST_AUTH_AND_RESET:
    
	  Seq = BRINGUP_SEQUENCE;
      /* skip unvoting if do unvote by ssr, or it's dtb image, or use timer but in debugging,*/
      if (UseSmp2pForUnvote || IS_DTB_IMAGE(pProxyVoteCfg->Flag[Seq]) || (!UseSmp2pForUnvote && DetectInSubsysDebug()))
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

	  pProxyVoteCfg->LastSeq = Seq;
      Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  PILProxyUnvoteCb,
                  (VOID*)pProxyVoteCfg,
                  &UnvoteTimer
                  );
                  
      if (EFI_ERROR (Status))
	  {
		  DEBUG(( EFI_D_ERROR, "Failed to create unvote timer evt %r\n", Status));
          break;
	  }


      Status = gBS->SetTimer (
                  UnvoteTimer,
                  TimerRelative,
                  EFI_TIMER_PERIOD_MILLISECONDS(UnvoteDelay)
                  );
                  
	  if (EFI_ERROR (Status))
	  {
		  DEBUG(( EFI_D_ERROR, "Failed to set unvote timer %r\n", Status));
          break;
	  }
                
	  DEBUG(( EFI_D_ERROR, "Set timer for unvoting subsysid=%d delay=%dms\n", pProxyVoteCfg->SubsysId, UnvoteDelay)); 
      break;
      
    case PIL_EVENT_PRE_SHUTDOWN:
      Status = PILProxyVote(pProxyVoteCfg, SHUTDOWN_SEQUENCE);
      break;
      
    case PIL_EVENT_POST_SHUTDOWN:
      Status = PILProxyUnvote(pProxyVoteCfg, SHUTDOWN_SEQUENCE);
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

EFI_STATUS PilProxyHandleEvent_Adsp_Dtb (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_AUDIO))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_QDSP6_DTB_PROC);
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

EFI_STATUS PilProxyHandleEvent_Cdsp_Dtb (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_COMP))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_CDSP_DTB_PROC);
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

EFI_STATUS PilProxyHandleEvent_Modem_Dtb (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    if (EFI_SUCCESS != GetDefectivePart(EFICHIPINFO_PART_MODEM))
        return EFI_UNSUPPORTED;
    
    return PilProxyHandleEvent(PILEvent, TZ_PIL_AUTH_MODEM_SW_DTB_PROC);
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

STATIC EFI_PIL_PROXY_PROTOCOL mCdspDtbPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Cdsp_Dtb
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

STATIC EFI_PIL_PROXY_PROTOCOL mAdspDtbPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Adsp_Dtb
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

STATIC EFI_PIL_PROXY_PROTOCOL mModemDtbPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   PilProxyHandleEvent_Modem_Dtb
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
					&gPILProxyCDSPDtbGuid,
                    (VOID **)&mCdspDtbPilProxyProtocol,
                    &gPILProxyModemGuid,
                    (VOID **)&mModemPilProxyProtocol,
					&gPILProxyModemDtbGuid,
                    (VOID **)&mModemDtbPilProxyProtocol,
                    &gPILProxyWPSSGuid,
                    (VOID **)&mWpssPilProxyProtocol,
                    &gPILProxyAdspGuid,
                    (VOID **)&mAdspPilProxyProtocol,
					&gPILProxyAdspDtbGuid,
                    (VOID **)&mAdspDtbPilProxyProtocol,
                    &gPILProxySlpiGuid,
                    (VOID **)&mSlpiPilProxyProtocol,
                    //&gPILProxyCDSP1Guid,
                    //(VOID **)&mCdsp1PilProxyProtocol,
                    NULL );
  return Status;
}
