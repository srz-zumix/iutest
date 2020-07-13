#!/usr/bin/env python
#
# iuwandbox_pp.py
#
# Copyright (C) 2018, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import codecs
import re
import collections
from iutest_pp_strip import IutestPreprocessor

predefined_macros = {
    '__WANDBOX__': '1',
    'NULL': '0',
    'IUTEST_USE_GTEST': None,
    'IUTEST_BUILD_DOXYGEN': None,
    '_IUTEST_DEBUG': None,
    '__CYGWIN__': None,
    'IUTEST_OS_CYGWIN': None,
    '__MINGW__': None,
    '__MINGW32__': None,
    '__MINGW64__': None,
    '__linux__': '1',
    '__arm__': None,
    'IUTEST_OS_ARM': None,
    '__ARMCC_VERSION': None,
    '__AVR32__': None,
    '__avr32__': None,
    'IUTEST_OS_AVR32': None,
    'ANDROID': None,
    '__ANDROID__': None,
    'IUTEST_OS_LINUX_ANDROID': None,
    '__APPLE__': None,
    'IUTEST_OS_IOS': None,
    'IUTEST_OS_MAC': None,
    '__INTEL_COMPILER': None,
    '__BORLANDC__': None,
    '__CUDACC__': None,
    '__IBMCPP__': None,
    'COMPILER_ICC': None,
    '_MSC_VER': None,
    '_MSC_FULL_VER': None,
    '_MSVC_LANG': None,
    '_WIN32': None,
    'WIN32': None,
    '__WIN32__': None,
    'UNICODE': None,
    'WINAPI_FAMILY': None,
    '__AFX_H__': None,
    '__MWERKS__': None,
    '__FreeBSD__': None,
    'sun': None,
    '__sun': None,
    '__MAC_OS_X_VERSION_MIN_REQUIRED': None,
    'IUTEST_OS_WINDOWS': None,
    'IUTEST_OS_WINDOWS_MINGW': None,
    'IUTEST_OS_WINDOWS_MOBILE': None,
    'IUTEST_OS_WINDOWS_PHONE': None,
    'IUTEST_OS_WINDOWS_RT': None,
    'IUTEST_OS_WINDOWS_WINE': None,
    'IUTEST_NO_UTIL_ASSERTION_GTEST_COMPATIBLE': '1',
    'IUTEST_NO_TWO_PHASE_NAME_LOOKUP': None,
    'IUTEST_NO_FUNCTION_TEMPLATE_ORDERING': None,
    'IUTEST_NO_INCLASS_MEMBER_INITIALIZATION': None,
    'IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS': None,
    'IUTEST_NO_SFINAE': None,
    'IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION': None,
    'IUTEST_NO_TEMPLATE_TEMPLATES': None,
    'IUTEST_NO_VOID_RETURNS': None,
    'IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP': None,
    'IUTEST_NO_PRIVATE_IN_AGGREGATE': None,
    'IUTEST_NO_VARIADIC_MACROS': None,
    'IUTEST_NO_UNITEST_AD_HOC_TEST_RESULT_ACCESSOR': None,
    'IUTEST_NO_TESTCASE_AD_HOC_TEST_RESULT_ACCESSOR': None,
    'IUTEST_NO_LAMBDA_SCOPE_RESOLUTION': None,
    'IUTEST_NO_GETENV': None,
    'IUTEST_NO_PUTENV': None,
    'IUTEST_NO_SETENV': None,
    'IUTEST_NO_GETCWD': None,
    'IUTEST_NOT_SUPPORT_STOPWATCH': None,
    'IUTEST_HAS_WANT_SECURE_LIB': '0',
    'IUTEST_HAS_MS_EXTENSIONS': '0',
    'IUTEST_HAS_MS_CXX_MODULE': '0',
    'IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION': '0',
    'MS_CPP_UNITTESTFRAMEWORK': None,
    'IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION': '1',
    'IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION': '1',
    '__native_client__': None,
    'IUTEST_OS_NACL': None,
    'IUTEST_HAS_INVALID_PARAMETER_HANDLER': '0',
    '__clang_analyzer__': None,
    'IUTEST_ANALYSIS_ASSUME_DELEGATE': None,
    'IUTEST_MBS_CODE': '0',
    'IUTEST_USE_EXTERNAL_STD_TUPLE': '0',
    'IUTEST_USE_EXTERNAL_TR1_TUPLE': '0',
    'IUTEST_USE_CXX_FILESYSTEM': '0',
    'IUTEST_CXX_NOEXCEPT': 'unused',
    'IUTEST_CXX_NOEXCEPT_AS': 'unused',
    'IUTEST_CXX_NOTHROW': 'unused',
    'IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY': 'unused',
    'IUTEST_PRAGMA_WARN_FORMAT_NONLITERAL': 'unused',
    'IUTEST_PRAGMA_WARN_CXX14_CONSTEXPR_NOT_IMPLY_CONST': 'unused',
    'IUTEST_MAKE_ASSERTIONRESULT_': 'unused',
}

iutest_config_macro = {
    'IUTEST_HAS_LIB': '0',
    'IUTEST_HAS_PARAM_TEST': '1',
    'IUTEST_HAS_TYPED_TEST': '1',
    'IUTEST_HAS_TYPED_TEST_P': '1',
    'IUTEST_TYPED_TEST_P_STRICT': '1',
    'IUTEST_HAS_MATCHERS': '1',
    'IUTEST_HAS_VALUESGEN': '1',
    'IUTEST_HAS_RANDOMVALUES': '1',
    'IUTEST_HAS_CONCAT': '1',
    'IUTEST_HAS_CSVPARAMS': '1',
    'IUTEST_HAS_TESTNAME_ALIAS_JP': '0',
    'IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE': '1',
    'IUTEST_HAS_AUTOFIXTURE_PARAM_TEST': '1',
    'IUTEST_HAS_ANY_PARAM_TEST': '1',
    'IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR': '1',
    'IUTEST_HAS_IF_EXISTS': '0',
    'IUTEST_HAS_ANALYSIS_ASSUME': '0',
    'IUTEST_HAS_IGNORE_TEST': '0',
    'IUTEST_HAS_MINIDUMP': '0',
    'IUTEST_HAS_STRSTREAM': '0',
    'IUTEST_HAS_STRINGSTREAM': '1',
    'IUTEST_HAS_IOMANIP': '1',
    'IUTEST_HAS_CTIME': '1',
    'IUTEST_HAS_GETTIMEOFDAY': '1',
    'IUTEST_HAS_HDR_SYSTIME': '1',
    'IUTEST_HAS_FOPEN': '1',
    'IUTEST_HAS_FILE_STAT': '1',
    'IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION': '0',
    'IUTEST_HAS_GENERIC': '0',
    'IUTEST_HAS_MEMORY_SANITIZER': '0',
    'IUTEST_HAS_ADDRESS_SANITIZER': '0',
    'IUTEST_HAS_THREAD_SANITIZER': '0',
    'IUTEST_HAS_SEH': '0',
    'IUTEST_USE_OWN_LIST': '0',
    'IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR': '1',
    'IUTEST_HAS_MATCHER_EACH': '1',
    'IUTEST_HAS_MATCHER_POINTWISE': '1',
    'IUTEST_HAS_GENRAND': '1',
    'IUTEST_HAS_PACKAGE': '1',
    'IUTEST_HAS_PEEP': '1',
    'IUTEST_HAS_SOCKET': '1',
    'IUTEST_HAS_PRINT_TO': '1',
    'IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE': '1',
    'IUTEST_HAS_STATIC_ASSERT_TYPEEQ': '1',
    'IUTEST_HAS_ASSERTION_RETURN': '1',
    'IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT': '1',
    'IUTEST_HAS_TESTNAME_ALIAS': '1',
    'IUTEST_HAS_REPORT_SKIPPED': '1',
    'IUTEST_HAS_STREAM_BUFFER': '1',
    # 'IUTEST_HAS_STREAM_RESULT': '1',
    'IUTEST_CHECK_STRICT': '1',
}

expands_macros = [
    'IUTEST_IPP_INLINE',
    'IUTEST_ATTRIBUTE_DEPRECATED_',
    'IUTEST_ATTRIBUTE_PURE_',
    'IUTEST_ATTRIBUTE_INIT_PRIORITY_',
    'IUTEST_HAS_ATTRIBUTE_DEPRECATED',
    'IUTEST_CXX_MODULE_EXPORT',
    'IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY',
    'IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS',
    'IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD',
    'IUTEST_ATTRIBUTE_NO_SANITIZE_ALL',
]

# expand function macros
expand_function_macros = [
    'IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN',
    'IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END',
    'IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN',
    'IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END',
    'IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN',
    'IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END',
    'IUTEST_PRAGMA_MSC_WARN_PUSH',
    'IUTEST_PRAGMA_MSC_WARN_DISABLE',
    'IUTEST_PRAGMA_MSC_WARN_POP',
    'IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_BEGIN',
    'IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_END',
    'IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_BEGIN',
    'IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_END',
    'IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY',
    'IUTEST_PRAGMA_WARN_FORMAT_NONLITERAL',
    'IUTEST_PRAGMA_WARN_CXX14_CONSTEXPR_NOT_IMPLY_CONST',
    'IUTEST_WORKAROUND_MSC_STLSTREAM_C4250',
    'IUTEST_EXPLICIT_TEMPLATE_TYPE_',
    'IUTEST_IF_EXISTS',
    'IUTEST_IF_NOT_EXISTS',
    'IUTEST_STATIC_EXISTS',
    'IUTEST_STATIC_ASSERT_IF_EXISTS',
    'IUTEST_STATIC_ASSERT_IF_NOT_EXISTS',
    'IUTEST_ANALYSIS_ASSUME',
    'IUTEST_PP_ENUM_CASE_RETURN_STRING',
    'IUTEST_CLASS_INITIALIZE',
    'IUTEST_CLASS_CLEANUP',
    'IUTEST_METHOD_INITIALIZE',
    'IUTEST_METHOD_CLEANUP',
    # 'IUTEST_MAKE_ASSERTIONRESULT_',
]

#
has_features = {
}

has_include = {
}

rename_macro = {
    'IUTEST_ASSERT_FAILURE': 'II_A_FAIL',
    'IUTEST_EXPECT_FAILURE': 'II_E_FAIL',
    'IUTEST_INFORM_FAILURE': 'II_I_FAIL',
    'IUTEST_ASSUME_FAILURE': 'II_M_FAIL',
    'IUTEST_ATTRIBUTE_UNUSED_': 'II_ATR_U',
    'IUTEST_ATTRIBUTE_NORETURN_': 'II_ATR_NR',
    'IUTEST_ATTRIBUTE_FORMAT_PRINTF': 'II_ATR_F_P',
    'IUTEST_ATTRIBUTE_FORMAT': 'II_ATR_F',
    'IUTEST_CXX_OVERRIDE': 'II_CXX_O',
    'IUTEST_CXX_NOEXCEPT_SPEC': 'II_CXX_NEX_S',
    'IUTEST_CXX_DEFAULT_FUNCTION': 'II_CXX_DF_F',
    'IUTEST_CXX_DELETED_FUNCTION': 'II_CXX_DL_F',
    'IUTEST_CXX_FINAL': 'II_CXX_F',
    'IUTEST_CXX_EXPLICIT_CONVERSION': 'II_CXX_E_C',
    'IUTEST_CXX_CONSTEXPR': 'II_CXX_CE',
    'IUTEST_CXX14_CONSTEXPR': 'II_CXX14_CE',
    'IUTEST_CXX_CONSTEXPR_OR_CONST': 'II_CXX_C_O_C',
    'IUTEST_AMBIGUOUS_ELSE_BLOCKER_': 'II_AMB_E_B',
    'IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING': 'II_S_UR_C_W',
    'IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_': 'II_A_E_TT',
    'IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_BEGIN': 'II_PGM_A_O_CN_G_W_D_B',
    'IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_END': 'II_PGM_A_O_CN_G_W_D_E',
    'IUTEST_PRAGMA_WARN_FLOAT_EQUAL': 'II_PGM_W_FE',
    'IUTEST_PRAGMA_WARN_CAST_ALIGN': 'II_PGM_W_CA',
    'IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE': 'II_PGM_W_D_NE_T',
    'IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE': 'II_PGM_W_D_S_C',
    'IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE': 'II_PGM_W_D_D_E',
    'IUTEST_PRAGMA_CLANG_WARN_PUSH': 'II_PGM_C_W_PU',
    'IUTEST_PRAGMA_CLANG_WARN_DISABLE': 'II_PGM_C_W_D',
    'IUTEST_PRAGMA_CLANG_WARN_POP': 'II_PGM_C_W_PP',
    'IUTEST_PRAGMA_GCC_WARN_PUSH': 'II_PGM_G_W_PU',
    'IUTEST_PRAGMA_GCC_WARN_DISABLE': 'II_PGM_G_W_D',
    'IUTEST_PRAGMA_GCC_WARN_POP': 'II_PGM_G_W_PP',
    'IUTEST_PRAGMA_WARN_PUSH': 'II_PGM_W_PU',
    # 'IUTEST_PRAGMA_WARN_DISABLE': 'II_PGM_W_D',
    'IUTEST_PRAGMA_WARN_POP': 'II_PGM_W_PP',
    'IUTEST_PP_DISALLOW_COPY_AND_ASSIGN': 'IP_DIS_C_A_A',
    'IUTEST_PP_DISALLOW_ASSIGN': 'IP_DIS_A',
    'IUTEST_PP_DISALLOW_MOVE_AND_COPY_AND_ASSIGN': 'IP_DIS_M_A_C_A_A',
    'IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING': 'IP_NS_E_C_R_S',
    'IUTEST_PP_INC': 'IP_INC',
    'IUTEST_PP_DEC': 'IP_DEC',
    'IUTEST_PP_CAT': 'IP_CAT',
    'IUTEST_PP_EMPTY': 'IP_EMPTY',
    'IUTEST_PP_IS_BEGIN_PARENS': 'IP_IS_B_PAR',
    'IUTEST_LIBSTDCXX_VERSION': 'II_LSTDCXX_V',
    'II_DECL_STREQ_COMPARE_HELPER_': 'II_DECL_SE_C_H_',
    'IUTEST_PRED_FORMAT_': 'II_PRD_FMT_',
    'IUTEST_PRED_FORMAT1_': 'II_PRD_FMT1_',
    'IUTEST_PRED_FORMAT2_': 'II_PRD_FMT2_',
    'IUTEST_PRED_FORMAT3_': 'II_PRD_FMT3_',
    'IUTEST_PRED_FORMAT4_': 'II_PRD_FMT4_',
    'IUTEST_PRED_FORMAT5_': 'II_PRD_FMT5_',
    'IUTEST_THROW_PRED_FORMAT2_': 'II_T_PRD_FMT2_',
    'IUTEST_PRED_': 'II_PRD_',
    'IUTEST_PRED1_': 'II_PRD1_',
    'IUTEST_PRED2_': 'II_PRD2_',
    'IUTEST_PRED3_': 'II_PRD3_',
    'IUTEST_PRED4_': 'II_PRD4_',
    'IUTEST_PRED5_': 'II_PRD5_',
    'IUTEST_TEST_ASSERT_': 'II_T_ASRT_',
    'IUTEST_TEST_CLASS_NAME_': 'II_T_CLS_N_',
    'IUTEST_TEST_INSTANCE_NAME_': 'II_T_INST_N_',
    'IUTEST_PMZ_TEST_CLASS_NAME_': 'II_P_T_CLS_N_',
    'IUTEST_MESSAGE_AT': 'II_MSG_AT',
    'IUTEST_MESSAGE': 'II_MSG',
}

debug = False

class WandboxPreprocessor:
    pp = IutestPreprocessor(predefined_macros
        , iutest_config_macro
        , expand_function_macros
        , expands_macros
        , has_features
        , has_include)

    def preprocess(self, code, add_macros):
        self.pp.set_debug_flag(debug)
        return self.pp.preprocess(code, add_macros)

    def remove_empty_ppif(self, code):
        return self.pp.remove_empty_ppif(code)

    def remove_redudant(self, code):
        dst = ""
        for line in code.splitlines():
            if '#define IP_D_' in line:
                v = line.split()
                try:
                    if int(v[2]) > 50:
                        continue
                except ValueError:
                    pass
            elif '#define IP_I_' in line:
                v = line.split()
                try:
                    if int(v[2]) > 51:
                        continue
                except ValueError:
                    pass
            elif '#define IP_B_' in line:
                v = line.split()
                v2 = v[1].split('_')
                try:
                    if int(v2[2]) > 51:
                        continue
                except ValueError:
                    pass
            elif 'IUTEST_MBS_CODE' in line:
                continue
            line += "\n"
            dst += line
        return dst

    def rename_macros(self, code):
        dst = ""
        global rename_macro
        found_macros = {}
        for k,v in rename_macro.items():
            if collections.Counter(rename_macro.values())[v] > 1:
                print('error: duplicated ' + v)
                return
        RE_DEFINE = re.compile('#\s*define\s([\w_]+)(.*)$')
        for line in code.splitlines():
            m = RE_DEFINE.match(line)
            if m:
                d = m.group(1)
                if d in rename_macro:
                    alias = rename_macro[d]
                    found_macros[d] = alias
                    del rename_macro[d]
            if len(rename_macro) == 0:
                break
        for line in code.splitlines():
            for k, v in found_macros.items():
                line = line.replace(k, v)
            line = line.replace('backward', 'bkw')
            line = line.replace('IUTEST_MAKE_ASSERTIONRESULT_', '')
            line += "\n"
            dst += line
        for k,v in found_macros.items():
            dst += "#define " + k + " " + v + "\n"
        return dst


def default_pp():
    output_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../fused-src")
    output = "iutest.wandbox.min.hpp"
    f = codecs.open(os.path.join(output_dir, "iutest.min.hpp"), 'r', 'utf-8-sig')
    code = f.read()
    f.close()
    output_file = codecs.open(os.path.join(output_dir, output), 'w', 'utf-8-sig')
    pp = WandboxPreprocessor()
    code = pp.preprocess(code, None)
    code = pp.remove_empty_ppif(code)
    code = pp.remove_redudant(code)
    code = pp.rename_macros(code)
    output_file.write(code)
    output_file.close()


def main():
    global debug
    argc = len(sys.argv)
    if argc == 2:
        if sys.argv[1] == 'debug':
            debug = True
    default_pp()

if __name__ == '__main__':
    main()
