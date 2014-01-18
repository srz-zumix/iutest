//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_scoped_trace_tests.cpp
 * @brief		IUTEST_SCOPED_TRACE 対応テスト
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

IUTEST(ScopedTraceTest, Dummy)
{
	IUTEST_SCOPED_TRACE("FIRST");
	int a=0;
	IUTEST_SCOPED_TRACE("SECOND");
	++a;
	IUTEST_ASSERT_EQ(1, a);
}

IUTEST(ScopedTraceTest, Failed)
{
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(ScopedTraceTest, Test)
{
#if !defined(IUTEST_USE_GTEST)
	Logger logger1, logger2, logger3;
	::iutest::detail::iuConsole::SetLogger(&logger1);
#endif

	{
		IUTEST_SCOPED_TRACE("Test Scope 1");
		IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT_STRIN("Test Scope 1", logger1.c_str());
		::iutest::detail::iuConsole::SetLogger(&logger2);
#endif
		{
			IUTEST_SCOPED_TRACE("Test Scope 2");
			IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
			IUTEST_ASSERT_STRIN("Test Scope 1", logger2.c_str());
			IUTEST_ASSERT_STRIN("Test Scope 2", logger2.c_str());
			::iutest::detail::iuConsole::SetLogger(&logger3);
#endif
		}
	}

	IUTEST_SCOPED_TRACE("Test Scope 3");
	IUTEST_EXPECT_EQ(0, 1);

#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT_STRIN("Test Scope 3", logger3.c_str());
	::iutest::detail::iuConsole::SetLogger(NULL);
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
	// 失敗テストを含むので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	
	const int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
	printf("*** Successful ***\n");
	return 0;
}
