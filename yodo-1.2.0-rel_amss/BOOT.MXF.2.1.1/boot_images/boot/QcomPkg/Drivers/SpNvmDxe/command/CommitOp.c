/*========================================================================
CommitOp.cpp
This file describe the implementation of the CommitOp class.

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
#include "CommitOp.h"
#include "SecNvmManager.h"

void CommitOp_ctor(struct CommitOp * self, void* req)
{
    self->m_req = (commit_req_t*)req;

    switch (self->m_req->reqId) {
        case COMMIT_REQUEST:
        case ASYNC_COMMIT_REQUEST:
            self->m_is_ari=true;
            break;
        case COMMIT_ARI_SKP_REQUEST:
            self->m_is_ari=true;
            self->m_is_skp=true;
            self->m_marker = self->m_req->arc;
            break;
        default:
            LOGE("invalid request id: %d", self->m_req->reqId);
            break;
    }
    LOGE("reqId=%d, %d segments, isAri=%d, isSkp=%d",
            self->m_req->reqId, self->m_req->numSegs, self->m_is_ari, self->m_is_skp);
}


int32_t  CommitOp_getRspSize()
{
    return sizeof(commit_rsp_t);
}


int  CommitOp_execute (void * _self, void* rspBuffer, uint32_t rspSize, void * _mng)
{
    struct CommitOp * self = (struct CommitOp *)_self;
    struct SecNvmManager* mng= (struct SecNvmManager*)_mng;

    LOGD("CommitOp");

    if (!rspBuffer || (rspSize < sizeof(generic_rsp_t))) {
        LOGE("invalid input parameters");
        return -EINVAL;
    }

    self->m_rsp = (commit_rsp_t*)rspBuffer;
    self->m_rsp->rspId = COMMIT_RESPONSE;
    self->m_rsp->ret = NVM_SUCCESS;

    //Check input message parameters
    if (!self->m_req || self->m_req->numSegs > MAX_SEGS) {
        LOGE("invalid message parameters");
        self->m_rsp->ret = INVALID_MSG_PARAM;
        return 0;
    }

    int ret = mng->updateSegmentsData(mng, self->m_req, _self);
    if (ret) {
        LOGE("Fail to update segment data (%d)", ret);
        self->m_rsp->ret = CRITICAL_ERROR;
    }
    return 0;
}


int CommitOp_get_is_skp(void * _self)
{
    LOGI("CommitOp--get_is_skp");
    struct CommitOp * self = (struct CommitOp *)_self;
    return self->m_is_skp;
}


int CommitOp_get_is_ari(void * _self)
{
    LOGI("CommitOp--get_is_ari");
    struct CommitOp * self = (struct CommitOp *)_self;
    return self->m_is_ari;
}


uint8_t* CommitOp_get_marker(void * _self)
{
    LOGI("CommitOp--get_marker");
    struct CommitOp * self = (struct CommitOp *)_self;
    return self->m_marker;
}


void CommitOp_set_marker(void * _self,  uint8_t* marker)
{
    LOGI("CommitOp--set_marker");
    struct CommitOp * self = (struct CommitOp *)_self;
    self->m_marker = marker;
}


void * CommitOp_new(va_list ap){

    void *req = va_arg(ap, void *);
    uint32_t reqSize = va_arg(ap, uint32_t);

    if (!req || (sizeof(commit_req_t) != reqSize)) {
        LOGE("invalid request buffer");
        return NULL;
    }

    //Allocate the IsCommitOp object
    struct CommitOp * commitOp = (struct CommitOp *)nvm_os_malloc(sizeof(struct CommitOp));
    ASSERT(commitOp);

    //Call constructor
    CommitOp_ctor(commitOp, req);
    return commitOp;
}

void CommitOp_delete(void * _self){
     (void)_self;
     //do nothing
}
