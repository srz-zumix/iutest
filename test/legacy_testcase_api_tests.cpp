//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        legacy_testcase_api_tests.cpp
 * @brief       iutest legacy testcase api test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TESTSUITE && IUTEST_HAS_TESTCASE

IUTEST(Util, Api)
{
    IUTEST_EXPECT_EQ(::iuutil::GetCurrentTestSuite(), ::iuutil::GetCurrentTestCase());
    IUTEST_EXPECT_STREQ(::iuutil::GetTestSuiteName(::iutest::UnitTest::GetInstance()->current_test_info())
        , ::iuutil::GetTestCaseName(::iutest::UnitTest::GetInstance()->current_test_info()));
    IUTEST_EXPECT_EQ(::iuutil::GetTotalTestSuiteCount(), ::iuutil::GetTotalTestCaseCount());
    IUTEST_EXPECT_EQ(::iuutil::GetSuccessfulTestSuiteCount(), ::iuutil::GetSuccessfulTestCaseCount());

    const char* name = "pkg.prefix/TestCase/0";
    IUTEST_EXPECT_STREQ(::iuutil::TestSuiteNameRemoveInstantiateAndIndexName(name)
        , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName(name));
    IUTEST_EXPECT_STREQ(::iuutil::TestSuiteNameRemoveIndexName(name)
        , ::iuutil::TestCaseNameRemoveIndexName(name));

    IUTEST_EXPECT_EQ(::iuutil::FindTestSuite(name), ::iuutil::FindTestCase(name));
    IUTEST_EXPECT_EQ(::iuutil::FindParamTestSuite(name), ::iuutil::FindParamTestCase(name));
    IUTEST_EXPECT_EQ(::iuutil::FindParamTypedTestSuite(name), ::iuutil::FindParamTypedTestCase(name));
    IUTEST_EXPECT_EQ(::iuutil::GetTestSuiteAdHocResult(::iuutil::GetCurrentTestSuite()), ::iuutil::GetTestCaseAdHocResult(::iuutil::GetCurrentTestCase()));
    IUTEST_EXPECT_EQ(::iuutil::GetCurrentTestSuiteAdHocResult(), ::iuutil::GetCurrentTestCaseAdHocResult());
}

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
