********************************************************************************
**                      UEFI Usbfn Loopback Application                       **
**                                                                            **
**                See go/usbtp for setup and host tool usage                  **
********************************************************************************

This UEFI application is used to validate the functionality of a UsbfnIo
protocol implementation. It performs various tests to ensure that the exposed
functions work when expected and fail when expected. To test the USB
functionality, a loopback mode is supported in which the device enumerates as
a "Qualcomm Mary Samsonite Profiling Board (COM#)" when attached to a host PC.
This USB configuration exposes a pair of bulk endpoints which are used for raw
throughput testing by the companion host PC application USBTP. See go/usbtp for
further details on the host tool and overall usage.

To run the application, enter the following at the EBL shell:
EBL >start fv2:\UsbfnTest

By default, the application only performs the protocol tests and exits. To
enter loopback mode for throughput testing the 'l' switch is required. Run with
the 'h' switch for complete usage details.


Zero Length Termination (ZLT)
********************************************************************************
ZLT refers to a protocol level contract between the host and device software to
terminate any bulk data transfer which is a multiple of the endpoint's maximum
packet size with a zero length packet. Due to the design of the host USBTP
tool, ZLT is always required by both host and device (ZLT always enabled means
the device and host both send zero length packets only when the transfer size
is a multiple of the maximum packet size, and don't otherwise). This
application supports ZLT via two mechanisms, so called "Application Driven ZLT"
and "Usbfn Driven ZLT". 

Application Driven ZLT
  This is the default behavior in which any ZLT support provided by the
  underlying Usbfn driver is disabled and the application explicitly submits
  zero length buffers for transfer following the completion of a transfer
  whose length was a multiple of the maximum packet size.

Usbfn Driven ZLT
  This mode is selected by passing the 'z' switch on the command line. When
  selected, the application will query Usbfn to determine if ZLT is supported
  on each direction of the bulk endpoint used for data transfers. If ZLT is
  supported on a given endpoint direction it is enabled and the application
  will not submit zero length buffers for transfer. Application driven ZLT is
  automatically enabled for endpoint direction(s) which don't support ZLT.

Supporting both these mechanisms allows this tool to more thoroughly test the
functionality of the underlying Usbfn implementation. It is recommended to run
tests using both ZLT modes after modifications to a Usbfn driver. Regardless of
which mode is selected a message will be printed showing which mode is active
for each endpoint direction.


Endpoint Buffer Validation
********************************************************************************
The Usbfn protocol is expected to return the same buffer pointer submitted by
the application for transfer in any EndpointStatusChanged event pertaining to
that transfer. Should an unexpected buffer pointer be returned by Usbfn, a
warning message will be printed informing the user of a bug in the Usbfn
implementation but the in progress throughput test will be otherwise unaffected.

