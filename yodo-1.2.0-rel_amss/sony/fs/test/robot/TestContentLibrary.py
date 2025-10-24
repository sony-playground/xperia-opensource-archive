#!/usr/bin/env python3

import os.path
import subprocess
import sys
import filecmp
import csv
from TestContent import *
from Definitions import *
from RobotVariables import *

class TestContentLibrary:
	tc = TestContent()

	def __init__(self):
		print("TCL:Init Test Content Library")

	def setup_content(self, dut_state, sw_state):
		# Generate test content
		print("TCL:Generate test content")
		self.tc.setup_test_content(dut_state, sw_state)

	def compare_content(self, content, content_id, variant = VariantId.TCV_VALID):
		# Get test content for <content_id> with variant <variant>
		# and compare it with content
		print("TCL:Get test content for {}".format(content_id))

		if content_id == ContentId.DO_NOT_CARE:
			return

		test_content = self.tc.get_test_content(content_id, variant)
		print("TCL:Test content id {} is {}".format(content_id, test_content))

		if content != test_content:
			raise AssertionError("Expected content to be '%s' but was '%s'"
						% (test_content, content))

	def compare_range(self, content, content_id_min, content_id_max, variant = VariantId.TCV_VALID):
		# Get test content for <content_id> with variant <variant>
		# and compare it with content.
		# The value should be within range min..max
		print("TCL:Get test content for {}".format(content_id_min))

		if (content_id_min == ContentId.DO_NOT_CARE) and (content_id_max == ContentId.DO_NOT_CARE):
			return

		if (content_id_min == ContentId.DO_NOT_CARE):
			# No lower limit
			test_content_max = self.tc.get_test_content(content_id_max, variant)
			print("TCL:Test content id {} is {}".format(content_id_max, test_content_max))

			if content > test_content_max:
				raise AssertionError("Expected content to be max '%s' but was '%s'"
					% (test_content_max, content))
			return

		if (content_id_max == ContentId.DO_NOT_CARE):
			# No upper limit
			test_content_min = self.tc.get_test_content(content_id_min, variant)
			print("TCL:Test content id {} is {}".format(content_id_min, test_content_min))

			if content > test_content_max:
				raise AssertionError("Expected content to be max '%s' but was '%s'"
					% (test_content_max, content))
			return

		test_content_max = self.tc.get_test_content(content_id_max, variant)
		print("TCL:Test content id {} is {}".format(content_id_max, test_content_max))
		test_content_min = self.tc.get_test_content(content_id_min, variant)
		print("TCL:Test content id {} is {}".format(content_id_min, test_content_min))
		if (content > test_content_max) or (content < test_content_min):
			raise AssertionError("Expected content to be max '%s' and min '%s' but was '%s'"
				% (test_content_max, test_content_min, content))

	def compare_version(self, content, content_id, variant = VariantId.TCV_VALID):
		# Get test content for <content_id> with variant <variant>
		# and compare it with content.
		# Convert to uppercase and '_' to '-' and remove whitespace
		# Ignore any traling '-live' in test_content
		print("TCL:Get test content for {}".format(content_id))

		if content_id == ContentId.DO_NOT_CARE:
			return

		test_content = self.tc.get_test_content(content_id, variant)
		print("TCL:Test content id {} is {}".format(content_id, test_content))
		content = content.upper()
		content = content.replace("_","-")
		test_content = test_content.strip()
		test_content = test_content.ljust(len(content))

		if not test_content.startswith(content):
			raise AssertionError("Expected content to be '%s' but was '%s'"
				% (test_content, content))

	def compare_file_content(self, content_file, content_id, variant_id = VariantId.TCV_VALID):
		# Get test content file for <content_id> with variant <variant_id>
		# and compare it with content in content_file
		print("TCL:Get test content file for {}".format(content_id))

		test_content_file = self.tc.get_test_content(content_id, variant_id)
		print("TCL:Test content file id {} is {}".format(content_id, test_content_file))

		if not filecmp.cmp(content_file, test_content_file):
			raise AssertionError("Expected data in file '%s' differs from data in file '%s'"
				% (content_file, test_content_file))

	def compare_file_list(self, file_list, content_id, variant_id):
		# Compare items in list1 and list from content_id
		# Every item in list1 should be in list2 and vice versa.
		# Get test content file for <content_id> with variant <variant_id>
		# and compare it with content in content_file
		list1 = []
		with open(file_list, 'r') as csvfile:
			reader = csv.reader(csvfile, delimiter=',')
			for row in reader:
				list1 = row

		list2 = self.tc.get_test_content(content_id, variant_id)
		print("TCL:list1 is {}".format(list1))
		print("TCL:list2 is {}".format(list2))
		for partition1 in list1:
			if not partition1 in list2:
				raise AssertionError(partition1 + " is missing")
		for partition2 in list2:
			if not partition2 in list1:
				raise AssertionError(partition2 + " is missing")

	def get_file_name(self, content_id, variant_id = VariantId.TCV_VALID):
		# Get test content file for <content_id> with variant <variant_id>
		# and compare it with content in content_file
		global gFastbootResponse
		print("TCL:Get test content file for {}".format(content_id))

		gTCV.filename = self.tc.get_test_content(content_id, variant_id)
		print("TCL:Test content file id {} is {}".format(content_id, gTCV.filename))

if __name__ == '__main__':
	# This is just test code for the interface

	dut_state = DutState()
	dut_state.model = Model.KUMANO_CDB

	sw_state = SwState()
	sw_state.xflVersion = "XFL-SDM845-O-17"
	sw_state.bootVersion = "1310-7079_X_Boot_SDM845_LA1.0_O_39"
	sw_state.versionBaseband = "1311-5320_51.1.A.1.137"

	tcl = TestContentLibrary()
	tcl.setup_content(dut_state, sw_state)

	tcl.compare_content(Model.KUMANO_CDB, ContentId.TC_TA_PHONE_NAME, VariantId.TCV_VALID)

	tcl.compare_version("1310-7079", ContentId.TC_GETVAR_VERSION_BOOTLOADER, VariantId.TCV_VALID)

	tcl.get_file_name(ContentId.TC_SIGNATURE_FILE, VariantId.TCV_VALID)

	tcl.get_file_name(ContentId.TC_SIGNATURE_FILE, VariantId.TCV_INVALID)

	print("Test OK!")
