//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        set_up_failure_tests.cpp
 * @brief       SetUp/TearDown で失敗したときのテスト
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

class TestSetUpFailure : public ::iutest::Test
{
public:
    virtual void SetUp() IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        IUTEST_FAIL() << "SetUp Failed.";
    }
};

IUTEST_F(TestSetUpFailure, Test)
{
    ++setup_flag;
}

class TestTearDownFailure : public ::iutest::Test
{
public:
    virtual void TearDown() IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        IUTEST_FAIL() << "TearDown Failed.";
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

    IUTEST_TERMINATE_ON_FAILURE( ret != 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
    IUTEST_TERMINATE_ON_FAILURE( setup_flag == 0 );
    IUTEST_TERMINATE_ON_FAILURE( teardown_flag == 1 );

    printf("*** Successful ***\n");
    return 0;
}
