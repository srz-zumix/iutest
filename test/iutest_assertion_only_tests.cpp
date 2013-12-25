//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assertion_only_tests.cpp
 * @brief		iutest assertion only test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <stdarg.h>
#include <iostream>

//======================================================================
// define
#define IUTEST_VPRINTF		test_vprintf
#define IUTEST_PRINTF		test_printf

//======================================================================
// declare
void test_vprintf(const char* fmt, va_list va);
void test_printf(const char* fmt, ...);

//======================================================================
// include
#include "../include/gtest/iutest_switch.hpp"
#include "../include/gtest/iutest_assertion_only.hpp"

#ifdef IUTEST_USE_GTEST
static ::std::stringstream s_outstream;
#else
static ::iutest::detail::iuStringStream::type s_outstream;
#endif

void test_vprintf(const char* fmt, va_list va)
{
	char buf[4096];
	vsprintf(buf, fmt, va);
	s_outstream << buf;
}

void test_printf(const char* fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	test_vprintf(fmt, va);
	va_end(va);
}


#ifdef UNICODE
int wmain(int, wchar_t**)
#else
int main(int, char**)
#endif
{
	IUTEST_EXPECT_EQ(0, 1);

#ifndef IUTEST_USE_GTEST
	::std::cout << s_outstream.str();
	if( s_outstream.str().empty() ) return 1;
#endif
	::std::cout << "*** Successful ***" << ::std::endl;
	return 0;
}

