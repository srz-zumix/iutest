//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_type_param_tests.hpp
 * @brief		iutest type parameter test
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
#ifndef INCG_iutest_type_param_tests_HPP_
#define INCG_iutest_type_param_tests_HPP_

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_TYPED_TEST_P

//======================================================================
// class
template<typename T>
class TypeParamTest : public ::iutest::Test
{
public:
	static T value;
};

template<typename T>
T TypeParamTest<T>::value = 0;


IUTEST_TYPED_TEST_CASE_P(TypeParamTest);

IUTEST_TYPED_TEST_P(TypeParamTest, Mul2)
{
	TypeParam x = 1;
	IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST_P(TypeParamTest, StaticMul2)
{
	TestFixture::value = 1;
	IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

IUTEST_REGISTER_TYPED_TEST_CASE_P(TypeParamTest, StaticMul2, Mul2);


#endif

#endif
