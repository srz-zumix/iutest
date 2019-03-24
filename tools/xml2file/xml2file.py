#!/usr/bin/env python
#
# xml2file.py
#
# Copyright (C) 2019, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import errno
import json
import codecs
import shutil
import tempfile
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
        type=int,
        default=0,
        metavar='LEVEL',
        help='log verbose'
    )
    parser.add_argument(
        '--encoding',
        default='utf-8',
        help='output file encoding.'
    )
    parser.add_argument(
        '--clean',
        action='store_true',
        help='clean output directory (before)'
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
    print(msg)


def logv(lv, msg):
    if cmdline_options.verbose >= lv:
        print(msg)


def logd(msg):
    if cmdline_options.debug:
        print(msg)


def loge(msg):
    sys.stderr.write(msg + "\n")


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            loge('failed mkdirs: ' + path)
            raise


def clean_dir(path):
    if os.path.exists(path):
        shutil.rmtree(path)


def fopen(path):
    dir = os.path.dirname(path)
    mkdir_p(dir)
    f = codecs.open(path, 'w', cmdline_options.encoding)
    return f


def make_rootpath(xml_filename):
    root_name = xml_filename
    path = os.path.join(cmdline_options.output, root_name)
    return path


def make_path(root_path, testsuite, testcase):
    suite_name = testsuite.attrib['name'].lstrip('/')
    case_name = testcase.attrib['name'].lstrip('/')
    ext = '.json'
    return os.path.join(os.path.join(root_path, suite_name), case_name + ext)


def get_properties_node(node):
    users = {}
    for prop in node:
        if ('name' in prop.attrib) and ('value' in prop.attrib):
            users[prop.attrib['name']] = prop.attrib['value']
    return users


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


def opentree(path):
    try:
        with codecs.open(path, 'r', encoding=cmdline_options.encoding) as f:
            return ET.parse(f)
    except Exception as e:
        loge("error: " + path + ": " + str(e))
        xmlp = ET.XMLParser(encoding=cmdline_options.encoding)
        return ET.parse(path, xmlp)


def xml2file(path):
    basename = os.path.basename(path)
    filename = os.path.splitext(basename)[0]
    logv(1, basename)

    root_path = make_rootpath(filename)
    clean_dir(root_path)

    try:
        tree = opentree(path)
        root = tree.getroot()
        testsuites = root

        testsuites_user_attrib = get_user_properties(testsuites)
        for testsuite in testsuites:
            logv(2, "  " + testsuite.attrib['name'])
            testsuite_user_attrib = get_user_properties(testsuite)
            for testcase in testsuite:
                if testcase.tag == 'testcase':
                    logv(3, "    " + testcase.attrib['name'])
                    f = fopen(make_path(root_path, testsuite, testcase))
                    write_result(f, testsuites_user_attrib, testsuite_user_attrib, testcase)
                    f.close()
                elif testcase.tag == 'properties':
                    testsuite_user_attrib.update(get_properties_node(testcase))
    except Exception as e:
        f = fopen(os.path.join(root_path, "parser_error.txt"))
        f.write(str(e))
        f.close()
        raise


def main():
    result=True
    global cmdline_options
    cmdline_options = parse_command_line()
    if cmdline_options.output is None:
        cmdline_options.output = tempfile.mkdtemp(prefix='xml2file')
    logd(sys.getfilesystemencoding())
    log("output: " + cmdline_options.output)
    if cmdline_options.clean:
        clean_dir(cmdline_options.output)
    for path in cmdline_options.file:
        try:
            xml2file(path)
        except Exception as e:
            loge("error: " + path + ": " + str(e))
            result = False
    if not result:
        exit(1)


if __name__ == '__main__':
    main()
