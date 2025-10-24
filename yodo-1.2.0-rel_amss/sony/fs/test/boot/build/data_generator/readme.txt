The script 'xboot_tfw_gendata_nofxtool.py' generates a device unique dut_normal.c
which can be used when building a xboot test framework on hardware target.
The script needs secs.
Dynamic libraries and secs.py is built from git:
- flashtools/secs

Execution:
export LD_LIBRARY_PATH=<path to libsecs.<dll/so> and libfxtool.<dll/so>> \
export PYTHONPATH=<path to 'secs.py' and 'fxtool.py'> \
python xboot_tfw_gendata_nofxtool.py Kumano-Ubuntu OFF FCABADF6 00440245851024 2
Platform:Kumano-Ubuntu
Security:OFF
DevID:FCABADF6
Imei:00440245851024 (or if two imeis: "00440245851024 00440245851025")
Keystore Counter:2

