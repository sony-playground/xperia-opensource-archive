#!/usr/bin/env python

import fxtool
import sys
import time
from optparse import OptionParser, OptionGroup
from fxtool import FxToolError
from sys import stdout
from ctypes import *

# ----------------------------------------------
# MAIN
#

l_loader    = ''

def main():
  parser = OptionParser()
  parser.add_option("--fxlog", dest="fxtool_loglevel", type=int,
                    default=0,
                    help="FxTool log level [%default]", metavar="LEVEL")
  parser.add_option("-v", "--verbose", dest="quiet", action="store_false",
                    default=True,
                    help="Tell script to be more talkative")
  file_opts_group = OptionGroup(parser, "File options",
                    "These options controls which files are used.")
  file_opts_group.add_option("-l", "--loader", dest="loaderfile",
                    default=l_loader,
                    help="Loader to use", metavar="FILE")
  file_opts_group.add_option("--part-image", dest="partimage",
                    help="Partition image file to flash", metavar="FILE")
  parser.add_option_group(file_opts_group);

  com_opts_group = OptionGroup(parser, "Comm options",
       "These options controls various host to device communication details.")
  com_opts_group.add_option("-c", "--com", dest="com",
                    default='\\\\.\\USB1',
                    help="Primary communications node [%default]")
  com_opts_group.add_option("-o", "--timeout", dest="timeout", type="int",
                    default=20,
                    help="Timeout for connection. [%defaults]",
                    metavar="SEC")
  com_opts_group.add_option("-r", "--rom", dest="usebootrom",
                    action="store_true",
                    default=False,
                    help="Use boot ROM to download loader")
  parser.add_option_group(com_opts_group);
  (options, args) = parser.parse_args()

  if options.usebootrom:
    print "LoaderType 21, Sahara"
    f = fxtool.FxTool(21, options.fxtool_loglevel, None, options.quiet)
  else:
    print "LoaderType 27, SOMC Fastboot"
    f = fxtool.FxTool(27, options.fxtool_loglevel, None, options.quiet)

  try:
    f.connect(options.com, options.timeout, options.quiet)
  except FxToolError, e:
    print 'ERROR: Failed to connect.'

  print "Boot info:", f.getBootInfo(options.quiet)
  f.setGenericSetting('TIMEOUT=24000000')

  if options.usebootrom:
    lhandle = f.uploadFlashImage(options.loaderfile, options.quiet)
    try:
      f.activateLoader(lhandle, 21, '921600', options.quiet)
    except:
      print "Failed to execute preloader"
      f.releaseFlashImage(lhandle, options.quiet)
    else:
      f.releaseFlashImage(lhandle, options.quiet)
  else:
    f.setupSecs('http://safesemla.extranet.sonyericsson.com/dispatch', 0, options.quiet)
    f.setSecsServerProxy('http://proxy.global.sonyericsson.net:8080');

  if options.usebootrom:
    time.sleep(2);
    f.changeLoaderType(26, "TIMEOUT=\"10000\";MEMORY_NAME=\"ufs\";")

  ##### This produces lots of spam #####
  system_info = f.getSystemInfo(options.quiet)
  print 'system info: ', system_info

  if options.usebootrom:
    print 'Hard service'
    #fh = f.uploadFlashImageV2("xfl.000")
    #f.flashImageFromHandleWithParameters("PARTITION=\"4\";START_SECTOR=\"5671\";RETRIES=\"3\";", fh)
  else:
    print "Soft service"

    ##### Authenticate #####
    #f.authenticate("sake", options.quiet)

    ##### oem lock example ####
    #f.oemLock()

    ##### Prepare a file for flashing #####
    #fh = f.uploadFlashImageV2("xfl.sin")
    #fh = f.uploadFlashImageV2("/home/CORPUSERS/23059324/Downloads/partitions/lun2.sin")

    ######################################
    ##### Example of generic command #####
    ##### Transfer a file to device  #####
    ######################################
    #fp = open('random.bin', 'rb')
    #buf = fp.read()
    #f.genCommand2(1, "download:00100000", buf, 1048576, 100000 )
    #fp.close()

    #try:
      ##### Flash the file prepared, som examples #####
      #f.flashImageFromHandleWithParameters("PARTITION=\"bootloader\";", fh)
      #f.flashImageFromHandleWithParameters("FORMAT=\"SIN\";ERASE_TYPE=\"SECURE\";ERASE_TIMEOUT=\"10000000\";TRANSFER_TIMEOUT=\"12000000\";FLASH_TIMEOUT=\"18000000\";", fh)
      #f.flashImageFromHandleWithParameters("FORMAT=\"SIN\";ERASE_TYPE=\"NONE\";ERASE_TIMEOUT=\"10000000\";TRANSFER_TIMEOUT=\"12000000\";FLASH_TIMEOUT=\"18000000\";PARTITION=\"__GPT__:2\";", fh)

      ##### Dump a partition to file #####
      #f.dumpPartition("appslog.bin", "PARTITION=\"apps_log\";")

      ##### Read TA. Note taOpen must still be made to please fxtool  #####
      #f.taOpen(2)
      #f.taReadAll("allta.bin");

    #except:
    #f.getInfo("file.log", "TYPE=\"LOG\";")

  f.getInfo("file.log", "TYPE=\"LOG\";")
  ##### Probably the least useful command here #####
  #f.taClose()

  ##### Free up memory in fxtool #####
  #f.releaseFlashImage(fh, options.quiet)

  # Set which LUN is bootable
  if options.usebootrom:
    f.setBootable(1)

  ##### Will reboot device, usually quite annoying #####
  #f.reboot(0)


if __name__ == "__main__":
  try:
    sys.exit(main())
  except FxToolError, e:
    print e
  finally:
    print "Done. Please disconnect USB cable to prevent unit discharge."

