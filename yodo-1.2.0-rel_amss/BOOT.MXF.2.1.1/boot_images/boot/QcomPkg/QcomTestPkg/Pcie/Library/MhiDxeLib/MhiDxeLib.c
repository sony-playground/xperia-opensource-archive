/** 
 * MHI Host Driver protocol interface
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
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EfiQcMhi.h>
#include "mhi.h"

static EFI_QC_MHI_DXE_PROTOCOL *MhiDxeProtocol;

EFI_STATUS
EFIAPI
MhiDxeLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   EFI_STATUS Status = EFI_SUCCESS;

   Status = gBS->LocateProtocol (&gEfiQcMhiDxeProtocolGuid,
                                NULL,
                                (VOID**)&MhiDxeProtocol);
   return Status;
}

mhi_status_t mhi_register(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->Register ((MHI_DEVICE_ID)dev_id, (MHI_CB*)cb);

   return MHI_ERROR;
}

mhi_status_t mhi_unregister(mhi_dev_id_t dev_id, mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->Unregister ((MHI_DEVICE_ID)dev_id, (MHI_CB*)cb);

   return MHI_ERROR;
}

mhi_status_t mhi_dev_open(const mhi_dev_info_t *dev_info, mhi_cb_t *cb, mhi_handle_t *dev_h)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->OpenDevice ((const MHI_DEV_INFO *)dev_info, 
                                                       (MHI_CB*)cb,
                                                       (MHI_HANDLE)dev_h);

   return MHI_ERROR; 
}

mhi_status_t mhi_dev_close(mhi_handle_t dev_h, mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->CloseDevice ((MHI_HANDLE)dev_h, (MHI_CB*)cb);

   return MHI_ERROR;
}

mhi_status_t mhi_transfer_image(mhi_handle_t dev_h, void *image, size_t size)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->TransferImage ((MHI_HANDLE)dev_h, image, size);

   return MHI_ERROR;
}

mhi_status_t mhi_execute_bhie(mhi_handle_t dev_h, void *image, size_t size)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->ExecuteBhie ((MHI_HANDLE)dev_h, image, size);

   return MHI_ERROR;
}

mhi_status_t mhi_get_ee(mhi_handle_t dev_h, mhi_ee_t *ee)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->GetExecEnv ((MHI_HANDLE)dev_h, (MHI_EXEC_ENV*)ee);

   return MHI_ERROR;  
}

mhi_status_t mhi_get_state(mhi_handle_t dev_h, mhi_state_t *state)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->GetState ((MHI_HANDLE)dev_h, (MHI_STATE*)state);

   return MHI_ERROR;  
}

mhi_status_t mhi_channel_open(mhi_handle_t dev_h, uint32 ch_id, mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->ChannelOpen ((MHI_HANDLE)dev_h, ch_id, (MHI_CB*)cb);

   return MHI_ERROR;
}

mhi_status_t mhi_channel_close(mhi_handle_t dev_h, uint32 ch_id)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->ChannelClose ((MHI_HANDLE)dev_h, ch_id);

   return MHI_ERROR;
}

mhi_status_t mhi_channel_write(mhi_handle_t dev_h, 
                               uint32 ch_id, 
                               void *buf, 
                               uint32 size, 
                               uint32 *bytes_written, 
                               mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->ChannelWrite ((MHI_HANDLE)dev_h, 
                                                         ch_id,
                                                         buf,
                                                         size,
                                                         bytes_written,
                                                         (MHI_CB*)cb);

   return MHI_ERROR;
}

mhi_status_t mhi_channel_read(mhi_handle_t dev_h, 
                              uint32 ch_id, 
                              void *buf, 
                              uint32 size, 
                              uint32 *bytes_read,
                              boolean *eot,
                              mhi_cb_t *cb)
{
   if (MhiDxeProtocol)
      return (mhi_status_t)MhiDxeProtocol->ChannelRead((MHI_HANDLE)dev_h, 
                                                        ch_id,
                                                        buf,
                                                        size,
                                                        bytes_read,
                                                        eot,
                                                        (MHI_CB*)cb);

   return MHI_ERROR;
}
