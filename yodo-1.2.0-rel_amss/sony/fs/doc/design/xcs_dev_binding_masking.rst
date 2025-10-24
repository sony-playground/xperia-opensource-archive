===========================
 XCS Device Binding Masking
===========================

Introduction
============

The XCS locking solution allows business partners to install additional signing keys and/or certificates into a
mobile device, to be used for authenticating selected parts of the device software. The current implementation
requires a server-generated data structure to be written into the device. This data structure contains an ID which is
unique for the device at hand; an ID which can be used by Sony to uniquely identify, and track, a device. Hence,
from a partner perspective, it is desirable to hide this ID from Sony, or any other third party.

Definitions
===========

Device Binding
   An identifier that is unique to a specific Mobile Device. For
   example, this can be the IMEI, a hardware serial number or an
   identifier derived from hardware-bound cryptographic keys.

Requirements
============
  * The Device Binding of the Mobile Device MUST be hidden from everyone except the XCS Partner.
  * It MUST NOT be possible to reverse, or brute-force, the process and recover the Device Binding.
  * It MUST NOT be possible to use the same Key Blob for multiple Mobile Devices.
  * The implementation SHOULD use mechanisms that are already available in the existing Bootloader.
    This limits us to the use of SHA-256 and/or RSA. (Implementation detail)
  * Boot SHOULD be able to handle masked and unmasked Device Binding.
  * Bootloader SHALL recompute HMAC using HMAC key written on to the device
  * Once HMAC key is verified, Bootloader SHALL move HMAC key from TA unit 2164 to high
    TA unit 66673 and then erase TA unit 2164.
  * Low TA unit 2164 SHALL be erased at every bootup if it exists.
  * HMAC MAY be present in Keystore CMS Structure as an unsigned attribute instead of TA unit.
  * During bootup, bootloader SHALL compare recomputed HMAC with HMAC in the keyblob.
    If they differ, the keystore SHALL be reverted.

Implementation
==============

The bootloader is responsible for verifying and applying the keystore. When new XCS keystore
is flashed the loader doesn't check the keystore. The keystore is flashed in the primary
partition and the HMAC key in low TA. On the next boot the bootloader will check the keystore
and if verification fails the keystore will be reverted, i.e the data from the backup
keystore partition will be copied to the primary partition. If the backup partition is
also invalid, the bootloader will only allow booting into service mode. If the keystore from the
primary partition is successfully verified, the keystore data from the primary partition
is copied to the backup partition.

.. note::
  The HMAC key handling is tightly connected to, and part of, the keystore
  handling (see :doc:`sony_keystore_security` for more info about
  keystore verification and loading).
  How and when the variables mentioned in :ref:`deviceBinding-masking`
  (update_hmac_key, hmac_key and secure storage data) are used is
  explained in :ref:`ks_set_keystore`.

.. _deviceBinding-masking:

.. uml::
  :caption: Keystore verification with Device Binding masking
  :align: center

  start

  :read secure storage data;
  note left
    secure storage data is set in ks_set_keystore
  end note
  if (xcs_rot in secure storage data is not set &&
  low MiscTA HMAC key not empty?) then (yes)
    :read HMAC key from low MiscTA;
      note left: MiscTA unit 2164
    :calculate HMAC SHA256 over the Device Binding using the low MiscTA key;
    :verify the keystore;
    note right
      A keystore can be verified against an HMAC Device Binding,
      or a plain Device Binding. Success is returned if one of
      the two succeeds.
    end note
    if (success?) then (yes)
      if (verified using HMAC Device Binding?) then (yes)
        if (low MiscTA HMAC key differs from high MiscTA HMAC key?) then (yes)
          :set update_hmac_key flag;
          note right
            This flag is used in ks_set_keystore. If it is set,
            the HMAC key from low MiscTA will be copied to
            high MiscTA.
          end note
          :copy the HMAC key to hmac_key;
          note right
            hmac_key is part of the keystore context.
            It is used for copying the low MiscTA HMAC key
            to high MiscTA.
          end note
        else (no)
        endif
      else (no)
      endif
      :erase low MiscTA HMAC key;
      :continue to load the keystore;
      stop
    else (no)
    endif
  else (no)
  endif
  if (is high MiscTA HMAC key empty?) then (no)
    :read HMAC key from high MiscTA;
      note left: MiscTA unit 66673
    :calculate HMAC SHA256 over the Device Binding using the high MiscTA key;
    note right
      Used for verifying the keystore later
    end note
  else (yes)
  endif
  :erase low MiscTA HMAC key;
  :continue to verify and load the keystore;
  stop

