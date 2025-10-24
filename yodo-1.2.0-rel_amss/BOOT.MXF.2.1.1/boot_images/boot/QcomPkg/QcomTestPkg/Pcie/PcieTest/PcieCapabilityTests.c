/** @file 
#
#  Pcie Test Capability tests
#
#  Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 06/08/2021   yg      Initial Revision
#==============================================================================
#**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "pcie_host_r.h"
#include <Protocol/EfiQcPcie.h>
#include <Library/pcie_rp.h>
#include <Library/PcieTestUtils.h>
#include <Library/ArmLib.h>
#include <string.h>

#define PCI_MSI_CAP_ID                               (0x05)
#define PCI_PCIE_CAP_ID                              (0x10)

#define PCIE_MSIX_CAP_ID                             (0x0011)
#define PCIE_L1SS_PM_CAP_ID                          (0x001E)
#define PCIE_LTR_EXT_CAP_ID                          (0x0018)
#define PCIE_AER_EXT_CAP_ID                          (0x0001)

// TODO: avoid having global and perhaps design it in a different way to just print once, or just don't
//       print at all
uint32 print_cap_dumps = 0;

void read_dump_caps_reg (volatile uint32* cfg_space_addr, uint32 reg_offset, uint32 last_reg)
{
   volatile uint32 val;
   uint32 i;

   for (i = 0; i <= last_reg; i += 4)
   {
      // Read config reg even if we don't need to print, this being the part of actual test
      val = READ_CFG_REG(cfg_space_addr, (reg_offset + i));
      if (print_cap_dumps)
      {
         if ((i % 16) == 0)
            AsciiPrint ("\n  0x%02X : ", i);

         AsciiPrint ("0x%08X ", val);
      }
   }

   AsciiPrint ("\n");
}

/* MSI ext capabilities bit definition macros */
#define MSI_MESSAGE_CONTROL_BIT_OFFSET      16

#define MSI_ENABLE_OFFSET                      (MSI_MESSAGE_CONTROL_BIT_OFFSET + 0)
#define MSI_MULTI_MSG_CAPABLE_OFFSET           (MSI_MESSAGE_CONTROL_BIT_OFFSET + 1)
#define MSI_MULTI_MSG_ENABLE_OFFSET            (MSI_MESSAGE_CONTROL_BIT_OFFSET + 4)
#define MSI_ADDR_64_BIT_CAPABLE_OFFSET         (MSI_MESSAGE_CONTROL_BIT_OFFSET + 7)
#define MSI_PER_VECTOR_MASK_CAPABLE_OFFSET     (MSI_MESSAGE_CONTROL_BIT_OFFSET + 8)
#define MSI_EXTENDED_MSG_DATA_CAPABLE_OFFSET   (MSI_MESSAGE_CONTROL_BIT_OFFSET + 9)
#define MSI_EXTENDED_MSG_DATA_ENABLE_OFFSET    (MSI_MESSAGE_CONTROL_BIT_OFFSET + 10)

#define MSI_ENABLE_MASK                        (1 << MSI_ENABLE_OFFSET)
#define MSI_ADDR_64_BIT_CAPABLE_MASK           (1 << MSI_ADDR_64_BIT_CAPABLE_OFFSET)
#define MSI_PER_VECTOR_MASK_CAPABLE_MASK       (1 << MSI_PER_VECTOR_MASK_CAPABLE_OFFSET)
#define MSI_EXTENDED_MSG_DATA_CAPABLE_MASK     (1 << MSI_EXTENDED_MSG_DATA_CAPABLE_OFFSET)
#define MSI_EXTENDED_MSG_DATA_ENABLE_MASK      (1 << MSI_EXTENDED_MSG_DATA_ENABLE_OFFSET)

volatile static uint32 EP_MSI_Dest = 0;

pcie_status_t test_msi_cap (UINTN CoreIdx, volatile uint32* cfg_space_addr, uint32 cap_offset)
{
   uint16 msg_cnt, data_loc, imask_reg = 0;
   uint32 msi_val, msg, msg_data = 0x1234, i, mask_sample, control_sample, mask_val;
   uint64 msg_addr = 0;

   msi_val = READ_CFG_REG(cfg_space_addr, cap_offset);

   data_loc = cap_offset;
   msg_cnt = (msi_val >> MSI_MULTI_MSG_CAPABLE_OFFSET) & 7;  // 8 options => 1, 2, 4, 8, 16, 32, rsrv, rsrv
   msi_val = msi_val | (msg_cnt << MSI_MULTI_MSG_ENABLE_OFFSET);  // Enable max capable it advertized or limit to what we need

   WRITE_CFG_REG (cfg_space_addr, data_loc, msi_val);

   //MemoryFence ();

   data_loc += 4;

   msg_addr = (uint64)&EP_MSI_Dest;

   msg = (uint32)(msg_addr & 0xFFFFFFFF);
   // First write the message address/data values
   WRITE_CFG_REG (cfg_space_addr, data_loc, msg);  // LS address
   data_loc += 4;

   msg = (uint32)((msg_addr >> 32) & 0xFFFFFFFF);
   if (msi_val & MSI_ADDR_64_BIT_CAPABLE_MASK)
   {
      WRITE_CFG_REG (cfg_space_addr, data_loc, msg);  // MS address
      data_loc += 4;
   }
   else if (msg != 0)
   {
      // ERROR..!! Message address is 64 bit but the MSI is not 64 bit addr capable..!!
      AsciiPrint ("MSI is not 64 bit addr capable");
      // TODO: determine all error conditions first and bail out before modifying anything
      return PCIE_ERROR;
   }

   if (msi_val & MSI_EXTENDED_MSG_DATA_CAPABLE_MASK)
      WRITE_CFG_REG (cfg_space_addr, data_loc, msg_data);
   else if ((msg_data >> 16) & 0xFFFF)
   {
      // TODO: determine all error conditions first and bail out before modifying anything
      AsciiPrint ("MSI doesn't support extended msg data");
      return PCIE_ERROR;
   }
   else
      WRITE_CFG_REG (cfg_space_addr, data_loc, msg_data);

   data_loc += 4;

   if (msi_val & MSI_PER_VECTOR_MASK_CAPABLE_MASK)
   {
      WRITE_CFG_REG (cfg_space_addr, data_loc, 0);  // Unmask all
      imask_reg = data_loc;
   }

   // Enable extended data if supported, need to preserve and write msi_val to take effect
   if (msi_val & MSI_EXTENDED_MSG_DATA_CAPABLE_MASK)
      msi_val = msi_val | MSI_EXTENDED_MSG_DATA_ENABLE_MASK;

   // Now enable MSI on device EP side
   msi_val = msi_val | MSI_ENABLE_MASK;
   WRITE_CFG_REG (cfg_space_addr, data_loc, msi_val);   

   /******* so far writes are done, now read back stuff and do more writes and verify ***/

   gBS->Stall (1000); // wait 1ms

   if (EP_MSI_Dest != 0)
      AsciiPrint ("MSI destination value before: 0, after %X\n", EP_MSI_Dest);

   // Stress enable/disable and mask bits.
   mask_sample = 0;
   control_sample = READ_CFG_REG(cfg_space_addr, cap_offset);
   msg_cnt = (1 << msg_cnt); // convert mask to actual number

   for (i=0; i<128; ++i)
   {
      if ((i & 0x7) == 0x4)
      {
         msi_val = msi_val ^ MSI_ENABLE_MASK;
         WRITE_CFG_REG (cfg_space_addr, cap_offset, msi_val);
         control_sample = msi_val;
      }

      {
         uint32 temp, flg;

         temp = i & (msg_cnt - 1);

         flg = ((i >> 5) & 1) ^ ((i >> 2) & 1); // just randomize using few bits, here 5, 2

         mask_sample = mask_sample ^ (flg << temp);
         WRITE_CFG_REG (cfg_space_addr, imask_reg, mask_sample);   
      }

      msi_val = READ_CFG_REG(cfg_space_addr, cap_offset);
      if (msi_val != control_sample)
         AsciiPrint ("MSI Control register changed, exp %X  act %X\n", control_sample, msi_val);

      mask_val = READ_CFG_REG(cfg_space_addr, imask_reg);
      if (mask_val != mask_sample)
         AsciiPrint ("MSI mask register changed, exp %X  act %X\n", mask_sample, mask_val);
   }

   if (EP_MSI_Dest != 0)
      AsciiPrint ("MSI destination value at the end %X\n", EP_MSI_Dest);

   return PCIE_SUCCESS;
}

pcie_status_t print_cap_details (volatile uint32* cfg_space_addr, uint32 cap_offset, uint32 last_reg, const char* cap_name)
{
   volatile uint32 val;

   val = READ_CFG_REG(cfg_space_addr, cap_offset);
   val = val & 0xff;

   if (cap_name == NULL)
      cap_name = "Unknown Cap";

   AsciiPrint ("%a : 0x%02X @ 0x%02X : 0x%08X", cap_name, val, cap_offset, cfg_space_addr + (cap_offset/4));

   read_dump_caps_reg (cfg_space_addr, cap_offset, last_reg);

   return PCIE_SUCCESS;
}

typedef pcie_status_t (*process_capability_fn)(UINTN CoreIdx, volatile uint32*, uint32);

typedef struct
{
   uint32                 cap_id;
   uint32                 last_reg;  // Helps referring from spec to find the last defined register
   process_capability_fn  cap_fn;
   const char*            cap_name;
}capability_handler_t;

// Map a specific test function if required
capability_handler_t capability_map [] =
{
   {  0x01,      0x0C, NULL, "PCI Pwr Mgmt cap"},
   {  0x10,      0x38, NULL, "PCIe cap"},
   {  0x11,      0x0C, NULL, "MSI-X cap"},
   {  0x05,      0x0C, test_msi_cap, "MSI cap"},

  // Extended capabilities. bit 16 helps with simple searching
   {  0x10001,   0x3C, NULL, "AER cap"},
   {  0x10017,   0x0C, NULL, "TPH cap"},
   {  0x10018,   0x04, NULL, "LTR cap"},
   {  0x10019,   0x14, NULL, "Sec PCIe cap"},
   {  0x1001E,   0x0C, NULL, "L1ss PM cap"},
};

/* cap_id will have bit 16 set to 1 for extended capability */
pcie_status_t run_capability_test (UINTN CoreIdx, volatile uint32* cfg_space_addr, uint32 cap_offset)
{
   uint32 cap_val, reg_val;
   process_capability_fn cap_handler = NULL;
   uint32 i, last_reg = 4;
   const char* cap_name = NULL;
   pcie_status_t pstatus = PCIE_SUCCESS;

   cap_val = READ_CFG_REG(cfg_space_addr, cap_offset);

   /* Just read ID's and Status */
   reg_val = READ_CFG_REG(cfg_space_addr, 0); // ID's
   reg_val = READ_CFG_REG(cfg_space_addr, 4);  // Status Cmd

   if (cap_offset >= 0x100)  // Extended capability
   {
      cap_val = cap_val & 0xFFFF;
      cap_val = cap_val | (1 << 16);
   }
   else
   {
      cap_val = cap_val & 0xFF;
   }

   for (i = 0; i < ARRAY_SIZE(capability_map); ++i)
   {
      if (capability_map[i].cap_id == cap_val)
      {
         last_reg = capability_map[i].last_reg;
         cap_name = capability_map[i].cap_name;
         cap_handler = capability_map[i].cap_fn;
         break;
      }
   }

   print_cap_details (cfg_space_addr, cap_offset, last_reg, cap_name);

   if (cap_handler != NULL)
   {
      AsciiPrint ("Running extended test for : %a (0x%X)\n", cap_name, (cap_val & 0xFFFF));
      pstatus = cap_handler (CoreIdx, cfg_space_addr, cap_offset);
      if (pstatus != PCIE_SUCCESS)
      {
         AsciiPrint ("Test failed for : %a (0x%X)\n", cap_name, (cap_val & 0xFFFF));
         pcie_print_aer_logs (CoreIdx, ALL_BDF_VAL);
      }
   }

   return pstatus;
}

#define EXT_CAP_ID(id)      (id | 0x10000)
#define IS_EXT_CAP_ID(id)   (id & 0x10000)

pcie_status_t EnumerateCapabilities (UINTN CoreIdx, volatile uint32* cfg_space_addr, process_capability_fn enum_cb_fn)
{
   uint32 next_cap_offset;
   uint32 cap_val, val;

   if ((enum_cb_fn == NULL) || (cfg_space_addr == NULL))
      return PCIE_INVALID_PARAM;

   next_cap_offset = READ_CFG_REG(cfg_space_addr, 0x34);
   next_cap_offset = next_cap_offset & 0xff;
   while (next_cap_offset)
   {
      cap_val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
      cap_val = cap_val & 0xff;

      enum_cb_fn (CoreIdx, cfg_space_addr, next_cap_offset);

      val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
      next_cap_offset = (val >> 8) & 0xff;
   }

   /* Ext capabilities */
   next_cap_offset = 0x100;
   while (next_cap_offset)
   {
      cap_val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
      cap_val = (cap_val & 0xfff) | (1 << 16);

      enum_cb_fn (CoreIdx, cfg_space_addr, next_cap_offset);

      val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
      next_cap_offset = (val >> 20) & 0xfff;
   }

   return PCIE_SUCCESS;
}

uint32 GetCapabilityRegOffset (volatile uint32* cfg_space_addr, uint32 cap_id)
{
   uint32 next_cap_offset;
   uint32 cap_val, val;

   if (cfg_space_addr == NULL)
      return 0;

   if (IS_EXT_CAP_ID(cap_id) == 0)
   {
      next_cap_offset = READ_CFG_REG(cfg_space_addr, 0x34);
      next_cap_offset = next_cap_offset & 0xff;
      while (next_cap_offset)
      {
         cap_val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
         cap_val = cap_val & 0xff;

         if (cap_id == cap_val)
            return next_cap_offset;

         val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
         next_cap_offset = (val >> 8) & 0xff;
      }
   }
   else
   {
      /* Ext capabilities */
      next_cap_offset = 0x100;
      while (next_cap_offset)
      {
         cap_val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
         cap_val = (cap_val & 0xfff) | (1 << 16);

         if (cap_id == cap_val)
            return next_cap_offset;

         val = READ_CFG_REG(cfg_space_addr, next_cap_offset);
         next_cap_offset = (val >> 20) & 0xfff;
      }
   }

   return 0;
}

EFI_STATUS RunCfgSpaceTest (UINTN CoreIdx)
{
   dev_handle_info_type handle_info;
   pcie_status_t pstatus;
   EFI_STATUS Status;
   volatile uint32* cfg_space_addr;
   int i, j;
   uint32 val;

   if (CoreIdx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d", MAX_PCIE_CORES);

   Status = enumerate_pcie_port (CoreIdx);
   if (Status != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   pstatus = get_enumerated_dev_handle(CoreIdx, &handle_info);
   if (pstatus != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   cfg_space_addr = handle_info.ep_info.cfg_space;

   if (cfg_space_addr == NULL)
   {
      AsciiPrint ("Failed...!! Invalid config space address\n");

      poweroff_pcie_port (CoreIdx);
      return EFI_SUCCESS;
   }

   // Read all registers till 0x40
   for (i = 0; i < 64; ++i)
   {
      for (j = 0; j < 0x40; j += 4)
      {
         val = READ_CFG_REG(cfg_space_addr, 0); // ID's
         val = READ_CFG_REG(cfg_space_addr, 4);  // Status Cmd

         val = READ_CFG_REG(cfg_space_addr, j); // Rest of the stuff
      }
   }

   print_cap_dumps = 1;  // print just once

   // Now read Status_Cmd and the capabilities
   for (i = 0; i < 4; ++i)
   {
      EnumerateCapabilities (CoreIdx, cfg_space_addr, &run_capability_test);

      print_cap_dumps = 0;  // print just once
      AsciiPrint ("\n");
   }

   poweroff_pcie_port (CoreIdx);

   return EFI_SUCCESS;
}

#define PCIE_CAP_LINK_CAPABILITIES       0x0C
#define PCIE_CAP_LINK_CONTROL            0x10
                                       
#define L1_PM_SS_CAPABILITIES            0x04
#define L1_PM_SS_CONTROL                 0x08

#define ASPM_L0s_SUPPORTED(x)            ((x) & (1 << 10))
#define ASPM_L1_SUPPORTED(x)             ((x) & (1 << 11))

#define ENABLE_ASPM_L0s(x)               ((x) | 1)
#define ENABLE_ASPM_L1(x)                ((x) | 2)

#define DISABLE_ASPM_L0s(x)              ((x) & (~(1)))
#define DISABLE_ASPM_L1(x)               ((x) & (~(2)))

#define L1_1_SS_BITS                     (1 << 3)
#define L1_2_SS_BITS                     (1 << 2)

#define ENABLE_BME_MSE(x)                ((x) | 6)
#define DISABLE_BME_MSE(x)               ((x) & (~(6)))

#define ASPM_L1_SS_SUPPORTED(x,op)       ((x) & (op))
#define ENABLE_ASPM_L1_SS(x,op)          ((x) | (op))
#define DISABLE_ASPM_L1_SS(x,op)         ((x) & (~(op)))

#define ASPM_L1_1_SUPPORTED(x)           ((x) & (1 << 3))
#define ASPM_L1_2_SUPPORTED(x)           ((x) & (1 << 2))

#define ENABLE_ASPM_L1_1(x)              ((x) | (1 << 3))
#define ENABLE_ASPM_L1_2(x)              ((x) | (1 << 2))

#define DISABLE_ASPM_L1_1(x)             ((x) & (~(1 << 3)))
#define DISABLE_ASPM_L1_2(x)             ((x) & (~(1 << 2)))

/*
 *   L1 Enable:
 *      - Enable on upstream component (host) first
 *      - Then enable on downstream component (EP)
 *
 *   L1 Disable:
 *      - Disable on downstream component (EP) first
 *      - Then Disable on upstream component (host)
 * */

pcie_status_t enable_disable_L1ss (volatile uint32* host_cfg_addr, uint32 host_pcie_cap, volatile uint32* ep_cfg_addr, uint32 ep_pcie_cap, uint32 enable, uint32 aspm_type)
{
   uint32 val, host_L1ss_cap, ep_L1ss_cap, option_bits = 0, pm_type = 0;

   ep_L1ss_cap = GetCapabilityRegOffset (ep_cfg_addr, EXT_CAP_ID(PCIE_L1SS_PM_CAP_ID));
   host_L1ss_cap = GetCapabilityRegOffset (host_cfg_addr, EXT_CAP_ID(PCIE_L1SS_PM_CAP_ID));
   if ((host_L1ss_cap == 0) || (ep_L1ss_cap == 0))
   {
      AsciiPrint ("Failed to get L1ss PM capability reg %X  %X\n", host_L1ss_cap, ep_L1ss_cap);
      return PCIE_ERROR;
   }

   if (aspm_type == ASPM_TYPE_L11ss)
   {
     option_bits = L1_1_SS_BITS;
     pm_type = 1;
   }
   if (aspm_type == ASPM_TYPE_L12ss)
   {
     option_bits = L1_2_SS_BITS;
     pm_type = 2;
   }
   
   // Enable BME/MSE
   val = READ_CFG_REG(host_cfg_addr, 4);
   if (enable)
      val = ENABLE_BME_MSE(val);
   else
      val = DISABLE_BME_MSE(val);
   WRITE_CFG_REG(host_cfg_addr, 4, val);

   val = READ_CFG_REG(host_cfg_addr, host_L1ss_cap + L1_PM_SS_CAPABILITIES);
   if (ASPM_L1_SS_SUPPORTED(val, option_bits) == 0)
   {
      AsciiPrint ("Host does NOT support L1.%d %X\n", pm_type, val);
      return PCIE_ERROR;
   }

   /* Note: assuming no switches/additional ports between host and EP */
   val = READ_CFG_REG(ep_cfg_addr, ep_L1ss_cap + L1_PM_SS_CAPABILITIES);
   if (ASPM_L1_SS_SUPPORTED(val, option_bits) == 0)
   {
      AsciiPrint ("EP does NOT support L1.%d %X\n", pm_type, val);
      return PCIE_ERROR;
   }
   
   // Now enable L1ss
   val = READ_CFG_REG(host_cfg_addr, host_L1ss_cap + L1_PM_SS_CONTROL);
   if (enable)
      val = ENABLE_ASPM_L1_SS(val, option_bits);
   else
      val = DISABLE_ASPM_L1_SS(val, option_bits);
   WRITE_CFG_REG(host_cfg_addr, host_L1ss_cap + L1_PM_SS_CONTROL, val);

   val = READ_CFG_REG(ep_cfg_addr, ep_L1ss_cap + L1_PM_SS_CONTROL);
   if (enable)
      val = ENABLE_ASPM_L1_SS(val, option_bits);
   else
      val = DISABLE_ASPM_L1_SS(val, option_bits);
   WRITE_CFG_REG(ep_cfg_addr, ep_L1ss_cap + L1_PM_SS_CONTROL, val);

   if (enable)
   {
      val = READ_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL);
      val = ENABLE_ASPM_L1(val);
      WRITE_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL, val);

      val = READ_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL);
      val = ENABLE_ASPM_L1(val);
      WRITE_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL, val);
   }
   else
   {
      val = READ_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL);
      val = DISABLE_ASPM_L1(val);
      WRITE_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL, val);

      val = READ_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL);
      val = DISABLE_ASPM_L1(val);
      WRITE_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL, val);
   }

   return PCIE_SUCCESS;
}

pcie_status_t enable_disable_L0s (volatile uint32* host_cfg_addr, uint32 host_pcie_cap, volatile uint32* ep_cfg_addr, uint32 ep_pcie_cap, uint32 enable)
{
   volatile uint32 val;

   val = READ_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CAPABILITIES);
   if (ASPM_L0s_SUPPORTED(val) == 0)
   {
      AsciiPrint ("Host does NOT support L0s %X\n", val);
      return PCIE_ERROR;
   }

   /* Note: assuming no switches/additional ports between host and EP */
   val = READ_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CAPABILITIES);
   if (ASPM_L0s_SUPPORTED(val) == 0)
   {
      AsciiPrint ("EP does NOT support L0s %X\n", val);
      return PCIE_ERROR;
   }

   // Enable BME/MSE
   val = READ_CFG_REG(host_cfg_addr, 4);
   if (enable)
      val = ENABLE_BME_MSE(val);
   else
      val = DISABLE_BME_MSE(val);
   WRITE_CFG_REG(host_cfg_addr, 4, val);

   gBS->Stall (1000); // wait 1ms

   val = READ_CFG_REG(ep_cfg_addr, 4);
   if (enable)
      val = ENABLE_BME_MSE(val);
   else
      val = DISABLE_BME_MSE(val);
   WRITE_CFG_REG(ep_cfg_addr, 4, val);

   gBS->Stall (1000); // wait 1ms

   // Now enable L0s
   val = READ_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL);
   if (enable)
      val = ENABLE_ASPM_L0s(val);
   else
      val = DISABLE_ASPM_L0s(val);
   WRITE_CFG_REG(host_cfg_addr, host_pcie_cap + PCIE_CAP_LINK_CONTROL, val);

   val = READ_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL);
   if (enable)
      val = ENABLE_ASPM_L0s(val);
   else
      val = DISABLE_ASPM_L0s(val);
   WRITE_CFG_REG(ep_cfg_addr, ep_pcie_cap + PCIE_CAP_LINK_CONTROL, val);

   return PCIE_SUCCESS;
}

EFI_STATUS PollForStateChange (UINTN CoreIdx, uint32 state, uint32 max_timeout_ms, uint32* state_ptr)
{
   pcie_status_t pstatus;
   pcie_link_status_t link_status_info;

#define STALL_DURATION_MILLI_SEC    5

   max_timeout_ms += STALL_DURATION_MILLI_SEC;

   if (state_ptr)
      *state_ptr = 0;

   do
   {
      pstatus = get_link_status (CoreIdx, &link_status_info);
      if (pstatus != PCIE_SUCCESS)
         return EFI_DEVICE_ERROR;

      if (link_status_info.link_state == state)
         return EFI_SUCCESS;
      
      gBS->Stall (STALL_DURATION_MILLI_SEC * 1000);

      max_timeout_ms -= STALL_DURATION_MILLI_SEC;
   }while (max_timeout_ms);

   if (state_ptr)
      *state_ptr = state;

   return EFI_DEVICE_ERROR;
}

pcie_status_t set_ASPM (UINTN CoreIdx, volatile uint32* ep_cfg_addr, boolean Enable, uint32 aspm_type)
{
   uint32 ep_pcie_cap, host_pcie_cap, *host_cfg_addr;
   pcie_status_t pstatus;
   uint32 aspm_state = 0x11, curr_state = 0;

   if ((aspm_type == ASPM_TYPE_L12ss) || (aspm_type == ASPM_TYPE_L11ss))
   {
      aspm_state = 0x14;  // TODO: Publish LTSSM states in a common header
   }
   else if (aspm_type == ASPM_TYPE_L0s)
      aspm_state = 0x12;

   host_cfg_addr = 0;
   
   pstatus = pcie_get_cfg_space_addr (CoreIdx, 0, &host_cfg_addr);
   if (pstatus != PCIE_SUCCESS)
   {
      AsciiPrint ("Failed to get Host config space addr\n");
      return pstatus;
   }

   ep_pcie_cap = GetCapabilityRegOffset (ep_cfg_addr, PCI_PCIE_CAP_ID);
   host_pcie_cap = GetCapabilityRegOffset (host_cfg_addr, PCI_PCIE_CAP_ID);
   if ((host_pcie_cap == 0) || (ep_pcie_cap == 0))
   {
      AsciiPrint ("Failed to get PCIe capability addr %X  %X\n", host_pcie_cap, ep_pcie_cap);
      return pstatus;
   }

   if (aspm_type == 0)
   {
      enable_disable_L1ss (host_cfg_addr, host_pcie_cap, ep_cfg_addr, ep_pcie_cap, 0, ASPM_TYPE_L11ss);
      enable_disable_L1ss (host_cfg_addr, host_pcie_cap, ep_cfg_addr, ep_pcie_cap, 0, ASPM_TYPE_L12ss);
      enable_disable_L0s (host_cfg_addr, host_pcie_cap, ep_cfg_addr, ep_pcie_cap, Enable);
   }
   else if ((aspm_type == ASPM_TYPE_L11ss) || (aspm_type == ASPM_TYPE_L12ss))
   {
      enable_disable_L1ss (host_cfg_addr, host_pcie_cap, ep_cfg_addr, ep_pcie_cap, Enable, aspm_type);
   }
   else
   {
      AsciiPrint ("Invalid type specified 0x%X\n", aspm_type);
      return PCIE_ERROR;
   }

   if (Enable == 0)
      aspm_state = 0x11;

   pstatus = PollForStateChange (CoreIdx, aspm_state, 5000, &curr_state);

   if (pstatus == PCIE_SUCCESS)
   {
      AsciiPrint ("Entered into link state 0x%X\n", aspm_state);
      return PCIE_SUCCESS;
   }

   AsciiPrint ("Failed to enter into requested ASPM state 0x%X\n", curr_state);

   return PCIE_ERROR;
}

EFI_STATUS TestASPM (UINTN CoreIdx, volatile uint32* ep_cfg_addr, uint32 aspm_type)
{
   pcie_link_status_t link_status_info;
   pcie_status_t pstatus;
   int i;
   volatile uint32 val, *aspm_counters, aspm_state = 0;
   uint32 last_cnt, counter_offset = 0, curr_state = 0;

   // This works based on assumption that counters are laid out sequentially in the
   // same order as the type is defined
   aspm_counters = &link_status_info.LPM_counters[0];

   if (aspm_type == ASPM_TYPE_L11ss)
   {
      aspm_state = 0x14;  // TODO: Publish LTSSM states in a common header
      counter_offset = 1;
   }
   else if (aspm_type == ASPM_TYPE_L12ss)
   {
      aspm_state = 0x14;
      counter_offset = 2;
   }
   else if (aspm_type == ASPM_TYPE_L0s)
      aspm_state = 0x12;

   for (i = 0; i < 0x10; ++i)
   {
      // Wait for link to go into our desired state first
      pstatus = PollForStateChange (CoreIdx, aspm_state, 5000, &curr_state);
      if (pstatus != PCIE_SUCCESS)
         AsciiPrint ("Link not in correct ASPM state 0x%x (0x%x) timed out\n", curr_state, aspm_state);

      // TODO: Add a new API that can return the counters instead of overloading the link status API for counters
      pstatus = get_link_status (CoreIdx, &link_status_info);
      if (pstatus != PCIE_SUCCESS)
         return EFI_DEVICE_ERROR;

      // TODO: Fix me, use a better way aspm_counters depends on link_status_info having updated value right before this call
      //       so it requires get_link_status again
      last_cnt = aspm_counters[counter_offset];

//      ArmDataSynchronizationBarrier ();

      //read some EP config space reg to bring the link to active
      val = READ_CFG_REG(ep_cfg_addr, 0);
       // TODO: since val is not used later, CPU might jump over to call the function
	   //       Add Barrier here to see if it alleviates the problem

//      ArmDataSynchronizationBarrier ();

      pstatus = PollForStateChange (CoreIdx, aspm_state, 5000, &curr_state);
      if (pstatus != PCIE_SUCCESS)
         AsciiPrint ("Link not in correct ASPM state 0x%x (0x%x) timed out\n", curr_state, aspm_state);

      // TODO: Add a new API that can return the counters instead of overloading the link status API for counters
      pstatus = get_link_status (CoreIdx, &link_status_info);
      if (pstatus != PCIE_SUCCESS)
         return EFI_DEVICE_ERROR;

      if ((last_cnt + 1) != aspm_counters[counter_offset])
         AsciiPrint ("Transitioned multiple times around the ASPM state 0x%x, 0x%X 0x%X\n", aspm_state, last_cnt, aspm_counters[counter_offset]);
   }

   if (last_cnt == aspm_counters[counter_offset])
   {
      AsciiPrint ("L%d test failed : ASPM counters 0x%X 0x%X\n", aspm_type, last_cnt, aspm_counters[counter_offset]);
      pcie_print_aer_logs (CoreIdx, ALL_BDF_VAL);         
      return EFI_DEVICE_ERROR;
   }
   else
      AsciiPrint ("L%d test Passed. Last count : 0x%X\n", aspm_type, last_cnt);

 
   return EFI_SUCCESS;
}

EFI_STATUS RunASPMTest (UINTN CoreIdx, uint32 aspm_type)
{
   dev_handle_info_type handle_info;
   pcie_status_t pstatus;
   EFI_STATUS Status;
   volatile uint32* cfg_space_addr;

   if (CoreIdx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d", MAX_PCIE_CORES);

   Status = enumerate_pcie_port (CoreIdx);
   if (Status != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   pstatus = get_enumerated_dev_handle(CoreIdx, &handle_info);
   if (pstatus != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   gBS->Stall (1000);
   pcie_setup_aspm (CoreIdx);
   gBS->Stall (1000);
   pcie_setup_l1ss (CoreIdx);
   gBS->Stall (1000);

   cfg_space_addr = handle_info.ep_info.cfg_space;

   if (cfg_space_addr == NULL)
   {
      AsciiPrint ("Failed...!! Invalid config space address\n");

      poweroff_pcie_port (CoreIdx);
      return EFI_SUCCESS;
   }

   // disable both L1.1 and L1.2
   set_ASPM (CoreIdx, cfg_space_addr, 0, ASPM_TYPE_L11ss);
   set_ASPM (CoreIdx, cfg_space_addr, 0, ASPM_TYPE_L12ss);

   // enable L1.1 or L1.2
   pstatus = set_ASPM (CoreIdx, cfg_space_addr, 1, aspm_type);

   if (pstatus == PCIE_SUCCESS)
      TestASPM(CoreIdx, cfg_space_addr, aspm_type);

   pstatus = set_ASPM (CoreIdx, cfg_space_addr, 0, aspm_type);
   if (pstatus != PCIE_SUCCESS)
      AsciiPrint ("Failed to disable L0 ASPM\n");

   // TODO: disable ASPM 
   poweroff_pcie_port (CoreIdx);

   return EFI_SUCCESS;
}

void print_AER_reg (volatile uint32* cfg_addr, uint32 cap_offset)
{
   uint32 val, v1, v2, v3, v4;

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x4);
   AsciiPrint ("Uncorrectable Error Status : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x8);
   AsciiPrint ("Uncorrectable Error Mask : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0xC);
   AsciiPrint ("Uncorrectable Error Severity : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x10);
   AsciiPrint ("Correctable Error Status : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x14);
   AsciiPrint ("Correctable Error Mask : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x18);
   AsciiPrint ("Advanced Error Capabilities and Control : %X\n", val);

   v1 = READ_CFG_REG(cfg_addr, cap_offset + 0x1C);
   v2 = READ_CFG_REG(cfg_addr, cap_offset + 0x20);
   v3 = READ_CFG_REG(cfg_addr, cap_offset + 0x24);
   v4 = READ_CFG_REG(cfg_addr, cap_offset + 0x28);
   AsciiPrint ("Header Log Registers : %08X, %08X, %08X, %08X\n", v1, v2, v3, v4);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x2C);
   AsciiPrint ("Root Error Command : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x30);
   AsciiPrint ("Root Error Status : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x34);
   AsciiPrint ("Error Source Identification : %X\n", val);

   val = READ_CFG_REG(cfg_addr, cap_offset + 0x38);
   AsciiPrint ("TLP Prefix Log : %X\n", val);
}

pcie_status_t set_AER (volatile uint32* host_cfg_addr, volatile uint32* ep_cfg_addr, uint32 operation)
{
   uint32 host_AER_cap, ep_AER_cap;

   ep_AER_cap = GetCapabilityRegOffset (ep_cfg_addr, EXT_CAP_ID(PCIE_AER_EXT_CAP_ID));
   host_AER_cap = GetCapabilityRegOffset (host_cfg_addr, EXT_CAP_ID(PCIE_AER_EXT_CAP_ID));
   if ((host_AER_cap == 0) || (ep_AER_cap == 0))
   {
      AsciiPrint ("Failed to get AER capability reg %X  %X\n", host_AER_cap, ep_AER_cap);
      return PCIE_ERROR;
   }

   AsciiPrint ("Host side AER:\n");
   print_AER_reg(host_cfg_addr, host_AER_cap);

   AsciiPrint ("EP side AER:\n");
   print_AER_reg(ep_cfg_addr, ep_AER_cap);
   
   // TODO: yet to develop
   //val = READ_CFG_REG(host_cfg_addr, host_AER_cap);
   //WRITE_CFG_REG(host_cfg_addr, host_AER_cap, val);
   return PCIE_SUCCESS;
}

