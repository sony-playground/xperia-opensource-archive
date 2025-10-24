===============
 Sony Keystore
===============

Introduction
============

The Sony keystore holds the keys used for verifying the images verified by the
xfl and the boot.

The Sony keystore is stored in a separate partition in persistent storage and
is verified against an embedded root and bound to Device Binding or an HMAC
([RFC2104]_), where the key is stored in misc TA and Device Binding is the message.
See :doc:`../design/xcs_dev_binding_masking` for details on the HMAC solution.

See :ref:`ks_check` for details on the verification.

The format for the keystore is described in :ref:`keystoredefinition`.

See :doc:`../requirements/signing` and :doc:`../projects/index` for a
description on key usage.

.. _keystoredefinition:

Definition
==========

This section describes the data structure of the Sony keystore,
in ASN.1 syntax, as defined by [ASN.1]_.

.. literalinclude:: ../../core/ks/keystore.asn
