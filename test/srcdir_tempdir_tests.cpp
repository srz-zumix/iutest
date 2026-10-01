//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        srcdir_tempdir_tests.cpp
 * @brief       ::iutest::SrcDir() / ::iutest::TempDir() tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TEMPDIR || IUTEST_HAS_SRCDIR

namespace
{

bool EndsWithPathSeparator(const ::std::string& path)
{
    if( path.empty() )
    {
        return false;
    }
    const char c = *path.rbegin();
    return c == '/' || c == '\\';
}

#if IUTEST_HAS_SRCDIR && !defined(IUTEST_USE_GTEST)

::std::string RemoveTrailingPathSeparator(const ::std::string& path)
{
    if( EndsWithPathSeparator(path) )
    {
        return path.substr(0, path.length() - 1);
    }
    return path;
}

#endif

}   // namespace

#endif

#if IUTEST_HAS_TEMPDIR

IUTEST(TempDirTest, Default)
{
    ::iutest::internal::posix::PutEnv("TEST_TMPDIR=");
#if defined(IUTEST_OS_WINDOWS)
    ::iutest::internal::posix::PutEnv("TEMP=");
#else
    ::iutest::internal::posix::PutEnv("TMPDIR=");
#endif

    const ::std::string dir = ::iutest::TempDir();
    IUTEST_EXPECT_FALSE(dir.empty());
    IUTEST_EXPECT_TRUE(EndsWithPathSeparator(dir));
}

IUTEST(TempDirTest, EnvironmentVariable)
{
    IUTEST_ASSUME_NE( -1, ::iutest::internal::posix::PutEnv("TEST_TMPDIR=/iutest_tempdir_test") );
    IUTEST_EXPECT_EQ("/iutest_tempdir_test/", ::iutest::TempDir());

    IUTEST_ASSUME_NE( -1, ::iutest::internal::posix::PutEnv("TEST_TMPDIR=/iutest_tempdir_test/") );
    IUTEST_EXPECT_EQ("/iutest_tempdir_test/", ::iutest::TempDir());

    ::iutest::internal::posix::PutEnv("TEST_TMPDIR=");
}

#endif

#if IUTEST_HAS_SRCDIR

IUTEST(SrcDirTest, Default)
{
    ::iutest::internal::posix::PutEnv("TEST_SRCDIR=");

    const ::std::string dir = ::iutest::SrcDir();
    IUTEST_EXPECT_FALSE(dir.empty());
    IUTEST_EXPECT_TRUE(EndsWithPathSeparator(dir));

#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_EQ( ::iutest::internal::FilePath::GetCurrentDir().string()
        , RemoveTrailingPathSeparator(dir) );
#endif
}

IUTEST(SrcDirTest, EnvironmentVariable)
{
    IUTEST_ASSUME_NE( -1, ::iutest::internal::posix::PutEnv("TEST_SRCDIR=/iutest_srcdir_test") );
    IUTEST_EXPECT_EQ("/iutest_srcdir_test/", ::iutest::SrcDir());

    IUTEST_ASSUME_NE( -1, ::iutest::internal::posix::PutEnv("TEST_SRCDIR=/iutest_srcdir_test/") );
    IUTEST_EXPECT_EQ("/iutest_srcdir_test/", ::iutest::SrcDir());

    ::iutest::internal::posix::PutEnv("TEST_SRCDIR=");
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
