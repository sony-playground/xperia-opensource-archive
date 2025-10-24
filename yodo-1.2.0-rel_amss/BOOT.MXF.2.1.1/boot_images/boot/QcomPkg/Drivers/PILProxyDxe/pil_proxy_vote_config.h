/*===============================================================================
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		pil_proxy_vote_config.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version
  06/29/22   yw         add flag in cfg struct to support DTB image
================================================================================*/
#ifndef __PIL_PROXY_VOTE_CFG_H__
#define __PIL_PROXY_VOTE_CFG_H__

#include <api/systemdrivers/icbarb.h>

#define MAX_SUBSYSTEM 10

/* flag macro */
#define	FLAG_VOTE_ONLY			0x1
#define FLAG_UNVOTE_ONLY		0x2
#define	FLAG_VOTE_AND_UNVOTE	(FLAG_VOTE_ONLY|FLAG_UNVOTE_ONLY)

#define FLAG_DTB_IMAGE			0x10
#define IS_DTB_IMAGE(f)			((f&FLAG_DTB_IMAGE)==FLAG_DTB_IMAGE)

typedef enum
{
	BRINGUP_SEQUENCE 	= 0,
	SHUTDOWN_SEQUENCE	= 1
} VOTING_SEQUENCE_TYPE;

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
	UINT32					FlagNum;
	UINT32*					Flag;
	VOTING_SEQUENCE_TYPE	LastSeq;	// the bringup/shutdown sequence used for unvote
} PIL_PROXY_VOTE_CFG_TYPE;

extern PIL_PROXY_VOTE_CFG_TYPE PilProxyVoteConfig[MAX_SUBSYSTEM];

PIL_PROXY_VOTE_CFG_TYPE* LoadPilProxyVoteConfigFromDT(UINT32 SubsysId);

#endif // __PIL_PROXY_VOTE_CFG_H__
