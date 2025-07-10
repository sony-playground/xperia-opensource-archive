=========
 Simlock
=========

This chapter details the Simlock solution used by Sony Mobile.

Introduction
============

Simlock consist of two parts, data and a signature protecting the data.
The data can be dived into:
* **static** - Provisioned at manufacturing or customer service center.
* **dynamic** - Influenced by interaction, e.g. inserting a SIM card
matching the settings or by unlocking a lock using an unlock code.

The signature only protects the static part of the data. The signature is device
bound, typically to device IMEI. The signature chains to an embedded root
certificate.

This document makes use of the practices described in [RFC2119]_ when describing
the requirements.

Each requirement specifies the stakeholder and the platforms that the
requirement is valid for. The term "Generic" implies that the requirement is
valid for all platforms listed under :ref:`simlock-platforms-label`.

Stakeholders
------------

FCS (Flash Core Security) Team Yellow <DL-SELD-FlashSecurity-TeamYellow@sonymobile.com>

FST (Flash Security Tokyo) <SG-JPTO-SW-FlashSecurity-ALL-G@sonymobile.com>

FAS (Flash Application Security) Magnus Strandh <Magnus1.Strandh@sonymobile.com>

SWS (Software Security) Petter Wallin <Petter.Wallin@sony.com>

SW Security-Advanced Team <SG-JPTO-SW-SoftwareSecurity-ALL-G@sonymobile.com>

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

.. _simlock-platforms-label:

Platforms/Products
------------------

* Kumano
* SM33

Data Format
===========

Bomb
  A 20 byte random data, set by simlock producer, e.g. SECS.
  **Type:** Dynamic.

Version
  Major version defined to 2.
  **Type:** Static.

Configuration
  Contains:
  * MNC
  * Maximum number of unlock attempts
  * Waiting time between each unlock attempt
  * Bomb validation hash
  * Factory fresh hash
  * Mobile operator identifier, identifier list is written as TAG="VALUE";
  * test SIM array of accepted test SIM cards.
  **Type:** Static.

Customization
  Holds auto lock and normal SIM lock for all categories.
  * Network
  * Network subset
  * Service Provider
  * Corporate
  **Type:** Static.

Codes
  Holds the hash of the 16 digit randomized unlock code for each lock category.
  * Network
  * Network subset
  * Service Provider
  * Corporate
  **Type:** Static.

Control Key State
  Holds the execution state for each lock category. That is for each state, the
  number of unsuccesful unlock attempts and the 16 digit unlock code.
  * Network
  * Network subset
  * Service Provider
  * Corporate
  **Type:** Dynamic.

AutoLocked
  Holds the lock properties: IMSI, GID1, GID2, for each category.
  Automatically lock one or several categories depedning on inserted SIM card
  properties.
  * Network
  * Network subset
  * Service Provider
  * Corporate
  **Type:** Dynamic.

Factory Fresh
  20 byte random data, set by simlock producer, e.g. SECS.
  **Type:** Dynamic.

Kirin
  Device generated signature.
  **Type:** Dynamic.

Signature Format
================

See :doc:`../requirements/signing` requirements.

Components
==========

TBD

Requirements
============

1. The simlock data object static part MUST be bound to a simlock signature
object.

2. The simlock signature object MUST be bound by a [X.509]_ SOMC certificate.
   If SOMC key usage extension is present, it MUST contain purpose simlock.

3. This binding MUST be controlled as outlined in the :doc:`../requirements/signing` requirements.

4. This binding MUST include a device IMEI binding.

5. The simlock signature object MUST contain an attribute stipulating the start
of the static data part and its size expressed in bytes.

Simlock Data Format
===================

This section describes the simlock data object used by Sony Mobile devices,
in C syntax.

.. literalinclude:: somc_simlock_format.h
   :linenos:
