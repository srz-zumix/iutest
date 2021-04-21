#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# iutest_compiler_error_test.py
#
# Copyright (C) 2015-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import re
import copy

from argparse import ArgumentParser
from argparse import FileType
from subprocess import Popen, PIPE, STDOUT


class ErrorMessage:
    file = ""
    line = 0
    type = ""
    message = ""
    parent = None
    child = None
    checked = False
    target = False
    expansion = False
    provided_for = False
    root_is_expansion = False
    included_from = []

    def set_type(self, str):
        s = str.strip()
        if s in {"error", u"エラー"}:
            self.type = "error"
        elif s in {"note", u"備考"}:
            self.type = "note"
        elif s in {"warning", u"警告"}:
            self.type = "warning"
        if s in {"error", "エラー"}:
            self.type = "error"
        elif s in {"note", "備考"}:
            self.type = "note"
        elif s in {"warning", "警告"}:
            self.type = "warning"
        else:
            self.type = s

    def is_error(self):
        if self.type == "error":
            return True
        return False

    def is_note(self):
        if self.type == "note":
            return True
        return False

    def is_iutest(self):
        if self.is_note() and self.message.find("IUTEST_TEST_COMPILEERROR") != -1:
            return True
        return False

    def is_type_none(self):
        if not self.type:
            return True
        return False

    def is_warning(self):
        if self.type == "warning":
            return True
        return False

    def is_type_root(self):
        if self.is_warning():
            return True
        if self.is_error():
            return True
        return False

    def has_error(self):
        if self.type == "error":
            return True
        elif self.parent and self.parent.has_error_parent():
            return True
        elif self.child and self.child.has_error_child():
            return True
        return False

    def has_error_parent(self):
        if self.type == "error":
            return True
        elif self.parent:
            return self.parent.has_error_parent()
        return False

    def has_error_child(self):
        if self.type == "error":
            return True
        elif self.child:
            return self.child.has_error_child()
        return False

    def is_checked(self):
        if self.checked:
            return True
        elif self.parent:
            return self.parent.is_checked()
        return False

    def is_provided_for(self):
        return self.provided_for

    def is_expansion(self):
        return self.expansion

    def is_tail(self):
        if self.child:
            return False
        return True

    def get_error(self):
        if self.type == "error":
            return self
        if self.parent:
            e = self.parent.get_error_parent()
            if e:
                return e
        if self.child:
            e = self.child.get_error_child()
            if e:
                return e
        return None

    def get_error_parent(self):
        if self.type == "error":
            return self
        elif self.parent:
            return self.parent.get_error_parent()
        return None

    def get_error_child(self):
        if self.type == "error":
            return self
        elif self.child:
            return self.child.get_error_child()
        return None

    def get_root_msg(self):
        if self.parent:
            return self.parent.get_root_msg()
        return self

    def get_source_msg(self):
        root = self.get_root_msg()
        if self.root_is_expansion:
            while root.child:
                if root.child.expansion:
                    root = root.child
                else:
                    break
        return root


class ExpectMessage:
    def __init__(self, msg, expect, expression):
        self.msg = msg
        self.expect = expect
        self.expression = expression


format_gcc = True
color_prompt = False


# command line option
def parse_command_line():
    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 0.4'
    )
    parser.add_argument(
        '-c',
        '--compiler',
        help='set compiler.',
        default='gcc'
    )
    parser.add_argument(
        '--passthrough',
        action='store_true',
        help='print input message.'
    )
    parser.add_argument(
        '--verbose',
        action='store_true',
        help='print input message when failed.'
    )
    parser.add_argument(
        '--allow-unknown-compiler',
        action='store_true',
        help='ignore unknown compiler.'
    )
    parser.add_argument(
        '--debug',
        action='store_true',
        help='debug.'
    )
    parser.add_argument(
        '--command',
        help='execute command.',
        default=None
    )
    if sys.version_info[0] >= 3:
        parser.add_argument(
            '-i',
            '--infile',
            type=FileType('r', encoding='UTF-8'),
            help='compiler stdout.',
            default=sys.stdin
        )
    else:
        parser.add_argument(
            '-i',
            '--infile',
            type=FileType('r'),
            help='compiler stdout.',
            default=sys.stdin
        )

    options = parser.parse_args()
    return options


def parse_gcc_clang(options, f, r_expansion, note_is_child, root_is_expansion):
    re_fatal = re.compile(r'(\S+)\s*:\s*fatal\s*error\s*.*')

    class rmessage:
        re_file_col = re.compile(r'(\S+):(\d+):(\d+):(.*)')
        re_file = re.compile(r'(\S+):(\d+):(.*)')
        re_infile = re.compile(r'In file included from (\S+):(\d+):(?:\d+|)(.*)')
        re_ininst = re.compile(r'(\S+):\s* (In instantiation of .*)')

        def __init__(self):
            self.m0 = None
            self.m1 = None
            self.m2 = None
            self.m3 = None

        def match(self, line):
            self.m0 = self.re_file_col.match(line)
            if self.m0:
                return True
            self.m1 = self.re_file.match(line)
            if self.m1:
                return True
            self.m2 = self.re_infile.match(line)
            if self.m2:
                return True
            self.m3 = self.re_ininst.match(line)
            if self.m3:
                return True
            return False

        def file(self):
            if self.m0:
                return self.m0.group(1)
            if self.m1:
                return self.m1.group(1)
            if self.m2:
                return self.m2.group(1)
            if self.m3:
                return self.m3.group(1)
            return None

        def line(self):
            if self.m0:
                return int(self.m0.group(2))
            if self.m1:
                return int(self.m1.group(2))
            if self.m2:
                return int(self.m2.group(2))
            return 0

        def message(self):
            if self.m0:
                return self.m0.group(4)
            if self.m1:
                return self.m1.group(3)
            if self.m2:
                return self.m2.group(3)
            if self.m3:
                return self.m3.group(2)
            return None

        def is_included_from(self):
            if self.m2:
                return True
            return False

    re_message = re.compile(r'.*:\d+:\s*(\S*):\s*(.*)')
    re_expansion = re.compile(r_expansion)
    re_declaration = re.compile(r'.*declaration of\s*(.*)')
    re_required_from = re.compile(r'.*(required|instantiated) from here')
    re_provided_for = re.compile(r'\s*provided for .*')
    msg_list = []
    included_from_list = []
    msg = None
    prev = None
    is_prev_required_from = False
    for line in f:
        if options.passthrough:
            print(line.rstrip())
        if re_fatal.match(line):
            raise Exception(line)

        m = rmessage()
        if m.match(line):
            if msg:
                msg.included_from = copy.deepcopy(included_from_list)
                msg_list.append(msg)
                included_from_list[:] = []
                prev = msg
            if m.is_included_from():
                inc = ErrorMessage()
                inc.file = m.file()
                inc.line = m.line()
                inc.type = 'In file included from'
                included_from_list.append(inc)
                msg = None
                continue
            msg = ErrorMessage()
            msg.file = m.file()
            msg.line = m.line()
            msg.type = ""
            msg.root_is_expansion = root_is_expansion
            n = re_message.match(line)
            if n:
                msg.set_type(n.group(1))
                msg.message += n.group(2)
            else:
                msg.set_type('')
                msg.message += m.message()

            is_child = note_is_child and msg.is_note()
            is_type_none = prev and prev.is_type_none()
            is_declaration = False
            n = re_declaration.match(line)
            if n and prev and prev.message.find(n.group(1)) != -1:
                is_declaration = True
            if re_provided_for.match(msg.message):
                msg.provided_for = True

            if prev:
                is_expansion = re_expansion.search(msg.message)
                msg.expansion = is_expansion
                # print('%s - %d: %s %s %s %s' % (msg.file, msg.line, is_child, is_type_none, is_declaration, is_expansion))
                if is_child or is_type_none or is_declaration or is_expansion or is_prev_required_from:
                    prev.child = msg
                    msg.parent = prev
            is_prev_required_from = re_required_from.search(msg.message)
        else:
            if msg:
                msg.message += '\n'
                msg.message += line
    msg_list.append(msg)
    return msg_list


def parse_gcc(options, f):
    return parse_gcc_clang(options, f, r'in (definition|expansion) of macro', False, True)


def parse_clang(options, f):
    return parse_gcc_clang(options, f, r'expanded from ', True, False)


def parse_vc(options, f):
    re_fatal = re.compile(r'(\S+)\s*:\s*fatal\s*error\s*.*')
    re_file = re.compile(r'(\s*)(\S+)\((\d+)\)\s*:\s*(.*)')
    re_message = re.compile(r'.*\(\d+\)\s*: (\S*)\s*(\S*: .*)')
    msg_list = []
    msg = None
    prev = None
    for line in f:
        if options.passthrough:
            print(line.rstrip())
        if re_fatal.match(line):
            raise Exception(line)

        m = re_file.match(line)
        if m:
            if msg:
                msg_list.append(msg)
                prev = msg
            msg = ErrorMessage()
            msg.file = m.group(2)
            msg.line = int(m.group(3))
            msg.type = ""
            n = re_message.match(line)
            if n:
                msg.set_type(n.group(1))
                msg.message += n.group(2)
            else:
                msg.set_type('')
                msg.message += m.group(4)

            child_note = m.group(1) or (msg.is_note() and not msg.is_iutest())
            if (m.group(1) or child_note) and prev:
                prev.child = msg
                msg.parent = prev
        else:
            if msg:
                msg.message += '\n'
                msg.message += line
    msg_list.append(msg)
    return msg_list


def dump_included_from(m):
    for inc in m.included_from:
        print("%s %s:%d:" % (inc.type, inc.file, inc.line))


def dump_msg(m):
    dump_included_from(m)
    s = m.file
    s += ':'
    if format_gcc:
        if m.line:
            s += '%d:' % (m.line)
        if not m.is_type_none():
            s += ' %s:' % (m.type)
        print("%s %s" % (s, m.message))
    else:
        if m.line:
            s += '(%d):' % (m.line)
        if m.parent:
            print("\t%s %s %s" % (s, m.type, m.message))
        else:
            print("%s %s %s" % (s, m.type, m.message))


def dump_msgs(m):
    if m.parent:
        dump_msgs(m.parent)
    dump_msg(m)


def dump_list(l):
    for m in l:
        if not m.parent:
            print('------------------------------')
        dump_msg(m)
        print('==')
        if not m.child:
            print('------------------------------')

    return True


def test_result(result, msg, e):
    OKGREEN = '\033[32m'
#   WARNING = '\033[33m'
    FAIL = '\033[31m'
    ENDC = '\033[0m'

    if e:
        msg += ': ' + e.file + ': ' + str(e.line)

    if result:
        if color_prompt:
            print(OKGREEN + '[OK] ' + ENDC + msg)
        else:
            print('[OK] ' + msg)
    else:
        if color_prompt:
            print(FAIL + '[NG] ' + ENDC + msg)
        else:
            print('[NG] ' + msg)


def iutest(l):
    result = True
    unexpected = []
    re_iutest = re.compile(r'IUTEST_TEST_COMPILEERROR\( ([^#]*) \)')
    checkList = []
    messageList = []
    for i, msg in enumerate(l):
        if not msg:
            continue
        mm = re_iutest.search(msg.message)
        if mm:
            root = msg.get_source_msg()
            if not root.target:
                expect = mm.group(1).strip('"')
                checkList.append(ExpectMessage(root, expect, mm.group(0)))
                root.target = True
        else:
            messageList.append(msg)

    for msg in messageList:
        if msg.has_error():
            #print('%s - %d' % (msg.file, msg.line))
            for check in checkList:
                if msg.file in check.msg.file and msg.line == check.msg.line + 1:
                    actual = msg.get_error()
                    #print(actual.message)
                    msg.checked = True
                    if not check.expect or re.search(check.expect, actual.message):
                        check.msg.checked = True
                        break
            if msg.is_tail() and not msg.is_checked() and not msg.is_provided_for():
                unexpected.append(msg)
        elif msg.is_warning():
            dump_msg(msg)

    for check in checkList:
        if check.msg.checked:
            test_result(True, check.expression, check.msg)
        else:
            test_result(False, check.expression, check.msg)
            result = False
    for msg in unexpected:
        test_result(False, "Unexpected error: " + msg.message, msg)
        result = False
    return result


def parse_output(options):
    global format_gcc
    l = None
    if options.command:
        args = re.split('\s+', options.command)
        for i in range(len(args)):
            args[i] = os.path.expandvars(args[i])
        p = Popen(args, stdout=PIPE, stderr=STDOUT)
        p.wait()
        out, err = p.communicate()
        f = out.decode('utf-8').splitlines()
    else:
        if not options.infile:
            raise Exception("infile null")
        #print(options.infile.encoding)
        f = options.infile
        #f = codecs.getreader('utf-8')(options.infile)

    if any(options.compiler.find(s) != -1 for s in ('clang', 'clang++', 'zapcc', 'zapcc++')):
        l = parse_clang(options, f)
    elif any(options.compiler.find(s) != -1 for s in ('gcc', 'g++')):
        l = parse_gcc(options, f)
    elif options.compiler == 'cl':
        format_gcc = False
        l = parse_vc(options, f)
    else:
        try:
            raise Exception("sorry, {0} compiler is not supported".format(options.compiler))
        except Exception as e:
            if options.allow_unknown_compiler:
                print(e)
                return True
            else:
                raise

    if options.debug:
        dump_list(l)
    if options.passthrough:
        print('----')
    result = iutest(l)
    if not result:
        if options.verbose:
            dump_list(l)
    return result

def setup():
    global color_prompt
    term = os.environ.get('TERM')
    if term:
        if any(term.find(s) for s in ('xterm', 'screen', 'rxvt', 'linux', 'cygwin')):
            color_prompt = True


def main():
    try:
        options = parse_command_line()
        setup()
        if not parse_output(options):
            sys.exit(1)
    except Exception as e:
        print(e)
        raise

if __name__ == '__main__':
    main()
