//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printers_overload_tests.cpp
 * @brief       overload default printers test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

#if IUTEST_HAS_CXX_HDR_STRING_VIEW

namespace std
{

void PrintTo(const ::std::string_view&, ::iutest::iu_ostream* os)
{
    *os << "{5c3016c8-9d8a-4b8f-b15d-2e12a91474b2}";
}

}

IUTEST(StringView, PrintTo)
{
    LogChecker ck("{5c3016c8-9d8a-4b8f-b15d-2e12a91474b2}");
    ::std::string_view view = "Hello";
    IUTEST_SUCCEED() << ::iutest::PrintToString(view);
}

#endif

#define DECL_BAR()      \
    struct Bar {        \
        int x, y, z;    \
        bool operator == (const Bar& rhs) const {           \
            return x == rhs.x && y == rhs.y && z == rhs.z;  \
        }               \
    }

namespace Foo
{
    DECL_BAR();

    ::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Bar& bar)
    {
        return os << "x:" << bar.x << " y:" << bar.y << " z:" << bar.z;
    }
}

IUTEST(PrintToTest, OperatorPrintToBar)
{
    Foo::Bar bar = {0, 1, 2};
    LogChecker ck("x:0 y:1 z:2");
    IUTEST_SUCCEED() << ::iutest::PrintToString(bar);
}

DECL_BAR();

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Bar& bar)
{
    IUTEST_ADD_FAILURE();
    return os << "X:" << bar.x << " Y:" << bar.y << " Z:" << bar.z;
}

void PrintTo(const Bar& bar, ::iutest::iu_ostream* os)
{
    *os << "x:" << bar.x << " y:" << bar.y << " z:" << bar.z;
}

IUTEST(PrintToTest, PrintToBar)
{
    Bar bar = {0, 1, 2};
    LogChecker ck("x:0 y:1 z:2");
    IUTEST_SUCCEED() << ::iutest::PrintToString(bar);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
