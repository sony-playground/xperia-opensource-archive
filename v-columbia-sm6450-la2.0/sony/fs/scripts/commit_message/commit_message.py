#!/usr/bin/env python

import sys
import re

from commit_message_class import CommitMessage
from processes import run_cmd, ChildExecutionError

def _main():

    rev = "HEAD"
    cmd = ["git", "log", "--format=%B", "-1", rev]
    try:
        _ret, stdout, _stderr, = run_cmd(cmd)
    except ChildExecutionError as err:
        fatal(1, "Unable to get commit from local repository: %s" % err)
    message = CommitMessage(stdout)
    issuelist = message.get_fixed_jira_issues()
    dmslist = message.get_fixed_issues()
    issuemissing = 0
    tagmissing = 0

    if not len(issuelist):
        print("No Jira Issue found in commit message")
        if not len(dmslist):
            print("No DMS Issue found in commit message")
            issuemissing = 1

    tag = message.get_tag_from_subject()
    if tag is None:
        print "No tag found"
        tagmissing = 1
    else:
        print "Subject tag found", tag.group()

    if issuemissing == 1 and tagmissing == 1:
        sys.exit(3)

    if issuemissing == 1:
        sys.exit(1)

    if tagmissing == 1:
        sys.exit(2)

    sys.exit(0)

if __name__ == '__main__':
    try:
        sys.exit(_main())
    except KeyboardInterrupt:
        fatal(1, "Interrupted by user")
