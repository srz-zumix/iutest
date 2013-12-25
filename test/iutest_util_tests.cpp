//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_tests.cpp
 * @brief		iutest util test
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
#include "../include/gtest/iutest_switch.hpp"

IUTEST(UtilTest, Find)
{
	IUTEST_ASSERT_NOTNULL(::iuutil::FindTestCase("UtilTest"));
	IUTEST_ASSERT_NOTNULL(::iuutil::FindTestInfo("UtilTest", "Find"));

	IUTEST_ASSERT_NULL(::iuutil::FindTestCase("UtilTestXXX"));
	IUTEST_ASSERT_NULL(::iuutil::FindTestInfo("UtilTest", "FindXXX"));
	IUTEST_ASSERT_NULL(::iuutil::FindTestInfo("UtilTestXXX", "Find"));
}

IUTEST(AssertionTest, EQ_COLLECTIONS)
{
	{
		int  a[] = { 0, 1, 2, 3, 4 };
		int  b[] = { 0, 1, 2, 3, 4 };
		char c[] = { 0, 1, 2, 3, 4 };
		
		IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
		IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
		IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));

		IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
		IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
		IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
	}

	{
		int  d[] = { 0, 1, 2, 3, 4 };
		const int COUNT=sizeof(d)/sizeof(d[0]);
		::std::vector<int> a, b;
		::std::vector<char> c;
		for( int i=0; i < COUNT; ++i )
		{
			a.push_back(i);
			b.push_back(i);
			c.push_back(i);
		}
		IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
		IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
		IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
		IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());

		IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
		IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
		IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
		IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());

		IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
		IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
		IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
	}
}

IUTEST(AssertionTest, EQ_RANGE)
{
	{
		int  a[] = { 0, 1, 2, 3, 4 };
		int  b[] = { 0, 1, 2, 3, 4 };
		char c[] = { 0, 1, 2, 3, 4 };
		
		IUTEST_ASSERT_EQ_RANGE(a, b);
		IUTEST_EXPECT_EQ_RANGE(a, b);
		IUTEST_INFORM_EQ_RANGE(a, b);
		IUTEST_ASSUME_EQ_RANGE(a, b);

		IUTEST_ASSERT_EQ_RANGE(a, c);
		IUTEST_EXPECT_EQ_RANGE(a, c);
		IUTEST_INFORM_EQ_RANGE(a, c);
		IUTEST_ASSUME_EQ_RANGE(a, c);
#if IUTEST_HAS_INITIALIZER_LIST
		IUTEST_ASSERT_EQ_RANGE(::std::initializer_list<int>({0,1,2,3,4}), a);
#endif
	}

	{
		int  d[] = { 0, 1, 2, 3, 4 };
		const int COUNT=sizeof(d)/sizeof(d[0]);
		::std::vector<int> a, b;
		::std::vector<char> c;
		for( int i=0; i < COUNT; ++i )
		{
			a.push_back(i);
			b.push_back(i);
			c.push_back(i);
		}
		IUTEST_ASSERT_EQ_RANGE(a, b);
		IUTEST_EXPECT_EQ_RANGE(a, b);
		IUTEST_INFORM_EQ_RANGE(a, b);
		IUTEST_ASSUME_EQ_RANGE(a, b);

		IUTEST_ASSERT_EQ_RANGE(a, c);
		IUTEST_EXPECT_EQ_RANGE(a, c);
		IUTEST_INFORM_EQ_RANGE(a, c);
		IUTEST_ASSUME_EQ_RANGE(a, c);

		IUTEST_ASSERT_EQ_RANGE(a, d);
		IUTEST_EXPECT_EQ_RANGE(a, d);
		IUTEST_INFORM_EQ_RANGE(a, d);
		IUTEST_ASSUME_EQ_RANGE(a, d);

		IUTEST_ASSERT_EQ_RANGE(d, c);
		IUTEST_EXPECT_EQ_RANGE(d, c);
		IUTEST_INFORM_EQ_RANGE(d, c);
		IUTEST_ASSUME_EQ_RANGE(d, c);
	}
}

IUTEST(AssertionTest, STRIN)
{
	const char test[] = "test";
	IUTEST_ASSERT_STRIN("tes", test);
	IUTEST_EXPECT_STRIN("tes", test);
	IUTEST_INFORM_STRIN("tes", test);
	IUTEST_ASSUME_STRIN("tes", test);

	IUTEST_ASSERT_STRIN("test", test);
	IUTEST_EXPECT_STRIN("test", test);
	IUTEST_INFORM_STRIN("test", test);
	IUTEST_ASSUME_STRIN("test", test);
}

IUTEST(AssertionTest, STRNOTIN)
{
	const char test[] = "test";
	IUTEST_ASSERT_STRNOTIN("Tes", test);
	IUTEST_EXPECT_STRNOTIN("Tes", test);
	IUTEST_INFORM_STRNOTIN("Tes", test);
	IUTEST_ASSUME_STRNOTIN("Tes", test);

	IUTEST_ASSERT_STRNOTIN(NULL, test);
	IUTEST_EXPECT_STRNOTIN(NULL, test);
	IUTEST_INFORM_STRNOTIN(NULL, test);
	IUTEST_ASSUME_STRNOTIN(NULL, test);
}

IUTEST(AssertionTest, STRLNEQ)
{
	const char test[] = "test";
	IUTEST_ASSERT_STRLNEQ(4, test);
	IUTEST_EXPECT_STRLNEQ(4, test);
	IUTEST_INFORM_STRLNEQ(4, test);
	IUTEST_ASSUME_STRLNEQ(4, test);
}

IUTEST(AssertionTest, OREQ)
{
	int x=1;
	IUTEST_ASSERT_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::NE >::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::LE >::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::LT >::Comp, x, 2);
	IUTEST_EXPECT_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::GE >::Comp, x, 1);
	IUTEST_INFORM_PRED_FORMAT2(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::GT >::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT3(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT3(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 0, 1);
	IUTEST_INFORM_PRED_FORMAT3(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, x, 1);
	IUTEST_ASSERT_PRED_FORMAT4(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 1, 2, 0);
	IUTEST_EXPECT_PRED_FORMAT4(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT4(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 2, 0, 1);
	IUTEST_ASSERT_PRED_FORMAT5(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 1, 2, 3, 0);
	IUTEST_ASSERT_PRED_FORMAT5(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED_FORMAT5(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 3, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT5(::iuutil::CmpHelperOR< ::iuutil::CmpHelper::EQ >::Comp, x, 2, 3, 0, 1);
}

