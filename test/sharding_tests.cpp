//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        sharding_tests.cpp
 * @brief       Runner sharding and marker file tests
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

#if defined(IUTEST_USE_GTEST)
int main() { return 0; }
#else

namespace
{

int runs[5] = { 0 };
bool check_markers = false;
bool exit_early = false;
bool fail_test = false;
::std::string status_path;
::std::string premature_path;

bool Exists(const ::std::string& path)
{
#if IUTEST_HAS_FOPEN
    FILE* fp = ::iutest::internal::posix::FileOpen(path.c_str(), "rb");
    if( fp != NULL )
    {
        fclose(fp);
        return true;
    }
#else
    IUTEST_UNUSED_VAR(path);
#endif
    return false;
}

void RecordRun(int index)
{
    ++runs[index];
    if( check_markers )
    {
        IUTEST_EXPECT_TRUE(Exists(status_path));
        IUTEST_EXPECT_TRUE(Exists(premature_path));
    }
    if( exit_early ) exit(0);
    IUTEST_EXPECT_FALSE(fail_test);
}

bool SetEnv(const char* name, const char* value)
{
    return ::iutest::detail::SetEnvironmentVariable(name, value);
}

bool CheckSelection(int total, int shard, bool run_disabled)
{
    const ::iutest::UnitTest* unit = ::iutest::UnitTest::GetInstance();
    const char* names[] = { "One", "DISABLED_Two", "Three", "Four", "Five" };
    int selected = 0;
    for( int s = 0; s < unit->total_test_suite_count(); ++s )
    {
        const ::iutest::TestSuite* suite = unit->GetTestSuite(s);
        for( int t = 0; t < suite->total_test_count(); ++t )
        {
            const ::iutest::TestInfo* info = suite->GetTestInfo(t);
            const bool runnable = strcmp(info->name(), "Excluded") != 0
                && (run_disabled || !info->is_disabled_test());
            int runnable_id = 0;
            while( runnable_id < 5 && strcmp(info->name(), names[runnable_id]) != 0 ) ++runnable_id;
            if( !run_disabled && runnable_id > 1 ) --runnable_id;
            const bool other = runnable && runnable_id % total != shard;
            if( info->is_in_another_shard() != other ) return false;
            if( info->should_run() != (runnable && !other) ) return false;
            if( info->is_reportable() != (strcmp(info->name(), "Excluded") != 0 && !other) ) return false;
            if( info->should_run() ) ++selected;
        }
    }
    return selected == unit->test_to_run_count() && selected == unit->reportable_test_count()
        - (run_disabled ? 0 : 1);
}

}   // namespace

IUTEST(ShardFirst, One) { RecordRun(0); }
IUTEST(ShardFirst, Excluded) { IUTEST_ADD_FAILURE(); }
IUTEST(ShardFirst, DISABLED_Two) { RecordRun(1); }
IUTEST(ShardFirst, Three) { RecordRun(2); }
IUTEST(ShardSecond, Four) { RecordRun(3); }
IUTEST(ShardSecond, Five) { RecordRun(4); }

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    IUTEST_FLAG_SET(filter, "*-*.Excluded");
    IUTEST_FLAG_SET(also_run_disabled_tests, false);

    if( argc > 1 && strcmp(argv[1], "--exit-early") == 0 )
    {
        exit_early = true;
        return IUTEST_RUN_ALL_TESTS();
    }
    if( argc > 1 && strcmp(argv[1], "--probe") == 0 )
    {
        return IUTEST_RUN_ALL_TESTS();
    }
    if( !SetEnv("GTEST_TOTAL_SHARDS", "3") || !SetEnv("GTEST_SHARD_INDEX", "0") ) return 0;
    IUTEST_FLAG_SET(shuffle, true);
    IUTEST_FLAG_SET(repeat, 2);

    for( int disabled = 0; disabled != 2; ++disabled )
    {
        for( int i = 0; i != 5; ++i ) runs[i] = 0;
        IUTEST_FLAG_SET(also_run_disabled_tests, disabled != 0);
        const char* indices[] = { "0", "1", "2" };
        for( int shard = 0; shard != 3; ++shard )
        {
            IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_SHARD_INDEX", indices[shard]));
            IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
            IUTEST_TERMINATE_ON_FAILURE(CheckSelection(3, shard, disabled != 0));
        }
        for( int i = 0; i != 5; ++i )
        {
            IUTEST_TERMINATE_ON_FAILURE(runs[i] == ((i == 1 && !disabled) ? 0 : 2));
        }
    }

    IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_TOTAL_SHARDS", "8"));
    IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_SHARD_INDEX", "7"));
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
    IUTEST_TERMINATE_ON_FAILURE(CheckSelection(8, 7, true));

    const char* invalid_totals[] = { "0", "-1", "x", "2x", "", "9999999999999999999999999", "2", "2" };
    const char* invalid_indices[] = { "0", "0", "0", "0", "0", "0", "-1", "2" };
    for( size_t i = 0; i < sizeof(invalid_totals) / sizeof(invalid_totals[0]); ++i )
    {
        IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_TOTAL_SHARDS", invalid_totals[i]));
        IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_SHARD_INDEX", invalid_indices[i]));
        IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
    }
    IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_TOTAL_SHARDS", "1"));
    IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_SHARD_INDEX", "0"));

#if IUTEST_HAS_FOPEN
    ::iutest::TempFile status, premature;
    if( status.Create("iutest-shard") && premature.Create("iutest-premature") )
    {
        status_path = status.GetFileName();
        premature_path = premature.GetFileName();
        status.Delete();
        premature.Delete();
        IUTEST_TERMINATE_ON_FAILURE(SetEnv("GTEST_SHARD_STATUS_FILE", status_path.c_str()));
        IUTEST_TERMINATE_ON_FAILURE(SetEnv("TEST_PREMATURE_EXIT_FILE", premature_path.c_str()));
        check_markers = true;
        IUTEST_FLAG_SET(repeat, 2);
        IUTEST_FLAG_SET(shuffle, true);
        IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
        IUTEST_TERMINATE_ON_FAILURE(Exists(status_path));
        IUTEST_TERMINATE_ON_FAILURE(!Exists(premature_path));
        remove(status_path.c_str());
        fail_test = true;
        IUTEST_FLAG_SET(repeat, 1);
        IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
        IUTEST_TERMINATE_ON_FAILURE(Exists(status_path));
        IUTEST_TERMINATE_ON_FAILURE(!Exists(premature_path));
        remove(status_path.c_str());
    }
#endif
    printf("*** Successful ***\n");
    return 0;
}

#endif
