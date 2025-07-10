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
import inspect
import subprocess
import json
import time
import threading
import Queue
from collections import OrderedDict

from fake_scons_env import FakeSConsEnv

#=================================
# Global variables
#=================================

UTILS_DIR = os.path.join(os.path.dirname(__file__), '../scripts')
MUTEX_DIR = os.path.join(UTILS_DIR, 'mp_mutexes')
TEST_MUTEX_NAME = 'test_mutex'
TEST_MUTEX_FILE = os.path.join(MUTEX_DIR, TEST_MUTEX_NAME + '.mpmutex')
TEST_BUILD_ID = '8998.gen.prod'
IMAGE_INFO_FILE = 'modem_proc/image_info.json'

#=================================
# Helper functions
#=================================

def decode_odict(data):
    ''' Add data to a new ordered dict and return. '''
    ordered_data = OrderedDict(data)
    return ordered_data

def json_load(file_name):
    with open(file_name, 'r') as fh:
        return json.load(fh, object_pairs_hook = decode_odict)

def json_loads(json_str):
    return json.loads(json_str, object_pairs_hook = decode_odict)

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

        self.fake_env = FakeSConsEnv(build_id=TEST_BUILD_ID)

        # image_info_writer expects a modem_proc directory, so create one if
        # one doesn't already exist.
        if not os.path.isdir('modem_proc'):
            os.makedirs('modem_proc')

    # End of TestApp.__init__()

    def setUp(self):
        LOG.info('')  # Needed because inittest doesn't add newline to initial message.
        LOG.info('=======================================================')
        LOG.info('Start of new Test Case:')
        if os.path.exists(IMAGE_INFO_FILE):
            os.remove(IMAGE_INFO_FILE)
    # End of TestApp.setUp()

    def tearDown (self):
        LOG.info('Completion of this Test Case')
        LOG.info('=======================================================')
    # End of TestApp.tearDown()

    def test_writing_to_image_info_file(self):

        LOG.info('Testing Writing to Image Info file')

        self.fake_env['USES_NO_STRIP_NO_ODM'] = True  # Pretend we're an internal build.

        self.fake_env.WriteImageInfo('basic_int', 5)
        self.fake_env.WriteImageInfo('basic_string', "hi-mom")
        self.fake_env.WriteImageInfo('basic_string_with_space', "hi mom")
        self.fake_env.WriteImageInfo('basic_list', ["this", "is", "a", "list"])
        self.fake_env.WriteImageInfo('basic_dict', {'this': "is", "a": "dict"})
        self.fake_env.WriteImageInfo('complex_struct',
                                     {'this': ["is", "a"], "dict": ["of", "lists"]})
        fake_env_2 = FakeSConsEnv(build_id='Another_Variant')
        fake_env_2['USES_NO_STRIP_NO_ODM'] = True  # Pretend we're an internal build.
        fake_env_2.WriteImageInfo('complex_struct',
                                     {'this': ["is", "a"], "dict": ["of", "lists"]})

        self.assertTrue(os.path.exists(IMAGE_INFO_FILE))
        result_data = json_load(IMAGE_INFO_FILE)
        expected_data = json_loads('''{
                                        "version" : "1.0",
                                        "variant_info" : {
                                          "8998.gen.prod" : {
                                            "basic_int" : 5,
                                            "basic_string" : "hi-mom",
                                            "basic_string_with_space" : "hi mom",
                                            "basic_list" : [
                                              "this",
                                              "is",
                                              "a",
                                              "list"
                                            ],
                                            "basic_dict" : {
                                              "this" : "is",
                                              "a" : "dict"
                                            },
                                            "complex_struct" : {
                                              "this" : [
                                                "is",
                                                "a"
                                              ],
                                              "dict" : [
                                                "of",
                                                "lists"
                                              ]
                                            }
                                          },
                                          "Another_Variant" : {
                                            "complex_struct" : {
                                              "this" : [
                                                "is",
                                                "a"
                                              ],
                                              "dict" : [
                                                "of",
                                                "lists"
                                              ]
                                            }
                                          }
                                        }
                                      }''')
        self.assertEqual(result_data, expected_data,
                         msg="image_info.json file is not as expected.\nExpected:\n"
                         + str(expected_data) + "\nFound:\n" + str(result_data))

        LOG.info("Test operation on customer builds")
        del self.fake_env['USES_NO_STRIP_NO_ODM']    # Pretend we're a customer build.
        self.fake_env.WriteImageInfo('basic_int', 5)
        # Verify that the contents of the image_info.json file are unchanged from
        # by the last write.
        self.assertTrue(os.path.exists(IMAGE_INFO_FILE))
        result_data = json_load(IMAGE_INFO_FILE)
        self.assertEqual(result_data, expected_data,
                         msg="image_info.json file is not as expected.\nExpected:\n"
                         + str(expected_data) + "\nFound:\n" + str(result_data))

        LOG.info('Testing Testing Writing to Image Info file - Completed')

    # End of test_writing_to_image_info_file()

    def test_mp_mutex(self):

        LOG.info('Testing SCons Multi-Processor Mutex')

        # clean up from previous failed tests just in case.
        if os.path.exists(TEST_MUTEX_FILE):
            os.remove(TEST_MUTEX_FILE)

        pid = os.getpid()
        thread = threading.current_thread()
        tid = thread.ident if thread is not None else -1

        # ===================================================
        LOG.info("Test acquiring mutex.")

        self.fake_env.AcquireMPMutex(TEST_MUTEX_NAME)

        self.assert_mutex_owner(pid, tid)

        # ===================================================
        LOG.info("Test re-acquiring mutex.")

        self.fake_env.AcquireMPMutex(TEST_MUTEX_NAME)

        self.assert_mutex_owner(pid, tid)

        # ===================================================
        LOG.info("Test releasing mutex.")

        # Try to release it.  Should succeed.
        self.fake_env.ReleaseMPMutex(TEST_MUTEX_NAME)
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        # ===================================================
        LOG.info("Test overwriting zombie mutex file.")

        # Write fake mutex file with fake pid, and make sure env.AcquireMPMutex()
        # correctly replaces the file with it's own.

        with open(TEST_MUTEX_FILE, 'w') as mfh:
            mfh.write('{"pid": 54321, "tid": 12345, "aquire_date_time": "Fri Mar 17 22:06:27 2017"}')

        self.fake_env.AcquireMPMutex(TEST_MUTEX_NAME)

        self.assert_mutex_owner(pid, tid)

        self.fake_env.ReleaseMPMutex(TEST_MUTEX_NAME)
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        # Now do the same with the current tid but wrong pid
        with open(TEST_MUTEX_FILE, 'w') as mfh:
            mfh.write('{"pid": 54321, "tid": %d, "aquire_date_time": "Fri Mar 17 22:06:27 2017"}' % tid)

        self.fake_env.AcquireMPMutex(TEST_MUTEX_NAME)

        self.assert_mutex_owner(pid, tid)

        self.fake_env.ReleaseMPMutex(TEST_MUTEX_NAME)
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))


        # ===================================================
        LOG.info("Test waiting for mutex availability.")

        p1 = subprocess.Popen(['python', 'do_from_another_process.py'],
                              stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)
        p2 = subprocess.Popen(['python', 'do_from_another_process.py'],
                              stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)

        # first line of output from subprocess will be thread id
        self.write_to_subprocess(p1, "PrintThreadId")
        p1.stdout.readline()
        p1.stdout.readline()
        p1Tid = int(p1.stdout.readline().strip())
        self.write_to_subprocess(p2, "PrintThreadId")
        p2.stdout.readline()
        p2.stdout.readline()
        p2Tid = int(p2.stdout.readline().strip())

        self.write_to_subprocess(p1, "AcquireMPMutex " + TEST_MUTEX_NAME)
        time.sleep(3)
        self.assert_mutex_owner(p1.pid, p1Tid)

        self.write_to_subprocess(p2, "AcquireMPMutex " + TEST_MUTEX_NAME)
        time.sleep(3)
        self.assert_mutex_owner(p1.pid, p1Tid)   # p1 should still own the mutex

        self.write_to_subprocess(p1, "ReleaseMPMutex " + TEST_MUTEX_NAME)
        time.sleep(4)
        self.assert_mutex_owner(p2.pid, p2Tid)   # p2 should now get the mutex

        self.write_to_subprocess(p2, "ReleaseMPMutex " + TEST_MUTEX_NAME)
        time.sleep(3)
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        self.write_to_subprocess(p1, "Quit")
        self.write_to_subprocess(p2, "Quit")
        p1.wait()
        p2.wait()
        self.assertEqual(p1.returncode, 0)
        self.assertEqual(p2.returncode, 0)

        # ===================================================
        LOG.info("Test mutex timeout warnings.")

        # Run test to make sure our warning message is being sent to STDOUT if
        # a semaphore hasn't been freed withing the specified timeout.
        p1 = subprocess.Popen(['python', 'do_from_another_process.py'],
                              stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)

        self.write_to_subprocess(p1, "SetEnvVarInt SCONS_MUTEX_TIMEOUT_PERIOD 1")
        self.write_to_subprocess(p1, "AcquireMPMutex " + TEST_MUTEX_NAME)
        time.sleep(3)
        output = [p1.stdout.readline(80).strip() for x in range(7)]

        # Skip extraneous output
        self.assertEqual(output[6],
                         "!! WARNING: A mutex named 'test_mutex' has not been freed.")
        self.write_to_subprocess(p1, "ReleaseMPMutex " + TEST_MUTEX_NAME)
        self.write_to_subprocess(p1, "Quit")
        p1.wait()
        self.assertEqual(p1.returncode, 0)

        # ===================================================
        LOG.info("Test mutex with threads...")

        # define our thread worker
        class MutexTestingThread(threading.Thread):
            ACQUIRE_LOCK = 'acquireLock'
            RELEASE_LOCK = 'releaseLock'
            GET_THREAD_ID = 'getThreadId'
            def __init__(self, actionQueue, resultQueue, mutexName, fakeEnv):
                threading.Thread.__init__(self)
                self.actionQueue = actionQueue
                self.resultQueue = resultQueue
                self.mutexName = mutexName
                self.fakeEnv = fakeEnv
                self.stopRequest = threading.Event()

            def run(self):
                while not self.stopRequest.isSet():
                    try:
                        action = self.actionQueue.get(True, .05)
                        self.resultQueue.put(self.doAction(action))
                    except Queue.Empty:
                        continue

            def join(self, timeout=None):
                self.stopRequest.set()
                threading.Thread.join(self, timeout)

            def doAction(self, action):
                if action == self.ACQUIRE_LOCK:
                    return self.acquireLock()
                elif action == self.RELEASE_LOCK:
                    return self.releaseLock()
                elif action == self.GET_THREAD_ID:
                    return self.getThreadId()
                return None

            def acquireLock(self):
                self.fakeEnv.AcquireMPMutex(self.mutexName)
                return True
            def releaseLock(self):
                self.fakeEnv.ReleaseMPMutex(self.mutexName)
                return True
            def getThreadId(self):
                return threading.current_thread().ident

        # Create communication queues for both threads.
        thread1ActionQueue = Queue.Queue()
        thread1ResultQueue = Queue.Queue()
        thread2ActionQueue = Queue.Queue()
        thread2ResultQueue = Queue.Queue()

        # Create and start both threads.
        thread1 = MutexTestingThread(actionQueue=thread1ActionQueue,
                                     resultQueue=thread1ResultQueue,
                                     mutexName=TEST_MUTEX_NAME,
                                     fakeEnv=self.fake_env)
        thread1.start()
        thread2 = MutexTestingThread(actionQueue=thread2ActionQueue,
                                     resultQueue=thread2ResultQueue,
                                     mutexName=TEST_MUTEX_NAME,
                                     fakeEnv=self.fake_env)
        thread2.start()

        # get the thread Id from our threads
        thread1ActionQueue.put(MutexTestingThread.GET_THREAD_ID)
        thread2ActionQueue.put(MutexTestingThread.GET_THREAD_ID)
        thread1ThreadId = thread1ResultQueue.get()
        thread2ThreadId = thread2ResultQueue.get()

        # ===================================================
        LOG.info("Test acquiring mutex with thread.")
        thread1ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        result = thread1ResultQueue.get()
        self.assert_mutex_owner(pid, thread1ThreadId)

        # ===================================================
        LOG.info("Test re-acquiring mutex with thread.")
        thread1ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        thread1ResultQueue.get()
        self.assert_mutex_owner(pid, thread1ThreadId)

        # ===================================================
        LOG.info("Test releasing mutex with thread.")
        thread1ActionQueue.put(MutexTestingThread.RELEASE_LOCK)
        thread1ResultQueue.get()
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        # ===================================================
        LOG.info("Test waiting for mutex availability with thread.")

        # thread 1 aquire
        thread1ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        thread1ResultQueue.get()
        self.assert_mutex_owner(pid, thread1ThreadId)

        # thread 2 attempt aquire
        thread2ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        time.sleep(.2)
        self.assert_mutex_owner(pid, thread1ThreadId)

        # thread 1 release, thread 2 should hold it now.
        thread1ActionQueue.put(MutexTestingThread.RELEASE_LOCK)
        thread1ResultQueue.get()
        thread2ResultQueue.get()
        self.assert_mutex_owner(pid, thread2ThreadId)

        # thread 2 release, lock should be gone.
        thread2ActionQueue.put(MutexTestingThread.RELEASE_LOCK)
        thread2ResultQueue.get()
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        # ===================================================
        LOG.info("Test acquireing mutex with dead thread.")

        # thread 1 acquire, then die
        thread1ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        thread1ResultQueue.get()
        self.assert_mutex_owner(pid, thread1ThreadId)
        thread1.join()

        # thread 2 should be able to aquire now that thread 1 is dead
        thread2ActionQueue.put(MutexTestingThread.ACQUIRE_LOCK)
        thread2ResultQueue.get()
        self.assert_mutex_owner(pid, thread2ThreadId)

        # release the lock again
        thread2ActionQueue.put(MutexTestingThread.RELEASE_LOCK)
        thread2ResultQueue.get()
        self.assertFalse(os.path.exists(TEST_MUTEX_FILE))

        # Now kill thread 2
        thread2.join()

        LOG.info('Testing SCons Multi-Processor Mutex - Completed')

    # End of test_mp_mutex()

    # Start test_action_binding
    def test_action_binding(self):

        LOG.info('Start testing Action Binding')

        import fSCons
        from fSCons import Node
        from fSCons.Node import FS
        from fSCons.Node.FS import File 

        node = fSCons.Node.FS.File()

        import SCons
        def test_blder(target, source, env):
            print('Testing unit test test_action_binding')
        fblder = SCons.Action.Action(test_blder, None)
        node.executor.action_list.append(fblder)

        self.assertEqual(len(node.executor.action_list), 1)
        self.fake_env.STAActionBinding(node, node_instance=fSCons.Node.FS.File)
        self.assertEqual(len(node.executor.action_list), 3)

        LOG.info('End testing Action Binding')
    # End test_action_binding
	
	# Start test_ApplyMPMutexToAction
    def test_ApplyMPMutexToAction(self):

        LOG.info('Start testing Apply Mutex to Action')

        import fSCons
        from fSCons import Node
        from fSCons.Node import Node

        node = fSCons.Node.Node()

        import SCons
        def test_blder(target, source, env):
            print('Testing unit test test_ApplyMPMutexToAction')
        fblder = SCons.Action.Action(test_blder, None)
        node.executor.action_list.append(fblder)

        self.assertEqual(len(node.executor.action_list), 1)
        self.fake_env.ApplyMPMutexToAction(node)
        self.assertEqual(len(node.executor.action_list), 3)

        LOG.info('End testing Apply Mutex to Action')
    # End test_ApplyMPMutexToAction


    #=================================
    # Support Functions
    #=================================

    def assert_mutex_owner(self, pid, tid):
        self.assertTrue(os.path.exists(TEST_MUTEX_FILE))
        with open(TEST_MUTEX_FILE, 'r') as mfh:
            mutex_data = json.load(mfh)
            self.assertEqual(mutex_data['pid'], pid)
            self.assertEqual(mutex_data['tid'], tid)
    # End of assert_mutex_owner

    def write_to_subprocess(self, process, string):
        process.stdin.write(bytes(string + '\n'))
        process.stdin.flush()
    # End of write_to_subprocess

    def testCompareTimeStampSourceOlder(self):
        source_file = "./test_source.txt"
        target_file = "./test_target.txt"

        with open(source_file, "w") as src:
            pass
        time.sleep(1)
        with open(target_file, "w") as targ:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_file)

        os.remove(source_file)
        os.remove(target_file)

        self.assertTrue(res)

    def testCompareTimeStampSourceNewer(self):
        source_file = "./test_source.txt"
        target_file = "./test_target.txt"

        with open(target_file, "w") as targ:
            pass
        time.sleep(1)
        with open(source_file, "w") as src:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_file)

        os.remove(source_file)
        os.remove(target_file)

        self.assertFalse(res)

    def testCompareTimeStampSourceTargetSame(self):
        source_file = "./test_source.txt"
        target_file = "./test_target.txt"

        # There is only millisecond resolution; the following two lines run much faster
        # than that and therefore end up having the same same timestamp
        with open(target_file, "w") as targ:
            pass
        with open(source_file, "w") as src:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_file)

        os.remove(source_file)
        os.remove(target_file)

        self.assertFalse(res)

    def testCompareTimeStampMultipleSourceOlder(self):
        source_files = ["./test_source_1.txt", "./test_source_2.txt"]
        target_file = "./test_target.txt"

        for source_file in source_files:
            with open(source_file, "w") as src:
                pass
        time.sleep(1)
        with open(target_file, "w") as targ:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_files)

        for source_file in source_files:
            os.remove(source_file)
        os.remove(target_file)

        self.assertTrue(res)

    def testCompareTimeStampSourceNonExistent(self):
        source_file = None
        target_file = "./test_target.txt"

        with open(target_file, "w") as targ:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_file)

        os.remove(target_file)

        self.assertFalse(res)
    
    def testCompareTimeStampTargetNonExistent(self):
        source_file = "./test_source.txt"
        target_file = None 

        with open(source_file, "w") as src:
            pass

        res = self.fake_env.CompareTimeStampAreSourceFilesOlder(target_file, source_file)

        os.remove(source_file)

        self.assertFalse(res)
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

