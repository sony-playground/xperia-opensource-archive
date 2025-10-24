#===============================================================================
#
# logger
#
# GENERAL DESCRIPTION
#    Library to provide logging services to other Python scripts.
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/pack/logger.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
#===============================================================================

'''
Description:
This is a library and all logging functions would be a part of this script. 
This module would be imported from all modules needing to log the necessary information
'''

import sys
import os
import subprocess
import shlex
import traceback
from threading import Timer

verbose_level = 2
   
class Logger:
   
   def __init__(self,lg_file_name, prefix=None):
      self.write_exception_count = 0
      self.flush_exception_count = 0
      if os.path.exists(lg_file_name + '.log'):
         i = 1
         while os.path.exists(lg_file_name + '_%.2d.log' % (i)):
            i += 1
         os.rename(lg_file_name + '.log', lg_file_name + '_%.2d.log' % (i))
      self.log_file = open(lg_file_name + '.log', 'a' , 0)
      self.prefix = prefix
      self.timer = None

   def __flush (self):
      try:
         self.log_file.flush()
      except IOError:
         # Ignore this error.  This is disappointing, but shouldn't
         # crash the caller.
         self.flush_exception_count += 1

   def log(self,str,verbose=1):
      try:
         if verbose_level >= verbose:
            str = str + '\n'
            if self.prefix:
               str = self.prefix + str
            self.log_file.write(str)
            sys.stdout.write(str)
            if self.timer:
               self.timer.cancel()
            self.timer = Timer(5.0, self.__flush, args=[self])
      except IOError:
         # Ignore this error.  This is disappointing, but shouldn't
         # crash the caller.
         self.write_exception_count += 1


   def log_exec (self,cmd, shell=True, verbose=1, capture_output = False):
      if type(cmd) is not list:
         self.log('Executing: ' + cmd)
         if not sys.platform.startswith("linux"):
            # Linux is having trouble executing commands from lists, the
            # parameters aren't being passed through, so only split commands
            # on Windows
            cmd = shlex.split()
      else:
         self.log('Executing: ' + ' '.join(cmd))
      task = subprocess.Popen(cmd, shell=True, stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
      captured_output = ''
      c = task.stdout.read(1)
      while c:
         if capture_output:
            captured_output += c
         if verbose_level >= verbose:
            self.log_file.write(c)
            sys.stdout.write(c)
            c = task.stdout.read(1)
      task.wait()  # Wait for the task to really complete
      if task.returncode != 0:
         self.log(cmd[0] + " command returned error: " + str(task.returncode), verbose)
      if capture_output:
         return [task.returncode, captured_output]
      else:
         return task.returncode

   def log_exception (self):
      traceback.print_exc (None, self.log_file)

   def log_error (self, msg):
      self.log("Error: " + msg, verbose = 0)
      if self.log_file:
         self.log_file.close()
      exit(1)
   
   def __del__ (self):
      if self.log_file:
         if self.flush_exception_count > 0:
            self.log_file.write(str(self.flush_exception_count) + " flush exceptions occurred")
         if self.write_exception_count > 0:
            self.log_file.write(str(self.write_exception_count) + " write exceptions occurred")
         self.log_file.close()
