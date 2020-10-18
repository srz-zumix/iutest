//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception_setup_testsuite_tests.cpp
 * @brief       iutest exception at SetUpTestSuite
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

class ExceptionSetUpTest : public ::iuutil::backward::Test<ExceptionSetUpTest>
{
public:
    static void SetUpTestSuite()
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
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif
    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        printf("Test expect fail.\n");
        return 1;
    }
    printf("failed_test_count: %d", ::iutest::UnitTest::GetInstance()->failed_test_count());
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->failed_test_count())
        << ::iutest::AssertionReturn<int>(1);
#else
    IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
#endif

#else
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
#endif
    printf("*** Successful ***\n");
    return 0;
}

