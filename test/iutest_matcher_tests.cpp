//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_matcher_tests.cpp
 * @brief		iutest matcher test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include <map>

#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

namespace {

::std::string Hoge = "Hoge";
::std::string hoge = "hoge";
::std::string hog = "hog";
::std::string oge = "oge";
::std::vector<int> va;
::std::vector<int> ve;
::std::vector< ::std::vector<int> > vv;
int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int b[3] = { 1, 2, 3 };
int c[3] = { 1, 1, 1 };
int n[2][2] = { {0,1}, {2,3} };
::std::map<int, int> m;
int* p1 = NULL;
int** p2 = &p1;
float f0 = 0.0f;
double d0 = 0.0;
struct X { int a, b; X(int _a, int _b) : a(_a), b(_b) {} int GetA() const { return a; } };
X x(1,1);
::std::map<int, X> mx;
int X2(int v) { return v*2; }

}

IUTEST(Matcher, Eq)
{
	IUTEST_EXPECT_THAT(1, Eq(1));
}

IUTEST(Matcher, Ne)
{
	IUTEST_EXPECT_THAT(0, Ne(1));
}

IUTEST(Matcher, Le)
{
	IUTEST_EXPECT_THAT(1, Le(1));
	IUTEST_EXPECT_THAT(0, Le(1));
}

IUTEST(Matcher, Lt)
{
	IUTEST_EXPECT_THAT(0, Lt(1));
}

IUTEST(Matcher, Ge)
{
	IUTEST_EXPECT_THAT(1, Ge(0));
	IUTEST_EXPECT_THAT(0, Ge(0));
}

IUTEST(Matcher, Gt)
{
	IUTEST_EXPECT_THAT(1, Gt(0));
}

IUTEST(Matcher, IsNull)
{
	IUTEST_EXPECT_THAT(p1, IsNull());
}

IUTEST(Matcher, NotNull)
{
	IUTEST_EXPECT_THAT(p2, NotNull());
}

IUTEST(Matcher, TypedEq)
{
	IUTEST_EXPECT_THAT(1, TypedEq<int>(1));
}

IUTEST(Matcher, FloatEq)
{
	IUTEST_EXPECT_THAT(f0, FloatEq(0.0f));
}

IUTEST(Matcher, DoubleEq)
{
	IUTEST_EXPECT_THAT(d0, DoubleEq(0.0));
}

IUTEST(Matcher, NanSensitiveFloatEq)
{
	IUTEST_EXPECT_THAT(f0, NanSensitiveFloatEq(0.0f));
	IUTEST_EXPECT_THAT(0.0f/f0, NanSensitiveFloatEq(0.0f/f0));
}

IUTEST(Matcher, NanSensitiveDoubleEq)
{
	IUTEST_EXPECT_THAT(d0, NanSensitiveDoubleEq(0.0));
	IUTEST_EXPECT_THAT(0.0/d0, NanSensitiveDoubleEq(0.0/d0));
}

IUTEST(Matcher, StrEq)
{
	IUTEST_EXPECT_THAT("hoge", StrEq("hoge"));
	IUTEST_EXPECT_THAT("hoge", StrEq(hoge));
	IUTEST_EXPECT_THAT(hoge, StrEq("hoge"));
	IUTEST_EXPECT_THAT(hoge, StrEq(hoge));
}

IUTEST(Matcher, StrNe)
{
	IUTEST_EXPECT_THAT("hoga", StrNe("hoge"));
	IUTEST_EXPECT_THAT("hoga", StrNe(hoge));
	IUTEST_EXPECT_THAT(hoge, StrNe("Hoge"));
	IUTEST_EXPECT_THAT(hoge, StrNe(Hoge));
}

IUTEST(Matcher, StrCaseEq)
{
	IUTEST_EXPECT_THAT("hoge", StrCaseEq("Hoge"));
	IUTEST_EXPECT_THAT("hoGe", StrCaseEq(hoge));
	IUTEST_EXPECT_THAT(hoge, StrCaseEq("hOge"));
	IUTEST_EXPECT_THAT(hoge, StrCaseEq(Hoge));
}

IUTEST(Matcher, StrCaseNe)
{
	IUTEST_EXPECT_THAT("hoga", StrCaseNe("hoge"));
	IUTEST_EXPECT_THAT("hoga", StrCaseNe(hoge));
	IUTEST_EXPECT_THAT(hoge, StrCaseNe("hoga"));
	IUTEST_EXPECT_THAT(hoge, StrCaseNe(hog));
}

IUTEST(Matcher, StartsWith)
{
	IUTEST_EXPECT_THAT("hoge", StartsWith("ho"));
	IUTEST_EXPECT_THAT("hoge", StartsWith(hog));
	IUTEST_EXPECT_THAT(hoge, StartsWith("ho"));
	IUTEST_EXPECT_THAT(hoge, StartsWith(hog));
}

IUTEST(Matcher, HasSubstr)
{
	IUTEST_EXPECT_THAT("hoge", HasSubstr("ho"));
	IUTEST_EXPECT_THAT("hoge", HasSubstr(oge));
	IUTEST_EXPECT_THAT(hoge, HasSubstr("ge"));
	IUTEST_EXPECT_THAT(hoge, HasSubstr(hog));
}

IUTEST(Matcher, EndsWith)
{
	IUTEST_EXPECT_THAT("hoge", EndsWith("ge"));
	IUTEST_EXPECT_THAT("hoge", EndsWith(oge));
	IUTEST_EXPECT_THAT(hoge, EndsWith("ge"));
	IUTEST_EXPECT_THAT(hoge, EndsWith(oge));
}

IUTEST(Matcher, Equals)
{
	IUTEST_EXPECT_THAT(0, Equals(0));
	IUTEST_EXPECT_THAT("hoge", Equals("hoge"));
	IUTEST_EXPECT_THAT("hoge", Equals(hoge));
	IUTEST_EXPECT_THAT(hoge, Equals("hoge"));
	IUTEST_EXPECT_THAT(hoge, Equals(hoge));
}

IUTEST(Matcher, Contains)
{
	IUTEST_EXPECT_THAT(va, Contains(1));
	IUTEST_EXPECT_THAT( b, Contains(1));
	IUTEST_EXPECT_THAT(va, Contains(Lt(4)));
	IUTEST_EXPECT_THAT(vv, Contains(Contains(Lt(4))));
}

IUTEST(Matcher, Each)
{
	IUTEST_EXPECT_THAT( c, Each(1));
	IUTEST_EXPECT_THAT(va, Each(Le(10)));
	IUTEST_EXPECT_THAT(vv, Each(Each(Le(10))));
}

IUTEST(Matcher, ContainerEq)
{
	IUTEST_EXPECT_THAT( a, ContainerEq( a));
	IUTEST_EXPECT_THAT(va, ContainerEq(va));
#if !defined(IUTEST_USE_GTEST)
	IUTEST_EXPECT_THAT( a, ContainerEq(va));
	IUTEST_EXPECT_THAT(va, ContainerEq( a));
#endif
}

IUTEST(Matcher, Pointwise)
{
	IUTEST_EXPECT_THAT(n[0], Pointwise(Ne(), n[1]));
	IUTEST_EXPECT_THAT(n[0], Pointwise(Lt(), n[1]));
	IUTEST_EXPECT_THAT(n[0], Pointwise(Le(), n[1]));
	IUTEST_EXPECT_THAT(n[1], Pointwise(Gt(), n[0]));
	IUTEST_EXPECT_THAT( b, Pointwise(Ge(), c));
	IUTEST_EXPECT_THAT(va, Pointwise(Eq(),va));
	IUTEST_EXPECT_THAT( a, Pointwise(Eq(),va));
	IUTEST_EXPECT_THAT(va, Pointwise(Eq(), a));
}


#if !defined(IUTEST_USE_GMOCK) || (defined(GMOCK_VER) && GMOCK_VER >= 0x01070000)
IUTEST(Matcher, IsEmpty)
{
	IUTEST_ASSERT_THAT(ve, IsEmpty());
}

IUTEST(Matcher, SizeIs)
{
	IUTEST_ASSERT_THAT(ve, SizeIs(0));
	IUTEST_ASSERT_THAT(va, SizeIs(Ge(10)));
#if !defined(IUTEST_USE_GMOCK)
	IUTEST_ASSERT_THAT( c, SizeIs(3));
#endif
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(Matcher, At)
{
	IUTEST_EXPECT_THAT( b, At(1, 2));
	IUTEST_EXPECT_THAT(va, At(1, Gt(0)));
}
#endif

IUTEST(Matcher, Key)
{
	IUTEST_EXPECT_THAT( m, Each(Key(Le(10))));
}

IUTEST(Matcher, Pair)
{
	IUTEST_EXPECT_THAT( m, Each(Pair(Le(10), 100)));
}

IUTEST(Matcher, Field)
{
	IUTEST_EXPECT_THAT( x, Field(&X::a, 1));
	IUTEST_EXPECT_THAT(&x, Field(&X::a, 1));
	IUTEST_EXPECT_THAT(mx, Each(Pair(Le(10), Field(&X::b, Ge(0)))));
}

IUTEST(Matcher, Propetry)
{
	IUTEST_EXPECT_THAT( x, Property(&X::GetA, 1));
	IUTEST_EXPECT_THAT(&x, Property(&X::GetA, 1));
	IUTEST_EXPECT_THAT(mx, Each(Pair(Le(10), Property(&X::GetA, Ge(0)))));
}

IUTEST(Matcher, ResultOf)
{
	IUTEST_EXPECT_THAT(1, ResultOf(X2, 2));
	IUTEST_EXPECT_THAT(1, ResultOf(X2, Gt(1)));
}

IUTEST(Matcher, Pointee)
{
#if !defined(IUTEST_USE_GMOCK)
	IUTEST_EXPECT_THAT(a, Pointee(0));
	IUTEST_EXPECT_THAT(a, Pointee(Ge(0)));
#endif
	IUTEST_EXPECT_THAT(p2, Pointee(IsNull()));
}

IUTEST(Matcher, _)
{
	IUTEST_EXPECT_THAT(42, _);
	IUTEST_EXPECT_THAT( x, _);
	IUTEST_EXPECT_THAT(&x, _);
}

IUTEST(Matcher, Not)
{
	IUTEST_EXPECT_THAT(42, Not(1));
	IUTEST_EXPECT_THAT(42, Not(Ne(42)));
}

IUTEST(Matcher, A)
{
	IUTEST_EXPECT_THAT(42, A<int>());
	IUTEST_EXPECT_THAT( x, A<X>());
	IUTEST_EXPECT_THAT(&x, A<X*>());
}

IUTEST(Matcher, ElementsAreArray)
{
	IUTEST_EXPECT_THAT( a, ElementsAreArray(va));
	IUTEST_EXPECT_THAT(va, ElementsAreArray(a));
	IUTEST_EXPECT_THAT(va, ElementsAreArray(va));
	IUTEST_EXPECT_THAT( c, ElementsAreArray(c));
#if !defined(IUTEST_USE_GMOCK)
	IUTEST_EXPECT_THAT( c, ElementsAreArray(b, 1));
#endif
#if IUTEST_HAS_INITIALIZER_LIST
	IUTEST_EXPECT_THAT( c, ElementsAreArray({1, 1, 1}));
#endif
}

#if !defined(IUTEST_USE_GMOCK)
#  define CHECK_FAILURE(x, str)	IUTEST_EXPECT_FATAL_FAILURE( x, str )
#else
#  define CHECK_FAILURE(x, str)	IUTEST_EXPECT_FATAL_FAILURE( x, "" )
#endif

IUTEST(MatcherFailure, Eq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Eq(0)), "Eq: 0" );
}

IUTEST(MatcherFailure, Ne)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Ne(0)), "Ne: 0" );
}

IUTEST(MatcherFailure, Le)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Le(0)), "Le: 0" );
}

IUTEST(MatcherFailure, Lt)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Lt(0)), "Lt: 0" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Lt(0)), "Lt: 0" );
}

IUTEST(MatcherFailure, Ge)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Ge(1)), "Ge: 1" );
}

IUTEST(MatcherFailure, Gt)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Gt(1)), "Gt: 1" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Gt(1)), "Gt: 1" );
}

IUTEST(MatcherFailure, IsNull)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(p2, IsNull()), "Is Null");
}

IUTEST(MatcherFailure, NotNull)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(p1, NotNull()), "Not Null");
}

IUTEST(MatcherFailure, TypedEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, TypedEq<int>(0)), "Eq: 0" );
}

IUTEST(MatcherFailure, FloatEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, FloatEq(1.0f)), "Eq: " );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0/f0, FloatEq(0/f0)), "Eq: " );
}

IUTEST(MatcherFailure, DoubleEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, DoubleEq(1.0)), "Eq: " );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0/d0, DoubleEq(0/d0)), "Eq: " );
}

IUTEST(MatcherFailure, NanSensitiveFloatEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatEq(1.0f)), "Eq: " );
}

IUTEST(MatcherFailure, NanSensitiveDoubleEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveDoubleEq(1.0)), "Eq: " );
}

IUTEST(MatcherFailure, StrEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StrEq("Hoge")), "StrEq: Hoge");
}

IUTEST(MatcherFailure, StrNe)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StrNe("hoge")), "StrNe: hoge");
}

IUTEST(MatcherFailure, StrCaseEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseEq("hoga")), "StrCaseEq: hoga");
}

IUTEST(MatcherFailure, StrCaseNe)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseNe("hoge")), "StrCaseNe: hoge");
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseNe("hoGe")), "StrCaseNe: hoGe");
}

IUTEST(MatcherFailure, StartsWith)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StartsWith("Ho")) , "StartsWith: Ho" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", StartsWith("oge")), "StartsWith: oge" );
}

IUTEST(MatcherFailure, HasSubstr)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", HasSubstr("Ho")), "HasSubstr: Ho" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", HasSubstr("oe")), "HasSubstr: oe" );
}

IUTEST(MatcherFailure, EndsWith)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", EndsWith("Ge")) , "EndsWith: Ge" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", EndsWith("gee")), "EndsWith: gee" );
}

IUTEST(MatcherFailure, Equals)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", Equals("Hoge")) , "Eq: Hoge" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Equals(1)), "Eq: 1" );
}

IUTEST(MatcherFailure, Contains)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Contains(42)), "Contains: 42" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, Contains(42)), "Contains: 42" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Contains(Lt(0))), "Contains: Lt: 0" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(vv, Contains(Contains(Lt(0)))), "Contains: Contains: Lt: 0" );
}

IUTEST(MatcherFailure, Each)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Each(42)), "Each: 42" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, Each(42)), "Each: 42" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Each(Ne(9))), "Each: Ne: 9" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(vv, Each(Each(Gt(5)))), "Each: Each: Gt: 5" );
}

IUTEST(MatcherFailure, ContainerEq)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, ContainerEq(c)), "ContainerEq: {1, 1, 1}" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, ContainerEq(c)), "Mismatch in a position 1: 1 vs 2" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, ContainerEq(c)), "Mismatch in a position 2: 1 vs 3" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( a, ContainerEq(c)), "Mismatch element : 3 vs 10" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( c, ContainerEq(a)), "Mismatch element : 10 vs 3" );
}

IUTEST(MatcherFailure, Pointwise)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, Pointwise(Eq(), c)), "Pointwise: Eq: {1, 1, 1}" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( a, Pointwise(Eq(), c)), "Mismatch element : 3 vs 10" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( c, Pointwise(Eq(), a)), "Mismatch element : 10 vs 3" );
}

#if !defined(IUTEST_USE_GMOCK) || (defined(GMOCK_VER) && GMOCK_VER >= 0x01070000)
IUTEST(MatcherFailure, IsEmpty)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, IsEmpty()), "Is Empty" );
}

IUTEST(MatcherFailure, SizeIs)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, SizeIs(0)), "Size is: 0" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, SizeIs(Lt(0))), "Size is: Lt: 0" );
#if !defined(IUTEST_USE_GMOCK)
	CHECK_FAILURE( IUTEST_ASSERT_THAT( c, SizeIs(Lt(0))), "Size is: Lt: 0" );
#endif
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(MatcherFailure, At)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( b, At(2, 2)), "At 2: 2" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va, At(1, Gt(1))), "At 1: Gt: 1" );
}
#endif

IUTEST(MatcherFailure, Key)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( m, Each(Key(0))), "Each: Key: 0" );
}

IUTEST(MatcherFailure, Pair)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( m, Each(Pair(Gt(5), 100))), "Each: Pair: (Gt: 5, 100)" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( m, Each(Pair(_, Ne(100)))), "Each: Pair: (_, Ne: 100)" );
}

IUTEST(MatcherFailure, Field)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( x, Field(&X::a, 100)), "Field: 100" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( x, Field(&X::a, Ne(1))), "Field: Ne: 1" );
}

IUTEST(MatcherFailure, Property)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( x, Property(&X::GetA, 100)), "Property: 100" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( x, Property(&X::GetA, Ne(1))), "Property: Ne: 1" );
}

IUTEST(MatcherFailure, ResultOf)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, 1)), "Result of: 1" );
	CHECK_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, Le(1))), "Result of: Le: 1" );
}

IUTEST(MatcherFailure, Pointee)
{
#if !defined(IUTEST_USE_GMOCK)
	CHECK_FAILURE( IUTEST_ASSERT_THAT(a, Pointee(1)), "Points To: 1");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(a, Pointee(Gt(0))), "Points To: Gt: 0");
#endif
	CHECK_FAILURE( IUTEST_ASSERT_THAT(p2, Pointee(NotNull())), "Points To: Not Null");
}

IUTEST(MatcherFailure, Not)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Not(1)), "Not: (1)");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(1, Not(Eq(1))), "Not: (Eq: 1)");
}

IUTEST(MatcherFailure, ElementsAreArray)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT(b, ElementsAreArray(c)), "ElementsAreArray: " );
	CHECK_FAILURE( IUTEST_ASSERT_THAT(b, ElementsAreArray(a))
		, "ElementsAreArray: argument[3] is less than 10");
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE

IUTEST(Matcher, ElementsAre)
{
	IUTEST_EXPECT_THAT("hoge", ElementsAre('h', 'o', 'g', 'e', '\0'));
#if !defined(IUTEST_USE_GMOCK)
	IUTEST_EXPECT_THAT(va, ElementsAre(Ge(0), Gt(0)));
#endif
}

IUTEST(MatcherFailure, ElementsAre)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ElementsAre( 'h', 'o', 'G', 'e', '\0')), "ElementsAre(2): G");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va
		, ElementsAre(Ge(0), Gt(0), Lt(1))), "ElementsAre(2): Lt: 1");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(n, Each(
		ElementsAre(Lt(3), Lt(3)))), "Each: ElementsAre: {Lt: 3, Lt: 3}");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(c
		, ElementsAre( Ge(0), Gt(0), Ne(0), Eq(0) ) ), "ElementsAre: argument[3] is less than 4");
}

#endif

#if IUTEST_HAS_MATCHER_REGEX

IUTEST(Matcher, MatchesRegex)
{
	::std::string s = "greeeeeen";
	IUTEST_EXPECT_THAT(s, MatchesRegex("gre+n"));
	IUTEST_EXPECT_THAT("hogeeeeeet", MatchesRegex("hoge+t"));
}

IUTEST(Matcher, ContainsRegex)
{
	::std::string s = "greeeeeen";
	IUTEST_EXPECT_THAT(s, MatchesRegex("e"));
	IUTEST_EXPECT_THAT("hogeeeeeet", ContainsRegex("hoge+"));
}

IUTEST(MatcherFailure, MatchesRegex)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hogeeeeeet", MatchesRegex("hoge+"))
		, "MatchesRegex: hoge+");
}

IUTEST(MatcherFailure, ContainsRegex)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", MatchesRegex("hoge+"))
		, "ContainsRegex: hoge+");
}

#endif


#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

IUTEST(Matcher, AllOf)
{
	IUTEST_EXPECT_THAT("hoge", AllOf( StartsWith("ho"), EndsWith("ge")));
	IUTEST_EXPECT_THAT("9347812650", AllOf(
		  HasSubstr("0")
		, HasSubstr("1")
		, HasSubstr("2")
		, HasSubstr("3")
		, HasSubstr("4")
		, HasSubstr("5")
		, HasSubstr("6")
		, HasSubstr("7")
		, HasSubstr("8")
	));
	IUTEST_EXPECT_THAT(va, Each(AllOf( Ge(0), Le(10) )));
}

IUTEST(Matcher, AnyOf)
{
	IUTEST_EXPECT_THAT("hoge", AnyOf( StartsWith("ho"), EndsWith("ge")));
	IUTEST_EXPECT_THAT("hoge", AnyOf( StartsWith("ho"), EndsWith("Ge")));
	IUTEST_EXPECT_THAT("hoge", AnyOf( StartsWith("Ho"), EndsWith("ge")));
	IUTEST_EXPECT_THAT("hoge7", AnyOf(
		  HasSubstr("0")
		, HasSubstr("1")
		, HasSubstr("2")
		, HasSubstr("3")
		, HasSubstr("4")
		, HasSubstr("5")
		, HasSubstr("6")
		, HasSubstr("7")
		, HasSubstr("8")
	));
	IUTEST_EXPECT_THAT(va, Each(AnyOf( Ge(0), Le(10) )));
}

IUTEST(MatcherFailure, AllOf)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AllOf( StartsWith("ho"), EndsWith("gE"))), "StartsWith: ho and EndsWith: gE");
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AllOf( StartsWith("Ho"), EndsWith("ge"))), "StartsWith: Ho");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va
		, Each(AllOf( Ge(0), Le(5) ))), "Each: Ge: 0 and Le: 5");
}

IUTEST(MatcherFailure, AnyOf)
{
	CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AnyOf( StartsWith("Ho"), EndsWith("gE"))), "StartsWith: Ho or EndsWith: gE");
	CHECK_FAILURE( IUTEST_ASSERT_THAT(va
		, Each(AnyOf( Gt(5), Lt(5) ))), "Each: Gt: 5 or Lt: 5");
}

#endif

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IUTEST_HAS_MATCHERS
	for( int i=0; i < 10; ++i ) va.push_back(i);
	for( int i=0; i < 10; ++i ) vv.push_back(va);
	for( int i=0; i < 10; ++i ) m.insert( ::std::pair<int,int>(i, 100) );
	for( int i=0; i < 10; ++i ) mx.insert( ::std::pair<int,X>(i, X(i, i)) );
#endif

	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

