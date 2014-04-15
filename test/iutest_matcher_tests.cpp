//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_matcher_tests.cpp
 * @brief		iutest matcher test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
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

::std::string hoge = "hoge";
::std::string hog = "hog";
::std::string oge = "oge";
::std::vector<int> a;
int b[3] = { 1, 2, 3 };

IUTEST(Matcher, StartsWith)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::StartsWith("ho"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::StartsWith(hog));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StartsWith("ho"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::StartsWith(hog));
}

IUTEST(Matcher, Contains)
{
	IUTEST_EXPECT_THAT("hoge", ::iutest::Contains("ho"));
	IUTEST_EXPECT_THAT("hoge", ::iutest::Contains(oge));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Contains("ge"));
	IUTEST_EXPECT_THAT(hoge, ::iutest::Contains(hog));
}

IUTEST(Matcher, ContainsContainer)
{
	IUTEST_EXPECT_THAT(a, ::iutest::Contains(1));
	IUTEST_EXPECT_THAT(b, ::iutest::Contains(1));
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


IUTEST(MatcherFailure, StartsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StartsWith("Ho")) , "StartsWith: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::StartsWith("oge")), "StartsWith: oge" );
}

IUTEST(MatcherFailure, Contains)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Contains("Ho")), "Contains: Ho" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Contains("oe")), "Contains: oe" );
}

IUTEST(MatcherFailure, ContainsContainer)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(a, ::iutest::Contains(42)), "Contains: 42" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(b, ::iutest::Contains(42)), "Contains: 42" );
}

IUTEST(MatcherFailure, EndsWith)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::EndsWith("Ge")) , "EndsWith: Ge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::EndsWith("gee")), "EndsWith: gee" );
}

IUTEST(MatcherFailure, Equals)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge", ::iutest::Equals("Hoge")) , "Equals: Hoge" );
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT(0, ::iutest::Equals(1)), "Equals: 1" );
}

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
}


IUTEST(MatcherFailure, AllOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AllOf( ::iutest::StartsWith("ho"), ::iutest::EndsWith("gE"))), "StartsWith: ho and EndsWith: gE");
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AllOf( ::iutest::StartsWith("Ho"), ::iutest::EndsWith("ge"))), "StartsWith: Ho");
}

IUTEST(MatcherFailure, AnyOf)
{
	IUTEST_EXPECT_FATAL_FAILURE( IUTEST_ASSERT_THAT("hoge"
		, ::iutest::AnyOf( ::iutest::StartsWith("Ho"), ::iutest::EndsWith("gE"))), "StartsWith: Ho or EndsWith: gE");
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
	for( int i=0; i < 10; ++i ) a.push_back(i);
#endif

	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

