//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        debug_tests.cpp
 * @brief       iutest_debug.hpp test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#define _IUTEST_DEBUG
#include "iutest.hpp"

IUTEST(Debug, BreakAlloc)
{
#if !defined(IUTEST_USE_GTEST)
    ::iutest::detail::iuDebugBreakAlloc(9999);
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
