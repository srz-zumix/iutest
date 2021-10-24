//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        skip_tests.cpp
 * @brief       IUTEST_SKIP tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static bool skip_check = true;

IUTEST(DISABLED_SkipTest, A)
{
}

IUTEST(SkipTest, CanSkip)
{
    IUTEST_SKIP() << "test";
    IUTEST_EXPECT_EQ(2, 3);
}

IUTEST(SkipTest, Failed)
{
    IUTEST_EXPECT_EQ(2, 3);
    IUTEST_SKIP();
    skip_check = false;
    IUTEST_EXPECT_EQ(2, 3);
}

IUTEST(SkipTest, Syntax)
{
    if( bool b = false )
        IUTEST_SKIP() << b << "no skip";
    IUTEST_EXPECT_EQ(2, 3);
}

#if !defined(IUTEST_USE_GTEST)

class SetUpTestSuiteSkipTest : public ::iuutil::backward::Test<SetUpTestSuiteSkipTest>
{
public:
    static void SetUpTestSuite()
    {
        IUTEST_SKIP() << "skip in SetUpTestSuite";
    }
};

IUTEST_F(SetUpTestSuiteSkipTest, NotRun)
{
    IUTEST_EXPECT_EQ(2, 3);
}

class SetUpSkipTest : public ::iutest::Test
{
public:
    virtual void SetUp() IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        IUTEST_SKIP() << "skip in SetUp";
    }
};

IUTEST_F(SetUpSkipTest, NotRun)
{
    IUTEST_EXPECT_EQ(2, 3);
}

#endif

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
    if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 5 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->test_run_skipped_count() == 3 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 3 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 4 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->successful_test_count() == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iuutil::GetTotalTestSuiteCount() == 4 );
    IUTEST_TERMINATE_ON_FAILURE( ::iuutil::GetSuccessfulTestSuiteCount() == 3 );
#else
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 3 );
#endif
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
    IUTEST_TERMINATE_ON_FAILURE( skip_check );
    printf("*** Successful ***\n");
    return 0;
}
