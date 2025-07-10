======================
General Description
======================

Introduction
============

The integration of flash core security functionality in boot and modem
consists of following parts:

  * Supply fused security properties.
  * Supply embedded security properties.
  * Supply access to MiscTA.
  * Supply crypto library support. Integration of crypto library
    will be described in last chapter.
  * Supply Standard C library with Heap

Detailed description for integration in boot and modem follows in
later chapters.


Fused Security properties
=========================
The following properites should be read only or OTP:
  * IsFused: Is the device fused?:

      "True"/"False"
  * DevId: An unique device id.

      Device id may have different length for different platforms.
      Represented as an array of bytes.
  * IsTestRootCertAllowed:

      +---------+----------------------------+--------+
      | Fused   | Root Cert Selector field   | Return |
      +=========+============================+========+
      | No      | Don't care                 | True   |
      +---------+----------------------------+--------+
      | Yes     | "0": Test fused            | True   |
      +---------+----------------------------+--------+
      | Yes     | "1": Live fused            | False  |
      +---------+----------------------------+--------+

Embedded security properties
============================
The following properites should be embedded into a signed image:
  * EmbeddedRootCerts: List of root certs with allowed usage. The property
    "IsTestRootCertAllowed" should be used to determine if the test root cert
    should be present.

Access to MiscTA
================
The FCS functionality provides two interface levels to access MiscTA:
  * Direct access to TA Library. The integrator needs to provided the
    TA Library.
  * Simple Init/Read/Size interface. The integrator needs to provide
    the functions.

