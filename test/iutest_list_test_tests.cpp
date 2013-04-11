//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_list_test_tests.cpp
 * @brief		list test ƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
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
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	{
#if !defined(IUTEST_USE_GTEST)
		Logger logger;
		::iutest::detail::iuConsole::SetLogger(&logger);
#endif
		::iutest::IUTEST_FLAG(list_tests) = true;
		int ret = IUTEST_RUN_ALL_TESTS();

#if !defined(IUTEST_USE_GTEST)
		::iutest::detail::iuConsole::SetLogger(NULL);
		IUTEST_ASSERT_STREQ(list_test_str, logger.c_str())
			<< ::iutest::AssertionReturn<int>(1);
#endif
		if( ret != 0 ) return 1;
	}
#if !defined(IUTEST_USE_GTEST)
	{
		Logger logger;
		::iutest::detail::iuConsole::SetLogger(&logger);

		::iutest::IUTEST_FLAG(list_tests) = false;
		::iutest::IUTEST_FLAG(list_tests_with_where) = true;
		int ret = IUTEST_RUN_ALL_TESTS();

		::iutest::detail::iuConsole::SetLogger(NULL);
		IUTEST_ASSERT_STREQ(list_test_with_where_str, logger.c_str())
			<< ::iutest::AssertionReturn<int>(1);
		if( ret != 0 ) return 1;
	}
#endif	
	return 0;
}

