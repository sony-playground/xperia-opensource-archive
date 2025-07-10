import sys, os
import subprocess
from subprocess import Popen, PIPE, DEVNULL
import logging
import time
from dotted_dict import DottedDict
import math
import shutil
from datetime import datetime as dt

logger = logging.getLogger(__name__)

def get_python_version():
    if os.name == 'posix':
        return f'python{sys.version_info.major}.{sys.version_info.minor}'
    else:
        return f'py -{sys.version_info.major}'

def run_shell_cmd(command, log=True):
    stdout, stderr = Popen(command, stdout=PIPE, stderr=PIPE,stdin=DEVNULL, shell=True).communicate()
    command_status = {'output': stdout.decode('utf-8'), 'error': stderr.decode('utf-8')}
    if log:
        logger.info(f'command: {command}, stdout: {stdout.decode("utf-8")}, stderr: {stderr.decode("utf-8")}')
    if stderr:
        command_status['error'] = stderr.decode('utf-8')
        logger.error(f'{stderr}')
    if stdout:
        command_status['output'] = stdout.decode('utf-8')
    return DottedDict(command_status)


def install_lib_modules(modules_list:list):
    python_version = get_python_version()
    freeze_command = f'{python_version} -m pip freeze'
    command_status = run_shell_cmd(freeze_command)

    if command_status.error:
        logger.error(f'{command_status.error}')
        return

    for module in modules_list:
        if module not in command_status.output:
            command_status = run_shell_cmd(f'{python_version} -m pip install {module}')