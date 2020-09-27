﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_stdlib.hpp
 * @brief       stdlib
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_
#define INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_

//======================================================================
// include
#define __STDC_FORMAT_MACROS    1
#include <inttypes.h>

#if defined(IUTEST_USE_GTEST) && defined(__STRICT_ANSI__)
#  undef __STRICT_ANSI__
#  include <string.h>
#  include <stdlib.h>
#  include <cstdio>
#  define __STRICT_ANSI__
#endif
#if !defined(_MSC_VER)
#  include <stdint.h>
#endif
#include <cstdlib>
#include <cstddef>
#include <limits>

// <version> header
#if defined(__has_include)
#  if __has_include(<version>)
#    define IUTEST_HAS_CXX_HDR_VERSION  1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX_HDR_VERSION)
#  define IUTEST_HAS_CXX_HDR_VERSION    0
#endif

#if IUTEST_HAS_CXX_HDR_VERSION
#include <version>
#endif

//======================================================================
// define
#if   defined(__GLIBCPP__) || defined(__GLIBCXX__)

// libstdc++
#if   defined(__clang__)
#  if __has_include(<experimental/memory_resource>)
#    define IUTEST_LIBSTDCXX_VERSION    60100
#  elif __has_include(<experimental/any>)
#    define IUTEST_LIBSTDCXX_VERSION    50100
#  elif __has_include(<shared_mutex>)
#    define IUTEST_LIBSTDCXX_VERSION    40900
#  elif __has_include(<ext/cmath>)
#    define IUTEST_LIBSTDCXX_VERSION    40800
#  elif   __has_include(<scoped_allocator>)
#    define IUTEST_LIBSTDCXX_VERSION    40700
#  elif __has_include(<typeindex>)
#    define IUTEST_LIBSTDCXX_VERSION    40600
#  elif __has_include(<future>)
#    define IUTEST_LIBSTDCXX_VERSION    40500
#  elif __has_include(<ratio>)
#    define IUTEST_LIBSTDCXX_VERSION    40400
#  elif __has_include(<array>)
#    define IUTEST_LIBSTDCXX_VERSION    40300
#  endif
#elif defined(__GNUC__)
#  define IUTEST_LIBSTDCXX_VERSION      (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#endif

#if IUTEST_HAS_CXX11
#  if IUTEST_LIBSTDCXX_VERSION >= 60100
#    if !defined(IUTEST_HAS_STD_INVOKE) && IUTEST_HAS_CXX1Z
#      define IUTEST_HAS_STD_INVOKE         1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 50100
#    if !defined(IUTEST_HAS_CXX_HDR_CODECVT)
#      define IUTEST_HAS_CXX_HDR_CODECVT    1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 40900
#    if !defined(IUTEST_HAS_CXX_HDR_REGEX)
#      define IUTEST_HAS_CXX_HDR_REGEX      1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 40700
#    if !defined(IUTEST_HAS_STD_EMPLACE)
#      define IUTEST_HAS_STD_EMPLACE        1
#    endif
#    if !defined(IUTEST_HAS_CXX_HDR_CHRONO)
#      define IUTEST_HAS_CXX_HDR_CHRONO     1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 40600
#    if !defined(IUTEST_HAS_STD_BEGIN_END)
#      define IUTEST_HAS_STD_BEGIN_END      1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 40500
#    if !defined(IUTEST_HAS_STD_DECLVAL)
#      define IUTEST_HAS_STD_DECLVAL        1
#    endif
#    if !defined(IUTEST_HAS_CXX_HDR_RANDOM)
#      define IUTEST_HAS_CXX_HDR_RANDOM     1
#    endif
#    if !defined(IUTEST_HAS_CXX_HDR_CSTDINT)
#      define IUTEST_HAS_CXX_HDR_CSTDINT    1
#    endif
#  endif
#  if IUTEST_LIBSTDCXX_VERSION >= 40300
#    if !defined(IUTEST_HAS_CXX_HDR_ARRAY)
#      define IUTEST_HAS_CXX_HDR_ARRAY      1
#    endif
#    if !defined(IUTEST_HAS_STD_TUPLE)
#      define IUTEST_HAS_STD_TUPLE          1
#    endif
#  endif
#  if defined(_GLIBCXX_HAVE_QUICK_EXIT) && defined(_GLIBCXX_HAVE_AT_QUICK_EXIT)
#    if !defined(IUTEST_HAS_STD_QUICK_EXIT)
#      define IUTEST_HAS_STD_QUICK_EXIT     1
#    endif
#  endif
#  if defined(__has_include)
#    if !defined(IUTEST_HAS_CXX_HDR_CUCHAR) && __has_include( <cuchar> )
#      if defined(_GLIBCXX_USE_C11_UCHAR_CXX11) && _GLIBCXX_USE_C11_UCHAR_CXX11
#        define IUTEST_HAS_CXX_HDR_CUCHAR   1
#      endif
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_STD_TUPLE)
#  if (!defined(__CUDACC__) && !defined(__ARMCC_VERSION) && (IUTEST_LIBSTDCXX_VERSION >= 40000))
#    if !defined(IUTEST_HAS_TR1_TUPLE)
#      define IUTEST_HAS_TR1_TUPLE          1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_HDR_CXXABI)
#  if   defined(__has_include)
#    if __has_include( <cxxabi.h> )
#      define IUTEST_HAS_HDR_CXXABI         1
#    endif
#  else
#    define IUTEST_HAS_HDR_CXXABI           1
#  endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
// GCC 8.x requires linking with -lstdc++fs. (iutest not support)
#  if   (__GNUC__ < 9)
#    define IUTEST_HAS_CXX_HDR_FILESYSTEM   0
#  endif
#endif

#elif defined(_LIBCPP_VERSION)

// libc++
#if IUTEST_HAS_CXX11
#  if !defined(IUTEST_HAS_STD_BEGIN_END)
#    define IUTEST_HAS_STD_BEGIN_END      1
#  endif
#  if !defined(IUTEST_HAS_STD_DECLVAL)
#    define IUTEST_HAS_STD_DECLVAL        1
#  endif
#  if !defined(IUTEST_HAS_STD_EMPLACE)
#    define IUTEST_HAS_STD_EMPLACE        1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CHRONO)
#    define IUTEST_HAS_CXX_HDR_CHRONO     1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_REGEX)
#    define IUTEST_HAS_CXX_HDR_REGEX      1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_RANDOM)
#    define IUTEST_HAS_CXX_HDR_RANDOM     1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CODECVT)
#    define IUTEST_HAS_CXX_HDR_CODECVT    1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CSTDINT)
#    define IUTEST_HAS_CXX_HDR_CSTDINT    1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_ARRAY)
#    define IUTEST_HAS_CXX_HDR_ARRAY      1
#  endif
#  if !defined(IUTEST_HAS_STD_QUICK_EXIT) && defined(_LIBCPP_HAS_QUICK_EXIT)
#    define IUTEST_HAS_STD_QUICK_EXIT     1
#  endif
#  if   defined(__has_include)
#    if !defined(IUTEST_HAS_CXX_HDR_CUCHAR) && __has_include( <cuchar> )
#      define IUTEST_HAS_CXX_HDR_CUCHAR   1
#    endif
#    if !defined(IUTEST_HAS_STD_TUPLE) && __has_include( <tuple> )
#      define IUTEST_HAS_STD_TUPLE          1
#    endif
#  endif
#endif

#if _LIBCPP_VERSION < 9000
#  define IUTEST_HAS_CXX_HDR_FILESYSTEM   0
#endif
#if _LIBCPP_VERSION >= 3700
#  if !defined(IUTEST_HAS_STD_INVOKE) && IUTEST_HAS_CXX1Z
#    define IUTEST_HAS_STD_INVOKE         1
#  endif
#endif
#if _LIBCPP_VERSION >= 1001
#  if !defined(IUTEST_HAS_STD_BEGIN_END)
#    define IUTEST_HAS_STD_BEGIN_END      1
#  endif
#endif

#if defined(__has_include)
#  if !defined(IUTEST_HAS_STD_TUPLE) && !defined(IUTEST_HAS_TR1_TUPLE) && __has_include( <tr1/tuple> )
#    define IUTEST_HAS_TR1_TUPLE          1
#  endif
#  if !defined(IUTEST_HAS_HDR_CXXABI) && __has_include( <cxxabi.h> )
#    define IUTEST_HAS_HDR_CXXABI         1
#  endif
#endif

#elif defined(_MSC_VER) && defined(_MSC_FULL_VER)

// Visual C++

#if _MSC_VER >= 1600
#  if !defined(IUTEST_HAS_CXX_HDR_ARRAY)
#    define IUTEST_HAS_CXX_HDR_ARRAY      1
#  endif
#endif

#if _MSC_VER >= 1700
#  if !defined(IUTEST_HAS_STD_BEGIN_END)
#    define IUTEST_HAS_STD_BEGIN_END      1
#  endif
#  if !defined(IUTEST_HAS_STD_DECLVAL)
#    define IUTEST_HAS_STD_DECLVAL        IUTEST_HAS_DECLTYPE
#  endif
#  if !defined(IUTEST_HAS_STD_EMPLACE)
#    define IUTEST_HAS_STD_EMPLACE        1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_REGEX)
#    define IUTEST_HAS_CXX_HDR_REGEX      1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_RANDOM)
#    define IUTEST_HAS_CXX_HDR_RANDOM     1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CODECVT)
#    define IUTEST_HAS_CXX_HDR_CODECVT    1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CSTDINT)
#    define IUTEST_HAS_CXX_HDR_CSTDINT    1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CHRONO) && _MSC_FULL_VER != 190023725
#    define IUTEST_HAS_CXX_HDR_CHRONO   1
#  endif
#endif

#if _MSC_VER >= 1900
#  if !defined(IUTEST_HAS_STD_QUICK_EXIT)
#    define IUTEST_HAS_STD_QUICK_EXIT       1
#  endif
#  if !defined(IUTEST_HAS_CXX_HDR_CUCHAR)
#    define IUTEST_HAS_CXX_HDR_CUCHAR       1
#  endif
#endif

#if _MSC_VER >= 1916
#  if !defined(IUTEST_HAS_CXX_HDR_CHARCONV) && IUTEST_HAS_CXX17
#    define IUTEST_HAS_CXX_HDR_CHARCONV     1
#  endif
#endif

// tuple
#if (_MSC_VER > 1700) || (_MSC_VER == 1700 && _VARIADIC_MAX >= 9)
#  if !defined(IUTEST_HAS_STD_TUPLE)
#    define IUTEST_HAS_STD_TUPLE          1
#  endif
#elif (_MSC_VER >= 1500) && (_MSC_VER < 1700) && (_MSC_FULL_VER > 150021022)
#  if !defined(IUTEST_HAS_TR1_TUPLE)
#    define IUTEST_HAS_TR1_TUPLE          1
#  endif
#endif

#elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

// stlport

#endif

#if IUTEST_HAS_CXX1Z

// c++1z feature

#if defined(__has_include)

#if !defined(IUTEST_HAS_CXX_HDR_ANY)
#  if __has_include(<any>)
#    define IUTEST_HAS_CXX_HDR_ANY          1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX_HDR_CHARCONV)
#  if __has_include(<charconv>)
#    define IUTEST_HAS_CXX_HDR_CHARCONV     1
#  endif
#endif

// apple(xcode) clang
#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#  if __MAC_OS_X_VERSION_MIN_REQUIRED < 101500
#    define IUTEST_HAS_CXX_HDR_FILESYSTEM   0
#  endif
#endif

#if !defined(IUTEST_HAS_CXX_HDR_FILESYSTEM)
#  if __has_include(<filesystem>)
#    define IUTEST_HAS_CXX_HDR_FILESYSTEM   1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX_HDR_OPTIONAL)
#  if __has_include(<optional>)
#    define IUTEST_HAS_CXX_HDR_OPTIONAL     1
#  endif
#endif

#if !defined(IUTEST_HAS_CXX_HDR_STRING_VIEW)
#  if __has_include(<string_view>)
#    define IUTEST_HAS_CXX_HDR_STRING_VIEW  1
#  endif
#endif

#endif

#endif

#if IUTEST_HAS_CXX17

// c++17 feature

#if !defined(IUTEST_HAS_CXX_HDR_VARIANT)
#  if IUTEST_HAS_VARIADIC_TEMPLATES && defined(__has_include)
#    if   defined(__clang__) && (__clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ < 6))
#      define IUTEST_HAS_CXX_HDR_VARIANT    0   // clang 3.5 + variant is not worked
#    elif __has_include(<variant>)
#      define IUTEST_HAS_CXX_HDR_VARIANT    1
#    endif
#  endif
#endif

#if defined(IUTEST_HAS_CXX_HDR_CODECVT) && IUTEST_HAS_CXX_HDR_CODECVT
// IUTEST_PRAGMA_MESSAGE("iutest use codecvt, but codecvt was deprecated. If you do not want to use this, define IUTEST_HAS_CXX_HDR_CODECVT 0")
#endif

#endif

#if defined(__has_include)
#  if defined(IUTEST_HAS_CXX_HDR_CODECVT) && IUTEST_HAS_CXX_HDR_CODECVT
#    if !__has_include( <codecvt> )
#      undef IUTEST_HAS_CXX_HDR_CODECVT
#    endif
#  endif
#endif

// defaults for include
//! has any header
#if !defined(IUTEST_HAS_CXX_HDR_ANY)
#  define IUTEST_HAS_CXX_HDR_ANY            0
#endif
//! has array header
#if !defined(IUTEST_HAS_CXX_HDR_ARRAY)
#  define IUTEST_HAS_CXX_HDR_ARRAY          0
#endif
//! has charconv header
#if !defined(IUTEST_HAS_CXX_HDR_CHARCONV)
#  define IUTEST_HAS_CXX_HDR_CHARCONV       0
#endif
//! has chrono header
#if !defined(IUTEST_HAS_CXX_HDR_CHRONO)
#  define IUTEST_HAS_CXX_HDR_CHRONO         0
#endif
/**
 * @brief       has codecvt header
 * @note        P0618R0 Deprecating <codecvt>: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0618r0.html
 * @deprecated
*/
#if !defined(IUTEST_HAS_CXX_HDR_CODECVT)
#  define IUTEST_HAS_CXX_HDR_CODECVT        0
#endif
//! has cstdint header
#if !defined(IUTEST_HAS_CXX_HDR_CSTDINT)
#  define IUTEST_HAS_CXX_HDR_CSTDINT        0
#endif
//! has cuchar
#if !defined(IUTEST_HAS_CXX_HDR_CUCHAR)
#  define IUTEST_HAS_CXX_HDR_CUCHAR         0
#endif
//! has filesystem
#if !defined(IUTEST_HAS_CXX_HDR_FILESYSTEM)
#  define IUTEST_HAS_CXX_HDR_FILESYSTEM     0
#endif
//! has optional header
#if !defined(IUTEST_HAS_CXX_HDR_OPTIONAL)
#  define IUTEST_HAS_CXX_HDR_OPTIONAL       0
#endif
//! has random header
#if !defined(IUTEST_HAS_CXX_HDR_RANDOM)
#  define IUTEST_HAS_CXX_HDR_RANDOM         0
#endif
//! has regex header
#if !defined(IUTEST_HAS_CXX_HDR_REGEX)
#  define IUTEST_HAS_CXX_HDR_REGEX          0
#endif
//! has string_view header
#if !defined(IUTEST_HAS_CXX_HDR_STRING_VIEW)
#  define IUTEST_HAS_CXX_HDR_STRING_VIEW    0
#endif
//! has variant header
#if !defined(IUTEST_HAS_CXX_HDR_VARIANT)
#  define IUTEST_HAS_CXX_HDR_VARIANT        0
#endif
//! has cxxabi header
#if !defined(IUTEST_HAS_HDR_CXXABI)
#  define IUTEST_HAS_HDR_CXXABI             0
#endif

//======================================================================
// include
#include <iterator>

#if IUTEST_HAS_CXX_HDR_ANY
#  include <any>
#endif
#if IUTEST_HAS_CXX_HDR_CSTDINT
#  include <cstdint>
#endif
#if IUTEST_HAS_CXX_HDR_FILESYSTEM
#  include <filesystem>
#endif
#if IUTEST_HAS_CXX_HDR_OPTIONAL
#  include <optional>
#endif
#if IUTEST_HAS_CXX_HDR_VARIANT
#  include <variant>
#endif
#if IUTEST_HAS_CXX_HDR_CHARCONV
#  include <charconv>
#endif

//======================================================================
// define
#if !defined(IUTEST_HAS_STD_FILESYSTEM)
#  if defined(ANDROID) || defined(__ANDROID__)
#    define IUTEST_HAS_STD_FILESYSTEM       0
#  elif IUTEST_HAS_CXX_HDR_FILESYSTEM && defined(__cpp_lib_filesystem) && __cpp_lib_filesystem >= 201703
#    if !defined(__cpp_lib_experimental_filesystem)
#      define IUTEST_HAS_STD_FILESYSTEM     1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_STD_TO_CHARS)
#  if defined(__cpp_lib_to_chars) && __cpp_lib_to_chars >= 201611
#    define IUTEST_HAS_STD_TO_CHARS         1
#  endif
#endif

// defaults for feature

//! has ::std::begin,::std::end
#if !defined(IUTEST_HAS_STD_BEGIN_END)
#  define IUTEST_HAS_STD_BEGIN_END      0
#endif
//! has ::std::declval
#if !defined(IUTEST_HAS_STD_DECLVAL)
#  define IUTEST_HAS_STD_DECLVAL        0
#endif
//! has emplace
#if !defined(IUTEST_HAS_STD_EMPLACE)
#  define IUTEST_HAS_STD_EMPLACE        0
#endif
//! has filesystem
#if !defined(IUTEST_HAS_STD_FILESYSTEM)
#  define IUTEST_HAS_STD_FILESYSTEM     0
#endif
//! has std::invoke
#if !defined(IUTEST_HAS_STD_INVOKE)
#  define IUTEST_HAS_STD_INVOKE         0
#endif
//! has quick_exit
#if !defined(IUTEST_HAS_STD_QUICK_EXIT)
#  define IUTEST_HAS_STD_QUICK_EXIT     0
#endif
//! has to_chars
#if !defined(IUTEST_HAS_STD_TO_CHARS)
#  define IUTEST_HAS_STD_TO_CHARS       0
#endif

//! use external include tr1::tuple
#if !defined(IUTEST_USE_EXTERNAL_TR1_TUPLE)
#  define IUTEST_USE_EXTERNAL_TR1_TUPLE 0
#endif
//! use external include ::std::tuple
#ifndef IUTEST_USE_EXTERNAL_STD_TUPLE
#  define IUTEST_USE_EXTERNAL_STD_TUPLE 0
#endif
//! has ::std::tuple
#if !defined(IUTEST_HAS_STD_TUPLE)
#  define IUTEST_HAS_STD_TUPLE          0
#endif
//! has ::std::tr1::tuple
#if !defined(IUTEST_HAS_TR1_TUPLE)
#  define IUTEST_HAS_TR1_TUPLE          0
#endif
//! has tuple
#if IUTEST_HAS_STD_TUPLE || IUTEST_HAS_TR1_TUPLE || IUTEST_USE_EXTERNAL_TR1_TUPLE || IUTEST_USE_EXTERNAL_STD_TUPLE
#  if !defined(IUTEST_HAS_TUPLE)
#    define IUTEST_HAS_TUPLE            1
#  endif
#else
#  if defined(IUTEST_HAS_TUPLE)
#    undef IUTEST_HAS_TUPLE
#  endif
#  define IUTEST_HAS_TUPLE              0
#endif
#if !defined(IUTEST_HAS_VARIADIC_TUPLES) && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE && IUTEST_HAS_STD_TUPLE
#  if defined(__clang__)
#    if (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ > 7))
#      define IUTEST_HAS_VARIADIC_TUPLES    1
#    endif
#  else
#    define IUTEST_HAS_VARIADIC_TUPLES      1
#  endif
#endif
#if !defined(IUTEST_HAS_VARIADIC_TUPLES)
#  define IUTEST_HAS_VARIADIC_TUPLES        0
#endif


//======================================================================
// declare

//! ::std::sto* が使用可能かどうか
#if !defined(IUTEST_HAS_STD_STR_TO_VALUE)
#  if IUTEST_HAS_CXX11
#    if defined(IUTEST_OS_WINDOWS_MINGW)
#      if defined(__MINGW64__) && (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)))
#        define IUTEST_HAS_STD_STR_TO_VALUE 1
#      endif
#    else
#      define IUTEST_HAS_STD_STR_TO_VALUE   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_STD_STR_TO_VALUE)
#  define IUTEST_HAS_STD_STR_TO_VALUE   0
#endif

//! using begin,end
#if !defined(IUTEST_USING_BEGIN_END)
#  if IUTEST_HAS_STD_BEGIN_END
#    define IUTEST_USING_BEGIN_END()    \
    using ::std::begin; using ::std::end
#  else
#    define IUTEST_USING_BEGIN_END()    \
    using ::iutest::detail::cxx::begin; using ::iutest::detail::cxx::end
#  endif
#endif

namespace iutest {
namespace detail {
namespace cxx
{

#if IUTEST_HAS_STD_BEGIN_END

using ::std::begin;
using ::std::end;

#else

template<typename T> typename T::iterator begin(T& x) { return x.begin(); }
template<typename T> typename T::iterator end  (T& x) { return x.end(); }

template<typename T> typename T::const_iterator begin(const T& x) { return x.begin(); }
template<typename T> typename T::const_iterator end  (const T& x) { return x.end(); }

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
template<typename T, size_t SIZE> T* begin(T (&x)[SIZE]) { return &x[0]; }
template<typename T, size_t SIZE> T* end  (T (&x)[SIZE]) { return begin(x) + SIZE; }

template<typename T, size_t SIZE> const T* begin(const T (&x)[SIZE]) { return &x[0]; }
template<typename T, size_t SIZE> const T* end  (const T (&x)[SIZE]) { return begin(x) + SIZE; }
#endif

#endif

}   // end of namespace cxx
}   // end of namespace detail
}   // end of namespace iutest

#if IUTEST_HAS_TUPLE
#if !IUTEST_USE_EXTERNAL_STD_TUPLE && !IUTEST_USE_EXTERNAL_TR1_TUPLE
#  if   IUTEST_HAS_STD_TUPLE
#    include <tuple>
#  elif IUTEST_HAS_TR1_TUPLE
#    if (defined(__GNUC__) && (__GNUC__ >= 4))
#      include <tr1/tuple>
#    else
#      include <tuple>
#    endif
#  endif
#endif

namespace iutest {
namespace tuples
{

#if   IUTEST_HAS_STD_TUPLE
namespace alias = ::std;
#elif IUTEST_HAS_TR1_TUPLE
namespace alias = ::std::tr1;
#endif

using alias::tuple;
using alias::tuple_element;
using alias::make_tuple;
using alias::get;

template<typename T>struct tuple_size : public alias::tuple_size<T> {};
template<typename T>struct tuple_size<const T> : public alias::tuple_size<T> {};
template<typename T>struct tuple_size<volatile T> : public alias::tuple_size<T>{};
template<typename T>struct tuple_size<const volatile T> : public alias::tuple_size<T>{};

namespace detail
{

template<typename T, typename F, int Begin>
struct tuple_foreach_impl
{
    template<int N, int I>
    struct impl
    {
        static void do_something(T& t, F fn)
        {
            fn(I, get<I>(t));
            impl<N, I + 1>::do_something(t, fn);
        }
    };
    template<int N>
    struct impl<N, N>
    {
        static void do_something(T&, F) {}
    };

    static void do_something(T& t, F fn)
    {
        impl<tuple_size<T>::value, Begin>::do_something(t, fn);
    }
};

template<typename T, typename U>
struct tuple_cast_copy_impl
{
    template<int N, int I>
    struct impl
    {
        static void copy(T& dst, const U& src)
        {
            get<I>(dst) = static_cast<typename tuple_element<I, T>::type>(get<I>(src));
            impl<N, I + 1>::copy(dst, src);
        }
    };
    template<int N>
    struct impl<N, N>
    {
        static void copy(T&, const U&) {}
    };

    static void copy(T& dst, const U& src)
    {
        impl<tuple_size<T>::value, 0>::copy(dst, src);
    }
};

}   // end of namespace detail

template<int I, typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, F& fn)
{
    detail::tuple_foreach_impl<tuple_t, F&, I>::do_something(t, fn);
}
template<typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, F& fn)
{
    tuple_foreach<0>(t, fn);
}
template<int I, typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, const F& fn)
{
    detail::tuple_foreach_impl<tuple_t, const F&, I>::do_something(t, fn);
}
template<typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, const F& fn)
{
    tuple_foreach<0>(t, fn);
}
template<typename T, typename U>
void tuple_cast_copy(T& dst, const U& src)
{
    detail::tuple_cast_copy_impl<T, U>::copy(dst, src);
}

}   // end of namespace tuples

using tuples::tuple;
using tuples::tuple_size;
using tuples::tuple_element;
using tuples::tuple_foreach;
using tuples::make_tuple;
using tuples::get;

}   // end of namespace iutest

#endif

//! has sys/time.h header
#if !defined(IUTEST_HAS_HDR_SYSTIME)
#  if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MINGW) && !defined(IUTEST_OS_WINDOWS_WINE)
#    define IUTEST_HAS_HDR_SYSTIME      0
#  endif
#endif

#if !defined(IUTEST_HAS_HDR_SYSTIME)
#  define IUTEST_HAS_HDR_SYSTIME        1
#endif

// socklen_t
#if defined(IUTEST_OS_WINDOWS_WINE)
#  define __socklen_t_defined
#endif

//! ::std::stringstream が使用可能かどうか
#if !defined(IUTEST_HAS_STRINGSTREAM)
#  if !defined(_STLP_NO_IOSTREAMS)
#    define IUTEST_HAS_STRINGSTREAM 1
#  endif
#endif

#if !defined(IUTEST_HAS_STRINGSTREAM)
#  define IUTEST_HAS_STRINGSTREAM   0
#endif


/**
 * @brief   ::std::strstream が使用可能かどうか
 * @note    IUTEST_HAS_STRINGSTREAM が優先されます
 * @deprecated
*/
#if !defined(IUTEST_HAS_STRSTREAM)
#  define IUTEST_HAS_STRSTREAM      0
#endif

//! iomanip が使用可能かどうか
#if !defined(IUTEST_HAS_IOMANIP)
#  if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
#    define IUTEST_HAS_IOMANIP      1
#  endif
#endif

#if !defined(IUTEST_HAS_IOMANIP)
#  define IUTEST_HAS_IOMANIP        0
#endif


//! _set_invalid_parameter_handler が使用可能かどうか
#if !defined(IUTEST_HAS_INVALID_PARAMETER_HANDLER)
#  if IUTEST_HAS_EXCEPTIONS && (defined(_MSC_VER) && (_MSC_VER >= 1400)) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_INVALID_PARAMETER_HANDLER    1
#  endif
#endif

#if !defined(IUTEST_HAS_INVALID_PARAMETER_HANDLER)
#  define IUTEST_HAS_INVALID_PARAMETER_HANDLER      0
#endif

//! size_t format macros
#if !defined(IUPRzu)
#  if defined(_MSC_VER) && (_MSC_VER < 1900)
#    define IUPRzu  "Iu"
#  elif defined(IUTEST_OS_WINDOWS_MINGW)
#    if !defined(__STRICT_ANSI__)
#      if defined(__MINGW64__)
#        define IUPRzu  PRIu64
#      elif defined(__MINGW32__)
#        define IUPRzu  PRIu32
#      endif
#    endif
#  endif
#endif

#if !defined(IUPRzu)
#  define IUPRzu  "zu"
#endif

#if !defined(iu_va_copy)
#  if defined(va_copy)
#    define iu_va_copy              va_copy
#  elif defined(__GNUC__) || defined(__clang__)
#    define iu_va_copy(dest, src)   __builtin_va_copy(dest, src)
#  else
#    define iu_va_copy(dest, src)   (dest = src)
#  endif
#endif

namespace iutest
{

namespace stl
{

// #if IUTEST_HAS_CXX_HDR_OPTIONAL
// #else
// #endif

#if IUTEST_HAS_EXCEPTIONS
/**
 * @brief   any_cast の失敗例外
*/
class bad_optional_access : public ::std::exception {};
#endif

class nullpot_t {};

template<typename T>
class optional
{
public:
    typedef T value_type;
public:
    optional() IUTEST_CXX_NOEXCEPT_SPEC : m_init(false) {}
    explicit optional(nullpot_t) IUTEST_CXX_NOEXCEPT_SPEC : m_init(false) {}
    explicit optional(const T& rhs) : m_init(true), m_value(rhs) {}
    template<typename U>
    explicit optional(const U& rhs) : m_init(true), m_value(T(rhs)) {}
    optional(const optional& rhs) : m_init(rhs.m_init), m_value(rhs.value) {}

public:
    optional& operator = (const T& rhs) { m_init = true; m_value = rhs; }
    operator bool () const { return has_value(); }
    const T& operator * () const { return value(); }
    T& operator * () { return value(); }
    const T* operator -> () const { return ptr(); }
    T* operator -> () { return ptr(); }

public:
    bool has_value() const { return m_init; }
    const T* ptr() const { return &m_value; }
    T* ptr() { return &m_value; }
    const T& value() const
    {
#if IUTEST_HAS_EXCEPTIONS
        if( !has_value() ) {
            throw bad_optional_access();
        }
#endif
        return m_value;
    }
    T& value()
    {
#if IUTEST_HAS_EXCEPTIONS
        if( !has_value() ) {
            throw bad_optional_access();
        }
#endif
        return m_value;
    }
    template<typename U>
    T value_or(const U& v) const
    {
        if( !has_value() ) {
            return v;
        }
        return m_value;
    }

private:
    bool m_init;
    T m_value;
};

}   // end of namespace stl

namespace detail
{

//======================================================================
// struct
/**
 * @brief   type_least_t
*/
template<int SIZE>
struct type_least_t {};

/** type_least_t<1> */
template<>
struct type_least_t<1>
{
#if defined(INT_LEAST8_MIN)
    typedef int_least8_t        Int;
    typedef uint_least8_t       UInt;
#else
    typedef char                Int;
    typedef unsigned char       UInt;
#endif
};

/** type_least_t<2> */
template<>
struct type_least_t<2>
{
#if defined(INT_LEAST16_MIN)
    typedef int_least16_t       Int;
    typedef uint_least16_t      UInt;
#else
    typedef short               Int;
    typedef unsigned short      UInt;
#endif
};

/** type_least_t<4> */
template<>
struct type_least_t<4>
{
#if defined(INT_LEAST32_MIN)
    typedef int_least32_t       Int;
    typedef uint_least32_t      UInt;
#else
    typedef int                 Int;
    typedef unsigned int        UInt;
#endif
};

/** type_least_t<8> */
template<>
struct type_least_t<8>
{
#if defined(INT_LEAST64_MIN)
    typedef int_least64_t       Int;
    typedef uint_least64_t      UInt;
#else
#if defined(_MSC_VER)
    typedef __int64             Int;
    typedef unsigned __int64    UInt;
#else
    typedef long long           Int;
    typedef unsigned long long  UInt;
#endif
#endif
};

/**
 * @brief   type_fit_t
*/
template<size_t SIZE>
struct type_fit_t {};

/** type_fit_t<1> */
template<>
struct type_fit_t<1>
{
#if defined(INT8_MIN)
    typedef int8_t              Int;
    typedef uint8_t             UInt;
#else
    typedef char                Int;
    typedef unsigned char       UInt;
#endif
};

/** type_fit_t<2> */
template<>
struct type_fit_t<2>
{
#if defined(INT16_MIN)
    typedef int16_t             Int;
    typedef uint16_t            UInt;
#else
    typedef short               Int;
    typedef unsigned short      UInt;
#endif
};

/** type_fit_t<4> */
template<>
struct type_fit_t<4>
{
#if defined(INT32_MIN)
    typedef int32_t             Int;
    typedef uint32_t            UInt;
#else
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
private:
    template<typename T, typename F, bool b>
    struct impl { typedef T type; };
    template<typename T, typename F>
    struct impl<T, F, false> { typedef F type; };

public:
    typedef impl<long, int
        , sizeof(int) != 4 && sizeof(long) == 4>::type Int;
    typedef impl<unsigned long, unsigned int
        , sizeof(int) != 4 && sizeof(long) == 4>::type UInt;
#else
    typedef int                 Int;
    typedef unsigned int        UInt;
#endif
#endif
};

/** type_fit_t<8> */
template<>
struct type_fit_t<8>
{
#if defined(INT64_MIN)
    typedef int64_t             Int;
    typedef uint64_t            UInt;
#else
#if defined(_MSC_VER)
    typedef __int64             Int;
    typedef unsigned __int64    UInt;
#else
    typedef long long           Int;
    typedef unsigned long long  UInt;
#endif
#endif
};

/** type_fit_t<8> */
template<>
struct type_fit_t<16>
{
#if IUTEST_HAS_INT128
#if defined(_MSC_VER)
    typedef __int128            Int;
    typedef unsigned __int128   UInt;
#else
    typedef __int128_t  Int;
    typedef __uint128_t UInt;
#endif
#endif
};

//======================================================================
// function
/**
 * @internal
 * @brief   mbtowc
*/
inline int iu_mbtowc(wchar_t* dst, const char* src, size_t size)
{
#if defined(IUTEST_OS_LINUX_ANDROID) || defined(IUTEST_OS_WINDOWS_MOBILE)
    // unimplimented
    IUTEST_UNUSED_VAR(dst);
    IUTEST_UNUSED_VAR(src);
    IUTEST_UNUSED_VAR(size);
    return 0;
#else
    return mbtowc(dst, src, size);
#endif
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_
