//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        default_main_tests.cpp
 * @brief       default main test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#define IUTEST_USE_MAIN
#include "iutest.hpp"

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(1, abs(-1));
}
