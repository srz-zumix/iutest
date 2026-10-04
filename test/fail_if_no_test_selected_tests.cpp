//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fail_if_no_test_selected_tests.cpp
 * @brief       Fail if no test selected tests
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

static int skipped_test_started = 0;

IUTEST(Selected, Skipped)
{
    ++skipped_test_started;
    IUTEST_SKIP();
}

IUTEST(Selected, DISABLED_NotRun)
{
    IUTEST_FAIL();
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    const bool command_line = argc > 1;
    IUTEST_INIT(&argc, argv);
    if( command_line ) return IUTEST_RUN_ALL_TESTS();

    IUTEST_FLAG_SET(filter, "NotSelected.*");
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000 || GTEST_LATEST
    IUTEST_FLAG_SET(fail_if_no_test_selected, true);
    if( IUTEST_RUN_ALL_TESTS() != 1 ) return 1;

    IUTEST_FLAG_SET(filter, "Selected.DISABLED_NotRun");
    if( IUTEST_RUN_ALL_TESTS() != 1 ) return 1;
#endif

    IUTEST_FLAG_SET(filter, "Selected.Skipped");
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    if( skipped_test_started != 1 ) return 1;

    return 0;
}
