#!/usr/bin/env python
'''
Perform test commands from another process.
'''

import sys
import os

from fake_scons_env import FakeSConsEnv
import threading

try:  # 'raw_input' renamed as 'input' in Python 3
    my_input = raw_input
except (NameError):
    my_input = input


def pack_input_args(input_list): 
   
   if all ('=' in str(each)  for each in input_list) : 
      argss = dict()
      for each_input in input_list :
         argss[each_input.split('=',1)[0]]=ast.literal_eval(each_input.split('=',1)[1])

   else : 
      argss = input_list
      
   return argss

# End of pack_input_args()

def print_flush(msg):
    print(msg)
    sys.stdout.flush()
# End of print_flush()

fake_env = FakeSConsEnv()

# send our thread id back to parent
thread = threading.current_thread()
tid = thread.ident if thread is not None else -1

# In a loop, process commands from stdin

while True:

    print_flush("Waiting for command")
    command = my_input().split()
    print_flush("Command Entered: " + str(command))

    if command[0] == 'Quit':
        break
    elif command[0] == 'PrintThreadId':
        print_flush (str(tid))

    elif command[0] == 'SetEnvVarInt':

        env_var_name = command[1]
        env_var_value = int(command[2])
        fake_env[env_var_name] = env_var_value

    else:

        # Call whatever command is specified
        func_name = command[0]
        func_args = pack_input_args(command[1:])
        
        if func_name not in dir(fake_env):
            raise Exception("Couldn't find " + func_name + " in fake_env")

        func = getattr(fake_env, func_name)
        if type(func_args) is list: 
            output = func(*func_args)
        else : 
            output = func(**func_args)
        print_flush(str(output))



