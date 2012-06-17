//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_string_assertion_tests.cpp
 * @brief		iutest 文字列比較 アサーション test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_switch.hpp"

namespace strtest
{

template<typename T>
struct text
{
	static const T* test;
	static const T* Test;
	static const T* host;
};
template<> const char* 		text<char>::test = "test";
template<> const char* 		text<char>::Test = "Test";
template<> const char*		text<char>::host = "host";

template<> const wchar_t*	text<wchar_t>::test = L"test";
template<> const wchar_t*	text<wchar_t>::Test = L"Test";
template<> const wchar_t*	text<wchar_t>::host = L"host";

#if IUTEST_HAS_CHAR16_T
template<> const char16_t*	text<char16_t>::test = u"test";
template<> const char16_t*	text<char16_t>::Test = u"Test";
template<> const char16_t*	text<char16_t>::host = u"host";
#endif
	
#if IUTEST_HAS_CHAR32_T
template<> const char32_t*	text<char32_t>::test = U"test";
template<> const char32_t*	text<char32_t>::Test = U"Test";
template<> const char32_t*	text<char32_t>::host = U"host";
#endif

	template<typename T>
class StrTest : public ::iutest::Test
{
public:
	typedef text<T>	Text;
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

IUTEST_TYPED_TEST_CASE(StrTest, StrTestTypes);
IUTEST_TYPED_TEST_CASE(StrCaseTest, StrCaseTestTypes);

IUTEST_TYPED_TEST(StrTest, Null)
{
	TypeParam* p=NULL;
	IUTEST_ASSERT_STREQ(NULL, p);
	IUTEST_EXPECT_STREQ(NULL, p);
	IUTEST_INFORM_STREQ(NULL, p);

	IUTEST_ASSERT_STRNE(TestFixture::Text::test, NULL);
	IUTEST_EXPECT_STRNE(TestFixture::Text::test, NULL);
	IUTEST_INFORM_STRNE(TestFixture::Text::test, NULL);

	IUTEST_ASSERT_STRNE(NULL, TestFixture::Text::test);
	IUTEST_EXPECT_STRNE(NULL, TestFixture::Text::test);
	IUTEST_INFORM_STRNE(NULL, TestFixture::Text::test);
}

IUTEST_TYPED_TEST(StrTest, Raw)
{
	const TypeParam* p = TestFixture::Text::test;
	IUTEST_ASSERT_STREQ(TestFixture::Text::test, p);
	IUTEST_EXPECT_STREQ(TestFixture::Text::test, p);
	IUTEST_INFORM_STREQ(TestFixture::Text::test, p);
	
	IUTEST_ASSERT_STRNE(TestFixture::Text::Test, p);
	IUTEST_EXPECT_STRNE(TestFixture::Text::Test, p);
	IUTEST_INFORM_STRNE(TestFixture::Text::Test, p);
}

IUTEST_TYPED_TEST(StrTest, String)
{
	typename TestFixture::String test1 = TestFixture::Text::test;
	typename TestFixture::String test2 = TestFixture::Text::test;
	IUTEST_ASSERT_STREQ(test1, TestFixture::Text::test);
	IUTEST_EXPECT_STREQ(test1, TestFixture::Text::test);
	IUTEST_INFORM_STREQ(test1, TestFixture::Text::test);
	IUTEST_ASSERT_STREQ(test1, test2);
	IUTEST_EXPECT_STREQ(test1, test2);
	IUTEST_INFORM_STREQ(test1, test2);
	IUTEST_ASSERT_STREQ(TestFixture::Text::test, test2);
	IUTEST_EXPECT_STREQ(TestFixture::Text::test, test2);
	IUTEST_INFORM_STREQ(TestFixture::Text::test, test2);

	typename TestFixture::String Test = TestFixture::Text::Test;
	IUTEST_ASSERT_STRNE(test1, Test);
	IUTEST_EXPECT_STRNE(test1, Test);
	IUTEST_INFORM_STRNE(test1, Test);
	IUTEST_ASSERT_STRNE(TestFixture::Text::test, Test);
	IUTEST_EXPECT_STRNE(TestFixture::Text::test, Test);
	IUTEST_INFORM_STRNE(TestFixture::Text::test, Test);
	IUTEST_ASSERT_STRNE(test1, TestFixture::Text::Test);
	IUTEST_EXPECT_STRNE(test1, TestFixture::Text::Test);
	IUTEST_INFORM_STRNE(test1, TestFixture::Text::Test);
}

IUTEST_TYPED_TEST(StrCaseTest, Raw)
{
	const TypeParam* p = TestFixture::Text::test;
	IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, p);
	IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, p);
	IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, p);
	IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::Test, p);
	IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::Test, p);
	IUTEST_INFORM_STRCASEEQ(TestFixture::Text::Test, p);
	
	IUTEST_ASSERT_STRCASENE(TestFixture::Text::host, p);
	IUTEST_EXPECT_STRCASENE(TestFixture::Text::host, p);
	IUTEST_INFORM_STRCASENE(TestFixture::Text::host, p);
}

IUTEST_TYPED_TEST(StrCaseTest, String)
{
	typename TestFixture::String test1 = TestFixture::Text::test;
	typename TestFixture::String test2 = TestFixture::Text::test;
	IUTEST_ASSERT_STRCASEEQ(test1, TestFixture::Text::test);
	IUTEST_EXPECT_STRCASEEQ(test1, TestFixture::Text::test);
	IUTEST_INFORM_STRCASEEQ(test1, TestFixture::Text::test);
	IUTEST_ASSERT_STRCASEEQ(test1, test2);
	IUTEST_EXPECT_STRCASEEQ(test1, test2);
	IUTEST_INFORM_STRCASEEQ(test1, test2);
	IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, test2);
	IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, test2);
	IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, test2);

	typename TestFixture::String Test = TestFixture::Text::Test;
	IUTEST_ASSERT_STRCASEEQ(Test, TestFixture::Text::test);
	IUTEST_EXPECT_STRCASEEQ(Test, TestFixture::Text::test);
	IUTEST_INFORM_STRCASEEQ(Test, TestFixture::Text::test);
	IUTEST_ASSERT_STRCASEEQ(Test, test2);
	IUTEST_EXPECT_STRCASEEQ(Test, test2);
	IUTEST_INFORM_STRCASEEQ(Test, test2);
	IUTEST_ASSERT_STRCASEEQ(TestFixture::Text::test, Test);
	IUTEST_EXPECT_STRCASEEQ(TestFixture::Text::test, Test);
	IUTEST_INFORM_STRCASEEQ(TestFixture::Text::test, Test);
	
	typename TestFixture::String host = TestFixture::Text::host;
	IUTEST_ASSERT_STRCASENE(host, TestFixture::Text::test);
	IUTEST_EXPECT_STRCASENE(host, TestFixture::Text::test);
	IUTEST_INFORM_STRCASENE(host, TestFixture::Text::test);
	IUTEST_ASSERT_STRCASENE(host, test2);
	IUTEST_EXPECT_STRCASENE(host, test2);
	IUTEST_INFORM_STRCASENE(host, test2);
	IUTEST_ASSERT_STRCASENE(TestFixture::Text::test, host);
	IUTEST_EXPECT_STRCASENE(TestFixture::Text::test, host);
	IUTEST_INFORM_STRCASENE(TestFixture::Text::test, host);
}

}

