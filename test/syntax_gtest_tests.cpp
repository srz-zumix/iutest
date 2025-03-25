//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        syntax_gtest_tests.cpp
 * @brief       gtest mode syntax test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020 Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_switch.hpp"

namespace syntax_gtest_tests
{

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()
IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION()

TEST(GTestSyntaxTest, True)
{
    if( bool b = true )
        ASSERT_TRUE(b) << b;
    if( bool b = true )
        EXPECT_TRUE(b) << b;
    if( bool b = true )
        INFORM_TRUE(b) << b;
    if( bool b = true )
        ASSUME_TRUE(b) << b;
}

TEST(GTestSyntaxTest, False)
{
    if( bool b = false )
        ASSERT_FALSE(b) << b;
    if( bool b = false )
        EXPECT_FALSE(b) << b;
    if( bool b = false )
        INFORM_FALSE(b) << b;
    if( bool b = false )
        ASSUME_FALSE(b) << b;
}

TEST(GTestSyntaxTest, EQ)
{
    if( int x = 1 )
        ASSERT_EQ(1, x) << x;
    if( int x = 1 )
        EXPECT_EQ(1, x) << x;
    if( int x = 1 )
        INFORM_EQ(1, x) << x;
    if( int x = 1 )
        ASSUME_EQ(1, x) << x;
}

TEST(GTestSyntaxTest, EQ_COLLECTIONS)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 2, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
}

TEST(GTestSyntaxTest, NE_COLLECTIONS)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 2, 2, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSERT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        EXPECT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        INFORM_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSUME_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
}

TEST(GTestSyntaxTest, EQ_RANGE)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 2, 3, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSERT_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        EXPECT_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        INFORM_EQ_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSUME_EQ_RANGE(a, b) << size;
}

TEST(GTestSyntaxTest, NE_RANGE)
{
    int a[] = { 0, 1, 2, 3, 4 };
    int b[] = { 0, 1, 2, 1, 4 };

    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSERT_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        EXPECT_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        INFORM_NE_RANGE(a, b) << size;
    if( int size = (sizeof(a)/sizeof(a[0])) )
        ASSUME_NE_RANGE(a, b) << size;
}

TEST(GTestSyntaxTest, NE)
{
    if( int x = 1 )
        ASSERT_NE(0, x) << x;
    if( int x = 1 )
        EXPECT_NE(0, x) << x;
    if( int x = 1 )
        INFORM_NE(0, x) << x;
    if( int x = 1 )
        ASSUME_NE(0, x) << x;
}

TEST(GTestSyntaxTest, LT)
{
    if( int x = 1 )
        ASSERT_LT(0, x) << x;
    if( int x = 1 )
        EXPECT_LT(0, x) << x;
    if( int x = 1 )
        INFORM_LT(0, x) << x;
    if( int x = 1 )
        ASSUME_LT(0, x) << x;
}

TEST(GTestSyntaxTest, LE)
{
    if( int x = 1 )
        ASSERT_LE(1, x) << x;
    if( int x = 1 )
        EXPECT_LE(1, x) << x;
    if( int x = 1 )
        INFORM_LE(1, x) << x;
    if( int x = 1 )
        ASSUME_LE(1, x) << x;
}

TEST(GTestSyntaxTest, GT)
{
    if( int x = 1 )
        ASSERT_GT(2, x) << x;
    if( int x = 1 )
        EXPECT_GT(2, x) << x;
    if( int x = 1 )
        INFORM_GT(2, x) << x;
    if( int x = 1 )
        ASSUME_GT(2, x) << x;
}

TEST(GTestSyntaxTest, GE)
{
    if( int x = 1 )
        ASSERT_GE(1, x) << x;
    if( int x = 1 )
        EXPECT_GE(1, x) << x;
    if( int x = 1 )
        INFORM_GE(1, x) << x;
    if( int x = 1 )
        ASSUME_GE(1, x) << x;
}

TEST(GTestSyntaxTest, Float)
{
    if( float f = 1.0f )
        ASSERT_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        EXPECT_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        INFORM_FLOAT_EQ(1.0f, f) << f;
    if( float f = 1.0f )
        ASSUME_FLOAT_EQ(1.0f, f) << f;
}

TEST(GTestSyntaxTest, Double)
{
    if( double d = 1.0 )
        ASSERT_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        EXPECT_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        INFORM_DOUBLE_EQ(1.0, d) << d;
    if( double d = 1.0 )
        ASSUME_DOUBLE_EQ(1.0, d) << d;
}

#if IUTEST_HAS_LONG_DOUBLE

TEST(SyntaxTest, LongDouble)
{
    if( long double d = 1.0l )
        ASSERT_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        EXPECT_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        INFORM_LONG_DOUBLE_EQ(1.0l, d) << d;
    if( long double d = 1.0l )
        ASSUME_LONG_DOUBLE_EQ(1.0l, d) << d;
}

#endif

TEST(SyntaxTest, Complex)
{
    ::std::complex<float> c(1.0f, 1.0f);
    if( float d = 1.0f )
        ASSERT_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0f )
        EXPECT_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0f )
        INFORM_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
    if( float d = 1.0f )
        ASSUME_COMPLEX_EQ(::std::complex<float>(d, d), c) << c;
}

TEST(GTestSyntaxTest, Near)
{
    if( int x = 1 )
        ASSERT_NEAR(0, x, 2) << x;
    if( int x = 1 )
        EXPECT_NEAR(0, x, 2) << x;
    if( int x = 1 )
        INFORM_NEAR(0, x, 2) << x;
    if( int x = 1 )
        ASSUME_NEAR(0, x, 2) << x;
}

TEST(SyntaxTest, AlmostEq)
{
    if( int x = 1 )
        ASSERT_ALMOST_EQ(1, x);
    if( int x = 1 )
        EXPECT_ALMOST_EQ(1, x);
    if( int x = 1 )
        INFORM_ALMOST_EQ(1, x);
    if( int x = 1 )
        ASSUME_ALMOST_EQ(1, x);
}

TEST(SyntaxTest, AlmostFloatEq)
{
    if( float x = 1.0f )
        ASSERT_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        EXPECT_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        INFORM_ALMOST_EQ(1.0f, x);
    if( float x = 1.0f )
        ASSUME_ALMOST_EQ(1.0f, x);
}

TEST(SyntaxTest, AlmostDoubleEq)
{
    if( double x = 1.0 )
        ASSERT_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        EXPECT_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        INFORM_ALMOST_EQ(1.0, x);
    if( double x = 1.0 )
        ASSUME_ALMOST_EQ(1.0, x);
}

#if IUTEST_HAS_LONG_DOUBLE

TEST(SyntaxTest, AlmostLongDoubleEq)
{
    if( long double x = 1.0l )
        ASSERT_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        EXPECT_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        INFORM_ALMOST_EQ(1.0l, x);
    if( long double x = 1.0l )
        ASSUME_ALMOST_EQ(1.0l, x);
}

#endif

TEST(SyntaxTest, AlmostComplexEq)
{
    ::std::complex<double> c(1.0, 0.0);
    if( double x = 1.0 )
        ASSERT_ALMOST_EQ(c, x);
    if( double x = 1.0 )
        EXPECT_ALMOST_EQ(x, c);
    if( double x = 1.0 )
        INFORM_ALMOST_EQ(::std::complex<double>(x, x), c);
    if( double x = 1.0 )
        ASSUME_ALMOST_EQ(c, ::std::complex<double>(x, x));
}

TEST(GTestSyntaxTest, Null)
{
    int* p = NULL;
    if( int x = 1 )
        ASSERT_NULL(p) << x;
    if( int x = 1 )
        EXPECT_NULL(p) << x;
    if( int x = 1 )
        INFORM_NULL(p) << x;
    if( int x = 1 )
        ASSUME_NULL(p) << x;
}

TEST(GTestSyntaxTest, NotNull)
{
    if( void* p = this )
        ASSERT_NOTNULL(p) << p;
    if( void* p = this )
        EXPECT_NOTNULL(p) << p;
    if( void* p = this )
        INFORM_NOTNULL(p) << p;
    if( void* p = this )
        ASSUME_NOTNULL(p) << p;
}

TEST(GTestSyntaxTest, Same)
{
    int v = 0;
    if( int* p = &v )
        ASSERT_SAME(v, *p) << p;
    if( int* p = &v )
        EXPECT_SAME(v, *p) << p;
    if( int* p = &v )
        INFORM_SAME(v, *p) << p;
    if( int* p = &v )
        ASSUME_SAME(v, *p) << p;
}

TEST(GTestSyntaxTest, StrEq)
{
    const char test[] = "test";
    if( const char* p = "test" )
        ASSERT_STREQ(p, test) << p;
    if( const char* p = "test" )
        EXPECT_STREQ(p, test) << p;
    if( const char* p = "test" )
        INFORM_STREQ(p, test) << p;
    if( const char* p = "test" )
        ASSUME_STREQ(p, test) << p;
}

TEST(GTestSyntaxTest, StrNe)
{
    const char test[] = "Test";
    if( const char* p = "test" )
        ASSERT_STRNE(p, test) << p;
    if( const char* p = "test" )
        EXPECT_STRNE(p, test) << p;
    if( const char* p = "test" )
        INFORM_STRNE(p, test) << p;
    if( const char* p = "test" )
        ASSUME_STRNE(p, test) << p;
}

TEST(GTestSyntaxTest, StrCaseEq)
{
    const char test[] = "Test";
    if( const char* p = "test" )
        ASSERT_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        EXPECT_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        INFORM_STRCASEEQ(p, test) << p;
    if( const char* p = "test" )
        ASSUME_STRCASEEQ(p, test) << p;
}

TEST(GTestSyntaxTest, StrCaseNe)
{
    const char test[] = "host";
    if( const char* p = "test" )
        ASSERT_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        EXPECT_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        INFORM_STRCASENE(p, test) << p;
    if( const char* p = "test" )
        ASSUME_STRCASENE(p, test) << p;
}

TEST(GTestSyntaxTest, StrLn)
{
    const char test[] = "test";
    if( int len = 4 )
        ASSERT_STRLNEQ(len, test) << len;
    if( int len = 4 )
        EXPECT_STRLNEQ(len, test) << len;
    if( int len = 4 )
        INFORM_STRLNEQ(len, test) << len;
    if( int len = 4 )
        ASSUME_STRLNEQ(len, test) << len;
}

#if defined(IUTEST_OS_WINDOWS)

TEST(GTestSyntaxTest, HResultSucceeded)
{
    if( int x=1 )
        ASSERT_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        EXPECT_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        INFORM_HRESULT_SUCCEEDED(0) << x;
    if( int x=1 )
        ASSUME_HRESULT_SUCCEEDED(0) << x;
}

TEST(GTestSyntaxTest, HResultFailed)
{
    if( int x=1 )
        ASSERT_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        EXPECT_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        INFORM_HRESULT_FAILED(-1) << x;
    if( int x=1 )
        ASSUME_HRESULT_FAILED(-1) << x;
}

#endif

TEST(GTestSyntaxTest, Skip)
{
    if( int x = 1 )
        GTEST_SKIP() << x;
}

#if IUTEST_HAS_EXCEPTIONS

namespace syntax_tests
{

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

TEST(GTestSyntaxTest, ExceptionThrow)
{
    if( int x = 2 )
        ASSERT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        EXPECT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        INFORM_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
    if( int x = 2 )
        ASSUME_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
}

TEST(GTestSyntaxTest, ExceptionAnyThrow)
{
    if( int x = 1 )
        ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
    if( int x = 1 )
        ASSUME_ANY_THROW(throw ::std::bad_exception()) << x;
}

TEST(GTestSyntaxTest, ExceptionNoThrow)
{
    if( int x = 1 )
        ASSERT_NO_THROW((void)x) << x;
    if( int x = 1 )
        EXPECT_NO_THROW((void)x) << x;
    if( int x = 1 )
        INFORM_NO_THROW((void)x) << x;
    if( int x = 1 )
        ASSUME_NO_THROW((void)x) << x;
}

TEST(GTestSyntaxTest, ExceptionValueEQ)
{
    if( int x = 1 )
        ASSERT_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        EXPECT_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        INFORM_THROW_VALUE_EQ(throw 1, int, x) << x;
    if( int x = 1 )
        ASSUME_THROW_VALUE_EQ(throw 1, int, x) << x;
}

TEST(GTestSyntaxTest, ExceptionValueNE)
{
    if( int x = 1 )
        ASSERT_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        EXPECT_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        INFORM_THROW_VALUE_NE(throw 2, int, x) << x;
    if( int x = 1 )
        ASSUME_THROW_VALUE_NE(throw 2, int, x) << x;
}

TEST(GTestSyntaxTest, ExceptionValueSTREQ)
{
    if( int x = 1 )
        ASSERT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        EXPECT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        INFORM_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
    if( int x = 1 )
        ASSUME_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
}

TEST(GTestSyntaxTest, ExceptionValueSTRCASEEQ)
{
    if( int x = 1 )
        ASSERT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        EXPECT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        INFORM_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
    if( int x = 1 )
        ASSUME_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
}

TEST(GTestSyntaxTest, ExceptionValueFormat)
{
    if( float x = 0.1f )
        ASSERT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        EXPECT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        INFORM_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
    if( float x = 0.1f )
        ASSUME_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
            , ExceptionFunction(5), float, x) << x;
}

}   // end of namespace syntax_tests

#if !defined(IUTEST_USE_GTEST)

class exception_test
{
public:
    explicit exception_test(const ::std::vector<int>&)
    {
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
    }
};

TEST(GTestSyntaxTest, ExceptionVectorConstructor)
{
    ::std::vector<int> a;
    ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

#endif

IUTEST_PRAGMA_WARN_POP()

}   // end of namespace syntax_gtest_tests
