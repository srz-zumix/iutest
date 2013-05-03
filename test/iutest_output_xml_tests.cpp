//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_filter_tests.cpp
 * @brief		filter ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

class FileIO : public ::iutest::StringStreamFile
{
public:
	static ::std::string s_io;

	virtual void Close()
	{
		s_io = ss.str();
	}
};

::std::string FileIO::s_io;

IUTEST_FILESYSTEM_INSTANTIATE(FileIO);

#endif

IUTEST(Test, Fail)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Fail, Test)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_EQ(3, 3);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);

#if !defined(IUTEST_USE_GTEST)
	{
		::iutest::DefaultXmlGeneratorListener* listener = new ::iutest::DefaultXmlGeneratorListener();
		listener->SetFilePath("test.xml");
		::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
		listeners.Append(listener);
	}
#endif

	{
		::iutest::IUTEST_FLAG(filter) = "-*Fail*";
		int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT_EQ(-1, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
		IUTEST_ASSERT_NE(-1, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
		
		FileIO::s_io.clear();
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "*Fail*";
		int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT_NE(-1, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
		IUTEST_ASSERT_EQ(-1, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

		FileIO::s_io.clear();
#endif
	}
	printf("*** Successful ***\n");
	return 0;
}
