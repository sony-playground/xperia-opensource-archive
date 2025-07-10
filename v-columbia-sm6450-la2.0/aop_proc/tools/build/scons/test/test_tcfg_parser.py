#===============================================================================
#
# Test scripts for the tools/build/scons/scripts/config.py file.
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
from cStringIO import StringIO

sys.path.insert(0, '../tcfg')
import tcfgparser


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

    def test_ParseTagMap_legacy(self):
        LOG.info('Testing parsing a tab map with variant name only')

        tag_map = tcfgparser.TagMap()

        # Tag map came from:
        #     //components/rel/boot.sbl/4.1.c1/boot_images/build/ms/common.target.builds#1
        build_file_str = ''' {
H0:     MSM Identifier
H1:     Platform Identifier
H2:     RAM Config
H3:     Flash Config
H4:     RF Config
S1:     Air Interface
S2,3:   Application Features
S4:     Image Type }
'''

        build_file = tcfgparser.Tokenizer(StringIO(build_file_str),
                                          'no_name_string_stream')
        tag_map.ParseTagMap(build_file)
        print(tag_map.DumpObjToStr(tag_map))

        self.assertEqual(len(tag_map.Elements), 8)

        self.assertEqual(tag_map.Elements[0].name, 'msm identifier')
        self.assertEqual(tag_map.Elements[0].start, 0)
        self.assertEqual(tag_map.Elements[0].end, 1)

        self.assertEqual(tag_map.Elements[1].name, 'platform identifier')
        self.assertEqual(tag_map.Elements[1].start, 1)
        self.assertEqual(tag_map.Elements[1].end, 2)

        self.assertEqual(tag_map.Elements[6].name, 'application features')
        self.assertEqual(tag_map.Elements[6].start,6)
        self.assertEqual(tag_map.Elements[6].end, 8)

        self.assertEqual(tag_map.Elements[7].name, 'image type')
        self.assertEqual(tag_map.Elements[7].start, 8)
        self.assertEqual(tag_map.Elements[7].end, 9)

    # End of test_ParseTagMap_legacy()

    def test_ParseTagMap_variant_name_only(self):
        LOG.info('Testing parsing a tab map with variant name only')

        tag_map = tcfgparser.TagMap()

        build_file_str = ''' {
   S0,+: Build Variant
}
'''

        build_file = tcfgparser.Tokenizer(StringIO(build_file_str),
                                          'no_name_string_stream')
        tag_map.ParseTagMap(build_file)
        print(tag_map.DumpObjToStr(tag_map))

        self.assertEqual(len(tag_map.Elements), 1)

        self.assertEqual(tag_map.Elements[0].name, 'build variant')
        self.assertEqual(tag_map.Elements[0].start, 0)
        self.assertIsNone(tag_map.Elements[0].end)

    # End of test_ParseTagMap_variant_name_only()

    def test_ParseTagMap_variant_name_and_image(self):
        LOG.info('Testing parsing a tab map with variant name only')

        tag_map = tcfgparser.TagMap()

        build_file_str = ''' {
  S0,-: Build Variant
  S8: Image Type
}
'''

        build_file = tcfgparser.Tokenizer(StringIO(build_file_str),
                                          'no_name_string_stream')
        tag_map.ParseTagMap(build_file)
        print(tag_map.DumpObjToStr(tag_map))

        self.assertEqual(len(tag_map.Elements), 2)

        self.assertEqual(tag_map.Elements[0].name, 'build variant')
        self.assertEqual(tag_map.Elements[0].start, 0)
        self.assertEqual(tag_map.Elements[0].end, -1)

        self.assertEqual(tag_map.Elements[1].name, 'image type')
        self.assertEqual(tag_map.Elements[1].start, -1)
        self.assertIsNone(tag_map.Elements[1].end)

    # End of test_ParseTagMap_variant_name_and_image()

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
