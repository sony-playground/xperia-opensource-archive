====
Boot
====

Introduction
============
This document makes use of the practices described in [RFC2119]_ when describing
the requirements.

Each requirement specifies the stakeholder and the platforms that the
requirement is valid for. The term "Generic" implies that the requirement is valid
for all platforms listed under :ref:`boot-platforms-label`.


Stakeholders
------------

FCS (Flash Core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

FST (Flash Security Tokyo) <SG-JPTO-SW-FlashSecurity-ALL-G@sonymobile.com>

SWuP (Software Update Platform) Esbjorn Wernhoff <Esbjorn.Wernhoff@sonymobile.com>

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sonymobile.com>

Developer World Alin Jerpelea <Alin.Jerpelea@sonymobile.com>

FOTA (Firmware update Over The Air) Kvist Håkan <Hakan.Kvist@sonymobile.com>

GCIS (Global Common Indus Solution) Yuying Chen <Yuying.Chen@sonymobile.com>

XCS-SWSE (Xperia Custom Software - SW Security & Enterprise) Rimpu Varshney <Rimpu.Varshney@sonymobile.com>

CS (Customer Service)

.. _boot-platforms-label:

Platforms
---------

* Yoshino
* Tama
* Nile
* Kumano
* AG1

Definitions
-----------

**Security state**
  Hash of the keystore payload

**Default security state**
  Fuse state of the device

**Bootloader unlock state**
  Qualcomm bootloader lock state

**Secdata**
  xflattest data blob for non XFL usage

**XFL secdata**
  xflattest data blob for XFL usage

**VB**
  Verified Boot defined by Google. See https://android.googlesource.com/platform/external/avb/+/master/README.md

**VBMeta**
  metadata for VM2.0 defined by Google. See https://android.googlesource.com/platform/external/avb/+/master/README.md

**Device Binding**
  An identifier that is unique to a specific Mobile Device. This can be
  the IMEI, a hardware serial number or an identifier derived from hardware-bound
  cryptographic keys. Device binding support a list of identifiers to handle
  isolated subsystems, e.g. a separate modem. The Device Binding per platforms:

| Yoshino, Tama, Nile - Device ID
| Kumano - Device ID or the first IMEI
| Huaihe - Device ID or the first IMEI
| AG1 - List of Device ID or the first IMEI
|

Requirements
============

Boot flow
---------

1. The XFL MUST be invoked when the USB cable is connected and the service trigger defined in boot config is active

* **Stakeholders:** SWuP, FAS, GCIS
* **Platforms:** Generic

2. Google fastboot MUST be invoked when the USB cable is inserted and volume up is pressed

* **Stakeholders:** Developer World
* **Platforms:** Generic

3. The Sony FOTA kernel SHOULD be invoked when FOTA warmboot reason is set

* **Stakeholders:** FOTA
* **Platforms:** Yoshino

4. The default boot SHOULD be invoked when FOTA CACHE warmboot reason is set

* **Stakeholders:** FOTA
* **Platforms:** Yoshino

5. The RAM dumper SHOULD be invoked when FOTA CRASH or FOTA_HWWD warmboot reason
   is set

* **Stakeholders:** FOTA
* **Platforms:** Yoshino

xflattest
---------

1. The security state MUST be stored in Secdata if booting FOTA

* **Stakeholders:** FOTA
* **Platforms:** Yoshino


Keystore
--------

Valid keystore definition
~~~~~~~~~~~~~~~~~~~~~~~~~

A keystore is considered valid if:

* CMS signature is valid and chained to embedded keystore root of trust.

* CMS signature is bound to either Device Binding or HMAC Device Binding.

* The hash sum over the payload matches the hash sum saved in secure
  storage and the keystore rollback counter is greater than or equal to
  the stored keystore counter, OR the keystore is being updated.

  * The keystore is being updated if the hash sum over the payload does not
    match the hash sum saved in secure storage, the keystore rollback counter
    is greater than the rollback counter stored in secure storage, and
    the XCS flag in secure storage is not set.

* The keystore can be decoded against the ASN.1 specification of the keystore
  format.


Keystore handling
~~~~~~~~~~~~~~~~~

1. The XFL MUST be invoked if the Keystore and the Keystore backup are invalid
   and the USB cable is connected

* **Stakeholders:** FAS
* **Platforms:** Generic

2. If a valid XCS Keystore is detected in the Keystore or the Keystore backup
   partition it MUST replace any non XCS Keystore

* **Stakeholders:** FCS, XCS-SWSE
* **Platforms:** Generic

3. The Keystore backup SHOULD be replaced by the Keystore if the Keystore is
   valid

* **Stakeholders:** FCS
* **Platforms:** Generic

4. The Keystore SHOULD be replaced by the Keystore backup if the Keystore is
   invalid and the Keystore backup is valid

* **Stakeholders:** FCS
* **Platforms:** Generic

5.  The Keystore is extended with a specific domain (5) for VB2.0, VBMeta.
    There will be 3 public keys for VBMeta variants:

Development
  Development Keystore will contain all public keys used for VBMeta
PreCommercial
  Precommercial Keystore will contain the pre-commercial, and commercial public keys used for VBMeta
Commercial
  Commercial Keystore will contain only the commercial public key used for VBMeta

* **Stakeholders:** FCS
* **Stakeholders:** FST
* **Stakeholders:** FAS
* **Platforms:** Tama, Nile, Kumano, Huaihe

Boot configuration
------------------

1. It SHOULD be possible to enable/disable the backlight

   * **Stakeholders:** Operator, GCIS
   * **Platforms:** Generic
   * **Background:** A Chinese operator (in the Rhine or Shinano platform) had a
     requirement that 1st boot logo MUST be their expected image,
     not SONY.
     Hence we need to disable showing SONY logo and their expected
     logo image needs to be shown by kernel at first to meet their
     requirement.
     GCIS have a requirement that they need to enable the display
     with their timing from factory test perspective, like current
     measuring.

XCS (Xperia Custom Software)
----------------------------
* **Stakeholders:** FCS
* **Stakeholders:** Developer World
* **Stakeholders:** XCS-SWSE
* **Platforms:** Generic

1. XCS keystore MUST be bound by the Device Binding.

2. It MUST NOT be possible to use the same Key Blob for multiple Mobile Devices.

3. Boot MUST have support for masked Device Binding.
   It MUST NOT be possible to reverse or brute-force the process and
   recover the Device Binding. Boot SHOULD be able to handle masked and unmasked Device Binding.

4. Setting XCS keystore MUST NOT be allowed if unlocking of the bootloader is not allowed.

5. Setting XCS keystore MUST be allowed on devices with an unlocked bootloader.

6. After setting XCS keystore the device rooting status MUST be NOT ROOTABLE.

7. User sensitive data (the same data as when doing "bootloader unlock") MUST be deleted when XCS keystore is applied on the device.

8. Changing to XCS keystore SHOULD only be possible to perform one time per device.

9. It SHOULD be possible to enter Recovery mode.

10. Ramdump MUST NOT be allowed to boot on devices with XCS keystore.

11. If the device has XCS keystore, and the image is verified against the XCS
    keystore root of trust, boot MUST show a splash screen informing the user
    that the device will not run Sony software. Only one boot splash image SHOULD
    be shown, Sony boot logo MUST NOT be shown.

Bootloader unlock states
------------------------

* **Stakeholders:** FCS
* **Stakeholders:** FAS
* **Platforms:** Generic
* **Background:** In order to enable locking/unlocking of the bootloader through
  FG4, the xfl has support for oem lock/unlock commands. When executing
  those commands, the xfl writes data in miscTA, which is then verified by
  the boot on the next boot up, and if valid, the bootloader is locked or
  unlocked respectively.

1. If MiscTA Unit 2226 (TA_RCK) is not empty, the boot SHALL check whether unlocking of the bootloader is allowed.

  If unlocking of the bootloader is allowed and the RCK is valid, the bootloader SHALL be unlocked.
  Before unlocking the bootloader, user sensitive data, as well
  as MiscTA Unit 66667 (TA_DEVICE_KEY) MUST be erased, and MiscTA Unit 2550 (TA_MASTER_RESET) SHALL
  be set to 0x1.
  Recovery message SHALL be written to the misc partition.
  Rollback counters in secure storage SHALL be reset.
  MiscTA Unit 2226 MUST be erased after the check.
  After unlocking the bootloader, the device SHALL reboot into recovery mode.

2. The boot SHALL check if MiscTA Unit 2334 contains the AUTH_CH_OEM_LOCK command.

  If authentication level is production, the bootloader SHALL be locked.
  Before locking the bootloader, user sensitive data MUST be erased.
  MiscTA Unit 2550 (TA_MASTER_RESET) SHALL be set to 0x1.
  Recovery message SHALL be written to the misc partition.
  After locking the bootloader, the device SHALL reboot into recovery mode.

Auto set OEM unlocking flag
---------------------------
* **Stakeholders:** FCS
* **Stakeholders:** Developer World
* **Stakeholders:** XCS-SWSE
* **Platforms:** Generic
* **Background:** Unlocking of the bootloader is not allowed if OEM unlocking
  checkbox is not checked in the developer options under Settings menu.
  This is part of Google factory reset protection feature that is enabled by
  default from factory. Our XCS partners might want to unlock a lot of units
  and it is cumbersome to start every unit and manually check this flag.
  By flashing a signed message the bootloader should set this flag, thus allowing
  unlocking of the bootloader.

.. note::
  There are also other conditions that needs
  to be fulfilled for allowing unlocking of the bootloader: SIMLock must be
  valid and it should allow unlocking.

#. If there is CMS signed message flashed (MiscTA unit 2234) bootloader MUST verify it.

#. Bootloader MUST check if there is Google account set on the device by parsing the
   frp partition.

#. If there is no Google account set on the device and a valid CMS message is present,
   bootloader MUST set the OEM unlocking flag (erase MiscTA unit 66671).

#. MiscTA unit 2234 MUST be erased after the check.

#. The CMS signed message MUST be bound to the Device Binding.

#. The CMS signed message MUST be mapped towards domain 0 in the Sony keystore (flash).

#. The CMS signed message MUST be mapped to “OEMunlocking” dummy partition.

VB2.0 support
---------------------------

1. Bootloader MUST verify that the public key in the VBMeta image is identical with at least one
   key found in the Sony keystore VBMeta domain

* **Stakeholders:** FCS
* **Stakeholders:** FST
* **Stakeholders:** FAS
* **Platforms:** Tama, Kumano, Huaihe

2. Bootloader MUST verify that the rollback index for VBMeta is equal or greater than the index
   found in RPMB

* **Stakeholders:** FCS
* **Stakeholders:** FST
* **Stakeholders:** FAS
* **Platforms:** Tama, Kumano, Huaihe

3. It MUST be possible to reset the vbmeta rollback counters using an
   authenticated XFL command.

* **RID** 4561
* **Stakeholders:** CS
* **Platforms:** Tama, Kumano, Huaihe
