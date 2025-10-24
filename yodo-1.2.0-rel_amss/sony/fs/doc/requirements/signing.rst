=========
 Signing
=========

This chapter details the method used to sign, and verify, various
pieces of data on Sony Mobile devices. This includes both executable
code and configuration data.

Introduction
============

The digital signature scheme used by Sony Mobile is based on X.509
version 3 certificates, as defined by [X.509]_, and the basic
certification path validation algorithm described in [RFC5280]_,
section 6.

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

Certification Path Validation
=============================

The certificate validation MUST follow the algorithm described in
[RFC5280]_, section 6, with the following additions and constraints:

  #. The current date/time MUST be set to either of these values:

     #. A constant time, decided on a per-project basis.
     #. The build time of the Component.
     #. The real world time at the moment when the validation is
        performed. This time SHOULD be provided by a trusted time
        source.

  #. Policies SHOULD NOT be used.

  #. The exact details of how to find valid trust anchors is
     intentionally left out of this specification. The Implementation
     SHOULD make sure that trust anchor information is securely
     provided to the path validation algorithm.

  #. For the XCS\ [#xcs]_ feature, the implementation
     SHOULD separate certificates into at least two domains: the Sony
     domain, and the XCS domain. Ownership of the XCS domain MAY be
     transferred to trusted partners. Ownership of the Sony domain
     MUST NOT be transferred.

     #. The Implementation MAY use additional domains, if necessary.

  #. Key usage can be restricted by adding a specific extension to a
     certificate, as described in :ref:`sonykeyusage`.

  #. The validity of a certificate can also be restricted to a smaller
     group of devices, as described in :ref:`sonydevicebinding`.

.. _sonykeyusage:

Sony Key Usage Extension
------------------------

The Sony Key Usage extension is an X.509 v3 certificate extension, which
is used to limit the operations that the holder of a certificate may
perform.

This extension is represented by a DER encoded ``KeyUsage`` ASN.1
structure, as defined in :ref:`asn1module`. The OID for this extension
is ``1.3.6.1.4.1.48533.1.1.1``.

During path validation, the Implementation SHALL keep track of the
effective permissions in a state variable, from here on referred to as
``permissions``:

  * In the initialization phase, ``permissions`` MUST be initalized to
    allow all operations.

  * For every subsequent certificate, ``permissions`` MUST be updated
    to represent the largest common subset of the current contents of
    the ``permissions`` variable and the set of permissions allowed by
    the given certificate. Hence, a certificate can restrict the set
    of permissions, but cannot lift earlier restrictions.

  * When validation is complete, the current contents of
    ``permissions`` SHALL be returned.

If this extension is present in a certificate, it MUST be marked as
critical. If the extension is missing from a certificate, the
certificate MUST be treated like a certificate which explicitly allows
all operations. End entity certificates SHOULD contain this extension.

The Sony Key Usage extension is represented as a list of purposes,
encoded in an ASN.1 sequence. The following purposes are currently
defined:

  * ``flash``: The ability to sign images which are flashed using the
    Fastboot protocol. This purpose is parameterized by the name of an
    image, which SHALL be matched against the image name provided
    during flashing.

  * ``boot``: The ability to sign bootable images, booted by Sony
    bootloaders.

  * ``config``: The ability to sign different types of configuration
    data. Each purpose allows only a single type of data to be
    signed. If multiple configuration items need to be signed with the
    same certificate, multiple purposes MAY be added to the
    certificate.

.. _sonydevicebinding:

Sony Device Bindings Extension
------------------------------

The Sony Device Binding extension is an X.509 v3 certificate extension,
which is used to limit the number of valid devices for a given
certificate. For example, a certificate can be limited to only a
single IMEI.

This extension is represented by a DER encoded ``DeviceBinding`` ASN.1
structure, as defined in :ref:`asn1module`. The OID for this extension
is ``1.3.6.1.4.1.48533.1.1.2``.

During path validation, the Implementation SHALL verify that all the
certificates in the path are valid for the current Device. For every
certificate in the path, the following checks MUST be made:

  #. If the Device Binding extension is missing, the certificate MUST
     be considered valid for the current Device.

  #. If the Device Binding extension is present, the contents of the
     extension MUST be matched against the properties of the
     Device. Every type of binding is matched in a specific way:

     * ``imei``: The encoded IMEI number MUST be matched against the
       effective IMEI number of the Device. If the Device's IMEI
       number is missing and/or unavailable, this binding fails, and
       the certificate MUST be considered invalid for the current
       Device.

     * ``deviceId``: The encoded ID MUST be matched against an ID
       unique to the current Device, and which MUST NOT be changed
       during the lifetime of the Device. The Device's ID SHOULD be
       fetched from a tamper-resistant location, to avoid spoofing
       attacks.

     * ``deviceIdList``: The list of encoded ID MUST be matched against
       an ID unique to the current Device's subsystem, e.g. main
       application processor or the modem processor.

  #. Additional types of bindings can be added in the future. If an
     unknown binding is encountered in a certificate, the
     Implementation MUST reject that certificate.

If this extension is present in a certificate, it MUST be marked as
critical.

Signature Format
================

The default signature format for signed data is *Cryptographic Message
Syntax* (CMS), as defined by [RFC5652]_. The CMS SHOULD be used
whenever possible. If there is a strong reason for not using CMS, an
Implementation MAY use a different format.

For historical reasons the device MAY support Sony Mobile legacy S1
signature format for protection of simlock. A detailed specification
of this format is omitted in this specification.

Attributes
----------

The CMS allows arbitrary (signed and/or unsigned) attributes to be
embedded into the signature. These attributes are used as input to the
signature verification, to limit the situations where a signature is
considered valid.

This specification defines a single attribute, *Signature Usage* as
described below. An Implementation MAY define additional attributes.

Signature Usage
+++++++++++++++

The Signature Usage attribute is used to indicate for which purpose,
and for which device, a signature is valid.

This attribute is represented by a DER encoded ``SignatureUsage``
ASN.1 structure, as defined in :ref:`asn1module`. The attribute reuses
the ``Purpose`` and ``Binding`` ASN.1 structures from the certificate
extensions. The main difference is that only one purpose can be
encoded, as opposed to the certificate extension, which uses a list of
allowed purposes. The OID for this attribute is
``1.3.6.1.4.1.48533.1.2.3``.

In addition to the above, the ``SignatureUsage`` attribute MAY also
contain a rollback value. If this exists, the Implementation MUST
compare it to a corresponding rollback counter, and reject any
signature where the rollback value in the signature is strictly less
than the rollback counter in the Device.

To prevent misuse, this attribute SHOULD be included in all
signatures. An Implementation SHOULD check that the encoded purpose
matches the current action.

Binding
+++++++

The ``binding`` field is optional, but if a binding is included, the
Implementation MUST check that it matches the current Device. Not all
combinations of bindings are supported (S) for all usages which is
described in table below. Unsupported (US) bindings SHOULD return error if
used. The support includes both attribute and extension binding.

+--------------+------------+-----------+------------+---------+----------+
| **Usage =>** | *HwConfig* | *SimLock* | *KeyStore* | *Flash* | *Kernel* |
+--------------+------------+-----------+------------+---------+----------+
| **Binding**  |                                                          |
+==============+============+===========+============+=========+==========+
| *DevID*      | S          | US        | S          | S       | US       |
+--------------+------------+-----------+------------+---------+----------+
| *DevID List* | S          | US        | S          | S       | US       |
+--------------+------------+-----------+------------+---------+----------+
| *HMAC DevID* | US         | US        | S          | US      | US       |
+--------------+------------+-----------+------------+---------+----------+
| *IMEI*       | US         | S         | S          | US      | US       |
+--------------+------------+-----------+------------+---------+----------+
| *HMAC IMEI*  | US         | US        | S          | US      | US       |
+--------------+------------+-----------+------------+---------+----------+

Binding Mask
++++++++++++

The Binding Mask attribute is used to mask the binding identifier from
the system that produces the signed message. The mask is an HMAC,
see :doc:`dev_binding_masking/dev_binding_mask` for details on the HMAC
solution.

This attribute is optional, it MAY be used to mask the binding. Masking
is currently done by writing the HMAC key to a dedicated Trim Area unit
instead.

This attribute is represented by a DER encoded ``BindingMask``
ASN.1 structure, as defined in :ref:`asn1module`. The attribute MUST be
unsigned which means that it is not protected by a signature. Only one
binding can be encoded. The OID for this attribute is
``1.3.6.1.4.1.48533.1.2.4``.

SIMLock Data Protection
+++++++++++++++++++++++

The simlock data protection attribute is used to describe what part of
the data is covered by the signature. Only the static part of the
simlock data MUST be protected by either CMS or a S1 signature,
see :doc:`simlock` for details on the simlock solution.

For CMS, this attribute is represented by a DER encoded
``SimlockProtection`` ASN.1 structure, as defined in :ref:`asn1module`.
The attribute is signed, i.e. it is protected by the CMS signature. The
attribute contains a sequence of two integers: start, length, where the
start indicates the offset from the beginning of the simlock data
object, and the length indicates how much data from the start should be
hashed to match the message. The OID for this attribute is
``1.3.6.1.4.1.48533.1.2.5``.

This attribute MUST only exist if the purpose specify simlock.

.. _asn1module:

ASN.1 Module
============

This section describes the data objects used by the Sony extensions,
in ASN.1 syntax, as defined by [ASN.1]_.

.. literalinclude:: keyusage.asn
   :linenos:

.. rubric:: Footnotes

.. [#xcs] Xperia Custom Software, a method to allow third party
          vendors to develop software for Xperia devices.
