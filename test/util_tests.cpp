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
#include "iutest.hpp"

IUTEST(UtilTest, Find)
{
    const ::iutest::TestSuite* testsuite = ::iuutil::FindTestSuite("UtilTest");
    IUTEST_EXPECT_NOTNULL(testsuite);
    IUTEST_EXPECT_NOTNULL(::iuutil::FindTestInfo("UtilTest", "Find"));

    const ::iutest::TestSuite* null_testsuite = NULL;
    const char* null_testsuite_name = NULL;
    IUTEST_EXPECT_NULL(::iuutil::FindTestSuite(NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestSuite("UtilTestXXX"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(null_testsuite, "Find"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(null_testsuite_name, "Find"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo(testsuite, NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTest", NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTest", "FindXXX"));
    IUTEST_EXPECT_NULL(::iuutil::FindTestInfo("UtilTestXXX", "Find"));
}

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, ParamTest, ::iutest::Values(0, 1));
IUTEST_INSTANTIATE_TEST_SUITE_P(B, ParamTest, ::iutest::Values(0, 1, 10));

#endif

IUTEST(UtilTest, FindParamTest)
{
    IUTEST_EXPECT_NULL(::iuutil::FindParamTestSuite(NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindParamTestSuite("UnitTest"));

#if IUTEST_HAS_PARAM_TEST
    const ::iutest::TestSuite* find_testsuite = ::iuutil::FindParamTestSuite("ParamTest");
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    const ::iutest::TestInfo* find_testinfo = ::iuutil::FindParamTestInfo(find_testsuite, "Test");
    IUTEST_EXPECT_NOTNULL(find_testinfo);
    find_testinfo = ::iuutil::FindParamTestInfo(find_testsuite, "Test", find_testinfo);
    IUTEST_EXPECT_NOTNULL(find_testinfo);
    find_testinfo = ::iuutil::FindParamTestInfo(find_testsuite, "Test", find_testinfo);
    IUTEST_EXPECT_NULL(find_testinfo);

    IUTEST_EXPECT_NULL(::iuutil::FindParamTestInfo(NULL, "Test"));
    IUTEST_EXPECT_NULL(::iuutil::FindParamTestInfo(find_testsuite, NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindParamTestInfo(find_testsuite, "FindParamTest"));


    find_testsuite = ::iuutil::FindParamTestSuite("ParamTest", find_testsuite);
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    find_testsuite = ::iuutil::FindParamTestSuite("ParamTest", find_testsuite);
    IUTEST_EXPECT_NULL(find_testsuite);
#endif
}

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

typedef ::iutest::Types<int, float> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Test)
{
}

#endif

IUTEST(UtilTest, FindTypedTest)
{
    IUTEST_EXPECT_NULL(::iuutil::FindTypedTestSuite(NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindTypedTestSuite("UnitTest"));

#if IUTEST_HAS_TYPED_TEST
    const ::iutest::TestSuite* find_testsuite = ::iuutil::FindTypedTestSuite("TypedTest");
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    find_testsuite = ::iuutil::FindTypedTestSuite("TypedTest", find_testsuite);
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    find_testsuite = ::iuutil::FindTypedTestSuite("TypedTest", find_testsuite);
    IUTEST_EXPECT_NULL(find_testsuite);
#endif
}

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(TypeParamTest);
IUTEST_TYPED_TEST_P(TypeParamTest, Test)
{
}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, Test);

typedef ::iutest::Types<int, float> TypeParamTestTypes;
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My1, TypeParamTest, TypeParamTestTypes);

#endif

IUTEST(UtilTest, FindParamTypedTest)
{
    IUTEST_EXPECT_NULL(::iuutil::FindParamTypedTestSuite(NULL));
    IUTEST_EXPECT_NULL(::iuutil::FindParamTypedTestSuite("UnitTest"));

#if IUTEST_HAS_TYPED_TEST_P
    const ::iutest::TestSuite* find_testsuite = ::iuutil::FindParamTypedTestSuite("TypeParamTest");
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    find_testsuite = ::iuutil::FindParamTypedTestSuite("TypeParamTest", find_testsuite);
    IUTEST_EXPECT_NOTNULL(find_testsuite);
    find_testsuite = ::iuutil::FindParamTypedTestSuite("TypeParamTest", find_testsuite);
    IUTEST_EXPECT_NULL(find_testsuite);
#endif
}

IUTEST(UtilTest, TestSuiteNameRemoveIndexName)
{
    IUTEST_EXPECT_STREQ( "pkg.TestSuite" , ::iuutil::TestSuiteNameRemoveIndexName("pkg.TestSuite") );
    IUTEST_EXPECT_STREQ( "pkg.TestSuite" , ::iuutil::TestSuiteNameRemoveIndexName("pkg.TestSuite/0") );
    IUTEST_EXPECT_STREQ( "TestSuite" , ::iuutil::TestSuiteNameRemoveIndexName("TestSuite") );
}

IUTEST(UtilTest, TestSuiteNameRemoveInstantiateAndIndexName)
{
    IUTEST_EXPECT_STREQ( "pkg.TestSuite" , ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName("pkg.prefix/TestSuite") );
    IUTEST_EXPECT_STREQ( "pkg.TestSuite" , ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName("pkg.prefix/TestSuite/0") );
    IUTEST_EXPECT_STREQ( "TestSuite" , ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName("TestSuite") );
    IUTEST_EXPECT_STREQ( "TestSuite" , ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName("prefix/TestSuite") );
    IUTEST_EXPECT_STREQ( "TestSuite" , ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName("prefix/TestSuite/0") );
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

