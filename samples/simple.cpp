//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        simple.cpp
 * @brief       sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * 簡単なテスト
*//*--------------------------------------------------*/
IUTEST(Test, Version)
{
    unsigned long v = (IUTEST_MAJORVER << 24) | (IUTEST_MINORVER << 16) | (IUTEST_BUILD << 8) | IUTEST_REVISION;
    IUTEST_ASSERT_EQ( IUTEST_VER, v );
}

IUTEST(Test, GetName)
{
    IUTEST_ASSERT_STREQ("GetName", test_info_->name());
    RecordProperty("test_name", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
    RecordProperty("number", 1);
}

IUTEST(Test, Stream)
{
    IUTEST_SUCCEED() << "OK!!";
    IUTEST_SUCCEED() << L"OK!!";
}

/* ---------------------------------------------------
 * スキップ
*//*--------------------------------------------------*/
IUTEST(SkipTest, Skip)
{
    IUTEST_SKIP() << "empty.";
}

#if IUTEST_HAS_ASSERTION_RETURN

/* ---------------------------------------------------
 * 戻り値のある関数での使用
*//*--------------------------------------------------*/
int ReturnTest()
{
    IUTEST_ASSERT_TRUE(true) << ::iutest::AssertionReturn(-1);
    return 0;
}

IUTEST(ReturnTest, Test)
{
    ReturnTest();
    IUTEST_ASSERT_TRUE(true);
    IUTEST_ASSERT_TRUE(true) << ::iutest::AssertionReturn();
}

#endif

/* ---------------------------------------------------
 * パッケージ
*//*--------------------------------------------------*/
IUTEST_PACKAGE(TestPackage)
{
    IUTEST(Test, Version)
    {
        IUTEST_ASSERT_TRUE(true);
    }
}

#if IUTEST_HAS_IF_EXISTS

IUTEST_PACKAGE(TestPackage)
{
    IUTEST_PACKAGE(TestPackage)
    {
        IUTEST(Test, Version)
        {
            IUTEST_ASSERT_TRUE(true);
        }
    }
}

#endif

/* ---------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if IUTEST_HAS_GENRAND

IUTEST(DISABLED_TestFailure, Random)
{
    IUTEST_EXPECT_EQ( genrand(), genrand() );
    IUTEST_EXPECT_EQ( genrand(), genrand() );
    IUTEST_EXPECT_EQ( genrand(), genrand() );
    IUTEST_EXPECT_EQ( genrand(), genrand() );
    IUTEST_EXPECT_EQ( genrand(), genrand() );
    IUTEST_EXPECT_EQ( genrand(), genrand() );
}

#endif

// サブルーチン
static void Sub1(int n)
{
    IUTEST_EXPECT_EQ(1, n);
}
static void Sub2(int n)
{
    IUTEST_ASSERT_EQ(1, n);
}

IUTEST(DISABLED_TestFailure, Subroutine1)
{
    {
        int x=100;
        IUTEST_SCOPED_TRACE(::iutest::Message() << "routine1. x=" << x);

        Sub1(x);
    }
    // ここの失敗には "routine1." のメッセージは表示されません。
    Sub1(3);
}

IUTEST(DISABLED_TestFailure, Subroutine2)
{
    {
        IUTEST_SCOPED_TRACE("routine2.");
#if !defined(IUTEST_USE_GTEST)
        IUTEST_SCOPED_TRACE("routine2.") << "iutest can do.";
#endif

        Sub2(2);
    }
    // ここの失敗には "routine2." のメッセージは表示されません。
    Sub2(3);
}

class ProdClass
{
    int m_x;
public:
    ProdClass() : m_x(100) {}
    int GetX() const { return m_x; }
};

IUTEST_MAKE_PEEP(int ProdClass::*, ProdClass, m_x);

IUTEST(ProdTest, Peep)
{
    ProdClass c;
    IUTEST_ASSERT_EQ(100, IUTEST_PEEP_GET(c, ProdClass, m_x));
}
