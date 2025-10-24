/** @file TzeLoaderTest.c
   
  Tests for using TzeLoader and Scm interface

  Copyright (c) 2017 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  
  Portions Copyright (c) 2006 - 2008, Intel Corporation
  All rights reserved. This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution. The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/09/19   shl     Replaced Qseecomm protocol with Scm and TzeLoader protocols
 05/12/16   rj      Initial revision

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Library/QcomLib.h>
#include <Protocol/EFITzeLoader.h>
#include <Protocol/EFIScm.h>
#include <Include/scm_qsee_interface.h>

#define TEST_APP   "keymaster"


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status=EFI_LOAD_ERROR;
  QCOM_SCM_PROTOCOL *ScmProtocol = NULL;
  EFI_TZE_LOADER_PROTOCOL *TzeLoaderProtocol = NULL;
  UINT32 AppId=0;
  UINTN  Argc;
  CHAR8  **Argv = NULL;
  CHAR8 app[QSEE_MAX_NAME_SIZE];
  CHAR16 app16[QSEE_MAX_NAME_SIZE];
  UINT32  cmd_id = 0;
  UINT64 data = 0;

  struct qsee_send_cmd_req {
    UINT32  cmd_id;
    UINT64 data;
    UINT64 data2;
    UINT32 len;
    UINT32 start_pkt;
    UINT32 end_pkt;
    UINT32 test_buf_size;
  }cmd_req;

  struct qsee_send_cmd_rsp {
    UINT32 data;
    INT32 status;
  }cmd_rsp;

  //Act on cmd line arguments if fails continue for charge
  Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);
  if (EFI_ERROR (Status)) {
    AsciiPrint ("Failed to parse commmand line\n");
    goto Exit;
  }

  switch(Argc)
  {
    case 0:
    default:
      // Use default application and commands/data.
      AsciiStrCpyS(app, QSEE_MAX_NAME_SIZE,TEST_APP);
      AsciiStrToUnicodeStrS(TEST_APP, app16, QSEE_MAX_NAME_SIZE);
      cmd_id = 0x200;  //get version command for keymaster 
      break;

    case 1:
      // use commandline arguments (tailered to sample app)
      AsciiStrCpyS(app, QSEE_MAX_NAME_SIZE, Argv[0]);
      AsciiStrToUnicodeStrS(Argv[0], app16, QSEE_MAX_NAME_SIZE);
      break;

    case 2:
      // use commandline arguments (tailered to sample app)
      AsciiStrCpyS(app, QSEE_MAX_NAME_SIZE, Argv[0]);
      AsciiStrToUnicodeStrS(Argv[0], app16, QSEE_MAX_NAME_SIZE);
      cmd_id = AsciiStrDecimalToUintn(Argv[1]);
      break;

    case 3:
     // use commandline arguments (tailered to sample app)
     AsciiStrCpyS(app, QSEE_MAX_NAME_SIZE, Argv[0]);
     AsciiStrToUnicodeStrS(Argv[0], app16, QSEE_MAX_NAME_SIZE);
     cmd_id = AsciiStrDecimalToUintn(Argv[1]);
     data = AsciiStrDecimalToUintn(Argv[2]);
     break;
  }
 
  TEST_START("TzeLoaderTest");

  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&ScmProtocol);
  if (Status != EFI_SUCCESS)
  {
      AsciiPrint("Failed to Locate Scm Protocol status=%d\n", Status);
      goto Exit;
  }

  Status = gBS->LocateProtocol (&gEfiTzeLoaderProtocolGuid, NULL, (VOID**)&TzeLoaderProtocol);
  if (Status != EFI_SUCCESS)
  {
      AsciiPrint("Failed to Locate TzeLoader Protocol status=%d\n", Status);
      goto Exit;
  }

  //AsciiPrint("app=%a, cmd_id=%d, data=%d\n", app, cmd_id, data);
  Status = TzeLoaderProtocol->LoadImageFromPartition(TzeLoaderProtocol, NULL, app16, &AppId);
  if (Status != EFI_SUCCESS)
  {
    AsciiPrint("Failed LoadImageFromPartition(%d)  status=%d, AppId=%d\n", app, Status, AppId);
    goto Exit;
  }
  AsciiPrint("LoadImageFromPartition (%d) call success status=%d, AppId=%d\n", app, Status, AppId);

  // load one more time to test the app id buffer code
  Status = TzeLoaderProtocol->LoadImageFromPartition(TzeLoaderProtocol, NULL, app16, &AppId);
  if (Status != EFI_SUCCESS)
  {
   AsciiPrint("One more loading Failed: LoadImageFromPartition(%d)  status=%d, AppId=%d\n", app, Status, AppId);
   goto Exit;
  }
  AsciiPrint(" one more loading: LoadImageFromPartition (%d) call success status=%d, AppId=%d\n", app, Status, AppId);

  cmd_req.cmd_id = cmd_id;
  cmd_req.data = data;
  cmd_req.start_pkt = 0;
  cmd_req.end_pkt = 0;
  cmd_req.test_buf_size = 0;
 
  Status = ScmProtocol->ScmSendCommand(ScmProtocol, APP_SEND_DATA_CMD, &AppId, (UINT8 *)&cmd_req, sizeof(cmd_req), (UINT8 *)&cmd_rsp, sizeof(cmd_rsp));
  if (Status != EFI_SUCCESS)
  {
    AsciiPrint("Failed ScmSendCommand (%a) status=%d\n", app, Status);
    goto Exit;
  }
  AsciiPrint("ScmSendCommand (%a) call success status=%d, AppId=%d resp.status=%d, resp.data=%d\n", app, Status, AppId, cmd_rsp.status, cmd_rsp.data);
  
  Status = ScmProtocol->ScmSendCommand(ScmProtocol, APP_SHUTDOWN_CMD, &AppId, NULL, 0, NULL, 0);
  if (Status != EFI_SUCCESS)
  {
    AsciiPrint("Failed ShutdownApp (%a) status=%d\n", app, Status);
    goto Exit;
  }
  AsciiPrint("ShutdownApp (%a) call success status=%d, AppId=%d\n", app, Status, AppId);

Exit:
  TestStatus("TzeLoaderTest", Status);
  TEST_STOP("TzeLoaderTest");

  AsciiPrint("TzeLoaderTest completed. Press any key to exit and reset the device\n");
  ReadAnyKey (NULL, 0);
  //gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
  return Status;
}
