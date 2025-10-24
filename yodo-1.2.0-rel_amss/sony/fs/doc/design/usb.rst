===
USB
===

The XFL uses the Kernel USB gadget configfs interface to communicate with the
host.

Kernel
======

To handle flashing of multiple devices on a single host PC iSerial of the USB
device descriptor is forced to zero. This needs to be done by applying a kernel
patch, see example http://review.sonyericsson.net/#/c/1659607/. The patch is
controlled by the added kernel config CONFIG_USB_ANDROID_PRODUCTION which needs
to be set to 'y' in the XFL environment.

User space
==========

The XFL is configuring the USB using the Kernel USB gadget configfs interface
to access the serial gadget driver. The Linux Kernel provides documentation
included in the mainline git (Documentation/usb).

The user space USB implementation is located in the fs/main git
(integration/linux/ffs.c). The C implementation sets the USB descriptors and
handles the read and write of USB data. The configuration of the USB is done
using either the init.rc script in an Android specific environment or as a
generic shell script. Both variants of the configuration implementations are
included in the fs/ramdisk git (loader.init.rc and rcS respectively).
