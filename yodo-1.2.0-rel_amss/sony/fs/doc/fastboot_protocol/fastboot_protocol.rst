FastBoot  Version  0.4 (Sony Extension Version 0.54)
====================================================

The fastboot protocol is a mechanism for communicating with bootloaders
over USB or ethernet.  It is designed to be very straightforward to implement,
to allow it to be used across a wide range of devices and from hosts running
Linux, Windows, or OSX.

Source: Google's implementation shipped with Android.

Sony Extension Version Revision History
=======================================

+---------+---------------------------------------------------------------------+
| Version | Changes                                                             |
+=========+=====================================================================+
| 0.54    || Change the required authentication level for set ship mode         |
|         || from PRODUCTION to NONE                                            |
+---------+---------------------------------------------------------------------+
| 0.53    || Added production level authentication to Enable-display and        |
|         || Disable-display commands                                           |
+---------+---------------------------------------------------------------------+
| 0.52    || Added Getnvlog command                                             |
+---------+---------------------------------------------------------------------+
| 0.51    || Added commands:                                                    |
|         || Enable-display                                                     |
|         || Disable-display                                                    |
+---------+---------------------------------------------------------------------+
| 0.50    || Added Set-ship-mode command                                        |
+---------+---------------------------------------------------------------------+
| 0.49    || Removed command Get-security                                       |
+---------+---------------------------------------------------------------------+
| 0.48    || Added Has-been-unlocked variable                                   |
+---------+---------------------------------------------------------------------+
| 0.47    || Added SD-card-inserted variable                                    |
+---------+---------------------------------------------------------------------+
| 0.46    || Removed the functionality of formatting all partitions with a      |
|         || single command in Format-TA; each partition has to be stated.      |
|         || Partition arguments in the TA commands can be between 0-9          |
+---------+---------------------------------------------------------------------+
| 0.45    || Added Soc-unique-id variable                                       |
+---------+---------------------------------------------------------------------+
| 0.44    || Added production authentication for oem unlock command in XFL      |
+---------+---------------------------------------------------------------------+
| 0.43    || Changed the "oem lock" implementation in xfl by removing the       |
|         || downloading of a CMS signed message to MiscTA. Instead added an    |
|         || "oem lock" command in the authenticated channel.                   |
+---------+---------------------------------------------------------------------+
| 0.42    || Added Reboot-bootloader command                                    |
+---------+---------------------------------------------------------------------+
| 0.41    || Added X-conf variable                                              |
+---------+---------------------------------------------------------------------+
| 0.40    || Changed command behavior:                                          |
|         || "reboot" will reboot the device in normal mode                     |
|         || "reboot-bootloader" will reboot the device back into the bootloader|
|         || If the bootloader is unlocked allow flashing or erasing any        |
|         || partition without restriction as long as the device is unfused, but|
|         || if the device is fused, allow flashing or erasing only platform    |
|         || specific selected partitions.                                      |
|         || "oem unlock %s" will reboot the device so that the bootloader will |
|         || execute the unlocking                                              |
+---------+---------------------------------------------------------------------+
| 0.39    || Added Reset-frp command                                            |
+---------+---------------------------------------------------------------------+
| 0.38    || Removed Stored-keystore-hash variable.                             |
|         || Security-state and Stored-security-state are changed to use SHA256 |
|         |  hashes                                                             |
+---------+---------------------------------------------------------------------+
| 0.37    || Added variables:                                                   |
|         || Stored-security-state                                              |
|         || Stored-keystore-hash                                               |
|         || Keystore-xcs                                                       |
+---------+---------------------------------------------------------------------+
| 0.36    || Added Reset-rollback-counter command                               |
+---------+---------------------------------------------------------------------+
| 0.35    || Added another level of authentication (Customer service) to        |
|         || SAKE-Authenticate                                                  |
+---------+---------------------------------------------------------------------+
| 0.34    || Removed fastboot variable slot-suffixes                            |
|         || Added variables partition-type and partition-size                  |
+---------+---------------------------------------------------------------------+
| 0.33    || Added Battery variable                                             |
+---------+---------------------------------------------------------------------+
| 0.31    || Added signature command                                            |
+---------+---------------------------------------------------------------------+
| 0.3     || Added slot-count variable                                          |
+---------+---------------------------------------------------------------------+
| 0.2     || Added oem lock command                                             |
+---------+---------------------------------------------------------------------+


References
==========
[1] SEMC Authentication and Key Establishment protocol, 23/159 35-LXE 108 116.

Basic Requirements
==================

USB
---
* Two bulk endpoints (in, out) are required
* Max packet size must be 64 bytes for full-speed, 512 bytes for
  high-speed and 1024 bytes for Super Speed USB.
* The protocol is entirely host-driven and synchronous (unlike the
  multi-channel, bi-directional, asynchronous ADB protocol)

TCP or UDP
----------
* Device must be reachable via IP.
* Device will act as the server, fastboot will be the client.
* Fastboot data is wrapped in a simple protocol; see below for details.


Transport and Framing
---------------------

1. Host sends a command, which is an ascii string in a single
   packet no greater than 64 bytes.

2. Client response with a single packet no greater than 64 bytes.
   The first four bytes of the response are "OKAY", "FAIL", "DATA",
   or "INFO".  Additional bytes may contain an (ascii) informative
   message.

   a. INFO -> the remaining 60 bytes are an informative message
      (providing progress or diagnostic messages).  They should
      be displayed and then step #2 repeats

   b. FAIL -> the requested command failed.  The remaining 60 bytes
      of the response (if present) provide a textual failure message
      to present to the user.  Stop.

   c. OKAY -> the requested command completed successfully.  Go to #5

   d. DATA -> the requested command is ready for the data phase.
      A DATA response packet will be 12 bytes long, in the form of
      DATA00000000 where the 8 digit hexadecimal number represents
      the total data size to transfer.

3. Data phase.  Depending on the command, the host or client will
   send the indicated amount of data.  Short packets are always
   acceptable and zero-length packets are ignored.  This phase continues
   until the client has sent or received the number of bytes indicated
   in the "DATA" response above.

4. Client responds with a single packet no greater than 64 bytes.
   The first four bytes of the response are "OKAY", "FAIL", or "INFO".
   Similar to #2:

   a. INFO -> display the remaining 60 bytes and return to #4

   b. FAIL -> display the remaining 60 bytes (if present) as a failure
      reason and consider the command failed.  Stop.

   c. OKAY -> success.  Go to #5

5. Success.  Stop.


Example Session
---------------

.. code-block:: none

    Host:    "getvar:version"        request version variable

    Client:  "OKAY0.4"               return version "0.4"

    Host:    "getvar:nonexistant"    request some undefined variable

    Client:  "OKAY"                  return value ""

    Host:    "download:00001234"     request to send 0x1234 bytes of data

    Client:  "DATA00001234"          ready to accept data

    Host:    < 0x1234 bytes >        send data

    Client:  "OKAY"                  success

    Host:    "flash:bootloader"      request to flash the data to the bootloader

    Client:  "INFOerasing flash"     indicate status / progress
             "INFOwriting flash"
             "OKAY"                  indicate success

    Host:    "powerdown"             send a command

    Client:  "FAILunknown command"   indicate failure


Command Reference
=================

* Command parameters are indicated by printf-style escape sequences.

* Commands are ascii strings and sent without the quotes (which are
  for illustration only here) and without a trailing 0 byte.

* Commands that begin with a lowercase letter are reserved for this
  specification.  OEM-specific commands should not begin with a
  lowercase letter, to prevent incompatibilities with future specs.

.. code-block:: none

 "getvar:%s"           Read a config/version variable from the bootloader.
                       The variable contents will be returned after the
                       OKAY response.

 "download:%08x"       Write data to memory which will be later used
                       by "boot", "ramdisk", "flash", etc.  The client
                       will reply with "DATA%08x" if it has enough
                       space in RAM or "FAIL" if not.  The size of
                       the download is remembered.

  "signature:%08x"     Send a digital signature and verify.
                       Required to verify future "flash" and "repartition"
                       data and accept "erase" if none of below is met:
                          1. The bootloader is authenticated to level
                             PRODUCTION.
                          For "flash" and "erase" only:
                          2. The device is unlocked and unfused.
                          3. The device is unlocked and fused and
                             not restricted partition.
                       If required the partition stated in the signature
                       must match future flashed and erased partition.

  "signature"          Verify previously downloaded digital signature.
                       Required to verify future "flash" and "repartition"
                       data and accept "erase" if none of below is met:
                          1. The bootloader is authenticated to level
                             PRODUCTION.
                          For "flash" and "erase" only:
                          2. The device is unlocked and unfused.
                          3. The device is unlocked and fused and
                             not restricted partition.
                       If required the partition stated in the signature
                       must match future flashed and erased partition.

  "flash:%s"           Write the previously downloaded image to the
                       named partition (if possible).
                       When flashing partition table the argument %s is target
                       device. In the UFS case target LUN is a number starting
                       at 0. In eMMC case just use 0.

  "erase:%s"           Erase the indicated partition.

  "boot"               The previously downloaded data is a boot.img
                       and should be booted according to the normal
                       procedure for a boot.img
                       SONY addition: not supported.

  "continue"           Continue booting as normal (if possible)
                       SONY addition: reboot into normal kernel.

  "reboot"             Reboot the device.

  "reboot-bootloader"  Reboot back into the bootloader.
                       Useful for upgrade processes that require upgrading
                       the bootloader and then upgrading other partitions
                       using the new bootloader.

  "powerdown"          Power off the device.
                       SONY addition: power off the device after detaching
                       USB cable.

  "oem unlock %s"      Unlock the bootloader.
                       Authentication should be performed before executing the
                       command. The parameter is an 18 or 16 byte
                       RCK data in hex format depending on whether 0x is
                       prefixed or not, for example "1234567890ABCDEF" or
                       "0x1234567890ABCDEF". If unlocking is allowed, the device
                       will reboot and the bootloader will execute the unlocking.

  "oem lock"           Lock the bootloader.
                       Authentication should be performed before executing the
                       command.
                       The bootloader will be locked on the next reboot.

  "set_active %s"      Set %s as active slot. This will clear unbootable flag
                       for slot %s and reset the retry count to default values.

SONY extensions
---------------

.. code-block:: none

  "Format-TA:<p>"      Formats the TA partition <p>.
                       Valid partitions are between 0-9.

  "Read-TA:<p>:<u>"    Read TA unit <u> from TA partition <p>.
                       Valid partitions are between 0-9.
                       Partition and unit are given as a decimal string.
                       Example:
                       Host:   "Read-TA:2:2053"
                       Read TA unit 2053 from TA partition MiscTA.

                       Client: "DATA00000004"
                       Will upload 4 bytes

                       Client: <0x4a 0x01 0x00 0x00>
                       Response is 4a010000. In this case an integer with
                       the value 0x0000014a.

                       Client: "OKAY"
                       Success

  "Read-all-TA:<p>"    Read all TA units from TA partition <p>.
                       Valid partitions are between 0-9.
                       Partition is given as a decimal string.
                       The response is an array of TA records. If authenticated
                       high TA will be included, otherwise not.
                       Every TA record has three elements:
                       unit number (4 bytes),
                       unit size (4 bytes),
                       unit data (unit size bytes).

                       Example:
                       Host:   "Read-all-TA:1"
                       Read all TA units from TA partition TA.

                       Client: "DATA00004444"
                       Will upload 0x4444 bytes

                       Client: <0x4444 bytes>

                       Client: "OKAY"
                       Success

  "Write-TA:<p>:<u>"   Write TA unit <u> to TA partition <p> with the previously
                       downloaded data.
                       Valid partitions are between 0-9.
                       Partition and unit are given as a decimal string.
                       Example:
                       Host:   "download:00000004"
                       Request to send 4 bytes of data.

                       Client: "DATA00000004"
                       Ready to accept data.

                       Host:   <0x0a 0x00 0x00 0x00>
                       Send data.

                       Client: "OKAY"
                       Success.

                       Host:   "Write-TA:2:2053"
                       Write data to TA unit 2053 to TA partition MiscTA. In this
                       case the data is an integer with the value 0x0000000a.

                       Client: "OKAY"
                       Success.

  "Get-partition-list" Gets all partitions on the device. The response is
                       given as ascii strings separated by comma.
                       Example:
                       Host:   "Get-partition-list"

                       Client: "DATA000000c8"
                       Will upload 200 bytes

                       Client: <200 bytes>
                       Data should be interpreted as comma separated strings
                       (example aboot,abootbak,apdp,...,xblbak").

                       Client: "OKAY"
                       Success.

  "Read-partition:<p>" Read partition <p>. <p> is given as an ascii string. If
                       partition is larger than 2 GB it will be sent in 2 GB
                       chunks each beginning with DATAxxxxxxxx and followed
                       by the actual data.
                       Example:
                       Host:   "Read-partition:system"
                       Request to read system partition.

                       Client: "DATA01234567"
                       Will upload 0x01234567 bytes.

                       Client: <0x01234567 bytes>
                       Sends data.

                       Client: "OKAY"
                       Success.

  "Read-sector[:<l>]:<s>:<e>"
                       Read flash from start sector <s> until end sector <e> on
                       lun <l>. If chunk is larger than 2 GB it will be sent in
                       2 GB chunks each beginning with DATAxxxxxxxx and followed
                       by the actual data.
                       If no lun <l> is provided it will be assumed to be lun 0.
                       Example:
                       Host:   "Read-sector:3:1024:2048"
                       Request to read some sectors from lun 3.

                       Client: "DATA04194304"
                       Will upload 68764564 bytes.

                       Client: <4194394 bytes>
                       Sends data.

                       Client: "OKAY"
                       Success

  "Set-security"       Sets the security properties of the device with the
                       previously downloaded data (platform specific).
                       Example:
                       Host:   "download:00000014"
                       Request to send 20 bytes of data.

                       Client: "DATA00000014"
                       Ready to accept data.

                       Host:   <security properties>
                       Send data.

                       Client: "OKAY"
                       Success.

                       Host:   "Set-security"
                       Set security properties of the device according to
                       downloaded data.

                       Client: "OKAY"
                       Success.

  "SAKE-Authenticate:%s[,%d]"
                       Perform authentication between the device and the host.
                       The first parameter is either "challenge" or "response".
                       The second parameter specifies to which level you
                       authenticate and is only specified for the challenge.
                       0 is "Customer service" and 1 is "Production". Default
                       value is "Production". The authentication method is SAKE,
                       specified in [1].

                       Which commands require authentication is shown in
                       section "Authentication level".

                       Example:
                       Host:   "SAKE-Authenticate:challenge"
                       Request to get authenticated.

                       Client: "DATA00002345"
                       Will send SakeHello message, 0x2345 bytes.

                       Client: < 0x2345 bytes >
                       Send SakeHello message, 0x2345 bytes.
                       The host will pass the SakeHello message to the SECS
                       server and receive SakeDeviceCertificate as a response.

                       Client  "OKAY"

                       Host:   "download:00003456"
                       Request to send SakeDeviceCertificate message,
                       0x3456 bytes.

                       Client: "DATA00003456"
                       Ready to accept SakeDeviceCertificate message,
                       0x3456 bytes.

                       Host:   < 0x3456 bytes >
                       Send SakeDeviceCertificate message, 0x3456 bytes.

                       Client: "OKAY"
                       Success.

                       Host:   "SAKE-Authenticate:response"
                       Verify received SakeDeviceCertificate.

                       Client: "OKAY"
                       Authentication was approved, otherwise "FAIL" is sent.

  "Repartition[:<l>]"  Repartition system. In the UFS case <l> represents the
                       desired LUN to repartition. The LUN value is a number
                       starting from zero. If emmc is used the trailing ":<l>"
                       (including ":") should be omitted.

                       Example:
                       Host:   "download:00004400"
                       Request to send partition table of 0x4400 bytes. The data
                       contains the raw GPT data including the protective MBR
                       and GPT header. The backup GPT is generated by the loader
                       based on the GPT data provided.

                       Client: "DATA00004400"
                       Ready to accept data.

                       Host:   < 0x4400 bytes >
                       Send data, 0x4400 bytes.

                       Client: "OKAY"
                       Success.

                       Host:   "Repartition" (EMMC)
                       Host:   "Repartition:0" (UFS)
                       The host requests to flash a new partition table provided
                       by the download command. In the UFS case we request to
                       access LUN 0.

  "Getnvlog"           Download non volatile log file from device.

                       Example 1:
                       There is a log file.

                       Host:   "Getnvlog"
                       Host indicates it is interested in reading the log file.

                       Client: "DATA00000077"
                       Client will attempt to send the whole log file which in
                       this case is 0x77 Bytes large.

                       Client: < .. 0x77 Bytes of data .. >
                       The log file is in text format.

                       Client: "OKAY"
                       Success.

                       Example 2:
                       There is no log file.

                       Host:   "Getnvlog"

                       Client: "DATA00000000"
                       Client: "OKAY"
                       Success

                       Example 3:
                       Error occurring.

                       Host:   "Getnvlog"

                       Client: "FAILCould not read log file: (<reason>)"
                       FAIL

  "Getlog"             Download log file from device.

                       Example 1:
                       There is a log file.

                       Host:   "Getlog"
                       Host indicates it is interested in reading the log file.

                       Client: "DATA00000077"
                       Client will attempt to send the whole log file which in
                       this case is 0x77 Bytes large.

                       Client: < .. 0x77 Bytes of data .. >
                       The log file is in text format.

                       Client: "OKAY"
                       Success.

                       Example 2:
                       There is no log file.

                       Host:   "Getlog"

                       Client: "DATA00000000"
                       Client: "OKAY"
                       Success

                       Example 3:
                       Error occurring.

                       Host:   "Getlog"

                       Client: "FAILCould not read log file: (<reason>)"
                       FAIL

  "Secure-erase:<p>"   Secure erase of the indicated partition <p>.

  "Erase-sector[:<l>]:<s>:<e>
                       Erase sectors from sector <s> to sector <e> (inclusive)
                       on lun <l>. If no lun is given it will be set to 0.
                       eMMC:<s> should be addressed without lun.

                       Erase sectors 0 to 10 on lun 4.
                       Host: "Erase-sector:4:0:10"

                       Client: "OKAY"

  "Secure-erase-sector[:<l>]:<s>:<e>
                       Secure erase sectors from sector <s> to sector <e>
                       (inclusive) on lun <l>. If no lun is given it will be set
                       to 0.
                       eMMC:<s> should be addressed without lun.

                       Secure erase sectors 0x1000 to 0x2000 on lun 0.
                       Host: "Secure-erase-sector:0:4096:8192"

                       Client: "OKAY"

  "Sync"               Synchronize cache and purge unmapped memory

  "Charge:<b>"         Start charging of the device until it reaches
                       the desired battery capacity specified by <b>.
                       Charging should be enabled by default
                       and should charge the battery to 70%.
                       It can be overridden by this command.
                       If <b> equals 0 charging is disabled.
                       Range for <b>: 0-100. Other values will
                       produce an error.

  "Digest:<p>"         Calculate a digest of the entire partition <p>.
                       The result is returned as a SHA256 hash.

                       Example:

                       Host:   "Digest:boot"
                       Client will now calculate the hash of the partition.
                       !!THIS MIGHT TAKE SOME TIME IF THE PARTITION IS BIG!!

                       Client: "DATA00000020"
                       Client: < 0x20 bytes >
                       Client will send hash as binary data.
                       Client: "OKAY"
                       Success

  "Get-root-key-hash"  Returns a hash of the platform root key. Size of the
                       hash is platform specific, depending on which hash
                       function is used (SHA-256, SHA-384, SHA-512, etc).

                       Example:
                       Host:   "Get-root-key-hash"
                       Request root key hash.

                       Client: "DATA00000020"
                       Client: < 0x20 bytes >
                       Client: "OKAY"
                       Success

  "Get-ufs-info"       Returns UFS device descriptor followed by unit
                       descriptors for each configured lun in one chunk
                       of data.

                       Example:
                       Host:   "Get-ufs-info"
                       The client will compose the response data by reading the
                       device descriptor followed by opening each configured
                       lun and read out the unit descriptor.
                       The format for the descriptors are descibed in the JEDEC
                       standard 220 for UFS, fields "Device Descriptor" and
                       "Unit Descriptor"

                       Client: "DATA000001A7"
                       Client: < 0x1A7 bytes >
                       Client: "OKAY"

  "Get-gpt-info[:<l>]" Get GPT info. In the UFS case <l> represents the
                       desired LUN from which to get the info.
                       The LUN value is a number starting from zero.
                       If emmc is used the trailing ":<l>"
                       (including ":") should be omitted.
                       The data contains the MBR, GPT header and
                       partition table.

  "Get-emmc-info"      Returns eMMC info.

                       Example:
                       Host:   "Get-emmc-info"
                       The client will compose the response data by reading the
                       eMMC properties.
                       The properties read are the contents of the "extended CSD"
                       register, as described in the JEDEC standard 84 for eMMC.

                       Client: "DATA00000200"
                       Client: < 0x200 bytes >
                       Client: "OKAY"

  "Reset-rollback-counter"
                       Reset rollback counters for Verified Boot
                       to allow downgrade of software.

  "Reset-frp"          Erase the frp partition.

                       Example:
                       Host:    "Reset-frp"
                       The client will do a plain erase on the frp partition.
                       Client:  "OKAY"

  "Reboot-bootloader"  Reboot into vendor fastboot.

  "Set-ship-mode"      Enters 'Ship mode'.

                       Example:
                       Host:    "Set-ship-mode"
                       The client will enter ship mode.
                       Client:  "OKAY"

  "Enable-display"     Enables the display.
                       Production level authentication should be performed
                       before executing this command.

                       Example:
                       Host:    "Enable-display"
                       The client will turn on the display.
                       Client:  "OKAY"

  "Disable-display"    Disables the display.
                       Production level authentication should be performed
                       before executing this command.

                       Example:
                       Host:    "Disable-display"
                       The client will turn off the display.
                       Client:  "OKAY"

Client Variables
================

The "getvar:%s" command is used to read client variables which
represent various information about the device and the software
on it.

The various currently defined names are:

.. code-block:: none

  version             Version of FastBoot protocol supported.
                      It should be "0.4" for this document.

  version-bootloader  Version string for the Bootloader.

  version-baseband    Version string of the Baseband Software

  product             Name of the product

  serialno            Product serial number

  secure              If the value is "yes", this is a secure
                      bootloader requiring a signature before
                      it will install or boot images.

  max-download-size   Returns the max download data size that
                      the device can accept.

  has-slot:<partition>
                      If <partition> has slots the response is "yes",
                      otherwise "no".

  current-slot        Returns the active slot.

  slot-count          Returns the number of slots supported by device.

  slot-unbootable:<slot-suffix>
                      Returns “yes” if the given slot is marked as unbootable,
                      "no" otherwise.

  slot-successful:<slot>
                      Return "yes" if <slot> is successful. Otherwise "no".

  slot-retry-count:<slot-suffix>
                      Return the number of retries remaining to attempt to
                      boot the given slot.

  partition-type:<p>  Returns type of file system in partition <p>.
                      Returns FAIL if the given partition is not supported.

  partition-size:<p>  Returns size of partition <p>. The value is given as
                      bytes in hexadecimal form (0x<hex size>).
                      Returns FAIL if the given partition is not supported.

SONY extensions
---------------

.. code-block:: none

  Version-sony        Version of the SONY extensions of the FastBoot protocol.
                      Current version is written at the top of this document.

  Loader-version      Version string of the Loader.

  Phone-id            Device IDs. Two IDs are presented, IMEI == 0000 and
                      MEID == 0001.
                      The string format is:
                      0000:<14 bcd coded digits>,0001:<14 hex digits>
                      Example: 0000:01234567890123,0001:0123456789ABCD

  Device-id           Unique device id presented as an ascii string.

  Rooting-status      Holds information about the controlled rooting status.
                      Possible values are:

                      NOT_ROOTABLE: Invalid SIMLock or ROOTING_ALLOWED is not
                      '1' in the SIMLock data file.

                      ROOTABLE: Valid SIMLock and ROOTING_ALLOWED is '1' in
                      the SIMLock data file, but the device is not yet rooted.

                      ROOTED: The device is successfully rooted.

                      SL_ROOTABLE: Valid SIMLock and ROOTING_ALLOWED is '2' in
                      the SIMLock data file, but in order for the device to be
                      rootable, the SIMLock needs to be unlocked first.

                      SL_UNL_ROOTABLE: Valid SIMLock, ROOTING_ALLOWED is '2'
                      in the SIMLock data file and the SIMLock is unlocked, but
                      the device is not yet rooted.

  Has-been-unlocked   Returns "no" if the bootloader has never been unlocked
                      during the device's lifetime. Otherwise returns "yes".
                      Returns an error if the xfl_sec_data protocol version
                      in the xboot doesn't support the has_been_unlocked flag.

  Platform-id         Identification string for the platform.

  Keystore-counter    Current keystore counter value in secure storage.
                      If not yet provisioned the value should be '0'.

  Keystore-xcs        Returns "yes" if the device has been flashed with a
                      keystore which should not be possible to update,
                      otherwise returns "no". This value is retrieved from
                      secure storage.

  Default-security    Default security state of the device based on the fuses.
                      Possible values are:
                      "ON"  Security is enabled.
                      "OFF" Security is disabled.

  Ufs-info            Sends back information about the UFS memory (if it has
                      one).
                      It's formatted in this way:
                      < Vendor name,model,version >

                      Example:
                      SAMSUNG,KLUCG4J1EB-B0B1,0200

  S1-root             Will return all valid S1 roots on device. If platform
                      security is disabled (unfused unit) it will reply with
                      both S1_Root_xxxx and S1_Test_Root_xxxx.

  Sake-root           Will return the ascii representation of the first two
                      bytes of sake root public hash.
                      If there is a sake test root available it will be in the
                      response, if not then it will be the live root.

  Frp-partition       Name of the the Factory Reset Protection partition

  Sector-size         Sector size of the default storage

  Emmc-info           Sends back information about the EMMC memory (if it has
                      one).
                      It's formatted in this way:
                      < Vendor name,model,version >

  Security-state      The SHA256 hash over the keystore payload in case there
                      is a valid keystore in the device. The hash format is
                      standard 'base64' encoding for RFC 3548 or RFC 4648.

  Stored-security-state
                      Returns the SHA256 hash over the keystore payload of the
                      latest successfully applied keystore. The value is
                      retrieved from the secure storage. The hash format is
                      standard 'base64' encoding for RFC 3548 or RFC 4648.

  USB-version         Returns which USB version we are currently communicating
                      with.

  Battery             Returns the battery capacity in percentage. The returned
                      value is a number between 0 and 100. Returns N/A if
                      operation is not supported on this platform.

  Rollback-index-count
                      Returns number of existing VB meta rollback counters.

  Rollback-index:<i>  Returns the value of rollback counter at index <i>.
                      Rollback index ranges from 0 to Rollback-index-count - 1.


  X-conf              Return all valid X-conf roots on device. If platform
                      security is disabled (unfused or test fused unit) it will
                      reply with identifiers for both certificates. The exact
                      identifier is the ascii representation of the first two
                      bytes of root public key SHA1 hash in PEM format. If the
                      test root is available it will be first identifier in the
                      list followed by the live root.

                      Example:
                      b98a,b94e

  Soc-unique-id       Will return the ascii representation of
                      SoC unique identifier (SUID), which is consisted of
                      Silicon Provider ID - 4Bytes LSB first,
                      SoC Model Identifier - 4Bytes,
                      Chip Serial Number as bytes 4-11 of SHA256 over MEID.

                      Example:
                      "090000006607000014662a82bdbb196e"
                      Silicon Provider ID: 00000009
                      SoC ID or chip->hwCode: 66070000
                      bytes 4-11 of SHA256 over MEID: 14662a82bdbb196e

  SD-card-inserted    Returns "yes" if an external SD card is currently
                      inserted in the device, "no" otherwise.

Names starting with a lowercase character are reserved by this
specification.  OEM-specific names should not start with lowercase
characters.


TCP Protocol v1
===============

The TCP protocol is designed to be a simple way to use the fastboot protocol
over ethernet if USB is not available.

The device will open a TCP server on port 5554 and wait for a fastboot client
to connect.

Handshake
---------
Upon connecting, both sides will send a 4-byte handshake message to ensure they
are speaking the same protocol. This consists of the ASCII characters "FB"
followed by a 2-digit base-10 ASCII version number. For example, the version 1
handshake message will be [FB01].

If either side detects a malformed handshake, it should disconnect.

The protocol version to use must be the minimum of the versions sent by each
side; if either side cannot speak this protocol version, it should disconnect.

Fastboot Data
-------------
Once the handshake is complete, fastboot data will be sent as follows:

  [data_size][data]

Where data_size is an unsigned 8-byte big-endian binary value, and data is the
fastboot packet. The 8-byte length is intended to provide future-proofing even
though currently fastboot packets have a 4-byte maximum length.

Example
-------
In this example the fastboot host queries the device for two variables,
"version" and "none".

::

    Host    <connect to the device on port 5555>
    Host    FB01
    Device  FB01
    Host    [0x00][0x00][0x00][0x00][0x00][0x00][0x00][0x0E]getvar:version
    Device  [0x00][0x00][0x00][0x00][0x00][0x00][0x00][0x07]OKAY0.4
    Host    [0x00][0x00][0x00][0x00][0x00][0x00][0x00][0x0B]getvar:none
    Device  [0x00][0x00][0x00][0x00][0x00][0x00][0x00][0x04]OKAY
    Host    <disconnect>


UDP Protocol v1
===============

The UDP protocol is more complex than TCP since we must implement reliability
to ensure no packets are lost, but the general concept of wrapping the fastboot
protocol is the same.

Overview:
  1. As with TCP, the device will listen on UDP port 5554.
  2. Maximum UDP packet size is negotiated during initialization.
  3. The host drives all communication; the device may only send a packet as a
     response to a host packet.
  4. If the host does not receive a response in 500ms it will re-transmit.

UDP Packet format
-----------------
  +----------+----+-------+-------+--------------------+
  | Byte #   | 0  |   1   | 2 - 3 |  4+                |
  +----------+----+-------+-------+--------------------+
  | Contents | ID | Flags | Seq # | Data               |
  +----------+----+-------+-------+--------------------+

  ID      Packet ID:
            0x00: Error.
            0x01: Query.
            0x02: Initialization.
            0x03: Fastboot.

          Packet types are described in more detail below.

  Flags   Packet flags: 0 0 0 0 0 0 0 C
            C=1 indicates a continuation packet; the data is too large and will
                continue in the next packet.

            Remaining bits are reserved for future use and must be set to 0.

  Seq #   2-byte packet sequence number (big-endian). The host will increment
          this by 1 with each new packet, and the device must provide the
          corresponding sequence number in the response packets.

  Data    Packet data, not present in all packets.

Packet Types
------------
Query     The host sends a query packet once on startup to sync with the device.
          The host will not know the current sequence number, so the device must
          respond to all query packets regardless of sequence number.

          The response data field should contain a 2-byte big-endian value
          giving the next expected sequence number.

Init      The host sends an init packet once the query response is returned. The
          device must abort any in-progress operation and prepare for a new
          fastboot session. This message is meant to allow recovery if a
          previous session failed, e.g. due to network error or user Ctrl+C.

          The data field contains two big-endian 2-byte values, a protocol
          version and the max UDP packet size (including the 4-byte header).
          Both the host and device will send these values, and in each case
          the minimum of the sent values must be used.

Fastboot  These packets wrap the fastboot protocol. To write, the host will
          send a packet with fastboot data, and the device will reply with an
          empty packet as an ACK. To read, the host will send an empty packet,
          and the device will reply with fastboot data. The device may not give
          any data in the ACK packet.

Error     The device may respond to any packet with an error packet to indicate
          a UDP protocol error. The data field should contain an ASCII string
          describing the error. This is the only case where a device is allowed
          to return a packet ID other than the one sent by the host.

Packet Size
-----------
The maximum packet size is negotiated by the host and device in the Init packet.
Devices must support at least 512-byte packets, but packet size has a direct
correlation with download speed, so devices are strongly suggested to support at
least 1024-byte packets. On a local network with 0.5ms round-trip time this will
provide transfer rates of ~2MB/s. Over WiFi it will likely be significantly
less.

Query and Initialization packets, which are sent before size negotiation is
complete, must always be 512 bytes or less.

Packet Re-Transmission
----------------------
The host will re-transmit any packet that does not receive a response. The
requirement of exactly one device response packet per host packet is how we
achieve reliability and in-order delivery of packets.

For simplicity of implementation, there is no windowing of multiple
unacknowledged packets in this version of the protocol. The host will continue
to send the same packet until a response is received. Windowing functionality
may be implemented in future versions if necessary to increase performance.

The first Query packet will only be attempted a small number of times, but
subsequent packets will attempt to retransmit for at least 1 minute before
giving up. This means a device may safely ignore host UDP packets for up to 1
minute during long operations, e.g. writing to flash.

Continuation Packets
--------------------
Any packet may set the continuation flag to indicate that the data is
incomplete. Large data such as downloading an image may require many
continuation packets. The receiver should respond to a continuation packet with
an empty packet to acknowledge receipt. See examples below.

Summary
-------
The host starts with a Query packet, then an Initialization packet, after
which only Fastboot packets are sent. Fastboot packets may contain data from
the host for writes, or from the device for reads, but not both.

Given a next expected sequence number S and a received packet P, the device
behavior should be:

::

  if P is a Query packet:
    * respond with a Query packet with S in the data field
  else if P has sequence == S:
    * process P and take any required action
    * create a response packet R with the same ID and sequence as P, containing
      any response data required.
    * transmit R and save it in case of re-transmission
    * increment S
  else if P has sequence == S - 1:
    * re-transmit the saved response packet R from above
  else:
    * ignore the packet

Examples
--------
In the examples below, S indicates the starting client sequence number.

.. code-block:: none

    Host                                    Client
    ======================================================================
    [Initialization, S = 0x55AA]
    [Host: version 1, 2048-byte packets. Client: version 2, 1024-byte packets.]
    [Resulting values to use: version = 1, max packet size = 1024]
    ID   Flag SeqH SeqL Data                ID   Flag SeqH SeqL Data
    ----------------------------------------------------------------------
    0x01 0x00 0x00 0x00
                                            0x01 0x00 0x00 0x00 0x55 0xAA
    0x02 0x00 0x55 0xAA 0x00 0x01 0x08 0x00
                                            0x02 0x00 0x55 0xAA 0x00 0x02 0x04 0x00

    ----------------------------------------------------------------------
    [fastboot "getvar" commands, S = 0x0001]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x03  0x00  0x00  0x01  getvar:version
                                            0x03  0x00  0x00  0x01
    0x03  0x00  0x00  0x02
                                            0x03  0x00  0x00  0x02  OKAY0.4
    0x03  0x00  0x00  0x03  getvar:none
                                            0x03  0x00  0x00  0x03
    0x03  0x00  0x00  0x04
                                            0x03  0x00  0x00  0x04  FAILUnknown var

    ----------------------------------------------------------------------
    [fastboot "INFO" responses, S = 0x0000]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x03  0x00  0x00  0x00  <command>
                                            0x03  0x00  0x00  0x00
    0x03  0x00  0x00  0x01
                                            0x03  0x00  0x00  0x01  INFOWait1
    0x03  0x00  0x00  0x02
                                            0x03  0x00  0x00  0x02  INFOWait2
    0x03  0x00  0x00  0x03
                                            0x03  0x00  0x00  0x03  OKAY

    ----------------------------------------------------------------------
    [Chunking 2100 bytes of data, max packet size = 1024, S = 0xFFFF]
    ID   Flag SeqH SeqL Data                ID   Flag SeqH SeqL Data
    ----------------------------------------------------------------------
    0x03 0x00 0xFF 0xFF download:0000834
                                            0x03 0x00 0xFF 0xFF
    0x03 0x00 0x00 0x00
                                            0x03 0x00 0x00 0x00 DATA0000834
    0x03 0x01 0x00 0x01 <1020 bytes>
                                            0x03 0x00 0x00 0x01
    0x03 0x01 0x00 0x02 <1020 bytes>
                                            0x03 0x00 0x00 0x02
    0x03 0x00 0x00 0x03 <60 bytes>
                                            0x03 0x00 0x00 0x03
    0x03 0x00 0x00 0x04
                                            0x03 0x00 0x00 0x04 OKAY

    ----------------------------------------------------------------------
    [Unknown ID error, S = 0x0000]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x10  0x00  0x00  0x00
                                            0x00  0x00  0x00  0x00  <error message>

    ----------------------------------------------------------------------
    [Host packet loss and retransmission, S = 0x0000]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x03  0x00  0x00  0x00  getvar:version [lost]
    0x03  0x00  0x00  0x00  getvar:version [lost]
    0x03  0x00  0x00  0x00  getvar:version
                                            0x03  0x00  0x00  0x00
    0x03  0x00  0x00  0x01
                                            0x03  0x00  0x00  0x01  OKAY0.4

    ----------------------------------------------------------------------
    [Client packet loss and retransmission, S = 0x0000]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x03  0x00  0x00  0x00  getvar:version
                                            0x03  0x00  0x00  0x00 [lost]
    0x03  0x00  0x00  0x00  getvar:version
                                            0x03  0x00  0x00  0x00 [lost]
    0x03  0x00  0x00  0x00  getvar:version
                                            0x03  0x00  0x00  0x00
    0x03  0x00  0x00  0x01
                                            0x03  0x00  0x00  0x01  OKAY0.4

    ----------------------------------------------------------------------
    [Host packet delayed, S = 0x0000]
    ID    Flags SeqH  SeqL  Data            ID    Flags SeqH  SeqL  Data
    ----------------------------------------------------------------------
    0x03  0x00  0x00  0x00  getvar:version [delayed]
    0x03  0x00  0x00  0x00  getvar:version
                                            0x03  0x00  0x00  0x00
    0x03  0x00  0x00  0x01
                                            0x03  0x00  0x00  0x01  OKAY0.4
    0x03  0x00  0x00  0x00  getvar:version [arrives late with old seq#, is ignored]


Program image on secure device with verification
================================================

Programming an image to a partition on a secure device requires additional
verification. The image must be accompanied by a signature that verify the
authenticity against a root of trust, integrity protects the image, and
inform the client what partition the data is intended for.

Note: Any command that modify content in flash memory or alter security
settings and has not been preceded by a signature or authentication command
shall fail.

Below outline the sequence required to program a image

1. Pass signature command to the client.

   Signature data comprise of a list of SHA256 hashes contained in a CMS
   message. There is a single SHA256 hash for every payload that is to be
   programmed to the partition outlined in the CMS message.

   Example: A sparse image consist of several payloads of data divided by gaps
   (don't care blocks) in the image.

   Verify signature using attached certificate chain.
   Verify certificate chain against root of trust.

2. Send erase:<p> command to client.

   In case the <p> partition differs from the intended partition in the
   signature, fail the command.

   Optionally use Secure-erase:<p> instead to ensure that existing data in
   partition is purged, e.g. when programming userdata partition.

   Note: This step is required if verification is to be conducted after
   programming of the image.

3. Send download command.

   Important note: downloaded data can only be as large as the
   getvar max-download-size stipulate.

4. Send flash:<p> command to client.

   Previously downloaded data shall be hashed and verified against hash in
   hashlist, if not equal, fail the command.

   In case the <p> partition differs from the intended partition in the
   signature, fail the command.

5. Repeat from step 3. until all data has been programmed.

6. Send Digest:<p> command to calculate a checksum hash over the partition.

   Important note: checksum cover entire partition not only the downloaded
   image.

   The calculcated checksum can be compared against a precalculated checksum
   accompaning the image to ensure that all data has been correctly programmed
   to device flash memory.

   Note:
   Optionally the Digest command are run after all images in a session have been
   flashed to the device. This could increase the likelihood of catching errors
   connected to the flash memory, e.g. bit flips.

Authentication level
====================

The authentication level is a Sony addition.

Different commands require different authentication levels depending on their
nature. There are 3 levels available:

* NONE
* CS
* PRODUCTION (also grants CS authentication)

The levels required for different commands are specified in the table below:

+------------------------+------------------+-----------------------------------------+
| Command                | Authentication   | Notes                                   |
+========================+==================+=========================================+
| getvar                 | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| download               | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| signature: (with       | NONE             |                                         |
| parameters)            |                  |                                         |
+------------------------+------------------+-----------------------------------------+
| signature              | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| flash                  | PRODUCTION       || If signature is sent before flash for  |
|                        |                  || the corresponding partition and        |
|                        |                  || verification passes then SAKE          |
|                        |                  || authentication is not needed           |
+------------------------+------------------+-----------------------------------------+
| erase                  | PRODUCTION       || If signature is sent before erase for  |
|                        |                  || the corresponding partition and        |
|                        |                  || verification passes then SAKE          |
|                        |                  || authentication is not needed           |
+------------------------+------------------+-----------------------------------------+
| continue               | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| reboot                 | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| reboot-bootloader      | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| powerdown              | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| oem unlock             | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| oem lock               | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| set_active             | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Format-TA              | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| Read-TA                | NONE             || Operations on high MiscTA (unit nr >   |
|                        |                  || 65535 require PRODUCTION authentication|
+------------------------+------------------+-----------------------------------------+
| Read-all-TA            | NONE             || Includes high MiscTA units if          |
|                        |                  || PRODUCTION authenticated               |
+------------------------+------------------+-----------------------------------------+
| Write-TA               | NONE             || Operations on high MiscTA (unit nr >   |
|                        |                  || 65535 require PRODUCTION authentication|
+------------------------+------------------+-----------------------------------------+
| Get-partition-list     | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Read-partition         | PRODUCTION       || Exception: Read-partition:apps_log     |
+------------------------+------------------+-----------------------------------------+
| Read-sector            | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| Set-Security           | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| SAKE-Authenticate      | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Repartition            | PRODUCTION       || If signature is sent before Repartition|
|                        |                  || and verification passes then SAKE      |
|                        |                  || authentication is not needed           |
+------------------------+------------------+-----------------------------------------+
| Getnvlog               | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Getlog                 | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Secure-erase           | PRODUCTION       || If signature is sent before            |
|                        |                  || Secure-erase for the corresponding     |
|                        |                  || partition and verification passes then |
|                        |                  || SAKE authentication is not needed      |
+------------------------+------------------+-----------------------------------------+
| Erase-sector           | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| Secure-erase-sector    | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| Sync                   | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Charge                 | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Digest                 | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Get-root-key-hash      | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Get-ufs-info           | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Get-gpt-info           | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Get-emmc-info          | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Reset-rollback-counter | CS               |                                         |
+------------------------+------------------+-----------------------------------------+
| Reset-frp              | CS               |                                         |
+------------------------+------------------+-----------------------------------------+
| Reboot-bootloader      | NONE             |                                         |
+------------------------+------------------+-----------------------------------------+
| Set-ship-mode          | NONE             || Before 0.54, it was PRODUCTION         |
+------------------------+------------------+-----------------------------------------+
| Enable-Display         | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+
| Disable-Display        | PRODUCTION       |                                         |
+------------------------+------------------+-----------------------------------------+


Translation table S1 protocol -> Fastboot
=========================================

.. code-block:: none

    S1 Command                      Fastboot command
    ------------------------------------------------
    Version Info                    getvar:version
      Comment: Only replies the protocol version. All other info need to be
      specifically requested, alternatively can getvar:all be used.
    Change Baud Rate                N/A
    Execute Software                N/A
    Shutdown                        powerdown
    Validate SIN Header             signature
    Data Image                      flash,Flash-stream
    Get Last Error                  N/A
    Force Open TA                   N/A
    Open TA                         N/A
    Close TA                        N/A
    Format TA                       Format-TA
    Read TA Unit                    Read-TA <p>:<u>
    Write TA Unit                   Write-TA <p>:<u>
    Read Memory Image               Read-partition <p>
    Set Security Properties         Set-security
    Authenticate                    SAKE-Authenticate
    Read All TA                     Read-all-TA
    Asynchronous Command Status     N/A
    Erase Device                    erase:<p>
    Get Partition List              Get-partition-list
    SwitchToUSB                     N/A
    BadBlockScan                    N/A
    SetBlockStatus                  N/A
    SetLoaderConfiguration          N/A
    eMMC Control                    Flash-info
    Charge while flashing           Charge
    GetEMMCWearStatus               N/A
    Register Write                  N/A
    Read Memory Hash                N/A

.. code-block:: none

    Version info tags
    S1 Tag                          Fastboot variable     Comment
    -------------------------------------------------------------
    PROT_VER                        version               Protocol version.
    ID                              version-bootloader    First part should be
                                                          space number.
    VER                             version-bootloader    Last part should be
                                                          version.
    S1SBL_VER                       Loader-version
    TYPE                            N/A
    ACTIVE_COMP_AID                 N/A
    MAX_PKT_SIZE                    N/A
    DEBUG_MESSAGE                   N/A
    IGNORE_CRC                      N/A
    DEF_SEC                         secure
    HWCONF_AID                      N/A                   Needed for rollback
                                                          prevention
    LOADER_AID                      N/A
    BOOT_AID                        N/A
    PLF_ROOT                        Get-root-key-hash     Get root key hash
    S1_ROOT                         S1-root
    NO_SUB_SYSTEMS                  N/A
    OTP_DATA_N                      N/A
    OTP_LOCK_STATUS_N               N/A
    UNIQUE_DEV_ID_N                 Device-id
    IDCODE_N                        Platform-id
    SUID_N                          Soc-unique-id         Needed if Trustonic is
                                                          used.
    AUTH_MET                        N/A
    AUTH_LEVEL                      N/A
    MEMDEVS                         N/A                   Replaced by command
                                                          Flash-info.
    MSN                             serialno
    HW_CONFIG_VER                   N/A
    HW_CONFIG                       N/A                   Read TA HWConfig instead.
    IMEI                            N/A                   See PhoneID
    PHONE_ID                        Phone-id              IMEI and MEID
    PROD_ID                         N/A
    GLOB_SEC                        N/A                   Read TA HWConfig instead.
    CARD_PRESENT                    SD-card-inserted
    CARD_SIZE                       N/A
    CARD_SIZE                       N/A
    ROOTING_STATUS                  Rooting-status
    RAM_INFO                        N/A
    HW_CONFIG_INFO                  N/A
    SEC_STATE                       Security-state
    REMOTE_LOCK                     N/A
    FRP_PARTITION                   Frp-partition
