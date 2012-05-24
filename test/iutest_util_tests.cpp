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

IUTEST(AssertionTest, OREQ)
{
	int x=1;
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::NE>::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::LE>::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::LT>::Comp, x, 2);
	IUTEST_EXPECT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::GE>::Comp, x, 1);
	IUTEST_INFORM_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::GT>::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1);
	IUTEST_INFORM_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, x, 1);
	IUTEST_ASSERT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 2, 0);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 2, 0, 1);
	IUTEST_ASSERT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 2, 3, 0);
	IUTEST_ASSERT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 3, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 2, 3, 0, 1);
}

