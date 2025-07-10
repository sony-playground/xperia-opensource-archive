#===============================================================================
#
# Test scripts for the tools/build/scons/scripts/swift_build_utils.py file.
#
#===============================================================================

import logging
LOG = logging.getLogger(__name__)
# LOG.setLevel(logging.INFO)

# Set logging defaults
logging.basicConfig(format=('%(levelname)s '
                            '%(filename)s '
                            '%(funcName)s() '
                            '%(message)s'), level=logging.DEBUG)

import unittest
import sys
import os

SWIFT_UTILS_DIR = os.path.join(os.path.dirname(__file__), '../scripts')
qcscons_lib_root = os.path.realpath(os.path.join(os.path.dirname(__file__), "../SCons/lib"))
sys.path.append(qcscons_lib_root)
sys.path.append(SWIFT_UTILS_DIR)

from SCons.Node import FS
import swift_build_utils
#MUTEX_DIR = os.path.join(UTILS_DIR, 'mp_mutexes')

#=================================
# Main test class
#=================================

class TestApp(unittest.TestCase):
    ''' Test cases are executed alphabetically.'''

    def __init__(self, testCaseNames):
        ''' Each test case specified below gets it instance of a unit
            test object with independent self definitions.
        '''
        super(TestApp, self).__init__(testCaseNames)

        self.swift_details_variant_dict = {
            "qswat_proc/build/ms/bin/sdx000.gen.test/sample": {
                "commands": [
                    "gcc -m32 --data-sections --machine=32 -L /local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/default -L /local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config -L /local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms -L /local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/bsp/../../scripts/bsp/sample_img/build -o \"qswat_proc/build/ms/bin/sdx000.gen.test/sample\" \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib\" \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms"
                ],
                "dependencies": [
                    "qswat_proc/scripts/bsp/sample_img/build/s_Under Action demo Linking timing_41a80e6d23e948ca9184a16bed27c352",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib",
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib"
                ],
                "dependents": [],
                "scanner": "",
                "sources": [],
                "targets": [
                    "qswat_proc/build/ms/bin/sdx000.gen.test/sample"
                ]
            },
            "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib": {
                "commands": [
                    "ar -r -c \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib\" \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o\" \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o\" \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o\" \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample/inc",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api"
                ],
                "dependencies": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o"
                ],
                "dependents": [
                    "qswat_proc/build/ms/bin/sdx000.gen.test/sample"
                ],
                "scanner": "None",
                "sources": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o",
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o"
                ],
                "targets": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib"
                ]
            },
            "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample/inc -Iqswat_proc/sample_red_r/api -c -o \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o\" \"qswat_proc/sample/csrc/sample-csrc.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample/inc",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api"
                ],
                "dependencies": [
                    "qswat_proc/sample/inc/sample.h"
                ],
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib"
                ],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample/csrc/sample-csrc.c"
                ],
                "targets": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o"
                ]
            },
            "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample/inc -Iqswat_proc/sample_red_r/api -c -o \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o\" \"qswat_proc/sample/dsrc/sample-dsrc.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample/inc",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api"
                ],
                "dependencies": [
                    "qswat_proc/sample/inc/sample.h"
                ],
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib"
                ],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample/dsrc/sample-dsrc.c"
                ],
                "targets": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o"
                ]
            },
            "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample/inc -Iqswat_proc/sample_red_r/api -c -o \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o\" \"qswat_proc/sample/src/main.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample/inc",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api"
                ],
                "dependencies": [
                    "qswat_proc/sample/inc/sample.h",
                    "qswat_proc/sample_red_r/api/sample_red.h"
                ],
                "dependents": [],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample/src/main.c"
                ],
                "targets": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o"
                ]
            },
            "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample/inc -Iqswat_proc/sample_red_r/api -c -o \"qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o\" \"qswat_proc/sample/src/sample.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample/inc",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api"
                ],
                "dependencies": [
                    "qswat_proc/sample/inc/sample.h"
                ],
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_LIB.lib"
                ],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample/src/sample.c"
                ],
                "targets": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o"
                ]
            },
            "qswat_proc/sample/csrc/sample-csrc.c": {
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/csrc/sample-csrc.o"
                ]
            },
            "qswat_proc/sample/dsrc/sample-dsrc.c": {
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/dsrc/sample-dsrc.o"
                ]
            },
            "qswat_proc/sample/src/main.c": {
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/main.o"
                ]
            },
            "qswat_proc/sample/src/sample.c": {
                "dependents": [
                    "qswat_proc/sample/build/sample/gcc_x86/sdx000.gen.test/src/sample.o"
                ]
            },
            "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib": {
                "commands": [
                    "ar -r -c \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib\" \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o\" \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o\" \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/inc"
                ],
                "dependencies": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o",
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o"
                ],
                "dependents": [
                    "qswat_proc/build/ms/bin/sdx000.gen.test/sample"
                ],
                "scanner": "None",
                "sources": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o",
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o",
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o"
                ],
                "targets": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib"
                ]
            },
            "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample_red_r/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample_red_r/api -Iqswat_proc/sample_red_r/inc -c -o \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o\" \"qswat_proc/sample_red_r/src/sample_green.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/inc"
                ],
                "dependencies": [
                    "qswat_proc/sample_red_r/api/sample_red.h",
                    "qswat_proc/sample_red_r/inc/sample_red_internal.h"
                ],
                "dependents": [],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample_red_r/src/sample_green.c"
                ],
                "targets": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o"
                ]
            },
            "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample_red_r/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample_red_r/api -Iqswat_proc/sample_red_r/inc -c -o \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o\" \"qswat_proc/sample_red_r/src/sample_red.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/inc"
                ],
                "dependencies": [
                    "qswat_proc/sample_red_r/api/sample_red.h",
                    "qswat_proc/sample_red_r/inc/sample_red_internal.h"
                ],
                "dependents": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib"
                ],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample_red_r/src/sample_red.c"
                ],
                "targets": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o"
                ]
            },
            "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o": {
                "commands": [
                    "gcc -g -m32 -Iqswat_proc/sample_red_r/build -Iqswat_proc/scripts/cust -Iqswat_proc/config/cust -Iqswat_proc/build/cust -Iqswat_proc/build/ms -Iqswat_proc/sample_red_r/api -Iqswat_proc/sample_red_r/inc -c -o \"qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o\" \"qswat_proc/sample_red_r/src/sample_yellow.c\""
                ],
                "cpppaths": [
                    ".",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/scripts/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/config/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/cust",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/build/ms",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/api",
                    "/local/mnt/workspace/sai/sprint159/testcases/qswat_proc/sample_red_r/inc"
                ],
                "dependencies": [
                    "qswat_proc/sample_red_r/api/sample_red.h",
                    "qswat_proc/sample_red_r/inc/sample_red_internal.h"
                ],
                "dependents": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/SAMPLE_RED_LIB.lib"
                ],
                "scanner": "CScanner",
                "sources": [
                    "qswat_proc/sample_red_r/src/sample_yellow.c"
                ],
                "targets": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o"
                ]
            },
            "qswat_proc/sample_red_r/src/sample_green.c": {
                "dependents": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_green.o"
                ]
            },
            "qswat_proc/sample_red_r/src/sample_red.c": {
                "dependents": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_red.o"
                ]
            },
            "qswat_proc/sample_red_r/src/sample_yellow.c": {
                "dependents": [
                    "qswat_proc/sample_red_r/build/sample/gcc_x86/sdx000.gen.test/sample_yellow.o"
                ]
            }
        }

    # End of TestApp.__init__()

    def setUp(self):
        LOG.info('')  # Needed because inittest doesn't add newline to initial message.
        LOG.info('=======================================================')
        LOG.info('Start of new Test Case:')
    # End of TestApp.setUp()

    def tearDown (self):
        LOG.info('Completion of this Test Case')
        LOG.info('=======================================================')
    # End of TestApp.tearDown()

    def test_get_all_related_dependents_for_c(self):
        LOG.info('Testing get_all_related_dependents function....')
        changed_file = "qswat_proc/sample/csrc/sample-csrc.c"
        c_related_dependencies = swift_build_utils.get_all_related_dependents(changed_file, self.swift_details_variant_dict)
        self.assertEqual(3, len(set(c_related_dependencies)))

    # End of test_get_all_related_dependents()

    def test_get_all_related_dependents_for_h(self):
        LOG.info('Testing get_all_related_dependents function....')
        changed_file = "qswat_proc/sample_red_r/api/sample_red.h"
        header_related_dependencies = swift_build_utils.get_all_related_dependents(changed_file, self.swift_details_variant_dict)
        self.assertEqual(8, len(set(header_related_dependencies)))

    # End of test_get_all_related_dependents()

# End of class TestApp


if __name__ == '__main__':
    LOG.info("Unittest args: " + ' '.join(sys.argv))
    LOG.info("Begining of the test suite:")
    LOG.info("===============================================")
    SUITE = unittest.TestLoader().loadTestsFromTestCase(TestApp)
    ret = unittest.TextTestRunner(verbosity=2).run(SUITE)
    # Print out the test results
    print(str(ret))
    if ret.printErrors() != None:
        print("Error: " + ret.printErrors())
    if ret.wasSuccessful():
        exit (0)
    else:
        exit (1)
