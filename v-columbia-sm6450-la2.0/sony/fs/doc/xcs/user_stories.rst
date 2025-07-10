User stories
============
This page describes the user stories associated with Xperia Custom Software.
It involves components like bootloader, ULF and NORI.


US1: XCS Unlock
---------------
As a partner, I want to unlock bootloader of my Xperia device
so that I can flash my own software.

* **Bootloader requirements:**

  - `Vendor fastboot requirements`_.


* **ULF requirements:**
* **NORI requirements:**

US2: Batch Unlock
-----------------
As a partner, I want to unlock bootloader on batch of Xperia devices
so that I can flash my own software on them in a batch mode.

* **Bootloader requirements:**

  - `Vendor fastboot requirements`_.

  - `Auto set OEM unlocking flag requirements`_.

* **ULF requirements:**

US3: XCS lock
-------------
As a partner, I want to migrate root of trust on my device.

* **Bootloader requirements:**

  - `Boot XCS requirements`_.

* **ULF requirements:**
* **NORI requirements:**

US4: XCS lock - secure storage for ROT
--------------------------------------
As a partner, I want the new root of trust to be unmodifiable (i.e. stored in persistent storage),
so that it is impossible for others to make the device execute code not chaining to the ROT.

* **Bootloader requirements:**

  - `Boot requirements`_.

  - `Boot XCS requirements`_.

  - `XCS device binding mask requirements`_.

.. _Vendor fastboot requirements: http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/requirements/vendor_fastboot.html#requirements
.. _Auto set OEM unlocking flag requirements: http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/design/autoset_OEM_unlocking_flag.html#requirements
.. _Boot XCS requirements: http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/requirements/boot.html#xcs-xperia-custom-software
.. _XCS device binding mask requirements: http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/design/xcs_dev_binding_masking.html#requirements
.. _Boot requirements: http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/requirements/boot.html#requirements
