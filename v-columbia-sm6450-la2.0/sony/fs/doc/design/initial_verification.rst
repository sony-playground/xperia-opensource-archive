====================
Initial verification
====================

Introduction
============
Initial verification serves two purposes. One is to prevent unintended data to
be flashed onto a device. Unintented in this case means images other than the
ones signed by the issuer of the images.
The other purpose is to detect possible errors, such as bit flips, that might
have happened to the images, or if they have been subject of tampering.

Requirements
============
If a signature command is sent to the device it will perform the initial
verification. If there is an error the flashing must be aborted.

Implementation
==============
There are three scenarios to consider:

 * File is smaller than or equal to the max download size. In this case there
   is one hash in the hash-list and one payload.
 * File is larger than max download size. In this case there are n hashes in the
   hash-list and n payloads.
 * File is small enough but still divided into multiple payloads, so it's equal
   to scenario with n hashes and payloads.

Every "sin-file" contains a hash list with one or more hashes. Each hash is
a sha256 over a payload, which has to be positively matched to the corresponding
hash in the list in order to pass initial verification. Once initial
verification is done the flashing of the payload can commence, or continue.
By design it does not prevent the partition to be erased before entire payload
is verified to be OK, so it cannot be said that initial verification prevents
devices from being reduced to a brick state.
