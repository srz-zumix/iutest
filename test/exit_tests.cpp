//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exit_tests.cpp
 * @brief       quick_exit test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2016-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STD_QUICK_EXIT

class ExitCheckEventListener IUTEST_CXX_FINAL : public ::iutest::EmptyTestEventListener
{
    virtual void OnTestProgramEnd(const ::iutest::UnitTest& test) IUTEST_CXX_OVERRIDE
    {
        if( test.current_test_info() == NULL ) throw "current_test_info() == NULL";
        if( iuutil::GetCurrentTestSuite(&test) == NULL ) throw "current_test_suite() == NULL";
        if( !test.current_test_info()->is_ran() ) throw "is_ran()";
        if( !test.current_test_info()->HasFailure() ) throw "HasFailure()";
    }
};

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()

IUTEST(ExitTest, QuickExit)
{
    ::std::quick_exit(0);
}

IUTEST_PRAGMA_WARN_POP()

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IUTEST_HAS_STD_QUICK_EXIT
    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    listeners.Append(new ExitCheckEventListener());

    IUTEST_INIT(&argc, argv);

#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    IUTEST_RUN_ALL_TESTS();
    return 1;
#else
    (void)argc;
    (void)argv;
    printf("*** IUTEST_HAS_STD_QUICK_EXIT=0 ***\n");
    return 0;
#endif
}
