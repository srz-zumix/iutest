//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        filepath_tests.cpp
 * @brief       iutest filepath test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/internal/iutest_filepath.hpp"

IUTEST(FilePath, Empty)
{
    ::iutest::internal::FilePath path;
    IUTEST_EXPECT_TRUE(path.IsEmpty());
}

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_FILE_STAT
IUTEST(FilePath, GetExecFilePath)
{
    ::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetExecFilePath();
    if(!path.IsEmpty())
    {
        IUTEST_EXPECT_TRUE(path.FileOrDirectoryExists()) << path;
    }
}
#endif

IUTEST(FilePath, DirectoryExists)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_FALSE(path.DirectoryExists());
    }
#if defined(IUTEST_USE_GTEST) || IUTEST_HAS_FILE_STAT
    {
        ::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetCurrentDir();
        IUTEST_EXPECT_FALSE(path.IsEmpty());
        IUTEST_EXPECT_TRUE (path.DirectoryExists());
    }
#endif
}

IUTEST(FilePath, FileOrDirectoryExists)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_FALSE(path.FileOrDirectoryExists());
    }
#if defined(IUTEST_USE_GTEST) || IUTEST_HAS_FILE_STAT
    {
        ::iutest::internal::FilePath path = ::iutest::internal::FilePath::GetCurrentDir();
        IUTEST_EXPECT_FALSE(path.IsEmpty());
        IUTEST_EXPECT_TRUE (path.FileOrDirectoryExists());
    }
#endif
}

IUTEST(FilePath, IsDirectory)
{
    ::iutest::internal::FilePath path;
    IUTEST_EXPECT_FALSE(path.IsDirectory());
}

IUTEST(FilePath, IsRootDirectory)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_FALSE(path.IsRootDirectory());
    }
    {
        ::iutest::internal::FilePath path("path");
        IUTEST_EXPECT_FALSE(path.IsRootDirectory());
    }
    {
#ifdef IUTEST_OS_WINDOWS
        ::iutest::internal::FilePath path("C:\\");
        IUTEST_EXPECT_TRUE(path.IsRootDirectory());
#else
        ::iutest::internal::FilePath path("/");
        IUTEST_EXPECT_TRUE(path.IsRootDirectory());
#endif
    }
}

IUTEST(FilePath, IsAbsolutePath)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_FALSE(path.IsAbsolutePath());
    }
    {
        ::iutest::internal::FilePath path("path");
        IUTEST_EXPECT_FALSE(path.IsAbsolutePath());
    }
}

IUTEST(FilePath, RemoveTrailingPathSeparator)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_EQ("", path.RemoveTrailingPathSeparator());
    }
    {
        ::iutest::internal::FilePath path("path/to/dir/////");
#ifdef IUTEST_OS_WINDOWS
        IUTEST_EXPECT_EQ("path\\to\\dir", path.RemoveTrailingPathSeparator());
#else
        IUTEST_EXPECT_EQ("path/to/dir", path.RemoveTrailingPathSeparator());
#endif
    }
}

IUTEST(FilePath, ConcatPaths)
{
    {
        ::iutest::internal::FilePath a("a");
        ::iutest::internal::FilePath empty;
        IUTEST_EXPECT_EQ("a", ::iutest::internal::FilePath::ConcatPaths(empty, a));
#ifdef IUTEST_OS_WINDOWS
        IUTEST_EXPECT_EQ("a\\", ::iutest::internal::FilePath::ConcatPaths(a, empty));
#else
        IUTEST_EXPECT_EQ("a/", ::iutest::internal::FilePath::ConcatPaths(a, empty));
#endif
    }
    {
        ::iutest::internal::FilePath dir("path/to/dir/////");
        ::iutest::internal::FilePath file("test.text");
#ifdef IUTEST_OS_WINDOWS
        IUTEST_EXPECT_EQ("path\\to\\dir\\test.text", ::iutest::internal::FilePath::ConcatPaths(dir, file));
#else
        IUTEST_EXPECT_EQ("path/to/dir/test.text", ::iutest::internal::FilePath::ConcatPaths(dir, file));
#endif
    }
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(FilePath, GetExtention)
{
    {
        ::iutest::internal::FilePath path;
        IUTEST_EXPECT_EQ("", path.GetExtension());
    }
    {
        ::iutest::internal::FilePath path("test.exe");
        IUTEST_EXPECT_EQ(".exe", path.GetExtension());
    }
    {
        ::iutest::internal::FilePath path("test.exe.txt");
        IUTEST_EXPECT_EQ(".txt", path.GetExtension());
    }
}
#endif

IUTEST(FilePath, RemoveExtension)
{
    {
        ::iutest::internal::FilePath path("test.exe");
        IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension("bin"));
        IUTEST_EXPECT_EQ("test", path.RemoveExtension("exe"));
#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_EQ("test", path.RemoveExtension());
#endif
    }
    {
        ::iutest::internal::FilePath path("test.exe.bin");
        IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension("bin"));
        IUTEST_EXPECT_EQ("test.exe.bin", path.RemoveExtension("exe"));
#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_EQ("test.exe", path.RemoveExtension());
#endif
    }
    {
        ::iutest::internal::FilePath path("test");
        IUTEST_EXPECT_EQ("test", path.RemoveExtension("test"));
        IUTEST_EXPECT_EQ("test", path.RemoveExtension("exe"));
    }
}

IUTEST(FilePath, RemoveFileName)
{
#if !defined(IUTEST_USE_GTEST)
    {
        ::iutest::internal::FilePath path("test.exe");
        IUTEST_EXPECT_EQ( ::iutest::internal::FilePath::GetRelativeCurrentDir(), path.RemoveFileName());
    }
#endif
    {
        ::iutest::internal::FilePath path("test/test.exe");
#ifdef IUTEST_OS_WINDOWS
        const char expected[] = "test\\";
#else
        const char expected[] = "test/";
#endif
        IUTEST_EXPECT_EQ(expected, path.RemoveFileName());
    }
}

IUTEST(FilePath, RemoveDirectoryName)
{
    {
        ::iutest::internal::FilePath path("test.exe");
        IUTEST_EXPECT_EQ("test.exe", path.RemoveDirectoryName());
    }
    {
        ::iutest::internal::FilePath path("test/test.exe");
        IUTEST_EXPECT_EQ("test.exe", path.RemoveDirectoryName());
    }
}

IUTEST(FilePath, Normalize)
{
    ::iutest::internal::FilePath path("path//to///dir////file.txt");
#ifdef IUTEST_OS_WINDOWS
    IUTEST_EXPECT_EQ("path\\to\\dir\\file.txt", path);
#else
    IUTEST_EXPECT_EQ("path/to/dir/file.txt", path);
#endif
}

#if IUTEST_HAS_PRINT_TO

IUTEST(FilePath, PrintTo)
{
    ::iutest::internal::FilePath path("test.exe");
    IUTEST_ASSERT_STREQ("test.exe", ::iutest::PrintToString(path));
}

#endif
