//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_prod_tests.cpp
 * @brief		product code access test
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

namespace prod_test
{

class ProdClass
{
	IUTEST_FRIEND_TEST(ProdTest, Friend);
	IUTEST_FRIEND_TEST(ProdFixtureTest, Friend);
#if IUTEST_HAS_PARAM_TEST	
	IUTEST_FRIEND_TEST(ProdParamTest, Friend);
#endif
#if IUTEST_HAS_TYPED_TEST
	IUTEST_FRIEND_TYPED_TEST(ProdTypedTest, Friend);
#endif
	
public:
	ProdClass(void) : m_dummy(0), m_x(0), m_z(0), m_c(42) {}
	ProdClass(const ProdClass& rhs) : m_dummy(rhs.m_dummy), m_x(rhs.m_x), m_z(rhs.m_z), m_c(42) {}

	int	GetX(void) const { return m_x; }
	int	GetZ(void) const { return m_z; }
private:
	int m_dummy;
	int m_x;
	int m_z;
	const int m_c;
	void SetX(int x) { m_x = x; }
	int	ConstGetX(void) const { return m_x; }

public:
	static int GetY(void)	{ return m_y; }
private:
	static int m_y;
	static void SetY(int y)	{ m_y = y; }
private:
	ProdClass& operator = (const ProdClass&);
};

int ProdClass::m_y = 0;

static ProdClass s_prod;

// IUTEST_FRIEND_TEST を使ってのアクセス
IUTEST(ProdTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_ASSERT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

class ProdFixtureTest : public ::iutest::Test {};

IUTEST_F(ProdFixtureTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_ASSERT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

#if IUTEST_HAS_PARAM_TEST

class ProdParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_CASE_P(X, ProdParamTest, ::iutest::Values(0));

IUTEST_P(ProdParamTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_ASSERT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class ProdTypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE(ProdTypedTest, int);

IUTEST_TYPED_TEST(ProdTypedTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_ASSERT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

#endif

#if IUTEST_HAS_PEEP

// peep を使ってのアクセス
IUTEST_MAKE_PEEP(int ProdClass::*, ProdClass, m_x);
IUTEST_MAKE_PEEP(const int ProdClass::*, ProdClass, m_c);

IUTEST(ProdTest, Peep)
{
	// マクロ版
	IUTEST_PEEP_GET(s_prod, ProdClass, m_x) = 4;
	IUTEST_ASSERT_EQ(4, s_prod.GetX());

	IUTEST_ASSERT_EQ(4, IUTEST_PEEP_GET(s_prod, ProdClass, m_x));

	// object 版
	IUTEST_PEEP(ProdClass, m_x) prod_class_x(&s_prod);
	prod_class_x = 5;
	IUTEST_ASSERT_EQ(5, s_prod.GetX());
	prod_class_x += prod_class_x;
	IUTEST_ASSERT_EQ(10, s_prod.GetX());

	IUTEST_ASSERT_EQ(10, prod_class_x);
}

IUTEST(ProdTest, PeepConst)
{
	// マクロ版
	IUTEST_ASSERT_EQ(42, IUTEST_PEEP_GET(s_prod, ProdClass, m_c));

	// object 版
	IUTEST_PEEP(ProdClass, m_c) prod_class_c(&s_prod);
	IUTEST_ASSERT_EQ(42, prod_class_c);
}

IUTEST_MAKE_PEEP(int *, ProdClass, m_y);

IUTEST(ProdTest, StaticPeep)
{
	IUTEST_PEEP_STATIC_GET(ProdClass, m_y) = 4;
	IUTEST_ASSERT_EQ(4, ProdClass::GetY());

	IUTEST_ASSERT_EQ(4, IUTEST_PEEP_STATIC_GET(ProdClass, m_y));

	// object 版
	IUTEST_PEEP(ProdClass, m_y) prod_class_y;
	prod_class_y = 5;
	IUTEST_ASSERT_EQ(5, ProdClass::GetY());
	prod_class_y *= 2;
	IUTEST_ASSERT_EQ(10, ProdClass::GetY());
	IUTEST_PEEP(ProdClass, m_y)(1);

	IUTEST_ASSERT_EQ(1, prod_class_y);
}

#if IUTEST_HAS_PEEP_FUNC

typedef void (ProdClass::* ProdClassSetX)(int);
typedef int (ProdClass::* ProdClassGetX)() const;
IUTEST_MAKE_PEEP(ProdClassSetX, ProdClass, SetX);
IUTEST_MAKE_PEEP(ProdClassGetX, ProdClass, ConstGetX);

IUTEST(ProdTest, PeepFunction)
{
	IUTEST_PEEP_GET(s_prod, ProdClass, SetX)(100);
	IUTEST_ASSERT_EQ(100, s_prod.GetX());
	IUTEST_ASSERT_EQ(100, IUTEST_PEEP_GET(s_prod, ProdClass, ConstGetX)());

	IUTEST_PEEP(ProdClass, SetX) peep_set(&s_prod);
	peep_set(101);
	IUTEST_ASSERT_EQ(101, s_prod.GetX());

	IUTEST_PEEP(ProdClass, ConstGetX) peep_get(&s_prod);
	IUTEST_ASSERT_EQ(101, peep_get());
}

#endif

#if IUTEST_HAS_PEEP_STATIC_FUNC

typedef void (* ProdClassSetY)(int);
IUTEST_MAKE_PEEP(ProdClassSetY, ProdClass, SetY);

IUTEST(ProdTest, StaticPeepFunction)
{
	IUTEST_PEEP_STATIC_GET(ProdClass, SetY)(100);
	IUTEST_ASSERT_EQ(100, ProdClass::GetY());

	// object 版
	IUTEST_PEEP(ProdClass, SetY) peep;
	peep(101);
	IUTEST_ASSERT_EQ(101, ProdClass::GetY());
}

#endif

#endif

}


#if IUTEST_HAS_PEEP

// peep を使ってのアクセス
IUTEST_MAKE_SCOPED_PEEP(int prod_test::ProdClass::*, prod_test, ProdClass, m_z);
IUTEST_MAKE_PEEP(int prod_test::ProdClass::*, prod_test::ProdClass, m_x);

IUTEST(ProdTest, ScopedPeep)
{
	// マクロ版
	{
		// IUTEST_MAKE_SCOPED_PEEP を使用した場合は、クラス名のみでも OK.
		IUTEST_PEEP_GET(prod_test::s_prod, ProdClass, m_z) = 4;
		IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetZ());

		IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_z));
	}
	{
		// IUTEST_MAKE_PEEP を使用した場合は、スコープ必須
		IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x) = 4;
		IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetX());

		IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x));
	}

	// object 版
	{
		// IUTEST_MAKE_SCOPED_PEEP を使用した場合は、クラス名のみでも OK.
		IUTEST_PEEP(ProdClass, m_z) prod_class_z(&prod_test::s_prod);
		prod_class_z = 5;
		IUTEST_EXPECT_EQ(5, prod_test::s_prod.GetZ());

		IUTEST_EXPECT_EQ(5, prod_class_z);
	}
	{
		IUTEST_PEEP(prod_test::ProdClass, m_z) prod_class_z(&prod_test::s_prod);
		prod_class_z = 5;
		IUTEST_EXPECT_EQ(5, prod_test::s_prod.GetZ());

		IUTEST_EXPECT_EQ(5, prod_class_z);
	}
	{
		// deprecated
		IUTEST_SCOPED_PEEP(prod_test, ProdClass, m_z) prod_class_z(&prod_test::s_prod);
		prod_class_z = 7;
		IUTEST_EXPECT_EQ(7, prod_test::s_prod.GetZ());

		IUTEST_EXPECT_EQ(7, prod_class_z);
	}
}

#endif
