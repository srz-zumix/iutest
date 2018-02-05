//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        break_on_failure_tests.cpp
 * @brief       break_on_fialure 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"


IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(2, 3);
}


#if IUTEST_HAS_SEH && !defined(IUTEST_OS_WINDOWS_MOBILE)
LONG WINAPI ExitWithExceptionCode(struct _EXCEPTION_POINTERS* exception_pointers)
{
    exit(exception_pointers->ExceptionRecord->ExceptionCode);
}
#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    ::iutest::IUTEST_FLAG(break_on_failure) = true;

#if defined(IUTEST_OS_WINDOWS) && IUTEST_OS_WINDOWS
    SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
#if IUTEST_HAS_SEH && !defined(IUTEST_OS_WINDOWS_MOBILE)
    SetUnhandledExceptionFilter(ExitWithExceptionCode);
#endif
#endif

    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
