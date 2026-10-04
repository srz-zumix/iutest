//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fail_if_no_test_linked_tests.cpp
 * @brief       Fail if no test linked tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#if !defined(IUTEST_FAIL_IF_NO_TEST_LINKED_NO_TEST)
IUTEST(LinkedTest, DISABLED_NotRun)
{
    IUTEST_FAIL();
}
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_FAIL_IF_NO_TEST_LINKED_NO_TEST)
    if( ::iutest::UnitTest::GetInstance()->total_test_count() != 1 ) return 1;
#else
    if( ::iutest::UnitTest::GetInstance()->total_test_count() != 0 ) return 1;
#endif
    return IUTEST_RUN_ALL_TESTS();
}
