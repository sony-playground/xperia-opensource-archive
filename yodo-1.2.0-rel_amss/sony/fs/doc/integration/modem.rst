======================
Modem support
======================

Introduction
============

The Modem support functionality (XModem) is delivered as header files and
source code to be integrated into target environment. See picture below:

.. raw:: latex

    \clearpage

.. uml::
   :caption: Modem Integration Overview
   :align: center

   package "Modem" {
      frame "Vendor Core System" as VCS {
         [Modem SW]
         frame "Adaption interface" {
            interface "IMEI" as CSIMEI
            interface "Simlock" as CSSL
         }
      }

      frame "Adaption to Core System" as ACS {
         [Sony IMEI Integration]
         [Sony Simlock Integration]
      }

      frame "Adaption to Application" as AA {
         [Sony MiscTA Integration]
      }

      frame "Sony XModem" as SX {
         [IMEI Verification/Extraction]
         [Simlock Verification]
      }

      frame "Adaption to XModem" as AXM {
         [XModem Support Functions]
      }

      frame "Crypto Library" as CL {
         [MbedTLS]
      }

   }

   package "Application" {
      frame "OS (Android)" {
         [MiscTA Access]
      }

      frame "Storage" {
         [MiscTA partition]
      }
   }

   [Modem SW] <- CSIMEI
   [Modem SW] <-> CSSL
   CSIMEI <- [Sony IMEI Integration]
   CSSL <-> [Sony Simlock Integration]
   [Sony IMEI Integration] <-> [IMEI Verification/Extraction]
   [Sony Simlock Integration] <-> [Simlock Verification]
   [IMEI Verification/Extraction] <- [MbedTLS]
   [IMEI Verification/Extraction] <- [XModem Support Functions]
   [Simlock Verification] <- [MbedTLS]
   [Simlock Verification] <- [XModem Support Functions]
   [Sony Simlock Integration] <-> [Sony MiscTA Integration]
   [XModem Support Functions] <- [Sony MiscTA Integration]
   [Sony MiscTA Integration] <-> [MiscTA Access]
   [MiscTA Access] <-> [MiscTA partition]

   note left of VCS : is (mainly) provided by chip vendor
   note right of ACS : is provided by modem integrator
   note right of AA : is provided by modem integrator
   note left of SX : is provided by Flash Core Security
   note left of AXM : is provided by modem integrator
   note right of CL : is integrated by modem integrator

.. raw:: latex

    \clearpage

Platforms using integration
===========================

None (older platforms use secmgr interface)

Git
===

**Git:**

  * platform/vendor/semc/fs/main

Interfaces
===========
**XModem user interface:**

  modem/include/xmodem.h


Source:
=======
**XModem main source:**

  * modem/src/\*.c

**XModem core source:**

  * Include directory:

    * core/include
    * core/util/include

  * Source:

    * core/*

**XModem core dependency source (platform specific):**

  * tama:

    * integration/tama/include

**XModem crypto (mbedtls) dependency source:**

  * Include directory:

    * integration/crypto/mbedtls/include

  * Source:

    * integration/crypto/mbedtls/core.c
    * integration/crypto/mbedtls/certificate_chain.c
    * integration/crypto/mbedtls/signature.c
    * integration/crypto/mbedtls/digest.c
    * integration/crypto/mbedtls/rule.c
    * xflcertificate (git: platform/vendor/semc/s1/s1certificate)


Requirements on Modem integrator
================================
**Implement support functions:**

  * core/include/core.h:

    * core_is_fused
    * core_is_test_cert_allowed
    * core_get_dieid
    * core_get_dieid_len

  * core/include/eroot.h:

    * get_embedded_roots
    * free_embedded_roots

    The integrator might need to integrate an additional git for
    embedded root certificates.

  * core/include/ta_interface.h:

    * ta_init
    * get_ta_unit_size
    * read_ta

  * core/include/fcslog.h ( If CFG_ENABLE_FCS_LOG is defined ):

    * fcslog

**Integrate crypto library mbedtls:**

  * Git: platform/vendor/semc/fs/mbedtls

  * Configuration for mbedtls should be defined:

    * MBEDTLS_CONFIG_FILE="config-somc-modem.h"

  * The integrator must assure that the stack size is sufficiently large
    for all threads which are accessing the xmodem interface.

**Standard C library with Heap**

