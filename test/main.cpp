//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        main.cpp
 * @brief       test main
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

/*
 * is not available vprintf, can be replaced.
*/
//#define IUTEST_VPRINTF

/*
 * include testing framework
*/
#include "iutest.hpp"

#ifdef USE_TAP
#  include "../include/listener/iutest_tap_printer.hpp"
#endif

#ifdef USE_PROGRESS
#  include "../include/listener/iutest_progress_printer.hpp"
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);

#ifdef USE_TAP
    ::iutest::TAPPrintListener::SetUp();
#endif

#ifdef USE_PROGRESS
    ::iutest::ProgressPrintListener::SetUp();
#endif

    return IUTEST_RUN_ALL_TESTS();
}

