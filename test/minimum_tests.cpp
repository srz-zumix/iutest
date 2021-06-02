﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        minimum_tests.cpp
 * @brief       minimum test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    IUTEST_ABORT();
    return IUTEST_RUN_ALL_TESTS();
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(1, abs(-1));
}
