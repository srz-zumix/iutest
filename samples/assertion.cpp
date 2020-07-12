//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion.cpp
 * @brief       assertion sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

int f()
{
    return 42;
}

/* ---------------------------------------------------
 * 各種アサーション
*//*--------------------------------------------------*/

/* ---------------------------------------------------
 * 式アサーション
*//*--------------------------------------------------*/
IUTEST(ExpressionTest, Test)
{
    IUTEST_EXPECT(f());
    IUTEST_EXPECT(f() == 42);
    IUTEST_EXPECT(f() + f() == 84);
    IUTEST_EXPECT(f() == 42 && true);
    IUTEST_EXPECT_NOT(f() != 42);
    IUTEST_ASSERT_TRUE(IUTEST_EXPRESSION(f() != 42) || IUTEST_EXPRESSION(f() != 10));
}

IUTEST(AssertionTest, NoFailure)
{
    IUTEST_ASSERT_NO_FATAL_FAILURE( IUTEST_ASSERT_TRUE(true) );
    IUTEST_ASSERT_NO_FAILURE( IUTEST_EXPECT_TRUE(true) );
}

IUTEST(AssertionTest, Base)
{
    int x0=0, y0=0, x1=1;
    float f0=0.0f, f1=1.0f;
    double d0=0.0, d1=1.0;

    IUTEST_ASSUME_EQ(x0, y0);

    // true/false
    {
        IUTEST_EXPECT_TRUE(true);
        IUTEST_EXPECT_TRUE(1);
        IUTEST_EXPECT_TRUE(100 == 100);
        IUTEST_EXPECT_TRUE(f()==42);

        IUTEST_EXPECT_FALSE(false);
        IUTEST_EXPECT_FALSE(0);
        IUTEST_EXPECT_FALSE(100 != 100);
        IUTEST_EXPECT_FALSE(f()!=42);
    }
    // EQ
    {
        IUTEST_EXPECT_EQ(x0, y0);
        int* zero=NULL;
        IUTEST_EXPECT_EQ(NULL, zero);

        ::std::vector<int> v1, v2;
        IUTEST_EXPECT_EQ(v1, v2);
    }

    // NE
    {
        IUTEST_EXPECT_NE(x0, x1);
        int* one=reinterpret_cast<int*>(1);
        IUTEST_EXPECT_NE(NULL, one);
    }

    // LE, LT
    {
        IUTEST_EXPECT_LE(x0, y0);
        IUTEST_EXPECT_LE(f0, f1);
        IUTEST_EXPECT_LE(0.0, 0x1);
        IUTEST_EXPECT_LT(x0, x1);
        IUTEST_EXPECT_LT(d0, d1);
        IUTEST_EXPECT_LT(0.0, 0x1);
    }

    // GE, GT
    {
        IUTEST_EXPECT_GE(x0, y0);
        IUTEST_EXPECT_GE(f1, f0);
        IUTEST_EXPECT_GE(0x1, 0.0f);
        IUTEST_EXPECT_GT(x1, x0);
        IUTEST_EXPECT_GT(d1, d0);
        IUTEST_EXPECT_GT(0x1, 0.0f);
    }

    // float. double
    {
        IUTEST_EXPECT_FLOAT_EQ(1.0f, f1);
        IUTEST_EXPECT_FLOAT_EQ(0.0f, f0);
        IUTEST_EXPECT_FLOAT_EQ(-1.0f, -2.0f/2.0f);

        IUTEST_EXPECT_DOUBLE_EQ(1.0, d1);
        IUTEST_EXPECT_DOUBLE_EQ(0.0, d0);
        IUTEST_EXPECT_DOUBLE_EQ(-1.0, -2.0/2.0);
    }

    // Near
    {
        IUTEST_EXPECT_NEAR(0, 1, 2);
        IUTEST_EXPECT_NEAR(1.0f, 4.0f, 4);
        IUTEST_EXPECT_NEAR(2.0, 1.0, 2);
    }
}

IUTEST(AssertionTest, Base2)
{
    // NULL
    {
        int* p1 = NULL;
        IUTEST_EXPECT_NULL(p1);

        void* p2 = &p1;
        IUTEST_EXPECT_NOTNULL(p2);
    }
    // SAME
    {
        int v = 0;
        int* p1 = &v;
        IUTEST_EXPECT_SAME(v, *p1);
    }
    // EQ_COLLECTIONS/EQ_RANGE
    {
        int aa[] ={ 0, 1, 2, 3, 4 };
        int ab[] ={ 0, 1, 2, 3, 4 };
        IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0])));
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        IUTEST_EXPECT_EQ_RANGE(aa, ab);
#endif
    }
    // NE_COLLECTIONS/NE_RANGE
    // NE_COLLECTIONS
    {
        int aa[] ={ 0, 1, 2, 3, 4 };
        int ab[] ={ 9, 1, 2, 3, 4 };
        IUTEST_EXPECT_NE_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0])));
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        IUTEST_EXPECT_NE_RANGE(aa, ab);
#endif
    }
}

#if !defined(IUTEST_USE_GTEST)

#if IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT

struct TestObjectX
{
    int a, b, c;
};

IUTEST(AssertionTest, MemCmpEQ)
{
    TestObjectX x={ 0, 1, 2 };
    TestObjectX y={ 0, 1, 2 };
    IUTEST_ASSERT_EQ(x, y);
}

#endif

#endif

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
}

IUTEST(AssertionTest, String)
{
    const char mbs[] = "test";
    const wchar_t wcs[] = L"test";
    IUTEST_EXPECT_STREQ( "test", mbs);
    IUTEST_EXPECT_STREQ(L"test", wcs);

    IUTEST_EXPECT_STRNE( "host", mbs);
    IUTEST_EXPECT_STRNE(L"host", wcs);

    IUTEST_EXPECT_STRLNEQ(4, mbs);
    IUTEST_EXPECT_STRLNEQ(4, wcs);

    {
        ::std::string str1 = "test";
        IUTEST_EXPECT_EQ(str1, "test");

        IUTEST_EXPECT_NE(str1, "host");
    }

    {
        ::std::string str1 = "tEst";
        ::std::string str2 = "teSt";
        ::std::string str3 = "hoSt";

        IUTEST_EXPECT_STRCASEEQ("TeSt", mbs);
        IUTEST_EXPECT_STRCASEEQ("TeSt", str1);
        IUTEST_EXPECT_STRCASEEQ(str1, "TeSt");
        IUTEST_EXPECT_STRCASEEQ(str1, str2);

        IUTEST_EXPECT_STRCASENE("HoSt", mbs);
        IUTEST_EXPECT_STRCASENE("HoSt", str1);
        IUTEST_EXPECT_STRCASENE(str1, "HoSt");
        IUTEST_EXPECT_STRCASENE(str1, str3);
    }
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(AssertionTest, HResult)
{
    IUTEST_EXPECT_HRESULT_SUCCEEDED(0);
    IUTEST_EXPECT_HRESULT_FAILED(-1);
}

#endif


/* ---------------------------------------------------
 * 述語アサーション
*//*--------------------------------------------------*/
static bool IsOdd(int val)
{
    return (val & 1) != 0;
}
static bool IsGreater(int a, int b)
{
    return a > b;
}
static bool PredTest3(int , int , int )
{
    return true;
}
static bool PredTest4(int , int , int , int )
{
    return true;
}
static bool PredTest5(int , int , int , int , int )
{
    return true;
}
IUTEST(AssertionTest, Pred)
{
    IUTEST_EXPECT_PRED1(IsOdd, 3);
    IUTEST_EXPECT_PRED2(IsGreater, 3, 1);
    IUTEST_EXPECT_PRED3(PredTest3, 0, 1, 2);
    IUTEST_EXPECT_PRED4(PredTest4, 0, 1, 2, 3);
    IUTEST_EXPECT_PRED5(PredTest5, 0, 1, 2, 3, 4);
}

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

/* ---------------------------------------------------
 * 型の一致テスト
*//*--------------------------------------------------*/
IUTEST(StaticTest, Eq)
{
    IUTEST_ASSERT_TRUE( (::iutest::StaticAssertTypeEq<int, int>()) );
    //iutest::StaticAssertTypeEq<bool, int>();
}

#endif

#if IUTEST_HAS_REGEX

IUTEST(AssertionTest, Regex)
{
    const char test [] = "te0123st";
    IUTEST_ASSERT_MATCHES_REGEXEQ("te[0-9]*st", test);
}

#endif

/* ---------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
IUTEST(DISABLED_TestFailure, Expression)
{
    IUTEST_EXPECT(f() > f() + 1 );
    IUTEST_EXPECT_NOT(f() == 42);
    IUTEST_EXPECT(f() && 0);
    IUTEST_EXPECT(true && false);
}

IUTEST(DISABLED_TestFailure, EQ)
{
    IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(DISABLED_TestFailure, NE)
{
    int x=1, y=1;
    IUTEST_ASSERT_NE(x, y);
}

IUTEST(DISABLED_TestFailure, GE)
{
    float a = 0.1f, b = 1.0f;
    IUTEST_ASSERT_GE(a, b);
}

IUTEST(DISABLED_TestFailure, TRUE)
{
    IUTEST_ASSERT_TRUE(0);
    IUTEST_ASSERT_TRUE(false);
}

IUTEST(DISABLED_TestFailure, FALSE)
{
    IUTEST_ASSERT_FALSE(true);
    IUTEST_ASSERT_FALSE(2);
}

IUTEST(DISABLED_TestFailure, Fail)
{
    IUTEST_FAIL() << "add messages.\n";
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(DISABLED_TestFailure, HRESULT)
{
    IUTEST_ASSERT_HRESULT_SUCCEEDED(E_OUTOFMEMORY);
}

#endif

void AssertFunc()
{
    IUTEST_ASSERT_TRUE(false);
}

IUTEST(DISABLED_TestFailure, NoFailure)
{
    IUTEST_INFORM_NO_FATAL_FAILURE( AssertFunc() );
    IUTEST_EXPECT_NO_FATAL_FAILURE( AssertFunc() );
    IUTEST_ASSERT_NO_FATAL_FAILURE( AssertFunc() );
}

IUTEST(DISABLED_TestFailure, Pred)
{
    int x=4, y=5;
    IUTEST_EXPECT_PRED1(IsOdd, x);
    IUTEST_EXPECT_PRED2(IsGreater, x, y);
}

IUTEST(DISABLED_TestFailure, Mix)
{
    IUTEST_EXPECT_EQ(0.1, 1);
    IUTEST_EXPECT_NE(0, 0);
    IUTEST_EXPECT_LE(2, 0);
    IUTEST_EXPECT_LT(0, 0);
    IUTEST_EXPECT_GE(0, 2);
    IUTEST_EXPECT_GT(0, 0);
    IUTEST_EXPECT_TRUE(0);
    IUTEST_EXPECT_FALSE(1);
    IUTEST_EXPECT_FLOAT_EQ(0.0f, 0.1f);
    IUTEST_EXPECT_DOUBLE_EQ(0.0, 0.1);
    IUTEST_EXPECT_NEAR(0, 100, 2);
    IUTEST_EXPECT_FAIL();
    {
        ::std::string str1 = "test";
        ::std::string str2 = "text";

        IUTEST_EXPECT_STREQ("text", str1);
        IUTEST_EXPECT_STRNE("text", str2);
        IUTEST_EXPECT_STRCASEEQ("Text", str1);
        IUTEST_EXPECT_STRCASENE("Text", str2);
    }
    // EQ_COLLECTIONS
    {
        int  aa[] = { 0, 1, 2, 3, 4 };
        int  ab[] = { 0, 1, 2, 3, 4, 5 };
        char ac[] = { 0, 0, 2, 3, 5 };
        IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0])));
        IUTEST_EXPECT_EQ_COLLECTIONS(ab, ab+(sizeof(ab)/sizeof(ab[0])), aa, aa+(sizeof(aa)/sizeof(aa[0])));
        IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ac, ac+(sizeof(ac)/sizeof(ac[0])));
    }
}
