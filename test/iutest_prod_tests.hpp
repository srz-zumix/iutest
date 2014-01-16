//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_prod_tests.hpp
 * @brief		product code access test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_iutest_prod_tests_HPP_
#define INCG_iutest_prod_tests_HPP_

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
	ProdClass(void) : m_dummy(0), m_x(0), m_z(0), m_a(0), m_c(42) {}
	ProdClass(const ProdClass& rhs) : m_dummy(rhs.m_dummy), m_x(rhs.m_x), m_z(rhs.m_z), m_a(rhs.m_a), m_c(42) {}

	int	GetA(void) const { return m_a; }
	int	GetX(void) const { return m_x; }
	int	GetZ(void) const { return m_z; }
private:
	int m_dummy;
	int m_x;
	int m_z;
	int m_a;
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

class ProdClass2
{
public:
	int GetX(void) { return m_x; }
private:
	int m_x;
};

IUTEST_MAKE_PEEP(int ProdClass::*, ProdClass, m_a);

}	// end of namespace prod_test

#endif
