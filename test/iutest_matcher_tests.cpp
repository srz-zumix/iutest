//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_matcher_tests.cpp
 * @brief		iutest matcher test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
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
::std::vector< ::std::vector<int> > vv;
int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int b[3] = { 1, 2, 3 };
int c[3] = { 1, 1, 1 };
int n[2][2] = { {0,1}, {2,3} };
::std::map<int, int> m;
void* p1 = NULL;
void* p2 = &p1;
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

IUTEST(Matcher, At)
{
	IUTEST_EXPECT_THAT( b, At(1, 2));
	IUTEST_EXPECT_THAT(va, At(1, Gt(0)));
}

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
	IUTEST_EXPECT_THAT(a, Pointee(0));
	IUTEST_EXPECT_THAT(a, Pointee(Ge(0)));
}

IUTEST(Matcher, _)
{
	IUTEST_EXPECT_THAT(42, _);
	IUTEST_EXPECT_THAT( x, _);
	IUTEST_EXPECT_THAT(&x, _);
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
	IUTEST_EXPECT_THAT( c, ElementsAreArray(b, 1));
}

IUTEST(MatcherFailure, Eq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, Eq(0)), "Eq: 0" );
}

IUTEST(MatcherFailure, Ne)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, Ne(0)), "Ne: 0" );
}

IUTEST(MatcherFailure, Le)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, Le(0)), "Le: 0" );
}

IUTEST(MatcherFailure, Lt)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, Lt(0)), "Lt: 0" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, Lt(0)), "Lt: 0" );
}

IUTEST(MatcherFailure, Ge)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, Ge(1)), "Ge: 1" );
}

IUTEST(MatcherFailure, Gt)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, Gt(1)), "Gt: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, Gt(1)), "Gt: 1" );
}

IUTEST(MatcherFailure, IsNull)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(p2, IsNull()), "Is Null");
}

IUTEST(MatcherFailure, NotNull)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(p1, NotNull()), "Not Null");
}

IUTEST(MatcherFailure, FloatEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(f0, FloatEq(1.0f)), "Eq: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0/f0, FloatEq(0/f0)), "Eq: " );
}

IUTEST(MatcherFailure, DoubleEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(d0, DoubleEq(1.0)), "Eq: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0/d0, DoubleEq(0/d0)), "Eq: " );
}

IUTEST(MatcherFailure, NanSensitiveFloatEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatEq(1.0f)), "Eq: 1" );
}

IUTEST(MatcherFailure, NanSensitiveDoubleEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveDoubleEq(1.0)), "Eq: 1" );
}

IUTEST(MatcherFailure, StrEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StrEq("Hoge")), "StrEq: Hoge");
}

IUTEST(MatcherFailure, StrNe)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StrNe("hoge")), "StrNe: hoge");
}

IUTEST(MatcherFailure, StrCaseEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseEq("hoga")), "StrCaseEq: hoga");
}

IUTEST(MatcherFailure, StrCaseNe)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseNe("hoge")), "StrCaseNe: hoge");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StrCaseNe("hoGe")), "StrCaseNe: hoGe");
}

IUTEST(MatcherFailure, StartsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StartsWith("Ho")) , "StartsWith: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", StartsWith("oge")), "StartsWith: oge" );
}

IUTEST(MatcherFailure, HasSubstr)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", HasSubstr("Ho")), "HasSubstr: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", HasSubstr("oe")), "HasSubstr: oe" );
}

IUTEST(MatcherFailure, EndsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", EndsWith("Ge")) , "EndsWith: Ge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", EndsWith("gee")), "EndsWith: gee" );
}

IUTEST(MatcherFailure, Equals)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", Equals("Hoge")) , "Eq: Hoge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, Equals(1)), "Eq: 1" );
}

IUTEST(MatcherFailure, Contains)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, Contains(42)), "Contains: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( b, Contains(42)), "Contains: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, Contains(Lt(0))), "Contains: Lt: 0" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(vv, Contains(Contains(Lt(0)))), "Contains: Contains: Lt: 0" );
}

IUTEST(MatcherFailure, Each)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, Each(42)), "Each: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( b, Each(42)), "Each: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, Each(Ne(9))), "Each: Ne: 9" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(vv, Each(Each(Gt(5)))), "Each: Each: Gt: 5" );
}

IUTEST(MatcherFailure, At)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( b, At(2, 2)), "At 2: 2" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, At(1, Gt(1))), "At 1: Gt: 1" );
}

IUTEST(MatcherFailure, Key)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( m, Each(Key(0))), "Each: Key: 0" );
}

IUTEST(MatcherFailure, Pair)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( m, Each(Pair(Gt(5), 100))), "Each: Pair: (Gt: 5, 100)" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( m, Each(Pair(_, Ne(100)))), "Each: Pair: (_, Ne: 100)" );
}

IUTEST(MatcherFailure, Field)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( x, Field(&X::a, 100)), "Field: 100" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( x, Field(&X::a, Ne(1))), "Field: Ne: 1" );
}

IUTEST(MatcherFailure, Property)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( x, Property(&X::GetA, 100)), "Property: 100" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( x, Property(&X::GetA, Ne(1))), "Property: Ne: 1" );
}

IUTEST(MatcherFailure, ResultOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, 1)), "Result of: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, Le(1))), "Result of: Le: 1" );
}

IUTEST(MatcherFailure, Pointee)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(a, Pointee(1)), "Points To: 1");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(a, Pointee(Gt(0))), "Points To: Gt: 0");
}

IUTEST(MatcherFailure, A)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", A<int>()), "A: ");
}

IUTEST(MatcherFailure, ElementsAreArray)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(b, ElementsAreArray(c)), "ElementsAreArray: " );
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE

IUTEST(Matcher, ElementsAre)
{
	IUTEST_EXPECT_THAT("hoge", ElementsAre('h', 'o', 'g', 'e', '\0'));
	IUTEST_EXPECT_THAT(va, ElementsAre(Ge(0), Gt(0)));
}

IUTEST(MatcherFailure, ElementsAre)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ElementsAre( 'h', 'o', 'G', 'e', '\0')), "ElementsAre(2): G");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
		, ElementsAre(Ge(0), Gt(0), Lt(1))), "ElementsAre(2): Lt: 1");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(n, Each(
		ElementsAre(Lt(3), Lt(3)))), "Each: ElementsAre: {Lt: 3, Lt: 3}");
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
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AllOf( StartsWith("ho"), EndsWith("gE"))), "StartsWith: ho and EndsWith: gE");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AllOf( StartsWith("Ho"), EndsWith("ge"))), "StartsWith: Ho");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
		, Each(AllOf( Ge(0), Le(5) ))), "Each: Ge: 0 and Le: 5");
}

IUTEST(MatcherFailure, AnyOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, AnyOf( StartsWith("Ho"), EndsWith("gE"))), "StartsWith: Ho or EndsWith: gE");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
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

