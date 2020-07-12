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
    'WINAPI_FAMILY': None,
    '__AFX_H__': None,
    '__MWERKS__': None,
    '__FreeBSD__': None,
    'sun': None,
    '__sun': None,
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
    'MS_CPP_UNITTESTFRAMEWORK': None,
    'IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION': '1',
    'IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION': '1',
    '__native_client__': None,
    'IUTEST_OS_NACL': None,
    'IUTEST_HAS_INVALID_PARAMETER_HANDLER': '0',
}

iutest_config_macro = {
    'IUTEST_HAS_LIB': '0',
    'IUTEST_HAS_TESTNAME_ALIAS_JP': '0',
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
    'IUTEST_WORKAROUND_MSC_STLSTREAM_C4250',
    'IUTEST_EXPLICIT_TEMPLATE_TYPE_',
    'IUTEST_IF_EXISTS',
    'IUTEST_IF_NOT_EXISTS',
    'IUTEST_STATIC_EXISTS',
    'IUTEST_STATIC_ASSERT_IF_EXISTS',
    'IUTEST_STATIC_ASSERT_IF_NOT_EXISTS',
    'IUTEST_ANALYSIS_ASSUME',
]

#
has_features = {
}

has_include = {
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
