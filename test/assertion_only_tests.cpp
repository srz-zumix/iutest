//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion_only_tests.cpp
 * @brief       iutest assertion only test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "internal/iutest_compiler.hpp" // IWYU pragma: keep
#include <stdarg.h>

//======================================================================
// define
#define IUTEST_VPRINTF      test_vprintf

//======================================================================
// declare
void test_vprintf(const char* fmt, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 0);

//======================================================================
// include
#include "iutest.hpp"
#include "../include/gtest/iutest_assertion_only.hpp"  // IWYU pragma: keep
#include <iostream>

#ifdef IUTEST_USE_GTEST
static ::std::stringstream s_outstream;
#else
static ::iutest::iu_stringstream s_outstream;
#endif

void test_vprintf(const char* fmt, va_list va)
{
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    char buf[4096];
    vsprintf(buf, fmt, va);
    s_outstream << buf;
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
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

