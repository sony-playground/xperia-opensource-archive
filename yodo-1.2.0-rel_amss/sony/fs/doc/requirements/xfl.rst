===================
Xperia Flash Loader
===================

Introduction
============

This document makes use of the practices described in [RFC2119]_ when describing
the requirements.

Each requirement specifies the stakeholder and the platforms that the
requirement is valid for. The term "Generic" implies that the requirement is valid
for all platforms listed under :ref:`xfl-platforms-label`.

Stakeholders
------------

FCS (Flash core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

RCALogReader Tomokazu Goto, <Tomokazu.Goto@sonymobile.com>

CS, Customer Service

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sonymobile.com>

FSV, Flash Security Verification Anil Gadiraju <anil.gadiraju@sonymobile.com>

GCIS, Global Common Indus Solution Yuying Chen <Yuying.Chen@sonymobile.com>

SWuP(Software Update Platform) Esbjorn Wernhoff <Esbjorn.Wernhoff@sonymobile.com>

Developer World Alin Jerpelea <Alin.Jerpelea@sonymobile.com>

XCS-SWSE (Xperia Custom Software - SW Security & Enterprise) Rimpu Varshney <Rimpu.Varshney@sonymobile.com>

Google, https://source.android.com/

.. _xfl-platforms-label:

Platforms
---------

* Yoshino
* Nile
* Tama
* Kumano
* Huaihe


Terminology
===========

#. SECURITY
   There are many "security" states that a device can have but they depend on
   two separate states:

   #. If the device is fused or not.

      There are three variants of fused devices:

      #. OEM0 devices

         Fused with a platform test key. This key is freely available for
         all in R&D.

      #. Pre-commercial devices

         Fused with a pre-commercial key. These devices MAY be delivered to
         operators for their customer acceptance. This key is more restricted
         in use and availability.
      #. Commercial devices

         Fused with a commercial key. These are the devices we sell.

   #. If the bootloader is unlocked or not.

#. PROTOCOL
   The fastboot protocol used is defined in fastboot_protocol.rst, which is
   adapted from Google original with SOMC extensions.

   #. It SHOULD be possible to read out transportation layer version the
      protocol is communicating over.

      * **Stakeholders:** FCS
      * **Platforms:** Generic
      * **Background:** Can be used for various benchmarking purposes.

#. KEYSTORE
   Sony keystore is a storage for keys/certificates. xflkeystore and
   xflkeystorebak partitions are used for storage of the keystore data.
   xflkeystorebak is a backup partition used to restore the keystore data to
   the primary partition if the keystore in the primary partition is invalid.
   To avoid the possibility to erase the backup and the primary partition and
   install new keystore to the device, the hash value of the current valid
   keystore is stored in a secure data storage (RPMB).

   * XFL MUST report getvar Security-state empty if there are invalid keystores
     in both partitions (xflkeystore and xflkeystorebak).

   * XFL SHOULD add variable Stored-security-state which returns the
     hash over the keystore payload of the latest successfully applied
     keystore. This is needed to identify which keystore that was used if the
     keystore partitions are erased. The hash is stored in secure storage.

   * XFL SHOULD add variable Keystore-xcs which reports the value of the XCS
     flag in secure storage to allow host side to easily detect warranty issue.

   * XFL MUST allow unrestricted erase and flash access to xflkeystore partition.

      * **Stakeholders:** XCS-SWSE
      * **Platforms:** Kumano, Huaihe
      * **RID:** 004579


Requirements
============

#. LOG

   #. Reading the appslog partition MUST NOT require authentication

      * **Stakeholders:** RCALogReader
      * **Platforms:** Generic

#. TA

   #. Reading the miscTA SHALL NOT require authentication

      * **Stakeholders:** RCALogReader
      * **Platforms:** Generic

   #. Reading units above 65535 of miscTA (high TA) MUST require authentication
      level PRODUCTION.

      * **Stakeholders:** FCS
      * **Platforms:** Generic

#. SECURITY STATES

   A number of fastboot commands and variables SHOULD be used to control/show
   the states.

   #. Command "Set-security"

      SHALL set the security properties for the device. The properties is
      obtained from the security server. In most platforms, this command will
      program some form of OTP (One Time Programmable).

      * **Stakeholders:** GCIS, FAS
      * **Platforms:** Generic

   #. Command "Authenticate"

      Authenticate can be done in two ways.

      +------------+---------------------------------------------+
      | Level      | Meaning                                     |
      +============+=============================================+
      | PRODUCTION | SHALL enable all commands on a device.      |
      +------------+---------------------------------------------+
      | CS         | SHALL allow Customer Service to execute     |
      |            | certain CS specific commands.               |
      +------------+---------------------------------------------+

      See fastboot protocol definition
      :doc:`../fastboot_protocol/fastboot_protocol` for a list of commands and
      the required authentication level.

      * **Stakeholders:** SSO, CS
      * **Platforms:** Generic

   #. Command "Reset-rollback-counter"

      SHALL reset Google rollback counters in secure storage which
      corresponds to VB Meta. When rollback counters are reset,
      partition userdata SHALL be erased.

      * **Stakeholders:** CS
      * **Platforms:** Tama, Nile
      * **RID:** 004561

   #. Variable "Rollback-index-count"

      SHALL return the number of existing rollback counters in VB Meta.

      * **Stakeholders:** CS
      * **Platforms:** Tama, Nile
      * **RID:** 004561

   #. Variable "Rollback-index:<i>"

      SHALL return the value of the specified rollback counter.

      * **Stakeholders:** CS
      * **Platforms:** Tama, Nile
      * **RID:** 004561

   #. Variable "secure"

      SHALL return the state of the bootloader.
      If the value is "yes", this is a secure bootloader requiring a signature
      before it will install or boot images. This is the case if the bootloader
      has not been unlocked.
      If the bootloader is unlocked the value SHALL be "no".

      * **Stakeholders:** DW
      * **Platforms:** Generic

   #. Variable "Rooting-status"

      SHALL show information about the bootloader unlock status (also known as
      controlled rooting status).

      Possible values are:

      +----------------------+----------------------------------------+
      | Value                | Meaning                                |
      +======================+========================================+
      | NOT_ROOTABLE         || Invalid SIMLock or ROOTING_ALLOWED    |
      |                      || is not '1' in the SIMLock data file   |
      +----------------------+----------------------------------------+
      | ROOTABLE             || Valid SIMLock and ROOTING_ALLOWED     |
      |                      || is '1' in the SIMLock data file,      |
      |                      || the device is not yet rooted          |
      +----------------------+----------------------------------------+
      | ROOTED               || The device is successfully rooted     |
      +----------------------+----------------------------------------+
      | SL_ROOTABLE          || Valid SIMLock and ROOTING_ALLOWED is  |
      |                      || '2' in the SIMLock data file, but in  |
      |                      || order for the device to be rootable,  |
      |                      || the SIMLock needs to be unlocked      |
      |                      || first                                 |
      +----------------------+----------------------------------------+
      | SL_UNL_ROOTABLE      || Valid SIMLock, ROOTING_ALLOWED is     |
      |                      || '2' in the SIMLock data file and the  |
      |                      || SIMLock is unlocked, but the device   |
      |                      || is not yet rooted                     |
      +----------------------+----------------------------------------+

      * **Stakeholders:** DW
      * **Platforms:** Generic

   #. Variable "Has-been-unlocked"

      SHALL show whether the bootloader has or has not been unlocked during the
      device's lifetime.
      If the value is "no", it means that the bootloader has never been
      unlocked. Otherwise, the value is "yes".
      SHALL return an error if the xfl_sec_data protocol version in the xboot
      doesn't support the has_been_unlocked flag.

      * **Stakeholders:** FAS,SWuP
      * **Platforms:** Kumano, Huaihe

   #. Variable "Default-security"

      SHALL show the security state of the device based on the fuses.
      Possible values are:
      "ON"  Security is enabled.
      "OFF" Security is disabled.

      * **Stakeholders:** FAS,GCIS,SWuP

   #. Variable "S1-root"

      SHALL return all valid S1 roots on device. If platform security is
      disabled (unfused unit), it SHALL reply with both S1_Root_xxxx and
      S1_Test_Root_xxxx.

      * **Stakeholders:** FAS,GCIS,SWuP
      * **Platforms:** Generic
      * **Background:**  It is used for e.g. generating simlock.

   #. Variable "Sake-root"

      SHALL return the ascii representation of the first two bytes of sake root
      public hash. If there is a sake test root available it will be in the
      response, if not then it will be the live root.

      * **Stakeholders:** FAS
      * **Platforms:** Generic

   #. Variable "X-conf"

      SHALL return all valid X-conf roots on device. If platform security is
      disabled (unfused or test fused unit) it SHALL reply with identifiers for
      both certificates. The exact identifier is the ascii representation of the
      first two bytes of root public key SHA1 hash in PEM format. If the test
      root is available it SHALL be returned as the first identifier followed
      by the live root.

      * **Stakeholders:** FAS
      * **Platforms:** Kumano, Huaihe


   #. Variable "Security-state"

      SHALL return a SHA256 hash of the keystore payload in case there is a
      valid keystore in the device. The hash is encoded in base64 format.

      * **Stakeholders:** FAS,GCIS,SWuP
      * **Platforms:** Generic (Yoshino has a SHA1 hash which is presented in
        hexadecimal format).
      * **Background:**  It is used for verifying that the correct device is
        produced as well as defining what SW the device will accept.
        The tool chain is dependent on a detection mechanism that let
        you quantify a device into different groups (development,
        precommercial, commercial). This also allow detection of XCS converted
        devices, since an XCS device will have a hash which is different from
        any of the defined groups for that product family.

   #. Variable "Stored-security-state"

      SHALL return a SHA256 hash of the keystore payload of the latest
      successfully applied keystore. The value is retrieved from the secure
      storage. The hash is encoded in base64 format.

      * **Stakeholders:** FCS,FAS
      * **Platforms:** Tama, Nile
      * **Background:**  Needed for protection against flashing of keystore
        in case the keystore partitions are erased or invalid. This value
        serves as an identification for the keystore that will be accepted.

   #. Variable "Keystore-counter"

      SHALL return the keystore counter value in secure storage.
      If not yet provisioned the value should be '0'.

      * **Stakeholders:** FCS,FAS
      * **Platforms:** Generic
      * **Background:**  Needed for anti rollback protection.
        A new keystore needs to have a counter value which is equal or higher
        than the value stored in secure storage.

   #. Variable "Keystore-xcs"

      SHALL return "yes" if the device has been flashed with a keystore,
      which MUST NOT be able to update, otherwise "no" SHALL be returned.
      This value is retrieved from secure storage.

      * **Stakeholders:** FAS,CS
      * **Platforms:** Tama, Nile
      * **Background:**  Since an upgrade of an XCS keystore must not be
        allowed, there is a need for Customer Service to know if a keystore
        for XCS is flashed.

   #. Variable "Soc-unique-id"

      SHALL return SUID number which is consisted of:
      Silicon Provider ID, HW code ID (SoC ID), Chip Serial Number (CSN)
      SUID is retrieved from RPMB data, block 4.

      * **Stakeholders:** FCS,FAS
      * **Platforms:** Huaihe
      * **Background:**  SUID is one of the arguments needed in FXT API interface
        which extracts Trustonic TEE Binding Key from SECS Server.

   #. Variable "SD-card-inserted"

      SHALL return "yes" if an external SD card is currently inserted in the
      device, otherwise "no".

      * **Stakeholders:** FCS,FAS
      * **Platforms:** Huaihe
      * **Background:**  This feature is requested by ODM vendor and is used
        in factory to ensure that no test cards are accidentally left in the
        devices when they are boxed.

#. MEMORY HANDLING

   #. Command "Sync"

      The command SHALL sync the memory and purge unmapped memory.

      * **Stakeholders:** FAS, GCIS, SWuP
      * **Platforms:** Generic
      * **Background:** Flash tools SHOULD execute this at the of flash flow if an
        erase operation has been performed on the memory.

#. BOOTLOADER UNLOCK STATE

   #. Unless authenticated via command 'Authenticate' or 'signature',
      the commands "flash" and "erase" MUST NOT be possible to execute when
      the bootloader is locked.

   #. The list of partitions possible to flash or erase on an unlocked and
      fused device SHALL be restricted to:

      * boot
      * dtbo (Kumano)
      * odmdtbo (Huaihe)
      * system
      * vendor
      * oem
      * userdata
      * vbmeta

      For an unfused (development) and unlocked device there SHOULD NOT be any
      restrictions on which partitions can be flashed or erased.

      * **Stakeholders:** FAS, GCIS, SWuP, Developer World
      * **Platforms:** Kumano, Huaihe

   #. Command "oem unlock"

      The command SHALL check the ROOTING_ALLOWED tag in SIMLock before
      allowing unlocking of the bootloader. The SIMLock MUST have tag
      ROOTING_ALLOWED="1" or ROOTING_ALLOWED="2", otherwise unlocking of the
      bootloader SHALL NOT be allowed. If the tag is ROOTING_ALLOWED="2",
      the SIMLock MUST be unlocked, otherwise unlocking of the bootloader
      SHALL NOT be allowed.

      The command SHALL check the miscTA unit 66671 (TA_GOOGLE_LOCK_STATE).
      The unit MUST be empty, otherwise unlock SHALL NOT be allowed.

      The command SHALL check whether the bootloader is already unlocked.

      The command SHALL require an unlock code (RCK) to be able to unlock.
      The SHA-256 hash of the RCK MUST match the stored RCK_H value in the
      SIMLock data.

      If the command is allowed the provided RCK SHALL be written to TA
      unit 2226 (TA_RCK). The device is then rebooted to let the bootloader
      execute the unlocking.

      * **Stakeholders:** FAS, Developer World
      * **Platforms:** Kumano, Huaihe
      * **Background:** It is used for enabling bootloader unlock functionality
        in FG4.

   #. Command "oem lock"

      The command SHALL write the AUTH_CH_OEM_LOCK command to MiscTA Unit
      2334 (TA_AUTH_CH). The device is then rebooted to let the bootloader
      execute the locking. The command MUST require authentication.

      * **Stakeholders:** FAS
      * **Platforms:** Kumano, Huaihe
      * **Background:** It is used for enabling bootloader lock functionality
        in FG4.

#. A/B UPDATES

   See also https://source.android.com/devices/tech/ota/ab_updates

   It is REQUIRED for slot 'a' to be in lun 1 and slot 'b' to be in lun 2.

   * **Stakeholders:** Google, FCS
   * **Platforms:** Nile, Tama

   #. Command "set_active <slot>"

      This command MUST set <slot> as active. It MUST clear unbootable flag for
      <slot> and reset retry count to default value. Any other slot MUST be set
      to inactive. This MUST be done for the boot and xfl partitions.
      This command MUST set corresponding lun to bootable. If <slot> is on lun 1
      it will be set as bootable, if <slot> is on lun 2 it will be set instead.
      If variable "slot-count" is an invalid number, currently any number
      different than 2, set_active command SHOULD report it is unsupported.
      This command MUST swap the GUID TYPEs between "a" and "b" slot partitions
      if needed. After the swap, all inactive slot partitions MUST have
      the same GUID TYPE, and all active slot partitions MUST have different
      GUID TYPE.

   #. Variable "slot-count"

      MUST return the number of slots available in current device configuration.
      Number of slots can be any number except 1, but it is OPTIONAL to support
      other slot counts than 0 or 2.

   #. Variable "has-slot:<partition>"

      MUST return "yes" if <partition> has slots and "no" otherwise.

   #. Variable "current-slot"

      MUST return the slot suffix that will be booted from next.

   #. Variable "slot-successful:<slot-suffix>"

      MUST return "yes" if the given slot has been marked as successfully booting,
      "no" otherwise.

   #. Variable "slot-unbootable:<slot-suffix>"

      MUST return “yes” if the given slot is marked as unbootable, "no" otherwise.

   #. Variable "slot-retry-count:<slot-suffix>"

      MUST return the number of retries remaining to attempt to boot the given slot.

   #. CMS signature partition name

      For A/B update handling it MUST be acceptable that the cms signature only
      contains the base partition name. If the cms signature contains a partition name
      with a slot then download MUST be acceptable only for that exact partition slot.
      Example:
      If cms signature contains <partition>, then flashing should be accepted for
      both <partition>_a and <partition>_b. If cms signature contains <partition>_a
      it can't be flashed into <partition>_b and vice versa.

#. SAFE BOOT UPGRADE

   This is an attempt of making boot updates to be atomic so that an aborted or
   otherwise disrupted flashing of a new bootloader will not render the device
   in a brick state.

   * The bootloader MUST be delivered as a tarred archive where all bootloader
     partitions are included.
   * The flash loader SHALL, after completely downloading and verifying content,
     flash each partition included in the archive.
   * In order to flash a bootloader archive the "bootloader[_<slot>]" magic MUST
     be used.
   * If the device has slots <slot> MUST be appended to the magic.

   * **Stakeholders:** FCS, CS
   * **Platforms:** Generic

#. MISC

   #. Variable "Battery"

      Should return the battery capacity in percentage. The returned value should
      be a number between 0 and 100. If operation is not supported on the current
      platform, then N/A should be returned.

      * **Stakeholders:** SWuP
      * **Platforms:** Tama, Nile
      * **Background:** It is used to ensure that a prolonged download time of
        files over internet has not affected the battery capacity negatively
        to the point where the flash will fail.

   #. Command "Charge:<b>"

      Start charging of the device until it reaches the desired battery capacity
      specified by <b>. Charging should be enabled by default and should charge
      the battery to 70%. It can be overridden by this command. Charging SHALL
      be disabled after level <b> is reached and not enabled again until a new
      command is issued. If <b> equals 0 charging is disabled.
      Range for <b>: 0-100. Other values will produce an error.

      * **Stakeholders:** SWuP, GCIS
      * **Platforms:** Tama, Yoshino(default charge to 60 %), Nile

   #. Command "Reset-frp"

      The command SHALL erase the frp partition.
      The command MUST require CS authentication.

      * **Stakeholders:** FAS, SWuP, CS
      * **Platforms:** Kumano, Huaihe

   #. Command "Reboot-bootloader"

      Reboot into the vendor fastboot.

      * **Stakeholders:** FCS, FSV
      * **Platforms:** Kumano, Huaihe
      * **Background:** Until Kumano and Huaihe, the generic reboot-bootloader
        command was used for rebooting the device from xfl to vendor fastboot.
	From these platforms, the generic command reboots to xfl, hence, the
	Reboot-bootloader command was introduced. It is used mostly for
	automated tests.

   #. Command "Erase-sector"

      Erase one or more sectors anywhere on the flash. This command is not constrained
      by partition layout. It is implemented for R&D and verification.
      The command MUST require authentication level production.

      * **Stakeholders:** FCS, FSV
      * **Platforms:** Generic
      * **Background:** The only command that can wipe the whole flash and/or only
        the partition table for instance.

   #. Command "Secure-erase-sector"

      Same as Erase-sector except purge is carried out, just as in Secure-erase case.
      The command MUST require authentication level production.

      * **Stakeholders:** FCS, FSV
      * **Platforms:** Generic
      * **Background:** Erase without purge might or might not erase the data in an
        arbitrary time period. To make sure data is erased now perform the secure
        version.

   #. Command "Read-sector"

      Read one or more sectors anywhere on the flash. This command is not constrained
      by partition layout. It is implemented for R&D and verification.
      The command MUST require authentication level production.

      * **Stakeholders:** FCS, FSV
      * **Platforms:** Generic
      * **Background:** In order to tackle the dilemma with growing flash sizes and
        increased readback verification time this command opens up for writing test
        cases that can execute quickly even on large flashes.

   #. Command "Set-ship-mode"

      To ensure that the battery does not discharge during shipping for
      non-removable battery applications, the PM8150B has the ability to switch
      the bulk connection of the battery to system FET, thereby reversing the
      body diode direction and completely disconnecting the battery from the
      system load. This mode is called ship mode.

      * **Stakeholders:** GCIS
      * **Platforms:** Kumano
      * **Background:** In order to enable the Anti-Replay Island(ARI),
        we need to set to ship mode during SW_SERVICE (e.g. at the end of
        FF station), in order to trigger UVLO(Power Loss) event.

   #. Command "Enable-display"

      This command will turn on the display. After it is turned on it will
      stay on until "Disable-display" is sent to the device.
      The command MUST require authentication level production.

      If MiscTA unit 66674 is set to 01 the display will be turned on when the
      loader is started, without the need of sending this command.
      This command MUST write 01 to MiscTA unit 66674.
      The loader commands that are sent SHALL be possible to be shown on the display.
      The loader internal log SHALL be possible to be shown on the display.
      Scrolling (up and down) on the display using physical keys SHOULD be supported.
      After a period of inactivity the display brightness SHOULD be turned down to 0
      and SHOULD be turned back on when a physical key is pressed or a new line is
      drawn to the display.


      +--------------------------------------+
      |Display layout                        |
      +======================================+
      || HEADER SEGMENT                      |
      || (Xperia Flash Loader)               |
      +--------------------------------------+
      || LOGS SEGMENT                        |
      || Commands and internal loader log    |
      || Commands and internal loader log    |
      || Commands and internal loader log    |
      || .                                   |
      || .                                   |
      || .                                   |
      +--------------------------------------+
      || STATUS SEGMENT                      |
      || (Shows the current loader status:   |
      || Working, Ready, Safe to disconnect  |
      || the device, etc. )                  |
      +--------------------------------------+
      || STATIC SEGMENT                      |
      || (Xboot and XFL version number)      |
      +--------------------------------------+


      * **Stakeholders:** FCS
      * **Platforms:** Kumano
      * **Background:** When debugging it is hard to know what is going on in
        the device. Seeing it on the display will save a lot of time for the
        people doing the debugging and lead to faster resolution times for issues.


   #. Command "Disable-display"

      This command will turn off the display.
      The command MUST require authentication level production.
      If MiscTA unit 66674 is set to 00 the display will be turned off when the
      loader is started, without the need of sending this command.
      This command MUST write 00 to MiscTA unit 66674.

      * **Stakeholders:** FCS
      * **Platforms:** Kumano


   #. Command "Getnvlog"

      Read loader log from non-volatile memory. When this command is issued the log
      is erased from the device.

      * **Stakeholders:** FCS, FSV
      * **Platforms:** Kumano, Huaihe
      * **Background:** Can be used for debugging purposes.

#. PARTITION TYPE AND SIZE

   Some tools require the fastboot variables partition-type:<partition> and
   partition-size:<partition> to be supported.
   Google's fastboot client supports these for the partitions system and userdata.
   Since the system partition is either in slot a or b, the command should check
   current slot and report type and size for partition system_a or system_b.
   SONY should follow Google's implementation.

   * **Stakeholders:** Google
   * **Platforms:** Nile, Tama

#. USB

   The XFL MUST ensure that the iSerial sent in the USB Device Descriptor is
   set to zero.
   iSerial equal to zero will trigger a specific behavior of Windows which is
   used by GCIS to identify which device is connected to which port of the host
   PC when flashing multiple devices on a single host PC.

   * **Stakeholders:** GCIS
   * **Platforms:** Generic
