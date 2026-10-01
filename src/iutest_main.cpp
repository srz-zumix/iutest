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
#ifndef IUTEST_USE_LIB
#define IUTEST_USE_LIB
#endif

//======================================================================
// include
#include <iostream>

#include "../include/iutest.hpp"

namespace {
template<typename Char>
int iutest_main(int argc, Char** argv)
{
    ::std::cout << "Running main() from iutest_main.cpp" << ::std::endl;

    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
}   // namespace

int main(int argc, char** argv)
{
    return iutest_main(argc, argv);
}

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
{
    return iutest_main(argc, argv);
}
#endif
