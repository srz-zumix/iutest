//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        file_system_tests.cpp
 * @brief       iutest file system test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

static bool is_call_create = false;
static bool is_call_delete = false;

class TestFileSystem : public ::iutest::detail::IFileSystem
{
private:
    virtual ::iutest::IFile* Create(void) IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        is_call_create = true;
        return NULL;
    }
    virtual void Delete(::iutest::IFile*) IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        is_call_delete = true;
    }
};

int RegisterFileSystem()
{
    static TestFileSystem s_file_system;
    return 0;
}

#endif


#ifndef IUTEST_EXPECT_NO_THROW
#  define IUTEST_EXPECT_NO_THROW void
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if !defined(IUTEST_USE_GTEST)
    {
        IUTEST_EXPECT_NULL(::iutest::detail::IFileSystem::New());
        ::std::string str;
        IUTEST_EXPECT_FALSE(::iutest::detail::IFileSystem::ReadAll("iutest_file_system_test.cpp", str));
        IUTEST_EXPECT_NO_THROW(::iutest::detail::IFileSystem::Free(NULL));
    }

    RegisterFileSystem();

    IUTEST_INIT(&argc, argv);
    ::iutest::IUTEST_FLAG(output) = "xml:test.xml";

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return ret;

    IUTEST_EXPECT_TRUE(is_call_create);
    IUTEST_EXPECT_FALSE(is_call_delete);

    IUTEST_EXPECT_NO_THROW(::iutest::detail::IFileSystem::Free(NULL));
    IUTEST_EXPECT_TRUE(is_call_delete);

    return ::iutest::UnitTest::GetInstance()->Failed() ? 1 : 0;
#else
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
#endif
}
