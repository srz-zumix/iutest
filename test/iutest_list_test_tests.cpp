//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_list_test_tests.cpp
 * @brief		list test テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

class Logger : public ::iutest::detail::iuLogger
{
	::std::string m_log;
public:
	virtual void voutput(const char* fmt, va_list va)
	{
		char buf[256];
		vsprintf(buf, fmt, va);
		m_log += buf;
		::iutest::detail::iuConsole::voutput(fmt, va);
	}
public:
	const char* c_str(void) const { return m_log.c_str(); }
};

#endif

IUTEST(Test, A)
{
}

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE(TypedTest, int);

IUTEST_TYPED_TEST(TypedTest, A)
{
}

#endif

const char list_test_str[] = 
#if IUTEST_HAS_TYPED_TEST
"2 tests from 2 testcase\n"
#else
"1 tests from 1 testcase\n"
#endif
"Test\n"
"  A\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0\n"
"  A\n"
#endif
;

const char list_test_with_where_str[] =
#if IUTEST_HAS_TYPED_TEST
"2 tests from 2 testcase\n"
#else
"1 tests from 1 testcase\n"
#endif
"Test\n"
"  A\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0, where TypeParam = int\n"
"  A\n"
#endif
;

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],   cmd }
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	(void)argc;
	(void)argv;
	{
		int targc = 2;
		DECAL_ARGV("--gtest_list_tests");
		IUTEST_INIT(&targc, targv);

#if !defined(IUTEST_USE_GTEST)
		Logger logger;
		::iutest::detail::iuConsole::SetLogger(&logger);
#endif
		IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(list_tests) );
		const int ret = IUTEST_RUN_ALL_TESTS();

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
		::iutest::detail::iuConsole::SetLogger(NULL);
		IUTEST_ASSERT_STREQ(list_test_str, logger.c_str())
			<< ::iutest::AssertionReturn<int>(1);
#endif
		if( ret != 0 ) return 1;
	}
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
	{
		int targc = 2;
		DECAL_ARGV("--iutest_list_tests_with_where");
		IUTEST_INIT(&targc, targv);

		Logger logger;
		::iutest::detail::iuConsole::SetLogger(&logger);

		IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(list_tests) );
		IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(list_tests_with_where) );
		const int ret = IUTEST_RUN_ALL_TESTS();

		::iutest::detail::iuConsole::SetLogger(NULL);
		IUTEST_ASSERT_STREQ(list_test_with_where_str, logger.c_str())
			<< ::iutest::AssertionReturn<int>(1);
		if( ret != 0 ) return 1;
	}
#endif	
	return 0;
}

