#!/usr/bin/env python
#===============================================================================
#
# Test scripts for the tools/build/scons/scripts/utils.py file.
#
#===============================================================================

import logging
LOG = logging.getLogger(__name__)

# Set logging defaults
logging.basicConfig(format=('%(levelname)s '
                            '%(filename)s '
                            '%(funcName)s() '
                            '%(message)s'), level=logging.DEBUG)

import unittest
import sys
import os
import subprocess
import re

import getpass

LOG.info("Cur user is: " + getpass.getuser())
LOG.info("Environment:")
for x in sorted(os.environ.keys()):
    LOG.info('   ' + x + ': ' + os.environ[x])

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

    def test_release_txt(self):

        LOG.info('Validating release.txt.')

        # Read the latest release.txt file
        LOG.info("Reading latest release.txt from P4")
        latest_rel_txt = self.__get_file_from_p4("//components/rel/scons.qc/3.0/release.txt")
        LOG.info("P4 has:")
        # [LOG.info('   ' + x) for x in latest_rel_txt.split('\n')]
        latest_rel_ver = self.__get_version(latest_rel_txt)
        LOG.info("P4 version is:  " + str(latest_rel_ver))

        # Read the local release.txt
        local_rel_txt_fn = os.path.join(os.path.dirname(__file__), '../release.txt')
        self.assertTrue(os.path.exists(local_rel_txt_fn))
        with open(local_rel_txt_fn, 'r') as f:
            local_rel_txt = ''.join(f.readlines())
        local_rel_ver = self.__get_version(local_rel_txt)
        LOG.info("Local version is:  " + str(local_rel_ver))

        self.assertEqual(local_rel_ver, latest_rel_ver+1)

        LOG.info('End validating release.txt.')

    # End test_action_binding

    #=================================
    # Support functions
    #=================================

    def __get_file_from_p4(self, fn):

        p4user = getpass.getuser()
        if p4user == 'qctecmdr':
            p4tickets_file = '/local/mnt/workspace/perforce/.p4tickets'
            if os.path.isfile(p4tickets_file):
                print "Found p4 tickets file at: " + p4tickets_file
            else:
                print "Couldn't find p4 tickets file at: " + p4tickets_file
            os.environ['P4TICKETS'] = p4tickets_file
            p4user = 'pwbldsvc'

        cmd = 'p4 -u {p4user} -p qctp401:1666 print -q {filename}'.format(filename=fn, p4user=p4user)
        LOG.info("Executing: " + cmd)
        file_contents = subprocess.check_output(cmd, shell=True)
        return file_contents

    # End of get_file_from_p4()

    def __get_version(self, release_txt_contents):

        match_obj = re.search('Release label: @scons.qc.3.0-(\d+)', release_txt_contents)
        match = match_obj.group(1)
        return int(match)

    # end of get_version()

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

