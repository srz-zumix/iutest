//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        scoped_trace_tests.cpp
 * @brief       IUTEST_SCOPED_TRACE test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

IUTEST(ScopedTraceTest, Dummy)
{
    IUTEST_SCOPED_TRACE("FIRST");
    int a=0;
    IUTEST_SCOPED_TRACE("SECOND");
    ++a;
    IUTEST_INFORM_EQ(1, a);
}

IUTEST(ScopedTraceTest, Failed)
{
    IUTEST_INFORM_EQ(0, 1);
}

IUTEST(ScopedTraceTest, Test)
{
#if !defined(IUTEST_USE_GTEST)
    TestLogger logger1, logger2, logger3;
    ::iutest::detail::iuConsole::SetLogger(&logger1);
#endif

    {
        IUTEST_SCOPED_TRACE("Test Scope 1");
        IUTEST_INFORM_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
        IUTEST_ASSERT_STRIN("Test Scope 1", logger1.c_str());
        ::iutest::detail::iuConsole::SetLogger(&logger2);
#endif
        {
            IUTEST_SCOPED_TRACE("Test Scope 2");
            IUTEST_INFORM_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
            IUTEST_ASSERT_STRIN("Test Scope 1", logger2.c_str());
            IUTEST_ASSERT_STRIN("Test Scope 2", logger2.c_str());
            ::iutest::detail::iuConsole::SetLogger(&logger3);
#endif
        }
    }

    IUTEST_SCOPED_TRACE("Test Scope 3");
    IUTEST_INFORM_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_STRIN("Test Scope 3", logger3.c_str());
    ::iutest::detail::iuConsole::SetLogger(NULL);
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
