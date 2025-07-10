========
Firehose
========

Introduction
============

This document describes the requirements on the SOMC adaptation of the Firehose loader.

Stakeholders
------------

FCS (Flash core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sonymobile.com>

FSV, Flash Security Verification Anil Gadiraju <anil.gadiraju@sonymobile.com>

GCIS, Global Common Indus Solution Yuying Chen <Yuying.Chen@sonymobile.com>


Platforms
---------

* Yoshino
* Tama
* Nile
* Kumano

Terminology
-----------

#. VIP
   Qualcomm Firehose Validated Image Programming

References
----------

#. Firehose Protocol (QCT doc nr 80-NG319-1)

Requirements
============

#. SOMC variant of the Firehose loader SHALL add SAKE authentication

   **Background:** The reason for this is to avoid supporting VIP image
   generation and signing in the factory flow, which would otherwise be
   necessary as we write device unique signed data.

#. Qualcomm VIP check SHALL be disabled for the SOMC variants of the loader.

   **Background:** See previous requirement.

#. The Firehose loader build SHALL produce 3 different executables:

   #. Pure QCT variant.

   #. SOMC variant using Test certificate for SAKE authentication.

   #. SOMC variant using Live certificate for SAKE authentication.

#. There SHALL be a SOMC version number added to the Firehose executable.

   #. The SOMC version number SHALL be used in the SAKE hello message.

   #. The SOMC version number SHALL be output in a USB info message at startup
      in both SOMC and QCT versions of the Firehose loader.

   #. There SHALL also be the Qualcomm base version sent in a USB info message.

   #. The SOMC adapted and vanilla QCT loaders SHALL be possible to distinguish
      via these USB info messages.

   Example output:

     **SOMC variant:**

   ``Loader version: TAMA_099-SOMC``

   ``Loader version: QC_IMAGE_VERSION_STRING=BOOT.XF.2.0-00288-SDM845LZB-1``


     **QCT variant:**

   ``Loader version: TAMA_099``

   ``Loader version: QC_IMAGE_VERSION_STRING=BOOT.XF.2.0-00288-SDM845LZB-1``

#. There SHALL be a SAKE public key hash identifier sent in a USB info message
   at startup in SOMC variant using Test or Live certificate for SAKE authentication.

   **Background:** The reason for this is to support FG4 on deciding how to handle
   authentication, either locally using signatory or remotely on SECS server.

   Example output:

   ``Sake public key hash identifier: d686``

#. A command is the sequence of packets starting with the PC sending a command
   and ending with the final ACK or NAK. The Firehose loader MUST NOT, except
   for initial packets during startup, output any USB packets outside of
   commands.

#. The following commands SHOULD be supported by the SOMC variants of the loader
   , with the exceptions stated below.

   +-------------------------+----------------------------+-------------------------+
   | Command                 | Platforms                  | Authentication required |
   +=========================+============================+=========================+
   | configure               | All                        | No                      |
   +-------------------------+----------------------------+-------------------------+
   | program                 | All                        | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | read                    | All                        | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | getstorageinfo          | All                        | No                      |
   +-------------------------+----------------------------+-------------------------+
   | getsha256digest         | Nile, Kumano               | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | erase                   | All                        | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | fixgpt                  | Tama, Kumano               | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | setbootablestoragedrive | All                        | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | power                   | All                        | No                      |
   +-------------------------+----------------------------+-------------------------+
   | ufs                     | Yoshino, Tama, Kumano      | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | emmc                    | Nile                       | Yes                     |
   +-------------------------+----------------------------+-------------------------+
   | somcauth                | All                        | No                      |
   | (*SAKE authentication*) |                            |                         |
   +-------------------------+----------------------------+-------------------------+

#. If the getsha256digest commands is present in the loader it SHOULD have a
   performance of minimum 100 MB/s.

Loadrun
=======

Loadrun is a Firehose variant used for memory testing. It is used in RCA
(Root Cause Analysis) activities.

Loadrun differs from Firehose by adding one authenticated operation
(somcrawrequest), and possibly removing other operations due to memory
constraints.

Requirements
------------

#. In addition to the Firehose requirements the following minimal set of supported
   operations for Loadrun SHALL be supported:

   +-------------------------+-------------------------+
   | Command                 | Authentication required |
   +=========================+=========================+
   | configure               | No                      |
   +-------------------------+-------------------------+
   | getstorageinfo          | No                      |
   +-------------------------+-------------------------+
   | power                   | No                      |
   +-------------------------+-------------------------+
   | somcauth                | No                      |
   | (*SAKE authentication*) |                         |
   +-------------------------+-------------------------+
   | somcrawrequest          | Yes                     |
   +-------------------------+-------------------------+
