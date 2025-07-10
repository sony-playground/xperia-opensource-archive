#!/usr/bin/env python

# Original code from: review.sonyericsson.net:29418/semctools/fbatools

from __future__ import print_function
import requests
import os
import re
import sys

arguments = sys.argv[1:]
if len (arguments) < 3 or len (arguments) > 4 :
    print("Usage: python sync2files.py <23xxxxxx> <password> <base_dir>")
    sys.exit (1)

os.chdir(arguments[2])

auth = (arguments[0], arguments[1])

host = 'http://sandbox-fcs.mplus.sonyericsson.net/'
#host = 'http://sandbox-shared.mplus.sonyericsson.net/'

print("GET'ing user id from " + host)
r = requests.get(
    host + 'tables/Users/?_format=json&_max_age=0&username+iexact=' + arguments[0],
    auth=auth
)
if r.status_code >= 400:
    print(r.text)
    sys.exit(1)
userid = r.json()['results'][0]['id']

print("GET'ing SG-WW-PLD-SD-FnS-Approvers-G user id from " + host)
r = requests.get(
    host + 'tables/Users/?_format=json&_max_age=0&username+iexact=SG-WW-PLD-SD-FnS-Approvers-G',
    auth=auth
)
if r.status_code >= 400:
    print(r.text)
    sys.exit(1)
sg_ww_fns_app_g = r.json()['results'][0]['id']

def update_or_create(file_path):
    filestruct = {
        'pathandname': file_path,
        'directory': file_path.rsplit('/', 1)[0] + '/', #this is pure directory, without filename
        'owners': []
    }

    path = filestruct['pathandname']

    realfile = {'file': open(path, 'rb')}

    r = requests.get(
        host + 'tables/Files/?_format=json&_max_age=0&_m=count&_m=results&_c=id&_c=file&_c=owners&_c=revision&_sq=file+is+"' + str(path) + '"',
        auth=auth
    )
    if r.status_code >= 400:
        print(r.text)
        sys.exit(1)
    count = r.json()['count']

#when creating a file, you yourself must be an owner of the file
#so always append myself as an owner, since I am touching it
    if userid not in filestruct['owners']:
        filestruct['owners'].append(userid)

#always append SG-WW-PLD-SD-FnS-Approvers-G as the owning user of the files uploaded by this script
#so that if one member of SG-WW-PLD-SD-FnS-Approvers-G uploaded a new file, other members get owner permission automatically
    if sg_ww_fns_app_g not in filestruct['owners']:
        filestruct['owners'].append(sg_ww_fns_app_g)

    if count == 1:
        existing_file = dict(  #path+name
            (result['file'], result)
            for result in r.json()['results']
        )
        filestruct['id'] = existing_file[path]['id']
        filestruct['owners'] = existing_file[path]['owners']
        filestruct['revision'] = existing_file[path]['revision']
        print("PUT'ting {0}".format(path))

        res = requests.put(
            host + 'tables/Files/{0}/?_format=json'.format(filestruct['id']),
            data=filestruct, files=realfile, auth=auth
        )

    else:
        print("POST'ing {0}".format(path))

        assert 'id' not in filestruct

        res = requests.post(
            host + 'tables/Files/?_format=json',
            data=filestruct, files=realfile, auth=auth
        )

    if res.status_code >= 400:
        print(res.text)
        print("update_or_create incomplete due to error, please check console message above")
        sys.exit (2)

file_paths = [
    file_path for file_path
    in os.popen('find {0}'.format('files')).read().splitlines()
    if os.path.splitext(file_path)[1]  #TODO bug, file_paths will ignore any file without extension
]

for file_path in file_paths:
    update_or_create(file_path)

