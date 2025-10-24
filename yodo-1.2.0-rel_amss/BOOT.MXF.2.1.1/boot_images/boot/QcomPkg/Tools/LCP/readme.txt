************ Usage example for generating new xbl_config.elf and updating DCB bin to include LCP bin ************
1). Please ensure to have python 3.8.x or higher version installed. 
    (Execute "python -V" on terminal/command promompt to check python version.)
2). Example to update xbl_config.elf to include LCP bin:
    python <boot_build_path>boot_imageoot\QcomPkg\Tools\LCP\lcp.py --target=SM8550 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o ./output in -l LCP.bin -x xbl_config.elf
3). Example to update DCB bins to include LCP bin:
    python <boot_build_path>boot_imageoot\QcomPkg\Tools\LCP\lcp.py --target=SM8550 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o ./output in -l LCP.bin -x <dcb_bin_path>\