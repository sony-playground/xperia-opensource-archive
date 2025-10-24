************
Startup Flow
************

1. General kernel startup.

2. AndroidInit: <fs/ramdisk>/android/<platform>/loader.init.rc

3. AndroidInit: Run XFL service. Entry point in
   <fs/main>/integration/linux/main.c

4. XFL service: Init crypto library if needed.

5. XFL service: Setup emmc/ufs block driver.

6. XFL service: Setup TA.

7. XFL service: Open host communication channel.

8. XFL service: Init OTP write.

   - Platform specific. Stub at bring up.
   - QC: Load TZ application, tzloader, from the flash partition tzxfl into
     ramdisk.
   - QC: Open TZ communication channel (QSee) to Fuse application.

9. XFL service: Read secure property.

   - Platform specific. Stub at bring up.
   - MTK: Load TZ application, tzxflattest, from the flash partition tzxflattest
     into ramdisk.
   - QC: The TZ application, tzxflattest, is already loaded by the bootloader.
   - Open TZ communication channel (QC: QSee) to tzxflattest application.
   - Read property

10. XFL service: Setup Display. Stubbed if no display support.

11. XFL service: Main loop

