/*========================================================================
IsCommitOp.cpp
This file describe the implementation of the IsCommitOp class.

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
#include "IsCommitOp.h"

void IsCommitOp_ctor(struct IsCommitOp * self, void* req)
{
   self->m_req = (is_commit_req_t*)req;

   switch (self->m_req->reqId) {
        case IS_COMMIT_REQUEST:
            self->m_is_ari=true;
            break;
        default:
            LOGE("invalid request id: %d", self->m_req->reqId);
            break;
    }
    LOGE("reqId=%d, isAri=%d, isSkp=%d",
            self->m_req->reqId, self->m_is_ari, self->m_is_skp);
}


int32_t  IsCommitOp_getRspSize()
{
    LOGI("IsCommitOp_getRspSize");
    return sizeof(is_commit_rsp_t);
}

int IsCommitOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng)
{
    (void)_mng;
    struct IsCommitOp * self = (struct IsCommitOp *)_self;

    LOGD("IsCommitOp");

    if (!rspBuffer || (rspSize < sizeof(generic_rsp_t))) {
        LOGE("invalid input parameters");
        return -1;
    }
    self->m_rsp = (is_commit_rsp_t*)rspBuffer;

    if (!self->m_req || (rspSize < sizeof(is_commit_rsp_t))) {
        LOGE("invalid message parameters");
        self->m_rsp->ret = INVALID_MSG_PARAM;
        return 0;
    }

    // spcom messages defined in SP and NVM service must be same
    if (self->m_req && (self->m_req->nvm_version != NVM_HANA_HEADER_VERSION) &&
            self->m_req->nvm_version != NVM_KONA_HEADER_VERSION) {
        LOGE("NVM version mismatch: requested nvm_version=%d, Supported  versions= {%d , %d}",
                self->m_req->nvm_version, NVM_HANA_HEADER_VERSION, NVM_KONA_HEADER_VERSION);
        self->m_rsp->ret = NVM_HEADER_VERSION_MISMATCH;
        return -1;
    }
    LOGD("NVM version is supported: %d", self->m_req->nvm_version);

    self->m_rsp->rspId = IS_COMMIT_RESPONSE;
    self->m_rsp->ret = NVM_SUCCESS;
    return 0;
}


int IsCommitOp_get_is_skp(void * _self)
{
    LOGI("IsCommitOp--get_is_skp");
    struct IsCommitOp * self = (struct IsCommitOp *)_self;
    return self->m_is_skp;
}


int IsCommitOp_get_is_ari(void * _self)
{
    LOGI("IsCommitOp--get_is_ari");
    struct IsCommitOp * self = (struct IsCommitOp *)_self;
    return self->m_is_ari;
}


uint8_t* IsCommitOp_get_marker(void * _self)
{
    LOGI("IsCommitOp--get_marker");
    struct IsCommitOp * self = (struct IsCommitOp *)_self;
    return self->m_marker;
}


void IsCommitOp_set_marker(void * _self,  uint8_t* marker)
{
    LOGI("IsCommitOp--set_marker");
    struct IsCommitOp * self = (struct IsCommitOp *)_self;
    self->m_marker = marker;
}


void * IsCommitOp_new(va_list ap){

    void *req = va_arg(ap, void *);
    uint32_t reqSize = va_arg(ap, uint32_t);
    LOGI("IsCommitOp_new, reqSize[%d]", reqSize);
    if (!req || (sizeof(is_commit_req_t) > reqSize)) {
        LOGE("Invalid request buffer");
        return NULL;
    }

    //Allocate the IsCommitOp object
    struct IsCommitOp * isCommitOp = (struct IsCommitOp *)nvm_os_malloc(sizeof(struct IsCommitOp));
    ASSERT(isCommitOp);

    //Call constructor
    IsCommitOp_ctor(isCommitOp, req);
    return isCommitOp;
}

void IsCommitOp_delete(void * _self){
     (void)_self;
     //do nothing
}

