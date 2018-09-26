#!/usr/bin/env python
#
# iupaizaio_pp.py
#
# Copyright (C) 2015-2018, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), '../fused'))
from iutest_pp_strip import IutestPreprocessor

predefined_macros = {
    '__clang__': '1',
    '_LIBCPP_VERSION': '1101',
    'NULL': '0',
    '__linux__': '1',
    '__cplusplus': '201402',
    '__cpp_rvalue_references': '200610',
    '__has_include': None
}

iutest_config_macro = {
}

expands_macros = [
    'IUTEST_IPP_INLINE',
    'IUTEST_NULLPTR',
    'IUTEST_CXX_CONSTEXPR',
    'IUTEST_CXX_CONSTEXPR_OR_CONST',
    'IUTEST_CXX_DELETED_FUNCTION',
    'IUTEST_CXX_DEFAULT_FUNCTION',
    'IUTEST_CXX_EXPLICIT_CONVERSION',
    'IUTEST_CXX_NOEXCEPT_SPEC',
    'IUTEST_CXX_OVERRIDE',
    'IUTEST_CXX_FINAL',
    'IUTEST_CXX_NOTHROW',
    'IUTEST_PRAGMA_GCC_WARN_PUSH',
    'IUTEST_PRAGMA_GCC_WARN_DISABLE',
    'IUTEST_PRAGMA_GCC_WARN_POP',
    'IUTEST_ATTRIBUTE_UNUSED_',
    'IUTEST_ATTRIBUTE_DEPRECATED_',
    'IUTEST_ATTRIBUTE_PURE_',
    'IUTEST_ATTRIBUTE_NORETURN_'
]

#
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
    'IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_'
]

#
clang_has_features = {
    'cxx_nullptr': '1',
    'cxx_attributes': '1',
    'cxx_auto_type': '1',
    'cxx_constexpr': '1',
    'cxx_decltype': '1',
    'cxx_defaulted_functions': '1',
    'cxx_deleted_functions': '1',
    'cxx_explicit_conversions': '1',
    'cxx_generalized_initializers': '1',
    'cxx_lambdas': '1',
    'cxx_noexcept': '1',
    'cxx_override_control': '1',
    'cxx_rtti': '1',
    'cxx_rvalue_references': '1',
    'cxx_static_assert': '1',
    'cxx_strong_enums': '1',
    'cxx_unicode_literals': '1',
    'cxx_variadic_templates': '1',
    'c_generic_selections': '0'
}

clang_has_include = {
    '<cxxabi.h>': '1',
    '<cuchar>': '0',
    '<uchar.h>': '0',
    '<experimental/any>': '0',
    '<ext/cmath>': '0',
    '<array>': '1',
    '<future>': '1',
    '<ratio>': '1',
    '<shared_mutex>': '1',
    '<scoped_allocator>': '1',
    '<typeindex>': '1',
    '<type_traits>': '1',
    '<tr1/tuple>': '0'
}

class PaizaPreprocessor:
    pp = IutestPreprocessor(predefined_macros
        , expand_function_macros
        , expands_macros
        , clang_has_features
        , clang_has_include)

    def preprocess(self, code, add_macros):
        return self.pp.preprocess(code, add_macros)
