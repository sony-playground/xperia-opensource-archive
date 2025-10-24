/** @file RscDxe.c

  This file inits RSC driver.

  Copyright (c) 2020, 2021, Qualcomm Technologies Inc. All rights
  reserved.

**/

/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Protocol/EFIRsc.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIHWIO.h>
#include <Library/UefiBootServicesTableLib.h>
#include  <Library/rsc.h>

/*=========================================================================
      Globals and prototypes
==========================================================================*/

STATIC EFI_HANDLE gRscProtocolHandle = NULL;

/**
 * <!-- rsc_pcie_clock_init -->
 *
 * @brief Initialize clock needed for pCIE RSC hardware block
 *
 * @return EFI_SUCCESS or error values
 */
STATIC EFI_STATUS rsc_pcie_clock_init(void)
{
  UINTN      ClockId;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_CLOCK_PROTOCOL *pClockProtocol = NULL;
  const char *Clocks[] =
  {
    "gcc_pcie_rscc_xo_clk",   /* Enables RSC HW block */
    "gcc_pcie_rscc_ahb_clk",  /* Enables access to RSC registers */
  };

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL,
                               (VOID **)&pClockProtocol);
  if (EFI_ERROR(Status) || !pClockProtocol)
  {
    DEBUG((EFI_D_WARN, "%a: Clock LocateProtocol failed\r\n", __func__));
    return Status;
  }

  for (int i = 0; i < ARRAY_SIZE(Clocks); i++)
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, Clocks[i], &ClockId);
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: GetClockID failed %s\r\n", __func__, Clocks[i]));
      return Status;
    }

    Status = pClockProtocol->EnableClock(pClockProtocol, ClockId);
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: EnableClock failed %s\r\n", __func__, Clocks[i])); 
      return Status;
    }
  }

  return Status;
}

/**
 * <!-- rsc_cam_clock_init -->
 *
 * @brief Initialize clock needed for cam RSC hardware block
 *
 * @return EFI_SUCCESS or error values
 */
STATIC EFI_STATUS rsc_cam_clock_init(void)
{
  UINTN      ClockId;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_CLOCK_PROTOCOL *pClockProtocol = NULL;
  const char *Clocks[] =
  {
    "gcc_camera_ahb_clk",
	"cam_cc_titan_top_gdsc",
	"cam_cc_drv_ahb_clk",
	"cam_cc_drv_xo_clk",
	"cam_cc_core_ahb_clk",
	"cam_cc_cpas_ahb_clk",
  };

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL,
                               (VOID **)&pClockProtocol);
  if (EFI_ERROR(Status) || !pClockProtocol)
  {
    DEBUG((EFI_D_WARN, "%a: Clock LocateProtocol failed\r\n", __func__));
    return Status;
  }

  for (int i = 0; i < ARRAY_SIZE(Clocks); i++)
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, Clocks[i], &ClockId);
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: GetClockID failed %s\r\n", __func__, Clocks[i]));
      return Status;
    }

    Status = pClockProtocol->EnableClock(pClockProtocol, ClockId);
	
	
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: EnableClock failed %s\r\n", __func__, Clocks[i])); 
      return Status;
    }
  }

  return Status;
}

/**
 * <!-- rsc_cam_clock_deinit -->
 *
 * @brief Deinitialize clock needed for cam RSC hardware block
 *
 * @return EFI_SUCCESS or error values
 */
STATIC EFI_STATUS rsc_cam_clock_deinit(void)
{
  UINTN      ClockId;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_CLOCK_PROTOCOL *pClockProtocol = NULL;
  const char *Clocks[] =
  {
    "gcc_camera_ahb_clk",
	"cam_cc_titan_top_gdsc",
	"cam_cc_drv_ahb_clk",
	"cam_cc_drv_xo_clk",
	"cam_cc_core_ahb_clk",
	"cam_cc_cpas_ahb_clk",
  };

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL,
                               (VOID **)&pClockProtocol);
  if (EFI_ERROR(Status) || !pClockProtocol)
  {
    DEBUG((EFI_D_WARN, "%a: Clock LocateProtocol failed\r\n", __func__));
    return Status;
  }

  for (int i = ARRAY_SIZE(Clocks)-1; i >=0 ; i--)
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, Clocks[i], &ClockId);
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: GetClockID failed %s\r\n", __func__, Clocks[i]));
      return Status;
    }

    Status = pClockProtocol->DisableClock(pClockProtocol, ClockId);
	
	
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "%a: DisableClock failed %s\r\n", __func__, Clocks[i])); 
      return Status;
    }
  }

  return Status;
}

/**
 * <!-- rsc_map_regions -->
 *
 * @brief Setup virtual memory needed for accessing RSC hardware block
 *
 * @return EFI_SUCCESS or error values
 */
STATIC EFI_STATUS rsc_map_regions(void *pHandle)
{
    EFI_HWIO_PROTOCOL *HWIOProtocol = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    rsc_handle rsc = (rsc_handle)pHandle;

    Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL,
                                 (void**)&HWIOProtocol);
    if ((EFI_ERROR(Status) || !HWIOProtocol))
    {
        DEBUG((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
        return Status;
    }

    Status = HWIOProtocol->MapRegionByAddress(HWIOProtocol, rsc->phys_addr, &rsc->addr);
    if (EFI_ERROR(Status))
        DEBUG((EFI_D_ERROR, "ERROR: Failed to MapRegion: 0x%08x\n", rsc->phys_addr));

    return Status;
}

/**
 * <!-- EFI_rsc_instance_init -->
 *
 * @brief Initialize the RSC instance
 *
 * @param[in]  name    The instance name like "cam", "apps"
 * @param[out] pHandle  The pHandle of the instance that was requested.
 *
 * @return  EFI_SUCCESS or error values
 */
STATIC EFI_STATUS EFI_rsc_instance_init(const char *name, void **pHandle)
{
  rsc_result_t res;
  EFI_STATUS Status;
  rsc_handle *rsc = (rsc_handle *)pHandle;

  if (1 != rsc_get_handles(name, 1, rsc))
    return EFI_NO_MAPPING;

  Status = rsc_map_regions(*rsc);
  if (EFI_ERROR(Status))
    return Status;

  /* Initialize the RSC clock for PCIE */
  if (rsc_is_pcie(*rsc))
  {
    Status = rsc_pcie_clock_init();
    if (EFI_ERROR(Status))
      return Status;
  }

  /* Initialize the RSC clock for CAM */

   if (rsc_is_cam(*rsc))
  {
    Status = rsc_cam_clock_init();
    if (EFI_ERROR(Status))
      return Status;
  }


  res = rsc_instance_init(*rsc);
  if(res != RSC_SUCCESS)
  {
    *rsc= NULL;
    return EFI_LOAD_ERROR;
  }



  /* Set up the default low power mode for the RSC */
    res = rsc_set_low_power_mode(*rsc, 0);
    if(res != RSC_SUCCESS)
      return EFI_LOAD_ERROR;

  /* Deinitialize the RSC clock for CAM */
   if (rsc_is_cam(*rsc))
  {
    Status = rsc_cam_clock_deinit();
    if (EFI_ERROR(Status))
      return Status;
  }
  
  return EFI_SUCCESS;
}



/**
 * <!-- EFI_rsc_pcie_disable_force_wake -->
 *
 * @brief Disable force wake after intializing the PLIMs
 *
 * @param[in] handle The handle of the instance that was requested.
 *
 * @return  EFI_SUCCESS or error values
 */
 
 /*
STATIC VOID EFI_rsc_pcie_disable_force_wake(void *pHandle)
{
  rsc_pcie_disable_force_wake(pHandle);
}
*/
STATIC EFI_RSC_PROTOCOL RscProtocol =
{
  EFI_RSC_PROTOCOL_REVISION,
  EFI_rsc_instance_init,
//EFI_rsc_pcie_disable_force_wake,
};

/**
 * Entry point for the Rsc DXE driver.
 */
EFI_STATUS EFIAPI RscDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status;
  VOID                       *RscHandle = NULL;
  EFI_RSC_PROTOCOL           *RscProtocolIntf = NULL;

  rsc_driver_init();

  Status = gBS->InstallProtocolInterface(&gRscProtocolHandle,
                                         &gEfiRscProtocolGuid,
                                         EFI_NATIVE_INTERFACE,
                                         &RscProtocol);
										 
										 
 


  Status = gBS->LocateProtocol (&gEfiRscProtocolGuid, NULL,
                               (VOID **)&RscProtocolIntf);

  //Initialize RSCC including turning on clocks and init RSC seq memory
  Status = RscProtocolIntf->rsc_instance_init("cam", &RscHandle);
  
  Status = RscProtocolIntf->rsc_instance_init("pcie", &RscHandle);

  return Status;
}
