//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printers_tests.cpp
 * @brief       iutest_printers.hpp テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
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

#if !defined(IUTEST_USE_GTEST)
TestLogger printer_logger;

class LogChecker
{
    ::std::string m_str;
public:
    explicit LogChecker(const char* str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
    ~LogChecker(void)
    {
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_EXPECT_STRIN(m_str.c_str(), printer_logger.c_str());
        printer_logger.clear();
    }
};
#else
class LogChecker
{
public:
    explicit LogChecker(const char*) {}
};
#endif

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
    IUTEST_SUCCEED() << ::iutest::PrintToString(bar);
}

#if !defined(IUTEST_USE_GTEST)
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
    LogChecker ck("40-Byte object < 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... >");
#endif
    IUTEST_SUCCEED() << ::iutest::PrintToString(bigvar);
}
#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedPrintToTest : public ::iutest::Test {};
typedef ::iutest::Types<char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, int*> PrintStringTestTypes;
IUTEST_TYPED_TEST_CASE(TypedPrintToTest, PrintStringTestTypes);

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

IUTEST(PrintToTest, Std)
{
    const int a[] = {0, 1, 2};
    ::std::pair<int, int> p(0, 1);
    ::std::vector<int> v(a, a+(sizeof(a)/sizeof(a[0])));

    {
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        LogChecker ck("0, 1");
#else
        LogChecker ck("4-Byte object < 00 00 00 00 >, 4-Byte object < 01 00 00 00 >");
#endif
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    }
    {
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        LogChecker ck("{ 0, 1, 2 }");
#else
        LogChecker ck("{ 4-Byte object < 00 00 00 00 >, 4-Byte object < 01 00 00 00 >, 4-Byte object < 02 00 00 00 > }");
#endif
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

IUTEST(PrintToTest, Null)
{
    {
        LogChecker ck("(null)");
        void* p = NULL;
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    }
    {
        LogChecker ck("(null)");
        void* p = NULL;
        IUTEST_SUCCEED() << p;
    }
}

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
IUTEST(PrintToTest, Iomanip)
{
    IUTEST_SUCCEED() << ::std::endl;
    IUTEST_SUCCEED() << ::std::ends;
}
#endif

IUTEST(PrintToTest, WideString)
{
    {
        LogChecker ck("Test");
        IUTEST_SUCCEED() << ::iutest::PrintToString(L"Test");
    }
    {
        LogChecker ck("\\0");
        wchar_t c = 0;
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    }
    {
        LogChecker ck("10");
        wchar_t c = L'\n';
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    }
//  {
//      LogChecker ck("\'A\'");
//      wchar_t c = L'A';
//      IUTEST_SUCCEED() << ::iutest::PrintToString(c);
//  }
    {
        LogChecker ck("(null)");
        wchar_t* p = NULL;
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    }
}

IUTEST(PrintToTest, String)
{
    {
        LogChecker ck("Test");
        IUTEST_SUCCEED() << ::iutest::PrintToString("Test");
    }
    {
        LogChecker ck("\\0");
        char c = 0;
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    }
    {
        LogChecker ck("10");
        char c = '\n';
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    }
    {
        LogChecker ck("\'A\'");
        char c = 'A';
        IUTEST_SUCCEED() << ::iutest::PrintToString(c);
    }
    {
        LogChecker ck("(null)");
        char* p = NULL;
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    }
}

#if IUTEST_HAS_CHAR16_T
IUTEST(PrintToTest, U16String)
{
    IUTEST_SUCCEED() << ::iutest::PrintToString(u"Test");
    {
        LogChecker ck("(null)");
        char16_t* p = NULL;
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
    }
}
#endif

#if IUTEST_HAS_CHAR32_T
IUTEST(PrintToTest, U32String)
{
    IUTEST_SUCCEED() << ::iutest::PrintToString(U"Test");
    {
        LogChecker ck("(null)");
        char32_t* p = NULL;
        IUTEST_SUCCEED() << ::iutest::PrintToString(p);
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
        LogChecker ck("8-Byte object <");
        IUTEST_SUCCEED() << ::iutest::PrintToString(p0);
    }
    {
        LogChecker ck("(operator overload)");
        IUTEST_SUCCEED() << ::iutest::PrintToString(p1);
    }
    {
        LogChecker ck("(function overload)");
        IUTEST_SUCCEED() << ::iutest::PrintToString(p2);
    }
}

#endif

struct Hoge {
    int a[256];
};
IUTEST(PrintToTest, MaxElem)
{
    Hoge hoge;
    {
        LogChecker ck(" ...");
        IUTEST_SUCCEED() << ::iutest::PrintToString(hoge);
    }
    {
        LogChecker ck(", ...");
        IUTEST_SUCCEED() << ::iutest::PrintToString(hoge.a);
    }
    {
        ::std::vector<int> v(hoge.a, hoge.a+256);
        LogChecker ck(", ...");
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

#if IUTEST_HAS_NULLPTR
IUTEST(PrintToTest, Nullptr)
{
    LogChecker ck("nullptr");
    IUTEST_SUCCEED() << ::iutest::PrintToString(nullptr);
}
#endif

#if IUTEST_HAS_TUPLE
IUTEST(PrintToTest, Tuple)
{
    ::iutest::tuples::tuple<bool, int, char> t(false, 100, 'a');

    IUTEST_SUCCEED() << ::iutest::PrintToString(t);
}
#endif

