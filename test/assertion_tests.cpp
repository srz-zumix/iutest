//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion_tests.cpp
 * @brief       iutest assertion test
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
#include "iutest.hpp"

template<int A, int B>
struct add_t { enum result { value = A + B }; };

::iutest::AssertionResult IsEven(int n)
{
    if( n%2 == 0 ) return ::iutest::AssertionSuccess();
    return ::iutest::AssertionFailure() << n << " is odd";
}

IUTEST(AssertionTest, True)
{
    IUTEST_ASSERT_TRUE(true);
    IUTEST_EXPECT_TRUE(true);
    IUTEST_INFORM_TRUE(true);
    IUTEST_EXPECT_TRUE(1);
    IUTEST_EXPECT_TRUE(100==100);
    IUTEST_EXPECT_TRUE(IsEven(2));
#if !defined(IUTEST_NO_VARIADIC_MACROS)
    IUTEST_ASSERT_TRUE(add_t<0, 1>::value);
    IUTEST_EXPECT_TRUE(add_t<0, 1>::value);
    IUTEST_INFORM_TRUE(add_t<0, 1>::value);
    IUTEST_ASSUME_TRUE(add_t<0, 1>::value);
#endif
}

IUTEST(AssertionTest, False)
{
    IUTEST_ASSERT_FALSE(false);
    IUTEST_EXPECT_FALSE(false);
    IUTEST_INFORM_FALSE(false);
    IUTEST_EXPECT_FALSE(0);
    IUTEST_EXPECT_FALSE(100!=100);
#if !defined(IUTEST_NO_VARIADIC_MACROS)
    IUTEST_ASSERT_FALSE(add_t<0, 0>::value);
    IUTEST_EXPECT_FALSE(add_t<0, 0>::value);
    IUTEST_INFORM_FALSE(add_t<0, 0>::value);
    IUTEST_ASSUME_FALSE(add_t<0, 0>::value);
#endif
}

struct Point
{
    int x, y;
    bool operator == (const Point& rhs) const { return x==rhs.x && y==rhs.y; }
};

IUTEST(AssertionTest, EQ)
{
    int x0=0, y0=0;
    char z0=0;
    IUTEST_ASSERT_EQ(x0, y0);
    IUTEST_EXPECT_EQ(x0, z0);
    IUTEST_INFORM_EQ(z0, y0);
    int* zero=NULL;
    IUTEST_ASSERT_EQ(NULL, zero);
#if IUTEST_HAS_NULLPTR
    IUTEST_ASSERT_EQ(nullptr, zero);
    IUTEST_ASSERT_EQ(zero, nullptr);
#endif

#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
    ::std::vector<int> v1, v2;
    IUTEST_ASSERT_EQ(v1, v2);
    IUTEST_EXPECT_EQ(v1, v2);
    IUTEST_INFORM_EQ(v1, v2);

    {
        Point a = {0, 0};
        Point b = {0, 0};

        IUTEST_ASSERT_EQ(a, b);
        IUTEST_EXPECT_EQ(a, b);
        IUTEST_INFORM_EQ(a, b);
    }
#endif

#if IUTEST_HAS_STRONG_ENUMS && IUTEST_HAS_PRINT_TO
    {
        enum class eTest { Var1=1, Var2=1 };
        IUTEST_ASSERT_EQ(eTest::Var1, eTest::Var2);
    }
#endif
}

#if IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT

struct TestObjectX
{
    int a, b, c;
};

IUTEST(AssertionTest, MemCmpEQ)
{
    TestObjectX x={0, 1, 2};
    TestObjectX y={0, 1, 2};
    IUTEST_ASSERT_EQ(x, y);
}

IUTEST(AssertionTest, MemCmpNE)
{
    TestObjectX x={0, 1, 2};
    TestObjectX y={0, 1, 3};
    IUTEST_ASSERT_NE(x, y);
}

#endif

IUTEST(AssertionTest, NE)
{
    int x0=0, x1=1;
    IUTEST_ASSERT_NE(x0, x1);
    IUTEST_EXPECT_NE(x0, x1);
    IUTEST_INFORM_NE(x0, x1);
    int* one=reinterpret_cast<int*>(1);
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
    IUTEST_INFORM_GT(0x1, 0.0f);
    IUTEST_EXPECT_GT(d1, d0);
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

IUTEST(AssertionTest, FloatLE)
{
    float f0=0.0f, f1=1.0f;
    IUTEST_ASSERT_PRED_FORMAT2(::iutest::FloatLE, 1.0f, f1);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::FloatLE, f0, f1);
    IUTEST_INFORM_PRED_FORMAT2(::iutest::FloatLE, -1.0f, -2.0f/2.0f);
}

IUTEST(AssertionTest, Double)
{
    double d0=0.0, d1=1.0;
    IUTEST_ASSERT_DOUBLE_EQ(1.0, d1);
    IUTEST_EXPECT_DOUBLE_EQ(0.0, d0);
    IUTEST_INFORM_DOUBLE_EQ(-1.0, -2.0/2.0);
}

IUTEST(AssertionTest, DoubleLE)
{
    double d0=0.0, d1=1.0;
    IUTEST_ASSERT_PRED_FORMAT2(::iutest::DoubleLE, 1.0, d1);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::DoubleLE, d0, d1);
    IUTEST_INFORM_PRED_FORMAT2(::iutest::DoubleLE, -1.0, -2.0/2.0);
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(AssertionTest, LongDouble)
{
    long double d0=0.0l, d1=1.0l;
    IUTEST_ASSERT_LONG_DOUBLE_EQ(1.0l, d1);
    IUTEST_EXPECT_LONG_DOUBLE_EQ(0.0l, d0);
    IUTEST_INFORM_LONG_DOUBLE_EQ(-1.0l, -2.0l/2.0l);
}

#endif

IUTEST(AssertionTest, Complex)
{
    ::std::complex<float> cf0(0.0f, 2.0f);
    ::std::complex<float> cf1(1.0f, 0.0f);
    ::std::complex<double> cd1(1.0, 0.0);
    IUTEST_ASSERT_COMPLEX_EQ(::std::complex<float>(1.0f, 0.0f), cf1);
    IUTEST_EXPECT_COMPLEX_EQ(::std::complex<float>(0.0f, 2.0f), cf0);
    IUTEST_INFORM_COMPLEX_EQ(1.0f, cf1);
    IUTEST_INFORM_COMPLEX_EQ(cf1, 1.0f);
    IUTEST_INFORM_COMPLEX_EQ(cf1, cd1);
}

IUTEST(AssertionTest, Near)
{
    IUTEST_ASSERT_NEAR(0, 1, 1.5);
    IUTEST_EXPECT_NEAR(1.0f, 4.0f, 3);
    IUTEST_INFORM_NEAR(2.0, 1.0, 2);
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

IUTEST(AssertionTest, HResultSucceeded)
{
    IUTEST_ASSERT_HRESULT_SUCCEEDED(0);
    IUTEST_EXPECT_HRESULT_SUCCEEDED(0);
    IUTEST_INFORM_HRESULT_SUCCEEDED(0);
}

IUTEST(AssertionTest, HResultFailed)
{
    IUTEST_ASSERT_HRESULT_FAILED(-1);
    IUTEST_EXPECT_HRESULT_FAILED(-1);
    IUTEST_INFORM_HRESULT_FAILED(-1);
}

#endif

IUTEST(AssertionTest, ScopedTrace)
{
    {
        int x=100;
        IUTEST_SCOPED_TRACE(::iutest::Message() << "x=" << x);
    }
    {
        IUTEST_SCOPED_TRACE("test");
    }
}

IUTEST(AssertionTest, Cpp11)
{
#if IUTEST_HAS_CHAR16_T
    const char16_t c16[] = u"test";
    IUTEST_EXPECT_STREQ(c16, u"test");
#endif

#if IUTEST_HAS_CHAR32_T
    const char32_t c32[] = U"test";
    IUTEST_EXPECT_STREQ(c32, U"test");
#endif

#if IUTEST_HAS_LAMBDA
    {
        IUTEST_EXPECT_EQ(100, [] () -> int { return 100; }());

        int x=0, y=0;
        [=] () { IUTEST_EXPECT_EQ(x, y); }();
    }
#endif
}

#if IUTEST_HAS_EXPLICIT_CONVERSION
class ec_test
{
public:
    IUTEST_CXX_EXPLICIT_CONVERSION operator bool() const { return true; }
};

IUTEST(AssertionTest, ExplicitConversion)
{
    ec_test ec;
    IUTEST_ASSERT_TRUE(ec);
    IUTEST_EXPECT_TRUE(ec);
    IUTEST_INFORM_TRUE(ec);
    IUTEST_ASSUME_TRUE(ec);
}

#endif
