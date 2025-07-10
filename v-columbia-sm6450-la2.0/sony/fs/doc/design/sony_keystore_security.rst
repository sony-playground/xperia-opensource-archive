===================================
Sony keystore security
===================================

Introduction
============
Sony keystore is a storage for keys/certificates. xflkeystore and
xflkeystorebak partitions are used for storage of the keystore data. xflkeystorebak
is a backup partition used to restore the keystore data to the primary
partition if the keystore in the primary partition is invalid. With this
design it is possible to erase the backup and the primary partition and install
new keystore to the device. This should not be allowed, especially for XCS
devices. One solution for this problem is to store the hash value of the
current valid keystore in a secure data storage (RPMB).

Implementation
==============
This feature affects the Xboot, XFL and the xflattest tz application.
SHA256 keystore hash, XCS boolean flag and the keystore counter (further referenced
as xfl_sec_data) should be added to the data that is kept in RPMB. RPMB is only available on fused devices.
On unfused devices this data should be kept in some non-volatile memory like Trim Area, or some
device partition. If needed new data can be added to the end of the structure and the version
should be increased.

.. code-block:: c

  #define KEYSTORE_SHA256_LENGTH 32
  #define XFLATTEST_NONCE_LEN 20
  #define XFLATTEST_MAX_NUM_OF_RB_INDEX 32

  struct xfl_sec_data {
        uint32_t version;
        uint8_t  bl_unlock_status;
        uint32_t rpmb_ks_counter;
        uint32_t xcs_rot;
        uint8_t  sake_nonce[XFLATTEST_NONCE_LEN];
        uint8_t  keystore_hash_sha256[KEYSTORE_SHA256_LENGTH];
        uint64_t rollback_counter[XFLATTEST_MAX_NUM_OF_RB_INDEX];
        uint32_t has_been_unlocked;
  } __attribute__ ((packed));

xflattest TZ application
------------------------
xfl_sec_data is retrieved from TZ application (xflattest). This data is sent to the tz application
by the bootloader or the xfl. If the device is fused the application should read and write this
data to RPMB. If the device is not fused it should keep the xfl_sec_data in local memory.

XFL
---
New/changed variables are needed in the XFL:

.. code-block:: none

  Variable Security-state
    This variable is changed to return the SHA256 hash over the keystore
    payload of the latest successfully applied keystore. The hash is encoded
    and presented in base64 format.

  Variable Stored-security-state
    Returns the SHA256 hash over the keystore payload of the latest
    successfully applied keystore. The value is retrieved from the secure
    storage. The hash is encoded and presented in base64 format.

  Variable Keystore-xcs
    Returns "yes" if the device has been flashed with keystore which should
    not be possible to update, otherwise returns "no". This value is retrieved
    from secure storage.

XBoot
-----
The bootloader MUST boot into service mode if the keystore is invalid. On unfused
devices the bootloader SHOULD write the xfl_sec_data to some non-volatile memory and also send the
same data to xflattest. On fused devices the data should be sent directly to xflattest and should
be written to the RPMB by the application.
The xboot flow for initialization and applying of the keystore is illustrated in
:ref:`ks_check`, :ref:`ks_load_keystore`, :ref:`ks_set_keystore` and :ref:`keystore_load`.

.. note::
  ks_check, ks_load_keystore, ks_set_keystore and keystore_load are function names in the code.
  Same names are used for the graphs so it is clearer which function is doing what.
  ks_check, ks_load_keystore and ks_set_keystore are common functions for the xfl and xboot.
  keystore_load is only used by the xboot.

.. _ks_check:

.. uml::
  :caption: ks_check(ks_partition)
  :align: center

  start
  :ks_check(ks_partition) is called;
  :read Keystore-counter;
  :read Stored-security-state;
  :read Keystore-xcs;
  :verify keystore signature;
  if (success?) then (yes)
    if (ks_calculated_SHA256 == Stored-security-state?) then (yes)
      if (ks_cms_counter >= Keystore-counter?) then (yes)
        if (ks_cms_counter > Keystore-counter?) then (yes)
          :set ks_counter_updated flag;
        else (no)
        endif
        :parse keystore payload;
        if (success?) then (yes)
          :return success;
          stop
        else (no)
        endif
      else (no)
        :return failure;
        stop
      endif
    else (no)
      if (ks_cms_counter > Keystore-counter?) then (yes)
        if (is Keystore-xcs set?) then (no)
          :set ks_updated flag;
          :parse keystore payload;
          if (success?) then (yes)
            if (is cms_xcs set?) then (yes)
              :get SIMLock unlock status;
              if (is bootloader unlockable?) then (yes)
                :set ks_xcs_updated flag;
              else (no)
                :return failure;
                stop
              endif
            else (no)
            endif
            :return success;
            stop
          else (no)
            :return failure;
            stop
          endif
        else (yes)
        endif
      else (no)
        if (ks_cms_counter == Keystore-counter?) then (yes)
          if (Stored-security-state is empty?) then (yes)
            :set ks_updated flag;
            :parse keystore payload;
            if (success?) then (yes)
              :return success;
              stop
            else (no)
            endif
          else (no)
          endif
        else (no)
        endif
      endif
    endif
  else (no)
  endif
  :return failure;
  stop


.. _ks_load_keystore:

.. uml::
  :caption: ks_load_keystore(ks_partition)
  :align: center

  start
  :ks_load_keystore(ks_partition) is called;
  :call ks_check(ks_partition);
  if (success?) then (yes)
    :return success;
    stop
  else (no)
    if (ks_partition is xflkeystorebak?) then (yes)
      :return failure;
      stop
    else (no)
      :call ks_check(xflkeystorebak);
      if (success?) then (yes)
        :set ks_revert flag;
        :return success;
        stop
      else (no)
        :return failure;
        stop
      endif
    endif
  endif

.. note::
  How and when the variables mentioned in :ref:`ks_set_keystore`
  (update_hmac_key and hmac_key) are populated is explained in
  :ref:`deviceBinding-masking`.

.. _ks_set_keystore:

.. uml::
  :caption: ks_set_keystore(ks_ctx)
  :align: center

  start
  :ks_set_keystore() is called;
  if (is ks_revert set?) then (yes)
    :copy xflkeystorebak to xflkeystore;
    if (success?) then (no)
      :return failure;
      stop
    else (yes)
    endif
  else (no)
    if (are xflkeystore and xflkeystorebak identical?) then (no)
      :copy xflkeystore to xflkeystorebak;
      if (success?) then (no)
        :return failure;
        stop
      else (yes)
      endif
    else (yes)
    endif
  endif
  if (is ks_updated set?) then (yes)
    :set secure storage data;
    if (success?) then (no)
      :return failure;
      stop
    else (yes)
    endif
  else (no)
    if (is ks_counter_updated?) then (yes)
      :set secure storage data;
      if (success?) then (no)
        :return failure;
        stop
      else (yes)
      endif
    else (no)
    endif
  endif
  if (is update_hmac_key set?) then (yes)
    :copy hmac_key to MiscTA 66673;
  else (no)
  endif
  :return success;
  stop


.. _keystore_load:

.. uml::
  :caption: keystore_load
  :align: center

  start
  :call ks_load_keystore(xflkeystore);
  if (success?) then (yes)
    if (is ks_xcs_updated flag set?) then (yes)
      :erase userdata/DK, set TA_MASTER_RESET to 0x1,
      write recovery message to misc partition,
      reset rollback counters and lock bootloader;
      if (success?) then (yes)
        :return ks_set_keystore();
        stop
      else (no)
        :return failure;
        stop
      endif
    else (no)
      :return ks_set_keystore();
      stop
    endif
  else (no)
    :return failure;
    stop
  endif

