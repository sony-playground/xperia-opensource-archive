#ifndef __USB4INITDXE_H__
#define __USB4INITDXE_H__
#if 0
#include <Uefi.h>
#include <Guid/EventGroup.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIUsbConfig.h>
#endif
#include <Protocol/EFIUsb4Protocol.h>
#include <Uefi.h>
//#include <Guid/EventGroup.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
//#include <Library/MemoryAllocationLib.h>
//#include <Protocol/EFIUsbConfig.h>
//#include <Protocol/EFIUsbInitProtocol.h>

#define USB4_PROTOCOL_INIT_SIGNATURE   SIGNATURE_32 ('u', 's', 'b', 'p')

typedef struct _USB4_PROTOCOL_CTXT USB4_PROTOCOL_CTXT;


// Terminate output with a newline, and eliminate the need for double parens.
#define DBG(EfiD, Str, args...) \
  DEBUG ((EfiD, "%a: " Str "\n",__FUNCTION__, ##args));

// For debug stack info.
#define FNC_ENTER_MSG() DBG (EFI_D_INFO, "++")
#define FNC_LEAVE_MSG() DBG (EFI_D_INFO, "--")

// Cannot continue, exit function.
#define ERR_CHK(ErrStr, ...) \
  do { \
    if (EFI_ERROR (Status)) { \
      DBG (EFI_D_ERROR, ErrStr, ##__VA_ARGS__); \
      goto ON_EXIT; \
    } \
  } while (0)

// Highly undesirable, but continue anyway.
#define WRN_CHK(WrnStr, ...) \
  do { \
    if (EFI_ERROR (Status)) { \
      DBG (EFI_D_WARN, WrnStr, ##__VA_ARGS__); \
    } \
  } while (0)


#define USB4_PROTOCOL_CTXT_FROM_THIS(x)    CR(x, USB4_PROTOCOL_CTXT, Usb4InitProtocol, USB_INIT_DEV_SIGNATURE)

/**
* Usbfn software device structure.
*/
struct _USB4_PROTOCOL_CTXT {
  UINTN                         Signature;
  USB4_PROTOCOL                 Usb4Protocol;
};

EFI_STATUS
EFIAPI
Usb4InitDriverEntryPoint(
  IN EFI_HANDLE           ImageHandle
  );

#endif /* __USB4ClientUsb3_H__ */

