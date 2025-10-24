/**
  @file pcie_root_port.c
  @brief Pcie Root Port configuration/mgmt interface implementation

  This file implements QC specific PCIe root port controller configuration
===============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/QcomBaseLib.h>
#include "pcie_rp.h"
#include "pcie_rp_priv.h"
#include "pcie_cfg_types.h"
#include "pcie_rp_cfg_svc.h"
#include "pcie_reg_cfg.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "pcie_reg_offsets.h"
#include "pcie_cap_config_utils.h"

#define PCIE_CONTEXT_SIGNATURE    ('R' | ('P' << 8) | ('c' << 16) | ('x' << 24))

#ifndef MAX_CAPABILITY_CACHE
#define MAX_CAPABILITY_CACHE    16
#endif

typedef enum
{
    PORT_NOT_AVAILABLE            = 0,
    PORT_CONTROLLER_DOWN          = 0,
    PORT_RESOURCES_INITIALIZED    = 1,
    PORT_PHY_INITIALIZED          = 2,
    PORT_LINK_TRAINING_STARTED    = 3,
    PORT_LINK_TRAINING_FAILED     = 4,
    PORT_LINK_UP                  = 5,
    PORT_HOST_CTRL_INITIALIZED    = 6,
    PORT_PORT_READY               = 7,
    PORT_LINK_IN_LPM              = 8,
    PORT_LINK_IN_POWER_COLLAPSE   = 9,
    PORT_CONTEXT_NOT_ASSIGNED     = 0xFFFF,
}pcie_port_state_type_t;

struct __pcie_rp_ctxt
{
  uint32                      port_index;
  uint32                      port_state;
  const pcie_port_config_t *  port_config;
  pcie_resources_ctxt_t       rsrc_ctxt;
  uint64                      host_config_addr;     // TODO: Make it va
  uint64                      ep_config_addr;       // TODO: Make it va
  uint64                      ahb_base_addr;       // TODO: Make it va
  uint64                      axi_base_addr;       // TODO: Make it va
  uint64                      axi_space_size;
  uint32                      host_capability_cache[MAX_CAPABILITY_CACHE];
  uint32                      ep_capability_cache[MAX_CAPABILITY_CACHE];
};


/* Different types of TLPs*/
typedef enum {
   PCIE_TLP_MEM_REQ       = 0x00,  /* Memory Read/Write TLP */
   PCIE_TLP_MEMRD_LOCK    = 0x01,  /* Memory Read Lock TLP */
   PCIE_TLP_IORW          = 0x02,  /* IO Read Write TLP */
   PCIE_TLP_TYPE0_CFG_RW  = 0x04,  /* Type 0 Config Read Write TLP */
   PCIE_TLP_TYPE1_CFG_RW  = 0x05,  /* Type 1 Config Read Write TLP */
} pcie_tlp_type_t;

typedef enum
{
   AtuSlotNonPrefMemOut   = 0,
   AtuSlotPrefMemOut      = 1,
   AtuSlotCfgOut          = 2,
   AtuSlotIoOut           = 3,
   AtuSlotMemIn           = 4,
   MaxAtuAssigned         = 5
} pcierc_atu_slot_t;

typedef enum{
    LTSSM_DETECT_QUIET      = 0x00,
    LTSSM_DETECT_ACT        = 0x01,
    LTSSM_POLL_ACTIVE       = 0x02,
    LTSSM_POLL_COMPLIANCE   = 0x03,
    LTSSM_POLL_CONFIG       = 0x04,
    LTSSM_PRE_DETECT_QUIET  = 0x05,
    LTSSM_DETECT_WAIT       = 0x06,
    LTSSM_CFG_LINKWD_START  = 0x07,
    LTSSM_CFG_LINKWD_ACEPT  = 0x08,
    LTSSM_CFG_LANENUM_WAIT  = 0x09,
    LTSSM_CFG_LANENUM_ACEPT = 0x0a,
    LTSSM_CFG_COMPLETE      = 0x0b,
    LTSSM_CFG_IDLE          = 0x0c,
    LTSSM_RCVRY_LOCK        = 0x0d,
    LTSSM_RCVRY_SPEED       = 0x0e,
    LTSSM_RCVRY_RCVRCFG     = 0x0f,
    LTSSM_RCVRY_IDLE        = 0x10,
    LTSSM_L0                = 0x11,
    LTSSM_L0S               = 0x12,
    LTSSM_L123_SEND_EIDLE   = 0x13,
    LTSSM_L1_IDLE           = 0x14,
    LTSSM_L2_IDLE           = 0x15,
    LTSSM_L2_WAKE           = 0x16,
    LTSSM_DISABLED_ENTRY    = 0x17,
    LTSSM_DISABLED_IDLE     = 0x18,
    LTSSM_DISABLED          = 0x19,
    LTSSM_LPBK_ENTRY        = 0x1a,
    LTSSM_LPBK_ACTIVE       = 0x1b,
    LTSSM_LPBK_EXIT         = 0x1c,
    LTSSM_LPBK_EXIT_TIMEOUT = 0x1d,
    LTSSM_HOT_RESET_ENTRY   = 0x1e,
    LTSSM_HOT_RESET         = 0x1f,
    LTSSM_RCVRY_EQ0         = 0x20,
    LTSSM_RCVRY_EQ1         = 0x21,
    LTSSM_RCVRY_EQ2         = 0x22,
    LTSSM_RCVRY_EQ3         = 0x23,

 	LTSSM_INVALID = 0xFFFFFFFF,
} ltssm_state_t;

/* Location[23:12], CapID[11:0] */
#define CAP_INFO_CACHE(Loc,id)  (((Loc & 0xFFF) << 12) | (id & 0xFFF))

/* ExtCap[31], Ver[27:24], Location[23:12], CapID[11:0] */
#define EXT_CAP_INFO_CACHE(ver,Loc,id)  ((1 << 31) | ((ver & 0xF) << 24) | ((Loc & 0xFFF) << 12) | (id & 0xFFF))

#define IS_EXT_CAP(c)  ((c) & (1 << 31))
#define GET_CAP_ID(c)  ((c) & 0xFFF)
#define GET_CAP_LOCATION(c)  (((c) >> 12) & 0xFFF)
#define GET_CAP_VER(c)  (((c) >> 24) & 0xF)

pcie_rp_handle pcie_rp_ctxt[PCIE_MAX_ENABLED_ROOT_PORTS];

#define PCIE_SINGLE_BUS_ADDR_SPACE_SIZE                  (0x100000)
#define PCIE_CONFIG_SPACE_LENGTH                         (0x1000)

#define CAP_ID_PM       0x01
#define CAP_ID_MSI      0x05
#define CAP_ID_PCIE     0x10
#define CAP_ID_MSIX     0x11

#define EXT_CAP_ID_AER        0x01
#define EXT_CAP_ID_TPH        0x17
#define EXT_CAP_ID_LTR        0x18
#define EXT_CAP_ID_SEC_PCIE   0x19
#define EXT_CAP_ID_L1SS_PM    0x1E

#define MAX_PORTS_LINKUP_TIMEOUT_MS         250

#define CLEAR_BIT(dst,bit)     (dst & (~(1 << bit)))

#define EP_CFG_SPACE      0
#define HOST_CFG_SPACE    1

#define GET_CAP           0
#define GET_EXT_CAP       1

#define PORT_IS_DISABLED(h) (h->port_state == PORT_NOT_AVAILABLE)

#define CHECK_PORT_HAS(h,bitn)   (h->port_state & (1 << bitn))

#define PORT_COMPLETED(h,bitn)                                do \
            {                                                        \
                if ((bitn == PORT_CONTROLLER_DOWN) ||                \
                    (h->port_state == (1 << PORT_CONTROLLER_DOWN)))  \
                   h->port_state = (1 << bitn);                      \
                else                                                 \
                   h->port_state |= (1 << bitn);                     \
            }while(0)


#if 0

void MmioOr32 (uint64 addr, uint32 val)
{
   uint32 reg = *(volatile uint32*)addr;

   reg = reg | val;

   *(volatile uint32*)addr = reg;
}

void MmioWrite32 (uint64 addr, uint32 val)
{
   *((volatile uint32*)addr) = val;
}

#endif

/******************************************************************************
 *         Private functions
 ******************************************************************************/

/* Offset, Mask and Shift macro to be used with HWIO macros */
#define PCIE_OMS(reg, field)  HWIO_OFFS(reg), HWIO_FMSK(reg,field), HWIO_SHFT(reg,field)

static 
uint32 read_reg_field (uint64_t base, uint32 offset, uint32 mask, uint32 shift)
{
   uint64_t addr = base + offset;
   uint32 regval = (*((volatile uint32 *)(addr)));

   regval &= mask;
   regval >>= shift;
   return regval;
}

static pcie_status_t setup_ecam_blocker (pcie_rp_handle* rp_handle, uint32 port_link_is_up)
{
   UINT32               block_cmd = 0;
   UINT64               blocking_start, blocking_end;
   UINT64               axi_base_pa, ahb_base_pa;
   const mem_region_t*  port_mem;

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
     return PCIE_INVALID_PARAM;

   port_mem = rp_handle->port_config->port_mem_bases;
   axi_base_pa = port_mem[axi_reg].pa;
   ahb_base_pa = port_mem[ahb_reg].pa;

/* This is required if we don't have enough space in for BAR's in the lower space 32 bit region.
 * TODO: Eval if required to enable this for external GPU usecase, also check to see if we can
 *       conditionalize this to ahb space being 64 bit to simplify solution */
//#define REMAP_DBI_SPACE_TO_HIGH_MEM_LOCATION
#ifdef REMAP_DBI_SPACE_TO_HIGH_MEM_LOCATION
   MmioWrite32((HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE) + port_mem[ahb_reg].pa), (UINT32)0);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE_HI) + port_mem[ahb_reg].pa), (UINT32)0x200);

   MmioWrite32((HWIO_OFFS(PCIE_PARF_DBI_BASE_ADDR) + port_mem[ahb_reg].pa), (UINT32)port_mem[axi_reg].pa);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_ATU_BASE_ADDR_LO) + port_mem[ahb_reg].pa), (UINT32)port_mem[axi_reg].pa + 0x1000);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_DMA_BASE_ADDR_LO) + port_mem[ahb_reg].pa), (UINT32)port_mem[axi_reg].pa + 0x2000);
#endif

   /* ECAM base */
   MmioWrite32((HWIO_OFFS(PCIE_PARF_ECAM_BASE) + ahb_base_pa),
              (UINT32)axi_base_pa);

   /* ECAM blocker wr & rd base for RC */
   // blocking_start, , allow_start, allow_end;

   blocking_start = axi_base_pa + PCIE_CONFIG_SPACE_LENGTH;
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_BASE) + ahb_base_pa),
              (UINT32)blocking_start);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_BASE_HI) + ahb_base_pa),
              (UINT32)(blocking_start >> 32));

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_BASE) + ahb_base_pa),
              (UINT32)blocking_start);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_BASE_HI) + ahb_base_pa),
              (UINT32)(blocking_start >> 32));

   block_cmd |= HWIO_PCIE_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK;

   /* ECAM blocker wr & rd limit for RC */
   if (port_link_is_up == TRUE)
   {
      blocking_end = axi_base_pa + (PCIE_SINGLE_BUS_ADDR_SPACE_SIZE - 1);
      block_cmd |= HWIO_PCIE_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_BMSK;
   }
   else
   {
      /* Hide the entire PCIe AXI range starting from Root complex
       * ECAM end, since there will be no endpoint to access */
      blocking_end = axi_base_pa + (port_mem[axi_reg].sz - 1);
   }

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_LIMIT) + ahb_base_pa),
              (UINT32)blocking_end);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI) + ahb_base_pa),
              (UINT32)(blocking_end >> 32));

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_LIMIT) + ahb_base_pa),
              (UINT32)blocking_end);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI) + ahb_base_pa),
              (UINT32)(blocking_end >> 32));

   /* ECAM blocker wr & rd base for EP */
   blocking_start = axi_base_pa + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE + PCIE_CONFIG_SPACE_LENGTH;
   blocking_end = axi_base_pa + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE + (PCIE_SINGLE_BUS_ADDR_SPACE_SIZE - 1);

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_BASE_2) + ahb_base_pa),
              (UINT32)blocking_start);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI) + ahb_base_pa),
              (UINT32)(blocking_start >> 32));

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_BASE_2) + ahb_base_pa),
              (UINT32)blocking_start);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI) + ahb_base_pa),
              (UINT32)(blocking_start >> 32));

   /* ECAM blocker wr & rd limit for EP */
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_LIMIT_2) + ahb_base_pa),
              (UINT32)blocking_end);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI) + ahb_base_pa),
              (UINT32)(blocking_end >> 32));

   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_LIMIT_2) + ahb_base_pa),
              (UINT32)blocking_end);
   MmioWrite32((HWIO_OFFS(PCIE_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI) + ahb_base_pa),
              (UINT32)(blocking_end >> 32));

   /* Enable ECAM blocker regions in the end after the configurations */
   MmioOr32((HWIO_OFFS(PCIE_PARF_SYS_CTRL) + ahb_base_pa), block_cmd);

   return PCIE_SUCCESS;
}

pcie_status_t configure_iatu (uint64                     axi_base_addr,
                              uint64                     axi_space_size,
                              pcierc_atu_slot_t          atu_idx,
                              pcie_tlp_type_t            tlp_type,
                              uint64                     rc_addr_base,
                              uint64                     rc_addr_limit,
                              uint64                     tlp_addr)
{
   uint32 incr_rgn_size = 0;
   uint64 axi_limit = 0;

   if ((axi_base_addr == 0) || (atu_idx >= MaxAtuAssigned))
     return PCIE_INVALID_PARAM;

   /* Step 1. Setup the Region Base and Limit Address Registers. */
   MmioWrite32((HWIO_PCIE_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)rc_addr_base);
   MmioWrite32((HWIO_PCIE_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)(rc_addr_base >> 32));
   MmioWrite32((HWIO_PCIE_IATU_LIMIT_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)rc_addr_limit);
   MmioWrite32((HWIO_PCIE_IATU_UPPR_LIMIT_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)(rc_addr_limit >> 32));

   /* Step 2. Setup the Target Address Registers. */
   MmioWrite32((HWIO_PCIE_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)tlp_addr);
   MmioWrite32((HWIO_PCIE_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              (UINT32)(tlp_addr >> 32));

   axi_limit = axi_base_addr + axi_space_size;

   if (rc_addr_base >= axi_limit)  // TODO: Do elaborate check within range of the entry to decide
      incr_rgn_size = HWIO_PCIE_IATU_REGION_CTRL_1_OFF_OUTBOUND_a_INCREASE_REGION_SIZE_BMSK;

   /* Step 3. Configure the region through the Region Control 1 Register. */
   MmioWrite32((HWIO_PCIE_IATU_REGION_CTRL_1_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              tlp_type | incr_rgn_size);

   /* Step 4. Enable the region. */
   MmioWrite32((HWIO_PCIE_IATU_REGION_CTRL_2_OFF_OUTBOUND_a_OFFS(atu_idx) + axi_base_addr),
              HWIO_PCIE_IATU_REGION_CTRL_2_OFF_OUTBOUND_a_REGION_EN_BMSK);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_disable_ob_iatu (UINT64 axi_base_addr, pcierc_atu_slot_t atu_idx)
{
   uint32 val;

   if ((axi_base_addr == 0) || (atu_idx >= MaxAtuAssigned))
     return PCIE_INVALID_PARAM;

   /* Disable the region. */
   val = MmioRead32 ((HWIO_PCIE_IATU_REGION_CTRL_2_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr));

   val &= (~HWIO_PCIE_IATU_REGION_CTRL_2_OFF_OUTBOUND_a_REGION_EN_BMSK);
   MmioWrite32((HWIO_PCIE_IATU_REGION_CTRL_2_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), val);

   /* Clear all Region Base, Limit and Target Address Registers. */
   MmioWrite32((HWIO_PCIE_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), 0);
   MmioWrite32((HWIO_PCIE_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), 0);
   MmioWrite32((HWIO_PCIE_IATU_LIMIT_ADDR_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), 0);
   MmioWrite32((HWIO_PCIE_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), 0);
   MmioWrite32((HWIO_PCIE_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_a_OFFS (atu_idx) + axi_base_addr), 0);

   return PCIE_SUCCESS;
}


/* TODO: get this from caller to support multiple bus levels for switch */
#define TLP_BUS_NUMBER_1        1

pcie_status_t pcie_rp_setup_config_space_ATU  (pcie_rp_handle* rp_handle)
{
   uint64               ep_cfg_addr_base, ep_cfg_addr_limit;
   pcie_status_t        pstatus;

   if (rp_handle == NULL)
     return PCIE_INVALID_PARAM;

   // TODO: determine address based off of the bus number as well
   ep_cfg_addr_base = rp_handle->axi_base_addr + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE;
   ep_cfg_addr_limit = ep_cfg_addr_base + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE - 1;

   rp_handle->host_config_addr = rp_handle->axi_base_addr;
   rp_handle->ep_config_addr = ep_cfg_addr_base;

   pstatus = configure_iatu (rp_handle->axi_base_addr, rp_handle->axi_space_size, AtuSlotCfgOut, PCIE_TLP_TYPE0_CFG_RW,
                            ep_cfg_addr_base, ep_cfg_addr_limit, (TLP_BUS_NUMBER_1 << 24));

   if (pstatus != PCIE_SUCCESS)
      PCIE_HOST_LOG_ERROR ("ATU Config Setup Failed\r\n");

   return pstatus;
}

typedef enum
{
   PHY_INIT_SETTINGS   = 0,
   PHY_DEINIT_SETTINGS = 1,
   PHY_LOOPBACK_ENABLE_SETTINGS = 2,
   PHY_LOOPBACK_DISABLE_SETTINGS = 3,
}pcie_phy_seq_type;

pcie_status_t apply_phy_settings (pcie_rp_handle* rp_handle, pcie_phy_seq_type seq_type)
{
   const pcie_reg_init_cfg_t* phy_seq_cfg;
   const mem_region_t* port_mem_regions;
   pcie_status_t pstatus;
   const pcie_port_config_t* port_config;
   const pcie_loopback_cfg_t *loopback_cfg;

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
     return PCIE_INVALID_PARAM;

   port_config = rp_handle->port_config;

   if (port_config->port_mem_bases == NULL)
      return PCIE_NOT_FOUND;

   /* TODO: Optimize this by storing VA mem region in the context */
   port_mem_regions = port_config->port_mem_bases;

   switch (seq_type)
   {
      case PHY_INIT_SETTINGS:
         phy_seq_cfg = port_config->port_phy_init_cfg;
         break;

      case PHY_DEINIT_SETTINGS:
         phy_seq_cfg = port_config->port_phy_deinit_cfg;
         break;

      case PHY_LOOPBACK_ENABLE_SETTINGS:
         loopback_cfg = port_config->loopback_cfg;
         if (loopback_cfg == NULL)
            return PCIE_NOT_FOUND;

         phy_seq_cfg = loopback_cfg->loopback_enable_cfg;
         break;

      case PHY_LOOPBACK_DISABLE_SETTINGS:
         loopback_cfg = port_config->loopback_cfg;
         if (loopback_cfg == NULL)
            return PCIE_NOT_FOUND;

         phy_seq_cfg = loopback_cfg->loopback_disable_cfg;
         break;

      default: 
         return PCIE_INVALID_PARAM;
   }

   pstatus = apply_reg_init_cfg (phy_seq_cfg, port_mem_regions);

   return pstatus;
}

pcie_status_t start_link_training (pcie_rp_handle* rp_handle)
{
   uint64_t parf_va;
   uint32 temp;

   if (rp_handle == NULL)
      return PCIE_ERROR;

   if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
      return PCIE_SUCCESS;

   if (CHECK_PORT_HAS(rp_handle, PORT_PHY_INITIALIZED) == 0)
      return PCIE_ERROR;

   parf_va = OSAL_CONVERT_PA_TO_VA(rp_handle->ahb_base_addr);

   do
   {
     temp = *((volatile uint32*)(HWIO_OFFS(PCIE_PARF_LTSSM) + parf_va));
     temp |= HWIO_PCIE_PARF_LTSSM_LTSSM_EN_BMSK;
     *((volatile uint32*)(HWIO_OFFS(PCIE_PARF_LTSSM) + parf_va)) = temp;
     temp = *((volatile uint32*)(HWIO_OFFS(PCIE_PARF_LTSSM) + parf_va));
   } while (!(temp & HWIO_PCIE_PARF_LTSSM_LTSSM_EN_BMSK));

   pcie_osal_memory_barrier ();

   PORT_COMPLETED (rp_handle, PORT_LINK_TRAINING_STARTED); 

   return PCIE_SUCCESS;
}

static ltssm_state_t read_ltssm_state (pcie_rp_handle* rp_handle)
{
   uint64_t parf_va;
   uint32 val;

   if (rp_handle == NULL)
      return LTSSM_INVALID;

   parf_va = OSAL_CONVERT_PA_TO_VA(rp_handle->ahb_base_addr);

   val = read_reg_field (parf_va, PCIE_OMS (PCIE_PARF_LTSSM, LTSSM_STATE));

   return val;
}

uint32 check_if_linkup (pcie_rp_handle* rp_handle)
{
   uint32 val;
   uint64_t parf_va, dbi_va;

   if (rp_handle == NULL)
      return 0;

   parf_va = OSAL_CONVERT_PA_TO_VA(rp_handle->ahb_base_addr);
   dbi_va = OSAL_CONVERT_PA_TO_VA(rp_handle->axi_base_addr);

   val = read_reg_field (parf_va, PCIE_OMS (PCIE_PARF_PM_STTS, XMLH_LINK_UP));
   if (val == 0)
      return 0;

   val = read_reg_field (dbi_va, PCIE_OMS (PCIE_LINK_CONTROL_LINK_STATUS_REG, PCIE_CAP_DLL_ACTIVE));
   if (val == 0)
      return 0;

   val = *((volatile uint32*)dbi_va);  // DEV_ID_VEND_ID_DBI_OFFSET TODO: Is this needed?
   if (val == 0xFFFFFFFF)
      return 0;

   return 1;
}

pcie_status_t pcie_rp_init_tunnelled_port (pcie_rp_handle* rp_handle)
{
   if (rp_handle == NULL)
      return PCIE_ERROR;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_deinit_tunnelled_port (pcie_rp_handle* rp_handle)
{
   if (rp_handle == NULL)
      return PCIE_ERROR;

   return PCIE_SUCCESS;
}

#define PHY_DEINIT    0
#define PHY_INIT      1

pcie_status_t pcie_rp_init_port_resources (pcie_rp_handle* rp_handle)
{
   pcie_status_t pstatus;

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
      return PCIE_ERROR;

   if (CHECK_PORT_HAS(rp_handle, PORT_RESOURCES_INITIALIZED))
      return PCIE_SUCCESS;

   pstatus = enable_pcie_resources (&rp_handle->rsrc_ctxt, rp_handle->port_config);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   pcie_osal_busywait_us (100); // Clks settle

   if (rp_handle->port_config->driver_config != NULL)
   {
      if (pcie_initialize_gpios (&rp_handle->rsrc_ctxt, rp_handle->port_config->driver_config->port_gpio_cfg) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("GPIO init failed\n");
         return PCIE_ERROR;
      }
   }

   PORT_COMPLETED (rp_handle, PORT_RESOURCES_INITIALIZED);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_init_port_phy (pcie_rp_handle* rp_handle)
{
   pcie_status_t pstatus;

   if (rp_handle == NULL)
      return PCIE_ERROR;

   if (CHECK_PORT_HAS(rp_handle, PORT_PHY_INITIALIZED))
      return PCIE_SUCCESS;

   if (CHECK_PORT_HAS(rp_handle, PORT_RESOURCES_INITIALIZED) == 0)
      return PCIE_ERROR;

   //  PERST should already be in Asserted state by now
//   pcie_drive_gpio_pin (rp_handle->port_config->perst_pin, ASSERT_PERST_PIN);

   pstatus = apply_phy_settings (rp_handle, PHY_INIT_SETTINGS);
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Phy settings init failed\n");
      return pstatus;
   }

   pcie_osal_busywait_us (1000);  // Refclk to PERST Deassert delay

   pcie_drive_gpio_pin (rp_handle->port_config->perst_pin, DEASSERT_PERST_PIN);

   PORT_COMPLETED (rp_handle, PORT_PHY_INITIALIZED); 

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_deinit_port (pcie_rp_handle* rp_handle)
{
   pcie_status_t pstatus;

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
      return PCIE_ERROR;

   if (PORT_IS_DISABLED(rp_handle))
      return PCIE_ERROR;

   if (CHECK_PORT_HAS(rp_handle, PORT_CONTROLLER_DOWN))
      return PCIE_SUCCESS;

   //if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
   //   Potentially send PME turn off to put device into D3

   /* Keep PERST Asserted */
   pcie_drive_gpio_pin (rp_handle->port_config->perst_pin, ASSERT_PERST_PIN);

   // TODO: track individually if Phy is initialized, deinit only if it was initialized
   //       For local digital loopback case we do not initialize Phy.
   pstatus = apply_phy_settings (rp_handle, PHY_DEINIT_SETTINGS);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   pstatus = disable_pcie_resources (&rp_handle->rsrc_ctxt, rp_handle->port_config);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   PORT_COMPLETED (rp_handle, PORT_CONTROLLER_DOWN);

   // Reload it next time just in case if HW config is switched
   rp_handle->port_config = NULL; 

   return PCIE_SUCCESS;
}

static pcie_status_t train_links (uint32 ports_mask, uint32 timeout_ms)
{
   pcie_status_t pstatus;
   uint32 i, fail_cnt = 0;
   uint64 linkup_deadline, cur_time;
   uint32 wait_cnt, time_remaining;
   uint32 port_cnt;
   pcie_rp_handle* rp_handle;

   port_cnt = pcie_rp_get_max_port_count ();

   pcie_osal_memory_barrier ();

   // TODO: Optimize to exit loop when only 1 core is specified
   for (i = 0; i < port_cnt; ++i)
   {
      if ((ports_mask & (1 << i)) == 0)
         continue;

      rp_handle = pcie_rp_get_port_handle (i);
      if (rp_handle == NULL)
         continue;

      pstatus = start_link_training (rp_handle);
      if (pstatus != PCIE_SUCCESS)
      {
         ports_mask = CLEAR_BIT (ports_mask, i);
         PCIE_HOST_LOG_ERROR ("PCIe Start Link training failed PCI%d\n", i);
      }
   }

   linkup_deadline = pcie_osal_get_time_ms ();

   PCIE_HOST_LOG_PERF ("Wait for link up start : %d\n", linkup_deadline);

   linkup_deadline += timeout_ms;

   do
   {
      wait_cnt = 0;

      pcie_osal_busywait_us (2000);

      for (i = 0; i < port_cnt; ++i)
      {
         if ((ports_mask & (1 << i)) == 0)
            continue;

         rp_handle = pcie_rp_get_port_handle (i);
         if (rp_handle == NULL)
            continue;

         if ((CHECK_PORT_HAS(rp_handle, PORT_LINK_UP)) ||
             (CHECK_PORT_HAS(rp_handle, PORT_LINK_TRAINING_STARTED) == 0))
            continue;

         if (check_if_linkup (rp_handle))
         {
            PORT_COMPLETED (rp_handle, PORT_LINK_UP);
            PCIE_HOST_LOG_HIGH ("PCIe Link up on port %d\n", i);
         }
         else
         {
            ++wait_cnt;
         }
      }

      cur_time = pcie_osal_get_time_ms ();

      if (cur_time < linkup_deadline)
         time_remaining = linkup_deadline - cur_time;
      else
         time_remaining = 0;

   }while ((wait_cnt > 0) && time_remaining);

   /* Just informative processing and one last chance to see if the link comesup
    * if previously timedout */
   for (i = 0; i < port_cnt; ++i)
   {
      if ((ports_mask & (1 << i)) == 0)
         continue;

      rp_handle = pcie_rp_get_port_handle (i);
      if (rp_handle == NULL)
         continue;

      if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
         continue;

      if (check_if_linkup (rp_handle))
      {
         PORT_COMPLETED (rp_handle, PORT_LINK_UP);
         PCIE_HOST_LOG_HIGH ("Link up PCIe %d\n", i);
      }
      else
      {
         PORT_COMPLETED (rp_handle, PORT_LINK_TRAINING_FAILED);
         PCIE_HOST_LOG_ERROR ("Link up Failed..!! PCIe %d \n", i);
         ++fail_cnt;
      }
   }

   return PCIE_SUCCESS;
}


#define PCI_CFG_CAPABILITY_OFFSET                   (0x0034)
#define PCIE_CFG_EXTENDED_CAPABILITY_OFFSET         (0x0100)

uint32 read_config_reg (pcie_rp_handle* rp_handle, uint32 host_space, uint32 offset)
{
   offset = offset & (~(0x3));

   if (host_space == 0)
      return *((volatile uint32*)(rp_handle->ep_config_addr + offset));
   else
      return *((volatile uint32*)(rp_handle->host_config_addr + offset));
}

pcie_status_t scan_capabilities (pcie_rp_handle* rp_handle, uint32 host_space)
{
   uint32 reg_val;
   uint8_t cap_id, version;
   uint16_t next_loc, next_ptr, ext_cap_id, cap_cnt;

   cap_cnt = 0;

   reg_val = read_config_reg (rp_handle, host_space, PCI_CFG_CAPABILITY_OFFSET);
   if (reg_val == 0xFFFFFFFF)
   {
      PCIE_HOST_LOG_ERROR ("Wrong Capability %x\n", reg_val);
      return PCIE_SUCCESS;
   }

   next_loc = reg_val & 0xff;

   /* Enumerate capability ID's */
   while (next_loc)
   {
      reg_val = read_config_reg (rp_handle, host_space, next_loc);
      cap_id = reg_val & 0xff;
      next_ptr = (reg_val >> 8) & 0xff;
      PCIE_HOST_LOG_LOW ("Curr %x, Next %x\n", cap_id, next_ptr);

      /* Store the cap info into the dev structure */
      if (cap_cnt >= MAX_CAPABILITY_CACHE)
         break;

      if (host_space == 0)
        rp_handle->ep_capability_cache[cap_cnt] = CAP_INFO_CACHE(next_loc, cap_id);
      else
        rp_handle->host_capability_cache[cap_cnt] = CAP_INFO_CACHE(next_loc, cap_id);

      ++cap_cnt;

      next_loc = next_ptr;
   }

   /* Now Enumerate ext capability ID's */
   next_loc = PCIE_CFG_EXTENDED_CAPABILITY_OFFSET;
   while (next_loc)
   {
      reg_val = read_config_reg (rp_handle, host_space, next_loc);
      ext_cap_id = reg_val & 0xffff;
      version = (reg_val >> 16) & 0xf;
      next_ptr = (reg_val >> 20) & 0xfff;
      PCIE_HOST_LOG_LOW ("Curr %x, Ver %d, Next %x\n", ext_cap_id, version, next_ptr);

      /* Store the cap info into the dev structure */
      if (cap_cnt >= MAX_CAPABILITY_CACHE)
         break;

      if (host_space == 0)
         rp_handle->ep_capability_cache[cap_cnt] = EXT_CAP_INFO_CACHE(version, next_loc, ext_cap_id);
      else
         rp_handle->host_capability_cache[cap_cnt] = EXT_CAP_INFO_CACHE(version, next_loc, ext_cap_id);

      ++cap_cnt;

      next_loc = next_ptr;
   }

   if (cap_cnt >= MAX_CAPABILITY_CACHE)
      PCIE_HOST_LOG_ERROR ("Insufficient Capability cache on port %d for type %d : %d, %d\n", rp_handle->port_config->hw_rp_index, host_space, MAX_CAPABILITY_CACHE, cap_cnt);

   return PCIE_SUCCESS;
}

boolean pcie_is_port_link_up (pcie_rp_handle* rp_handle)
{
   return (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP) != 0);
}

pcie_status_t setup_config_space (pcie_rp_handle* rp_handle)
{
   pcie_status_t pstatus = PCIE_SUCCESS;
   boolean link_is_up;

   pstatus = pcie_rp_setup_config_space_ATU (rp_handle);
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Setup config space Failed\r\n");
      return pstatus;
   }

   link_is_up = pcie_is_port_link_up (rp_handle);

   pstatus = setup_ecam_blocker (rp_handle, link_is_up);
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Setup config space Failed\r\n");
      return pstatus;
   }

   scan_capabilities (rp_handle, HOST_CFG_SPACE); 

   if (read_ltssm_state (rp_handle) == LTSSM_L0)
      scan_capabilities (rp_handle, EP_CFG_SPACE); 

   return pstatus;
}

uint32 pcie_rp_get_ltssm_state (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return 0;

   if (CHECK_PORT_HAS(rp_handle, PORT_RESOURCES_INITIALIZED))
      return read_ltssm_state (rp_handle);

   return 0;
}

pcie_status_t get_capability (pcie_rp_handle* rp_handle, uint16 bdf, uint32 cap_id, uint64* addrp, uint32* reg_offsetp, uint32 get_ext_cap)
{
   uint32* cap_cache, cap, offset;
   uint64 cap_addr;
   int i;

   if ((rp_handle == NULL) || ((addrp == NULL) && (reg_offsetp == NULL)))
      return PCIE_INVALID_PARAM;

   if (bdf == HOST_BDF_VAL)
   {
      cap_cache = rp_handle->host_capability_cache;
      cap_addr = rp_handle->host_config_addr;
   }
   else if (bdf == EP_BDF_VAL) /* For now assuming only single EP is connected on bus 1 */
   {
      cap_cache = rp_handle->ep_capability_cache;
      cap_addr = rp_handle->ep_config_addr;
   }
   else
      return PCIE_INVALID_PARAM;

   for (i=0; i< MAX_CAPABILITY_CACHE; ++i)
   {
      cap = cap_cache[i];
      if (get_ext_cap)
      {
         if (IS_EXT_CAP(cap) && (GET_CAP_ID(cap) == cap_id))
         {
            offset = GET_CAP_LOCATION(cap);
            if (addrp)
               *addrp = cap_addr + offset;
            if (reg_offsetp)
               *reg_offsetp = offset;
            return PCIE_SUCCESS;
         }
      }
      else
      {
         if ((IS_EXT_CAP(cap) == 0) && (GET_CAP_ID(cap) == cap_id))
         {
            offset = GET_CAP_LOCATION(cap);
            if (addrp)
               *addrp = cap_addr + offset;
            if (reg_offsetp)
               *reg_offsetp = offset;
            return PCIE_SUCCESS;
         }
      }
   }

   /* We are here means we didn't find it */
   return PCIE_NOT_FOUND;
}

const pcie_port_config_t * pcie_rp_get_port_config (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return NULL;

   return rp_handle->port_config;
}

const mem_region_t * pcie_rp_get_port_mem_config (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return NULL;

   return rp_handle->port_config->port_mem_bases;
}

/* TODO: For now allocate if one doesn't exist, but should have explicit
 * alloc called from a deterministic place */
static pcie_rp_handle* get_port_context (uint32 port_index)
{
   int i;
   pcie_rp_handle* free_ctxt = NULL;

   for (i = 0; i < sizeof(pcie_rp_ctxt)/sizeof(*pcie_rp_ctxt); ++i)
   {
      if (pcie_rp_ctxt[i].port_state == PORT_CONTEXT_NOT_ASSIGNED)
      {
         if (free_ctxt == NULL)
            free_ctxt = &pcie_rp_ctxt[i];
         continue;
      }

      if (pcie_rp_ctxt[i].port_index == port_index)
         return &pcie_rp_ctxt[i];
   }

   if (free_ctxt)
   {
      free_ctxt->port_index = port_index;
      free_ctxt->port_state = PORT_NOT_AVAILABLE; 
      free_ctxt->port_config = NULL;
   }

   return free_ctxt;
}

uint32 pcie_rp_get_ltr_th_scale (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
     return 0;

   return PORT_ATTRIB_LTR_TH_SCALE(rp_handle->port_config);
}

ltr_threshold_scale_t pcie_rp_get_ltr_th_val (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
     return 0;

   return PORT_ATTRIB_LTR_TH_VAL(rp_handle->port_config);
}

pcie_rp_handle* pcie_rp_get_port_handle (uint32 port_index)
{
   pcie_rp_handle* rp_handle = NULL;
   const pcie_port_config_t *rp_cfg_ptr = NULL;

   rp_handle = get_port_context (port_index);
   if (rp_handle == NULL)
      return NULL;

   if (rp_handle->port_config == NULL)
   {
      if (pcie_rp_cfg_get_config (port_index, &rp_cfg_ptr) != PCIE_SUCCESS)
          return NULL;

      if ((rp_cfg_ptr != NULL) && (rp_cfg_ptr->port_mem_bases != NULL))
      {
         rp_handle->port_config = rp_cfg_ptr;

         // Should be careful on assigning the VA here, since it could be used
         // for ATU programming which needs PA
         rp_handle->ahb_base_addr = rp_cfg_ptr->port_mem_bases[ahb_reg].pa;
         rp_handle->axi_base_addr = rp_cfg_ptr->port_mem_bases[axi_reg].pa;
		 rp_handle->axi_space_size = rp_cfg_ptr->port_mem_bases[axi_reg].sz;
      }
      else
         return NULL;
   }

   return rp_handle;
}

/******************************************************************************
 *         Public functions
 ******************************************************************************/

pcie_status_t pcie_rp_lib_init (void)
{
   int i;
   static int rp_lib_initialized = 0;

   if (rp_lib_initialized)
      return PCIE_SUCCESS;

   if (pcie_rp_cfg_load_config () != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to load Pcie port config\n");
      return PCIE_ERROR;
   }

   for (i = 0; i < sizeof(pcie_rp_ctxt)/sizeof(*pcie_rp_ctxt); ++i)
   {
      pcie_rp_ctxt[i].port_state = PORT_CONTEXT_NOT_ASSIGNED;
      pcie_rp_ctxt[i].port_config = NULL;
   }
   
   if (pcie_rp_cfg_get_target_chip_family () != EFICHIPINFO_FAMILY_KAILUA)
   {
      enable_rsc_module (); 
   }

   ++rp_lib_initialized;

   return PCIE_SUCCESS;
}

uint32 pcie_rp_get_max_port_count (void)
{
   return pcie_rp_cfg_get_max_port_count ();
}

uint32 pcie_rp_get_enabled_ports_mask (void)
{
   return pcie_rp_cfg_get_enabled_ports_mask ();
}

pcie_status_t pcie_rp_disable_port_config (uint32 port_index)
{
   return pcie_rp_cfg_disable_port (port_index);
}

uint32 pcie_rp_is_port_link_up (uint32 port_index)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return 0;

   return pcie_is_port_link_up (rp_handle);
}

#define PCIE_CONFIG_SPACE_SIZE     4096

pcie_status_t pcie_rp_get_cfg_space_addr (uint32 port_index, uint16 bdf, uint32** ptr)
{
   pcie_rp_handle* rp_handle;

   if (ptr == NULL)
      return PCIE_INVALID_PARAM;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   *ptr = (uint32*)(rp_handle->axi_base_addr + (bdf * PCIE_CONFIG_SPACE_SIZE));

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_get_hw_idx (uint32 port_index, uint32* hw_idx_ptr)
{
   pcie_rp_handle* rp_handle;

   if (hw_idx_ptr == NULL)
      return PCIE_INVALID_PARAM;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   *hw_idx_ptr = rp_handle->port_config->hw_rp_index;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_enumerate_ports (uint32 ports_mask)
{
   uint32 port_cnt, i;
   pcie_status_t pstatus = PCIE_ERROR;
   uint32 enabled_ports;
   pcie_rp_handle* rp_handle;
   uint32 enum_start_ts, enum_end_ts;

   enum_start_ts = pcie_osal_get_time_ms ();
   PCIE_HOST_LOG_PERF ("PCIe enum (0x%d) start : %u\n", ports_mask, enum_start_ts);

   port_cnt = pcie_rp_get_max_port_count ();
   enabled_ports = pcie_rp_get_enabled_ports_mask ();

   ports_mask = ports_mask & enabled_ports;

   /* First setup all the ports and attempt to get link up on those */
   for (i = 0; i < port_cnt; ++i)
   {
      if ((ports_mask & (1 << i)) == 0)
         continue;

      rp_handle = pcie_rp_get_port_handle (i);
      if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
         continue;

      if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
      {
         PCIE_HOST_LOG_HIGH ("Port %d link is already up\n", i);
         ports_mask = CLEAR_BIT (ports_mask, i); 
         if (ports_mask == 0)
            return PCIE_SUCCESS;

         continue;
      }

      pstatus = pcie_rp_init_port_resources (rp_handle);
      if (pstatus != PCIE_SUCCESS)
      {
         ports_mask = CLEAR_BIT (ports_mask, i); 
         continue;
      }

      if (PORT_ATTRIB_IS_USB4_TUNNELED(rp_handle->port_config))
         pstatus = pcie_rp_init_tunnelled_port (rp_handle);
      else
         pstatus = pcie_rp_init_port_phy (rp_handle);

      if (pstatus != PCIE_SUCCESS)
         ports_mask = CLEAR_BIT (ports_mask, i); 
   }

   PCIE_HOST_LOG_PERF ("Training start : %d\n", pcie_osal_get_time_ms ());

   pcie_osal_busywait_us (20000); // 20 ms delay after PERST deassert to start training

   train_links (ports_mask, MAX_PORTS_LINKUP_TIMEOUT_MS);

   PCIE_HOST_LOG_PERF ("Training complete : %d\n", pcie_osal_get_time_ms ());

   pcie_osal_busywait_us (1000); // Link up to config space init TODO: is it needed?

   for (i = 0; i < port_cnt; ++i)
   {
      if ((ports_mask & (1 << i)) == 0)
         continue;

      rp_handle = pcie_rp_get_port_handle (i);
      if (rp_handle == NULL)
         continue;

      if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
      {
         uint32 spd, wid;

         setup_config_space (rp_handle);
         if (pcie_cap_get_link_stat (i, &wid, &spd) == PCIE_SUCCESS)
             PCIE_HOST_LOG_HIGH ("Port %d : x%d, Gen %d\n", i, wid, spd);
      }
      else
      {
         pcie_rp_powerdown_port (i);
         ports_mask = CLEAR_BIT (ports_mask, i);
      }
   }

   enum_end_ts = pcie_osal_get_time_ms ();

   PCIE_HOST_LOG_PERF ("PCIe Links ready : %d\n", enum_end_ts);
   PCIE_HOST_LOG_PERF ("PCIe Links setup in %d ms\n", enum_end_ts - enum_start_ts);

   // None of the ports enumerated
   if (ports_mask == 0)
      return PCIE_ERROR;

   return pstatus;
}

pcie_status_t pcie_rp_powerdown_ports (uint32 ports_mask)
{
   uint32 port_cnt, i;
   pcie_status_t pstatus = PCIE_ERROR;
   pcie_rp_handle* rp_handle;

   port_cnt = pcie_rp_get_max_port_count ();

   for (i = 0; i < port_cnt; ++i)
   {
      if ((ports_mask & (1 << i)) == 0)
         continue;

      rp_handle = pcie_rp_get_port_handle (i);
      if (rp_handle == NULL)
         continue;

      if (PORT_IS_DISABLED(rp_handle))
         continue;

      if (rp_handle->port_config == NULL)
         continue;

      if (PORT_ATTRIB_IS_USB4_TUNNELED(rp_handle->port_config))
         pstatus = pcie_rp_deinit_tunnelled_port (rp_handle);
      else
         pstatus = pcie_rp_deinit_port (rp_handle);

      if (pstatus == PCIE_SUCCESS)
         PCIE_HOST_LOG_HIGH ("Powered down PCI%d\n", i);
      else
         PCIE_HOST_LOG_ERROR ("Failed PCI%d Power down\n", i);
   }

   return pstatus;
}

pcie_status_t pcie_rp_get_capability (uint32 port_index, uint16 bdf, uint32 cap_id, uint64* addrp, uint32* reg_offsetp)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return PCIE_ERROR;

   return get_capability (rp_handle, bdf, cap_id, addrp, reg_offsetp, GET_CAP);
}

pcie_status_t pcie_rp_get_ext_capability (uint32 port_index, uint16 bdf, uint32 cap_id, uint64* addrp, uint32* reg_offsetp)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);

   if (rp_handle == NULL)
      return PCIE_ERROR;

   return get_capability (rp_handle, bdf, cap_id, addrp, reg_offsetp, GET_EXT_CAP);
}

#define BDF_CONFIG_OFFSET(x)       (x << 12)
uint32 pcie_rp_read_config_reg (uint32 port_index, uint16 bdf, uint32 reg_index)
{
   uint32 val;
   uint64_t dbi_va;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   dbi_va = OSAL_CONVERT_PA_TO_VA(rp_handle->axi_base_addr);

   dbi_va += BDF_CONFIG_OFFSET(bdf);

   val = MmioRead32 (dbi_va + reg_index);

   return val;
}

pcie_status_t pcie_rp_write_config_reg (uint32 port_index, uint16 bdf, uint32 reg_index, uint32 val)
{
   uint64_t dbi_va;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   dbi_va = OSAL_CONVERT_PA_TO_VA(rp_handle->axi_base_addr);

   dbi_va += BDF_CONFIG_OFFSET(bdf);

   MmioWrite32 ((dbi_va + reg_index), val);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_setup_io_space_ATU (uint32 port_index, uint64 BaseAddr, uint64 BaseLimit, uint64 TranslationAddr)
{
   pcie_status_t  pstatus = PCIE_SUCCESS;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   pstatus = configure_iatu (rp_handle->axi_base_addr, rp_handle->axi_space_size, AtuSlotIoOut, PCIE_TLP_IORW,
                            BaseAddr, BaseLimit, TranslationAddr);
   if (pstatus != PCIE_SUCCESS)
      PCIE_HOST_LOG_ERROR ("ATU IO Setup Failed\r\n");

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_map_mem_smmu_sid (uint32 port_index, uint32 bdf, void* base_addr, uint64 size_bytes, void** map_handle_ptr)
{
   pcie_rp_handle* rp_handle = pcie_rp_get_port_handle (port_index);
   uint32 rbdf;

   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
     return 0;

   // if SMMU differs between targets, get the config and findout before invoking the API's as required
   rbdf = (port_index & 0xF) << 16;
   rbdf = rbdf | (bdf & 0xFFFF);
   return map_mem_smmu_sid (0, rbdf, base_addr, size_bytes, map_handle_ptr);
}

pcie_status_t pcie_rp_unmap_smmu_sid (void* map_handle)
{
   return unmap_smmu_sid (map_handle);
}

/******************************************************************************
 *         Test infrastructure Public functions
 ******************************************************************************/
#ifdef ENABLE_TEST_INFRASTRUCTURE
pcie_status_t  pcie_rp_setup_mem_rw_ATU (uint32 port_index, uint64 BaseAddr, uint64 BaseLimit, uint64 TranslationAddr)
{
   pcie_status_t  pstatus = PCIE_SUCCESS;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   pstatus = configure_iatu (rp_handle->axi_base_addr, rp_handle->axi_space_size, AtuSlotNonPrefMemOut, PCIE_TLP_MEM_REQ,
                            BaseAddr, BaseLimit, TranslationAddr);
   if (pstatus != PCIE_SUCCESS)
      PCIE_HOST_LOG_ERROR ("ATU IO Setup Failed\r\n");

   return pstatus;
}

pcie_status_t  pcie_rp_unmap_mem_rw_ATU (uint32 port_index)
{
   pcie_status_t  pstatus = PCIE_SUCCESS;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   pstatus = pcie_disable_ob_iatu (rp_handle->axi_base_addr, AtuSlotNonPrefMemOut);
   if (pstatus != PCIE_SUCCESS)
      PCIE_HOST_LOG_ERROR ("ATU IO Setup Failed\r\n");

   return pstatus;
}

pcie_status_t pcie_rp_enable_loopback (uint32 port_index, pcie_loopback_type type)
{
   pcie_status_t pstatus;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   if (type == PCIE_LOCAL_DIGITAL_LOOPBACK)
   {
      /* Just enable link, for local digital loopback, controller layer should have
       * already setup the link register bits for loopback */
      pstatus = pcie_rp_train_link (port_index);

      return pstatus;
   }

   if (type == PCIE_LOCAL_ANALOG_LOOPBACK)
   {
      pstatus = apply_phy_settings (rp_handle, PHY_LOOPBACK_ENABLE_SETTINGS);
      if (pstatus != PCIE_SUCCESS)
         PCIE_HOST_LOG_ERROR ("Analog loopback apply phy settings failed\r\n");

      pstatus = pcie_rp_train_link (port_index);
      return pstatus;
   }

   if (type == PCIE_REMOTE_DIGITAL_LOOPBACK)
   {
   //   enumeration_should_have_happened ();
      return PCIE_SUCCESS;
   }
   
   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_disable_loopback (uint32 port_index)
{
   return PCIE_SUCCESS;
}

/* This macro limits how many buses can be on the port, if its 2 switches cannot be supported */
#define MAX_BUS_COUNT              2

pcie_status_t pcie_rp_get_mem_resources (uint32 port_index, pcie_resource_type rsrc, pcie_mem_resource_t *res)
{
   uint64 cfg_space_size;
   const mem_region_t * mem_bases;
   pcie_rp_handle* rp_handle;

   if (res == NULL)
      return PCIE_INVALID_PARAM;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if ((rp_handle == NULL) || (rp_handle->port_config == NULL))
      return PCIE_INVALID_PARAM;

   mem_bases = rp_handle->port_config->port_mem_bases;
   if (mem_bases == NULL)
      return PCIE_ERROR;

   cfg_space_size = PCIE_SINGLE_BUS_ADDR_SPACE_SIZE * MAX_BUS_COUNT;
      
   if (rsrc == PCIE_RESOURCE_PARF_BASE)
   {
      res->pa = mem_bases[ahb_reg].pa;
      res->sz = mem_bases[ahb_reg].sz;
      res->va = OSAL_CONVERT_PA_TO_VA(res->pa);
      return PCIE_SUCCESS;
   }

   if (rsrc == PCIE_RESOURCE_DBI_BASE)
   {
      res->pa = mem_bases[axi_reg].pa;
      res->sz = cfg_space_size;
      res->va = OSAL_CONVERT_PA_TO_VA(res->pa);
      return PCIE_SUCCESS;
   }

   if (rsrc == PCIE_RESOURCE_NON_PREFETCH_MEM_SPACE)
   {
      res->pa = mem_bases[axi_reg].pa + cfg_space_size;
      res->sz = mem_bases[axi_reg].sz - cfg_space_size;
      res->va = OSAL_CONVERT_PA_TO_VA(res->pa);
      return PCIE_SUCCESS;
   }

   if (rsrc == PCIE_RESOURCE_PREFETCHABLE_MEM_SPACE)
   {
      res->pa = mem_bases[prefetchable_mem_space].pa;
      res->sz = mem_bases[prefetchable_mem_space].sz;
      res->va = OSAL_CONVERT_PA_TO_VA(res->pa);
      return PCIE_SUCCESS;
   }

   return PCIE_UNSUPPORTED;
}

pcie_status_t pcie_rp_init_controller (uint32 port_index)
{
   pcie_status_t pstatus = PCIE_ERROR;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   if (CHECK_PORT_HAS(rp_handle, PORT_RESOURCES_INITIALIZED))
      return PCIE_SUCCESS;

   pstatus = pcie_rp_init_port_resources (rp_handle);
   if (pstatus != PCIE_SUCCESS)
       PCIE_HOST_LOG_HIGH ("Port %d : init resources failed\n", port_index);

   return pstatus;
}

pcie_status_t pcie_rp_init_phy (uint32 port_index)
{
   pcie_status_t pstatus = PCIE_ERROR;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   if (CHECK_PORT_HAS(rp_handle, PORT_PHY_INITIALIZED))
      return PCIE_SUCCESS;

   if (CHECK_PORT_HAS(rp_handle, PORT_RESOURCES_INITIALIZED) == 0)
   {
      PCIE_HOST_LOG_HIGH ("Port %d : Resources not initialized for phy init\n", port_index);
      return PCIE_ERROR;
   }

   if (rp_handle->port_config == NULL)
      return PCIE_ERROR;

   if (PORT_ATTRIB_IS_USB4_TUNNELED(rp_handle->port_config))
      pstatus = pcie_rp_init_tunnelled_port (rp_handle);
   else
      pstatus = pcie_rp_init_port_phy (rp_handle);

   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_HIGH ("Port %d : Phy init failed\n", port_index);
      return pstatus;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_train_link (uint32 port_index)
{
   pcie_status_t pstatus = PCIE_ERROR;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
      return PCIE_SUCCESS;

   if (CHECK_PORT_HAS(rp_handle, PORT_PHY_INITIALIZED) == 0)
   {
      PCIE_HOST_LOG_HIGH ("Port %d : in wrong state for link training\n", port_index);
      return PCIE_ERROR;
   }

   train_links ((1 << port_index), MAX_PORTS_LINKUP_TIMEOUT_MS);

   PCIE_HOST_LOG_PERF ("Training complete : %d\n", pcie_osal_get_time_ms ());

   pcie_osal_busywait_us (1000); // Link up to config space init TODO: is it needed?

   if (CHECK_PORT_HAS(rp_handle, PORT_LINK_UP))
   {
      uint32 spd, wid;

      setup_config_space (rp_handle);
      if (pcie_cap_get_link_stat (port_index, &wid, &spd) == PCIE_SUCCESS)
          PCIE_HOST_LOG_ALWAYS ("Port %d : x%d, Gen %d\n", port_index, wid, spd);

      pstatus = PCIE_SUCCESS;
   }

   return pstatus;
}

uint32 pcie_rp_read_parf_reg (uint32 port_index, uint32 reg_index)
{
   uint32 val;
   uint64_t parf_va;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return 0;

   parf_va = OSAL_CONVERT_PA_TO_VA(rp_handle->ahb_base_addr);

   val = MmioRead32 (parf_va + reg_index);

   return val;
}

pcie_status_t pcie_rp_write_parf_reg (uint32 port_index, uint32 reg_index, uint32 val)
{
   uint64_t parf_va;
   pcie_rp_handle* rp_handle;

   rp_handle = pcie_rp_get_port_handle (port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   parf_va = OSAL_CONVERT_PA_TO_VA(rp_handle->ahb_base_addr);

   MmioWrite32((parf_va + reg_index), val);

   return PCIE_SUCCESS;
}

#endif

