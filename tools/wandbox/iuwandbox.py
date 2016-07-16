#!/usr/bin/env python
#
# iuwandbox.py
#
# Copyright (C) 2014-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import codecs

from argparse import ArgumentParser
from wandbox import Wandbox
from requests.exceptions import HTTPError

IUTEST_FUSED_SRC = os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.min.hpp')
IUTEST_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*".*iutest\.hpp"')
EXPAND_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*?)"')


#
# command line option
def parse_command_line():
    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 4.2'
    )
    parser.add_argument(
        '--list_compiler',
        action='store_true',
        help='listup compiler.'
    )
    parser.add_argument(
        '--list_options',
        metavar='COMPILER',
        help='listup compiler options.'
    )
    parser.add_argument(
        '-c',
        '--compiler',
        default='gcc-head',
        help='compiler select. default: %(default)s'
    )
    parser.add_argument(
        '-x',
        '--options',
        help='used options for a compiler.'
    )
    parser.add_argument(
        '--default',
        action='store_true',
        help='use default options.'
    )
    parser.add_argument(
        '--boost',
        metavar='VERSION',
        help='set boost options version X.XX or nothing.'
    )
    parser.add_argument(
        '--sprout',
        action='store_true',
        help='use sprout.'
    )
    parser.add_argument(
        '--msgpack',
        action='store_true',
        help='use msgpack.'
    )
    parser.add_argument(
        '--stdin',
        help='set stdin.'
    )
    parser.add_argument(
        '-f',
        '--compiler_option_raw',
        metavar='OPTIONS',
        action='append',
        default=['-D__WANDBOX__'],
        help='compile-time any additional options.'
    )
    parser.add_argument(
        '-r',
        '--runtime_option_raw',
        metavar='OPTIONS',
        action='append',
        help='runtime-time any additional options.'
    )
    parser.add_argument(
        '-s',
        '--save',
        action='store_true',
        help='generate permanent link.'
    )
    parser.add_argument(
        '--permlink',
        metavar='ID',
        help='get permanent link.'
    )
    parser.add_argument(
        '-o',
        '--output',
        metavar='FILE',
        help='output source code.'
    )
    parser.add_argument(
        '--xml',
        metavar='FILE',
        help='output result xml.'
    )
    parser.add_argument(
        '--junit',
        metavar='FILE',
        help='output result junit xml.'
    )
    parser.add_argument(
        '--stderr',
        action='store_true',
        help='output stderr.'
    )
    parser.add_argument(
        '--encoding',
        help='set encoding.'
    )
    parser.add_argument(
        '--expand_include',
        action='store_true',
        help='expand include file.'
    )
    parser.add_argument(
        '--check_config',
        action='store_true',
        help='check config.'
    )
    parser.add_argument(
        '--verbose',
        action='store_true',
        help='verbose.'
    )
    parser.add_argument(
        '--dryrun',
        action='store_true',
        help='dryrun.'
    )
    parser.add_argument(
        'code',
        metavar='CODE',
        nargs='?',
        help='source code file'
    )
    options = parser.parse_args()
    return options, parser


# file open
def file_open(path, mode, encoding):
    if encoding:
        file = codecs.open(path, mode, encoding)
    else:
        file = open(path, mode)
    return file


# make include filename
def make_include_filename(path, includes, included_files):
    if path in included_files:
        return included_files[path]
    else:
        include_dir, include_filename = os.path.split(path)
        while include_filename in includes:
            include_dir, dirname = os.path.split(include_dir) 
            include_filename = dirname + '__' + include_filename
        included_files[path] = include_filename
        return include_filename


# make code
def make_code(path, encoding, expand, includes, included_files):
    code = ''
    file = file_open(path, 'r', encoding)
    for line in file:
        m = IUTEST_INCLUDE_REGEX.match(line)
        if m:
            code += '#include "iutest.hpp"\n'
            code += '//origin>> ' + line
            if 'iutest.hpp' not in includes:
                f = codecs.open(IUTEST_FUSED_SRC, 'r', 'utf-8-sig')
                includes['iutest.hpp'] = f.read()
        else:
            m = EXPAND_INCLUDE_REGEX.match(line)
            if m:
                include_path = os.path.join(os.path.dirname(path), m.group(1))
                if os.path.exists(include_path):
                    expand_include_file_code = make_code(include_path, encoding, expand, includes, included_files)
                    if expand:
                        code += expand_include_file_code
                        code += '//origin>> '
                    else:
                        include_abspath = os.path.abspath(include_path)
                        include_filename = make_include_filename(include_abspath, includes, included_files)
                        code += '#include "' + include_filename + '"\n'
                        code += '//origin>> '
                        if include_filename not in includes:
                            includes[include_filename] = expand_include_file_code
            code += line
    file.close()
    return code


# check config
def check_config(options):
    if not find_compiler(options.compiler):
        print('Wandbox is not supported compiler [' + options.compiler + ']')
        listup_compiler()
        sys.exit(1)


# setup includes
def setup_includes(w, includes):
    for filename,code in includes.items():
        w.add_file(filename, code)


# run wandbox
def run_wandbox(code, includes, options):
    w = Wandbox()
    w.compiler(options.compiler)
    opt = []
    if options.options:
        opt = options.options.split(',')
    elif options.default:
        opt = get_default_options(options.compiler)
    if options.boost:
        opt = list(filter(lambda s: s.find('boost') == -1, opt))
        opt.append('boost-' + str(options.boost))
    if options.sprout and 'sprout' not in opt:
        opt.append('sprout')
    if options.msgpack and 'msgpack' not in opt:
        opt.append('msgpack')
    w.options(','.join(opt))
    if options.stdin:
        w.stdin(options.stdin)
    if options.compiler_option_raw:
        co = '\n'.join(options.compiler_option_raw)
        co = co.replace('\\n', '\n')
        if options.compiler == "clang-3.5":
            co += "\n-DIUTEST_HAS_HDR_CXXABI=0"
        if options.compiler in ["clang-3.2", "clang-3.1", "clang-3.0"]:
            co += "\n-Qunused-arguments"
        w.compiler_options(co)
    if options.runtime_option_raw:
        ro = ''
        for opt in options.runtime_option_raw:
            ro += opt + '\n'
        ro = ro.replace('\\n', '\n')
        w.runtime_options(ro)
    if options.save:
        w.permanent_link(options.save)
    if options.verbose:
        w.dump()
    w.code(code)
    setup_includes(w, includes)
    if options.dryrun:
        sys.exit(0)
    def run(retries):
        try:
            return w.run()
        except HTTPError as e:
            if e.response.status_code == 504 and retries > 0:
                print(e.message)
                return run(retries-1)
            else:
                raise
        except:
            raise
    return run(3)


# show result
def show_result(r, options):
    if 'error' in r:
        print(r['error'])
        sys.exit(1)
    if options.stderr:
        if 'compiler_output' in r:
            print('compiler_output:')
            print(r['compiler_output'].encode('utf_8'))
        if 'compiler_error' in r:
            sys.stderr.write(r['compiler_error'].encode('utf_8'))
        if 'program_output' in r:
            print('program_output:')
            print(r['program_output'].encode('utf_8'))
        if options.xml is None and options.junit is None and 'program_error' in r:
            sys.stderr.write(r['program_error'].encode('utf_8'))
    else:
        if 'compiler_message' in r:
            print('compiler_message:')
            print(r['compiler_message'].encode('utf_8'))
        if 'program_message' in r:
            print('program_message:')
            print(r['program_message'].encode('utf_8'))
    if 'url' in r:
        print('permlink: ' + r['permlink'])
        print('url: ' + r['url'])
    if 'signal' in r:
        print('signal: ' + r['signal'])
    if 'status' in r:
        return int(r['status'])
    return 1


# show parameter
def show_parameter(r):
    if 'compiler' in r:
        print('compiler:' + r['compiler'])
    if 'options' in r:
        print('options:' + r['options'])
    if 'compiler-option-raw' in r:
        print('compiler-option-raw:' + r['compiler-option-raw'])
    if 'runtime-option-raw' in r:
        print('runtime-option-raw' + r['runtime-option-raw'])
    if 'created-at' in r:
        print(r['created-at'])


def set_output_xml(options, t, xml):
    options.stderr = True
    if options.runtime_option_raw:
        options.runtime_option_raw.append("--iutest_output=" + t + ":" + xml)
    else:
        options.runtime_option_raw = ["--iutest_output=" + t + ":" + xml]


def run(options):
    filepath = options.code
    if not os.path.exists(filepath):
        sys.exit(1)
    includes = {}
    included_files = {}
    code = make_code(filepath, options.encoding, options.expand_include, includes, included_files)
    if options.output:
        f = file_open(options.output, 'w', options.encoding)
        f.write(code)
        f.close()
    xml = None
    if options.xml:
        xml = options.xml
        set_output_xml(options, 'xml', xml)
    if options.junit:
        xml = options.junit
        set_output_xml(options, 'junit', xml)
    r = run_wandbox(code, includes, options)
    b = show_result(r, options)
    if xml and 'program_error' in r:
        f = file_open(xml, 'w', options.encoding)
        f.write(r['program_error'])
        f.close()
    sys.exit(b)


# listup compiler
def listup_compiler(verbose):
    w = Wandbox()
    r = w.get_compiler_list()
    for d in r:
        if d['language'] == 'C++':
            if verbose:
                print(d['name'] + ' (' + d['version'] + ')')
            else:
                print(d['name'])


# find compiler
def find_compiler(c):
    w = Wandbox()
    r = w.get_compiler_list()
    for d in r:
        if d['language'] == 'C++' and d['name'] == c:
            return True
    return False


# listup options
def listup_options(compiler):
    w = Wandbox()
    r = w.get_compiler_list()
    for d in r:
        if d['name'] == compiler:
            if 'switches' in d:
                switches = d['switches']
                for s in switches:
                    if 'name' in s:
                        if s['default']:
                            print(s['name'] + ' (default)')
                        else:
                            print(s['name'])
                    elif 'options' in s:
                        print(s['default'] + ' (default)')
                        for o in s['options']:
                            print('  ' + o['name'])


# get default options
def get_default_options(compiler):
    w = Wandbox()
    r = w.get_compiler_list()
    opt = []
    for d in r:
        if d['name'] == compiler:
            if 'switches' in d:
                switches = d['switches']
                for s in switches:
                    if 'name' in s:
                        if s['default']:
                            opt.append(s['name'])
                    elif 'options' in s:
                        opt.append(s['default'])
    return opt


# get permlink
def get_permlink(options):
    w = Wandbox()
    r = w.get_permlink(options.permlink)
    p = r['parameter']
    show_parameter(p)
    print('result:')
    b = show_result(r['result'], options)
    if options.output:
        f = open(options.output, 'w')
        f.write(p['code'])
        f.close()
    sys.exit(b)


def main():
    options, parser = parse_command_line()
    if options.list_compiler:
        listup_compiler(options.verbose)
    elif options.list_options:
        listup_options(options.list_options)
    elif options.permlink:
        get_permlink(options)
    else:
        if options.check_config:
            check_config(options)
        elif options.code is None:
            parser.print_help()
            sys.exit(1)
        run(options)

if __name__ == '__main__':
    main()
