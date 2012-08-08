//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_switch.hpp
 * @brief		gtest から iutest への切り替え用 ファイル
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
#ifndef INCG_IRIS_iutest_switch_HPP_9E5FA1C8_EFB5_40a9_A3AD_971584ECAE56_
#define INCG_IRIS_iutest_switch_HPP_9E5FA1C8_EFB5_40a9_A3AD_971584ECAE56_

#if !defined(IUTEST_USE_GTEST)

#ifdef GTEST_USE_OWN_TR1_TUPLE
#  define IUTEST_USE_EXTERNAL_TR1_TUPLE	1	// gtest の tuple を使用する
#endif

//======================================================================
// include
#include "../iutest.hpp"

//======================================================================
// define

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
#undef RUN_ALL_TESTS
#undef TEST
#undef GTEST_TEST
#undef TEST_F
#undef TEST_P
#undef INSTANTIATE_TEST_CASE_P
#undef FRIEND_TEST

#undef ASSERT_TRUE
#undef ASSERT_FALSE
#undef ASSERT_EQ
#undef ASSERT_NE
#undef ASSERT_LT
#undef ASSERT_LE
#undef ASSERT_GT
#undef ASSERT_GE
#undef ASSERT_NEAR
#undef ASSERT_FLOAT_EQ
#undef ASSERT_DOUBLE_EQ
#undef ASSERT_STREQ
#undef ASSERT_STRNE
#undef ASSERT_STRCASEEQ
#undef ASSERT_STRCASENE
#undef ASSERT_THROW
#undef ASSERT_NO_THROW
#undef ASSERT_ANY_THROW
#undef ASSERT_NO_FATAL_FAILURE
#undef ASSERT_PRED_FORMAT1
#undef ASSERT_PRED_FORMAT2
#undef ASSERT_PRED_FORMAT3
#undef ASSERT_PRED_FORMAT4
#undef ASSERT_PRED_FORMAT5
#undef ASSERT_PRED1
#undef ASSERT_PRED2
#undef ASSERT_PRED3
#undef ASSERT_PRED4
#undef ASSERT_PRED5

#undef EXPECT_TRUE
#undef EXPECT_FALSE
#undef EXPECT_EQ
#undef EXPECT_NE
#undef EXPECT_LT
#undef EXPECT_LE
#undef EXPECT_GT
#undef EXPECT_GE
#undef EXPECT_NEAR
#undef EXPECT_FLOAT_EQ
#undef EXPECT_DOUBLE_EQ
#undef EXPECT_STREQ
#undef EXPECT_STRNE
#undef EXPECT_STRCASEEQ
#undef EXPECT_STRCASENE
#undef EXPECT_THROW
#undef EXPECT_NO_THROW
#undef EXPECT_ANY_THROW
#undef EXPECT_NO_FATAL_FAILURE
#undef EXPECT_PRED_FORMAT1
#undef EXPECT_PRED_FORMAT2
#undef EXPECT_PRED_FORMAT3
#undef EXPECT_PRED_FORMAT4
#undef EXPECT_PRED_FORMAT5
#undef EXPECT_PRED1
#undef EXPECT_PRED2
#undef EXPECT_PRED3
#undef EXPECT_PRED4
#undef EXPECT_PRED5

#undef SUCCEED
#undef FAIL
#undef ADD_FAILURE
#undef ADD_FAILURE_AT
#undef SCOPED_TRACE
#ifdef GTEST_OS_WINDOWS
#undef ASSERT_HRESULT_SUCCEEDED
#undef ASSERT_HRESULT_FAILED
#undef EXPECT_HRESULT_SUCCEEDED
#undef EXPECT_HRESULT_FAILED
#endif
#undef GTEST_FLAG

#undef TYPED_TEST_CASE
#undef TYPED_TEST
#undef TYPED_TEST_CASE_P
#undef TYPED_TEST_P
#undef REGISTER_TYPED_TEST_CASE_P
#undef INSTANTIATE_TYPED_TEST_CASE_P

#undef GTEST_HAS_DEATH_TEST
#undef GTEST_HAS_PARAM_TEST
#undef GTEST_HAS_COMBINE
#undef GTEST_HAS_TYPED_TEST
#undef GTEST_HAS_TYPED_TEST_P

#undef GTEST_HAS_EXCEPTIONS
#undef GTEST_HAS_RTTI
#undef GTEST_HAS_SEH

#ifdef GTEST_OS_CYGWIN
#  undef GTEST_OS_CYGWIN
#endif
#ifdef GTEST_OS_WINDOWS
#  undef GTEST_OS_WINDOWS
#  ifdef GTEST_OS_WINDOWS_MOBILE
#	 undef GTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef GTEST_OS_WINDOWS_MINGW
#	 undef GTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef GTEST_OS_WINDOWS_DESKTOP
#	 undef GTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef GTEST_OS_MAC
#  undef GTEST_OS_MAC
#endif
#ifdef GTEST_OS_LINUX
#  undef GTEST_OS_LINUX
#  ifdef GTEST_OS_LINUX_ANDROID
#	 undef GTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  undef IUTEST_OS_NACL
#endif

#undef GTEST_ATTRIBUTE_UNUSED_
#undef GTEST_AMBIGUOUS_ELSE_BLOCKER_

#undef GTEST_TEST_CLASS_NAME_
#undef GTEST_TEST_

#endif

#define RUN_ALL_TESTS	IUTEST_RUN_ALL_TESTS

#define TEST		IUTEST
#define GTEST_TEST	IUTEST_TEST
#define TEST_F		IUTEST_F
#define TEST_P		IUTEST_P
#define INSTANTIATE_TEST_CASE_P	IUTEST_INSTANTIATE_TEST_CASE_P

#define GTEST_TEST_CLASS_NAME_	IUTEST_TEST_CLASS_NAME_
#define GTEST_TEST_				IUTEST_TEST_

#define FRIEND_TEST		IUTEST_FRIEND_TEST

// ASSERT
#define ASSERT_TRUE		IUTEST_ASSERT_TRUE
#define ASSERT_FALSE	IUTEST_ASSERT_FALSE
#define ASSERT_EQ		IUTEST_ASSERT_EQ
#define ASSERT_NE		IUTEST_ASSERT_NE
#define ASSERT_LT		IUTEST_ASSERT_LT
#define ASSERT_LE		IUTEST_ASSERT_LE
#define ASSERT_GT		IUTEST_ASSERT_GT
#define ASSERT_GE		IUTEST_ASSERT_GE
#define ASSERT_NEAR		IUTEST_ASSERT_NEAR
#define ASSERT_FLOAT_EQ		IUTEST_ASSERT_FLOAT_EQ
#define ASSERT_DOUBLE_EQ	IUTEST_ASSERT_DOUBLE_EQ
#define ASSERT_STREQ		IUTEST_ASSERT_STREQ
#define ASSERT_STRNE		IUTEST_ASSERT_STRNE
#define ASSERT_STRCASEEQ	IUTEST_ASSERT_STRCASEEQ
#define ASSERT_STRCASENE	IUTEST_ASSERT_STRCASENE
#define ASSERT_THROW		IUTEST_ASSERT_THROW
#define ASSERT_NO_THROW		IUTEST_ASSERT_NO_THROW
#define ASSERT_ANY_THROW	IUTEST_ASSERT_ANY_THROW
#define ASSERT_NO_FATAL_FAILURE	IUTEST_ASSERT_NO_FATAL_FAILURE

#ifdef IUTEST_OS_WINDOWS
#  define ASSERT_HRESULT_SUCCEEDED	IUTEST_ASSERT_HRESULT_SUCCEEDED
#  define ASSERT_HRESULT_FAILED		IUTEST_ASSERT_HRESULT_FAILED
#endif

#define ASSERT_PRED1	IUTEST_ASSERT_PRED1
#define ASSERT_PRED2	IUTEST_ASSERT_PRED2
#define ASSERT_PRED3	IUTEST_ASSERT_PRED3
#define ASSERT_PRED4	IUTEST_ASSERT_PRED4
#define ASSERT_PRED5	IUTEST_ASSERT_PRED5

#define ASSERT_PRED_FORMAT1	IUTEST_ASSERT_PRED_FORMAT1
#define ASSERT_PRED_FORMAT2	IUTEST_ASSERT_PRED_FORMAT2
#define ASSERT_PRED_FORMAT3	IUTEST_ASSERT_PRED_FORMAT3
#define ASSERT_PRED_FORMAT4	IUTEST_ASSERT_PRED_FORMAT4
#define ASSERT_PRED_FORMAT5	IUTEST_ASSERT_PRED_FORMAT5

// EXPECT
#define EXPECT_TRUE		IUTEST_EXPECT_TRUE
#define EXPECT_FALSE	IUTEST_EXPECT_FALSE
#define EXPECT_EQ		IUTEST_EXPECT_EQ
#define EXPECT_NE		IUTEST_EXPECT_NE
#define EXPECT_LT		IUTEST_EXPECT_LT
#define EXPECT_LE		IUTEST_EXPECT_LE
#define EXPECT_GT		IUTEST_EXPECT_GT
#define EXPECT_GE		IUTEST_EXPECT_GE
#define EXPECT_NEAR		IUTEST_EXPECT_NEAR
#define EXPECT_FLOAT_EQ		IUTEST_EXPECT_FLOAT_EQ
#define EXPECT_DOUBLE_EQ	IUTEST_EXPECT_DOUBLE_EQ
#define EXPECT_STREQ		IUTEST_EXPECT_STREQ
#define EXPECT_STRNE		IUTEST_EXPECT_STRNE
#define EXPECT_STRCASEEQ	IUTEST_EXPECT_STRCASEEQ
#define EXPECT_STRCASENE	IUTEST_EXPECT_STRCASENE
#define EXPECT_THROW		IUTEST_EXPECT_THROW
#define EXPECT_NO_THROW		IUTEST_EXPECT_NO_THROW
#define EXPECT_ANY_THROW	IUTEST_EXPECT_ANY_THROW
#define EXPECT_NO_FATAL_FAILURE	IUTEST_EXPECT_NO_FATAL_FAILURE

#ifdef IUTEST_OS_WINDOWS
#  define EXPECT_HRESULT_SUCCEEDED	IUTEST_EXPECT_HRESULT_SUCCEEDED
#  define EXPECT_HRESULT_FAILED		IUTEST_EXPECT_HRESULT_FAILED
#endif

#define EXPECT_PRED1	IUTEST_EXPECT_PRED1
#define EXPECT_PRED2	IUTEST_EXPECT_PRED2
#define EXPECT_PRED3	IUTEST_EXPECT_PRED3
#define EXPECT_PRED4	IUTEST_EXPECT_PRED4
#define EXPECT_PRED5	IUTEST_EXPECT_PRED5

#define EXPECT_PRED_FORMAT1	IUTEST_EXPECT_PRED_FORMAT1
#define EXPECT_PRED_FORMAT2	IUTEST_EXPECT_PRED_FORMAT2
#define EXPECT_PRED_FORMAT3	IUTEST_EXPECT_PRED_FORMAT3
#define EXPECT_PRED_FORMAT4	IUTEST_EXPECT_PRED_FORMAT4
#define EXPECT_PRED_FORMAT5	IUTEST_EXPECT_PRED_FORMAT5

// INFORM
#define INFORM_TRUE		IUTEST_INFORM_TRUE
#define INFORM_FALSE	IUTEST_INFORM_FALSE
#define INFORM_EQ		IUTEST_INFORM_EQ
#define INFORM_NE		IUTEST_INFORM_NE
#define INFORM_LT		IUTEST_INFORM_LT
#define INFORM_LE		IUTEST_INFORM_LE
#define INFORM_GT		IUTEST_INFORM_GT
#define INFORM_GE		IUTEST_INFORM_GE
#define INFORM_NEAR		IUTEST_INFORM_NEAR
#define INFORM_FLOAT_EQ		IUTEST_INFORM_FLOAT_EQ
#define INFORM_DOUBLE_EQ	IUTEST_INFORM_DOUBLE_EQ
#define INFORM_STREQ		IUTEST_INFORM_STREQ
#define INFORM_STRNE		IUTEST_INFORM_STRNE
#define INFORM_STRCASEEQ	IUTEST_INFORM_STRCASEEQ
#define INFORM_STRCASENE	IUTEST_INFORM_STRCASENE
#define INFORM_THROW		IUTEST_INFORM_THROW
#define INFORM_NO_THROW		IUTEST_INFORM_NO_THROW
#define INFORM_ANY_THROW	IUTEST_INFORM_ANY_THROW
#define INFORM_NO_FATAL_FAILURE	IUTEST_INFORM_NO_FATAL_FAILURE

#ifdef IUTEST_OS_WINDOWS
#  define INFORM_HRESULT_SUCCEEDED	IUTEST_INFORM_HRESULT_SUCCEEDED
#  define INFORM_HRESULT_FAILED		IUTEST_INFORM_HRESULT_FAILED
#endif

#define INFORM_PRED1	IUTEST_INFORM_PRED1
#define INFORM_PRED2	IUTEST_INFORM_PRED2
#define INFORM_PRED3	IUTEST_INFORM_PRED3
#define INFORM_PRED4	IUTEST_INFORM_PRED4
#define INFORM_PRED5	IUTEST_INFORM_PRED5

#define INFORM_PRED_FORMAT1	IUTEST_INFORM_PRED_FORMAT1
#define INFORM_PRED_FORMAT2	IUTEST_INFORM_PRED_FORMAT2
#define INFORM_PRED_FORMAT3	IUTEST_INFORM_PRED_FORMAT3
#define INFORM_PRED_FORMAT4	IUTEST_INFORM_PRED_FORMAT4
#define INFORM_PRED_FORMAT5	IUTEST_INFORM_PRED_FORMAT5


#define SUCCEED				IUTEST_SUCCEED
#define FAIL				IUTEST_FAIL
#define ADD_FAILURE			IUTEST_ADD_FAILURE
#define ADD_FAILURE_AT		IUTEST_ADD_FAILURE_AT

#define SCOPED_TRACE		IUTEST_SCOPED_TRACE

#define GTEST_FLAG			IUTEST_FLAG

#define TYPED_TEST_CASE		IUTEST_TYPED_TEST_CASE
#define TYPED_TEST			IUTEST_TYPED_TEST
#define TYPED_TEST_CASE_P	IUTEST_TYPED_TEST_CASE_P
#define TYPED_TEST_P		IUTEST_TYPED_TEST_P
#define REGISTER_TYPED_TEST_CASE_P		IUTEST_REGISTER_TYPED_TEST_CASE_P
#define INSTANTIATE_TYPED_TEST_CASE_P	IUTEST_INSTANTIATE_TYPED_TEST_CASE_P


#define GTEST_HAS_DEATH_TEST	0
#define GTEST_HAS_PARAM_TEST	IUTEST_HAS_PARAM_TEST
#define GTEST_HAS_COMBINE		IUTEST_HAS_COMBINE
#define GTEST_HAS_TYPED_TEST	IUTEST_HAS_TYPED_TEST
#define GTEST_HAS_TYPED_TEST_P	IUTEST_HAS_TYPED_TEST_P

#define GTEST_HAS_EXCEPTIONS	IUTEST_HAS_EXCEPTIONS
#define GTEST_HAS_RTTI			IUTEST_HAS_RTTI
#define GTEST_HAS_SEH			IUTEST_HAS_SEH

#ifdef IUTEST_OS_CYGWIN
#  define GTEST_OS_CYGWIN		IUTEST_OS_CYGWIN
#endif
#ifdef IUTEST_OS_WINDOWS
#  define GTEST_OS_WINDOWS		IUTEST_OS_WINDOWS
#  ifdef IUTEST_OS_WINDOWS_MOBILE
#	 define GTEST_OS_WINDOWS_MOBILE		IUTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef IUTEST_OS_WINDOWS_MINGW
#	 define GTEST_OS_WINDOWS_MINGW		IUTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef IUTEST_OS_WINDOWS_DESKTOP
#	 define GTEST_OS_WINDOWS_DESKTOP	IUTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef IUTEST_OS_MAC
#  define GTEST_OS_MAC	IUTEST_OS_MAC
#endif
#ifdef IUTEST_OS_LINUX
#  define GTEST_OS_LINUX		IUTEST_OS_LINUX
#  ifdef IUTEST_OS_LINUX_ANDROID
#	 define GTEST_OS_LINUX_ANDROID	IUTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  define GTEST_OS_NACL	IUTEST_OS_NACL
#endif

#define GTEST_ATTRIBUTE_UNUSED_			IUTEST_ATTRIBUTE_UNUSED_
#define GTEST_AMBIGUOUS_ELSE_BLOCKER_	IUTEST_AMBIGUOUS_ELSE_BLOCKER_

namespace iutest
{

//======================================================================
// function
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleTest(int* argc, char** argv)
{
	InitIrisUnitTest(argc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleTest(int* argc, wchar_t** argv)
{
	InitIrisUnitTest(argc, argv);
}

#ifdef GMOCK_INCLUDE_GMOCK_GMOCK_H_
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleMock(int* argc, char** argv)
{
	testing::InitGoogleMock(argc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleMock(int* argc, wchar_t** argv)
{
	testing::InitGoogleMock(argc, argv);
}
#endif

}

#ifndef GMOCK_INCLUDE_GMOCK_GMOCK_H_

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
// すでに testing namespace が存在するので、define で置き換え
#  define testing	iutest
#else
// それ以外は namespace の置き換えで対応
namespace testing = iutest;
#endif

#endif

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#  define GTEST_INCLUDE_GTEST_GTEST_H_	// 以降で、gtest が include されないようにする
#endif

#else

#ifdef INCG_IRIS_iutest_HPP_
#  define GTEST_USE_OWN_TR1_TUPLE	0
#  ifdef StaticAssertTypeEq
#	 undef StaticAssertTypeEq
#  endif
#endif

#if	defined(_MSC_VER) && _MSC_VER >= 1700
#  ifndef _VARIADIC_MAX
#    define _VARIADIC_MAX	10
#  endif

#include <tuple>
namespace std {
namespace tr1
{
	using ::std::tuple;
}
}
#endif

//======================================================================
// include
#include "../iutest_ver.h"
#include <gtest/gtest.h>
#include "iutest_gtest_ver.hpp"

//======================================================================
// define

#ifdef INCG_IRIS_iutest_HPP_
#undef IUTEST_RUN_ALL_TESTS
#undef IUTEST
#undef IUTEST_TEST
#undef IUTEST_F
#undef IUTEST_P
#undef IUTEST_INSTANTIATE_TEST_CASE_P
#undef IUTEST_FRIEND_TEST

#undef IUTEST_ASSERT_TRUE
#undef IUTEST_ASSERT_FALSE
#undef IUTEST_ASSERT_EQ
#undef IUTEST_ASSERT_NE
#undef IUTEST_ASSERT_LT
#undef IUTEST_ASSERT_LE
#undef IUTEST_ASSERT_GT
#undef IUTEST_ASSERT_GE
#undef IUTEST_ASSERT_NEAR
#undef IUTEST_ASSERT_NULL
#undef IUTEST_ASSERT_NOTNULL
#undef IUTEST_ASSERT_SAME
#undef IUTEST_ASSERT_FLOAT_EQ
#undef IUTEST_ASSERT_DOUBLE_EQ
#undef IUTEST_ASSERT_STREQ
#undef IUTEST_ASSERT_STRNE
#undef IUTEST_ASSERT_STRLNEQ
#undef IUTEST_ASSERT_STRCASEEQ
#undef IUTEST_ASSERT_STRCASENE
#undef IUTEST_ASSERT_THROW
#undef IUTEST_ASSERT_NO_THROW
#undef IUTEST_ASSERT_ANY_THROW
#undef IUTEST_ASSERT_NO_FATAL_FAILURE
#undef IUTEST_ASSERT_PRED_FORMAT1
#undef IUTEST_ASSERT_PRED_FORMAT2
#undef IUTEST_ASSERT_PRED_FORMAT3
#undef IUTEST_ASSERT_PRED_FORMAT4
#undef IUTEST_ASSERT_PRED_FORMAT5
#undef IUTEST_ASSERT_PRED1
#undef IUTEST_ASSERT_PRED2
#undef IUTEST_ASSERT_PRED3
#undef IUTEST_ASSERT_PRED4
#undef IUTEST_ASSERT_PRED5

#undef IUTEST_EXPECT_TRUE
#undef IUTEST_EXPECT_FALSE
#undef IUTEST_EXPECT_EQ
#undef IUTEST_EXPECT_NE
#undef IUTEST_EXPECT_LT
#undef IUTEST_EXPECT_LE
#undef IUTEST_EXPECT_GT
#undef IUTEST_EXPECT_GE
#undef IUTEST_EXPECT_NEAR
#undef IUTEST_EXPECT_NULL
#undef IUTEST_EXPECT_NOTNULL
#undef IUTEST_EXPECT_SAME
#undef IUTEST_EXPECT_FLOAT_EQ
#undef IUTEST_EXPECT_DOUBLE_EQ
#undef IUTEST_EXPECT_STREQ
#undef IUTEST_EXPECT_STRNE
#undef IUTEST_EXPECT_STRLNEQ
#undef IUTEST_EXPECT_STRCASEEQ
#undef IUTEST_EXPECT_STRCASENE
#undef IUTEST_EXPECT_THROW
#undef IUTEST_EXPECT_NO_THROW
#undef IUTEST_EXPECT_ANY_THROW
#undef IUTEST_EXPECT_NO_FATAL_FAILURE
#undef IUTEST_EXPECT_PRED_FORMAT1
#undef IUTEST_EXPECT_PRED_FORMAT2
#undef IUTEST_EXPECT_PRED_FORMAT3
#undef IUTEST_EXPECT_PRED_FORMAT4
#undef IUTEST_EXPECT_PRED_FORMAT5
#undef IUTEST_EXPECT_PRED1
#undef IUTEST_EXPECT_PRED2
#undef IUTEST_EXPECT_PRED3
#undef IUTEST_EXPECT_PRED4
#undef IUTEST_EXPECT_PRED5

#undef IUTEST_INFORM_TRUE
#undef IUTEST_INFORM_FALSE
#undef IUTEST_INFORM_EQ
#undef IUTEST_INFORM_NE
#undef IUTEST_INFORM_LT
#undef IUTEST_INFORM_LE
#undef IUTEST_INFORM_GT
#undef IUTEST_INFORM_GE
#undef IUTEST_INFORM_NEAR
#undef IUTEST_INFORM_NULL
#undef IUTEST_INFORM_NOTNULL
#undef IUTEST_INFORM_SAME
#undef IUTEST_INFORM_FLOAT_EQ
#undef IUTEST_INFORM_DOUBLE_EQ
#undef IUTEST_INFORM_STREQ
#undef IUTEST_INFORM_STRNE
#undef IUTEST_INFORM_STRLNEQ
#undef IUTEST_INFORM_STRCASEEQ
#undef IUTEST_INFORM_STRCASENE
#undef IUTEST_INFORM_THROW
#undef IUTEST_INFORM_NO_THROW
#undef IUTEST_INFORM_ANY_THROW
#undef IUTEST_INFORM_NO_FATAL_FAILURE
#undef IUTEST_INFORM_PRED_FORMAT1
#undef IUTEST_INFORM_PRED_FORMAT2
#undef IUTEST_INFORM_PRED_FORMAT3
#undef IUTEST_INFORM_PRED_FORMAT4
#undef IUTEST_INFORM_PRED_FORMAT5
#undef IUTEST_INFORM_PRED1
#undef IUTEST_INFORM_PRED2
#undef IUTEST_INFORM_PRED3
#undef IUTEST_INFORM_PRED4
#undef IUTEST_INFORM_PRED5
#undef IUTEST_SUCCEED
#undef IUTEST_FAIL
#undef IUTEST_ASSERT_FAIL
#undef IUTEST_ADD_FAILURE
#undef IUTEST_EXPECT_FAIL
#undef IUTEST_ADD_FAILURE_AT
#undef IUTEST_EXPECT_FAIL_AT
#undef IUTEST_SCOPED_TRACE

#undef IUTEST_PRED_FORMAT1_
#undef IUTEST_PRED_FORMAT2_
#undef IUTEST_PRED_FORMAT3_
#undef IUTEST_PRED_FORMAT4_
#undef IUTEST_PRED_FORMAT5_

#ifdef IUTEST_OS_WINDOWS
#undef IUTEST_ASSERT_HRESULT_SUCCEEDED
#undef IUTEST_ASSERT_HRESULT_FAILED
#undef IUTEST_EXPECT_HRESULT_SUCCEEDED
#undef IUTEST_EXPECT_HRESULT_FAILED
#undef IUTEST_INFORM_HRESULT_SUCCEEDED
#undef IUTEST_INFORM_HRESULT_FAILED
#endif

#undef IUTEST_FLAG

#undef IUTEST_TYPED_TEST_CASE
#undef IUTEST_TYPED_TEST
#undef IUTEST_TYPED_TEST_CASE_P
#undef IUTEST_TYPED_TEST_P
#undef IUTEST_REGISTER_TYPED_TEST_CASE_P
#undef IUTEST_INSTANTIATE_TYPED_TEST_CASE_P

#undef IUTEST_HAS_PARAM_TEST
#undef IUTEST_HAS_COMBINE
#undef IUTEST_HAS_VARIADIC_COMBINE
#undef IUTEST_HAS_TYPED_TEST
#undef IUTEST_HAS_TYPED_TEST_P

#undef IUTEST_HAS_PARAM_METHOD_TEST

#undef IUTEST_THROW_ON_ASSERT_FAILURE

#undef IUTEST_HAS_PEEP
#undef IUTEST_HAS_PEEP_FUNC
#undef IUTEST_HAS_PEEP_STATIC_FUNC
#undef IUTEST_HAS_GENRAND

#undef IUTEST_HAS_VARIADIC_TEMPLATES
#undef IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES

#undef IUTEST_HAS_EXCEPTIONS
#undef IUTEST_HAS_RTTI
#undef IUTEST_HAS_SEH

#undef IUTEST_INIT

#undef IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING

#ifdef IUTEST_OS_CYGWIN
#  undef IUTEST_OS_CYGWIN
#endif
#ifdef IUTEST_OS_WINDOWS
#  undef IUTEST_OS_WINDOWS
#  ifdef IUTEST_OS_WINDOWS_MOBILE
#	 undef IUTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef IUTEST_OS_WINDOWS_MINGW
#	 undef IUTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef IUTEST_OS_WINDOWS_DESKTOP
#	 undef IUTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef IUTEST_OS_MAC
#  undef IUTEST_OS_MAC
#endif
#ifdef IUTEST_OS_LINUX
#  undef IUTEST_OS_LINUX
#  ifdef IUTEST_OS_LINUX_ANDROID
#	 undef IUTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  undef IUTEST_OS_NACL
#endif

#undef IUTEST_ATTRIBUTE_UNUSED_
#undef IUTEST_AMBIGUOUS_ELSE_BLOCKER_

#undef IUTEST_TEST_CLASS_NAME_
#undef IUTEST_TEST_

#endif

// INFORM 対応のために、初期化関数を呼ぶ
#undef RUN_ALL_TESTS
#define RUN_ALL_TESTS()			(::testing::iusupport::iuInitializeOfSupport(), (::testing::UnitTest::GetInstance()->Run()))
#define IUTEST_RUN_ALL_TESTS	RUN_ALL_TESTS

#define IUTEST		GTEST_TEST
#define IUTEST_TEST	GTEST_TEST
#define IUTEST_F	TEST_F
#define IUTEST_P	TEST_P
#define IUTEST_INSTANTIATE_TEST_CASE_P	INSTANTIATE_TEST_CASE_P

#define IUTEST_TEST_CLASS_NAME_	GTEST_TEST_CLASS_NAME_
#define IUTEST_TEST_			GTEST_TEST_

#define IUTEST_FRIEND_TEST		FRIEND_TEST


#define IUTEST_ASSERT_TRUE		ASSERT_TRUE
#define IUTEST_ASSERT_FALSE		ASSERT_FALSE
#define IUTEST_ASSERT_EQ		ASSERT_EQ
#define IUTEST_ASSERT_NE(expected, actual)		ASSERT_PRED_FORMAT2(::testing::internal::NeHelper<GTEST_IS_NULL_LITERAL_(expected)>::Compare, expected, actual)
#define IUTEST_ASSERT_LT		ASSERT_LT
#define IUTEST_ASSERT_LE		ASSERT_LE
#define IUTEST_ASSERT_GT		ASSERT_GT
#define IUTEST_ASSERT_GE		ASSERT_GE
#define IUTEST_ASSERT_NEAR		ASSERT_NEAR
#define IUTEST_ASSERT_NULL(v)	ASSERT_EQ(NULL, v)
#define IUTEST_ASSERT_NOTNULL(v)	ASSERT_TRUE(NULL != (v))
#define IUTEST_ASSERT_SAME(v1, v2)	ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSame, v1, v2)
#define IUTEST_ASSERT_FLOAT_EQ	ASSERT_FLOAT_EQ
#define IUTEST_ASSERT_DOUBLE_EQ	ASSERT_DOUBLE_EQ
#define IUTEST_ASSERT_STREQ		ASSERT_STREQ
#define IUTEST_ASSERT_STRNE		ASSERT_STRNE
#define IUTEST_ASSERT_STRLNEQ(len, v2)			ASSERT_PRED_FORMAT2(iuutil::CmpHelperSTRLNEQ, len, v2)
#define IUTEST_ASSERT_STRCASEEQ	ASSERT_STRCASEEQ
#define IUTEST_ASSERT_STRCASENE	ASSERT_STRCASENE
#define IUTEST_ASSERT_THROW(statement, expected_exception)		ASSERT_THROW((void)statement, expected_exception)
#define IUTEST_ASSERT_NO_THROW(statement)						ASSERT_NO_THROW((void)statement)
#define IUTEST_ASSERT_ANY_THROW(statement)						ASSERT_ANY_THROW((void)statement)
#define IUTEST_ASSERT_NO_FATAL_FAILURE		ASSERT_NO_FATAL_FAILURE

#ifdef GTEST_OS_WINDOWS
#  define IUTEST_ASSERT_HRESULT_SUCCEEDED	ASSERT_HRESULT_SUCCEEDED
#  define IUTEST_ASSERT_HRESULT_FAILED		ASSERT_HRESULT_FAILED
#endif

#define IUTEST_ASSERT_PRED1	ASSERT_PRED1
#define IUTEST_ASSERT_PRED2	ASSERT_PRED2
#define IUTEST_ASSERT_PRED3	ASSERT_PRED3
#define IUTEST_ASSERT_PRED4	ASSERT_PRED4
#define IUTEST_ASSERT_PRED5	ASSERT_PRED5

#define IUTEST_ASSERT_PRED_FORMAT1	ASSERT_PRED_FORMAT1
#define IUTEST_ASSERT_PRED_FORMAT2	ASSERT_PRED_FORMAT2
#define IUTEST_ASSERT_PRED_FORMAT3	ASSERT_PRED_FORMAT3
#define IUTEST_ASSERT_PRED_FORMAT4	ASSERT_PRED_FORMAT4
#define IUTEST_ASSERT_PRED_FORMAT5	ASSERT_PRED_FORMAT5

#define IUTEST_EXPECT_TRUE		EXPECT_TRUE
#define IUTEST_EXPECT_FALSE		EXPECT_FALSE
#define IUTEST_EXPECT_EQ		EXPECT_EQ
#define IUTEST_EXPECT_NE(expected, actual)		EXPECT_PRED_FORMAT2(::testing::internal::NeHelper<GTEST_IS_NULL_LITERAL_(expected)>::Compare, expected, actual)
#define IUTEST_EXPECT_LT		EXPECT_LT
#define IUTEST_EXPECT_LE		EXPECT_LE
#define IUTEST_EXPECT_GT		EXPECT_GT
#define IUTEST_EXPECT_GE		EXPECT_GE
#define IUTEST_EXPECT_NEAR		EXPECT_NEAR
#define IUTEST_EXPECT_NULL(v)	EXPECT_EQ(NULL, v)
#define IUTEST_EXPECT_NOTNULL(v)	EXPECT_TRUE(NULL != (v))
#define IUTEST_EXPECT_SAME(v1, v2)	EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSame, v1, v2)
#define IUTEST_EXPECT_FLOAT_EQ	EXPECT_FLOAT_EQ
#define IUTEST_EXPECT_DOUBLE_EQ	EXPECT_DOUBLE_EQ
#define IUTEST_EXPECT_STREQ		EXPECT_STREQ
#define IUTEST_EXPECT_STRNE		EXPECT_STRNE
#define IUTEST_EXPECT_STRLNEQ(len, v2)			EXPECT_PRED_FORMAT2(iuutil::CmpHelperSTRLNEQ, len, v2)
#define IUTEST_EXPECT_STRCASEEQ	EXPECT_STRCASEEQ
#define IUTEST_EXPECT_STRCASENE	EXPECT_STRCASENE
#define IUTEST_EXPECT_THROW(statement, expected_exception)	EXPECT_THROW((void)statement, expected_exception)
#define IUTEST_EXPECT_NO_THROW(statement)					EXPECT_NO_THROW((void)statement)
#define IUTEST_EXPECT_ANY_THROW(statement)					EXPECT_ANY_THROW((void)statement)
#define IUTEST_EXPECT_NO_FATAL_FAILURE		EXPECT_NO_FATAL_FAILURE

#ifdef GTEST_OS_WINDOWS
#  define IUTEST_EXPECT_HRESULT_SUCCEEDED	EXPECT_HRESULT_SUCCEEDED
#  define IUTEST_EXPECT_HRESULT_FAILED		EXPECT_HRESULT_FAILED
#endif

#define IUTEST_EXPECT_PRED1	EXPECT_PRED1
#define IUTEST_EXPECT_PRED2	EXPECT_PRED2
#define IUTEST_EXPECT_PRED3	EXPECT_PRED3
#define IUTEST_EXPECT_PRED4	EXPECT_PRED4
#define IUTEST_EXPECT_PRED5	EXPECT_PRED5

#define IUTEST_EXPECT_PRED_FORMAT1	EXPECT_PRED_FORMAT1
#define IUTEST_EXPECT_PRED_FORMAT2	EXPECT_PRED_FORMAT2
#define IUTEST_EXPECT_PRED_FORMAT3	EXPECT_PRED_FORMAT3
#define IUTEST_EXPECT_PRED_FORMAT4	EXPECT_PRED_FORMAT4
#define IUTEST_EXPECT_PRED_FORMAT5	EXPECT_PRED_FORMAT5

//	INFORM 対応
#define GTEST_INFORM_FAILURE_(message) \
	GTEST_MESSAGE_(message, ::testing::TestPartResult::kSuccess)

#define INFORM_PRED_FORMAT1(pred_format, v1) \
  GTEST_PRED_FORMAT1_(pred_format, v1, GTEST_INFORM_FAILURE_)
#define INFORM_PRED1(pred, v1) \
  GTEST_PRED1_(pred, v1, GTEST_INFORM_FAILURE_)

#define INFORM_PRED_FORMAT2(pred_format, v1, v2) \
  GTEST_PRED_FORMAT2_(pred_format, v1, v2, GTEST_INFORM_FAILURE_)
#define INFORM_PRED2(pred, v1, v2) \
  GTEST_PRED2_(pred, v1, v2, GTEST_INFORM_FAILURE_)

#define INFORM_PRED_FORMAT3(pred_format, v1, v2, v3) \
  GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, GTEST_INFORM_FAILURE_)
#define INFORM_PRED3(pred, v1, v2, v3) \
  GTEST_PRED3_(pred, v1, v2, v3, GTEST_INFORM_FAILURE_)

#define INFORM_PRED_FORMAT4(pred_format, v1, v2, v3, v4) \
  GTEST_PRED_FORMAT4_(pred_format, v1, v2, v3, v4, GTEST_INFORM_FAILURE_)
#define INFORM_PRED4(pred, v1, v2, v3, v4) \
  GTEST_PRED4_(pred, v1, v2, v3, v4, GTEST_INFORM_FAILURE_)

#define INFORM_PRED_FORMAT5(pred_format, v1, v2, v3, v4, v5) \
  GTEST_PRED_FORMAT5_(pred_format, v1, v2, v3, v4, v5, GTEST_INFORM_FAILURE_)
#define INFORM_PRED5(pred, v1, v2, v3, v4, v5) \
  GTEST_PRED5_(pred, v1, v2, v3, v4, v5, GTEST_INFORM_FAILURE_)


#define INFORM_TRUE(condition)	GTEST_TEST_BOOLEAN_(condition, #condition, false, true, GTEST_INFORM_FAILURE_)
#define INFORM_FALSE(condition)	GTEST_TEST_BOOLEAN_(!(condition), #condition, true, false, GTEST_INFORM_FAILURE_)

#define INFORM_EQ(expected, actual) \
  INFORM_PRED_FORMAT2(::testing::internal:: \
					  EqHelper<GTEST_IS_NULL_LITERAL_(expected)>::Compare, \
					  expected, actual)
#define INFORM_NE(expected, actual) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperNE, expected, actual)
#define INFORM_LE(val1, val2) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperLE, val1, val2)
#define INFORM_LT(val1, val2) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperLT, val1, val2)
#define INFORM_GE(val1, val2) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperGE, val1, val2)
#define INFORM_GT(val1, val2) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperGT, val1, val2)

#define INFORM_STREQ(expected, actual) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperSTREQ, expected, actual)
#define INFORM_STRNE(s1, s2) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperSTRNE, s1, s2)
#define INFORM_STRCASEEQ(expected, actual) \
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASEEQ, expected, actual)
#define INFORM_STRCASENE(s1, s2)\
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASENE, s1, s2)

#define INFORM_FLOAT_EQ(expected, actual)\
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<float>, \
					  expected, actual)
#define INFORM_DOUBLE_EQ(expected, actual)\
  INFORM_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, \
					  expected, actual)
#define INFORM_NEAR(val1, val2, abs_error)\
  INFORM_PRED_FORMAT3(::testing::internal::DoubleNearPredFormat, \
					  val1, val2, abs_error)

#define INFORM_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_INFORM_FAILURE_)
#define INFORM_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_INFORM_FAILURE_)
#define INFORM_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_INFORM_FAILURE_)

#define INFORM_NO_FATAL_FAILURE(statement) \
    GTEST_TEST_NO_FATAL_FAILURE_(statement, GTEST_INFORM_FAILURE_)

#define IUTEST_INFORM_TRUE		INFORM_TRUE
#define IUTEST_INFORM_FALSE		INFORM_FALSE
#define IUTEST_INFORM_EQ		INFORM_EQ
#define IUTEST_INFORM_NE(expected, actual)		INFORM_PRED_FORMAT2(::testing::internal::NeHelper<GTEST_IS_NULL_LITERAL_(expected)>::Compare, expected, actual)
#define IUTEST_INFORM_LT		INFORM_LT
#define IUTEST_INFORM_LE		INFORM_LE
#define IUTEST_INFORM_GT		INFORM_GT
#define IUTEST_INFORM_GE		INFORM_GE
#define IUTEST_INFORM_NULL(v)	INFORM_EQ(NULL, v)
#define IUTEST_INFORM_NOTNULL(v)	INFORM_TRUE(NULL != (v))
#define IUTEST_INFORM_SAME(v1, v2)	INFORM_PRED_FORMAT2(::testing::internal::CmpHelperSame, v1, v2)
#define IUTEST_INFORM_NEAR		INFORM_NEAR
#define IUTEST_INFORM_FLOAT_EQ	INFORM_FLOAT_EQ
#define IUTEST_INFORM_DOUBLE_EQ	INFORM_DOUBLE_EQ
#define IUTEST_INFORM_STREQ		INFORM_STREQ
#define IUTEST_INFORM_STRNE		INFORM_STRNE
#define IUTEST_INFORM_STRLNEQ(len, v2)			INFORM_PRED_FORMAT2(iuutil::CmpHelperSTRLNEQ, len, v2)
#define IUTEST_INFORM_STRCASEEQ	INFORM_STRCASEEQ
#define IUTEST_INFORM_STRCASENE	INFORM_STRCASENE
#define IUTEST_INFORM_THROW(statement, expected_exception)	INFORM_THROW((void)statement, expected_exception)
#define IUTEST_INFORM_NO_THROW(statement)					INFORM_NO_THROW((void)statement)
#define IUTEST_INFORM_ANY_THROW(statement)					INFORM_ANY_THROW((void)statement)
#define IUTEST_INFORM_NO_FATAL_FAILURE		INFORM_NO_FATAL_FAILURE


#define IUTEST_PRED_FORMAT1_	GTEST_PRED_FORMAT1_
#define IUTEST_PRED_FORMAT2_	GTEST_PRED_FORMAT2_
#define IUTEST_PRED_FORMAT3_	GTEST_PRED_FORMAT3_
#define IUTEST_PRED_FORMAT4_	GTEST_PRED_FORMAT4_
#define IUTEST_PRED_FORMAT5_	GTEST_PRED_FORMAT5_


#ifdef GTEST_OS_WINDOWS
# define INFORM_HRESULT_SUCCEEDED(expr) \
	INFORM_PRED_FORMAT1(::testing::internal::IsHRESULTSuccess, (expr))
# define INFORM_HRESULT_FAILED(expr) \
	INFORM_PRED_FORMAT1(::testing::internal::IsHRESULTFailure, (expr))

#  define IUTEST_INFORM_HRESULT_SUCCEEDED	INFORM_HRESULT_SUCCEEDED
#  define IUTEST_INFORM_HRESULT_FAILED		INFORM_HRESULT_FAILED
#endif

#define IUTEST_INFORM_PRED1	INFORM_PRED1
#define IUTEST_INFORM_PRED2	INFORM_PRED2
#define IUTEST_INFORM_PRED3	INFORM_PRED3
#define IUTEST_INFORM_PRED4	INFORM_PRED4
#define IUTEST_INFORM_PRED5	INFORM_PRED5

#define IUTEST_INFORM_PRED_FORMAT1	INFORM_PRED_FORMAT1
#define IUTEST_INFORM_PRED_FORMAT2	INFORM_PRED_FORMAT2
#define IUTEST_INFORM_PRED_FORMAT3	INFORM_PRED_FORMAT3
#define IUTEST_INFORM_PRED_FORMAT4	INFORM_PRED_FORMAT4
#define IUTEST_INFORM_PRED_FORMAT5	INFORM_PRED_FORMAT5

#define IUTEST_SUCCEED			GTEST_SUCCEED
#define IUTEST_FAIL				GTEST_FAIL
#define IUTEST_ASSERT_FAIL		GTEST_FAIL
#define IUTEST_ADD_FAILURE		ADD_FAILURE
#define IUTEST_EXPECT_FAIL		ADD_FAILURE
#define IUTEST_ADD_FAILURE_AT	ADD_FAILURE_AT
#define IUTEST_EXPECT_FAIL_AT	ADD_FAILURE_AT

#define IUTEST_SCOPED_TRACE		SCOPED_TRACE

#define IUTEST_FLAG				GTEST_FLAG

#define IUTEST_TYPED_TEST_CASE		TYPED_TEST_CASE
#define IUTEST_TYPED_TEST			TYPED_TEST
#define IUTEST_TYPED_TEST_CASE_P	TYPED_TEST_CASE_P
#define IUTEST_TYPED_TEST_P			TYPED_TEST_P
#define IUTEST_REGISTER_TYPED_TEST_CASE_P		REGISTER_TYPED_TEST_CASE_P
#define IUTEST_INSTANTIATE_TYPED_TEST_CASE_P	INSTANTIATE_TYPED_TEST_CASE_P

#define IUTEST_HAS_PARAM_TEST		GTEST_HAS_PARAM_TEST
#define IUTEST_HAS_COMBINE			GTEST_HAS_COMBINE
#define IUTEST_HAS_VARIADIC_COMBINE	0
#define IUTEST_HAS_TYPED_TEST		GTEST_HAS_TYPED_TEST
#define IUTEST_HAS_TYPED_TEST_P		GTEST_HAS_TYPED_TEST_P

#define IUTEST_HAS_PARAM_METHOD_TEST	0
#define IUTEST_THROW_ON_ASSERT_FAILURE	0

#define IUTEST_HAS_PEEP				0
#define IUTEST_HAS_PEEP_FUNC		0
#define IUTEST_HAS_PEEP_STATIC_FUNC	0
#define IUTEST_HAS_GENRAND			0

#define IUTEST_HAS_EXCEPTIONS		GTEST_HAS_EXCEPTIONS
#define IUTEST_HAS_RTTI				GTEST_HAS_RTTI
#define IUTEST_HAS_SEH				GTEST_HAS_SEH

#ifdef GTEST_OS_CYGWIN
#  define IUTEST_OS_CYGWIN		GTEST_OS_CYGWIN
#endif
#ifdef GTEST_OS_WINDOWS
#  include <windows.h>
#  define IUTEST_OS_WINDOWS		GTEST_OS_WINDOWS
#  ifdef GTEST_OS_WINDOWS_MOBILE
#	 define IUTEST_OS_WINDOWS_MOBILE	GTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef GTEST_OS_WINDOWS_MINGW
#	 define IUTEST_OS_WINDOWS_MINGW		GTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef GTEST_OS_WINDOWS_DESKTOP
#	 define IUTEST_OS_WINDOWS_DESKTOP	GTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef GTEST_OS_MAC
#  define IUTEST_OS_MAC	GTEST_OS_MAC
#endif
#ifdef GTEST_OS_LINUX
#  define IUTEST_OS_LINUX		GTEST_OS_LINUX
#  ifdef GTEST_OS_LINUX_ANDROID
#	 define IUTEST_OS_LINUX_ANDROID	GTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef GTEST_OS_NACL
#  define IUTEST_OS_NACL	GTEST_OS_NACL
#endif

#define IUTEST_ATTRIBUTE_UNUSED_		GTEST_ATTRIBUTE_UNUSED_
#define IUTEST_AMBIGUOUS_ELSE_BLOCKER_	GTEST_AMBIGUOUS_ELSE_BLOCKER_

#define IUTEST_INIT				testing::InitIrisUnitTest

#define IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING	GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_

namespace testing
{

//======================================================================
// function
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, char** argv)
{
	InitGoogleTest(pargc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, wchar_t** argv)
{
	InitGoogleTest(pargc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const char** argv)
{
	InitGoogleTest(pargc, const_cast<char**>(argv));
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const wchar_t** argv)
{
	InitGoogleTest(pargc, const_cast<wchar_t**>(argv));
}


namespace internal 
{

#if GTEST_MINORVER < 0x06
template<bool> struct EnableIf;
template<> struct EnableIf<true> { typedef void type; };
#endif

template<typename T1, typename T2>
inline AssertionResult	CmpHelperSame(const char* expected_str, const char* actual_str
									  , const T1& expected, const T2& actual)
{
	return EqHelper<false>::Compare(expected_str, actual_str, &expected, &actual);
}

template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
															   , const ::std::basic_string<Elem, Traits, Ax>& val1
															   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTREQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTREQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTREQ(expr1, expr2, val1.c_str(), val2);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRNE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRNE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTRNE(expr1, expr2, val1.c_str(), val2);
}

inline int iu_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
#if		defined(_MSC_VER)
	return _wcsicmp(str1, str2);
#elif	defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID)
	return wcscasecmp(str1, str2);
#else
	const wchar_t* l = str1;
	const wchar_t* r = str2;
	while(*l)
	{
		wchar_t ul = towupper(*l);
		wchar_t ur = towupper(*r);
		if( ul < ur ) return -1;
		if( ul > ur ) return 1;
		++l;
		++r;
	}
	if( *l < *r ) return -1;
	if( *l > *r ) return 1;
	return 0;
#endif
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 == val2 ) return AssertionSuccess();
	}
	else
	{
		if( iu_wcsicmp(val1, val2) == 0 ) return AssertionSuccess();
	}
	return EqFailure(expr1, expr2
		, String::ShowCStringQuoted(FormatForComparisonFailureMessage(val1, val2).c_str())
		, String::ShowCStringQuoted(FormatForComparisonFailureMessage(val2, val1).c_str())
		, true);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2);
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const wchar_t* val1, const wchar_t* val2)
{
	if( val1 == NULL || val2 == NULL ) 
	{
		if( val1 != val2 ) return AssertionSuccess();
	}
	else
	{
		if( iu_wcsicmp(val1, val2) != 0 ) return AssertionSuccess();
	}
	return AssertionFailure() << "error: Value of: " << expr1 << " != " << expr2
		<< "\n  Actual: " << FormatForComparisonFailureMessage(val2, val1) << "\nExpected: " << FormatForComparisonFailureMessage(val1, val2) ;
}

template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const Elem* val1
																   , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
																   , const ::std::basic_string<Elem, Traits, Ax>& val1
																   , const Elem* val2)
{
	return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2);
}

template <bool lhs_is_null_literal>
class NeHelper {
public:
	template <typename T1, typename T2>
	static AssertionResult Compare(const char* expected_expression,
		const char* actual_expression,
		const T1& expected,
		const T2& actual) {
			return CmpHelperNE(expected_expression, actual_expression, expected,
				actual);
	}

	static AssertionResult Compare(const char* expected_expression,
		const char* actual_expression,
		BiggestInt expected,
		BiggestInt actual) {
			return CmpHelperNE(expected_expression, actual_expression, expected,
				actual);
	}
};

template <>
class NeHelper<true> {
public:
	template <typename T1, typename T2>
	static AssertionResult Compare(
		const char* expected_expression,
		const char* actual_expression,
		const T1& expected,
		const T2& actual,
		typename EnableIf<!is_pointer<T2>::value>::type* = 0) {
			return CmpHelperNE(expected_expression, actual_expression, expected,
				actual);
	}

	template <typename T>
	static AssertionResult Compare(
		const char* expected_expression,
		const char* actual_expression,
		Secret* /* expected (NULL) */,
		T* actual) {
			return CmpHelperNE(expected_expression, actual_expression,
				static_cast<T*>(NULL), actual);
	}
};

}	// end of namespace internal

// tuple
namespace tuples
{
	using ::std::tr1::tuple;
	using ::std::tr1::tuple_size;
	using ::std::tr1::tuple_element;
	using ::std::tr1::make_tuple;
	using ::std::tr1::get;
}

using tuples::tuple;
using tuples::tuple_size;
using tuples::tuple_element;
using tuples::make_tuple;
using tuples::get;

namespace iusupport
{
	class iuDefaultPrinter : public ::testing::EmptyTestEventListener
	{
	private:
		virtual void OnTestPartResult(const TestPartResult& test_part_result)
		{
			if( ::testing::UnitTest::GetInstance()->listeners().default_result_printer() == NULL ) return;

			if( test_part_result.type() == TestPartResult::kSuccess )
			{
				// 成功のときに出力
				TestPartResult tmp(TestPartResult::kNonFatalFailure
					, test_part_result.file_name()
					, test_part_result.line_number()
					, test_part_result.message());
				::testing::UnitTest::GetInstance()->listeners().default_result_printer()->OnTestPartResult(tmp);
			}
		}
	};
	inline void	iuInitializeOfSupport(void)
	{
		// INFORM 用に printer を追加
		::testing::UnitTest::GetInstance()->listeners().Append( new iuDefaultPrinter() );
	}
}

#ifdef INCG_IRIS_iutest_HPP_
// iutest.hpp がすでにインクルードされていた場合

namespace iusupport
{
	inline AssertionResult iuMakeAssertionResult(const AssertionResult& ar) { return ar; }
	inline AssertionResult iuMakeAssertionResult(const ::iutest::AssertionResult& ar) { return AssertionResult(ar) << ar.failure_message(); }
}

// ::iutest::AssertionResult -> ::testing::AssertionResult 変換
#undef GTEST_ASSERT_
#define GTEST_ASSERT_(expression, on_failure) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar = ::testing::iusupport::iuMakeAssertionResult(expression)) \
	; \
  else \
	on_failure(gtest_ar.failure_message())

#endif

}	// end of namespace testing

#ifdef INCG_IRIS_iutest_HPP_
// すでに iutest namespace が存在するので、define で対応
#  define iutest testing
#else
namespace iutest = testing;
#endif

#include "../internal/iutest_pragma.h"
#include "../iutest_util.hpp"

#ifndef INCG_IRIS_iutest_HPP_
#  define INCG_IRIS_iutest_HPP_	// 以降で、iutest が include されないようにする
#endif

#endif

#endif
