======================
Boot support
======================

Introduction
============

The Boot support functionality (XBoot) is delivered as header files and
source code to be integrated into target environment.

Git
===

**Git:**

  * platform/vendor/semc/fs/main

Interfaces
===========
**XBoot user interface:**

  boot/include/xboot_glue.h

**XBoot PAL interface (see below):**

  boot/include/xboot_pal_types.h

**XBoot core dependencies (see below):**

  boot/include/xboot_pal_includes.h


Source:
=======
**XBoot main source:**

  * boot/xboot_glue.c
  * boot/src/\*.c

**XBoot core source:**

  * Include directory:

    * core/include
    * core/util/include
    * core/ks/include
  * Source:

    * core/*

**XBoot core dependency source (platform specific):**

  * 8998:

    * integration/common/eroot.c
    * integration/qc/include
    * integration/8998/include/
    * integration/8998/fcs_roots.c
    * integration/8998/core_xboot.c
    * xflcertificate (*git: platform/vendor/semc/s1/s1certificate*)


Requirements on Boot integrator
===============================

XBoot PAL (xboot_pal_types.h)
-----------------------------

The boot integrator needs to provide implementation of a set of
functions described in the PAL interface.

Core dependencies (xboot_pal_includes.h)
----------------------------------------


**The core needs the following support functionality from target system:**
  - Standard C library with Heap
  - TA Library implementation
  - Crypto functionality, see crypto.txt
  - Parts of core.h:

    - core_is_fused
    - core_get_dieid
    - core_get_dieid_len
    - core_is_test_cert_allowed

    Implementation existing platforms can be found in git folder *integration*.
  - Embedded roots defined by eroot.h:

    Implementation for existing platforms can be found in git folder *integration*.
    The integrator might need to integrate an additional git for
    embedded root certificates.

