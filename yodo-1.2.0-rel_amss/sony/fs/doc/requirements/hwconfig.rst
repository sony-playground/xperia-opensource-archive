=========
 HWConfig
=========

This chapter details the HWConfig object, its purpose and features
used within Sony Mobile devices.

Introduction
============

HWConfig acts as a root of trust anchor for IMEI values.
In addition it also contain a symmetric encryption/decryption key,
and a prototype indicator.

This document makes use of the practices described in [RFC2119]_ when describing
the requirements.

Each requirement specifies the stakeholder and the platforms that the
requirement is valid for. The term "Generic" implies that the requirement is
valid for all platforms listed under :ref:`boot-hwc-platforms-label`.

Stakeholders
------------

FCS (Flash Core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

FST (Flash Security Tokyo) <SG-JPTO-SW-FlashSecurity-ALL-G@sonymobile.com>

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sonymobile.com>

SWS (Software Security) Petter Wallin <Petter.Wallin@sony.com>

Terminology
-----------

Implementation
  This specification can be implemented in a multitude of different
  components. In the text below, such an implementation is referred to
  simply as the *Implementation*.

Component
  This refers to the software component which is produced as part of
  the Implementation's build process. As an example, the
  Implementation of Sony bootloaders produce bootloader binary images.

Device
  This refers to the hardware device, or isolated environment, where
  the Component is executed.

.. _boot-hwc-platforms-label:

Platforms
---------

* Kumano
* Huaihe
* AG1

Format
======

Version
  Major version defined to 1.

Prototype
  A boolean flag representing a prototype indicator.
  False on Commercial device.
  Normally True on Development device.

Imei
  A list of maximum 2 entries with a string representing a value as
  outlined [RFC7254]_.
  Note that the checksum digit is omitted in the entry.

Device Key
  A 16 byte randomized data object.

Components
==========

Prototype
---------

For development purposes it is sometimes beneficial to use a flag
to allow different execution paths within the same delivery.

Imei
----
Supporting mobile network capable devices requires the assignment of mobile
identifier, imei. Within Sony Mobile there are single SIM and dual SIM type of
devices and thus the HWConfig object must be able to hold at least one but at
most two imei identifiers. For non mobile network capable devices a unique
identifier (IDID) is still required as other security related features depend
upon it, e.g. derivation of a device key.

Device Key
----------
A symmetric encryption/decryption key used when transferring content
between a trusted back-end and a device through a less trusted production
system.

The device key is used when provisioning device with device unique widevine,
android attestation, and core key blob content. Once on the device the encrypted
content must be re-encrypted by a hardware unique key, (HUK)_, to prevent
misuse and leakage.

The device key is derived by the security server (SECS) from a master key and a
device identifier (imei/idid). Knowledge of the device identifier is enough for
the secs server to encrypt the content as it can derive the device key in
runtime. By using the provisioned device key on the device the content can be
decrypted.

Requirements
============

1. The HWConfig object MUST be bound to at least one unique digital asic's
device identifier.

2. The HWConfig object MUST be bound by a [X.509]_ certificate containing an
extension for HWConfig.

3. This binding MUST be controlled as outlined in the :doc:`../requirements/signing` requirements.

4. The Version of the HWConfig object MUST be a positive integer.

5. The initial version of this HWConfig object SHALL be 1.

6. The prototype flag MUST be set to False on end consumer devices.

7. The prototype flag SHOULD be set to True on development devices.

8. The Imei list MUST contain at least one entry.

9. The Imei list MUST contain at maximum two entries.

10. One Imei entry MUST be 14 UTF-8 characters long.

11. One Imei entry MUST only contain characters of {0-9, A-F}.

12. The device key MUST be 16 bytes long.


.. _hwc-asn1module:

ASN.1 Module
============

This section describes the hwconfig data object used by the Sony extensions,
in ASN.1 syntax, as defined by [ASN.1]_.

.. literalinclude:: hwconfig.asn
   :linenos:
