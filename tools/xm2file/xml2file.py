#!/usr/bin/env python
#
# xml2file.py
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import argparse
import os
import errno
import re
import json
import codecs
import shutil
import xml.etree.ElementTree as ET

from argparse import ArgumentParser

# command line option
def parse_command_line():
    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 0.1'
    )
    parser.add_argument(
        '-o',
        '--output',
        default=None,
        help='output file path.'
    )
    parser.add_argument(
        '--no-time',
        action='store_true',
        help='no output time attribute'
    )
    parser.add_argument(
        '--verbose',
        action='store_true',
        help='log verbose'
    )
    parser.add_argument(
        '--encoding',
        default=None,
        help='output file encoding.'
    )
    parser.add_argument(
        '--debug',
        action='store_true',
        help='log debug'
    )
    parser.add_argument(
        'file',
        metavar='FILE',
        nargs='+',
        help='test result xml files'
    )
    options = parser.parse_args()
    return options

cmdline_options = None


def log(msg):
    if cmdline_options.verbose:
        print(msg)


def logd(msg):
    if cmdline_options.debug:
        print(msg)


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise


def clean_dir(path):
    if os.path.exists(path):
        shutil.rmtree(path)


def fopen(path):
    dir = os.path.dirname(path)
    mkdir_p(dir)
    f = codecs.open(path, 'w', cmdline_options.encoding)
    return f


def make_rootpath(xml_filename, testsuites):
    # root_name = testsuites.attrib['name']
    root_name = xml_filename
    path = os.path.join(cmdline_options.output, root_name)
    return path


def make_path(root_path, testsuite, testcase):
    suite_name = testsuite.attrib['name']
    case_name = testcase.attrib['name']
    ext = '.json'
    return os.path.join(os.path.join(root_path, suite_name), case_name + ext)


def _get_user_properties(node, system_attributes):
    users = {}
    for a in node.attrib:
        if a not in system_attributes:
            users[a] = node.attrib[a]
    return users


def get_user_properties(node):
    system_attributes = {
        "testsuites": [
            "name", "tests", "failures", "disabled", "skip", "errors", "time", "timestamp", "random_seed"
        ],
        "testsuite": [
            "name", "tests", "failures", "disabled", "skip", "errors", "time", "timestamp", "random_seed"
        ],
        "testcase": [
            "name", "status", "time", "classname", "type_param", "value_param"
        ]
    }
    for k,v in system_attributes.items():
        if node.tag == k:
            return _get_user_properties(node, v)
    return node.attrib


def write_result(f, testsuites_user_attrib, testsuite_user_attrib, testcase):
    d = testcase.attrib
    if cmdline_options.no_time:
        if 'time' in d:
            del d['time']
    d['testsuites_attrib'] = testsuites_user_attrib
    d['testsuite_attrib'] = testsuite_user_attrib
    # failure and skipped ...
    for child in testcase:
        tag = child.tag
        if tag not in d:
            d[tag] = []
        fd = child.attrib
        fd['text'] = child.text
        d[tag].append(fd)
    jt = json.dumps(d, indent=4, ensure_ascii=False)
    logd(jt)
    f.write(jt)


def xml2file(path):
    tree = ET.parse(path)
    root = tree.getroot()
    testsuites = root

    basename = os.path.basename(path)
    filename = os.path.splitext(basename)[0]
    root_path = make_rootpath(filename, testsuites)
    clean_dir(root_path)

    log(basename)
    testsuites_user_attrib = get_user_properties(testsuites)
    for testsuite in testsuites:
        log("  " + testsuite.attrib['name'])
        testsuite_user_attrib = get_user_properties(testsuite)
        for testcase in testsuite:
            log("    " + testcase.attrib['name'])
            f = fopen(make_path(root_path, testsuite, testcase))
            write_result(f, testsuites_user_attrib, testsuite_user_attrib, testcase)
            f.close()


def main():
    global cmdline_options
    cmdline_options = parse_command_line()
    for path in cmdline_options.file:
        xml2file(path)


if __name__ == '__main__':
    main()
