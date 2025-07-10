=====================
Authenticated channel
=====================

Introduction
============

Authenticated channel is a feature to enable the UEFI boot code to perform a
SAKE authentication. The boot relies on the XFL for security server
communication and the flow requires a reboot to complete.

Design
======

The sequence of the authenticated channel used for resetting the anti rollback
(ARB) counters is described below. RPMB is used by the boot to store the nonce
which is vital for replay protection. The TA unit 2334 and xflattest are used to
store non security sensitive data between boot and XFL.

All commands are appended after each other in the TA. Layout of the TA unit
2334:

+-----------------------------------------+
|Command 1 header (16 bytes)              |
+-----------------------------------------+
|Command buffer (size defined by header)  |
+-----------------------------------------+
|Command 2 header (16 bytes)              |
+-----------------------------------------+
|Command buffer (size defined by header)  |
+-----------------------------------------+
|...                                      |
+-----------------------------------------+
|Command N header (16 bytes)              |
+-----------------------------------------+
|Command buffer (size defined by header)  |
+-----------------------------------------+

Command header definition:

+-----------------------------------------+
|Magic "0x11770112" (4 bytes)             |
+-----------------------------------------+
|Version (4 bytes)                        |
+-----------------------------------------+
|Command id (4 bytes)                     |
+-----------------------------------------+
|Size of command buffer (4 bytes)         |
+-----------------------------------------+

Each command defines its own command buffer layout, see :ref:`supp-cmds`.

.. _authch_bootflow:

.. uml::
  :caption: Authenticate command main flow

  @startuml
  group boot (soft service)
  boot -> boot: generate nonce
  boot -> xflattest: save nonce in RPMB
  xflattest -> RPMB: save nonce
  xflattest --> boot: ok
  boot -> xflattest: save nonce in xflattest data
  boot -> xfl: start xfl
  destroy boot
  end
  group xfl
  xfl -> host: enumerate USB
  host -> xfl: command "SAKE-Authenticate:challenge"
  xfl -> xflattest: get nonce
  xfl -> host: authenticate challenge
  host -> server: authenticate challenge
  server -> host: authenticate response
  host -> xfl: command "SAKE-Authenticate:response"
  xfl -> xfl: verify SAKE response
  xfl -> TA: store command 0 with response in TA 2334
  xfl -> host: send authenticate result
  host -> xfl: command "Reset-rollback-counter"
  xfl -> TA: store reset cmd in TA unit 2334
  xfl -> boot: **REBOOT**
  destroy xfl
  end
  group boot
  boot -> TA: read commands from TA unit 2334
  boot -> xflattest: read nonce from RPMB
  xflattest -> RPMB: read nonce
  xflattest --> boot: ok
  boot -> boot: verify SAKE response
  boot -> boot: reset VB ARB counters
  end
  @enduml

Below is the state chart of the boot parts.

.. _authch-check_cmd:

.. uml::
  :caption: Execute authenticated commands
  :align: center

  start
  :**authenticate level** = NONE;
  :**quit** = FALSE;
  while (**quit**) is (FALSE)
    :read next command;
    note left: command stored in TA unit 2334
    if (command available) then (yes)
      if (is authentication command) then (yes)
        :verify SAKE response;
        note left
          read SAKE response from TA
          read rev string from TA
          read nonce stored in rpmb
        end note
        if (is valid) then (yes)
          :set **authenticate level**;
          note left
            Auth level set to the
            level in the response
          end note
        else (no)
          :**quit** = TRUE;
        endif
      else (no)
        if (**authenticate level** ok) then (FALSE)
          :**quit** = TRUE;
        else (TRUE)
          :execute command;
        endif
      endif
    else (no)
      :**quit** = TRUE;
    endif
  endwhile (TRUE)
  if (boot in service mode) then (yes)
    :generate nonce;
    note left: Random number is generated from EFI_QCOM_RNG_PROTOCOL in UEFI
  else (no)
  endif
  :lock RPMB for writing;
  note left: Lock xflattest RPMB write interface using softfuse
  if (boot in service mode) then (yes)
    :update xfl data with generated nonce;
  endif
  :continue boot;
  stop

.. _supp-cmds:

Supported commands
==================

Authenticate
------------

**Command id: 0**

Some commands require authentication to be run before execution. The
authentication command buffer layout is defined below:

+-----------------------------------------+
|SSN (authentication level) (4 bytes)     |
+-----------------------------------------+
|Revision id size (4 bytes)               |
+-----------------------------------------+
|Response size (4 bytes)                  |
+-----------------------------------------+
|Revision id ("Revision id size" bytes)   |
+-----------------------------------------+
|SAKE response ("Response size" bytes)    |
+-----------------------------------------+

Reset VB meta Anti Rollback counters
------------------------------------

**Command id: 1**

Updating the VBMeta anti rollback counters must be done prior booting the OS. QC
provides UEFI interface to reset the VBMeta ARB counters in a simple way. To
protect this function authentication is required.

This command has no command buffer.

Oem lock
---------------

**Command id: 2**

Executing this command locks the bootloader. Erasing of user sensitive data,
setting the TA_MASTER_RESET flag and writing recovery message to the misc
partition must be done prior to locking the bootloader. To protect this function
authentication is required.

This command has no command buffer.
