//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        invalid_both_suite_and_case_set_up_tests.cpp
 * @brief       invalid testsuite and testcase both implement
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
#define IUTEST_ABORT()  (void)0
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)
#  if IUTEST_HAS_TESTSUITE && IUTEST_HAS_TESTCASE && !defined(IUTEST_USE_LIB)
#    define HAS_INVALID_TESTSUITE_AND_TESTCASE  1
#  endif
#endif

#if !defined(HAS_INVALID_TESTSUITE_AND_TESTCASE)
#  define HAS_INVALID_TESTSUITE_AND_TESTCASE    0
#endif

#if HAS_INVALID_TESTSUITE_AND_TESTCASE

#if IUTEST_HAS_STREAM_BUFFER
::iutest::detail::IUStreamBuffer<2048> stderr_capture(stderr);
#endif

class BothTest : public ::iutest::Test
{
public:
    static int x;
public:
    static void SetUpTestSuite()
    {
        ++x;
    }
    static void SetUpTestCase()
    {
        ++x;
    }
};

IUTEST_F(BothTest, Run)
{
}

int BothTest::x = 0;

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if HAS_INVALID_TESTSUITE_AND_TESTCASE
    int ret = IUTEST_RUN_ALL_TESTS();
#if IUTEST_HAS_ASSERTION_RETURN
#if IUTEST_HAS_STREAM_BUFFER
    IUTEST_ASSERT_STRIN(
        "Test can not provide both SetUpTestSuite and SetUpTestCase"
        ", please make sure there is only one present at "
        , stderr_capture.GetStreamString()) << ::iutest::AssertionReturn<int>(1);
#endif
    IUTEST_ASSERT_EQ(1, BothTest::x) << ::iutest::AssertionReturn<int>(1);
#endif
    if( ret == 0 )
    {
        return 1;
    }
    printf("*** Successful ***\n");
    return 0;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}

