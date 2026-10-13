//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        ref_matcher_tests.cpp
 * @brief       Reference identity matcher tests
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

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::Ref;

namespace {

int expected = 1;
int other = 1;

int& GetRef() { return expected; }

struct NonCopyable
{
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

#if !defined(IUTEST_USE_GMOCK)
struct OverloadedAddress
{
    OverloadedAddress* operator&() { return NULL; }  // NOLINT(runtime/operator)
    const OverloadedAddress* operator&() const { return NULL; }  // NOLINT(runtime/operator)
};
#endif

} // namespace

IUTEST(RefMatcher, Identity)
{
    IUTEST_EXPECT_THAT(GetRef(), Ref(expected));
    IUTEST_EXPECT_THAT(other, ::iutest::matchers::Not(Ref(expected)));
    NonCopyable object;
    IUTEST_EXPECT_THAT(object, Ref(object));
    const int constant = 2;
    IUTEST_EXPECT_THAT(constant, Ref(constant));
#if !defined(IUTEST_USE_GMOCK)
    OverloadedAddress overloaded[2];
    IUTEST_EXPECT_THAT(overloaded[0], Ref(overloaded[0]));
    IUTEST_EXPECT_THAT(overloaded[1], ::iutest::matchers::Not(Ref(overloaded[0])));
#endif
}

IUTEST(RefMatcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(other, Ref(expected)), "");
#if !defined(IUTEST_USE_GMOCK)
    ::std::ostringstream expected_address;
    expected_address << static_cast<const void*>(&expected);
    ::std::ostringstream actual_address;
    actual_address << static_cast<const void*>(&other);
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(other, Ref(expected)), expected_address.str().c_str());
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(other, Ref(expected)), actual_address.str().c_str());
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
