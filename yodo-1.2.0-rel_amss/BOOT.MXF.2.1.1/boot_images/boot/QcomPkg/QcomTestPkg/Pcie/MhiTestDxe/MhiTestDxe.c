/** 
 * MHI Host Protocol interface
 *  
 * Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/21/21   nr      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EfiQcMhi.h>
#include "pcie_host_r.h"
#include "mhi.h"

STATIC EFI_HANDLE  gMhiDxeHandle = NULL;

static EFI_QC_MHI_DXE_PROTOCOL MhiDxeProtocol =
{
  EFI_QC_MHI_PROTOCOL_VERSION,
  .Register      = (MHI_REGISTER)mhi_register,
  .Unregister    = (MHI_UNREGISTER)mhi_unregister,
  .OpenDevice    = (MHI_DEV_OPEN)mhi_dev_open,
  .CloseDevice   = (MHI_DEV_CLOSE)mhi_dev_close,
  .TransferImage = (MHI_TRANSFER_IMAGE)mhi_transfer_image,
  .ExecuteBhie   = (MHI_EXECUTE_BHIE)mhi_execute_bhie,
  .GetExecEnv    = (MHI_GET_EE)mhi_get_ee,
  .GetState      = (MHI_GET_STATE)mhi_get_state,
  .ChannelOpen   = (MHI_CHANNEL_OPEN)mhi_channel_open,
  .ChannelClose  = (MHI_CHANNEL_CLOSE)mhi_channel_close,
  .ChannelWrite  = (MHI_CHANNEL_WRITE)mhi_channel_write,
  .ChannelRead   = (MHI_CHANNEL_READ)mhi_channel_read,
};

EFI_STATUS
EFIAPI
QcMhiDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   EFI_STATUS Status = EFI_SUCCESS;
   mhi_status_t status;

   pcie_enable_test_environment();
   status = mhi_init();
   if (status != MHI_SUCCESS)
      return EFI_UNSUPPORTED;

   AsciiPrint ("MhiTestDxe : %a %a\r\n", __DATE__, __TIME__);

   Status = gBS->InstallMultipleProtocolInterfaces(
                    &gMhiDxeHandle,
                    &gEfiQcMhiDxeProtocolGuid,
                    (void **)&MhiDxeProtocol,
                    NULL);

   return Status;
}
