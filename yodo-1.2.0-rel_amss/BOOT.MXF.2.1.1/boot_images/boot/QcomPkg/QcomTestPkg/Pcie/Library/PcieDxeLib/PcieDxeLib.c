/** 
 * Qualcomm specific PCIE Protocol interface
 *  
 * Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/13/20   yg      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EfiQcPcie.h>
#include "pcie_host_r.h"

static EFI_QC_PCIE_DXE_PROTOCOL *PcieDxeProtocol;

EFI_STATUS
EFIAPI
PcieDxeLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   return PCIE_SUCCESS;  // Asserts if Constructor returns failure
}

pcie_status_t pcie_rc_init (void)
{
   EFI_STATUS Status = EFI_SUCCESS;

   Status = gBS->LocateProtocol (&gEfiQcPcieDxeProtocolGuid,
                                 NULL,
                                 (VOID**)&PcieDxeProtocol);
   return Status;
}

pcie_status_t pcie_enumerate(uint32 rc_index)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->Enumerate (rc_index);

   return PCIE_ERROR;
}

pcie_status_t pcie_reset(uint32 rc_index)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->Reset (rc_index);

   return PCIE_ERROR;
}

pcie_status_t pcie_register_device (const pcie_device_info_t *device_id_ptr, pcie_probefn_t probe_fn, void* user_data)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->RegisterForDevice ((const PCIE_DEVICE_INFO*)device_id_ptr, (PCIE_PROBE_FN_TYPE)probe_fn, user_data);

   return PCIE_ERROR;
}

pcie_status_t pcie_unregister_device (const pcie_device_info_t *device_id_ptr, pcie_probefn_t probe_fn, void* user_data)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->UnregisterForDevice ((const PCIE_DEVICE_INFO*)device_id_ptr, (PCIE_PROBE_FN_TYPE)probe_fn, user_data);

   return PCIE_ERROR;
}

pcie_status_t pcie_enable_device (pcie_dev_t *pdev)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->EnableDevice (pdev);

   return PCIE_ERROR;
}

pcie_status_t pcie_disable_device (pcie_dev_t *pdev)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->DisableDevice (pdev);

   return PCIE_ERROR;
}

pcie_status_t pcie_config_rw (pcie_dev_t *pdev, pcie_rw_op_t operation, uint32 offset, uint32 *val)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->ConfigRw (pdev, (PCIE_CONFIG_RW_TYPE)operation, offset, val);

   return PCIE_ERROR;
}

pcie_status_t pcie_register_msi_callback (pcie_dev_t *pdev, uint32 msi_vector, pcie_msi_callback_fn_t msi_cb_fn, void* arg, uint64* trig_addr_ptr, uint32* trig_data_ptr)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->RegisterMsiCb (pdev, msi_vector, msi_cb_fn, arg, trig_addr_ptr, trig_data_ptr);

   return PCIE_ERROR;
}

pcie_status_t pcie_unregister_msi_callback (pcie_dev_t *pdev, uint32 msi_vector, pcie_msi_callback_fn_t msi_cb_fn)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->UnregisterMsiCb (pdev, msi_vector, msi_cb_fn);

   return PCIE_ERROR;
}

pcie_status_t pcie_msi_enable_int (pcie_dev_t *pdev, uint32 msi_vector)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->MsiEnableInt (pdev, msi_vector);

   return PCIE_ERROR;
}

pcie_status_t pcie_msi_disable_int (pcie_dev_t *pdev, uint32 msi_vector)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->MsiDisableInt (pdev, msi_vector);

   return PCIE_ERROR;
}

pcie_status_t pcie_enable_test_environment (void)
{
   if (PcieDxeProtocol == NULL)
      pcie_rc_init ();

   if (PcieDxeProtocol)
      PcieDxeProtocol->StartTestEnvironment ();

   return PCIE_SUCCESS;
}

pcie_status_t pcie_enable_local_digital_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->EnableLocalDigitalLoopback ((PCIE_LOOPBACK_REQ*)req_info, pcie_space_ptr, port_handle_ptr);

   return PCIE_ERROR;
}

pcie_status_t pcie_enable_local_analog_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->EnableLocalAnalogLoopback ((PCIE_LOOPBACK_REQ*)req_info, pcie_space_ptr, port_handle_ptr);

   return PCIE_ERROR;
}

pcie_status_t pcie_enable_remote_digital_loopback (loopback_req_t *req_info, uint64** pcie_space_ptr, pcie_root_port_t** port_handle_ptr)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->EnableRemoteDigitalLoopback ((PCIE_LOOPBACK_REQ*)req_info, pcie_space_ptr, port_handle_ptr);

   return PCIE_ERROR;
}

pcie_status_t pcie_disable_loopback (pcie_root_port_t *port_handle)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->DisableLoopback (port_handle);

   return PCIE_ERROR;
}


pcie_dev_t *pcie_get_parent (pcie_dev_t *pdev)
{
   if (PcieDxeProtocol)
      return PcieDxeProtocol->GetParent (pdev);

   return NULL;
}

pcie_status_t pcie_get_port_info (uint32 rc_index, pcie_port_info_t* info)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->GetPortInfo (rc_index, (PCIE_PORT_INFO*)info);

   return PCIE_ERROR;
}

pcie_status_t pcie_get_link_status (uint32 rc_index, pcie_link_status_t* stats)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->GetLinkStatus (rc_index, (PCIE_LINK_STATUS*)stats);

   return PCIE_ERROR;
}

pcie_status_t pcie_set_lane_width (uint32 rc_index, uint32 width)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->SetLaneWidth (rc_index, width);

   return PCIE_ERROR;
}

pcie_status_t pcie_set_link_width (uint32 rc_index, uint32 width)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->SetLinkWidth (rc_index, width);

   return PCIE_ERROR;
}

pcie_status_t pcie_set_link_speed (uint32 rc_index, uint32 speed)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->SetLinkSpeed (rc_index, speed);

   return PCIE_ERROR;
}

pcie_status_t pcie_set_allowed_link_speeds (uint32 rc_index, uint32 speed_mask)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->SetAllowedLinkSpeeds (rc_index, speed_mask);

   return PCIE_ERROR;
}

pcie_status_t pcie_set_allowed_lpm_states (uint32 rc_index, uint32 lpm_mask)
{
   if (PcieDxeProtocol)
      return (pcie_status_t)PcieDxeProtocol->SetAllowedLpmStates (rc_index, lpm_mask);

   return PCIE_ERROR;
}

pcie_status_t pcie_rp_set_hw_port_lanes_config (uint32 port, uint32 option)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_HW_LANE_CFG_API)
         return (pcie_status_t)PcieDxeProtocol->SetHwPortLanesConfig (port, option);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_rp_cfg_reload_config (void)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_CFG_RELOAD_API)
         return (pcie_status_t)PcieDxeProtocol->ReloadPortsConfig ();
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_get_cfg_space_addr (uint32 rc_index, uint16 bdf, uint32** ptr)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_GET_CFG_ADDR_API)
         return (pcie_status_t)PcieDxeProtocol->PcieGetCfgSpaceAddr (rc_index, bdf, ptr);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_setup_aspm (uint32 rc_index)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_ASPM_SUPPORT_API)
         return (pcie_status_t)PcieDxeProtocol->PcieSetupASPM (rc_index);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_setup_l1ss (uint32 rc_index)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_ASPM_SUPPORT_API)
         return (pcie_status_t)PcieDxeProtocol->PcieSetupL1ss (rc_index);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_setup_aer (uint32 rc_index, uint16 bdf_val, int enable)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_AER_SUPPORT_API)
         return (pcie_status_t)PcieDxeProtocol->SetupAER (rc_index, bdf_val, enable);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

pcie_status_t pcie_print_aer_logs (uint32 rc_index, uint16 bdf_val)
{
   if (PcieDxeProtocol)
   {
      if (PcieDxeProtocol->Version >= EFI_QC_PCIE_PROTOCOL_AER_SUPPORT_API)
         return (pcie_status_t)PcieDxeProtocol->PrintAERLogs (rc_index, bdf_val);
      else
         return PCIE_UNSUPPORTED;
   }

   return PCIE_ERROR;
}

