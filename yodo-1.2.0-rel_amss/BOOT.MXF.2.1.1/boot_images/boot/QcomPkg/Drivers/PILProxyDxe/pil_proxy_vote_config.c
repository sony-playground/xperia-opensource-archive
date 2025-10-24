/*===============================================================================
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		pil_proxy_vote_config.c
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version
  06/29/22   yw         add flag in cfg struct to support DTB image
================================================================================*/

#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIDtbExtn.h>
#include <api/systemdrivers/icbarb.h>
#include "pil_proxy_vote_config.h"

#define PIL_PROXY_VOTE_CONFIG_NODE     "/soc/pil/pil_proxy_vote/pil_proxy_vote_"
#define DT_NODE_BUF_SIZE               100

PIL_PROXY_VOTE_CFG_TYPE PilProxyVoteConfig[MAX_SUBSYSTEM] = { 0 };

PIL_PROXY_VOTE_CFG_TYPE* LoadPilProxyVoteConfigFromDT(UINT32 SubsysId)
{
	STATIC EFI_DTB_EXTN_PROTOCOL *DtbExtnProtocol = NULL;
	EFI_STATUS Status = EFI_SUCCESS;
	FdtNodeHandle hNode;
	UINT32 Idx = 0;
	UINT32 Size = 0;
	CHAR8 PilProxyVoteNode[DT_NODE_BUF_SIZE];
	CHAR8* WalkStr = NULL;
	CHAR8* RailNamesStr = NULL;
	UINT32 RailConfigIndx = 0, Len = 0, RailNameLen = 0, RailNum = 0;
	UINT32 MasterSlaveIndx = 0;

	for (Idx = 0; Idx < MAX_SUBSYSTEM; Idx++)
	{
		if (PilProxyVoteConfig[Idx].SubsysId == SubsysId)
			return &PilProxyVoteConfig[Idx];
		
		if (PilProxyVoteConfig[Idx].SubsysId == 0)
			break;
	}
	
	if (Idx == MAX_SUBSYSTEM)
	{
		DEBUG((EFI_D_ERROR,"Not enough space to load dt data in PilProxyVoteConfig\n"));
		return NULL;
	}
	
	if (!DtbExtnProtocol)
	{
		Status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL, (VOID **)&DtbExtnProtocol);
		if (EFI_ERROR(Status))
		{
			DtbExtnProtocol = NULL;
			DEBUG((EFI_D_ERROR,"Failed to locate dtb protocol %r\n",Status));
			return NULL;
		}
	}
	
	if (DtbExtnProtocol && (EFI_SUCCESS == Status))
	{
		AsciiSPrint(PilProxyVoteNode, DT_NODE_BUF_SIZE, "%a%d", PIL_PROXY_VOTE_CONFIG_NODE, SubsysId);
		
		
		Status = DtbExtnProtocol->FdtGetNodeHandle (&hNode, PilProxyVoteNode);
		if (EFI_SUCCESS != Status) {
			DEBUG((EFI_D_ERROR,"Unable to find PIL Proxy Vote Configuration in dt for subsystem id: %d\n", SubsysId));
			return NULL;
		}
		
		// Subsytem Id
		Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "subsys_id", &PilProxyVoteConfig[Idx].SubsysId);
		if (EFI_SUCCESS != Status) {
			DEBUG((EFI_D_ERROR,"Unable to get subsystem id for node: %a\n", PilProxyVoteNode));
			return NULL;
		}
		
		// Client name
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "client_name", &Size);
		if (Status == EFI_SUCCESS)
		{
			if (PilProxyVoteConfig[Idx].ClientName != NULL)
				FreePool(PilProxyVoteConfig[Idx].ClientName);
			
			PilProxyVoteConfig[Idx].ClientName = AllocateZeroPool(Size);
			if (PilProxyVoteConfig[Idx].ClientName == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for client name for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			Status = DtbExtnProtocol->FdtGetStringPropList(&hNode, "client_name", PilProxyVoteConfig[Idx].ClientName, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"Unable to get Client Name for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
		}
		else {
			DEBUG((EFI_D_ERROR,"Unable to get Subsystem size for node: %a\n", PilProxyVoteNode));
			return NULL;
		}
		
		// Rail Name Configuration
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "rail_names", &Size);
		if (Status == EFI_SUCCESS)
		{
			if (RailNamesStr != NULL)
				FreePool(RailNamesStr);
			
			RailNamesStr = AllocateZeroPool(Size);
			if (RailNamesStr == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for Rail Name Str for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			Status = DtbExtnProtocol->FdtGetStringPropList(&hNode, "rail_names", RailNamesStr, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"Unable to get rail names for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			RailConfigIndx = 0; 
			Len = 0;
			RailNameLen = 0; 
			PilProxyVoteConfig[Idx].NumOfRails = 0;
			WalkStr = RailNamesStr;
			
			while (Len < Size)
			{
				RailNameLen = AsciiStrLen(WalkStr);
				Len += (RailNameLen+1);
				WalkStr += (RailNameLen+1);
				PilProxyVoteConfig[Idx].NumOfRails++;
			}
			
			WalkStr = RailNamesStr;
			
			if (PilProxyVoteConfig[Idx].RailNames != NULL)
				FreePool(PilProxyVoteConfig[Idx].RailNames);
			
			PilProxyVoteConfig[Idx].RailNames = (CHAR8 **) AllocateZeroPool(PilProxyVoteConfig[Idx].NumOfRails * sizeof(CHAR8*));
			for (RailConfigIndx = 0; RailConfigIndx < PilProxyVoteConfig[Idx].NumOfRails; RailConfigIndx++)
			{
				PilProxyVoteConfig[Idx].RailNames[RailConfigIndx] = WalkStr;
				RailNameLen = AsciiStrLen(WalkStr);
				WalkStr += (RailNameLen+1);
			}
		}
		else {
			PilProxyVoteConfig[Idx].RailNames = NULL;
			PilProxyVoteConfig[Idx].NumOfRails = 0;
			Status = EFI_SUCCESS;
		}
		
		//Rail Voltage Level Configuration;
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "rail_voltage_levels", &Size);
		if (Status == EFI_SUCCESS)
		{
			PilProxyVoteConfig[Idx].RailVtgLvl = AllocateZeroPool(Size);
			if (PilProxyVoteConfig[Idx].RailVtgLvl == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for Rail Vtg Lvl for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			Status = DtbExtnProtocol->FdtGetUint32PropList(&hNode, "rail_voltage_levels", PilProxyVoteConfig[Idx].RailVtgLvl, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"Unable to get Rail Voltage Levels for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			RailNum = Size / sizeof(UINT32);
			
			if (RailNum != PilProxyVoteConfig[Idx].NumOfRails)
			{
				DEBUG((EFI_D_ERROR,"Rail Name and Rail Voltage Level are not configuered correctly in dt for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
		}
		else {
			PilProxyVoteConfig[Idx].RailVtgLvl = NULL;
			Status = EFI_SUCCESS;
		}
		
		//Icb configuration
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "icb_name", &Size);
		if (Status == EFI_SUCCESS)
		{
			PilProxyVoteConfig[Idx].IcbName = AllocateZeroPool(Size);
			if (PilProxyVoteConfig[Idx].IcbName == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for ICB name for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			Status = DtbExtnProtocol->FdtGetStringPropList(&hNode, "icb_name", PilProxyVoteConfig[Idx].IcbName, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"Unable to get ICB Name for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
		}
		else
		{
			PilProxyVoteConfig[Idx].IcbName = NULL;
			Status = EFI_SUCCESS;
		}
		
		//Icb arb master slave
		UINT32 SliceIdx = 0;
		UINT32 Count = 2;
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "icb_arb_master_slave", &Size);
		if (Status == EFI_SUCCESS)
		{
			PilProxyVoteConfig[Idx].NumOfMaterSlave = Size / sizeof(ICBArb_MasterSlaveType);
			
			if (PilProxyVoteConfig[Idx].MasterSlave != NULL)
				FreePool(PilProxyVoteConfig[Idx].MasterSlave);
			
			PilProxyVoteConfig[Idx].MasterSlave = AllocateZeroPool(PilProxyVoteConfig[Idx].NumOfMaterSlave * sizeof(ICBArb_MasterSlaveType));
			if (PilProxyVoteConfig[Idx].MasterSlave == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for ICB Master Slave Configuration for node: %a\n", PilProxyVoteNode));
				return NULL;
			}

			for (MasterSlaveIndx = 0; MasterSlaveIndx < PilProxyVoteConfig[Idx].NumOfMaterSlave; MasterSlaveIndx++)
			{
				Status = DtbExtnProtocol->FdtGetUint32PropListSlice(&hNode, "icb_arb_master_slave", (UINT32*) &PilProxyVoteConfig[Idx].MasterSlave[MasterSlaveIndx], SliceIdx, Count);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"Unable to get ICB Arb Master Slave pair %d for node: %a\n", MasterSlaveIndx, PilProxyVoteNode));
					return NULL;
				}
				SliceIdx += Count;
			}
		}
		else
			Status = EFI_SUCCESS;
		
		//Icb arb request type
		SliceIdx = 0;
		Count = 1;
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "icb_arb_request_type", &Size);
		if (Status == EFI_SUCCESS)
		{
			if (PilProxyVoteConfig[Idx].NumOfMaterSlave != (Size / sizeof(ICBArb_RequestTypeType)))
			{
				DEBUG((EFI_D_ERROR,"icb_arb_master_slave and icb_arb_request_type are not configuered correctly in dt for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			if (PilProxyVoteConfig[Idx].Request != NULL)
				FreePool(PilProxyVoteConfig[Idx].Request);
			
			PilProxyVoteConfig[Idx].Request = AllocateZeroPool(PilProxyVoteConfig[Idx].NumOfMaterSlave * sizeof(ICBArb_RequestType));
			if (PilProxyVoteConfig[Idx].Request == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for ICB Request for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			for (MasterSlaveIndx = 0; MasterSlaveIndx < PilProxyVoteConfig[Idx].NumOfMaterSlave; MasterSlaveIndx++)
			{
				Status = DtbExtnProtocol->FdtGetUint32PropListSlice(&hNode, "icb_arb_request_type", &PilProxyVoteConfig[Idx].Request[MasterSlaveIndx].arbType, SliceIdx, Count);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"Unable to get ICB Arb request type for node: %a\n", PilProxyVoteNode));
					return NULL;
				}
				SliceIdx += Count;
			}
		}
		else
			Status = EFI_SUCCESS;
		
		//Icb arb request data
		SliceIdx = 0;
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "icb_arb_request_data", &Size);
		if (Status == EFI_SUCCESS)
		{
			if (PilProxyVoteConfig[Idx].NumOfMaterSlave != (Size / (sizeof(UINT64) * 2)))
			{
				DEBUG((EFI_D_ERROR,"icb_arb_master_slave and icb_arb_request_type are not configuered correctly in dt for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			UINT64* arbData = AllocateZeroPool(Size);
			if (arbData == NULL) {
				DEBUG((EFI_D_ERROR,"Unable to get enough memory for arbData for node: %a\n", PilProxyVoteNode));
				return NULL;
			}
			
			Status = DtbExtnProtocol->FdtGetUint64PropList(&hNode, "icb_arb_request_data", (UINT64*) arbData, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"Unable to get ICB Arb request data for node: %a\n", PilProxyVoteNode));
				return NULL;
			}

			for (MasterSlaveIndx = 0; MasterSlaveIndx < PilProxyVoteConfig[Idx].NumOfMaterSlave; MasterSlaveIndx++)
			{
				PilProxyVoteConfig[Idx].Request[MasterSlaveIndx].arbData.type3.uIb = arbData[SliceIdx++];
				PilProxyVoteConfig[Idx].Request[MasterSlaveIndx].arbData.type3.uAb = arbData[SliceIdx++];
			}
			FreePool(arbData);
		}
		else
			Status = EFI_SUCCESS;
		
		Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "flag", &Size);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"error: failed to get flag size for %a\n", PilProxyVoteNode));
			return NULL;
		}
		
		PilProxyVoteConfig[Idx].FlagNum = Size/sizeof(UINT32);
		UINT32* Flag = AllocateZeroPool(Size);
		if (Flag==NULL)
		{
			DEBUG((EFI_D_ERROR,"error: failed to alloc flag buffer for %a\n", PilProxyVoteNode));
			return NULL;
		}
			
		Status = DtbExtnProtocol->FdtGetUint32PropList(&hNode, "flag", Flag, Size);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"error: failed to read flag value for %a\n", PilProxyVoteNode));
			return NULL;
		}
		PilProxyVoteConfig[Idx].Flag = Flag;
	}
	
	return &PilProxyVoteConfig[Idx];
}
