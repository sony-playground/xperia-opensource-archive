============
Introduction
============
This document makes use of the practices described in [RFC2119]_ when describing
the dependencies.

This document lists FCS boot external dependencies.

============
Dependencies
============

Signing
=======

Dependency owner
----------------

QC (Qualcomm)

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sony.com>


Platforms
---------

* Generic

Description
-----------

1. QSEE and XBL_SEC images are signed by both Qualcomm and OEM ROT independently.
   In order to execute the QSEE image, both signatures have to pass. For the
   QC signature to pass on a fused unit the dual signed binary MUST be live
   signed by QC.

  * **Dependencies:** QC
  * **Platforms:** Generic

2. Platform specific security properties MUST be generated for development,
   precommercial, and commercial fused units.

  * **Dependencies:** FAS
  * **Platforms:** Generic

3. Platform specific Sony certificates MUST be generated to sign the boot
   images to be used on a fused unit with matching ROT.

  * **Dependencies:** FAS
  * **Platforms:** Generic


Trustzone applications
======================

Dependency owner
----------------

SWSE (SW Security)
FCS (Flash Core Security)

Platforms
---------

* Generic (See below for exceptions)

Description
-----------

The boot publishes security information via the xflattest TZ application. The
information published varies on whether the image started by the boot is xfl
or application SW.

#. Application SW is provided the following information:

   +---------------------------------------+--------------------------------------+------------------+
   |              Field                    |        Purpose                       | Platform         |
   +=======================================+======================================+==================+
   | XCS ROT                               || *Not used currently*                | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | SW device security state              || From HW config. Used by libasb.     | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | Phone id (IMEI)                       || Used by libasb and displayed in     | Generic          |
   |                                       || settings etc.                       |                  |
   +---------------------------------------+--------------------------------------+------------------+
   | Device Key                            || Used by DRM                         | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | Bootloader unlock status              || Used by credential manager, adb etc.| Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | HW config revision                    || Used for logging and debug menu     | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | HW config revision length             || Used for logging and debug menu     | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | Keystore hash                         || *Not used currently*                | Generic          |
   +---------------------------------------+--------------------------------------+------------------+
   | Android verified boot version         || Version of the AVB implementation   | Tama             |
   +---------------------------------------+--------------------------------------+------------------+
   | VB meta rollback counter              || The data is only valid if AVB       | Tama             |
   |                                       || version 2 is used                   |                  |
   +---------------------------------------+--------------------------------------+------------------+

#. XFL is provided the following information:

   +---------------------------------------+--------------------------------------+-------------------+
   |              Field                    |        Purpose                       |  Platform         |
   +=======================================+======================================+===================+
   | XCS ROT                               || Reported as fastboot variable, used |  Tama, Nile       |
   |                                       || to check validity of keystore       |                   |
   +---------------------------------------+--------------------------------------+-------------------+
   | RPMB keystore counter                 || Used to check validity of keystore  |  Generic          |
   +---------------------------------------+--------------------------------------+-------------------+
   | SAKE nonce                            || Used for SAKE authentication        |  Tama, Nile       |
   +---------------------------------------+--------------------------------------+-------------------+
   | Bootloader unlock status              || Reported as fastboot variable, used |  Generic          |
   |                                       || to report bootloader unlock state   |                   |
   +---------------------------------------+--------------------------------------+-------------------+
   | Keystore hash                         || Reported as fastboot variable, used |  Tama, Nile       |
   |                                       || to check validity of keystore       |                   |
   +---------------------------------------+--------------------------------------+-------------------+
   | VB meta rollback counter              || Reported as fastboot variable       |  Tama, Nile       |
   +---------------------------------------+--------------------------------------+-------------------+


