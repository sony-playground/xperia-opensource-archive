********
Overview
********

Components
==========
The test system is divided into two major components:

   * Main Tester: Responsible for starting the "Device" for every test case in the expected state.
   * Device: Prepare, Run and Verify one test case.

Main Tester
-----------
Main Tester might be a program or a person that handles a collection of test cases.
For every test case it is responsible for setting up the test case state/prerequisite and
collect expected prerequisite or the result of the test case.


Device
------
Device is a program which receives the test case setup from "Main Tester" and executes
the test case on target with xboot software.
The program is divided into the following parts:

   * Main application (Specific for Test Target Environment)
   * Framework (Common)
   * Test Cases (Common)

      * Some Test Data might be unique per target if enforced by Integration Platform.
      * Some test cases might not be executable for a Test Target Environment
   * Software Under Test - XBoot (Common)
   * Integration Main - for Test Cases (Specific for Test Target Environment)
   * Integration Platform - for XBoot (Specific for Test Target Environment)

Device states
-------------
A test case is normally divided into the following states initiated from "Main Tester":

   1. Report the test case prerequisites.
   2. Execute test case with prerequisites
   3. Optional post process

.. raw:: latex

    \clearpage

Boot Test on Software Target (Ubuntu)
=====================================

   * Main Tester is python application which starts Device executable.
   * Device is a Linux executable console application.
   * Test Case state (TCState) and prerequisites (HWState) are communicated to Device through command line parameters.
   * Next Test Case state (TCState) and expected prerequisites (HWState) are communicated to Main Tester through stdout.
   * Integration Platform uses a wrapper interface to allow runtime change of integration.

.. uml::
   :align: center

   :Main Tester: as MAINTEST << Python Application >>

   package "Device Main\nConsole Application" {
      [Param]
      [TCState - StdOut]
      [HWState - StdOut]
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

   package "Integration Main" {
      frame "Interface\nIntegration Main\nMain App" {
         interface "Callback HWstate" as CBHW
      }

      frame "Interface\nIntegration Main\nModule Test" {
         interface "Set Property" as SPTY
         interface "Clear Property" as CPTY
         interface "IsEqual Property" as EPTY
         interface "Prepare HWstate" as PHW
      }

      frame "Interface\nIntegration Main\nTarget Specific" {
         interface "Create with HWState" as UCRT
      }

      frame "Implementation Integration Main" {
         [Integration Main Ubuntu]
      }
   }

   package "SW Under Test" {
      [XBoot]
   }

   package "Integration" {
      frame "Interface\nIntegration" {
         interface "Core" as ICORE
         interface "TA" as ITA
         interface "Plf" as IPLF
         interface "NV" as INV
         interface "Rpmb" as IRPMB
         interface "ERoot" as IEROOT
      }

      frame "Implementation\nIntegration" {
         [Integration Wrapper]
      }

   }

   MAINTEST -> [Param]
   MAINTEST <- [TCState - StdOut]
   MAINTEST <- [HWState - StdOut]

   [Param] -> CRT
   [Param] -> EXE
   [Param] -> UCRT

   [TCState - StdOut] <- CBTC
   [HWState - StdOut] <- CBHW

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

   [Test Case] -> SPTY
   [Test Case] -> CPTY
   [Test Case] -> EPTY
   [Test Case] -> PHW
   [Test Case] -> [XBoot]

   UCRT -> [Integration Main Ubuntu]
   SPTY -> [Integration Main Ubuntu]
   CPTY -> [Integration Main Ubuntu]
   EPTY -> [Integration Main Ubuntu]
   PHW -> [Integration Main Ubuntu]
   CBHW <- [Integration Main Ubuntu]

   [XBoot] -> ICORE
   [XBoot] -> ITA
   [XBoot] -> IPLF
   [XBoot] -> INV
   [XBoot] -> IRPMB
   [XBoot] -> IEROOT

   ICORE -> [Integration Wrapper]
   ITA -> [Integration Wrapper]
   IPLF -> [Integration Wrapper]
   INV -> [Integration Wrapper]
   IRPMB -> [Integration Wrapper]
   IEROOT -> [Integration Wrapper]

   [Integration Main Ubuntu] <- [Integration Wrapper]

.. raw:: latex

    \clearpage

Boot Test on Hardware Target (UEFI)
===================================

.. uml::
   :align: center

   :Main Tester: as MAINTEST << Person Handling Target >>

   package "Device Main\nUEFI Test Application" {
      [Param]
      [TCState - StdOut]
      [HWState - StdOut]
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

   package "Integration Main" {
      frame "Interface\nIntegration Main\nMain App" {
         interface "Callback HWstate" as CBHW
      }

      frame "Interface\nIntegration Main\nModule Test" {
         interface "Set Property" as SPTY
         interface "Clear Property" as CPTY
         interface "IsEqual Property" as EPTY
         interface "Prepare HWstate" as PHW
      }

      frame "Interface\nIntegration Main\nTarget Specific" {
         interface "Create" as UCRT
      }

      frame "Implementation Integration Main" {
         [Integration Main UEFI]
      }
   }

   package "SW Under Test" {
      [XBoot]
   }

   package "Integration" {
      frame "Interface\nIntegration" {
         interface "Core" as ICORE
         interface "TA" as ITA
         interface "Plf" as IPLF
         interface "NV" as INV
         interface "Rpmb" as IRPMB
         interface "ERoot" as IEROOT
      }

      frame "Implementation\nIntegration" {
         [Integration Target UEFI/XBL]
      }

   }

   MAINTEST -> [Param]
   MAINTEST <- [TCState - StdOut]
   MAINTEST <- [HWState - StdOut]

   [Param] -> CRT
   [Param] -> EXE
   [Param] -> UCRT

   [TCState - StdOut] <- CBTC
   [HWState - StdOut] <- CBHW

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

   [Test Case] -> SPTY
   [Test Case] -> CPTY
   [Test Case] -> EPTY
   [Test Case] -> PHW
   [Test Case] -> [XBoot]

   UCRT -> [Integration Main UEFI]
   SPTY -> [Integration Main UEFI]
   CPTY -> [Integration Main UEFI]
   EPTY -> [Integration Main UEFI]
   PHW -> [Integration Main UEFI]
   CBHW <- [Integration Main UEFI]

   [XBoot] -> ICORE
   [XBoot] -> ITA
   [XBoot] -> IPLF
   [XBoot] -> INV
   [XBoot] -> IRPMB
   [XBoot] -> IEROOT

   ICORE -> [Integration Target UEFI/XBL]
   ITA -> [Integration Target UEFI/XBL]
   IPLF -> [Integration Target UEFI/XBL]
   INV -> [Integration Target UEFI/XBL]
   IRPMB -> [Integration Target UEFI/XBL]
   IEROOT -> [Integration Target UEFI/XBL]

.. raw:: latex

    \clearpage

