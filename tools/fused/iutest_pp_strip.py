#!/usr/bin/env python
#
# iutest_pp_strip.py
#
# Copyright (C) 2018, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import re

RE_MACRO_SPLIT = re.compile('([\(\):;{} /%+\-=<>!&\|*#]+)')
RE_SPLIT_PAREN = re.compile('([\(\)])')
RE_FUNC_MACRO = re.compile('([\w_]+)\((.*?)\)')
RE_DEFINE = re.compile('#\s*define (\S+)\s*(.*)$')
RE_DEFINE_PARSE = re.compile('(.*)defined\((.*?)\)(.*)')
RE_HAS_INCLUDE = re.compile('(.*)__has_include\((.*?)\)(.*)')
RE_HAS_FEATURE = re.compile('(.*)__has_feature\((.*?)\)(.*)')
RE_SPLIT_OP = re.compile('(&&|\|\||!)')
RE_SYMBOLMARK = re.compile('([+\-=<>\(\)]+)')
RE_PPIF = re.compile('#\s*(ifdef|ifndef|if)\s*(.*)$')
RE_PPELIF = re.compile('#\s*elif(.*)$')
RE_PPELSE = re.compile('#\s*else\s*$')
RE_PPENDIF = re.compile('#\s*endif')
RE_CPP_COMMENT = re.compile('^//.*')


class IutestPreprocessor:
    macros = {}
    expands_macros = []
    expand_function_macros = []
    iutest_config_macro = []
    has_include = {}
    has_features = {}
    unkowns = []
    depth = []
    brothers = []
    debug = False

    def __init__(self
            , predefined_macros
            , iutest_config_macro
            , expand_function_macros
            , expands_macros
            , has_features
            , has_include):
        self.set_predefined_macros(predefined_macros)
        self.set_iutest_config_macro(iutest_config_macro)
        self.set_expand_function_macros(expand_function_macros)
        self.set_expands_macros(expands_macros)
        self.set_has_features(has_features)
        self.set_has_include(has_include)

    def set_predefined_macros(self, predefined_macros):
        self.macros = predefined_macros

    def set_iutest_config_macro(self, iutest_config_macro):
        self.iutest_config_macro = iutest_config_macro
        self.macros.update(iutest_config_macro)

    def set_expands_macros(self, expands_macros):
        self.expands_macros = expands_macros

    def set_expand_function_macros(self, expand_function_macros):
        self.expand_function_macros = expand_function_macros

    def set_has_include(self, has_include):
        self.has_include = has_include

    def set_has_features(self, has_features):
        self.has_features = has_features
    
    def set_debug_flag(self, flag):
        self.debug = flag

    def __expand_macro(self, line):
        dst = ""
        for s in RE_MACRO_SPLIT.split(line):
            if s in self.expands_macros:
                if s in self.macros and self.macros[s]:
                    dst += self.macros[s]
            else:
                dst += s
        return self.__expand_function_macro(dst)

    def __expand_function_macro(self, line):
        dst = ""
        tokens = []
        prev = ""
        for s in RE_SPLIT_PAREN.split(line):
            if s == '(':
                tokens.append(prev)
            elif s == ')' and len(tokens) > 0:
                tokens[-1] += prev + s
                s = ""
                ss = tokens.pop()
                for m in RE_FUNC_MACRO.finditer(ss):
                    d = m.group(1)
                    if d in self.expand_function_macros:
                        if d not in self.macros or self.macros[d] is None:
                            ss = ss.replace(m.group(0), '')
                if len(tokens) > 0:
                    tokens[-1] += ss
                else:
                    dst += ss
            elif len(tokens) > 0:
                tokens[-1] += prev
            else:
                dst += prev
            prev = s
        for s in tokens:
            dst += s
        dst += prev
        return dst

    def __append_define(self, line):
        def append(d, v, depth, macros, unkowns):
            d = re.sub('\(.*\)', '', d)
            if any(x == -1 for x in depth):
                unkowns.append(d)
            else:
                if len(v) == 0:
                    macros[d] = None
                else:
                    macros[d] = v
            return d
        m = RE_DEFINE.match(line)
        if m:
            return append(m.group(1), m.group(2), self.depth, self.macros, self.unkowns)
        return None

    def __expand_ppif_macro(self, expr):
        expand = ""
        for s in RE_SPLIT_OP.split(expr):
            if s == '&&':
                expand += ' and '
            elif s == '||':
                expand += ' or '
            elif s == '!':
                expand += " not "
            else:
                m = RE_DEFINE_PARSE.match(s)
                if m:
                    d = m.group(2)
                    if d in self.unkowns:
                        expand += s
                    elif d in self.macros:
                        if self.macros[d] is None:
                            f = False
                        else:
                            f = self.macros[d]
                        expand += m.group(1) + str(f) + m.group(3)
                    else:
                        expand += s
                        self.unkowns.append(d)
                    continue
                m = RE_HAS_INCLUDE.match(s)
                if m:
                    f = m.group(2)
                    if f in self.has_include:
                        expand += m.group(1) + self.has_include[f] + m.group(3)
                    else:
                        expand += s
                    continue
                m = RE_HAS_FEATURE.match(s)
                if m:
                    f = m.group(2)
                    if f in self.has_features:
                        expand += m.group(1) + self.has_features[f] + m.group(3)
                        continue
                for w in RE_SYMBOLMARK.split(s.strip()):
                    if RE_SYMBOLMARK.match(w) or w.isspace():
                        expand += w
                    elif len(w) > 0:
                        if w in self.unkowns:
                            expand += w
                        elif w in self.macros:
                            if self.macros[w] is None:
                                expand += '0'
                            else:
                                expand += self.__expand_ppif_macro(self.macros[w])
                        elif w.isdigit():
                            expand += w
                        else:
                            expand += w

        expand = expand.replace('0(0)', '0')
        expand = expand.replace('not =', '!=')
        return expand

    def __eval_ppif(self, expr):
        expand = self.__expand_ppif_macro(expr)
        try:
            if eval(expand):
                return 1
            else:
                return 0
        except Exception as e:
            if not any(x in expand for x in self.unkowns):
                if self.debug:
                    print(expr)
                    print(expand)
                    print(e)
            return -1

    def __check_ppif(self, ins, expr):
        if ins == "if" or ins == "elif":
            return self.__eval_ppif(expr)
        elif ins == "ifdef":
            if expr in self.unkowns:
                return -1
            elif expr not in self.macros:
                return -1
            elif expr in self.macros:
                if self.macros[expr] is None:
                    return 0
        elif ins == "ifndef":
            if expr in self.unkowns:
                return -1
            elif expr in self.macros:
                if self.macros[expr] is None:
                    return 1
                return 0
            else:
                return -1
        return 1

    # return line string or None
    def __check_pp(self, line):
        def ret(b):
            if b:
                return line
            return None
        m = RE_PPIF.match(line)
        if m:
            f = self.__check_ppif(m.group(1), m.group(2))
            self.depth.append(f)
            self.brothers.append([])
            return ret(all(x != 0 for x in self.depth) and f == -1)
        m = RE_PPELIF.match(line)
        if m:
            brother = self.brothers[-1]
            prev_brother_f = self.depth[-1]
            if len(brother) == 0 and prev_brother_f == 0:
                # 直前が if で 結果が False だった場合 #if に変換する
                line = line.replace('#elif', '#if')
            brother.append(prev_brother_f)
            f = 0
            if not any(x == 1 for x in brother):
                f = self.__check_ppif("elif", m.group(1))
            self.depth[-1] = f
            if all(x != 0 for x in self.depth):
                if f == -1 or any(x == -1 for x in brother):
                    return line
            return None
        m = RE_PPELSE.match(line)
        if m:
            brother = self.brothers[-1]
            brother.append(self.depth[-1])
            f = -1
            if f == 1 or any(x == 1 for x in brother):
                f = 0
            elif all(x == 0 for x in brother):
                f = 1
            self.depth[-1] = f
            return ret(all(x != 0 for x in self.depth) and f == -1)
        if RE_PPENDIF.match(line):
            brother = self.brothers[-1]
            f = self.depth.pop()
            b1 = all(x != 0 for x in self.depth)
            b2 = any(x == -1 for x in brother)
            self.brothers.pop()
            return ret(b1 and (f == -1 or b2))
        return ret(len(self.depth) == 0 or all(x != 0 for x in self.depth))

    def __reduction(self, line):
        line = line.replace('IIUT_', 'II_')
        line = line.replace('II_PP_', 'IP_')
        line = line.replace('IUTEST_UNUSED_VAR', '(void)')
        line = re.sub('\s+', ' ', line)
        line = re.sub('\s$', '', line)
        return line

    def preprocess(self, code, add_macros):
        if not add_macros is None:
            self.macros.update(add_macros)
        dst = ""
        for line in code.splitlines():
            # c++ comment
            if RE_CPP_COMMENT.match(line):
                continue
            # if/ifdef/ifndef/elif/endif
            line = self.__check_pp(line)
            if line:
                # define
                d = self.__append_define(line)
                if d:
                    if d in self.expands_macros or d in self.expand_function_macros:
                        continue
                    if d in ['IUTEST_UNUSED_VAR']:
                        continue
                line = self.__expand_macro(line)
                if len(line) > 0:
                    line = self.__reduction(line)
                    dst += line + "\n"
                # config macro insert
                if '#define INCG_IRIS_IUTEST_CONFIG_HPP_' in line:
                    for k,v in self.iutest_config_macro.items():
                        dst += '#define ' + k + ' ' + str(v) + '\n'
                    self.iutest_config_macro.clear()
        return dst
