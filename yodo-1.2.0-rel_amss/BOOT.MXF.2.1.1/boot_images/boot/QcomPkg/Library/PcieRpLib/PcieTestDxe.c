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
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EfiQcPcie.h>
#include "pcie_host_r.h"
#include "pcie_rp.h"
#include <Protocol/PciIo.h>
#include <Protocol/EFIPciePlatPolicy.h>
#include <Protocol/EFIRamPartition.h>

STATIC EFI_HANDLE  gPcieDxeHandle = NULL;

EFI_STATUS StartTestEnvironment (void);

/*******************************************************************************
 *     Test protocol
 ******************************************************************************/
static EFI_QC_PCIE_DXE_PROTOCOL PcieDxeProtocol =
{
  EFI_QC_PCIE_PROTOCOL_VERSION,
  .Enumerate = (PCIE_ENUMERATE)pcie_enumerate,
  .Reset = (PCIE_RESET)pcie_reset,
                                                            
  .RegisterForDevice = (PCIE_REGISTER_DEVICE)pcie_register_device,
  .UnregisterForDevice = (PCIE_UNREGISTER_DEVICE)pcie_unregister_device,
                                                            
  .EnableDevice = (PCIE_ENABLE_DEVICE)pcie_enable_device,
  .DisableDevice = (PCIE_DISABLE_DEVICE)pcie_disable_device,
                                                            
  .ConfigRw = (PCIE_CONFIG_RW)pcie_config_rw,

  .GetParent = (PCIE_GET_PARENT)pcie_get_parent,

#ifdef ENABLE_MSI_SUPPORT
  .RegisterMsiCb = (PCIE_REGISTER_MSI_CALLBACK)pcie_register_msi_callback,
  .UnregisterMsiCb = (PCIE_UNREGISTER_MSI_CALLBACK)pcie_unregister_msi_callback,
  .MsiEnableInt = (PCIE_MSI_ENABLE_INT)pcie_msi_enable_int,
  .MsiDisableInt = (PCIE_MSI_DISABLE_INT)pcie_msi_disable_int,
#endif

  .StartTestEnvironment = StartTestEnvironment,
  .EnableLocalDigitalLoopback = (PCIE_ENABLE_LOCAL_DIGITAL_LOOPBACK)pcie_enable_local_digital_loopback,
  .EnableLocalAnalogLoopback = (PCIE_ENABLE_LOCAL_ANALOG_LOOPBACK)pcie_enable_local_analog_loopback,
  .EnableRemoteDigitalLoopback = (PCIE_ENABLE_REMOTE_DIGITAL_LOOPBACK)pcie_enable_remote_digital_loopback,
  .DisableLoopback = (PCIE_DISABLE_LOOPBACK)pcie_disable_loopback,
                                                            
  .GetPortInfo = (PCIE_GET_PORT_INFO)pcie_get_port_info,
  .GetLinkStatus = (PCIE_GET_LINK_STATUS)pcie_get_link_status,

  .SetLaneWidth = (PCIE_SET_LANE_WIDTH)pcie_set_lane_width,
  .SetLinkWidth = (PCIE_SET_LINK_WIDTH)pcie_set_link_width,

  .SetLinkSpeed = (PCIE_SET_GEN_SPEED)pcie_set_link_speed,

  .MapDmaBuffer = (PCIE_MAP_DMA_BUFFER)pcie_rp_map_mem_smmu_sid,
  .UnMapDmaBuffer = (PCIE_UNMAP_DMA_BUFFER)pcie_rp_unmap_smmu_sid,

  .SetHwPortLanesConfig = (PCIE_SET_HW_LANES_CONFIG)pcie_rp_set_hw_port_lanes_config,

  .ReloadPortsConfig = (PCIE_RELOAD_PORTS_CONFIG)pcie_rp_cfg_reload_config,

  .PcieGetCfgSpaceAddr = (PCIE_GET_CFG_SPACE_ADDR)pcie_rp_get_cfg_space_addr,
  
  .PcieSetupASPM = (PCIE_SETUP_ASPM)pcie_rp_setup_aspm,
  .PcieSetupL1ss = (PCIE_SETUP_L1SS)pcie_rp_setup_l1ss,

  .SetupAER = (PCIE_SETUP_AER)pcie_rp_setup_aer,
  .PrintAERLogs = (PCIE_PRINT_AER_LOGS)pcie_rp_print_aer_logs,
};

// Requires USE_BLANKET_DDR_SID_MAPPING_FOR_TEST be defined in PcieTestLib.c
EFI_STATUS MapAllPcieSIDsToInstalledMemory (void)
{
   EFI_STATUS                  Status = EFI_NOT_FOUND;
   EFI_RAMPARTITION_PROTOCOL   *pRamPartProtocol = NULL;
   RamPartitionEntry           *pRamPartitions = NULL;
   UINT32                      NumPartitions = 0, PortIndex, PortCnt;
   UINT32                      i = 0; 

   Status = gBS->LocateProtocol(&gEfiRamPartitionProtocolGuid, NULL, (VOID**)&pRamPartProtocol);
   if (EFI_ERROR(Status) || (&pRamPartProtocol == NULL))
   {
      DEBUG ((EFI_D_ERROR, "Failed to locate EFI_RAMPARTITION_Protocol\r\n"));
      return EFI_NOT_FOUND;
   }

   Status = pRamPartProtocol->GetRamPartitions (pRamPartProtocol, NULL, &NumPartitions);
   if (Status == EFI_BUFFER_TOO_SMALL)
   {
      pRamPartitions = AllocatePool (NumPartitions * sizeof (RamPartitionEntry));
      if (pRamPartitions == NULL) 
         return EFI_OUT_OF_RESOURCES;
    
      Status = pRamPartProtocol->GetRamPartitions (pRamPartProtocol, pRamPartitions, &NumPartitions);
      if (EFI_ERROR (Status) || (NumPartitions < 1) )
      {
         DEBUG ((EFI_D_ERROR, "Failed to get RAM partitions"));
         return EFI_NOT_FOUND;
      }
   }

   if (pRamPartitions == NULL)
      return EFI_NOT_FOUND;

   PortCnt = pcie_rp_get_max_port_count ();

   DEBUG ((EFI_D_WARN, "Mapping all DDR region for SIDs of all %d PCIe ports\n", PortCnt));
   for (PortIndex = 0; PortIndex < PortCnt; ++PortIndex)
   {
      for (i = 0; i < NumPartitions; i++)
      {
         pcie_status_t pstatus;
         void*   map_handle;

//         DEBUG ((EFI_D_WARN, "Mapping 0x%09lx ++ 0x%09lx for PCIe SID for port %d\n",
//                            pRamPartitions[i].Base, pRamPartitions[i].AvailableLength, PortIndex));

         pstatus = pcie_rp_map_mem_smmu_sid (PortIndex, HOST_BDF_VAL, (void*)pRamPartitions[i].Base,
                                             pRamPartitions[i].AvailableLength, &map_handle);
         if (pstatus != PCIE_SUCCESS)
            DEBUG ((EFI_D_ERROR, "SID Mapping failed for Host %d : 0x%09lx\n", PortIndex, pRamPartitions[i].Base));

         pstatus = pcie_rp_map_mem_smmu_sid (PortIndex, EP_BDF_VAL, (void*)pRamPartitions[i].Base,
                                             pRamPartitions[i].AvailableLength, &map_handle);
         if (pstatus != PCIE_SUCCESS)
            DEBUG ((EFI_D_ERROR, "SID Mapping failed for EP %d : 0x%09lx\n", PortIndex, pRamPartitions[i].Base));
      }
   }

   return EFI_SUCCESS;
}

EFI_STATUS StartTestEnvironment (void)
{
  static uint32 TestEnvInitDone = 0;
  EFI_STATUS             Status;
  EFI_HANDLE            *PciHandles;
  UINTN                  PciHandleCount, i;
//  EFI_BLOCK_IO_PROTOCOL               *BlkIo;

  if (TestEnvInitDone)
     return EFI_SUCCESS;

  ++TestEnvInitDone;

  PciHandleCount = 0;

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiPciIoProtocolGuid,
                                    NULL, &PciHandleCount, &PciHandles);
  if (EFI_ERROR(Status))
    return Status;

//  PCIE_HOST_LOG_ERROR ("Got %d handles to disconnect\r\n", PciHandleCount);

  for (i = 0; i < PciHandleCount; i++)
  {
//    Status = gBS->HandleProtocol (PciHandles[i], &gEfiBlockIoProtocolGuid,
//                                  (VOID **) &BlkIo);
//    if (Status != EFI_SUCCESS)
//      continue;

    Status = gBS->DisconnectController (PciHandles[i], NULL, NULL);
    if (EFI_ERROR(Status))
      DEBUG ((EFI_D_ERROR, "Failed to disconnect controller\n"));
  }

  // TODO: potentially leave this to descretion of test instead
  MapAllPcieSIDsToInstalledMemory ();

  return EFI_SUCCESS;
}

/*******************************************************************************
 *   Policy protocol test code.
 *       required here since the policy need to be set before the enumeration.
 ******************************************************************************/
//#define ENABLE_POLICY_PROTOCOL_TEST
#ifdef ENABLE_POLICY_PROTOCOL_TEST
VOID PolicyProtocolInstalledCb (EFI_EVENT   Event, VOID   *Context)
{
   EFI_PCIE_PLAT_POLICY_PROTOCOL* PciePolicyIntf = 0;
   EFI_STATUS Status;

   Status = gBS->LocateProtocol (&gEfiPciePlatPolicyProtocolGuid, NULL,
                                 (void**)&PciePolicyIntf);

   if ((Status != EFI_SUCCESS) || (PciePolicyIntf == NULL))
      return;

   PciePolicyIntf->SetPcieHwConfig (PcieHwPhyLanesConfig, 4, 2);  // Set 3A to 2 Lane

#define PCIE_2A_MASK  (1 << 2)
#define PCIE_2B_MASK  (1 << 3)
#define PCIE_3A_MASK  (1 << 4)
#define PCIE_3B_MASK  (1 << 5)
#define PCIE_4_MASK   (1 << 6)

   PciePolicyIntf->DisablePcieRootPorts (PCIE_3B_MASK);
//   PciePolicyIntf->DisablePcieRootPorts (PCIE_2B_MASK | PCIE_3A_MASK | PCIE_3B_MASK | PCIE_4_MASK);
   //PciePolicyIntf->DisablePcieRootPorts (PCIE_3A_MASK | PCIE_4_MASK);

//   PciePolicyIntf->SetPcieHwConfig (PcieHwPhyLanesConfig, 2, 4);
}

EFI_EVENT PolicyNotifyEvt  = (EFI_EVENT)NULL;
VOID* PolicyNotifyToken  = NULL;

VOID TestPolicyProtocol(VOID)
{
   EFI_STATUS Status;

   // Set up to be notified when the Cpu protocol is installed.
   Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_NOTIFY, PolicyProtocolInstalledCb, NULL, &PolicyNotifyEvt);
   if (Status != EFI_SUCCESS)
      DEBUG ((EFI_D_ERROR, "Failed to create evt\r\n"));

   Status = gBS->RegisterProtocolNotify (&gEfiPciePlatPolicyProtocolGuid, PolicyNotifyEvt, (VOID *)&PolicyNotifyToken);
   if (Status != EFI_SUCCESS)
      DEBUG ((EFI_D_ERROR, "Failed to get proto notify\r\n"));
}
#else
VOID TestPolicyProtocol(VOID)
{
}
#endif

/*******************************************************************************
 *     Public interface functions
 ******************************************************************************/
EFI_STATUS PublishPcieTestInfrastructure (void)
{
   EFI_STATUS Status = EFI_SUCCESS;
   EFI_QC_PCIE_DXE_PROTOCOL *CheckPcieDxeIntf = NULL;
//   pcie_status_t pStatus;

//   pStatus = pcie_rc_init();
//   if (pStatus != PCIE_SUCCESS)
//      return EFI_UNSUPPORTED;

//   AsciiPrint ("PcieTestDxe : %a %a\r\n", __DATE__, __TIME__);

   Status = gBS->LocateProtocol (&gEfiQcPcieDxeProtocolGuid,
                                 NULL, (VOID**)&CheckPcieDxeIntf);

   if ((Status == EFI_SUCCESS) && (CheckPcieDxeIntf != NULL))
   {
      DEBUG ((EFI_D_ERROR, "PCIe driver is already loaded...!!\r\n"));
      return EFI_ALREADY_STARTED;
   }

   Status = gBS->InstallMultipleProtocolInterfaces(
                    &gPcieDxeHandle,
                    &gEfiQcPcieDxeProtocolGuid,
                    (void **)&PcieDxeProtocol,
                    NULL);

   TestPolicyProtocol ();

   return Status;
}

EFI_STATUS
EFIAPI
QcPcieDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   // This routine executes only as part of non mission mode image driver. So all test dxe
   // related specific initialization can be done here without doing the same in mission mode
   // driver.
   pcie_rp_lib_init ();

   return PublishPcieTestInfrastructure ();
}


