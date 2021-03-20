//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        string_assertion_tests.cpp
 * @brief       string compare assertion test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST

namespace string_assertion_test
{

template<typename T>
struct text
{
    static const T* test;
    static const T* Test;
    static const T* host;
};
template<> const char*      text<char>::test = "test";
template<> const char*      text<char>::Test = "Test";
template<> const char*      text<char>::host = "host";

template<> const wchar_t*   text<wchar_t>::test = L"test";
template<> const wchar_t*   text<wchar_t>::Test = L"Test";
template<> const wchar_t*   text<wchar_t>::host = L"host";

#if IUTEST_HAS_CHAR16_T
template<> const char16_t*  text<char16_t>::test = u"test";
template<> const char16_t*  text<char16_t>::Test = u"Test";
template<> const char16_t*  text<char16_t>::host = u"host";
#endif

#if IUTEST_HAS_CHAR32_T
template<> const char32_t*  text<char32_t>::test = U"test";
template<> const char32_t*  text<char32_t>::Test = U"Test";
template<> const char32_t*  text<char32_t>::host = U"host";
#endif

template<typename T>
class StrTest : public ::iutest::Test
{
public:
    typedef text<T> Text;
    typedef ::std::basic_string< T, ::std::char_traits<T>, ::std::allocator<T> > String;
};

template<typename T>
class StrCaseTest : public StrTest<T> {};

typedef ::iutest::Types<char, wchar_t
#if IUTEST_HAS_CHAR16_T
    , char16_t
#endif
#if IUTEST_HAS_CHAR32_T
    , char32_t
#endif
    > StrTestTypes;
typedef ::iutest::Types<char, wchar_t> StrCaseTestTypes;

IUTEST_TYPED_TEST_SUITE(StrTest, StrTestTypes);
IUTEST_TYPED_TEST_SUITE(StrCaseTest, StrCaseTestTypes);

IUTEST_TYPED_TEST(StrTest, EqNull)
{
    TypeParam* p=NULL;
    IUTEST_INFORM_STREQ(NULL, p);
    IUTEST_EXPECT_STREQ(NULL, p);
    IUTEST_ASSERT_STREQ(NULL, p);
}

IUTEST_TYPED_TEST(StrTest, NeNull_R)
{
    IUTEST_INFORM_STRNE(TestFixture::Text::test, NULL);
    IUTEST_EXPECT_STRNE(TestFixture::Text::test, NULL);
    IUTEST_ASSERT_STRNE(TestFixture::Text::test, NULL);
}

IUTEST_TYPED_TEST(StrTest, NeNull_L)
{
    IUTEST_INFORM_STRNE(NULL, TestFixture::Text::test);
    IUTEST_EXPECT_STRNE(NULL, TestFixture::Text::test);
    IUTEST_ASSERT_STRNE(NULL, TestFixture::Text::test);
}

IUTEST_TYPED_TEST(StrTest, EqRaw)
{
    const TypeParam* p = TestFixture::Text::test;
    IUTEST_INFORM_STREQ(TestFixture::Text::test, p);
    IUTEST_EXPECT_STREQ(TestFixture::Text::test, p);
    IUTEST_ASSERT_STREQ(TestFixture::Text::test, p);
}

IUTEST_TYPED_TEST(StrTest, StrNeRaw)
{
    const TypeParam* p = TestFixture::Text::test;
    IUTEST_INFORM_STRNE(TestFixture::Text::Test, p);
    IUTEST_EXPECT_STRNE(TestFixture::Text::Test, p);
    IUTEST_ASSERT_STRNE(TestFixture::Text::Test, p);
}

IUTEST_TYPED_TEST(StrTest, EqString)
{
    typename TestFixture::String test1 = TestFixture::Text::test;
    typename TestFixture::String test2 = TestFixture::Text::test;
    IUTEST_INFORM_STREQ(test1, TestFixture::Text::test);
    IUTEST_INFORM_STREQ(test1, test2);
    IUTEST_INFORM_STREQ(TestFixture::Text::test, test2);

    IUTEST_EXPECT_STREQ(test1, TestFixture::Text::test);
    IUTEST_EXPECT_STREQ(test1, test2);
    IUTEST_EXPECT_STREQ(TestFixture::Text::test, test2);

    IUTEST_ASSERT_STREQ(test1, TestFixture::Text::test);
    IUTEST_ASSERT_STREQ(test1, test2);
    IUTEST_ASSERT_STREQ(TestFixture::Text::test, test2);
}

IUTEST_TYPED_TEST(StrTest, NeString)
{
    typename TestFixture::String test = TestFixture::Text::test;
    typename TestFixture::String Test = TestFixture::Text::Test;
    IUTEST_INFORM_STRNE(test, Test);
    IUTEST_INFORM_STRNE(TestFixture::Text::test, Test);
    IUTEST_INFORM_STRNE(test, TestFixture::Text::Test);

    IUTEST_EXPECT_STRNE(test, Test);
    IUTEST_EXPECT_STRNE(TestFixture::Text::test, Test);
    IUTEST_EXPECT_STRNE(test, TestFixture::Text::Test);

    IUTEST_ASSERT_STRNE(test, Test);
    IUTEST_ASSERT_STRNE(TestFixture::Text::test, Test);
    IUTEST_ASSERT_STRNE(test, TestFixture::Text::Test);
}

IUTEST_TYPED_TEST(StrCaseTest, EqNull)
{
    TypeParam* p=NULL;
    IUTEST_INFORM_STRCASEEQ(NULL, p);
    IUTEST_EXPECT_STRCASEEQ(NULL, p);
    IUTEST_ASSERT_STRCASEEQ(NULL, p);
}

IUTEST_TYPED_TEST(StrCaseTest, NeNull_R)
{
    IUTEST_INFORM_STRCASENE(TestFixture::Text::test, NULL);
    IUTEST_EXPECT_STRCASENE(TestFixture::Text::test, NULL);
    IUTEST_ASSERT_STRCASENE(TestFixture::Text::test, NULL);
}

IUTEST_TYPED_TEST(StrCaseTest, NeNull_L)
{
    IUTEST_INFORM_STRCASENE(NULL, TestFixture::Text::test);
    IUTEST_EXPECT_STRCASENE(NULL, TestFixture::Text::test);
    IUTEST_ASSERT_STRCASENE(NULL, TestFixture::Text::test);
}

IUTEST_TYPED_TEST(StrCaseTest, EqRaw)
{
    const TypeParam* p = TestFixture::Text::test;
    IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, p);
    IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, p);
    IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, p);
}

IUTEST_TYPED_TEST(StrCaseTest, CaseEqRaw)
{
    const TypeParam* p = TestFixture::Text::test;
    IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::Test, p);
    IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::Test, p);
    IUTEST_INFORM_STRCASEEQ(TestFixture::Text::Test, p);
}

IUTEST_TYPED_TEST(StrCaseTest, NeRaw)
{
    const TypeParam* p = TestFixture::Text::test;
    IUTEST_ASSERT_STRCASENE(TestFixture::Text::host, p);
    IUTEST_EXPECT_STRCASENE(TestFixture::Text::host, p);
    IUTEST_INFORM_STRCASENE(TestFixture::Text::host, p);
}

IUTEST_TYPED_TEST(StrCaseTest, EqString)
{
    typename TestFixture::String test1 = TestFixture::Text::test;
    typename TestFixture::String test2 = TestFixture::Text::test;
    IUTEST_INFORM_STRCASEEQ(test1, TestFixture::Text::test);
    IUTEST_INFORM_STRCASEEQ(test1, test2);
    IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, test2);

    IUTEST_EXPECT_STRCASEEQ(test1, TestFixture::Text::test);
    IUTEST_EXPECT_STRCASEEQ(test1, test2);
    IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, test2);

    IUTEST_ASSERT_STRCASEEQ(test1, TestFixture::Text::test);
    IUTEST_ASSERT_STRCASEEQ(test1, test2);
    IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, test2);
}

IUTEST_TYPED_TEST(StrCaseTest, CaseEqString)
{
    typename TestFixture::String test = TestFixture::Text::test;
    typename TestFixture::String Test = TestFixture::Text::Test;
    IUTEST_INFORM_STRCASEEQ(Test, TestFixture::Text::test);
    IUTEST_INFORM_STRCASEEQ(Test, test);
    IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, Test);

    IUTEST_EXPECT_STRCASEEQ(Test, TestFixture::Text::test);
    IUTEST_EXPECT_STRCASEEQ(Test, test);
    IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, Test);

    IUTEST_ASSERT_STRCASEEQ(Test, TestFixture::Text::test);
    IUTEST_ASSERT_STRCASEEQ(Test, test);
    IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, Test);
}

IUTEST_TYPED_TEST(StrCaseTest, NeString)
{
    typename TestFixture::String test = TestFixture::Text::test;
    typename TestFixture::String host = TestFixture::Text::host;
    IUTEST_INFORM_STRCASENE(host, TestFixture::Text::test);
    IUTEST_INFORM_STRCASENE(host, test);
    IUTEST_INFORM_STRCASENE(TestFixture::Text::test, host);

    IUTEST_EXPECT_STRCASENE(host, TestFixture::Text::test);
    IUTEST_EXPECT_STRCASENE(host, test);
    IUTEST_EXPECT_STRCASENE(TestFixture::Text::test, host);

    IUTEST_ASSERT_STRCASENE(host, TestFixture::Text::test);
    IUTEST_ASSERT_STRCASENE(host, test);
    IUTEST_ASSERT_STRCASENE(TestFixture::Text::test, host);
}

}   // end of namespace string_assertion_test

#endif
