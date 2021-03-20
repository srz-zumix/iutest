//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_tests.cpp
 * @brief       iutest matcher test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <map>
#include <memory>
#include "../include/gtest/iutest_spi_switch.hpp"

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
int ga[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int gb[3] = { 1, 2, 3 };
int gc[3] = { 1, 1, 1 };
int gd[4] = { 1, 2, 3, 4 };
int gn[2][2] = { {0, 1}, {2, 3} };
::std::map<int, int> gm;
int* p1 = NULL;
int** p2 = &p1;
float f0 = 0.0f;
double d0 = 0.0;
#if IUTEST_HAS_LONG_DOUBLE
long double ld0 = 0.0l;
#endif

struct X { int a, b; X(int _a, int _b) : a(_a), b(_b) {} int GetA() const { return a; } };
X gx(1, 1);
::std::map<int, X> mx;
int X2(int v) { return v*2; }

}   // end of namespace

IUTEST(Matcher, SuppressWarning)
{
    (void)gn;
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
    int v=0;
    IUTEST_EXPECT_THAT(1, TypedEq<int>(1));
    IUTEST_EXPECT_THAT(&v, TypedEq<int*>(&v));
}

IUTEST(Matcher, FloatEq)
{
    IUTEST_EXPECT_THAT(f0, FloatEq(0.0f));
    IUTEST_EXPECT_THAT(f0, FloatingPointEq(0.0f));
}

IUTEST(Matcher, DoubleEq)
{
    IUTEST_EXPECT_THAT(d0, DoubleEq(0.0));
    IUTEST_EXPECT_THAT(d0, FloatingPointEq(0.0));
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(Matcher, LongDoubleEq)
{
    IUTEST_EXPECT_THAT(ld0, LongDoubleEq(0.0l));
    long double ldx = 0.001l;
    IUTEST_EXPECT_THAT(ldx, LongDoubleEq(0.001l));
}

#endif

IUTEST(Matcher, NanSensitiveFloatEq)
{
    IUTEST_EXPECT_THAT(f0, NanSensitiveFloatEq(0.0f));
    IUTEST_EXPECT_THAT(0.0f/f0, NanSensitiveFloatEq(0.0f/f0));
    IUTEST_EXPECT_THAT(0.0f/f0, NanSensitiveFloatingPointEq(0.0f/f0));
}

IUTEST(Matcher, NanSensitiveDoubleEq)
{
    IUTEST_EXPECT_THAT(d0, NanSensitiveDoubleEq(0.0));
    IUTEST_EXPECT_THAT(0.0/d0, NanSensitiveDoubleEq(0.0/d0));
    IUTEST_EXPECT_THAT(0.0/d0, NanSensitiveFloatingPointEq(0.0/d0));
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(Matcher, NanSensitiveLongDoubleEq)
{
    IUTEST_EXPECT_THAT(ld0, NanSensitiveLongDoubleEq(0.0l));
    IUTEST_EXPECT_THAT(0.0l/ld0, NanSensitiveLongDoubleEq(0.0l/ld0));
    long double ldx = 0.001l;
    IUTEST_EXPECT_THAT(ldx, NanSensitiveLongDoubleEq(0.001l));
}

#endif

#if IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR

IUTEST(Matcher, FloatNear)
{
    IUTEST_EXPECT_THAT(f0, FloatNear(0.0f, 0.0f));
    IUTEST_EXPECT_THAT(f0, FloatNear(1.0f, 1.0f));
    IUTEST_EXPECT_THAT(f0, FloatingPointNear(0.0f, 0.0f));
}

IUTEST(Matcher, DoubleNear)
{
    IUTEST_EXPECT_THAT(d0, DoubleNear(0.0, 0.0));
    IUTEST_EXPECT_THAT(d0, DoubleNear(1.0, 1.0));
    IUTEST_EXPECT_THAT(d0, FloatingPointNear(0.0, 0.0));
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(Matcher, LongDoubleNear)
{
    IUTEST_EXPECT_THAT(ld0, LongDoubleNear(0.0l, 0.0l));
    long double ldx = 0.001l;
    IUTEST_EXPECT_THAT(ld0, LongDoubleNear(ldx, ldx));
}
#endif

IUTEST(Matcher, NanSensitiveFloatNear)
{
    IUTEST_EXPECT_THAT(f0, NanSensitiveFloatNear(0.0f, 0.0f));
    IUTEST_EXPECT_THAT(f0, NanSensitiveFloatNear(1.0f, 1.0f));
    IUTEST_EXPECT_THAT(0.0f/f0, NanSensitiveFloatNear(0.0f/f0, 0.0f));
    IUTEST_EXPECT_THAT(0.0f/f0, NanSensitiveFloatingPointNear(0.0f/f0, 0.0f));
}

IUTEST(Matcher, NanSensitiveDoubleNear)
{
    IUTEST_EXPECT_THAT(d0, NanSensitiveDoubleNear(0.0, 0.0));
    IUTEST_EXPECT_THAT(d0, NanSensitiveDoubleNear(1.0, 1.0));
    IUTEST_EXPECT_THAT(0.0/d0, NanSensitiveDoubleNear(0.0/d0, 0.0));
    IUTEST_EXPECT_THAT(0.0/d0, NanSensitiveFloatingPointNear(0.0/d0, 0.0));
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(Matcher, NanSensitiveLongDoubleNear)
{
    IUTEST_EXPECT_THAT(ld0, NanSensitiveLongDoubleNear(0.0l, 0.0l));
    IUTEST_EXPECT_THAT(0.0l/ld0, NanSensitiveLongDoubleNear(0.0l/ld0, 0.0l));
    long double ldx = 0.001l;
    IUTEST_EXPECT_THAT(ld0, NanSensitiveLongDoubleNear(ldx, ldx));
}

#endif

#endif

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
    IUTEST_EXPECT_THAT(gb, Contains(1));
    IUTEST_EXPECT_THAT(va, Contains(Lt(4)));
    IUTEST_EXPECT_THAT(vv, Contains(Contains(Lt(4))));
}

#if IUTEST_HAS_MATCHER_EACH
IUTEST(Matcher, Each)
{
    IUTEST_EXPECT_THAT(gc, Each(1));
    IUTEST_EXPECT_THAT(va, Each(Le(10)));
    IUTEST_EXPECT_THAT(vv, Each(Each(Le(10))));
}
#endif

IUTEST(Matcher, ContainerEq)
{
    IUTEST_EXPECT_THAT(ga, ContainerEq(ga));
    IUTEST_EXPECT_THAT(va, ContainerEq(va));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_THAT(ga, ContainerEq(va));
    IUTEST_EXPECT_THAT(va, ContainerEq(ga));
#endif
}

#if IUTEST_HAS_MATCHER_POINTWISE
IUTEST(Matcher, Pointwise)
{
    IUTEST_EXPECT_THAT(gn[0], Pointwise(Ne(), gn[1]));
    IUTEST_EXPECT_THAT(gn[0], Pointwise(Lt(), gn[1]));
    IUTEST_EXPECT_THAT(gn[0], Pointwise(Le(), gn[1]));
    IUTEST_EXPECT_THAT(gn[1], Pointwise(Gt(), gn[0]));
    IUTEST_EXPECT_THAT(gb, Pointwise(Ge(), gc));
    IUTEST_EXPECT_THAT(va, Pointwise(Eq(), va));
    IUTEST_EXPECT_THAT(ga, Pointwise(Eq(), va));
    IUTEST_EXPECT_THAT(va, Pointwise(Eq(), ga));
}
#endif

#if !defined(IUTEST_USE_GMOCK) || (defined(GMOCK_VER) && GMOCK_VER >= 0x01070000)
IUTEST(Matcher, IsEmpty)
{
    IUTEST_ASSERT_THAT(ve, IsEmpty());
}

IUTEST(Matcher, SizeIs)
{
    IUTEST_ASSERT_THAT(ve, SizeIs(0u));
    IUTEST_ASSERT_THAT(va, SizeIs(Ge(10u)));
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_ASSERT_THAT(gc, SizeIs(3u));
#endif
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(Matcher, At)
{
    IUTEST_EXPECT_THAT(gb, At(1, 2));
    IUTEST_EXPECT_THAT(va, At(1, Gt(0)));
}
#endif

#if IUTEST_HAS_MATCHER_EACH
IUTEST(Matcher, Key)
{
    IUTEST_EXPECT_THAT(gm, Each(Key(Le(10))));
}

IUTEST(Matcher, Pair)
{
    IUTEST_EXPECT_THAT(gm, Each(Pair(Le(10), 100)));
}
#endif

IUTEST(Matcher, Field)
{
    IUTEST_EXPECT_THAT( gx, Field(&X::a, 1));
    IUTEST_EXPECT_THAT(&gx, Field(&X::a, 1));
#if IUTEST_HAS_MATCHER_EACH
    IUTEST_EXPECT_THAT( mx, Each(Pair(Le(10), Field(&X::b, Ge(0)))));
#endif
}

IUTEST(Matcher, Property)
{
    IUTEST_EXPECT_THAT( gx, Property(&X::GetA, 1));
    IUTEST_EXPECT_THAT(&gx, Property(&X::GetA, 1));
#if IUTEST_HAS_MATCHER_EACH
    IUTEST_EXPECT_THAT( mx, Each(Pair(Le(10), Property(&X::GetA, Ge(0)))));
#endif
}

IUTEST(Matcher, ResultOf)
{
    IUTEST_EXPECT_THAT(1, ResultOf(X2, 2));
    IUTEST_EXPECT_THAT(1, ResultOf(X2, Gt(1)));
}

IUTEST(Matcher, Pointee)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_THAT(ga, Pointee(0));
    IUTEST_EXPECT_THAT(ga, Pointee(Ge(0)));
#endif
    IUTEST_EXPECT_THAT(p2, Pointee(IsNull()));
}

IUTEST(Matcher, _)
{
    IUTEST_EXPECT_THAT( 42, _);
    IUTEST_EXPECT_THAT( gx, _);
    IUTEST_EXPECT_THAT(&gx, _);
}

IUTEST(Matcher, Not)
{
    IUTEST_EXPECT_THAT(42, Not(1));
    IUTEST_EXPECT_THAT(42, Not(Ne(42)));
}

IUTEST(Matcher, A)
{
    IUTEST_EXPECT_THAT( 42, A<int>());
    IUTEST_EXPECT_THAT( gx, A<X>());
    IUTEST_EXPECT_THAT(&gx, A<X*>());
}

IUTEST(Matcher, ElementsAreArray)
{
    IUTEST_EXPECT_THAT(va, ElementsAreArray(ga));
    IUTEST_EXPECT_THAT(gc, ElementsAreArray(gc));
    IUTEST_EXPECT_THAT(gb, ElementsAreArray(gd, 3));
#if !defined(IUTEST_USE_GMOCK) || (GMOCK_VER >= 0x01070000)
    IUTEST_EXPECT_THAT(ga, ElementsAreArray(va.begin(), va.end()));
    IUTEST_EXPECT_THAT(ga, ElementsAreArray(va));
    IUTEST_EXPECT_THAT(va, ElementsAreArray(va));
#endif
#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_EXPECT_THAT(gc, ElementsAreArray({1, 1, 1}));
#endif
}

#if !defined(IUTEST_USE_GMOCK)
#  define CHECK_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE( x, str )
#else
#  define CHECK_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE( x, "" )
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
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/f0, FloatingPointEq(0/f0)), "Eq: " );
}

IUTEST(MatcherFailure, DoubleEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, DoubleEq(1.0)), "Eq: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/d0, DoubleEq(0/d0)), "Eq: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/d0, FloatingPointEq(0/d0)), "Eq: " );
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(MatcherFailure, LongDoubleEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ld0, LongDoubleEq(1.0l)), "Eq: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/ld0, LongDoubleEq(0/ld0)), "Eq: " );
}

#endif

IUTEST(MatcherFailure, NanSensitiveFloatEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatEq(1.0f)), "Eq: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatingPointEq(1.0f)), "Eq: " );
}

IUTEST(MatcherFailure, NanSensitiveDoubleEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveDoubleEq(1.0)), "Eq: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveFloatingPointEq(1.0)), "Eq: " );
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(MatcherFailure, NanSensitiveLongDoubleEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ld0, NanSensitiveLongDoubleEq(1.0l)), "Eq: " );
}

#endif

#if IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR

IUTEST(MatcherFailure, FloatNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, FloatNear(1.0f, f0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/f0, FloatNear(0/f0, 1.0f)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/f0, FloatingPointNear(f0, 1.0f)), "Near: " );
}

IUTEST(MatcherFailure, DoubleNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, DoubleNear(1.0, d0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/d0, DoubleNear(0/d0, 1.0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/d0, FloatingPointNear(0/d0, 1.0)), "Near: " );
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(MatcherFailure, LongDoubleNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ld0, LongDoubleNear(1.0l, ld0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0/ld0, LongDoubleNear(0/ld0, 1.0l)), "Near: " );
}

#endif

IUTEST(MatcherFailure, NanSensitiveFloatNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatNear(1.0f, f0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(f0, NanSensitiveFloatingPointNear(1.0f, f0)), "Near: " );
}

IUTEST(MatcherFailure, NanSensitiveDoubleNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveDoubleNear(1.0, d0)), "Near: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(d0, NanSensitiveFloatingPointNear(1.0, d0)), "Near: " );
}

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(MatcherFailure, NanSensitiveLongDoubleNear)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ld0, NanSensitiveLongDoubleNear(1.0l, ld0)), "Near: " );
}

#endif

#endif

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
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", EndsWith("TooLongLongEnds")) , "EndsWith: TooLongLongEnds" );
}

IUTEST(MatcherFailure, Equals)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", Equals("Hoge")) , "Eq: Hoge" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(0, Equals(1)), "Eq: 1" );
}

IUTEST(MatcherFailure, Contains)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Contains(42)), "Contains: 42" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, Contains(42)), "Contains: 42" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Contains(Lt(0))), "Contains: Lt: 0" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(vv, Contains(Contains(Lt(0)))), "Contains: Contains: Lt: 0" );
}

#if IUTEST_HAS_MATCHER_EACH
IUTEST(MatcherFailure, Each)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Each(42)), "Each: 42" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, Each(42)), "Each: 42" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, Each(Ne(9))), "Each: Ne: 9" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(vv, Each(Each(Gt(5)))), "Each: Each: Gt: 5" );
}
#endif

IUTEST(MatcherFailure, ContainerEq)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ContainerEq(gc)), "ContainerEq: { 1, 1, 1 }" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ContainerEq(gc)), "Mismatch in a position 1: 1 vs 2" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ContainerEq(gc)), "Mismatch in a position 2: 1 vs 3" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ga, ContainerEq(gc)), "Mismatch element : 3 vs 10" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gc, ContainerEq(ga)), "Mismatch element : 10 vs 3" );
}

#if IUTEST_HAS_MATCHER_POINTWISE
IUTEST(MatcherFailure, Pointwise)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, Pointwise(Eq(), gc)), "Pointwise: Eq: { 1, 1, 1 }" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ga, Pointwise(Eq(), gc)), "Mismatch element : 3 vs 10" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gc, Pointwise(Eq(), ga)), "Mismatch element : 10 vs 3" );
}
#endif

#if !defined(IUTEST_USE_GMOCK) || (defined(GMOCK_VER) && GMOCK_VER >= 0x01070000)
IUTEST(MatcherFailure, IsEmpty)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, IsEmpty()), "Is Empty" );
}

IUTEST(MatcherFailure, SizeIs)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, SizeIs(0u)), "Size is: 0" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, SizeIs(Lt(0u))), "Size is: Lt: 0" );
#if !defined(IUTEST_USE_GMOCK)
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gc, SizeIs(Lt(0u))), "Size is: Lt: 0" );
#endif
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(MatcherFailure, At)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, At(2, 2)), "At 2: 2" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va, At(1, Gt(1))), "At 1: Gt: 1" );
}
#endif

#if IUTEST_HAS_MATCHER_EACH
IUTEST(MatcherFailure, Key)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gm, Each(Key(0))), "Each: Key: 0" );
}

IUTEST(MatcherFailure, Pair)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gm, Each(Pair(Gt(5), 100))), "Each: Pair: (Gt: 5, 100)" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gm, Each(Pair(_, Ne(100)))), "Each: Pair: (_, Ne: 100)" );
}
#endif

IUTEST(MatcherFailure, Field)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gx, Field(&X::a, 100)), "Field: 100" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gx, Field(&X::a, Ne(1))), "Field: Ne: 1" );
}

IUTEST(MatcherFailure, Property)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gx, Property(&X::GetA, 100)), "Property: 100" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gx, Property(&X::GetA, Ne(1))), "Property: Ne: 1" );
}

IUTEST(MatcherFailure, ResultOf)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, 1)), "Result of: 1" );
    CHECK_FAILURE( IUTEST_ASSERT_THAT( 1, ResultOf(X2, Le(1))), "Result of: Le: 1" );
}

IUTEST(MatcherFailure, Pointee)
{
#if !defined(IUTEST_USE_GMOCK)
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ga, Pointee(1)), "Points To: 1");
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ga, Pointee(Gt(0))), "Points To: Gt: 0");
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
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ElementsAreArray(gc)), "ElementsAreArray: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ElementsAreArray(ga))
        , "ElementsAreArray: actual argument[3] is less than 10");
    CHECK_FAILURE( IUTEST_ASSERT_THAT(ga, ElementsAreArray(gb))
        , "ElementsAreArray: actual argument[10] is greater than 3");
}

#if IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD

IUTEST(Matcher, ElementsAreArrayForward)
{
    IUTEST_EXPECT_THAT(va, ElementsAreArrayForward(ga));
    IUTEST_EXPECT_THAT(gc, ElementsAreArrayForward(gc));
    IUTEST_EXPECT_THAT(ga, ElementsAreArrayForward(va.begin(), va.begin()+1));
    IUTEST_EXPECT_THAT(va, ElementsAreArrayForward(va));
#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_EXPECT_THAT(gc, ElementsAreArrayForward({1, 1}));
#endif
    IUTEST_EXPECT_THAT(gc, ElementsAreArrayForward(gb, 1));
}

IUTEST(MatcherFailure, ElementsAreArrayForward)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ElementsAreArrayForward(gc)), "ElementsAreArrayForward: " );
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gb, ElementsAreArrayForward(ga))
        , "ElementsAreArrayForward: actual argument[3] is less than 10");
}

#endif

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
#if IUTEST_HAS_MATCHER_EACH
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gn, Each(
        ElementsAre(Lt(3), Lt(3)))), "Each: ElementsAre: {Lt: 3, Lt: 3}");
#endif
    CHECK_FAILURE( IUTEST_ASSERT_THAT(gc
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
    IUTEST_EXPECT_THAT(s, ContainsRegex("e"));
    IUTEST_EXPECT_THAT("hogeeeeeet", ContainsRegex("hoge+"));
}

IUTEST(MatcherFailure, MatchesRegex)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hogeeeeeet", MatchesRegex("hoge+"))
        , "MatchesRegex: hoge+");
}

IUTEST(MatcherFailure, ContainsRegex)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge", ContainsRegex("[0-9]"))
        , "ContainsRegex: [0-9]");
}

#endif


#if IUTEST_HAS_CXX11
typedef ::std::unique_ptr<int> test_int_ptr;
#else
typedef int* test_int_ptr;
#endif
#if IUTEST_HAS_MATCHER_OPTIONAL

#if IUTEST_HAS_CXX_HDR_OPTIONAL
typedef ::std::optional<int> OptionalInt;
typedef ::std::optional<test_int_ptr> OptionalIntPtr;
#elif !defined(IUTEST_USE_GTEST)
typedef ::iutest::stl::optional<int> OptionalInt;
typedef ::iutest::stl::optional<test_int_ptr> OptionalIntPtr;
#else
template <typename T>
class SampleOptional
{
public:
    typedef T value_type;
    template<typename U>
    explicit SampleOptional(const U& value)
        : value_(T(value)), has_value_(true) {}
    SampleOptional() : value_(), has_value_(false) {}
    operator bool() const { return has_value_; }
    const T &operator*() const { return value_; }

private:
    T value_;
    bool has_value_;
};
typedef SampleOptional<int> OptionalInt;
typedef SampleOptional<test_int_ptr> OptionalIntPtr;
#endif

OptionalInt opt1(1);
OptionalIntPtr optnull(p1);
OptionalInt optempty;

IUTEST(Matcher, Optional)
{
    IUTEST_EXPECT_THAT(opt1, Optional(1));
    IUTEST_EXPECT_THAT(opt1, Optional(Eq(1)));
    IUTEST_EXPECT_THAT(opt1, Optional(Lt(2)));

    IUTEST_EXPECT_THAT(optnull, Optional(IsNull()));
}

IUTEST(MatcherFailure, Optional)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(optempty, Optional(1)), "Optional: 1 (which is not engaged)");
    CHECK_FAILURE( IUTEST_ASSERT_THAT(opt1, Optional(2)), "Optional: 2 (1)");
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
}

IUTEST(MatcherFailure, AllOf)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
        , AllOf( StartsWith("ho"), EndsWith("gE"))), "StartsWith: ho and EndsWith: gE");
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
        , AllOf( StartsWith("Ho"), EndsWith("ge"))), "StartsWith: Ho");
}

IUTEST(MatcherFailure, AnyOf)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT("hoge"
        , AnyOf( StartsWith("Ho"), EndsWith("gE"))), "StartsWith: Ho or EndsWith: gE");
}

#if IUTEST_HAS_MATCHER_EACH
IUTEST(Matcher, EachAllOf)
{
    IUTEST_EXPECT_THAT(va, Each(AllOf( Ge(0), Le(10) )));
}

IUTEST(Matcher, EachAnyOf)
{
    IUTEST_EXPECT_THAT(va, Each(AnyOf( Ge(0), Le(10) )));
}

IUTEST(MatcherFailure, EachAllOf)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va
        , Each(AllOf( Ge(0), Le(5) ))), "Each: Ge: 0 and Le: 5");
}

IUTEST(MatcherFailure, EachAnyOf)
{
    CHECK_FAILURE( IUTEST_ASSERT_THAT(va
        , Each(AnyOf( Gt(5), Lt(5) ))), "Each: Gt: 5 or Lt: 5");
}
#endif

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
    for( int i=0; i < 10; ++i ) gm.insert( ::std::pair<int, int>(i, 100) );
    for( int i=0; i < 10; ++i ) mx.insert( ::std::pair<int, X>(i, X(i, i)) );
#endif

    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

