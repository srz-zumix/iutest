//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_static_assertion_tests.cpp
 * @brief		iutest StaticAssertTypeEq アサーション test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_switch.hpp"

bool b = ::iutest::StaticAssertTypeEq<int, int>();

IUTEST(StaticAssertTypeEqTest, OK)
{
	::iutest::StaticAssertTypeEq<float, float>();
	IUTEST_STATIC_ASSERT(true);
}
