//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception_tests.cpp
 * @brief       iutest test 例外テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if defined(IUTEST_USE_GTEST)
#  if GTEST_VER < 0x01060000 && !IUTEST_HAS_SEH
#    define EXCEPTION_CATCH_TEST  0
#  endif
#endif

#if !defined(EXCEPTION_CATCH_TEST)
#  if IUTEST_HAS_EXCEPTIONS
#    define EXCEPTION_CATCH_TEST  1
#  else
#    define EXCEPTION_CATCH_TEST  0
#  endif
#endif


#if EXCEPTION_CATCH_TEST
#include <stdexcept>

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE("-Wmissing-noreturn")

IUTEST(ExceptionTest, StdExceptionThrow)
{
    throw ::std::runtime_error("ExceptionTest");
}

IUTEST(ExceptionTest, Throw)
{
    throw "ExceptionTest";
}

IUTEST_PRAGMA_WARN_POP()

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if EXCEPTION_CATCH_TEST
    ::iutest::IUTEST_FLAG(catch_exceptions) = true;

#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif
    if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
#else
    if( IUTEST_RUN_ALL_TESTS() ) return 1;
#endif
    printf("*** Successful ***\n");
    return 0;
}

