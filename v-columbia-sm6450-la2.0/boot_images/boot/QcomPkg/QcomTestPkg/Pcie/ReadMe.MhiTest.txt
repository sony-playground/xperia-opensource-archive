 ==============================================================================
     Copyright (c) 2021 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================

Usage: MhiTest
  mhitest can be used to load firmware on an MHI-capable endpoint. Currently MHI is supported by
  SDX targets such as SDX60/SDX65 and WLAN targets such as HastingsPrime (QCA6490) and Hamilton.
  
  In addition, mhitest can be perform MHI loopback tests between the Host and the MHI capable 
  endpoint.  MHI Loopback indirectly tests PCIe functionality (Memory Reads and Writes over PCIe).
  
  This can be launched in
  uefi shell environment (Ebl) or from any other tool that can launch app in an automated way.

  mhitest takes 2 kinds of arguments, ControlArgs and Commands. Each of these can have their own specific
  sub arguments. All arguments are case insensitive. Multiple commands can be given per launch.
  
ControlArgs:
-------------
  endpoint : MHI device identifier. 
             - For HastingsPrime, this value is 4355.

  rootport : Root port number that the endpoint is connected to. This depends on the Host platform.

  loopcount : Number of iterations. For now, this is applicable only to the MHI loopback test.

Porting instructions:
---------------------
1) Get right amss.bin from WLAN team, this is the SBL image that will get downloaded in PBL.
2) amss.bin for each target is kept at : QcomTestPkg\Pcie\Fw
3) Same amss.bin will be maintained at QcomPkg\QuestPkg\Quest\packages\test_vector\MhiTest for Quest testing
4) Check the logs after BOOT_TO_UEFI and make sure MhiTestDxe is loaded properly before running MHI test case

Quest Changes to be Maintained:
------------------------------
1) Add the path for target specific amss.bin to <Build Path>\boot_images\boot\QcomPkg\QuestPkg\TestVectorFv.fdf.inc 
2) Add target specific inf file path in <Build Path>\boot_images\boot\QcomPkg\QuestBinPkg\QuestBinPkg.dsc
3) Add target specific inf file path in <Build Path>\boot_images\boot\QcomPkg\QuestBinPkg\QuestBinPkg.fdf 
4) As part of testvector.fv amss.bin will be loaded and as part of quest.fv MHI binaries will be loaded

Build Flashing steps:
1) Compile test folder to generate pcie/mhi EFIs :  python -u boot_images/boot_tools/buildex.py -t Target,QcomToolsPkg,QcomTestPkg -r DEBUG -v LAA
2) Copy pcie, mhi and pwrup EFIs from <Build Path>\boot_images\Build\QcomTest\DEBUG_CLANG120LINUX\AARCH64 to <Build Path>\boot_images\boot\QcomPkg\QuestBinPkg\TARGET_NAME\EFI
3) Go to <Build Path>\boot_images\boot_tools and compile Quest Package using this command : python buildex.py -t QuestPkg -v LAA --build_flag="-D,TARGET_NAME"
4) Go to <Build Path>\boot_images\boot_tools and compile Quest Bin package using this command : python buildex.py -t QuestBinPkg -r debug -v LAA --build_flag="-D,TARGET_NAME"
5) Make sure to change target names in above commands as per the target getting tested.
6) Boot the device to fastboot
7) Flash testvector in logdump partition, on the target, using command prompt : fastboot flash logdump "<Build Path>\boot_images\boot\QcomPkg\QuestBinPkg\Bin\QuestBin\DEBUG\testvector.fv"
8) Flash questfv in toolsfv partiotion, on the target, using command prompt : fastboot flash toolsfv "<Build Path>\boot_images\boot\QcomPkg\QuestBinPkg\Bin\QuestBin\DEBUG\quest.fv"
9) Boot the device to bring BDS menu using BOOT_TO_UEFI option on Alpaca/Axiom
10) Power up the Endpoint using this command on Putty : st fv4:\PwrUp "wlan on"
11) Mount logdump partition, using this command on putty : "mount logdump" (Note : toolsfv is mounted by defaulted when BDS menu opens. Hence, no need to do it manually)
12) Once the partition has been successfully mounted run MHI commands in below sequence

Commands :
----------
  loadfirmware  : Load firmware image into the endpoint SoC so that it transitions from PBL to mission mode.
                  This command MUST be executed before attempting MHI loopback.

  loopback : Execute MHI loopback test

In order to perform an MHI loopback test, the following sequence must be executed
2) Execute MHI test app with the "loadfirmware" command so that the endpoint transitions to mission mode.
3) Execute MHI test app with the "loopback" command.

Example usage of commands:
  st fv4:\MhiTest "endpoint 4355 rootport 0 loadfirmware"
  st fv4:\MhiTest "endpoint 4355 rootport 0 loopcount 5 loopback"

