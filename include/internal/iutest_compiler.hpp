//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_compiler.hpp
 * @brief       iris unit test compiler 依存の吸収 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_COMPILER_HPP_6DDB27E8_E2FF_4754_80B0_F500025820C4_
#define INCG_IRIS_IUTEST_COMPILER_HPP_6DDB27E8_E2FF_4754_80B0_F500025820C4_

//======================================================================
// include
#include "iutest_platform.hpp"

//======================================================================
// define
#if defined(_MSC_VER) && _MSC_VER == 1700
#  ifndef _VARIADIC_MAX
#    define _VARIADIC_MAX   10
#  endif
#endif

// for clang
#if defined(__clang__)
#  if !defined(IUTEST_CLANG_MAJOR)
#    if defined(__APPLE__)
#      if __clang_major__ > 11
#        define IUTEST_CLANG_MAJOR      10
#      elif __clang_major__ > 10
#        if __clang_minor__ > 3
#          define IUTEST_CLANG_MAJOR    9
#        else
#          define IUTEST_CLANG_MAJOR    8
#        endif
#      elif __clang_major__ > 9
#        if __clang_minor__ > 1
#          define IUTEST_CLANG_MAJOR    7
#        else
#          define IUTEST_CLANG_MAJOR    6
#        endif
#      elif __clang_major__ > 8
#        if __clang_minor__ > 2
#          define IUTEST_CLANG_MAJOR    5
#        else
#          define IUTEST_CLANG_MAJOR    4
#        endif
#      else
#        define IUTEST_CLANG_MAJOR      3
#        if __clang_major__ > 7
#          define IUTEST_CLANG_MINOR    9
#        elif __clang_major__ > 6
#          if __clang_minor__ > 2
#            define IUTEST_CLANG_MINOR  8
#          else
#            define IUTEST_CLANG_MINOR  7
#          endif
#        else
#          define IUTEST_CLANG_MINOR    __clang_major__
#        endif
#      endif
#    else
#      define IUTEST_CLANG_MAJOR  __clang_major__
#    endif
#  endif
#  if !defined(IUTEST_CLANG_MINOR)
#    define IUTEST_CLANG_MINOR  __clang_minor__
#  endif
#endif

// __cplusplus numbers
#define IUTEST_CPLUSPLUS_CXX11 201103L
#define IUTEST_CPLUSPLUS_CXX14 201402L
#define IUTEST_CPLUSPLUS_CXX17 201703L
#define IUTEST_CPLUSPLUS_CXX20 202002L

// __cplusplus
#if     defined(_MSVC_LANG)
#  define IUTEST_CPLUSPLUS      _MSVC_LANG
#elif   defined(__cplusplus)
#  define IUTEST_CPLUSPLUS      __cplusplus
#else
#  define IUTEST_CPLUSPLUS      0
#endif

// c++2a

#if !defined(IUTEST_HAS_CXX2B)
#  if IUTEST_CPLUSPLUS > IUTEST_CPLUSPLUS_CXX20
#    define IUTEST_HAS_CXX2B        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX2B)
#  define IUTEST_HAS_CXX2B          0
#endif

// c++20

#if !defined(IUTEST_HAS_CXX20)
#  if IUTEST_CPLUSPLUS >= IUTEST_CPLUSPLUS_CXX20
#    define IUTEST_HAS_CXX20        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX20)
#  define IUTEST_HAS_CXX20          0
#endif

// c++2a

#if !defined(IUTEST_HAS_CXX2A)
#  if IUTEST_CPLUSPLUS > IUTEST_CPLUSPLUS_CXX17
#    define IUTEST_HAS_CXX2A        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX2A)
#  define IUTEST_HAS_CXX2A          0
#endif

// c++17
//! is c++17 compiler
#if !defined(IUTEST_HAS_CXX17)
#  if IUTEST_CPLUSPLUS >= IUTEST_CPLUSPLUS_CXX17
#    define IUTEST_HAS_CXX17        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX17)
#  define IUTEST_HAS_CXX17          0
#endif

#if !defined(IUTEST_HAS_CXX1Z)
#  if IUTEST_CPLUSPLUS > IUTEST_CPLUSPLUS_CXX14
#    define IUTEST_HAS_CXX1Z        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX1Z)
#  define IUTEST_HAS_CXX1Z          0
#endif

//! is c++14 compiler
#if !defined(IUTEST_HAS_CXX14)
#  if IUTEST_CPLUSPLUS >= IUTEST_CPLUSPLUS_CXX14
#    define IUTEST_HAS_CXX14        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX14)
#  define IUTEST_HAS_CXX14          0
#endif

//! is c++11 compiler
#if !defined(IUTEST_HAS_CXX11)
#  if (IUTEST_CPLUSPLUS >= IUTEST_CPLUSPLUS_CXX11) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_CXX11        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX11)
#  define IUTEST_HAS_CXX11          0
#endif


// c++20 features

//! has concepts
#if !defined(IUTEST_HAS_CONCEPTS)
#  if   defined(__cpp_concepts) && __cpp_concepts >= 201907
#    define IUTEST_HAS_CONCEPTS             1
#  elif IUTEST_HAS_CXX2A && defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 192328105
#    define IUTEST_HAS_CONCEPTS             1
#  endif
#endif

#if !defined(IUTEST_HAS_CONCEPTS)
#  define IUTEST_HAS_CONCEPTS               0
#endif

// c++17 features

//! inline variable
#if !defined(IUTEST_HAS_INLINE_VARIABLE)
#if   defined(__cpp_inline_variables) && __cpp_inline_variables >= 201606
#  define IUTEST_HAS_INLINE_VARIABLE        1
#elif defined(__clang__)
#  if IUTEST_HAS_CXX1Z && (IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR >= 9))
#    define IUTEST_HAS_INLINE_VARIABLE      1
#  endif
#endif
#endif

#if !defined(IUTEST_HAS_INLINE_VARIABLE)
#  define IUTEST_HAS_INLINE_VARIABLE        0
#endif

//! constexpr if
#if !defined(IUTEST_HAS_CONSTEXPR_IF)
#  if   defined(__cpp_if_constexpr) && __cpp_if_constexpr >= 201606
#    define IUTEST_HAS_CONSTEXPR_IF         1
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1910 && IUTEST_HAS_CXX17
#      define IUTEST_HAS_CONSTEXPR_IF       1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_CONSTEXPR_IF)
#  define IUTEST_HAS_CONSTEXPR_IF           0
#endif

// c++11 features

//! has nullptr
#if !defined(IUTEST_HAS_NULLPTR)
#  if   defined(_NATIVE_NULLPTR_SUPPORTED)
#    define IUTEST_HAS_NULLPTR      1
#  elif defined(__clang__)
#    if __has_feature(cxx_nullptr)
#      define IUTEST_HAS_NULLPTR    1
#    endif
#    if  (IUTEST_CLANG_MAJOR < 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR <= 2))
#      define IUTEST_NO_NULL_TO_NULLPTR_T   1   // -Wnull-conversion
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER > 1200
#      define IUTEST_HAS_NULLPTR    1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_NULLPTR    1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER > 1500
#      define IUTEST_HAS_NULLPTR    1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_NULLPTR)
#  define IUTEST_HAS_NULLPTR        0
#endif

#if !defined(IUTEST_NULLPTR)
#  if IUTEST_HAS_NULLPTR
#    define IUTEST_NULLPTR          nullptr
#  else
#    define IUTEST_NULLPTR          NULL
#  endif
#endif

//! auto
#if !defined(IUTEST_HAS_AUTO)
#  if   defined(__clang__)
#    if __has_feature(cxx_auto_type)
#      define IUTEST_HAS_AUTO   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_AUTO   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_AUTO   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_AUTO   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_AUTO)
#  define IUTEST_HAS_AUTO       0
#endif

//! has decltype
#if !defined(IUTEST_HAS_DECLTYPE)
#  if   defined(__cpp_decltype) && __cpp_decltype >= 200707
#    define IUTEST_HAS_DECLTYPE     1
#  elif defined(__clang__)
#    if __has_feature(cxx_decltype)
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_DECLTYPE)
#  define IUTEST_HAS_DECLTYPE       0
#endif

//! has static_assert
#if !defined(IUTEST_HAS_STATIC_ASSERT)
#  if   defined(__cpp_static_assert) && __cpp_static_assert >= 200410
#    define IUTEST_HAS_STATIC_ASSERT    1
#  elif defined(__clang__)
#    if __has_feature(cxx_static_assert)
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER > 1100
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_STATIC_ASSERT)
#  define IUTEST_HAS_STATIC_ASSERT  0
#endif


//! has constexpr
#if !defined(IUTEST_HAS_CONSTEXPR)
#  if   defined(__cpp_constexpr) && __cpp_constexpr >= 200704
#    define IUTEST_HAS_CONSTEXPR    1
#  elif defined(__clang__)
#    if __has_feature(cxx_constexpr)
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900 || _MSC_FULL_VER == 180021114
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_CONSTEXPR)
#  define IUTEST_HAS_CONSTEXPR      0
#endif

//! constexpr
#if IUTEST_HAS_CONSTEXPR
#  define IUTEST_CXX_CONSTEXPR          constexpr
#else
#  define IUTEST_CXX_CONSTEXPR
#endif

#if IUTEST_HAS_CONSTEXPR && \
        (defined(__cpp_constexpr) && __cpp_constexpr >= 201304 || IUTEST_HAS_CXX14)
#  define IUTEST_CXX14_CONSTEXPR        constexpr
#else
#  define IUTEST_CXX14_CONSTEXPR
#endif

//! constexpr or const
#if IUTEST_HAS_CONSTEXPR
#  define IUTEST_CXX_CONSTEXPR_OR_CONST constexpr
#else
#  define IUTEST_CXX_CONSTEXPR_OR_CONST const
#endif

//! has rvalue reference
#if !defined(IUTEST_HAS_RVALUE_REFS)
#  if   defined(__cpp_rvalue_references) && __cpp_rvalue_references >= 200610
#      define IUTEST_HAS_RVALUE_REFS    1
#  elif defined(__clang__)
#    if __has_feature(cxx_rvalue_references)
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1700)
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_RVALUE_REFS)
#  define IUTEST_HAS_RVALUE_REFS    0
#endif

//! has delete function
#ifndef IUTEST_HAS_DELETED_FUNCTIONS
#  if   defined(__clang__)
#    if __has_feature(cxx_deleted_functions)
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  elif defined(_MSC_VER)
#    if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180020827)
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_DELETED_FUNCTIONS)
#  define IUTEST_HAS_DELETED_FUNCTIONS      0
#endif

//! delete function
#if IUTEST_HAS_DELETED_FUNCTIONS
#  define IUTEST_CXX_DELETED_FUNCTION   = delete
#else
#  define IUTEST_CXX_DELETED_FUNCTION
#endif

#if !defined(IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION) && !IUTEST_HAS_RVALUE_REFS
#  define IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION   0
#endif

//! has default function
#if !defined(IUTEST_HAS_DEFAULT_FUNCTIONS)
#  if   defined(__clang__)
#    if __has_feature(cxx_defaulted_functions)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(__GNUC__)
// move assignment operator = default is not works in gcc 4.4
// private destractor = default is not works in gcc 4.5 - 4.6
#    if   (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ == 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#      if !defined(IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION)
#        define IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION 0
#      endif
#    elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(_MSC_VER)
#    if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180020827)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#      if (_MSV_VER <= 1800) && !defined(IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION)
#        define IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION 0
#      endif
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_DEFAULT_FUNCTIONS)
#  define IUTEST_HAS_DEFAULT_FUNCTIONS      0
#endif
#if !defined(IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION)
#  define IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION   IUTEST_HAS_DEFAULT_FUNCTIONS
#endif

//! default function
#if IUTEST_HAS_DEFAULT_FUNCTIONS
#  define IUTEST_CXX_DEFAULT_FUNCTION   = default;
#else
#  define IUTEST_CXX_DEFAULT_FUNCTION   {}
#endif

//! has initializer_list
#if !defined(IUTEST_HAS_INITIALIZER_LIST)
#  if   defined(__cpp_initializer_lists) && __cpp_initializer_lists >= 200806
#    define IUTEST_HAS_INITIALIZER_LIST 1
#  elif defined(__clang__)
#    if __has_feature(cxx_generalized_initializers)
#      define IUTEST_HAS_INITIALIZER_LIST   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_INITIALIZER_LIST   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_INITIALIZER_LIST   1
#    endif
#  elif defined(_MSC_VER)
#    if   (_MSC_VER >= 1800)
#      define IUTEST_HAS_INITIALIZER_LIST   1
#    elif (_MSC_FULL_VER == 170051025)
#      define IUTEST_HAS_INITIALIZER_LIST   1
#      include <initializer_list>
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_INITIALIZER_LIST)
#  define IUTEST_HAS_INITIALIZER_LIST       0
#endif

//! has variadic template
#if !defined(IUTEST_HAS_VARIADIC_TEMPLATES)
#  if   defined(__cpp_variadic_templates) && __cpp_variadic_templates >= 200704
#    define IUTEST_HAS_VARIADIC_TEMPLATES   1
#  elif defined(__clang__)
#    if __has_feature(cxx_variadic_templates)
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER > 1200
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
#    endif
#  elif defined(__GNUC__)
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=35722
#    if defined(__VARIADIC_TEMPLATES)   \
            || ( ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))) && defined(__GXX_EXPERIMENTAL_CXX0X__) )
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
#    endif
#  elif defined(_MSC_VER)
#    if   (_MSC_VER >= 1800)
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
#    elif (_MSC_FULL_VER == 170051025)
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
#      define IUTEST_HAS_VARIADIC_COMBINE   0
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_VARIADIC_TEMPLATES)
#  define IUTEST_HAS_VARIADIC_TEMPLATES     0
#endif

//! has variadic template templates
#if !defined(IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES)
#  if   defined(__clang__)
#    if __has_feature(cxx_variadic_templates)
#      define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES    1
#    endif
#  elif defined(__INTEL_COMPILER)
#    define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES  IUTEST_HAS_VARIADIC_TEMPLATES
#  elif defined(__GNUC__)
#    if defined(__VARIADIC_TEMPLATES) || ( ((__GNUC__ > 4) \
                || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) \
                || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7) && (__GNUC_PATCHLEVEL__ >= 1))) \
                && defined(__GXX_EXPERIMENTAL_CXX0X__) )
#      define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES    1
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES  IUTEST_HAS_VARIADIC_TEMPLATES
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES
#  define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES    0
#endif

//! has char16_t
#if !defined(IUTEST_HAS_CHAR16_T)
#  if   defined(__cpp_unicode_characters) && __cpp_unicode_characters >= 200704 && defined(__cpp_unicode_literals) && __cpp_unicode_literals >= 200710
#    define IUTEST_HAS_CHAR16_T     1
#  elif defined(__clang__)
#    if __has_feature(cxx_unicode_literals)
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_CHAR16_T)
#  define IUTEST_HAS_CHAR16_T   0
#endif

//! has char32_t
#ifndef IUTEST_HAS_CHAR32_T
#  if   defined(__cpp_unicode_characters) && __cpp_unicode_characters >= 200704 && defined(__cpp_unicode_literals) && __cpp_unicode_literals >= 200710
#    define IUTEST_HAS_CHAR32_T 1
#  elif defined(__clang__)
#    if __has_feature(cxx_unicode_literals)
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_CHAR32_T)
#  define IUTEST_HAS_CHAR32_T   0
#endif

//! has lambda
#if !defined(IUTEST_HAS_LAMBDA)
#  if   defined(__cpp_lambdas) && __cpp_lambdas >= 200907
#    define IUTEST_HAS_LAMBDA       1
#  elif defined(__clang__)
#    if __has_feature(cxx_lambdas)
#      define IUTEST_HAS_LAMBDA     1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_LAMBDA     1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_LAMBDA     1
#    endif
#  elif defined(_MSC_VER)
#    if   _MSC_VER > 1800
#      define IUTEST_HAS_LAMBDA     1
#    elif _MSC_VER > 1600
#      define IUTEST_HAS_LAMBDA     1
#      define IUTEST_NO_LAMBDA_SEH_SCOPE_RESOLUTION // lambda v1.1 is not supported try/__try scope resolution.
#    elif _MSC_VER == 1600
#      define IUTEST_HAS_LAMBDA     1
#      define IUTEST_NO_LAMBDA_SCOPE_RESOLUTION // VC++10 lambda v1.0 is not supported.
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_LAMBDA)
#  define IUTEST_HAS_LAMBDA     0
#endif

#if IUTEST_HAS_LAMBDA
#  if defined(__GNUC__)
#    if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7))
#      define IUTEST_NO_LAMBDA_LOCAL_OBJECT_TEMPLATE_PARAMETERS
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_NO_LAMBDA_LOCAL_OBJECT_TEMPLATE_PARAMETERS
#  endif
#endif

//! explicit conversion operator
#if !defined(IUTEST_HAS_EXPLICIT_CONVERSION)
#  if   defined(__clang__)
#    if __has_feature(cxx_explicit_conversions)
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1300
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1800) || (_MSC_FULL_VER == 170051025)
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_EXPLICIT_CONVERSION)
#  define IUTEST_HAS_EXPLICIT_CONVERSION        0
#endif

//! explicit conversion definition
#if !defined(IUTEST_CXX_EXPLICIT_CONVERSION)
#  if IUTEST_HAS_EXPLICIT_CONVERSION
#    define IUTEST_CXX_EXPLICIT_CONVERSION      explicit
#  else
#    define IUTEST_CXX_EXPLICIT_CONVERSION
#  endif
#endif

//! has override and final
#if !defined(IUTEST_HAS_OVERRIDE_AND_FINAL)
#  if   defined(__clang__)
#    if __has_feature(cxx_override_control)
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1700
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_OVERRIDE_AND_FINAL)
#  define IUTEST_HAS_OVERRIDE_AND_FINAL     0
#endif

//! override definition
#if !defined(IUTEST_CXX_OVERRIDE)
#  if IUTEST_HAS_OVERRIDE_AND_FINAL
#    define IUTEST_CXX_OVERRIDE     override
#  else
#    define IUTEST_CXX_OVERRIDE
#  endif
#endif

//! final definition
#if !defined(IUTEST_CXX_FINAL)
#  if IUTEST_HAS_OVERRIDE_AND_FINAL
#    define IUTEST_CXX_FINAL        final
#  else
#    define IUTEST_CXX_FINAL
#  endif
#endif

//! has noexcept
#ifndef IUTEST_HAS_NOEXCEPT
#  if   defined(__clang__)
#    if __has_feature(cxx_noexcept)
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  elif defined(_MSC_VER)
// https://connect.microsoft.com/VisualStudio/feedback/details/809079/torino-compile-error-template-noexcept
#    if _MSC_FULL_VER >= 190022816
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_NOEXCEPT)
#  define IUTEST_HAS_NOEXCEPT   0
#endif

//! noexcept function type
#if !defined(IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE)
#  if defined(__cpp_noexcept_function_type) && __cpp_noexcept_function_type >= 201510L
#    define IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE 1
#  endif
#endif

#if !defined(IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE)
#  define IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE 0
#endif

//! noexcept definition
#if !defined(IUTEST_CXX_NOEXCEPT)
#  if IUTEST_HAS_NOEXCEPT
#    define IUTEST_CXX_NOEXCEPT(expr_)      noexcept(expr_)
#  else
#    define IUTEST_CXX_NOEXCEPT(expr_)
#  endif
#endif

//! noexcept specification definition
#if !defined(IUTEST_CXX_NOEXCEPT_SPEC)
#  if IUTEST_HAS_NOEXCEPT
#    define IUTEST_CXX_NOEXCEPT_SPEC        noexcept
#  else
#    define IUTEST_CXX_NOEXCEPT_SPEC
#  endif
#endif

#if !defined(IUTEST_CXX_NOEXCEPT_AS)
#  if IUTEST_HAS_NOEXCEPT
#    define IUTEST_CXX_NOEXCEPT_AS(expr_)   noexcept( noexcept(expr_) )
#  else
#    define IUTEST_CXX_NOEXCEPT_AS(expr_)
#  endif
#endif

//! nothrow definition
#if !defined(IUTEST_CXX_NOTHROW)
#  if IUTEST_HAS_NOEXCEPT
#    define IUTEST_CXX_NOTHROW  noexcept
#  elif IUTEST_HAS_CXX2A
#    define IUTEST_CXX_NOTHROW
#  else
#    define IUTEST_CXX_NOTHROW  throw() // C++20 で消える
#  endif
#endif

//! has extern template
#if !defined(IUTEST_HAS_EXTERN_TEMPLATE)
#  if defined(_MSC_VER) && _MSC_VER >= 1400
#    define IUTEST_HAS_EXTERN_TEMPLATE      1
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER > 1100
#      define IUTEST_HAS_EXTERN_TEMPLATE    1
#    endif
#  elif defined(__GNUC__) || defined(__clang__)
#    define IUTEST_HAS_EXTERN_TEMPLATE      1
#  endif
#endif

#if !defined(IUTEST_HAS_EXTERN_TEMPLATE)
#  define IUTEST_HAS_EXTERN_TEMPLATE    0
#endif

//! has enum class
#if !defined(IUTEST_HAS_STRONG_ENUMS)
#  if   defined(__clang__)
#    if __has_feature(cxx_strong_enums)
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if IUTEST_HAS_CXX11 && __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1700
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_STRONG_ENUMS)
#  define IUTEST_HAS_STRONG_ENUMS       0
#endif

// c++
//! has exceptions
#if !defined(IUTEST_HAS_EXCEPTIONS)
#  if   defined(_MSC_VER)
#    if defined(_CPPUNWIND) && _CPPUNWIND
#      define IUTEST_HAS_EXCEPTIONS 1
#    endif
#  elif defined(__BORLANDC__)
#    ifndef _HAS_EXCEPTIONS
#      define _HAS_EXCEPTIONS       1
#    endif
#    define IUTEST_HAS_EXCEPTIONS   _HAS_EXCEPTIONS
#  elif defined(__clang__)
#    if __EXCEPTIONS && __has_feature(cxx_exceptions)
#      define IUTEST_HAS_EXCEPTIONS 1
#    endif
#  elif defined(__GNUC__)
#    if defined(__EXCEPTIONS)
#      define IUTEST_HAS_EXCEPTIONS 1
#    endif
#  elif defined(__MWERKS__)
#    if __option(exceptions)
#      define IUTEST_HAS_EXCEPTIONS 1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_EXCEPTIONS)
#  define IUTEST_HAS_EXCEPTIONS 0
#endif

//! has Structured Exception Handling
#if !defined(IUTEST_HAS_SEH)
#  if   defined(_WIN32) && !defined(__clang__)
#    if defined(_MSC_VER) && _MSC_VER > 1400
#      define IUTEST_HAS_SEH    IUTEST_HAS_EXCEPTIONS
#    endif
#  elif defined(__BORLANDC__)
#    define IUTEST_HAS_SEH      IUTEST_HAS_EXCEPTIONS
#  endif
#endif

#if !defined(IUTEST_HAS_SEH)
#  define IUTEST_HAS_SEH        0
#endif

//! has RTTI
#if !defined(IUTEST_HAS_RTTI)
#  if   defined(__clang__)
#    if __has_feature(cxx_rtti)
#      define IUTEST_HAS_RTTI   1
#    endif
#    if defined(_MSC_VER)   // clang for windows
#      if !defined(_CPPRTTI)
#        include <exception>
#      endif
#    endif
#  elif defined(__GNUC__)
#    ifdef __RTTI
#      define IUTEST_HAS_RTTI   1
#    endif
#    ifdef __GXX_RTTI
#      define IUTEST_HAS_RTTI   1
#    endif
#  elif defined(__MWERKS__)
#    if __option(RTTI)
#      define IUTEST_HAS_RTTI   1
#    endif
#  elif defined(__ARMCC_VERSION)
#    ifdef __RTTI
#      define IUTEST_HAS_RTTI   1
#    endif
#  elif defined(__IBMCPP__)
#    if (__IBMCPP__ >= 900)
#      define IUTEST_HAS_RTTI   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if defined(__INTEL_RTTI__) || defined(__cpp_rtti)
#      define IUTEST_HAS_RTTI   1
#    endif
#  elif defined(_MSC_VER)
#    ifdef _CPPRTTI
#      define IUTEST_HAS_RTTI   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_RTTI)
#  define IUTEST_HAS_RTTI       0
#endif

#if IUTEST_HAS_RTTI
#  include <typeinfo>
#endif

#if !defined(IUTEST_WCHAR_UNSIGNED)
#  if defined(__WCHAR_UNSIGNED__) && __WCHAR_UNSIGNED__
#    define IUTEST_WCHAR_UNSIGNED   1
#  elif defined(_MSC_VER)
#    if defined(_NATIVE_WCHAR_T_DEFINED)
#      define IUTEST_WCHAR_UNSIGNED 1
#    endif
#  endif
#endif

#if !defined(IUTEST_WCHAR_UNSIGNED)
#  define IUTEST_WCHAR_UNSIGNED 0
#endif

//! has 128bit type
#if !defined(IUTEST_HAS_INT128)
#  if defined(__SIZEOF_INT128__) && __SIZEOF_INT128__ == 16
#    define IUTEST_HAS_INT128   1
#  elif defined(_MSC_VER) && defined(_M_X64)
// https://docs.microsoft.com/ja-jp/cpp/cpp/fundamental-types-cpp?view=vs-2019
// __int128 is not supported
// #    define IUTEST_HAS_INT128   1
#  endif
#endif

#if !defined(IUTEST_HAS_INT128)
#  define IUTEST_HAS_INT128         0
#endif

//! hsa 128bit float type
#if !defined(IUTEST_HAS_FLOAT128)
#  if defined(__SIZEOF_FLOAT128__) && IUTEST_HAS_INT128
#    if   defined(__clang__)
#      if IUTEST_CLANG_MAJOR > 4 && defined(__has_include)
#        if __has_include(<quadmath.h>)
#          define IUTEST_HAS_FLOAT128   1
#        endif
#      endif
#    else
#      define IUTEST_HAS_FLOAT128   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_FLOAT128)
#  define IUTEST_HAS_FLOAT128       0
#endif

#if IUTEST_HAS_FLOAT128
#  if defined(__FLT128_MANT_DIG__)
#    define IUTEST_FLT128_MANT_DIG  __FLT128_MANT_DIG__
#  else
#    define IUTEST_FLT128_MANT_DIG  113
#  endif
#endif

//! long double as is double
#if !defined(IUTEST_LONG_DOUBLE_AS_IS_DOUBLE)
#  if defined(__SIZEOF_LONG_DOUBLE__) && defined(__SIZEOF_DOUBLE__) \
            && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
#    define IUTEST_LONG_DOUBLE_AS_IS_DOUBLE 1
#  endif
#endif

#if !defined(IUTEST_LONG_DOUBLE_AS_IS_DOUBLE)
#  define IUTEST_LONG_DOUBLE_AS_IS_DOUBLE   0
#endif

//! has long double
#if !defined(IUTEST_HAS_LONG_DOUBLE)
#  if defined(__SIZEOF_LONG_DOUBLE__)
#    if IUTEST_LONG_DOUBLE_AS_IS_DOUBLE || IUTEST_HAS_INT128
#      define IUTEST_HAS_LONG_DOUBLE  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_LONG_DOUBLE)
#  define IUTEST_HAS_LONG_DOUBLE    0
#endif

//! explicit instantiation access checking
#if !defined(IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION)
#  if defined(_MSC_VER) && ((_MSC_VER < 1600) || (_MSC_VER == 1900))
// VS2008 以前では、private なメンバー関数に explicit instantiation でもアクセスできない
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION    0
#  else
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION    1
#  endif
#endif

//! explicit instantiation access checking (static member function)
#if !defined(IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION)
#  if defined(_MSC_VER) && (_MSC_VER < 1910)
// Visual Studio では、private な static メンバー関数に explicit instantiation でもアクセスできない
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION 0
#  else
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION 1
#  endif
#endif

//! explicit instantiation access checking (overload member function)
#if !defined(IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION)
#  if defined(_MSC_VER) && (_MSC_VER < 1900)
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION   0
#  elif defined(__clang__)
// Does clang give priority to access restrictions during overload resolution?
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION   0
#  else
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION   1
#  endif
#endif

// 可変長引数マクロ
#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  if defined(_MSC_VER) && (_MSC_VER < 1500)
#    define IUTEST_NO_VARIADIC_MACROS       1
#  endif
#endif

//! has __COUNTER__
#if !defined(IUTEST_HAS_COUNTER_MACRO)
#  if   defined(_MSC_VER) && (_MSC_VER >= 1300)
#    define IUTEST_HAS_COUNTER_MACRO        1
#  elif defined(__clang__)
#    define IUTEST_HAS_COUNTER_MACRO        1
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#      define IUTEST_HAS_COUNTER_MACRO      1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_COUNTER_MACRO)
#  define IUTEST_HAS_COUNTER_MACRO          0
#endif

//! has file stat
#if !defined(IUTEST_HAS_FILE_STAT)
#  if !defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_FILE_STAT            1
#  endif
#endif

//! has fileno
#if !defined(IUTEST_HAS_FILENO)
#  if !defined(IUTEST_OS_WINDOWS_MOBILE) && !defined(__STRICT_ANSI__)
#    define IUTEST_HAS_FILENO               1
#  endif
#endif

//! explicit class member template specialization
#if !defined(IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION)
#  if defined(_MSC_VER)
#    define IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION 1
#  else
#    define IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION 0
#  endif
#endif

//! partial template specialization
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#  if defined(_MSC_VER) && (_MSC_VER < 1310)
#    define IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION   1
#  endif
#endif

//! has two pahse name lookup
#if !defined(IUTEST_NO_TWO_PHASE_NAME_LOOKUP)
// Visual Studio 2017 (15.3) 以降は two phase name lookup が実装されている
// （コンパイルオプションで無視できるが iutest はこれを検出しない）
#  if defined(_MSC_VER) && (_MSC_VER < 1910)
#    define IUTEST_NO_TWO_PHASE_NAME_LOOKUP             1
#  endif
#endif

//! function template ordering
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
#  if defined(_MSC_VER) && (_MSC_VER < 1310)
#    define IUTEST_NO_FUNCTION_TEMPLATE_ORDERING        1
#  endif
#endif

//! in class member initialization
#if !defined(IUTEST_NO_INCLASS_MEMBER_INITIALIZATION)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_INCLASS_MEMBER_INITIALIZATION     1
#  endif
#endif

//! explicit function template instantiation
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS  1
#  endif
#endif

//! SFINAE
#if !defined(IUTEST_NO_SFINAE)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_SFINAE    1
#  endif
#endif

//! template template
#if !defined(IUTEST_NO_TEMPLATE_TEMPLATES)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_TEMPLATE_TEMPLATES    1
#  endif
#endif

//! void return
#if !defined(IUTEST_NO_VOID_RETURNS)
#  if defined(_MSC_VER) && _MSC_VER < 1300
#    define IUTEST_NO_VOID_RETURNS          1
#  endif
#endif

//! ADL
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP 1
#  endif
#endif

#if !defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
#  if defined(_MSC_VER) && _MSC_VER < 1310
#    define IUTEST_NO_PRIVATE_IN_AGGREGATE  1
#  endif
#endif

//! secure lib
#if !defined(IUTEST_HAS_WANT_SECURE_LIB)
#  if defined(_MSC_VER)
#    if defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__
#      define IUTEST_HAS_WANT_SECURE_LIB    1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_WANT_SECURE_LIB)
#  define IUTEST_HAS_WANT_SECURE_LIB        0
#endif

// MS extensions

//! has Microsoft compiler extension
#if !defined(IUTEST_HAS_MS_EXTENSIONS)
#  if defined(__clang__)
//#    if defined(_MSC_VER)
//#      define IUTEST_HAS_MS_EXTENSIONS        1
//#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_HAS_MS_EXTENSIONS        1
#  endif
#endif

#if !defined(IUTEST_HAS_MS_EXTENSIONS)
#  define IUTEST_HAS_MS_EXTENSIONS          0
#endif

//! has __if_exists
#if !defined(IUTEST_HAS_IF_EXISTS)
#  if defined(__clang__)
#    if IUTEST_HAS_MS_EXTENSIONS && (IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR >= 5) )
#      define IUTEST_HAS_IF_EXISTS          1
#    endif
#  elif defined(_MSC_VER) && _MSC_VER >= 1310
#    define IUTEST_HAS_IF_EXISTS            1
#  endif
#endif

#if !defined(IUTEST_HAS_IF_EXISTS)
#  define IUTEST_HAS_IF_EXISTS      0
#endif

//! has __analysis_assume
#if !defined(IUTEST_HAS_ANALYSIS_ASSUME)
#  if defined(_MSC_VER) && (_MSC_VER >= 1500) && !defined(__CUDACC__)
#    define IUTEST_HAS_ANALYSIS_ASSUME      1
#    define IUTEST_ANALYSIS_ASSUME          __analysis_assume
//#  elif defined(__clang__)
//#    if __has_builtin(__builtin_assume)
//#      define IUTEST_HAS_ANALYSIS_ASSUME  1
//#      define IUTEST_ANALYSIS_ASSUME      __builtin_assume
//#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_ANALYSIS_ASSUME)
#  define IUTEST_HAS_ANALYSIS_ASSUME        0
#endif
#if !defined(IUTEST_ANALYSIS_ASSUME)
#  if defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_ANALYSIS_ASSUME(x)       (void)0
#  else
#    define IUTEST_ANALYSIS_ASSUME(...)     (void)0
#  endif
#endif

#if !defined(IUTEST_HAS_MS_CXX_MODULE)
#  if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023506
#    define IUTEST_HAS_MS_CXX_MODULE        1
#  endif
#endif

#if !defined(IUTEST_HAS_MS_CXX_MODULE)
#  define IUTEST_HAS_MS_CXX_MODULE          0
#endif

#if IUTEST_HAS_MS_CXX_MODULE
#  define IUTEST_CXX_MODULE_EXPORT          export
#else
#  define IUTEST_CXX_MODULE_EXPORT
#endif

// C11

//! has _Generic
#if !defined(IUTEST_HAS_GENERIC)
#  if   defined(__clang__)
#    if __has_feature(c_generic_selections)
#      define IUTEST_HAS_GENERIC    1
#    endif
#  elif defined(__GNUC__)
//#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
//#      define IUTEST_HAS_GENERIC  1
//#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_GENERIC)
#  define IUTEST_HAS_GENERIC        0
#endif

// attribute

//! has c++11 attribute [[]]
#if !defined(IUTEST_HAS_ATTRIBUTE)
#  if defined(__cpp_attributes) && __cpp_attributes >= 200809
#    define IUTEST_HAS_ATTRIBUTE    1
#  elif   defined(__clang__)
#    if __has_feature(cxx_attributes)
#      define IUTEST_HAS_ATTRIBUTE  1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_ATTRIBUTE  1
#    endif
#  elif   defined(_MSC_VER)
#    if _MSC_VER > 1800
#      define IUTEST_HAS_ATTRIBUTE  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_ATTRIBUTE)
#  define IUTEST_HAS_ATTRIBUTE      0
#endif

//! has likely/unlikely attribute
#if !defined(IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY)
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(likely) >= 201803L && __has_cpp_attribute(unlikely) >= 201803L
#      if defined(__GNUC__) && (__GNUC__ <= 9)
// gcc 9.X likely is experimental. can be used in switch~case, cannot be used in if statement
#        define IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY  0
#       else
#        define IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY  IUTEST_HAS_ATTRIBUTE
#       endif
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY)
#  define IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY      0
#endif

//! likely attribute
#if !defined(IUTEST_ATTRIBUTE_LIKELY_)
#  if IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY
#    define IUTEST_ATTRIBUTE_LIKELY_    [[likely]]
#  else
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_LIKELY_)
#  define IUTEST_ATTRIBUTE_LIKELY_
#endif

//! unlikely attribute
#if !defined(IUTEST_ATTRIBUTE_UNLIKELY_)
#  if IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY
#    define IUTEST_ATTRIBUTE_UNLIKELY_  [[unlikely]]
#  else
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_UNLIKELY_)
#  define IUTEST_ATTRIBUTE_UNLIKELY_
#endif

//! has deprecated attribute
#if !defined(IUTEST_HAS_ATTRIBUTE_DEPRECATED)
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(deprecated) >= 201309
#      define IUTEST_HAS_ATTRIBUTE_DEPRECATED   IUTEST_HAS_ATTRIBUTE
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_ATTRIBUTE_DEPRECATED   1
#    endif
#  elif   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR >= 4)
#      define IUTEST_HAS_ATTRIBUTE_DEPRECATED   1
#    endif
#  elif   defined(_MSC_VER)
#    define IUTEST_HAS_ATTRIBUTE_DEPRECATED     IUTEST_HAS_ATTRIBUTE
#  endif
#endif

#if !defined(IUTEST_HAS_ATTRIBUTE_DEPRECATED)
#  define IUTEST_HAS_ATTRIBUTE_DEPRECATED       0
#endif

//! deprecated attribute
#if !defined(IUTEST_ATTRIBUTE_DEPRECATED_)
#  if IUTEST_HAS_ATTRIBUTE_DEPRECATED
#    define IUTEST_ATTRIBUTE_DEPRECATED_        [[deprecated]]
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_DEPRECATED_)
#  define IUTEST_ATTRIBUTE_DEPRECATED_
#endif

//! unused attribute
#if !defined(IUTEST_ATTRIBUTE_UNUSED_)
#  if (defined(__GNUC__) && !defined(COMPILER_ICC))
#    define IUTEST_ATTRIBUTE_UNUSED_    __attribute__((unused))
#  elif defined(__clang__)
#    if __has_attribute(unused)
#      define IUTEST_ATTRIBUTE_UNUSED_  __attribute__((unused))
#    endif
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_UNUSED_)
#  define IUTEST_ATTRIBUTE_UNUSED_
#endif

//! pure attribute
#if !defined(IUTEST_ATTRIBUTE_PURE_)
#  if defined(__GNUC__) && !defined(COMPILER_ICC)
#    define IUTEST_ATTRIBUTE_PURE_      __attribute__((pure))
#  else
#    define IUTEST_ATTRIBUTE_PURE_
#  endif
#endif

//! noreturn
#if !defined(IUTEST_ATTRIBUTE_NORETURN_)
#  if IUTEST_HAS_ATTRIBUTE
#    define IUTEST_ATTRIBUTE_NORETURN_      [[noreturn]]
#  elif   defined(__clang__)
#    if __has_attribute(noreturn)
#      define IUTEST_ATTRIBUTE_NORETURN_    __attribute__((noreturn))
#    endif
#  elif defined(__GNUC__) && !defined(COMPILER_ICC)
#    define IUTEST_ATTRIBUTE_NORETURN_      __attribute__((noreturn))
#  elif defined(_MSC_VER)
#    define IUTEST_ATTRIBUTE_NORETURN_      __declspec(noreturn)
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_NORETURN_)
#  define IUTEST_ATTRIBUTE_NORETURN_
#endif

//! init_priority
#if !defined(IUTEST_ATTRIBUTE_INIT_PRIORITY_)
#  if   defined(__clang__)
#    if __has_attribute(init_priority)
#      define IUTEST_ATTRIBUTE_INIT_PRIORITY_(n)    __attribute__((init_priority(n)))
#    endif
#  elif defined(__GNUC__) && !defined(COMPILER_ICC)
#    define IUTEST_ATTRIBUTE_INIT_PRIORITY_(n)      __attribute__((init_priority(n)))
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_INIT_PRIORITY_)
#  define IUTEST_ATTRIBUTE_INIT_PRIORITY_(n)
#endif

//! format
#if !defined(IUTEST_ATTRIBUTE_FORMAT)
#  if   defined(__has_attribute)
#    if __has_attribute(format)
#      define IUTEST_ATTRIBUTE_FORMAT(fmt, fi, vi)  __attribute__ ((__format__ (fmt, fi, vi)))
#    endif
#  elif defined(__GNUC__) && !defined(COMPILER_ICC)
#    define IUTEST_ATTRIBUTE_FORMAT(fmt, fi, vi)    __attribute__ ((__format__ (fmt, fi, vi)))
#  endif
#endif

//! format printf
#if !defined(IUTEST_ATTRIBUTE_FORMAT_PRINTF) && defined(IUTEST_ATTRIBUTE_FORMAT)
#  if defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#    if !defined(__MINGW_PRINTF_FORMAT)
#      define __MINGW_PRINTF_FORMAT     gnu_printf
#    endif
#    define IUTEST_ATTRIBUTE_FORMAT_PRINTF(fi, vi)  IUTEST_ATTRIBUTE_FORMAT(__MINGW_PRINTF_FORMAT, fi, vi)
#  else
#    define IUTEST_ATTRIBUTE_FORMAT_PRINTF(fi, vi)  IUTEST_ATTRIBUTE_FORMAT(__printf__, fi, vi)
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_FORMAT)
#  define IUTEST_ATTRIBUTE_FORMAT(fmt, fi, vi)
#endif
#if !defined(IUTEST_ATTRIBUTE_FORMAT_PRINTF)
#  define IUTEST_ATTRIBUTE_FORMAT_PRINTF(fi, vi)
#endif


// builtin

//! builtin expect
#if !defined(IUTEST_HAS_BUILTIN_EXPECT)
#  if defined(__clang__) || defined(__GNUC__)
#    define IUTEST_HAS_BUILTIN_EXPECT   1
#  endif
#endif

#if !defined(IUTEST_HAS_BUILTIN_EXPECT)
#  define IUTEST_HAS_BUILTIN_EXPECT     0
#endif

#if !defined(IUTEST_COND_LIKELY)
#  if IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY
#    define IUTEST_COND_LIKELY(cond)    (cond) IUTEST_ATTRIBUTE_LIKELY_
#  elif IUTEST_HAS_BUILTIN_EXPECT
#    define IUTEST_COND_LIKELY(cond)    (__builtin_expect(static_cast<bool>(!!(cond)), 1))
#  else
#    define IUTEST_COND_LIKELY(cond)    (cond)
#  endif
#endif

#if !defined(IUTEST_COND_UNLIKELY)
#  if IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY
#    define IUTEST_COND_UNLIKELY(cond)  (cond) IUTEST_ATTRIBUTE_UNLIKELY_
#  elif IUTEST_HAS_BUILTIN_EXPECT
#    define IUTEST_COND_UNLIKELY(cond)  (__builtin_expect(static_cast<bool>(!!(cond)), 0))
#  else
#    define IUTEST_COND_UNLIKELY(cond)  (cond)
#  endif
#endif

//! MemorySanitizer
#if !defined(IUTEST_HAS_MEMORY_SANITIZER)
#  if defined(__has_feature)
#    if __has_feature(memory_sanitizer)
#      define IUTEST_HAS_MEMORY_SANITIZER   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_MEMORY_SANITIZER)
#  define IUTEST_HAS_MEMORY_SANITIZER       0
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY)
#  if IUTEST_HAS_MEMORY_SANITIZER
#    if   defined(__clang__)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY   __attribute__((no_sanitize_memory))
#    elif defined(__GNUC__) && !defined(COMPILER_ICC)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY   __attribute__((no_sanitize_memory))
#    endif
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY
#endif

//! AddressSanitizer
#if !defined(IUTEST_HAS_ADDRESS_SANITIZER)
#  if defined(__has_feature)
#    if __has_feature(address_sanitizer)
#      define IUTEST_HAS_ADDRESS_SANITIZER  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_ADDRESS_SANITIZER)
#  define IUTEST_HAS_ADDRESS_SANITIZER      0
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS)
#  if IUTEST_HAS_ADDRESS_SANITIZER
#    if   defined(__clang__)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS  __attribute__((no_sanitize_address))
#    elif defined(__GNUC__) && !defined(COMPILER_ICC)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS  __attribute__((no_sanitize_address))
#    endif
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS
#endif

//! ThreadSanitizer
#if !defined(IUTEST_HAS_THREAD_SANITIZER)
#  if defined(__has_feature)
#    if __has_feature(thread_sanitizer)
#      define IUTEST_HAS_THREAD_SANITIZER   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_THREAD_SANITIZER)
#  define IUTEST_HAS_THREAD_SANITIZER       0
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD)
#  if IUTEST_HAS_THREAD_SANITIZER
#    if   defined(__clang__)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD   __attribute__((no_sanitize_thread))
#    elif defined(__GNUC__) && !defined(COMPILER_ICC)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD   __attribute__((no_sanitize_thread))
#    endif
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_ALL)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_ALL \
    IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY \
    IUTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS \
    IUTEST_ATTRIBUTE_NO_SANITIZE_THREAD
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_ALL)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_ALL
#endif

// workaround
/**
 * @private
 * @{
*/

#if defined(_MSC_VER)
// https://stackoverflow.com/questions/14487241/avoiding-an-inheritance-by-dominance-warning-for-a-mocked-stdfstream-class
#  define IUTEST_WORKAROUND_MSC_STLSTREAM_C4250()   \
    void _Add_vtordisp1() {}    \
    void _Add_vtordisp2() {}
#else
#  define IUTEST_WORKAROUND_MSC_STLSTREAM_C4250()
#endif

/**
 * @}
*/

// pragma
#include "iutest_pragma.hpp"

#if defined(_MSC_VER) && _MSC_VER < 1300
#  pragma warning(disable:4786) // ident trunc to '255' chars in debug info
#endif

#endif // INCG_IRIS_IUTEST_COMPILER_HPP_6DDB27E8_E2FF_4754_80B0_F500025820C4_
