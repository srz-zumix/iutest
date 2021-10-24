//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        inform_tests.cpp
 * @brief       iutest inform flavor test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2017-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

IUTEST(InformTest, A)
{
    IUTEST_INFORM_TRUE(false);
}
#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(warning_into_error) = true;
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();
#if !defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE( ret != 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iuutil::GetSuccessfulTestSuiteCount() == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
#else
    IUTEST_TERMINATE_ON_FAILURE( ret == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iuutil::GetSuccessfulTestSuiteCount() == 1 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
#endif
    printf("*** Successful ***\n");
    return 0;
}

