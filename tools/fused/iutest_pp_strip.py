#!/usr/bin/env python
#
# iutest_pp_strip.py
#
# Copyright (C) 2018, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import re
import collections

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
RE_SYSTEM_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*<(.*)>')

RE_STRIP_INCG_REGEX = re.compile(r'^INCG_\S*_[IH]PP_\S+\Z')


class IutestPreprocessor:
    macros = {}
    depth_macros = [ {} ]
    expands_macros = []
    expand_function_macros = []
    iutest_config_macro = []
    included_path = [ [] ]
    has_include = {}
    has_features = {}
    unknowns = []
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

    def __has_current_macro(self, name):
        current_depth_macro = self.depth_macros[-1]
        if name in current_depth_macro:
            return True
        if name in self.macros:
            return True
        return False

    def __get_current_macro(self, name):
        current_depth_macro = self.depth_macros[-1]
        if name in current_depth_macro:
            return current_depth_macro[name]
        if name in self.macros:
            return self.macros[name]
        return False

    def __append_define(self, line):
        def append(d, v, depth, macros, unknowns, current):
            d = re.sub('\(.*\)', '', d)
            if len(v) == 0:
                if RE_STRIP_INCG_REGEX.match(d):
                    self.expands_macros.append(d)
                v = 'defined'
            if any(x == -1 for x in depth):
                unknowns.append(d)
                current[d] = v
            else:
                macros[d] = v
            return d
        m = RE_DEFINE.match(line)
        if m:
            current_depth_macro = self.depth_macros[-1]
            return append(m.group(1), m.group(2), self.depth, self.macros, self.unknowns, current_depth_macro)
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
                    if self.__has_current_macro(d):
                        expand += m.group(1)
                        if self.__get_current_macro(d) is None:
                            expand += ' (0==1) '
                        else:
                            expand += ' (0==0) '
                        expand += m.group(3)
                    elif d in self.unknowns:
                        expand += s
                    else:
                        expand += s
                        self.unknowns.append(d)
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
                        if w in self.unknowns:
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
            r = eval(expand)
            if r:
                return 1
            else:
                return 0
        except Exception as e:
            def debug_print():
                if self.debug:
                    print(expr)
                    print(expand)
                    print(e)
            if 'INCG_IRIS_' in expr:
                print(expr)
                print(expand)
                print(e)
            if not any(x in expand for x in self.unknowns):
                debug_print()
            elif len(expr.split()) > 1:
                debug_print()
            return -1

    def __check_ppif(self, ins, expr):
        if ins == "if" or ins == "elif":
            return self.__eval_ppif(expr)
        elif ins == "ifdef":
            if expr in self.unknowns:
                return -1
            elif expr not in self.macros:
                return -1
            elif expr in self.macros:
                if self.macros[expr] is None:
                    return 0
        elif ins == "ifndef":
            if expr in self.unknowns:
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
            self.depth_macros.append({})
            self.included_path.append([])
            self.brothers.append([])
            return ret(all(x != 0 for x in self.depth) and f == -1)
        m = RE_PPELIF.match(line)
        if m:
            brother = self.brothers[-1]
            prev_brother_f = self.depth[-1]
            if len(brother) == 0 and prev_brother_f == 0:
                # Convert to #if if the last is if and the result is False
                line = line.replace('#elif', '#if')
            else:
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
            self.included_path.pop()
            self.depth_macros.pop()
            b1 = all(x != 0 for x in self.depth)
            b2 = any(x == -1 for x in brother)
            self.brothers.pop()
            return ret(b1 and (f == -1 or b2))
        return ret(len(self.depth) == 0 or all(x != 0 for x in self.depth))

    def __check_include(self, line):
        m = RE_SYSTEM_INCLUDE_REGEX.match(line)
        if m:
            path = m.group(1)
            if path in self.included_path[-1]:
                return False
            else:
                self.included_path[-1].append(path)
        return True

    def __reduction(self, line):
        reduction_macros = {
            'IP_INC':    'IP_I',
            'IP_DEC':    'IP_D',
            'IP_BOOL':   'IP_B',
            'IP_ENUM':   'IP_E',
            'IP_REPEAT': 'IP_R',
            'IP_IS_EMPTY_': 'IP_IS_EMP_',
            'IP_EMPTY_TAG': 'IP_EMP_T',
            'IP_IS_BEGIN_PARENS': 'IP_IS_BGN_P',
            'II_SHOW_MACRO':  'II_S_M',
            'II_ELEMENTSARE': 'II_EA',
            'II_DECL_VALUEARRAY_': 'II_D_VA_',
            'II_DECL_CARTESIAN_PRODUCT_': 'II_D_C_P_',
            'II_DECL_PAIRWISE_': 'II_D_PW_',
            'II_DECL_IS_FUNCTION_PTR_': 'II_D_IS_FP_',
            'II_DECL_IS_MEMBER_FUNCTION_PTR_': 'II_D_IS_M_FP_',
            'II_DECL_FUNCTION_RETURN_TYPE_': 'II_D_F_R_T_',
            'II_DECL_EXPRESSION_': 'II_D_EP_',
            'II_DECL_ELEMENTSARE_': 'II_D_EA_',
            'II_DECL_TUPLE_PRINTTO': 'II_D_T_PT',
            'II_DECL_ANYOF_AND_ALLOF': 'II_D_AAA',
            'II_DECL_COMPARE_HELPER_': 'II_D_C_H_',
            'II_DECL_COMBINE_':   'II_D_C_',
            'II_DECL_VALUES_':    'II_D_V_',
            'II_DECL_TYPES_':     'II_D_T_',
            'II_DECL_TEMPLATES_': 'II_D_TPL_',
            'II_DECL_TYPELIST_':  'II_D_TL_',
            'II_DECL_TEMPLATETYPELIST_': 'II_D_TTL_',
            'II_D_C_P_GENERATOR_': 'II_D_C_P_GEN_',
            'II_D_C_P_HOLDER_': 'II_D_C_P_HLR_',
            'II_D_PW_GENERATOR_': 'II_D_PW_GEN_',
            'II_D_PW_HOLDER_': 'II_D_PW_HLR_',
            'II_CONCAT_PACKAGE': 'II_CC_PKG',
            'II_PACKAGE_': 'II_PKG_',
            'II_PKG_CURRENT_NAMESPACE_': 'II_PKG_C_NS_',
            'II_PKG_PARENT_NAMESPACE_':  'II_PKG_P_NS_',
            'II_TEST_CLASS_NAME_': 'II_T_C_N_',
            'II_TEST_INSTANCE_NAME_': 'II_T_INST_N_',
            'II_TO_VARNAME_': 'II_TO_VN_',
            'II_TO_NAME_': 'II_TO_N_',
            'II_CHECK_TESTFIXTURE': 'II_CK_TF',
            'II_PMZ_TEST_CLASS_NAME_': 'II_PMZ_T_C_N_',
            'II_GETTESTCASEPATTERNHOLDER': 'II_GTCPH',
            'II_INSTANTIATE_TEST_CASE_P_': 'II_INST_TC_P_',
            'II_TEST_P_EVALGENERATOR_NAME_':    'II_T_P_EGEN_N_',
            'II_TEST_P_PARAMGENERATOR_NAME_':   'II_T_P_PGEN_N_',
            'II_TEST_P_INSTANTIATIONREGISTER_': 'II_T_P_INST_R_',
            'II_GeTypeNameSpecialization': 'II_GTNS',
            'II_WORKAROUND_GENRAND': 'II_WA_GENRAND',
        }
        line = line.replace('IIUT_', 'II_')
        line = line.replace('II_PP_', 'IP_')
        line = line.replace('IUTEST_UNUSED_VAR', '(void)')
        for k,v in reduction_macros.items():
            if collections.Counter(reduction_macros.values())[v] > 1:
                print('error: duplicated ' + v)
                continue
            line = line.replace(k, v)
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
                # include
                if not self.__check_include(line):
                    continue
                # define
                d = self.__append_define(line)
                if d:
                    # config macro insert
                    if 'INCG_IRIS_IUTEST_CONFIG_HPP_' in d:
                        for k,v in self.iutest_config_macro.items():
                            dst += '#define ' + k + ' ' + str(v) + '\n'
                        self.iutest_config_macro = []
                    if d in self.expands_macros or d in self.expand_function_macros:
                        continue
                    if d in ['IUTEST_UNUSED_VAR']:
                        continue
                line = self.__expand_macro(line)
                if len(line) > 0:
                    line = self.__reduction(line)
                    dst += line + "\n"
        return dst

    def __get_ppif_type(self, line):
        if RE_PPIF.match(line):
            return 'if'
        elif RE_PPELIF.match(line):
            return 'elif'
        elif RE_PPELSE.match(line):
            return 'else'
        elif RE_PPENDIF.match(line):
            return 'endif'
        return None

    def remove_empty_ppif(self, code):
        dst = ""
        prev = None
        cache_lines = []
        def cach_clear():
            ret = ""
            for s in cache_lines:
                if s is not None:
                    ret += s
            del cache_lines[:]
            return ret

        for line in code.splitlines():
            line += "\n"
            t = self.__get_ppif_type(line)
            if t == 'endif':
                if prev == 'if':
                    if len(cache_lines) > 0:
                        cache_lines = cache_lines[:-1]
                elif prev != 'endif':
                    if len(cache_lines) > 0:
                        cache_lines[-1] = line
                    else:
                        cache_lines.append(line)
                else:
                    dst += cach_clear()
                    dst += line
            elif t is not None:
                if prev is None:
                    cache_lines.append(line)
                else:
                    if t == 'else' and prev == 'elif':
                        cache_lines[-1] = line
                    elif t == 'elif' and prev == 'elif':
                        cache_lines[-1] = line
                    else:
                        cache_lines.append(line)
            else:
                dst += cach_clear()
                dst += line
            prev = t
        dst += cach_clear()
        return dst
