===============
Vendor fastboot
===============

Introduction
============

This document describes the requirements on the vendor fastboot implementation,
that is the modifications SOMC needs to do on this implementation.

Stakeholders
------------

FCS (Flash core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

Developer World Alin Jerpelea <Alin.Jerpelea@sonymobile.com>

Platforms
---------

* Yoshino
* Nile
* Tama

Terminology
-----------
1. RCK

    The Rooting Control Key (RCK) is a 16 hex digit code used for unlocking
    the bootloader.

2. DK (Device Key)

    The Device Key is used to encrypt the DRM certificates.

See :doc:`xfl` for other terminology

Supported fastboot commands and variables
=========================================


Commands
--------

The following fastboot commands SHALL be supported by the vendor fastboot
implementation:

**Generic**

* fastboot flash
* fastboot erase
* fastboot continue
* fastboot reboot
* fastboot reboot-bootloader
* fastboot getvar
* fastboot download
* fastboot oem unlock

**Nile, Tama**

* fastboot set_active

**Kumano**

* fastboot oem lock

Variables
---------

The following variables SHALL be available through the getvar command:

**Generic**

* max-download-size
* product
* secure
* serial
* serialno
* version-baseband
* version-bootloader

**Nile, Tama**

* slot-count
* slot-successful
* slot-retry-count
* current-slot


Requirements
============

Security
--------

#. fastboot command 'oem unlock' SHALL check the
   ROOTING_ALLOWED tag in SIMLock before allowing unlock.

   The SIMLock MUST have tag ROOTING_ALLOWED="1" or ROOTING_ALLOWED="2", otherwise
   unlock SHALL NOT be allowed. If the tag is ROOTING_ALLOWED="2", the
   SIMLock MUST be unlocked, otherwise unlock SHALL NOT be allowed.

#. The device MUST NOT have had an XCS keystore during its lifetime.

#. fastboot oem unlock SHALL check the miscTA unit 66671
   (TA_GOOGLE_LOCK_STATE). The unit MUST be empty, otherwise unlock
   SHALL NOT be allowed.

#. fastboot oem unlock SHALL check whether the bootloader is
   already unlocked.

#. fastboot oem unlock SHALL require an unlock code (RCK) to be
   able to unlock. The SHA-256 hash of the RCK MUST match the stored RCK_H
   value in the SIMLock data.

#. When fastboot oem unlock is executed the following actions
   SHALL be performed:

   * Erase the Device Key (miscTA unit 66667 - TA_DEVICE_KEY)
   * Secure erase user sensitive partitions
   * Reset rollback counters in secure storage
   * Set miscTA unit 2550 (TA_MASTER_RESET) to 0x1
   * Write recovery message to the misc partition

#. When fastboot oem lock is executed the following actions
   SHALL be performed:

   * Secure erase user sensitive partitions
   * Reset rollback counters in secure storage
   * Set miscTA unit 2550 (TA_MASTER_RESET) to 0x1
   * Write recovery message to the misc partition

#. The fastboot flash and fastboot erase commands MUST NOT be possible to
   execute when the bootloader is locked.

#. The list of partitions possible to flash or erase on an unlocked and
   fused device SHALL be restricted to:

   **Generic**

   * boot
   * system
   * vendor
   * userdata
   * oem

   **Yoshino**

   * odm
   * cache
   * recovery (remapped to FOTAKernel)
   * FOTAKernel

   **Tama**

   * dtbo
   * vbmeta

   **Huaihe**

   * odmdtbo
   * vbmeta

   For an unfused (development) and unlocked device, flashing and erasing
   SHALL be allowed on any partition.

Identification
--------------
#. USB IDs

   The vendor fastboot SHALL use the SOMC VID (0x0FCE) and PID (0x0DDE).

#. Serial number

   The vendor fastboot SHALL present the SOMC device serial number (MSN, ASCII
   representation of TA 4900) when the client issues the 'fastboot devices'
   command.
