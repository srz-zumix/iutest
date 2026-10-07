//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        address_matcher_tests.cpp
 * @brief       Address matcher tests
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

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01110000)

using ::iutest::matchers::Address;
using ::iutest::matchers::Eq;

namespace {

int address_target = 1;
int other = 1;

struct OverloadedAddress
{
    OverloadedAddress* operator&() { return NULL; }
    const OverloadedAddress* operator&() const { return NULL; }
};
OverloadedAddress objects[2];

} // namespace

IUTEST(AddressMatcher, SameAndDifferentObjects)
{
    IUTEST_EXPECT_THAT(address_target, Address(Eq(&address_target)));
    IUTEST_EXPECT_THAT(address_target, Address(&address_target));
    IUTEST_EXPECT_THAT(other, Address(Eq(&other)));
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(address_target, Address(Eq(&other))), "Address:");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(address_target, Address(Eq(&other))), "");
#endif
}

IUTEST(AddressMatcher, OverloadedAddressOf)
{
    IUTEST_EXPECT_THAT(objects[0], Address(Eq(objects)));
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(objects[0], Address(Eq(objects + 1))), "Address:");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(objects[0], Address(Eq(objects + 1))), "");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
