#!/usr/bin/env python
#
# iupaizaio.py
#
# Copyright (C) 2015-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import codecs
import paizaio

from argparse import ArgumentParser
from paizaio import PaizaIO
from iupaizaio_pp import PaizaPreprocessor

IUTEST_FUSED_SRC = os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.min.hpp')
IUTEST_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*".*iutest\.hpp"')
EXPAND_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*?)"')


# command line option
def parse_command_line():
    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 0.2'
    )
    parser.add_argument(
        '--stdin',
        help='set stdin.'
    )
    parser.add_argument(
        '-o',
        '--output',
        help='output source code.'
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
        '--use-main',
        action='store_true',
        help='IUTEST_USE_MAIN.'
    )
    parser.add_argument(
        'code',
        metavar='CODE',
        help='source code file'
    )
    options = parser.parse_args()
    return options


# file open
def file_open(path, mode, encoding):
    if encoding:
        file = codecs.open(path, mode, encoding)
    else:
        file = open(path, mode)
    return file


# make code
def make_code(path, encoding, expand):
    code = ''
    file = file_open(path, 'r', encoding)
    for line in file:
        m = IUTEST_INCLUDE_REGEX.match(line)
        if m:
            f = codecs.open(IUTEST_FUSED_SRC, 'r', 'utf-8-sig')

            code += '//========================================================>>>> ' + line
            code += f.read()
            code += '//========================================================<<<< ' + line
        else:
            if expand:
                m = EXPAND_INCLUDE_REGEX.match(line)
                if m:
                    include_path = os.path.join(os.path.dirname(path), m.group(1))
                    if os.path.exists(include_path):
                        code += make_code(include_path, encoding, expand)
                        code += '// '
            code += line
    file.close()
    return code


# run paiza
def run_paiza(code, options):
    paiza = PaizaIO()
    paiza.longpoll(True)
    paiza.longpoll_timeout(100)
    paiza.code(code)
    return paiza.run()


# show result
def show_result(r):
    if 'error' in r:
        print(r['error'])
        sys.exit(1)
    build_result = r['build_result']
    if 'success' in build_result:
        if 'stdout' in r:
            print('stdout:')
            print(r['stdout'])
        if 'stderr' in r:
            print('stderr:')
            print(r['stderr'])
        if 'time' in r:
            print('time:')
            print(r['time'])
        if 'memory' in r:
            print('memory:')
            print(r['memory'])
        if 'exit_code' in r:
            return int(r['exit_code'])
    else:
        if 'build_stderr' in r:
            print(r['build_stderr'])
        if 'build_exit_code' in r:
            return int(r['build_exit_code'])

    return 1


# output code
def output_code(path, code, encoding):
    f = file_open(path, 'w', encoding)
    f.write(code)
    f.close()


def run_impl(code, options):
    r = run_paiza(code, options)
    b = show_result(r)
    sys.exit(b)


# run
def run(options):
    filepath = options.code
    if not os.path.exists(filepath):
        sys.exit(1)
    code = make_code(filepath, options.encoding, options.expand_include)
    if options.output:
        output_code(options.output, code, options.encoding)
    try:
        run_impl(code, options)
    except paizaio.TooLongException as e:
        print(e)
        if not options.output:
            output = "paizaio-toolong-sourcecode.cpp"
            output_code(output, code, options.encoding)
            print("source code -> " + output)
        try:
            pp = PaizaPreprocessor()
            macros = {}
            if options.use_main:
                macros['IUTEST_USE_MAIN'] = '1'
            code = pp.preprocess(code, macros)
            output_code("paizaio-sourcecode.cpp", code, options.encoding)
            run_impl(code, options)
        except paizaio.TooLongException as e:
            print(e)
            sys.exit(1)
        except Exception as e:
            print(e)
            raise
    except:
        raise


def main():
    options = parse_command_line()
    run(options)


if __name__ == '__main__':
    main()
