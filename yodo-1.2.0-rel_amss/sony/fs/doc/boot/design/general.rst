********
General
********

This describes how the core functions in git platform/vendor/semc/fs/main are
integrated to the Xboot.

The main interface is the XBootGlueLib, functions are defined in xboot_glue.h.
The functions should be called from XBootLib, which is the UEFI interface to
the core functions.

The core functions need PAL (platform abstraction layer) functions to be implemented
in the boot code. They should be defined in XBootPALApiLib.

The core functions are also dependent on a crypto library, which can be mbed TLS or
OpenSSL. mbed TLS is integrated in library MbedTLSLib in package SomcPkg, while
OpensslLib is included in the package CryptoPkg. Because of build problems
OpensslLib can not be used directly in XBootGlueLib. Instead it is integrated
in XBootCryptoLib together with the core files that use OpenSSL.

