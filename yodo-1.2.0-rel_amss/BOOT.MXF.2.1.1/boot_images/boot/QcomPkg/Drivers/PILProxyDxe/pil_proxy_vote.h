/*===============================================================================
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		pil_proxy_vote.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version
  06/29/22   yw         change input type of vote and unvote APIs, to support DTB image
================================================================================*/
#include "pil_proxy_vote_config.h"

#ifndef __PIL_PROXY_VOTE_H__
#define __PIL_PROXY_VOTE_H__

EFI_STATUS PILProxyVote(PIL_PROXY_VOTE_CFG_TYPE*, VOTING_SEQUENCE_TYPE);
EFI_STATUS PILProxyUnvote(PIL_PROXY_VOTE_CFG_TYPE*, VOTING_SEQUENCE_TYPE);

#endif // __PIL_PROXY_VOTE_H__