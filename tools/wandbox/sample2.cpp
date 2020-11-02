//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        sample2.cpp
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

#include "sample2.h"
#include <iostream>
#include "../../include/iutest.hpp"

int g()
{
    return 0;
}

IUTEST_PACKAGE(sample2)
{

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT( g() == 0 );
}

}
