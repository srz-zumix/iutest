//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        floatingpoint_tests.cpp
 * @brief       float/double test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <cmath>
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

#if IUTEST_HAS_TYPED_TEST

namespace floatingpoint_test
{

template<typename T>
class FloatingpointTest : public ::iutest::Test
{
public:
    typedef ::iutest::floating_point<T> ftype;

    static T ONE;
    static T ZERO;
};
template<typename T>
T FloatingpointTest<T>::ONE = static_cast<T>(1);
template<typename T>
T FloatingpointTest<T>::ZERO = static_cast<T>(0);

typedef ::iutest::Types<float, double> FloatingpointTestTypes;
IUTEST_TYPED_TEST_SUITE(FloatingpointTest, FloatingpointTestTypes);

IUTEST_TYPED_TEST(FloatingpointTest, PINF)
{
    typedef typename TestFixture::ftype FloatType;
    TypeParam a=TestFixture::ONE;
    TypeParam b=TestFixture::ZERO;

    IUTEST_EXPECT_EQ(FloatType(a/b), FloatType::PINF());
}

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION()

IUTEST_TYPED_TEST(FloatingpointTest, NINF)
{
    typedef typename TestFixture::ftype FloatType;
    const TypeParam b=TestFixture::ZERO;
    const TypeParam lb=static_cast<TypeParam>(log(b));
    IUTEST_EXPECT_EQ(FloatType(lb), FloatType::NINF());
}

// MinGW-w64 sqrt bug
// https://sourceforge.net/p/mingw/bugs/2337/
#if !defined(__MINGW64__)
IUTEST_TYPED_TEST(FloatingpointTest, IsNAN)
{
    IUTEST_ASSUME_TRUE(::std::numeric_limits<TypeParam>::is_iec559);

    const TypeParam a=TestFixture::ONE;
    const TypeParam sq=static_cast<TypeParam>(sqrt(-a));
    IUTEST_EXPECT_NAN(sq);
}
#endif

IUTEST_PRAGMA_WARN_POP()

}   // end of namespace floatingpoint_test

#endif

#endif
