//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception_set_up_testsuite_tests.cpp
 * @brief       iutest exception at SetUpTestSuite
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
#if defined(IUTEST_USE_GTEST) && (GTEST_VER >= 0x01080100 && GTEST_VER <= 0x01100000) && !GTEST_LATEST
    // bug?
    if( IUTEST_RUN_ALL_TESTS() != 0 )
    {
        printf("Test expect success.\n");
        return 1;
    }
#else
    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        printf("Test expect fail.\n");
        return 1;
    }
#endif
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->failed_test_count())
        << ::iutest::AssertionReturn<int>(1);
#else
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
#endif

#else
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
#endif
    printf("*** Successful ***\n");
    return 0;
}

