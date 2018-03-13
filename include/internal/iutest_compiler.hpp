﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_compiler.hpp
 * @brief       iris unit test compiler 依存の吸収 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_COMPILER_HPP_6DDB27E8_E2FF_4754_80B0_F500025820C4_
#define INCG_IRIS_IUTEST_COMPILER_HPP_6DDB27E8_E2FF_4754_80B0_F500025820C4_

//======================================================================
// include

//======================================================================
// define
#if defined(_MSC_VER) && _MSC_VER == 1700
#  ifndef _VARIADIC_MAX
#    define _VARIADIC_MAX   10
#  endif
#endif

// os
#if   defined(__CYGWIN__)
#  define IUTEST_OS_CYGWIN              1
#  define IUTEST_PLATFORM               "CYGWIN"
#elif defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(WINAPI_FAMILY)
#  define IUTEST_OS_WINDOWS             1
#  if !defined(WIN32_LEAN_AND_MEAN)
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#  if defined(_WIN32_WCE)
#    define IUTEST_OS_WINDOWS_MOBILE    1
#    define IUTEST_PLATFORM             "Windows CE"
#  elif defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#    define IUTEST_OS_WINDOWS_MINGW     1
#  elif defined(__WINE__)
#    define IUTEST_OS_WINDOWS_WINE      1
#    define IUTEST_PLATFORM             "WINE"
#  elif defined(__CUDACC__)
#    define IUTEST_OS_WINDOWS_CUDA      1
#  elif defined(WINAPI_FAMILY)
#    if defined(WINAPI_FAMILY_PHONE_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#      define IUTEST_OS_WINDOWS_PHONE   1
#      define IUTEST_PLATFORM           "Windows Phone"
#    elif defined(WINAPI_FAMILY_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#      define IUTEST_OS_WINDOWS_RT      1
#      define IUTEST_PLATFORM           "Windows RT"
#    else
#      define IUTEST_OS_WINDOWS_DESKTOP 1
#    endif
#  else
#    define IUTEST_OS_WINDOWS_DESKTOP   1
#  endif
#  if !defined(IUTEST_PLATFORM)
#    define IUTEST_PLATFORM             "Windows"
#  endif
#elif defined(__APPLE__)
#  include "TargetConditionals.h"
#  if TARGET_OS_IPHONE
#    define IUTEST_OS_IOS               1
#    define IUTEST_PLATFORM             "iOS"
#  else
#    define IUTEST_OS_MAC               1
#    define IUTEST_PLATFORM             "Mac OS"
#  endif
#elif defined(__FreeBSD__)
#  define IUTEST_OS_FREEBSD             1
#  define IUTEST_PLATFORM               "FreeBSD"
#elif defined(sun) || defined(__sun)
#  define IUTEST_OS_SOLARIS             1
#  define IUTEST_PLATFORM               "Solaris"
#elif defined(__linux__)
#  define IUTEST_OS_LINUX               1
#  if defined(ANDROID) || defined(__ANDROID__)
#    define IUTEST_OS_LINUX_ANDROID     1
#    define IUTEST_PLATFORM             "Android"
#  else
#    define IUTEST_PLATFORM             "LINUX"
#  endif
#elif defined(__native_client__)
#  define IUTEST_OS_NACL                1   //!< @deprecated native client to eol
#  define IUTEST_PLATFORM               "Google Native Client"
#elif defined(__AVR32__) || defined(__avr32__)
#  define IUTEST_OS_AVR32               1
#  define IUTEST_PLATFORM               "AVR32"
#elif defined(__arm__)
#  define IUTEST_OS_ARM                 1
#  define IUTEST_PLATFORM               "ARM"
#endif

#if defined(IUTEST_OS_LINUX_ANDROID)
#  include <android/api-level.h>
#endif

// c++17

//! is c++17 compiler
#if !defined(IUTEST_HAS_CXX17)
#  if (defined(__cplusplus) && __cplusplus >= 201406L)
#    define IUTEST_HAS_CXX17        1
#  elif defined(_MSVC_LANG) && _MSVC_LANG > 201402
#    define IUTEST_HAS_CXX17        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX17)
#  define IUTEST_HAS_CXX17          0
#endif

//! inline variable
#if !defined(IUTEST_HAS_INLINE_VARIABLE)
#if defined(__clang__)
#  if (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 9)) && IUTEST_HAS_CXX17
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

// c++11

//! is c++11 compiler
#if !defined(IUTEST_HAS_CXX11)
#  if (defined(__cplusplus) && __cplusplus >= 201103L) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_CXX11        1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX11)
#  define IUTEST_HAS_CXX11          0
#endif

//! has nullptr
#if !defined(IUTEST_HAS_NULLPTR)
#  if   defined(_NATIVE_NULLPTR_SUPPORTED)
#    define IUTEST_HAS_NULLPTR      1
#  elif defined(__clang__)
#    if __has_feature(cxx_nullptr)
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
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER > 1200
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_AUTO   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_AUTO   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_DECLTYPE   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600
#      define IUTEST_HAS_STATIC_ASSERT  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER > 1100
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900 || _MSC_FULL_VER == 180021114
#      define IUTEST_HAS_CONSTEXPR  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1700)
#      define IUTEST_HAS_RVALUE_REFS    1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  elif defined(_MSC_VER)
#    if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180020827)
#      define IUTEST_HAS_DELETED_FUNCTIONS  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
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

//! has default function
#if !defined(IUTEST_HAS_DEFAULT_FUNCTIONS)
#  if   defined(__clang__)
#    if __has_feature(cxx_defaulted_functions)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(__GNUC__)
     // private destractor = default is not works in gcc 4.5 - 4.6
#    if   (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ == 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(_MSC_VER)
#    if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180020827)
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_DEFAULT_FUNCTIONS  1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_DEFAULT_FUNCTIONS)
#  define IUTEST_HAS_DEFAULT_FUNCTIONS      0
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
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
#      define IUTEST_HAS_INITIALIZER_LIST   1
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
#  elif defined(__GNUC__)
     // http://gcc.gnu.org/bugzilla/show_bug.cgi?id=35722
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
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER > 1200
#      define IUTEST_HAS_VARIADIC_TEMPLATES 1
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
#  elif defined(__GNUC__)
#    if defined(__VARIADIC_TEMPLATES) || ( ((__GNUC__ > 4) \
                || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) \
                || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7) && (__GNUC_PATCHLEVEL__ >= 1))) \
                && defined(__GXX_EXPERIMENTAL_CXX0X__) )
#      define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES    1
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES  IUTEST_HAS_VARIADIC_TEMPLATES
#  elif defined(__INTEL_COMPILER)
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900
#      define IUTEST_HAS_CHAR16_T   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900
#      define IUTEST_HAS_CHAR32_T   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1200
#      define IUTEST_HAS_LAMBDA     1
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1800) || (_MSC_FULL_VER == 170051025)
#      define IUTEST_HAS_EXPLICIT_CONVERSION    1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1300
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1700
#      define IUTEST_HAS_OVERRIDE_AND_FINAL 1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  elif defined(_MSC_VER)
     // https://connect.microsoft.com/VisualStudio/feedback/details/809079/torino-compile-error-template-noexcept
#    if _MSC_FULL_VER >= 190022816
#      define IUTEST_HAS_NOEXCEPT   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  else
#    define IUTEST_CXX_NOTHROW  throw()
#  endif
#endif

//! has extern template
#if !defined(IUTEST_HAS_EXTERN_TEMPLATE)
#  if defined(_MSC_VER) && _MSC_VER >= 1400
#    define IUTEST_HAS_EXTERN_TEMPLATE      1
#  elif defined(__GNUC__) || defined(__clang__)
#    define IUTEST_HAS_EXTERN_TEMPLATE      1
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER > 1100
#      define IUTEST_HAS_EXTERN_TEMPLATE    1
#    endif
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
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1700
#      define IUTEST_HAS_STRONG_ENUMS   1
#    endif
#  elif defined(__INTEL_COMPILER)
#    if __INTEL_COMPILER >= 1400
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
#  if   defined(_MSC_VER) || defined(__BORLANDC__)
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
#      define IUTEST_HAS_SEH    1
#    endif
#  elif defined(__BORLANDC__)
#    define IUTEST_HAS_SEH      1
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

//! has Two pahse name lookup
#if !defined(IUTEST_NO_TWO_PHASE_NAME_LOOKUP)
#  if defined(_MSC_VER)
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
#    if (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 5) ) && IUTEST_HAS_MS_EXTENSIONS
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

#if defined(IUTEST_MODULE_EXPORT)
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

//! has deprecated attribute
#if !defined(IUTEST_HAS_ATTRIBUTE_DEPRECATED)
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(deprecated) >= 201309
#      define IUTEST_HAS_ATTRIBUTE_DEPRECATED   1
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_ATTRIBUTE_DEPRECATED   1
#    endif
#  elif   defined(__clang__)
#    if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4)
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
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY   __attribute__((no_sanitize("memory")))
#    elif defined(__GNUC__) && !defined(COMPILER_ICC)
#      define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY   __attribute__((no_sanitize("memory")))
#    endif
#  endif
#endif

#if !defined(IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY)
#  define IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY
#endif


// workaround
/**
 * @private
 * @{
*/

#if defined(_MSC_VER)
// http://stackoverflow.com/questions/14487241/avoiding-an-inheritance-by-dominance-warning-for-a-mocked-stdfstream-class
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
