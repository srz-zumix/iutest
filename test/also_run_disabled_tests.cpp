﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        also_run_disabled_tests.cpp
 * @brief       also_run_disabled_tests option test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "disabled_tests_decl.cpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif
    ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
    const int ret = IUTEST_RUN_ALL_TESTS();
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->disabled_test_count() == expected_disable_test_count );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == expected_disable_test_count );
#endif
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->test_to_run_count() == expected_test_count );
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == expected_disable_test_count );
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->total_test_count() == expected_test_count );
#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 0 );
#endif
    if( ret == 0 ) return 1;
    printf("*** Successful ***\n");
    return 0;
}
