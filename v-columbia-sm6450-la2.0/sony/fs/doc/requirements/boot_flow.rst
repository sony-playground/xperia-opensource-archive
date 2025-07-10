=========
Boot Flow
=========

Introduction
============

The boot flow is determined by two major reasons: startup reason and
warmboot restart reason.

Startup reasons and warmboot reasons
====================================

The following startup reasons could be detected:

+---------------------------------------+--------------------------------------+
| Generic code                          |        Purpose                       |
+=======================================+======================================+
| XBPAL_STARTUP_MASK_ONKEY              |  Power key pressed                   |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_WATCHDOG           |  Watchdog expired                    |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_VBUS               |  USB inserted                        |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_SMPL               |  SMPL, Sudden momentarily power loss |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_RTC                |  Real time clock alarm               |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_WALLCHARGER        |  Charger attached                    |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_HARD_RESET         |  Hard reset                          |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_POWERLOCK          |  Power lock (QC)                     |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_WATCHDOG_BYPASS_PWK| Startup by wdt (MTK)                 |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_TOOL_BYPASS_PWK    | Startup by tool (MTK)                |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_PLF_WATCHDOG_1     | Platform specific watchdog 1         |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_PLF_WATCHDOG_2     | Platform specific watchdog 2         |
+---------------------------------------+--------------------------------------+
| XBPAL_STARTUP_MASK_PLF_WATCHDOG_3     | Platform specific watchdog 3         |
+---------------------------------------+--------------------------------------+

Warmboot restart reason SHOULD be written by the kernel before a reboot occurs.
The boot will read the value by using platform function plf_get_wb_reason. The
value returned is platform specific and therefore translated to a generic
value.

The following warmboot reasons SHALL be handled:

+------------------------------+-------------------------------------------+
| Generic code                 |        Purpose                            |
+==============================+===========================================+
| XBPAL_WB_CLEAR               | Cleared reason (uncontrolled restart)     |
+------------------------------+-------------------------------------------+
| XBPAL_WB_NONE                | Indicate cold boot                        |
+------------------------------+-------------------------------------------+
| XBPAL_WB_XBPAL_SVC           | Sony service (XFL)                        |
+------------------------------+-------------------------------------------+
| XBPAL_WB_FB_SVC              | Fastboot service                          |
+------------------------------+-------------------------------------------+
| XBPAL_WB_FOTA                | FOTA boot                                 |
+------------------------------+-------------------------------------------+
| XBPAL_WB_FOTA_CACHE          | FOTA PIN cache boot, used during override |
+------------------------------+-------------------------------------------+
| XBPAL_WB_NORMAL              | Normal boot                               |
+------------------------------+-------------------------------------------+
| XBPAL_WB_CRASH               | System crash                              |
+------------------------------+-------------------------------------------+
| XBPAL_WB_CRASH_ND            | System crash without dumper               |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RECOVERY            | Recovery service                          |
+------------------------------+-------------------------------------------+
| XBPAL_WB_OTHER               | Unknown warmbot reason                    |
+------------------------------+-------------------------------------------+
| XBPAL_WB_SYSTEM              | Service mode override reason              |
+------------------------------+-------------------------------------------+
| XBPAL_WB_FOTA_CRASH          | Crash during FOTA update                  |
+------------------------------+-------------------------------------------+
| XBPAL_WB_DMV_EIO             | Verified boot EIO mode                    |
+------------------------------+-------------------------------------------+
| XBPAL_WB_DMV_ENFORCE         | Verified boot Enforce mode                |
+------------------------------+-------------------------------------------+
| XBPAL_WB_DMV_KEYCLEAR        | Verified boot EIO mode                    |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_OK               | Ramdumper successfully done               |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_DECFAIL_NO_TL    | Ramdumper decryption failure 1            |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_DECFAIL_PART_TL  | Ramdumper decryption failure 2            |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_CRASH_EARLY_HWWD | Ramdumper too early HWWD                  |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_CRASH_LATE_HWWD  | Ramdumper HWWD                            |
+------------------------------+-------------------------------------------+
| XBPAL_WB_RD_NO_SPACE         | Ramdumper NO free space to store tlcore   |
+------------------------------+-------------------------------------------+
| XBPAL_WB_REBOOT_RD_CRASH     | Ramdumper kernel panic                    |
+------------------------------+-------------------------------------------+
| XBPAL_WB_REBOOT_RD_APPERR    | Ramdumper application failure             |
+------------------------------+-------------------------------------------+
| XBPAL_WB_FOTA_HWWD           | HWWD during FOTA update                   |
+------------------------------+-------------------------------------------+


Boot Configuration
------------------

In the boot configuration it is possible to set how reset and service is
triggered.
These conditions are named *RESET_TRIGGERED* and *SERVICE_TRIGGERED*.


Boot Modes
----------

The following boot modes are defined:

+-------------------------+-----------------------------------+
| Generic code            | Purpose                           |
+=========================+===================================+
| BOOT_DEFAULT_MODE       | Normal image (usually a kernel)   |
+-------------------------+-----------------------------------+
| BOOT_SONY_SERVICE_MODE  | Sony service (XFL)                |
+-------------------------+-----------------------------------+
| BOOT_FASTBOOT_MODE      | Fastboot service                  |
+-------------------------+-----------------------------------+
| BOOT_RECOVERY_MODE      | Recovery service                  |
+-------------------------+-----------------------------------+
| BOOT_DUMPER_MODE        | Ramdumper                         |
+-------------------------+-----------------------------------+
| BOOT_FOTA_MODE          | FOTA                              |
+-------------------------+-----------------------------------+


Service Modes
-------------

The following service modes are defined:

+----------------------------------+-------------------------------+
| Generic code                     | Purpose                       |
+==================================+===============================+
| SERVICE_MODE_DETECT_NONE         | No service mode requested     |
+----------------------------------+-------------------------------+
| SERVICE_MODE_DETECT_USB_SONY     | Sony service mode via USB     |
+----------------------------------+-------------------------------+
| SERVICE_MODE_DETECT_USB_FASTBOOT | Fastboot service mode         |
+----------------------------------+-------------------------------+
| SERVICE_MODE_DETECT_RECOVERY     | Recovery service mode         |
+----------------------------------+-------------------------------+


Startup Logic
-------------

#. If an error occurs during initialization we SHALL enter BOOT_SONY_SERVICE_MODE.

#. If warmboot reason is XBPAL_WB_NONE and there is no hardware reason to
   startup, we SHALL shutdown.

#. If warmboot reason is XBPAL_WB_NONE and startup reason is STARTUP_MASK_RTC,
   we SHALL shutdown.

#. Check if RESET_TRIGGERED.

   #. If RESET_TRIGGERED long enough (according to configuration) we SHALL shutdown.

   #. If RESET_TRIGGERED not long enough (according to configuration) or an
      error occurs we SHALL ignore the reset trigger.

   #. If the key press timeout is set to zero, we SHALL enter
      BOOT_RECOVERY_MODE, unless warmboot reason is XBPAL_WB_SYSTEM (see below)

#. Check if SERVICE_TRIGGERED.

   #. If warmboot reason is XBPAL_WB_SYSTEM, any service trigger SHALL be
      ignored.

   #. Check if BOOT_SONY_SERVICE_MODE (according to configuration) is
      requested and USB inserted.

   #. Check if BOOT_RECOVERY_MODE (according to configuration) is
      requested.

   #. Check if BOOT_FASTBOOT_MODE (according to configuration) is
      requested and USB inserted.

   #. Check if TA unit Factory Mode (2002) is set to 1 and enter
      BOOT_SONY_SERVICE_MODE if USB is inserted.

#. Check if restart and warmboot reason should be overridden. (**Yoshino** only)

   #. If warmboot reason is XBPAL_WB_FOTA_CRASH or XBPAL_WB_FOTA_HWWD we SHALL
      not override restart and warmboot reason.

   #. Check TA unit Boot Param Override (2301). If there is valid data for
      startup and warmboot reason, we SHALL store new values according to the
      TA configuration.

   #. If we boot into XBPAL_WB_FOTA then we SHALL set WB override to make it
      permanent by writing it into TA unit 2301.
      This way FOTA will continue until explicitly doing a normal reboot.

   #. If we are in FOTA flow and have a normal warmboot FOTA is finished,
      we SHALL the remove WB override and continue normal boot.

   #. Obtain raw override data and commit to MiscTA unit 2301.

#. Set boot mode, i.e. image to boot.

   #. If no service mode is requested, set boot mode according to warmboot
      reason.

      NOTE: Due to Sony specific handling of Master Reset we treat recovery
      warmboot reason as normal warmboot.

      #. For warmboot reason XBPAL_WB_FOTA_CRASH, XBPAL_WB_CRASH and
         XBPAL_WB_CLEAR, we SHALL set boot mode to BOOT_DUMPER_MODE.

      #. For warmboot reason XBPAL_WB_FOTA, we SHALL set boot mode to
         BOOT_FOTA_MODE.

      #. For warmboot reason XBPAL_WB_SONY_SVC, we SHALL set boot mode to
         BOOT_SONY_SERVICE_MODE if USB is inserted.

      #. For warmboot reason XBPAL_WB_FB_SVC, we SHALL set boot mode to
         BOOT_FASTBOOT_MODE if USB is inserted.

      #. For warmboot reason XBPAL_WB_RECOVERY, we SHALL set boot mode to
         BOOT_RECOVERY_MODE. Also see note in 7.1

      #. For all other known warmboot reasons, we SHALL set boot mode to
         BOOT_DEFAULT_MODE.

      #. For unknown warmboot reasons, we SHALL set boot mode to
         BOOT_DUMPER_MODE, if the startup flags STARTUP_MASK_WATCHDOG or
         STARTUP_MASK_PLF_WATCHDOG_x is set.

   #. If recovery service is requested, we SHALL set boot mode to
      BOOT_RECOVERY_MODE.

#. Do a startup indication according to the boot configuration.

#. Add command line additions.

#. Obtain backlight configuration.

#. Enable LED for Sony service, Fastboot or VBUS insertion.

   #. For BOOT_SONY_SERVICE_MODE, we SHALL turn on green LED.

   #. For BOOT_FASTBOOT_MODE, we SHALL turn on blue LED.

   #. If USB is inserted, we SHALL turn on red LED.
