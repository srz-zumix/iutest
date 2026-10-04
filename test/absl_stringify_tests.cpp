//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        absl_stringify_tests.cpp
 * @brief       AbslStringify printer test
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

#if IUTEST_HAS_ABSL_STRINGIFY && (!defined(IUTEST_USE_GTEST) || (GTEST_VER >= 0x01150000 && defined(GTEST_HAS_ABSL)))

#include <absl/strings/str_cat.h>

namespace absl_stringify_test
{

struct Value
{
    int value;
};

template<typename Sink>
void AbslStringify(Sink& sink, const Value& value)
{
    sink.Append(absl::StrCat("absl:", value.value));
}

std::ostream& operator << (std::ostream& os, const Value&)
{
    return os << "stream";
}

struct WithPrintTo
{
    int value;
};

template<typename Sink>
void AbslStringify(Sink& sink, const WithPrintTo& value)
{
    sink.Append(absl::StrCat("absl:", value.value));
}

std::ostream& operator << (std::ostream& os, const WithPrintTo&)
{
    return os << "stream";
}

void PrintTo(const WithPrintTo& value, std::ostream* os)
{
    *os << "print:" << value.value;
}

}   // namespace absl_stringify_test

IUTEST(AbslStringifyTest, BeforeStream)
{
    absl_stringify_test::Value value = { 42 };
    IUTEST_EXPECT_STREQ("absl:42", ::iutest::PrintToString(value));
}

IUTEST(AbslStringifyTest, AfterPrintTo)
{
    absl_stringify_test::WithPrintTo value = { 42 };
    IUTEST_EXPECT_STREQ("print:42", ::iutest::PrintToString(value));
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
