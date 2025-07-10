===========================
 Bootloader Unlock for IoT
===========================

This document describes a method for unlocking the bootloader in IoT
devices.

.. warning::

   This is a DRAFT of a proposed way of handling bootloader unlocking
   in IoT devices. This document does NOT describe the method used to
   unlock the bootloader in Xperia devices.

Introduction
============

The current implementation of bootloader unlocking, used in Xperia
devices, has a number of problems which makes it hard to port to other
kinds of products:

* It depends on the S1 SIMLock solution, which is usually not
  available on IoT devices. Two pieces of data are currently stored in
  the SIMLock structure:

  * The hashed RCK, which is used to validate the RCK
  * The setting to allow or disallow unlocking

* It requires a USB connection to the device

Since an IoT device does not necessarily contain a cellular modem, nor
a USB port, it does not make sense to depend on these features.

Terminology
===========

Definitions
-----------

Device
   An IoT device/product.

Management Service
   In this document, it is assumed that a Device is connected to some
   sort of management service. The user can use this service to manage
   the list of owned Device(s). This can be done, for example, with a
   mobile application, or a website.

Bootloader
   This is the first piece of software (excluding code in ROM) that
   executes on the Device when it is powered on. Its main
   responsibility is to load and authenticate the main software.

Bootloader Unlocking
   When a Device is shipped from the factory, the Bootloader is in a
   locked state, meaning that it will only allow properly signed
   software to execute. Once the Bootloader is unlocked, it will
   execute any software.

Unlocking Server
   The secret keys used for unlocking the Bootloader need to be stored
   securely. There should be a dedicated server for this purpose. In
   some cases, this server is part of the Management Service. In other
   cases, this server is completely isolated.

Requirements
------------

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT",
"SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this
document are to be interpreted as described in [RFC2119]_.

Unlocking
=========

This section describes the sequence for unlocking the Bootloader. A
high level diagram of the process can be seen in :numref:`unlock_seq`.

.. _unlock_seq:

.. uml::
   :align: center
   :caption: Bootloader unlocking sequence

   hide footbox

   participant "Unlocking\nServer" as srv
   participant "Management\nService" as mgmt
   participant "Device" as dev

   activate mgmt

   opt
     mgmt -> dev: get_key_id()
     activate dev
     dev -> mgmt: key_id
     deactivate dev
   end

   mgmt -> srv: get_unlock_data(key_id, dev_id)
   activate srv
   srv -> mgmt: unlock_data
   deactivate srv

   mgmt -> dev: unlock(unlock_data)
   activate dev
   dev -> mgmt: result
   destroy dev

As a first step in this process, the Management Service asks the
Device which key to use to sign the unlocking data. The Device MUST
respond with the ID of the key that will be used when the unlocking
data is authenticated. In some cases the Management Service already
knows which key to use, so this entire step is OPTIONAL.

For the next step, the unlocking data is generated. The Management
Service MUST provide the key ID and the device ID to the Unlocking
Server, and request it to generate the necessary unlocking data. The
Unlocking Server MUST sign the device ID with the correct secret key\
[#secret_key]_, and return the result to the Management Service.

Once the Unlocking Server has returned a result, the Management
Service MUST send this to the Device, and request that the Device
unlocks its Bootloader. The Device MUST authenticate the request data
and send the result back.

The full authentication process is illustrated in
:numref:`authentication`. First, the signature MUST be verified, to
make sure that the data is signed with the correct key. After the
signature is verified, the device ID in the unlocking data MUST be
compared to the device ID of the Device. If they match, the data MUST
be written to the Device's storage, and the Device MUST reboot to
apply the change.

.. _authentication:

.. uml::
   :align: center
   :caption: Verification of unlocking data

   start

   if (signature ok?) then (yes)
     if (dev_id ok?) then (yes)
       :write unlock data to storage;
       :result = OK;
     else (no)
       :result = FAIL;
     endif
   else (no)
     :result = FAIL;
   endif

   stop

After the reboot, the Bootloader in the Device MUST be able to detect
that the lock state should be changed. If a change is detected, the
Bootloader MUST erase all sensitive data from the Device, before
finalizing the change. The exact details of the finalization step is
intentionally left out of this document, since it depends on the
capabilities of the Device and product security requirements. Some
possible ways of doing this is to blow a fuse or write to
replay-protected storage. It can also be implemented by simply storing
the signed unlocking data; if this method is used, the Bootloader MUST
authenticate the data on every boot.

General Requirements
====================

* The secret keys MUST be stored in an HSM, or equivalent, device which
  does not allow keys to be extracted..

* The secret keys MUST be large enough to be resistant to brute force
  attacks.

* The Management Service MAY restrict unlocking to only a subset of
  all the available users.

Open Issues
===========

* Do we need to care about replay attacks? Is there ever a case where
  a Device is unlocked multiple times? Anti-replay complicates the
  solution a lot:

  * We need to generate a nonce on the device
  * Persisting the state is much more complicated

* Do we need to assert the user's physical presence before unlocking?

  * How high is the risk of abuse?

.. rubric:: Footnotes

.. [#secret_key] This is usually a private key for a public key
                 cryptosystem, such as RSA or ECDSA.
