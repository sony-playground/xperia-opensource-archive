""" Method and error classes used for executing a command in a
child process. """

import logging
import subprocess


class ChildExecutionError(Exception):

    """ Execution error.

    Superclass for the various types of errors that can occur when
    running child processes.

    """

    def __init__(self, command):
        super(ChildExecutionError, self).__init__()
        if isinstance(command, list):
            self.command = " ".join(command)
        else:
            self.command = command


class ChildRuntimeError(ChildExecutionError):

    """ Runtime error.

    Raised when a child process has died with a non-zero exit status,
    and this case is considered exceptional.

    """

    def __init__(self, command, result):
        super(ChildRuntimeError, self).__init__(command)
        self.result = result

    def __str__(self):
        return 'Command exited with status %d: %s\nError message: %s' % \
            (self.result[0], self.command, self.result[2])


class ChildSignalledError(ChildExecutionError):

    """ Signalled error.

    Raised when a child process dies of a signal.

    """

    def __init__(self, command, result):
        super(ChildSignalledError, self).__init__(command)
        self.result = result

    def __str__(self):
        return 'Command killed by signal %d: %s' % (-self.result[0],
                                                    self.command)


class ChildStartupError(ChildExecutionError):

    """ Startup error.

    Raised when a child process couldn't be started at all,
    typically because the process fork failed or because the
    program executable couldn't be found.

    """

    def __init__(self, command, enverror):
        super(ChildStartupError, self).__init__(command)
        self.enverror = enverror

    def __str__(self):
        return 'Error running command (%s): %s' % (self.enverror.strerror,
                                                   self.command)


def run_cmd(*cmdandargs, **kwargs):
    """ Run a command, return the result.

    This function can be used in the following ways:

    run_cmd(list, **kwargs) -> Runs the command (with arguments) in list.
    run_cmd(cmd, arg1, arg2, ..., **kwargs) -> Runs cmd with the specified
        arguments.

    Possible kwargs:
    capture:
        If set to false the output from the command won't be captured and will
        go directly to the current stdout/stderr. Default True.
    input:
        Send this data to the process on stdin.
    path:
        Runs the command at the given path

    Returns a tuple with: the exit status, a string containing stdout
    and a string containing stderr.

    Raises some version of ChildExecutionError if it encountered an error.

    """

    if isinstance(cmdandargs[0], list):
        cmdandargs = cmdandargs[0]
    cmddesc = ' '.join(cmdandargs)

    popenkwargs = {}
    if "capture" not in kwargs or kwargs["capture"] is True:
        popenkwargs = {"stdout": subprocess.PIPE,
                       "stderr": subprocess.PIPE}

    if "path" in kwargs:
        popenkwargs["cwd"] = kwargs["path"]
        cmddesc += " (In directory: %s)" % kwargs["path"]

    logging.debug("Running: %s", cmddesc)

    if "input" in kwargs:
        popenkwargs["stdin"] = subprocess.PIPE

    def close_files(files):
        """ Utility to close files. """
        for f in [f for f in files if f]:
            f.close()

    try:
        process = subprocess.Popen(cmdandargs, **popenkwargs)
        if "input" in kwargs:
            stdout, stderr = process.communicate(input=kwargs["input"])
        else:
            stdout, stderr = process.communicate()
        result = (process.returncode, stdout, stderr)
        close_files([process.stdin, process.stdout, process.stderr])
        if process.returncode == 0:
            return result
        elif process.returncode < 0:
            raise ChildSignalledError(cmddesc, result)
        else:
            raise ChildRuntimeError(cmddesc, result)
    except EnvironmentError as e:
        raise ChildStartupError(cmddesc, e)
