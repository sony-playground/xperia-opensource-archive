/*========================================================================
CreatePartitionOp.cpp
This file describe the implementation of the CreatePartitionOp class.

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
#include "CreatePartitionOp.h"
#include "SecNvmManager.h"

void CreatePartitionOp_ctor(struct CreatePartitionOp * self, void* req)
{
    self->m_req = (create_partition_req_t*)req;

    memset(self->m_segSizes, 0, MAX_SEGS);

    switch (self->m_req->reqId) {
        case CREATE_PARTITION_REQUEST:
        case EXT_CREATE_PARTITION_REQUEST:
            self->m_is_ari=true;
            break;
        case CREATE_PARTITION_ARI_SKP_REQUEST:
        case EXT_CREATE_PARTITION_ARI_SKP_REQUEST:
            self->m_is_ari=true;
            self->m_is_skp=true;
            self->m_marker = self->m_req->arc;
            break;
        default:
            LOGE("invalid request id: %d", self->m_req->reqId);
            break;
    }


    for(uint8_t i=0; (i < self->m_req->numSegs) && (i < MAX_SEGS); i++) {
           if((CREATE_PARTITION_REQUEST == self->m_req->reqId) ||
                   (CREATE_PARTITION_ARI_SKP_REQUEST == self->m_req->reqId)) {
               self->m_segSizes[i] = MAX_BLOCKS_IN_SEGMENT;

           } else if((EXT_CREATE_PARTITION_REQUEST == self->m_req->reqId) ||
                   (EXT_CREATE_PARTITION_ARI_SKP_REQUEST == self->m_req->reqId)) {
               self->m_segSizes[i] = ((extended_create_partition_req_t*)(self->m_req))->segSizes[i];
           }
    }

    LOGE("reqId=%d, %d segments, isAri=%d, isSkp=%d",
            self->m_req->reqId, self->m_req->numSegs, self->m_is_ari, self->m_is_skp);
}


int32_t CreatePartitionOp_getRspSize()
{
    return sizeof(create_partition_rsp_t);
}


int CreatePartitionOp_execute(void * _self, void* rspBuffer, uint32_t rspSize, void * _mng)
{
    LOGD("CreatePartitionOp");
    struct CreatePartitionOp * self = (struct CreatePartitionOp *)_self;
    struct SecNvmManager* mng= (struct SecNvmManager*)_mng;
    //Check input parameter
    if (!rspBuffer || (rspSize < sizeof(generic_rsp_t))) {
        LOGE("invalid input parameters");
        return -EINVAL;
    }

    // prepare response buffer
    self->m_rsp = (create_partition_rsp_t*)rspBuffer;
    self->m_rsp->rspId = CREATE_PARTITION_RESPONSE;
    self->m_rsp->ret = NVM_SUCCESS;

    //if (self->m_req->reqId == CREATE_PARTITION_ARI_SKP_REQUEST || 
        //self->m_req->reqId == EXT_CREATE_PARTITION_ARI_SKP_REQUEST) {
        //SegDB       36K  0x98AA9000; Note only 1 seg allowed
        //self->m_rsp->baseAddr = 0x98AA9000;
    //}else {
        //sTPM-Lite NVM Data   36K  0x98AA0000 Note only 1 seg allowed
        //self->m_rsp->baseAddr = 0x98AA0000;
    //}

    if (!self->m_req || (self->m_req->numSegs > MAX_SEGS)
            || (rspSize != sizeof(create_partition_rsp_t))) {
        LOGE("invalid request parameters");
        self->m_rsp->ret = INVALID_MSG_PARAM;
        return 0;
    }
    memscpy(self->m_rsp->uuid, UUID_SIZE, self->m_req->uuid, UUID_SIZE);

    self->m_rsp->numSegs = self->m_req->numSegs;

    //mng.isInLockState()

    //mng.isAsyncCmdThreadBusy()

    // allocate DDR segments, and create segments files
    int ret = mng->allocatePartition(mng, self->m_req, self->m_rsp, &(self->m_rsp->baseAddr), self->m_rsp->offsets, _self, self->m_segSizes);
    if (ret) {
        LOGE("allocate partition fail (%d)", ret);
        switch (ret) {
           case -EEXIST:
               self->m_rsp->ret = PARTITION_ALREADY_EXIST;
               break;
           case -ENOBUFS:
               self->m_rsp->ret = NO_PARTITION_AVAILABLE;
               break;
           case -EBUSY:
               self->m_rsp->ret = SERVER_IS_BUSY;
               break;
           case -EINVAL:
               self->m_rsp->ret = VERIFICATION_FAIL;
               break;
           default:
               self->m_rsp->ret = CRITICAL_ERROR;
        }
    }
    return 0;
}


int CreatePartitionOp_get_is_skp(void * _self)
{
    LOGI("CreatePartitionOp--get_is_skp");
    struct CreatePartitionOp * self = (struct CreatePartitionOp *)_self;
    return self->m_is_skp;
}


int CreatePartitionOp_get_is_ari(void * _self)
{
    LOGI("CreatePartitionOp--get_is_ari");
    struct CreatePartitionOp * self = (struct CreatePartitionOp *)_self;
    return self->m_is_ari;
}


uint8_t* CreatePartitionOp_get_marker(void * _self)
{
    LOGI("CreatePartitionOp--get_marker");
    struct CreatePartitionOp * self = (struct CreatePartitionOp *)_self;
    return self->m_marker;
}


void CreatePartitionOp_set_marker(void * _self,  uint8_t* marker)
{
    LOGI("CreatePartitionOp--set_marker");
    struct CreatePartitionOp * self = (struct CreatePartitionOp *)_self;
    self->m_marker = marker;
}


void * CreatePartitionOp_new(va_list ap){

    void *req = va_arg(ap, void *);
    uint32_t reqSize = va_arg(ap, uint32_t);

    if (!req || (sizeof(create_partition_req_t) > reqSize)) {
        LOGE("Invalid request buffer");
        return NULL;
    }

    create_partition_req_t* create_req =  (create_partition_req_t*)req;
    if((EXT_CREATE_PARTITION_REQUEST == create_req->reqId) ||
                   (EXT_CREATE_PARTITION_ARI_SKP_REQUEST == create_req->reqId)) {
        if(reqSize < sizeof(extended_create_partition_req_t)) {
            LOGE("invalid request buffer reqSize=%d, expected:%lu",
                    reqSize, sizeof(extended_create_partition_req_t));
            return NULL;
        }
    }

    //Allocate the IsCommitOp object
    struct CreatePartitionOp * createPartitionOp = (struct CreatePartitionOp *)nvm_os_malloc(sizeof(struct CreatePartitionOp));
    ASSERT(createPartitionOp);

    //Call constructor
    CreatePartitionOp_ctor(createPartitionOp, req);
    return createPartitionOp;
}

void CreatePartitionOp_delete(void * _self){
     (void)_self;
     //do nothing
}
