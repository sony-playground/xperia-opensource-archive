********
General
********

This test framework aims to test the xmodem library (Part of Flash Core Security GIT).
Besides verifying the implementation through the interfaces (fcs git: /modem/include), it
should also be possible to run the test system on multiple platforms, like Ubuntu and Target,
with small changes.

The system is divided into two parts which represent:

   * Host machine/ User
   * Device

The host is active during the whole test session (multiple test cases) and is reponsible for
starting the device for the current test case.

The device is only active during the test case and will be shutdown/restarted between test cases.

