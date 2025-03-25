//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher.cpp
 * @brief       matcher test sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

#if IUTEST_HAS_MATCHERS
#include <map>

using namespace ::iutest::matchers;

namespace {
    struct X { int a, b; X(int _a, int _b) : a(_a), b(_b) {} int GetA() const { return a; } };
    int X2(int v) { return v * 2; }
    float f0 = 0.0f;
    double d0 = 0.0;
}

IUTEST(Matcher, Gernal)
{
    IUTEST_EXPECT_THAT(1, Eq(1));
    IUTEST_EXPECT_THAT(0, Ne(1));
    IUTEST_EXPECT_THAT(0, Le(1));
    IUTEST_EXPECT_THAT(0, Lt(1));
    IUTEST_EXPECT_THAT(1, Ge(0));
    IUTEST_EXPECT_THAT(0, Ge(0));
    IUTEST_EXPECT_THAT(1, Gt(0));
}

IUTEST(Matcher, Null)
{
    int* p1 = NULL;
    int** p2 = &p1;
    IUTEST_EXPECT_THAT(p1, IsNull());
    IUTEST_EXPECT_THAT(p2, NotNull());
    IUTEST_EXPECT_THAT(p2, Pointee(IsNull()));
}

IUTEST_PRAGMA_MSC_WARN_PUSH()
IUTEST_PRAGMA_MSC_WARN_DISABLE(4723)
IUTEST(Matcher, FloatingPoint)
{
    IUTEST_EXPECT_THAT(f0, FloatEq(0.0f));
    IUTEST_EXPECT_THAT(d0, DoubleEq(0.0));
    IUTEST_EXPECT_THAT(f0, NanSensitiveFloatEq(0.0f));
    IUTEST_EXPECT_THAT(0.0f / f0, NanSensitiveFloatEq(0.0f / f0));
    IUTEST_EXPECT_THAT(d0, NanSensitiveDoubleEq(0.0));
    IUTEST_EXPECT_THAT(0.0 / d0, NanSensitiveDoubleEq(0.0 / d0));
}
IUTEST_PRAGMA_MSC_WARN_POP()

IUTEST(Matcher, String)
{
    IUTEST_EXPECT_THAT("hoge", StrEq("hoge"));
    IUTEST_EXPECT_THAT("hoga", StrNe("hoge"));
    IUTEST_EXPECT_THAT("hoge", StrCaseEq("Hoge"));
    IUTEST_EXPECT_THAT("hoga", StrCaseNe("hoge"));

    IUTEST_EXPECT_THAT("hoge", StartsWith("ho"));
    IUTEST_EXPECT_THAT("hoge", HasSubstr("og"));
    IUTEST_EXPECT_THAT("hoge", EndsWith("ge"));
}

IUTEST(Matcher, Container)
{
    int a[2][3] ={ { 1, 2, 3 }, { 4, 5, 6 } };
    int b[3] ={ 1, 2, 3 };
    IUTEST_EXPECT_THAT(b, Contains(Gt(2)));
    IUTEST_EXPECT_THAT(b, Each(Le(10)));
    IUTEST_EXPECT_THAT(a, Each(Each(Le(10))));
}

IUTEST(Matcher, Member)
{
    X x(0, 1);
    ::std::map<int, X> m;
    for( int i=0; i < 10; ++i )
    {
        m.insert(::std::pair<int, X>(i, X(i, 100)));
    }
    IUTEST_EXPECT_THAT(m, Each(Key(Le(10))));
    IUTEST_EXPECT_THAT(m, Each(Pair(Le(10), Field(&X::b, Ge(0)))));
    IUTEST_EXPECT_THAT(x, Property(&X::GetA, 0));
    IUTEST_EXPECT_THAT(&x, Property(&X::GetA, 0));
}

IUTEST(Matcher, Function)
{
    IUTEST_EXPECT_THAT(1, ResultOf(X2, 2));
}

IUTEST(Matcher, Not)
{
    IUTEST_EXPECT_THAT(1, Not(2));
}

IUTEST(Matcher, Wildcard)
{
    IUTEST_EXPECT_THAT(42, _);
    IUTEST_EXPECT_THAT(42, A<int>());
}

IUTEST(Matcher, ElementsAreArray)
{
    int a[3] ={ 0, 1, 3 };
    int b[3] ={ 0, 1, 3 };
    IUTEST_EXPECT_THAT(a, ElementsAreArray(b));
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE

IUTEST(Matcher, ElementsAre)
{
    int a[3] ={ 0, -1, 3 };
    IUTEST_EXPECT_THAT(a, ElementsAre(Ge(0), _, Gt(0)));
}

#endif

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

IUTEST(Matcher, AllOf)
{
    int a[3] ={ 0, 1, 3 };
    IUTEST_EXPECT_THAT("hoge", AllOf(StartsWith("ho"), EndsWith("ge")));
    IUTEST_EXPECT_THAT(a, Each(AllOf(Ge(0), Le(10))));
}

IUTEST(Matcher, AnyOf)
{
    int a[3] ={ 0, -1, 10 };
    IUTEST_EXPECT_THAT("hoge", AnyOf(StartsWith("Ho"), EndsWith("ge")));
    IUTEST_EXPECT_THAT(a, Each(AnyOf(Le(0), Ge(10))));
}

#endif

#endif
