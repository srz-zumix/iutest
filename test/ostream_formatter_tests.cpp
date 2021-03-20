//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        ostream_formatter_tests.cpp
 * @brief       ostream formatter test
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
#include <iomanip>
#include "iutest.hpp"
#include "logger_tests.hpp"

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP) && (IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM)
#  define OSTREAM_FORMATTER_TESTS_ENABLE
#endif

TestLogger logger;

IUTEST(Test, Hex)
{
    IUTEST_ASSERT_EQ(1024, 1025);
}

IUTEST(Test, Float)
{
    IUTEST_ASSERT_EQ(0.33f, 1.0f/3.0f);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 実行対象テストがないので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    ::iutest::detail::iuConsole::SetLogger(&logger);

    ::iutest::IUTEST_FLAG(color) = "no";
#if defined(OSTREAM_FORMATTER_TESTS_ENABLE)
    ::iutest::IUTEST_FLAG(ostream_formatter) << ::std::hex
        << ::std::setw(8) << ::std::setfill('0') << ::std::setprecision(5);
#endif

    {
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if defined(OSTREAM_FORMATTER_TESTS_ENABLE)

#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN("  Actual: 00000401", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("Which is: 00000400", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("  Actual: 00.33333", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("Which is: 00000.33", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif

#endif
    }
    printf("*** Successful ***\n");
    return 0;
}
