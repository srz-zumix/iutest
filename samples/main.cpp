//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        main.cpp
 * @brief       sample main ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2016, Takazumi Shirayanagi\n
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
#include "../include/iutest.hpp"

#if defined(USE_TAP)
#include "../include/listener/iutest_tap_printer.hpp"
#endif
#if defined(USE_PROGRESS)
#include "../include/listener/iutest_progress_printer.hpp"
#endif
#if defined(USE_SSTPNOTIFIER)
#include "../include/listener/iutest_sstp_notifier.hpp"
#endif

/** --------------------------------------------------
 * Environment サンプル
*//*--------------------------------------------------*/
class FooEnvironment : public ::iutest::Environment
{
    virtual void SetUp()
    {
        iuutil::Console::output("FooEnvironment::SetUp\n");
    }
    virtual void TearDown()
    {
        iuutil::Console::output("FooEnvironment::TearDown\n");
    }
};

#if defined(_MSC_VER) && IUTEST_HAS_LIB

#pragma comment(lib, IUTEST_LIB_NAME(libiutest_main) )

#else

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
    setlocale(LC_CTYPE, "");
#endif

#if 1
    iutest::AddGlobalTestEnvironment(new FooEnvironment());
#endif

    //iutest::IUTEST_FLAG(shuffle) = false;
    //iutest::IUTEST_FLAG(throw_on_failure) = true;
    IUTEST_INIT(&argc, argv);

#if defined(USE_TAP)
    ::iutest::TAPPrintListener::SetUp();
#endif

#if defined(USE_PROGRESS)
    ::iutest::ProgressPrintListener::SetUp();
#endif

#if defined(USE_SSTPNOTIFIER)
    ::iutest::SSTPNotifier::SetUp("localhost");
#endif

    //::iuutil::QuietResultPrinter::SetUp();

    return IUTEST_RUN_ALL_TESTS();
}

#endif
