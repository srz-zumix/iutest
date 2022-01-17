//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        no_failure_fail_tests.cpp
 * @brief       iutest no (fatal) failure fail test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

int nCount = 0;

void OccurFatalFailure(void)
{
    IUTEST_ASSERT_TRUE(false);
}

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()

IUTEST(NoFatalFailureTest, Assert)
{
    IUTEST_ASSERT_NO_FATAL_FAILURE(OccurFatalFailure());
    ++nCount;
}

IUTEST(NoFailureTest, Assert)
{
    IUTEST_ASSERT_NO_FAILURE(OccurFatalFailure());
    ++nCount;
}

IUTEST_PRAGMA_WARN_POP()

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret == 0 ) return 1;

#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->successful_test_count()) << ::iutest::AssertionReturn(1);
    IUTEST_ASSERT_EQ(2, ::iutest::UnitTest::GetInstance()->failed_test_count()) << ::iutest::AssertionReturn(1);
    IUTEST_ASSERT_EQ(0, nCount) << ::iutest::AssertionReturn(1);
#else
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->successful_test_count() == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
    IUTEST_TERMINATE_ON_FAILURE( nCount == 0 );
#endif
    printf("*** Successful ***\n");
    return 0;
}
