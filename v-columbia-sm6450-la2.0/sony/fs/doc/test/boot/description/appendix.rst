********
Appendix
********

Build and run tests on Ubuntu
=============================
#.      The tests need mbed TLS. The tests use the mbed TLS version
	supplied in associated boot repo.

#.      The system should be built and run in:

	”test/boot/build/ubuntu/<platform>” [make/make clean]

	(only full build is currently supported).
#.      The build will produce two files:

	A Python script and a Linux application.

#.      The tests are executed with the command:

	”python ./main_test.py [name of module test]”.

#.      Available module tests are listed with the command:

	” python ./main_test.py list”.

#.      Please make sure to remember to execute "make clean" after finishing
        running tests as a regular boot build will not be possible otherwise.

Build and run tests on Target (UEFI)
====================================

#.      The boot should be built with:

	”make USES_FEATURE_XBOOT_TFW='yes' mbn”.

#.      To switch between normal boot build and TFW the build system must be
	completely cleaned:

	#. rm -rf edk2/abl/Build/DEBUG_CLANG35/
	#. rm -rf edk2/abl/Conf/.cache/
	#. rm -rf boot_images/Build/*
	#. rm -rf boot_images/Conf/.cache/

#.      The tests are executed in "test/boot/uefi" with the command:

	”python main.py "/dev/ttyUSB0" "dump.txt" [name of module test]”.

#.      Available module tests are listed with the command:

	” python ./main.py "/dev/ttyUSB0" "dump.txt" list”.

