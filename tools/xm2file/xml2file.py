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
        '--encoding',
        default=None,
        help='output file encoding.'
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


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise


def fopen(relative_path):
    path = os.path.join(cmdline_options.output, relative_path)
    dir = os.path.dirname(path)
    mkdir_p(dir)
    f = codecs.open(path, 'w', cmdline_options.encoding)
    return f


def make_path(filename, testsuites, testsuite, testcase):
    # root_name = testsuites.attrib['name']
    root_name = filename
    suite_name = testsuite.attrib['name']
    case_name = testcase.attrib['name']
    ext = '.json'
    return os.path.join(os.path.join(root_name, suite_name), case_name + ext)


def write_result(f, testcase):
    d = testcase.attrib
    if 'time' in d:
        del d['time']
    jt = json.dumps(d)
    print(jt)
    f.write(jt)


def xml2file(path):
    tree = ET.parse(path)
    root = tree.getroot()
    testsuites = root

    filename = os.path.split(os.path.basename(path))[0]
    for testsuite in testsuites:
        for testcase in testsuite:
            f = fopen(make_path(filename, testsuites, testsuite, testcase))
            write_result(f, testcase)
            f.close()

def main():
    global cmdline_options
    cmdline_options = parse_command_line()
    for path in cmdline_options.file:
        xml2file(path)

if __name__ == '__main__':
    main()
