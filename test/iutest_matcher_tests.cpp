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

#if IUTEST_HAS_MATCHERS

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
void* p1 = NULL;
void* p2 = &p1;
float f0 = 0.0f;
double d0 = 0.0;

}

IUTEST(Matcher, Eq)
{
	IUTEST_EXPECT_THAT(1, ::iutest::Eq(1));
}

IUTEST(Matcher, Ne)
{
	IUTEST_EXPECT_THAT(0, ::iutest::Ne(1));
}

IUTEST(Matcher, Le)
{
	IUTEST_EXPECT_THAT(1, ::iutest::Le(1));
	IUTEST_EXPECT_THAT(0, ::iutest::Le(1));
}

IUTEST(Matcher, Lt)
{
	IUTEST_EXPECT_THAT(0, ::iutest::Lt(1));
}

IUTEST(Matcher, Ge)
{
	IUTEST_EXPECT_THAT(1, ::iutest::Ge(0));
	IUTEST_EXPECT_THAT(0, ::iutest::Ge(0));
}

IUTEST(Matcher, Gt)
{
	IUTEST_EXPECT_THAT(1, ::iutest::Gt(0));
}

IUTEST(Matcher, IsNull)
{
	IUTEST_EXPECT_THAT(p1, ::iutest::IsNull());
}

IUTEST(Matcher, NotNull)
{
	IUTEST_EXPECT_THAT(p2, ::iutest::NotNull());
}

IUTEST(Matcher, FloatEq)
{
	IUTEST_EXPECT_THAT(f0, ::iutest::FloatEq(0.0f));
}

IUTEST(Matcher, DoubleEq)
{
	IUTEST_EXPECT_THAT(d0, ::iutest::DoubleEq(0.0));
}

IUTEST(Matcher, NanSensitiveFloatEq)
{
	IUTEST_EXPECT_THAT(f0, ::iutest::NanSensitiveFloatEq(0.0f));
	IUTEST_EXPECT_THAT(0.0f/f0, ::iutest::NanSensitiveFloatEq(0.0f/f0));
}

IUTEST(Matcher, NanSensitiveDoubleEq)
{
	IUTEST_EXPECT_THAT(d0, ::iutest::NanSensitiveDoubleEq(0.0));
	IUTEST_EXPECT_THAT(0.0/d0, ::iutest::NanSensitiveDoubleEq(0.0/d0));
}

IUTEST(Matcher, StrEq)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::StrEq("hoge"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::StrEq(hoge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrEq("hoge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrEq(hoge));
}

IUTEST(Matcher, StrNe)
{
	IUTEST_EXPECT_THAT("hoga", ::iutest::StrNe("hoge"));
	IUTEST_EXPECT_THAT("hoga", ::iutest::StrNe(hoge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrNe("Hoge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrNe(Hoge));
}

IUTEST(Matcher, StrCaseEq)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::StrCaseEq("Hoge"));
	IUTEST_EXPECT_THAT("hoGe", ::iutest::StrCaseEq(hoge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrCaseEq("hOge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrCaseEq(Hoge));
}

IUTEST(Matcher, StrCaseNe)
{
	IUTEST_EXPECT_THAT("hoga", ::iutest::StrCaseNe("hoge"));
	IUTEST_EXPECT_THAT("hoga", ::iutest::StrCaseNe(hoge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrCaseNe("hoga"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StrCaseNe(hog));
}

IUTEST(Matcher, StartsWith)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::StartsWith("ho"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::StartsWith(hog));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StartsWith("ho"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StartsWith(hog));
}

IUTEST(Matcher, HasSubstr)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::HasSubstr("ho"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::HasSubstr(oge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::HasSubstr("ge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::HasSubstr(hog));
}

IUTEST(Matcher, EndsWith)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::EndsWith("ge"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::EndsWith(oge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::EndsWith("ge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::EndsWith(oge));
}

IUTEST(Matcher, Equals)
{
	IUTEST_EXPECT_THAT(0, ::iutest::Equals(0));
	IUTEST_EXPECT_THAT("hoge", ::iutest::Equals("hoge"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::Equals(hoge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Equals("hoge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Equals(hoge));
}

IUTEST(Matcher, ContainsString)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::Contains("ho"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::Contains(oge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Contains("ge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Contains(hog));
}

IUTEST(Matcher, ContainsContainer)
{
	IUTEST_EXPECT_THAT(va, ::iutest::Contains(1));
	IUTEST_EXPECT_THAT( b, ::iutest::Contains(1));
	IUTEST_EXPECT_THAT(va, ::iutest::Contains(::iutest::Lt(4)));
	IUTEST_EXPECT_THAT(vv, ::iutest::Contains(::iutest::Contains(::iutest::Lt(4))));
}

IUTEST(Matcher, Each)
{
	IUTEST_EXPECT_THAT( c, ::iutest::Each(1));
	IUTEST_EXPECT_THAT(va, ::iutest::Each(::iutest::Le(10)));
	IUTEST_EXPECT_THAT(vv, ::iutest::Each(::iutest::Each(::iutest::Le(10))));
}

IUTEST(Matcher, ElementsAreArray)
{
	IUTEST_EXPECT_THAT( a, ::iutest::ElementsAreArray(va));
	IUTEST_EXPECT_THAT(va, ::iutest::ElementsAreArray(a));
	IUTEST_EXPECT_THAT(va, ::iutest::ElementsAreArray(va));
	IUTEST_EXPECT_THAT( c, ::iutest::ElementsAreArray(c));
}

IUTEST(MatcherFailure, Eq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, ::iutest::Eq(0)), "Eq: 0" );
}

IUTEST(MatcherFailure, Ne)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Ne(0)), "Ne: 0" );
}

IUTEST(MatcherFailure, Le)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, ::iutest::Le(0)), "Le: 0" );
}

IUTEST(MatcherFailure, Lt)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Lt(0)), "Lt: 0" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, ::iutest::Lt(0)), "Lt: 0" );
}

IUTEST(MatcherFailure, Ge)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Ge(1)), "Ge: 1" );
}

IUTEST(MatcherFailure, Gt)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Gt(1)), "Gt: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(1, ::iutest::Gt(1)), "Gt: 1" );
}

IUTEST(MatcherFailure, IsNull)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(p2, ::iutest::IsNull()), "Is Null");
}

IUTEST(MatcherFailure, NotNull)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(p1, ::iutest::NotNull()), "Not Null");
}

IUTEST(MatcherFailure, FloatEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(f0, ::iutest::FloatEq(1.0f)), "Eq: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0/f0, ::iutest::FloatEq(0/f0)), "Eq: " );
}

IUTEST(MatcherFailure, DoubleEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(d0, ::iutest::DoubleEq(1.0)), "Eq: 1" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0/d0, ::iutest::DoubleEq(0/d0)), "Eq: " );
}

IUTEST(MatcherFailure, NanSensitiveFloatEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(f0, ::iutest::NanSensitiveFloatEq(1.0f)), "Eq: 1" );
}

IUTEST(MatcherFailure, NanSensitiveDoubleEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(d0, ::iutest::NanSensitiveDoubleEq(1.0)), "Eq: 1" );
}

IUTEST(MatcherFailure, StrEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StrEq("Hoge")), "StrEq: Hoge");
}

IUTEST(MatcherFailure, StrNe)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StrNe("hoge")), "StrNe: hoge");
}

IUTEST(MatcherFailure, StrCaseEq)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StrCaseEq("hoga")), "StrCaseEq: hoga");
}

IUTEST(MatcherFailure, StrCaseNe)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StrCaseNe("hoge")), "StrCaseNe: hoge");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StrCaseNe("hoGe")), "StrCaseNe: hoGe");
}

IUTEST(MatcherFailure, StartsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StartsWith("Ho")) , "StartsWith: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StartsWith("oge")), "StartsWith: oge" );
}

IUTEST(MatcherFailure, HasSubstr)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::HasSubstr("Ho")), "HasSubstr: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::HasSubstr("oe")), "HasSubstr: oe" );
}

IUTEST(MatcherFailure, EndsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::EndsWith("Ge")) , "EndsWith: Ge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::EndsWith("gee")), "EndsWith: gee" );
}

IUTEST(MatcherFailure, Equals)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Equals("Hoge")) , "Eq: Hoge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Equals(1)), "Eq: 1" );
}

IUTEST(MatcherFailure, ContainsString)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Contains("Ho")), "Contains: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Contains("oe")), "Contains: oe" );
}

IUTEST(MatcherFailure, ContainsContainer)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, ::iutest::Contains(42)), "Contains: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( b, ::iutest::Contains(42)), "Contains: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, ::iutest::Contains(::iutest::Lt(0))), "Contains: Lt: 0" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(vv, ::iutest::Contains(::iutest::Contains(::iutest::Lt(0)))), "Contains: Contains: Lt: 0" );
}

IUTEST(MatcherFailure, Each)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, ::iutest::Each(42)), "Each: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT( b, ::iutest::Each(42)), "Each: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va, ::iutest::Each(::iutest::Ne(9))), "Each: Ne: 9" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(vv, ::iutest::Each(::iutest::Each(::iutest::Gt(5)))), "Each: Each: Gt: 5" );
}

IUTEST(MatcherFailure, ElementsAreArray)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(b, ::iutest::ElementsAreArray(c)), "ElementsAreArray: " );
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE

IUTEST(Matcher, ElementsAre)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::ElementsAre('h', 'o', 'g', 'e', '\0'));
	IUTEST_EXPECT_THAT(va, ::iutest::ElementsAre(::iutest::Ge(0), ::iutest::Gt(0)));
}

IUTEST(MatcherFailure, ElementsAre)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::ElementsAre( 'h', 'o', 'G', 'e', '\0')), "ElementsAre(2): G");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
		, ::iutest::ElementsAre(::iutest::Ge(0), ::iutest::Gt(0), ::iutest::Lt(1))), "ElementsAre(2): Lt: 1");
}

#endif


#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

IUTEST(Matcher, AllOf)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::AllOf( ::iutest::StartsWith("ho"), ::iutest::EndsWith("ge")));
	IUTEST_EXPECT_THAT("9347812650", ::iutest::AllOf(
		  ::iutest::Contains("0")
		, ::iutest::Contains("1")
		, ::iutest::Contains("2")
		, ::iutest::Contains("3")
		, ::iutest::Contains("4")
		, ::iutest::Contains("5")
		, ::iutest::Contains("6")
		, ::iutest::Contains("7")
		, ::iutest::Contains("8")
	));
	IUTEST_EXPECT_THAT(va, ::iutest::Each(::iutest::AllOf( ::iutest::Ge(0), ::iutest::Le(10) )));
}

IUTEST(Matcher, AnyOf)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::AnyOf( ::iutest::StartsWith("ho"), ::iutest::EndsWith("ge")));
	IUTEST_EXPECT_THAT("hoge", ::iutest::AnyOf( ::iutest::StartsWith("ho"), ::iutest::EndsWith("Ge")));
	IUTEST_EXPECT_THAT("hoge", ::iutest::AnyOf( ::iutest::StartsWith("Ho"), ::iutest::EndsWith("ge")));
	IUTEST_EXPECT_THAT("hoge7", ::iutest::AnyOf(
		  ::iutest::Contains("0")
		, ::iutest::Contains("1")
		, ::iutest::Contains("2")
		, ::iutest::Contains("3")
		, ::iutest::Contains("4")
		, ::iutest::Contains("5")
		, ::iutest::Contains("6")
		, ::iutest::Contains("7")
		, ::iutest::Contains("8")
	));
	IUTEST_EXPECT_THAT(va, ::iutest::Each(::iutest::AnyOf( ::iutest::Ge(0), ::iutest::Le(10) )));
}


IUTEST(MatcherFailure, AllOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AllOf( ::iutest::StartsWith("ho"), ::iutest::EndsWith("gE"))), "StartsWith: ho and EndsWith: gE");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AllOf( ::iutest::StartsWith("Ho"), ::iutest::EndsWith("ge"))), "StartsWith: Ho");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
		, ::iutest::Each(::iutest::AllOf( ::iutest::Ge(0), ::iutest::Le(5) ))), "Each: Ge: 0 and Le: 5");
}

IUTEST(MatcherFailure, AnyOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AnyOf( ::iutest::StartsWith("Ho"), ::iutest::EndsWith("gE"))), "StartsWith: Ho or EndsWith: gE");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(va
		, ::iutest::Each(::iutest::AnyOf( ::iutest::Gt(5), ::iutest::Lt(5) ))), "Each: Gt: 5 or Lt: 5");
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
#endif

	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

