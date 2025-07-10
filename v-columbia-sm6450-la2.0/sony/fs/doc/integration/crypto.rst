======================
Crypto integration
======================

The FCS Main requires the following crypto funtionality in the integration system:

1. Digest functionality (*sha1/sha256*)

   **Defined in:** core/include/digest.h

   **Used by:**

     * boot
     * xfl
     * modem [#f4]_
     * Android

   **Currently supported implementations:**

     * openssl : integration/crypto/openssl/digest.c
     * boringssl : integration/crypto/openssl/digest.c
     * mbedtls : integration/crypto/mbedtls/digest.c

2. Signature verification *RSA PKCS1* and *RSASSA_PSS*

   **Defined in:** core/include/signature.h

   **Used by:**

     * boot
     * xfl
     * modem [#f4]_
     * Android

   **Currently supported implementations:**

     * openssl : integration/crypto/openssl/signature.c
     * boringssl : integration/crypto/openssl/signature.c
     * mbedtls : integration/crypto/mbedtls/signature.c


3. Certificate chain verification with customized extension handling [#f1]_:sup:`,` [#f2]_

   **Defined in:** core/include/certificate_chain.h

   **Used by:**

     * boot
     * xfl
     * modem [#f4]_
     * Android

   **Currently supported implementations:**

     * openssl : integration/crypto/openssl/certificate_chain.c, integration/crypto/openssl/rule.c
     * boringssl : integration/crypto/openssl/certificate_chain.c, integration/crypto/openssl/rule_boringssl.c [#f3]_
     * mbedtls : integration/crypto/mbedtls/certificate_chain.c, integration/crypto/mbedtls/rule.c

4. CMS verification

   **Defined in:** core/include/cms_verifier.h

   **Used by:**

     * boot
     * xfl
     * modem [#f4]_
     * (Android [#f4]_)

   **Currently supported implementations:**

     * openssl : core/cms/cms_verifier.c
     * boringssl : core/cms/cms_verifier_derparser.c core/cms/asn1pdu_cms.c
     * systems with functionality 1, 2, 3 (mbedtls): core/cms/cms_verifier_derparser.c core/cms/asn1pdu_cms.c

5. Raw RSA Encryption (in SAKE authentication)

   **Defined in:** loader/include/authenticate.h

   **Used by:**

     * boot
     * xfl

   **Currently supported implementations:**

     * openssl : integration/crypto/openssl/authenticate.c
     * mbedtls : integration/crypto/mbedtls/authenticate.c


.. [#f1] FSC uses proprietary extension to define certificate usage.

.. [#f2] This includes support for certificate parsing of custom extensions.

.. [#f3] The implementation is not thread safe.

.. [#f4] Yoshino/Tama uses legacy S1 solution and images in these environments.

