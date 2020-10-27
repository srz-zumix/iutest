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
RE_PPELIF = re.compile('#\s*elif\s*(.*)$')
RE_PPELSE = re.compile('#\s*else\s*$')
RE_PPENDIF = re.compile('#\s*endif')
RE_AND = re.compile('and')
RE_CPP_COMMENT = re.compile('^//.*')
RE_SYSTEM_INCLUDE_REGEX = re.compile(r'^\s*#\s*include\s*<(.*)>')

RE_STRIP_INCG_REGEX = re.compile(r'^INCG_\S*_[IH]PP_\S+\Z')

RE_EVAL_UNDEFINED_EXCEPTION = re.compile(r'^name \'(defined_.*)\' is not defined\Z')

UNUSED_ = "unused"


class IutestPreprocessor:
    macros = {}
    expands_macros = []
    expand_function_macros = []
    iutest_config_macro = []
    has_include = {}
    has_features = {}
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
        self.unknowns = []
        self.included_path = [[]]
        self.depth_macros = [{}]
        self.depth = []
        self.brothers = []
        self.prev_line = None


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

    def __none_or_unused(self, v):
        if v is None or v == UNUSED_:
            return True
        return False

    def __expand_macro(self, line):
        dst = ""
        for s in RE_MACRO_SPLIT.split(line):
            if s in self.expands_macros:
                expand = self.__get_current_macro(s)
                if expand is not None:
                    dst += expand
                    continue
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
                        if d not in self.macros or self.__none_or_unused(self.macros[d]):
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
        if name in self.macros:
            return True
        for m in self.depth_macros:
            if name in m:
                return True
        return False

    def __get_current_macro(self, name):
        if name in self.macros:
            return self.macros[name]
        for m in self.depth_macros:
            if name in m:
                return m[name]
        return None

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
                            expand += ' (0) '
                        else:
                            expand += ' (1) '
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

        expand = expand.replace('0(0)', '(0)')
        expand = expand.replace('not =', '!=')
        expand = re.sub(r'not\s*\(0\)', '(1)', expand)
        return expand.strip()

    def __eval_ppif_unknown_defined(self, expand):
        if 'defined' not in expand:
            return -1
        expand = re.sub(r'defined\((.*?)\)', 'defined_\\1', expand)
        try:
            r = eval(expand)
        except Exception as e:
            r = self.__eval_ppif_unknown_defined_(str(e), expand)
        return r

    def __eval_ppif_unknown_defined_(self, exception_str, expand):
        def eval_x(d, x):
            try:
                expanded = expand.replace(d, str(x))
                return eval(expanded)
            except Exception:
                return -1
        m = RE_EVAL_UNDEFINED_EXCEPTION.match(exception_str)
        if m:
            d = m.group(1)
            r0 = eval_x(d, 0)
            r1 = eval_x(d, 1)
            if r0 == r1:
                return r0
        return -1

    def __eval_expanded_expr(self, expand_expr):
        error = None
        try:
            r = eval(expand_expr)
            if r:
                return (1, '1')
            else:
                return (0, '0')
        except Exception as e:
            error = e

        expand = expand_expr
        if 'or' not in expand:
            for expr in RE_AND.split(expand):
                try:
                    r = eval(expr)
                    if not r:
                        return (0, '0')
                except Exception as e:
                    error = e
        raise error

    def __eval_ppif(self, expr):
        expand = self.__expand_ppif_macro(expr)
        expand_expr = re.sub(r'([0-9])+L', r'\1', expand)
        try:
            return self.__eval_expanded_expr(expand_expr)
        except Exception as e:
            r = -1
            if len(expand.split()) > 1:
                # r = self.__eval_ppif_unknown_defined(expand_expr)
                if r == -1:
                    if self.debug:
                        print(expr)
                        print(expand)
                        print(e)
                # strip fixed condition
                if '(0)' in expand or '(1)' in expand:
                    expand = re.sub(r'\s*\(0\)\s*or\s*', '', expand)
                    expand = re.sub(r'\s*or\s*\(0\)\s*', '', expand)
                    expand = re.sub(r'\s*\(1\)\s*and\s*', '', expand)
                    expand = re.sub(r'\s*and\s*\(1\)\s*', '', expand)
                    expand = expand.replace(' and ', '&&')
                    expand = expand.replace(' or ' , '||')
                    expand = expand.replace(' not ', '!')
                    expand = expand.replace('(0)', '0')
                    expand = expand.replace('(1)', '1')
                    return (r, expand)
            return (r, None)

    def __check_ppif(self, ins, expr):
        if ins == "if" or ins == "elif":
            return self.__eval_ppif(expr)
        else:
            def other():
                if ins == "ifdef":
                    if expr in self.unknowns:
                        return -1
                    elif expr not in self.macros:
                        return -1
                    elif expr in self.macros:
                        if self.macros[expr] is None:
                            return 0
                        return 1
                elif ins == "ifndef":
                    if expr in self.unknowns:
                        return -1
                    elif expr in self.macros:
                        if self.macros[expr] is None:
                            return 1
                        return 0
                    elif expr in self.expands_macros:
                        return 0
                    else:
                        return -1
                return -1
            return other(), None

    # return line string or None
    def __check_pp(self, line):
        def ret(b):
            if b:
                return line
            return None
        m = RE_PPIF.match(line)
        if m:
            expr = m.group(2)
            f,expanded_expr = self.__check_ppif(m.group(1), expr)
            self.depth.append(f)
            self.depth_macros.append({})
            self.included_path.append([])
            self.brothers.append([])
            if expanded_expr is not None:
                line = line.replace(expr, expanded_expr)
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
                expr = m.group(1)
                f,expanded_expr = self.__check_ppif("elif", expr)
                if expanded_expr is not None:
                    line = line.replace(expr, expanded_expr)
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
            if any(x == 1 for x in brother):
                f = 0
            elif all(x == 0 for x in brother):
                f = 1
            self.depth[-1] = f
            return ret(all(x != 0 for x in self.depth) and f == -1)
        if RE_PPENDIF.match(line):
            brother = self.brothers[-1]
            f = self.depth.pop()
            self.included_path.pop()
            poped_macros = self.depth_macros.pop()
            b1 = all(x != 0 for x in self.depth)
            b2 = any(x == -1 for x in brother)
            self.brothers.pop()
            need_endif = b1 and (f == -1 or b2)
            if need_endif:
                return line
            if len(self.depth_macros) > 0:
                current_depth_macros = self.depth_macros[-1]
                current_depth_macros.update(poped_macros)
            return None
        return ret(len(self.depth) == 0 or all(x != 0 for x in self.depth))

    def __check_include(self, line):
        m = RE_SYSTEM_INCLUDE_REGEX.match(line)
        if m:
            path = m.group(1)
            for include_paths in self.included_path:
                if path in include_paths:
                    return False
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
            'IP_E_PARAMS_MACRO_': 'IP_E_P_M_',
            'IP_E_P_M_IN_BINARY_': 'IP_E_P_M_B_',
            'IP_E_BINARY_PARAMS_': 'IP_E_B_P_',
            'IP_E_B_P_MACRO_': 'IP_E_B_P_M_',
            'IP_R_PARAMS_MACRO_': 'IP_R_P_M_',
            'IP_R_P_M_IN_BINARY_': 'IP_R_P_M_B_',
            'IP_R_BINARY_PARAMS_': 'IP_R_B_P_',
            'IP_R_B_P_MACRO_': 'IP_R_B_P_M_',
            'II_SHOW_MACRO':  'II_S_M',
            'II_SHOW_ENABLE_MACRO':   'II_S_E_M',
            'II_SHOW_DISABLE_MACRO':  'II_S_D_M',
            'II_SHOW_FEATURE_MACROS': 'II_S_F_M',
            'II_ELEMENTSARE': 'II_EA',
            'II_EA_MATCHER_NAME': 'II_EA_M_N',
            'II_ANYOF_AND_ALLOF_MATCHER_NAME': 'II_AAA_M_N',
            'II_DECL_VALUEARRAY_': 'II_D_VA_',
            'II_DECL_CARTESIAN_PRODUCT_': 'II_D_C_P_',
            'II_DECL_PAIRWISE_': 'II_D_PW_',
            'II_DECL_IS_FUNCTION_PTR_': 'II_D_IS_FP_',
            'II_DECL_IS_MEMBER_FUNCTION_PTR_': 'II_D_IS_M_FP_',
            'II_DECL_FUNCTION_RETURN_TYPE_': 'II_D_F_R_T_',
            'II_DECL_EXPRESSION_': 'II_D_EP_',
            'II_DECL_ELEMENTSARE': 'II_D_EA',
            'II_DECL_TUPLE_PRINTTO': 'II_D_T_PT',
            'II_DECL_ANYOF_AND_ALLOF': 'II_D_AAA',
            'II_DECL_COMPARE_HELPER_': 'II_D_C_H_',
            'II_DECL_COMBINE_': 'II_D_C_',
            'II_DECL_VALUES_': 'II_D_V_',
            'II_DECL_TYPES_': 'II_D_T_',
            'II_DECL_TEMPLATES_': 'II_D_TPL_',
            'II_DECL_TYPELIST_': 'II_D_TL_',
            'II_DECL_TEMPLATETYPELIST_': 'II_D_TTL_',
            'II_DECL_PEEP_MEMBER_FUNC_': 'II_D_PE_M_F_',
            'II_DECL_COMPARE_MATCHER': 'II_D_COMP_M',
            'II_DECL_STR_COMPARE_MATCHER': 'II_D_S_COMP_M',
            'II_DECL_ALLOF_MATCHER': 'II_D_ALL_M',
            'II_DECL_ANYOF_MATCHER': 'II_D_ANY_M',
            'II_DECL_DEFAULT_ARG_': 'II_D_DEF_A_',
            'II_DECL_SPEC_NONE_': 'II_D_S_NN_',
            'II_SUCCEED': 'II_S',
            'II_FAIL': 'II_F',
            'II_ADD_FAILURE': 'II_ADD_F',
            'II_SCOPED_MESSAGE': 'II_S_MSG',
            'II_D_C_P_GENERATOR_': 'II_D_C_P_GEN_',
            'II_D_C_P_HOLDER_': 'II_D_C_P_HLR_',
            'II_D_PW_GENERATOR_': 'II_D_PW_GEN_',
            'II_D_PW_HOLDER_': 'II_D_PW_HLR_',
            'II_CONCAT_PACKAGE': 'II_CC_PKG',
            'II_PACKAGE_': 'II_PKG_',
            'II_PKG_CURRENT_NAMESPACE_': 'II_PKG_C_NS_',
            'II_PKG_PARENT_NAMESPACE_': 'II_PKG_P_NS_',
            'II_TEST_CLASS_NAME_': 'II_T_C_N_',
            'II_TEST_INSTANCE_NAME_': 'II_T_INST_N_',
            'II_TO_VARNAME_': 'II_TO_VN_',
            'II_TO_NAME_': 'II_TO_N_',
            'II_CHECK_TESTFIXTURE': 'II_CK_TF',
            'II_PMZ_TEST_CLASS_NAME_': 'II_PMZ_T_C_N_',
            'II_GETTESTCASEPATTERNHOLDER': 'II_GTCPH',
            'II_INSTANTIATE_TEST_CASE_P_': 'II_INST_TC_P_',
            'II_TEST_P_EVALGENERATOR_NAME_': 'II_T_P_EGEN_N_',
            'II_TEST_P_PARAMGENERATOR_NAME_': 'II_T_P_PGEN_N_',
            'II_TEST_P_INSTANTIATIONREGISTER_': 'II_T_P_INST_R_',
            'II_TEST_P_FIXTURE_DECL_': 'II_T_P_FX_D_',
            'II_TEST_P_BASE_FIXTURE': 'II_T_P_B_FX',
            'II_T_P_INST_R_NAME_': 'II_T_P_INST_R_N_',
            'II_ALIAS_TESTNAME_PP_': 'II_A_TN_PP_',
            'II_TEST_EXPRESSION_': 'II_T_EXPR_',
            'II_T_EXPR_EXPAND_EXPRESSION': 'II_T_EXPR_E_E',
            'II_EXPRESSION_DECOMPOSE': 'II_EXPR_DEC',
            'II_D_EP_RESULT_OP': 'II_D_EP_R_OP',
            'II_TYPED_TEST_': 'II_T_T_',
            'II_T_T_CASE_': 'II_T_TC_',
            'II_T_TC_PSTATE_NAME_': 'II_T_TC_PS_N_',
            'II_T_T_P_NAMESPACE_': 'II_T_T_P_NS_',
            'II_T_T_P_ADDTESTNAME': 'II_T_T_P_ADD_TN',
            'II_T_T_PARAMS_': 'II_T_T_PRMS_',
            'II_REGISTER_TYPED_TEST_CASE_P_': 'II_R_T_TC_P_',
            'II_INSTANTIATE_TYPED_TEST_CASE_P_': 'II_INST_T_TC_P_',
            'II_PEEP_TAG_NAME_': 'II_PE_T_N_',
            'II_PEEP_SETTER_NAME_': 'II_PE_S_N_',
            'II_GeTypeNameSpecialization': 'II_GTNS',
            'II_WORKAROUND_GENRAND': 'II_WA_GENRAND',
            'II_FILESYSTEM_INSTANTIATE_': 'II_FS_I_',
        }
        line = line.replace('IIUT_', 'II_')
        line = line.replace('II_PP_', 'IP_')
        line = line.replace('IUTEST_UNUSED_VAR', '(void)')
        line = line.replace('statement', 'st')
        line = line.replace('expected_exception', 'exp_e')
        line = line.replace('exp_e_value', 'exp_e_v')
        line = line.replace('expected_str', 'exp_s')
        line = line.replace('expected_value', 'exp_v')
        line = line.replace('actual_str', 'act_s')
        line = line.replace('regex_str', 'regex_s')
        line = line.replace('pred_formatter', 'pd_fmt')
        line = line.replace('on_failure', 'on_f')
        line = line.replace('testcasename_', 'tcn_')
        line = line.replace('testcase_', 't_c_')
        line = line.replace('testname_', 'tn_')
        line = line.replace('testfixture_', 'tf_')
        line = line.replace('result_type_', 'rt_')
        line = line.replace('parent_class_', 'p_c_')
        line = line.replace('type_id_', 'tid_')
        line = line.replace('methodName', 'mN_')
        line = line.replace('method_', 'mtd_')
        line = line.replace('prefix_', 'pfx_')
        line = line.replace('paramname_generator_', 'pn_gen_')
        line = line.replace('generator_', 'gen_')
        line = line.replace('dummy', 'dmy')
        # line = line.replace('value', 'val')
        # line = line.replace('macro', 'mcr')
        line = line.replace('EXTEND_POINT_', 'EX_P_')
        for k,v in reduction_macros.items():
            if collections.Counter(reduction_macros.values())[v] > 1:
                print('error: duplicated ' + v)
                continue
            line = line.replace(k, v)
        line = re.sub(r'(?<![\w\d_])NULL(?![\w\d_])', '0', line)
        # line = re.sub('\s+', ' ', line)
        line = re.sub('\s$', '', line)
        line = line.strip()
        return line

    def __strip_namespace(self, line, ns):
        s = ""
        e = ""
        for n in ns:
            s += "namespace " + n + "{"
            e += "}"
        def __is_namespace_open_close_line(x):
            return x.startswith(s) and x.endswith(e)
        if __is_namespace_open_close_line(line) and __is_namespace_open_close_line(self.prev_line):
            self.prev_line = self.prev_line[:-len(e)]
            line = line[len(s):]
        return line

    def __strip_namespace_iutest_detail(self, line):
        ns = ['iutest', 'detail']
        return self.__strip_namespace(line, ns)

    def __strip_namespace_iutest(self, line):
        ns = ['iutest']
        return self.__strip_namespace(line, ns)

    def __strip_namespaces(self, line):
        line = self.__strip_namespace_iutest_detail(line)
        line = self.__strip_namespace_iutest(line)
        return line

    def preprocess(self, code, add_macros):
        if add_macros is not None:
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
                        dst += self.prev_line + '\n'
                        self.prev_line = None
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
                    if self.prev_line is not None:
                        line = self.__strip_namespaces(line)
                        if self.prev_line.startswith('#'):
                            self.prev_line += '\n'
                        elif line.startswith('#'):
                            self.prev_line += '\n'
                        dst += self.prev_line
                    self.prev_line = line
        dst += self.prev_line + '\n'
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

    def trancate_line(self, code):
        dst = ""
        limit = 6000
        for line in code.splitlines():
            found = True
            while len(line) >= limit and found:
                found = False
                for sep in ['}}', '};', '";']:
                    idx = line.rfind(sep, 0, limit)
                    if idx >= 0:
                        idx += len(sep)
                        dst += line[:idx] + '\n'
                        line = line[idx:]
                        found = True
                        break
            line += "\n"
            dst += line
        return dst
