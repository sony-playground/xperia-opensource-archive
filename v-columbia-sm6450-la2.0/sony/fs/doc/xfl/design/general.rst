********
General
********

The Xperia Flash Loader, XFL, runs as a service under a dedicated
linux kernel with no external partitions mounted.
The XFL has the following kernel dependencies:

- The flash is accessed through linux flash block devices

- USB is accessed through linux usb gadget framework.

- Secure properties are handled through trustzone applications loaded by
  XFL.

- Charging is handled through general kernel support.

- Optionally the XFL might have display support.

The git platform/vendor/semc/fs/main contains configuration and code to generate
the XFL application.

The XFL is also dependent on a crypto library, which can be mbedTLS
or OpenSSL. The crypto libraries are integrated as external android libraries
in the build system. The build parameter CFG_CRYPTOLIB defines what library to
use in XFL integration.

Two additional gits are used to configure and generate general parts of xfl image:

- platform/vendor/semc/fs/build: build (android) configuration.

- platform/vendor/semc/fs/ramdisk: configure and build ramdisk and
  kernel startup scripts.


Threads
=======

XFL is a multi-threaded application. Threads are used to speed up some operations
or do multiple jobs in parallel. Standard POSIX pthread [#pthreads]_ API is used.

Uevents handler thread [#xfl_uevent_src]_
-----------------------------------------
This thread is used for reading and parsing kernel uevents. Uevents are
received from a kernel netlink [#netlink]_ socket. Every time when a device is added,
removed or its state is changed the kernel sends an uevent to the userspace using this
socket. The XFL uses uevents to control the charging of the device and to detect
when the USB cable has been disconnected. If an USB disconnect event is detected it will
shut down the device. This thread is started when the XFL is started and it is
running constantly.

Hash calculation of an entire partition [#digest]_
--------------------------------------------------
A digest thread that calculates sha256 of a given data. It is used for the fastboot
command "Digest", to speed up the hash calculation. The thread is started and runs only
during the "Digest" command execution.

XFL Display [#display]_
-----------------------
The XFL Display feature uses 2 threads. These threads run only when the display
is enabled using the fastboot command "Enable-display". The first thread (fcsgfx_worker)
is used for drawing to the display. It reads data from a shared print buffer and draws it to
the display. The other thread (fcsgfx_worker_key) is used for waiting for an input event.
It waits for VOLUME UP, DOWN, POWER or CAMERA key press. When an input event is registered it
will call a callback function that will scroll the lines on the display or the display
brightness will be turned on, depending on the key pressed.

USB ep0 thread [#usb]_
----------------------
The XFL uses a separate thread for ep0 handling due to this node handles
asyncronous events. Due to the fastboot protocol is synchronous it is possible
for the main XFL thread to handle both in and out endpoints.


.. rubric:: Footnotes

.. [#xfl_uevent_src] Uevent handler source code: http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/integration/linux/uevent_handler.c
.. [#pthreads] Pthreads man page: http://man7.org/linux/man-pages/man7/pthreads.7.html
.. [#netlink] Netlink man page: http://man7.org/linux/man-pages/man7/netlink.7.html
.. [#digest] Digest thread source code: http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/loader/protocol/protocol_util.c#595
.. [#display] XFL display source code: http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/loader/gfx/fcsgfx.cc
.. [#usb] USB gadget API framework: http://www.linux-usb.org/gadget/
