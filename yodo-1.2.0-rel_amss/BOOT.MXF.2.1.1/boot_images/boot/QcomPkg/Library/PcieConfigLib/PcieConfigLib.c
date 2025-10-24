/** @file PcieConfigLib.c

   Shim file to bridge between PCIe root port lib and UEFI drivers

   Copyright (c) 2014-2022 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Confidential and Proprietary - Qualcomm Technologies, Inc.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 12/18/20   yg       Migrated to new interface
 07/31/20   yg       Keep EP MSI's disabled
 04/10/20   ts       First port for SC8280X
 06/25/19   ts       Optimized boot time with just one root port wait time
                     Included for CLS subtype 1 platform type
 01/31/19   ts       Register for PCIe ExitBootServices callback
 10/23/18   ts       Register for a callback to update AML variable based on
                     the bifurcation configuration
 07/16/18   ts       Supporting PCIe LPM mode for off mode charging
 05/16/18   ts       Deferred L1ss config to a 100 ms timer callback
 11/15/17   ts       called SMMU Config from PcieConfigLibEnableRootports
 05/22/17   ts       Fixed UpdatePortInfo function for possible memory
                     corruption
 05/05/17   ts       Updated the global port info structure to take in account
                     the removed ports
 07/28/16   ts       Register for a callback to update AML variable on PCIe link
                     state and powered down port PHY in case of link training
                     failure
 07/28/16   ts       Included I/O port access support and removed Address
                     resource configuration for End points
 07/15/16   ts       Formatted strings to %a in debug prints and Implemented
                     PcieConfigLibUpdatePortInfo to update global port info
                     and as well as disable clocks and LDOs(if necessary)
 07/08/16   ts       Renamed file to PcieConfigLib.c & made changes to init
                     root ports one by one
 06/08/16   ts       merged the PERST and link training in one function
 02/08/16   ts       Added pcie xml config support
 01/11/16   ts       Register for PCIe ExitBootServices callback
 06/15/15   ts       Simplified PCIeConfigLibRead_Config function.
                     Calling setup L1ss after iATU setup.
 05/13/15   ts       Unified code for multi platforms
 03/18/15   ts       Fixed Copyrights header
 03/16/15   ts       Added warning messages and split PHY code
                     into common and port
 01/26/15   ts       Updated the code as per 8994 changes
 10/07/14   ah       Changes for 8996
 06/16/14   hk       Add PcieInit protocol
 05/07/14   hk       Turn on PCie during exitbootservices
 04/18/14   hk       First checkin for 8994
=============================================================================*/


#include <Uefi.h>
#include "pcie_dtypes.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomBaseLib.h>
#include <Protocol/EFIPciePlatPolicy.h>

#include "Library/pcie_rp.h"
#include "PcieConfig_i.h"

//#define ENABLE_PERF_LOGGING
#ifdef ENABLE_PERF_LOGGING
#define PCIE_PROFILE_PERF(x)     DEBUG(x)
#else
#define PCIE_PROFILE_PERF(x)     do{}while(0)
#endif

struct pcie_nvme_controller_registers * pcie_nvme_mmio = NULL;

#define TIME_MS_TO_TIMER_100NS_UNITS(a)   (a * 10000)

pcie_status_t pcie_cap_disable_MSIs (uint32 port_index);
EFI_STATUS PublishPcieTestInfrastructure (void);

/*******************************************************************************
 *            Private functions
 ******************************************************************************/

VOID PcieEnableL1ssOnAllPorts (EFI_EVENT Event, VOID *Context)
{
   UINT32          i;
   UINT32          TotalRootPorts = 0;
   TotalRootPorts = pcie_rp_get_max_port_count ();
   UINT32          Strtms, Endms;

   Strtms = GetTimerCountms ();

   for (i = 0; i < TotalRootPorts; i++)
   {
      if (pcie_rp_is_port_link_up (i) == 0)
        continue;
  
      if (pcie_rp_setup_l1ss (i) != PCIE_SUCCESS)
         DEBUG ((EFI_D_ERROR, "Failed to enable L1ss on %d\r\n", i));
	  else
         DEBUG ((EFI_D_ERROR, "Enabled L1ss on %d\r\n", i));
   }

   Endms = GetTimerCountms ();

   DEBUG ((EFI_D_ERROR, "Setup L1ss took %d ms\r\n", Endms - Strtms));
}

/* TODO: does this really need to be timer callback based? */
EFI_STATUS
SetupL1ssConfig(void)
{
   EFI_STATUS        Status = EFI_SUCCESS;
   EFI_EVENT         L1ssEnableTimer;

   Status = gBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
                              PcieEnableL1ssOnAllPorts,
                              NULL, &L1ssEnableTimer);
   if (EFI_ERROR (Status))
   {
      DEBUG ((EFI_D_WARN, "L1ss CreateEvent Failed\r\n"));
      return Status;
   }

   Status = gBS->SetTimer (L1ssEnableTimer, TimerRelative,
                           TIME_MS_TO_TIMER_100NS_UNITS(100));

   if (EFI_ERROR (Status))
   {
      DEBUG ((EFI_D_WARN, "L1ss SetTimer failed\r\n"));
      return Status;
   }

   return Status;
}

EFI_STATUS SetupRootPort (UINT32 CurrentRootPort)
{
   EFI_STATUS Status = EFI_SUCCESS;

   Status = PcieConfigLibSetACPIPlatCallback (CurrentRootPort);

   if (pcie_rp_setup_aspm (CurrentRootPort) != PCIE_SUCCESS)
   {
      DEBUG ((EFI_D_WARN, "Setup ASPM Failed for %u\r\n", CurrentRootPort));
      return EFI_DEVICE_ERROR;
   }

   /* Initially keep MSI's disabled, later required module can enable it explicitly */
   Status = pcie_cap_disable_MSIs (CurrentRootPort);
   if (EFI_ERROR (Status))
      DEBUG ((EFI_D_WARN, "Disable MSI's Failed for %u\r\n", CurrentRootPort));

   return Status;
}

/*******************************************************************************
 *            Pcie Platform Policy Protocol
 ******************************************************************************/
EFI_STATUS PcieDisableRootPorts (IN UINT32 PortsMask)
{
   UINT32 PortIndex = 0;

   while (PortsMask)
   {
      if (PortsMask & 0x1)
         pcie_rp_disable_port_config (PortIndex);
      PortsMask >>= 1;
      ++PortIndex;
   }

   return EFI_SUCCESS;
}

EFI_STATUS PcieSetHwConfig (IN PcieHwConfigType  HwCfg,
                            IN UINT32            Port    OPTIONAL,
                            IN UINTN             Arg     OPTIONAL)
{
   pcie_status_t        pstatus;

   if (HwCfg == PcieHwPhyLanesConfig)
   {
      pstatus = pcie_rp_set_hw_port_lanes_config (Port, Arg);

      if (pstatus != PCIE_SUCCESS)
      {
         DEBUG ((EFI_D_ERROR, "Failed to set Lane config\r\n"));
         return EFI_DEVICE_ERROR;
      }

      return EFI_SUCCESS;
   }

   return EFI_INVALID_PARAMETER;
}

EFI_PCIE_PLAT_POLICY_PROTOCOL PciePlatformPolicyProtocol = 
{
   .Version = PCIE_PLAT_POLICY_VERSION,
   .DisablePcieRootPorts = &PcieDisableRootPorts,
   .SetPcieHwConfig = &PcieSetHwConfig,
};

EFI_STATUS InstallPolicyProtocol (VOID)
{
   EFI_STATUS Status;
   EFI_HANDLE Hndl = NULL;

   Status = gBS->InstallProtocolInterface (&Hndl, &gEfiPciePlatPolicyProtocolGuid, 
                                           EFI_NATIVE_INTERFACE,
                                           (void **)&PciePlatformPolicyProtocol);
   if (Status != EFI_SUCCESS)
      DEBUG ((EFI_D_ERROR, "Failed to Install Policy protocol\r\n"));

   return Status;
}

/*******************************************************************************
 *
 *            Public functions
 *
 ******************************************************************************/
EFI_STATUS
EFIAPI
PcieConfigLibEnableRootPorts (VOID)
{
   UINT32            CurrentRootPort = 0;
   UINT32            TotalRootPorts = 0;
   uint32            enabled_ports;
   pcie_status_t     pStatus;
   
   if (IsDeviceInOffModeCharging ())
   {
     DEBUG ((EFI_D_WARN, "In off mode charging, skip PCIe initialization\r\n"));
     return EFI_SUCCESS;
   }

   PublishPcieTestInfrastructure ();

   /* Enable default config options before pcie_rp_lib_init which loads the
    * enabled configurations */
   pcie_rp_set_default_target_config (0);

   /* Install policy protocol after setting default config, so that policy
    * can override the defaults */
   InstallPolicyProtocol ();

   /* Required config should be set now, enable lib and load config */
   if (pcie_rp_lib_init () != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   TotalRootPorts = pcie_rp_get_max_port_count ();

   enabled_ports = pcie_rp_get_enabled_ports_mask ();

   pStatus = pcie_rp_enumerate_ports (enabled_ports); // Pick all enabled ports to enumerate

   if (pStatus != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   PCIE_PROFILE_PERF ((EFI_D_ERROR, "Ports Root ports setup done : %ld\r\n", pcie_osal_get_time_ms ()));

   for (CurrentRootPort = 0; CurrentRootPort < TotalRootPorts; CurrentRootPort++)
   {
      if ((enabled_ports & (1 << CurrentRootPort)) == 0)
         continue;

      if (pcie_rp_is_port_link_up (CurrentRootPort))
        SetupRootPort (CurrentRootPort);
   }

   PCIE_PROFILE_PERF ((EFI_D_ERROR, "Root ports setup done : %ld\r\n", pcie_osal_get_time_ms ()));

   PcieConfigLibSetupBattChargingHandler ();

   SetupL1ssConfig ();

   PCIE_PROFILE_PERF ((EFI_D_ERROR, "Root ports enable complete : %ld\r\n", pcie_osal_get_time_ms ()));

   return EFI_SUCCESS;
}

EFI_STATUS ConfigLibDeinitializeAllPcieCores (VOID)
{
   /* For now give all 16 bits set specifying power down
    * 16 ports, though we wouldn't have that many */
   if (pcie_rp_powerdown_ports (0xFFFF) != PCIE_SUCCESS)
      return EFI_DEVICE_ERROR;

   return EFI_SUCCESS;
}

UINT32
PcieConfigLibGetNumberOfHostBridges (VOID)
{
   return pcie_rp_get_max_port_count ();
}

UINT32
PcieConfigLibGetNumberOfRootBridges (UINT32 RootPortIndex)
{
   /*
   * Return 1 as of now
   * This can be changed in future, if we have more than one
   * root port sharing:
   *  o PCI I/O space
   *  o PCI memory space
   *  o PCI prefetchable memory space
   */
   return 0x1;
}

EFI_STATUS
PcieConfigLibGetResourceAperture (UINT32 RootPortIndex,
    PCI_ROOT_BRIDGE_RESOURCE_APERTURE * ResAperture)
{
   pcie_mem_resource_t  mem_cfg;
   pcie_status_t        pstatus;

   if (ResAperture == NULL)
      return EFI_INVALID_PARAMETER;

   /*
   * Before proceeding further, lets define some terms of resource aperture
   *
   * Base  - Base as seen from PCIe root complex after translation
   * Start - As seen from CPU before translation
   * End   - As seen from CPU before translation
   */

   /*
   * Bus number Information
   *
   * Base  - Start bus number of this segment
   * Start - Start bus number of this segment
   * End   - End bus number of this segment
   */
   ResAperture[PciRbResTypeBus].Base = 0;
   ResAperture[PciRbResTypeBus].Start = 0;
   ResAperture[PciRbResTypeBus].End = 1;   // Only 1 port per controller

   /*
   * Config Mem Address information
   *
   * Base  - DBI Base
   * Start - DBI Base
   * End   - Ecam size of maximum available bus under this segment
   */
   pstatus = pcie_rp_get_mem_resources (RootPortIndex, PCIE_RESOURCE_DBI_BASE, &mem_cfg);
   if (pstatus != PCIE_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "Unable to get mem resource %d\r\n", RootPortIndex));
      return EFI_NOT_FOUND;
   }

   ResAperture[PciRbResTypeCfg].Base = mem_cfg.pa;
   ResAperture[PciRbResTypeCfg].Start = mem_cfg.pa;
   ResAperture[PciRbResTypeCfg].End = mem_cfg.pa + mem_cfg.sz - 1;

   /* IO Mapped IO Information
   *
   * Base  - Device accessible address (arbitrary 20 bit value)
   * Start - CPU accessible DBI address
   * End   - DBI end
   */
   ResAperture[PciRbResTypeIo].Base = (0x10000 * RootPortIndex);
   ResAperture[PciRbResTypeIo].Start = ResAperture[PciRbResTypeCfg].End + 1;
   ResAperture[PciRbResTypeIo].End = ResAperture[PciRbResTypeIo].Start + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE - 1;

   /* Mem Mapped IO Information
   *
   * Base  - Config Mem End for this segment
   * Start - Config Mem End for this segment
   * End   - Ecam size of maximum available bus under this segment
   */
   pstatus = pcie_rp_get_mem_resources (RootPortIndex, PCIE_RESOURCE_NON_PREFETCH_MEM_SPACE, &mem_cfg);
   if (pstatus != PCIE_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "Unable to get mem resource %d\r\n", RootPortIndex));
      return EFI_NOT_FOUND;
   }

   // TODO: cleanup, this is because of indirect dependency on the restypeio resource  adjustment
   mem_cfg.pa += PCIE_SINGLE_BUS_ADDR_SPACE_SIZE;
   mem_cfg.sz -= PCIE_SINGLE_BUS_ADDR_SPACE_SIZE;

   ResAperture[PciRbResTypeMem].Base = mem_cfg.pa;
   ResAperture[PciRbResTypeMem].Start = mem_cfg.pa;
   ResAperture[PciRbResTypeMem].End = mem_cfg.pa +  mem_cfg.sz - 1;

   pstatus = pcie_rp_get_mem_resources (RootPortIndex, PCIE_RESOURCE_PREFETCHABLE_MEM_SPACE, &mem_cfg);
   if (pstatus != PCIE_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "Unable to get mem resource %d\r\n", RootPortIndex));
      return EFI_NOT_FOUND;
   }
   /* Prefetchable Mem Map Information
   *
   * Base  - Config Mem End for this segment
   * Start - Config Mem End for this segment
   * End   - Ecam size of maximum available bus under this segment
   */
   ResAperture[PciRbResTypePMem].Base = mem_cfg.pa;
   ResAperture[PciRbResTypePMem].Start = mem_cfg.pa;
   ResAperture[PciRbResTypePMem].End = mem_cfg.pa +  mem_cfg.sz - 1;

   return EFI_SUCCESS;
}

EFI_STATUS
PcieConfigLibGetSegmentNumber (UINT32 RootPortIndex, UINT32 *SegPtr)
{
   if (pcie_rp_is_port_link_up (RootPortIndex) == 0)
      return EFI_NOT_FOUND;

   if (pcie_rp_get_hw_idx (RootPortIndex, SegPtr) == PCIE_SUCCESS)
      return EFI_SUCCESS;

   return EFI_NOT_FOUND;
}

EFI_STATUS
PcieConfigLibSetupIoSpace (UINT32 RootPortIndex, UINT64 Base, UINT64 Limit, UINT64 IOAddr)
{
   pcie_status_t        status;

   status = pcie_rp_setup_io_space_ATU (RootPortIndex, Base, Limit, IOAddr);

   if (status != PCIE_SUCCESS)
      DEBUG ((EFI_D_ERROR, "Pcie ATU setup for IO Space Failed\r\n"));

   return EFI_SUCCESS;
}

