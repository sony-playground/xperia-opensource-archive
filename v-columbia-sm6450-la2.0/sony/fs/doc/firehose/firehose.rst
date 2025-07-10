Firehose
====================================================

Terminology
-----------

#. EDL
   Emergency Download Mode (Hardware Service Mode)
#. RAM
   Random Access Memory
#. USB
   Universal Serial Bus

Introduction
------------

Firehose is used in EDL. The Firehose binary is loaded into RAM over USB via the
Sahara protocol and can be used for writing to device storage, recovery and
initial configuration of the device, etc. A more thorough description of the
protocol can be found in Qualcomm document 80-NG319-1 Rev. A - Firehose Protocol
V2.0 Definition Document.

References
==========
| [1] Firehose Protocol V2.0 Definition Document, 80-NG319-1 Rev. A
| [2] Qualcomm Firehose Loader User Guide, 80-P6549-1 Rev C
| [3] SEMC Authentication and Key Establishment protocol, 23/159 35-LXE 108 116
| [4] Source Code: <boot_path>/boot_images/QcomPkg/Library/
|     Particularly DevPrgLib and DevPrgSomcLib.


Basic Requirements
==================

USB
---
* Two bulk endpoints (in, out) are required.
* Assumed to run over a reliable USB channel in a secure environment.
* The protocol is entirely host-driven and synchronous like fastboot.
  (but unlike the multi-channel, bi-directional, asynchronous ADB protocol)

Packets
-------
* Two types of packets are used in Firehose protocol;
  Plain text commands and Raw data.
* Plain text commands are non-fixed length, plain text documents in an XML file
  structure. The XML text supports Unicode ASCII text (UTF-8).
* Raw data packets are used for uploading and downloading binary data. The
  structure of raw data packets is raw binary data with no framing or encoding.
  The smallest size could be 1 byte, and the largest could be up to the maximum
  payload size allowed by the target (e.g. 16KB or larger).

Transport and Framing
---------------------

#. Host sends a non-fixed plain ASCII text command, which is in an XML format.

#. Target responds with a non-fixed plain ASCII text. Target responds either
   with <response> tag and/or <log>.

   a. <response> -> ACK or NAK to indicate success or failure. It may return
      additional variables as attributes along with values used for
      configuring/reading/programming. Then go to step #3 if rawmode attribute
      is set to "true" which indicates that the target is in RAW DATA mode.
      Or Stop with rawmode="false".

   b. <log> -> respond with human readable message. Then Stop.

#. Raw data mode. Depending on the command, the host or target will send
   the indicated amount of data. Acceptable packet size ranges from 1 byte to
   the specified amount in chunks of the maximum payload size allowed by target.
   Target switches to RAW MODE by setting rawmode="true" to start receiving data.
   Once the target is in RAW DATA mode, it treats any bytes received as RAW DATA
   until the total number of bytes indicated has been received. Even if a command is
   sent in-between in an XML command format, the target assumes it to be RAW DATA.

#. Target responds with a non-fixed plain ASCII text as in #2. Target responds
   with <response> tag and/or with <log> in some cases.

   a. <response> -> ACK if command was successful or NAK if it failed. Return
      additional variables as attributes if it exists then go to #5.

   b. <log> -> respond with human readable messages. Repeat responding with log
      according to how "AckRawDataEveryNumPackets" is set in a previous
      <configure> command if it was sent until a response with rawmode="false".
      Then Stop.

#. rawmode="false". Stop.

Example Session
---------------

A typical firehose <nop> and <response> command structures looks as follows:

.. code-block:: none

    Host:    send a dummy command that requests nothing
             <?xml version="1.0"?>
             <data>
             <nop value="ping"/>
             </data>

    Target:  return "ACK"
             <?xml version="1.0"?>
             <data>
             <response value="ACK"/>
             </data>

For the sake of brevity, the xml prolog and data element will be excluded
from this point onwards. Below is a session with 10 transactions for sending
and receiving a binary text data "hello world".

.. code-block:: none

    Host:    configure device for programming
             <configure MaxDigestTableSizeInBytes="4096" MemoryName="eMMC"
                        TargetName="8960"
                        MaxPayloadSizeToTargetInBytes="131072"/>

    Target:  acknowledge configuration and return relevant attributes
             <response value="ACK" MinVersionSupported="1" MemoryName="eMMC"
                       MaxPayloadSizeFromTargetInbytes="4096"
                       MaxPayloadSizeToTargetInBytes="131072" Version="1"
                       TargetName="8960"/>

    Host:    send program command with data attributes
             <program SECTOR_SIZE_IN_BYTES="512" read_back_verify="1"
                      num_partition_sectors="1" physical_partition_number="0"
                      start_sector="0"/>

    Target:  acknowledge programming and switch to RAW DATA mode
             <response value="ACK" rawmode="true"/>

    Host:    transfer 512 bytes of hello world text binary data
             68 65 6C 6C 6F 20 77 6F 72 6C 64 0D 0A 00 00 00
             00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
             .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
             .. .. .. skipping 28 lines (448 bytes) .. .. ..
             .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
             00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
             00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

    Target:  acknowledge data received and exit RAW DATA mode
             <response value="ACK" rawmode="false"/>

    Host:    set partition 0 to be active
             <setbootablestoragedrive value="0"/>

    Target:  acknowledge setbootablestoragedrive command
             <response value="ACK"/>

    Host:    reset device by using power command
             <power value="reset"/>

    Target:  acknowledge power command and reset
             <response value="ACK"/>


Start-up Sequence Diagram
=========================

.. uml::
  :caption: Firehose startup flow

  @startuml
  group Firehose (EDL)
  Firehose -> Firehose: init
  host -> Firehose: Send 'configure command'
  Firehose --> host: Device parameters
  host -> Firehose: Send 'getstorageinfo command'
  Firehose --> host: Storage parameters
  host -> Firehose: Send 'somcauth command'
  Firehose --> host: Send SAKE challenge
  host -> security_server: Relay SAKE challenge
  security_server -> host: Send SAKE response
  host -> Firehose: Relay Sake response
  Firehose -> Firehose: Verify SAKE response
  Firehose --> host: OK
  host -> Firehose: Send commands that need authentication
  Firehose --> host: Response
  end
  @enduml


Command Reference
=================

* Commands are indicated as elements/tags in angle brackets with parameters
  as attributes following the standard XML structure format.

* Sending multiple tags in a single file to target is not allowed.

* Commands are not case sensitive as well as its variables.

* The protocol allows a sense of forward compatibility where new commands or
  variables in new versions will not break previous target versions since
  the Firehose protocol will only extract the fields it is looking for
  from each plain text command.

.. code-block:: none

  Host side commands

  <program>             Writes data to the flash on the device.
                        It could also be used to erase a certain area
                        of flash memory by writing either 0x00 or 0xFF.

                        Example:
                        Host: send dummy.bin to target for written.
                        <program SECTOR_SIZE_IN_BYTES="512" filename="dummy.bin"
                                  num_partition_sectors="4096"
                                  physical_partition_number="0" start_sector="0"/>
                        Target: acknowledge and enter DATA mode to receive data.
                        <response value="ACK" rawmode=”true”/>
                        Host: transfer dummy.bin as raw data.
                        00 00 00 00 00 ... dummy.bin ... 00 00 00 00 00
                        Target: acknowledge that the write was successful and
                                exit DATA mode.
                        <response value="ACK" rawmode=”false”/>

  <read>                Reads sectors from flash on the device.

                        Example:
                        Host: read the sectors specified and store them in the
                              host as dummy.bin.
                        <read SECTOR_SIZE_IN_BYTES="512" filename="dummy.bin"
                              num_partition_sectors="4096"
                              physical_partition_number="0" start_sector="0"/>
                        Target: acknowledge and enter DATA mode to send data.
                        <response value="ACK" rawmode=”true”/>
                        Target: transfer the data to be stored as dummy.bin
                        00 00 00 00 00 ... dummy.bin ... 00 00 00 00 00
                        Target: acknowledge that the read command was
                                successful and exit DATA mode.
                        <response value="ACK" rawmode=”false”/>

  <nop>                 A dummy command that can be sent to the target,
                        which is free to ACK or NAK.
                        It also sends basic device information to host.

                        Example:
                        Host: send a dummy command that requests nothing
                        <nop value="foo"/>
                        Target: respond with NAK. It could as well be ACK.
                        <response value="NAK"/>

  <patch>               Writes individual bytes with CRC. This command is
                        deprecated and scheduled to be removed.

                        Example:
                        Host: patch the device when generating partition table.
                              (part of several patch commands)
                        <patch byte_offset="40" filename="DISK"
                                physical_partition_number="0" size_in_bytes="8"
                                start_sector="7" SECTOR_SIZE_IN_BYTES=”512”
                                value="NUM_DISK_SECTORS-34."/>
                        Target: acknowledge that the patch was successful.
                        <response value="ACK"/>

  <configure>           Configures and defines protocol parameters used in
                        read/write transaction.

                        Example:
                        Host: inform the target about the payload size intended
                              to be used.
                        <configure MaxPayloadSizeToTargetInBytes="8192"/>
                        Target: respond by echoing the same size to inform the
                                host that the target can handle the intended size.
                        <response value="ACK" MaxXMLSizeInBytes=”2048”
                                  MaxPayloadSizeToTargetInBytes="8192"/>

  <setbootablestoragedrive>
                        Defines which storage drive (Physical Partition) will be
                        made bootable/active

                        Example:
                        Host: set the first physical partition active/bootable;
                              BOOT1 for eMMC or LUN1 for a UFS device.
                        <setbootablestoragedrive value="1"/>
                        Target: acknowledge that the command was successful.
                        <response value="ACK"/>

  <erase>               Erases sectors in flash memory on device.

                        Example:
                        Host: erase physical partition 0.
                        <erase StorageDrive="0"/>
                        Target: acknowledge that the erase was successful
                        <response value="ACK"/>

  <power>               Controls the power of the device.

                        Example:
                        Host: reset the device
                        <power value="reset"/>
                        Target: acknowledge that the reset was successful
                        <response value="ACK"/>
                        Target: resets

  <getstorageinfo>      Used to retrieve information about any physical partition
                        in eMMC or LUN on UFS device.

                        Example:
                        Host: retrieve information about the first physical
                              partition in eMMC or the first LUN on UFS device.
                        <getStorageInfo physical_partition_number=”1”/>
                        Target: responds back with the parameters of the requested
                                partition or LUN.
                        <log num_partition_sectors=1024 SECTOR_SIZE_IN_BYTES=512
                              num_physical_partitions=4 serial_num=1234/>
                        Target: acknowledge that getstorageinfo was successful.
                        <response value="ACK"/>

  <benchmark>           Can be used to benchmark storage write performance.

                        Example:
                        Host: test the write performance on the flash storage.
                        <benchmark trials="1000" TestWritePerformance="1"/>
                        Target: acknowledge that the test was successful
                        <response value="ACK"/>

  <peek>                The peek command can be used to read memory directly from
                        the device at any location for a given number of bytes.

                        Example:
                        Host: read 10 bytes starting at address 0x10000.
                        <peek address64=”0x10000” size_in_bytes=”10”/>
                        Target: acknowledge that the read/peek was successful.
                        <response value="ACK"/>

  <poke>                Used to write an 8-bit to 64-bit value to any address on
                        the device.

                        Example:
                        Host: write 2 bytes at the address location "0x10000"
                        <poke address64=”0x10000” size_in_bytes=”2” value=”0x2343”/>
                        Target: acknowledge that the write/poke was successful.
                        <response value="ACK"/>

  <ufs>                 The UFS commands are used during provisioning and
                        configuring your ufs device.

                        Example:
                        Host: describe the number of LUNs and details of a UFS
                              device to be provisioned.
                              (part of several ufs commands)
                        <ufs bNumberLU="5" bBootEnable="1" bDescrAccessEn="0"
                              bInitPowerMode="1" bHighPriorityLUN="0"
                              bSecureRemovalType="0" bInitActiveICCLevel="0"
                              wPeriodicRTCUpdate="0"/>
                        Target: acknowledge that the ufs command was successful
                        <response value="ACK"/>

  <fixgpt>              Used to restore and manipulate GPT attributes.

                        Example:
                        Host: grow the last partition to fill the disk.
                        <fixgpt grow_last_partition="1"/>
                        Target: acknowledge that fixgpt was successful
                        <response value="ACK"/>

  <getsha256digest>     Used to get a unique signature of data present in
                        storage.

                        Example:
                        Host: hash 2MB of data starting from sector 0.
                        <getsha256digest SECTOR_SIZE_IN_BYTES="512"
                                          num_partition_sectors="4096"
                                          physical_partition_number="0"
                                          start_sector="0"/>
                        Target: confirm that hashing has started.
                        <log value="Hash start sector 0 num sectors 4096"/>
                        Target: return the digest/hash result as a log.
                                (this is an example of what a hash might look like)
                        <log value="Digest 5647F05EC18958947D32874EEB788FA396A05D0B
                                           AB7C1B71F112CEB7E9B31EEE"/>
                        Target: acknowledge that hashing was successful.
                        <response value="ACK"/>


  Target side Commands

  <response>            Used to ACK or NAK commands as well as return
                        additional variables used for reading/programming.

                        Example:
                        Take a look at previous examples.

  <log>                 Used to send human readable message.

                        Example:
                        Take a look at previous examples.


SONY extensions
---------------

.. code-block:: none

 <somcauth>            Used to authenticate commands that require authentication.

                       Example:
                       Host: request target for sake challenge to be sent to the
                             security server.
                       <somcauth size_in_bytes="5"/>
                       Target: acknowledge and enter DATA mode to send data.
                       <response value="ACK" rawmode=”true”/>
                       Target: transfer sake challenge back to host
                       00 00 00 00 ... sake challenge ... 00 00 00 00
                       Target: acknowledge that sending sake challenge was
                               successful and exit DATA mode.
                       <response value="ACK" rawmode=”false”/>
                       Host: relay response back from security server to target.
                       <somcauth size_in_bytes="2028"/>
                       Target: acknowledge and enter DATA mode to receive data.
                       <response value="ACK" rawmode=”true”/>
                       Host: transfer response from security server as raw data.
                       00 00 00 00 ... sake response ... 00 00 00 00
                       Target: acknowledge that receiving sake response was
                               successful and exit DATA mode.
                       <response value="ACK" rawmode=”false”/>
                       Target: acknowledge that somcauth was successful and send
                               back OKAY to confirm successful authentication.
                       <response value="ACK" rawmode=”true”/>
                       Target: transfer OKAY back to host
                       00 00 00 00 00 ... OKAY ... 00 00 00 00 00 00
                       Target: acknowledge that sending OKAY was successful and
                               exit DATA mode.
                       <response value="ACK" rawmode=”false”/>


Variable Reference
==================

Commands are accompanied with one or more variable as attributes to fill in the
parameters required to execute the commands. Below is a table that maps commands
with its associated attributes followed by description of each.

   +-------------------------+-----------------------------------------------+
   | Command                 | Variables/Attributes                          |
   +=========================+===============================================+
   | nop                     || value                                        |
   +-------------------------+-----------------------------------------------+
   | configure               || SkipWrite, SkipStorageInit, MemoryName,      |
   |                         || AckRawDataEveryNumPacket, AlwaysValidate,    |
   |                         || Verbose, Version, TargetName, BuildId,       |
   |                         || DateTime, MaxXMLSizeInBytes,                 |
   |                         || MinVersionSupported,                         |
   |                         || MaxPayloadSizeFromTargetInBytes,             |
   |                         || MaxDigestTableSizeInBytes,                   |
   |                         || MaxPayloadSizeToTargetInBytes,               |
   |                         || ZLPAwareHost                                 |
   +-------------------------+-----------------------------------------------+
   | program                 || SECTOR_SIZE_IN_BYTES, num_partition_sectors  |
   |                         || physical_partition_number, start_sector,     |
   |                         || filename                                     |
   +-------------------------+-----------------------------------------------+
   | poke                    || address64, size_in_bytes, value              |
   +-------------------------+-----------------------------------------------+
   | read                    || same as program                              |
   +-------------------------+-----------------------------------------------+
   | peek                    || address64, size_in_bytes                     |
   +-------------------------+-----------------------------------------------+
   | patch                   || byte_offset, physical_partition_number,      |
   |                         || size_in_bytes, start_sector, filename,       |
   |                         || SECTOR_SIZE_IN_BYTES, value                  |
   +-------------------------+-----------------------------------------------+
   | erase                   || StorageDrive                                 |
   +-------------------------+-----------------------------------------------+
   | power                   || reset_to_edl, reset, off, Delayinseconds     |
   +-------------------------+-----------------------------------------------+
   | fixgpt                  || grow_last_partition                          |
   +-------------------------+-----------------------------------------------+
   | ufs                     || bNumberLU, bBootEnable, bDescrAccessEn,      |
   |                         || bInitPowerMode, bHighPriorityLUN,            |
   |                         || bSecureRemovalType, bInitActiveICCLevel,     |
   |                         || wPeriodicRTCUpdate, LUNum, bLUEnable,        |
   |                         || bBootLunID, bLUWriteProtect, bMemoryType,    |
   |                         || size_in_KB, bDataReliability,                |
   |                         || bLogicalBlockSize, bProvisioningType,        |
   |                         || wContextCapabilities, desc, commit           |
   +-------------------------+-----------------------------------------------+
   | benchmark               || trials, TestWritePerformance,                |
   |                         || TestReadPerformance, TestDigestPerformance   |
   +-------------------------+-----------------------------------------------+
   | getsha256digest         || same as program                              |
   +-------------------------+-----------------------------------------------+
   | setbootablestoragedrive || value                                        |
   +-------------------------+-----------------------------------------------+
   | getstorageinfo          || physical_partition_number                    |
   +-------------------------+-----------------------------------------------+
   | response                || value, rawmode                               |
   +-------------------------+-----------------------------------------------+
   | log                     || value, num_partition_sectors,serial_num      |
   |                         || SECTOR_SIZE_IN_BYTES, num_physical_partitions|
   +-------------------------+-----------------------------------------------+
   | somcauth                || size_in_bytes                                |
   +-------------------------+-----------------------------------------------+

The various currently defined common attributes/parameters are:

.. code-block:: none

  SkipWrite           Causes the target to skip writing the data to disk.
                      This is used for benchmarking performance.

  SkipStorageInit     This will skip calling UFSInit or EMMCInit. This must be
                      defined for UFS devices before they have been provisioned
                      otherwise initialization will fail. Default is “1”
                      so that storage will be initialized if not provided.

  MemoryName          This can be “ufs” or “emmc” depending on the type of device
                      you are expecting on the device. If not provided it will
                      default to “emmc”.

  AckRawDataEveryNumPackets
                      Causes the target to send an ACK after every “Num” of
                      RAW DATA packets have been sent. For example,
                      an ACK <response> will be sent every 400 RAW Data packets
                      if AckRawDataEveryNumPackets=“400.” This can be used to
                      throttle the host or get periodic feedback on very large
                      file transfers.

  AlwaysValidate      Causes the validation operation to occur on every packet
                      (note that VIP is not enabled by this). This is used to see
                      the impact of validation (hashing) without needing to enable
                      secure boot.

  Verbose             Causes the target to send many more logs to the host.

  Version             Returns firehose protocol version from device to host.

  TargetName          Returns the target that the device programmer was
                      compiled for to the host.

  BuildId             Returns the build ID of the device programmer to the host.

  DateTime            Returns the date and time from device programmer to the host.

  MaxXMLSizeInBytes   The maximum payload size for any given XML command.

  MinVersionSupported Returns the minimum version of firehose protocol supported
                      by device programmer to the host.

  MaxPayloadSizeFromTargetInBytes
                      This parameter is only present in configure response from
                      the target. It represents the maximum RAW DATA payload size
                      that the target will send back to the host.

  MaxDigestTableSizeInBytes
                      Used with VIP; indicates maximum size of the Digest Table,
                      i.e., 8KB.

  MaxPayloadSizeToTargetInBytes
                      Maximum RAW DATA payload size, i.e., 128KB. Note that this
                      value needs to be a multiple of 512. It is highly recommended
                      this value is not smaller than SECTOR_SIZE_IN_BYTES.

  ZLPAwareHost        Host can send this to device programmer to indicate if
                      the host expects a zero length packet to terminate transfers.
                      For Windows hosts this is set to “1” and for Linux hosts to “0”.
                      Default is “1” for Windows host.

  filename            The file to be programmed to the target or saved on the host.

  SECTOR_SIZE_IN_BYTES
                      The size of the sector in bytes. For example 512 for eMMC
                      devices and 4096 for UFS devices.

  num_partition_sectors
                      Number of sectors to be programmed or read.

  physical_partition_number
                      Specifies the partition in eMMC or LUN in UFS.

  start_sector        The beginning of the sector to be read or programmed.

  address64           The address location where you want to poke/write bytes to or
                      peak/read number of bytes from directly.

  size_in_bytes       The size in bytes you want to poke/peak/patch. It also
                      indicates the size of bytes to be sent when authenticating
                      using somcauth.

  value               Any value the command sets or refers to. For example,
                      value for setbootablestoragedrive means setting the active
                      partition or lun and for log means the human readable
                      message to be sent.

  StorageDrive        Specifies the partition or LUN to be erased.

  byte_offset         The offset in bytes from the start_sector where the patch
                      is going to be applied.

  reset_to_edl        Reset to emergency download mode.

  reset               Reset and try booting normally.

  off                 Power off and do not turn back on.

  Delayinseconds      The number of seconds to delay before executing power command,
                      usually used for powering off device since USB cable
                      needs to be removed first.

  trials              The number of times the test is iterated for benchmarking
                      purposes.

  TestReadPerformance Specifies the performance test to be for reading from the device.

  TestWritePerformance
                      Specifies the performance test to be for writing on the device.

  TestDigestPerformance
                      Specifies the performance test to be for hashing on the device.

  bNumberLU           Number of Logical Units.
                      bNumberLU does not include well known logical units.

  bBootEnable         Indicates whether the device is enabled for boot.
                      00h: Boot feature disabled.
                      01h: Bootable feature enabled.

  bDescrAccessEn      Indicates whether the Device Descriptor can be read after
                      the partial initialization phase of the boot sequence.
                      00h: Device Descriptor access disabled.
                      01h: Device Descriptor access enabled.

  bInitPowerMode      The bInitPowerMode parameter in the Device Descriptor defines
                      the power mode to which the device shall transition to after
                      completing the initialization phase.
                      (fDeviceInit cleared to zero)

  bHighPriorityLUN    bHighPriorityLUN defines the high priority logical unit.

  bSecureRemovalType  Secure Removal Type.
                      00h: Information removed by an erase of the physical memory.
                      01h: Information removed by overwriting the addressed locations
                      with a single character followed by an erase.
                      02h: Information removed by overwriting the addressed locations
                      with a character, its complement, then a random character.
                      03h: Information removed using a vendor define mechanism.
                      Others: Reserved.

  bInitActiveICCLevel bInitActiveICCLevel defines the bActiveICCLevel value after
                      power on or reset. Valid range from 00h to 0Fh.

  wPeriodicRTCUpdate  Frequency and method of Real-time Clock update.

  LUNum               The logical unit number that the parameters apply to.

  bLUEnable           Logical Unit Enable.
                      00h: Logical Unit disabled.
                      01h: Logical Unit enabled.

  bBootLunID          Boot LUN ID.
                      00h: Not bootable.
                      01h: Boot LU A.
                      02h: boot LU B.

  bLUWriteProtect     Logical Unit Write Protect.
                      00h: LU not write protected.
                      01h: LU write protected when fPowerOnWPEn = 1.
                      02h: LU permanently write protected when fPermanentWPEn = 1.
                      03h: Reserved (for UFS Security Extension specification).

  bMemoryType         bMemoryType defines logical unit memory type.
                      00h: Normal Memory.
                      01h: System code memory type.
                      02h: Non-Persistent memory type.
                      03h: Enhanced memory type 1.
                      04h: Enhanced memory type 2.
                      05h: Enhanced memory type 3.
                      06h: Enhanced memory type 4.

  size_in_KB          The size of this LUN in KB.

  bDataReliability    bDataReliability defines the device behavior when a power
                      failure occurs during a write operation to the logical unit.
                      00h: The logical unit is not protected. Logical unit's
                      entire data might be lost as a result of a power failure
                      during a write operation.
                      01h: Logical unit is protected. Logical unit's data is
                      protected against power failure.

  bLogicalBlockSize   The size of addressable logical blocks is equal to
                      the result of exponentiation with as base the number two
                      and as exponent thebLogicalBlockSize value: 2bLogicalBlockSize.
                      (i.e., bLogicalBlockSize = 0Ch corresponds to 4 KByte
                      Logical Block Size). Its minimum value is 0Ch, which
                      corresponds to 4KByte.

  bProvisioningType   Provisioning Type.
                      00h:Thin Provisioning is disabled (default).
                      02h:Thin Provisioning is enabled and TPRZ = 0.
                      03h:Thin Provisioning is enabled and TPRZ = 1.

  wContextCapabilities
                      Bits [3:0]: MaxContextID is the maximum amount of contexts
                      that the LU supports simultaneously. The sum of all
                      MaXContextID must not exceed bMaxContexIDNumber.
                      Bits [6:4]: LARGE_UNIT_MAX_MULTIPLIER_M1 is the highest
                      multiplier that can be configured for Large Unit contexts,
                      minus one. Large Unit contexts may be configured to have
                      a multiplier in the range: 1 <= multiplier
                      <= (LARGE_UNIT_MAX_MULTIPLIER_M1 + 1). This field is read only.

  desc                Description of the purpose of this LUN.

  commit              When set to “1” will commit all previous efs LUN settings;
                      setting to “0” will just test the parameters but not do
                      the provisioning.
