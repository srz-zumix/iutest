//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_cast_tests.cpp
 * @brief       Typed matcher cast tests
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

using ::iutest::matchers::Matcher;
using ::iutest::matchers::MatcherCast;
using ::iutest::matchers::SafeMatcherCast;

namespace {

const int matcher_expected = 42;

struct Base { virtual ~Base() {} };
struct Derived : Base {};

struct NonCopyable
{
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

#if !defined(IUTEST_USE_GTEST)
struct StatefulMatcher : ::iutest::detail::IMatcher
{
    explicit StatefulMatcher(int* live, int* copies)
        : m_live(live), m_copies(copies), m_calls(0) { ++*m_live; }
    StatefulMatcher(const StatefulMatcher& rhs)
        : ::iutest::detail::IMatcher(rhs)
        , m_live(rhs.m_live), m_copies(rhs.m_copies), m_calls(rhs.m_calls)
    {
        ++*m_live;
        ++*m_copies;
    }
    ~StatefulMatcher() IUTEST_CXX_OVERRIDE { --*m_live; }
    ::iutest::AssertionResult operator ()(int actual)
    {
        if( actual == ++m_calls ) return ::iutest::AssertionSuccess();
        return ::iutest::AssertionFailure();
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "has the next call count"; }
    int* m_live;
    int* m_copies;
    int m_calls;
};

struct CopyTrackedValue
{
    explicit CopyTrackedValue(int* copies) : m_copies(copies) {}
    CopyTrackedValue(const CopyTrackedValue& rhs) : m_copies(rhs.m_copies) { ++*m_copies; }
    int* m_copies;
};

struct IntegralConstant
{
    static const int value = 42;
};

struct VolatileValue
{
    explicit VolatileValue(int value) : m_value(value) {}
    VolatileValue(const volatile VolatileValue& rhs) : m_value(rhs.m_value) {}
    operator int() const { return m_value; }
    int m_value;
};

struct VolatileMatcher : ::iutest::detail::IMatcher
{
    explicit VolatileMatcher(int value) : m_value(value) {}
    VolatileMatcher(const volatile VolatileMatcher& rhs)
        : ::iutest::detail::IMatcher(), m_value(rhs.m_value) {}
    ::iutest::AssertionResult operator ()(int actual) const
    {
        if( actual == m_value ) return ::iutest::AssertionSuccess();
        return ::iutest::AssertionFailure();
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "matches the value"; }
    int m_value;
};

struct MutableConversion
{
    MutableConversion() : conversions(0) {}
    MutableConversion(const MutableConversion& rhs) : conversions(rhs.conversions) {}
    operator int() const { return ++conversions; }
    mutable int conversions;
};

int IdentityFunction(int value) { return value; }
#endif

int SelectOverload(const Matcher<int>&) { return 1; }
int SelectOverload(const Matcher< ::std::string>&) { return 2; }

Matcher<int> MakeValueMatcher()
{
    int value = matcher_expected;
    return MatcherCast<int>(value);
}

}   // end of namespace

IUTEST(MatcherCast, Value)
{
    const Matcher<int> matcher = MakeValueMatcher();
    IUTEST_EXPECT_TRUE(matcher.Matches(matcher_expected));
    IUTEST_EXPECT_FALSE(matcher.Matches(0));
    IUTEST_EXPECT_THAT(matcher_expected, matcher);
    IUTEST_EXPECT_THAT(0, ::iutest::matchers::Not(matcher));
    const Matcher< ::std::string> text = MatcherCast< ::std::string>("hello");
    IUTEST_EXPECT_TRUE(text.Matches("hello"));
    IUTEST_EXPECT_FALSE(text.Matches("world"));
    const Matcher<const ::std::string&> reference = MatcherCast<const ::std::string&>(::std::string("hello"));
    IUTEST_EXPECT_TRUE(reference.Matches("hello"));
}

IUTEST(MatcherCast, PolymorphicMatcher)
{
    const Matcher<int> matcher = MatcherCast<int>(::iutest::matchers::Eq(matcher_expected));
    IUTEST_EXPECT_TRUE(matcher.Matches(matcher_expected));
    IUTEST_EXPECT_FALSE(matcher.Matches(0));
    IUTEST_EXPECT_EQ(1, SelectOverload(MatcherCast<int>(::iutest::matchers::_)));
    IUTEST_EXPECT_EQ(2, SelectOverload(MatcherCast< ::std::string>(::iutest::matchers::_)));
}

IUTEST(MatcherCast, TypedMatcher)
{
    const Matcher<int> original = MatcherCast<int>(matcher_expected);
    const Matcher<short> safe = SafeMatcherCast<short>(original);
    IUTEST_EXPECT_TRUE(safe.Matches(42));
    IUTEST_EXPECT_FALSE(safe.Matches(0));
    const Matcher<double> unchecked = MatcherCast<double>(original);
    IUTEST_EXPECT_TRUE(unchecked.Matches(42.9));
    const Matcher<int> same = MatcherCast<int>(original);
    IUTEST_EXPECT_TRUE(same.Matches(matcher_expected));
}

IUTEST(MatcherCast, CopyAndAssignment)
{
    Matcher<int> assigned;
    {
        const Matcher<int> original = MakeValueMatcher();
        Matcher<int> copy(original);
        assigned = copy;
        copy = MatcherCast<int>(0);
        IUTEST_EXPECT_TRUE(copy.Matches(0));
    }
    IUTEST_EXPECT_TRUE(assigned.Matches(matcher_expected));
    Matcher<int>& alias = assigned;
    assigned = alias;
    IUTEST_EXPECT_TRUE(assigned.Matches(matcher_expected));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(MatcherCast, SharedMatcherLifetimeAndState)
{
    int live = 0;
    int copies = 0;
    Matcher<int> retained;
    Matcher<short> converted;
    {
        const StatefulMatcher source(&live, &copies);
        retained = Matcher<int>(source);
        IUTEST_EXPECT_EQ(2, live);
#if !defined(IUTEST_NO_SFINAE)
        IUTEST_EXPECT_EQ(1, copies);
#endif
        IUTEST_EXPECT_TRUE(retained.Matches(1));
        {
            const Matcher<int> copy(retained);
            converted = MatcherCast<short>(copy);
            IUTEST_EXPECT_EQ(2, live);
            IUTEST_EXPECT_TRUE(copy.Matches(2));
        }
        IUTEST_EXPECT_TRUE(converted.Matches(3));
    }
    IUTEST_EXPECT_EQ(1, live);
    Matcher<int>& alias = retained;
    retained = alias;
    IUTEST_EXPECT_TRUE(retained.Matches(4));
    retained = Matcher<int>();
    IUTEST_EXPECT_EQ(1, live);
    IUTEST_EXPECT_TRUE(converted.Matches(5));
    converted = Matcher<short>();
    IUTEST_EXPECT_EQ(0, live);
}

IUTEST(MatcherCast, ReassignmentReleasesPreviousOwnership)
{
    int live = 0;
    int copies = 0;
    {
        const StatefulMatcher first_source(&live, &copies);
        const StatefulMatcher second_source(&live, &copies);
        Matcher<int> first(first_source);
        Matcher<int> second(second_source);
        IUTEST_EXPECT_EQ(4, live);
        first = second;
        IUTEST_EXPECT_EQ(3, live);
        IUTEST_EXPECT_TRUE(first.Matches(1));
        IUTEST_EXPECT_TRUE(second.Matches(2));
        second = Matcher<int>();
        IUTEST_EXPECT_EQ(3, live);
        first = Matcher<int>();
        IUTEST_EXPECT_EQ(2, live);
    }
    IUTEST_EXPECT_EQ(0, live);
}

IUTEST(MatcherCast, ValueArgumentsAreCopiedOnlyOnce)
{
    int copies = 0;
    const CopyTrackedValue value(&copies);
    const Matcher<CopyTrackedValue> by_value = MatcherCast<CopyTrackedValue>(::iutest::matchers::Ref(value));
    const Matcher<const CopyTrackedValue&> by_reference =
        MatcherCast<const CopyTrackedValue&>(::iutest::matchers::Ref(value));

    copies = 0;
    IUTEST_EXPECT_FALSE(by_value.Matches(value));
    IUTEST_EXPECT_EQ(1, copies);
    copies = 0;
    ::std::ostringstream explanation;
    IUTEST_EXPECT_FALSE(by_value.MatchAndExplain(value, &explanation));
    IUTEST_EXPECT_EQ(1, copies);
    copies = 0;
    IUTEST_EXPECT_FALSE(static_cast<bool>(by_value(value)));
    IUTEST_EXPECT_EQ(1, copies);
    copies = 0;
    IUTEST_EXPECT_TRUE(by_reference.Matches(value));
    IUTEST_EXPECT_EQ(0, copies);

    int number = matcher_expected;
    const Matcher<int&> reference = MatcherCast<int&>(::iutest::matchers::Ref(number));
    const Matcher<int> cast_value = MatcherCast<int>(reference);
    IUTEST_EXPECT_FALSE(cast_value.Matches(number));
}

IUTEST(MatcherCast, DirectConstructionPreservesDecay)
{
    const Matcher<int> integer = IntegralConstant::value;
    IUTEST_EXPECT_TRUE(integer.Matches(matcher_expected));

    char text[] = "hello";
    const Matcher<char*> pointer(text);
    IUTEST_EXPECT_TRUE(pointer.Matches(text));
    Matcher< ::std::string> string_matcher = "hello";
    IUTEST_EXPECT_TRUE(string_matcher.Matches("hello"));
    string_matcher = ::std::string("world");
    IUTEST_EXPECT_TRUE(string_matcher.Matches("world"));

    typedef int (*FunctionPointer)(int);
    const Matcher<FunctionPointer> function(IdentityFunction);
    IUTEST_EXPECT_TRUE(function.Matches(&IdentityFunction));

    volatile VolatileValue volatile_value(matcher_expected);
    const volatile VolatileValue const_volatile_value(matcher_expected);
    const Matcher<int> from_volatile(volatile_value);
    const Matcher<int> from_const_volatile(const_volatile_value);
    IUTEST_EXPECT_TRUE(from_volatile.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(from_const_volatile.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(MatcherCast<int>(volatile_value).Matches(matcher_expected));

    volatile VolatileMatcher volatile_matcher(matcher_expected);
    const volatile VolatileMatcher const_volatile_matcher(matcher_expected);
    const Matcher<int> matcher_from_volatile(volatile_matcher);
    const Matcher<int> matcher_from_const_volatile(const_volatile_matcher);
    IUTEST_EXPECT_TRUE(matcher_from_volatile.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(matcher_from_const_volatile.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(MatcherCast<int>(volatile_matcher).Matches(matcher_expected));
}

IUTEST(MatcherCast, ValueConversionsUseCopy)
{
    MutableConversion value;
    const Matcher<int> direct(value);
    IUTEST_EXPECT_EQ(0, value.conversions);
    IUTEST_EXPECT_TRUE(direct.Matches(1));
    const Matcher<int> cast = MatcherCast<int>(value);
    IUTEST_EXPECT_EQ(0, value.conversions);
    IUTEST_EXPECT_TRUE(cast.Matches(1));
}

#if !IUTEST_HAS_CXX20  // Volatile value parameters are deprecated in C++20.
IUTEST(MatcherCast, VolatileInputType)
{
    const Matcher<volatile int> matcher(matcher_expected);
    IUTEST_EXPECT_TRUE(matcher.Matches(matcher_expected));
    const Matcher<const volatile int> const_matcher(matcher_expected);
    IUTEST_EXPECT_TRUE(const_matcher.Matches(matcher_expected));

    int number = matcher_expected;
    typedef int* volatile VolatilePointer;
    const Matcher<VolatilePointer> pointer(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(pointer.Matches(&number));
}
#endif

IUTEST(MatcherCast, ArrayAndFunctionInputTypes)
{
    typedef int Array[2];
    int value[2] = { 1, 2 };
    const Matcher<Array> any_array(::iutest::matchers::_);
    ::std::ostringstream explanation;
    IUTEST_EXPECT_TRUE(any_array.Matches(value));
    IUTEST_EXPECT_TRUE(any_array.MatchAndExplain(value, &explanation));
    IUTEST_EXPECT_TRUE(static_cast<bool>(any_array(value)));

#if !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4)
    // GCC 3 rejects unspecified-bound arrays in matcher parameters.
    typedef int UnboundedArray[];
    const Matcher<UnboundedArray> unbounded(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(unbounded.Matches(value));
#endif

    typedef const int ConstArray[2];
    const int const_value[2] = { 1, 2 };
    const Matcher<ConstArray> const_array(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(const_array.Matches(const_value));

    typedef int Matrix[2][2];
    int matrix_value[2][2] = { { 1, 2 }, { 3, 4 } };
    const Matcher<Matrix> matrix(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(matrix.Matches(matrix_value));

    const Matcher<Array&> array_reference(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(array_reference.Matches(value));

    typedef int Function(int);
    const Matcher<Function> any_function(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(any_function.Matches(&IdentityFunction));
    IUTEST_EXPECT_TRUE(any_function.MatchAndExplain(&IdentityFunction, &explanation));
    IUTEST_EXPECT_TRUE(static_cast<bool>(any_function(&IdentityFunction)));
    const Matcher<Function&> function_reference(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(function_reference.Matches(IdentityFunction));

    int number = matcher_expected;
    typedef int* const ConstPointer;
    const Matcher<ConstPointer> const_pointer(::iutest::matchers::_);
    IUTEST_EXPECT_TRUE(const_pointer.Matches(&number));

#if IUTEST_HAS_CXX11 && IUTEST_HAS_CXX_HDR_TYPE_TARITS
    const Matcher<Array> array(value);
    IUTEST_EXPECT_TRUE(array.Matches(value));
    const Matcher<Function> function(IdentityFunction);
    IUTEST_EXPECT_TRUE(function.Matches(&IdentityFunction));
#endif
}
#endif

IUTEST(MatcherCast, SafeValuesAndPolymorphicMatchers)
{
    IUTEST_EXPECT_TRUE(SafeMatcherCast<int>(matcher_expected).Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<int>(::iutest::matchers::Eq(matcher_expected)).Matches(matcher_expected));
    const Matcher<double> wide = MatcherCast<double>(1.5);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<float>(wide).Matches(1.5f));
    const Matcher<int> integer = MatcherCast<int>(1);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<bool>(integer).Matches(true));
    IUTEST_EXPECT_FALSE(SafeMatcherCast<bool>(wide).Matches(false));
    const Matcher<unsigned int> unsigned_integer = MatcherCast<unsigned int>(1U);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<unsigned char>(unsigned_integer).Matches(1));
}

IUTEST(MatcherCast, ReferencesAndNonCopyable)
{
    NonCopyable object;
    const Matcher<const NonCopyable&> original =
        MatcherCast<const NonCopyable&>(::iutest::matchers::Ref(object));
    const Matcher<NonCopyable&> converted = SafeMatcherCast<NonCopyable&>(original);
    IUTEST_EXPECT_TRUE(converted.Matches(object));
    NonCopyable other;
    IUTEST_EXPECT_FALSE(converted.Matches(other));
    const Matcher<const int&> reference = MatcherCast<const int&>(::iutest::matchers::Ref(matcher_expected));
    const Matcher<const int&> same = SafeMatcherCast<const int&>(reference);
    IUTEST_EXPECT_TRUE(same.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<const int&>(MatcherCast<int>(matcher_expected)).Matches(matcher_expected));
}

IUTEST(MatcherCast, PointerAndReferenceUpcasts)
{
    Derived object;
    const Matcher<Base*> pointer = MatcherCast<Base*>(::iutest::matchers::NotNull());
    IUTEST_EXPECT_TRUE(SafeMatcherCast<Derived*>(pointer).Matches(&object));
    IUTEST_EXPECT_FALSE(SafeMatcherCast<Derived*>(pointer).Matches(NULL));
    const Matcher<const Base&> reference = MatcherCast<const Base&>(::iutest::matchers::Ref(object));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<const Derived&>(reference).Matches(object));
}

IUTEST(MatcherCast, Descriptions)
{
    const Matcher<int> matcher = MatcherCast<int>(::iutest::matchers::Eq(matcher_expected));
    ::std::ostringstream original;
    ::std::ostringstream converted;
    matcher.DescribeTo(&original);
    SafeMatcherCast<short>(matcher).DescribeTo(&converted);
    IUTEST_EXPECT_EQ(original.str(), converted.str());
    original.str("");
    converted.str("");
    matcher.DescribeNegationTo(&original);
    SafeMatcherCast<short>(matcher).DescribeNegationTo(&converted);
    IUTEST_EXPECT_EQ(original.str(), converted.str());
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(0, MatcherCast<int>(matcher_expected)), "42");
}

#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)

namespace {

#if defined(IUTEST_USE_GTEST)
typedef ::testing::MatchResultListener Explanation;
#else
typedef ::std::ostream Explanation;
#endif

struct IsEven
{
    bool MatchAndExplain(int value, Explanation* os) const
    {
        *os << "remainder " << value % 2;
        return value % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

Matcher<int> MakeIsEvenMatcher()
{
#if defined(IUTEST_USE_GTEST)
    return MatcherCast<int>(::testing::MakePolymorphicMatcher(IsEven()));
#else
    return MatcherCast<int>(IsEven());
#endif
}

}   // end of namespace

IUTEST(MatcherCast, Explanation)
{
    const Matcher<int> matcher = MakeIsEvenMatcher();
#if defined(IUTEST_USE_GTEST)
    ::testing::StringMatchResultListener listener;
#else
    ::std::ostringstream listener;
#endif
    IUTEST_EXPECT_FALSE(SafeMatcherCast<short>(matcher).MatchAndExplain(3, &listener));
    IUTEST_EXPECT_EQ("remainder 1", listener.str());
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(3, MakeIsEvenMatcher()), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(4, ::iutest::matchers::Not(MakeIsEvenMatcher())), "is odd");
}

#endif
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
