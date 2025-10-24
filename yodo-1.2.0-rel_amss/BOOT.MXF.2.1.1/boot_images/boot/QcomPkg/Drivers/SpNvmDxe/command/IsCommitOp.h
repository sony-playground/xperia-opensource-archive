/*========================================================================
IsCommitOp.h
This file describes the IsCommit done operation struct.

Copyright (c) 2020 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=========================================================================*/
/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/09/20   ll      initial release
=============================================================================*/
#ifndef ISCOMMITOP_H_
#define ISCOMMITOP_H_

#include "Operation.h"

void *   IsCommitOp_new(va_list ap);
void     IsCommitOp_delete(void * _self);
int32_t  IsCommitOp_getRspSize();
int      IsCommitOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng);
int      IsCommitOp_get_is_skp(void * _self);
int      IsCommitOp_get_is_ari(void * _self);
uint8_t* IsCommitOp_get_marker(void * _self);
void     IsCommitOp_set_marker(void * _self,  uint8_t* marker);

/**
 * This struct defines the is commit done operation
 */
struct IsCommitOp {
    const void * Operation;

    boolean     m_is_skp;
    boolean     m_is_ari;
    uint8_t*    m_marker;

    is_commit_req_t* m_req;
    is_commit_rsp_t* m_rsp;
};

#endif /* ISCOMMITOP_H_ */




