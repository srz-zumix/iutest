//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception_tests.cpp
 * @brief       iutest test 例外テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
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
IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()

IUTEST(ExceptionTest, StdExceptionThrow)
{
    throw ::std::runtime_error("ExceptionTest");
}

IUTEST(ExceptionTest, Throw)
{
    throw "ExceptionTest";
}

IUTEST_PRAGMA_WARN_POP()

class ExceptionSetUpTest : public ::iuutil::backward::Test<ExceptionSetUpTest>
{
public:
    IUTEST_ATTRIBUTE_NORETURN_ static void SetUpTestSuite()
    {
        throw "ExceptionSetUpTest";
    }
};

IUTEST_F(ExceptionSetUpTest, Empty)
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
    if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_EQ(2, ::iutest::UnitTest::GetInstance()->failed_test_count())
        << ::iutest::AssertionReturn<int>(1);
#else
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
#endif

#else
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
#endif
    printf("*** Successful ***\n");
    return 0;
}

