//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_typed_test_tests.cpp
 * @brief		iutest typed test test
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

#if IUTEST_HAS_TYPED_TEST

//======================================================================
// class
template<typename T>
class TypedTest : public ::iutest::Test
{
public:
	static T value;
};

template<typename T>
T TypedTest<T>::value = 0;

typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_CASE(TypedTest, TypedTestTypes);


IUTEST_TYPED_TEST(TypedTest, Mul2)
{
	TypeParam x = 1;
	IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST(TypedTest, StaticMul2)
{
	TestFixture::value = 1;
	IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

template<typename T>
class TypedTest2 : public TypedTest<T> {};
IUTEST_TYPED_TEST_CASE(TypedTest2, float);


IUTEST_TYPED_TEST(TypedTest2, Mul2)
{
	TypeParam x = 1;
	IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST(TypedTest2, StaticMul2)
{
	TestFixture::value = 1;
	IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

#endif
