//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest.hpp
 * @brief       iris unit test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
 *
 * @see         iutest_ver.hpp
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_HPP_
#define INCG_IRIS_IUTEST_HPP_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_ver.hpp"
#include "internal/iutest_compiler.hpp"

IUTEST_PRAGMA_IUTEST_WARN_DISABLE_BEGIN()

#include "iutest_legacy.hpp"
#include "iutest_core.hpp"
#include "iutest_param_tests.hpp"
#include "iutest_typed_tests.hpp"
#include "iutest_prod.hpp"
#include "iutest_expression_assertion.hpp"
#include "iutest_matcher.hpp"
#include "iutest_static_assertion.hpp"
#include "iutest_ignore.hpp"
#include "listener/iutest_default_printer.hpp"
#include "listener/iutest_stderr_xml_generator.hpp"
#include "listener/iutest_streaming_listener.hpp"

#if defined(__AFX_H__)
#include "internal/iutest_mfc.hpp"
#endif
// IWYU pragma: end_exports

//======================================================================
// define
/**
 * @defgroup    TESTDEF     テスト定義マクロ
 * @brief       テスト定義マクロ
*/

/**
 * @ingroup TESTDEF
 * @def     IUTEST_TEST(testsuite_, testname_)
 * @brief   テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST_TEST(testsuite_, testname_)      IUTEST_TEST_STRICT_(testsuite_, testname_    \
                                                    , ::iutest::Test, ::iutest::internal::GetTestTypeId())

/**
 * @ingroup TESTDEF
 * @def     IUTEST(testsuite_, testname_)
 * @brief   テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST(testsuite_, testname_)           IUTEST_TEST(testsuite_, testname_)

/**
 * @ingroup TESTDEF
 * @def     IUTEST_F(testfixture_, testname_)
 * @brief   ユーザー指定テスト関数定義マクロ
 * @param   testfixture_    = テストフィクスチャ名
 * @param   testname_       = テスト名
*/
#define IUTEST_F(testfixture_, testname_)       IUTEST_TEST_F_(testfixture_, testname_)

#if IUTEST_HAS_PARAM_METHOD_TEST
/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_PMZ(testsuite_, testname_, method_, ...)
 * @brief   パラメタライズ関数コールテスト定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @param   method_     = 関数
*/
#define IUTEST_PMZ(testsuite_, testname_, method_, ...) IIUT_TEST_PMZ_(testsuite_, testname_    \
                                                            , method_, ::iutest::Test           \
                                                            , ::iutest::internal::GetTestTypeId(), __VA_ARGS__)

/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_PMZ_F(testfixture_, testname_, method_, ...)
 * @brief   パラメタライズ関数コールテスト定義マクロ
 * @param   testfixture_    = テストフィクスチャ名
 * @param   testname_       = テスト名
 * @param   method_         = 関数
*/
#define IUTEST_PMZ_F(testfixture_, testname_, method_, ...) IIUT_TEST_PMZ_(testfixture_, testname_  \
                                                                , method_, testfixture_             \
                                                                , ::iutest::internal::GetTypeId< testfixture_ >(), __VA_ARGS__)

#endif

#if IUTEST_HAS_TESTNAME_ALIAS

/**
 * @ingroup TESTDEF
 * @brief   テストの別名
 * @param   testname_       = テスト名
*/
#define IUTEST_ALIAS_TESTNAME(testname_)                        IUTEST_ALIAS_TESTNAME_(testname_)

/**
 * @ingroup TESTDEF
 * @brief   テストフィクスチャ用テストの別名
 * @param   testsuitename_   = TestSuite 名
 * @param   testfixture_    = テストフィクスチャ名
*/
#define IUTEST_ALIAS_TESTNAME_F(testsuitename_, testfixture_)   IUTEST_ALIAS_TESTNAME_F_(testsuitename_, testfixture_)

#if IUTEST_HAS_TESTNAME_ALIAS_JP

/**
 * @ingroup TESTDEF
 * @brief   日本語テスト名
 * @param   testname_       = テスト名
*/
#define IUTEST_JAPANESE_NAME(testname_)                         IUTEST_ALIAS_TESTNAME(testname_)

/**
 * @ingroup TESTDEF
 * @brief   テストフィクスチャ用日本語テスト名
 * @param   testsuitename_   = TestSuite 名
 * @param   testfixture_    = テストフィクスチャ名
*/
#define IUTEST_JAPANESE_NAME_F(testsuitename_, testfixture_)    IUTEST_ALIAS_TESTNAME_F(testsuitename_, testfixture_)

#endif

#endif

/**
 * @ingroup TESTDEF
 * @brief   iutest の初期化処理
 * @param   argc_   = コマンドライン引数の総数
 * @param   argv_   = コマンドライン引数
*/
#define IUTEST_INIT(argc_, argv_)               ::iutest::InitIrisUnitTest(argc_, argv_)

/**
 * @ingroup TESTDEF
 * @brief   すべてのテストを実行する
*/
#define IUTEST_RUN_ALL_TESTS()                  ::iutest::UnitTestSource::GetInstance().Run()


/**
 * @defgroup    IUTEST_UTIL     テスト記述補助
 * @brief       テスト記述補助マクロ
*/

/**
 * @ingroup     IUTEST_UTIL
 * @brief       get iutest flag
 * @name        name = flag name
*/
#ifndef IUTEST_FLAG_GET
#  define IUTEST_FLAG_GET(name)   ::iutest::IUTEST_FLAG(name)
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       set iutest flag
 * @name        name  = flag name
 * @param       value = flag value
*/
#ifndef IUTEST_FLAG_SET
#  define IUTEST_FLAG_SET(name, value)   (void)(::iutest::IUTEST_FLAG(name) = value)
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       スコープ内のテストメッセージへのメッセージ追加
 * @param       msg = メッセージ
*/
#ifndef IUTEST_SCOPED_TRAC
#  define IUTEST_SCOPED_TRACE(msg)                IIUT_SCOPED_MESSAGE(msg)
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       明示的な成功
 * @details     明示的に成功を報告します
*/
#ifndef IUTEST_SUCCEED
#  define IUTEST_SUCCEED()                      IIUT_SUCCEED()
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       明示的な失敗
 * @details     明示的に致命的な失敗を報告します
*/
#ifndef IUTEST_FAIL
#  define IUTEST_FAIL()                         IIUT_FAIL()
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       明示的な失敗
 * @details     明示的に致命的でない失敗を報告します
*/
#ifndef IUTEST_ADD_FAILURE
#  define IUTEST_ADD_FAILURE()                  IIUT_ADD_FAILURE()
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       明示的な失敗
 * @details     明示的に致命的でない失敗を報告します
 * @param       file    = ファイルパス
 * @param       line    = 行番号
*/
#ifndef IUTEST_ADD_FAILURE_AT
#  define IUTEST_ADD_FAILURE_AT(file, line)     IIUT_ADD_FAILURE_AT(file, line)
#endif

/**
 * @ingroup     IUTEST_UTIL
 * @brief       テストの明示的なスキップ
 * @details     明示的にスキップを報告します
*/
#ifndef IUTEST_SKIP
#  define IUTEST_SKIP()                         IUTEST_TEST_SKIP()
#endif

/**
 * @defgroup    IUTEST_ASSERTION_   アサーション
*/

/**
 * @ingroup     IUTEST_ASSERTION_
 * @{
*/

/**
 * @defgroup    IUTEST_ASSERT_  ASSERT
 * @brief       致命的エラーフレーバー
 * @details     失敗した場合、その時点でテストから抜けます。
*/

/**
 * @}
*/

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_ASSERT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT(...)                      IUTEST_TEST_EXPRESSION_((__VA_ARGS__), true, IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT(expression)               IUTEST_TEST_EXPRESSION_(expression, true, IUTEST_ASSERT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_ASSERT_NOT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_NOT(...)                  IUTEST_TEST_EXPRESSION_((__VA_ARGS__), false, IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_NOT(expression)           IUTEST_TEST_EXPRESSION_(expression, false, IUTEST_ASSERT_FAILURE)
#  endif
#endif

#if IUTEST_HAS_MATCHERS
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   matcher テスト
 * @param   actual  = 検査対象
 * @param   matcher = matcher
*/
#ifndef IUTEST_ASSERT_THAT
#  define IUTEST_ASSERT_THAT(actual, matcher)       IUTEST_TEST_THAT(actual, matcher, IUTEST_ASSERT_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   == テスト
 * @details actual が expected と等しいことを検証します
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_EQ
#  define IUTEST_ASSERT_EQ(expected, actual)        IUTEST_TEST_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   != テスト（浮動小数点数は誤差考慮）
 * @details actual が expected と等しいことを検証します
 *          浮動小数点数の場合、誤差を考慮した FLOAT_EQ/DOUBLE_EQ での検証になります。
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_ALMOST_EQ
#  define IUTEST_ASSERT_ALMOST_EQ(expected, actual) IUTEST_TEST_ALMOST_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   != テスト
 * @details v1 と v2 が等しくないことを検証します
*/
#ifndef IUTEST_ASSERT_NE
#  define IUTEST_ASSERT_NE(v1, v2)                  IUTEST_TEST_NE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   <= テスト
 * @details v1 <= v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSERT_LE
#  define IUTEST_ASSERT_LE(v1, v2)                  IUTEST_TEST_LE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   < テスト
 * @details v1 < v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSERT_LT
#  define IUTEST_ASSERT_LT(v1, v2)                  IUTEST_TEST_LT(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   >= テスト
 * @details v1 >= v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSERT_GE
#  define IUTEST_ASSERT_GE(v1, v2)                  IUTEST_TEST_GE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   \> テスト
 * @details v1 > v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSERT_GT
#  define IUTEST_ASSERT_GT(v1, v2)                  IUTEST_TEST_GT(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   TRUE テスト
 * @details v が真であることを検証します
*/
#ifndef IUTEST_ASSERT_TRUE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_TRUE(...)                 IUTEST_TEST_TRUE((__VA_ARGS__), #__VA_ARGS__, IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_TRUE(v)                   IUTEST_TEST_TRUE(v, #v, IUTEST_ASSERT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   FALSE テスト
 * @details v が偽であることを検証します
*/
#ifndef IUTEST_ASSERT_FALSE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_FALSE(...)                IUTEST_TEST_FALSE((__VA_ARGS__), #__VA_ARGS__, IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_FALSE(v)                  IUTEST_TEST_FALSE(v, #v, IUTEST_ASSERT_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   NULL テスト
 * @details v が NULL であることを検証します
*/
#ifndef IUTEST_ASSERT_NULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_NULL(...)                 IUTEST_TEST_NULL((__VA_ARGS__), IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_NULL(v)                   IUTEST_TEST_NULL(v, IUTEST_ASSERT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   NOT NULL テスト
 * @details v が NULL でないことを検証します
*/
#ifndef IUTEST_ASSERT_NOTNULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_NOTNULL(...)              IUTEST_TEST_NOTNULL((__VA_ARGS__), IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_NOTNULL(v)                IUTEST_TEST_NOTNULL(v, IUTEST_ASSERT_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   アドレス一致 テスト
 * @details v1 と v2 のアドレスが同じであることを検証します
*/
#ifndef IUTEST_ASSERT_SAME
#  define IUTEST_ASSERT_SAME(v1, v2)                IUTEST_TEST_SAME(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_FLOAT_EQ
#  define IUTEST_ASSERT_FLOAT_EQ(expected, actual)  IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_DOUBLE_EQ
#  define IUTEST_ASSERT_DOUBLE_EQ(expected, actual) IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif

#if IUTEST_HAS_LONG_DOUBLE
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   long double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_LONG_DOUBLE_EQ
#  define IUTEST_ASSERT_LONG_DOUBLE_EQ(expected, actual)    \
    IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSERT_COMPLEX_EQ
#  define IUTEST_ASSERT_COMPLEX_EQ(expected, actual)    \
    IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   ２値の差の範囲 テスト
 * @param   v1      = 値1
 * @param   v2      = 値2
 * @param   abs_v   = v1 と v2 の差分の期待値
*/
#ifndef IUTEST_ASSERT_NEAR
#  define IUTEST_ASSERT_NEAR(v1, v2, abs_v)         IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   文字列の一致 テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_ASSERT_STREQ
#  define IUTEST_ASSERT_STREQ(expected_str, actual_str) \
    IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   文字列の不一致 テスト
 * @details v1 と v2 文字列が異なることを検証します
*/
#ifndef IUTEST_ASSERT_STRNE
#  define IUTEST_ASSERT_STRNE(v1, v2)               IUTEST_TEST_STRNE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   文字列の一致（大文字小文字区別なし） テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_ASSERT_STRCASEEQ
#  define IUTEST_ASSERT_STRCASEEQ(expected_str, actual_str) \
    IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   文字列の不一致（大文字小文字区別なし） テスト
 * @details v1 と v2 文字列が異なることを検証します（大文字小文字区別なし）
*/
#ifndef IUTEST_ASSERT_STRCASENE
#  define IUTEST_ASSERT_STRCASENE(v1, v2)           IUTEST_TEST_STRCASENE(v1, v2, IUTEST_ASSERT_FAILURE)
#endif

#if defined(IUTEST_OS_WINDOWS)

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   HRESULT の成功 テスト
 * @details HRESULT が成功であることを検証します
*/
#ifndef IUTEST_ASSERT_HRESULT_SUCCEEDED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_HRESULT_SUCCEEDED(...)    IUTEST_TEST_HRESULT_SUCCEEDED((__VA_ARGS__), IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_HRESULT_SUCCEEDED(hr)     IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_ASSERT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSERT_
 * @brief   HRESULT の失敗 テスト
 * @details HRESULT が失敗であることを検証します
*/
#ifndef IUTEST_ASSERT_HRESULT_FAILED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSERT_HRESULT_FAILED(...)       IUTEST_TEST_HRESULT_FAILED((__VA_ARGS__), IUTEST_ASSERT_FAILURE)
#  else
#    define IUTEST_ASSERT_HRESULT_FAILED(hr)        IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_ASSERT_FAILURE)
#  endif
#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   throw テスト
 * @details statement が expected_exception を throw することを検証します
 * @param   statement   = ステートメント
 * @param   expected_exception = 期待する例外
*/
#ifndef IUTEST_ASSERT_THROW
#  define IUTEST_ASSERT_THROW(statement, expected_exception)    \
    IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   throw value == テスト
 * @details statement が expected_exception を throw し、その値が expected_value と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_value      = 期待値
*/
#ifndef IUTEST_ASSERT_THROW_VALUE_EQ
#  define IUTEST_ASSERT_THROW_VALUE_EQ(statement, expected_exception, expected_value)   \
    IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_value, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   throw value != テスト
 * @details statement が expected_exception を throw し、その値が v と等しくないことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   v                   = 値
*/
#ifndef IUTEST_ASSERT_THROW_VALUE_NE
#  define IUTEST_ASSERT_THROW_VALUE_NE(statement, expected_exception, v)    \
    IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, v, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   throw value 文字列一致 テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_ASSERT_THROW_VALUE_STREQ
#  define IUTEST_ASSERT_THROW_VALUE_STREQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_str, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   throw value 文字列一致（大文字小文字区別なし） テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します（大文字小文字区別なし）
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_ASSERT_THROW_VALUE_STRCASEEQ
#  define IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_str, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   any throw テスト
 * @details statement が何らかの例外を投げることを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSERT_ANY_THROW
#  define IUTEST_ASSERT_ANY_THROW(statement)        IUTEST_TEST_ANY_THROW_(statement, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   no throw テスト
 * @details statement が例外を投げないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSERT_NO_THROW
#  define IUTEST_ASSERT_NO_THROW(statement)         IUTEST_TEST_NO_THROW_(statement, IUTEST_ASSERT_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   no new failure テスト
 * @details statement で失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSERT_NO_FAILURE
#  define IUTEST_ASSERT_NO_FAILURE(statement)       IUTEST_TEST_NO_FAILURE_(statement, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   no new fatal failure テスト
 * @details statement で致命的な失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSERT_NO_FATAL_FAILURE
#  define IUTEST_ASSERT_NO_FATAL_FAILURE(statement) IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSERT_
 * @brief   明示的な失敗
 * @details     明示的に致命的な失敗を報告します
*/
#ifndef IUTEST_ASSERT_FAIL
#  define IUTEST_ASSERT_FAIL()                      IIUT_FAIL()
#endif

/**
 * @ingroup     IUTEST_ASSERTION_
 * @{
*/

/**
 * @defgroup    IUTEST_EXPECT_  EXPECT
 * @brief       致命的ではないエラーフレーバー
 * @details     失敗した場合でも、テストを続行します。
*/

/**
 * @}
*/

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_EXPECT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT(...)                      IUTEST_TEST_EXPRESSION_((__VA_ARGS__), true, IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT(expression)               IUTEST_TEST_EXPRESSION_(expression, true, IUTEST_EXPECT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_EXPECT_NOT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_NOT(...)                  IUTEST_TEST_EXPRESSION_((__VA_ARGS__), false, IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_NOT(expression)           IUTEST_TEST_EXPRESSION_(expression, false, IUTEST_EXPECT_FAILURE)
#  endif
#endif

#if IUTEST_HAS_MATCHERS
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   matcher テスト
 * @param   actual  = 検査対象
 * @param   matcher = matcher
*/
#ifndef IUTEST_EXPECT_THAT
#  define IUTEST_EXPECT_THAT(actual, matcher)       IUTEST_TEST_THAT(actual, matcher, IUTEST_EXPECT_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   == テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_EQ
#  define IUTEST_EXPECT_EQ(expected, actual)        IUTEST_TEST_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   != テスト（浮動小数点数は誤差考慮）
 * @details actual が expected と等しいことを検証します
 *          浮動小数点数の場合、誤差を考慮した FLOAT_EQ/DOUBLE_EQ での検証になります。
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_ALMOST_EQ
#  define IUTEST_EXPECT_ALMOST_EQ(expected, actual) IUTEST_TEST_ALMOST_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   != テスト
 * @details v1 と v2 が等しくないことを検証します
*/
#ifndef IUTEST_EXPECT_NE
#  define IUTEST_EXPECT_NE(v1, v2)                  IUTEST_TEST_NE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   <= テスト
 * @details v1 <= v2 が成り立つことを検証します
*/
#ifndef IUTEST_EXPECT_LE
#  define IUTEST_EXPECT_LE(v1, v2)                  IUTEST_TEST_LE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   < テスト
 * @details v1 < v2 が成り立つことを検証します
*/
#ifndef IUTEST_EXPECT_LT
#  define IUTEST_EXPECT_LT(v1, v2)                  IUTEST_TEST_LT(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   >= テスト
 * @details v1 >= v2 が成り立つことを検証します
*/
#ifndef IUTEST_EXPECT_GE
#  define IUTEST_EXPECT_GE(v1, v2)                  IUTEST_TEST_GE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   \> テスト
 * @details v1 > v2 が成り立つことを検証します
*/
#ifndef IUTEST_EXPECT_GT
#  define IUTEST_EXPECT_GT(v1, v2)                  IUTEST_TEST_GT(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   TRUE テスト
 * @details v が真であることを検証します
*/
#ifndef IUTEST_EXPECT_TRUE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_TRUE(...)                 IUTEST_TEST_TRUE((__VA_ARGS__), #__VA_ARGS__, IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_TRUE(v)                   IUTEST_TEST_TRUE(v, #v, IUTEST_EXPECT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   FALSE テスト
 * @details v が偽であることを検証します
*/
#ifndef IUTEST_EXPECT_FALSE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_FALSE(...)                IUTEST_TEST_FALSE((__VA_ARGS__), #__VA_ARGS__, IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_FALSE(v)                  IUTEST_TEST_FALSE(v, #v, IUTEST_EXPECT_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   NULL テスト
 * @details v が NULL であることを検証します
*/
#ifndef IUTEST_EXPECT_NULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_NULL(...)                 IUTEST_TEST_NULL((__VA_ARGS__), IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_NULL(v)                   IUTEST_TEST_NULL(v, IUTEST_EXPECT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   NOT NULL テスト
 * @details v が NULL でないことを検証します
*/
#ifndef IUTEST_EXPECT_NOTNULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_NOTNULL(...)              IUTEST_TEST_NOTNULL((__VA_ARGS__), IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_NOTNULL(v)                IUTEST_TEST_NOTNULL(v, IUTEST_EXPECT_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   アドレス一致 テスト
 * @details v1 と v2 のアドレスが同じであることを検証します
*/
#ifndef IUTEST_EXPECT_SAME
#  define IUTEST_EXPECT_SAME(v1, v2)                IUTEST_TEST_SAME(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_FLOAT_EQ
#  define IUTEST_EXPECT_FLOAT_EQ(expected, actual)  IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_DOUBLE_EQ
#  define IUTEST_EXPECT_DOUBLE_EQ(expected, actual) IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif

#if IUTEST_HAS_LONG_DOUBLE
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   long double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_LONG_DOUBLE_EQ
#  define IUTEST_EXPECT_LONG_DOUBLE_EQ(expected, actual)    \
    IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   std::complex の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_EXPECT_COMPLEX_EQ
#  define IUTEST_EXPECT_COMPLEX_EQ(expected, actual)    \
    IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   ２値の差の範囲 テスト
 * @param   v1      = 値1
 * @param   v2      = 値2
 * @param   abs_v   = v1 と v2 の差分の期待値
*/
#ifndef IUTEST_EXPECT_NEAR
#  define IUTEST_EXPECT_NEAR(v1, v2, abs_v)         IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   文字列の一致 テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_EXPECT_STREQ
#  define IUTEST_EXPECT_STREQ(expected_str, actual_str) \
    IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   文字列の不一致 テスト
 * @details v1 と v2 文字列が異なることを検証します
*/
#ifndef IUTEST_EXPECT_STRNE
#  define   IUTEST_EXPECT_STRNE(v1, v2)             IUTEST_TEST_STRNE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   文字列の一致（大文字小文字区別なし） テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_EXPECT_STRCASEEQ
#  define   IUTEST_EXPECT_STRCASEEQ(expected_str, actual_str)   \
    IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   文字列の不一致（大文字小文字区別なし） テスト
 * @details v1 と v2 文字列が異なることを検証します（大文字小文字区別なし）
*/
#ifndef IUTEST_EXPECT_STRCASENE
#  define   IUTEST_EXPECT_STRCASENE(v1, v2)         IUTEST_TEST_STRCASENE(v1, v2, IUTEST_EXPECT_FAILURE)
#endif

#if defined(IUTEST_OS_WINDOWS)

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   HRESULT の成功 テスト
 * @details HRESULT が成功であることを検証します
*/
#ifndef IUTEST_EXPECT_HRESULT_SUCCEEDED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_HRESULT_SUCCEEDED(...)    IUTEST_TEST_HRESULT_SUCCEEDED((__VA_ARGS__), IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_HRESULT_SUCCEEDED(hr)     IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_EXPECT_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_EXPECT_
 * @brief   HRESULT の失敗 テスト
 * @details HRESULT が失敗であることを検証します
*/
#ifndef IUTEST_EXPECT_HRESULT_FAILED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_EXPECT_HRESULT_FAILED(...)       IUTEST_TEST_HRESULT_FAILED((__VA_ARGS__), IUTEST_EXPECT_FAILURE)
#  else
#    define IUTEST_EXPECT_HRESULT_FAILED(hr)        IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_EXPECT_FAILURE)
#  endif
#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   throw テスト
 * @details statement が expected_exception を throw することを検証します
 * @param   statement   = ステートメント
 * @param   expected_exception = 期待する例外
*/
#ifndef IUTEST_EXPECT_THROW
#  define IUTEST_EXPECT_THROW(statement, expected_exception)    \
    IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   throw value == テスト
 * @details statement が expected_exception を throw し、その値が expected_value と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_value      = 期待値
*/
#ifndef IUTEST_EXPECT_THROW_VALUE_EQ
#  define IUTEST_EXPECT_THROW_VALUE_EQ(statement, expected_exception, expected_value)   \
    IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_value, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   throw value != テスト
 * @details statement が expected_exception を throw し、その値が v と等しくないことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   v                   = 値
*/
#ifndef IUTEST_EXPECT_THROW_VALUE_NE
#  define IUTEST_EXPECT_THROW_VALUE_NE(statement, expected_exception, v)    \
    IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, v, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   throw value 文字列一致 テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_EXPECT_THROW_VALUE_STREQ
#  define IUTEST_EXPECT_THROW_VALUE_STREQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_str, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   throw value 文字列一致（大文字小文字区別なし） テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します（大文字小文字区別なし）
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_EXPECT_THROW_VALUE_STRCASEEQ
#  define IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_str, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   any throw テスト
 * @details statement が何らかの例外を投げることを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_EXPECT_ANY_THROW
#  define IUTEST_EXPECT_ANY_THROW(statement)        IUTEST_TEST_ANY_THROW_(statement, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   no throw テスト
 * @details statement が例外を投げないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_EXPECT_NO_THROW
#  define IUTEST_EXPECT_NO_THROW(statement)         IUTEST_TEST_NO_THROW_(statement, IUTEST_EXPECT_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   no new failure テスト
 * @details statement で失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_EXPECT_NO_FAILURE
#  define IUTEST_EXPECT_NO_FAILURE(statement)       IUTEST_TEST_NO_FAILURE_(statement, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   no new fatal failure テスト
 * @details statement で致命的な失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_EXPECT_NO_FATAL_FAILURE
#  define IUTEST_EXPECT_NO_FATAL_FAILURE(statement) IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   明示的な失敗
 * @details 明示的に致命的でない失敗を報告します
*/
#ifndef IUTEST_EXPECT_FAIL
#  define IUTEST_EXPECT_FAIL()                      IIUT_ADD_FAILURE()
#endif

/**
 * @ingroup IUTEST_EXPECT_
 * @brief   明示的な失敗
 * @details 明示的に致命的でない失敗を報告します
*/
#ifndef IUTEST_EXPECT_FAIL_AT
#  define IUTEST_EXPECT_FAIL_AT(file, line)         IIUT_ADD_FAILURE_AT(file, line)
#endif


/**
 * @ingroup     IUTEST_ASSERTION_
 * @{
*/

/**
 * @defgroup    IUTEST_INFORM_  INFORM
 * @brief       警告フレーバー
 * @details     失敗した場合でも、テスト失敗として記録しません。また、テストは続行します。
*/

/**
 * @}
*/

/**
 * @ingroup IUTEST_INFORM_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_INFORM
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM(...)                      IUTEST_TEST_EXPRESSION_((__VA_ARGS__), true, IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM(expression)               IUTEST_TEST_EXPRESSION_(expression, true, IUTEST_INFORM_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_INFORM_NOT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_NOT(...)                  IUTEST_TEST_EXPRESSION_((__VA_ARGS__), false, IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_NOT(expression)           IUTEST_TEST_EXPRESSION_(expression, false, IUTEST_INFORM_FAILURE)
#  endif
#endif

#if IUTEST_HAS_MATCHERS
/**
 * @ingroup IUTEST_INFORM_
 * @brief   matcher テスト
 * @param   actual  = 検査対象
 * @param   matcher = matcher
*/
#ifndef IUTEST_INFORM_THAT
#  define IUTEST_INFORM_THAT(actual, matcher)       IUTEST_TEST_THAT(actual, matcher, IUTEST_INFORM_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   == テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_EQ
#  define   IUTEST_INFORM_EQ(expected, actual)      IUTEST_TEST_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   != テスト（浮動小数点数は誤差考慮）
 * @details actual が expected と等しいことを検証します
 *          浮動小数点数の場合、誤差を考慮した FLOAT_EQ/DOUBLE_EQ での検証になります。
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_ALMOST_EQ
#  define IUTEST_INFORM_ALMOST_EQ(expected, actual) IUTEST_TEST_ALMOST_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   != テスト
 * @details v1 と v2 が等しくないことを検証します
*/
#ifndef IUTEST_INFORM_NE
#  define IUTEST_INFORM_NE(v1, v2)                  IUTEST_TEST_NE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   <= テスト
 * @details v1 <= v2 が成り立つことを検証します
*/
#ifndef IUTEST_INFORM_LE
#  define IUTEST_INFORM_LE(v1, v2)                  IUTEST_TEST_LE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   < テスト
 * @details v1 < v2 が成り立つことを検証します
*/
#ifndef IUTEST_INFORM_LT
#  define IUTEST_INFORM_LT(v1, v2)                  IUTEST_TEST_LT(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   >= テスト
 * @details v1 >= v2 が成り立つことを検証します
*/
#ifndef IUTEST_INFORM_GE
#  define IUTEST_INFORM_GE(v1, v2)                  IUTEST_TEST_GE(v1, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   \> テスト
 * @details v1 > v2 が成り立つことを検証します
*/
#ifndef IUTEST_INFORM_GT
#  define IUTEST_INFORM_GT(v1, v2)                  IUTEST_TEST_GT(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   TRUE テスト
 * @details v が真であることを検証します
*/
#ifndef IUTEST_INFORM_TRUE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_TRUE(...)                 IUTEST_TEST_TRUE((__VA_ARGS__), #__VA_ARGS__, IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_TRUE(v)                   IUTEST_TEST_TRUE(v, #v, IUTEST_INFORM_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   FALSE テスト
 * @details v が偽であることを検証します
*/
#ifndef IUTEST_INFORM_FALSE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_FALSE(...)                IUTEST_TEST_FALSE((__VA_ARGS__), #__VA_ARGS__, IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_FALSE(v)                  IUTEST_TEST_FALSE(v, #v, IUTEST_INFORM_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   NULL テスト
 * @details v が NULL であることを検証します
*/
#ifndef IUTEST_INFORM_NULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_NULL(...)                 IUTEST_TEST_NULL((__VA_ARGS__), IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_NULL(v)                   IUTEST_TEST_NULL(v, IUTEST_INFORM_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   NOT NULL テスト
 * @details v が NULL でないことを検証します
*/
#ifndef IUTEST_INFORM_NOTNULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_NOTNULL(...)              IUTEST_TEST_NOTNULL((__VA_ARGS__), IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_NOTNULL(v)                IUTEST_TEST_NOTNULL(v, IUTEST_INFORM_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   アドレス一致 テスト
 * @details v1 と v2 のアドレスが同じであることを検証します
*/
#ifndef IUTEST_INFORM_SAME
#  define IUTEST_INFORM_SAME(v1, v2)                IUTEST_TEST_SAME(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_FLOAT_EQ
#  define IUTEST_INFORM_FLOAT_EQ(expected, actual)  IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_DOUBLE_EQ
#  define IUTEST_INFORM_DOUBLE_EQ(expected, actual) IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif

#if IUTEST_HAS_LONG_DOUBLE
/**
 * @ingroup IUTEST_INFORM_
 * @brief   long double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_LONG_DOUBLE_EQ
#  define IUTEST_INFORM_LONG_DOUBLE_EQ(expected, actual)    \
    IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_INFORM_COMPLEX_EQ
#  define IUTEST_INFORM_COMPLEX_EQ(expected, actual)    \
    IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   ２値の差の範囲 テスト
 * @param   v1      = 値1
 * @param   v2      = 値2
 * @param   abs_v   = v1 と v2 の差分の期待値
*/
#ifndef IUTEST_INFORM_NEAR
#  define IUTEST_INFORM_NEAR(v1, v2, abs_v)         IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   文字列の一致 テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_INFORM_STREQ
#  define IUTEST_INFORM_STREQ(expected_str, actual_str) \
    IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   文字列の不一致 テスト
 * @details v1 と v2 文字列が異なることを検証します
*/
#ifndef IUTEST_INFORM_STRNE
#  define IUTEST_INFORM_STRNE(v1, v2)               IUTEST_TEST_STRNE(v1, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   文字列の一致（大文字小文字区別なし） テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_INFORM_STRCASEEQ
#  define IUTEST_INFORM_STRCASEEQ(expected_str, actual_str) \
    IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   文字列の不一致（大文字小文字区別なし） テスト
 * @details v1 と v2 文字列が異なることを検証します（大文字小文字区別なし）
*/
#ifndef IUTEST_INFORM_STRCASENE
#  define IUTEST_INFORM_STRCASENE(v1, v2)           IUTEST_TEST_STRCASENE(v1, v2, IUTEST_INFORM_FAILURE)
#endif

#if defined(IUTEST_OS_WINDOWS)

/**
 * @ingroup IUTEST_INFORM_
 * @brief   HRESULT の成功 テスト
 * @details HRESULT が成功であることを検証します
*/
#ifndef IUTEST_INFORM_HRESULT_SUCCEEDED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_HRESULT_SUCCEEDED(...)    IUTEST_TEST_HRESULT_SUCCEEDED((__VA_ARGS__), IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_HRESULT_SUCCEEDED(hr)     IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_INFORM_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_INFORM_
 * @brief   HRESULT の失敗 テスト
 * @details HRESULT が失敗であることを検証します
*/
#ifndef IUTEST_INFORM_HRESULT_FAILED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_INFORM_HRESULT_FAILED(...)       IUTEST_TEST_HRESULT_FAILED((__VA_ARGS__), IUTEST_INFORM_FAILURE)
#  else
#    define IUTEST_INFORM_HRESULT_FAILED(hr)        IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_INFORM_FAILURE)
#  endif
#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup IUTEST_INFORM_
 * @brief   throw テスト
 * @details statement が expected_exception を throw することを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
*/
#ifndef IUTEST_INFORM_THROW
#  define IUTEST_INFORM_THROW(statement, expected_exception)    \
    IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   throw value == テスト
 * @details statement が expected_exception を throw し、その値が expected_value と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_value      = 期待値
*/
#ifndef IUTEST_INFORM_THROW_VALUE_EQ
#  define IUTEST_INFORM_THROW_VALUE_EQ(statement, expected_exception, expected_value)   \
    IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_value, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   throw value != テスト
 * @details statement が expected_exception を throw し、その値が v と等しくないことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   v                   = 値
*/
#ifndef IUTEST_INFORM_THROW_VALUE_NE
#  define IUTEST_INFORM_THROW_VALUE_NE(statement, expected_exception, v)    \
    IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, v, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   throw value 文字列一致 テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_INFORM_THROW_VALUE_STREQ
#  define IUTEST_INFORM_THROW_VALUE_STREQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_str, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   throw value 文字列一致（大文字小文字区別なし） テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します（大文字小文字区別なし）
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_INFORM_THROW_VALUE_STRCASEEQ
#  define IUTEST_INFORM_THROW_VALUE_STRCASEEQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_str, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   any throw テスト
 * @details statement が何らかの例外を投げることを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_INFORM_ANY_THROW
#  define IUTEST_INFORM_ANY_THROW(statement)        IUTEST_TEST_ANY_THROW_(statement, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   no throw テスト
 * @details statement が例外を投げないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_INFORM_NO_THROW
#  define IUTEST_INFORM_NO_THROW(statement)         IUTEST_TEST_NO_THROW_(statement, IUTEST_INFORM_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   no new failure テスト
 * @details statement で失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_INFORM_NO_FAILURE
#  define IUTEST_INFORM_NO_FAILURE(statement)       IUTEST_TEST_NO_FAILURE_(statement, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup IUTEST_INFORM_
 * @brief   no new fatal failure テスト
 * @details statement で致命的な失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_INFORM_NO_FATAL_FAILURE
#  define IUTEST_INFORM_NO_FATAL_FAILURE(statement) IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_INFORM_FAILURE)
#endif

/**
 * @ingroup     IUTEST_ASSERTION_
 * @{
*/

/**
 * @defgroup    IUTEST_ASSUME_  ASSUME
 * @brief       前提条件フレーバー
 * @details     テストの前提検証用マクロです。失敗した場合、以降の処理を行わずテストはスキップされます。
*/

/**
 * @}
*/

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_ASSUME
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME(...)                      IUTEST_TEST_EXPRESSION_((__VA_ARGS__), true, IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME(expression)               IUTEST_TEST_EXPRESSION_(expression, true, IUTEST_ASSUME_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   式アサーション
 * @param   expression  = 式
*/
#ifndef IUTEST_ASSUME_NOT
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_NOT(...)                  IUTEST_TEST_EXPRESSION_((__VA_ARGS__), false, IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_NOT(expression)           IUTEST_TEST_EXPRESSION_(expression, false, IUTEST_ASSUME_FAILURE)
#  endif
#endif

#if IUTEST_HAS_MATCHERS

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   matcher テスト
 * @param   actual  = 検査対象
 * @param   matcher = matcher
*/
#ifndef IUTEST_ASSUME_THAT
#  define IUTEST_ASSUME_THAT(actual, matcher)       IUTEST_TEST_THAT(actual, matcher, IUTEST_ASSUME_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   == テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_EQ
#  define IUTEST_ASSUME_EQ(expected, actual)        IUTEST_TEST_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   != テスト（浮動小数点数は誤差考慮）
 * @details actual が expected と等しいことを検証します
 *          浮動小数点数の場合、誤差を考慮した FLOAT_EQ/DOUBLE_EQ での検証になります。
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_ALMOST_EQ
#  define IUTEST_ASSUME_ALMOST_EQ(expected, actual) IUTEST_TEST_ALMOST_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   != テスト
 * @details v1 と v2 が等しくないことを検証します
*/
#ifndef IUTEST_ASSUME_NE
#  define IUTEST_ASSUME_NE(v1, v2)                  IUTEST_TEST_NE(v1, v2, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   <= テスト
 * @details v1 <= v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSUME_LE
#  define   IUTEST_ASSUME_LE(v1, v2)                IUTEST_TEST_LE(v1, v2, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   < テスト
 * @details v1 < v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSUME_LT
#  define IUTEST_ASSUME_LT(v1, v2)                  IUTEST_TEST_LT(v1, v2, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   >= テスト
 * @details v1 >= v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSUME_GE
#  define IUTEST_ASSUME_GE(v1, v2)                  IUTEST_TEST_GE(v1, v2, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   \> テスト
 * @details v1 > v2 が成り立つことを検証します
*/
#ifndef IUTEST_ASSUME_GT
#  define IUTEST_ASSUME_GT(v1, v2)                  IUTEST_TEST_GT(v1, v2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   TRUE テスト
 * @details v が真であることを検証します
*/
#ifndef IUTEST_ASSUME_TRUE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_TRUE(...)                 IUTEST_TEST_TRUE((__VA_ARGS__), #__VA_ARGS__, IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_TRUE(v)                   IUTEST_TEST_TRUE(v, #v, IUTEST_ASSUME_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   FALSE テスト
 * @details v が偽であることを検証します
*/
#ifndef IUTEST_ASSUME_FALSE
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_FALSE(...)                IUTEST_TEST_FALSE((__VA_ARGS__), #__VA_ARGS__, IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_FALSE(v)                  IUTEST_TEST_FALSE(v, #v, IUTEST_ASSUME_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   NULL テスト
 * @details v が NULL であることを検証します
*/
#ifndef IUTEST_ASSUME_NULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_NULL(...)                 IUTEST_TEST_NULL((__VA_ARGS__), IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_NULL(v)                   IUTEST_TEST_NULL(v, IUTEST_ASSUME_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   NOT NULL テスト
 * @details v が NULL でないことを検証します
*/
#ifndef IUTEST_ASSUME_NOTNULL
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_NOTNULL(...)              IUTEST_TEST_NOTNULL((__VA_ARGS__), IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_NOTNULL(v)                IUTEST_TEST_NOTNULL(v, IUTEST_ASSUME_FAILURE)
#  endif
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   アドレス一致 テスト
 * @details v1 と v2 のアドレスが同じであることを検証します
*/
#ifndef IUTEST_ASSUME_SAME
#  define IUTEST_ASSUME_SAME(v1, v2)                IUTEST_TEST_SAME(v1, v2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_FLOAT_EQ
#  define IUTEST_ASSUME_FLOAT_EQ(expected, actual)  IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_DOUBLE_EQ
#  define IUTEST_ASSUME_DOUBLE_EQ(expected, actual) IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

#if IUTEST_HAS_LONG_DOUBLE
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   long double の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_LONG_DOUBLE_EQ
#  define IUTEST_ASSUME_LONG_DOUBLE_EQ(expected, actual)    \
    IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   float の比較 テスト
 * @param   expected    = 期待値
 * @param   actual      = 検査対象
*/
#ifndef IUTEST_ASSUME_COMPLEX_EQ
#  define IUTEST_ASSUME_COMPLEX_EQ(expected, actual)    \
    IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   ２値の差の範囲 テスト
 * @param   v1      = 値1
 * @param   v2      = 値2
 * @param   abs_v   = v1 と v2 の差分の期待値
*/
#ifndef IUTEST_ASSUME_NEAR
#  define IUTEST_ASSUME_NEAR(v1, v2, abs_v)         IUTEST_TEST_NEAR(v1, v2, abs_v, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   文字列の一致 テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_ASSUME_STREQ
#  define IUTEST_ASSUME_STREQ(expected_str, actual_str) \
    IUTEST_TEST_STREQ(expected_str, actual_str, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   文字列の不一致 テスト
 * @details v1 と v2 文字列が異なることを検証します
*/
#ifndef IUTEST_ASSUME_STRNE
#  define IUTEST_ASSUME_STRNE(v1, v2)               IUTEST_TEST_STRNE(v1, v2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   文字列の一致（大文字小文字区別なし） テスト
 * @param   expected_str    = 期待値
 * @param   actual_str      = 検査対象
*/
#ifndef IUTEST_ASSUME_STRCASEEQ
#  define IUTEST_ASSUME_STRCASEEQ(expected_str, actual_str) \
    IUTEST_TEST_STRCASEEQ(expected_str, actual_str, IUTEST_ASSUME_FAILURE)
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   文字列の不一致（大文字小文字区別なし） テスト
 * @details v1 と v2 文字列が異なることを検証します（大文字小文字区別なし）
*/
#ifndef IUTEST_ASSUME_STRCASENE
#  define IUTEST_ASSUME_STRCASENE(v1, v2)           IUTEST_TEST_STRCASENE(v1, v2, IUTEST_ASSUME_FAILURE)
#endif

#if defined(IUTEST_OS_WINDOWS)

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   HRESULT の成功 テスト
 * @details HRESULT が成功であることを検証します
*/
#ifndef IUTEST_ASSUME_HRESULT_SUCCEEDED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_HRESULT_SUCCEEDED(...)    IUTEST_TEST_HRESULT_SUCCEEDED((__VA_ARGS__), IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_HRESULT_SUCCEEDED(hr)     IUTEST_TEST_HRESULT_SUCCEEDED(hr, IUTEST_ASSUME_FAILURE)
#  endif
#endif
/**
 * @ingroup IUTEST_ASSUME_
 * @brief   HRESULT の失敗 テスト
 * @details HRESULT が失敗であることを検証します
*/
#ifndef IUTEST_ASSUME_HRESULT_FAILED
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_ASSUME_HRESULT_FAILED(...)       IUTEST_TEST_HRESULT_FAILED((__VA_ARGS__), IUTEST_ASSUME_FAILURE)
#  else
#    define IUTEST_ASSUME_HRESULT_FAILED(hr)        IUTEST_TEST_HRESULT_FAILED(hr, IUTEST_ASSUME_FAILURE)
#  endif
#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   throw テスト
 * @details statement が expected_exception を throw することを検証します
 * @param   statement   = ステートメント
 * @param   expected_exception = 期待する例外
*/
#ifndef IUTEST_ASSUME_THROW
#  define IUTEST_ASSUME_THROW(statement, expected_exception)    \
    IUTEST_TEST_THROW_(statement, expected_exception, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   throw value == テスト
 * @details statement が expected_exception を throw し、その値が expected_value と等しいことを検証します
 * @param   statement   = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_value      = 期待値
*/
#ifndef IUTEST_ASSUME_THROW_VALUE_EQ
#  define IUTEST_ASSUME_THROW_VALUE_EQ(statement, expected_exception, expected_value)   \
    IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_value, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   throw value != テスト
 * @details statement が expected_exception を throw し、その値が v と等しくないことを検証します
 * @param   statement   = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   v           = 値
*/
#ifndef IUTEST_ASSUME_THROW_VALUE_NE
#  define IUTEST_ASSUME_THROW_VALUE_NE(statement, expected_exception, v)    \
    IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, v, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   throw value 文字列一致 テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_ASSUME_THROW_VALUE_STREQ
#  define IUTEST_ASSUME_THROW_VALUE_STREQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_str, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   throw value 文字列一致（大文字小文字区別なし） テスト
 * @details statement が expected_exception を throw し、その文字列が expected_str と等しいことを検証します（大文字小文字区別なし）
 * @param   statement           = ステートメント
 * @param   expected_exception  = 期待する例外
 * @param   expected_str        = 期待文字列
*/
#ifndef IUTEST_ASSUME_THROW_VALUE_STRCASEEQ
#  define IUTEST_ASSUME_THROW_VALUE_STRCASEEQ(statement, expected_exception, expected_str)  \
    IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_str, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   any throw テスト
 * @details statement が何らかの例外を投げることを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSUME_ANY_THROW
#  define IUTEST_ASSUME_ANY_THROW(statement)        IUTEST_TEST_ANY_THROW_(statement, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   no throw テスト
 * @details statement が例外を投げないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSUME_NO_THROW
#  define IUTEST_ASSUME_NO_THROW(statement)         IUTEST_TEST_NO_THROW_(statement, IUTEST_ASSUME_FAILURE)
#endif

#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   no new failure テスト
 * @details statement で失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSUME_NO_FAILURE
#  define IUTEST_ASSUME_NO_FAILURE(statement)       IUTEST_TEST_NO_FAILURE_(statement, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup IUTEST_ASSUME_
 * @brief   no new fatal failure テスト
 * @details statement で致命的な失敗がないことを検証します
 * @param   statement = ステートメント
*/
#ifndef IUTEST_ASSUME_NO_FATAL_FAILURE
#  define IUTEST_ASSUME_NO_FATAL_FAILURE(statement) IUTEST_TEST_NO_FATAL_FAILURE_(statement, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @brief iutest root namespace
*/
namespace iutest
{

//======================================================================
// class
/**
 * @brief   単体テスト起点
*/
class UnitTestSource
{
public:
    /** @private */
    static UnitTestSource& GetInstance() { static UnitTestSource inst; return inst; }

private:
    UnitTestSource()
    {
#if defined(_IUTEST_DEBUG)
        detail::iuDebugInitialize();
#else
        IUTEST_UNUSED_VAR(&detail::iuDebugInitialize);
        IUTEST_UNUSED_VAR(&detail::iuDebugBreakAlloc);
#endif
        TestEnv::event_listeners().set_default_result_printer(new DefaultResultPrintListener());
    }

public:
    /** @private */
    ~UnitTestSource()
    {
        TestEnv::event_listeners().set_default_result_printer(NULL);
        TestEnv::event_listeners().set_default_xml_generator(NULL);
    }

public:
    /**
     * @brief   初期化
    */
    void Initialize()
    {
        UnitTest::instance().Initialize();
    }

    /**
     * @brief   テストの実行
    */
    int Run()
    {
        SetUpDefaultListener();
        return UnitTest::instance().Run();
    }

public:
    void SetUpDefaultXmlListener()
    {
        if( TestEnv::is_output_option_dirty() )
        {
            if( TestEnv::has_output_option() )
            {
                TestEnv::flush_output_option();

                do
                {
#if defined(__WANDBOX__)
                    if( StderrXmlGeneratorListener::SetUp() )
                    {
                        break;
                    }
                    if( StderrJunitXmlGeneratorListener::SetUp() )
                    {
                        break;
                    }
#else
                    if( DefaultXmlGeneratorListener::SetUp() )
                    {
                        break;
                    }
                    if( JunitXmlGeneratorListener::SetUp() )
                    {
                        break;
                    }
#endif
                    IUTEST_LOG_(WARNING) << "unrecognized output format \"" << TestEnv::get_output_option() << "\" ignored.";
                } while( detail::AlwaysFalse() );
            }
            else
            {
                TestEnv::event_listeners().Release(TestEnv::event_listeners().default_xml_generator());
            }
        }
    }

private:
    void SetUpDefaultListener()
    {
        SetUpDefaultXmlListener();
#if IUTEST_HAS_STREAM_RESULT
        StreamResultListener::SetUp();
#endif
    }
};

//======================================================================
// function
namespace detail
{

template<typename T>
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, T argv)
{
    UnitTestSource::GetInstance().Initialize();
    TestEnv::ParseCommandLine(pargc, argv);
    TestEnv::LoadFlagFile();
    UnitTestSource::GetInstance().SetUpDefaultXmlListener();
}

}   // end of namespace detail

/**
 * @brief   初期化
 * @details コマンドラインオプションの解析をします。
 *          使用した引数は削除され pargc, argv を書き換えます
*/
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, char** argv)      { detail::InitIrisUnitTest(pargc, argv); }
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, wchar_t** argv)   { detail::InitIrisUnitTest(pargc, argv); }      //!< @overload
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const char** argv)    { detail::InitIrisUnitTest(pargc, argv); }  //!< @overload
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, const wchar_t** argv) { detail::InitIrisUnitTest(pargc, argv); }  //!< @overload
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest() { detail::InitIrisUnitTest<char**>(NULL, NULL); }   //!< @overload

#if IUTEST_HAS_NULLPTR
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(int* pargc, ::std::nullptr_t) { detail::InitIrisUnitTest<char**>(pargc, NULL); }  //!< @overload
#endif

/** @overload */
template<typename CharType>
inline void IUTEST_ATTRIBUTE_UNUSED_ InitIrisUnitTest(::std::vector< ::std::basic_string<CharType> >& argv)
{
    UnitTestSource::GetInstance().Initialize();
    TestEnv::ParseCommandLine(argv);
    TestEnv::LoadFlagFile();
    UnitTestSource::GetInstance().SetUpDefaultXmlListener();
}

/**
 * @brief   グローバル環境セットクラスの追加
 * @param [in]  env = 環境セットクラスアドレス
 * @return  登録されたクラスアドレス
 * @note    メモリ管理はしない。new した Environment はユーザーが解放する
*/
inline Environment* IUTEST_ATTRIBUTE_UNUSED_ AddGlobalTestEnvironment(Environment* env)
{
    return TestEnv::AddGlobalTestEnvironment(env);
}

}   // end of namespace iutest

#if defined(IUTEST_USE_GTEST)
#  include "gtest/iutest_switch.hpp"
#endif

#include "iutest_util.hpp"  // IWYU pragma: export

#if defined(IUTEST_USE_MAIN)
#  include "internal/iutest_default_main.hpp"
#endif

IUTEST_PRAGMA_IUTEST_WARN_DISABLE_END()

#endif // INCG_IRIS_IUTEST_HPP_
