//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        legacy_testcase_api_tests.cpp
 * @brief       iutest legacy testcase api test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020-2021, Takazumi Shirayanagi\n
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

class CaseFixture : public ::iutest::Test
{
public:
    static void SetUpTestCase()
    {
        ::iutest::Test::SetUpTestCase();
    }
    static void TearDownTestCase()
    {
        ::iutest::Test::TearDownTestCase();
    }
};

IUTEST_F(CaseFixture, Test)
{
}

class SuiteFixture : public ::iutest::Test
{
public:
    static void SetUpTestSuite()
    {
        ::iutest::Test::SetUpTestSuite();
    }
    static void TearDownTestSuite()
    {
        ::iutest::Test::TearDownTestSuite();
    }
};

IUTEST_F(SuiteFixture, Test)
{
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

#if !defined(IUTEST_USE_GTEST)

class MyTestEventListener IUTEST_CXX_FINAL : public ::iutest::TestEventListener
{
public:
    bool called_OnTestCaseStart;
    bool called_OnTestCaseEnd;

public:
    MyTestEventListener(void)
    : called_OnTestCaseStart(false)
    , called_OnTestCaseEnd(false)
    {}

public:
    virtual void OnTestProgramStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestIterationStart(const ::iutest::UnitTest& /*test*/
                                    , int /*iteration*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnEnvironmentsSetUpStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnEnvironmentsSetUpEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestCaseStart(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE
    {
        if( ::iutest::detail::IsStringEqual(test_case.name(), "EventListenerTest") )
        {
            called_OnTestCaseStart = true;
        }
    }
    virtual void OnTestStart(const ::iutest::TestInfo& /*test_info*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestPartResult(const ::iutest::TestPartResult& /*test_part_result*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestRecordProperty(const ::iutest::TestProperty& /*test_property*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestEnd(const ::iutest::TestInfo& /*test_info*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestCaseEnd(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE
    {
        if( ::iutest::detail::IsStringEqual(test_case.name(), "EventListenerTest") )
        {
            called_OnTestCaseEnd = true;
        }
    }
    virtual void OnEnvironmentsTearDownStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnEnvironmentsTearDownEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestIterationEnd(const ::iutest::UnitTest& /*test*/
                                    , int /*iteration*/) IUTEST_CXX_OVERRIDE
    {
    }
    virtual void OnTestProgramEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
    }
};

static MyTestEventListener* listener = NULL;

IUTEST(EventListenerTest, FlagCheck)
{
    IUTEST_ASSERT_TRUE( listener->called_OnTestCaseStart );
    IUTEST_ASSERT_FALSE( listener->called_OnTestCaseEnd );
}
#endif

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);

#if IUTEST_HAS_TESTSUITE && IUTEST_HAS_TESTCASE && !defined(IUTEST_USE_GTEST)
    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    listener = new MyTestEventListener();
    listeners.Append( listener );
    const int ret = IUTEST_RUN_ALL_TESTS();

    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnTestCaseEnd );
    return ret;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}
