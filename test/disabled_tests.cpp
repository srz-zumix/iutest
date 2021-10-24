//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        disabled_tests.cpp
 * @brief       also_run_disabled_tests option test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "disabled_tests_decl.cpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    const int ret = IUTEST_RUN_ALL_TESTS();
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->disabled_test_count() == expected_disable_test_count );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == expected_disable_test_count );
#endif
#if !defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->skip_test_count() == expected_disable_test_count );
#endif
    return ret;
}
