// Copyright (c) 2017, 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.

#include <stdint.h>
#include <stddef.h>
#include "object.h"

#include <Protocol/EFIScm.h>
#include <string.h>
#include "cdefs.h"
#include "ITestCBack.h"
#include "ITestCBack_invoke.h"
#include "CTestCallable_priv.h"
#include "heap.h"


extern QCOM_SCM_PROTOCOL *ScmProtocol;

static int32_t CTestCallable_retain(TestCallable *me)
{
  me->refs++;
  return Object_OK;
}

static int32_t CTestCallable_release(TestCallable *me)
{

  if (--me->refs == 0) {

    Object_RELEASE_IF(me->oArg);
    Object_RELEASE_IF(me->oOOArg);
    Object_RELEASE_IF(me->oOOArg0);
    Object_RELEASE_IF(me->oOOArg1);
    Object_RELEASE_IF(me->oOOArg2);
    HEAP_FREE_PTR(me);
  }
  return Object_OK;
}

static int32_t CTestCallable_call(TestCallable *me)
{

  me->counter++;
  me->op = ITestCallable_OP_call;
  return me->retValue;
}

static int32_t CTestCallable_callWithBuffer(TestCallable *me, const void *arg_ptr, size_t arg_len)
{

  me->counter++;
  me->op = ITestCallable_OP_callWithBuffer;
  if ((arg_len == me->bArg_len) &&
      (0 == memcmp(arg_ptr, me->bArg_ptr, arg_len))) {
    return me->retValue;
  } else {
    return me->retValueError;
  }
}

static int32_t CTestCallable_callWithBufferOut(TestCallable *me, void *arg1_ptr, size_t arg1_len, size_t *arg1_lenout)
{

  me->counter++;
  me->op = ITestCallable_OP_callWithBufferOut;
  memset(arg1_ptr, 'A', arg1_len);
  *arg1_lenout = arg1_len;
  return me->retValue;
}

static int32_t CTestCallable_callWithObject(TestCallable *me, Object arg_val)
{

  me->counter++;
  me->op = ITestCallable_OP_callWithObject;
  /* The passed object is supposed to be a callback Obj, so we can compare its members directly */
  if ((arg_val.invoke == me->oArg.invoke) &&
      (arg_val.context == me->oArg.context)) {
    return me->retValue;
  } 
//  else if (arg_val.invoke == RemoteObj_invoke) {
//    return ITestCallable_ERROR_OBJECT_REMOTE;
//  }
  else {
    return me->retValueError;
  }
}

static int32_t CTestCallable_callGetObject(TestCallable *me, Object *arg_ptr)
{

  me->counter++;
  me->op = ITestCallable_OP_callGetObject;
  Object_INIT(*arg_ptr, me->oOOArg);
  return me->retValue;
}

static int32_t CTestCallable_callGetThreeObjects(TestCallable *me, Object *arg0_ptr, Object *arg1_ptr, Object *arg2_ptr)
{

  me->counter++;
  me->op = ITestCallable_OP_callGetThreeObjects;
  Object_INIT(*arg0_ptr, me->oOOArg0);
  Object_INIT(*arg1_ptr, me->oOOArg1);
  Object_INIT(*arg2_ptr, me->oOOArg2);
  return me->retValue;
}

static int32_t CTestCallable_callAddInt(TestCallable *me, uint32_t inVal1, uint32_t inVal2, uint32_t *outVal)
{
  *outVal = inVal1 + inVal2;
  return me->retValue;
}

static int32_t CTestCallable_returnError(TestCallable *me)
{
  (void)me;
  return ITestCallable_ERROR;
}

static int32_t CTestCallable_callCopyBuffer(TestCallable *me,
                                            const void *inBuf, size_t inBuf_len,
                                            void *outBuf, size_t outBuf_len,
                                            size_t *outBuf_lenOut)
{
  me->counter++;
  me->op = ITestCallable_OP_callCopyBuffer;

  *outBuf_lenOut = memscpy(outBuf, outBuf_len, inBuf, inBuf_len);

  return Object_OK;
}

static ITestCallable_DEFINE_INVOKE(CTestCallable_invoke, CTestCallable_, TestCallable*)

int32_t CTestCallable_open(Object* obj)
{
  TestCallable *me = HEAP_ZALLOC_TYPE(TestCallable);
  if (!me) {
     return Object_ERROR_KMEM;
  }

  /* Get an QSEE OO we can return as needed. The RootClientEnv fits the picture
   * and I don't even need to ask for it :) */

  ScmProtocol->ScmGetClientEnv(ScmProtocol, &(me->oOOArg));
  if (Object_isNull(me->oOOArg)) {
    HEAP_FREE_PTR(me);
    return Object_ERROR_KMEM;
  }
  me->refs = 1;
  me->op = -1;
  *obj = (Object) { CTestCallable_invoke, me };
  return Object_OK;
}
