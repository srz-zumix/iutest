//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_file_system_tests.cpp
 * @brief		iutest file system test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

static bool is_call_create = false;
static bool is_call_delete = false;

void FileSystemCallTest()
{
	IUTEST_EXPECT_TRUE(is_call_create);
	IUTEST_EXPECT_FALSE(is_call_delete);
}

class TestFileSystem : public ::iutest::detail::IFileSystem
{
private:
	virtual ::iutest::IFile* Create(void)
	{
		is_call_create = true;
		return NULL;
	}
	virtual void Delete(::iutest::IFile*)
	{
		is_call_delete = true;
	}
};

static TestFileSystem	s_file_system;

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
	::iutest::IUTEST_FLAG(output) = "xml:test.xml";
	const int ret = IUTEST_RUN_ALL_TESTS();
	if( ret != 0 ) return ret;
	FileSystemCallTest();
	return ::iutest::UnitTest::GetInstance()->Failed() ? 1 : 0;
#else
	return IUTEST_RUN_ALL_TESTS();
#endif
}
