/** @file MhiTest.c
#
#  Mhi Test Application.
#
#  Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 05/21/2020   nr      Initial Revision
#==============================================================================
#**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/GuidedFvLib.h>
#include <Library/KernelLib.h>

#include <Library/npa.h>
#include <Library/pmapp_npa.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicTest.h>
#include <Protocol/EFIChipInfo.h>

#include "pcie_host_r.h"
#include <Protocol/EfiQcPcie.h>

#include "mhi.h"
#include <Protocol/EfiQcMhi.h>

volatile UINT32 stopfordebug = 0;
UINT8  DebugLevel = 0;
UINT64 TestBuffSize = 1 * 1024 * 1024;
UINT32 *ResultReturnAddr = NULL;

typedef struct {
   pcie_dev_t *ep_handle;
   pcie_dev_t *rc_handle;
   pcie_dev_probe_cb_payload_t ep_info;
   uint32 RcIdx;
}dev_handle_info_type;

mhi_dev_info_t mhi_test_dev_info;

mhi_handle_t mhi_dev_handle = NULL;

boolean mhi_cb_invoked = FALSE;

void MhiTestCb(mhi_cb_payload_t *payload)
{
   Event *testCbEvt = NULL;

   AsciiPrint("MHI test callback invoked\n");

   if(!payload)
   {
      AsciiPrint("WARNING: MHI callback payload is NULL");
      return;
   }

   testCbEvt = (Event*)(payload->user_data);
   
   gBS->CopyMem(&mhi_test_dev_info, 
                &(payload->dev_info), 
                sizeof(mhi_test_dev_info));

   AsciiPrint("MHI Device ID - 0x%x, Instance ID - 0x%x\n", 
              mhi_test_dev_info.dev_id,
              mhi_test_dev_info.instance_id);

   if(testCbEvt)
   {
      EventSignal(testCbEvt, FALSE);
   }

   /* ToDo : Remove this once events start working */
   //mhi_cb_invoked = TRUE;
}

void probe_cb_fn (pcie_dev_t *pdev, const pcie_dev_probe_cb_payload_t *cb_data, void* user_data)
{
   int i;
   pcie_dev_t *ep_handle, *rc_handle;
   dev_handle_info_type* handle_info = (dev_handle_info_type*)user_data;

   if ((handle_info == NULL) || (cb_data == NULL) ||
       (handle_info->RcIdx != (cb_data->dev_ids.rbdf_info >> 16)))
      return;

   AsciiPrint ("Device EP detected on core %d : Vend ID %X, Dev ID %X\r\n", handle_info->RcIdx, cb_data->dev_ids.vendor_id, cb_data->dev_ids.device_id);

   for (i=0; i<PCIE_MAX_BARS; ++i)
      if (cb_data->rsrc.bars[i].pa)
         AsciiPrint ("BAR %d : 0x%X  0x%X\r\n", i, cb_data->rsrc.bars[i].pa, cb_data->rsrc.bars[i].sz);

   ep_handle = pdev;

   rc_handle = ep_handle;

   while (rc_handle)
   {
      pcie_dev_t *ptr = pcie_get_parent (rc_handle);
      if (ptr == NULL)
         break;
      rc_handle = ptr;
   }

   if (rc_handle == ep_handle)
      AsciiPrint ("Parent handle failure\n");

   handle_info->ep_handle = ep_handle;
   handle_info->rc_handle = rc_handle;
   handle_info->ep_info = *cb_data;
}

#define REGISTER_OPERATION     1
#define UNREGISTER_OPERATION   2

void register_handler (dev_handle_info_type* handle_info, int reg_operation)
{
   pcie_device_info_t FilterDeviceID;

   FilterDeviceID.vendor_id = PCIE_ID_ANY;
   FilterDeviceID.device_id = PCIE_ID_ANY;
   FilterDeviceID.class_id = PCIE_ID_ANY;

   if (reg_operation == REGISTER_OPERATION)
     pcie_register_device (&FilterDeviceID, probe_cb_fn, handle_info);
   else
     pcie_unregister_device (&FilterDeviceID, probe_cb_fn, handle_info);
}

static EFI_STATUS TestFramework_CommandResponse(
      EFI_PHYSICAL_ADDRESS cmd_buf,
      uint32 cmd_buf_size,
      EFI_PHYSICAL_ADDRESS response_buf,
      uint32 response_buf_size
   )
{
   EFI_STATUS status = EFI_SUCCESS;
   mhi_status_t mstatus = MHI_SUCCESS;
   uint32 tx_chan_num = 22;
   uint32 rx_chan_num = 23;
   uint32 bytes_written, bytes_read, i = 0;
   boolean eot_occurred = FALSE;
   char tf_response_end_marker[] = "TEST CORE END";

   char *response_buf_ptr = (char*)response_buf;

   mstatus = mhi_channel_write(mhi_dev_handle, 
                               tx_chan_num, 
                               (void*)cmd_buf, 
                               cmd_buf_size,
                               &bytes_written, 
                               NULL);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI channel write failed - errorcode %u\n", status);
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }

   gBS->Stall(100 * 1000);


   AsciiPrint("Response from device \n\n");
   do{
      mstatus = mhi_channel_read(mhi_dev_handle, 
                                 rx_chan_num, 
                                 (void*)response_buf, 
                                 response_buf_size,
                                 &bytes_read, 
                                 &eot_occurred, 
                                 NULL);
      if(MHI_SUCCESS != mstatus)
      {
         AsciiPrint("MHI channel read failed - errorcode %u\n", mstatus);
         status = EFI_DEVICE_ERROR;
         goto cleanup;
      }

      response_buf_ptr[bytes_read] = '\0';
      for(i = 0; i < bytes_read; i++)
      {
         AsciiPrint("%c", response_buf_ptr[i]);
      }
      //Print(L"%s", (CHAR16*)response_buf_ptr);
      AsciiPrint("\n");
   }while ( NULL == AsciiStrStr(response_buf_ptr, tf_response_end_marker) );

cleanup:
   return status;
}

EFI_STATUS TestFrameworkDemo (UINT32 EndpointIdx, UINT32 CoreIdx)
{
   EFI_STATUS status = EFI_SUCCESS;

   mhi_status_t mstatus = MHI_SUCCESS;
   mhi_dev_id_t devIdx = (mhi_dev_id_t)EndpointIdx;
   mhi_cb_t cb = {
      NULL,
      MhiTestCb
   };
   Event *testCbEvt = NULL;
   mhi_ee_t current_ee = 0xFF;

   EFI_PHYSICAL_ADDRESS tx_buf = 0xFFFFF000ULL;
   EFI_PHYSICAL_ADDRESS rx_buf = 0xFFFFF000ULL;
   
   uint32 tx_chan_num = 22; /* TF channels are 22 and 23 */
   uint32 rx_chan_num = 23;
   boolean tx_chan_open = FALSE;
   boolean rx_chan_open = FALSE;

   uint32 transfer_size = EFI_PAGE_SIZE;
   char *tx_buf_ptr = NULL, *rx_buf_ptr = NULL;
   uint32 num_pages = transfer_size / EFI_PAGE_SIZE;

   /* 
      Logical flow
      1. Allocate TX and RX buffers
      2. mhi_channel_open() for TF channels 22 and 23
      3. Send the TF command "LIST" over channel 22
      4. Read back TF response over channel 23
   */

   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_pages,
                &tx_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate TX buffer\n");
      goto cleanup;
   }

   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_pages,
                &rx_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate RX buffer\n");
      goto cleanup;
   }

   ZeroMem((void*)rx_buf, EFI_PAGE_SIZE);
   ZeroMem((void*)tx_buf, EFI_PAGE_SIZE);

   testCbEvt = EventInit(0, 0, 1);
   if(!testCbEvt)
   {
      AsciiPrint ("ERROR: Could not create event for signalling\n");
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }

   /* Register with the specified MHI device to obtain a handle */
   cb.user_data = (void*)testCbEvt;
   cb.cb_func = MhiTestCb;
   mhi_register(devIdx, &cb);

   EventWait(testCbEvt);

   /* We should have the device handle now */
   mstatus = mhi_dev_open(&mhi_test_dev_info, &cb, &mhi_dev_handle);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI device open failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI get EE failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   AsciiPrint ("Current Execution Environment of device - %d\n", 
               current_ee);
   
   if(MHI_EE_AMSS != current_ee)
   {
      AsciiPrint("Error : Endpoint is not in AMSS, current EE: %u\n",
                 current_ee);
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }


   AsciiPrint("TX buffer addr : 0x%llx, RX buffer addr : 0x%llx\n\n",
                  tx_buf, rx_buf);
   
   status = mhi_channel_open(mhi_dev_handle, tx_chan_num, NULL);
   if(MHI_SUCCESS != status)
   {
      AsciiPrint("MHI channel open failed - channel 0\n");
      goto cleanup;
   }
   tx_chan_open = TRUE;

   status = mhi_channel_open(mhi_dev_handle, rx_chan_num, NULL);
   if(MHI_SUCCESS != status)
   {
      AsciiPrint("MHI channel open failed - channel 1\n");
      goto cleanup;
   }
   rx_chan_open = TRUE;

   /* Initialize TX buffer to an incrementing pattern
      and RX buffer to all zeros */
   tx_buf_ptr = (char*)tx_buf;
   rx_buf_ptr = (char*)rx_buf;

   /* Step 1: Send initial "LIST" command to get TF top level
      initialization test (platformInitTest) */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE, "LIST", 4);
   AsciiPrint("Sending LIST command to TF component on endpoint\n");
   transfer_size = 5;
   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);


   /* Step 2: Run platformInitTest to initialize the top level
      tests for each functional area  */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE, 
                "RUN(platformInitTest,1,all)", 
                AsciiStrLen("RUN(platformInitTest,1,all)"));
   AsciiPrint("Sending RUN command to TF component on endpoint\n");
   transfer_size = AsciiStrLen("RUN(platformInitTest,1,all)") + 1;

   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);

   /* Step 3: Send "LIST" command again to fetch the list of top level
      tests in each functional area */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE, "LIST", 4);
   AsciiPrint("Sending LIST command to TF component on endpoint\n");
   transfer_size = 5;
   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);
   
   /* Step 4: Run QurtInitTest to fetch QuRT kernel mutex tests  */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE,   
                "RUN(QurtInitTest,1,mutex)", 
                AsciiStrLen("RUN(QurtInitTest,1,mutex)"));
   AsciiPrint("Sending RUN command to TF component on endpoint\n");
   transfer_size = AsciiStrLen("RUN(QurtInitTest,1,mutex)") + 1;

   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);
   
   /* Step 5: Send "LIST" command again to fetch the QuRT mutex tests */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE, "LIST", 4);
   AsciiPrint("Sending LIST command to TF component on endpoint\n");
   transfer_size = 5;
   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);
   
   /* Step 6: Finally, run QurtPiMutexTest */
   AsciiStrnCpyS(tx_buf_ptr, EFI_PAGE_SIZE, 
                "RUN(QurtPimutexTest,2,3,1)", 
                AsciiStrLen("RUN(QurtPimutexTest,2,3,1)"));
   AsciiPrint("Sending RUN command to TF component on endpoint\n");
   transfer_size = AsciiStrLen("RUN(QurtPimutexTest,2,3,1)") + 1;

   TestFramework_CommandResponse(tx_buf,
                                 transfer_size,
                                 rx_buf,
                                 EFI_PAGE_SIZE);


cleanup:
   gBS->FreePages(tx_buf, num_pages);
   gBS->FreePages(rx_buf, num_pages);

   if(tx_chan_open)
   {
      mhi_channel_close(mhi_dev_handle, tx_chan_num);
   }
   if(rx_chan_open)
   {
      mhi_channel_close(mhi_dev_handle, rx_chan_num);
   }
   
   EventUnsignal(testCbEvt);
   mhi_dev_close(mhi_dev_handle, &cb);
   EventWait(testCbEvt);
   EventDestroy(testCbEvt);
   mhi_unregister(devIdx, &cb);

   return status;
}

EFI_STATUS RunMhiLoopbackTest (UINT32 EndpointIdx, UINT32 CoreIdx, UINT32 LoopCnt)
{
   EFI_STATUS status = EFI_SUCCESS;

   mhi_status_t mstatus = MHI_SUCCESS;
   mhi_dev_id_t devIdx = (mhi_dev_id_t)EndpointIdx;
   mhi_cb_t cb = {
      NULL,
      MhiTestCb
   };
   Event *testCbEvt = NULL;
   mhi_ee_t current_ee = 0xFF;

   EFI_PHYSICAL_ADDRESS tx_buf = 0xFFFFF000ULL;
   EFI_PHYSICAL_ADDRESS rx_buf = 0xFFFFF000ULL;
   
   uint32 tx_chan_num = 0; /* Loopback channels are 0 and 1 */
   uint32 rx_chan_num = 1;
   boolean tx_chan_open = FALSE;
   boolean rx_chan_open = FALSE;

   uint32 transfer_size = EFI_PAGE_SIZE;
   uint32 bytes_written = 0, bytes_read = 0, i = 0, j = 0; /* */
   uint8 *tx_buf_ptr = NULL, *rx_buf_ptr = NULL;
   uint32 num_pages = transfer_size / EFI_PAGE_SIZE;
   boolean mismatch = FALSE;
   boolean eot_occurred = FALSE;
   
   uint32 num_iterations = LoopCnt;

   /* 
      Logical flow
      1. Allocate TX and RX buffers
      2. mhi_channel_open() for loopback channels 0 and 1
      3. In a loop, do
         3.1 mhi_channel_write() on channel 0 (LOOPBACK_OUT)
         3.2 mhi_channel_read() on channel 1 (LOOPBACK_IN)
         3.3 Compare TX and RX buffers. If mismatch, fail and bail.
   */

   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_pages,
                &tx_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate TX buffer\n");
      goto cleanup;
   }

   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_pages,
                &rx_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate RX buffer\n");
      goto cleanup;
   }

   testCbEvt = EventInit(0, 0, 1);
   if(!testCbEvt)
   {
      AsciiPrint ("ERROR: Could not create event for signalling\n");
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }

   /* Register with the specified MHI device to obtain a handle */
   cb.user_data = (void*)testCbEvt;
   cb.cb_func = MhiTestCb;
   mhi_register(devIdx, &cb);

   EventWait(testCbEvt);

   /* We should have the device handle now */
   mstatus = mhi_dev_open(&mhi_test_dev_info, &cb, &mhi_dev_handle);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI device open failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI get EE failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   AsciiPrint ("Current Execution Environment of device - %d\n", 
               current_ee);
   
   if(MHI_EE_AMSS != current_ee)
   {
      AsciiPrint("Error : Endpoint is not in AMSS, current EE: %u\n",
                 current_ee);
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }


   AsciiPrint("TX buffer addr : 0x%llx, RX buffer addr : 0x%llx\n\n",
                  tx_buf, rx_buf);
   
   status = mhi_channel_open(mhi_dev_handle, tx_chan_num, NULL);
   if(MHI_SUCCESS != status)
   {
      AsciiPrint("MHI channel open failed - channel 0\n");
      goto cleanup;
   }
   tx_chan_open = TRUE;

   status = mhi_channel_open(mhi_dev_handle, rx_chan_num, NULL);
   if(MHI_SUCCESS != status)
   {
      AsciiPrint("MHI channel open failed - channel 1\n");
      goto cleanup;
   }
   rx_chan_open = TRUE;

   for(i = 1; i <= num_iterations; i++)
   {
      /* Initialize TX buffer to an incrementing pattern
         and RX buffer to all zeros */
      tx_buf_ptr = (uint8*)tx_buf;
      rx_buf_ptr = (uint8*)rx_buf;
      for(j = 0; j < transfer_size; j++)
      {
         tx_buf_ptr[j] = (uint8)(i + j);
         //rx_buf_ptr[j] = 0;
      }
      ZeroMem((void*)rx_buf, EFI_PAGE_SIZE);

      status = mhi_channel_write(mhi_dev_handle, tx_chan_num, (void*)tx_buf, transfer_size,
                                 &bytes_written, NULL);
      if(MHI_SUCCESS != status)
      {
         AsciiPrint("MHI channel write failed - errorcode %u\n", status);
         goto cleanup;
      }

      status = mhi_channel_read(mhi_dev_handle, rx_chan_num, (void*)rx_buf, transfer_size,
                                 &bytes_read, &eot_occurred, NULL);
      if(MHI_SUCCESS != status)
      {
         AsciiPrint("MHI channel read failed - errorcode %u\n", status);
         goto cleanup;
      }

      for(j = 0; j < transfer_size; j++)
      {
         if(tx_buf_ptr[j] != rx_buf_ptr[j])
         {
            AsciiPrint("ERROR : Iteration %u, mismatch at %uth byte\n", 
                       i, j);
            AsciiPrint("ERROR : TX buffer = %u, RX buffer = %u\n",
                       tx_buf_ptr[j], rx_buf_ptr[j]);
            mismatch = TRUE;
            break;
         }
      }
      
      if(mismatch)
      {
         status = EFI_DEVICE_ERROR;
         break;
      }
      else
      {
         AsciiPrint("Iteration %u :  TX and RX buffers MATCH\n", i);
      }
      
      gBS->Stall(10 * 1000);
   }
   
cleanup:
   gBS->FreePages(tx_buf, num_pages);
   gBS->FreePages(rx_buf, num_pages);

   if(tx_chan_open)
   {
      mhi_channel_close(mhi_dev_handle, tx_chan_num);
   }
   if(rx_chan_open)
   {
      mhi_channel_close(mhi_dev_handle, rx_chan_num);
   }
   
   EventUnsignal(testCbEvt);
   mhi_dev_close(mhi_dev_handle, &cb);
   EventWait(testCbEvt);
   EventDestroy(testCbEvt);
   mhi_unregister(devIdx, &cb);

   return status;
}

EFI_STATUS RunBhiTest (UINT32 EndpointIdx, UINT32 CoreIdx, CHAR8 *filepath, CHAR8 *volumename)
{
   pcie_status_t pstatus = PCIE_SUCCESS;
   mhi_status_t mstatus = MHI_SUCCESS;
   mhi_dev_id_t devIdx = (mhi_dev_id_t)EndpointIdx;
   mhi_cb_t cb = {
      NULL,
      MhiTestCb
   };
   //VOID* MapHandle = NULL;
   
   mhi_ee_t current_ee = 0xFF;
   //mhi_state_t current_state = 0x0;

   EFI_STATUS status = EFI_SUCCESS;

   UINT8 *imgbuf = NULL;
   UINTN imgsize = 0;

   EFI_PHYSICAL_ADDRESS sbl_buf = 0xFFFFF000ULL;
   UINTN sbl_size = 0x80000;
   uint32 num_sbl_pages = 0;
   
   EFI_PHYSICAL_ADDRESS mission_img_buf = 0xFFFFF000ULL;
   UINTN mission_img_size = 0;
   uint32 num_mission_img_pages = 0;

   Event *testCbEvt = NULL;

   uint32 counter = 0;

   testCbEvt = EventInit(0, 0, 1);
   if(!testCbEvt)
   {
      AsciiPrint ("WARNING: Could not create event for signalling\n");
   }

   /* Register for a notification when the endpoint comes up */
   cb.user_data = (void*)testCbEvt;
   cb.cb_func = MhiTestCb;
   mhi_register(devIdx, &cb);

   /* Enumerate the MHI device over PCIe on the specified root port */
   pstatus = pcie_enumerate(CoreIdx);
   if (pstatus != PCIE_SUCCESS)
   {
       AsciiPrint ("Link enumeration failed\n");
       return EFI_DEVICE_ERROR;
   }

   AsciiPrint ("Waiting for MHI callback\n");

   //while(!mhi_cb_invoked);

   EventWait(testCbEvt);

   /* We should have the device handle now */
   mstatus = mhi_dev_open(&mhi_test_dev_info, &cb, &mhi_dev_handle);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI device open failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI get EE failed - %d\n", mstatus);
      return EFI_DEVICE_ERROR;
   }

   AsciiPrint ("Current Execution Environment of device - %d\n", 
               current_ee);
   AsciiPrint ("Now executing BHI\n");

   /* Load firmware image to memory */
   status = LoadFileFromGuidedFv(NULL,
                                 filepath,
                                 (UINT8 **)&imgbuf,
                                 &imgsize);
   if(status != EFI_SUCCESS)
   {
      AsciiPrint("LoadlFileFromGuidedFv failed - %u\n", status);
      return EFI_DEVICE_ERROR;
   }

   if(!imgbuf || !imgsize)
   {
      AsciiPrint("Invalid buffer pointer and size : %d and %d\n", imgbuf, imgsize);
      return EFI_DEVICE_ERROR;
   }

   AsciiPrint ("Firmware image %a loaded to memory, address 0x%x\n", 
               filepath,
               imgbuf);
   
   /* If the whole image is smaller than SBL itself */
   if(imgsize < sbl_size)
   {
      sbl_size = imgsize;
   }

   num_sbl_pages = sbl_size / EFI_PAGE_SIZE;
   if(sbl_size % EFI_PAGE_SIZE)
   {
      num_sbl_pages += 1;
   }

   //sbl_buf = (UINT8*)AllocatePages (num_sbl_pages);
   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_sbl_pages,
                &sbl_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate pages for sbl image\n");
      goto cleanup;
   }
   
   gBS->CopyMem((void*)sbl_buf, 
                imgbuf, 
                sbl_size);

   AsciiPrint ("SBL buffer address 0x%llx\n", sbl_buf);

   //mission_img_size = imgsize - sbl_size;
   mission_img_size = imgsize;
   num_mission_img_pages = mission_img_size / EFI_PAGE_SIZE;
   if(mission_img_size % EFI_PAGE_SIZE)
   {
      num_mission_img_pages += 1;
   }

   status = gBS->AllocatePages (
                AllocateMaxAddress,
                EfiLoaderData,
                num_mission_img_pages,
                &mission_img_buf
                );
   if (EFI_ERROR (status)) 
   {
      AsciiPrint("Could not allocate pages for mission-mode img");
      goto cleanup;
   }
   AsciiPrint("Allocated %u pages for mission mode img\n", num_mission_img_pages);
   
   gBS->CopyMem((UINT8*)mission_img_buf, 
                imgbuf, 
                mission_img_size);

   AsciiPrint ("Mission image buffer address 0x%llx\n", mission_img_buf);

//#define PAGES_TO_BYTES(x)    (x * EFI_PAGE_SIZE)
   //pcie_map_dma_buffer (CoreIdx, 0x100, (void*)sbl_buf, PAGES_TO_BYTES(num_sbl_pages), &MapHandle); 

   /* Execute BHI protocol to transfer SBL image */
   mstatus = mhi_transfer_image(mhi_dev_handle, (void*)sbl_buf, sbl_size);

   //pcie_unmap_dma_buffer (MapHandle); 

   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("MHI transfer image failed - %d\n", mstatus);
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }


   do {
      mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
      if(MHI_SUCCESS != mstatus)
      {
         AsciiPrint("MHI get EE failed - %d\n", mstatus);
         status = EFI_DEVICE_ERROR;
         break;
      }
   }while(MHI_EE_SBL != current_ee);

   AsciiPrint("Done executing BHI. Device EE = %d\n", current_ee);

   gBS->Stall (1000);

   //pcie_map_dma_buffer (CoreIdx, 0x100, (void*)mission_img_buf, PAGES_TO_BYTES(num_mission_img_pages), &MapHandle); 
   /* Execute BHIE Protocol to transfer mission mode image */
   mstatus = mhi_execute_bhie(mhi_dev_handle, (void*)mission_img_buf, mission_img_size);

   //pcie_unmap_dma_buffer (MapHandle); 

   if(MHI_SUCCESS != mstatus)
   {
      AsciiPrint("mhi_execute_bhie failed - %d\n", mstatus);
      mhi_get_ee(mhi_dev_handle, &current_ee);
      AsciiPrint("Device EE = %d\n", current_ee);
      status = EFI_DEVICE_ERROR;
      goto cleanup;
   }

   do {
      mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
      if(MHI_SUCCESS != mstatus)
      {
         AsciiPrint("MHI get EE failed - %d\n", mstatus);
         status = EFI_DEVICE_ERROR;
         break;
      }
   }while(MHI_EE_AMSS != current_ee);

   counter = 0;
   while(counter < 10)
   {
      gBS->Stall(100 * 1000);

      AsciiPrint("\n Checking EE again \n");
      mstatus = mhi_get_ee(mhi_dev_handle, &current_ee);
      if(MHI_SUCCESS != mstatus)
      {
         AsciiPrint("MHI get EE failed - %d\n", mstatus);
         status = EFI_DEVICE_ERROR;
         break;
      }
      AsciiPrint("Device EE = %d\n", current_ee);
      counter++;
   }

   /*if(MHI_EE_AMSS == current_ee)
   {
      status = RunMhiLoopbackTest(EndpointIdx, CoreIdx);
   }*/

cleanup:
   if(sbl_buf)
   {
      gBS->FreePages(sbl_buf, num_sbl_pages);
   }
   
   /*
   if(mission_img_buf)
   {
      gBS->FreePages(mission_img_buf, num_mission_img_pages);
   }
   */

   if(imgbuf)
   {
      FreePool(imgbuf);
   }
   
   EventUnsignal(testCbEvt);
   mhi_dev_close(mhi_dev_handle, &cb);
   EventWait(testCbEvt);
   EventDestroy(testCbEvt);
   mhi_unregister(devIdx, &cb);

   return status;
}

EFI_STATUS
MhiTestEntry (IN EFI_HANDLE         ImageHandle,
               IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS       Status = EFI_SUCCESS;
  UINTN            ErrorCode = 0, Errors = 0;
  UINTN            Argc, ArgcBak;
  CHAR8          **Argv, **ArgvMem = NULL, **ArgvBak;
  UINTN            EndpointIdx = 0xFFFFFFFF;
  UINTN            CoreIdx = 0xFFFFFFFF;
  int              i;
  CHAR8* ArgStr;
  UINT32           TestDuration, TestStart;
  UINT32           LoopCnt = 0;

  /* To do : parameterize these as well */
  CHAR8*   filePath = "amss.bin";
  CHAR8*   volumeName = "fv3";

  Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);

  if (!EFI_ERROR(Status) && (Argc > 0))
  {
     ArgvMem = Argv;

     /* Check if the app was launched by shell and the Cmd str is actually the
      * app name itself, ie it would be "app" or "app.efi", then again process
      * to split, this is because Ebl doesn't pass the name of app, but shell does &
      * other methods could yeild mixed results (like BDS launching apps via Menu, etc) */
     if ((AsciiStriCmp (Argv[0], "mhitest") == 0) ||
         (AsciiStriCmp (Argv[0], "mhitest.efi") == 0))
     {
       --Argc;
       if (Argc == 0)
       {
         FreePool (Argv);
         ArgvMem = NULL;
         Argv = NULL;

         /* Here, either return back or assume default values as required
          * if an argument is expected. If this image doesn't need any argument
          * then this whole block of code can be removed */
         AsciiPrint ("No Command to process, or assuming default values... \r\n");
   //      return EFI_SUCCESS;
       }
       else
         ++Argv;
     }
  }
  
  for (i=0; i<Argc; ++i)
  {
     if (AsciiStriCmp (Argv[i], "dbg") == 0)
     {
        ++stopfordebug;
         AsciiPrint ("Debug enabled, waiting for debugger attach..!!\r\n");
     }

  //   AsciiPrint (" %d : %a\r\n", i, Argv[i]);
  }

  if (stopfordebug)
     while (stopfordebug);

   pcie_enable_test_environment ();
  /*
   * Arguments and usage:
   *
   *   Usage: MhiTest
   *    mhitest can be used to test MHI functionality. This can be launched in
   *    uefi shell environment (Ebl) or from any other tool that can launch app in an automated way.
   *
   *    mhitest takes 2 kinds of arguments, ControlArgs and Commands. Each of these can have their own specific
   *    sub arguments. All arguments are case insensitive. Multiple commands can be given per launch.
   *    
   *  ControlArgs:
   *  -------------
   *    endpoint : MHI device identifer for a particular endpoint SoC
   *    rootport : PCIe Root port number where the endpoint SoC is connected
   *
   *  Commands :
   *  ----------
   *    loadfirmware : Load the endpoint SoC's firmware image(s) using BHI (and BHIe where applicable)
   *    loopback : MHI Loopback Test
   *
   *  e.g.:
   *    st fv3:\mhitest "core 1 info BuffSize 0x200000 Phy LinkWidth 1 LinkSpeed 2"
   *    st fv3:\mhitest "core 1 info"
   *
   * */

  EndpointIdx = 0;  // by default use 0 if not specified

  TestStart = GetTimerCountms();

  ArgcBak = Argc;
  ArgvBak = Argv;

  while (Argc)
  {
     //UINT32 ArgsConsumed = 0;

     ArgStr = Argv[0];

     /* Now prep Argc/Argv to pass futher by removeing name since we will
      * use ArgStr for getting current command */
     --Argc; ++Argv;

     if (AsciiStriCmp (ArgStr, "endpoint") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        EndpointIdx = AsciiStrDecimalToUintn (Argv[0]);
        Argc--; Argv++;
        continue;
     }

     if (AsciiStriCmp (ArgStr, "rootport") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        CoreIdx = AsciiStrDecimalToUintn (Argv[0]);
        Argc--; Argv++;
        continue;
     }

     if(AsciiStriCmp (ArgStr, "loopcount") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        LoopCnt = AsciiStrDecimalToUintn (Argv[0]);
        Argc--; Argv++;
        continue;
     }


     if (AsciiStriCmp (ArgStr, "loadfirmware") == 0)
     {
        ErrorCode = RunBhiTest (EndpointIdx, CoreIdx, filePath, volumeName);
        if (ErrorCode) ++Errors;
        continue;
     }

     if (AsciiStriCmp (ArgStr, "loopback") == 0)
     {
        ErrorCode = RunMhiLoopbackTest (EndpointIdx, CoreIdx, LoopCnt);
        if (ErrorCode) ++Errors;
        continue;
     }

     if (AsciiStriCmp (ArgStr, "testframework") == 0)
     {
        ErrorCode = TestFrameworkDemo (EndpointIdx, CoreIdx);
        if (ErrorCode) ++Errors;
        continue;
     }
  }

  if (ArgvMem)
    FreePool (ArgvMem);

  if (ErrorCode != 0)
    AsciiPrint ("Error count %d, Last Error Code: %X\r\n", Errors, ErrorCode);

  if (ResultReturnAddr)
  {
     *ResultReturnAddr = 0;

     if ((ErrorCode != 0) || (Errors != 0))
        *ResultReturnAddr = 1;
  }

  TestDuration = GetTimerCountms();
  TestDuration -= TestStart;
  
  AsciiPrint ("Total test took %d ms\r\n\r\n", TestDuration);

  return Status;
}
