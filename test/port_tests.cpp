//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        port_tests.cpp
 * @brief       iutest portable function test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2016, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"


IUTEST(PortableTest, SetGetEnv)
{
    const char* env_name = "IUTEST_PORT_TEST_SETENV";
    if( ::iutest::internal::posix::SetEnv(env_name, "test", 0) != 0 ) IUTEST_SKIP();
    IUTEST_ASSERT_STREQ("test", ::iutest::internal::posix::GetEnv(env_name));

    IUTEST_EXPECT_EQ(0, ::iutest::internal::posix::SetEnv(env_name, "hoge", 0));
    IUTEST_ASSERT_STREQ("test", ::iutest::internal::posix::GetEnv(env_name));

    IUTEST_EXPECT_EQ(0, ::iutest::internal::posix::SetEnv(env_name, "hoge", 1));
    IUTEST_ASSERT_STREQ("hoge", ::iutest::internal::posix::GetEnv(env_name));
}

IUTEST(PortableTest, PutGetEnv)
{
    const char* env_name = "IUTEST_PORT_TEST_PUTENV";
    if( ::iutest::internal::posix::PutEnv("IUTEST_PORT_TEST_PUTENV=test") != 0 ) IUTEST_SKIP();
    IUTEST_ASSERT_STREQ("test", ::iutest::internal::posix::GetEnv(env_name));

    IUTEST_EXPECT_NE(-1, ::iutest::internal::posix::PutEnv("IUTEST_PORT_TEST_PUTENV=hoge"));
    IUTEST_ASSERT_STREQ("hoge", ::iutest::internal::posix::GetEnv(env_name));
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

