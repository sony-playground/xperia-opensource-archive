********
Appendix
********

Build and run tests on Ubuntu
=============================
1.      The tests need MbedTLS. The tests use the MbedTLS version supplied in associated modem repo.
2.      The system should be built and run in ”test/modem/build/ubuntu” [make/make clean].
3.      The build will produce two files: A Python script and a Linux application.
4.      The tests are executed with the command: ”python ./main_test.py [name of modultest]”.
5.      Available modultests are listed with the command: ” python ./main_test.py list”.

