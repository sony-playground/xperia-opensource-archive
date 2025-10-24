************ Usage example for standalone XBL Config generation and disassembling cases ************
NOTE:
	example syntax is Linux Bash shell command-line
	.../ refers to root of checked-out P4 tree
	sandbox/ refers to local directory to work examples in

A. XBL_Config Disassembling:
  (one time steps#1-6)
  1). Please ensure to have python 3.8.x or higher version installed. 
      (Execute "python -V" on terminal/command promompt to check python version.)
  2). Sync BOOT.MXF.2.0 XBL image OR use released CRM build. 
  3). From synced-image/CRM-build, cp .../boot_images/boot_tools/XBLConfig/* sandbox/XBLConfig
  4). Copy sectools from server path(s) to sandbox/XBLConfig/sectools/ directory:
	Linux   : /pkg/sectools/v2/latest/Linux
	Windows : \\sundae\sectools\v2\latest\Windows\sectools.exe
  4.a) Copy security profile from .../boot_images/ssg_tmefw/waipio_tme_security_profile.xml and rename it to tme_security_profile.xml
  5). Please ensure copied files and folder in sandbox/XBLConfig/* have read/write permissions.
  6). Create sandbox/XBLConfig/output/ directory if it doesn't exist.
  (repeat steps#7-11 for every new xbl_config.elf to be disassembled)
  7). cd sandbox/XBLConfig
  8). Copy xbl_config.elf to be disassembled in sandbox/XBLConfig/   directory.
      From built XBL image, xbl_config.elf can be found at 
          .../boot_images/boot/QcomPkg/SocPkg/Waipio/Bin/LAA/DEBUG/xbl_config.elf
  9). To disassemble xbl_config.elf, Execute 
      "python GenXBLConfig.py -d ./xbl_config.elf -f ELF -o ./output"
  10). Above command creates "create_xbl_config.json" and config-items in sandbox/XBLConfig/output/ folder.
  11). Above disassemble successful run also prints command at the end which can be executed 
       to re-create xbl-config.elf as captured in "B. XBL_Config generation: option-1".
B. XBL_Config Generation:
  option-1: (easy option, when you already have xbl_config.elf from build.)
  1). Follow above steps listed in "A. XBL_Config Disassembling:"
  2). (optional) If settings need to be updated then update respective xbl-config .bins in 
      sanbox/XBLConfig/output/ and add/remove more xbl-config .bin along with config-item 
      info (like file_name, config_name) in sandbox/XBLConfig/output/create_xbl_config.json.
      Follow existing config-item structure to add/remove more config-items.
  3). To generate xbl_config.elf, Execute 
  "python GenXBLConfig.py -i ./output/create_xbl_config.json -b ./output -f ELF  -o ./output/xbl_config --sectools_directory ./sectools --security_profile waipio_tme_security_profile.xml --sign_id XBL-CONFIG --sectools_version v2"
  4). Above command creates new ./output/xbl_config.elf which has updated config-items from #2.

  option-2:
  (one time steps#1-6)
  1). Please ensure to have python 3.8.x or higher version installed. 
      (Execute "python -V" on terminal/command promompt to check python version.)
  2). Sync BOOT.MXF.2.0 XBL image OR use released CRM build. 
  3). From synced-image/CRM-build, cp .../boot_images/boot_tools/XBLConfig/* sandbox/XBLConfig
  4). Copy sectools from server path(s) to sandbox/XBLConfig/sectools/ directory:
	Linux   : /pkg/sectools/v2/latest/Linux
	Windows : \\sundae\sectools\v2\latest\Windows\sectools.exe
  4.a) Copy security profile from .../boot_images/ssg_tmefw/waipio_tme_security_profile.xml
  5). Please ensure copied files and folder in sandbox/XBLConfig/* have read/write permissions.
  6). Create sandbox/XBLConfig/output/ directory if it doesn't exist.
  (repeat steps#7-12 for every new xbl_config.elf generation)
  7). cd sandbox/XBLConfig/
  8). Create sandbox/XBLConfig/output/create_xbl_config.json file with settings config binaries.
      Below is example "create_xbl_config.json" which contains two example config items in local directory.
      "ram_address" in first entry is elf_entry_point, only required for first entry. 
      1. 1st item has unique "config_name":"/pmic_settings.bin" and "file_name" has file-name of 
         settings binary including path relative to base_directory.
      2. 2nd item has unique "config_name":"/ddr_settings.bin" and "file_name" has file-name of 
         settings binary including path relative to base_directory.
          {
              "CFGL":{
                  "major_version": 2,
                  "minor_version": 1,
                  "file1":{
                      "config_name":"/pmic_settings.bin",
                      "file_name":"pmic.bin",
                      "ram_address":"0x1494E000"
                  },
                  "file2":{
                      "config_name":"/ddr_settings.bin",
                      "file_name":"ddr.bin"
                  }
              }
          }
      Use above example "create_xbl_config.json" and update/ensure to capture your settings 
      "config_name" and "file_name" path relative to sandbox/XBLConfig/output directory
      and those .bin files must exist in respective relative directories.
  10). (optional) As required, update config-item.bin in sandbox/XBLConfig/output/ and
      add/remove more config-item info in sandbox/XBLConfig/output/create_xbl_config.json.
      Follow existing config-item structure to add/remove more config-items.
  11). To generate xbl_config.elf, Execute 
  "python GenXBLConfig.py -i ./output/create_xbl_config.json -b ./output -f ELF  -o ./output/xbl_config --sectools_directory ./sectools --security_profile waipio_tme_security_profile.xml --sign_id XBL-CONFIG --sectools_version v2"
  12). Above command creates sandbox/XBLConfig/output/xbl_config.elf as per -o option above.
****************************************************************************


Usage Example to generate XBL config image with Pmic binary data blob using XBL build.
(Above steps should have been run to create sandbox area that is used here)

1) Use arm utility to generate pmic binary

    /pkg/qct/software/llvm/release/arm/12.0.3/tools/bin/arm-elfcopy -O binary .../boot_images/boot_images/Build/WaipioLAA/Pmic/DEBUG_CLANG120LINUX/AARCH64/QcomPkg/SocPkg/Waipio/Library/PmicLib/loader/Pmic/DEBUG/Pmic.dll sandbox/XBLConfig/output/_pmic_settings.bin

2) Run GenXBLConfig.py to generate the final XBL config image

    python GenXBLConfig.py -i sandbox/XBLConfig/output/create_xbl_config.json -b sandbox/XBLConfig/output --sectools_directory sandbox/XBLConfig/sectools -f ELF --output-file sandbox/XBLConfig/output/xbl_config --autogen_directory sandbox/XBLConfig/output/auto_gen --elf-address 0x1494E000 --security_profile waipio_tme_security_profile.xml --sign_id XBL-CONFIG --sectools_version v2

