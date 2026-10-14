//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        flag_restore_tests.cpp
 * @brief       Per-test flag restoration tests
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

namespace
{

bool original_print_time;
::std::string original_filter;
::std::string original_output;
bool suite_print_time;
::std::string suite_filter;
::std::string suite_output;
bool suite_torn_down = false;

class FlagRestore : public ::iuutil::backward::Test<FlagRestore>
{
public:
    static void SetUpTestSuite()
    {
        original_print_time = ::iutest::IUTEST_FLAG(print_time);
        original_filter = ::iutest::IUTEST_FLAG(filter);
        original_output = ::iutest::IUTEST_FLAG(output);
        suite_print_time = !original_print_time;
        suite_filter = "FlagRestore.*";
        suite_output = "xml:suite_flags.xml";
        IUTEST_FLAG_SET(print_time, suite_print_time);
        IUTEST_FLAG_SET(filter, suite_filter);
        IUTEST_FLAG_SET(output, suite_output);
    }

    static void TearDownTestSuite()
    {
        IUTEST_EXPECT_EQ(suite_print_time, ::iutest::IUTEST_FLAG(print_time));
        IUTEST_EXPECT_STREQ(suite_filter.c_str(), ::iutest::IUTEST_FLAG(filter).c_str());
        IUTEST_EXPECT_STREQ(suite_output.c_str(), ::iutest::IUTEST_FLAG(output).c_str());
        suite_torn_down = true;
        IUTEST_FLAG_SET(print_time, original_print_time);
        IUTEST_FLAG_SET(filter, original_filter);
        IUTEST_FLAG_SET(output, original_output);
    }
};

}   // namespace

IUTEST_F(FlagRestore, A_Modify)
{
    IUTEST_EXPECT_EQ(suite_print_time, ::iutest::IUTEST_FLAG(print_time));
    IUTEST_FLAG_SET(print_time, !suite_print_time);
    IUTEST_FLAG_SET(filter, "FlagRestore.Other");
    IUTEST_FLAG_SET(output, "xml:test_flags.xml");
}

IUTEST_F(FlagRestore, B_Restored)
{
    IUTEST_EXPECT_EQ(suite_print_time, ::iutest::IUTEST_FLAG(print_time));
    IUTEST_EXPECT_STREQ(suite_filter.c_str(), ::iutest::IUTEST_FLAG(filter).c_str());
    IUTEST_EXPECT_STREQ(suite_output.c_str(), ::iutest::IUTEST_FLAG(output).c_str());
}

IUTEST(FlagRestoreAfterSuite, Restored)
{
    IUTEST_EXPECT_TRUE(suite_torn_down);
    IUTEST_EXPECT_EQ(original_print_time, ::iutest::IUTEST_FLAG(print_time));
    IUTEST_EXPECT_STREQ(original_filter.c_str(), ::iutest::IUTEST_FLAG(filter).c_str());
    IUTEST_EXPECT_STREQ(original_output.c_str(), ::iutest::IUTEST_FLAG(output).c_str());
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
