#!/usr/bin/env python


#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 11/16/21   yps     Wrapper of genconfigimage.py and will delete once toolchain migrate to genconfigimage.py
import subprocess
import sys
import os

if __name__ == "__main__":
  subprocess.call(["python",os.path.join(os.path.dirname(os.path.realpath(__file__)),"GenConfigImage.py")]+sys.argv[1:])
