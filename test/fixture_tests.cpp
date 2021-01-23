//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fixture_tests.cpp
 * @brief       fixture test
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

class TestSetUpEachCall : public ::iuutil::backward::Test<TestSetUpEachCall>
{
protected:
    static int x;
public:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        ++x;
    }
    static void SetUpTestCase(void)
    {
        x = 0;
    }
};
int TestSetUpEachCall::x = -1;

IUTEST_F(TestSetUpEachCall, Test1)
{
    IUTEST_ASSERT_EQ(1, x);
}

IUTEST_F(TestSetUpEachCall, Test2)
{
    IUTEST_ASSERT_EQ(2, x);
}

class TestFixture : public ::iuutil::backward::Test<TestFixture>
{
public:
    static int x;
public:
    static void SetUpTestCase(void)
    {
        IUTEST_ASSERT_EQ(-1, x);
        x = 0;
    }
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        IUTEST_ASSERT_EQ(0, x);
        ++x;
    }
    virtual void TearDown(void) IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        IUTEST_ASSERT_EQ(2, x);
        ++x;
    }
    static void TearDownTestCase(void)
    {
        IUTEST_ASSERT_EQ(3, x);
        x = -1;
    }
};
int TestFixture::x = -1;

IUTEST_F(TestFixture, Test)
{
    IUTEST_ASSERT_EQ(1, x);
    ++x;
}


#if !defined(IUTEST_USE_GTEST)

class TestFixtureLikeVCUnit : public ::iutest::Test
{
public:
    static int x;

    ~TestFixtureLikeVCUnit()
    {
        IUTEST_EXPECT_EQ(3, x);
    }
public:
    IUTEST_CLASS_INITIALIZE(a)
    {
        IUTEST_ASSERT_EQ(-1, x);
        x = 0;
    }
    IUTEST_METHOD_INITIALIZE(b)
    {
        IUTEST_ASSERT_EQ(0, x);
        ++x;
    }
    IUTEST_METHOD_CLEANUP(c)
    {
        IUTEST_ASSERT_EQ(2, x);
        ++x;
    }
    IUTEST_CLASS_CLEANUP(d)
    {
        IUTEST_ASSERT_EQ(3, x);
        x = -x;
        IUTEST_SUCCEED() << x;
    }
};
int TestFixtureLikeVCUnit::x = -1;

IUTEST_F(TestFixtureLikeVCUnit, Test)
{
    IUTEST_ASSERT_EQ(1, x);
    ++x;
}

#endif

