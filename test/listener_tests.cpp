//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        listener_tests.cpp
 * @brief       リスナー 対応テスト
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

class MyTestEventListener IUTEST_CXX_FINAL : public ::iuutil::backward::TestEventListener
{
public:
    bool called_OnTestProgramStart;
    bool called_OnTestIterationStart;
    bool called_OnEnvironmentsSetUpStart;
    bool called_OnEnvironmentsSetUpEnd;
    bool called_OnTestSuiteStart;
    bool called_OnTestStart;
    bool called_OnTestPartResult;
    bool called_OnTestRecordProperty;
    bool called_OnTestEnd;
    bool called_OnTestSuiteEnd;
    bool called_OnEnvironmentsTearDownStart;
    bool called_OnEnvironmentsTearDownEnd;
    bool called_OnTestIterationEnd;
    bool called_OnTestProgramEnd;

public:
    MyTestEventListener(void)
    : called_OnTestProgramStart(false)
    , called_OnTestIterationStart(false)
    , called_OnEnvironmentsSetUpStart(false)
    , called_OnEnvironmentsSetUpEnd(false)
    , called_OnTestSuiteStart(false)
    , called_OnTestStart(false)
    , called_OnTestPartResult(false)
    , called_OnTestRecordProperty(false)
    , called_OnTestEnd(false)
    , called_OnTestSuiteEnd(false)
    , called_OnEnvironmentsTearDownStart(false)
    , called_OnEnvironmentsTearDownEnd(false)
    , called_OnTestIterationEnd(false)
    , called_OnTestProgramEnd(false)
    {}

public:
    virtual void OnTestProgramStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestProgramStart = true;
    }
    virtual void OnTestIterationStart(const ::iutest::UnitTest& /*test*/
                                    , int /*iteration*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestIterationStart = true;
    }
    virtual void OnEnvironmentsSetUpStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        called_OnEnvironmentsSetUpStart = true;
    }
    virtual void OnEnvironmentsSetUpEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        called_OnEnvironmentsSetUpEnd = true;
    }
    virtual void OnTestSuiteStart(const ::iutest::TestSuite& /*test_suite*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestSuiteStart = true;
    }
    virtual void OnTestStart(const ::iutest::TestInfo& /*test_info*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestStart = true;
    }
    virtual void OnTestPartResult(const ::iutest::TestPartResult& /*test_part_result*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestPartResult = true;
    }
#if !defined(IUTEST_USE_GTEST)
    virtual void OnTestRecordProperty(const ::iutest::TestProperty& test_property) IUTEST_CXX_OVERRIDE
    {
        called_OnTestRecordProperty = true;
        TestEventListener::OnTestRecordProperty(test_property);
    }
#endif
    virtual void OnTestEnd(const ::iutest::TestInfo& /*test_info*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestEnd = true;
    }
    virtual void OnTestSuiteEnd(const ::iutest::TestSuite& /*test_suite*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestSuiteEnd = true;
    }
    virtual void OnEnvironmentsTearDownStart(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        called_OnEnvironmentsTearDownStart = true;
    }
    virtual void OnEnvironmentsTearDownEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        called_OnEnvironmentsTearDownEnd = true;
    }
    virtual void OnTestIterationEnd(const ::iutest::UnitTest& /*test*/
                                    , int /*iteration*/) IUTEST_CXX_OVERRIDE
    {
        called_OnTestIterationEnd = true;
    }
    virtual void OnTestProgramEnd(const ::iutest::UnitTest& /*test*/) IUTEST_CXX_OVERRIDE
    {
        if( called_OnTestProgramEnd ) exit(1);
        called_OnTestProgramEnd = true;
    }
};

static MyTestEventListener* listener = NULL;

IUTEST(EventListenerTest, FlagCheck)
{
    IUTEST_ASSERT_TRUE( listener->called_OnTestProgramStart );
    IUTEST_ASSERT_TRUE( listener->called_OnTestIterationStart );
    IUTEST_ASSERT_TRUE( listener->called_OnEnvironmentsSetUpStart );
    IUTEST_ASSERT_TRUE( listener->called_OnEnvironmentsSetUpEnd );
    IUTEST_ASSERT_TRUE( listener->called_OnTestSuiteStart );
    IUTEST_ASSERT_TRUE( listener->called_OnTestStart );

    IUTEST_ASSERT_FALSE( listener->called_OnTestEnd );
    IUTEST_ASSERT_FALSE( listener->called_OnTestSuiteEnd );
    IUTEST_ASSERT_FALSE( listener->called_OnEnvironmentsTearDownStart );
    IUTEST_ASSERT_FALSE( listener->called_OnEnvironmentsTearDownEnd );
    IUTEST_ASSERT_FALSE( listener->called_OnTestIterationEnd );
    IUTEST_ASSERT_FALSE( listener->called_OnTestProgramEnd );

    IUTEST_ASSERT_FALSE( listener->called_OnTestPartResult );
    IUTEST_INFORM_EQ(1, 2);
    IUTEST_ASSERT_TRUE( listener->called_OnTestPartResult );

#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_FALSE( listener->called_OnTestRecordProperty );
    RecordProperty("dummy", 0);
    IUTEST_ASSERT_TRUE( listener->called_OnTestRecordProperty );
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);

    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    listener = new MyTestEventListener();
    listeners.Append( listener );
    listeners.Append( new ::iutest::EmptyTestEventListener() );
    const int ret = IUTEST_RUN_ALL_TESTS();

    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnTestEnd );
    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnTestSuiteEnd );
    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnEnvironmentsTearDownStart );
    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnEnvironmentsTearDownEnd );
    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnTestIterationEnd );
    IUTEST_TERMINATE_ON_FAILURE( listener->called_OnTestProgramEnd );

    return ret;
}
