//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        scoped_trace_exception_tests.cpp
 * @brief       IUTEST_SCOPED_TRACE via exception test
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
#include "logger_tests.hpp"

#if IUTEST_HAS_EXCEPTIONS

IUTEST(ScopedTraceExceptionTest, Exception)
{
    IUTEST_SCOPED_TRACE("Test Scope Exception");
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

    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret == 0 ) return 1;

#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_STRIN("Test Scope Exception", logger.c_str())
        << ::iutest::AssertionReturn<int>(1);
#endif
    printf("*** Successful ***\n");
    return 0;
}
