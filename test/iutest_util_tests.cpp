//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_tests.cpp
 * @brief		iutest_util test
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

IUTEST(UtilTest, Find)
{
	IUTEST_ASSERT_NOTNULL(iuutil::FindTestCase("UtilTest"));
	IUTEST_ASSERT_NOTNULL(iuutil::FindTestInfo("UtilTest", "Find"));

	IUTEST_ASSERT_NULL(iuutil::FindTestCase("UtilTestXXX"));
	IUTEST_ASSERT_NULL(iuutil::FindTestInfo("UtilTest", "FindXXX"));
	IUTEST_ASSERT_NULL(iuutil::FindTestInfo("UtilTestXXX", "Find"));
}


