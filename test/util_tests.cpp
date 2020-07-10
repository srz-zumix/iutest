//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        util_tests.cpp
 * @brief       iutest util test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "gtest/iutest_switch.hpp"

IUTEST(UtilTest, Find)
{
    const ::iutest::TestCase* testcase = ::iuutil::FindTestCase("UtilTest");
    IUTEST_EXPECT_NOTNULL(testcase);
    IUTEST_EXPECT_NOTNULL(::iuutil::FindTestInfo("UtilTest", "Find"));

    const ::iutest::TestCase* null_testcase = NULL;
    const char* null_testcase_name = NULL;
    IUTEST_EXPECT_NULL(::iuutil::FindTestCase(NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestCase("UtilTestXXX"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(null_testcase, "Find"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(null_testcase_name, "Find"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(testcase, NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTest", NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTest", "FindXXX"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTestXXX", "Find"));
}

IUTEST(UtilTest, TestCaseNameRemoveIndexName)
{
    IUTEST_EXPECT_STREQ( "pkg.TestCase" , ::iuutil::TestCaseNameRemoveIndexName("pkg.TestCase") );
    IUTEST_EXPECT_STREQ( "pkg.TestCase" , ::iuutil::TestCaseNameRemoveIndexName("pkg.TestCase/0") );
    IUTEST_EXPECT_STREQ( "TestCase" , ::iuutil::TestCaseNameRemoveIndexName("TestCase") );
}

IUTEST(UtilTest, TestCaseNameRemoveInstantiateAndIndexName)
{
    IUTEST_EXPECT_STREQ( "pkg.TestCase" , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName("pkg.prefix/TestCase") );
    IUTEST_EXPECT_STREQ( "pkg.TestCase" , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName("pkg.prefix/TestCase/0") );
    IUTEST_EXPECT_STREQ( "TestCase" , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName("TestCase") );
    IUTEST_EXPECT_STREQ( "TestCase" , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName("prefix/TestCase") );
    IUTEST_EXPECT_STREQ( "TestCase" , ::iuutil::TestCaseNameRemoveInstantiateAndIndexName("prefix/TestCase/0") );
}

IUTEST(AssertionTest, EQ_COLLECTIONS_Array)
{
    int  a[] = { 0, 1, 2, 3, 4 };
    int  b[] = { 0, 1, 2, 3, 4 };
    char c[] = { 0, 1, 2, 3, 4 };

    IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));

    IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
}

IUTEST(AssertionTest, EQ_COLLECTIONS_Vector)
{
    int  d[] = { 0, 1, 2, 3, 4 };
    const int COUNT=sizeof(d)/sizeof(d[0]);
    ::std::vector<int> a, b;
    ::std::vector<char> c;
    for( int i=0; i < COUNT; ++i )
    {
        a.push_back(i);
        b.push_back(i);
        c.push_back(static_cast<char>(i));
    }
    IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
    IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
    IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
    IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());

    IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
    IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
    IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());
    IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), c.begin(), c.end());

    IUTEST_ASSERT_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
    IUTEST_EXPECT_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
    IUTEST_INFORM_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
    IUTEST_ASSUME_EQ_COLLECTIONS(a.begin(), a.end(), d, d+(sizeof(d)/sizeof(d[0])));
}

IUTEST(AssertionTest, NE_COLLECTIONS)
{
    int  a[] = { 0, 1, 2, 3, 4 };
    int  b[] = { 0, 1, 2, 3, 4, 5 };
    char c[] = { 0, 1, 2, 1, 4 };
    ::std::vector<int> d(b+1, b+(sizeof(b)/sizeof(b[0])));

    IUTEST_ASSERT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_EXPECT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_INFORM_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));
    IUTEST_ASSUME_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0])));

    IUTEST_ASSERT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_EXPECT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_INFORM_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));
    IUTEST_ASSUME_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), c, c+(sizeof(c)/sizeof(c[0])));

    IUTEST_ASSERT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), d.begin(), d.end());
    IUTEST_EXPECT_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), d.begin(), d.end());
    IUTEST_INFORM_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), d.begin(), d.end());
    IUTEST_ASSUME_NE_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), d.begin(), d.end());
}

IUTEST(AssertionTest, EQ_RANGE_Array)
{
    int  a[] = { 0, 1, 2, 3, 4 };
    int  b[] = { 0, 1, 2, 3, 4 };
    char c[] = { 0, 1, 2, 3, 4 };

    IUTEST_ASSERT_EQ_RANGE(a, b);
    IUTEST_EXPECT_EQ_RANGE(a, b);
    IUTEST_INFORM_EQ_RANGE(a, b);
    IUTEST_ASSUME_EQ_RANGE(a, b);

    IUTEST_ASSERT_EQ_RANGE(a, c);
    IUTEST_EXPECT_EQ_RANGE(a, c);
    IUTEST_INFORM_EQ_RANGE(a, c);
    IUTEST_ASSUME_EQ_RANGE(a, c);
#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_ASSERT_EQ_RANGE(::std::initializer_list<int>({0, 1, 2, 3, 4}), a);
#if IUTEST_HAS_AUTO
    auto il = {0, 1, 2, 3, 4};
    IUTEST_ASSERT_EQ_RANGE(il, a);
#endif
#endif
}

IUTEST(AssertionTest, EQ_RANGE_Vector)
{
    int  d[] = { 0, 1, 2, 3, 4 };
    const int COUNT=sizeof(d)/sizeof(d[0]);
    ::std::vector<int> a, b;
    ::std::vector<char> c;
    for( int i=0; i < COUNT; ++i )
    {
        a.push_back(i);
        b.push_back(i);
        c.push_back(static_cast<char>(i));
    }
    IUTEST_ASSERT_EQ_RANGE(a, b);
    IUTEST_EXPECT_EQ_RANGE(a, b);
    IUTEST_INFORM_EQ_RANGE(a, b);
    IUTEST_ASSUME_EQ_RANGE(a, b);

    IUTEST_ASSERT_EQ_RANGE(a, c);
    IUTEST_EXPECT_EQ_RANGE(a, c);
    IUTEST_INFORM_EQ_RANGE(a, c);
    IUTEST_ASSUME_EQ_RANGE(a, c);

    IUTEST_ASSERT_EQ_RANGE(a, d);
    IUTEST_EXPECT_EQ_RANGE(a, d);
    IUTEST_INFORM_EQ_RANGE(a, d);
    IUTEST_ASSUME_EQ_RANGE(a, d);

    IUTEST_ASSERT_EQ_RANGE(d, c);
    IUTEST_EXPECT_EQ_RANGE(d, c);
    IUTEST_INFORM_EQ_RANGE(d, c);
    IUTEST_ASSUME_EQ_RANGE(d, c);
}

IUTEST(AssertionTest, NE_RANGE)
{
    int  a[] = { 0, 1, 2, 3, 4 };
    int  b[] = { 0, 1, 2, 3, 4, 5 };
    char c[] = { 0, 1, 2, 0, 4 };
    ::std::vector<int> d(b+1, b+(sizeof(b)/sizeof(b[0])));

    IUTEST_ASSERT_NE_RANGE(a, b);
    IUTEST_EXPECT_NE_RANGE(a, b);
    IUTEST_INFORM_NE_RANGE(a, b);
    IUTEST_ASSUME_NE_RANGE(a, b);

    IUTEST_ASSERT_NE_RANGE(a, c);
    IUTEST_EXPECT_NE_RANGE(a, c);
    IUTEST_INFORM_NE_RANGE(a, c);
    IUTEST_ASSUME_NE_RANGE(a, c);

    IUTEST_ASSERT_NE_RANGE(a, d);
    IUTEST_EXPECT_NE_RANGE(a, d);
    IUTEST_INFORM_NE_RANGE(a, d);
    IUTEST_ASSUME_NE_RANGE(a, d);

#if IUTEST_HAS_INITIALIZER_LIST
    IUTEST_ASSERT_NE_RANGE(::std::initializer_list<int>({0, 1, 2, 3, 0}), a);
#if IUTEST_HAS_AUTO
    auto il = {1, 1, 2, 3, 4};
    IUTEST_ASSERT_NE_RANGE(il, a);
#endif
#endif
}

IUTEST(AssertionTest, STRIN)
{
    const char test[] = "test";
    ::std::string str = test;
    IUTEST_ASSERT_STRIN("tes", test);
    IUTEST_EXPECT_STRIN("tes", test);
    IUTEST_INFORM_STRIN("tes", test);
    IUTEST_ASSUME_STRIN("tes", test);

    IUTEST_ASSERT_STRIN("test", test);
    IUTEST_EXPECT_STRIN("test", test);
    IUTEST_INFORM_STRIN("test", test);
    IUTEST_ASSUME_STRIN("test", test);

    IUTEST_ASSERT_STRIN("tes", str);
    IUTEST_EXPECT_STRIN("tes", str);
    IUTEST_INFORM_STRIN("tes", str);
    IUTEST_ASSUME_STRIN("tes", str);
}

IUTEST(AssertionTest, STRNOTIN)
{
    const char test[] = "test";
    const char* null = NULL;
    ::std::string str = test;
    IUTEST_ASSERT_STRNOTIN("Tes", test);
    IUTEST_EXPECT_STRNOTIN("Tes", test);
    IUTEST_INFORM_STRNOTIN("Tes", test);
    IUTEST_ASSUME_STRNOTIN("Tes", test);

    IUTEST_ASSERT_STRNOTIN("Tes", str);
    IUTEST_EXPECT_STRNOTIN("Tes", str);
    IUTEST_INFORM_STRNOTIN("Tes", str);
    IUTEST_ASSUME_STRNOTIN("Tes", str);

    IUTEST_ASSERT_STRNOTIN(null, test);
    IUTEST_EXPECT_STRNOTIN(null, test);
    IUTEST_INFORM_STRNOTIN(null, test);
    IUTEST_ASSUME_STRNOTIN(null, test);
}

IUTEST(AssertionTest, STRLNEQ)
{
    const char test[] = "test";
    IUTEST_ASSERT_STRLNEQ(4, test);
    IUTEST_EXPECT_STRLNEQ(4, test);
    IUTEST_INFORM_STRLNEQ(4, test);
    IUTEST_ASSUME_STRLNEQ(4, test);
}

#if IUTEST_HAS_REGEX

IUTEST(AssertionTest, MATCHES_REGEXEQ)
{
    const char test[] = "te0123st";
    IUTEST_ASSERT_MATCHES_REGEXEQ("te[0-9]*st", test);
    IUTEST_EXPECT_MATCHES_REGEXEQ("te[0-9]*st", test);
    IUTEST_INFORM_MATCHES_REGEXEQ("te[0-9]*st", test);
    IUTEST_ASSUME_MATCHES_REGEXEQ("te[0-9]*st", test);
}

IUTEST(AssertionTest, MATCHES_REGEXNE)
{
    const char test[] = "te0123sta";
    IUTEST_ASSERT_MATCHES_REGEXNE("te[0-9]*st", test);
    IUTEST_EXPECT_MATCHES_REGEXNE("te[0-9]*st", test);
    IUTEST_INFORM_MATCHES_REGEXNE("te[0-9]*st", test);
    IUTEST_ASSUME_MATCHES_REGEXNE("te[0-9]*st", test);
}

IUTEST(AssertionTest, CONTAINS_REGEXEQ)
{
    const char test[] = "te0123sta";
    IUTEST_ASSERT_CONTAINS_REGEXEQ("te[0-9]*st", test);
    IUTEST_EXPECT_CONTAINS_REGEXEQ("te[0-9]*st", test);
    IUTEST_INFORM_CONTAINS_REGEXEQ("te[0-9]*st", test);
    IUTEST_ASSUME_CONTAINS_REGEXEQ("te[0-9]*st", test);
}

IUTEST(AssertionTest, CONTAINS_REGEXNE)
{
    const char test[] = "te01q23st";
    IUTEST_ASSERT_CONTAINS_REGEXNE("te[0-9]*st", test);
    IUTEST_EXPECT_CONTAINS_REGEXNE("te[0-9]*st", test);
    IUTEST_INFORM_CONTAINS_REGEXNE("te[0-9]*st", test);
    IUTEST_ASSUME_CONTAINS_REGEXNE("te[0-9]*st", test);
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

