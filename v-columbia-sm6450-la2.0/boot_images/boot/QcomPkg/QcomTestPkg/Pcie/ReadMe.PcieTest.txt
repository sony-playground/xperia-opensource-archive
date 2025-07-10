 ==============================================================================
     Copyright (c) 2020 - 2021 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================

Usage: PwrUp
  PwrUp tool can be used to powerup modules on QCom platforms from UEFI. It
  powers up a particular module either on/off based on arguments. If no argument
  is given, then it lists the available modules that can be given as argument.

Arguments:
  ModuleName <operation on/off>

  ModuleName can be one of currently supported ones. ie wlan or wigig or sdx
  Operation can be one of on or off.

e.g. st fv3:\PwrUp "wlan on"


Usage: PcieTest
  pcietest can be used to test basic PCIe core functionality in loopback mode. This can be launched in
  uefi shell environment (Ebl) or from any other tool that can launch app in an automated way.

  pcietest takes 2 kinds of arguments, ControlArgs and Commands. Each of these can have their own specific
  sub arguments. All arguments are case insensitive. Multiple commands can be given per launch.
  
ControlArgs:
-------------
  Core : 0 | 1 | 2 (0 default if not given)
  BuffSize : Hex number string (will be rounded up to page size, default 1MB if not given)
  --result : Hex address string (only used with automation launching tool)
  loop : <count> loop through (rerun) the list of commands argument count times

Commands :
----------
  LocalAnalog  : LocalAnalog/Phy loopback test. Phy or LA aliases can also be used.
  LocalDigital : LocalDigital/Pipe loopback test. Pipe or LD aliases can also be used.
  RemoteDigital : RemoteDigital loopback test. Remote or RL aliases can also be used.

          Optional Sub Args: for above 3 commands. If unspecified, uses fastest possible
                 LinkWidth <dec num> : Set link width as specified number of lanes. (also lw)
                 LinkSpeed <dec num> : Set link speed as the Gen number. (also ls)

  Info : Print Core related capability info. (No other args)
  enum : Enumerate the device connected to port and print info (No other args)
  rst  : Reset and power off the port (No other args)

  tpsel : Target platform option Select, one of the following options required. Would work only on supported target platform
          Sub arguments : Required
            x4 : Set platform Lane option to x4
            x2 : Set platform Lane option to x2

  L0  : Bring the link up and enumerate (the module should already be powered),
          then enable L0s and perform config access test to bring link out of L0
          and going back into L0

  epcfg : Bring the link up and enumerate (the module should already be powered),
            then perform read/write tests on the end point config space.

  memio : Perform memory IO to BAR space registers. To prevent causing errors, a map of writable
            registers range per VendID/DevID need to be present in the test.

e.g.:
  st fv3:\pcietest "core 1 BuffSize 0x200000 info Phy LinkWidth 1 LinkSpeed 2"
  st fv3:\pcietest "core 1 info"
  st fv3:\pcietest "core 0 rl core 1 rl rl ls 2 rl ls 1 loop 5"

