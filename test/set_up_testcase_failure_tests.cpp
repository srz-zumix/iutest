//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        set_up_TestSuite_failure_tests.cpp
 * @brief       SetUpTestSuite で失敗したときのテスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static int setup_flag = 0;
static int teardown_flag = 0;

class TestSetUpFailure : public ::iuutil::backward::Test<TestSetUpFailure>
{
public:
    static void SetUpTestSuite()
    {
        IUTEST_FAIL() << "SetUp TestSuite Failed.";
    }
};

IUTEST_F(TestSetUpFailure, Test)
{
    ++setup_flag;
}

class TestTearDownFailure : public ::iuutil::backward::Test<TestTearDownFailure>
{
public:
    static void TearDownTestSuite()
    {
        IUTEST_FAIL() << "TearDown TestSuite Failed.";
    }
};

IUTEST_F(TestTearDownFailure, Test)
{
    ++teardown_flag;
}


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();

#if defined(IUTEST_USE_GTEST) && (GTEST_VER >= 0x01080100 && GTEST_VER <= 0x01100000) && !GTEST_LATEST
    // "Google Test" fails to set up a test case,
    // it does not report a failure, and the test is also continued
    // fixed at https://github.com/google/googletest/commit/9ed99c6c837ae1cbfcabd36959fc802ebb5ae07f
    IUTEST_TERMINATE_ON_FAILURE( ret == 0 );
    if( ret != 0 ) return 1;
#else
    IUTEST_TERMINATE_ON_FAILURE( ret != 0 );
    if( ret == 0 ) return 1;
#endif

    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() != 2 );
#if !defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE( setup_flag == 0 );
#else
    IUTEST_TERMINATE_ON_FAILURE( setup_flag == 1 );
#endif
    IUTEST_TERMINATE_ON_FAILURE( teardown_flag == 1);

    printf("*** Successful ***\n");
    return 0;
}
