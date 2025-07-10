Transport Pipe Tests


Basic Requirements
------------------

* Configure loader for test
  * Modify <vendor/semc/fs/build/tasks/loader.mk>
    * Set <FCS_PRODUCTION ?= false>
    * Set <FCS_TR_FILE ?= true>
  * Modify <vendor/semc/fs/main/build/linux/android_main.mk>
    * Set <CFG_TR_FILE := n>
    * Set <CFG_TR_PIPE := y>

* Build the loader from root of repo <make loader -j24>

* Flash using your favorite tool


Running
-------

* Run tests from <vendor/semc/fs/main/test/trs> using <./run.sh>
* Run single test by using <./run.sh <test name>>


Add test
--------

* Create a new directory in <vendor/semc/fs/main/test/trs/tests>
* Create a new filed named <cmd> in new directory
* Add test flow in <cmd> file


cmd syntax
----------

"start_loader"

  Starts the loader as a service. The command will do nothing if the loader is
  already running.

"stop_loader"

  Stops the loader service. The command will do nothing if the loader is not
  running.

"run %s"

  Run test case %s. The test case must be present in the
  <vendor/semc/fs/main/test/trs/tests> folder. Note that no restart of the
  loader is done after the test is run. If a restart is needed please use
  command <stop_loader> & <start_loader>.

"sh %s [OPTIONS]

  Run shell script %s with arguments specified in OPTIONS. Please read chapter
  <Bash helper scripts> for more information.

"fc %s [REPLY]"

  Run fastboot command %s. The command %s could include a dynamic part which is
  convenient in the case of <download:12345678> or <verify:12345678>. It is
  possible to provide a file containing the size to such a command. To do this
  <:%> is used. E.g. <download:%file> will use the file temporary file <file>
  to provide the 8 digit size needed. The size of <file> is concatenated with
  the original string to create the complete command.

  REPLY
    -s %s
      The command is expected to return the string %s as a response. If the
      expected string is not returned the test case fails.
    -f %s %n
      The command return value is stored in the file %s with the expected size
      of %n bytes.

"fd %s [OPTIONS] [REPLY]"

  Download the binary %s to the host using fastboot.

  OPTIONS
    -n %n
      Download %n bytes.
    -f %s
      Download the specified amount of bytes specified in file %s. The file %s
      must contain a string formated as "DATA12345678", i.e. "fastboot style".

  REPLY
    -s %s
      The command is expected to return the string %s as a response. If the
      expected string is not returned the test case fails.
    -f %s %n
      The command return value is stored in the file %s with the expected size
      of %n bytes.

"fu %s [REPLY]"

  Upload the binary file %s to the device.

  REPLY
    -s %s
      The command is expected to return the string %s as a response. If the
      expected string is not returned the test case fails.
    -f %s %n
      The command return value is stored in the file %s with the expected size
      of %n bytes.


Bash helper scripts
-------------------

It is possible to extend the test case with bash scripts. To ease the
development make sure you source the <common.sh> script first. The head of a
helper script will typically contain:

  #!/bin/bash
  . ../../core/init.sh

The source will enable access to e.g. <HOST_TMP_DIR> and <DEV_TMP_DIR>.


Examples
--------

start_loader
  Start the loader

fc SAKE-Authenticate:challenge -f size 12
  Send command <SAKE-Authenticate:challenge> and store the result in file
  <size> and expected number of bytes of the response is 12.

fd challenge -f size -s OKAY
  Download data from the device to the file <challenge>. The size of the
  downloaded data is defined in the file <size>. Note the requirements on
  formating of file <size> above. The expected response is "OKAY".

sh send_challenge.sh challenge resp
  Run the <send_challenge.sh> script with the parameters <challenge> and
  <resp>. The script must be located in the test root directory.

fc download:%resp -f out2 12
  Send command download with the size of the file resp as an input parameter.
  If the size of <resp> is 0x1234 the command sent is <download:00001234>. The
  result is stored in the file <out2> and the expected size if 12 bytes.

fu resp -s OKAY
  Binary upload the file <resp> to the device. The expected response is the
  string <OKAY>.

fc SAKE-Authenticate:response -s OKAY
  Send the command <SAKE-Authenticate:response> with the expected response
  <OKAY>.

run authenticate_1
  Run the test case <authenticate_1> available in the tests directory.
