======================
Bootloader Lock/Unlock
======================

Introduction
============

The bootloader can be either locked or unlocked. A locked bootloader requires a
signature before it will flash or boot images. An unlocked bootloader allows
flashing and booting of unsigned images. By default, every phone exiting
factory has a locked bootloader. In order to unlock the bootloader, the user
has to explicitly run a fastboot command, providing a correct RCK (Rooting
Control Key) that they have previously acquired by a Sony service.

Bootloader lock/unlock operations in vendor fastboot
====================================================

The vendor fastboot supports the following fastboot commands for
bootloader state operations:

  * fastboot oem unlock
  * fastboot oem lock

Vendor fastboot oem unlock
----------------------------

Pre-requisites
++++++++++++++

  * SIMLock MUST have tag ROOTING_ALLOWED="1"
    (or ROOTING_ALLOWED="2" and the SIMLock is unlocked).
  * The XCS flag in the keystore MUST NOT be set.
  * The XCS flag in secure storage MUST NOT be set.
  * MiscTA unit 66671 (TA_GOOGLE_LOCK_STATE) MUST be empty.
  * The bootloader MUST NOT be already unlocked.

Requirements
++++++++++++

  * An RCK MUST be provided as argument.
  * The SHA-256 hash of the provided RCK MUST match the stored RCK_H
    value in the SIMLock data.
  * The user sensitive partitions SHALL be securely erased.
  * Stored vbmeta rollback indexes SHALL be reset to 0.
  * MiscTA unit 66667 (TA_DEVICE_KEY) SHALL be erased.
  * MiscTA unit 2550 (TA_MASTER_RESET) SHALL be set to 0x1.
  * Recovery message SHALL be written to misc partition.
  * Bootloader unlock state SHALL be set to true.

.. _oem_unlock_fastboot:

.. uml::
  :caption: fastboot oem unlock in vendor fastboot
  :align: center

  start

  if (bootloader already unlocked?) then (no)
    :read bootloader unlock status;
    note right
      The unlock status is calculated by reading the
      ROOTING_ALLOWED tag from SIMLock, and the xcs flag from
      the Sony keystore and secure storage
    end note
    :check TA_GOOGLE_LOCK_STATE\n(miscTA unit 66671);
    if (bootloader unlock allowed
  and TA_GOOGLE_LOCK_STATE is empty?) then (no)
      :FAILCommand not allowed;
      stop
    else (yes)
      :verify RCK;
      if (RCK valid?) then (yes)
        :delete DK;
        if (success?) then (yes)
          :erase user sensitive data;
          note left
            Erases userdata partition,
            sets TA_MASTER_RESET to 0x1,
            writes recovery message to misc partition
          end note
          if (success?) then (yes)
            :reset rollback counters;
            if (success?) then (yes)
              :unlock bootloader;
              if (success?) then (yes)
                :set has_been_unlocked flag in RPMB if not set previously;
                if (success?) then (no)
                  :lock bootloader;
                  note left
                    Writing to RPMB has failed, try to lock back
                    the bootloader.
                    If both writing to RPMB and locking the bootloader
                    fail, then there's not much we can do, but return
                    OKAY to the "oem unlock" command.
                  end note
                  if (success?) then (yes)
                    :FAILCommand did not succeed;
                    stop
                  else (no)
                  endif
                else (yes)
                endif
                :OKAY;
                stop
              else (no)
              endif
            else (no)
            endif
          else (no)
          endif
        else (no)
        endif
      else (no)
      endif
      :FAILCommand did not succeed;
      stop
    endif
  else (yes)
    :FAILBootloader already unlocked;
    stop
  endif

Vendor fastboot oem lock
--------------------------

Pre-requisites
++++++++++++++

  * The bootloader MUST be unlocked

Requirements
++++++++++++

  * The user sensitive partitions SHALL be securely erased.
  * Stored vbmeta rollback indexes SHALL be reset to 0.
  * MiscTA unit 2550 (TA_MASTER_RESET) SHALL be set to 0x1.
  * Recovery message SHALL be written to misc partition.
  * Bootloader unlock state SHALL be set to false.

.. _oem_lock_fastboot:

.. uml::
  :caption: fastboot oem lock in vendor fastboot
  :align: center

  start

  if (bootloader already locked?) then (no)
    :erase user sensitive data;
    note left
      Erases userdata partition,
      sets TA_MASTER_RESET to 0x1,
      writes recovery message to misc partition
    end note
    if (success?) then (yes)
      :reset rollback counters;
        if (success?) then (yes)
          :lock bootloader;
          if (success?) then (yes)
            :OKAY;
          else (no)
            :FAILCommand did not succeed;
            stop
          endif
        else (no)
          :FAILCommand did not succeed;
          stop
        endif
    else (no)
     :FAILCommand did not succeed;
     stop
    endif
  else (yes)
    :FAILBootloader already locked;
  endif

  stop

Bootloader lock/unlock operations in xfl
========================================

The xfl supports the following fastboot commands for bootloader state
operations:

  * fastboot oem unlock
  * fastboot oem lock

Note that these commands do not change the state of the bootloader, but rather
enable the boot to lock/unlock the bootloader based on the data that is written
in miscTA. The device will also reboot immediately back into xfl after a successful
oem lock or unlock command. These commands in the xfl are present only for
development purposes. They are protected with production authentication.

fastboot oem unlock
-------------------

Pre-requisites
++++++++++++++

  * SIMLock MUST have tag ROOTING_ALLOWED="1"
    (or ROOTING_ALLOWED="2" and the SIMLock is unlocked).
  * The XCS flag in the keystore MUST NOT be set.
  * The XCS flag in secure storage MUST NOT be set.
  * MiscTA unit 66671 (TA_GOOGLE_LOCK_STATE) MUST be empty.
  * The bootloader MUST NOT be already unlocked.

Requirements
++++++++++++

  * The command MUST require authentication.
  * An RCK MUST be provided as argument.
  * The SHA-256 hash of the provided RCK MUST match the stored RCK_H
    value in the SIMLock data.
  * The valid RCK SHALL be written to miscTA unit 2226 (TA_RCK).
  * The device SHALL reboot immediately back into xfl
    for the boot to complete the unlocking.

.. _oem_unlock_xfl:

.. uml::
  :caption: fastboot oem unlock in xfl
  :align: center

  start

  :check ROOTING_ALLOWED tag in SIMLock;
  :check TA_GOOGLE_LOCK_STATE\n(miscTA unit 66671);
  if (bootloader unlock allowed
  and TA_GOOGLE_LOCK_STATE is empty?) then (yes)
     if (bootloader already unlocked?) then (yes)
        :FAILBootloader already unlocked;
     else (no)
        :verify RCK;
        if (RCK valid?) then (yes)
           :write RCK to TA_RCK
           (miscTA unit 2226);
           :reboot back into xfl for the
           boot to complete unlocking;
        else (no)
           :FAILCommand did not succeed;
        endif
     endif
  else (no)
     :FAILCommand not allowed;
  endif

  stop

fastboot oem lock
-----------------

Pre-requisites
++++++++++++++

  * The bootloader MUST be unlocked


Requirements
++++++++++++

  * The command MUST require authentication.
  * The command SHALL write the oem lock command to the authenticated channel
    MiscTA unit 2334.
  * The device SHALL reboot immediately back into xfl
    for the boot to complete the locking.

.. _oem_lock_xfl:

.. uml::
  :caption: fastboot oem lock in xfl
  :align: center

  start
  :read bootloader unlock status;
  if (bootloader unlocked?) then (yes)
    :append oem lock command to MiscTA unit 2334;
    :reboot back into xfl for the
    boot to complete locking;
  else (no)
    :FAILBootloader already locked;
  endif

  stop

Bootloader lock/unlock operations in boot
=========================================

During boot up, the boot checks miscTA units, that can be previously written
by the xfl, while executing fastboot oem lock/unlock commands.
Based on the validity of the data, the boot can lock/unlock the bootloader.

bootloader unlock
-----------------

Pre-requisites
++++++++++++++

  * miscTA unit 2226 (TA_RCK) MUST contain data (the RCK)
  * SIMLock MUST have tag ROOTING_ALLOWED="1"
    (or ROOTING_ALLOWED="2" and the SIMLock is unlocked).
  * MiscTA unit 66671 (TA_GOOGLE_LOCK_STATE) MUST be empty.
  * The bootloader MUST NOT be already unlocked.

Requirements
++++++++++++

  * The SHA-256 hash of the RCK MUST match the stored RCK_H value
    in the SIMLock data.
  * The user sensitive partitions SHALL be securely erased.
  * Stored vbmeta rollback indexes SHALL be reset to 0.
  * MiscTA unit 66667 (TA_DEVICE_KEY) SHALL be erased.
  * MiscTA unit 2550 (TA_MASTER_RESET) SHALL be set to 0x1.
  * Recovery message SHALL be written to misc partition.
  * Bootloader unlock state SHALL be set to true.
  * MiscTA unit 2226 MUST always be erased, regardless of the outcome of the
    RCK validation.

.. _bootloader_unlock_boot:

.. uml::
  :caption: bootloader unlock in boot
  :align: center

  start

  if (TA_RCK empty?) then (no)
    :read TA_RCK unit;
    :delete TA_RCK unit;
    if (bootloader already unlocked?) then (yes)
      :Bootloader already unlocked;
      stop
    else (no)
      :read bootloader unlock status;
      note left
        The unlock status is calculated by reading the
        ROOTING_ALLOWED tag from SIMLock, and the xcs flag from
        the Sony keystore and secure storage
      end note
      :check TA_GOOGLE_LOCK_STATE\n(miscTA unit 66671);
      if (bootloader unlock allowed
  and TA_GOOGLE_LOCK_STATE is empty?) then (yes)
        :verify RCK;
        if (RCK valid?) then (yes)
          :delete DK;
          if (success?) then (yes)
            :erase user sensitive data;
            note left
              Erases userdata partition,
              sets TA_MASTER_RESET to 0x1,
              writes recovery message to misc partition
            end note
            if (success?) then (yes)
              :reset rollback counters;
              if (success?) then (yes)
                :unlock bootloader;
                if (success?) then (yes)
                  :set has_been_unlocked flag in RPMB if not set previously;
                  if (success?) then (no)
                    :lock bootloader;
                    note left
                      Writing to RPMB has failed, try to lock back
                      the bootloader.
                      If both writing to RPMB and locking the bootloader
                      fail, then there's not much we can do, but just
                      print the error.
                    end note
                    if (success?) then (yes)
                      :Bootloader unlock not successful;
                      stop
                    else (no)
                    endif
                  else (yes)
                  endif
                  :Bootloader unlocked successfully;
                stop
                else (no)
                endif
              else (no)
              endif
            else (no)
            endif
          else (no)
          endif
        else (no)
        endif
      else (no)
      endif
      :Bootloader unlock not successful;
      stop
    endif
  else (yes)
    :continue booting up;
    stop
  endif


bootloader lock
---------------

Requirements
++++++++++++

  * Production SAKE authentication MUST be done through the authenticated channel.
  * The user sensitive partitions SHALL be securely erased.
  * Stored vbmeta rollback indexes SHALL be reset to 0.
  * MiscTA unit 2550 (TA_MASTER_RESET) SHALL be set to 0x1.
  * Recovery message SHALL be written to misc partition.
  * Bootloader unlock state SHALL be set to false.

.. note::
  For more information about how the authenticated channel works,
  see :doc:`authenticated_channel`.

.. _bootloader_lock_boot:

.. uml::
  :caption: bootloader lock in boot
  :align: center

  start

  :check miscTA unit 2334
  (TA_AUTH_CH);
  if (AUTH_CH_OEM_LOCK command present?) then (yes)
    if (AUTH_LEVEL_PRODUCITON?) then (yes)
      :erase user sensitive data;
      note left
        Erases userdata partition,
        sets TA_MASTER_RESET to 0x1,
        writes recovery message to misc partition
      end note
      if (success?) then (yes)
        :reset rollback counters;
          if (success?) then (yes)
            :lock bootloader;
          else (no)
          endif
      else (no)
      endif
      :Bootloader lock not successful;
    else (no)
      :continue booting up;
    endif
  else (no)
    :continue booting up;
  endif
  stop


Master reset flow after bootloader lock/unlock
==============================================

Bootloader lock/unlock requires master reset

.. _master_reset_flow:

.. uml::
  :caption: Master reset flow
  :align: center

  start

  :bootloader writes message("boot-recovery --wipe-data") in misc partition;
  :set 0x01 in 2550(TA_MASTER_RESET) for clear NV data;
  :reboot;
  :boot into recovery mode;
  :recovery process executes
  * format the userdata
  * set 0x01 in 2550(TA_MASTER_RESET) for clear NV data,
  * clear misc partition;
  :reboot;
  :boot into mission mode;
  if (TA_MASTER_RESET == 0x01?) then (yes)
        :modem erase NV data;
  else (no)
  endif
  :continue booting up;

  stop

