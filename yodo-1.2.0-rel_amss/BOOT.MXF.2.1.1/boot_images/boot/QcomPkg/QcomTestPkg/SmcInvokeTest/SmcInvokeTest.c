/** @file SmcInvokeTest.c
   
  Tests for using ScmDxe SmcInvoke interface

  Copyright (c) 2020-2022 Copyright Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

*/
/*=============================================================================
                               EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/31/21   shl     Added loading commonLib call
 12/02/19   shl     Initial revision

=============================================================================*/
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include <Include/scm_qsee_interface.h>
#include <Library/EfiFileLib.h>
#include <Library/QcomLib.h>

#include "cdefs.h"

#include <object.h>
#include "IClientEnv.h"
#include "CAppLoader.h"
#include "IAppLoader.h"
#include "IAppController.h"

#include "CTestCallable_open.h"
#include "CTestCallable_priv.h"
#include "CTestCBack.h"

#include "CTestParams.h"
#include "CTestParams_open.h"

#include "ITestCBack.h"
#include "ITestParams.h"
#include "smcinvoketestapp_uids.h"


const UINT32 LOOP = 3;

#define TEST_RETURN(xx)                                                   \
  do                                                                      \
  {                                                                       \
    if ((xx) != 0 )                                                       \
    {                                                                     \
      AsciiPrint("........ %a:%d Failed!  ret = 0x%x  \n", __FUNCTION__, __LINE__, (xx));   \
      numOfFailedTest++;                                                  \
      goto Exit;                                                          \
    }                                                                     \
  } while(0)


#define TEST_TRUE(xx)                                                     \
  do                                                                      \
  {                                                                       \
    if (!(xx))                                                            \
    {                                                                     \
      AsciiPrint("........ %a:%d Failed!\n", __FUNCTION__, __LINE__);     \
      numOfFailedTest++;                                                  \
      goto Exit;                                                          \
    }                                                                     \
  } while(0)


static UINT32 numOfFailedTest = 0;

QCOM_SCM_PROTOCOL       *ScmProtocol       = NULL;
EFI_SHMBRIDGE_PROTOCOL  *ShmBridgeProtocol = NULL;

static  Object  clientEnv        = Object_NULL;
static  Object  clientEnvA[LOOP] = {Object_NULL};
static  Object  appLoader        = Object_NULL;
static  Object  appController    = Object_NULL;
static  UINT8  *Image            = NULL;
static  UINTN   ImageSize        = 0;

static  UINT32  refCount  = 0;
static  UINT32  refCount1 = 0;

typedef struct
{
  UINT32   remoteHandle;
  UINT32   magicNum;
  size_t   refs;
} RemoteObjCxt;

static CHAR8  TzTestAppName[] = "smcinvoketestapp";
static CHAR8  TzTestAppFile[] = "fv4:\\smcinvoketestapp.mbn";


#define   LEGACY_LISTENER_ID      0xABCD1234
static UINT32 LegacyCbCounter = 0;
UINT8* BufCb;
UINTN  BufCbSize = 0x1000;


EFI_STATUS ReadImage(void)
{
   EFI_STATUS      Status  = EFI_LOAD_ERROR;
   EFI_OPEN_FILE  *File    = NULL;
   UINT8          *Buf     = NULL;
   UINTN           BufSize = 0;

   File = EfiOpen (TzTestAppFile, EFI_FILE_MODE_READ, EFI_SECTION_RAW);
   TEST_TRUE( File != NULL);

   Status = EfiReadAllocatePool (File, (VOID**)&Buf, &BufSize);

   AsciiPrint( "BufSize =%d \n", BufSize );

   EfiClose( File );

   TEST_RETURN( Status );
   TEST_TRUE(Buf != NULL );
   TEST_TRUE(BufSize != 0 );

   Image = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &BufSize, ShmBridgeBootSvcData);
   TEST_TRUE(Image != NULL );

   ImageSize = BufSize;
   CopyMem(Image, Buf, BufSize);

   FreePool( Buf );

Exit:

   return Status;
}


void FreeImage(void)
{ 
   if( Image )
      ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, Image);

   Image     = NULL;  
   ImageSize = 0;

   return;
}


static EFI_STATUS Start(void)
{     
   EFI_STATUS   Status = EFI_SUCCESS; 
   int          ret    = Object_OK;                                                                    
                                                                                                                                                                                  
   Status = ScmProtocol->ScmGetClientEnv(ScmProtocol, &clientEnv);
   TEST_RETURN( Status );
   TEST_TRUE( !Object_isNull(clientEnv)); 
                                                                                         
   ret = IClientEnv_open(clientEnv, CAppLoader_UID, &appLoader);
   TEST_RETURN( ret );
   TEST_TRUE(!Object_isNull(appLoader));
                                                                                         
   ret = IAppLoader_loadFromBuffer(appLoader, Image, ImageSize, &appController);
   TEST_RETURN( ret );
   TEST_TRUE(!Object_isNull(appController));

   return 0;

Exit:

   return ( Status | ret );
}


static void End( )
{
   Object_release(appController);
   TEST_TRUE( ((RemoteObjCxt *)(appController.context))->magicNum == 0  );
   appController = Object_NULL;

   Object_release(appLoader);
   TEST_TRUE( ((RemoteObjCxt *)(appLoader.context))->magicNum == 0  );
   appLoader = Object_NULL;

   Object_release(clientEnv);

Exit:
   return;
}


void MutiClientsTest(void)
{
   EFI_STATUS   Status      = EFI_SUCCESS;
   UINT32       numOfFail   = numOfFailedTest;

   Status = ScmProtocol->ScmGetClientEnv( ScmProtocol, &clientEnv);
   TEST_RETURN( Status );
   TEST_TRUE( !Object_isNull(clientEnv));

   refCount = ((RemoteObjCxt *)(clientEnv.context))->refs;

   for( int ii = 0; ii < LOOP; ii++ )
   {
      Status = ScmProtocol->ScmGetClientEnv( ScmProtocol, &clientEnv );
      TEST_RETURN( Status );
      TEST_TRUE( !Object_isNull(clientEnv)); 
   }

   refCount1 = ((RemoteObjCxt *)(clientEnv.context))->refs;
   TEST_TRUE( (  refCount1 == (refCount + LOOP)));

   for( int ii = 0; ii < LOOP; ii++ )
       Object_release( clientEnv );

   refCount1 = ((RemoteObjCxt *)(clientEnv.context))->refs;
   TEST_TRUE( refCount1 == refCount );

   for( int ii = 0; ii < LOOP; ii++ )
   {
      Status = ScmProtocol->ScmGetClientEnv( ScmProtocol, &clientEnvA[ii] );
      TEST_RETURN( Status );
      TEST_TRUE( !Object_isNull(clientEnvA[ii])); 
   }

   refCount1 = ((RemoteObjCxt *)(clientEnv.context))->refs;
   TEST_TRUE( refCount1 == (refCount + LOOP));

   for( int ii = 0; ii < LOOP; ii++ )
       Object_release( clientEnvA[ii] );

   refCount1 = ((RemoteObjCxt *)(clientEnv.context))->refs;
   TEST_TRUE( refCount1  == refCount );
  
   for( int ii = 0; ii < 2*LOOP; ii++ )
       Object_release( clientEnv );

   refCount1 = ((RemoteObjCxt *)(clientEnv.context))->refs;
   TEST_TRUE( refCount1 == 1 );

Exit:

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n MutiClientsTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n MutiClientsTest is successful \n\n");

   return;
}


Object  obj[32];
void ObjectTableTest(void)
{
   EFI_STATUS  Status    = EFI_SUCCESS; 
   int         ret       = Object_OK;
   UINT32      numOfFail = numOfFailedTest; 
   UINT32      i, j;
   UINT32      numOfObj[2];

   Status = ScmProtocol->ScmGetClientEnv(ScmProtocol, &clientEnv);
   TEST_RETURN(Status);
   TEST_TRUE(!Object_isNull(clientEnv));

   C_FOR_ARRAY(i, obj)
   {
      obj[i] = Object_NULL;
   }

   for( j=0; j<2; ++j )
   {
      C_FOR_ARRAY(i, obj)
      {
         ret = IClientEnv_open( clientEnv, CAppLoader_UID, &obj[i] );
         TEST_RETURN ( ret );
         TEST_TRUE( !Object_isNull(obj[i]));
      }

      AsciiPrint("\n  open  i  = %d \n\n", i );
      numOfObj[j] = i;

      C_FOR_ARRAY(i, obj)
      {
         Object_RELEASE_IF( obj[i] );
         obj[i] = Object_NULL;
      }

      AsciiPrint("\n  release  i  = %d \n\n", i );
   }

   TEST_TRUE( numOfObj[0] == numOfObj[1] );

Exit:

    Object_release( clientEnv );

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n ObjectTableTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n ObjectTableTest is successful \n\n");

   return;

}


void PerformanceTest(void)
{
   EFI_STATUS            Status         = EFI_SUCCESS; 
   int                   ret            = Object_OK;
   UINT32                numOfFail      = numOfFailedTest; 
   UINT32                appId          = 0;
   qsee_app_start_req_t  qsee_app_start_req;
   UINT64                tick0;
   UINT64                tick1;
   UINT64                duration;
   UINT32                ii;

   SetMem((VOID *)&qsee_app_start_req, sizeof(qsee_app_start_req_t), 0x0);
   qsee_app_start_req.mdt_len = 0;
   qsee_app_start_req.img_len = (UINT32)ImageSize;
   qsee_app_start_req.pa      = (UINT32)(UINTN)Image;
   CopyMem((void *)qsee_app_start_req.app_name, (void *)TzTestAppName, QSEE_MAX_NAME_SIZE);

   duration  = 0;

   for( ii = 0; ii < LOOP; ii++ )
   {
      tick0 = GetTimerCountus();
      // legacy load
      Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                             APP_START_APP_CMD,
                                            &appId,
                                    (void *)&qsee_app_start_req,
                                             sizeof(qsee_app_start_req_t),
                                             NULL,
                                             0 );
      TEST_RETURN( Status );

      tick1 = GetTimerCountus();
      duration += tick1 - tick0;

AsciiPrint("\n legacy load time = %d \n", tick1 - tick0 );

      // legacy unload
      Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                             APP_SHUTDOWN_CMD, 
                                            &appId,
                                             NULL,
                                             0,
                                             NULL,
                                             0 );
      TEST_RETURN( Status );
   } 

   AsciiPrint("\n Ave legacy load time = %d \n", duration/LOOP );

   duration  = 0;
   for( ii = 0; ii < LOOP; ii++ )
   {
      tick0 = GetTimerCountus();

      // load tz app
      Status = ScmProtocol->ScmGetClientEnv(ScmProtocol, &clientEnv);
      TEST_RETURN( Status );
      TEST_TRUE( !Object_isNull(clientEnv)); 
                                                                                         
      ret = IClientEnv_open(clientEnv, CAppLoader_UID, &appLoader);
      TEST_RETURN( ret );
      TEST_TRUE(!Object_isNull(appLoader));
                                                                                         
      ret = IAppLoader_loadFromBuffer(appLoader, Image, ImageSize, &appController);
      TEST_RETURN( ret );
      TEST_TRUE(!Object_isNull(appController));

      tick1 = GetTimerCountus();
      duration += tick1 - tick0;   

AsciiPrint("\n load time = %d \n", tick1 - tick0 );

      // unload tz app
      ret = IAppController_unload(appController);
      TEST_RETURN( ret );

      Object_release( appController );
      Object_release( appLoader );
      Object_release( clientEnv );
      appController = Object_NULL;
      appLoader     = Object_NULL;
      clientEnv     = Object_NULL;

   }

   AsciiPrint("\n Ave smc load time = %d \n", duration/LOOP );

Exit:

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n PerformanceTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n PerformanceTest is successful \n\n");

   return;
}


void StressTest(void)
{
   EFI_STATUS   Status     = EFI_SUCCESS; 
   int          ret        = Object_OK;
   UINT32       numOfFail  = numOfFailedTest; 

   Object       appObj          = Object_NULL;
   Object       objTestCallback = Object_NULL;

   Status = Start();
   TEST_RETURN( Status );
 
   // load/unload LOOP times
   for( int i = 0; i < LOOP; i++)
   {
      ret = IAppController_getAppObject(appController, &appObj);
      TEST_RETURN( ret );
      TEST_TRUE( !Object_isNull(appObj) );

      // get objTestCallback from this TA
      Object_RELEASE_IF(objTestCallback);
      ret = IClientEnv_open(appObj, CTzEcoTestApp_TestCBack_UID, &objTestCallback);
      TEST_RETURN( ret );
      TEST_TRUE( !Object_isNull(objTestCallback) );

      // release this object 
      Object_release(objTestCallback);
      TEST_TRUE( ((RemoteObjCxt *)(objTestCallback.context))->magicNum == 0 );
      objTestCallback = Object_NULL;

      // unload tz app
      ret = IAppController_unload(appController);
      TEST_RETURN( ret );

      // try to get this object again from this unloaded TA, should fail
      ret = IClientEnv_open(appObj, CTzEcoTestApp_TestCBack_UID, &objTestCallback);
      TEST_TRUE( ret != 0 );
      objTestCallback = Object_NULL;

      Object_release(appObj);
      TEST_TRUE( ((RemoteObjCxt *)(appObj.context))->magicNum == 0  );
      appObj = Object_NULL;
      Object_release(appController);
      TEST_TRUE( ((RemoteObjCxt *)(appController.context))->magicNum == 0  );
      appController = Object_NULL;

      // load tz app again
      TEST_TRUE(!Object_isNull(appLoader)); 
      ret = IAppLoader_loadFromBuffer(appLoader, Image, ImageSize, &appController);
      TEST_RETURN( ret );
      TEST_TRUE(!Object_isNull(appController)); 

   }

Exit:

   End( );

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n StressTest failed test cases = %d\n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n StressTest is successful \n\n");

   return;
}


EFI_STATUS LegacyListenerCb(void *Handle, void *Buffer, UINT32 BufferLen)
{
   LegacyCbCounter = 22;

   return EFI_SUCCESS;
}


void CallbackTest(void)
{
   EFI_STATUS   Status          = EFI_SUCCESS; 
   int          ret             = Object_OK;

   Object       appObj          = Object_NULL; 
   Object       objCb_0         = Object_NULL ;
   Object       objCb_1         = Object_NULL;
   Object       objTestCallback = Object_NULL;

   TestCallable *objCbCtx       = NULL;
   UINT8         testArray[]    = {0,1,2,3,4,5,6,7};
   UINT8        *bigArray       = NULL;

   UINT32       numOfFail  = numOfFailedTest; 

   BufCb = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &BufCbSize, ShmBridgeBootSvcData);
   TEST_TRUE(BufCb != NULL );

   Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                              LEGACY_LISTENER_ID,
                                              LegacyListenerCb,
                                              NULL,
                                              BufCb,
                                              BufCbSize);
   TEST_RETURN(Status);

   Status = Start( );
   TEST_RETURN( Status );

   ret = IAppController_getAppObject(appController, &appObj);
   TEST_RETURN( ret );
   TEST_TRUE( !Object_isNull(appObj));

   // get objTestCallback from remote which is for test callback
   ret = IClientEnv_open(appObj, CTzEcoTestApp_TestCBack_UID, &objTestCallback);
   TEST_RETURN( ret );
   TEST_TRUE(!Object_isNull(objTestCallback));

   /* Get a local callable object which will be invoked locally from remote( callback object!) */
   ret = CTestCallable_open(&objCb_0);
   TEST_RETURN( ret );
   TEST_TRUE(!Object_isNull(objCb_0));

   objCbCtx = (TestCallable*)objCb_0.context;

   /* Set the expected return and check preconditions */
   TEST_TRUE(objCbCtx->op == -1);
   TEST_TRUE(objCbCtx->counter == 0);
   TEST_TRUE(objCbCtx->refs == 1);
   objCbCtx->retValue = Object_OK;

   LegacyCbCounter = 0;
   ret = ITestCBack_call(objTestCallback, objCb_0);

   /* Check it happened as expected */
   TEST_TRUE(ret == objCbCtx->retValue);
   TEST_TRUE(objCbCtx->counter == 64);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_call);
   TEST_TRUE(objCbCtx->refs == 1);
   TEST_TRUE(LegacyCbCounter == 22);

   /* Repeat with BI */
   objCbCtx->counter = 0;
   objCbCtx->retValueError = 0xFAFAFAFA; /* Some unique error code which doesn't overlap with those in Mink */
   objCbCtx->bArg_ptr = testArray;
   objCbCtx->bArg_len = sizeof(testArray);

   ret = ITestCBack_callWithBuffer(objTestCallback, testArray, sizeof(testArray), objCb_0);

   TEST_TRUE(ret == objCbCtx->retValue);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_callWithBuffer);
   TEST_TRUE(objCbCtx->refs == 1);

   /* And with a buffer that doesn't match. */
   objCbCtx->counter = 0;

   ret = ITestCBack_callWithBuffer(objTestCallback, testArray, sizeof(testArray)-1, objCb_0);

   TEST_TRUE(ret == objCbCtx->retValueError);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_callWithBuffer);
   TEST_TRUE(objCbCtx->refs == 1);

   /* test register API */
   BufCbSize = 0x80000 + 1;
   Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                              0,
                                              NULL,
                                              NULL,
                                              NULL,
                                              BufCbSize);
   TEST_RETURN(!Status);

   BufCbSize = 0x80000;
   Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                              0,
                                              NULL,
                                              NULL,
                                              NULL,
                                              BufCbSize);
   TEST_RETURN(Status);

   BufCbSize = 0x60000;
   Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                              0,
                                              NULL,
                                              NULL,
                                              NULL,
                                              BufCbSize);
   TEST_RETURN(Status);

   bigArray = (UINT8 *)AllocateZeroPool( BufCbSize );
   TEST_TRUE( bigArray != NULL );

   CopyMem( bigArray, testArray, sizeof(testArray) );
    
   /* And with a big buffer. */
   objCbCtx->counter = 0;

   ret = ITestCBack_callWithBuffer(objTestCallback, bigArray, BufCbSize, objCb_0);
   TEST_TRUE(ret == objCbCtx->retValueError);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_callWithBuffer);
   TEST_TRUE(objCbCtx->refs == 1);

   /* With another callable object as argument */
   ret = CTestCallable_open(&objCb_1);
   objCbCtx->counter = 0;
   Object_ASSIGN(objCbCtx->oArg, objCb_1);
   ret = ITestCBack_callWithObject(objTestCallback, objCb_1, objCb_0);

   TEST_TRUE(ret == objCbCtx->retValue);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_callWithObject);
   TEST_TRUE(objCbCtx->refs == 1);

#if 0

   /* Now with a remote object as argument */
   objCbCtx->counter = 0;
   objCbCtx->op = -1;
   ret = ITestCBack_callWithObject(objTestCallback, objTestCallback, objCb_0);

   TEST_TRUE(ret == objCbCtx->retValueError);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_callWithObject);
   TEST_TRUE(objCbCtx->refs == 1);

   Object_release(objCb_1);

   /* Now test the callback object being retained by a secure object */
   objCbCtx->counter = 0;
   objCbCtx->op = -1;
   ret = ITestCBack_set(objTestCallback, objCb_0);

   TEST_RETURN( ret );
   TEST_TRUE(objCbCtx->refs == 2);
   TEST_TRUE(objCbCtx->counter == 0);
   TEST_TRUE(objCbCtx->op == -1);

   /* Now call it */
   ret = ITestCBack_callSet(objTestCallback);

   /* Check it happened as expected */
   TEST_TRUE(ret == objCbCtx->retValue);
   TEST_TRUE(objCbCtx->counter == 1);
   TEST_TRUE(objCbCtx->op == ITestCallable_OP_call);
   TEST_TRUE(objCbCtx->refs == 2);

   /* Release it */
   objCbCtx->counter = 0;
   objCbCtx->op = -1;
   ret = ITestCBack_set(objTestCallback, Object_NULL);

   TEST_RETURN( ret );;
   TEST_TRUE(objCbCtx->refs == 1);
   TEST_TRUE(objCbCtx->counter == 0);
   TEST_TRUE(objCbCtx->op == -1);

#endif

   Object_release(objTestCallback);
   Object_release(objCb_0);
   Object_release(appObj);

Exit:

   End( );

   Status = ScmProtocol->ScmDeRegisterCallback( ScmProtocol, LEGACY_LISTENER_ID );
   if( Status )
      AsciiPrint("\n ScmDeRegisterCallback failed \n");

   if( bigArray )
      FreePool( bigArray );

   Status = ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, BufCb);
   if( Status )
      AsciiPrint("\n ShmBridgeFree failed \n");

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n CallbackTest failed test cases = %d\n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n CallbackTest is successful \n\n");

   return;

}


void ConnectDisconnectTest(void)
{
   EFI_STATUS   Status             = EFI_SUCCESS; 
   int          ret                = Object_OK;
   Object       appObj             = Object_NULL;
   UINT32       numOfFail          = numOfFailedTest; 

   Status = Start( );
   TEST_RETURN( Status );

   ret = IAppController_getAppObject(appController, &appObj);
   TEST_RETURN( ret );
   TEST_TRUE( !Object_isNull(appObj) );

   for( int ii = 0; ii < LOOP; ii++ )
   {
      // disconnect the TA 
      ret = IAppController_disconnect(appController);
      TEST_RETURN( ret );

      Object_release(appObj);
      Object_release(appController);
      Object_release( appLoader );
      appObj = Object_NULL;
      appController = Object_NULL;
      appLoader = Object_NULL;

      Status = ScmProtocol->ScmGetClientEnv( ScmProtocol, &clientEnvA[ii] );
      TEST_RETURN( Status );
      TEST_TRUE( !Object_isNull(clientEnvA[ii])); 
                                                                                     
      ret = IClientEnv_open(clientEnvA[ii], CAppLoader_UID, &appLoader);
      TEST_RETURN( ret );
      TEST_TRUE(!Object_isNull(appLoader));

      // connect this TA again
      ret = IAppLoader_connect(appLoader, TzTestAppName, sizeof(TzTestAppName), &appController); 
      TEST_RETURN( ret );
      TEST_TRUE( !Object_isNull(appController)); 

      ret = IAppController_getAppObject(appController, &appObj);
      TEST_RETURN( ret );
      TEST_TRUE( !Object_isNull(appObj) );

   }
   
   TEST_TRUE( ((RemoteObjCxt *)(clientEnvA[LOOP-1].context))->refs > LOOP);
  
   // unload tz app
   ret = IAppController_unload(appController);
   TEST_RETURN( ret );

Exit:

   Object_release(appObj);

   for( int ii = 0; ii < LOOP; ii++ )
       Object_release( clientEnvA[ii] );

   End( );

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n ConnectDisconnectTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n ConnectDisconnectTest is successful \n\n");

   return;
}


/**
 * Test parameters passing
 * */
typedef struct {
  void * ptr;
  size_t len;
} TestParams_bi;

typedef struct {
  void * ptr;
  size_t len;
  size_t lenout;
} TestParams_bo;

#define TEST_PARAMS_IN_SZ   16
#define TEST_PARAMS_OUT_SZ  32

Object oi[15];
Object oo[15];

TestParams_bi bi[15];
TestParams_bo bo[15];

void SmcInvokeParamTest(void)
{
   EFI_STATUS  Status;
   INT32       ret;
   Object      appObj        = Object_NULL; 
   Object      objTestParams = Object_NULL;
   UINT32      numOfFail     = numOfFailedTest; 
   size_t      i;

   SetMem(oi, sizeof(oi), 0);
   SetMem(oo, sizeof(oo), 0);
   SetMem(bi, sizeof(bi), 0);
   SetMem(bo, sizeof(bo), 0);

   Status = Start();
   TEST_RETURN( Status );

   ret = IAppController_getAppObject(appController, &appObj);
   TEST_RETURN( ret );
   TEST_TRUE( !Object_isNull(appObj));

   // allocate our buffers and put something in them
   C_FOR_ARRAY(i, bi)
   {
      UINT8 *up = NULL;
      bi[i].ptr = AllocateZeroPool(TEST_PARAMS_IN_SZ);
      TEST_TRUE(bi[i].ptr != NULL);
      bi[i].len = TEST_PARAMS_IN_SZ;
      up = (UINT8*)bi[i].ptr;
      for (size_t j = 0; j < bi[i].len; j++)
         up[j] = j;
   }

   C_FOR_ARRAY(i, bo)
   {
      bo[i].ptr = AllocateZeroPool(TEST_PARAMS_OUT_SZ);
      TEST_TRUE(bo[i].ptr != NULL);
      bo[i].len = TEST_PARAMS_OUT_SZ;
      bo[i].lenout = 0;
   }

   // get our objects input
   C_FOR_ARRAY(i, oi)
   {
      UINT8 v[]={'o','i',i};
      ret = IClientEnv_open(appObj, CTzEcoTestApp_TestParams_UID, &oi[i]);
      TEST_RETURN( ret );
      TEST_TRUE(!Object_isNull(oi[i]));
      // set their index in them, so we can recognize them
      ret = TestParams_set(oi[i], i, v, sizeof(v), Object_NULL);
      TEST_RETURN( ret );
   }

   // get an object to perform the call on
   ret = IClientEnv_open(appObj, CTzEcoTestApp_TestParams_UID , &objTestParams);
   TEST_RETURN( ret );
   TEST_TRUE(!Object_isNull(objTestParams));

   // make the call
   ret = TestParams_ioAllTA(objTestParams,
                          bi[0].ptr, bi[0].len,
                          bi[1].ptr, bi[1].len,
                          bi[2].ptr, bi[2].len,
                          bi[3].ptr, bi[3].len,
                          oi[0],
                          oi[1],
                          oi[2],
                          oi[3],
                          bo[0].ptr, bo[0].len, &bo[0].lenout,
                          bo[1].ptr, bo[1].len, &bo[1].lenout,
                          bo[2].ptr, bo[2].len, &bo[2].lenout,
                          bo[3].ptr, bo[3].len, &bo[3].lenout,
                          &oo[0],
                          &oo[1],
                          &oo[2],
                          &oo[3]
                         );
   TEST_RETURN( ret );

   // test that the OO were actually set to reference the passed OI
   for( i = 0; i< 4; ++i )
   {
      UINT8 v[]={'o','i',i};
      UINT8 b[16] = {0};
      size_t len = 0;
      Object oTmp = Object_NULL;
      UINT32 u32 = 0;
      ret = TestParams_get(oo[i], &u32, b, sizeof(b), &len, &oTmp);
      TEST_RETURN( ret );  

      Object_RELEASE_IF(oTmp);
      TEST_TRUE(u32 == i);
      TEST_TRUE(sizeof(v) == len);
      TEST_TRUE(0 == memcmp(b, v, len));
   }

   for( i = 0; i< 4; ++i )
   {
      TEST_TRUE(bo[i].lenout == TEST_PARAMS_IN_SZ);
      UINT8* up = (UINT8*)bo[i].ptr;
      for (size_t j = 0; j < bo[i].lenout; j++)
         TEST_TRUE(up[j] == j);
   }

/*
   // make the call
   ret = TestParams_ioAll(objTestParams,
                          bi[0].ptr, bi[0].len,
                          bi[1].ptr, bi[1].len,
                          bi[2].ptr, bi[2].len,
                          bi[3].ptr, bi[3].len,
                          bi[4].ptr, bi[4].len,
                          bi[5].ptr, bi[5].len,
                          bi[6].ptr, bi[6].len,
                          bi[7].ptr, bi[7].len,
                          bi[8].ptr, bi[8].len,
                          bi[9].ptr, bi[9].len,
                          bi[10].ptr, bi[10].len,
                          bi[11].ptr, bi[11].len,
                          bi[12].ptr, bi[12].len,
                          bi[13].ptr, bi[13].len,
                          bi[14].ptr, bi[14].len,
                          oi[0],
                          oi[1],
                          oi[2],
                          oi[3],
                          oi[4],
                          oi[5],
                          oi[6],
                          oi[7],
                          oi[8],
                          oi[9],
                          oi[10],
                          oi[11],
                          oi[12],
                          oi[13],
                          oi[14],
                          bo[0].ptr, bo[0].len, &bo[0].lenout,
                          bo[1].ptr, bo[1].len, &bo[1].lenout,
                          bo[2].ptr, bo[2].len, &bo[2].lenout,
                          bo[3].ptr, bo[3].len, &bo[3].lenout,
                          bo[4].ptr, bo[4].len, &bo[4].lenout,
                          bo[5].ptr, bo[5].len, &bo[5].lenout,
                          bo[6].ptr, bo[6].len, &bo[6].lenout,
                          bo[7].ptr, bo[7].len, &bo[7].lenout,
                          bo[8].ptr, bo[8].len, &bo[8].lenout,
                          bo[9].ptr, bo[9].len, &bo[9].lenout,
                          bo[10].ptr, bo[10].len, &bo[10].lenout,
                          bo[11].ptr, bo[11].len, &bo[11].lenout,
                          bo[12].ptr, bo[12].len, &bo[12].lenout,
                          bo[13].ptr, bo[13].len, &bo[13].lenout,
                          bo[14].ptr, bo[14].len, &bo[14].lenout,
                          &oo[0],
                          &oo[1],
                          &oo[2],
                          &oo[3],
                          &oo[4],
                          &oo[5],
                          &oo[6],
                          &oo[7],
                          &oo[8],
                          &oo[9],
                          &oo[10],
                          &oo[11],
                          &oo[12],
                          &oo[13],
                          &oo[14]
                         );
   TEST_TRUE( ret == Object_ERROR_MAXDATA );
*/

Exit:

   // cleanup
   C_FOR_ARRAY(i, bi)
      if (bi[i].ptr)
         FreePool(bi[i].ptr);

   C_FOR_ARRAY(i, bo)
      if (bo[i].ptr)
         FreePool(bo[i].ptr);

   C_FOR_ARRAY(i, oi)
      Object_RELEASE_IF(oi[i]);

   C_FOR_ARRAY(i, oo)
      Object_RELEASE_IF(oo[i]);

   Object_release(objTestParams);
   Object_release(appObj);

   End();

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n SmcInvokeParamTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n SmcInvokeParamTest is successful \n\n");

   return;
}


void LoadTaTest(void)
{
   EFI_STATUS            Status         = EFI_SUCCESS; 
   UINT32                numOfFail      = numOfFailedTest; 
   UINT32                appId          = 0;
   UINT32                appId_0        = 0;
   UINT32                appId_1        = 0;
   UINT32                req            = 0;
   UINT32                rsp[2];
   qsee_app_start_req_t  qsee_app_start_req;

   BufCb = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &BufCbSize, ShmBridgeBootSvcData);
   TEST_TRUE(BufCb != NULL );

   Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                              LEGACY_LISTENER_ID,
                                              LegacyListenerCb,
                                              NULL,
                                              BufCb,
                                              BufCbSize);
   TEST_RETURN(Status);

   SetMem((VOID *)&qsee_app_start_req, sizeof(qsee_app_start_req_t), 0x0);
   qsee_app_start_req.mdt_len = 0;
   qsee_app_start_req.img_len = (UINT32)ImageSize;
   qsee_app_start_req.pa      = (UINT32)(UINTN)Image;
   CopyMem((void *)qsee_app_start_req.app_name, (void *)TzTestAppName, QSEE_MAX_NAME_SIZE);

   Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                         APP_START_APP_CMD,
                                        &appId,
                                (void *)&qsee_app_start_req,
                                         sizeof(qsee_app_start_req_t),
                                         NULL,
                                         0 );
   TEST_RETURN( Status );
   TEST_TRUE( (appId & 0xFFFF0000) == 0xFFFF0000 );

   Status = ScmProtocol->ScmSendCommand( ScmProtocol, 
                                         APP_START_APP_CMD,
                                        &appId_0,
                                (void *)&qsee_app_start_req,
                                         sizeof(qsee_app_start_req_t),
                                         NULL,
                                         0 );
   TEST_TRUE( Status != 0 );

   Status = ScmProtocol->ScmSendCommand( ScmProtocol, 
                                         APP_QUERY_APPID_CMD, 
                                        &appId_1,
                                         TzTestAppName, 
                                         sizeof(TzTestAppName),
                                         NULL,
                                         0 );   
   TEST_RETURN( Status );
   TEST_TRUE( (appId & 0xFFFF0000) == 0xFFFF0000 );
   TEST_TRUE( appId  == appId_1 );

   req = 1;
   Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                         APP_SEND_DATA_CMD,
                                        &appId,
                                        &req,
                                         sizeof(req),
                                        &rsp,
                                         sizeof(rsp) );
   TEST_RETURN( Status );
   TEST_TRUE( rsp[0] == 0 );
   TEST_TRUE( rsp[1] == 1 );

   LegacyCbCounter = 0;
   req = 2;
   Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                         APP_SEND_DATA_CMD,
                                        &appId,
                                        &req,
                                         sizeof(req),
                                        &rsp,
                                         sizeof(rsp) );
   TEST_RETURN(Status);
   TEST_TRUE( rsp[0] == 0 );
   TEST_TRUE( rsp[1] == 2 );
   TEST_TRUE( LegacyCbCounter == 22 );

   Status = ScmProtocol->ScmSendCommand( ScmProtocol,
                                         APP_SHUTDOWN_CMD, 
                                        &appId,
                                         NULL,
                                         0,
                                         NULL,
                                         0 );
   TEST_RETURN( Status );

Exit:

   Status = ScmProtocol->ScmDeRegisterCallback( ScmProtocol, LEGACY_LISTENER_ID);
   if( Status )
      AsciiPrint("\n ScmDeRegisterCallback failed \n");

   Status = ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, BufCb);
   if( Status )
      AsciiPrint("\n ShmBridgeFree failed \n");

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n LoadTaTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n LoadTaTest is successful \n\n");

   return;

}


void DisConnectTaTest(void)
{
   EFI_STATUS  Status;
   UINT32      numOfFail = numOfFailedTest; 

   Status = ScmProtocol->ScmExitBootServicesHandler( ScmProtocol);
   TEST_RETURN(Status);

Exit:

   if((numOfFailedTest - numOfFail) > 0 )
      AsciiPrint("\n DisConnectTaTest failed test cases = %d \n\n", (numOfFailedTest - numOfFail));
   else
      AsciiPrint("\n DisConnectTaTest is successful \n\n");

   return;

}


EFI_STATUS
EFIAPI
UefiMain (
   IN EFI_HANDLE        ImageHandle,
   IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
   EFI_STATUS  Status = EFI_LOAD_ERROR;
   UINTN       Argc;
   CHAR8     **Argv = NULL;
   UINT32      TestCase = 0;

Loop:

  Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);
  if (EFI_ERROR (Status))
  {
     AsciiPrint ("Failed to parse commmand line\n");
     goto Exit;
  }

  switch(Argc)
  {
     case 0:
     default:
        // all test cases.
        break;

     case 1:
        TestCase = AsciiStrDecimalToUintn(Argv[0]);;
        break;
  } 

  if( TestCase > 2 )
     goto Loop;

   Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&ScmProtocol);
   TEST_RETURN(Status);

   Status = gBS->LocateProtocol(&gEfiShmBridgeProtocolGuid, NULL, (VOID **)&ShmBridgeProtocol);
   TEST_RETURN(Status);

   ScmProtocol->ScmSendCommand( ScmProtocol,
                                APP_QUERY_EMBEDDED_IMAGES_SUPPORT_CMD,
                                NULL,
                                NULL,
                                0,
                                NULL,
                                0);

   TEST_START("SmcInvokeTest");
   Status = ReadImage();
   TEST_RETURN( Status );

   if( TestCase == 0 || TestCase == 1 )
   {
      TEST_START("SmcInvokeTest");
      AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   MutiClientsTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   ObjectTableTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   PerformanceTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   ConnectDisconnectTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   StressTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   CallbackTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   SmcInvokeParamTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   AsciiPrint(" \n ");
   }

   if( TestCase == 0 || TestCase == 2 )
   {
   TEST_START("SmcInvokeCompatibilityTest");
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
      LoadTaTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
      DisConnectTaTest();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   }

   FreeImage(); 

   if( numOfFailedTest == 0 )
       AsciiPrint("\n SmcInvokeTest is successful ! \n");
   else
      AsciiPrint("\n SmcInvokeTest has %d failed test cases !!! \n\n", numOfFailedTest);

   TEST_STOP("SmcInvokeTest");

Exit:

   return Status;
}
