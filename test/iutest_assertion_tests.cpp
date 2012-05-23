//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assertion_tests.cpp
 * @brief		iutest assertion test
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
#include "../include/iutest.hpp"

IUTEST(AssertionTest, True)
{
	IUTEST_ASSERT_TRUE(true);
	IUTEST_EXPECT_TRUE(true);
	IUTEST_INFORM_TRUE(true);
	IUTEST_ASSERT_TRUE(1);
	IUTEST_ASSERT_TRUE(100==100);
}

IUTEST(AssertionTest, False)
{
	IUTEST_ASSERT_FALSE(false);
	IUTEST_EXPECT_FALSE(false);
	IUTEST_INFORM_FALSE(false);
	IUTEST_ASSERT_FALSE(0);
	IUTEST_ASSERT_FALSE(100!=100);
}

IUTEST(AssertionTest, EQ)
{
	int x0=0, y0=0;
	IUTEST_ASSERT_EQ(x0, y0);
	IUTEST_EXPECT_EQ(x0, y0);
	IUTEST_INFORM_EQ(x0, y0);
	int* zero=NULL;
	IUTEST_ASSERT_EQ(NULL, zero);
#if IUTEST_HAS_NULLPTR
	IUTEST_ASSERT_EQ(nullptr, zero);
	IUTEST_ASSERT_EQ(zero, nullptr);
#endif

	std::vector<int> v1, v2;
	IUTEST_ASSERT_EQ(v1, v2);
	IUTEST_EXPECT_EQ(v1, v2);
	IUTEST_INFORM_EQ(v1, v2);
}

IUTEST(AssertionTest, NE)
{
	int x0=0, x1=1;
	IUTEST_ASSERT_NE(x0, x1);
	IUTEST_EXPECT_NE(x0, x1);
	IUTEST_INFORM_NE(x0, x1);
	int* one=(int*)1;
	IUTEST_ASSERT_NE(NULL, one);
	
#if IUTEST_HAS_NULLPTR
	IUTEST_ASSERT_NE(nullptr, one);
	IUTEST_ASSERT_NE(one, nullptr);
#endif
}

IUTEST(AssertionTest, LT)
{
	int x0=0, x1=1;
	float f0=0.0f, f1=1.0f;
	double d0=0.0, d1=1.0;
	IUTEST_ASSERT_LT(x0, x1);
	IUTEST_EXPECT_LT(d0, d1);
	IUTEST_INFORM_LT(0.0, 0x1);
	IUTEST_ASSERT_LT(f0, f1);
}

IUTEST(AssertionTest, LE)
{
	int x0=0, y0=0;
	float f0=0.0f, f1=1.0f;
	double d0=0.0, d1=1.0;
	IUTEST_ASSERT_LE(x0, y0);
	IUTEST_EXPECT_LE(f0, f1);
	IUTEST_INFORM_LE(0.0, 0x1);
	IUTEST_EXPECT_LE(d0, d1);
}

IUTEST(AssertionTest, GT)
{
	int x0=0, x1=1;
	float f0=0.0f, f1=1.0f;
	double d0=0.0, d1=1.0;
	IUTEST_EXPECT_GT(f1, f0);
	IUTEST_ASSERT_GT(x1, x0);
	IUTEST_EXPECT_GT(d1, d0);
	IUTEST_INFORM_GT(0x1, 0.0f);
}

IUTEST(AssertionTest, GE)
{
	int x0=0, y0=0;
	float f0=0.0f, f1=1.0f;
	double d0=0.0, d1=1.0;
	IUTEST_ASSERT_GE(x0, y0);
	IUTEST_EXPECT_GE(f1, f0);
	IUTEST_INFORM_GE(0x1, 0.0f);
	IUTEST_INFORM_GE(d1, d0);
}

IUTEST(AssertionTest, Float)
{
	float f0=0.0f, f1=1.0f;
	IUTEST_ASSERT_FLOAT_EQ(1.0f, f1);
	IUTEST_EXPECT_FLOAT_EQ(0.0f, f0);
	IUTEST_INFORM_FLOAT_EQ(-1.0f, -2.0f/2.0f);
}

IUTEST(AssertionTest, Double)
{
	double d0=0.0, d1=1.0;
	IUTEST_ASSERT_DOUBLE_EQ(1.0, d1);
	IUTEST_EXPECT_DOUBLE_EQ(0.0, d0);
	IUTEST_INFORM_DOUBLE_EQ(-1.0, -2.0/2.0);
}

IUTEST(AssertionTest, Near)
{
	IUTEST_ASSERT_NEAR(0, 1, 2);
	IUTEST_EXPECT_NEAR(1.0f, 4.0f, 4);
	IUTEST_INFORM_NEAR(2.0, 1.0, 2);
}

IUTEST(AssertionTest, Null)
{
	int* p1 = NULL;
	IUTEST_ASSERT_NULL(p1);
	IUTEST_EXPECT_NULL(p1);
	IUTEST_INFORM_NULL(p1);
	
	void* p2 = &p1;
	IUTEST_ASSERT_NOTNULL(p2);
	IUTEST_EXPECT_NOTNULL(p2);
	IUTEST_INFORM_NOTNULL(p2);
}

IUTEST(AssertionTest, Same)
{
	int v = 0;
	int* p1 = &v;
	IUTEST_ASSERT_SAME(v, *p1);
	IUTEST_EXPECT_SAME(v, *p1);
	IUTEST_INFORM_SAME(v, *p1);
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(AssertionTest, HResult)
{
	IUTEST_ASSERT_HRESULT_SUCCEEDED(0);
	IUTEST_EXPECT_HRESULT_SUCCEEDED(0);
	IUTEST_INFORM_HRESULT_SUCCEEDED(0);
	IUTEST_ASSERT_HRESULT_FAILED(-1);
	IUTEST_EXPECT_HRESULT_FAILED(-1);
	IUTEST_INFORM_HRESULT_FAILED(-1);
}

#endif

