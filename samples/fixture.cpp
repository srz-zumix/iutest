//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fixture.cpp
 * @brief       fixture sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * テストフィクスチャの利用
*//*--------------------------------------------------*/
class TestFixed : public ::iutest::Test
{
protected:
    static int x;
public:
    virtual void SetUp()
    {
        ++x;
    }
    static void SetUpTestSuite()
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
    IUTEST_ASSERT_EQ(2, x);
}

typedef TestFixed TestFixed2;

struct Point
{
    int x, y;
    bool operator == (const Point& rhs) const { return x==rhs.x && y==rhs.y; }
};

IUTEST_F(TestFixed2, Test1)
{
    IUTEST_ASSERT_EQ(1, x);

    {
        Point a = {0, 0};
        Point b = {0, 0};
        IUTEST_EXPECT_EQ(a, b); // operator == があれば可能.
    }
}

IUTEST_F(TestFixed2, Test2)
{
    IUTEST_ASSERT_EQ(2, x);
    IUTEST_EXPECT_EQ(2, x);
    IUTEST_INFORM_EQ(2, x);
}
