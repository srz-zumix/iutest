//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_minimum_tests.cpp
 * @brief		ç≈è¨ÉeÉXÉg
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
#include "../include/iutest.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_EQ(1, abs(-1));
}
