//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        set_up_testcase_failure_tests.cpp
 * @brief       SetUpTestCase で失敗したときのテスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2016, Takazumi Shirayanagi\n
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

class TestSetUpFailure : public ::iutest::Test
{
public:
    static void SetUpTestCase()
    {
        IUTEST_FAIL() << "SetUp TestCase Failed.";
    }
};

IUTEST_F(TestSetUpFailure, Test)
{
    ++setup_flag;
}

class TestTearDownFailure : public ::iutest::Test
{
public:
    static void TearDownTestCase()
    {
        IUTEST_FAIL() << "TearDown TestCase Failed.";
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
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();
    
    if( ret == 0 ) return 1;

    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_EXIT( setup_flag == 0 );
#else
    IUTEST_ASSERT_EXIT( setup_flag == 1 );
#endif
    IUTEST_ASSERT_EXIT( teardown_flag == 1);

    printf("*** Successful ***\n");
    return 0;
}
