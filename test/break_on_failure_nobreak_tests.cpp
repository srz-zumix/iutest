//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        break_on_failure_nobreak_tests.cpp
 * @brief       break_on_fialure no break test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(Foo, Skip)
{
    IUTEST_SKIP();
}

IUTEST(Foo, Inform)
{
    IUTEST_INFORM_FALSE(true);
}

IUTEST(Foo, Assume)
{
    IUTEST_ASSUME_FALSE(true);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    ::iutest::IUTEST_FLAG(break_on_failure) = true;
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
#endif
    return IUTEST_RUN_ALL_TESTS();
}
