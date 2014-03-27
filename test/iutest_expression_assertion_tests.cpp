//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_expression_assertion_tests.cpp
 * @brief		iutest expression assertion test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

int f(void)
{
	return 42;
}
bool g(void)
{
	return false;
}

IUTEST(Expression, Success)
{
	IUTEST_ASSERT(true);
	IUTEST_ASSERT(f());
	IUTEST_ASSERT(f() == 42);
	IUTEST_ASSERT(f() != 41);
	IUTEST_ASSERT(f() <= 42);
	IUTEST_ASSERT(f() >= 42);
	IUTEST_ASSERT(f() <  50);
	IUTEST_ASSERT(f() >  40);
	IUTEST_ASSERT(f() &   2);
	IUTEST_ASSERT(f() |   1);
	IUTEST_ASSERT(f() &&  1);
	IUTEST_ASSERT(f() ||  0);
	IUTEST_ASSERT(f() != 42 || g() == false );
}

#if !defined(IUTEST_USE_GTEST)
#  define CHECK_FATAL_FAILURE(expr, str)	IUTEST_ASSERT_FATAL_FAILURE(expr, str)
#else
#  define CHECK_FATAL_FAILURE(expr, str)	IUTEST_ASSERT_FATAL_FAILURE(expr, "")
#endif

IUTEST(Expression, Fail)
{
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(false), "expansion: false");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(!f()) , "expansion: false");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() == 41), "expansion: 42 == 41");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42), "expansion: 42 != 42");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() <  41), "expansion: 42 < 41");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() <= 41), "expansion: 42 <= 41");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() >  43), "expansion: 42 > 43");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() >= 43), "expansion: 42 >= 43");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() &   1), "expansion: 42 & 1");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(g() |   0), "expansion: false | 0");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(g() &&  0), "expansion: false && 0");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(g() ||  0), "expansion: false || 0");
	CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42 || f() == 32 ), "expansion: 42 != 42 || false");
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

