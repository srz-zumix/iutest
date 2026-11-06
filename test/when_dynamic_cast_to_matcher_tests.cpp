//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        when_dynamic_cast_to_matcher_tests.cpp
 * @brief       Dynamic cast matcher tests
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

#if IUTEST_HAS_MATCHERS && IUTEST_HAS_RTTI \
    && (!defined(IUTEST_USE_GMOCK) || (GTEST_HAS_RTTI && GMOCK_VER >= 0x01080000))

using ::iutest::matchers::Eq;
using ::iutest::matchers::IsNull;
using ::iutest::matchers::Not;
using ::iutest::matchers::NotNull;
using ::iutest::matchers::Ref;
using ::iutest::matchers::WhenDynamicCastTo;

namespace {

struct Base
{
    virtual ~Base() {}
};

struct Derived : Base {};
struct Other : Base {};

Derived derived;
Derived another;
Other other;
Base* derived_ptr = &derived;
Base* other_ptr = &other;

} // namespace

IUTEST(WhenDynamicCastToMatcher, PointerSuccess)
{
    IUTEST_EXPECT_THAT(derived_ptr, WhenDynamicCastTo<Derived*>(NotNull()));
    IUTEST_EXPECT_THAT(derived_ptr, WhenDynamicCastTo<Derived*>(Eq(&derived)));
    IUTEST_EXPECT_THAT(derived_ptr, WhenDynamicCastTo<Derived*>(&derived));
    const Base* constant = derived_ptr;
    IUTEST_EXPECT_THAT(constant, WhenDynamicCastTo<const Derived*>(Eq(&derived)));
}

IUTEST(WhenDynamicCastToMatcher, PointerFailure)
{
    IUTEST_EXPECT_THAT(other_ptr, WhenDynamicCastTo<Derived*>(IsNull()));
    IUTEST_EXPECT_THAT(other_ptr, Not(WhenDynamicCastTo<Derived*>(NotNull())));
    IUTEST_EXPECT_THAT(static_cast<Base*>(NULL), WhenDynamicCastTo<Derived*>(IsNull()));
}

IUTEST(WhenDynamicCastToMatcher, ReferenceSuccess)
{
    const Base& base = derived;
    IUTEST_EXPECT_THAT(base, WhenDynamicCastTo<const Derived&>(Ref(derived)));
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_THAT(base, WhenDynamicCastTo<Derived&>(Ref(derived)));
#endif
}

IUTEST(WhenDynamicCastToMatcher, ReferenceFailure)
{
    const Base& base = other;
    IUTEST_EXPECT_THAT(base, Not(WhenDynamicCastTo<const Derived&>(Ref(derived))));
}

IUTEST(WhenDynamicCastToMatcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(other_ptr, WhenDynamicCastTo<Derived*>(NotNull())), "");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(*other_ptr, WhenDynamicCastTo<const Derived&>(Ref(derived))), "");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(*derived_ptr, WhenDynamicCastTo<const Derived&>(Ref(another))), "");
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(other_ptr, WhenDynamicCastTo<Derived*>(NotNull())), "WhenDynamicCastTo:");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(*other_ptr, WhenDynamicCastTo<const Derived&>(Ref(derived))),
        "cannot be dynamic_cast");
#endif
}

#if !defined(IUTEST_USE_GMOCK)
namespace {

struct OverloadedAddress : Derived
{
    const OverloadedAddress* operator&() const { return NULL; }  // NOLINT(runtime/operator)
};

} // namespace

IUTEST(WhenDynamicCastToMatcher, OverloadedAddress)
{
    OverloadedAddress object;
    IUTEST_EXPECT_THAT(object, WhenDynamicCastTo<const Derived&>(Ref(object)));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
