//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        install_failure_signal_handler_tests.cpp
 * @brief       Failure signal handler flag compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"
#include <cstdlib>

#if !defined(IUTEST_USE_GTEST) && (defined(__unix__) || defined(__APPLE__) \
    || (defined(_WIN32) && !defined(_WIN32_WCE)))
#  include <signal.h>
#  define IIUT_TEST_SIGNAL_HANDLER 1
#else
#  define IIUT_TEST_SIGNAL_HANDLER 0
#endif

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000

namespace
{

bool initial_flag;

#if IIUT_TEST_SIGNAL_HANDLER
void ExistingHandler(int) {}
#endif

class FailureSignalFlag : public ::iutest::Test
{
protected:
    virtual void SetUp() IUTEST_CXX_OVERRIDE
    {
        IUTEST_EXPECT_EQ(initial_flag, IUTEST_FLAG_GET(install_failure_signal_handler));
    }
};

}   // namespace

IUTEST_F(FailureSignalFlag, FlagAPI)
{
    IUTEST_FLAG_SET(install_failure_signal_handler, false);
    IUTEST_EXPECT_FALSE(GTEST_FLAG_GET(install_failure_signal_handler));
    GTEST_FLAG_SET(install_failure_signal_handler, true);
    IUTEST_EXPECT_TRUE(IUTEST_FLAG_GET(install_failure_signal_handler));
#if defined(IUTEST_USE_GTEST)
    IUTEST_FLAG_SET(install_failure_signal_handler, initial_flag);
#else
    IUTEST_FLAG_SET(install_failure_signal_handler, !initial_flag);
#endif
}

IUTEST_F(FailureSignalFlag, Restored)
{
    IUTEST_EXPECT_EQ(initial_flag, GTEST_FLAG_GET(install_failure_signal_handler));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST_F(FailureSignalFlag, ScopedRestoration)
{
    {
        ::iutest::TestFlag::ScopedGuard guard;
        IUTEST_FLAG_SET(install_failure_signal_handler, !initial_flag);
    }
    IUTEST_EXPECT_EQ(initial_flag, IUTEST_FLAG_GET(install_failure_signal_handler));
}

IUTEST_F(FailureSignalFlag, NoCommandLineFlag)
{
    ::iutest::TestFlag::ScopedGuard guard;
    const char* options[] = {
        "--gtest_install_failure_signal_handler", "--gtest_install_failure_signal_handler=1",
        "--iutest_install_failure_signal_handler=0", "--install_failure_signal_handler=true"
    };
    for( size_t i = 0; i < sizeof(options)/sizeof(options[0]); ++i )
    {
        char program[] = "test";
        ::std::string option(options[i]);
        ::std::vector<char> argument(option.begin(), option.end());
        argument.push_back('\0');
        char* argv[] = { program, &argument[0], NULL };
        int argc = 2;
        IUTEST_INIT(&argc, argv);
        IUTEST_EXPECT_EQ(2, argc);
        IUTEST_EXPECT_STREQ(options[i], argv[1]);
        IUTEST_EXPECT_EQ(initial_flag, IUTEST_FLAG_GET(install_failure_signal_handler));
    }
}
#endif

#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IIUT_TEST_SIGNAL_HANDLER
    typedef void (*Handler)(int);
    const Handler previous = signal(SIGABRT, ExistingHandler);
    IUTEST_TERMINATE_ON_FAILURE(previous != SIG_ERR);
#endif
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    const char* value = NULL;
#if !defined(IUTEST_USE_GTEST)
    value = ::std::getenv("IUTEST_INSTALL_FAILURE_SIGNAL_HANDLER");
#endif
    if( value == NULL )
    {
        value = ::std::getenv("GTEST_INSTALL_FAILURE_SIGNAL_HANDLER");
    }
    initial_flag = value != NULL && ::std::string(value) != "0";
    IUTEST_TERMINATE_ON_FAILURE(initial_flag == IUTEST_FLAG_GET(install_failure_signal_handler));
#if !defined(IUTEST_USE_GTEST)
    // Enabling the native flag must not replace an application's signal handlers.
    IUTEST_FLAG_SET(install_failure_signal_handler, true);
    initial_flag = true;
#endif
#endif
    const int result = IUTEST_RUN_ALL_TESTS();
#if IIUT_TEST_SIGNAL_HANDLER
    const Handler current = signal(SIGABRT, previous);
    IUTEST_TERMINATE_ON_FAILURE(current == ExistingHandler);
#endif
    return result;
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
