/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		pil_proxy_vote.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/08/21	 avm  	    initial version

================================================================================*/

#ifndef __PIL_PROXY_VOTE_H__
#define __PIL_PROXY_VOTE_H__

EFI_STATUS PILProxyVote(UINT32);
EFI_STATUS PILProxyUnvote(UINT32);

#endif // __PIL_PROXY_VOTE_H__