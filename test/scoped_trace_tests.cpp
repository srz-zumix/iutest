//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        scoped_trace_tests.cpp
 * @brief       IUTEST_SCOPED_TRACE test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2019, Takazumi Shirayanagi\n
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
    IUTEST_ASSERT_EQ(1, a);
}

IUTEST(ScopedTraceTest, Failed)
{
    IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(ScopedTraceTest, Test)
{
#if !defined(IUTEST_USE_GTEST)
    TestLogger logger1, logger2, logger3;
    ::iutest::detail::iuConsole::SetLogger(&logger1);
#endif

    {
        IUTEST_SCOPED_TRACE("Test Scope 1");
        IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
        IUTEST_ASSERT_STRIN("Test Scope 1", logger1.c_str());
        ::iutest::detail::iuConsole::SetLogger(&logger2);
#endif
        {
            IUTEST_SCOPED_TRACE("Test Scope 2");
            IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
            IUTEST_ASSERT_STRIN("Test Scope 1", logger2.c_str());
            IUTEST_ASSERT_STRIN("Test Scope 2", logger2.c_str());
            ::iutest::detail::iuConsole::SetLogger(&logger3);
#endif
        }
    }

    IUTEST_SCOPED_TRACE("Test Scope 3");
    IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_STRIN("Test Scope 3", logger3.c_str());
    ::iutest::detail::iuConsole::SetLogger(NULL);
#endif
}

#if IUTEST_HAS_EXCEPTIONS

class ScopedTraceExceptionTest : public ::iutest::Test
{
public:
#if !defined(IUTEST_USE_GTEST)
    TestLogger logger;

    void SetUp()
    {
        ::iutest::detail::iuConsole::SetLogger(&logger);
    }
    void TearDown()
    {
        ::iutest::detail::iuConsole::SetLogger(NULL);
    }
#endif
};

IUTEST_F(ScopedTraceExceptionTest, Exception)
{
    // IUTEST_SCOPED_TRACE("Test Scope Exception");
    throw "error";
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
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret == 0 ) return 1;
    printf("*** Successful ***\n");
    return 0;
}
