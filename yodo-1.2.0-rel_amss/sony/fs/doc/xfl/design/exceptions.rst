***********************
Startup Flow Exceptions
***********************

Below are some exceptions which might occur during development cycle:

- "Setup TA" fails:

  1. Most likely partition list does not contain the TA partition.

- "Init OTP write" or "Read secure property" fails:

  1. Early in development cycle the TZ communication service is not
     integrated in kernel.

  2. The fuse/xflattest tz application is missing in xfl tz applications
     partition.

