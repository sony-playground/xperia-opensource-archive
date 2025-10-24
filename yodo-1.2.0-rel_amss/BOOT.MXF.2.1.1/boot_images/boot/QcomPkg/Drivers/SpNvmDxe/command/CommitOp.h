/*========================================================================
CommitOp.h
This file describes the Commit operation class.

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
#ifndef COMMITOP_H_
#define COMMITOP_H_

#include "Operation.h"

void *   CommitOp_new(va_list ap);
void     CommitOp_delete(void * _self);
int32_t  CommitOp_getRspSize();
int      CommitOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng);
int      CommitOp_get_is_skp(void * _self);
int      CommitOp_get_is_ari(void * _self);
uint8_t* CommitOp_get_marker(void * _self);
void     CommitOp_set_marker(void * _self,  uint8_t* marker);

/* This struct defines the commit operation */
struct CommitOp {
    const void * Operation;

    boolean     m_is_skp;
    boolean     m_is_ari;
    uint8_t*    m_marker;

    commit_req_t*    m_req;
    commit_rsp_t*    m_rsp;
    struct SecNvmManager*   m_mng;
};

#endif /* COMMITOP_H_ */




