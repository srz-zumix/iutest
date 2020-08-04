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
    IUTEST_EXPECT_EQ(::iuutil::GetTestSuite(0), ::iuutil::GetTestCase(0));
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
    IUTEST_EXPECT_EQ(::iuutil::GetTestSuiteAdHocResult(::iuutil::GetCurrentTestSuite())
        , ::iuutil::GetTestCaseAdHocResult(::iuutil::GetCurrentTestCase()));
    IUTEST_EXPECT_EQ(::iuutil::GetCurrentTestSuiteAdHocResult(), ::iuutil::GetCurrentTestCaseAdHocResult());
}

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, ParamTest, ::iutest::Values(0, 1));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

typedef ::iutest::Types<int, float> TypedTestTypes;
IUTEST_TYPED_TEST_CASE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Test)
{
}

#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE_P(TypeParamTest);
IUTEST_TYPED_TEST_P(TypeParamTest, Test)
{
}
IUTEST_REGISTER_TYPED_TEST_CASE_P(TypeParamTest, Test);

typedef ::iutest::Types<int, float> TypeParamTestTypes;
IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(My1, TypeParamTest, TypeParamTestTypes);

#endif

#if IUTEST_HAS_ANY_PARAM_TEST

IUTEST_AP(AnyParamTest, Test)
{
    IUTEST_EXPECT_STREQ("My1/AnyParamTest", ::iuutil::GetCurrentTestSuite()->name());
    const int value = GetParam<int>();
    IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_CASE_AP(My1, AnyParamTest, ::iutest::Values(0));

IUTEST_AP(AnyParamTest2, Test)
{
    const ::std::string value = GetParam< ::std::string >();
    IUTEST_ASSERT_EQ("0", value);
}

IUTEST_INSTANTIATE_TEST_CASE_AP(My1, AnyParamTest2, ::iutest::Values("0"));

#endif

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
