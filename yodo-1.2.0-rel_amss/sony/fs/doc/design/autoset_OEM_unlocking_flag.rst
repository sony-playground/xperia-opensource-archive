===========================
Auto set OEM unlocking flag
===========================

Introduction
============

Unlocking of the bootloader is not allowed if OEM unlocking
checkbox is not checked in the developer options under Settings menu.
This is part of Google factory reset protection feature that is enabled by
default from factory. Our XCS partners might want to unlock a lot of units
and it is cumbersome to start every unit and manually check this flag.
By flashing a signed message the bootloader SHOULD set this flag, thus allowing
unlocking of the bootloader.

.. note::
  There are also other conditions that needs
  to be fulfilled for allowing unlocking of the bootloader: SIMLock must be
  valid and it SHOULD allow unlocking.

Requirements
============
  * If there is a CMS signed message flashed (MiscTA unit 2234), the bootloader MUST verify it.
  * The bootloader MUST check if there is Google account set on the device by parsing the
    frp partition.
  * If there is no Google account set on the device and a valid CMS message is present,
    the bootloader MUST set the OEM unlocking flag (erase MiscTA unit 66671).
  * MiscTA unit 2234 MUST be erased after the check.
  * The CMS signed message MUST be bound to the IMEI.
  * The signature of the CMS signed message MUST chain to at least one certificate belonging to
    domain 0 (Flash) in the Sony keystore.
  * The CMS signed message MUST be mapped to “OEMunlocking” dummy partition.


Implementation
==============
The bootloader must check if there is Google account set on the device. Google gms app
uses a partition for storing the account data (frp partition). In order to determine if
an account is present on the device we need to parse this data. The format of the
data is:

+----------------------------------+
|SHA-256 of partition (32 bytes)   |
+----------------------------------+
|Magic "0x19901873" (4 bytes)      |
+----------------------------------+
|Size of rest of the data (4 bytes)|
+----------------------------------+
|... data ...                      |
+----------------------------------+

.. _bootloader_oem_unlock_flag:

.. uml::
  :caption: Bootloader auto set OEM unlocking flag
  :align: center

  start

  :read MiscTA unit 2234 (TA_REMOTE_LOCK_UNLOCK_GFRP);
  if (TA_REMOTE_LOCK_UNLOCK_GFRP empty?) then (no)
    :verify signed message;
    if (message valid?) then (yes)
      :check if Google account is set;
      note right
        check if the magic number matches
        and if size is > 0
      end note
      if (account set?) then (no)
        :delete MiscTa unit 66671 (TA_GOOGLE_LOCK_STATE);
      else (yes)
      endif
    else (no)
    endif
  else(yes)
  endif

  :delete MiscTA unit 2234;
  stop



