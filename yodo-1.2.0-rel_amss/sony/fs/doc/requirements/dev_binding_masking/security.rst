Security Analysis
=================

SHA-256 has\ [#sha256]_ the following properties, common for
cryptograhic hashes [HAC]_:

Preimage Resistance
   For essentially all pre-specified outputs, it is computationally
   infeasible to find any input which hashes to that output, i.e., to
   find any preimage :math:`x'` such that :math:`h(x') = y` when given
   any :math:`y` for which a corresponding input is not known

2nd-preimage Resistance
   It is computationally infeasible to find any second input which has
   the same output as any specified input, i.e., given :math:`x`, to
   find a 2nd-preimage :math:`x' /= x` such that :math:`h(x) = h(x')`.

Collision Resistance
   It is computationally infeasible to find any two distinct inputs
   :math:`x, x'` which hash to the same output, i.e., such that
   :math:`h(x) = h(x')`. (Note that here there is free choice of both
   inputs.)

Considering the basic requirements from section :ref:`requirements`,
the *Preimage Resistance* property effectively hides the original
Device Binding. The *Collision Resistance*, and the *2nd-preimage
Resistance* that follows from it [HASH]_, ensures that one Key Blob
cannot be used for multiple devices.

The HMAC construction, while not strictly required to fulfill these
requirements, was chosen as a standard way of securely combining a key
and a message. In that sense, HMAC acts more like a PRF [PRF]_, rather
than a MAC. Assuming that SHA-256 is a PRF, the HMAC construction is a
PRF as well, as shown by [HMAC-PRF]_.

.. rubric:: Footnotes

.. [#sha256] Even though this has never been proven, it is widely
             believed to be true in practice
