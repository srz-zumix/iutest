//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        original_working_dir_tests.cpp
 * @brief       original working directory tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
 */
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) \
    && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
#  include <direct.h>
#elif IUTEST_HAS_HDR_UNISTD
#  include <unistd.h>
#endif

namespace
{

::std::string initialization_dir;

::std::string GetWorkingDirectory()
{
#if defined(IUTEST_USE_GTEST)
    return ::iutest::internal::FilePath::GetCurrentDir().string();
#else
    char cwd[IUTEST_MAX_PATH] = { 0 };
    const char* const dir = ::iutest::internal::posix::GetCWD(cwd, sizeof(cwd));
    return dir != NULL ? dir : "";
#endif
}

#if (defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) \
    && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)) \
    || (IUTEST_HAS_HDR_UNISTD && !defined(__arm__))

int ChangeDirectory(const char* path)
{
#if defined(IUTEST_OS_WINDOWS)
    return ::_chdir(path);
#else
    return ::chdir(path);
#endif
}

class OriginalWorkingDir : public ::iutest::Test
{
protected:
    virtual void SetUp() IUTEST_CXX_OVERRIDE
    {
        const ::iutest::internal::FilePath current(GetWorkingDirectory());
        IUTEST_ASSUME_TRUE(current.IsAbsolutePath());
        m_restore_dir = current.string();
        IUTEST_ASSERT_EQ(0, ChangeDirectory(".."));
        IUTEST_ASSUME_STRNE(initialization_dir.c_str(), GetWorkingDirectory().c_str());
    }

    virtual void TearDown() IUTEST_CXX_OVERRIDE
    {
        if( !m_restore_dir.empty() )
        {
            IUTEST_EXPECT_EQ(0, ChangeDirectory(m_restore_dir.c_str()));
        }
    }

private:
    ::std::string m_restore_dir;
};

IUTEST_F(OriginalWorkingDir, AfterChangingDirectory)
{
    const char* const original = ::iutest::UnitTest::GetInstance()->original_working_dir();
    IUTEST_EXPECT_STREQ(initialization_dir.c_str(), original);
}

IUTEST_F(OriginalWorkingDir, AfterRepeatedInitialization)
{
    const char* const original = ::iutest::UnitTest::GetInstance()->original_working_dir();
    int argc = 1;
    char name[] = "original_working_dir_tests";
    char* argv[] = { name, NULL };
    IUTEST_INIT(&argc, argv);
    IUTEST_EXPECT_STREQ(initialization_dir.c_str(), ::iutest::UnitTest::GetInstance()->original_working_dir());
    IUTEST_EXPECT_STREQ(initialization_dir.c_str(), original);
}

#endif

IUTEST(OriginalWorkingDirTest, InitializationDirectory)
{
    IUTEST_EXPECT_FALSE(initialization_dir.empty());
    IUTEST_EXPECT_STREQ(initialization_dir.c_str(), ::iutest::UnitTest::GetInstance()->original_working_dir());
}

}   // namespace

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    initialization_dir = GetWorkingDirectory();
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
