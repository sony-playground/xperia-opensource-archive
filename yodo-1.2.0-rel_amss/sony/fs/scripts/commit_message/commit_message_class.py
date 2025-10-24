""" Classes for handling git commit messages. """

import re

_DMS_PATTERN = re.compile(r'^\s*FIX=(DMS\d{6,8})\s*$', flags=re.MULTILINE)
_ISSUE_PATTERN = re.compile(
    r'^\s*([Ii]ssue|[Ff]ixes|[Cc]loses|[Rr]efs): ([A-Z][A-Z0-9]+-[0-9]+)$',
    flags=re.MULTILINE)
_TAG_PATTERN = re.compile(r'\[(.*?)\]', flags=0)

def _sanitise_string(string):
    """ Return `string` with all non-ascii characters removed. """
    return "".join(i for i in string if ord(i) < 128)


class CommitMessageError(Exception):

    """ Error performing an operation on the commit message. """


class CommitMessage(object):

    """ Wrapper for the commit message. """

    def __init__(self, message_body):
        """ Initialize the class with the commit message in `message_body`. """

        # Normalize line endings.
        message_body = message_body.replace("\r\n", "\n").strip()


        # Split the message into paragraphs which are delimited by
        # two or more new line characters.
        parts = re.split(r'\n{2,}', message_body)

        # The subject is the first paragraph.
        self.subject = parts[0]

        # If there are multiple paragraphs, join them to make the rest
        # of the body.
        if len(parts) >= 2:
            self.message = "\n\n".join(parts[1:])
        else:
            self.message = ""

        # The footers are the last paragraph
        if len(parts) > 1:
            self.footers = parts[-1].split("\n")
        else:
            self.footers = []

        # Strip trailing whitespace and newlines off the subject and message.
        self.subject = self.subject.rstrip()
        self.message = self.message.rstrip()

    def get_fixed_issues(self):
        """ Get the fixed issues that are listed in the commit message.

        Return a list of issues, or an empty list if no issues were found.

        """
        groups = re.findall(_DMS_PATTERN, _sanitise_string(self.message))
        issues = []
        for issue in groups:
            if issue.strip() not in issues:
                issues.append(issue.strip())
        return issues

    def get_fixed_jira_issues(self):
        """ Get the fixed JIRA issues that are listed in the commit message.

        Return a list of issues, or an empty list if no issues were found.

        """
        groups = re.findall(_ISSUE_PATTERN, _sanitise_string(self.message))
        issues = []
        for issue_id in groups:
            issue = issue_id[1]
            if issue.strip() not in issues:
                issues.append(issue.strip())
        return issues

    def get_tag_from_subject(self):
        tag = re.match(_TAG_PATTERN, _sanitise_string(self.subject))
        return tag

