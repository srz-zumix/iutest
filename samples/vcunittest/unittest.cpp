//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unittest.cpp
 * @brief       vc unittest sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../include/iutest.hpp"
#include "../../include/gtest/iutest_switch.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#ifdef USE_IUTEST_TR1
#include "../../include/tr1/iutest_vc_unittest.hpp"

namespace iutest_unittest
{
    TEST_MODULE_INITIALIZE(iutest)
    {
        ::iuutil::VisualStudio::SetUpCppUnitTest();
    }

    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_CLASS_INITIALIZE(a) { Logger::WriteMessage(__FUNCTION__); }
        TEST_METHOD_INITIALIZE(b) { Logger::WriteMessage(__FUNCTION__); }

        TEST_METHOD(TestMethod1)
        {
            Assert::AreEqual(0, 1);
        }
        TEST_METHOD(TestMethod2)
        {
            Assert::AreEqual(0, 1);
        }
    };
}   // end of namespace iutest_unittest
#endif

/** --------------------------------------------------
 * 簡単なテスト
*//*--------------------------------------------------*/
IUTEST(Test, Version)
{
    unsigned long v = (IUTEST_MAJORVER << 24) | (IUTEST_MINORVER << 16) | (IUTEST_BUILD << 8) | IUTEST_REVISION;
    IUTEST_ASSERT_EQ( IUTEST_VER, v );
}

IUTEST(Test, GetName)
{
    IUTEST_ASSERT_STREQ("GetName", iutest::UnitTest::GetInstance()->current_test_info()->name());
    RecordProperty("test_name", iutest::UnitTest::GetInstance()->current_test_info()->name());
    RecordProperty("number", 1);
}

IUTEST(Test, Stream)
{
    IUTEST_SUCCEED() << "OK!!";
    IUTEST_SUCCEED() << L"OK!!";
}

/** --------------------------------------------------
 * テストフィクスチャの利用
*//*--------------------------------------------------*/
class TestFixed : public iutest::Test
{
protected:
    static int x;
public:
    virtual void SetUp(void)
    {
        ++x;
    }
    static void SetUpTestSuite(void)
    {
        x = 0;
    }
};
int TestFixed::x = -1;

IUTEST_F(TestFixed, Test1)
{
    IUTEST_ASSERT_EQ(1, x);
}

IUTEST_F(TestFixed, Test2)
{
    IUTEST_ASSERT_EQ(1, x);
}

typedef TestFixed TestFixed2;

IUTEST_F(TestFixed2, Test1)
{
    IUTEST_ASSERT_EQ(1, x);
}

IUTEST_F(TestFixed2, Test2)
{
    IUTEST_ASSERT_EQ(1, x);
}

/** --------------------------------------------------
 * 各種アサーション
*//*--------------------------------------------------*/
IUTEST(AssertionTest, NoFailure)
{
    IUTEST_ASSERT_NO_FATAL_FAILURE( IUTEST_EXPECT_TRUE(true) );
    IUTEST_EXPECT_NO_FATAL_FAILURE( IUTEST_EXPECT_TRUE(true) );
    IUTEST_INFORM_NO_FATAL_FAILURE( IUTEST_EXPECT_TRUE(true) );
}
IUTEST(AssertionTest, Base)
{
    int x0=0, y0=0, x1=1;
    float f0=0.0f, f1=1.0f;
    double d0=0.0, d1=1.0;
    // EQ
    {
        IUTEST_ASSERT_EQ(x0, y0);
        IUTEST_EXPECT_EQ(x0, y0);
        IUTEST_INFORM_EQ(x0, y0);
        int* zero=NULL;
        IUTEST_ASSERT_EQ(NULL, zero);
    }

    // NE
    {
        IUTEST_ASSERT_NE(x0, x1);
        IUTEST_EXPECT_NE(x0, x1);
        IUTEST_INFORM_NE(x0, x1);
        int* one=reinterpret_cast<int*>(1);
        IUTEST_ASSERT_NE(NULL, one);
    }

    // LE, LT
    {
        IUTEST_ASSERT_LE(x0, y0);
        IUTEST_EXPECT_LE(f0, f1);
        IUTEST_INFORM_LE(0.0, 0x1);
        IUTEST_ASSERT_LT(x0, x1);
        IUTEST_EXPECT_LT(d0, d1);
        IUTEST_INFORM_LT(0.0, 0x1);
    }

    // GE, GT
    {
        IUTEST_ASSERT_GE(x0, y0);
        IUTEST_EXPECT_GE(f1, f0);
        IUTEST_INFORM_GE(0x1, 0.0f);
        IUTEST_ASSERT_GT(x1, x0);
        IUTEST_EXPECT_GT(d1, d0);
        IUTEST_INFORM_GT(0x1, 0.0f);
    }

    // float. double
    {
        IUTEST_ASSERT_FLOAT_EQ(1.0f, f1);
        IUTEST_EXPECT_FLOAT_EQ(0.0f, f0);
        IUTEST_INFORM_FLOAT_EQ(-1.0f, -2.0f/2.0f);

        IUTEST_ASSERT_DOUBLE_EQ(1.0, d1);
        IUTEST_EXPECT_DOUBLE_EQ(0.0, d0);
        IUTEST_INFORM_DOUBLE_EQ(-1.0, -2.0/2.0);
    }

    // Near
    {
        IUTEST_ASSERT_NEAR(0, 1, 2);
        IUTEST_EXPECT_NEAR(1.0f, 4.0f, 4);
        IUTEST_INFORM_NEAR(2.0, 1.0, 2);
    }
}

IUTEST(AssertionTest, String)
{
    const char mbs[] = "test";
    const wchar_t wcs[] = L"test";
    IUTEST_ASSERT_STREQ( "test", mbs);
    IUTEST_ASSERT_STREQ(L"test", wcs);
    IUTEST_EXPECT_STREQ( "test", mbs);
    IUTEST_INFORM_STREQ(L"test", wcs);
    IUTEST_ASSERT_STRNE( "host", mbs);
    IUTEST_ASSERT_STRNE(L"host", wcs);
    IUTEST_EXPECT_STRNE( "host", mbs);
    IUTEST_INFORM_STRNE(L"host", wcs);

    IUTEST_ASSERT_STRLNEQ(4, mbs);
    IUTEST_ASSERT_STRLNEQ(4, wcs);
    IUTEST_EXPECT_STRLNEQ(4, wcs);
    IUTEST_INFORM_STRLNEQ(4, wcs);

    {
        ::std::string str1 = "tEst";
        ::std::string str2 = "teSt";
        ::std::string str3 = "hoSt";

        IUTEST_ASSERT_STRCASEEQ("TeSt", mbs);
        IUTEST_ASSERT_STRCASEEQ("TeSt", str1);
        IUTEST_EXPECT_STRCASEEQ(str1, "TeSt");
        IUTEST_INFORM_STRCASEEQ(str1, str2);

        IUTEST_ASSERT_STRCASENE("HoSt", mbs);
        IUTEST_ASSERT_STRCASENE("HoSt", str1);
        IUTEST_EXPECT_STRCASENE(str1, "HoSt");
        IUTEST_INFORM_STRCASENE(str1, str3);
    }
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(AssertionTest, HResult)
{
    IUTEST_ASSERT_HRESULT_SUCCEEDED(0);
    IUTEST_EXPECT_HRESULT_SUCCEEDED(0);
    IUTEST_INFORM_HRESULT_SUCCEEDED(0);
    IUTEST_ASSERT_HRESULT_FAILED(-1);
    IUTEST_EXPECT_HRESULT_FAILED(-1);
    IUTEST_INFORM_HRESULT_FAILED(-1);
}

#endif

/** --------------------------------------------------
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
    IUTEST_ASSERT_PRED1(IsOdd, 3);
    IUTEST_EXPECT_PRED1(IsOdd, 3);
    IUTEST_INFORM_PRED1(IsOdd, 3);
    IUTEST_ASSERT_PRED2(IsGreater, 3, 1);
    IUTEST_EXPECT_PRED2(IsGreater, 3, 1);
    IUTEST_INFORM_PRED2(IsGreater, 3, 1);
    IUTEST_ASSERT_PRED3(PredTest3, 0, 1, 2);
    IUTEST_EXPECT_PRED3(PredTest3, 0, 1, 2);
    IUTEST_INFORM_PRED3(PredTest3, 0, 1, 2);
    IUTEST_ASSERT_PRED4(PredTest4, 0, 1, 2, 3);
    IUTEST_EXPECT_PRED4(PredTest4, 0, 1, 2, 3);
    IUTEST_INFORM_PRED4(PredTest4, 0, 1, 2, 3);
    IUTEST_ASSERT_PRED5(PredTest5, 0, 1, 2, 3, 4);
    IUTEST_EXPECT_PRED5(PredTest5, 0, 1, 2, 3, 4);
    IUTEST_INFORM_PRED5(PredTest5, 0, 1, 2, 3, 4);
}

/** --------------------------------------------------
 * 値をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_TEST
// Param Test Range
class TestP : public iutest::TestWithParam<int>
{
protected:
    static int a;
    static int b;
public:
    static void SetUpTestSuite(void)
    {
        a = 0;
        b = 0;
        IUTEST_SUCCEED() << "SetUpTestSuite";
    }
    static void TearDownTestSuite(void)
    {
        IUTEST_SUCCEED() << "TearDownTestSuite";
    }
};
int TestP::a = 0;
int TestP::b = 0;

IUTEST_INSTANTIATE_TEST_SUITE_P(TestPInstance, TestP, iutest::Range<int>(0, 10));

IUTEST_P(TestP, TestA)
{
    IUTEST_ASSERT_EQ(a, GetParam());
    ++a;
}

IUTEST_P(TestP, TestB)
{
    IUTEST_ASSERT_EQ(b, GetParam());
    ++b;
}

// Param Test Bool
class TestBool : public iutest::TestWithParam<bool> {};
IUTEST_INSTANTIATE_TEST_SUITE_P(TestBoolInstance, TestBool, iutest::Bool());

IUTEST_P(TestBool, TestA)
{
    static bool x=false;
    IUTEST_ASSERT_EQ(x, GetParam());
    x = !x;
}

// Param Test ValueIn
const char ValueInTestText[] = "ValueInTestText";
class TestPValueIn : public iutest::TestWithParam<char>
{
protected:
    static int a;
public:
    static void SetUpTestSuite(void)
    {
        a = 0;
    }
};
int TestPValueIn::a = 0;
IUTEST_INSTANTIATE_TEST_SUITE_P(TestPValueInInstance, TestPValueIn, iutest::ValuesIn(ValueInTestText));

IUTEST_P(TestPValueIn, TestA)
{
    IUTEST_ASSERT_EQ(ValueInTestText[a++], GetParam());
}

// Param Test Values
class TestPValues1 : public iutest::TestWithParam<float> {};
IUTEST_INSTANTIATE_TEST_SUITE_P(TestPValues1Instance, TestPValues1, iutest::Values(1.0f));

IUTEST_P(TestPValues1, TestA)
{
    IUTEST_ASSERT_FLOAT_EQ(1.0f, GetParam());
}

class TestPValuesN : public iutest::TestWithParam<int>
{
protected:
    static int a;
public:
    static void SetUpTestSuite(void)
    {
        a = 1;
    }
};
int TestPValuesN::a = 1;
IUTEST_INSTANTIATE_TEST_SUITE_P(TestPValuesNInstance, TestPValuesN, iutest::Values(1, 2, 3, 4, 5, 6, 7, 8, 9
                                                                    //, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                                                                    //, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
                                                                    //, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
                                                                    //, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
                                                                    //, 50
                                                                    ));

IUTEST_P(TestPValuesN, TestA)
{
    IUTEST_ASSERT_EQ(a++, GetParam());
}

#if IUTEST_HAS_COMBINE

class TestPCombine : public iutest::TestWithParam< iutest::tuples::tuple<bool, int, int> >
{
};

IUTEST_P(TestPCombine, TestA)
{
    bool b = iutest::tuples::get<0>(GetParam());
    int i1 = iutest::tuples::get<1>(GetParam());
    int i2 = iutest::tuples::get<2>(GetParam());
    IUTEST_SUCCEED() << b << ", " << i1 << ", " << i2;
}

IUTEST_INSTANTIATE_TEST_SUITE_P(TestPCombineInstance, TestPCombine
                                , iutest::Combine( iutest::Bool(), iutest::Values(1, 2), iutest::Values(10, 11) ) );
#endif

#endif

/** --------------------------------------------------
 * 型付けテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public iutest::Test
{
public:
    static void SetUpTestSuite(void)
    {
        IUTEST_SUCCEED() << "SetUpTestSuite";
    }
    static void TearDownTestSuite(void)
    {
        IUTEST_SUCCEED() << "TearDownTestSuite";
    }
};
typedef iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Equal)
{
    TypeParam a = 0;
    IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST(TypedTest, Litle)
{
    TypeParam a = 1;
    IUTEST_ASSERT_LT(0, a);
}

#endif

/** --------------------------------------------------
 * 型をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypedTestP : public iutest::Test {};
typedef iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE_P(TypedTestP);

IUTEST_TYPED_TEST_P(TypedTestP, Equal)
{
    TypeParam a = 0;
    IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST_P(TypedTestP, Litle)
{
    TypeParam a = 1;
    IUTEST_ASSERT_LT(0, a);
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypedTestP, Equal, Litle);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(TypedTestPInstance, TypedTestP, TypedTestTypes);

#endif

/** --------------------------------------------------
 * Diabled Test
*//*--------------------------------------------------*/
IUTEST(TestDisabled, DISABLED_Test1)
{
    IUTEST_ASSERT_TRUE(false);
}

IUTEST(TestDisabled, Test2)
{
    IUTEST_ASSERT_TRUE(true);
}

IUTEST(DISABLED_TestCaseDisabled, Test1)
{
    IUTEST_ASSERT_TRUE(false);
}
IUTEST(DISABLED_TestCaseDisabled, Test2)
{
    IUTEST_ASSERT_TRUE(false);
}

/** --------------------------------------------------
 * 例外アサーション
*//*--------------------------------------------------*/
#if IUTEST_HAS_EXCEPTIONS

static void ExceptionFunction(int i)
{
    switch( i )
    {
    case 0:
        return;
    case 1:
        throw 2;
        break;
    case 2:
        throw ::std::bad_exception();
        break;
    default:
        break;
    }
}

IUTEST(AssertionTest, Exception)
{
    //IUTEST_ASSERT_THROW(throw ::std::bad_exception(), ::std::bad_exception);
    IUTEST_ASSERT_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_EXPECT_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_INFORM_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_ASSERT_ANY_THROW(ExceptionFunction(1));
    IUTEST_EXPECT_ANY_THROW(ExceptionFunction(1));
    IUTEST_INFORM_ANY_THROW(ExceptionFunction(1));
    IUTEST_ASSERT_NO_THROW(ExceptionFunction(0));
    IUTEST_EXPECT_NO_THROW(ExceptionFunction(0));
    IUTEST_INFORM_NO_THROW(ExceptionFunction(0));
}

class exception_test
{
public:
    explicit exception_test(const ::std::vector<int>&)
    {
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
    }
};

IUTEST(AssertionTest, Exception2)
{
    ::std::vector<int> a;
    IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

/** --------------------------------------------------
 * 型の一致テスト
*//*--------------------------------------------------*/
IUTEST(StaticTest, Eq)
{
    IUTEST_ASSERT_TRUE( (iutest::StaticAssertTypeEq<int, int>()) );
    //iutest::StaticAssertTypeEq<bool, int>();
}

