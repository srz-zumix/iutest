//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fail_fast_tests.cpp
 * @brief       fail_fast flag tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

namespace
{

int ran_before_failure = 0;
int ran_after_failure = 0;
int ran_next_suite = 0;
int torn_down = 0;
int environment_torn_down = 0;

class FailFastFixture : public ::iutest::Test
{
public:
    virtual void TearDown() IUTEST_CXX_OVERRIDE
    {
        ++torn_down;
    }
};

class FailFastEnvironment : public ::iutest::Environment
{
public:
    virtual void TearDown() IUTEST_CXX_OVERRIDE
    {
        ++environment_torn_down;
    }
};

}   // namespace

IUTEST_F(FailFastFixture, First)
{
    ++ran_before_failure;
    IUTEST_EXPECT_TRUE(false);
}

IUTEST_F(FailFastFixture, Second)
{
    ++ran_after_failure;
}

IUTEST(FailFastNextSuite, Test)
{
    ++ran_next_suite;
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    ::iutest::AddGlobalTestEnvironment(new FailFastEnvironment);
    IUTEST_FLAG_SET(fail_fast, true);
#if !defined(IUTEST_USE_GTEST)
    IUTEST_FLAG_SET(repeat, 2);
#endif

    IUTEST_TERMINATE_ON_FAILURE( IUTEST_RUN_ALL_TESTS() != 0 );
    IUTEST_TERMINATE_ON_FAILURE( ran_before_failure == 1 );
    IUTEST_TERMINATE_ON_FAILURE( ran_after_failure == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ran_next_suite == 0 );
    IUTEST_TERMINATE_ON_FAILURE( torn_down == 1 );
    IUTEST_TERMINATE_ON_FAILURE( environment_torn_down == 1 );

    printf("*** Successful ***\n");
    return 0;
}
