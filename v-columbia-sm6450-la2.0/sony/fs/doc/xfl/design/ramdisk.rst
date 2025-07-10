*********************
XFL image composition
*********************

The XFL image is composed of a kernel with an appended device tree and a
ramdisk. The kernel is built using the standard Android build system. The
ramdisk is populated during the XFL build and by the standard Android init
binary during runtime.

XFL ramdisk
===========

The XFL ramdisk is created by the loader.mk file. The below list is the files
located in the ramdisk not created by standard Android init.

+-----------------------------+-------------------------------------+
| default.prop                | Android default properties          |
+-----------------------------+-------------------------------------+
| etc/fuse_modem.sh           | 5G fusing script                    |
+-----------------------------+-------------------------------------+
| init                        | The standard android init binary    |
+-----------------------------+-------------------------------------+
| init.rc                     | The init script                     |
+-----------------------------+-------------------------------------+
| mnt/sdcard                  | Mount point for sdcard              |
+-----------------------------+-------------------------------------+
| plat_property_contexts      | Needed by selinux                   |
+-----------------------------+-------------------------------------+
| res/images/font.png         | Font for display while flashing     |
+-----------------------------+-------------------------------------+
| root/file_contexts.bin      | Needed by selinux                   |
+-----------------------------+-------------------------------------+
| root/sepolicy               | Needed by selinux                   |
+-----------------------------+-------------------------------------+
| sbin/ueventd                | link to ../init                     |
+-----------------------------+-------------------------------------+
| sepolicy                    | Needed by selinux                   |
+-----------------------------+-------------------------------------+
| system/bin/adbd             | ADBD binary                         |
+-----------------------------+-------------------------------------+
| system/bin/linker*          | Android linker binaries             |
+-----------------------------+-------------------------------------+
| system/bin/logcat           | Android logcat binary               |
+-----------------------------+-------------------------------------+
| system/bin/logd             | Android logd binary                 |
+-----------------------------+-------------------------------------+
| system/bin/reboot           | Android reboot binary               |
+-----------------------------+-------------------------------------+
| system/bin/sh               | Android sh binary                   |
+-----------------------------+-------------------------------------+
| system/bin/toolbox          | Android toolbox binary              |
+-----------------------------+-------------------------------------+
| system/bin/toybox           | Android toybox binary               |
+-----------------------------+-------------------------------------+
| system/etc/keys             | Deprecated, not used anymore        |
+-----------------------------+-------------------------------------+
| system/etc/lib64            | Contains the needed system libs     |
+-----------------------------+-------------------------------------+
| vendor/app/mcRegistry       | MTK/ODM                             |
+-----------------------------+-------------------------------------+
| vendor/bin/ks               | QC helper binary to fuse 5G modem   |
+-----------------------------+-------------------------------------+
| vendor/bin/lilo             | XFL application (LInux LOader)      |
+-----------------------------+-------------------------------------+
| vendor/bin/loader           | Link to ./lilo binary               |
+-----------------------------+-------------------------------------+
| vendor/bin/mdm_helper       | QC helper binary to fuse 5G modem   |
+-----------------------------+-------------------------------------+
| vendor/bin/mdm_helper_proxy | QC helper binary to fuse 5G modem   |
+-----------------------------+-------------------------------------+
| vendor/bin/qcat_unbuffered  | QC helper binary to fuse 5G modem   |
+-----------------------------+-------------------------------------+
| vendor/bin/qseecomd         | QC qseecomd binary                  |
+-----------------------------+-------------------------------------+
| vendor/lib64                | Contains the needed vendor libs     |
+-----------------------------+-------------------------------------+
