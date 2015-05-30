//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_static_assertion_failure_tests.cpp
 * @brief		StaticAssertTypeEq fail test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

IUTEST_TEST_COMPILEERROR("false")
bool b = ::iutest::StaticAssertTypeEq<int, float>();

IUTEST(StaticAssertTypeEqTest, Fail)
{
	IUTEST_TEST_COMPILEERROR("false")
	::iutest::StaticAssertTypeEq<float, int>();
	
	IUTEST_TEST_COMPILEERROR("false")
	IUTEST_STATIC_ASSERT(false);
}

#endif
