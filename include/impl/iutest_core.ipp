//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_core.ipp
 * @brief       iris unit test core
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
#define INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

IUTEST_IPP_INLINE int UnitTest::reportable_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_test_count);
}

IUTEST_IPP_INLINE int UnitTest::failed_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::failed_test_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_disabled_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_disabled_test_count);
}

IUTEST_IPP_INLINE int UnitTest::successful_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::successful_test_count);
}

IUTEST_IPP_INLINE int UnitTest::skip_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::skip_test_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_skip_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_skip_test_count);
}

IUTEST_IPP_INLINE int UnitTest::test_run_skipped_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::test_run_skipped_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_test_run_skipped_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_test_run_skipped_count);
}

IUTEST_IPP_INLINE int UnitTest::test_suite_to_run_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::should_run);
}

IUTEST_IPP_INLINE int UnitTest::successful_test_suite_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::Passed);
}

IUTEST_IPP_INLINE int UnitTest::failed_test_suite_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::Failed);
}

IUTEST_IPP_INLINE bool UnitTest::Passed() const
{
    if( m_ad_hoc_testresult.Failed() )
    {
        return false;
    }
    for( iuTestSuites::const_iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
    {
        if( (*it)->Failed() )
        {
            return false;
        }
    }
    return true;
}

IUTEST_IPP_INLINE int UnitTest::Run()
{
    if( m_init_iutest_count == 0 )
    {
//#if IUTEST_HAS_PARAM_TEST
//      if( m_param_testsuite_holder.count() )
//#endif
        {
            detail::iuConsole::output(
                "This test program did NOT call ::iutest::InitIrisUnitTest before calling IUTEST_RUN_ALL_TESTS().  Please fix it.\n"
            );
            return 1;
        }
    }

    if( !PreRunner() )
    {
        return Passed() ? 0 : 1;
    }

#if IUTEST_HAS_EXCEPTIONS
    if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_GLOBAL) )
    {
        int ret = 1;
        try
        {
#if IUTEST_HAS_SEH
            ret = RunOnMSC();
#else
            ret = RunImpl();
#endif
        }
        //catch( ::std::exception& e )
        //{
        //  iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(e.what()), TestPartResult::kFatalFailure) = AssertionHelper::Fixed();
        //}
        catch( ... )
        {
        }
        return ret;
    }
#endif
    return RunImpl();
}

#if IUTEST_HAS_SEH && IUTEST_HAS_EXCEPTIONS
IUTEST_IPP_INLINE int UnitTest::RunOnMSC()
{
    _EXCEPTION_POINTERS* ep = NULL;
    int ret = 1;
    __try
    {
        ret = RunImpl();
    }
    __except (ep = GetExceptionInformation()
#if IUTEST_HAS_MINIDUMP
        , detail::MiniDump::Create("minidump.dump", ep)
#endif
        , detail::seh_exception::should_process_through_break_and_cppexceptions(GetExceptionCode()))
    {
        detail::seh_exception::translator(GetExceptionCode(), ep);
    }
    return ret;
}
#endif

IUTEST_IPP_INLINE int UnitTest::RunImpl()
{
    m_repeat_counter = 0;
    int repeat = TestEnv::get_repeat_count();
    bool result = true;
    if( repeat != 0 )
    {
        m_start_timestamp = detail::GetTimeInMillis();
        TestProgramStart();

        while( repeat )
        {
            SetUpTestIteration();

            listeners().OnTestIterationStart(*this, m_repeat_counter);
            if( !RunOnce() )
            {
                result = false;
            }
            listeners().OnTestIterationEnd(*this, m_repeat_counter);

            ++m_repeat_counter;
            if( repeat > 0 )
            {
                --repeat;
            }
        }

        TestProgramEnd();
    }
    if( !result )
    {
        return 1;
    }
    if( detail::IUTestLog::HasError() )
    {
        return 1;
    }
    if( IUTEST_FLAG(warning_into_error) )
    {
        if( detail::IUTestLog::HasWarning() )
        {
            return 1;
        }
    }
    return 0;
}

IUTEST_IPP_INLINE bool UnitTest::RunOnce()
{
    m_elapsedmsec = 0;

    // テスト結果のクリア
    ClearNonAdHocTestResult();

    // 実行対象のテストがない場合は何もしない
    if( test_to_run_count() == 0 )
    {
        return Passed();
    }

    // シャッフル
    if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
    {
        detail::RandomShuffle(m_testsuites, TestEnv::genrand());
    }

    // グローバル環境セット
    EnvironmentSetUp();

    if( m_ad_hoc_testresult.HasFatalFailure() )
    {
        return false;
    }

    {
        detail::iuStopWatch sw;
        sw.start();
        for( iuTestSuites::iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
        {
            m_current_testsuite = *it;
            m_current_testsuite->Run();
            m_current_testsuite = NULL;
        }
        m_elapsedmsec = sw.stop();
    }

    // グローバル環境セット
    EnvironmentTearDown();

    return Passed();
}

IUTEST_IPP_INLINE void UnitTest::TestProgramStart()
{
//#if IUTEST_HAS_EXCEPTIONS && defined(_MSC_VER) && IUTEST_HAS_SEH
//  // /EHa オプションが必要
//  if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION) )
//  {
//      // SEH 例外に対応する
//      _set_se_translator(detail::seh_exception::translator);
//  }
//#endif

    // フィルタリング
    m_should_run_num = 0;
    m_disable_num = 0;
    for( iuTestSuites::iterator it = m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
    {
        TestSuite* testsuite = *it;
        testsuite->filter();
        m_should_run_num += testsuite->test_to_run_count();
        m_disable_num += testsuite->disabled_test_count();
    }

    atexit(OnExit);
#if IUTEST_HAS_STD_QUICK_EXIT
    ::std::at_quick_exit(OnExit);
#endif

    m_test_started = true;

    listeners().OnTestProgramStart(*this);
}

IUTEST_IPP_INLINE void UnitTest::SetUpTestIteration()
{
    TestEnv::SetUp();
}

IUTEST_IPP_INLINE void UnitTest::EnvironmentSetUp()
{
    listeners().OnEnvironmentsSetUpStart(*this);
    for( iuEnvironmentList::iterator it = TestEnv::environments().begin(), end=TestEnv::environments().end(); it != end; ++it )
    {
        (*it)->SetUp();
    }
    listeners().OnEnvironmentsSetUpEnd(*this);
}

IUTEST_IPP_INLINE void UnitTest::EnvironmentTearDown()
{
    listeners().OnEnvironmentsTearDownStart(*this);
    for( iuEnvironmentList::reverse_iterator it = TestEnv::environments().rbegin(), end=TestEnv::environments().rend(); it != end; ++it )
    {
        (*it)->TearDown();
    }
    listeners().OnEnvironmentsTearDownEnd(*this);
}

IUTEST_IPP_INLINE void UnitTest::TestProgramEnd()
{
    if( !m_test_started )
    {
        return;
    }
    if( current_test_info() != NULL )
    {
        IUTEST_EXPECT_FAILURE("program exit.");
    }
    listeners().OnTestProgramEnd(*this);
    m_test_started = false;
}

IUTEST_IPP_INLINE void UnitTest::Initialize()
{
    m_init_iutest_count++;

    ClearAdHocTestResult();

    // ファイルシステムの初期化
    if( detail::IFileSystem::GetInstance() == NULL )
    {
#if defined(IUTEST_FILE)
        static FileSystem<IUTEST_FILE> filesystem;
        filesystem.Initialize();
#elif IUTEST_HAS_FOPEN
        static FileSystem<StdioFile> filesystem;
        filesystem.Initialize();
#endif
    }

    // 以降初回のみ
    if( m_init_iutest_count != 1 )
    {
        return;
    }

#if IUTEST_HAS_PARAM_TEST
    m_param_testsuite_holder.RegisterTests();
#endif
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
