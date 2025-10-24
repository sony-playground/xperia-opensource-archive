/*
  @file pcie_test.c
  @brief PCIe test implementation.

*/
/*
 ==============================================================================

          Edit History


  when       who     what, where, why
  --------   ---     ---------------------------------------------------------
  03/08/21   Yg      Ported from previous implementation

 ==============================================================================
     Copyright (c) 2018 - 2022 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================
*/

#include "pcie_host_r.h"
#include "pcie_host_log.h"
#include "pcie_reg_offsets.h"
#include "string.h"
#include "pcie_rp.h"
//#include "PcieHwioRegs.h"

struct __pcie_root_port
{
   uint8   loopback_type;
   uint8   port_index;

   // TODO: Need solution if multiple buffers need to be mapped for parallel operation
   void*   smmu_map_handle;
};

#define MAX_PCIE_ROOT_PORTS      8
struct __pcie_root_port root_ports[MAX_PCIE_ROOT_PORTS];

#define PHY_CMD_NOP                   0
#define PHY_CMD_INIT_PHY              1
#define PHY_CMD_INITIATE_TRAINING     2
#define PHY_CMD_GET_DEV_HANDLE        3

#define LOOPBACK_NONE               0
#define LOOPBACK_LOCAL_DIGITAL      1
#define LOOPBACK_LOCAL_ANALOG       2
#define LOOPBACK_REMOTE_DIGIAL      3

#define USE_BLANKET_DDR_SID_MAPPING_FOR_TEST

/*******************************************************************************
 *                 Loopback test related
 ******************************************************************************/

#define PAGE_SIZE    4096

/******************************************************************************
 *         Loopback private functions
 ******************************************************************************/
pcie_status_t pcie_enable_loopback (uint32 port_index, uint64 mem_space, uint64 size, uint64** pcie_space_ptr, pcie_loopback_type lpb_type);

pcie_status_t pcie_core_init (uint32 port_index, int phy_cmd)
{
   pcie_status_t pstatus = PCIE_ERROR;

   pstatus = pcie_rp_init_controller (port_index);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   if (phy_cmd != PHY_CMD_NOP)
   {
      if (pcie_rp_init_phy (port_index) != PCIE_SUCCESS)
         return PCIE_ERROR;
   }

   if (phy_cmd == PHY_CMD_INITIATE_TRAINING)
   {
      if (pcie_rp_train_link (port_index) != PCIE_SUCCESS)
      {
         pcie_rp_powerdown_port (port_index);
         return PCIE_ERROR;
      }
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_get_link_state (uint32 port_index, uint16* link_up_ptr, uint16* link_state_ptr)
{
   if (link_state_ptr)
      *link_state_ptr = pcie_rp_get_ltssm_state (port_index);

   if (link_up_ptr)
      *link_up_ptr = pcie_rp_is_port_link_up (port_index);

   return PCIE_SUCCESS;
}


pcie_status_t map_mem_to_pcie_space (uint32 port_index, uint64 mem_space, uint64 size, uint64** pcie_space_ptr)
{
   pcie_status_t pstatus;
   uint64 limit, pcie_space, max_space;
   pcie_mem_resource_t mem_res;

   if ((size == 0) || (size & (PAGE_SIZE - 1)) || (mem_space == 0) || (pcie_space_ptr == NULL))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_rp_get_mem_resources (port_index, PCIE_RESOURCE_NON_PREFETCH_MEM_SPACE, &mem_res);
   if (pstatus != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Failed to get DBI base %d", port_index);
      return pstatus;
   }
   max_space = mem_res.sz;

   if (size > max_space)
      return PCIE_OUT_OF_RANGE;

   pcie_space = mem_res.va + 0x100000;  // Leave any BAR space allocated, TODO: Get this in a right way
   limit = pcie_space + size - 1;

   /* Map the given pcie_space address to be translated into mem_space address by ATU to use
    * it to add to address field in TLP */
   pstatus = pcie_rp_setup_mem_rw_ATU (port_index, pcie_space, limit, mem_space);

   if (pstatus != PCIE_SUCCESS)
      PCIE_HOST_LOG_ERROR ("Outbound ATU mapping failed\r\n");

   *pcie_space_ptr = (uint64*)pcie_space;

   return pstatus;
}


pcie_status_t enable_local_analog_loopback (uint32 port_index, uint64 mem_base, uint64 mem_size, uint64** pcie_space_ptr)
{
   uint32 val;
   pcie_status_t pstatus;


   /* ASPM must be disabled prior to enabling LOOPBACK mode.
    * ASPM is disabled by programming the PCIE_CAP_ACTIVE_LINK_PM_SUPPORT field
    * of the LINK_CAPABILITIES_REG register to 2'b00. */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET);
   SET_MASK_VAL (val, PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT, 0);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET, val);

   /* Enable LOOPBACK in the PORT_LINK_CTRL register */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET, val);

   pstatus = pcie_enable_loopback (port_index, mem_base, mem_size, pcie_space_ptr, PCIE_LOCAL_ANALOG_LOOPBACK);

   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   return PCIE_SUCCESS;
}

void set_memory_space_busmastering (uint32 port_index, boolean enable)
{
   uint32 val;

   // enable BME/MSE
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, STATUS_COMMAND_DBI_OFFSET);

   if (enable)
      val = val | 0x6;
   else
      val = val & (~(0x6));

   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, STATUS_COMMAND_DBI_OFFSET, val);
}

pcie_status_t enable_local_digital_loopback (uint32 port_index, uint64 mem_base, uint64 mem_size, uint64** pcie_space_ptr)
{
   uint32 val;
   pcie_status_t pstatus;

   /* ASPM must be disabled prior to enabling LOOPBACK mode.
    * ASPM is disabled by programming the PCIE_CAP_ACTIVE_LINK_PM_SUPPORT field
    * of the LINK_CAPABILITIES_REG register to 2'b00. */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET);
   SET_MASK_VAL (val, PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT, 0);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET, val);

   /*  Now enable loopback mode */
   /*  Set the Gen3 Equalization Disable bit in the “Gen3 Control Register 
    *  GEN3_RELATED_OFF. You must do this, as the PHY has no role in PIPE loopback */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, GEN3_RELATED_DBI_OFFSET);
   SET_MASK_VAL (val, GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, GEN3_RELATED_DBI_OFFSET, val);

   /* Enable PIPE_LOOPBACK bit in the PIPE_LOOPBACK_CONTROL register */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PIPE_LOOPBACK_CONTROL_DBI_OFFSET);
   SET_MASK_VAL (val, PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PIPE_LOOPBACK_CONTROL_DBI_OFFSET, val);

   /* Enable LOOPBACK in the PORT_LINK_CTRL register */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET, val);

   /* This will bring the link up */
   pstatus = pcie_enable_loopback (port_index, mem_base, mem_size, pcie_space_ptr, PCIE_LOCAL_DIGITAL_LOOPBACK);

   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   set_memory_space_busmastering (port_index, 1);

   return PCIE_SUCCESS;
}

void disable_ltssm_debug_counters (uint32 port_index)
{
   /* Even after disable counter values are retained for debug as required */
   pcie_rp_write_parf_reg (port_index, HWIO_PCIE_PARF_LTSSM_DEBUG_CFG_OFFS, 0);
}

void enable_ltssm_debug_counters (uint32 port_index)
{
   /* Clear counters */
   pcie_rp_write_parf_reg (port_index, HWIO_PCIE_PARF_LTSSM_DEBUG_CFG_OFFS, 0);
   pcie_rp_write_parf_reg (port_index, HWIO_PCIE_PARF_LTSSM_DEBUG_CFG_OFFS, 2);
   pcie_rp_write_parf_reg (port_index, HWIO_PCIE_PARF_LTSSM_DEBUG_CFG_OFFS, 0);

   /* Enable counters in mode 1 to count duration in each state */
   pcie_rp_write_parf_reg (port_index, HWIO_PCIE_PARF_LTSSM_DEBUG_CFG_OFFS, 5);
}

pcie_status_t enable_remote_digital_loopback (uint32 port_index, uint64 mem_base, uint64 mem_size, uint64** pcie_space_ptr)
{
   uint32 val, cnt = 0;
   pcie_status_t pstatus;
   uint16 link_state = 0;

   enable_ltssm_debug_counters (port_index);

   /* Here contrary to the documentation that TS1/2 OS's will have bits set to initiate
    * remote loopback, its required to actually bring the link up first before
    * setting the loopback bit. So first bring up the link. */
   /* This will bring the link up */
   pstatus = pcie_enable_loopback (port_index, mem_base, mem_size, pcie_space_ptr, PCIE_REMOTE_DIGITAL_LOOPBACK);

   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET);
   SET_MASK_VAL (val, PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT, 0);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LINK_CAPABILITIES_DBI_OFFSET, val);

//#define PIPE_LOOPBACK_SETTINGS_FOR_REMOTE_ASWELL
#ifdef PIPE_LOOPBACK_SETTINGS_FOR_REMOTE_ASWELL
   /* Enable PIPE_LOOPBACK bit in the PIPE_LOOPBACK_CONTROL register */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PIPE_LOOPBACK_CONTROL_DBI_OFFSET);
   SET_MASK_VAL (val, PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PIPE_LOOPBACK_CONTROL_DBI_OFFSET, val);
#endif

   pcie_osal_busywait_us (25000);  // Wait for link to stabilize after entering loopback

   /* Enable LOOPBACK in the PORT_LINK_CTRL register */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET, val);

   pcie_osal_busywait_us (25000);  // Wait for link to stabilize after entering loopback

   do {
      pstatus = pcie_get_link_state (port_index, NULL, &link_state);
      if (pstatus != PCIE_SUCCESS)
         return pstatus;
      ++cnt;

      pcie_osal_busywait_us (100);

   }while ((link_state == 0x11) && (cnt < 100));  // TODO: Fix me, LTSSM state shouldn't be known here

   disable_ltssm_debug_counters (port_index);

   if (link_state == 0x1B)  // TODO: statemachine states shouldn't be known in this layer
      return PCIE_SUCCESS;

   PCIE_HOST_LOG_ERROR ("LTSSM is in wrong state (0x%X)\n", link_state);
   return PCIE_ERROR;
}

pcie_status_t set_link_speed (uint32 port_index, uint32 speed)
{
   uint32 val;

   if ((speed == 0) || (speed > 4))  // TODO: check based on capability
      return PCIE_INVALID_PARAM;

   /* These both following operations need to be done before training starts */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LINK_CONTROL2_LINK_STATUS2_DBI_OFFSET);
   SET_MASK_VAL (val, LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED, speed);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LINK_CONTROL2_LINK_STATUS2_DBI_OFFSET, val);

   return PCIE_SUCCESS;
}

pcie_status_t set_lane_width (uint32 port_index, uint32 width)
{
   uint32 val, lane_mask;

   if ((width == 0) || (width > 4))
      return PCIE_INVALID_PARAM;

   if (width & (width - 1))
      return PCIE_INVALID_PARAM;

   lane_mask = (1 << width);
   --lane_mask;
//   lane_mask = width;   // do not allow scale down

   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, PORT_LINK_CTRL_OFF_LINK_CAPABLE, lane_mask);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, PORT_LINK_CTRL_DBI_OFFSET, val);

   return PCIE_SUCCESS;
}

static uint32 get_current_link_width (uint32 port_index)
{
   uint32 val;

   val = pcie_rp_read_config_reg (port_index, 0, LINK_CONTROL_LINK_STATUS_DBI_OFFSET);
   return ((val >> 0x14) & 0x3F);  // Negotiated link width @ bit 20
}

static uint32 get_current_link_speed (uint32 port_index)
{
   uint32 val, curr_spd_vect;

   val = pcie_rp_read_config_reg (port_index, 0, LINK_CONTROL_LINK_STATUS_DBI_OFFSET);
   /* Bit location represented in speed vector
    * 0001 : Bit 0 => Gen 1
    * 0010 : Bit 1 => Gen 2
    * 0011 : Bit 2 => Gen 3
    * 0100 : Bit 3 => Gen 4
    *
    * Since bit assignments directly match the Gen speed,
    * return the value without further processing            */
   curr_spd_vect = (val >> 16) & 0xF;  // Link speed

  return curr_spd_vect;  // Use the number represented as Gen x
}

/* This width setting is done on the link in L0 */
pcie_status_t set_link_width (uint32 port_index, uint32 width)
{
   uint32 val, cnt;

   if ((width == 0) || (width > 4))
      return PCIE_INVALID_PARAM;

   if (width & (width - 1))
      return PCIE_INVALID_PARAM;

   /* Settings from SVE */
   val = pcie_rp_read_parf_reg (port_index, PARF_CFG_BITS_3_OFFS);
   SET_MASK_VAL (val, PARF_CFG_BITS_3_ENABLE_REMOTE_UPCONFIG_LANE, 1);
   pcie_rp_write_parf_reg (port_index, PARF_CFG_BITS_3_OFFS, val);

   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LANE_SKEW_OFFS);
   val = val | (1 << 5);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LANE_SKEW_OFFS, val);
   
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, MULTI_LANE_CONTROL_DBI_OFFSET);
   SET_MASK_VAL (val, MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH, width);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, MULTI_LANE_CONTROL_DBI_OFFSET, val);

   /* Start upconfigure or downconfigure process now */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, MULTI_LANE_CONTROL_DBI_OFFSET);
   SET_MASK_VAL (val, MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, MULTI_LANE_CONTROL_DBI_OFFSET, val);

   for (cnt = 0; cnt < 100; ++cnt)  // Max 10mS
   {
      pcie_osal_busywait_us (100);  // 100uS

      if (get_current_link_width (port_index) == width)
         break;
   }
   /* For now ignoring the result of link width setting, since success also depends
    * on whether the EP supports switching and the width */

   return PCIE_SUCCESS;
}

/******************************************************************************
 *         Loopback Public functions
 ******************************************************************************/

pcie_status_t pcie_enable_local_digital_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   uint32 port_index;
   pcie_status_t pstatus;
   pcie_root_port_t *curr_root_port;

   if ((req_info == NULL) || (port_handle_ptr == NULL) || (pcie_space_ptr == NULL) || (req_info->mem_base == 0) || (req_info->mem_size == 0))
      return PCIE_INVALID_PARAM;

   port_index = req_info->rc_index;

   if (port_index >= ARRAY_SIZE(root_ports))
      return PCIE_INVALID_PARAM;

   if (pcie_rp_is_port_link_up (port_index))
      pcie_rp_powerdown_port (port_index);

//   pcie_osal_busywait_us (5000);

   pstatus = pcie_rp_init_controller (port_index);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   if (pcie_rp_init_phy (port_index) != PCIE_SUCCESS)
      return PCIE_ERROR;

   curr_root_port = &root_ports[port_index];

   curr_root_port->port_index = port_index;
   curr_root_port->loopback_type = LOOPBACK_LOCAL_DIGITAL;
   curr_root_port->smmu_map_handle = NULL;

   set_lane_width (port_index, req_info->link_width);
   set_link_speed (port_index, req_info->link_speed);

   pstatus = enable_local_digital_loopback (port_index, req_info->mem_base, req_info->mem_size, pcie_space_ptr);

   if (pstatus == PCIE_SUCCESS)
   {
#ifndef USE_BLANKET_DDR_SID_MAPPING_FOR_TEST
      void* map_handle = NULL;

      // Use HOST BDF value for loopback
      pstatus = pcie_rp_map_mem_smmu_sid (port_index, HOST_BDF_VAL, (void*)req_info->mem_base, req_info->mem_size, &map_handle);
      if (pstatus == PCIE_SUCCESS)
         curr_root_port->smmu_map_handle = map_handle;
#endif

      *port_handle_ptr = curr_root_port;
   }

   if (pstatus != PCIE_SUCCESS)
      pcie_disable_loopback (curr_root_port);  // if Link doesn't come up this should recover

   return pstatus;
}

pcie_status_t pcie_enable_local_analog_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   pcie_status_t pstatus;
   pcie_root_port_t *curr_root_port;
   uint32 port_index;

   if ((req_info == NULL) || (port_handle_ptr == NULL) || (pcie_space_ptr == NULL) || (req_info->mem_base == 0) || (req_info->mem_size == 0))
      return PCIE_INVALID_PARAM;

   port_index = req_info->rc_index;

   if (port_index >= ARRAY_SIZE(root_ports))
      return PCIE_INVALID_PARAM;

   if (pcie_rp_is_port_link_up (port_index))
      pcie_rp_powerdown_port (port_index);

   pstatus = pcie_rp_init_controller (port_index);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   if (pcie_rp_init_phy (port_index) != PCIE_SUCCESS)
      return PCIE_ERROR;

   curr_root_port = &root_ports[port_index];

   curr_root_port->port_index = port_index;
   curr_root_port->loopback_type = LOOPBACK_LOCAL_ANALOG;
   curr_root_port->smmu_map_handle = NULL;

   set_lane_width (port_index, req_info->link_width);
   set_link_speed (port_index, req_info->link_speed);

   pstatus = enable_local_analog_loopback (port_index, req_info->mem_base, req_info->mem_size, pcie_space_ptr);

   if (pstatus == PCIE_SUCCESS)
   {
#ifndef USE_BLANKET_DDR_SID_MAPPING_FOR_TEST
      void* map_handle = NULL;

      // Use HOST BDF value for loopback
      pstatus = pcie_rp_map_mem_smmu_sid (port_index, HOST_BDF_VAL, (void*)req_info->mem_base, req_info->mem_size, &map_handle);
      if (pstatus == PCIE_SUCCESS)
         curr_root_port->smmu_map_handle = map_handle;
#endif

      *port_handle_ptr = curr_root_port;
   }

   if (pstatus != PCIE_SUCCESS)
      pcie_disable_loopback (curr_root_port);  // if Link doesn't come up this should recover

   return pstatus;
}

pcie_status_t pcie_enable_remote_digital_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   pcie_status_t pstatus;
   pcie_root_port_t *curr_root_port;
   uint32 port_index, val;

   if ((req_info == NULL) || (port_handle_ptr == NULL) || (pcie_space_ptr == NULL) || (req_info->mem_base == 0) || (req_info->mem_size == 0))
      return PCIE_INVALID_PARAM;

   port_index = req_info->rc_index;

   if (port_index >= ARRAY_SIZE(root_ports))
      return PCIE_INVALID_PARAM;

   if (pcie_rp_is_port_link_up (port_index))
      pcie_rp_powerdown_port (port_index);

   pstatus = pcie_rp_init_controller (port_index);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   if (pcie_rp_init_phy (port_index) != PCIE_SUCCESS)
      return PCIE_ERROR;

   curr_root_port = &root_ports[port_index];

   curr_root_port->port_index = port_index;
   curr_root_port->loopback_type = LOOPBACK_REMOTE_DIGIAL;
   curr_root_port->smmu_map_handle = NULL;

   /* Set link speed before the link Training happens and link comesup
    * For remote we need to start enumeration with all lanes first, then
    * scale down */
   set_link_speed (port_index, req_info->link_speed);

   pcie_osal_busywait_us (25000);

   if (pcie_rp_train_link (port_index) != PCIE_SUCCESS)
   {
      pcie_rp_powerdown_port (port_index);
      return PCIE_ERROR;
   }

   if ((req_info->link_width != 0) && (req_info->link_width != get_current_link_width (port_index)))
   {
      pcie_osal_busywait_us (1000);
      /* Already link should be up, set the link width now */
      set_link_width (port_index, req_info->link_width);
   }

/* TODO: Check if mapping is required */
#define BAR_MAP_FOR_LOOPBACK
#ifdef BAR_MAP_FOR_LOOPBACK
   pstatus = pcie_bus_initialize (port_index);
   if (pstatus != PCIE_SUCCESS)
   {
      pcie_rp_powerdown_port (port_index);
      return pstatus;
   }

   pcie_osal_busywait_us (25000);  // Wait for link to stabilize before entering loopback
#endif

   //val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, 0x104);
   //val1 = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, 0x108);
   //PCIE_HOST_LOG_ERROR ("AER before LPB 0x%X 0x%X\n", val, val1);

   if (pstatus == PCIE_SUCCESS)
   {
      /* This function bringsup the link */
      pstatus = enable_remote_digital_loopback (port_index, req_info->mem_base, req_info->mem_size, pcie_space_ptr);
      pcie_osal_busywait_us (5000);
   }

   if (pstatus == PCIE_SUCCESS)
   {
#ifndef USE_BLANKET_DDR_SID_MAPPING_FOR_TEST
      void* map_handle = NULL;

      // Use HOST BDF value for loopback
      pstatus = pcie_rp_map_mem_smmu_sid (port_index, HOST_BDF_VAL, (void*)req_info->mem_base, req_info->mem_size, &map_handle);
      if (pstatus == PCIE_SUCCESS)
         curr_root_port->smmu_map_handle = map_handle;
#endif

      *port_handle_ptr = curr_root_port;
   }

   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, 0x104);
   //val1 = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, 0x108);
   //PCIE_HOST_LOG_ERROR ("AER after LPB 0x%X 0x%X\n", val, val1);

   if ((val & 0x100000) == 0)
   {
      PCIE_HOST_LOG_ERROR ("Recovering from error, discard loopback\n");
      pstatus = PCIE_ERROR;
   }

   if (pstatus != PCIE_SUCCESS)
      pcie_disable_loopback (curr_root_port);  // if Link doesn't come up this should recover

   return pstatus;
}

pcie_status_t pcie_disable_loopback (pcie_root_port_t* port_handle)
{
   pcie_status_t pstatus;

   if (port_handle == NULL)
      return PCIE_INVALID_PARAM;

#ifndef USE_BLANKET_DDR_SID_MAPPING_FOR_TEST
   if (port_handle->smmu_map_handle)
     pstatus = pcie_rp_unmap_smmu_sid (port_handle->smmu_map_handle);
#endif

   // This reset call also calls pcie_rp_powerdown_port
   pstatus = pcie_reset (port_handle->port_index);

   port_handle->loopback_type = LOOPBACK_NONE;

   return pstatus;
}

pcie_status_t pcie_get_port_info (uint32 port_index, pcie_port_info_t* infop)
{
   pcie_status_t pstatus;
   uint32 val, speeds, max_spd_vect;

   if ((port_index >= ARRAY_SIZE(root_ports)) || (infop == NULL))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_core_init (port_index, PHY_CMD_INIT_PHY);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   /* TODO: ideally this should read the register by using info from capabilities
    * enumeration offsets */
   val = pcie_rp_read_config_reg (port_index, 0, LINK_CAPABILITIES_DBI_OFFSET);
   infop->max_lane_width = (val >> 4) & 0x3F;
   max_spd_vect = val & 0xF;
   
   speeds = pcie_rp_read_config_reg (port_index, 0, LINK_CAPABILITIES2_DBI_OFFSET);
   speeds = speeds >> 1;
   speeds = speeds & 0xF;
   speeds = speeds & ((1 << max_spd_vect) - 1);
   infop->link_speed_mask = speeds;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_get_link_status (uint32 port_index, pcie_link_status_t* caps)
{
   pcie_status_t pstatus;

   if ((port_index >= ARRAY_SIZE(root_ports)) || (caps == NULL))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_core_init (port_index, PHY_CMD_INIT_PHY);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   caps->current_link_width = get_current_link_width (port_index);

   caps->current_link_speed = get_current_link_speed (port_index);

   pcie_get_link_state (port_index, &caps->link_up, &caps->link_state);

   caps->LPM_counters[0] = pcie_rp_read_parf_reg (port_index, PCIE_PARF_DEBUG_CNT_PM_LINKST_IN_L0S_OFF);
   caps->LPM_counters[1] = pcie_rp_read_parf_reg (port_index, PCIE_PARF_DEBUG_CNT_AUX_CLK_IN_L1SUB_L1_OFF);
   caps->LPM_counters[2] = pcie_rp_read_parf_reg (port_index, PCIE_PARF_DEBUG_CNT_AUX_CLK_IN_L1SUB_L2_OFF);

   return PCIE_SUCCESS;
}

// Here lane width refers to *before* link training/establishment.
// This is Lane resize
pcie_status_t pcie_set_lane_width (uint32 port_index, uint32 width)
{
   pcie_status_t pstatus;

   if ((port_index >= ARRAY_SIZE(root_ports)) || (width == 0) || (width > 16))
      return PCIE_INVALID_PARAM;

   if (width & (width - 1))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_core_init (port_index, PHY_CMD_INIT_PHY);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   set_lane_width (port_index, width);

   return PCIE_SUCCESS;
}

// Here we will be doing resizing of the Link width when the link
// is already established in L0. This is Link resize
pcie_status_t pcie_set_link_width (uint32 port_index, uint32 width)
{
   pcie_status_t pstatus;

   if ((port_index >= ARRAY_SIZE(root_ports)) || (width == 0) || (width > 16))
      return PCIE_INVALID_PARAM;

   if (width & (width - 1))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_core_init (port_index, PHY_CMD_INIT_PHY);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   /* Link should be in L0 */
   set_link_width (port_index, width);

   return PCIE_SUCCESS;
}

// 1 => Gen1, 2 => Gen2, 3 => Gen3
pcie_status_t pcie_set_link_speed (uint32 port_index, uint32 speed)
{
   uint32 val;
   pcie_status_t pstatus;

   if ((port_index >= ARRAY_SIZE(root_ports)) || (speed == 0) || (speed > 6))
      return PCIE_INVALID_PARAM;

   pstatus = pcie_core_init (port_index, PHY_CMD_INITIATE_TRAINING);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   /* These both following operations need to be done before training starts */
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, LINK_CONTROL2_LINK_STATUS2_DBI_OFFSET);
   SET_MASK_VAL (val, LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED, speed);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, LINK_CONTROL2_LINK_STATUS2_DBI_OFFSET, val);

#if 0
   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, GEN2_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE, 0);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, GEN2_CTRL_DBI_OFFSET, val);

   val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, GEN2_CTRL_DBI_OFFSET);
   SET_MASK_VAL (val, GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE, 1);
   pcie_rp_write_config_reg (port_index, HOST_BDF_VAL, GEN2_CTRL_DBI_OFFSET, val);

   do 
   {
      val = pcie_rp_read_config_reg (port_index, HOST_BDF_VAL, GEN2_CTRL_DBI_OFFSET);
      flag = GET_MASK_VAL (val, GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE);      
   }while (flag == 1);
#endif

   return PCIE_SUCCESS;
}

pcie_status_t pcie_enable_loopback (uint32 port_index, uint64 mem_space, uint64 size, uint64** pcie_space_ptr, pcie_loopback_type lpb_type)

{
   pcie_status_t pstatus;
   uint32 ltssm_state;

   pstatus = pcie_rp_enable_loopback (port_index, lpb_type);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   pstatus = map_mem_to_pcie_space (port_index, mem_space, size, pcie_space_ptr);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   ltssm_state = pcie_rp_get_ltssm_state (port_index);

   //if ((ltssm_state == LTSSM_LPBK_ACTIVE) || (ltssm_state == LTSSM_L0))
   if ((ltssm_state == 0x1B) || (ltssm_state == 0x11))
      return PCIE_SUCCESS;

   PCIE_HOST_LOG_ERROR ("Remote loopback LTSSM in wrong state %X\r\n", ltssm_state);

   return PCIE_ERROR;
}

