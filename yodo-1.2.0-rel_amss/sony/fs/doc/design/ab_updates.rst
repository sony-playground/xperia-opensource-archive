===========
A/B Updates
===========

Introduction
============

A/B updates is an OTA (Over The Air) update feature designed to make your
device always have a working bootable software. Apart from logic handling
the feature, it also requires several partitions to exist in pairs, one 'a'
and one 'b' version respectively. These additional partitions along with the
extra logic puts a demand on the flash loader to manage some cases that might
occur.

How these 'a' and 'b' partitions are used (which partition is flashed and when)
is outside the scope of this document as it is not up to the flash loader to
make those decisions, but rather up to the host tool on the PC.

Terminology
===========

  * Two sets of partitions are referred to as slots, and they are normally
    called A and B. The system will run on one slot - current slot - and the
    remaining slots are considered inactive.

Pre-requisites and requirements
===============================

For any of the A/B commands or A/B logic to be put into effect, the following
requirement must be fulfilled.

  * Partition layout must have both A and B partitions of relevant partitions
    (minimum boot, system, and bootloader partitions).

For products based on Qualcomm platforms this additional requirement must be
fulfilled:

  * GUID Partition Table (GPT) must be used on the device.

For products based on Mediatek platforms this additional requirement must be
fulfilled:

  * Partition layout must contain a partition called "para".

If abovementioned is not fulfilled the A/B-commands will be unsupported.

Setting active slot
===================

When the command set_active is called with argument 'a' or 'b', the given slot
will be considered active by the flash loader immediately and by the bootloader
after a power cycle.

The flash loader will set target slot (boot and xfl partitions) as active and
bootable. It will clear the unbootable flag if it's there and also reset the
retry count to default value. Any other slot will also be set as inactive.
If a slot is active, the bootloader will only boot contents of that slot
irrespective of boot mode (normal mode, service mode or any other mode).

Additionally, in projects based on Qualcomm platforms, the flash loader will
swap the GUID TYPEs between all "a/b" partitions if needed. That should result
in all inactive slot partitions having the same GUID TYPE, and all active slot
partitions having different GUID TYPES.

  * On eMMC devices slot selection is done differently depending on who the
    vendor is. On Qualcomm platforms the bootrom finds the first partition to
    load from flash based on the GUID TYPE and the bootloader will find the
    next partition to boot based on GUID TYPE as well. On Mediatek platforms
    the bootrom will first load the preloader from the active boot partition
    (as set in the eCSD). The preloader will then find which slot to use by
    reading boot configuration metadata stored in the "para" partition and
    load the boot images from the corresponding partitions.

  * On UFS devices a slot will be associated with a LUN, which tells the
    bootrom where to look for the first partition to load from flash. When
    slot A is active the bootrom will load the first partition (xbl) from LUN1
    and when slot B is active it will load from LUN2 instead.
    Just as on Qualcomm eMMC devices, the bootloader partitions are identified
    by their GUID TYPE. Since the first boot step on flash is on its own device
    the GUID TYPE need not be changed for that partition.

Impact on device
================

There are no longer backup partitions for each partition included in the boot
loader, and consequently the device will depend on how the host decides to do
a boot upgrade.
For safest update the host should flash an inactive slot with a known good
boot followed by a "set_active" command for that slot. That way in the
happenstance of a sudden power loss or kernel panic the device will make it
into service mode despite incomplete flashing of bootloader. In other words
there is a risk involved while updating the bootloader in current active slot.
