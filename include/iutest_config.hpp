//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_config.hpp
 * @brief		iris unit test config ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_config_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_
#define INCG_IRIS_iutest_config_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_

//======================================================================
// include

/**
 * @defgroup	IUTEST_CONFIG	IUTEST_CONFIG
 * @brief		設定マクロ
 * @note		ユーザーが事前定義することで変更可能
 * @{
*/

/**
 * @defgroup	IUTEST_CONFIG_OUTPUT	OUTPUT
 * @brief		出力関係 CONFIG
 * @{
*/

#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)	vprintf(f, a)	//!< vprintf 呼び出しマクロ
#endif

#ifndef IUTEST_REPORT_SKIPPED
#  define IUTEST_REPORT_SKIPPED		1			//!< xml 出力に skipped タグを含めるかどうか
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_TEST	TEST
 * @brief		テスト関係 CONFIG
 * @{
*/

#ifndef IUTEST_HAS_PARAM_METHOD_TEST
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_HAS_PARAM_METHOD_TEST	1	//!< パラメタライズ関数コールテストが使用可能かどうか
#  else
#    define IUTEST_HAS_PARAM_METHOD_TEST	0	//!< パラメタライズ関数コールテストが使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_PARAM_TEST
#  define IUTEST_HAS_PARAM_TEST		1	//!< 値をパラメータ化したテストが使用可能かどうか
#endif

#ifndef IUTEST_HAS_TYPED_TEST
#  define IUTEST_HAS_TYPED_TEST		1	//!< 型付けテストが使用可能かどうか
#endif

#ifndef IUTEST_HAS_TYPED_TEST_P
//! 型をパラメータ化したテストが使用可能かどうか
#  if IUTEST_HAS_TYPED_TEST && !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_TYPED_TEST_P	1
#  else
#    define IUTEST_HAS_TYPED_TEST_P	0
#  endif
#endif

#ifndef IUTEST_TYPED_TEST_P_STRICT
#  define IUTEST_TYPED_TEST_P_STRICT	1	//!< より厳しい構文チェックを行うかどうか
#endif

#if IUTEST_HAS_TYPED_TEST_P
#  if IUTEST_TYPED_TEST_P_STRICT
#    include <set>
#  endif
#endif

#ifndef IUTEST_HAS_COMBINE
//! ::iutest::Combine が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_COMBINE		1
#  else
#    define IUTEST_HAS_COMBINE		0
#  endif
#endif

#ifndef IUTEST_HAS_PAIRWISE
//! ::iutest::Pairwise が使用可能かどうか
#  if IUTEST_HAS_COMBINE
#    define IUTEST_HAS_PAIRWISE		1
#  else
#    define IUTEST_HAS_PAIRWISE		0
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_VALUES
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_VALUES	1	//!< 可変長引数に対応した ::iutest::Values が使用可能かどうか
#  else
#    define IUTEST_HAS_VARIADIC_VALUES	0	//!< 可変長引数に対応した ::iutest::Values が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_COMBINE
#  if IUTEST_HAS_COMBINE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_COMBINE	1	//!< 可変長引数に対応した ::iutest::Combine が使用可能かどうか
#  else
#    define IUTEST_HAS_VARIADIC_COMBINE	0	//!< 可変長引数に対応した ::iutest::Combine が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_PAIRWISE
#  if IUTEST_HAS_PAIRWISE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_VARIADIC_PAIRWISE	1	//!< 可変長引数に対応した ::iutest::Pairwise が使用可能かどうか
#  else
#    define IUTEST_HAS_VARIADIC_PAIRWISE	0	//!< 可変長引数に対応した ::iutest::Pairwise が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_THROW_ON_ASSERT_FAILURE
/**
 * @brief	ASSERT マクロで失敗時に例外を throw します。
 * @note	サブ関数にアサーションを記述しても、その時点でテストが中断されるようになります
*/
#  define IUTEST_THROW_ON_ASSERT_FAILURE	0
#endif

#ifndef IUTEST_HAS_GENRAND
#  define IUTEST_HAS_GENRAND		1	//!< テストごとの genrand 関数が使用可能かどうか
#endif

#ifndef IUTEST_HAS_PACKAGE
#  define IUTEST_HAS_PACKAGE		1	//!< パッケージ機能があるかどうか
#endif

// peep
#ifndef IUTEST_HAS_PEEP
#  define IUTEST_HAS_PEEP			1	//!< private メンバーへのアクセスマクロが使用可能かどうか
#endif

#ifndef IUTEST_HAS_PEEP_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_FUNC	1	//!< private メンバー関数へのアクセスが可能かどうか
#  else
#    define IUTEST_HAS_PEEP_FUNC	0	//!< private メンバー関数へのアクセスが可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_PEEP_STATIC_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_STATIC_FUNC	1	//!< private static メンバー関数へのアクセスが可能かどうか
#  else
#    define IUTEST_HAS_PEEP_STATIC_FUNC	0	//!< private static メンバー関数へのアクセスが可能かどうか
#  endif
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_FILE	FILE
 * @brief		ファイル関係 CONFIG
 * @{
*/

// file
#ifndef IUTEST_HAS_FOPEN
#  define IUTEST_HAS_FOPEN			1	//!< fopen が使用可能かどうか
#endif

#ifndef IUTEST_HAS_FILE_STAT
#  define IUTEST_HAS_FILE_STAT		0	//!< stat が使用可能かどうか
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_TIME	TIME
 * @brief		TIME関係 CONFIG
 * @{
*/

#ifndef IUTEST_HAS_CTIME
#  if	defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_CTIME		0	//!< time 関数が使用可能かどうか
#  else
#    define IUTEST_HAS_CTIME		1	//!< time 関数が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_GETTIMEOFDAY
#  define IUTEST_HAS_GETTIMEOFDAY	0	//!< gettimeofday 関数が使用可能かどうか
#endif

#ifndef IUTEST_HAS_CLOCK
#  define IUTEST_HAS_CLOCK			0	//!< clock 関数が使用可能かどうか
#endif

/**
 * @}
*/


/**
 * @defgroup	IUTEST_CONFIG_OTHER	OTHER
 * @brief		その他の CONFIG
 * @{
*/

// other
#ifndef IUTEST_HAS_STRINGSTREAM
#  define IUTEST_HAS_STRINGSTREAM	1	//!< std::stringstream が使用可能かどうか
#endif

#ifndef IUTEST_USE_STRSTREAM
#  define IUTEST_USE_STRSTREAM		0	//!< std::strstream が使用可能かどうか
#endif

/**
 * @}
*/

// Doxygen 用
#ifdef IUTEST_BUILD_DOXYGEN

/**
 * @ingroup	IUTEST_CONFIG_TIME	TIME
 * @{
*/

#define IUTEST_GetMillisec()	//!< 現在時刻のミリ秒取得関数を独自定義

/**
* @}
*/


/**
 * @brief	iutest で t1/tuple.h をインクルードするかどうか
 * @details	1: std::tr1 名前空間にある tuple を使用します。
 *			tuple.h はユーザーがインクルードします。
 *			0: 指定なし iutest が自動で判断します。
*/
#define IUTEST_USE_EXTERNAL_TR1_TUPLE	0

/**
 * @brief	iutest で tuple.h をインクルードするかどうか
 * @details	1: std 名前空間にある tuple を使用します。
 *			tuple.h はユーザーがインクルードします。
 *			0: 指定なし iutest が自動で判断します。
*/
#define IUTEST_USE_EXTERNAL_STD_TUPLE	0

/**
 * @ingroup	IUTEST_CONFIG_OTHER	OTHER
 * @{
*/

#define IUTEST_NO_GETENV	//!< getenv 関数がない場合は定義
#define IUTEST_NO_PUTENV	//!< putenv 関数がない場合は定義
#define IUTEST_NO_GETCWD	//!< getcwd 関数がない場合は定義

/**
 * @}
*/

#endif

/**
 * @}
*/

#endif
