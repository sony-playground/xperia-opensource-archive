Robot Framework Quick Start Guide
=================================

This document is a quick start guide to install Robot Framework and its
dependencies to execute xfl tests and view generated reports and logs.

Introduction
============

Robot Framework overview
------------------------

See http://robotframework.org

For installation follow instructions at
https://github.com/robotframework/robotframework/blob/master/INSTALL.rst

USB Prerequisites
-----------------

Python usb package must be installed. Install it by::

    sudo apt-get install python-usb

Python3 setuptools may also have to be installed::

    sudo apt-get install python3-setuptools

Python requests package must be installed. If not already installed
(error occurs stating "ImportError: No module named 'requests'"), install it by::

    sudo apt-get install python3-requests

For module core, you also need the following::

    sudo pip install pyusb --upgrade

Execution
---------

After installations and with all other preconditions in place, you can run
the tests on the command line by using the `robot` command::

    robot Test.rst

You can also specify a platform by using the option '-i' followed by a tag::

    robot -i kumano Test.rst
    robot -i kumano -i softbank Test.rst

For a list of available options run `robot --help`.


Viewing results
---------------

Running the tests generates the following three result files.

`report.html`
    Higher level test report.
`log.html`
    Detailed test execution log.
`output.xml`
    Results in machine readable XML format.


