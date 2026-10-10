//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        throws_matcher_tests.cpp
 * @brief       Throws matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01110000)

#include <stdexcept>

using ::iutest::matchers::Eq;
using ::iutest::matchers::HasSubstr;
using ::iutest::matchers::Throws;
using ::iutest::matchers::ThrowsMessage;

namespace {

struct Error
{
    explicit Error(int n) : value(n) {}
    bool operator==(const Error& rhs) const { return value == rhs.value; }
    int value;
};

struct ThrowError
{
    void operator()() const { throw Error(7); }
};

struct ThrowOther
{
    void operator()() const { throw std::runtime_error("other"); }
};

struct NoThrow
{
    void operator()() const {}
};

ThrowError throw_error;
ThrowOther throw_other;
NoThrow no_throw;

} // namespace

IUTEST(ThrowsMatcher, Matches)
{
    IUTEST_EXPECT_THAT(throw_error, Throws<Error>());
    IUTEST_EXPECT_THAT(throw_error, Throws<Error>(Eq(Error(7))));
    IUTEST_EXPECT_THAT(throw_other, ThrowsMessage<std::runtime_error>(HasSubstr("oth")));
}

IUTEST(ThrowsMatcher, Failures)
{
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(no_throw, Throws<Error>()), "did not throw");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(throw_other, Throws<Error>()), "different type");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(throw_error, Throws<Error>(Eq(Error(8)))), "did not match");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(no_throw, ThrowsMessage<std::runtime_error>(HasSubstr("other"))), "did not throw");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(throw_error, ThrowsMessage<std::runtime_error>(HasSubstr("other"))), "different type");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(throw_other, ThrowsMessage<std::runtime_error>(HasSubstr("missing"))), "did not match");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(no_throw, Throws<Error>()), "");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(throw_other, Throws<Error>()), "");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(throw_error, Throws<Error>(Eq(Error(8)))), "");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(no_throw, ThrowsMessage<std::runtime_error>(HasSubstr("other"))), "");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(throw_error, ThrowsMessage<std::runtime_error>(HasSubstr("other"))), "");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(throw_other, ThrowsMessage<std::runtime_error>(HasSubstr("missing"))), "");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
