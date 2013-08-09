//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_fixture_tests.cpp
 * @brief		iutest fixture test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

class TestSetUpEachCall : public ::iutest::Test
{
protected:
	static int x;
public:
	virtual void SetUp(void)
	{
		++x;
	}
	static void SetUpTestCase(void)
	{
		x = 0;
	}
};
int TestSetUpEachCall::x = -1;

IUTEST_F(TestSetUpEachCall, Test1)
{
	IUTEST_ASSERT_EQ(1, x);
}

IUTEST_F(TestSetUpEachCall, Test2)
{
	IUTEST_ASSERT_EQ(2, x);
}

class TestFixture : public ::iutest::Test
{
public:
	static int x;
public:
	static void SetUpTestCase(void)
	{
		IUTEST_ASSERT_EQ(-1, x);
		x = 0;
	}
	virtual void SetUp(void)
	{
		IUTEST_ASSERT_EQ(0, x);
		++x;
	}
	virtual void TearDown(void)
	{
		IUTEST_ASSERT_EQ(2, x);
		++x;
	}
	static void TearDownTestCase(void)
	{
		IUTEST_ASSERT_EQ(3, x);
		x = -1;
	}
};
int TestFixture::x = -1;

IUTEST_F(TestFixture, Test)
{
	IUTEST_ASSERT_EQ(1, x);
	++x;
}
