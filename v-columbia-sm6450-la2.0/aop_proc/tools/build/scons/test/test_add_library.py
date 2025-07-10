#===============================================================================
#
# Test scripts for the tools/build/scons/scripts/utils.py file.
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

        self.start_dir = os.getcwd()
        self.fake_env = None
        self.target_root = os.getcwd()
        self.image_dir = 'test_proc'
        self.buildpath = 'image/proc/variant'

        self.build_dir = self.image_dir + '/test/build'
        self.variant_dir = self.build_dir + '/' + self.buildpath

        self.dep_tree_src_only = {
                self.variant_dir + '/test.lib': [
                    self.variant_dir + '/test_1.o',
                    self.variant_dir + '/test_2.o',
                    self.variant_dir + '/test_3.o',
                    self.variant_dir + '/test_4.o'
                    ]
            }

        self.dep_tree_obj_only = {
                self.variant_dir + '/test.lib': [
                    self.variant_dir + '/test_1.o',
                    self.variant_dir + '/test_2.o',
                    self.variant_dir + '/test_3.o',
                    self.variant_dir + '/test_4.o'
                    ],
                self.variant_dir + '/test_1.o': [],  # This means the source doesn't ship
                self.variant_dir + '/test_2.o': [],   # This means the source doesn't ship
                self.variant_dir + '/test_3.o': [],  # This means the source doesn't ship
                self.variant_dir + '/test_4.o': []   # This means the source doesn't ship
            }

        self.dep_tree_lib_only = {
                self.variant_dir + '/test.lib': []
            }

        self.dep_tree_mixed = {
                self.variant_dir + '/test.lib': [
                    self.variant_dir + '/test_1.o',
                    self.variant_dir + '/test_2.o',
                    self.variant_dir + '/test_3.o',
                    self.variant_dir + '/test_4.o'
                    ],
                self.variant_dir + '/test_1.o': [],  # This means the source doesn't ship
                self.variant_dir + '/test_3.o': []   # This means the source doesn't ship
            }

    # End of TestApp.__init__()

    def setUp(self):
        LOG.info('')  # Needed because inittest doesn't add newline to initial message.
        LOG.info('=======================================================')
        LOG.info('Start of new Test Case:')
        self.fake_env = FakeSConsEnv()
        self.fake_env['BUILDPATH'] = self.buildpath
        self.fake_env['BINARY_BUILDPATH'] = self.buildpath
        self.fake_env['TARGET_ROOT'] = self.target_root
        self.fake_env['BUILD_ROOT'] = self.target_root + '/' + self.image_dir
        if not os.path.exists(self.build_dir):
            os.makedirs(self.build_dir)
        os.chdir(self.build_dir)
    # End of TestApp.setUp()

    def tearDown (self):
        self.fake_env = None
        os.chdir(self.start_dir)
        LOG.info('Completion of this Test Case')
        LOG.info('=======================================================')
    # End of TestApp.tearDown()

    def test_analyze_internal_build(self):

        LOG.info('Testing analyze internal build')

        self.fake_env['USES_NO_STRIP_NO_ODM'] = True  # Pretend we're an internal build.

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']
        result = self.fake_env.AnalyzeLibrary(library, sources, '.lib')

        # Verify no changes for internal builds
        self.assertEqual(result.library, library)
        self.assertEqual(result.sources, sources)
        self.assertEqual(result.build_as, 'library')

        LOG.info('Testing analyze internal build - Completed')

    # End of test_analyze_internal_build()

    def test_shared_library_on_cleanpack_build(self):
        'Test Shared Library on cleanpack build'

        LOG.info(TestApp.test_shared_library_on_cleanpack_build.__doc__)

        self.fake_env.SetOption('cleanpack', True)

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']

        # All files must exist for cleanpack test
        self.CreateFile(library + '.so')
        for src in sources:
            self.CreateFile(src)
        result = self.fake_env.AnalyzeLibrary(library, sources,
                                              libsuffix='.so', pack=True)

        # Verify changes for cleanpack build
        self.assertEqual(self.fake_env.subst(str(result.library)), self.fake_env.subst(library) + '_cleanpack.so')
        self.assertEqual(4, len(result.sources))
        self.assertEqual(result.build_as, 'already_a_node')

        LOG.info(TestApp.test_shared_library_on_cleanpack_build.__doc__ + ' - Completed')

    # End of test_shared_library_on_cleanpack_build()

    def test_compile_pack_build_with_dep_tree_src_only(self):
        'Test compiling a packed build with dependency tree'

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_src_only.__doc__)

        self.fake_env['DEPENDENCY_TREE_DATA'] = self.dep_tree_src_only

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']

        result = self.fake_env.AnalyzeLibrary(library, sources,
                                              libsuffix='.lib', pack=False)

        # Verify changes for depgen build
        self.assertEqual(result.library, library)
        self.assertEqual(4, len(result.sources))
        self.assertEqual(result.build_as, 'library')

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_src_only.__doc__ + ' - Completed')

    # End of test_compile_pack_build_with_dep_tree_src_only()

    def test_compile_pack_build_with_dep_tree_obj_only(self):
        'Test compiling a packed build with dependency tree with only object files'

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_obj_only.__doc__)

        self.fake_env['DEPENDENCY_TREE_DATA'] = self.dep_tree_obj_only

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']

        result = self.fake_env.AnalyzeLibrary(library, sources,
                                              libsuffix='.lib', pack=False)

        # Verify changes for depgen build
        self.assertEqual(result.library, library)
        self.assertEqual(8, len(result.sources))
        self.assertTrue(result.sources[0].endswith('test_1.c'))
        self.assertTrue(result.sources[1].endswith('test_2.c'))
        self.assertTrue(result.sources[2].endswith('test_3.c'))
        self.assertTrue(result.sources[3].endswith('test_4.c'))
        self.assertTrue(result.sources[4].endswith('test_1.o'))
        self.assertTrue(result.sources[5].endswith('test_2.o'))
        self.assertTrue(result.sources[6].endswith('test_3.o'))
        self.assertTrue(result.sources[7].endswith('test_4.o'))
        self.assertEqual(result.build_as, 'library')

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_obj_only.__doc__ + ' - Completed')

    # End of test_compile_pack_build_with_dep_tree_obj_only()

    def test_compile_pack_build_with_dep_tree_lib_only(self):
        'Test compiling a packed build with dependency tree with only lib files'

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_lib_only.__doc__)

        self.fake_env['DEPENDENCY_TREE_DATA'] = self.dep_tree_lib_only

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']

        result = self.fake_env.AnalyzeLibrary(library, sources,
                                              libsuffix='.lib', pack=False)

        # Verify changes for depgen build
        self.assertEqual(result.library, self.fake_env.subst(library) + '.lib')
        self.assertEqual(0, len(result.sources))
        self.assertEqual(result.build_as, 'file')

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_lib_only.__doc__ + ' - Completed')

    # End of test_compile_pack_build_with_dep_tree_lib_only()

    def test_compile_pack_build_with_dep_tree_mixed(self):
        'Test compiling a packed build with dependency tree with mixed source and object files'

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_mixed.__doc__)

        self.fake_env['DEPENDENCY_TREE_DATA'] = self.dep_tree_mixed

        library = '${BUILDPATH}/test'
        sources = ['${BUILDPATH}/test_1.c',
                   '${BUILDPATH}/test_2.c',
                   '${BUILDPATH}/test_3.c',
                   '${BUILDPATH}/test_4.c']

        result = self.fake_env.AnalyzeLibrary(library, sources,
                                              libsuffix='.lib', pack=False)

        # Verify changes for depgen build
        self.assertEqual(result.library, library)
        self.assertEqual(6, len(result.sources))
        self.assertTrue(result.sources[0].endswith('test_1.c'))
        self.assertTrue(result.sources[1].endswith('test_2.c'))
        self.assertTrue(result.sources[2].endswith('test_3.c'))
        self.assertTrue(result.sources[3].endswith('test_4.c'))
        self.assertTrue(result.sources[4].endswith('test_1.o'))
        self.assertTrue(result.sources[5].endswith('test_3.o'))
        self.assertEqual(result.build_as, 'library')

        LOG.info(TestApp.test_compile_pack_build_with_dep_tree_mixed.__doc__ + ' - Completed')

    # End of test_compile_pack_build_with_dep_tree_mixed()

    #===================================================
    # Support Functions
    #===================================================

    def CreateFile(self, filename):
        filename = self.fake_env.subst(filename)
        filepath = os.path.dirname(filename)
        if not os.path.exists(filepath):
            os.makedirs(filepath)
        with open(filename, 'w') as f:
            f.write(filename)
    # End of TestApp.CreateFile()

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

