//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_compiler.h
 * @brief		iris unit test compiler 依存の吸収 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_compiler_H_6DDB27E8_E2FF_4754_80B0_F500025820C4_
#define INCG_IRIS_iutest_compiler_H_6DDB27E8_E2FF_4754_80B0_F500025820C4_

//======================================================================
// include

//======================================================================
// define
#if defined(_MSC_VER) && _MSC_VER == 1700
#  ifndef _VARIADIC_MAX
#    define _VARIADIC_MAX	10
#  endif
#endif

// os
#if		defined(__CYGWIN__)
#  define IUTEST_OS_CYGWIN				1
#  include <sys/time.h>
#  define IUTEST_HAS_GETTIMEOFDAY		1
#elif	defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#  define IUTEST_OS_WINDOWS				1
#  include <windows.h>
#  if	defined(_WIN32_WCE)
#    define IUTEST_OS_WINDOWS_MOBILE	1
#  elif	defined(__MINGW__) || defined(__MINGW32__)
#    define IUTEST_OS_WINDOWS_MINGW		1
#  else
#    define IUTEST_OS_WINDOWS_DESKTOP	1
#  endif
#elif	defined(__APPLE__)
#  define IUTEST_OS_MAC					1
#elif	defined(__linux__)
#  define IUTEST_OS_LINUX				1
#  ifdef ANDROID
#    define IUTEST_OS_LINUX_ANDROID		1
#  endif
#elif	defined(__native_client__)
#  define IUTEST_OS_NACL				1
#endif

#if	!defined(IUTEST_HAS_CLOCK) && defined(CLOCKS_PER_SEC)
#  define IUTEST_HAS_CLOCK			1
#endif

// c++11
#if !defined(IUTEST_HAS_NULLPTR)
#  if	defined(__clang__)
#    if __has_feature(cxx_nullptr)
#      define IUTEST_HAS_NULLPTR	1
#    endif
#  elif	defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_NULLPTR	1
#    endif
#  elif	defined(_MSC_VER)
#    if _MSC_VER > 1500
#      define IUTEST_HAS_NULLPTR	1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_NULLPTR)
#  define IUTEST_HAS_NULLPTR		0
#endif

// constexpr
#if !defined(IUTEST_HAS_CONSTEXPR)
#  if	defined(__clang__)
#    if !__has_feature(cxx_constexpr)
#      define IUTEST_HAS_CONSTEXPR	0
#    endif
#  elif	defined(__GNUC__)
#    if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CONSTEXPR	0
#    endif
#  elif	defined(_MSC_VER)
#    define IUTEST_HAS_CONSTEXPR	0
#  elif	defined(__MWERKS__)
#    define IUTEST_HAS_CONSTEXPR	0
#  else
#    define IUTEST_HAS_CONSTEXPR	0
#  endif
#endif

#ifndef IUTEST_HAS_CONSTEXPR
#  define IUTEST_HAS_CONSTEXPR		1
#endif

#if IUTEST_HAS_CONSTEXPR
#  define IUTEST_CONSTEXPR			constexpr
#  define IUTEST_CONSTEXPR_OR_CONST	constexpr
#else
#  define IUTEST_NO_CONSTEXPR
#  define IUTEST_CONSTEXPR
#  define IUTEST_CONSTEXPR_OR_CONST	const
#endif

// rvalue reference
#if !defined(IUTEST_HAS_RVALUE_REFS)
#  if	defined(__clang__)
#    if __has_feature(cxx_rvalue_references)
#      define IUTEST_HAS_RVALUE_REFS	1
#    endif
#  elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_RVALUE_REFS	1
#  elif	defined(_MSC_VER) && (_MSC_VER >= 1700)
#    define IUTEST_HAS_RVALUE_REFS	1
#  endif
#endif

#ifndef IUTEST_HAS_RVALUE_REFS
#  define IUTEST_HAS_RVALUE_REFS	0
#endif

// delete function
#ifndef IUTEST_NO_DELETED_FUNCTIONS
#  if	defined(__clang__)
#    if __has_feature(cxx_deleted_functions)
#      define IUTEST_HAS_DELETED_FUNCTIONS	1
#    endif
#  elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_DELETED_FUNCTIONS	1
#  endif
#endif

#ifndef IUTEST_NO_DELETED_FUNCTIONS
#  define IUTEST_NO_DELETED_FUNCTIONS		0
#endif

// variadic template
#ifndef IUTEST_HAS_VARIADIC_TEMPLATES
#  if	defined(__clang__)
#    if __has_feature(cxx_variadic_templates)
#      define IUTEST_HAS_VARIADIC_TEMPLATES	1
#    endif
#  elif	defined(__GNUC__)
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=35722
#    if defined(__VARIADIC_TEMPLATES) || (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7) && defined(__GXX_EXPERIMENTAL_CXX0X__))
#      define IUTEST_HAS_VARIADIC_TEMPLATES	1
#    endif
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_TEMPLATES
#  define IUTEST_HAS_VARIADIC_TEMPLATES		0
#endif

//#ifndef IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES
//#  if	defined(__clang__)
//#    if __has_feature(cxx_variadic_templates)
//#      define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES	1
//#    endif
//#  elif	defined(__GNUC__)
//#    if defined(__VARIADIC_TEMPLATES) || (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7) && defined(__GXX_EXPERIMENTAL_CXX0X__))
//#      define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES	1
//#    endif
//#  endif
//#endif

#ifndef IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES
#  define IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES	0
#endif

// char16_t char32_t
#ifndef IUTEST_HAS_CHAR16_T
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_CHAR16_T	1
#  endif
#endif

#ifndef IUTEST_HAS_CHAR32_T
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_CHAR32_T	1
#  endif
#endif

#ifndef IUTEST_HAS_CHAR16_T
#  define IUTEST_HAS_CHAR16_T	0
#endif
#ifndef IUTEST_HAS_CHAR32_T
#  define IUTEST_HAS_CHAR32_T	0
#endif

// attribute
#ifndef IUTEST_ATTRIBUTE_UNUSED_
#  if defined(__GNUC__) && !defined(COMPILER_ICC)
#    define IUTEST_ATTRIBUTE_UNUSED_	__attribute__ ((unused))
#  else
#    define IUTEST_ATTRIBUTE_UNUSED_
#  endif
#endif

// exceptions
#if !defined(IUTEST_HAS_EXCEPTIONS)
#  if	defined(_MSC_VER) || defined(__BORLANDC__)
#    ifndef _HAS_EXCEPTIONS
#      define _HAS_EXCEPTIONS		1
#    endif
#    define IUTEST_HAS_EXCEPTIONS	_HAS_EXCEPTIONS
#  elif	defined(__clang__)
#    if __has_feature(cxx_exceptions)
#      define IUTEST_HAS_EXCEPTIONS	1
#    endif
#  elif	defined(__GNUC__)
#    if defined(__EXCEPTIONS)
#      define IUTEST_HAS_EXCEPTIONS	1
#    endif
#  elif	defined(__MWERKS__)
#    if __option(exceptions)
#      define IUTEST_HAS_EXCEPTIONS	1
#    endif
#  endif
#endif

#ifndef IUTEST_HAS_EXCEPTIONS
#  define IUTEST_HAS_EXCEPTIONS	0
#endif

#if !defined(IUTEST_HAS_SEH)
#  if	defined(_WIN32)
#    if	_MSC_VER > 1400
#      define IUTEST_HAS_SEH	1
#    endif
#  elif	defined(__BORLANDC__)
#    define IUTEST_HAS_SEH		1
#  endif
#endif

#ifndef IUTEST_HAS_SEH
#  define IUTEST_HAS_SEH		0
#endif

// rtti
#if !defined(IUTEST_HAS_RTTI)
#  if		defined(_MSC_VER)
#    ifdef _CPPRTTI
#      define IUTEST_HAS_RTTI	1
#    endif
#  elif	defined(__MWERKS__)
#    if	__option(RTTI)
#      define IUTEST_HAS_RTTI	1
#    endif
#  elif	defined(__ARMCC_VERSION)
#    ifdef __RTTI
#      define IUTEST_HAS_RTTI	1
#    endif
#  elif defined(__clang__)
#    if __has_feature(cxx_rtti)
#      define IUTEST_HAS_RTTI	1
#    endif
#  elif	defined(__GNUC__)
#    ifdef __RTTI
#      define IUTEST_HAS_RTTI	1
#    endif
#    ifdef __GXX_RTTI
#      define IUTEST_HAS_RTTI	1
#    endif
#  elif	defined(__IBMCPP__)
#    if (__IBMCPP__ >= 900)
#      define IUTEST_HAS_RTTI	1
#    endif
#  endif
#endif

#ifndef IUTEST_HAS_RTTI
#  define IUTEST_HAS_RTTI		0
#endif

#if IUTEST_HAS_RTTI
#  include <typeinfo>
#endif

// explicit instantiation access checking
#ifndef IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION
#  if defined(_MSC_VER) && (_MSC_VER <= 1500)
     // VS2008 以前では、private なメンバー関数に explicit instantiation でもアクセスできない
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION	0
#  else
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION	1
#  endif
#endif

#ifndef IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION
#  if defined(_MSC_VER)
// Visual Studio では、private な static メンバー関数に explicit instantiation でもアクセスできない
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION	0
#  else
#    define IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION	1
#  endif
#endif

// tuple
#if	defined(IUTEST_USE_EXTERNAL_TR1_TUPLE) && IUTEST_USE_EXTERNAL_TR1_TUPLE
# define IUTEST_HAS_STD_TUPLE	0
#endif

#ifndef IUTEST_USE_EXTERNAL_TR1_TUPLE
#  define IUTEST_USE_EXTERNAL_TR1_TUPLE	0
#endif

// std::tuple
#ifndef IUTEST_HAS_STD_TUPLE
#  if defined(IUTEST_USE_EXTERNAL_STD_TUPLE) && IUTEST_USE_EXTERNAL_STD_TUPLE
#    define IUTEST_HAS_STD_TUPLE	1
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1700) && _VARIADIC_MAX >= 9
#      define IUTEST_HAS_STD_TUPLE	1
#    endif
#  elif	defined(__GNUC__)
#    if IUTEST_HAS_VARIADIC_TEMPLATES
#      define IUTEST_HAS_STD_TUPLE	1
#    endif
#  endif
#endif

#ifndef IUTEST_HAS_STD_TUPLE
#  define IUTEST_HAS_STD_TUPLE		0
#endif

#ifndef IUTEST_USE_EXTERNAL_STD_TUPLE
#  define IUTEST_USE_EXTERNAL_STD_TUPLE	0
#endif

#if !IUTEST_HAS_STD_TUPLE

// std::tr1::tuple
#ifndef IUTEST_HAS_TR1_TUPLE
#  if defined(IUTEST_USE_EXTERNAL_TR1_TUPLE) && IUTEST_USE_EXTERNAL_TR1_TUPLE
#    define IUTEST_HAS_TR1_TUPLE	1
#  elif defined(_MSC_VER)
#    if (_MSC_VER >= 1500) && (_MSC_VER < 1700)
#      define IUTEST_HAS_TR1_TUPLE	1
#    endif
#  elif	defined(__GNUC__)
#    if (!defined(__CUDACC__) && !defined(__ARMCC_VERSION) && (__GNUC__ >= 4))
#      define IUTEST_HAS_TR1_TUPLE	1
#    endif
#  endif
#endif

#endif

#ifndef IUTEST_HAS_TR1_TUPLE
#  define IUTEST_HAS_TR1_TUPLE		0
#endif

#ifndef IUTEST_USE_OWN_TR1_TUPLE
#  define IUTEST_USE_OWN_TR1_TUPLE	0
#endif

#if IUTEST_HAS_STD_TUPLE
#  if !IUTEST_USE_EXTERNAL_STD_TUPLE
#    include <tuple>
#  endif
#else
#  if IUTEST_HAS_TR1_TUPLE && !IUTEST_USE_EXTERNAL_TR1_TUPLE
#    if IUTEST_USE_OWN_TR1_TUPLE
#      include "iutest_tuple.h"
#    else
#      if (defined(__GNUC__) && (__GNUC__ >= 4))
#        include <tr1/tuple>
#      else
#        include <tuple>
#      endif
#    endif
#  endif
#endif

#ifdef IUTEST_HAS_TUPLE
#  undef IUTEST_HAS_TUPLE
#endif
#if IUTEST_HAS_STD_TUPLE || IUTEST_HAS_TR1_TUPLE
#  define IUTEST_HAS_TUPLE	1
#else
#  define IUTEST_HAS_TUPLE	0
#endif

#if IUTEST_HAS_TUPLE

namespace iutest {
namespace tuple
{
#if IUTEST_HAS_STD_TUPLE
	using std::tuple;
	using std::tuple_size;
	using std::get;
#elif IUTEST_HAS_TR1_TUPLE
	using std::tr1::tuple;
	using std::tr1::tuple_size;
	using std::tr1::get;
#endif
}
}

#endif

// 可変長引数マクロ
#ifndef IUTEST_NO_VARIADIC_MACROS
#  if	defined(_MSC_VER) && (_MSC_VER < 1500)
#    define IUTEST_NO_VARIADIC_MACROS		1
#  endif
#endif

// pragma
#if		defined(_MSC_VER)
#  define IUTEST_PRAGMA(x)	__pragma(x)
#elif	defined(__GNUC__)
#  define IUTEST_PRAGMA(x)	_Pragma(#x)
#elif	defined(__clang__)
#  define IUTEST_PRAGMA(x)	_Pragma(#x)
#else
#  define IUTEST_PRAGMA(x)
#endif

// pragma warning
#if		defined(__GNUC__)
#  if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#    define IUTEST_PRAGMA_GCC_WARN_PUSH()		IUTEST_PRAGMA(GCC diagnostic push)
#    define IUTEST_PRAGMA_GCC_WARN_DISABLE(x)	IUTEST_PRAGMA(GCC diagnostic ignored x)
#    define IUTEST_PRAGMA_GCC_WARN_POP()		IUTEST_PRAGMA(GCC diagnostic pop)
#  else
#    define IUTEST_PRAGMA_GCC_WARN_PUSH()		
#    define IUTEST_PRAGMA_GCC_WARN_DISABLE(x)	
#    define IUTEST_PRAGMA_GCC_WARN_POP()		
#  endif
#endif

#if		defined(__clang__)
#  define IUTEST_PRAGMA_CLANG_WARN_PUSH()		IUTEST_PRAGMA(clang diagnostic push)
#  define IUTEST_PRAGMA_CLANG_WARN_DISABLE(x)	IUTEST_PRAGMA(clang diagnostic ignored x)
#  define IUTEST_PRAGMA_CLANG_WARN_POP()		IUTEST_PRAGMA(clang diagnostic pop)
#  define IUTEST_PRAGMA_GCC_WARN_PUSH			IUTEST_PRAGMA_CLANG_WARN_PUSH
#  define IUTEST_PRAGMA_GCC_WARN_DISABLE		IUTEST_PRAGMA_CLANG_WARN_DISABLE
#  define IUTEST_PRAGMA_GCC_WARN_POP			IUTEST_PRAGMA_CLANG_WARN_POP
#endif

#ifndef IUTEST_PRAGMA_GCC_WARN_PUSH
#  define IUTEST_PRAGMA_GCC_WARN_PUSH()
#endif
#ifndef IUTEST_PRAGMA_GCC_WARN_DISABLE
#  define IUTEST_PRAGMA_GCC_WARN_DISABLE(x)
#endif
#ifndef IUTEST_PRAGMA_GCC_WARN_POP
#  define IUTEST_PRAGMA_GCC_WARN_POP()
#endif

#ifndef IUTEST_PRAGMA_CLANG_WARN_PUSH
#  define IUTEST_PRAGMA_CLANG_WARN_PUSH()
#endif
#ifndef IUTEST_PRAGMA_CLANG_WARN_DISABLE
#  define IUTEST_PRAGMA_CLANG_WARN_DISABLE(x)
#endif
#ifndef IUTEST_PRAGMA_CLANG_WARN_POP
#  define IUTEST_PRAGMA_CLANG_WARN_POP()
#endif

#if		defined(_MSC_VER)
#  define IUTEST_PARGMA_WARN_PUSH()		IUTEST_PRAGMA(warning (push))
#  define IUTEST_PARGMA_WARN_POP()		IUTEST_PRAGMA(warning (pop))
#elif	defined(__GNUC__)
#  define IUTEST_PARGMA_WARN_PUSH()		IUTEST_PRAGMA_GCC_WARN_PUSH()
#  define IUTEST_PARGMA_WARN_POP()		IUTEST_PRAGMA_GCC_WARN_POP()
#elif	defined(__clang__)
#  define IUTEST_PARGMA_WARN_PUSH()		IUTEST_PRAGMA_CLANG_WARN_PUSH()
#  define IUTEST_PARGMA_WARN_POP()		IUTEST_PRAGMA_CLANG_WARN_PUSH()
#else
#  define IUTEST_PARGMA_WARN_PUSH()
#  define IUTEST_PARGMA_WARN_POP()
#endif


// pragma warning xxx
#if defined(_MSC_VER) && defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()		IUTEST_PRAGMA(warning (push))	\
															IUTEST_PRAGMA(warning (disable:4996))
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()		IUTEST_PRAGMA(warning (pop))
#else
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
#endif

#if		defined(_MSC_VER)
#  define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()	IUTEST_PRAGMA(warning (disable:4389))
#elif	defined(__clang__)
#  define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()	IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wsign-compare")
#elif	defined(__GNUC__)
#  define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()	IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wsign-compare")
#else
#  define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()
#endif

#if		defined(_MSC_VER)
#  define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()	IUTEST_PRAGMA(warning (disable:4390))
#elif	defined(__clang__)
#  define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()	IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wempty-body")
#elif	defined(__GNUC__)
#  define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()	IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wempty-body")
#else
#  define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()
#endif

#endif
