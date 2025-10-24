/** @file
 *  DTB protocol installation
 *
 * Copyright (c) 2021 Qualcomm Technologies Inc. All rights reserved.
 *
 * Portions Copyright (c) 2008-2014 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/29/21   ai      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <PiDxe.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DTBDefs.h>
#include <Protocol/EFIDtbExtn.h>

extern EFI_GUID gEfiDtbExtnProtocolGuid;
extern EFI_GUID gEfiDtbExtnIntfHobGuid;

EFI_DTB_EXTN_PROTOCOL gDtbExtnProtocol;

EFI_DTB_EXTN_PROTOCOL*
GetDtbExtnIntf (VOID)
{
  EFI_HOB_GUID_TYPE *GuidHob;
  UINTN** DataPtr;

  GuidHob = GetFirstGuidHob (&gEfiDtbExtnIntfHobGuid);

  if (GuidHob == NULL)
    return NULL;

  DataPtr = GET_GUID_HOB_DATA (GuidHob);
  return (EFI_DTB_EXTN_PROTOCOL*) *DataPtr;
}

EFI_STATUS
InstallDtbExtnProtocol (VOID)
{
  EFI_DTB_EXTN_PROTOCOL *DtbExtnIntfPtr;
  EFI_STATUS  Status = EFI_NOT_FOUND;
  EFI_HANDLE  Handle = NULL;

  DtbExtnIntfPtr = GetDtbExtnIntf ();
  if (DtbExtnIntfPtr == NULL)
    return EFI_NOT_FOUND;

  gDtbExtnProtocol = *DtbExtnIntfPtr;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiDtbExtnProtocolGuid, &gDtbExtnProtocol,
                  NULL
                  );

  return Status;
}
