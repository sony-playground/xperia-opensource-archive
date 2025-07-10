Basic Parameters
================

* All signing keys MUST be RSA keys with a 2048/4096-bit modulus (*n*),
  and the public exponent (*e*) MUST be 65537 (0x10001).
* All hashes/digests MUST use full-length (non-truncated) *SHA-256*.
* All signatures SHOULD use the *RSASSA-PSS* scheme, as described in
  [RFC3447]_ or [PKCS1]_\ [#pkcs1]_.


.. rubric:: Footnotes

.. [#pkcs1] Although PKCS#1 version 2.2 supersedes RFC3447, the two
            specifications are equivalent for the purposes described
            in this document.
