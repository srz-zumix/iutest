//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_filepath_tests.cpp
 * @brief		iutest filepath test
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
#include "../include/iutest.hpp"
#include "../include/internal/iutest_filepath.hpp"

#if !defined(IUTEST_USE_GTEST)
IUTEST(FilePath, GetExecFilePath)
{
	::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetExecFilePath();
	IUTEST_ASSERT_FALSE(path.IsEmpty());
	IUTEST_ASSERT_TRUE (path.FileOrDirectoryExists());
}
#endif

IUTEST(FilePath, IsDirectory)
{
	::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetCurrentDir();
	IUTEST_ASSERT_FALSE(path.IsEmpty());
	IUTEST_ASSERT_TRUE (path.DirectoryExists());
}

IUTEST(FilePath, RemoveExtension)
{
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_ASSERT_EQ("test", path.RemoveExtension());
		IUTEST_ASSERT_EQ("test.exe", path.RemoveExtension("bin"));
		IUTEST_ASSERT_EQ("test", path.RemoveExtension("exe"));
	}
	{
		::iutest::internal::FilePath path("test.exe.bin");
		IUTEST_ASSERT_EQ("test.exe", path.RemoveExtension());
		IUTEST_ASSERT_EQ("test.exe", path.RemoveExtension("bin"));
		IUTEST_ASSERT_EQ("test.exe.bin", path.RemoveExtension("exe"));
	}
}

IUTEST(FilePath, RemoveFileName)
{
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_ASSERT_EQ( ::iutest::internal::FilePath::GetRelativeCurrentDir(), path.RemoveFileName());
	}
	{
		::iutest::internal::FilePath path("test/test.exe");
		IUTEST_ASSERT_EQ("test/", path.RemoveFileName());
	}
}

IUTEST(FilePath, RemoveDirectoryName)
{
	{
		::iutest::internal::FilePath path("test.exe");
		IUTEST_ASSERT_EQ("test.exe", path.RemoveDirectoryName());
	}
	{
		::iutest::internal::FilePath path("test/test.exe");
		IUTEST_ASSERT_EQ("test.exe", path.RemoveDirectoryName());
	}
}
