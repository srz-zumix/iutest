//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        sample.cpp
 * @brief       wandbox sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "sample.h"
#include <iostream>
#include "../../include/iutest.hpp"
#if defined(SAMPLE2)
#include "sample2.h"
#endif

int main(int argc, char** argv)
{
    int x = 0;
    ::std::cout << "hoge" << ::std::endl;

    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(42, f());
#if defined(SAMPLE2)
    IUTEST_ASSERT_EQ( 0, g());
#endif
}
