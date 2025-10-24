.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Readme file for debugging stack frame from dump and generating call stack.
   
     Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
   
                                 EDIT HISTORY

    when       who     what, where, why
    --------   ---     -----------------------------------------------------------
    07/03/22   bxr      Initial version
   ==============================================================================*/


.. _DebuggingStackTrace:

=====================
  DebuggingStackTrace
=====================

Introduction
------------

For developers who are working with source code, we use T32 to do online debug or crash dump analysis.
The purpose of the generate_callstack.py script is to easily reconstruct call stack from uart log without T32.


Required Tools and Setup
------------------------

For all::

  python : 3.8.2  (required in search path, use "python -V" to verify)



Command and options
-------------------

Usage:: 

  python QcomPkg/Tools/Uefi/python/generate_callstack.py -p <uart_log_path>

Arguments::

    -p, --uart-log-path
    The uart log path.


Output format::

  - <stack frame address><driver>::<function> + <offset>
  - <stack frame address><driver> + <offset> (for packed out driver)

Example::

  python QcomPkg/Tools/Uefi/python/generate_callstack.py -p ./boot_images/uefi_log.txt


Dependencies
------------

1. Prefer option: driver *.map file 

2. Alternative option: driver *.dll file (need readelf and nm tool to do binary disassembling)
   
   To use readelf and nm tool, firstly set environment by command line::

     On Windows:
       set nmtool=<nmtool path>
       set readelf=<nmtool path>
       Ex:
           set nmtool=C:\Apps\LLVM\14.0.0\tools\bin\arm-nm
           set readelf=C:\Apps\LLVM\14.0.0\tools\bin\arm-readelf

     On Linux:
       export nmtool=<nmtool path>
       export readelf=<nmtool path>
       Ex:
          export nmtool=/pkg/qct/software/arm/linaro-toolchain/aarch64-none-elf/4.9-2014.07/bin/aarch64-none-elf-nm
          export readelf= /pkg/qct/software/llvm/release/arm/14.0.0/tools/bin/arm-readelf 



Limitations
-----------

1. Uart log with “UEFI Start” and only check the last instance of “UEFI Start”.

2. Not support release build.

3. Inline functions, some qc drivers released only as binary will not show function name.

4. Functions that do not backup and restore the SP and FP.
