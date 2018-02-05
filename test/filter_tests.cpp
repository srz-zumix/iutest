//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        filter_tests.cpp
 * @brief       filter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#define MAKE_TEST(TestCase, TestName)                                   \
    namespace TestCase##TestName { enum STATE { NOT_RAN, RAN };         \
        void PrintTo(const STATE& state, ::iutest::iu_ostream* os) {    \
            *os << ((state) ? "RAN" : "NOT_RAN");                       \
        }                                                               \
        static STATE state;                                             \
    }                                                                   \
    IUTEST(TestCase, TestName) {                                        \
        TestCase##TestName::state = TestCase##TestName::RAN;            \
    }                                                                   \

MAKE_TEST(Test, Hoge)
MAKE_TEST(Hoge, Test)
MAKE_TEST(Foo, Bar)
MAKE_TEST(Foo, Baz)
MAKE_TEST(Foo, BarTest)
MAKE_TEST(Foo, Qux)

bool FilterTest(const char* filter
    , TestHoge::STATE ranTestHoge
    , HogeTest::STATE ranHogeTest
    , FooBar::STATE ranFooBar
    , FooBaz::STATE ranFooBaz
    , FooBarTest::STATE ranFooBarTest
    , FooQux::STATE ranFooQux
)
{
    TestHoge::state = TestHoge::NOT_RAN;
    HogeTest::state = HogeTest::NOT_RAN;
    FooBar::state = FooBar::NOT_RAN;
    FooBaz::state = FooBaz::NOT_RAN;
    FooBarTest::state = FooBarTest::NOT_RAN;
    FooQux::state = FooQux::NOT_RAN;

    ::iutest::IUTEST_FLAG(filter) = filter;
    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return false;

    {
        IUTEST_SCOPED_TRACE(filter);

        IUTEST_EXPECT_EQ( ranTestHoge  , TestHoge::state );
        IUTEST_EXPECT_EQ( ranHogeTest  , HogeTest::state );
        IUTEST_EXPECT_EQ( ranFooBar    , FooBar::state );
        IUTEST_EXPECT_EQ( ranFooBaz    , FooBaz::state );
        IUTEST_EXPECT_EQ( ranFooBarTest, FooBarTest::state );
        IUTEST_EXPECT_EQ( ranFooQux    , FooQux::state );

        int nRan = 0;

        if( ranTestHoge ) ++nRan;
        if( ranHogeTest ) ++nRan;
        if( ranFooBar ) ++nRan;
        if( ranFooBaz ) ++nRan;
        if( ranFooBarTest ) ++nRan;
        if( ranFooQux ) ++nRan;

#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
        IUTEST_EXPECT_EQ( nRan, ::iutest::UnitTest::GetInstance()->reportable_test_count() );
        IUTEST_EXPECT_EQ( 0, ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() );
#endif
#if !defined(IUTEST_USE_GTEST)
        const int kTotal = 6;
        IUTEST_EXPECT_EQ( kTotal-nRan, ::iutest::UnitTest::GetInstance()->skip_test_count() );
        IUTEST_EXPECT_EQ( 0, ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() );
        IUTEST_EXPECT_EQ( 0, ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() );
#endif
    }
    return ::iutest::UnitTest::GetInstance()->Passed();
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);

    if( !FilterTest("*Test*"
        , TestHoge::RAN
        , HogeTest::RAN
        , FooBar::NOT_RAN
        , FooBaz::NOT_RAN
        , FooBarTest::RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("-*Test*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("Foo.Bar"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::NOT_RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("***.Bar"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::NOT_RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("???.Ba?"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("???.Ba?"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("Foo.Ba*-*Test*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("Foo.Ba*:-*Test*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("-*Test*:*Baz*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::NOT_RAN
        , FooBarTest::NOT_RAN
        , FooQux::RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("Foo.Ba*-*Test*:*Baz*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::RAN
        , FooBaz::NOT_RAN
        , FooBarTest::NOT_RAN
        , FooQux::NOT_RAN
    ) ) {
        return 1;
    }

    if( !FilterTest("*Baz*:*Qux*"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::NOT_RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::RAN
    ) ) {
        return 1;
    }

    if( !FilterTest(":::*Baz*:::::*Qux*:::"
        , TestHoge::NOT_RAN
        , HogeTest::NOT_RAN
        , FooBar::NOT_RAN
        , FooBaz::RAN
        , FooBarTest::NOT_RAN
        , FooQux::RAN
    ) ) {
        return 1;
    }

    printf("*** Successful ***\n");
    return 0;
}
