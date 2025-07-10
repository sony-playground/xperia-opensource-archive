#!/usr/bin/env python

import requests, json
import sys, getopt
import xml.dom.minidom
import time
import os
import cgi
from sys import path
from os import getcwd

path.append(getcwd() + "/commit_message")
from commit_message_class import CommitMessage
from processes import run_cmd, ChildExecutionError

#CONFLUENCE_URL = "http://test-confluence.sonymobile.net/rest/api/content"
CONFLUENCE_URL = "http://confluence.sonymobile.net/rest/api/content"

def parse_jenkins_config_xml(config_xml_path):
    matrix_dom_tree = xml.dom.minidom.parse(config_xml_path)
    matrix_project = matrix_dom_tree.documentElement
    package_names_list=[]

    TextAxis = matrix_project.getElementsByTagName(
        "ca.silvermaplesolutions.jenkins.plugins.daxis.DynamicAxis")
    # There are two types of config.xml formats. We check which one it is.
    if TextAxis:
        for text in TextAxis:
            name = text.getElementsByTagName("name")[0]
            if name.childNodes[0].data == "HUDSON_PRODUCT":
                axisValues = text.getElementsByTagName("axisValues")[0]
                package_group_names = axisValues.getElementsByTagName("string")
    else:
        TextAxis = matrix_project.getElementsByTagName("hudson.matrix.TextAxis")
        for text in TextAxis:
            name = text.getElementsByTagName("name")[0]
            if name.childNodes[0].data == "HUDSON_PRODUCT":
                package_group_names = text.getElementsByTagName("string")

    for string in package_group_names:
        package_names_list.append("fw-xfl-" + string.childNodes[0].data.replace("_", "-"))

    return package_names_list

def printResponse(r):
    print '{} {}\n'.format(json.dumps(r.json(), sort_keys=True, indent=4, separators=(',', ': ')), r)

def get_page_ancestors(user, password, pageid):

    # Get basic page information plus the ancestors property

    url = '{base}/{pageid}?expand=ancestors'.format(
        base = CONFLUENCE_URL,
        pageid = pageid)

    r = requests.get(url, auth=(user, password))

    r.raise_for_status()

    return r.json()['ancestors']

def get_page_info(user, password, pageid):

    url = '{base}/{pageid}'.format(
        base = CONFLUENCE_URL,
        pageid = pageid)

    r = requests.get(url, auth=(user, password))

    r.raise_for_status()

    return r.json()

def get_page_body(user, password, pageid):

    url = '{base}/{pageid}?expand=body.storage'.format(
        base = CONFLUENCE_URL,
        pageid = pageid)

    r = requests.get(url, auth=(user, password))

    r.raise_for_status()

    return r.json()

def get_commit_changes(previous_rev, current_rev):

    change = ''
    current_rev_it = current_rev
    dif = previous_rev + ".." + current_rev

    cmd = ["git", "rev-list", "--count", dif]

    try:
        _ret, stdout, _stderr, = run_cmd(cmd)
    except ChildExecutionError as err:
        fatal(1, "Unable to get commit from local repository: %s" % err)

    nb_commits = stdout

    for x in range(0, int(nb_commits)):
        cmd = ["git", "log", "--format=%B", "-1", current_rev_it]

        try:
            _ret, stdout, _stderr, = run_cmd(cmd)
        except ChildExecutionError as err:
            fatal(1, "Unable to get commit from local repository: %s" % err)

        message = CommitMessage(stdout)
        issuelist = message.get_fixed_jira_issues()
        dmslist = message.get_fixed_issues()

        for issue in issuelist:
            change += '<a href="http://jira.sonymobile.net/browse/' + ''.join(issue) \
            + '">' + ''.join(issue) + '</a>' + ' ' + cgi.escape(message.subject) + '<br/>'

        if not len(issuelist):
            change += cgi.escape(message.subject) + '<br/>'

        current_rev_it = current_rev_it + "^"

    return change

def usage():
    print 'usage: --user <user> --password <password> --rev <current revison> --oldrev <old revision>'
    print '--somcbuildid <build id> --matrixxml <jenkins matrix build job config xml> '
    print '--pageid <confluence pageid that will be updated>'

def main(argv):

    user = None
    pas = None
    current_rev = ''
    previous_rev = ''
    somcbuildid = ''
    jenkins_config_xml_path = ''
    pageid = ''

    try:
        opts, args = getopt.getopt(sys.argv[1:], "",
            ["user=", "password=", "rev=", "oldrev=", "somcbuildid=", "matrixxml=", "pageid="])
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
        elif opt in ("--somcbuildid"):
            somcbuildid = arg
        elif opt in ("--matrixxml"):
            jenkins_config_xml_path = arg
        elif opt in ("--pageid"):
            pageid = arg

    if user is None or pas is None:
        usage()
        sys.exit(1)

    if current_rev == '' or somcbuildid == '' or jenkins_config_xml_path == '' or pageid == '':
        usage()
        sys.exit(1)

    if previous_rev == '':
        previous_rev = current_rev


    change = "<h1>" + current_rev + "</h1>"
    change += "<p>Date: " + time.strftime("%Y-%m-%d") + "</p>"
    change += '<p>CMWEB release info: <a href="http://cmweb.sonyericsson.net/builds/platform/xflmanifest/' \
    + somcbuildid + '">' + somcbuildid + '</a>' '</p>'
    change += "<h3>Changes </h3>"


    change += '<p><b>fs/main diff</b></p>'
    change += get_commit_changes(previous_rev, current_rev)

    change += '<p><b>fs/build diff</b></p>'
    os.chdir('../../build/')
    change += get_commit_changes(previous_rev, current_rev)

    change += '<p><b>fs/ramdisk diff</b></p>'
    os.chdir('../ramdisk/')
    change += get_commit_changes(previous_rev, current_rev)

    change += '<p><b>manifest</b></p>'
    os.chdir('../../../../.repo/manifests/')
    change += get_commit_changes(previous_rev, current_rev)

    change += "<h3>Download deb</h3>"
    package_names_list = parse_jenkins_config_xml(jenkins_config_xml_path)
    for package_name in package_names_list:
        change += "repository getpackage " + package_name + " " + current_rev + "<br/>"

    info = get_page_info(user, pas, pageid)
    ver = int(info['version']['number']) + 1

    ancestors = get_page_ancestors(user, pas, pageid)

    anc = ancestors[-1]
    del anc['_links']
    del anc['_expandable']
    del anc['extensions']

    body = get_page_body(user, pas, pageid)
    body_data = str(body["body"]["storage"]["value"])

    body_data += change

    pageData = {
        'id' : str(pageid),
        'type' : 'page',
        'title' : info['title'],
        'version' : {'number' : ver},
        'ancestors' : [anc],
        'body'  : {
            'storage' :
            {
                'representation' : 'storage',
                'value' : str(body_data),
            }
        }
    }

    url = '{base}/{pageid}'.format(base = CONFLUENCE_URL, pageid = pageid)
    r = requests.put(
        url,
        data=json.dumps(pageData),
        auth=(user, pas),
        headers={'Content-Type':'application/json'})
    print r.status_code
    print r.reason
    print r.text

if __name__ == "__main__":
   main(sys.argv[1:])
