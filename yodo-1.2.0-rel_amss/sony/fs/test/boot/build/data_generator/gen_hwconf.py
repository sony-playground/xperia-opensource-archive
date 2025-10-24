#!/usr/bin/env python

import sys

from data_generator import DataGenerator

def main():
	quiet = True

	dg = DataGenerator()

	if (len(sys.argv) < 5):
		print "Please provide platform name, defsec, devid, phoneid1 [,phoneId2] !"
		dg.printPlatforms()
		assert(0)

	platform = sys.argv[1]
	if len(sys.argv) == 5:
		dev_info = { "defsec":sys.argv[2], "devid":sys.argv[3], "phoneid1":sys.argv[4] }
	else:
		dev_info = { "defsec":sys.argv[2], "devid":sys.argv[3], "phoneid1":sys.argv[4], "phoneid2":sys.argv[5] }

	dg.getPlatform(platform)

	print "Generating HW config for platform " + sys.argv[1]
	print "DefSec ", dev_info["defsec"]
	print "DevID ", dev_info["devid"]
	print "PhoneID1 ", dev_info["phoneid1"]
	if (len(dev_info) == 4):
		print "PhoneID2 ", dev_info["phoneid2"]

	f = open('hwconf.hex', 'w')

	dg.getSignedHWConfigNormal(dev_info, platform, quiet)
	dg.saveResult2File(f)

	f.close

if __name__ == "__main__":
	try:
		sys.exit(main())
	finally:
		print "Done."
