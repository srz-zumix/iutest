//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        incomplete_printers_tests.cpp
 * @brief       incomplete type printer test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

struct Incomplete;

#if (!defined(__GNUC__) || __GNUC__ != 3 || defined(__clang__)) \
    && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(IncompletePrintersTest, Reference)
{
    char object = 0;
    IUTEST_EXPECT_STREQ("(incomplete type)", ::iutest::PrintToString(reinterpret_cast<Incomplete&>(object)));
}
#endif

struct Complete
{
    unsigned char bytes[2];
};

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01060000
IUTEST(IncompletePrintersTest, CompleteRawBytes)
{
    Complete object = { { 0, 1 } };
#if defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("2-byte object <00-01>", ::iutest::PrintToString(object));
#else
    IUTEST_EXPECT_STREQ("2-Byte object < 00 01 >", ::iutest::PrintToString(object));
#endif
}
#endif

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01060000
IUTEST(IncompletePrintersTest, CompleteBuiltin)
{
    IUTEST_EXPECT_STREQ("42", ::iutest::PrintToString(42));
    IUTEST_EXPECT_STREQ("true", ::iutest::PrintToString(true));
}

namespace complete_printer_test
{

struct Custom
{
};

void PrintTo(const Custom&, ::iutest::iu_ostream* os)
{
    *os << "custom";
}

struct Streamable
{
};

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Streamable&)
{
    return os << "streamable";
}

}   // namespace complete_printer_test

IUTEST(IncompletePrintersTest, CompleteCustomPrinter)
{
    IUTEST_EXPECT_STREQ("custom", ::iutest::PrintToString(complete_printer_test::Custom()));
}

IUTEST(IncompletePrintersTest, CompleteStreamable)
{
    IUTEST_EXPECT_STREQ("streamable", ::iutest::PrintToString(complete_printer_test::Streamable()));
}
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
