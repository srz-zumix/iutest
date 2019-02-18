//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_main.cpp
 * @brief       iris unit test main
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#define IUTEST_USE_LIB

//======================================================================
// include
#include <iostream>

#include "../include/iutest.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
    ::std::cout << "Running main() from iutest_main.cpp" << ::std::endl;

    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
