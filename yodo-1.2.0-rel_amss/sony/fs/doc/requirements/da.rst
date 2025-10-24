========
DA
========

Introduction
============

This document describes the requirements on the SOMC adaptation of the DA loader.

Stakeholders
------------
* FCS (Flash core Security): DL-SELD-FlashSecurity_ODM_Loader
* FAS (Flash Application Security): Magnus Strandh <Magnus1.Strandh@sonymobile.com>



Platforms
---------

* Dragon MT6762 (SM33)

Terminology
-----------

#. DA
   Download Agent

Requirements
============

#. SOMC variant of the DA loader SHALL add SAKE authentication

#. The DA loader build SHALL produce:

   * Two .zip files

   * One is MTK Vanilla DA without any modifications, the other one includes SOMC modifications.

   * There is only one .zip file with SOMC modifications that acts as both live signed and test signed image. Correct certificate is loaded in run-time depending on the content of the EFUSED_C_DAT0 register.


#. There SHALL be a SOMC version number added to the DA executable.

   #. The SOMC version number SHALL be used in the SAKE hello message.

   #. The SOMC version number SHALL be output in a USB info message at startup
      in both SOMC and MTK versions of the DA loader.

   #. The SOMC adapted and vanilla MTK loaders SHALL be possible to distinguish
      via these USB info messages.

   Example output:

     **SOMC variant:**

   ``Loader version: MT6762_HUAIHE_0007-SOMC``



     **MTK variant:**

   ``Loader version: MT6762_HUAIHE_0007``


#. There SHALL be a SAKE public key hash identifier sent in a USB info message
   at startup in SOMC variant using Test or Live certificate for SAKE authentication.

   **Background:** The reason for this is to support FG4 on deciding how to handle
   authentication, either locally using signatory or remotely on SECS server.

   Example output:

   ``SAKE_ROOT: D8D2``

#. A command is the sequence of packets starting with the PC sending a command
   and ending with the final ACK or NAK. The DA loader MUST NOT, except
   for initial packets during startup, output any USB packets outside of
   commands.

#. The following commands SHOULD be supported by the SOMC variants of the loader

   +---------------------------------+----------------------------+-------------------------+
   | Command                         | Platforms                  | Authentication required |
   +=================================+============================+=========================+
   | cmd_download                    | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_upload                      | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_write_data                  | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_read_data                   | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_format                      | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_format_partition            | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_boot_to                     | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_shutdown                    | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_switch_usb_speed            | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_init_dram                   | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_device_ctl                  | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_read_otp_zone               | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_write_otp_zone              | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_read_efuse                  | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_write_efuse                 | All                        | Yes                     |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_sram_write_test             | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_set_environment             | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_set_hw_init_parameter       | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_handle_auth                 | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_get_sake_identifier         | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_get_root_key_hash           | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_get_device_serial_number    | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | cmd_get_device_id               | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_battery_opt            | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_reset_key              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_checksum_level         | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_meta_boot_flag         | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_register_value         | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_rsc_info               | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_partition_tbl_catagory | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_version                | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_packet_length          | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_emmc_info              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_nand_info              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_nor_info               | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_ufs_info               | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_ram_info               | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_connection_agent       | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_usb_speed              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_chip_baseband          | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_random_id              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_check_rpmb_key_status      | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_dram_type              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_hrid                   | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_start_dl_info              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_end_dl_info                | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_lock_otp_zone              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_opt_post_download_act      | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_ctrl_read_register         | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_ctrl_ram_test              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_check_status_otp_zone      | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_check_battery_voltage      | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_disable_emmc_reset_pin     | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_host_info              | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_emmc_hwreset_pin       | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_expire_date            | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_external_signature     | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_get_dev_fw_info            | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_all_in_one_signature   | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
   | devc_set_remote_sec_policy      | All                        | No                      |
   +---------------------------------+----------------------------+-------------------------+
