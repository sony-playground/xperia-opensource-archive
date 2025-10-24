========
Overview
========

.. uml::
   :align: center

   package ABL {
      class "LinuxLoader\n(abl/tianocore/edk2)" as LinuxLoader {
         LinuxLoaderEntry
         XBootLinux
      }

      class "FastbootLib\n(abl/tianocore/edk2)" as FastbootLib{
         FastbootUsbDeviceStart
         FastbootCommandSetup
         BuildDefaultDescriptors
      }

      LinuxLoader -[hidden] FastbootLib

      class "XBootLib\n(platform/vendor/semc/s1/s1integration)" as XBootLib {
         <XBoot.h>
         XBootInitLoader
         XBootFinalizeLongpress
         XBootMakeDecisions
         XBootGetBootMode
         XBootGetCommandLine
         XBootIsBacklightEnable
         XBootResetSignerCert
         XBootSetNextSignerCert
         XBootPublishAttestation
         XBootPublishAttestationXfl
         XBootIsKeystoreXcsROT
         XBootAVBPubKeyCheck

         <XFastbootCmds.h>
         XFastbootCmdsInit
         XSetSonyStrings
         XGetProduct
         XGetSerialno
      }

      class "XBootGlueLib\n(vendor/semc/fs/main)" as XBootGlueLib {
         <xboot_glue.h>
         xboot_init
         xboot_get_ks_counter
         xboot_get_ks_is_xcs_rot
         xboot_get_sec_stor_xcs_rot
         xboot_get_die_id
         xboot_get_simlock_unlock_data
         xboot_compare_rck
         xboot_google_allow_unlock
         xboot_delete_dk
         xboot_get_pub_key_count
         xboot_get_signer_cert_count
         xboot_get_pub_key
         xboot_get_signer_cert
         xboot_check_auto_set_oem_unlock
         xboot_check_auth_cmd
         xboot_gen_auth_ch_nonce
         xboot_get_auth_ch_nonce
         xboot_get_phoneid
         xboot_get_devicekey
         xboot_is_tcb_security_on
         xboot_get_hwconf_rev
         xboot_make_decisions
         xboot_get_cmdline_additions
         xboot_is_backlight_enable
         xboot_get_boot_mode
         xboot_finalize_longpress
         xboot_get_rollback_counters
         xboot_reset_rollback_counters
         xboot_get_avb_version
      }

      class "XBootPALApiLib\n(platform/vendor/semc/s1/s1integration)" as XBootPALApiLib {
         <XBootPALApiLib.h>
         XBootPALApiInit

         <xboot_pal_types.h>
         xbpal_gpio_get_pin
         xbpal_gpio_set_config
         xbpal_get_boot_time
         xbpal_timer_register_cb
         xbpal_timer_deregister_cb
         xbpal_delay_us
         xbpal_get_startup_bits
         xbpal_get_wb_reason
         xbpal_translate_wb_reason
         xbpal_clear_wb_reason
         xbpal_usb_vbus_detect
         xbpal_usb_otg_detect
         xbpal_pwr_button_pressed
         xbpal_rst_button_pressed
         xbpal_kbd_button_pressed
         xbpal_erase_user_sensitive
         xbpal_get_frp_data_size
         xbpal_read_frp_data
         xbpal_reset_detect
         xbpal_vibrate
         xbpal_rgb_led_ctl
         xbpal_shutdown
         xbpal_get_version_string
         xbpal_unlock_bootloader
         xbpal_lock_bootloader
         xbpal_reset_vbmeta_counters
         xbpal_read_vbmeta_counters
         xbpal_get_avb_version
      }

      class "XBootPAL\n(platform/vendor/semc/s1/s1integration)" as XBootPAL {
         <XBootPAL.h>
         XGetPartitionSize
         XReadPartition
         XWritePartition
         XErasePartition
         XEraseUserSensitivePartitions
         XEraseFrpPartition
         XIsDeviceFused
         XSendAttestCmd
         XGetFRPDataSize
         XReadFRPData
         XGetRNG
      }


      XBootLib -[hidden] XBootGlueLib
      XBootGlueLib -[hidden] XBootPALApiLib

      class "XBootCryptoLib\n(vendor/semc/fs/main)" as XBootCryptoLib {
      }

      class "TaApiLib" {
         Ta_Init
         TA_OpenPartition
         TA_Close
         TA_GetUnitSize
         TA_ReadData
         TA_WriteData
         TA_DeleteUnit
      }

      class "XOemCertLib\n(platform/vendor/semc/s1/s1integration)" as XOemCertLibABL {
         XOemCertSet
      }

      class "OpensslLib\n(vendor/semc/fs/openssl)" as OpensslLib {
      }
   }

   package XBL {

      package DXE {
         class "XBootPALDxe\n(platform/vendor/semc/s1/s1integration)" as XBootPALDxe {
            XBootPALInit
            CopyHwConfToSharedMem
            GetStartupBits
            Shutdown
            Vibrate
            PowerButtonPressed
            ResetButtonPressed
            DelayUs
            RgbLedControl
            UsbVbusDetect
            GetVersionString
            TimerDeregisterCB
            TimerRegisterCB
            ResetDetect
            GpioSetConfig
            GpioGetPin
            GetBootTime
         }

         class "TaDxe\n(platform/vendor/semc/s1/s1integration)" as TaDxe {
            Ta_Init
            TA_OpenPartition
            TA_Close
            TA_GetUnitSize
            TA_ReadData
            TA_WriteData
            TA_DeleteUnit
         }

         class "VerifiedBootDxe\n(platform/boot8998)" as VerifiedBootDxe {
            VBVerifyImage
         }

         class "XOemCertDxe\n(platform/vendor/semc/s1/s1integration)" as XOemCertDxe {
            Get
            Set
         }
      }

      class "XBootPALLib\n(platform/vendor/semc/s1/s1integration)" as XBootPALLib {
         XBootPALInit
         CopyHwConfToSharedMem
         GetStartupBits
         Shutdown
         Vibrate
         PowerButtonPressed
         ResetButtonPressed
         DelayUs
         RgbLedControl
         UsbVbusDetect
         GetVersionString
         TimerDeregisterCB
         TimerRegisterCB
         ResetDetect
         GpioSetConfig
         GpioGetPin
         GetBootTime
      }

      class "TaLib\n(platform/vendor/semc/miscta)" as TaLib {
         TA_ReadBlock
         TA_WriteBlock
         TA_EraseBlock
         TA_IsBadBlock
         TA_Malloc
         TA_Free
         TA_ReadVerify
         TA_Crash
         TA_GetCodeID
      }

      class "XOemCertLib\n(platform/vendor/semc/s1/s1integration)" as XOemCertLibXBL {
         XOemCertGet
      }
   }

   LinuxLoader --> XBootLib
   FastbootLib --> XBootLib
   XBootLib --> XOemCertLibABL
   XBootLib --> XBootGlueLib
   XBootGlueLib --> TaApiLib
   XBootGlueLib -->  XBootPALApiLib
   XBootGlueLib --> XBootCryptoLib
   XBootGlueLib --> XBootPAL
   XBootCryptoLib --> OpensslLib
   XBootPALApiLib --> XBootPALDxe
   XBootPALDxe --> XBootPALLib
   TaApiLib --> TaDxe
   TaDxe --> TaLib
   VerifiedBootDxe --> XOemCertLibXBL
   XOemCertLibABL -> XOemCertDxe
   XOemCertLibXBL -> XOemCertDxe

.. raw:: latex

    \clearpage

