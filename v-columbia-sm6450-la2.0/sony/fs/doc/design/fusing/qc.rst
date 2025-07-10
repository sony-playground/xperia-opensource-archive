===
QC
===

Fusing
======

The fusing logic of a QC device makes use of the QSEE fuse interface. The QSEE
application tzapp_loader is used by the XFL to access the QSEE fuse interface.
The communication with the tzapp_loader is using a Request command buffer
defined below.

Request command
+++++++++++++++

+-----------------------------------------+
|Magic "0x66553545" (4 bytes)             |
+-----------------------------------------+
|Version (4 bytes)                        |
+-----------------------------------------+
|Command ID (4 bytes)                     |
+-----------------------------------------+
|Length (4 bytes)                         |
+-----------------------------------------+
|RW buffer(s) (size defined by Length)    |
+-----------------------------------------+

The magic is a hard coded value and version is 0. There is two commands
supported, read and write fuse data. Length in Request command buffer is
defined in bytes. The request command contains one or more RW (read/write)
buffers. The RW buffers have a length of 12 bytes each.

RW buffer
+++++++++

+-----------------------------------------+
|Flag (4 bytes)                           |
+-----------------------------------------+
|Address (4 bytes)                        |
+-----------------------------------------+
|Data (4 bytes)                           |
+-----------------------------------------+

The usage of the structure varies depending on the command.

Supported commands
------------------

Read Fuse
+++++++++

**Command id: 0x00000000**

This command will read fuse data and return the value to normal world. Only one
RW buffer is supported when using the Read Fuse command.

  * Flag, **not used**
  * Address, the fuse data address to be read
  * Data, **not used**

Write fuse
++++++++++

**Command id: 0x01000000**

This command will write fuse data. Multiple RW buffers are supported.

  * Flag, flags explained below
  * Address, the fuse data address to be written
  * Data, the data to be written

Flag translates to the security property file.

+------+----------+--------------------+
| Flag | Sec Prop | Description        |
+------+----------+--------------------+
| 1    | 0x80     | Data + FEC         |
+------+----------+--------------------+
| 2    | 0x8D     | Data no FEC        |
+------+----------+--------------------+
| 3    | 0x88     | Random data + FEC  |
+------+----------+--------------------+
| 4    | 0x90     | Random data no FEC |
+------+----------+--------------------+

SW fuse as safety measure
==========================

The tzapp_loader is protected from non XFL usage (e.g. Android) by the usage of
SW fuse QSEE_SONYTZAPPXFL_LOADED_FUSE. If the fuse is blown the tzapp_loader
will refuse to execute commands. The boot is responsible for blowing the
QSEE_SONYTZAPPXFL_LOADED_FUSE in all non XFL boot scenarios.

External modem fusing
=====================

The XFL supports external modem fusing. The configuration is sent through the
security properties file just as the normal fuse flow. The actual fusing is done
by executing a shell script that starts the requested boot binary on the
external modem which handles the actual fusing. The XFL responsibility in this
flow is only to select and execute the correct fusing binary. The actual fusing
is completely handled by the external modem itself.

External modem fuse log
=======================

In the case of an external modem (e.g. Kumano+, edo), when fusing the modem,
the fuse configuration will be stored in TA unit 2151 for Edo and newer,
while for Kumano+ it was stored in miscTA 2150.
The configuration consists of one byte and it is defined as:

+----+------+
| 00 | oem0 |
+----+------+
| 01 | pcm  |
+----+------+
| 02 | com  |
+----+------+
