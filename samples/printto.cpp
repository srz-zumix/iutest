//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printto.cpp
 * @brief       printto sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * PrintTo
*//*--------------------------------------------------*/
#if IUTEST_HAS_PRINT_TO

struct Bar
{
    int x, y, z;
    bool operator == (const Bar& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Bar& bar)
{
    return os << "X:" << bar.x << " Y:" << bar.y << " Z:" << bar.z;
}

void PrintTo(const Bar& bar, ::iutest::iu_ostream* os)
{
    *os << "x:" << bar.x << " y:" << bar.y << " z:" << bar.z;
}

IUTEST(PrintToTest, Test1)
{
    ::std::vector<int> a;
    for( int i = 0; i < 10; ++i )
    {
        a.push_back(i);
    }
    IUTEST_SUCCEED() << ::iutest::PrintToString(a);

    int* pi=NULL;
    void* p=NULL;
    IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    IUTEST_SUCCEED() << ::iutest::PrintToString(pi);

    Bar bar = {0, 1, 2};
    IUTEST_SUCCEED() << ::iutest::PrintToString(bar);
}

IUTEST(PrintToTest, Test2)
{
    Bar bar1 = {0, 1, 2};
    Bar bar2 = {0, 1, 2};
    IUTEST_ASSERT_EQ(bar1, bar2);
}

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

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedPrintToTest : public ::iutest::Test {};
typedef ::iutest::Types<char, unsigned char
            , short, unsigned short
            , int, unsigned int
            , long, unsigned long
            , int*> PrintStringTestTypes;
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

#if IUTEST_HAS_CHAR16_T
IUTEST(PrintToTest, U16String)
{
    IUTEST_SUCCEED() << ::iutest::PrintToString(u"test");
}
#endif

#if IUTEST_HAS_CHAR32_T
IUTEST(PrintToTest, U32String)
{
    IUTEST_SUCCEED() << ::iutest::PrintToString(U"TEST");
}
#endif

#endif

#endif
