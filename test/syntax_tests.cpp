//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        syntax_tests.cpp
 * @brief       syntax test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "pred_tests.hpp"
#include <limits>

namespace syntax_tests
{

#ifndef IUTEST_NO_VARIADIC_MACROS

template<int A, int B>struct T
{
    template<typename U>
    static U call(U v) { return v; }
};

#endif

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()
IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION()

IUTEST(SyntaxTest, True)
{
    if( bool b = true )
        IUTEST_ASSERT_TRUE(b) << b;
    if( bool b = true )
        IUTEST_EXPECT_TRUE(b) << b;
    if( bool b = true )
        IUTEST_INFORM_TRUE(b) << b;
    if( bool b = true )
        IUTEST_ASSUME_TRUE(b) << b;
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(SyntaxTest, VariadicTrue)
{
    if( bool b = true )
        IUTEST_ASSERT_TRUE(T<0, 0>::call(b)) << b;
    if( bool b = true )
        IUTEST_EXPECT_TRUE(T<0, 0>::call(b)) << b;
    if( bool b = true )
        IUTEST_INFORM_TRUE(T<0, 0>::call(b)) << b;
    if( bool b = true )
        IUTEST_ASSUME_TRUE(T<0, 0>::call(b)) << b;
}
#endif

IUTEST(SyntaxTest, False)
{
    if( bool b = false )
        IUTEST_ASSERT_FALSE(b) << b;
    if( bool b = false )
        IUTEST_EXPECT_FALSE(b) << b;
    if( bool b = false )
        IUTEST_INFORM_FALSE(b) << b;
    if( bool b = false )
        IUTEST_ASSUME_FALSE(b) << b;
}

#ifndef IUTEST_NO_VARIADIC_MACROS

IUTEST(SyntaxTest, VariadicFalse)
{
    if( bool b = false )
        IUTEST_ASSERT_FALSE(T<0, 0>::call(b)) << b;
    if( bool b = false )
        IUTEST_EXPECT_FALSE(T<0, 0>::call(b)) << b;
    if( bool b = false )
        IUTEST_INFORM_FALSE(T<0, 0>::call(b)) << b;
    if( bool b = false )
        IUTEST_ASSUME_FALSE(T<0, 0>::call(b)) << b;
}

#endif

IUTEST(SyntaxTest, EQ)
{
    if( int x = 1 )
        IUTEST_ASSERT_EQ(1, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_EQ(1, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_EQ(1, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_EQ(1, x) << x;
}

IUTEST(SyntaxTest, EQ_COLLECTIONS)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 2, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
}

IUTEST(SyntaxTest, NE_COLLECTIONS)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 5, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSERT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_EXPECT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_INFORM_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSUME_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
}

IUTEST(SyntaxTest, EQ_RANGE)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 2, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSERT_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_EXPECT_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_INFORM_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSUME_EQ_RANGE(a, b) << size;
}

IUTEST(SyntaxTest, NE_RANGE)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 0, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSERT_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_EXPECT_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_INFORM_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        IUTEST_ASSUME_NE_RANGE(a, b) << size;
}

IUTEST(SyntaxTest, NE)
{
    if( int x = 1 )
        IUTEST_ASSERT_NE(0, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_NE(0, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_NE(0, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_NE(0, x) << x;
}

IUTEST(SyntaxTest, LT)
{
    if( int x = 1 )
        IUTEST_ASSERT_LT(0, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_LT(0, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_LT(0, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_LT(0, x) << x;
}

IUTEST(SyntaxTest, LE)
{
    if( int x = 1 )
        IUTEST_ASSERT_LE(1, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_LE(1, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_LE(1, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_LE(1, x) << x;
}

IUTEST(SyntaxTest, GT)
{
    if( int x = 1 )
        IUTEST_ASSERT_GT(2, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_GT(2, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_GT(2, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_GT(2, x) << x;
}

IUTEST(SyntaxTest, GE)
{
    if( int x = 1 )
        IUTEST_ASSERT_GE(1, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_GE(1, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_GE(1, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_GE(1, x) << x;
}

IUTEST(SyntaxTest, Float)
{
    if( float f = 1.0f )
        IUTEST_ASSERT_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        IUTEST_EXPECT_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        IUTEST_INFORM_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        IUTEST_ASSUME_FLOAT_EQ(1.0f, f) << f;
}

IUTEST(SyntaxTest, Double)
{
    if( double d = 1.0 )
        IUTEST_ASSERT_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        IUTEST_EXPECT_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        IUTEST_INFORM_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        IUTEST_ASSUME_DOUBLE_EQ(1.0, d) << d;
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(SyntaxTest, LongDouble)
{
    if( long double d = 1.0l )
        IUTEST_ASSERT_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        IUTEST_EXPECT_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        IUTEST_INFORM_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        IUTEST_ASSUME_LONG_DOUBLE_EQ(1.0l, d) << d;
}

#endif

IUTEST(SyntaxTest, Complex)
{
    ::std::complex<float> c(1.0f, 1.0f);
    if( float d = 1.0 )
        IUTEST_ASSERT_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0 )
        IUTEST_EXPECT_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0 )
        IUTEST_INFORM_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0 )
        IUTEST_ASSUME_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
}

IUTEST(SyntaxTest, Near)
{
    if( int x = 1 )
        IUTEST_ASSERT_NEAR(0, x, 2) << x;
    if( int x = 1 )
        IUTEST_EXPECT_NEAR(0, x, 2) << x;
    if( int x = 1 )
        IUTEST_INFORM_NEAR(0, x, 2) << x;
    if( int x = 1 )
        IUTEST_ASSUME_NEAR(0, x, 2) << x;
}

IUTEST(SyntaxTest, AlmostEq)
{
    if( int x = 1 )
        IUTEST_ASSERT_ALMOST_EQ(1, x);
    if( int x = 1 )
        IUTEST_EXPECT_ALMOST_EQ(1, x);
    if( int x = 1 )
        IUTEST_INFORM_ALMOST_EQ(1, x);
    if( int x = 1 )
        IUTEST_ASSUME_ALMOST_EQ(1, x);
}

IUTEST(SyntaxTest, AlmostFloatEq)
{
    if( float x = 1.0f )
        IUTEST_ASSERT_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        IUTEST_EXPECT_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        IUTEST_INFORM_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        IUTEST_ASSUME_ALMOST_EQ(1.0f, x);
}

IUTEST(SyntaxTest, AlmostDoubleEq)
{
    if( double x = 1.0 )
        IUTEST_ASSERT_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        IUTEST_EXPECT_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        IUTEST_INFORM_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        IUTEST_ASSUME_ALMOST_EQ(1.0, x);
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(SyntaxTest, AlmostLongDoubleEq)
{
    if( long double x = 1.0l )
        IUTEST_ASSERT_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        IUTEST_EXPECT_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        IUTEST_INFORM_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        IUTEST_ASSUME_ALMOST_EQ(1.0l, x);
}

#endif

IUTEST(SyntaxTest, AlmostComplexEq)
{
    ::std::complex<double> c(1.0, 0.0);
    if( double x = 1.0 )
        IUTEST_ASSERT_ALMOST_EQ(c, x);
    if( double x = 1.0 )
        IUTEST_EXPECT_ALMOST_EQ(x, c);
    if( double x = 1.0 )
        IUTEST_INFORM_ALMOST_EQ(::std::complex<double>(x, x), c);
    if( double x = 1.0 )
        IUTEST_ASSUME_ALMOST_EQ(c, ::std::complex<double>(x, x));
}

IUTEST(SyntaxTest, Null)
{
    int* p = NULL;
    if( int x = 1 )
        IUTEST_ASSERT_NULL(p) << x;
    if( int x = 1 )
        IUTEST_EXPECT_NULL(p) << x;
    if( int x = 1 )
        IUTEST_INFORM_NULL(p) << x;
    if( int x = 1 )
        IUTEST_ASSUME_NULL(p) << x;
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(SyntaxTest, VariadicNull)
{
    int* p = NULL;
    if( int x = 1 )
        IUTEST_ASSERT_NULL(T<0, 0>::call(p)) << x;
    if( int x = 1 )
        IUTEST_EXPECT_NULL(T<0, 0>::call(p)) << x;
    if( int x = 1 )
        IUTEST_INFORM_NULL(T<0, 0>::call(p)) << x;
    if( int x = 1 )
        IUTEST_ASSUME_NULL(T<0, 0>::call(p)) << x;
}
#endif

IUTEST(SyntaxTest, NotNull)
{
    if( void* p = this )
        IUTEST_ASSERT_NOTNULL(p) << p;
    if( void* p = this )
        IUTEST_EXPECT_NOTNULL(p) << p;
    if( void* p = this )
        IUTEST_INFORM_NOTNULL(p) << p;
    if( void* p = this )
        IUTEST_ASSUME_NOTNULL(p) << p;
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(SyntaxTest, VariadicNotNull)
{
    if( void* p = this )
        IUTEST_ASSERT_NOTNULL(T<0, 0>::call(p)) << p;
    if( void* p = this )
        IUTEST_EXPECT_NOTNULL(T<0, 0>::call(p)) << p;
    if( void* p = this )
        IUTEST_INFORM_NOTNULL(T<0, 0>::call(p)) << p;
    if( void* p = this )
        IUTEST_ASSUME_NOTNULL(T<0, 0>::call(p)) << p;
}
#endif

IUTEST(SyntaxTest, Same)
{
    int v = 0;
    if( int* p = &v )
        IUTEST_ASSERT_SAME(v, *p) << p;
    if( int* p = &v )
        IUTEST_EXPECT_SAME(v, *p) << p;
    if( int* p = &v )
        IUTEST_INFORM_SAME(v, *p) << p;
    if( int* p = &v )
        IUTEST_ASSUME_SAME(v, *p) << p;
}

IUTEST(SyntaxTest, StrEq)
{
    const char test[] = "test";
    if( const char* p = "test" )
        IUTEST_ASSERT_STREQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_EXPECT_STREQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_INFORM_STREQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_ASSUME_STREQ(p, test) << p;
}

IUTEST(SyntaxTest, StrNe)
{
    const char test[] = "Test";
    if( const char* p = "test" )
        IUTEST_ASSERT_STRNE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_EXPECT_STRNE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_INFORM_STRNE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_ASSUME_STRNE(p, test) << p;
}

IUTEST(SyntaxTest, StrCaseEq)
{
    const char test[] = "Test";
    if( const char* p = "test" )
        IUTEST_ASSERT_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_EXPECT_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_INFORM_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        IUTEST_ASSUME_STRCASEEQ(p, test) << p;
}

IUTEST(SyntaxTest, StrCaseNe)
{
    const char test[] = "host";
    if( const char* p = "test" )
        IUTEST_ASSERT_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_EXPECT_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_INFORM_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        IUTEST_ASSUME_STRCASENE(p, test) << p;
}

IUTEST(SyntaxTest, StrLn)
{
    const char test[] = "test";
    if( int len = 4 )
        IUTEST_ASSERT_STRLNEQ(len, test) << len;
    if( int len = 4 )
        IUTEST_EXPECT_STRLNEQ(len, test) << len;
    if( int len = 4 )
        IUTEST_INFORM_STRLNEQ(len, test) << len;
    if( int len = 4 )
        IUTEST_ASSUME_STRLNEQ(len, test) << len;
}

IUTEST(SyntaxTest, Nan)
{
    float  fnan = ::std::numeric_limits<float>::quiet_NaN();
    double dnan = ::std::numeric_limits<double>::quiet_NaN();
    if( fnan )
        IUTEST_ASSERT_NAN(fnan) << fnan;
    if( fnan )
        IUTEST_EXPECT_NAN(fnan) << fnan;
    if( dnan )
        IUTEST_INFORM_NAN(dnan) << dnan;
    if( dnan )
        IUTEST_ASSUME_NAN(dnan) << dnan;
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(SyntaxTest, HResultSucceeded)
{
    if( int x=1 )
        IUTEST_ASSERT_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        IUTEST_EXPECT_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        IUTEST_INFORM_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        IUTEST_ASSUME_HRESULT_SUCCEEDED(0) << x;
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(SyntaxTest, VariadicHResultSucceeded)
{
    if( int x=1 )
        IUTEST_ASSERT_HRESULT_SUCCEEDED(T<0, 0>::call(0)) << x;
    if( int x=1 )
        IUTEST_EXPECT_HRESULT_SUCCEEDED(T<0, 0>::call(0)) << x;
    if( int x=1 )
        IUTEST_INFORM_HRESULT_SUCCEEDED(T<0, 0>::call(0)) << x;
    if( int x=1 )
        IUTEST_ASSUME_HRESULT_SUCCEEDED(T<0, 0>::call(0)) << x;
}
#endif

IUTEST(SyntaxTest, HResultFailed)
{
    if( int x=1 )
        IUTEST_ASSERT_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        IUTEST_EXPECT_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        IUTEST_INFORM_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        IUTEST_ASSUME_HRESULT_FAILED(-1) << x;
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(SyntaxTest, VariadicHResultFailed)
{
    if( int x=1 )
        IUTEST_ASSERT_HRESULT_FAILED(T<0, 0>::call(-1)) << x;
    if( int x=1 )
        IUTEST_EXPECT_HRESULT_FAILED(T<0, 0>::call(-1)) << x;
    if( int x=1 )
        IUTEST_INFORM_HRESULT_FAILED(T<0, 0>::call(-1)) << x;
    if( int x=1 )
        IUTEST_ASSUME_HRESULT_FAILED(T<0, 0>::call(-1)) << x;
}
#endif

#endif

IUTEST(SyntaxTest, Skip)
{
    if( int x = 1 )
        IUTEST_SKIP() << x;
}

IUTEST(SyntaxTest, Pred1)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED1(IsOdd, x) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED1(IsOdd, x) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED1(IsOdd, x) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED1(IsOdd, x) << x;
}

IUTEST(SyntaxTest, Pred2)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED2(IsGreater, 3, x) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED2(IsGreater, 3, x) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED2(IsGreater, 3, x) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED2(IsGreater, 3, x) << x;
}

IUTEST(SyntaxTest, Pred3)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED3(PredTest3, 0, x, 2) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED3(PredTest3, 0, x, 2) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED3(PredTest3, 0, x, 2) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED3(PredTest3, 0, x, 2) << x;
}

IUTEST(SyntaxTest, Pred4)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED4(PredTest4, 0, x, 2, 3) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED4(PredTest4, 0, x, 2, 3) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED4(PredTest4, 0, x, 2, 3) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED4(PredTest4, 0, x, 2, 3) << x;
}

IUTEST(SyntaxTest, Pred5)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
}

#if IUTEST_HAS_MATCHERS

IUTEST(SyntaxTest, That)
{
    if( int x=1 )
        IUTEST_ASSERT_THAT(x, ::iutest::Eq(1)) << x;
    if( int x=1 )
        IUTEST_EXPECT_THAT(x, ::iutest::Le(1)) << x;
    if( int x=1 )
        IUTEST_INFORM_THAT(x, ::iutest::Ge(1)) << x;
    if( int x=1 )
        IUTEST_ASSUME_THAT(x, ::iutest::Ne(0)) << x;
}

struct X { int a, b; X(int _a, int _b) : a(_a), b(_b) {} int GetA() const { return a; } };
int X2(int value) { return value*2; }

IUTEST(SyntaxTest, Matcher)
{
    ::std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    int a[3] = { 0, 1, 2 };
    int b[4] = { 0, 1, 2, 3 };
    X x(0, 1);
    int z=1;
    IUTEST_EXPECT_THAT(a, ::iutest::Contains(0));
    IUTEST_EXPECT_THAT(a, ::iutest::Contains(::iutest::Lt(10)));
#if IUTEST_HAS_MATCHER_EACH
    IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::Le(10)));
    IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::_));
    IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::A<int>()));
#endif
    IUTEST_EXPECT_THAT(&x, ::iutest::Field(&X::a, 0));
    IUTEST_EXPECT_THAT(x, ::iutest::Field(&X::a, 0));
    IUTEST_EXPECT_THAT(&x, ::iutest::Property(&X::GetA, 0));
    IUTEST_EXPECT_THAT(x, ::iutest::Property(&X::GetA, 0));
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(a));
    IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArray(a));
#if !defined(IUTEST_USE_GMOCK) || (GMOCK_VER >= 0x01070000)
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(v));
    IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArray(v));
#endif
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(b, 3));
#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray({0, 1, 2}));
#endif
    IUTEST_EXPECT_THAT(1, ::iutest::ResultOf(X2, 2));
    IUTEST_EXPECT_THAT(1, ::iutest::ResultOf(X2, ::iutest::Gt(1)));
    IUTEST_EXPECT_THAT(z, ::iutest::TypedEq<int>(1.0));
}

#if IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD
IUTEST(SyntaxTest, ElementsAreArrayForward)
{
    ::std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    int a[3] = { 0, 1, 2 };
    int b[4] = { 0, 1, 2, 3 };

    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArrayForward(a));
    IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArrayForward(a));
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArrayForward(v));
    IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArrayForward(v));
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArrayForward(b, 1));
#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArrayForward({0, 1, 2}));
#endif
}
#endif

#if IUTEST_HAS_MATCHER_REGEX
IUTEST(SyntaxTest, MatcherRegex)
{
    ::std::string s = "greeeeeen";
    IUTEST_EXPECT_THAT(s, ::iutest::MatchesRegex("gre+n"));
    IUTEST_EXPECT_THAT("hogeeeeeet", ::iutest::MatchesRegex("hoge+t"));
    IUTEST_EXPECT_THAT(s, ::iutest::ContainsRegex("e"));
    IUTEST_EXPECT_THAT("hogeeeeeet", ::iutest::ContainsRegex("hoge+"));
}
#endif

IUTEST(SyntaxTest, MatcherPredicate)
{
    IUTEST_EXPECT_TRUE(::iutest::Value(2, 2));
    IUTEST_EXPECT_TRUE(::iutest::Value(2, ::iutest::Eq(2)));
}

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

IUTEST(SyntaxTest, AllOf)
{
#if IUTEST_HAS_MATCHER_VARIADIC
    IUTEST_EXPECT_THAT("9347812650", ::iutest::AllOf(
          ::iutest::HasSubstr("0")
        , ::iutest::HasSubstr("1")
        , ::iutest::HasSubstr("2")
        , ::iutest::HasSubstr("3")
        , ::iutest::HasSubstr("4")
        , ::iutest::HasSubstr("5")
        , ::iutest::HasSubstr("6")
        , ::iutest::HasSubstr("7")
        , ::iutest::HasSubstr("8")
        , ::iutest::HasSubstr("9")
        , ::iutest::HasSubstr("0")
    ));
#else
    IUTEST_EXPECT_THAT("9347812650", ::iutest::AllOf(
          ::iutest::HasSubstr("0")
        , ::iutest::HasSubstr("1")
        , ::iutest::HasSubstr("2")
        , ::iutest::HasSubstr("3")
        , ::iutest::HasSubstr("4")
        , ::iutest::HasSubstr("5")
        , ::iutest::HasSubstr("6")
        , ::iutest::HasSubstr("7")
        , ::iutest::HasSubstr("8")
        , ::iutest::HasSubstr("9")
    ));
#endif
}

IUTEST(SyntaxTest, AnyOf)
{
#if IUTEST_HAS_MATCHER_VARIADIC
    IUTEST_EXPECT_THAT("hoge7", ::iutest::AnyOf(
          ::iutest::HasSubstr("0")
        , ::iutest::HasSubstr("1")
        , ::iutest::HasSubstr("2")
        , ::iutest::HasSubstr("3")
        , ::iutest::HasSubstr("4")
        , ::iutest::HasSubstr("5")
        , ::iutest::HasSubstr("6")
        , ::iutest::HasSubstr("7")
        , ::iutest::HasSubstr("8")
        , ::iutest::HasSubstr("9")
        , ::iutest::HasSubstr("0")
    ));
#else
    IUTEST_EXPECT_THAT("hoge7", ::iutest::AnyOf(
          ::iutest::HasSubstr("0")
        , ::iutest::HasSubstr("1")
        , ::iutest::HasSubstr("2")
        , ::iutest::HasSubstr("3")
        , ::iutest::HasSubstr("4")
        , ::iutest::HasSubstr("5")
        , ::iutest::HasSubstr("6")
        , ::iutest::HasSubstr("7")
        , ::iutest::HasSubstr("8")
        , ::iutest::HasSubstr("9")
    ));
#endif
}

#endif

#endif


#if !defined(IUTEST_USE_GTEST)

#if !defined(IUTEST_NO_VARIADIC_MACROS)

#if IUTEST_HAS_VARIADIC_TEMPLATES

IUTEST(SyntaxTest, VariadicPred)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
}

#endif

IUTEST(SyntaxTest, VariadicPredFormat)
{
    if( int x=1 )
        IUTEST_ASSERT_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_EXPECT_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_INFORM_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
    if( int x=1 )
        IUTEST_ASSUME_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
}

#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

static void ExceptionFunction(int i)
{
    switch( i )
    {
    case 0:
        return;
    case 1:
        throw 2;
    case 2:
        throw ::std::bad_exception();
    case 3:
        throw "error";
    case 4:
        throw ::std::string("error");
    case 5:
        throw 0.1f;
    default:
        break;
    }
}

IUTEST(SyntaxTest, ExceptionThrow)
{
    if( int x = 2 )
        IUTEST_ASSERT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        IUTEST_EXPECT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        IUTEST_INFORM_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        IUTEST_ASSUME_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
}

IUTEST(SyntaxTest, ExceptionAnyThrow)
{
    if( int x = 1 )
        IUTEST_ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        IUTEST_EXPECT_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        IUTEST_INFORM_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        IUTEST_ASSUME_ANY_THROW(throw ::std::bad_exception()) << x;
}

IUTEST(SyntaxTest, ExceptionNoThrow)
{
    if( int x = 1 )
        IUTEST_ASSERT_NO_THROW((void)x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_NO_THROW((void)x) << x;
    if( int x = 1 )
        IUTEST_INFORM_NO_THROW((void)x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_NO_THROW((void)x) << x;
}

IUTEST(SyntaxTest, ExceptionValueEQ)
{
    if( int x = 1 )
        IUTEST_ASSERT_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_THROW_VALUE_EQ(throw 1, int, x) << x;
}

IUTEST(SyntaxTest, ExceptionValueNE)
{
    if( int x = 1 )
        IUTEST_ASSERT_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        IUTEST_EXPECT_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        IUTEST_INFORM_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        IUTEST_ASSUME_THROW_VALUE_NE(throw 2, int, x) << x;
}

IUTEST(SyntaxTest, ExceptionValueSTREQ)
{
    if( int x = 1 )
        IUTEST_ASSERT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        IUTEST_EXPECT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        IUTEST_INFORM_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        IUTEST_ASSUME_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
}

IUTEST(SyntaxTest, ExceptionValueSTRCASEEQ)
{
    if( int x = 1 )
        IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        IUTEST_INFORM_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        IUTEST_ASSUME_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
}

IUTEST(SyntaxTest, ExceptionValueFormat)
{
    if( float x = 0.1f )
        IUTEST_ASSERT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        IUTEST_EXPECT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        IUTEST_INFORM_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        IUTEST_ASSUME_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
}

class exception_test
{
public:
    explicit exception_test(const ::std::vector<int>&)
    {
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
    }
};

IUTEST(SyntaxTest, ExceptionVectorConstructor)
{
    ::std::vector<int> a;
    IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

#if !defined(IUTEST_USE_GTEST) && defined(__WANDBOX__)

IUTEST(SyntaxTest, ShowFeature)
{
    ::iutest::detail::iuOptionMessage::ShowFeature();
}
IUTEST(SyntaxTest, ShowSpec)
{
    ::iutest::detail::iuOptionMessage::ShowSpec();
}

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedPrintToTest : public ::iutest::Test {};
typedef ::iutest::Types<char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, int*> PrintStringTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedPrintToTest, PrintStringTestTypes);

IUTEST_TYPED_TEST(TypedPrintToTest, Print)
{
    TypeParam a = 0;
    TypeParam& b = a;
    const TypeParam c = a;
    const volatile TypeParam d = a;

    IUTEST_SUCCEED() << ::iutest::PrintToString(a);
    IUTEST_SUCCEED() << ::iutest::PrintToString(b);
    IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    IUTEST_SUCCEED() << ::iutest::PrintToString(d);
}

#endif

IUTEST(PrintToTest, RawArray)
{
    {
        unsigned char a[3] = {0, 1, 2};
        const unsigned char b[3] = {0, 1, 2};
        const volatile unsigned char c[3] = {0, 1, 2};
        volatile unsigned char d[3] = {0, 1, 2};

        IUTEST_SUCCEED() << ::iutest::PrintToString(a);
        IUTEST_SUCCEED() << ::iutest::PrintToString(b);
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
        IUTEST_SUCCEED() << ::iutest::PrintToString(d);
    }
    {
        char a[3] = {0, 1, 2};
        const char b[3] = {0, 1, 2};
        const volatile char c[3] = {0, 1, 2};
        volatile char d[3] = {0, 1, 2};

        IUTEST_SUCCEED() << ::iutest::PrintToString(a);
        IUTEST_SUCCEED() << ::iutest::PrintToString(b);
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
        IUTEST_SUCCEED() << ::iutest::PrintToString(d);
    }
}

#if IUTEST_HAS_IOMANIP
IUTEST(PrintToTest, Iomanip)
{
    IUTEST_SUCCEED() << ::std::endl;
    IUTEST_SUCCEED() << ::std::ends;
}
#endif

#if IUTEST_HAS_CHAR16_T
IUTEST(PrintToTest, U16String)
{
    IUTEST_SUCCEED() << u"test";
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, U16StringStringView)
{
    ::std::u16string_view view = u"Hello";
    IUTEST_SUCCEED() << view;
}
#endif

#endif

#if IUTEST_HAS_CHAR32_T
IUTEST(PrintToTest, U32String)
{
    IUTEST_SUCCEED() << U"TEST";
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, U32StringStringView)
{
    ::std::u32string_view view = U"Hello";
    IUTEST_SUCCEED() << view;
}
#endif
#endif

#if defined(__WANDBOX__)

#if IUTEST_HAS_PARAM_TEST

class ValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ValuesTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P( X1, ValuesTest, ::iutest::Values(1) );
IUTEST_INSTANTIATE_TEST_SUITE_P( X2, ValuesTest, ::iutest::Values(1, 2) );

#if IUTEST_HAS_VARIADIC_VALUES

IUTEST_INSTANTIATE_TEST_SUITE_P( X51, ValuesTest
    , ::iutest::Values( IUTEST_PP_ENUM_PARAMS(51, IUTEST_PP_EMPTY()) ) );

#endif

#endif

#endif

IUTEST_PRAGMA_WARN_POP()

}   // end of namespace syntax_tests
