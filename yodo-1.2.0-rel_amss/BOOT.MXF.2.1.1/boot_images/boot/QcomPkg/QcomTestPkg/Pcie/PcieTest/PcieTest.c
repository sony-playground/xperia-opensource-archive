/** @file PcieTest.c
#
#  Pcie Test Application.
#
#  Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc. All rights reserved.
#**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/npa.h>
#include <Library/pmapp_npa.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicTest.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIRamPartition.h>
#include "pcie_host_r.h"
#include "PcieTest_i.h"
#include <Protocol/EfiQcPcie.h>
#include <Library/pcie_rp.h>
#include <Library/PcieTestUtils.h>
#include <string.h>

volatile UINT32 stopfordebug = 0;
UINT8  DebugLevel = 0;
UINT32 TestBuffSize = 1 * 1024 * 1024;
UINT32 *ResultReturnAddr = NULL;

uint32 SetMemData (UINT64* Ptr, UINT64 SetPattern, UINT32 Sz)
{
   UINT64 *EndPtr, *WalkPtr;

   WalkPtr = Ptr;
   EndPtr = (UINT64*)(((UINT64)WalkPtr) + Sz);

   while (WalkPtr < EndPtr)
   {
      *WalkPtr = SetPattern;
      ++WalkPtr;
   }

   return 0;
}

uint32 VerifyMemData (UINT64* Ptr, UINT64 VerifyPattern, UINT32 Sz)
{
   UINT64 *EndPtr, *WalkPtr, vdata;
   UINT32 Errors = 0;

   WalkPtr = Ptr;
   EndPtr = (UINT64*)(((UINT64)WalkPtr) + Sz);

   while (WalkPtr < EndPtr)
   {
      vdata = *WalkPtr;
      if (vdata != VerifyPattern)
      {
         AsciiPrint ("Err @ 0x%X : exp 0x%lX act 0x%lX\n", WalkPtr, VerifyPattern, vdata);
         Errors++;
      }

      ++WalkPtr;
   }

   return Errors;
}
                              
uint32 VerifySetMemData (UINT64* Ptr, UINT64 VerifyPattern, UINT64 SetPattern, UINT32 Sz)
{
   UINT64 *EndPtr, *WalkPtr, vdata;
   UINT32 Errors = 0, Counter = 0, Reload = Sz/(10 * sizeof(UINT32));

   WalkPtr = Ptr;
   EndPtr = (UINT64*)(((UINT64)WalkPtr) + Sz);

   while (WalkPtr < EndPtr)
   {
      vdata = *WalkPtr;
      if (vdata != VerifyPattern)
      {
         AsciiPrint ("Err @ 0x%X : exp 0x%lX act 0x%lX\n", WalkPtr, VerifyPattern, vdata);
         Errors++;
      }

      *WalkPtr = SetPattern;
      ++WalkPtr;

      if (Counter == 0)
      {
         Counter = Reload;
         AsciiPrint (".");
      }
      --Counter;
   }

   return Errors;
}

#define PATTERN_1  0x5555555555555555ULL 
#define PATTERN_2  0xAA55AA55A5A55A5AULL 
#define PATTERN_3  0xBADF00DADEADD00DULL 
#define PATTERN_4  0x1234567890ABCDEFULL 

EFI_STATUS MemoryVerifyTest (UINT64* SrcBuffer, UINT64* PcieSpace, UINT32 BufferSize)
{
   UINT32 Errors = 0;

   /* No need for cache maint since it should already be cache coherent */
   SetMemData (SrcBuffer, PATTERN_1, BufferSize);

   AsciiPrint ("PCIe interleaved RW test ");
   /* Read data over PCIe and write again 8 byte chunks, read/write */
   Errors += VerifySetMemData (PcieSpace, PATTERN_1, PATTERN_2, BufferSize);

   /* Verify from memory side, nop from PCIe bus */
   Errors += VerifyMemData (SrcBuffer, PATTERN_2, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   AsciiPrint ("PCIe Reads test ");
   /* Now verify, only reads over PCIe bus */
   Errors += VerifyMemData (PcieSpace, PATTERN_2, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   AsciiPrint ("PCIe write 0's test ");
   /* Only writes over Pcie bus */
   SetMemData (PcieSpace, 0, BufferSize);
   AsciiPrint (" Done\n");

   /* Byte access */
//   ((CHAR8*)PcieSpace)[17] = '$';
//   if (((CHAR8*)SrcBuffer)[17] != '$') Errors++;

   AsciiPrint ("PCIe write test ");
   /* Only writes over Pcie bus */
   SetMemData (PcieSpace, PATTERN_3, BufferSize);

   /* Verify from memory side, nop from PCIe bus */
   Errors += VerifyMemData (SrcBuffer, PATTERN_3, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   AsciiPrint ("PCIe interleaved RW test ");
   /* Read data over PCIe and write again 8 byte chunks, read/write */
   Errors += VerifySetMemData (PcieSpace, PATTERN_3, PATTERN_4, BufferSize);

   /* Verify from memory side, nop from PCIe bus */
   Errors += VerifyMemData (SrcBuffer, PATTERN_4, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   AsciiPrint ("PCIe Reads test ");
   /* Now verify, only reads over PCIe bus */
   Errors += VerifyMemData (PcieSpace, PATTERN_4, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   AsciiPrint ("PCIe write test ");
   /* Only writes over Pcie bus */
   SetMemData (PcieSpace, 0, BufferSize);
   AsciiPrint (" Done\n");

   AsciiPrint ("PCIe Reads test ");
   /* Now verify, only reads over PCIe bus */
   Errors += VerifyMemData (PcieSpace, 0, BufferSize);
   AsciiPrint (" Done %d errors\n", Errors);

   if (Errors != 0)
      return EFI_DEVICE_ERROR;

   return EFI_SUCCESS;
}

EFI_STATUS RunPcieResetTest (UINTN CoreIdx)
{
   if (poweroff_pcie_port (CoreIdx) == PCIE_SUCCESS)
      return EFI_SUCCESS;

   return EFI_DEVICE_ERROR;
}

EFI_STATUS RunPcieEnumerateTest (UINTN CoreIdx)
{
   dev_handle_info_type handle_info;
   pcie_status_t pstatus;
   EFI_STATUS Status;

   if (CoreIdx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d", MAX_PCIE_CORES);

   Status = enumerate_pcie_port (CoreIdx);
   if (Status != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   pstatus = get_enumerated_dev_handle (CoreIdx, &handle_info);
   if (pstatus != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   return EFI_SUCCESS;
}

typedef enum
{
   reg_type_addr = 1,
   reg_type_size = 2,
   reg_type_bit_masks = 3,

}bar_reg_data_type_t;

typedef struct
{
   uint16                vend_id;
   uint16                dev_id;
   uint32                reg_offset;  // TODO: for now assume BAR 0, later if required use MSB 3 bits for each BAR
   uint32                size;        // Limit each entry size to 8 bytes so that address writes can be performed
   bar_reg_data_type_t   type_of_data;
   uint16                rsrv;
}bar_mem_rw_ranges_t;

bar_mem_rw_ranges_t bar_mem_rw_ranges[] = 
{
   {.vend_id = 0x17CB, .dev_id = 0x1103, .reg_offset = 0x10, .size = 0x8, .type_of_data = reg_type_addr},
   {.vend_id = 0x17CB, .dev_id = 0x1107, .reg_offset = 0x10, .size = 0x8, .type_of_data = reg_type_addr},
   {.vend_id = 0x1987, .dev_id = 0x5021, .reg_offset = 0x2C, .size = 0x4},  // Phison NVMe device

};

#define MAX_MEM_IOPS    1024

EFI_STATUS RunMemIOTest (UINTN CoreIdx)
{
   dev_handle_info_type handle_info;
   pcie_status_t pstatus;
   EFI_STATUS Status;
   uint32 ven_dev_id, i;
   volatile uint32* bar_addr;
   uint32 addrh = 0, addrl = 0, errors = 0, rw_cnt = 0, found_match = 0;

   if (CoreIdx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d\n", MAX_PCIE_CORES);

   Status = enumerate_pcie_port (CoreIdx);
   if (Status != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   pstatus = get_enumerated_dev_handle(CoreIdx, &handle_info);
   if (pstatus != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   bar_addr = (uint32*)handle_info.ep_info.rsrc.bars[0].pa;
   ven_dev_id = (handle_info.ep_info.dev_ids.vendor_id << 16) | handle_info.ep_info.dev_ids.device_id;

   for (i=0; i < ARRAY_SIZE(bar_mem_rw_ranges); ++i)
   {
      uint32 temp_id, wr_size, reg_off, val, data;

      temp_id = bar_mem_rw_ranges[i].dev_id | (bar_mem_rw_ranges[i].vend_id << 16);
      if (temp_id == ven_dev_id)
      {
         found_match++;
         reg_off = bar_mem_rw_ranges[i].reg_offset;
         wr_size = bar_mem_rw_ranges[i].size;

         AsciiPrint ("Found match %X  Reg off %X, Size %X\n", temp_id, reg_off, wr_size);

         switch (bar_mem_rw_ranges[i].type_of_data)
         {
            case reg_type_addr:
               if ((addrh == 0) && (addrl == 0))
               {
                  // TODO: determine if cache/page aligned addresses are required
                  addrl = (uint32)((uint64)bar_mem_rw_ranges);
                  write_mmio_reg32 (bar_addr, reg_off, addrl);
                  ++rw_cnt;
                  if (wr_size > 4)
                  {
                     addrh = (uint32)((uint64)&bar_mem_rw_ranges >> 32);
                     write_mmio_reg32 (bar_addr, reg_off + 4, addrh);
                     ++rw_cnt;
                  }
               }

               for (i=0; i < MAX_MEM_IOPS; ++i)
               {
                  val = read_mmio_reg32 (bar_addr, reg_off);
                  if (addrl != val)
                  {
                     AsciiPrint ("MMIO readback verify failed @ %d, %X, %X\n", reg_off, addrl, val);
                     ++errors;
                  }
                  addrl += 4;
                  write_mmio_reg32 (bar_addr, reg_off, addrl);
                  ++rw_cnt;

                  if (wr_size > 4)
                  {
                     val = read_mmio_reg32 (bar_addr, reg_off + 4);
                     if (addrh != val)
                     {
                        AsciiPrint ("MMIO readback verify failed @ %d, %X, %X\n", reg_off + 4, addrh, val);
                        ++errors;
                     }
                     addrh += 1;
                     if (addrh > 3)
                        addrh = 0;
                     write_mmio_reg32 (bar_addr, reg_off + 4, addrh);
                     ++rw_cnt;
                  }
               }
               break;
               
            case reg_type_bit_masks:
            default:
            case reg_type_size:
               data = 0x40101000;
               write_mmio_reg32 (bar_addr, reg_off, data);
               ++rw_cnt;

               for (i=0; i < MAX_MEM_IOPS; ++i)
               {
                  val = read_mmio_reg32 (bar_addr, reg_off);
                  if (data != val)
                  {
                     AsciiPrint ("MMIO readback verify failed @ %d, %X, %X\n", reg_off, data, val);
                     ++errors;
                  }
                  data += 4;
                  write_mmio_reg32 (bar_addr, reg_off, data);
                  ++rw_cnt;
               }
               break;
         }
      }
   }

   if (found_match)
      AsciiPrint ("Performed %d MMIO IO's and encountered %d errors\n", rw_cnt, errors);
   else
      AsciiPrint ("Couldn't find matching device Memio config...!!\n");

   if (errors)
      pcie_print_aer_logs (CoreIdx, ALL_BDF_VAL);

   poweroff_pcie_port (CoreIdx);

   if (errors)
      return EFI_DEVICE_ERROR;

   return EFI_SUCCESS;
}

EFI_STATUS RunPcieInfoTest (UINTN Idx, pcie_link_status_t* link_stat_ptr)
{
   pcie_port_info_t port_info;
   pcie_link_status_t link_status;
   CHAR8* link_state_str = "Down";

   if (pcie_get_port_info (Idx, &port_info) != PCIE_SUCCESS)
      return EFI_INVALID_PARAMETER;

   AsciiPrint ("Port : %d   ", Idx);
   AsciiPrint ("Capabilities : Lane width : x%d,  ", port_info.max_lane_width);
   AsciiPrint ("Link Speed mask : %X\n", port_info.link_speed_mask);
//   AsciiPrint ("ASPM mask : %X\n", port_info.link_aspm_mask);

   if (get_link_status (Idx, &link_status) != PCIE_SUCCESS)
      return EFI_INVALID_PARAMETER;

   if (link_status.link_up)
      link_state_str = "Up";
      
   AsciiPrint ("Current Status : Link %a  (%X)  ", link_state_str, link_status.link_state);
   AsciiPrint ("Link width : x%d,  ", link_status.current_link_width);

   AsciiPrint ("Link Speed : Gen %X\n", link_status.current_link_speed);

   if (link_stat_ptr)
      *link_stat_ptr = link_status;

   return EFI_SUCCESS;
}

//#define ENABLE_UNCACHED

char* LpbDisp[] = {"None", "Phy  LPB", "Digi LPB", "Rmt  LPB", "ERR"};

EFI_STATUS RunLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr, UINTN LoopBackOption)
{
   EFI_STATUS Status = EFI_SUCCESS;
   pcie_root_port_t* port_handle;
   UINT64 *SrcBuffer, *PcieSpace = NULL;
   CHAR8* LoopbackTypeStr = "None", *ResultStr = "";
   loopback_req_t Lpb_req;
   uint32 BufferSize, req_width, req_speed;
   int i;
   UINT32 ArgsConsumed = 0;
   UINT32           TestDuration, TestStart;

   BufferSize = TestBuffSize;

   // TODO: Choice of this memory seems to be picked based on the snooping ability of the
   //       PCIe controller on the CPU cache and whether the BAR region's memory attributes
   //       list as prefetchable or not.
   if (PcdGetBool(UseUncachedMemForPcieShadow) == FALSE)
   {
      SrcBuffer = AllocatePages (BufferSize / EFI_PAGE_SIZE);
   }
   else
   {
      SrcBuffer = UncachedAllocatePool (BufferSize);
//      AsciiPrint ("Configured for Uncached memory\n\n");
   }

   if (SrcBuffer == NULL)
     return EFI_OUT_OF_RESOURCES;

   req_width = 0;
   req_speed = 0;

   for (i=0; i<Argc; ++i)
   {
      //AsciiPrint ("Arg %a\n", Argv[i]);
      if ((AsciiStriCmp (Argv[i], "lw") == 0) || (AsciiStriCmp (Argv[i], "linkwidth") == 0))
      {
         if (Argc > i+1)
         {
           req_width = AsciiStrDecimalToUintn (Argv[i+1]);
           ++i;
           ArgsConsumed += 2;
//           AsciiPrint ("Width set to %d\n", req_width);
         }
      }
      else if ((AsciiStriCmp (Argv[i], "ls") == 0) || (AsciiStriCmp (Argv[i], "linkspeed") == 0))
      {
         if (Argc > i+1)
         {
           req_speed = AsciiStrDecimalToUintn (Argv[i+1]);
           ++i;
           ArgsConsumed += 2;
//           AsciiPrint ("Speed set to %d\n", req_speed);
         }
      }
      else
         break;
   }

   if (ArgsConsumedPtr)
      *ArgsConsumedPtr = ArgsConsumed;

   Lpb_req.rc_index = CoreIdx;
   Lpb_req.mem_base = (UINT64)SrcBuffer;
   Lpb_req.mem_size = BufferSize;
   Lpb_req.link_width = req_width;
   Lpb_req.link_speed = req_speed;

   AsciiPrint ("Request : Core %d, %a, ls %d, lw %d\n", CoreIdx, LpbDisp[LoopBackOption], req_speed, req_width);

   TestStart = GetTimerCountms();

   switch (LoopBackOption)
   {
     case LOCAL_ANALOG_TEST:
        LoopbackTypeStr = "Local Analog/Phy";
        if (pcie_enable_local_analog_loopback (&Lpb_req, &PcieSpace, &port_handle) != PCIE_SUCCESS)
        {
           Status = EFI_DEVICE_ERROR;
           AsciiPrint ("Error LA loopback entry failed\n");
           break;
        }
        AsciiPrint ("Entered LA loopback, Memory 0x%X ++ 0x%X => PCIe 0x%X\n", SrcBuffer, BufferSize, PcieSpace);
        Status = EFI_SUCCESS;
        break;

     case LOCAL_DIGITAL_TEST:
        LoopbackTypeStr = "Local Digital/Pipe";
        if (pcie_enable_local_digital_loopback (&Lpb_req, &PcieSpace, &port_handle) != PCIE_SUCCESS)
        {
           Status = EFI_DEVICE_ERROR;
           AsciiPrint ("Error LD loopback entry failed\n");
           break;
        }
        AsciiPrint ("Entered LD loopback, Memory 0x%X ++ 0x%X => PCIe 0x%X\n", SrcBuffer, BufferSize, PcieSpace);
        Status = EFI_SUCCESS;
        break;

     case REMOTE_DIGITAL_TEST:
        LoopbackTypeStr = "Remote Digital";
        if (pcie_enable_remote_digital_loopback (&Lpb_req, &PcieSpace, &port_handle) != PCIE_SUCCESS)
        {
           Status = EFI_DEVICE_ERROR;
           AsciiPrint ("Error Remote loopback entry failed\n");
           break;
        }

        AsciiPrint ("Entered Remote loopback, Memory 0x%X ++ 0x%X => PCIe 0x%X\n", SrcBuffer, BufferSize, PcieSpace);
        Status = EFI_SUCCESS;
        break;

     default:
        AsciiPrint ("Invalid option!\n");
        Status = EFI_INVALID_PARAMETER;
   }

   if (Status == EFI_SUCCESS)
   {
     pcie_link_status_t link_status;
     RunPcieInfoTest (CoreIdx, &link_status);

     Status = MemoryVerifyTest (SrcBuffer, PcieSpace, BufferSize);

     if (Status != EFI_SUCCESS)
     {
        ResultStr = "FAILED";
        pcie_print_aer_logs (CoreIdx, ALL_BDF_VAL);
     }
     else
        ResultStr = "PASSED";

     TestDuration = GetTimerCountms();
     TestDuration -= TestStart;

     if (req_speed)
     {
        if (req_speed != link_status.current_link_speed)
           AsciiPrint ("Mismatch speed : %d  %a (Gen %d != %d)\n", CoreIdx, LpbDisp[LoopBackOption], req_speed, link_status.current_link_speed);
     }

     if (req_width)
     {
        if (req_width != link_status.current_link_width)
           AsciiPrint ("Mismatch lane width : %d  %a (Lane x%d != x%d)\n", CoreIdx, LpbDisp[LoopBackOption], req_width, link_status.current_link_width);
     }

     AsciiPrint ("Result :====== Core %d, x%d, Gen %d, MemPgs 0x%X, %a : %a, %d ms\n", CoreIdx, 
           link_status.current_link_width, link_status.current_link_speed, BufferSize/EFI_PAGE_SIZE, LoopbackTypeStr, ResultStr, TestDuration);

     if (pcie_disable_loopback (port_handle) != PCIE_SUCCESS)
        AsciiPrint ("PCIe core Loopback Exited with Errors\n\n");
     else
        AsciiPrint ("PCIe core Loopback Exited\n\n");
   }

   if (PcdGetBool(UseUncachedMemForPcieShadow) == FALSE)
      FreePages (SrcBuffer, BufferSize / EFI_PAGE_SIZE);
   else
      UncachedFreePool (SrcBuffer);

   return Status;
}

EFI_STATUS SetLinkWidth (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx)
{
   UINTN Width;

   if ((Argc == 0) || (Argv[0] == NULL))
      return EFI_INVALID_PARAMETER;

   Width = AsciiStrDecimalToUintn (Argv[0]);

   AsciiPrint ("Set Link width of %d to %d\n", CoreIdx, Width);

   if (pcie_set_link_width (CoreIdx, Width) != PCIE_SUCCESS)
      AsciiPrint ("Set Link width Failed\n");

   RunPcieInfoTest (CoreIdx, NULL);

   return EFI_SUCCESS;
}

EFI_STATUS SetLaneWidth (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx)
{
   UINTN Width;

   if ((Argc == 0) || (Argv[0] == NULL))
      return EFI_INVALID_PARAMETER;

   Width = AsciiStrDecimalToUintn (Argv[0]);

   AsciiPrint ("Set Lane width of %d to %d\n", CoreIdx, Width);

   if (pcie_set_lane_width (CoreIdx, Width) != PCIE_SUCCESS)
      AsciiPrint ("Set Lane width Failed\n");

   RunPcieInfoTest (CoreIdx, NULL);

   return EFI_SUCCESS;
}

EFI_STATUS SetLinkSpeed (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx)
{
   UINTN Speed;

   if ((Argc == 0) || (Argv[0] == NULL))
      return EFI_INVALID_PARAMETER;

   Speed = AsciiStrDecimalToUintn (Argv[0]);

   AsciiPrint ("Set Link speed of %d to %d\n", CoreIdx, Speed);

   if (pcie_set_link_speed (CoreIdx, Speed) != PCIE_SUCCESS)
      AsciiPrint ("Set Link Speed Failed\n");

   RunPcieInfoTest (CoreIdx, NULL);

   return EFI_SUCCESS;
}

EFI_STATUS SetLinkSpeedMask (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx)
{
   UINTN Mask;

   if ((Argc == 0) || (Argv[0] == NULL))
      return EFI_INVALID_PARAMETER;

   Mask = AsciiStrHexToUintn (Argv[0]);

   AsciiPrint ("Set allowed Link sppeds of %d to %X\n", CoreIdx, Mask);

   if (pcie_set_allowed_link_speeds (CoreIdx, Mask) != PCIE_SUCCESS)
      AsciiPrint ("Set Allowed link speeds Failed\n");

   RunPcieInfoTest (CoreIdx, NULL);

   return EFI_SUCCESS;
}

EFI_STATUS AnalogLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunLoopbackTest (Argc, Argv, CoreIdx, ArgsConsumedPtr, LOCAL_ANALOG_TEST);
}

EFI_STATUS DigitalLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunLoopbackTest (Argc, Argv, CoreIdx, ArgsConsumedPtr, LOCAL_DIGITAL_TEST);
}

EFI_STATUS RemoteLoopbackTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunLoopbackTest (Argc, Argv, CoreIdx, ArgsConsumedPtr, REMOTE_DIGITAL_TEST);
}

EFI_STATUS ASPML0Test (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunASPMTest (CoreIdx, ASPM_TYPE_L0s);
}

EFI_STATUS ASPML11ssTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunASPMTest (CoreIdx, ASPM_TYPE_L11ss);
}

EFI_STATUS ASPML12ssTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunASPMTest (CoreIdx, ASPM_TYPE_L12ss);
}

EFI_STATUS CfgSpaceTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunCfgSpaceTest (CoreIdx);
}

EFI_STATUS MemIOTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunMemIOTest (CoreIdx);
}

EFI_STATUS EnumerateTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunPcieEnumerateTest (CoreIdx);
}

EFI_STATUS ResetTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunPcieResetTest (CoreIdx);
}

EFI_STATUS TargetPlatSelectTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return TargetPlatformOptionSelect (Argc, Argv, ArgsConsumedPtr);
}

EFI_STATUS EPCfgTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunCfgSpaceTest (CoreIdx);
}

EFI_STATUS SidMemMap (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
//   return Map_Installed_memory ();
   return EFI_SUCCESS;
}

EFI_STATUS AllPreConfigured (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   run_all_predefined ();
   return EFI_SUCCESS;
}

EFI_STATUS AllPreConfiguredRemote (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   run_all_remote ();
   return EFI_SUCCESS;
}

EFI_STATUS AllPreConfiguredAnalog (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   run_all_local_analog ();
   return EFI_SUCCESS;
}

EFI_STATUS AllPreConfiguredDigital (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   run_all_local_digital ();
   return EFI_SUCCESS;
}

EFI_STATUS PciePortInfoTest (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr)
{
   return RunPcieInfoTest (CoreIdx, NULL);
}

typedef EFI_STATUS (*PcieTestFn) (UINTN Argc, CHAR8** Argv, UINT32 CoreIdx, UINT32* ArgsConsumedPtr);

typedef struct
{
   UINTN        MinArgs;
   const char*  Alias;
   const char*  Cmd;
   PcieTestFn   TestFunc;
   const char*  HelpString;
}PcieTestType;

#define INFO_TEST_HELP_STR    "Read Pcie port information from registers and print"
#define LD_TEST_HELP_STR      "Local Digital loopback test. Command aliases (ld,pipe,LocalDigital). Optional arguments: LinkWidth lw x, Link Speed ls x"
#define LA_TEST_HELP_STR      "Local Analog loopback test. Command aliases (la,phy,LocalAnalog). Optional arguments: LinkWidth lw x, Link Speed ls x"
#define RL_TEST_HELP_STR      "Remote Digital loopback test. Command aliases (rl,RemoteDigital). Optional arguments: LinkWidth lw x, Link Speed ls x. Requires a powered and functional remote partner that supports loopback"
#define L0_TEST_HELP_STR      "Link L0s test. Requires a powered and functional remote partner"
#define L11SS_TEST_HELP_STR   "Link L11ss (L1.1) test. Requires a powered and functional remote partner that supports the L1.1ss mode"
#define L12SS_TEST_HELP_STR   "Link L12ss (L1.2) test. Requires a powered and functional remote partner that supports the L1.2ss mode"
#define EPCFG_TEST_HELP_STR   "End point Config space test. Requires a powered and functional remote partner"
#define MEMIO_TEST_HELP_STR   "End point Memory IO (BAR Space) test. Requires a powered and functional remote partner"
#define ENUM_TEST_HELP_STR    "Linkup and Enumerate test. Just brings the linkup and leaves it in that state. Requires a powered and functional remote partner"
#define RST_TEST_HELP_STR     "Reset and Power off the PCIe port which was left in non powered down state."
#define TPSEL_TEST_HELP_STR   "Target Platform Option select test. Selects and switches target/SOC specific configuration as supported"
#define SIDMAP_TEST_HELP_STR  "Map all memory to all PCIe ports SID on a supported SOC"


PcieTestType PcieTests [] = 
{
   {0, "inf",    "info", PciePortInfoTest, INFO_TEST_HELP_STR},
   {0, "ld",     "LocalDigital", DigitalLoopbackTest, LD_TEST_HELP_STR},
   {0, "ld",     "Pipe", DigitalLoopbackTest, LD_TEST_HELP_STR},
   {0, "la",     "LocalAnalog", AnalogLoopbackTest, LA_TEST_HELP_STR},
   {0, "la",     "Phy", AnalogLoopbackTest, LA_TEST_HELP_STR},
   {0, "rl",     "RemoteDigital", RemoteLoopbackTest, RL_TEST_HELP_STR},
   {0, "l0",     "L0", ASPML0Test, L0_TEST_HELP_STR},
   {0, "l11",    "L11ss", ASPML11ssTest, L11SS_TEST_HELP_STR},
   {0, "l12",    "L12ss", ASPML12ssTest, L12SS_TEST_HELP_STR},
   {0, "epcfg",  "epcfg", EPCfgTest, EPCFG_TEST_HELP_STR},
   {0, "memio",  "memio", MemIOTest, MEMIO_TEST_HELP_STR},
   {0, "enum",   "enum", EnumerateTest, ENUM_TEST_HELP_STR},
   {0, "reset",  "rst", ResetTest, RST_TEST_HELP_STR},
   {1, "tpsel",  "tpsel", TargetPlatSelectTest, TPSEL_TEST_HELP_STR},
   {0, "dbg",    "dbg", NULL, "Spin in infinite debug loop for JTAG attach and debug"},

   {0, "sid",    "SidMapMem", SidMemMap, SIDMAP_TEST_HELP_STR},
   {0, "all",    "AllPreConfigured", AllPreConfigured, "All preconfigured tests for unit test"},

   {0, "all_rl", "AllPreCfgRemote", AllPreConfiguredRemote, "All preconfigured remote loopback tests for unit test"},
   {0, "all_la", "AllPreCfgAnalog", AllPreConfiguredAnalog, "All preconfigured local analog loopback tests for unit test"},
   {0, "all_ld", "AllPreCfgDigital", AllPreConfiguredDigital, "All preconfigured local digital loopback tests for unit test"},

};

  /*
   * Arguments and usage:
   *
   *   Refer to ReadMe.PcieTest.txt for usage and argument details.
   *
   * */


EFI_STATUS
RunMappedPcieTest (UINTN  Argc, CHAR8   **Argv)
{
  EFI_STATUS       Status = EFI_SUCCESS;
  UINTN            ErrorCode = 0, Errors = 0;
  UINTN            ArgcBak;
  CHAR8          **ArgvBak;
  UINTN            CoreIdx = 0xFFFFFFFF;
  CHAR8           *ArgStr;
  UINT32           TestDuration, TestStart;
  UINT32           LoopCnt = 0, i, TestFound;

  CoreIdx = 0;  // by default use 0 if not specified

  TestStart = GetTimerCountms();

  ArgcBak = Argc;
  ArgvBak = Argv;

  while (Argc)
  {
     UINT32 ArgsConsumed;

     ArgStr = Argv[0];

     /* Now prep Argc/Argv to pass futher by removeing name since we will
      * use ArgStr for getting current command */
     --Argc; ++Argv;

     if (AsciiStriCmp (ArgStr, "dbg") == 0)
        continue;

     if (AsciiStriCmp (ArgStr, "core") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        CoreIdx = AsciiStrDecimalToUintn (Argv[0]);
        Argc--; Argv++;
        continue;
     }

     /* Loop example: st fv4:\pcietest "core 0 rl core 1 rl ls 2 core 0 rl ls 2 core 1 rl ls 1 loop 200"
      * above example repeats the whole set of tests 200 times */
     if (AsciiStriCmp (ArgStr, "loop") == 0)
     {
        UINT32 Cnt;

        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        Cnt = AsciiStrDecimalToUintn (Argv[0]);
        Argc--; Argv++;
        if (LoopCnt < Cnt)
        {
           ++LoopCnt;
           AsciiPrint ("       Repeating tests : %d\r\n       ---------------------\r\n", LoopCnt);                        

           Argc = ArgcBak;
           Argv = ArgvBak;
        }
        continue;
     }

     if (AsciiStriCmp (ArgStr, "--result") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        ResultReturnAddr = (UINT32*)AsciiStrHexToUintn (Argv[0]);
        Argc--; Argv++;
        continue;
     }

     if (AsciiStriCmp (ArgStr, "buffsize") == 0)
     {
        if (Argc < 1) { ++Errors; break; } // insufficient arguments
        TestBuffSize = AsciiStrHexToUintn (Argv[0]);

        // Round off to page size
        TestBuffSize += (EFI_PAGE_SIZE - 1);
        TestBuffSize &= (~(EFI_PAGE_SIZE - 1));

        AsciiPrint ("Test Buffer Size 0x%08X\r\n", TestBuffSize);
        Argc--; Argv++;
        continue;
     }

     ArgsConsumed = 0;
     TestFound = 0;
     for (i=0; i < ARRAY_SIZE(PcieTests); ++i)
     {
        if ((AsciiStriCmp (ArgStr, PcieTests[i].Cmd) == 0) || (AsciiStriCmp (ArgStr, PcieTests[i].Alias) == 0))
        {
           PcieTestFn   TestFn;

           TestFound = 1;

           if (Argc < PcieTests[i].MinArgs)
           {
              AsciiPrint ("Insufficient arguments for command : %a min required %d\r\n", ArgStr, PcieTests[i].MinArgs);
              ++Errors;
              break;
           } // insufficient arguments

           TestFn = PcieTests[i].TestFunc;

           if (TestFn != NULL)
           {
              ErrorCode = TestFn (Argc, Argv, CoreIdx, &ArgsConsumed);
              if (ErrorCode)
              {
                 AsciiPrint ("Test failed [%a] 0x%08X\r\n", ArgStr, ErrorCode);
                 ++Errors;
              }
           }

           if (Argc >= ArgsConsumed)
           {
              Argc -= ArgsConsumed;
              Argv += ArgsConsumed;
           }
           break;
        }
     }

     if (TestFound == 0)
        /* Landed here means we didn't find the command */
        AsciiPrint ("Unknown command : %a\r\n", ArgStr);
  }

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

EFI_STATUS
PcieTestEntry (IN EFI_HANDLE         ImageHandle,
               IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS       Status = EFI_SUCCESS;
  UINTN            Argc = 0;
  CHAR8          **Argv = NULL, **ArgvMem = NULL;
  int              i;

  Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);

  if (!EFI_ERROR(Status) && (Argc > 0))
  {
     ArgvMem = Argv;

     /* Check if the app was launched by shell and the Cmd str is actually the
      * app name itself, ie it would be "app" or "app.efi", then again process
      * to split, this is because Ebl doesn't pass the name of app, but shell does &
      * other methods could yeild mixed results (like BDS launching apps via Menu, etc) */
     if ((AsciiStriCmp (Argv[0], "pcietest") == 0) ||
         (AsciiStriCmp (Argv[0], "pcietest.efi") == 0))
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

  Status = RunMappedPcieTest (Argc, Argv);

  if (ArgvMem)
    FreePool (ArgvMem);

  return Status;
}


