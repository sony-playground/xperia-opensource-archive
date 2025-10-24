#!/usr/bin/env python

import requests, json
import sys, getopt
import os
import time
from sys import path
from os import getcwd

path.append(getcwd() + "/commit_message")
from commit_message_class import CommitMessage
from processes import run_cmd, ChildExecutionError

JIRA_ISSUE_URL = "http://jira.sonymobile.net/rest/api/latest/issue"
JIRA_VERSION_URL = "http://jira.sonymobile.net/rest/api/latest/version"

def usage():
    print 'Set fixversion field and try to close JIRA issues found between two git tags or changes'
    print 'usage: --user <user> --password <password>'
    print '--rev <current revison> --oldrev <old revision>'
    print '--gitpath <path to the git that contains the changes>'


def main(argv):

    user = None
    pas = None
    current_rev = ''
    previous_rev = ''
    git_path = ''


    try:
        opts, args = getopt.getopt(sys.argv[1:], "",
            ["user=", "password=", "rev=", "oldrev=", "gitpath="])
    except getopt.GetoptError:
        usage()
        sys.exit(1)

    for opt, arg in opts:
        if opt == '--user':
            user = arg
        elif opt == '--password':
            pas = arg
        elif opt in ("--rev"):
            current_rev = arg
        elif opt in ("--oldrev"):
            previous_rev = arg
        elif opt in ("--gitpath"):
            git_path = arg

    if user is None or pas is None:
        usage()
        sys.exit(1)

    if git_path == '':
        usage()
        sys.exit(1)

    if previous_rev == '':
        previous_rev = current_rev


    fixVersions_payload = {
        'update' : {
            'fixVersions' :  [
                 {
                     'add' :
                         {
                             'name' : str(current_rev)
                         }
                 }
             ]
         }
    }

    closeIssue_payload = {
        "transition": {
            "id": "701"
        }
    }

    os.chdir(git_path)
    dif = previous_rev + ".." + current_rev
    cmd = ["git", "rev-list", "--count", dif]

    try:
        _ret, stdout, _stderr, = run_cmd(cmd)
    except ChildExecutionError as err:
        fatal(1, "Unable to get commit from local repository: %s" % err)

    nb_commits = stdout

    current_rev_it = current_rev


    for x in range(0, int(nb_commits)):
        cmd = ["git", "log", "--format=%B", "-1", current_rev_it]

        try:
            _ret, stdout, _stderr, = run_cmd(cmd)
        except ChildExecutionError as err:
            fatal(1, "Unable to get commit from local repository: %s" % err)

        message = CommitMessage(stdout)
        issuelist = message.get_fixed_jira_issues()

        for issue in issuelist:

            header = {'content-type': 'application/json'}
            new_version_payload = {
                'name' : str(current_rev),
                'project': str(issue[:issue.index('-')]),
                'released' : 'true',
                'releaseDate' : time.strftime("%Y-%m-%d")
            }

            r = requests.post(
                JIRA_VERSION_URL,
                headers=header,
                data=json.dumps(new_version_payload),
                auth=(user, pas))

#Set fixVersion field
            jira_issue_url = '{base}/{issue}'.format(base = JIRA_ISSUE_URL, issue = ''.join(issue))
            r = requests.put(
                jira_issue_url,
                headers=header,
                data=json.dumps(fixVersions_payload),
                auth=(user, pas))
            print 'update Jira issue: ' + ''.join(issue) + ' with fixVersion=' + current_rev
            print r.status_code
            print r.reason
            print r.text
#Try to close the issue, this will work only if the issue is in Resolved state
            url = '{base}/{issue}/transitions?expand=transitions.fields'.format(
                base = JIRA_ISSUE_URL,
                issue = ''.join(issue))
            print 'Close url ' + url
            r = requests.post(
                url,
                headers=header,
                data=json.dumps(closeIssue_payload),
                auth=(user, pas))
            print r.status_code
            print r.reason
            print r.text

        current_rev_it = current_rev_it + "^"

if __name__ == "__main__":
   main(sys.argv[1:])
