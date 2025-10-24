/*============================================================================
  FILE:         pil_proxy_vote.c

  OVERVIEW:     Implement proxy vote

  DEPENDENCIES: None

                Copyright (c) 2019-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
				
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version
  06/29/22   yw         change input type of vote and unvote APIs, to support DTB image
  
============================================================================*/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <api/systemdrivers/icbarb.h>
#include <Library/BaseLib.h>
#include <npa.h>
#include <Library/voltage_level.h>
#include <Library/MemoryAllocationLib.h>
#include<Library/TimerLib.h>
#include<Library/QcomBaseLib.h>
#include "pil_proxy_vote_config.h"

/*=========================================================================
      Globals and prototypes
==========================================================================*/

typedef struct _PIL_NPA_ENTRY_
{
	LIST_ENTRY		List;
	CONST CHAR8*	ClientName;
	CONST CHAR8* 	ResourceName;
	npa_client_handle	Hdl;
} PIL_NPA_ENTRY;


LIST_ENTRY   PILNpaClientList = INITIALIZE_LIST_HEAD_VARIABLE (PILNpaClientList);

STATIC UINT64 VoteDoneTime=0;

STATIC PIL_NPA_ENTRY* SearchForNPAEntry(CONST CHAR8* ClientName, CONST CHAR8* ResourceName)
{
	LIST_ENTRY*			Node;
	PIL_NPA_ENTRY*		Entry, *RetEntry=NULL;
	
	for (Node = GetFirstNode(&PILNpaClientList); !IsNull(&PILNpaClientList, Node); \
						Node = GetNextNode(&PILNpaClientList, Node))
	{
		Entry = BASE_CR(Node, PIL_NPA_ENTRY, List);
		if (AsciiStrLen(ClientName) == AsciiStrLen(Entry->ClientName) && \
			0 == AsciiStrCmp(ClientName, Entry->ClientName) && \
			AsciiStrLen(ResourceName) == AsciiStrLen(Entry->ResourceName) && 
			0 == AsciiStrCmp(ResourceName, Entry->ResourceName))
		{
			RetEntry = Entry;
			break;
		}
	}
	return RetEntry;
}

STATIC npa_client_handle SearchForHdl(CONST CHAR8* ClientName, CONST CHAR8* ResourceName)
{
	npa_client_handle   RetHdl = NULL;
	PIL_NPA_ENTRY*		Entry = SearchForNPAEntry(ClientName, ResourceName);
	if (Entry != NULL)
		RetHdl = Entry->Hdl;
	
	return RetHdl;
}


/**
  do regulator vote 

  @param[in] ClientName         client name used to createt the NPA client
  @param[in] RailName           resource name used to createt the NPA client
  @param[in] Level              Requested resource state
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/

STATIC EFI_STATUS RegVote(CONST CHAR8* ClientName, CONST CHAR8* RailName, rail_voltage_level Level)
{
	PIL_NPA_ENTRY*	NpaEntry;
	npa_client_handle Hdl = SearchForHdl(ClientName, RailName);
	if (Hdl == NULL)
	{
		Hdl = npa_create_sync_client(RailName, ClientName, NPA_CLIENT_REQUIRED);
		if (Hdl == NULL)
			return EFI_UNSUPPORTED;
		else {
			// add to list
			NpaEntry = AllocateZeroPool(sizeof(PIL_NPA_ENTRY));
			if (NpaEntry==NULL)
			{
				DEBUG(( EFI_D_ERROR, "PilProxyVoteLib: out of memory\n"));
				npa_destroy_client(Hdl);
				return EFI_OUT_OF_RESOURCES;
			}
			
			NpaEntry->ClientName = ClientName;
			NpaEntry->ResourceName = RailName;
			NpaEntry->Hdl = Hdl;
			InsertTailList(&PILNpaClientList, &NpaEntry->List);
		}
	}
	
	npa_issue_scalar_request(Hdl, Level);
	return EFI_SUCCESS;
}


/**
  do regulator unvote 

  @param[in] ClientName         client name used to createt the NPA client
  @param[in] RailName           resource name used to createt the NPA client
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/
STATIC EFI_STATUS RegUnvote(CONST CHAR8* ClientName, CONST CHAR8* RailName) 
{
	PIL_NPA_ENTRY* NpaEntry = SearchForNPAEntry(ClientName, RailName);
	
	if (NpaEntry == NULL || NpaEntry->Hdl == NULL)
	{
		DEBUG(( EFI_D_ERROR, "%a: NULL Client for%a\r\n", __func__,"PIL proxy"));
		ASSERT(0);
	}
	
	npa_complete_request(NpaEntry->Hdl);
    npa_destroy_client(NpaEntry->Hdl);
	//remove entry
	RemoveEntryList(&NpaEntry->List);
	FreePool(NpaEntry);
	return EFI_SUCCESS;
}


/**
  do ICB vote 

  @param[in] ClientName         client name used to createt the NPA client
  @param[in] RailName           resource name used to createt the NPA client
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/
STATIC EFI_STATUS IcbVote(CONST PIL_PROXY_VOTE_CFG_TYPE* pProxyVoteCfg)
{
	PIL_NPA_ENTRY*	NpaEntry;

	npa_client_handle Hdl = SearchForHdl(pProxyVoteCfg->ClientName, pProxyVoteCfg->IcbName);
	
	if (Hdl == NULL)
	{
		Hdl = npa_create_sync_client_ex(pProxyVoteCfg->IcbName, 
									pProxyVoteCfg->ClientName, 
									NPA_CLIENT_VECTOR,
									sizeof(ICBArb_MasterSlaveType) * pProxyVoteCfg->NumOfMaterSlave,
									pProxyVoteCfg->MasterSlave);
		if (Hdl == NULL)
			return EFI_UNSUPPORTED;
		else {
			NpaEntry = AllocateZeroPool(sizeof(PIL_NPA_ENTRY));
			if (NpaEntry==NULL)
			{
				DEBUG(( EFI_D_ERROR, "PilProxyVoteLib: out of memory\n"));
				npa_destroy_client(Hdl);
				return EFI_OUT_OF_RESOURCES;
			}
			
			NpaEntry->ClientName = pProxyVoteCfg->ClientName;
			NpaEntry->ResourceName = pProxyVoteCfg->IcbName;
			NpaEntry->Hdl = Hdl;
			InsertTailList(&PILNpaClientList, &NpaEntry->List);
		}
	
	npa_issue_vector_request(Hdl, (sizeof(ICBArb_RequestType) * pProxyVoteCfg->NumOfMaterSlave) / (sizeof(npa_resource_state)),
						(npa_resource_state *) pProxyVoteCfg->Request );
	}
	return EFI_SUCCESS;
}


/**
  do ICB unvote 

  @param[in] ClientName         client name used to createt the NPA client
  @param[in] RailName           resource name used to createt the NPA client
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/
STATIC EFI_STATUS IcbUnvote(CONST PIL_PROXY_VOTE_CFG_TYPE* pProxyVoteCfg)
{
	PIL_NPA_ENTRY* NpaEntry = SearchForNPAEntry(pProxyVoteCfg->ClientName, pProxyVoteCfg->IcbName);
	
	if (NpaEntry == NULL || NpaEntry->Hdl == NULL)
	{
		DEBUG(( EFI_D_ERROR, "%a: NULL Client for%a\r\n", __func__,"PIL proxy"));
		ASSERT(0);
	}
	
	npa_complete_request(NpaEntry->Hdl);
	npa_destroy_client(NpaEntry->Hdl);
	//remove entry
	RemoveEntryList(&NpaEntry->List);
	FreePool(NpaEntry);
	return EFI_SUCCESS;
}


/**
  do proxy vote 

  @param[in] SubsysId           subsystem ID
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/
EFI_STATUS PILProxyVote(PIL_PROXY_VOTE_CFG_TYPE* pProxyVoteCfg, VOTING_SEQUENCE_TYPE Seq)
{
	UINT32 ConfigIndx = 0;
	
	ASSERT(pProxyVoteCfg!=NULL);
	
	if ((pProxyVoteCfg->Flag[Seq] & FLAG_VOTE_ONLY) != FLAG_VOTE_ONLY)
		return EFI_SUCCESS;

	for (ConfigIndx = 0; ConfigIndx < pProxyVoteCfg->NumOfRails; ConfigIndx++)
	{
		if (EFI_SUCCESS != RegVote(pProxyVoteCfg->ClientName, pProxyVoteCfg->RailNames[ConfigIndx], pProxyVoteCfg->RailVtgLvl[ConfigIndx]))
		{
			DEBUG((EFI_D_ERROR,"Unable to reg vote for rail %a\n", pProxyVoteCfg->RailNames[ConfigIndx]));
			return EFI_UNSUPPORTED;
		}
	}
		
	if (pProxyVoteCfg->IcbName != NULL)
	{
		if (EFI_SUCCESS != IcbVote(pProxyVoteCfg))
		{
			DEBUG((EFI_D_ERROR,"Unable to icb vote for subsytem %a\n", pProxyVoteCfg->ClientName));
			return EFI_UNSUPPORTED;
		}
	}
	VoteDoneTime = GetPerformanceCounter();
	DEBUG((EFI_D_ERROR,"proxy vote done SubsysId=%d\n", pProxyVoteCfg->SubsysId));		
	return EFI_SUCCESS;
}

/**
  do proxy unvote 

  @param[in] SubsysId           subsystem ID
  
  @retval EFI_SUCCESS           success
  @retval otherwise             fail
**/
EFI_STATUS PILProxyUnvote(PIL_PROXY_VOTE_CFG_TYPE* pProxyVoteCfg, VOTING_SEQUENCE_TYPE Seq)
{
	UINT32 ConfigIndx = 0;
	UINT64 HoldTime;
	
	ASSERT(pProxyVoteCfg!=NULL);
	
	if ((pProxyVoteCfg->Flag[Seq] & FLAG_UNVOTE_ONLY) != FLAG_UNVOTE_ONLY)
		return EFI_SUCCESS;
	
	for (ConfigIndx = 0; ConfigIndx < pProxyVoteCfg->NumOfRails; ConfigIndx++)
	{
		if (EFI_SUCCESS != RegUnvote(pProxyVoteCfg->ClientName, pProxyVoteCfg->RailNames[ConfigIndx]))
		{
			DEBUG((EFI_D_ERROR,"Unable to reg unvote for rail %a\n", pProxyVoteCfg->RailNames[ConfigIndx]));
			return EFI_UNSUPPORTED;
		}
	}
		
	if (pProxyVoteCfg->IcbName != NULL)
	{
		if (EFI_SUCCESS != IcbUnvote(pProxyVoteCfg))
		{
			DEBUG((EFI_D_ERROR,"Unable to icb unvote for subsytem %a\n", pProxyVoteCfg->ClientName));
			return EFI_UNSUPPORTED;
		}
	}
	
	if (VoteDoneTime != 0)
	{
		HoldTime = GetPerformanceCounter() - VoteDoneTime;
		VoteDoneTime = 0;
		DEBUG((EFI_D_ERROR, "proxy unvote done subsysId=%d hold_time=%dms\n", pProxyVoteCfg->SubsysId, ConvertTimerCountms(HoldTime)));
	}
	return EFI_SUCCESS;
}

