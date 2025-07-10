Download Agent
====================================================

Terminology
-----------

#. BROM
   ROM boot mode (BootRom)
#. RAM
   Random Access Memory
#. USB
   Universal Serial Bus
#. XFL
   Xperia Flash Loader
#. OS
   Operating System
#. DA
   Download agent
#. INT_SYSRAM
   First DA binary(preloader)
#. EXT_RAM
   Second DA binary(loader)

Introduction
------------

DA is used in BROM USB Download Mode. The DA binaries are loaded into RAM over USB and can
be used for writing to device storage, recovery and initial configuration of the device, etc.

Command Reference
=================

This is the command reference to the vanilla MediaTek (MTK) Download Agent loader

.. code-block:: none

 <cmd_download>               Writes data to any existing partition to the flash
                              on the device.

 <cmd_upload>                 Reads data from any existing partition from the flash
                              on the device.

 <cmd_write_data>             Writes data on a specified address and size to the flash
                              on the device.

 <cmd_read_data>              Reads data from specified address and size on the flash
                              on the device.

 <cmd_format>                 Erases data from specified address and size from the flash
                              on the device.

 <cmd_format_partition>       Erases any existing data in a partition from the flash on the device.

 <cmd_boot_to>                INT_SYSRAM loads EXT_RAM binary and handovers execution
                              to the EXT_RAM.

 <cmd_shutdown>               Controls the power of the device.

 <cmd_switch_usb_speed>       Switches the USB speed.

 <cmd_init_dram>              Initializes the SDRAM on the device.

 <cmd_device_ctrl>            Receives "device control" command execution requests
                              over USB and invokes its corresponding definition.

 <cmd_read_otp_zone>          NOT used by SONY

 <cmd_write_otp_zone>         NOT used by SONY

 <cmd_read_efuse>             NOT used by SONY

 <cmd_write_efuse>            NOT used by SONY

 <cmd_sram_write_test>        NOT used by SONY.

 <cmd_set_environment>        Sets DA environment variables like log_level, log_channel
                              and system_os.

 <cmd_set_hw_init_parameter>  Sets DA hw init parameter like charger or project
                              related parameters.
                              Note: SONY uses this command only as requirement for
                              proper initialization of the DA loader, without modifying
                              any of the hw init parameters. Thus, host app sends 0 hw
                              init parameters towards DA.

SOMC additions to the DA protocol

.. code-block:: none

 <cmd_handle_auth>                     Used to authenticate commands that require authentication.

 <cmd_get_sake_identifier>             Reads SAKE public key hash identifier used for FG4 to
                                       decide what SAKE verification to execute.

 <cmd_get_root_key_hash>               Reads the hash of the platform root key.

 <cmd_get_device_serial_number>        Reads the device serial number of the device, which
                                       correspondence with the serial number read from MTK's BROM.

 <cmd_get_device_id>                   Reads the unique device ID from the device, which
                                       correspondence with the device id read from the XFL.
                                       Note: <cmd_get_device_serial_number> cannot be fetched
                                       from XFL due to MTK security restrictions, thus device id
                                       is used instead.

Device control commands

.. code-block:: none

  <devc_set_battery_opt>               NOT used by SONY.

  <devc_set_reset_key>                 NOT used by SONY.

  <devc_set_checksum_level>            NOT used by SONY.

  <devc_set_meta_boot_flag>            NOT used by SONY.

  <devc_set_register_value>            NOT used by SONY.

  <devc_set_rsc_info>                  NOT used by SONY.

  <devc_get_partition_tbl_catagory>    NOT used by SONY.

  <devc_get_version>                   Reads DA version.

  <devc_get_packet_length>             Reads the sizes of USB communication packets,
                                       which are different depending on OS where the
                                       host application is being used. Info about which
                                       OS is used is sent towards DA trough <cmd_set_environment>.

  <devc_get_emmc_info>                 Reads device EMMC info.

  <devc_get_nand_info>                 NOT used by SONY.

  <devc_get_nor_info>                  NOT used by SONY.

  <devc_get_ufs_info>                  NOT used by SONY.

  <devc_get_ram_info>                  Reads device DRAM info.

  <devc_get_connection_agent>          NOT used by SONY.

  <devc_get_usb_speed>                 Reads devices USB speed.

  <devc_get_chip_baseband>             Reads hardware version registers.

  <devc_get_random_id>                 NOT used by SONY.

  <devc_check_rpmb_key_status>         NOT used by SONY.

  <devc_get_dram_type>                 NOT used by SONY.

  <devc_get_hrid>                      NOT used by SONY.

  <devc_start_dl_info>                 Checks for existence of flashinfo partition and enables
                                       updating it (if exists) with metadata about the partitions
                                       that are going to be flashed.
                                       Note: Starting from MT6762, this command is not mandatory
                                       anymore for proper initialization of DA loader and flashing
                                       of the preloader image.

  <devc_end_dl_info>                   NOT used by SONY.

  <devc_lock_otp_zone>                 NOT used by SONY.

  <devc_opt_post_download_act>         NOT used by SONY.

  <devc_ctrl_read_register>            NOT used by SONY.

  <devc_ctrl_ram_test>                 NOT used by SONY.

  <devc_check_status_otp_zone>         NOT used by SONY.

  <devc_check_battery_voltage>         NOT used by SONY.

  <devc_disable_emmc_reset_pin>        NOT used by SONY.

  <devc_set_host_info>                 NOT used by SONY.

  <devc_set_emmc_hwreset_pin>          NOT used by SONY.

  <devc_get_expire_date>               NOT used by SONY.

  <devc_set_external_signature>        NOT used by SONY.

  <devc_get_dev_fw_info>               NOT used by SONY.

  <devc_set_all_in_one_signature>      NOT used by SONY.

  <devc_set_remote_sec_policy>         NOT used by SONY.

Supported DA commands which are protected by authentication
-----------------------------------------------------------

 +-------------------------+----------------------------+-------------------------+
 | Command                 | Platforms                  | Authentication required |
 +=========================+============================+=========================+
 |                         |   Vanilla MTK DA commands  |                         |
 +-------------------------+----------------------------+-------------------------+
 | download                | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | upload                  | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | write_data              | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | read_data               | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | format                  | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | format_partition        | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | boot_to                 | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | shutdown                | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | switch_usb_speed        | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | init_dram               | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | device_ctrl             | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | read_otp_zone           | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | write_otp_zone          | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | read_efuse              | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | write_efuse             | All                        | Yes                     |
 +-------------------------+----------------------------+-------------------------+
 | sram_write_test         | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | set_environment         | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | set_hw_init_parameter   | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 |                         |  SOMC additional commands  |                         |
 +-------------------------+----------------------------+-------------------------+
 | handle_auth             | All                        | No                      |
 | (*SAKE authentication*) |                            |                         |
 +-------------------------+----------------------------+-------------------------+
 | get_sake_identifier     | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | get_root_key_hash       | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | get_device_serial_number| All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 | get_device_id           | All                        | No                      |
 +-------------------------+----------------------------+-------------------------+
 |                         |  Device control commands   |                         |
 +-------------------------+----------------------------+-------------------------+
 | None of the device control commands needs authentication at this time of       |
 | writing, although the authentication is supported for these commands as well   |
 +-------------------------+----------------------------+-------------------------+

Start-up Sequence Diagram
=========================

.. uml::
  :caption: Download Agent startup flow

  @startuml
  group Download Agent (BROM USB Download Mode)
  DA <- host: Usual set of BROM commands
  DA <- host: INT_SYSRAM binary
  DA -> DA: init of INT_SYSRAM
  DA <- host: Set environment and hw init parameters
  DA --> host: Ready to execute commands
  DA <- host: Init DRAM (EMI settings)
  DA --> host: OK
  DA <- host: BOOT_TO command, send EXT_RAM binary
  DA --> host: DA verify pass and sends response
  DA -> DA: Jumps to DRAM and init EXT_RAM
  DA --> host: Ready to execute commands
  DA <- host: Switch usb speed
  DA --> host: OK
  DA <- host: Get HW information
  DA --> host: HW information
  DA <- host: Send 'handle_auth command'
  DA --> host: Send SAKE challenge
  host -> security_server: Relay SAKE challenge
  security_server -> host: Send SAKE response
  DA <- host: Relay SAKE response
  DA -> DA: Verify SAKE response
  DA --> host: OK
  DA <- host: Send commands that need authentication
  DA --> host: Response
  end
  @enduml
