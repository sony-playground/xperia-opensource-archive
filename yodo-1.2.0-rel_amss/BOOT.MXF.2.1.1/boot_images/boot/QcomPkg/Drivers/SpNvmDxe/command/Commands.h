/*========================================================================
Commands.h
This file describes the commands structure types of the SP messages.

The request/commands messages are sent by the SP library via
the SPCOM channel.

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
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "SecNvmDefs.h"

typedef enum {
   CREATE_PARTITION_REQUEST = 0,
   OPEN_PARTITION_REQUEST,            //1
   COMMIT_REQUEST,                    //2
   ABORT_REQUEST,                     //3
   ASYNC_COMMIT_REQUEST,              //4
   IS_COMMIT_REQUEST,                 //5

   // SKP special app case
   CREATE_PARTITION_ARI_SKP_REQUEST,  //6
   OPEN_PARTITION_ARI_SKP_REQUEST,    //7
   COMMIT_ARI_SKP_REQUEST,            //8

   // Dynamic segment request
   EXT_CREATE_PARTITION_REQUEST,                //9
   EXT_OPEN_PARTITION_REQUEST,                 //10

   // Dynamic segment SKP request
   EXT_CREATE_PARTITION_ARI_SKP_REQUEST,       //11
   EXT_OPEN_PARTITION_ARI_SKP_REQUEST,         //12

   // Scratch buffer support
   GET_SBDB_ADDR_REQUEST,            // 13
   LOOKUP_SBAPP_REQUEST,             // 14

   REQUEST_MAX_SIZE
} sec_nvm_request_id_t;

typedef enum {
   CREATE_PARTITION_RESPONSE = 100,
   OPEN_PARTITION_RESPONSE,
   COMMIT_RESPONSE,
   ABORT_RESPONSE,
   ASYNC_COMMIT_RESPONSE,
   IS_COMMIT_RESPONSE,
   SCRATCH_BUFFER_RESPONSE,
   RESPONSE_MAX_SIZE
} sec_nvm_response_id_t;

typedef enum {
   NVM_SUCCESS = 0,
   GENERAL_ERROR,
   VERIFICATION_FAIL,
   NO_PARTITION_AVAILABLE,
   INVALID_MSG_PARAM,
   CORRUPTION_ERROR,
   SERVER_IS_BUSY,
   PARTITION_ALREADY_EXIST, //not used anymore - SP block reopen
   PARTITION_DOESNT_EXIST,
   CRITICAL_ERROR,
   NVM_HEADER_VERSION_MISMATCH,
} sec_nvm_result_t;

#pragma pack(push, 1) // exact fit - no padding
typedef struct {
    uint8_t cmac[CMAC_SIZE];
} cmac_t;

typedef struct {
   uint8_t segNum;
   cmac_t  cmac;
} seg_info_t;

typedef struct {
   uint8_t reqId;
} generic_req_t;

typedef struct GenericRsp {
   uint8_t rspId;
   int8_t ret;
} generic_rsp_t;

//  CREATE_PARTITION_REQUEST
typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint8_t arc[ARC_SIZE];
   cmac_t  cmacs[MAX_SEGS];
} create_partition_req_t;

//  EXTENDED CREATE_PARTITION_REQUEST
typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint8_t arc[ARC_SIZE];
   cmac_t  cmacs[MAX_SEGS];
   uint32_t segSizes[MAX_SEGS];
} extended_create_partition_req_t;

typedef struct {
   uint8_t rspId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint64_t baseAddr;
   uint32_t offsets[MAX_SEGS];
   int8_t ret;
} create_partition_rsp_t;

// OPEN_PARTITION_REQUEST
typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint8_t arc[ARC_SIZE];
   cmac_t  cmacs[MAX_SEGS];
} open_partition_req_t;

// EXTENDED OPEN_PARTITION_REQUEST
typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint8_t arc[ARC_SIZE];
   cmac_t  cmacs[MAX_SEGS];
   uint32_t segSizes[MAX_SEGS];
} extended_open_partition_req_t;

typedef struct {
   uint8_t rspId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   uint64_t baseAddr;
   uint32_t offsets[MAX_SEGS];
   int8_t ret;
} open_partition_rsp_t;

// COMMIT_REQUEST
typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   seg_info_t  segs[MAX_SEGS];
   uint8_t arc[ARC_SIZE];
} commit_req_t;

typedef struct {
   uint8_t rspId; //ASYNC_COMMIT_RESPONSE
   int8_t ret;
} async_commit_rsp_t;

typedef struct {
   uint8_t rspId;
   uint8_t uuid[UUID_SIZE];
   int8_t ret;
} commit_rsp_t;

typedef struct {
   uint8_t reqId;
   uint8_t nvm_version;
} is_commit_req_t;

typedef struct {
   uint8_t rspId;
   commit_rsp_t commitRsp; //COMMIT_RESPNSE id
   uint8_t isDone;
   int8_t ret;
} is_commit_rsp_t;

typedef struct {
   uint8_t reqId;
   uint8_t uuid[UUID_SIZE];
   uint8_t numSegs;
   seg_info_t  segs[MAX_SEGS];
} abort_req_t;

typedef struct {
   uint8_t rspId;
   uint8_t uuid[UUID_SIZE];
   uint8_t ret;
} abort_rsp_t;


// GET_SBDB_ADDR_REQUEST
// LOOKUP_SBAPP_REQUEST
typedef struct {
   uint8_t  reqId;
   uint8_t  numSegs;        // number of sb supported
   uint64_t baseAddr;       // ScratchDb/app sb address
   uint8_t  is_created;     // equals to false iif exists
   uint8_t  uuid[UUID_SIZE];// sb owner uuid
   uint32_t  size;           // size of application sb
   int8_t   ret;
} scratch_buffer_req_rsp_t;

#pragma pack(pop)

#endif /* COMMANDS_H_ */
