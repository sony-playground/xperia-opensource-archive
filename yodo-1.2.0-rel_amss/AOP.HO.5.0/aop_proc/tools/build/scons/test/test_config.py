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

from fake_scons_env import FakeSConsEnv

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

        self.fake_env = FakeSConsEnv()
        self.api_name = "AT_PUBLIC"
        self.api_env = {self.api_name:''}
        self.paths = ['${QMIMSGS_ROOT}/common/api',
                      ['${QMIMSGS_ROOT}/common/api', ['${QMIMSGS_ROOT}/common/api', '$(QMIMSGS_ROOT)/at/api'],
                       '$(QMIMSGS_ROOT)/at/api'],
                       '${QMIMSGS_ROOT}/at/api']
        self.publish_file = "C:\\Temp\\test.txt"

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

    def test_publish_api(self):
        LOG.info('Testing publish api to discard $( in the paths in a nested list from being added'
                 ' to the api env')
        self.fake_env.publish_api(self.api_env, self.api_name, self.paths, self.publish_file)
        result_data = self.api_env
        expected_data = {'AT_PUBLIC': '', 'UNKNOWN_AT_PUBLIC': ['${QMIMSGS_ROOT}/common/api',
                                                                ['${QMIMSGS_ROOT}/common/api',
                                                                 ['${QMIMSGS_ROOT}/common/api']],
                                                                '${QMIMSGS_ROOT}/at/api']}
        self.assertEqual(result_data, expected_data, msg="result is not as expected.\nExpected:\n"
                         + str(expected_data) + "\nFound:\n" + str(result_data))

    # End of test_publish_api()

    def test_publish_api_with_area(self):

        LOG.info("Testing publish api with the 'area' parameter")
        api_env = {}
        api_name = "NAME_PUBLIC"
        api_paths = ['path1', 'path2']
        area = "AREA"
        self.fake_env.publish_api(api_env, api_name, api_paths,
                                  self.publish_file, area)
        self.assertTrue('AREA_NAME_PUBLIC' in api_env)
        self.assertEqual(api_env['AREA_NAME_PUBLIC'], api_paths)

    # End of test_publish_api()

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
