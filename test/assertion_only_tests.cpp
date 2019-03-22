﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion_only_tests.cpp
 * @brief       iutest assertion only test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <stdarg.h>

//======================================================================
// define
#define IUTEST_VPRINTF      test_vprintf

//======================================================================
// declare
void test_vprintf(const char* fmt, va_list va);

//======================================================================
// include
#include <iostream>
#include "iutest.hpp"
#include "../include/gtest/iutest_assertion_only.hpp"

#ifdef IUTEST_USE_GTEST
static ::std::stringstream s_outstream;
#else
static ::iutest::iu_stringstream s_outstream;
#endif

void test_vprintf(const char* fmt, va_list va)
{
    char buf[4096];
    vsprintf(buf, fmt, va);
    s_outstream << buf;
}

#ifdef UNICODE
int wmain(int, wchar_t**)
#else
int main(int, char**)
#endif
{
    IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
//  ::std::cout << s_outstream.str();
    if( s_outstream.str().empty() )
    {
        return 1;
    }
#endif
    ::std::cout << "*** Successful ***" << ::std::endl;
    return 0;
}

