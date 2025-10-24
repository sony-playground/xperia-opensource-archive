===================================
Flash SIN files
===================================

Introduction
============
Images which are flashed to the device may be signed with an external signature.
This transport signature is stored in a CMS file which is bundled together with
the image in a tar file.
The image may be split into several files. In this case the files are in
sparse format. The transport signature is calculated on all files and thus
protecting all of them.
The tar file is renamed to have the extension SIN.

Flash flow
==========

1. The host unpacks the sin file into a signature file (.cms) and one or more
   image files.
2. The signature file is downloaded to the device using the 'download' command.
3. The command 'signature' is then executed and the device verifies the
   signature.
4. If successful, the host erases the partition with the 'erase' command.
5. The host downloads the image file with the 'download' command.
6. The downloaded content is then flashed to the partition with the 'flash'
   command. If the image is split into several files, steps 5-6 are repeated
   until the whole image is flashed.

.. uml::
  :caption: Flash SIN files flow

  @startuml
  host -> XFL: Download signature
  XFL --> host: OKAY
  host -> XFL: Verify signature
  XFL --> host: OKAY
  host -> XFL: Erase partition
  XFL --> host: OKAY
  host -> XFL: Download partition image
  XFL --> host: OKAY
  host -> XFL: Flash partition
  XFL -> host: OKAY
  @enduml
