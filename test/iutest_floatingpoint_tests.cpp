//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_floatingpoint_tests.cpp
 * @brief		iutest float test
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
#include <cmath>

namespace floationgpoint_test
{

template<typename T>
class FloatingpointTest : public ::iutest::Test
{
public:
	typedef iutest::floating_point<T>	ftype;

	static T ONE;
	static T ZERO;
};
template<typename T>
T FloatingpointTest<T>::ONE = (T)1;
template<typename T>
T FloatingpointTest<T>::ZERO = (T)0;

typedef ::iutest::Types<float, double> FloatingpointTestTypes;
IUTEST_TYPED_TEST_CASE(FloatingpointTest, FloatingpointTestTypes);

IUTEST_TYPED_TEST(FloatingpointTest, NaN)
{
	typedef typename TestFixture::ftype FloatType;
	TypeParam a=TestFixture::ONE;
	TypeParam b=TestFixture::ZERO;

	IUTEST_EXPECT_EQ(FloatType(a/b)   , TestFixture::ftype::PINF());
	IUTEST_EXPECT_EQ(FloatType(log(b)), TestFixture::ftype::NINF());
	
	IUTEST_EXPECT_EQ(FloatType(sqrt(-a)), TestFixture::ftype::NQNAN());
}

}

