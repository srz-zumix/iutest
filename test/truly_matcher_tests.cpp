//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        truly_matcher_tests.cpp
 * @brief       Truly matcher tests
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

using ::iutest::matchers::Not;
using ::iutest::matchers::Truly;

namespace {

bool IsEven(int value)
{
    return value % 2 == 0;
}

struct GreaterThan
{
    explicit GreaterThan(int value) : threshold(value) {}
    bool operator()(int value) const { return value > threshold; }
    int threshold;
};

template<typename Matcher>
void CheckPredicateCopy(const Matcher& matcher, GreaterThan* predicate)
{
    predicate->threshold = 5;
    IUTEST_EXPECT_THAT(4, matcher);
}

int Identity(int value)
{
    return value;
}

class BoolLike
{
public:
    explicit BoolLike(bool value) : m_value(value) {}
    IUTEST_CXX_EXPLICIT_CONVERSION operator bool() const { return m_value; }
private:
    bool m_value;
};

BoolLike IsEvenBoolLike(int value)
{
    return BoolLike(IsEven(value));
}

struct HasAddress
{
    explicit HasAddress(const int* value) : address(value) {}
    bool operator()(const int& value) const { return &value == address; }
    const int* address;
};

} // namespace

IUTEST(TrulyMatcher, FunctionPointer)
{
    bool (*predicate)(int) = &IsEven;
    IUTEST_EXPECT_THAT(4, Truly(predicate));
    IUTEST_EXPECT_THAT(2, Truly(IsEven));
    IUTEST_EXPECT_THAT(3, Not(Truly(predicate)));
}

IUTEST(TrulyMatcher, FunctionObject)
{
    const GreaterThan predicate(3);
    IUTEST_EXPECT_THAT(4, Truly(predicate));
    IUTEST_EXPECT_THAT(3, Not(Truly(predicate)));
    IUTEST_EXPECT_THAT(5, Truly(GreaterThan(4)));
}

IUTEST(TrulyMatcher, StoresPredicateByValue)
{
    GreaterThan predicate(3);
    CheckPredicateCopy(Truly(predicate), &predicate);
}

IUTEST(TrulyMatcher, BoolConvertibleResult)
{
    IUTEST_EXPECT_THAT(2, Truly(Identity));
    IUTEST_EXPECT_THAT(-1, Truly(Identity));
    IUTEST_EXPECT_THAT(0, Not(Truly(Identity)));
    IUTEST_EXPECT_THAT(4, Truly(IsEvenBoolLike));
    IUTEST_EXPECT_THAT(3, Not(Truly(IsEvenBoolLike)));
}

IUTEST(TrulyMatcher, PassesArgumentByReference)
{
    const int value = 2;
    IUTEST_EXPECT_THAT(value, Truly(HasAddress(&value)));
}

#if IUTEST_HAS_LAMBDA
IUTEST(TrulyMatcher, Lambda)
{
    int threshold = 3;
    IUTEST_EXPECT_THAT(4, Truly([threshold](int value) { return value > threshold; }));
    IUTEST_EXPECT_THAT(3, Not(Truly([threshold](int value) { return value > threshold; })));
}
#endif

IUTEST(TrulyMatcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(3, Truly(IsEven)), "satisfies the given predicate");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(4, Not(Truly(IsEven))), "doesn't satisfy the given predicate");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
