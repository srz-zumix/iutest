//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        scoped_trace_exception_tests.cpp
 * @brief       IUTEST_SCOPED_TRACE via exception test
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
#include "logger_tests.hpp"

#if defined(IUTEST_USE_GTEST)
#  define EXCEPTION_CATCH_TEST  0
#endif

#if !defined(EXCEPTION_CATCH_TEST)
#  if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_ASSERTION_RETURN
#    define EXCEPTION_CATCH_TEST  1
#  else
#    define EXCEPTION_CATCH_TEST  0
#  endif
#endif

#if EXCEPTION_CATCH_TEST

bool no_throw = false;

IUTEST(ScopedTraceExceptionTest, Exception)
{
    IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Exception A");
    {
        IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Exception B");
    }
    {
        // FIXME: caught scoped trace include "C" ..
        try
        {
            IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Exception C");
            throw "error";
        }
        catch(...)
        {
        }
    }
    {
        IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Exception D");
        if( !no_throw )
        {
            throw "error";
        }
    }
}

IUTEST(ScopedTraceExceptionTest, Assertion)
{
    IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Assertion A");
    {
        try
        {
            IUTEST_SCOPED_TRACE("ScopedTraceExceptionTest Scoped Assertion B");
            throw "error";
        }
        catch(...)
        {
        }
    }
    IUTEST_INFORM_EQ(1, 0);
}

class ScopedTraceExceptionSetUpTest : public ::iuutil::backward::Test<ScopedTraceExceptionSetUpTest>
{
public:
    IUTEST_ATTRIBUTE_NORETURN_ static void SetUpTestSuite()
    {
        IUTEST_SCOPED_TRACE("ScopedTraceExceptionSetUpTest Scoped Exception");
        throw "ScopedTraceExceptionSetUpTest";
    }
};

typedef ScopedTraceExceptionSetUpTest DISABLED_ScopedTraceExceptionSetUpTest;

IUTEST_F(DISABLED_ScopedTraceExceptionSetUpTest, Empty)
{
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if EXCEPTION_CATCH_TEST
    IUTEST_INIT(&argc, argv);
    ::iutest::IUTEST_FLAG(catch_exceptions) = true;
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
    IUTEST_ASSERT_NE(IUTEST_RUN_ALL_TESTS(), 0)
        << ::iutest::AssertionReturn<int>(1);

    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);

    try
    {
        IUTEST_SCOPED_TRACE("Scope Exception Global");
        throw "error";
    }
    catch(...)
    {
    }

    ::iutest::IUTEST_FLAG(also_run_disabled_tests) = false;
    {
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret == 0 ) return 1;
    }

    IUTEST_ASSERT_STRIN(   "ScopedTraceExceptionTest Scoped Exception A", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception B", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    // FIXME: caught scoped trace include "C" ..
    // IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception C", logger.c_str())
    //     << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRIN(   "ScopedTraceExceptionTest Scoped Exception D", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionSetUpTest Scoped Exception", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("Scoped Exception Global", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);

    IUTEST_ASSERT_STRIN   ("ScopedTraceExceptionTest Scoped Assertion A", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Assertion B", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);

    no_throw = true;
    logger.clear();
    {
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;
    }

    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception A", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception B", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception C", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRNOTIN("ScopedTraceExceptionTest Scoped Exception D", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);

#else
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
#endif
    printf("*** Successful ***\n");
    return 0;
}
