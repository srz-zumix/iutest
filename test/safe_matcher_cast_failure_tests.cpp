//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        safe_matcher_cast_failure_tests.cpp
 * @brief       SafeMatcherCast compile-error tests
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

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::MatcherCast;
using ::iutest::matchers::SafeMatcherCast;

namespace {

struct Explicit
{
    explicit Explicit(int) {}
};

struct Base { virtual ~Base() {} };
struct Derived : Base {};

}   // end of namespace

IUTEST(SafeMatcherCast, IntegerNarrowing)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<int>(MatcherCast<short>(0));
}

IUTEST(SafeMatcherCast, FloatingPointNarrowing)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<double>(MatcherCast<float>(0));
}

IUTEST(SafeMatcherCast, FloatingPointToInteger)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<double>(MatcherCast<int>(0));
}

IUTEST(SafeMatcherCast, IntegerToFloatingPoint)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<int>(MatcherCast<double>(0));
}

IUTEST(SafeMatcherCast, SignedToUnsigned)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<int>(MatcherCast<unsigned int>(0));
}

IUTEST(SafeMatcherCast, ValueToReference)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<int>(MatcherCast<const int&>(0));
}

IUTEST(SafeMatcherCast, ExplicitConversion)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    SafeMatcherCast<int>(MatcherCast<Explicit>(::iutest::matchers::_));
}

IUTEST(MatcherCast, PointerDowncast)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    MatcherCast<Base*>(MatcherCast<Derived*>(::iutest::matchers::_));
}

IUTEST(MatcherCast, ReferenceDowncast)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    MatcherCast<const Base&>(MatcherCast<const Derived&>(::iutest::matchers::_));
}

#endif
