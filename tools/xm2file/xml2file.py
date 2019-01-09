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


def write_result(f, testcase):
    d = testcase.attrib
    if cmdline_options.no_time:
        if 'time' in d:
            del d['time']
    # failures
    d['failure'] = []
    for failure in testcase:
        fd = failure.attrib
        fd['text'] = failure.text
        d['failure'].append(fd)
    jt = json.dumps(d, indent=4, ensure_ascii=False)
    print(jt)
    f.write(jt)


def xml2file(path):
    tree = ET.parse(path)
    root = tree.getroot()
    testsuites = root

    filename = os.path.splitext(os.path.basename(path))[0]
    root_path = make_rootpath(filename, testsuites)
    clean_dir(root_path)

    for testsuite in testsuites:
        for testcase in testsuite:
            f = fopen(make_path(root_path, testsuite, testcase))
            write_result(f, testcase)
            f.close()


def main():
    global cmdline_options
    cmdline_options = parse_command_line()
    for path in cmdline_options.file:
        xml2file(path)


if __name__ == '__main__':
    main()
