Introduction
============

This is the guideline for when to create branches for loader development and
releases.

Manifest branches
=================

There should be a manifest branch for each platform.
Name convention is <platform>-lilo. lilo stands for 'Linux loader'.
We might need to add the the prefix 'pre', when working with Google pre-access
code.

Examples:
   yoshino-lilo
   pre-o-tama-lilo

For releases we might need to lock a number of gits to be able to do bug fixes
on older releases. Then we should use a static manifest branch with a suffix
'-static'.

Example: We have made 2 releases, #1 and #2, and we want to make a bugfix on
release #1. The first step is to take the static manifest for release #1 and
submit it to branch <platform>-lilo-static. Secondly we need to branch out the
git(s) that should be modified and use these branches in the manifest.


Flash Core Security branches
============================

Projects (gits) that are maintained by Flash Core Security should use the
following strategy:

Development should be on the 'master' branch. To avoid unnecessary
cherry-picking, we should only branch out when we need to change an older
release and the latest on 'master' is not compatible with that release.

The naming of this branch (these branches) should describe the reason of the
branch, preferably a JIRA issue. The platform name should also be included.

Example:

A bugfix reported in JIRA issue FS-789, needs to be released for the yoshino
platform in git vendor/semc/fs/main. This fix is not compatible with the latest
on the 'master' branch which has moved on to support next platform. A new
branch named yoshino-fs-789 is created which is branched out from the point
where last yoshino release was made. The manifest on branch yoshino-lilo-static
is updated with the static manifest for last yoshino release except for project
vendor/semc/fs/main which revision is set to yoshino-fs-789.
The issue is then fixed on branch yoshino-fs-789 and a new release is done on
the manifest branch yoshino-lilo-static.
