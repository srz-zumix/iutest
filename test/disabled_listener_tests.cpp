//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        disabled_listener_tests.cpp
 * @brief       disabled test listener and printer test
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
#include "logger_tests.hpp"

static int enabled_runs = 0;
static int disabled_runs = 0;

IUTEST(DisabledEvent, Enabled)
{
    ++enabled_runs;
}

IUTEST(DisabledEvent, DISABLED_Selected)
{
    ++disabled_runs;
}

IUTEST(DisabledEvent, DISABLED_Excluded)
{
    ++disabled_runs;
}

IUTEST(DISABLED_Only, Test)
{
    ++disabled_runs;
}

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01120000
class DisabledListener : public ::iutest::EmptyTestEventListener
{
public:
    int disabled_count;
    int started_count;
    ::std::string disabled_names;

    DisabledListener() : disabled_count(0), started_count(0) {}

    virtual void OnTestDisabled(const ::iutest::TestInfo& info) IUTEST_CXX_OVERRIDE
    {
        ++disabled_count;
        disabled_names += info.test_suite_name();
        disabled_names += ".";
        disabled_names += info.name();
        disabled_names += "\n";
    }

    virtual void OnTestStart(const ::iutest::TestInfo& /*info*/) IUTEST_CXX_OVERRIDE
    {
        ++started_count;
    }

    void Clear()
    {
        disabled_count = 0;
        started_count = 0;
        disabled_names.clear();
    }
};
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01120000
    ::iutest::IUTEST_FLAG(filter) = "DisabledEvent.Enabled:DisabledEvent.DISABLED_Selected:DISABLED_Only.Test";
    ::iutest::IUTEST_FLAG(also_run_disabled_tests) = false;
    DisabledListener* listener = new DisabledListener();
    ::iutest::UnitTest::GetInstance()->listeners().Append(listener);
#if !defined(IUTEST_USE_GTEST)
    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
    ::iutest::IUTEST_FLAG(color) = "no";
    ::iutest::IUTEST_FLAG(verbose) = false;
#endif
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    if( listener->disabled_count != 2 || listener->started_count != 1
        || enabled_runs != 1 || disabled_runs != 0
        || listener->disabled_names != "DisabledEvent.DISABLED_Selected\nDISABLED_Only.Test\n" ) return 1;
#if !defined(IUTEST_USE_GTEST)
    if( ::std::string(logger.c_str()).find("[ DISABLED ] DisabledEvent.DISABLED_Selected") != ::std::string::npos ) return 1;
    listener->Clear();
    logger.clear();
    ::iutest::IUTEST_FLAG(verbose) = true;
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    if( listener->disabled_count != 2 || listener->started_count != 1
        || enabled_runs != 2 || disabled_runs != 0 ) return 1;
    const ::std::string output = logger.c_str();
    if( output.find("[ DISABLED ] DisabledEvent.DISABLED_Selected\n") == ::std::string::npos
        || output.find("[ DISABLED ] DISABLED_Only.Test\n") == ::std::string::npos
        || output.find("[ DISABLED ] DisabledEvent.DISABLED_Excluded") != ::std::string::npos ) return 1;
#endif
    listener->Clear();
    ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    if( listener->disabled_count != 0 || listener->started_count != 3
#if !defined(IUTEST_USE_GTEST)
        || enabled_runs != 3 || disabled_runs != 2
#else
        || enabled_runs != 2 || disabled_runs != 2
#endif
        ) return 1;
#else
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
#endif
    return 0;
}
