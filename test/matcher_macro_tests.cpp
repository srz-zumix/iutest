//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_macro_tests.cpp
 * @brief       Matcher definition macro tests
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

#if IUTEST_HAS_MATCHER_MACROS

namespace {

IUTEST_MATCHER(IsEven, "")
{
    const arg_type remainder = arg % 2;
    if( result_listener->IsInterested() )
    {
        *result_listener << "remainder ";
        *result_listener->stream() << remainder;
    }
    return remainder == 0;
}

IUTEST_MATCHER(IsPositive, negation ? "is not positive" : "is positive")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg > 0;
}

IUTEST_MATCHER_P(IsDivisibleBy, n, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    const n_type divisor = n;
    return arg % divisor == 0;
}

IUTEST_MATCHER_P(HasValue, value, ::std::string(negation ? "does not equal " : "equals ") + ::iutest::PrintToString(value))
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == value;
}

IUTEST_MATCHER_P2(IsBetween, low, high, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    const low_type lower = low;
    const high_type upper = high;
    return lower <= arg && arg <= upper;
}

IUTEST_MATCHER_P3(HasSum, a, b, c, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c;
}
IUTEST_MATCHER_P4(HasSum, a, b, c, d, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d;
}
IUTEST_MATCHER_P5(HasSum, a, b, c, d, e, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e;
}
IUTEST_MATCHER_P6(HasSum, a, b, c, d, e, f, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e + f;
}
IUTEST_MATCHER_P7(HasSum, a, b, c, d, e, f, g, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e + f + g;
}
IUTEST_MATCHER_P8(HasSum, a, b, c, d, e, f, g, h, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e + f + g + h;
}
IUTEST_MATCHER_P9(HasSum, a, b, c, d, e, f, g, h, i, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e + f + g + h + i;
}
IUTEST_MATCHER_P10(HasSum, a, b, c, d, e, f, g, h, i, j, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b + c + d + e + f + g + h + i + j;
}

MATCHER(IsZero, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == 0;
}
MATCHER_P(IsEqualTo, value, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == value;
}
MATCHER_P2(IsSumOf, a, b, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == a + b;
}

IUTEST_MATCHER(Is_HTTP2_ready, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg;
}

IUTEST_MATCHER_P(IsExplainedBy, inner, "")
{
#if defined(IUTEST_USE_GTEST)
    return ::testing::ExplainMatchResult(inner, arg, result_listener);
#else
    return ::iutest::matchers::ExplainMatchResult(inner, arg, result_listener);
#endif
}

IUTEST_MATCHER_P(EqualsStreamParameter, os, "")
{
    IUTEST_UNUSED_VAR(result_listener);
    return arg == os;
}

#if !defined(IUTEST_USE_GTEST)
struct CopyTrackedParameter
{
    int* copies;
    int* moves;
    explicit CopyTrackedParameter(int* count, int* move_count = NULL) : copies(count), moves(move_count) {}
    CopyTrackedParameter(const CopyTrackedParameter& other) : copies(other.copies), moves(other.moves) { ++*copies; }
#if IUTEST_HAS_RVALUE_REFS
    CopyTrackedParameter(CopyTrackedParameter&& other) IUTEST_CXX_NOEXCEPT_SPEC : copies(other.copies), moves(other.moves)
    {
        if( moves != NULL ) ++*moves;
    }
#endif
};

struct CopyOnlyLegacyParameter
{
    int value;
    explicit CopyOnlyLegacyParameter(int n) : value(n) {}
    CopyOnlyLegacyParameter(const CopyOnlyLegacyParameter& other) : value(other.value) {}
};

struct VolatileCopyParameter
{
    int value;
    explicit VolatileCopyParameter(int n) : value(n) {}
    VolatileCopyParameter(const volatile VolatileCopyParameter& other) : value(other.value) {}
};

#if !IIUT_HAS_MATCHER_PARAMETER_MOVE_
struct NonConstCopyParameter
{
    int value;
    explicit NonConstCopyParameter(int n) : value(n) {}
    NonConstCopyParameter(NonConstCopyParameter& other) : value(other.value) {}
};
#endif

int MatcherFunction(int value) { return value; }

#if IUTEST_HAS_RVALUE_REFS && IUTEST_HAS_DELETED_FUNCTIONS
struct CopyOnlyParameter
{
    int value;
    int* copies;
    CopyOnlyParameter(int n, int* count) : value(n), copies(count) {}
    CopyOnlyParameter(const CopyOnlyParameter& other) : value(other.value), copies(other.copies) { ++*copies; }
    CopyOnlyParameter(CopyOnlyParameter&&) = delete;
};
#endif
#endif

} // namespace

IUTEST(MatcherMacro, Match)
{
    IUTEST_EXPECT_THAT(4, IsEven());
    IUTEST_EXPECT_THAT(2L, IsEven());
    IUTEST_EXPECT_THAT(10, IsDivisibleBy(5));
    IUTEST_EXPECT_THAT(2, IsBetween(1, 3L));
    IUTEST_EXPECT_THAT(6, HasSum(1, 2, 3));
    IUTEST_EXPECT_THAT(10, HasSum(1, 2, 3, 4));
    IUTEST_EXPECT_THAT(15, HasSum(1, 2, 3, 4, 5));
    IUTEST_EXPECT_THAT(21, HasSum(1, 2, 3, 4, 5, 6));
    IUTEST_EXPECT_THAT(28, HasSum(1, 2, 3, 4, 5, 6, 7));
    IUTEST_EXPECT_THAT(36, HasSum(1, 2, 3, 4, 5, 6, 7, 8));
    IUTEST_EXPECT_THAT(45, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9));
    IUTEST_EXPECT_THAT(55, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    IUTEST_EXPECT_THAT(0, IsZero());
    IUTEST_EXPECT_THAT(1, IsEqualTo(1));
    IUTEST_EXPECT_THAT(3, IsSumOf(1, 2));
    IUTEST_EXPECT_THAT(::std::string("abc"), HasValue(::std::string("abc")));
    IUTEST_EXPECT_THAT(2, IsExplainedBy(IsEven()));
    IUTEST_EXPECT_THAT(3, EqualsStreamParameter(3));
}

IUTEST(MatcherMacro, FailureDescriptions)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "is even");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(-1, IsPositive()), "is positive");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, IsDivisibleBy(3)), "is divisible by (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, IsDivisibleBy(3)), "3)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, IsBetween(1, 3)), "is between (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(1, HasValue(2)), "equals 2");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(0, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
        "10)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(false, Is_HTTP2_ready()), "is h t t p 2 ready");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsExplainedBy(IsEven())), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(2, EqualsStreamParameter(3)), "3)");
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(4, IsBetween(1, 3)), "is between (low: 1, high: 3)");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(0, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
        "has sum (a: 1, b: 2, c: 3, d: 4, e: 5, f: 6, g: 7, h: 8, i: 9, j: 10)");
#endif
}

IUTEST(MatcherMacro, CompositionAndNegation)
{
    using ::iutest::matchers::Not;
    IUTEST_EXPECT_THAT(3, Not(IsEven()));
#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
    IUTEST_EXPECT_THAT(2, ::iutest::matchers::AllOf(IsEven(), IsPositive()));
    IUTEST_EXPECT_THAT(5, ::iutest::matchers::AnyOf(IsEven(), IsPositive()));
#endif
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, Not(IsEven())), "not (is even)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(1, Not(IsPositive())), "is not positive");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, Not(IsDivisibleBy(5))), "not (is divisible by (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, Not(IsDivisibleBy(5))), "5))");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(2, Not(HasValue(2))), "does not equal 2");
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(MatcherMacro, ExactDescriptions)
{
    IUTEST_EXPECT_EQ("is even", IsEven().WhichIs());
    IUTEST_EXPECT_EQ("is between (low: 1, high: 3)", IsBetween(1, 3).WhichIs());

    ::std::ostringstream description;
    IsEven().DescribeNegationTo(&description);
    IUTEST_EXPECT_EQ("not (is even)", description.str());
    description.str("");
    IsBetween(1, 3).DescribeNegationTo(&description);
    IUTEST_EXPECT_EQ("not (is between (low: 1, high: 3))", description.str());
}

IUTEST(MatcherMacro, ParameterValueAndReferenceSemantics)
{
    ::std::string source("original");
    const HasValueMatcherP1< ::std::string> owned = HasValue(source);
    const HasValueMatcherP1< ::std::string&> referenced = HasValue< ::std::string&>(source);
    const HasValueMatcherP1<const ::std::string&> const_referenced = HasValue<const ::std::string&>(source);
    source = "changed";
    IUTEST_EXPECT_THAT(::std::string("original"), owned);
    IUTEST_EXPECT_THAT(source, referenced);
    IUTEST_EXPECT_THAT(source, const_referenced);

    ::std::string low("low");
    ::std::string high("high");
    const IsBetweenMatcherP2< ::std::string&, ::std::string> mixed =
        IsBetween< ::std::string&, ::std::string>(low, high);
    low = "changed low";
    high = "changed high";
    IUTEST_EXPECT_EQ("changed low", mixed.low);
    IUTEST_EXPECT_EQ("high", mixed.high);

    const HasValueMatcherP1< ::std::string> temporary = HasValue(::std::string("temporary"));
    IUTEST_EXPECT_THAT(::std::string("temporary"), temporary);

    const HasValueMatcherP1<const char*> literal = HasValue("literal");
    IUTEST_EXPECT_STREQ("literal", literal.value);
    char buffer[] = "buffer";
    const HasValueMatcherP1<char*> array = HasValue(buffer);
    IUTEST_EXPECT_EQ(buffer, array.value);
    const HasValueMatcherP1<char (&)[7]> array_reference = HasValue<char (&)[7]>(buffer);
    buffer[0] = 'B';
    IUTEST_EXPECT_EQ('B', array_reference.value[0]);

    typedef int (*Function)(int);
    const EqualsStreamParameterMatcherP1<Function> function = EqualsStreamParameter(MatcherFunction);
    IUTEST_EXPECT_THAT(&MatcherFunction, function);
    typedef int FunctionType(int);
    const EqualsStreamParameterMatcherP1<FunctionType&> function_reference =
        EqualsStreamParameter<FunctionType&>(MatcherFunction);
    IUTEST_EXPECT_THAT(&MatcherFunction, function_reference);
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    IUTEST_EXPECT_EQ("equals stream parameter (os: <function>)", function_reference.WhichIs());
#endif
}

IUTEST(MatcherMacro, MixedParameters)
{
    int first = 1;
    int second = 2;
    const HasSumMatcherP10<int&, const int&, int, long, int, int, int, int, int, int> matcher =
        HasSum<int&, const int&, int, long, int, int, int, int, int, int>(first, second, 3, 4L, 5, 6, 7, 8, 9, 10);
    IUTEST_EXPECT_TRUE(&first == &matcher.a);
    IUTEST_EXPECT_TRUE(&second == &matcher.b);
    first = 10;
    second = 20;
    IUTEST_EXPECT_THAT(82, matcher);
}

IUTEST(MatcherMacro, ParameterCopies)
{
    int copies = 0;
    CopyTrackedParameter source(&copies);
    const HasValueMatcherP1<CopyTrackedParameter> single = HasValue(source);
#if IUTEST_CPLUSPLUS >= 201703L
    IUTEST_EXPECT_EQ(IIUT_HAS_MATCHER_PARAMETER_MOVE_ ? 1 : 2, copies);
#endif
    IUTEST_EXPECT_EQ(&copies, single.value.copies);

    copies = 0;
    const IsBetweenMatcherP2<CopyTrackedParameter, CopyTrackedParameter> pair = IsBetween(source, source);
#if IUTEST_CPLUSPLUS >= 201703L
    IUTEST_EXPECT_EQ(IIUT_HAS_MATCHER_PARAMETER_MOVE_ ? 2 : 4, copies);
#endif
    IUTEST_EXPECT_EQ(&copies, pair.low.copies);
    IUTEST_EXPECT_EQ(&copies, pair.high.copies);

    copies = 0;
    const HasValueMatcherP1<CopyTrackedParameter> direct(source);
    IUTEST_EXPECT_EQ(IIUT_HAS_MATCHER_PARAMETER_MOVE_ ? 1 : 2, copies);
    IUTEST_EXPECT_EQ(&copies, direct.value.copies);

    copies = 0;
    const HasValueMatcherP1<CopyTrackedParameter> temporary = HasValue(CopyTrackedParameter(&copies));
#if IUTEST_CPLUSPLUS >= 201703L
    IUTEST_EXPECT_EQ(IIUT_HAS_MATCHER_PARAMETER_MOVE_ ? 0 : 1, copies);
#endif
    IUTEST_EXPECT_EQ(&copies, temporary.value.copies);
}

IUTEST(MatcherMacro, CopyOnlyLegacyParameter)
{
    const CopyOnlyLegacyParameter source(42);
    const HasValueMatcherP1<CopyOnlyLegacyParameter> matcher = HasValue(source);
    IUTEST_EXPECT_EQ(42, matcher.value.value);
}

IUTEST(MatcherMacro, FactorySignatureAndVolatileParameter)
{
    typedef HasValueMatcherP1< ::std::string> (*StringFactory)(::std::string);
    const StringFactory factory = &HasValue< ::std::string>;
    IUTEST_EXPECT_EQ("value", factory(::std::string("value")).value);

    volatile VolatileCopyParameter source(42);
    const HasValueMatcherP1<VolatileCopyParameter> matcher = HasValue(source);
    IUTEST_EXPECT_EQ(42, matcher.value.value);
}

#if !IIUT_HAS_MATCHER_PARAMETER_MOVE_
IUTEST(MatcherMacro, DirectNonConstCopyParameter)
{
    NonConstCopyParameter source(42);
    const HasValueMatcherP1<NonConstCopyParameter> matcher(source);
    IUTEST_EXPECT_EQ(42, matcher.value.value);
}
#endif

#if IUTEST_HAS_RVALUE_REFS && IUTEST_HAS_DELETED_FUNCTIONS
IUTEST(MatcherMacro, CopyOnlyParameter)
{
    int copies = 0;
    const CopyOnlyParameter source(42, &copies);
    const HasValueMatcherP1<CopyOnlyParameter> matcher = HasValue(source);
#if IUTEST_CPLUSPLUS >= 201703L
    IUTEST_EXPECT_EQ(2, copies);
#endif
    copies = 0;
    const HasValueMatcherP1<CopyOnlyParameter> direct(source);
    IUTEST_EXPECT_EQ(2, copies);
    IUTEST_EXPECT_EQ(42, matcher.value.value);
    IUTEST_EXPECT_EQ(42, direct.value.value);
}
#endif

#if IUTEST_HAS_CXX11 && IIUT_HAS_MATCHER_PARAMETER_MOVE_ && IUTEST_CPLUSPLUS >= 201703L
IUTEST(MatcherMacro, ParameterMoves)
{
    int copies = 0;
    int moves = 0;
    const CopyTrackedParameter source(&copies, &moves);
    const HasValueMatcherP1<CopyTrackedParameter> single = HasValue(source);
    IUTEST_EXPECT_EQ(1, copies);
    IUTEST_EXPECT_EQ(1, moves);
    IUTEST_EXPECT_EQ(&copies, single.value.copies);

    copies = 0;
    moves = 0;
    const HasValueMatcherP1<CopyTrackedParameter> direct(source);
    IUTEST_EXPECT_EQ(1, copies);
    IUTEST_EXPECT_EQ(1, moves);
    IUTEST_EXPECT_EQ(&copies, direct.value.copies);

    copies = 0;
    moves = 0;
    const IsBetweenMatcherP2<CopyTrackedParameter, CopyTrackedParameter> pair = IsBetween(source, source);
    IUTEST_EXPECT_EQ(2, copies);
    IUTEST_EXPECT_EQ(2, moves);
    IUTEST_EXPECT_EQ(&moves, pair.low.moves);
    IUTEST_EXPECT_EQ(&moves, pair.high.moves);

    copies = 0;
    moves = 0;
    const HasValueMatcherP1<CopyTrackedParameter> temporary = HasValue(CopyTrackedParameter(&copies, &moves));
    IUTEST_EXPECT_EQ(0, copies);
    IUTEST_EXPECT_EQ(1, moves);
    IUTEST_EXPECT_EQ(&moves, temporary.value.moves);
}

IUTEST(MatcherMacro, MoveOnlyParameter)
{
    const HasValueMatcherP1< ::std::unique_ptr<int> > matcher = HasValue(::std::unique_ptr<int>(new int(42)));
    IUTEST_EXPECT_EQ(42, *matcher.value);

#if IUTEST_HAS_DELETED_FUNCTIONS
    int copies = 0;
    const CopyOnlyParameter source(42, &copies);
    const IsBetweenMatcherP2<CopyOnlyParameter, ::std::unique_ptr<int> > mixed =
        IsBetween<CopyOnlyParameter, ::std::unique_ptr<int> >(source, ::std::unique_ptr<int>(new int(43)));
    IUTEST_EXPECT_EQ(2, copies);
    IUTEST_EXPECT_EQ(42, mixed.low.value);
    IUTEST_EXPECT_EQ(43, *mixed.high);
#endif
}
#endif

IUTEST(MatcherMacro, UninterestedListener)
{
    IUTEST_EXPECT_TRUE(IsEven().MatchAndExplain(4, NULL));
    IUTEST_EXPECT_FALSE(IsEven().MatchAndExplain(3, NULL));
    IUTEST_EXPECT_FALSE(IsExplainedBy(IsEven()).MatchAndExplain(3, NULL));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
