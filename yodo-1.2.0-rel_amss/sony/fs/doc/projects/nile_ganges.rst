Nile/Ganges
===========

This section describes the concrete implementation of security
features for the Nile/Ganges platform.

Domains
-------

The following domains, and corresponding trust anchors, are used:

+--------------+-----------------+---------------------+---+-------------------+
|Domain Name   |Signed Objects   |Trust anchor location|XCS|Comment            |
+==============+=================+=====================+===+===================+
|*Keystore*    || Sony keystore  || Hardcoded in       |NO || Self-signed      |
|              |                 || xboot, XFL         |   || certificate      |
+--------------+-----------------+---------------------+---+-------------------+
|*S1*          || HwConfig       || Hardcoded in       |NO || Certificates are |
|              || SIMLock,       || xboot, XFL, modem  |   || validated based  |
|              || RemoteLock,    ||                    |   || on CN            |
|              || FOTA           ||                    |   ||                  |
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
|              |                 |                     |   || contain more than|
|              |                 |                     |   || one certificate; |
|              |                 |                     |   || if it does, the  |
|              |                 |                     |   || behavior of the  |
|              |                 |                     |   || XFL is undefined |
+--------------+-----------------+---------------------+---+-------------------+
