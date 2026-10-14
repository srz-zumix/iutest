//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion_exception_tests.cpp
 * @brief       assertion exception test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#if IUTEST_HAS_EXCEPTIONS

static bool g_throw_caught = false;
static bool g_listener_reached = false;

IUTEST(AssertionExceptionTest, ThrowOnFailure)
{
    ::iutest::IUTEST_FLAG(throw_on_failure) = true;
    try
    {
        IUTEST_EXPECT_EQ(1, 2) << "throw on failure marker";
        g_listener_reached = true;
    }
    catch (const ::std::exception& e)
    {
        const ::std::string message(e.what());
        g_throw_caught = message.find("assertion_exception_tests.cpp") != ::std::string::npos
            && message.find("throw on failure marker") != ::std::string::npos;
    }
    ::iutest::IUTEST_FLAG(throw_on_failure) = false;
}

#if !defined(IUTEST_USE_GTEST)
class ThrowingListener : public ::iutest::EmptyTestEventListener
{
public:
    virtual void OnTestPartResult(const ::iutest::TestPartResult& result) IUTEST_CXX_OVERRIDE
    {
        if( result.failed() )
        {
            throw ::iutest::AssertionException(result);
        }
    }
};

IUTEST(AssertionExceptionTest, Listener)
{
    IUTEST_EXPECT_EQ(1, 2) << "listener exception marker";
    g_listener_reached = true;
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
#if IUTEST_HAS_EXCEPTIONS
    ::iutest::IUTEST_FLAG(catch_exceptions) = false;
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    ::iutest::IUTEST_FLAG(filter) = "AssertionExceptionTest.ThrowOnFailure";
    if( IUTEST_RUN_ALL_TESTS() == 0 || !g_throw_caught || g_listener_reached ) return 1;

#if !defined(IUTEST_USE_GTEST)
    ThrowingListener* listener = new ThrowingListener();
    ::iutest::UnitTest::GetInstance()->listeners().Append(listener);
    ::iutest::IUTEST_FLAG(filter) = "AssertionExceptionTest.Listener";
    bool caught = false;
    bool completed = false;
    try
    {
        completed = IUTEST_RUN_ALL_TESTS() != 0;
    }
    catch (const ::iutest::AssertionException& e)
    {
        caught = ::std::string(e.what()).find("listener exception marker") != ::std::string::npos;
    }
    delete ::iutest::UnitTest::GetInstance()->listeners().Release(listener);
    if( !caught || completed || g_listener_reached ) return 2;
#endif
#else
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
#endif
    return 0;
}
