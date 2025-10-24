Huaihe
======

This section describes the concrete implementation of security
features for the Huaihe platform.

Domains
-------

The following domains, and corresponding trust anchors, are used:

+--------------+-----------------+---------------------+---+-------------------+
|Domain Name   |Signed Objects   |Trust anchor location|XCS|Comment            |
+==============+=================+=====================+===+===================+
+--------------+-----------------+---------------------+---+-------------------+
|*Config*      || HwConfig,      || Hardcoded in       |NO || Certificates are |
|              || SIMLock,       || xboot, XFL,        |   || validated based  |
|              || Keystore       || modem (not         |   || on Sony          |
|              ||                || Keystore)          |   || certificates     |
|              ||                ||                    |   || extensions and   |
|              ||                ||                    |   || CMS attributes   |
+--------------+-----------------+---------------------+---+-------------------+
|*XFL*         || XFL            || Hardcoded in xboot |NO || Google/Qualcomm  |
|              |                 |                     |   || certificate      |
|              |                 |                     |   || format; may not  |
|              |                 |                     |   || use Sony         |
|              |                 |                     |   || certificate      |
|              |                 |                     |   || extensions       |
+--------------+-----------------+---------------------+---+-------------------+
|*SAKE*        || XFL SAKE       || Hardcoded in XFL   |NO || Public key; no   |
|              || authentication |                     |   || certificate      |
|              || response       |                     |   |                   |
+--------------+-----------------+---------------------+---+-------------------+
|*Flash*       || Flashable      || Dynamic keystore,  |YES|                   |
|              || images         || domain 0           |   |                   |
+--------------+-----------------+---------------------+---+-------------------+
|*Kernel*      || Android kernel,|| Dynamic keystore,  |YES|| Google/Qualcomm  |
|              || Ramdumper      || domain 1           |   || certificate      |
|              |                 |                     |   || format; may not  |
|              |                 |                     |   || use Sony         |
|              |                 |                     |   || certificate      |
|              |                 |                     |   || extensions       |
+--------------+-----------------+---------------------+---+-------------------+
|N/A           || N/A            || Dynamic keystore,  |N/A|| Deleted FOTA     |
|              |                 || domain 2           |   || keystore domain; |
|              |                 |                     |   || **DO NOT REUSE** |
+--------------+-----------------+---------------------+---+-------------------+
|*XFL Dynamic* || XFL            || Dynamic keystore,  |NO || Certificates     |
|              |                 || domain 3           |   || added in this    |
|              |                 |                     |   || domain will be   |
|              |                 |                     |   || checked in       |
|              |                 |                     |   || addition to the  |
|              |                 |                     |   || hardcoded        |
|              |                 |                     |   || certificate in   |
|              |                 |                     |   || the *XFL* domain |
+--------------+-----------------+---------------------+---+-------------------+
|*SAKE Dynamic*|| XFL SAKE       || Dynamic keystore,  |NO || A certificate    |
|              || authentication || domain 4           |   || added in this    |
|              || response       |                     |   || domain will      |
|              |                 |                     |   || override the     |
|              |                 |                     |   || hardcoded key in |
|              |                 |                     |   || the *SAKE* domain|
|              |                 |                     |   ||                  |
|              |                 |                     |   || This domain      |
|              |                 |                     |   || SHOULD NOT       |
|              |                 |                     |   || contain more     |
|              |                 |                     |   || than one         |
|              |                 |                     |   || certificate; if  |
|              |                 |                     |   || it does, the     |
|              |                 |                     |   || behavior of the  |
|              |                 |                     |   || XFL is undefined |
+--------------+-----------------+---------------------+---+-------------------+
|*VBMeta*      || vbmeta image   || Dynamic keystore,  |YES|| A public key     |
|              |                 || domain 5           |   || added in this    |
|              |                 |                     |   || domain will be   |
|              |                 |                     |   || used to verify   |
|              |                 |                     |   || the vbmeta image |
|              |                 |                     |   ||                  |
|              |                 |                     |   || The bootloader   |
|              |                 |                     |   || must test all    |
|              |                 |                     |   || keys in this     |
|              |                 |                     |   || domain before    |
|              |                 |                     |   || aborting with an |
|              |                 |                     |   || error            |
+--------------+-----------------+---------------------+---+-------------------+

Partition consideration
-----------------------

+---------------+------------------------------------+---------------------------------+
|Partition Name | Description                        | Comment                         |
+===============+====================================+=================================+
+---------------+------------------------------------+---------------------------------+
|*para*         || Contains all A/B slot handling    || Erasing the para partition     |
|               || information (retry count, active  || in XFL is not a valid use      |
|               || slot, magic number etc.)          || case since the A/B slot        |
|               |                                    || information is needed for      |
|               |                                    || the XFL to function. Erasing   |
|               |                                    || it causes errors on subsequent |
|               |                                    || erase and flash operations     |
|               |                                    || since the para partition magic |
|               |                                    || number cannot be verified.     |
|               |                                    ||                                |
|               |                                    || If A/B slot information is     |
|               |                                    || missing in the partition it    |
|               |                                    || will be generated on the       |
|               |                                    || next reboot.                   |
+---------------+------------------------------------+---------------------------------+
