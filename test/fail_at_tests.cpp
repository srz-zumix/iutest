//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fail_at_tests.cpp
 * @brief       IUTEST_FAIL_AT/IUTEST_ASSERT_FAIL_AT test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2024, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include <cstring>

namespace
{

int nCount = 0;

class RecordingListener IUTEST_CXX_FINAL : public ::iutest::EmptyTestEventListener
{
public:
    RecordingListener(void)
        : fail_at_ok(false), assert_fail_at_ok(false), add_failure_at_ok(false) {}

    virtual void OnTestEnd(const ::iutest::TestInfo& test_info) IUTEST_CXX_OVERRIDE
    {
        const ::iutest::TestResult* result = test_info.result();
        for( int i=0; i < result->total_part_count(); ++i )
        {
            const ::iutest::TestPartResult& part = result->GetTestPartResult(i);
            const char* file = part.file_name();
            if( file == IUTEST_NULLPTR )
            {
                continue;
            }
            if( strcmp(file, "fail_at_test_file.cc") == 0 )
            {
                fail_at_ok = part.fatally_failed() && part.line_number() == 100;
            }
            else if( strcmp(file, "assert_fail_at_test_file.cc") == 0 )
            {
                assert_fail_at_ok = part.fatally_failed() && part.line_number() == 200;
            }
            else if( strcmp(file, "add_failure_at_test_file.cc") == 0 )
            {
                add_failure_at_ok = part.nonfatally_failed() && part.line_number() == 300;
            }
        }
    }

    bool fail_at_ok;
    bool assert_fail_at_ok;
    bool add_failure_at_ok;
};

}   // namespace

IUTEST(FailAtTest, Fail)
{
    IUTEST_FAIL_AT("fail_at_test_file.cc", 100);
    ++nCount;
}

IUTEST(FailAtTest, AssertFail)
{
    IUTEST_ASSERT_FAIL_AT("assert_fail_at_test_file.cc", 200);
    ++nCount;
}

IUTEST(FailAtTest, AddFailure)
{
    // ADD_FAILURE_AT is non fatal, so the statement after it is executed.
    IUTEST_ADD_FAILURE_AT("add_failure_at_test_file.cc", 300);
    ++nCount;
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(DISABLE_FALSE_POSITIVE_XML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    RecordingListener* listener = new RecordingListener();
    ::iutest::UnitTest::GetInstance()->listeners().Append(listener);

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret == 0 ) return 1;

    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 3 );
    // IUTEST_FAIL_AT/IUTEST_ASSERT_FAIL_AT are fatal: the statement after them must not run.
    // only the non fatal IUTEST_ADD_FAILURE_AT lets the following statement run.
    IUTEST_TERMINATE_ON_FAILURE( nCount == 1 );
    IUTEST_TERMINATE_ON_FAILURE( listener->fail_at_ok );
    IUTEST_TERMINATE_ON_FAILURE( listener->assert_fail_at_ok );
    IUTEST_TERMINATE_ON_FAILURE( listener->add_failure_at_ok );

    printf("*** Successful ***\n");
    return 0;
}
