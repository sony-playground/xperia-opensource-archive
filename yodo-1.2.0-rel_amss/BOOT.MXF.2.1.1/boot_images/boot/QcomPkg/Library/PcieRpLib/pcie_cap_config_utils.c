/**
 @file pcie_cap_config_utils.c

  Utilities used to configure PCIe capabilities in the PCIe config space using
  generic API's without any target specific information.
  (TODO: Currently its still relying on target defined registers, move to
         correct the design)

  Copyright (c) 2021 - 2022 Qualcomm Technologies, Inc.
        All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---    ------------------------------------------------------------
 02/18/21    yg      Created
=============================================================================*/

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>

#include "pcie_rp.h"
#include "pcie_rp_priv.h"
#include "pcie_reg_cfg.h"
#include "pcie_host_log.h"


#define MSI_X_ENABLE_MASK        (1 << 31)
#define MSI_ENABLE_MASK          (1 << 16)

#define PCI_MSI_CAP_ID                               (0x05)
#define PCI_PCIE_CAP_ID                              (0x10)
#define PCIE_MSIX_CAP_ID                             (0x11)

#define PCIE_L1SS_PM_EXT_CAP_ID                      (0x001E)
#define PCIE_LTR_EXT_CAP_ID                          (0x0018)
#define PCIE_AER_EXT_CAP_ID                          (0x0001)

#define PCIE_CAP_COMMON_CLK_CONFIG_BMSK                 0x40
#define PCIE_CAP_RETRAIN_LINK_BMSK                      0x20
#define PCIE_CAP_LINK_TRAINING_BMSK                     0x8000000
#define PCIE_CAP_LTR_EN_BMSK                            0x400
#define PCIE_CAP_ASPM_OPT_COMPLIANCE_BMSK               0x400000
#define PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_BMSK      0xc00
#define PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_SHFT      10

#define PCIE_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT        16
#define PCIE_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT        29

#define RETRAIN_POLL_US_100_us       100
#define RETRAIN_TIMEOUT_MS_15_ms     15

#define PCIE_CAP_CONTROL1_REG_OFFSET            0x8

#define PCIE_CAP_LINK_CAPABILITIES_OFFSET      0x0c
#define PCIE_CAP_LINK_CONTROL_OFFSET           0x10
#define PCIE_CAP_DEVICE_CONTROL2_OFFSET        0x28
#define PCIE_CAP_LINK_CAPABILITIES2_OFFSET     0x2c

/* TODO: Target specific info, move to dbi-regs.h */
#define HWIO_PCIE_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK       0x1
#define HWIO_PCIE_MISC_CONTROL_1_OFF_OFFS                       (0x8bc)


#define PARITY_ERROR_RESPONSE_REPORT    (1 << 6)
#define SERROR_ENABLE                   (1 << 8)

#define PCIE_DEVICE_CONTROL_STATUS_OFFSET    0x8

#define PCIE_CAP_CORRECTABLE_ERROR_REPORT_ENABLE      (1 << 0)
#define PCIE_CAP_NONFATAL_ERROR_REPORT_ENABLE         (1 << 1)
#define PCIE_CAP_FATAL_ERROR_REPORT_ENABLE            (1 << 2)
#define PCIE_CAP_UNSUPP_REQ_ERROR_REPORT_ENABLE       (1 << 3)

#define PCIE_CAP_ERROR_REPORT_ENABLE                           \
               (PCIE_CAP_CORRECTABLE_ERROR_REPORT_ENABLE      |\
                PCIE_CAP_NONFATAL_ERROR_REPORT_ENABLE         |\
                PCIE_CAP_FATAL_ERROR_REPORT_ENABLE            |\
                PCIE_CAP_UNSUPP_REQ_ERROR_REPORT_ENABLE)

#define AER_UNCORRECTABLE_ERROR_STATUS_REG_OFF                0x04
#define AER_UNCORRECTABLE_ERROR_STATUS_FILTER                 0x07FFF030
#define AER_UNCORRECTABLE_ERROR_MASK_REG_OFF                  0x08
#define AER_UNCORRECTABLE_ERROR_SEVERITY_REG_OFF              0x0C
#define AER_CORRECTABLE_ERROR_STATUS_REG_OFF                  0x10
#define AER_CORRECTABLE_ERROR_STATUS_FILTER                   0xF1C1
#define AER_CORRECTABLE_ERROR_MASK_REG_OFF                    0x14
#define AER_CAPABILITIES_CONTROL_REG_OFF                      0x18
#define AER_CAP_HEADER_LOGS_REG_OFF                           0x1C

#define AER_CAP_ROOT_ERR_CMD_REG_OFF                          0x2C
#define AER_CAP_ROOT_ERR_STATUS_REG_OFF                       0x30
#define AER_CAP_ROOT_ERR_STATUS_REG_FILTER                    (0x7F | (0x1F << 27))

#define AER_CAP_ERR_SRC_ID_REG_OFF                            0x34
#define AER_CAP_TLP_PREFIX_LOG_REG_OFF                        0x38

#define AER_MULT_HDR_RECORD_ECRC_GEN_CHK_CAPABLE_MASK         0x15
#define AER_MULT_HDR_RECORD_ECRC_GEN_CHK_CAPABLE_SHIFT        5

/*******************************************************************************
 *             Data structures
 ******************************************************************************/
typedef struct
{
   uint32    bit_offset;
   char*     msg_str;
}err_msg_type;

err_msg_type correctable_error_strings[] = 
{
   {0, "Receiver err"},
   {6, "Bad TLP"},
   {7, "Bad DLLP"},
   {8, "Replay_Num rollover"},
   {12, "Replay timer timeout"},
   {13, "Advisory non fatal"},
   {14, "Corrected internal err"},
   {15, "Hdr log overflow"},
};

err_msg_type uncorrectable_error_strings[] = 
{
   {4, "Data link protocol err"},
   {5, "Surprise down"},
   {12, "Poisoned TLP"},
   {13, "Flow control err"},
   {14, "Completion timeout"},
   {15, "Completer abort"},
   {16, "Unexpected completion"},
   {17, "Receiver overflow"},
   {18, "Malformed TLP"},
   {19, "ECRC err"},
   {20, "Unsupported request"},
   {21, "ACS Violation"},
   {22, "Uncorrectable internal err"},
   {23, "MC Blocked TLP"},
   {24, "AtomicOp Egress blocked"},
   {25, "TLP Prefix blocked"},
   {26, "Poisoned TLP Egress blocked"},
};

err_msg_type root_error_strings[] = 
{
   {0, "Correctable error received"},
   {1, "Multi correctable errors received"},
   {2, "Fatal/non-fatal error received"},
   {3, "Multi Fatal/non-fatal errors received"},
   {4, "First uncorrectable fatal error received"},
   {5, "Non fatal error msgs received"},
   {6, "Fatal error msgs received"},
};

/*******************************************************************************
 *             General helper functions
 ******************************************************************************/
void print_hex_data (uint64 reg_addr, uint32 bytes)
{
   uint32              reg_val, i;

   PCIE_HOST_LOG_ERROR ("Data @ : 0x%X", reg_addr);
   for (i=0; i < bytes; i += 4)
   {
      if ((i % 16) == 0)
         PCIE_HOST_LOG_ERROR ("\r\n 0x%03X ", i);

      reg_val = MmioRead32 (reg_addr + i);
      PCIE_HOST_LOG_ERROR (" 0x%08X", reg_val);
   }
   PCIE_HOST_LOG_ERROR ("\r\n");
}

// prints only the bits that have defined error message
void print_error_bit_messages (uint32 err_status, err_msg_type* err_msg_pool, uint32 count)
{
   int i, found = 0;

   if (err_status == 0)
      return;

   PCIE_HOST_LOG_ERROR ("         ");

   for (i=0; i < count; ++i)
   {
      if (err_status & (1 << err_msg_pool[i].bit_offset))
      {
         PCIE_HOST_LOG_ERROR (" %a,", err_msg_pool[i].msg_str);
         ++found;
      }
   }
   if (found)
      PCIE_HOST_LOG_ERROR ("\r\n");
}

/*******************************************************************************
 *             AER private functions
 ******************************************************************************/
static pcie_status_t get_pcie_aer_cap_addr (uint32 port_index, uint16 bdf_val, uint64* pcie_cap_addr_ptr, uint64* aer_cap_addr_ptr)
{
   pcie_status_t       status = PCIE_SUCCESS;

   if (pcie_rp_is_port_link_up (port_index) == 0)
      return PCIE_NOT_FOUND;

   status = pcie_rp_get_ext_capability (port_index, bdf_val, PCIE_AER_EXT_CAP_ID, aer_cap_addr_ptr, NULL);
   if (status != PCIE_SUCCESS)
      return status;

   status = pcie_rp_get_capability (port_index, bdf_val, PCI_PCIE_CAP_ID, pcie_cap_addr_ptr, NULL);
   if (status != PCIE_SUCCESS)
      return status;

   return PCIE_SUCCESS;
}

static pcie_status_t pcie_print_aer_logs (uint32 port_index, uint32 bdf_val)
{
   uint32              reg_val, i, ctrl;
   uint64              aer_cap_addr = 0, pcie_cap_addr = 0, reg_addr;
   pcie_status_t       status = PCIE_SUCCESS;

   status = get_pcie_aer_cap_addr (port_index, bdf_val, &pcie_cap_addr, &aer_cap_addr);
   if (status != PCIE_SUCCESS)
      return status;

   if (bdf_val == 0)
      PCIE_HOST_LOG_ERROR ("Host AERs:\r\n----------\r\n");
   else
      PCIE_HOST_LOG_ERROR ("EP AERs: 0x%X\r\n----------\r\n", bdf_val);

   reg_addr = pcie_cap_addr + PCIE_DEVICE_CONTROL_STATUS_OFFSET;
   reg_val = MmioRead32 (reg_addr);
   reg_val >>= 16;
   reg_val &= 0x7F;
   PCIE_HOST_LOG_ERROR ("   Device status : 0x%X\r\n", reg_val);

   reg_addr = aer_cap_addr + AER_CAPABILITIES_CONTROL_REG_OFF;
   ctrl = MmioRead32 (reg_addr);

   reg_addr = aer_cap_addr + AER_UNCORRECTABLE_ERROR_STATUS_REG_OFF;
   reg_val = MmioRead32 (reg_addr);
   reg_val &= AER_UNCORRECTABLE_ERROR_STATUS_FILTER;
   if (reg_val)
      MmioWrite32 (reg_addr, reg_val);

   PCIE_HOST_LOG_ERROR ("   Uncorrectable error status : 0x%X (First err bit : %d)\r\n", reg_val, (ctrl & 0x1F));
   print_error_bit_messages (reg_val, uncorrectable_error_strings, ARRAY_SIZE(uncorrectable_error_strings));

   reg_addr = aer_cap_addr + AER_CORRECTABLE_ERROR_STATUS_REG_OFF;
   reg_val = MmioRead32 (reg_addr);
   reg_val &= AER_CORRECTABLE_ERROR_STATUS_FILTER;
   if (reg_val)
      MmioWrite32 (reg_addr, reg_val);

   PCIE_HOST_LOG_ERROR ("   Correctable error status   : 0x%X\r\n", reg_val);
   print_error_bit_messages (reg_val, correctable_error_strings, ARRAY_SIZE(correctable_error_strings));


   PCIE_HOST_LOG_ERROR ("   Error TLP Hdr Log Reg      :");
   reg_addr = aer_cap_addr + AER_CAP_HEADER_LOGS_REG_OFF;
   for (i=0; i<4; ++i)
   {
      reg_val = MmioRead32 (reg_addr + (i * 4));
      PCIE_HOST_LOG_ERROR (" 0x%X ", reg_val);
   }
   PCIE_HOST_LOG_ERROR ("\r\n");

   reg_addr = aer_cap_addr + AER_CAP_ROOT_ERR_STATUS_REG_OFF;
   reg_val = MmioRead32 (reg_addr);
   reg_val &= AER_CAP_ROOT_ERR_STATUS_REG_FILTER;
   if (reg_val)
      MmioWrite32 (reg_addr, reg_val);

   PCIE_HOST_LOG_ERROR ("   Root error status          : 0x%X  (Adv Err Intr Msg %d)\r\n", reg_val, ((reg_val >> 27) & 0x1F));
   print_error_bit_messages (reg_val, root_error_strings, ARRAY_SIZE(root_error_strings));
   

   reg_addr = aer_cap_addr + AER_CAP_ERR_SRC_ID_REG_OFF;
   reg_val = MmioRead32 (reg_addr);
   if (reg_val)
      MmioWrite32 (reg_addr, reg_val);
   PCIE_HOST_LOG_ERROR ("   ERR/Corr Err src ID Reg    : 0x%X 0x%X\r\n", ((reg_val >> 16) & 0xFFFF), (reg_val & 0xFFFF));


   return PCIE_SUCCESS;
}

static pcie_status_t enable_AER (uint32 port_index, uint16 bdf_val)
{
   uint32              reg_val, cmd_val;
   uint64              reg_addr, pcie_cap_addr = 0, aer_cap_addr = 0;
   pcie_status_t       status = PCIE_SUCCESS;

   status = get_pcie_aer_cap_addr (port_index, bdf_val, &pcie_cap_addr, &aer_cap_addr);
   if (status != PCIE_SUCCESS)
      return status;

//#define ENABLE_LEGACY_PCI_ERROR_REPORTING
#ifdef ENABLE_LEGACY_PCI_ERROR_REPORTING
   /* Enable legacy PCI error reporting, Error bits showup in status register */
   reg_addr = aer_cap_addr & (~(0xFFF));

   reg_val = MmioRead32 (reg_addr);
   reg_val = reg_val | PARITY_ERROR_RESPONSE_REPORT | SERROR_ENABLE;
   MmioWrite32 (reg_addr, reg_val);

   MemoryFence ();
#endif

#define ENABLE_PCIE_ERROR_REPORTING
#ifdef ENABLE_PCIE_ERROR_REPORTING
   /* Enable PCIe error reporting, Error bits showup in Device Status register in PCIe capability */
   reg_addr = pcie_cap_addr + PCIE_DEVICE_CONTROL_STATUS_OFFSET;

   reg_val = MmioRead32 (reg_addr);
   reg_val = reg_val | PCIE_CAP_ERROR_REPORT_ENABLE;
   MmioWrite32 (reg_addr, reg_val);

   MemoryFence ();
#endif

   /* Finally enable Advanced PCIe error reporting, Error bits showup in
    * AER capability registers */

#define ENABLE_ECRC_GENERATION_AND_CHECKING
#ifdef ENABLE_ECRC_GENERATION_AND_CHECKING
   // Enable ECRC generation and checking
   reg_addr = aer_cap_addr + AER_CAPABILITIES_CONTROL_REG_OFF;

   reg_val = MmioRead32 (reg_addr);
   cmd_val = reg_val >> AER_MULT_HDR_RECORD_ECRC_GEN_CHK_CAPABLE_SHIFT;
   cmd_val &= AER_MULT_HDR_RECORD_ECRC_GEN_CHK_CAPABLE_MASK;
//   PCIE_HOST_LOG_ERROR ("Multi Hdr Recording, ECRC Check, Generation Capble : 0x%X\r\n", cmd_val);
   if (cmd_val)
   {
      cmd_val = cmd_val << 1;
      reg_val = cmd_val | reg_val;
      MmioWrite32 (reg_addr, reg_val);

      MemoryFence ();
   }
#endif

#define ENABLE_AER_INTERRUPT_GENERATION
#ifdef ENABLE_AER_INTERRUPT_GENERATION
   // Enable interrupt generation for the errors occurred.
   // TODO: This generates MSI/MSI-x, is this really needed if MSI's are not configured/enabled??
   reg_addr = aer_cap_addr + AER_CAP_ROOT_ERR_CMD_REG_OFF;

   reg_val = MmioRead32 (reg_addr);
   reg_val |= 0x7; // enable all error reports to generate interrupts.
   MmioWrite32 (reg_addr, reg_val);

   MemoryFence ();
#endif

   // TODO: Unmask if something is masked?

   return PCIE_SUCCESS;
}

/*******************************************************************************
 *             AER Public functions
 ******************************************************************************/
pcie_status_t pcie_rp_setup_aer (uint32 port_index, uint16 bdf_val, int enable)
{
   pcie_status_t       status = PCIE_SUCCESS;

   if (bdf_val != ALL_BDF_VAL)
   {
      status = enable_AER (port_index, bdf_val);
      return status;
   }

   status = enable_AER (port_index, HOST_BDF_VAL);
   if (status != PCIE_SUCCESS)
      return status;

   status = enable_AER (port_index, EP_BDF_VAL);
   if (status != PCIE_SUCCESS)
      return status;

//#define PRINT_AER_STATE_ON_INIT
#ifdef PRINT_AER_STATE_ON_INIT
   PCIE_HOST_LOG_ERROR ("AER state on setup: BDF 0x%X\r\n", HOST_BDF_VAL);
   pcie_rp_print_aer_logs (port_index, HOST_BDF_VAL);
#endif

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_print_aer_logs (uint32 port_index, uint16 bdf_val)
{
   pcie_status_t       status = PCIE_SUCCESS;

   if (bdf_val != ALL_BDF_VAL)
      return pcie_print_aer_logs (port_index, bdf_val);

   status = pcie_print_aer_logs (port_index, HOST_BDF_VAL);
   status = pcie_print_aer_logs (port_index, EP_BDF_VAL);

   return status;
}

/*******************************************************************************
 *             MSI, MSI-X
 ******************************************************************************/
pcie_status_t pcie_cap_disable_MSIs (uint32 port_index)
{
   uint32              reg_val;
   uint64              ep_cap_addr;
   pcie_status_t       status = PCIE_SUCCESS;

   if (pcie_rp_is_port_link_up (port_index) == 0)
      return PCIE_NOT_FOUND;

   status = pcie_rp_get_capability (port_index, EP_BDF_VAL, PCIE_MSIX_CAP_ID, &ep_cap_addr, NULL);
   if (status == PCIE_SUCCESS)
   {
      reg_val = MmioRead32 (ep_cap_addr);
      reg_val = reg_val & (~(MSI_X_ENABLE_MASK));
      MmioWrite32 (ep_cap_addr, reg_val);

      MemoryFence ();
   }

   status = pcie_rp_get_capability (port_index, EP_BDF_VAL, PCI_MSI_CAP_ID, &ep_cap_addr, NULL);
   if (status == PCIE_SUCCESS)
   {
      reg_val = MmioRead32 (ep_cap_addr);
      reg_val = reg_val & (~(MSI_ENABLE_MASK));
      MmioWrite32 (ep_cap_addr, reg_val);

      MemoryFence ();
   }

   return PCIE_SUCCESS;
}

/*******************************************************************************
 *                         Link state
 ******************************************************************************/
pcie_status_t pcie_cap_get_link_stat (uint32 port_index, uint32* widthp, uint32* speedp)
{
   uint64    host_cap_addr = 0;
   uint32    link_ctrl_status;
   uint32    link_width, link_speed;
   pcie_status_t       status = PCIE_SUCCESS;

   status = pcie_rp_get_capability (port_index, HOST_BDF_VAL, PCI_PCIE_CAP_ID, &host_cap_addr, NULL);
   if (status != PCIE_SUCCESS)
      return status;

   link_ctrl_status = MmioRead32 (host_cap_addr + PCIE_CAP_LINK_CONTROL_OFFSET);

   link_width = ((link_ctrl_status >> 20) & 0x3F);  // Negotiated link width @ bit 20
   link_speed = ((link_ctrl_status >> 16) & 0xF);;

   if (widthp)
      *widthp = link_width;

   if (speedp)
      *speedp = link_speed;

   return PCIE_SUCCESS;
}

/*******************************************************************************
 *                         ASPM
 ******************************************************************************/
const pcie_port_config_t * pcie_rp_get_port_config (uint32 port_index);

pcie_status_t pcie_rp_setup_aspm (uint32 port_index)
{
   uint32                      TempReg, AspmSetting;
   uint64                      ep_cap_addr = 0;
   uint64                      host_cap_addr = 0;
   pcie_status_t               status = PCIE_SUCCESS;
   const mem_region_t*         port_mem;
   const pcie_port_config_t*   port_cfg;

   if (pcie_rp_is_port_link_up (port_index) == 0)
      return PCIE_NOT_READY;

   port_cfg = pcie_rp_get_port_config (port_index);

   if (port_cfg == NULL)
      return PCIE_NOT_FOUND;

   port_mem = port_cfg->port_mem_bases; // TODO: use only until a new API to get Config space addr

   status = pcie_rp_get_capability (port_index, HOST_BDF_VAL, PCI_PCIE_CAP_ID, &host_cap_addr, NULL);

   if (status != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_HIGH ("No PCIe Cap for Host on PCI%d\r\n", port_index);
      return PCIE_SUCCESS;
   }

   status = pcie_rp_get_capability (port_index, EP_BDF_VAL, PCI_PCIE_CAP_ID, &ep_cap_addr, NULL);

   if (status != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("No PCIe Cap on EP PCI%d\r\n", port_index);
      return PCIE_SUCCESS;  // may be device doesn't support?
   }

   /* Perform Common Clock Configuration and Link Retrain
    * before enabling ASPM */

   /* Enable Common Clock Configuration for Root port */
   MmioOr16(host_cap_addr + PCIE_CAP_LINK_CONTROL_OFFSET, PCIE_CAP_COMMON_CLK_CONFIG_BMSK);

   /* Enable Common Clock Configuration for End Point */
   MmioOr16(ep_cap_addr + PCIE_CAP_LINK_CONTROL_OFFSET, PCIE_CAP_COMMON_CLK_CONFIG_BMSK);

   /* Re-Train the link */
   MmioOr16(host_cap_addr + PCIE_CAP_LINK_CONTROL_OFFSET, PCIE_CAP_RETRAIN_LINK_BMSK);

   /* Wait for link to retrain */
   // TODO: Why ignore return val?!!
   pcie_poll_field_val (host_cap_addr + PCIE_CAP_LINK_CONTROL_OFFSET,
                        PCIE_CAP_LINK_TRAINING_BMSK, 0,
                        RETRAIN_POLL_US_100_us, RETRAIN_TIMEOUT_MS_15_ms);

   /* PCIE_1_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1.PCIE_CAP_LTR_EN Enable */
   TempReg =  PCIE_CAP_LTR_EN_BMSK;
   MmioOr32(ep_cap_addr + PCIE_CAP_DEVICE_CONTROL2_OFFSET, TempReg);

   /* PCIE_1_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1.PCIE_CAP_LTR_EN Enable */
   TempReg =  PCIE_CAP_LTR_EN_BMSK;
   MmioOr32(host_cap_addr + PCIE_CAP_DEVICE_CONTROL2_OFFSET, TempReg);

   /* Enable DBI_RO_WR_EN to access CS1 region
    * TODO: Detach from DBI_RO_WR_EN dependency and add rp based API to handle this.
    *       this should solve both target specific header file and config related
    *       dependencies for this high level target independent file  */
   MmioWrite32 ((HWIO_OFFS (PCIE_MISC_CONTROL_1_OFF) + port_mem[axi_reg].pa),
                HWIO_PCIE_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK);

   MemoryFence ();

   /* Optionality Compliance */
   TempReg = MmioRead32 (host_cap_addr + PCIE_CAP_LINK_CAPABILITIES_OFFSET);
   TempReg |= PCIE_CAP_ASPM_OPT_COMPLIANCE_BMSK;

   /* clear AS_LINK_PM_SUPT */
   TempReg = TempReg & (~(uint32)(PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_BMSK));

   /* Disable L0s & Enable L1 TODO: Detach from target specific direct config reference */
   AspmSetting = PORT_ATTRIB_ASPM_SETTING(port_cfg);
   TempReg = TempReg | (AspmSetting << PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_SHFT);
   MmioWrite32 (host_cap_addr + PCIE_CAP_LINK_CAPABILITIES_OFFSET, TempReg);

   /* Disable DBI_RO_WR_EN bit to access CS1 region */
   MmioWrite32 ((HWIO_OFFS (PCIE_MISC_CONTROL_1_OFF) + port_mem[axi_reg].pa),
                !(HWIO_PCIE_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK));

   MemoryFence ();

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_setup_l1ss (uint32 port_index)
{
   uint32                   rp_L1_cap, ep_L1_cap, L1_cap;
   uint64                   rp_l1ss_cap_addr = 0;
   uint64                   ep_L1ss_cap_addr = 0;
   pcie_status_t            status = PCIE_SUCCESS;
   ltr_threshold_scale_t    LTR_scale = 0;
   uint32                   LTR_val = 0;
//   uint64                   ep_LTR_cap_addr = 0;

   if (pcie_rp_is_port_link_up (port_index) == 0)
      return PCIE_NOT_READY;

   status = pcie_rp_get_ext_capability (port_index, HOST_BDF_VAL, PCIE_L1SS_PM_EXT_CAP_ID, &rp_l1ss_cap_addr, NULL);
  
   if (status != PCIE_SUCCESS)
     return status;
  
   rp_L1_cap = MmioRead32(rp_l1ss_cap_addr + 4);
  
   status = pcie_rp_get_ext_capability (port_index, EP_BDF_VAL, PCIE_L1SS_PM_EXT_CAP_ID, &ep_L1ss_cap_addr, NULL);
  
   if (status != PCIE_SUCCESS)
     return status;
  
   ep_L1_cap = MmioRead32(ep_L1ss_cap_addr + 4);
  
   /* Enable the common states bwtween EP & RP from the following:
    * L1_2_PCIPM_EN | L1_1_PCIPM_EN | L1_2_ASPM_EN | L1_1_ASPM_EN */
   L1_cap = ((ep_L1_cap & rp_L1_cap) & 0xF);
  
   /* Clear the L1ss Enable Bits */
   MmioAnd32(rp_l1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET, ~0xF);

   LTR_scale = pcie_rp_get_ltr_th_scale (port_index);
   LTR_val =  pcie_rp_get_ltr_th_val (port_index);
  
   if ((LTR_val != 0) || (LTR_scale != 0))
   {
      /* Write LTR Threshold value and scale */
      MmioBitFieldWrite32 (rp_l1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT + 9,
                           LTR_val);
   
      MmioBitFieldWrite32 (rp_l1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT + 2,
                           LTR_scale);
   }

   /* Enable L1ss */
   MmioOr32 (rp_l1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET, L1_cap);
  
   /* Endpoint L1ss should be enable only after the Root port L1ss is enabled */
   MemoryFence ();
  
   /* Clear the L1ss Enable Bits */
   MmioAnd32 (ep_L1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET, ~0xF);
  
   if ((LTR_val != 0) || (LTR_scale != 0))
   {
      /* Write LTR Threshold value and scale */
      MmioBitFieldWrite32 (ep_L1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT + 9,
                           LTR_val);
   
      MmioBitFieldWrite32 (ep_L1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT,
                           PCIE_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT + 2,
                           LTR_scale);
   
#ifdef ENABLE_LTR_SNOOP_VAL_SETTING
      status = pcie_rp_get_ext_capability (port_index, EP_BDF_VAL, PCIE_LTR_EXT_CAP_ID,
                                              &ep_LTR_cap_addr, NULL);
      if (status == PCIE_SUCCESS)
      {
         uint32  snoopreg, max_snoop;
   
         /* TODO: Determine max snoop value from system response spec */
         max_snoop = LTR_val + 1;
   
         if (max_snoop >= (1 << 10))
            max_snoop = ((1 << 10) - 1);
   
         snoopreg = (LTR_scale << 10) | max_snoop;
         snoopreg = snoopreg | (snoopreg << 16);
   
         MmioWrite32 (ep_LTR_cap_addr + 4, snoopreg);
      }
#endif
   }
  
   /* Enable L1ss */
   MmioOr32(ep_L1ss_cap_addr + PCIE_CAP_CONTROL1_REG_OFFSET, L1_cap);

   return status;
}

void pcie_link_transition_L23 (void)
{
#if 0
      MmioOr32(mem[ahb_reg].va + HWIO_OFFS(PCIE_PARF_SYS_CTRL),
               HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_BMSK);

      MmioOr32(mem[axi_reg].va + HWIO_OFFS(PCIE_ELBI_SYS_CTRL),
               HWIO_PCIE_ELBI_SYS_CTRL_PME_TURNOFF_MSG_BMSK);

      /*
       * Check if the link is in L2 already
       */
      PcieConfigLibPollBitMsk(mem[ahb_reg].va + HWIO_OFFS(PCIE_PARF_PM_STTS),
                              HWIO_PCIE_PARF_PM_STTS_PM_LINKST_IN_L2_BMSK,
                              TRUE,
                              100); => how many 1ms loops to timeout
#endif
}


