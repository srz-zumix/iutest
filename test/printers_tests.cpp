//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printers_tests.cpp
 * @brief       iutest_printers.hpp テスト
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
#include "logger_tests.hpp"

#if !defined(IUTEST_USE_GTEST)

#define IUTEST_PRINTTOSTRING_EQ(expect, val)        \
    IUTEST_EXPECT_STREQ(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#define IUTEST_PRINTTOSTRING_CONTAIN(expect, val)  \
    IUTEST_EXPECT_STRIN(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#else

#define IUTEST_PRINTTOSTRING_EQ(expect, val)        \
    (void)(expect); \
    (void)(val)

#define IUTEST_PRINTTOSTRING_CONTAIN(expect, val)   \
    (void)(expect); \
    (void)(val)

#endif

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#define IUTEST_STREAMOUT_CHECK(val) \
    IUTEST_SUCCEED() << val

#else

#define IUTEST_STREAMOUT_CHECK(val) \
    IUTEST_SUCCEED() << ::iutest::PrintToString(val)

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
    IUTEST_PRINTTOSTRING_EQ(ck, bar);
    IUTEST_STREAMOUT_CHECK(bar);
}

#if !defined(IUTEST_USE_GTEST)

IUTEST(PrintToTest, FloatingPoint)
{
    ::iutest::floating_point<float> f = 1.0f;
    ::iutest::internal::FloatingPoint<float> F(1.0f);
    IUTEST_ASSERT_STREQ(::iutest::PrintToString(f), ::iutest::PrintToString(F));
}

#if IUTEST_HAS_INT128
IUTEST(PrintToTest, Int128)
{
    typedef ::iutest::internal::TypeWithSize<16>::Int i128_t;
    IUTEST_ASSUME_EQ(16u, sizeof(i128_t));
    i128_t i128 = ::iutest::detail::numeric_min< ::iutest::internal::TypeWithSize<8>::Int >(); // -9223372036854775808
    i128 -= 1;
    LogChecker ck("0xFFFFFFFFFFFFFFFF7FFFFFFFFFFFFFFF");
    IUTEST_PRINTTOSTRING_EQ(ck, i128);
    IUTEST_STREAMOUT_CHECK(i128);
}

IUTEST(PrintToTest, UInt128)
{
    typedef ::iutest::internal::TypeWithSize<16>::UInt i128_t;
    IUTEST_ASSUME_EQ(16u, sizeof(i128_t));
    i128_t i128 = ::iutest::detail::numeric_max< ::iutest::internal::TypeWithSize<8>::UInt >(); // 18446744073709551615;
    i128 += 1;
    LogChecker ck("0x00000000000000010000000000000000");
    IUTEST_PRINTTOSTRING_EQ(ck, i128);
    IUTEST_STREAMOUT_CHECK(i128);
}
#endif

#if IUTEST_HAS_LONG_DOUBLE
IUTEST(PrintToTest, LongDouble)
{
    ::iutest::internal::LongDouble ld(static_cast< ::iutest::internal::LongDouble::Float>(1.0f));
    LogChecker ck("1");
    IUTEST_PRINTTOSTRING_CONTAIN(ck, ld);
    IUTEST_STREAMOUT_CHECK(ld);
}
#endif

#if IUTEST_HAS_FLOAT128
IUTEST(PrintToTest, Float128)
{
    ::iutest::internal::Float128 f128(static_cast< ::iutest::internal::Float128::Float>(1.0f));
    LogChecker ck("1");
    IUTEST_PRINTTOSTRING_CONTAIN(ck, f128);
    IUTEST_STREAMOUT_CHECK(f128);
}
#endif


IUTEST(PrintToTest, IutestAnyNotInitialized)
{
    ::iutest::any a;
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("empty");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
#else
    LogChecker ck("-Byte object < 00 00 00 00 ");
    IUTEST_PRINTTOSTRING_CONTAIN(ck, a);
#endif
    IUTEST_STREAMOUT_CHECK(a);
}

IUTEST(PrintToTest, IutestAnyString)
{
    ::iutest::any a = "any-test";
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("any-test");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
#else
    LogChecker ck("-Byte object");
    IUTEST_PRINTTOSTRING_CONTAIN(ck, a);
#endif
    IUTEST_STREAMOUT_CHECK(a);
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
    IUTEST_STREAMOUT_CHECK(bigvar);
}
#endif

IUTEST(PrintToTest, RawArray)
{
    unsigned char a[3] = {0, 1, 2};
    LogChecker ck("{ 0, 1, 2 }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_STREAMOUT_CHECK(a);
}

IUTEST(PrintToTest, RawMultiArray)
{
    int a[2][2] = { {0, 1}, {2, 3} };
    LogChecker ck("{ { 0, 1 }, { 2, 3 } }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_STREAMOUT_CHECK(a);
}

IUTEST(PrintToTest, StdPair)
{
    ::std::pair<int, int> p(0, 1);
    LogChecker ck("(0, 1)");
    IUTEST_PRINTTOSTRING_EQ(ck, p);
    IUTEST_STREAMOUT_CHECK(p);
}

IUTEST(PrintToTest, StdVector)
{
    const int a[] = {0, 1, 2};
    ::std::vector<int> v(a, a+(sizeof(a)/sizeof(a[0])));
    LogChecker ck("{ 0, 1, 2 }");
    IUTEST_PRINTTOSTRING_EQ(ck, v);
    IUTEST_STREAMOUT_CHECK(v);
}

IUTEST(PrintToTest, Null)
{
    LogChecker ck("(null)");
    void* p = NULL;
    IUTEST_PRINTTOSTRING_EQ(ck, p);
    IUTEST_STREAMOUT_CHECK(p);
}

IUTEST(PrintToTest, String)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, "XYZ");
        IUTEST_STREAMOUT_CHECK("XYZ");
    }
    {
        LogChecker ck("\\0");
        char c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("0x0A");
        char c = '\n';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("\'A\'");
        char c = 'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("0x80");
        unsigned char uc = 0x80;
        char c = static_cast<char>(uc);
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("(null)");
        char* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_STREAMOUT_CHECK(p);
    }
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, StringStringView)
{
    {
        LogChecker ck("XYZ");
        ::std::string_view view = "XYZ";
        IUTEST_PRINTTOSTRING_EQ(ck, view);
        IUTEST_STREAMOUT_CHECK(view);
    }
}
#endif

IUTEST(PrintToTest, WideString)
{
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, L"XYZ");
        IUTEST_STREAMOUT_CHECK(L"XYZ");
    }
    {
        LogChecker ck("\\0");
        wchar_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("000A");
        wchar_t c = L'\n';
        IUTEST_PRINTTOSTRING_CONTAIN(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("\'A\'");
        wchar_t c = L'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("(null)");
        wchar_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_STREAMOUT_CHECK(p);
    }
}

IUTEST_PRAGMA_MSC_WARN_PUSH()
IUTEST_PRAGMA_MSC_WARN_DISABLE(4566)

IUTEST(PrintToTest, SurrogatePair)
{
#if !defined(IUTEST_USE_GTEST)
    {
        const wchar_t* p = L"\U00020BB7";
        const ::std::string s = ::iutest::PrintToString(p);
        if( s[0] == '0' )
        {
            // LogChecker ck("00020BB7000091CE00005BB6");
            LogChecker ck("00020BB7");
            IUTEST_PRINTTOSTRING_CONTAIN(ck, s);
            IUTEST_STREAMOUT_CHECK(p);
        }
        else if( s[0] == '?' )
        {
            // FIXME
        }
        else
        {
            LogChecker ck("\U00020BB7");
            IUTEST_PRINTTOSTRING_EQ(ck, s);
            IUTEST_STREAMOUT_CHECK(p);
        }
    }
#endif
#if IUTEST_HAS_CHAR16_T_PRINTABLE
    {
        const char16_t* p = u"\U00020BB7";
        const ::std::string s = ::iutest::PrintToString(p);
        if( s[0] == '?' )
        {
            // FIXME
        }
        else
        {
            LogChecker ck("\U00020BB7");
            IUTEST_PRINTTOSTRING_EQ(ck, s);
            IUTEST_STREAMOUT_CHECK(p);
        }
    }
#endif
}

IUTEST_PRAGMA_MSC_WARN_POP()

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, WideStringStringView)
{
    {
        LogChecker ck("XYZ");
        ::std::wstring_view view = L"XYZ";
        IUTEST_PRINTTOSTRING_EQ(ck, view);
        IUTEST_STREAMOUT_CHECK(view);
    }
}
#endif

#if IUTEST_HAS_CHAR16_T
IUTEST(PrintToTest, U16String)
{
#if IUTEST_HAS_CHAR16_T_PRINTABLE
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, u"XYZ");
        IUTEST_STREAMOUT_CHECK(u"XYZ");
    }
    {
        LogChecker ck("\'A\'");
        char16_t c = u'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
#endif
    {
        LogChecker ck("\\0");
        char16_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("(null)");
        char16_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_STREAMOUT_CHECK(p);
    }
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, U16StringStringView)
{
    {
        LogChecker ck("XYZ");
        ::std::u16string_view view = u"XYZ";
        IUTEST_PRINTTOSTRING_EQ(ck, view);
        IUTEST_STREAMOUT_CHECK(view);
    }
}
#endif
#endif

#if IUTEST_HAS_CHAR32_T
IUTEST(PrintToTest, U32String)
{
#if IUTEST_HAS_CHAR32_T_PRINTABLE
    {
        LogChecker ck("XYZ");
        IUTEST_PRINTTOSTRING_EQ(ck, U"XYZ");
        IUTEST_STREAMOUT_CHECK(U"XYZ");
    }
    {
        LogChecker ck("\'A\'");
        char32_t c = U'A';
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
#endif
    {
        LogChecker ck("\\0");
        char32_t c = 0;
        IUTEST_PRINTTOSTRING_EQ(ck, c);
        IUTEST_STREAMOUT_CHECK(c);
    }
    {
        LogChecker ck("(null)");
        char32_t* p = NULL;
        IUTEST_PRINTTOSTRING_EQ(ck, p);
        IUTEST_STREAMOUT_CHECK(p);
    }
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(PrintToTest, U32StringStringView)
{
    {
        LogChecker ck("XYZ");
        ::std::u32string_view view = U"XYZ";
        IUTEST_PRINTTOSTRING_EQ(ck, view);
        IUTEST_STREAMOUT_CHECK(view);
    }
}
#endif
#endif

#if IUTEST_HAS_PRINT_TO

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

IUTEST(PrintToTest, Overload)
{
    Point0 p0 = { 0x12345678, 0x9ABCDEF0 };
    Point1 p1 = {0, 0};
    Point2 p2 = {1, 1};
    {
        PrintToLogChecker ck("8-Byte object < 78 56 34 12 F0 DE BC 9A >");
        IUTEST_PRINTTOSTRING_EQ(ck, p0);
        IUTEST_STREAMOUT_CHECK(p0);
    }
    {
        PrintToLogChecker ck("0, 0(operator overload)");
        IUTEST_PRINTTOSTRING_EQ(ck, p1);
        IUTEST_STREAMOUT_CHECK(p1);
    }
    {
        PrintToLogChecker ck("1, 1(function overload)");
        IUTEST_PRINTTOSTRING_EQ(ck, p2);
        IUTEST_STREAMOUT_CHECK(p2);
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
    IUTEST_STREAMOUT_CHECK(hoge);
}
IUTEST(PrintToTest, ThresholdArraySize)
{
    int a[256] = { 0 };
    LogChecker ck("{ 0, 0, 0, 0, 0, 0, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0, 0 }");
    IUTEST_PRINTTOSTRING_EQ(ck, a);
    IUTEST_STREAMOUT_CHECK(a);
}
IUTEST(PrintToTest, ThresholdContainerSizer)
{
    int a[256] = { 0 };
    ::std::vector<int> v(a, a+256);
    LogChecker ck("{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ... }");
    IUTEST_PRINTTOSTRING_EQ(ck, v);
    IUTEST_STREAMOUT_CHECK(v);
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
    IUTEST_STREAMOUT_CHECK(t);
}
#endif

#if IUTEST_HAS_CXX_HDR_VARIANT

#if IUTEST_HAS_EXCEPTIONS
struct AlwaysThrow
{
    AlwaysThrow() = default;
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow(const AlwaysThrow &)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow(AlwaysThrow &&)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow &operator=(const AlwaysThrow &)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow &operator=(AlwaysThrow &&)
    {
        throw std::exception();
    }
};
#endif

IUTEST(PrintToTest, Variant)
{
    {
        PrintToLogChecker ck("1234");
        ::std::variant<int, float, ::std::string> v = 1234;
        IUTEST_PRINTTOSTRING_EQ(ck, v);
        IUTEST_STREAMOUT_CHECK(v);
    }
    {
        PrintToLogChecker ck("test");
        ::std::variant<int, float, ::std::string> v("test");
        IUTEST_PRINTTOSTRING_EQ(ck, v);
        IUTEST_STREAMOUT_CHECK(v);
    }
    {
        PrintToLogChecker ck("monostate");
        ::std::variant<std::monostate, int, float, std::string> v;
        IUTEST_PRINTTOSTRING_EQ(ck, v);
        IUTEST_STREAMOUT_CHECK(v);
    }
#if IUTEST_HAS_EXCEPTIONS && !defined(IUTEST_USE_GTEST)
    {
        // gtest no support variant valueless
        PrintToLogChecker ck("valueless_by_exception");
        ::std::variant<int, float, AlwaysThrow> v = 0.2f;
        try
        {
            struct S { operator int() { throw 42; } };
            v.emplace<0>(S());
        }
        catch(...)
        {
            IUTEST_INFORM_TRUE(v.valueless_by_exception());
        }
        if( !v.valueless_by_exception() )
        {
            try
            {
                v = AlwaysThrow();
            }
            catch(...)
            {
                IUTEST_INFORM_TRUE(v.valueless_by_exception());
            }
        }

        IUTEST_PRINTTOSTRING_EQ(ck, v);
        IUTEST_STREAMOUT_CHECK(v);
    }
#endif
}

#endif
