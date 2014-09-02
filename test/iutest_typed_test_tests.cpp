//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_typed_test_tests.cpp
 * @brief		typed test test
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
#include "iutest.hpp"

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

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_VARIADIC_MACROS)

template<typename T>
class TypedTest3 : public TypedTest<T> {};
IUTEST_TYPED_TEST_CASE(TypedTest3, ::iutest::Types<int, float>);

IUTEST_TYPED_TEST(TypedTest3, Mul2)
{
	TypeParam x = 1;
	IUTEST_ASSERT_EQ(x+x, 2*x);
}

#endif

#if !defined(IUTEST_USE_GTEST)

template<typename T>
class MultiTypedTest : public ::iutest::Test
{
};
typedef ::iutest::Types< ::iutest::Types<int, float>, ::iutest::Types<int, double> > MultiTypedTestTypes;

IUTEST_TYPED_TEST_CASE(MultiTypedTest, MultiTypedTestTypes);

IUTEST_TYPED_TEST(MultiTypedTest, Get)
{
	typedef typename TypeParam:: template get<0>::type	Type1;
	typedef typename TypeParam:: template get<1>::type	Type2;
	
	::iutest::StaticAssertTypeEq< Type1, int >();
	IUTEST_SUCCEED() << ::iutest::detail::GetTypeName< Type1 >();
	IUTEST_SUCCEED() << ::iutest::detail::GetTypeName< Type2 >();
}

#endif

#endif
