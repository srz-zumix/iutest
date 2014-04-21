//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_prod_tests1.cpp
 * @brief		product code access test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_prod_tests.hpp"

namespace prod_test
{

int ProdClass::m_y = 0;

}

namespace prod_test
{

static ProdClass s_prod;

// IUTEST_FRIEND_TEST を使ってのアクセス
IUTEST(ProdTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_EXPECT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_EXPECT_EQ(2, s_prod.GetX());
}

class ProdFixtureTest : public ::iutest::Test {};

IUTEST_F(ProdFixtureTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_EXPECT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_EXPECT_EQ(2, s_prod.GetX());
}

#if IUTEST_HAS_PARAM_TEST

class ProdParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_CASE_P(X, ProdParamTest, ::iutest::Values(0));

IUTEST_P(ProdParamTest, Friend)
{
	s_prod.SetX(1);
	IUTEST_EXPECT_EQ(1, s_prod.GetX());

	s_prod.m_x = 2;
	IUTEST_EXPECT_EQ(2, s_prod.GetX());
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

static ProdClass2 s_prod2;

// peep を使ってのアクセス
IUTEST_MAKE_PEEP(int ProdClass::*, ProdClass, m_x);
IUTEST_MAKE_PEEP(const int ProdClass::*, ProdClass, m_c);

IUTEST_MAKE_PEEP(int ProdClass2::*, ProdClass2, m_x);

IUTEST(ProdTest, PeepMacro)
{
	IUTEST_PEEP_GET(s_prod, ProdClass, m_x) = 4;
	IUTEST_EXPECT_EQ(4, s_prod.GetX());

	IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(s_prod, ProdClass, m_x));

	IUTEST_PEEP_GET(s_prod2, ProdClass2, m_x) = 42;
	IUTEST_EXPECT_EQ(42, s_prod2.GetX());
	
	IUTEST_EXPECT_EQ(42, IUTEST_PEEP_GET(s_prod2, ProdClass2, m_x));
}
	
IUTEST(ProdTest, PeepObject)
{
	IUTEST_PEEP(ProdClass, m_x) prod_class_x(&s_prod);
	prod_class_x = 5;
	IUTEST_EXPECT_EQ(5, s_prod.GetX());
	prod_class_x += prod_class_x;
	IUTEST_EXPECT_EQ(10, s_prod.GetX());

	IUTEST_EXPECT_EQ(10, prod_class_x);

	IUTEST_PEEP(ProdClass2, m_x) prod_class2_x(&s_prod2);
	prod_class2_x = 54;
	IUTEST_EXPECT_EQ(54, s_prod2.GetX());
	prod_class2_x += prod_class2_x;
	IUTEST_EXPECT_EQ(108, s_prod2.GetX());

	IUTEST_EXPECT_EQ(108, prod_class2_x);
}

IUTEST(ProdTest, PeepA1)
{
	IUTEST_PEEP_GET(s_prod, ProdClass, m_a) = 1;
	IUTEST_EXPECT_EQ(1, s_prod.GetA());

	IUTEST_EXPECT_EQ(1, IUTEST_PEEP_GET(s_prod, ProdClass, m_a));
}

IUTEST(ProdTest, PeepConst)
{
	// マクロ版
	IUTEST_EXPECT_EQ(42, IUTEST_PEEP_GET(s_prod, ProdClass, m_c));

	// object 版
	IUTEST_PEEP(ProdClass, m_c) prod_class_c(&s_prod);
	IUTEST_EXPECT_EQ(42, prod_class_c);
}

IUTEST_MAKE_PEEP(int *, ProdClass, m_y);

IUTEST(ProdTest, StaticPeep)
{
	IUTEST_PEEP_STATIC_GET(ProdClass, m_y) = 4;
	IUTEST_EXPECT_EQ(4, ProdClass::GetY());

	IUTEST_EXPECT_EQ(4, IUTEST_PEEP_STATIC_GET(ProdClass, m_y));

	// object 版
	IUTEST_PEEP(ProdClass, m_y) prod_class_y;
	prod_class_y = 5;
	IUTEST_EXPECT_EQ(5, ProdClass::GetY());
	prod_class_y *= 2;
	IUTEST_EXPECT_EQ(10, ProdClass::GetY());

	IUTEST_PEEP(ProdClass, m_y)(1);
	IUTEST_EXPECT_EQ(1, prod_class_y);

	IUTEST_PEEP(ProdClass, m_y) prod_class_y2 = 2;
	IUTEST_EXPECT_EQ(2, prod_class_y2);
}

#if IUTEST_HAS_PEEP_FUNC

typedef void (ProdClass::* ProdClassSetX)(int);
typedef int (ProdClass::* ProdClassGetX)() const;
IUTEST_MAKE_PEEP(ProdClassSetX, ProdClass, SetX);
IUTEST_MAKE_PEEP(ProdClassGetX, ProdClass, ConstGetX);

IUTEST(ProdTest, PeepFunction)
{
	IUTEST_PEEP_GET(s_prod, ProdClass, SetX)(100);
	IUTEST_EXPECT_EQ(100, s_prod.GetX());
	IUTEST_EXPECT_EQ(100, IUTEST_PEEP_GET(s_prod, ProdClass, ConstGetX)());

	IUTEST_PEEP(ProdClass, SetX) peep_set(&s_prod);
	peep_set(101);
	IUTEST_EXPECT_EQ(101, s_prod.GetX());

	IUTEST_PEEP(ProdClass, ConstGetX) peep_get(&s_prod);
	IUTEST_EXPECT_EQ(101, peep_get());
}

#endif

#if IUTEST_HAS_PEEP_STATIC_FUNC

typedef void (* ProdClassSetY)(int);
IUTEST_MAKE_PEEP(ProdClassSetY, ProdClass, SetY);

IUTEST(ProdTest, StaticPeepFunction)
{
	IUTEST_PEEP_STATIC_GET(ProdClass, SetY)(100);
	IUTEST_EXPECT_EQ(100, ProdClass::GetY());

	// object 版
	IUTEST_PEEP(ProdClass, SetY) peep;
	peep(101);
	IUTEST_EXPECT_EQ(101, ProdClass::GetY());
}

#endif

#endif

}


#if IUTEST_HAS_PEEP

// peep を使ってのアクセス
IUTEST_MAKE_PEEP(int prod_test::ProdClass::*, prod_test::ProdClass, m_z);
IUTEST_MAKE_PEEP(int prod_test::ProdClass::*, prod_test::ProdClass, m_x);

IUTEST(ProdTest, ScopedPeep)
{
	// マクロ版
	{
		IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_z) = 4;
		IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetZ());

		IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_z));
	}
	{
		IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x) = 4;
		IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetX());

		IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x));
	}

	// object 版
	{
		IUTEST_PEEP(prod_test::ProdClass, m_z) prod_class_z(&prod_test::s_prod);
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
}

#endif
