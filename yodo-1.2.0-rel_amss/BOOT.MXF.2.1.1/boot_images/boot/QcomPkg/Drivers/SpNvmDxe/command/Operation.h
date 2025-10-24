/*========================================================================
Operation.h
This file describes the Operation abstract class.

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
#ifndef OPERATION_H_
#define OPERATION_H_

#include "osCommon.h"
#include "Commands.h"
#include <string.h>		// memset()
#include <stdbool.h>	// bool , true , false
#include <stdint.h>		// size_t
#include <stdarg.h>		// va_arg()
#include <stdbool.h>	// bool , true , false
#include <Uefi.h>
#include "QcomLib.h" //#include <Library/QcomLib.h>

void *   DefaultOp_new(va_list ap);
void     DefaultOp_delete(void * _self);
int32_t  DefaultOp_getRspSize();
int      DefaultOp_execute(void * _self, void*  rspBuffer, uint32_t rspSize, void* _mng);
int      DefaultOp_get_is_skp(void * _self);
int      DefaultOp_get_is_ari(void * _self);
uint8_t* DefaultOp_get_marker(void * _self);
void     DefaultOp_set_marker(void * _self, uint8_t* marker);

/**
 * This struct defines the Operation supported methods. Each
 * operation has execute() function:
 *  - receives request struct as an input
 *  - replies with response struct as an output
 *  - above structs defined in the Commands.h
 *
 *  For the requests that expect to receive and parse physical address of the
 *  shared ION buffer, getRspSize() method should set *out_isRspModified to true
 */
struct Operation{
    void * (* new) (va_list ap);
    void (* delete) (void * operation);

    /**
    * The function ptr enforce final object getRspSize
    * implementation.
    * The function returns the response message size of the
    * concrete operation
    *
    * @return size of the concrete operation repose buffer.
    */
    int32_t (* getRspSize)(void);

   /**
    * The function ptr enforce final object execute implementation.
    * The function executes the operation request.
    *
    * @param rsp           - The response allocated buffer
    * @param rspSize       - The response buffer size
    * @param mng           - The secnvm manager app instance
    *
    *
    * @return -1 on failure that can't be send in the response,
    *  and 0 otherwise
    */
    int (* exec) (void * self, void* rspBuffer, uint32_t rspSize, void* _mng);

    int      (* get_is_skp) (void * _self);
    int      (* get_is_ari) (void * _self);
    uint8_t* (* get_marker) (void * _self);
    void     (* set_marker) (void * _self, uint8_t* marker);
};

//void * newOperation (const struct Operation * operation, ...);
void * newOperation (const void * operation, ...);

#endif /* OPERATION_H_ */
