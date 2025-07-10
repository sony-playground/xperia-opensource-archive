********
Overview
********

Components
==========
The test system is divided into two major components:

   * Main Tester: Responsible for starting the "Device" for every test case.
   * Device: Prepare, Run and Verify one test case.

Main Tester
-----------
Main Tester might be a program or a person that handles a collection of test cases.
For every test case it is responsible for setting up the test case state/prerequisite and
collect expected prerequisite or the result of the test case.


Device
------
Device is a program which receives the test case setup from "Main Tester" and execute
the test case on target with xmodem software.
The program is divided into the following parts:

   * Main application (Specific for Test Target Environment)
   * Framework (Common)
   * Test Cases (Common)

      * Some Test Data might be unique per target if enforced by Integration Platform.
      * Some test cases might not be executable for a Test Target Environment
   * Software Under Test - XModem (Common)

Device states
-------------
A test case is normally divided into the following states initiated from "Main Tester":

   1. Execute test case
   2. Optional post process

.. raw:: latex

    \clearpage

Modem Test on Software Target (Ubuntu)
======================================

   * Main Tester is python application which starts Device executable.
   * Device is a Linux executable console application.
   * Test Case state (TCState) is communicated to Device through command line parameters.
   * Next Test Case state (TCState) is communicated to Main Tester through stdout.

.. uml::
   :align: center

   :Main Tester: as MAINTEST << Python Application >>

   package "Device Main\nConsole Application" {
      [Param]
      [TCState - StdOut]
   }

   package "Framework" {
      frame "Interface\nMain App" {
         interface "Callback TCState" as CBTC
         interface "Create with TCState" as CRT
         interface "Execute" as EXE
      }

      frame "Interface\nModule Test" {
         interface "Set Next Operation" as SNO
         interface "Inc Executed" as IEXE
         interface "Inc FAILED" as IFLD
         interface "Export TCState" as ETC
      }

      [Iterator]

   }

   package "Test Cases" {
      [Test Case]
   }

   package "SW Under Test" {
      [XModem]
   }

   MAINTEST -> [Param]
   MAINTEST <- [TCState - StdOut]

   [Param] -> CRT
   [Param] -> EXE

   [TCState - StdOut] <- CBTC

   CBTC <- [Iterator]
   CRT -> [Iterator]
   EXE -> [Iterator]

   SNO -> [Iterator]
   IEXE -> [Iterator]
   IFLD -> [Iterator]
   ETC -> [Iterator]

   [Iterator] -> [Test Case]
   SNO <- [Test Case]
   IEXE <- [Test Case]
   IFLD <- [Test Case]
   ETC <- [Test Case]

   [Test Case] -> [XModem]

.. raw:: latex

    \clearpage


