#!/usr/bin/env python
#
# iuwandbox.py
#
# Copyright (C) 2014-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import codecs

from argparse import ArgumentParser
from argparse import SUPPRESS
from wandbox import Wandbox

IUTEST_FUSED_SRC = os.path.normpath(os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.min.hpp'))
IUTEST_WANDBOX_FUSED_SRC = os.path.normpath(os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.wandbox.min.hpp'))
IUTEST_WANDBOX_FUSED_CLANG_SRC = os.path.normpath(os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.wandbox.min.clang.hpp'))
IUTEST_WANDBOX_FUSED_GCC_SRC = os.path.normpath(os.path.join(os.path.dirname(__file__), '../../fused-src/iutest.wandbox.min.gcc.hpp'))
IUTEST_INCLUDE_PATH = os.path.normpath(os.path.join(os.path.dirname(__file__), '../../include'))
IUTEST_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*".*(iutest|iutest_switch)\.hpp"')
EXPAND_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*"(.*?)"')
IUTEST_INCG_REGEX = re.compile(r'\s*#\s*define[/\s]*(INCG_IRIS_\S*)\s*')

iutest_src_map = {
    'wandbox': {
        'any': IUTEST_WANDBOX_FUSED_SRC,
        'clang': IUTEST_WANDBOX_FUSED_CLANG_SRC,
        'gcc': IUTEST_WANDBOX_FUSED_GCC_SRC,
    },
    'min': {
        'any': IUTEST_FUSED_SRC,
    }
}

iutest_incg_list = []
workaround = True
api_retries = 3
api_retry_wait = 60
fused_src = 'wandbox'


# command line option
def parse_command_line():
    global api_retries
    global api_retry_wait
    global fused_src

    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 8.0'
    )
    parser.add_argument(
        '--list-compiler',
        '--list_compiler',
        action='store_true',
        help='listup compiler.'
    )
    parser.add_argument(
        '--list-options',
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
        help='--default option is deprecated. default options are always set.'
    )
    parser.add_argument(
        '--no-default',
        action='store_true',
        help='no set default options.'
    )
    parser.add_argument(
        '--std',
        metavar='VERSION',
        help='set --std options.'
    )
    parser.add_argument(
        '--boost',
        metavar='VERSION',
        help='set boost options version X.XX or nothing.'
    )
    parser.add_argument(
        '--optimize',
        action='store_true',
        help='use optimization.'
    )
    parser.add_argument(
        '--cpp-verbose',
        action='store_true',
        help='use cpp-verbose.'
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
        '--compiler-option-raw',
        '--compiler_option_raw',
        metavar='OPTIONS',
        action='append',
        default=['-D__WANDBOX__'],
        help='compile-time any additional options.'
    )
    parser.add_argument(
        '-r',
        '--runtime-option-raw',
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
        '--expand-include',
        '--expand_include',
        action='store_true',
        help='expand include file.'
    )
    parser.add_argument(
        '--make',
        action='store_true',
        help=SUPPRESS
    )
    parser.add_argument(
        '--retry-wait',
        type=int,
        default=api_retry_wait,
        metavar='SECONDS',
        help='Wait time for retry when HTTPError occurs'
    )
    parser.add_argument(
        '--retry',
        type=int,
        default=api_retries,
        metavar='COUNT',
        help='Number of retries when HTTPError occurs'
    )
    parser.add_argument(
        '--check-config',
        '--check_config',
        action='store_true',
        help='check config.'
    )
    parser.add_argument(
        '--iutest-use-main',
        action='store_true',
        help='define IUTEST_USE_MAIN.'
    )
    parser.add_argument(
        '--iutest-use-wandbox-min',
        action='store_true',
        default=True,
        help='!this option is deprecated! use iutest.wandbox.min.hpp (default true).'
    )
    parser.add_argument(
        '--no-iutest-use-wandbox-min',
        action='store_true',
        help='not use iutest.wandbox.min.hpp (experimental).'
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
        nargs='*',
        help='source code file'
    )
    options = parser.parse_args()
    api_retries = options.retry
    api_retry_wait = options.retry_wait
    if options.no_iutest_use_wandbox_min:
        fused_src = "min"
    else:
        fused_src = "wandbox"
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
    include_dir, include_filename = os.path.split(path)
    while include_filename in includes:
        include_dir, dirname = os.path.split(include_dir)
        include_filename = dirname + '__' + include_filename
    included_files[path] = include_filename
    return include_filename


def is_iutest_included_file(filepath):
    if os.path.abspath(filepath).startswith(IUTEST_INCLUDE_PATH):
        incg = 'INCG_IRIS_' + os.path.basename(filepath).upper().replace('.', '_')
        for included_incg in iutest_incg_list:
            if included_incg.startswith(incg):
                return True
    return False


def select_fused_src(compiler, group):
    if group not in iutest_src_map:
        return IUTEST_WANDBOX_FUSED_SRC
    cxx = 'any'
    if 'clang' in compiler:
        cxx = 'clang'
    elif 'gcc' in compiler:
        cxx = 'gcc'

    if cxx not in iutest_src_map[group]:
        return iutest_src_map[group]['any']
    return iutest_src_map[group][cxx]


# make code
def make_code(path, compiler, encoding, expand, includes, included_files):
    code = ''
    file = file_open(path, 'r', encoding)
    for line in file:
        m = IUTEST_INCLUDE_REGEX.match(line)
        if m:
            code += '#include "iutest.hpp"\n'
            code += '//origin>> ' + line
            if 'iutest.hpp' not in includes:
                fused_src_path = select_fused_src(compiler, fused_src)
                try:
                    f = codecs.open(fused_src_path, 'r', 'utf-8-sig')
                    iutest_src = f.read()
                    f.close()
                    includes['iutest.hpp'] = iutest_src
                    global iutest_incg_list
                    iutest_incg_list = IUTEST_INCG_REGEX.findall(iutest_src)
                except Exception:
                    print('{0} is not found...'.format(fused_src_path))
                    print('please try \"make fused\"')
                    exit(1)
        else:
            m = EXPAND_INCLUDE_REGEX.match(line)
            if m:
                include_path = os.path.normpath(os.path.join(os.path.dirname(path), m.group(1)))
                if is_iutest_included_file(include_path):
                    code += '//origin>> '
                elif os.path.exists(include_path):
                    if expand:
                        expand_include_file_code = make_code(
                            include_path, compiler, encoding, expand, includes, included_files)
                        code += expand_include_file_code
                        code += '//origin>> '
                    else:
                        include_abspath = os.path.abspath(include_path)
                        include_filename = make_include_filename(
                            include_abspath, includes, included_files)
                        if not include_filename == include_path:
                            code += '#include "' + include_filename + '"\n'
                            code += '//origin>> '
                        if include_filename not in includes:
                            includes[include_filename] = ''
                            expand_include_file_code = make_code(
                                include_path, compiler, encoding, expand, includes, included_files)
                            includes[include_filename] = expand_include_file_code
            code += line
    file.close()
    return code


def print_undefined_option(option_name, compiler):
    print('Wandbox is not supported option [{0}] ({1})'.format(option_name, compiler))


def change_std_option(options, new_value):
    print('  change std option: {0} -> {1}'.format(options.std, new_value))
    options.std = new_value


def check_std_option_compatible(options, old, new, optlist):
    if (options.std == old) and (new in optlist):
        print('  [{0}] is not supported option. you can use [{1}]'.format(old, new))
        change_std_option(options, new)
        return True
    elif (options.std == new) and (old in optlist):
        print('  [{0}] is not supported option. you can use [{1}]'.format(new, old))
        change_std_option(options, old)
        return True
    return False

# check config
def check_config(options):
    has_error = False
    if not find_compiler(options.compiler):
        print('Wandbox is not supported compiler [' + options.compiler + ']')
        listup_compiler(options.verbose)
        has_error = True
    if options.options or options.std:
        opt = get_options(options.compiler)
        if options.options:
            for o in options.options.split(','):
                if o not in opt:
                    print_undefined_option(o, options.compiler)
                    has_error = True
        if options.std:
            if options.std not in opt:
                print_undefined_option(options.std, options.compiler)
                prev_std_option = options.std
                if  check_std_option_compatible(options, 'c++1z', 'c++17', opt) or \
                    check_std_option_compatible(options, 'gnu++1z', 'gnu++17', opt) or \
                    check_std_option_compatible(options, 'c++1y', 'c++14', opt) or \
                    check_std_option_compatible(options, 'gnu++1y', 'gnu++14', opt) or \
                    check_std_option_compatible(options, 'c++0x', 'c++11', opt) or \
                    check_std_option_compatible(options, 'gnu++0x', 'gnu++11', opt):
                    pass
                if (options.std == prev_std_option):
                    has_error = True
        if has_error:
            listup_options(options.compiler)
    if has_error:
        sys.exit(1)
    if options.default:
        print('--default option is deprecated. default options are always set.')


# setup additional files
def add_files(w, fileinfos):
    for filename, code in fileinfos.items():
        w.add_file(filename, code)


# create opt list
def create_option_list(options):
    def filterout_cppver(opt):
        tmp = list(filter(lambda s: s.find('c++') == -1, opt))
        tmp = list(filter(lambda s: s.find('gnu++') == -1, tmp))
        return tmp
    def find_cppname(opt):
        if any((x.startswith('c++') for x in opt)):
            return 'c++'
        return 'gnu++'
    opt = []
    if not options.no_default:
        opt = get_default_options(options.compiler)
    if options.options:
        for o in options.options.split(','):
            if o not in opt:
                if (o.find('c++') == 0) or (o.find('gnu++') == 0):
                    opt = filterout_cppver(opt)
                opt.append(o)
    # std
    if options.std:
        opt = filterout_cppver(opt)
        opt.append(options.std)
    # optimize
    if options.optimize and ('optimize' not in opt):
        opt.append('optimize')
    # cpp-verbose
    if options.cpp_verbose and ('cpp-verbose' not in opt):
        opt.append('cpp-verbose')
    # boost
    if workaround:
        if options.compiler in ['clang-3.1']:
            cppname = find_cppname(opt)
            opt = filterout_cppver(opt)
            opt.append(cppname + '98')
#        if options.compiler in ['clang-3.4', 'clang-3.3']:
#            if not options.boost:
#                options.boost = 'nothing'
    if options.boost:
        if options.compiler not in options.boost:
            options.boost = options.boost + '-' + options.compiler
        opt = list(filter(lambda s: s.find('boost') == -1, opt))
        opt.append('boost-' + str(options.boost))
    # sprout
    if options.sprout and ('sprout' not in opt):
        opt.append('sprout')
    # msgpack
    if options.msgpack and ('msgpack' not in opt):
        opt.append('msgpack')
    return opt


def expand_wandbox_options(w, compiler, options):
    colist = []
    defs = {}
    for d in w.get_compiler_list():
        if d['name'] == compiler:
            if 'switches' in d:
                switches = d['switches']
                for s in switches:
                    if 'options' in s:
                        for o in s['options']:
                            if ('name' in o) and ('display-flags' in o):
                                defs[o['name']] = o['display-flags']
                    elif ('name' in s) and ('display-flags' in s):
                        defs[s['name']] = s['display-flags']
    for opt in options:
        if opt in defs:
            colist.extend(defs[opt].split())
    return colist


def wandbox_api_call(callback, retries, retry_wait):
    return Wandbox.Call(callback, retries, retry_wait)


def wandbox_get_compilerlist():
    return wandbox_api_call(Wandbox.GetCompilerList, api_retries, api_retry_wait)


def wandbox_get_compilerswitches(compiler):
    for d in wandbox_get_compilerlist():
        if d['name'] == compiler:
            if 'switches' in d:
                return d['switches']
    return []


def run_wandbox_impl(w, options):
    if options.dryrun:
        sys.exit(0)
    retries = options.retry

    def run():
        return w.run()
    return wandbox_api_call(run, retries, options.retry_wait)


def create_compiler_raw_option_list(options):
    colist = []
    if options.compiler_option_raw:
        raw_options = options.compiler_option_raw
        for x in raw_options:
            colist.extend(re.split('\s(?=-)', x.strip('"')))
    if options.iutest_use_main:
        if len(options.code) < 2:
            colist.append('-DIUTEST_USE_MAIN')
    if '-D__WANDBOX__' not in colist:
        colist.append('-D__WANDBOX__')
    return colist


def get_compiler_exec(compiler):
    if 'gcc' in compiler:
        return 'g++'
    if 'clang' in compiler:
        return 'clang++'
    if 'zapcc' in compiler:
        return 'zapcc++'
    return None


# run wandbox (makefile)
def run_wandbox_make(main_filepath, code, includes, implements, options):
    with Wandbox() as w:
        w.compiler('bash')
        woptions = create_option_list(options)
        if options.stdin:
            w.stdin(options.stdin)
        implements[os.path.basename(main_filepath)] = code

        colist = create_compiler_raw_option_list(options)
        colist.extend(expand_wandbox_options(w, options.compiler, woptions))

        rolist = []
        if options.runtime_option_raw:
            for opt in options.runtime_option_raw:
                rolist.extend(opt.split())

        makefile = '#!/bin/make\n# generate makefile by iuwandbox.py\n'
        cxx = get_compiler_exec(options.compiler)
        if cxx is None:
            print('failed: invalid compiler...')
            sys.exit(1)
        makefile += '\nCXX=/opt/wandbox/' + options.compiler + '/bin/' + cxx
        makefile += '\nCXXFLAGS+='
        for opt in colist:
            makefile += opt + ' '
        makefile += '\nOBJS='
        for filename in implements.keys():
            makefile += os.path.splitext(filename)[0] + '.o '

        makefile += '\n\
prog: $(OBJS)\n\
\t$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)\n\
'

        implements['Makefile'] = makefile

        bashscript = 'make -j 4\n'
        bashscript += './prog '
        for opt in rolist:
            bashscript += opt + ' '
        bashscript += '\n'
        w.code(bashscript)

        if options.save:
            w.permanent_link(options.save)
        if options.verbose:
            w.dump()
        add_files(w, implements)
        add_files(w, includes)

        return run_wandbox_impl(w, options)


# run wandbox (cxx)
def run_wandbox_cxx(code, includes, implements, options):
    with Wandbox() as w:
        w.compiler(options.compiler)
        woptions = ','.join(create_option_list(options))
        w.options(woptions)
        if options.stdin:
            w.stdin(options.stdin)
        colist = create_compiler_raw_option_list(options)

        if workaround:
            if options.compiler in ['clang-3.2']:
                colist.append('-ftemplate-depth=1024')
    #        if options.compiler in ['clang-3.4']:
    #            colist.append('-DIUTEST_HAS_HDR_CXXABI=0')
    #        if options.compiler in ['clang-3.3', 'clang-3.2', 'clang-3.1', 'clang-3.0']:
    #            colist.append('-Qunused-arguments')
            if 'boost-nothing' in woptions:
                if options.compiler in ['clang-3.4', 'clang-3.3']:
                    colist.append('-fno-exceptions')
                    colist.append('-fno-rtti')
            # if 'gcc' in options.compiler:
            #     colist.append('-flarge-source-files')
        if colist:
            co = '\n'.join(colist)
            co = co.replace('\\n', '\n')
            w.compiler_options(co)
        if options.runtime_option_raw:
            rolist = []
            for opt in options.runtime_option_raw:
                rolist.extend(opt.split())
            ro = '\n'.join(rolist)
            ro = ro.replace('\\n', '\n')
            w.runtime_options(ro)
        if options.save:
            w.permanent_link(options.save)
        for filename in implements.keys():
            w.add_compiler_options(filename)
        if options.verbose:
            w.dump()
        w.code(code)
        add_files(w, implements)
        add_files(w, includes)

        return run_wandbox_impl(w, options)


# run wandbox
def run_wandbox(main_filepath, code, includes, implements, options):
    if options.make:
        return run_wandbox_make(main_filepath, code, includes, implements, options)
    return run_wandbox_cxx(code, includes, implements, options)


def wandbox_hint(r):
    if 'compiler_error' in r:
        if 'undefined reference to `main' in r['compiler_error']:
            print('hint:')
            print('  In "iutest" you can omit the definition of the main function, please define IUTEST_USE_MAIN. (--iutest-use-main or -f"-DIUTEST_USE_MAIN")')
        elif 'undefined reference to `init_unit_test_suite' in r['compiler_error']:
            print('hint:')
            print('  If you do not use boost test, please specify the file with the main function first.')


def text_transform(value):
    try:
        if isinstance(value, str):
            return value.decode()
        elif isinstance(value, unicode):
            return value.encode('utf_8')
    except Exception:
        pass
    return value


# show result
def show_result(r, options):
    if r is None:
        print('failed: timeout...')
        sys.exit(1)
    if 'error' in r:
        print(r['error'])
        sys.exit(1)
    if options.stderr:
        if 'compiler_output' in r:
            print('compiler_output:')
            print(text_transform(r['compiler_output']))
        if 'compiler_error' in r:
            sys.stderr.write(text_transform(r['compiler_error']))
        if 'program_output' in r:
            print('program_output:')
            print(text_transform(r['program_output']))
        if options.xml is None and options.junit is None and 'program_error' in r:
            sys.stderr.write(text_transform(r['program_error']))
    else:
        if 'compiler_message' in r:
            print('compiler_message:')
            print(text_transform(r['compiler_message']))
        if 'program_message' in r:
            print('program_message:')
            print(text_transform(r['program_message']))
    if 'url' in r:
        print('permlink: ' + r['permlink'])
        print('url: ' + r['url'])
    if 'signal' in r:
        print('signal: ' + r['signal'])
    wandbox_hint(r)

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
        options.runtime_option_raw.append('--iutest_output=' + t + ':' + xml)
    else:
        options.runtime_option_raw = ['--iutest_output=' + t + ':' + xml]


def run(options):
    main_filepath = options.code[0].strip()
    if not os.path.exists(main_filepath):
        sys.exit(1)
    includes = {}
    included_files = {}
    implements = {}
    code = ""
    if len(options.code) > 1 and options.iutest_use_main:
        code += '#define IUTEST_USE_MAIN\n'
    code += make_code(main_filepath, options.compiler, options.encoding, options.expand_include, includes, included_files)


    for filepath_ in options.code[1:]:
        filepath = filepath_.strip()
        implements[os.path.basename(filepath)] = make_code(filepath,
            options.compiler, options.encoding, options.expand_include, includes, included_files)

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
    r = run_wandbox(main_filepath, code, includes, implements, options)
    b = show_result(r, options)
    if xml and 'program_error' in r:
        f = file_open(xml, 'w', options.encoding)
        f.write(r['program_error'])
        f.close()
    sys.exit(b)


# listup compiler
def listup_compiler(verbose):
    r = wandbox_get_compilerlist()
    for d in r:
        if d['language'] == 'C++':
            if verbose:
                print(d['name'] + ' (' + d['version'] + ')')
            else:
                print(d['name'])


# find compiler
def find_compiler(c):
    r = wandbox_get_compilerlist()
    for d in r:
        if d['language'] == 'C++' and d['name'] == c:
            return True
    return False


# listup options
def listup_options(compiler):
    r = wandbox_get_compilerlist()
    for d in r:
        if d['name'] == compiler:
            print('# ' + compiler)
            if 'switches' in d:
                switches = d['switches']
                for s in switches:
                    try:
                        if 'options' in s:
                            default_option = s['default']
                            if 'name' in s:
                                print(s['name'])
                            for o in s['options']:
                                if o['name'] == default_option:
                                    print('  ' + o['name'] + ' (default)')
                                else:
                                    print('  ' + o['name'])
                        elif 'name' in s:
                            if s['default']:
                                print(s['name'] + ' (default)')
                            else:
                                print(s['name'])
                    except KeyError:
                        print("unknown format:")
                        print(s)


def get_options(compiler):
    opt = []
    for s in wandbox_get_compilerswitches(compiler):
        if 'options' in s:
            opt.append(s['default'])
            for o in s['options']:
                opt.append(o['name'])
        elif 'name' in s:
            opt.append(s['name'])
    return opt


# get default options
def get_default_options(compiler):
    opt = []
    for s in wandbox_get_compilerswitches(compiler):
        if 'options' in s:
            opt.append(s['default'])
        elif 'name' in s:
            if s['default']:
                opt.append(s['name'])
    return opt


# get permlink
def get_permlink(options):
    r = Wandbox.GetPermlink(options.permlink)
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
        elif not options.code:
            parser.print_help()
            sys.exit(1)
        run(options)


if __name__ == '__main__':
    main()
