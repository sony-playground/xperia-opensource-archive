/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		pil_proxy_vote_config.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version

================================================================================*/
#ifndef __PIL_PROXY_VOTE_CFG_H__
#define __PIL_PROXY_VOTE_CFG_H__

#include <api/systemdrivers/icbarb.h>

#define MAX_SUBSYSTEM 10

typedef struct
{
	UINT32					SubsysId;
	CHAR8*					ClientName;
	UINT32					NumOfRails;
	CHAR8**					RailNames;
	UINT32*					RailVtgLvl;
	CHAR8*					IcbName;
	UINT32					NumOfMaterSlave;
	ICBArb_MasterSlaveType*	MasterSlave;
	ICBArb_RequestType*		Request;
} PIL_PROXY_VOTE_CFG_TYPE;

extern PIL_PROXY_VOTE_CFG_TYPE PilProxyVoteConfig[MAX_SUBSYSTEM];

PIL_PROXY_VOTE_CFG_TYPE* LoadPilProxyVoteConfigFromDT(UINT32 SubsysId);

#endif // __PIL_PROXY_VOTE_CFG_H__
