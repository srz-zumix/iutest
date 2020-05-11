//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printers_tests.cpp
 * @brief       iutest_printers.hpp テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <vector>
#include "iutest.hpp"
#include "logger_tests.hpp"

#define IUTEST_PRINTTOSTRING_EQ(expect, val)        \
    IUTEST_EXPECT_STREQ(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#define IUTEST_PRINTTOSTRING_CONTAINE(expect, val)  \
    IUTEST_EXPECT_STRIN(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

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
    IUTEST_ADD_FAILURE();
    return os << "X:" << bar.x << " Y:" << bar.y << " Z:" << bar.z;
}

void PrintTo(const Bar& bar, ::iutest::iu_ostream* os)
{
    *os << "x:" << bar.x << " y:" << bar.y << " z:" << bar.z;
}

IUTEST(PrintToTest, Bar)
{
    Bar bar = {0, 1, 2};
    LogChecker ck("x:0 y:1 z:2");
    IUTEST_PRINTTOSTRING_EQ(ck, bar);
    IUTEST_SUCCEED() << bar;
}

#if !defined(IUTEST_USE_GTEST)

IUTEST(PrintToTest, IutestAnyNotInitialized)
{
    ::iutest::any a;
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("empty");
#else
    LogChecker ck("8-Byte object < 00 00 00 00 00 00 00 00 >");
#endif
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_SUCCEED() << a;
}

IUTEST(PrintToTest, IutestAnyString)
{
    ::iutest::any a = "any-test";
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("any-test");
#else
    LogChecker ck("8-Byte object");
#endif
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_SUCCEED() << a;
}

struct BigVar
{
    int big[10];
    BigVar() { memset(big, 0, sizeof(big)); }
    operator ::iutest::BiggestInt () const
    {
        return 42;
    }
};

IUTEST(PrintToTest, BigVar)
{
    BigVar bigvar;
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("42");
#else
    LogChecker ck("40-Byte object < 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... >");
#endif
    IUTEST_PRINTTOSTRING_EQ(ck, bigvar);
    IUTEST_SUCCEED() << bigvar;
}
#endif

IUTEST(PrintToTest, RawArray)
{
    unsigned char a[3] = {0, 1, 2};
    LogChecker ck("{ 0, 1, 2 }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_SUCCEED() << a;
}

IUTEST(PrintToTest, RawMultiArray)
{
    int a[2][2] = { {0, 1}, {2, 3} };
    LogChecker ck("{ { 0, 1 }, { 2, 3 } }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_SUCCEED() << a;
}

IUTEST(PrintToTest, StdPair)
{
    ::std::pair<int, int> p(0, 1);
    LogChecker ck("(0, 1)");
    IUTEST_PRINTTOSTRING_EQ(ck, p);
    IUTEST_SUCCEED() << p;
}

IUTEST(PrintToTest, StdVector)
{
    const int a[] = {0, 1, 2};
    ::std::vector<int> v(a, a+(sizeof(a)/sizeof(a[0])));
    LogChecker ck("{ 0, 1, 2 }");
    IUTEST_PRINTTOSTRING_EQ(ck, v);
    IUTEST_SUCCEED() << v;
}

IUTEST(PrintToTest, Null)
{
    LogChecker ck("(null)");
    void* p = NULL;
    IUTEST_PRINTTOSTRING_EQ(ck, p);
    IUTEST_SUCCEED() << p;
}

IUTEST(PrintToTest, WideString)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, L"XYZ");
        IUTEST_SUCCEED() << L"XYZ";
    }
    {
        LogChecker ck("\\0");
        wchar_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("10");
        wchar_t c = L'\n';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("\'A\'");
        wchar_t c = L'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("(null)");
        wchar_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_SUCCEED() << p;
    }
}

IUTEST(PrintToTest, String)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, "XYZ");
        IUTEST_SUCCEED() << "XYZ";
    }
    {
        LogChecker ck("\\0");
        char c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("10");
        char c = '\n';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("\'A\'");
        char c = 'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("(null)");
        char* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_SUCCEED() << p;
    }
}

#if IUTEST_HAS_CHAR16_T
IUTEST(PrintToTest, U16String)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, u"XYZ");
        IUTEST_SUCCEED() << u"XYZ";
    }
    {
        LogChecker ck("0");
        char16_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("65");
        char16_t c = u'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("(null)");
        char16_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_SUCCEED() << p;
    }
}
#endif

#if IUTEST_HAS_CHAR32_T
IUTEST(PrintToTest, U32String)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, U"XYZ");
        IUTEST_SUCCEED() << U"XYZ";
    }
    {
        LogChecker ck("0");
        char32_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("65");
        char32_t c = U'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_SUCCEED() << c;
    }
    {
        LogChecker ck("(null)");
        char32_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_SUCCEED() << p;
    }
}
#endif

struct Point0
{
    unsigned int x, y;
};
struct Point1
{
    int x, y;
};
struct Point2
{
    int x, y;
};

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Point1& x)
{
    return os << x.x << ", " << x.y << "(operator overload)";
}

void PrintTo(const Point2& x, ::iutest::iu_ostream* os)
{
    *os << x.x << ", " << x.y << "(function overload)";
}

#if IUTEST_HAS_PRINT_TO

IUTEST(PrintToTest, Overload)
{
    Point0 p0 = { 0x12345678, 0x9ABCDEF0 };
    Point1 p1 = {0, 0};
    Point2 p2 = {1, 1};
    {
        LogChecker ck("8-Byte object < 78 56 34 12 F0 DE BC 9A >");
        IUTEST_PRINTTOSTRING_EQ(ck, p0);
        IUTEST_SUCCEED() << p0;
    }
    {
        LogChecker ck("0, 0(operator overload)");
        IUTEST_PRINTTOSTRING_EQ(ck, p1);
        IUTEST_SUCCEED() << p1;
    }
    {
        LogChecker ck("1, 1(function overload)");
        IUTEST_PRINTTOSTRING_EQ(ck, p2);
        IUTEST_SUCCEED() << p2;
    }
}

#endif

struct Hoge {
    int a[256];
};
IUTEST(PrintToTest, ThresholdObjectSize)
{
    Hoge hoge = { { 0 } };
    LogChecker ck("1024-Byte object < 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... >");
    IUTEST_PRINTTOSTRING_EQ(ck, hoge);
    IUTEST_SUCCEED() << hoge;
}
IUTEST(PrintToTest, ThresholdArraySize)
{
    int a[256] = { 0 };
    LogChecker ck("{ 0, 0, 0, 0, 0, 0, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0, 0 }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_SUCCEED() << a;
}
IUTEST(PrintToTest, ThresholdContainerSizer)
{
    int a[256] = { 0 };
    ::std::vector<int> v(a, a+256);
    LogChecker ck("{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ... }");
    IUTEST_PRINTTOSTRING_EQ(ck, v);
    IUTEST_SUCCEED() << v;
}

#if IUTEST_HAS_NULLPTR
IUTEST(PrintToTest, Nullptr)
{
    IUTEST_PRINTTOSTRING_EQ("nullptr", nullptr);
}
#endif

#if IUTEST_HAS_TUPLE
IUTEST(PrintToTest, Tuple)
{
    LogChecker ck("(false, 100, 'a')");
    ::iutest::tuples::tuple<bool, int, char> t(false, 100, 'a');
    IUTEST_PRINTTOSTRING_EQ(ck, t);
    IUTEST_SUCCEED() << t;
}
#endif

