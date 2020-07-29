//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_ignore.hpp
 * @brief       iris unit test ignore test ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_
#define INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_

//======================================================================
// define

#if IUTEST_HAS_IGNORE_TEST

/**
 * @ingroup TESTDEF
 * @def     IUTEST_TEST_IGNORE(testsuite_, testname_)
 * @brief   テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
 * @deprecated
*/
#define IUTEST_TEST_IGNORE(testsuite_, testname_)                \
    IUTEST_TEST_IGNORE_(testsuite_, testname_, ::iutest::Test    \
                        , ::iutest::internal::GetTestTypeId())

/**
 * @ingroup TESTDEF
 * @def     IUTEST_TEST_IGNORE(testsuite_, testname_)
 * @brief   テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
 * @deprecated
*/
#define IUTEST_IGNORE(testsuite_, testname_)         \
    IUTEST_TEST_IGNORE(testsuite_, testname_)


/**
 * @ingroup TESTDEF
 * @def     IUTEST_F_IGNORE(testfixture_, testname_)
 * @brief   ユーザー指定テスト関数定義マクロ
 * @param   testfixture_    = テストフィクスチャ名
 * @param   testname_       = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
*/
#define IUTEST_F_IGNORE(testfixture_, testname_)    \
    IUTEST_TEST_F_IGNORE_(testfixture_, testname_)

#if IUTEST_HAS_PARAM_TEST

/**
 * @ingroup TESTDEF
 * @def     IUTEST_P_IGNORE(testsuite_, testname_)
 * @brief   パラメータユーザー指定テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
 * @deprecated
*/
#define IUTEST_P_IGNORE(testsuite_, testname_)       \
    IUTEST_TEST_P_IGNORE_(testsuite_, testname_)

#endif

#if IUTEST_HAS_TYPED_TEST

/**
 * @ingroup TESTDEF
 * @def     IUTEST_TYPED_TEST(testsuite_, testname_)
 * @brief   型付けテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
 * @deprecated
*/
#define IUTEST_TYPED_TEST_IGNORE(testsuite_, testname_)  \
    IUTEST_TYPED_TEST_IGNORE_(testsuite_, testname_)

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @ingroup TESTDEF
 * @def     IUTEST_TYPED_TEST_P(testsuite_, testname_)
 * @brief   型パラメータテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note    ignore 版ではテストコードのコンパイルが通らなくても問題ない
 * @deprecated
*/
#define IUTEST_TYPED_TEST_P_IGNORE(testsuite_, testname_)    \
    IIUT_TYPED_TEST_P_IGNORE_(testsuite_, testname_)

#endif

#endif

#endif // INCG_IRIS_IUTEST_IGNORE_HPP_D87CADCE_110D_43CE_9E68_3B6BB0B91E66_
