//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_config.hpp
 * @brief       iris unit test config
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CONFIG_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_
#define INCG_IRIS_IUTEST_CONFIG_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_

//======================================================================
// include

/**
 * @defgroup    IUTEST_CONFIG   IUTEST_CONFIG
 * @brief       設定マクロ
 * @note        ユーザーが事前定義することで変更可能
 * @{
*/

//! Library を使うかどうか
#if !defined(IUTEST_HAS_LIB)
#  if   defined(IUTEST_NO_LIB)
#    define IUTEST_HAS_LIB          0
#  elif defined(IUTEST_USE_LIB) || defined(IUTEST_AUTO_LINK)
#    define IUTEST_HAS_LIB          1
#  endif
#endif

#if !defined(IUTEST_HAS_LIB)
#  define IUTEST_HAS_LIB            0
#endif

/**
 * @defgroup    IUTEST_CONFIG_OUTPUT    OUTPUT
 * @brief       出力関係 CONFIG
 * @{
*/

#if !defined(IUTEST_VPRINTF)
#  define IUTEST_VPRINTF(f, a)  vprintf(f, a)   //!< vprintf 呼び出しマクロ
#endif

#if !defined(IUTEST_HAS_REPORT_SKIPPED)
#  define IUTEST_HAS_REPORT_SKIPPED     1       //!< xml 出力に skipped タグを含めるかどうか
#endif

/**
 * @}
*/


/**
 * @defgroup    IUTEST_CONFIG_TEST  TEST
 * @brief       テスト関係 CONFIG
 * @{
*/

#if !defined(IUTEST_HAS_PARAM_METHOD_TEST)
//! パラメタライズ関数コールテストが使用可能かどうか
#  if   !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_PARAM_METHOD_TEST    1
#  else
#    define IUTEST_HAS_PARAM_METHOD_TEST    0
#  endif
#endif

#if !defined(IUTEST_HAS_PARAM_TEST)
#  define IUTEST_HAS_PARAM_TEST         1   //!< 値をパラメータ化したテストが使用可能かどうか
#endif

#if !defined(IUTEST_HAS_TYPED_TEST)
//! 型付けテストが使用可能かどうか
#  if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#    define IUTEST_HAS_TYPED_TEST       1
#  else
#    define IUTEST_HAS_TYPED_TEST       0
#  endif
#endif

#if !defined(IUTEST_HAS_TYPED_TEST_P)
//! 型をパラメータ化したテストが使用可能かどうか
#  if IUTEST_HAS_TYPED_TEST && !defined(IUTEST_NO_VARIADIC_MACROS) \
        && !defined(IUTEST_NO_TEMPLATE_TEMPLATES)
#    define IUTEST_HAS_TYPED_TEST_P 1
#  else
#    define IUTEST_HAS_TYPED_TEST_P 0
#  endif
#endif

#if !defined(IUTEST_TYPED_TEST_P_STRICT)
//! Typed Test のより厳しい構文チェックを行うかどうか
#  define IUTEST_TYPED_TEST_P_STRICT    1
#endif

#if !defined(IUTEST_HAS_IGNORE_TEST)
/**
 * @brief   コンパイルが通らなくてもよいテスト生成マクロが使用可能かどうか
 * @deprecated
*/
#  if defined(IUTEST_NO_TWO_PHASE_NAME_LOOKUP)
#    define IUTEST_HAS_IGNORE_TEST  1
#  else
#    define IUTEST_HAS_IGNORE_TEST  0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHERS)
/**
 * @brief   IUTEST_*_THAT が使用可能かどうか
*/
#  if !defined(IUTEST_NO_SFINAE) && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING) \
        && !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#    define IUTEST_HAS_MATCHERS     1
#  else
#    define IUTEST_HAS_MATCHERS     0
#  endif
#endif

#if !defined(IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE)
/**
 * @brief   式アサーションで算術演算子の展開をサポートするかどうか
 * @deprecated
*/
#  if 1 // IUTEST_HAS_DECLTYPE
#    define IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE  1
#  else
#    define IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE  0
#  endif
#endif

#if !defined(IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE)
/**
 * @brief   式アサーションでビット演算子の展開をサポートするかどうか
*/
#  if IUTEST_HAS_DECLTYPE
#    define IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE     1
#  else
#    define IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE     0
#  endif
#endif

#if !defined(IUTEST_HAS_VALUESGEN)
//! ::iutest::ValuesGen が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST
#    define IUTEST_HAS_VALUESGEN    1
#  else
#    define IUTEST_HAS_VALUESGEN    0
#  endif
#endif

#if !defined(IUTEST_HAS_RANDOMVALUES)
//! ::iutest::RandomValues が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_VALUESGEN
#    define IUTEST_HAS_RANDOMVALUES 1
#  else
#    define IUTEST_HAS_RANDOMVALUES 0
#  endif
#endif

#if IUTEST_HAS_RANDOMVALUES
#  if !IUTEST_HAS_PARAM_TEST || !IUTEST_HAS_VALUESGEN
#    undef IUTEST_HAS_RANDOMVALUES
#    define IUTEST_HAS_RANDOMVALUES 0
#  endif
#endif

#if !defined(IUTEST_HAS_COMBINE)
//! ::iutest::Combine が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_COMBINE      1
#  endif
#else
#  if IUTEST_HAS_COMBINE && !IUTEST_HAS_TUPLE
#    undef IUTEST_HAS_COMBINE
#  endif
#endif

#if !defined(IUTEST_HAS_COMBINE)
#  define IUTEST_HAS_COMBINE        0
#endif

#if !defined(IUTEST_HAS_PAIRWISE)
//! ::iutest::Pairwise が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_PAIRWISE     1
#  endif
#else
#  if IUTEST_HAS_PAIRWISE && !IUTEST_HAS_TUPLE
#    undef IUTEST_HAS_PAIRWISE
#  endif
#endif

#if !defined(IUTEST_HAS_PAIRWISE)
#  define IUTEST_HAS_PAIRWISE       0
#endif

#if !defined(IUTEST_HAS_CONCAT)
//! ::iutest::Concat が使用可能かどうか
# define IUTEST_HAS_CONCAT          1
#endif

#if !defined(IUTEST_HAS_CSVPARAMS)
//! ::iutest::CSV が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_STRINGSTREAM
#    define IUTEST_HAS_CSVPARAMS    1
#  else
#    define IUTEST_HAS_CSVPARAMS    0
#  endif
#endif

#if !defined(IUTEST_HAS_VARIADIC_VALUES)
//! 可変長引数に対応した ::iutest::Values が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_VARIADIC_TUPLES
#    define IUTEST_HAS_VARIADIC_VALUES  1
#  else
#    define IUTEST_HAS_VARIADIC_VALUES  0
#  endif
#endif

#if !defined(IUTEST_HAS_VARIADIC_COMBINE)
//! 可変長引数に対応した ::iutest::Combine が使用可能かどうか
#  if IUTEST_HAS_COMBINE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_VARIADIC_TUPLES
#    define IUTEST_HAS_VARIADIC_COMBINE 1
#  else
#    define IUTEST_HAS_VARIADIC_COMBINE 0
#  endif
#endif

#if !defined(IUTEST_HAS_VARIADIC_PAIRWISE)
//! 可変長引数に対応した ::iutest::Pairwise が使用可能かどうか
#  if IUTEST_HAS_PAIRWISE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_VARIADIC_TUPLES
#    define IUTEST_HAS_VARIADIC_PAIRWISE    1
#  else
#    define IUTEST_HAS_VARIADIC_PAIRWISE    0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHER_ELEMENTSARE)
//! ::iutest::matchers::ElementsAre matcher が使用可能かどうか
#  if IUTEST_HAS_TUPLE && !defined(IUTEST_NO_SFINAE)
#    define IUTEST_HAS_MATCHER_ELEMENTSARE      IUTEST_HAS_MATCHERS
#  else
#    define IUTEST_HAS_MATCHER_ELEMENTSARE      0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD)
//! ::iutest::matchers::ElementsAreArrayForward matcher が使用可能かどうか
#  if IUTEST_HAS_TUPLE && !defined(IUTEST_NO_SFINAE)
#    define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD  IUTEST_HAS_MATCHERS
#  else
#    define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD  0
#  endif
#endif

#if !defined(IUTEST_HAS_REGEX)
//! regex が使用可能かどうか
#  if IUTEST_HAS_CXX_HDR_REGEX
#    define IUTEST_HAS_REGEX    1
#  else
#    define IUTEST_HAS_REGEX    0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHER_VARIADIC)
//! matchers が variadic template に対応しているかどうか
#  define IUTEST_HAS_MATCHER_VARIADIC   IUTEST_HAS_VARIADIC_TEMPLATES
#endif

#if !defined(IUTEST_HAS_MATCHER_REGEX)
//! ::iutest::matchers::MatchesRegex, ::iutest::matchers::ContainsRegex matcher が使用可能かどうか
#  if IUTEST_HAS_CXX_HDR_REGEX && IUTEST_HAS_REGEX
#    define IUTEST_HAS_MATCHER_REGEX    IUTEST_HAS_MATCHERS
#  else
#    define IUTEST_HAS_MATCHER_REGEX    0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF)
//! ::iutest::matchers::AllOf, ::iutest::matchers::AnyOf matcher が使用可能かどうか
#  if IUTEST_HAS_TUPLE
#    define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF  IUTEST_HAS_MATCHERS
#  else
#    define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF  0
#  endif
#endif

#if !defined(IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR)
//! Wether ::iutest::matchers::(NanSensitive)(Float|Double)Near is available
#  define IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR 1
#endif

#if !defined(IUTEST_HAS_MATCHER_EACH)
//! Wether ::iutest::matchers::Each is available
#  define IUTEST_HAS_MATCHER_EACH               1
#endif

#if !defined(IUTEST_HAS_MATCHER_POINTWISE)
//! Wether ::iutest::matchers::Pointwise is available
#  define IUTEST_HAS_MATCHER_POINTWISE          1
#endif

#if !defined(IUTEST_HAS_MATCHER_OPTIONAL)
#  define IUTEST_HAS_MATCHER_OPTIONAL           1
#endif

#if !defined(IUTEST_USE_THROW_ON_ASSERTION_FAILURE)
/**
 * @brief   失敗時に例外を throw します。
 * @note    サブ関数にアサーションを記述しても、その時点でテストが中断されるようになります
*/
#  if defined(IUTEST_USE_THROW_ON_ASSERT_FAILURE)
#    define IUTEST_USE_THROW_ON_ASSERTION_FAILURE       IUTEST_USE_THROW_ON_ASSERT_FAILURE
#  else
#    if !defined(IUTEST_NO_VOID_RETURNS)
#      define IUTEST_USE_THROW_ON_ASSERTION_FAILURE     0
#    else
#      define IUTEST_USE_THROW_ON_ASSERTION_FAILURE     1
#    endif
#  endif
#endif

#if !IUTEST_HAS_EXCEPTIONS && IUTEST_USE_THROW_ON_ASSERTION_FAILURE
#  undef IUTEST_USE_THROW_ON_ASSERTION_FAILURE
#  define IUTEST_USE_THROW_ON_ASSERTION_FAILURE         0
#endif

#if !defined(IUTEST_HAS_LAMBDA_STATEMENTS)
//! lambda を使った statements 展開が可能かどうか
#  if IUTEST_HAS_LAMBDA && !defined(IUTEST_NO_LAMBDA_SCOPE_RESOLUTION)
#    define IUTEST_HAS_LAMBDA_STATEMENTS        1
#  else
#    define IUTEST_HAS_LAMBDA_STATEMENTS        0
#  endif
#endif

#if !defined(IUTEST_HAS_SPI_LAMBDA_SUPPORT)
//! spi マクロで lambda を使って変数にアクセス可能かどうか
#  define IUTEST_HAS_SPI_LAMBDA_SUPPORT       IUTEST_HAS_LAMBDA_STATEMENTS
#endif

#if !defined(IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION)
//! 例外アサーションで SEH をキャッチ可能かどうか
#  if IUTEST_HAS_SEH && IUTEST_HAS_LAMBDA_STATEMENTS
#    define IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION  1
#  else
#    define IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION  0
#  endif
#endif

#if !defined(IUTEST_HAS_GENRAND)
#  define IUTEST_HAS_GENRAND        1   //!< テストごとの genrand 関数が使用可能かどうか
#endif

#if !defined(IUTEST_HAS_PACKAGE)
//! パッケージ機能があるかどうか
#  if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
#    define IUTEST_HAS_PACKAGE      1
#  else
#    define IUTEST_HAS_PACKAGE      0
#  endif
#endif

// peep
#if !defined(IUTEST_HAS_PEEP)
//! private メンバーへのアクセスマクロが使用可能かどうか
#  define IUTEST_HAS_PEEP           1
#endif

#if !defined(IUTEST_HAS_PEEP_FUNC)
//! private メンバー関数へのアクセスが可能かどうか
#  if IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_FUNC    IUTEST_HAS_PEEP
#  else
#    define IUTEST_HAS_PEEP_FUNC    0
#  endif
#endif

#if !defined(IUTEST_HAS_PEEP_STATIC_FUNC)
//! private static メンバー関数へのアクセスが可能かどうか
#  if IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_STATIC_FUNC IUTEST_HAS_PEEP
#  else
#    define IUTEST_HAS_PEEP_STATIC_FUNC 0
#  endif
#endif

#if !defined(IUTEST_HAS_PEEP_CLASS)
//! private メンバー関数へのアクセスが可能かどうか
#  if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#    define IUTEST_HAS_PEEP_CLASS   IUTEST_HAS_PEEP
#  else
#    define IUTEST_HAS_PEEP_CLASS   0
#  endif
#endif

#if !defined(IUTEST_HAS_STATIC_ASSERT_TYPEEQ)
//! StaticAssertTypeEq が使用可能かどうか
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#    define IUTEST_HAS_STATIC_ASSERT_TYPEEQ     1
#  else
#    define IUTEST_HAS_STATIC_ASSERT_TYPEEQ     0
#  endif
#endif

#if !defined(IUTEST_HAS_PRINT_TO)
//! PrintTo が使用可能かどうか
#  if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING) \
        && !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
#    define IUTEST_HAS_PRINT_TO     1
#  else
#    define IUTEST_HAS_PRINT_TO     0
#  endif
#endif

#if !defined(IUTEST_HAS_VARIADIC_PRED)
//! 可変長述語アサーションが使用可能かどうか
#  if IUTEST_HAS_VARIADIC_TEMPLATES && !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_VARIADIC_PRED        1
#  else
#    define IUTEST_HAS_VARIADIC_PRED        0
#  endif
#endif

#if !defined(IUTEST_HAS_ASSERTION_RETURN)
//! ::iutest::AssertionReturn が使用可能かどうか
#  if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
#    define IUTEST_HAS_ASSERTION_RETURN     1
#  else
#    define IUTEST_HAS_ASSERTION_RETURN     0
#  endif
#endif

#if !defined(IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT)
//! IUTEST_*_EQ で operator == がないオブジェクトの検証が可能かどうか
#  if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING) \
        && !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
#    define IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT   1
#  else
#    define IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT   0
#  endif
#endif

#if !defined(IUTEST_HAS_TESTNAME_ALIAS)
//! テスト名の別名指定記法が使用できるかどうか
#  if !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_TESTNAME_ALIAS       1
#  else
#    define IUTEST_HAS_TESTNAME_ALIAS       0
#  endif
#endif

#if !defined(IUTEST_HAS_TESTNAME_ALIAS_JP)
//! テスト名の別名に日本語が使用できるかどうか
#  if IUTEST_HAS_TESTNAME_ALIAS && !defined(__CUDACC__) && !defined(IUTEST_OS_NACL)
#    define IUTEST_HAS_TESTNAME_ALIAS_JP    1
#  else
#    define IUTEST_HAS_TESTNAME_ALIAS_JP    0
#  endif
#endif

#if !defined(IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE)
//! テスト名の別名指定の簡易記法が可能かどうか
#  define IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE IUTEST_HAS_TESTNAME_ALIAS
#endif

#if !defined(IUTEST_HAS_AUTOFIXTURE_PARAM_TEST)
//! fixture の自動定義に対応したパラメータ化テストが使用可能かどうか
#  if IUTEST_HAS_IF_EXISTS || !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#    define IUTEST_HAS_AUTOFIXTURE_PARAM_TEST   IUTEST_HAS_PARAM_TEST
#  else
#    define IUTEST_HAS_AUTOFIXTURE_PARAM_TEST   0
#  endif
#endif

#if !defined(IUTEST_HAS_ANY_PARAM_TEST)
//! any を利用した値のパラメータ化テストが使用可能かどうか
#  if IUTEST_HAS_TESTNAME_ALIAS
#    define IUTEST_HAS_ANY_PARAM_TEST       IUTEST_HAS_PARAM_TEST
#  else
#    define IUTEST_HAS_ANY_PARAM_TEST       0
#  endif
#endif

#if !defined(IUTEST_TYPED_TEST_APPEND_TYPENAME)
//! @deprecated
#  define IUTEST_TYPED_TEST_APPEND_TYPENAME     0
#endif

#if !defined(IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME)
//! 型付けテスト名に型名を付けるかどうか
#  define IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME IUTEST_TYPED_TEST_APPEND_TYPENAME
#endif

#if !defined(IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR)
//! 値をパラメータ化したテストのパラメータ名生成が可能かどうか
#  if   !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR  1
#  else
#    define IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR  0
#  endif
#endif

/**
 * @}
*/


/**
 * @defgroup    IUTEST_CONFIG_FILE  FILE
 * @brief       ファイル関係 CONFIG
 * @{
*/

#if !defined(IUTEST_HAS_FOPEN)
#  define IUTEST_HAS_FOPEN          1   //!< fopen が使用可能かどうか
#endif

#if !defined(IUTEST_HAS_FILE_STAT)
#  define IUTEST_HAS_FILE_STAT      0   //!< stat が使用可能かどうか
#endif

#if !defined(IUTEST_HAS_FILENO)
#  define IUTEST_HAS_FILENO         0   //!< fileno が使用可能かどうか
#endif

//! ::std::filesystem を使用するかどうか
#if !defined(IUTEST_USE_CXX_FILESYSTEM)
#  if IUTEST_HAS_STD_FILESYSTEM
#    if defined(_MSC_VER)
#      define IUTEST_USE_CXX_FILESYSTEM 1
#    endif
#  endif
#endif

#if !defined(IUTEST_USE_CXX_FILESYSTEM)
#  define IUTEST_USE_CXX_FILESYSTEM     0
#endif

/**
 * @}
*/


/**
 * @defgroup    IUTEST_CONFIG_TIME  TIME
 * @brief       TIME関係 CONFIG
 * @{
*/

//! time 関数が使用可能かどうか
#if !defined(IUTEST_HAS_CTIME)
#  if defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_CTIME        0
#  else
#    define IUTEST_HAS_CTIME        1
#  endif
#endif

//! gettimeofday 関数が使用可能かどうか
#if !defined(IUTEST_HAS_GETTIMEOFDAY)
#  if IUTEST_HAS_HDR_SYSTIME
#    define IUTEST_HAS_GETTIMEOFDAY 1
#  endif
#endif

#if !defined(IUTEST_HAS_GETTIMEOFDAY)
#  define IUTEST_HAS_GETTIMEOFDAY   0
#endif

//! clock 関数が使用可能かどうか
#if !defined(IUTEST_HAS_CLOCK)
#  if defined(CLOCKS_PER_SEC)
#    define IUTEST_HAS_CLOCK        1
#  endif
#endif

#if !defined(IUTEST_HAS_CLOCK)
#  define IUTEST_HAS_CLOCK          0
#endif

/**
 * @}
*/

/**
 * @defgroup    IUTEST_CONFIG_CODECVT  CODECVT
 * @brief       charcode convert CONFIG
 * @{
*/

//! char16_t printable
#if !defined(IUTEST_HAS_CHAR16_T_PRINTABLE)
#  if defined(_MSC_VER) || IUTEST_HAS_CXX_HDR_CODECVT || IUTEST_HAS_CXX_HDR_CUCHAR
#    define IUTEST_HAS_CHAR16_T_PRINTABLE   IUTEST_HAS_CHAR16_T
#  endif
#endif

#if !defined(IUTEST_HAS_CHAR16_T_PRINTABLE)
#  define IUTEST_HAS_CHAR16_T_PRINTABLE     0
#endif

//! char32_t printable
#if !defined(IUTEST_HAS_CHAR32_T_PRINTABLE)
#  if defined(_MSC_VER) || IUTEST_HAS_CXX_HDR_CODECVT || IUTEST_HAS_CXX_HDR_CUCHAR
#    define IUTEST_HAS_CHAR32_T_PRINTABLE   IUTEST_HAS_CHAR32_T
#  endif
#endif

#if !defined(IUTEST_HAS_CHAR32_T_PRINTABLE)
#  define IUTEST_HAS_CHAR32_T_PRINTABLE     0
#endif

/**
 * @}
*/

/**
 * @defgroup    IUTEST_CONFIG_OTHER OTHER
 * @brief       その他の CONFIG
 * @{
*/

//! use quadmath
#if !defined(IUTEST_USE_QUADMATH)
#  define IUTEST_USE_QUADMATH       0
#endif

//! テストのチェック機能の有無
#if !defined(IUTEST_CHECK_STRICT)
#  define IUTEST_CHECK_STRICT       1
#endif

#if !defined(IUTEST_HAS_MINIDUMP)
//! MiniDump 出力が有効かどうか
#  if defined(_MSC_VER) && _MSC_VER >= 1310
#    if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH \
            && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
#      define IUTEST_HAS_MINIDUMP   1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_MINIDUMP)
#  define IUTEST_HAS_MINIDUMP       0
#endif

#if !defined(IUTEST_HAS_SOCKET)
//! ソケット通信可能かどうか
#  if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_RT)
#    if (!defined(_MSC_VER) || _MSC_VER >= 1310) && (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x501)
#      define IUTEST_HAS_SOCKET 1
#    endif
#  elif defined(IUTEST_OS_CYGWIN)
#    if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 1) \
        || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE) \
        || (defined(_POSIX_SOURCE) && _POSIX_SOURCE)
#      define IUTEST_HAS_SOCKET   1
#    endif
#  elif defined(IUTEST_OS_LINUX)
#    define IUTEST_HAS_SOCKET   1
#  endif
#endif

#if !defined(IUTEST_HAS_SOCKET)
#  define IUTEST_HAS_SOCKET     0
#endif

/**
 * @brief   stdout/stderr の StreamBuffer が使用可能かどうか
*/
#if !defined(IUTEST_HAS_STREAM_BUFFER)
#  define IUTEST_HAS_STREAM_BUFFER  1
#endif


/**
 * @brief   テストの所持を独自リストクラスで行う
 * @deprecated
*/
#if !defined(IUTEST_USE_OWN_LIST)
#  if defined(IUTEST_NO_TEMPLATE_TEMPLATES)
#    define IUTEST_USE_OWN_LIST 1
#  endif
#endif

#if !defined(IUTEST_USE_OWN_LIST)
#  define IUTEST_USE_OWN_LIST   0
#endif

/**
 * @brief   独自 string_view クラスを使う
*/
#if !defined(IUTEST_USE_OWN_STRING_VIEW)
#  if !IUTEST_HAS_CXX_HDR_STRING_VIEW
#    define IUTEST_USE_OWN_STRING_VIEW  1
#  endif
#endif

#if !defined(IUTEST_USE_OWN_STRING_VIEW)
#  define IUTEST_USE_OWN_STRING_VIEW    0
#endif


/**
 * @}
*/

/**
 * @defgroup    IUTEST_CONFIG_LISTENER  LISTENER
 * @brief       Listener 関係の CONFIG
 * @{
*/

#if !defined(IUTEST_HAS_STREAM_RESULT)
//! stream result が使用可能かどうか
#  if IUTEST_HAS_SOCKET
#    define IUTEST_HAS_STREAM_RESULT    1
#  else
#    define IUTEST_HAS_STREAM_RESULT    0
#  endif
#endif

/**
 * @}
*/

// Doxygen 用
#ifdef IUTEST_BUILD_DOXYGEN

/**
 * @ingroup IUTEST_CONFIG_TIME  TIME
 * @{
*/

#define IUTEST_GetMillisec()    //!< 現在時刻のミリ秒取得関数を独自定義

/**
 * @}
*/


/**
 * @ingroup IUTEST_CONFIG_OTHER OTHER
 * @{
*/

/**
 * @brief   iutest で t1/tuple.h をインクルードするかどうか
 * @details 1: ::std::tr1 名前空間にある tuple を使用します。
 *          tuple.h はユーザーがインクルードします。
 *          0: 指定なし iutest が自動で判断します。
*/
#define IUTEST_USE_EXTERNAL_TR1_TUPLE   0

/**
 * @brief   iutest で tuple.h をインクルードするかどうか
 * @details 1: std 名前空間にある tuple を使用します。
 *          tuple.h はユーザーがインクルードします。
 *          0: 指定なし iutest が自動で判断します。
*/
#define IUTEST_USE_EXTERNAL_STD_TUPLE   0

/**
 * @brief   ::std::is_member_function_pointer がコンパイルエラーになる場合に定義する
*/
#define IUTEST_USE_OWN_IS_MEMBER_FUNCTION_POINTER   1

/**
 * @brief   iutest で使用する乱数エンジンを指定します
 * @details 未定義の場合は iutest が実装しているエンジンを使用します(XorShift 128)
*/
#define IUTEST_USE_RANDOM_ENGINE_TYPENAME   ::std::default_random_engine

#define IUTEST_NO_GETENV    //!< getenv 関数がない場合は定義
#define IUTEST_NO_SETENV    //!< setenv 関数がない場合は定義
#define IUTEST_NO_PUTENV    //!< putenv 関数がない場合は定義
#define IUTEST_NO_GETCWD    //!< getcwd 関数がない場合は定義

//! RecordProperty が Test 以外の場所でも使用できない場合に定義される
#define IUTEST_NO_RECORDPROPERTY_OUTSIDE_TESTMETHOD_LIFESPAN

/**
 * @}
*/

#define IUTEST_USE_LIB      //!< ライブラリ版を使用する
#define IUTEST_AUTO_LINK    //!< ライブラリ版を使用し、自動リンクする
#define IUTEST_USE_MAIN     //!< main 関数定義を iutest に任せる

#endif

/**
 * @}
*/

/**
 * @brief   iutest has testsuite api
*/
#define IUTEST_HAS_TESTSUITE    1

/**
 * @brief   iutest has testcase api
*/
#if !defined(IUTEST_HAS_TESTCASE)
#  define IUTEST_HAS_TESTCASE   1
#endif

#if defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
#  undef IUTEST_REMOVE_LEGACY_TEST_CASEAPI_
#endif

#if !IUTEST_HAS_TESTCASE
#  define IUTEST_REMOVE_LEGACY_TEST_CASEAPI_
#endif

/**
 * @private
 * @{
*/

// include only
#if IUTEST_HAS_LIB
#  define IUTEST_IPP_INLINE
#else
#  define IUTEST_IPP_INLINE     inline
#endif

// auto link
#if IUTEST_HAS_LIB && defined(IUTEST_AUTO_LINK)

#if defined(_MSC_VER)

#if defined(_MT) || defined(__MT__)
#  if defined(_DLL)
#    define IUTEST_LIB_THREAD_OPT   "md"
#  else
#    define IUTEST_LIB_THREAD_OPT   "mt"
#  endif
#else
#  define IUTEST_LIB_THREAD_OPT ""
#endif

#if   _MSC_VER >= 1930
#  define IUTEST_LIB_TOOLSET    "vc143"
#elif _MSC_VER >= 1920
#  define IUTEST_LIB_TOOLSET    "vc142"
#elif _MSC_VER >= 1910
#  define IUTEST_LIB_TOOLSET    "vc141"
#elif _MSC_VER >= 1900
#  define IUTEST_LIB_TOOLSET    "vc140"
#elif _MSC_VER == 1800
#  define IUTEST_LIB_TOOLSET    "vc120"
#elif _MSC_VER == 1700
#  define IUTEST_LIB_TOOLSET    "vc110"
#elif _MSC_VER == 1600
#  define IUTEST_LIB_TOOLSET    "vc100"
#elif _MSC_VER == 1500
#  define IUTEST_LIB_TOOLSET    "vc90"
#elif _MSC_VER == 1400
#  define IUTEST_LIB_TOOLSET    "vc80"
#else
#  error unknown _MSC_VER.
#endif

#if defined(_DEBUG)
#  define IUTEST_LIB_RT_OPT     "d"
#else
#  define IUTEST_LIB_RT_OPT     ""
#endif

#define IUTEST_LIB_NAME(name)   \
    #name "-" IUTEST_LIB_TOOLSET "-" IUTEST_LIB_THREAD_OPT IUTEST_LIB_RT_OPT ".lib"

#pragma comment(lib, IUTEST_LIB_NAME(libiutest) )

#endif

#endif

/**
 * @}
*/

#endif // INCG_IRIS_IUTEST_CONFIG_HPP_F0151607_0D9D_4055_B94D_ED4A0FFA748B_
