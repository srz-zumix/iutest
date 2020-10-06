//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_info.ipp
 * @brief       iris unit test 情報 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_INFO_IPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_
#define INCG_IRIS_IUTEST_INFO_IPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_

//======================================================================
// include
#include "../iutest_info.hpp"

namespace iutest
{

/**
 * @brief   実行
*/
IUTEST_IPP_INLINE bool TestInfo::Run()
{
    if( !should_run() )
    {
        return true;
    }

    // テスト開始
    TestEnv::event_listeners().OnTestStart(*this);

    RunImpl();

    // テスト終了
    TestEnv::event_listeners().OnTestEnd(*this);
    return !HasFailure();
}

IUTEST_IPP_INLINE void TestInfo::RunImpl()
{
    detail::iuStopWatch sw;
    TimeInMillisec elapsedmsec = 0;

    m_ran = true;

#if IUTEST_HAS_EXCEPTIONS
    if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_EACH) )
    {
        detail::auto_ptr<Test> p = m_factory->Create();
        try
        {
            sw.start();
#if IUTEST_HAS_SEH
            RunOnMSC(p.get());
#else
            p->Run(&m_mediator);
#endif
            elapsedmsec = sw.stop();
        }
        catch (const ::std::exception& e)
        {
            elapsedmsec = sw.stop();
            iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(e.what())
                , TestPartResult::kFatalFailure).OnFixed(AssertionHelper::Fixed(), true);
            if( TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
            {
                throw;
            }
        }
        catch (const TestPartResult::Type& eType)
        {
            elapsedmsec = sw.stop();
            if( TestPartResult::type_is_failed(eType) && TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
            {
                throw;
            }
        }
        catch (...)
        {
            elapsedmsec = sw.stop();
            iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(NULL)
                , TestPartResult::kFatalFailure).OnFixed(AssertionHelper::Fixed(), true);
            if( TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
            {
                throw;
            }
        }
    }
    else
#endif
    {
        detail::auto_ptr<Test> p = m_factory->Create();
        sw.start();
        p->Run(&m_mediator);
        elapsedmsec = sw.stop();
    }

    m_test_result.set_elapsed_time(elapsedmsec);

    if( HasFailure() && TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
    {
#if IUTEST_HAS_EXCEPTIONS
        throw HasFatalFailure() ? TestPartResult::kFatalFailure : TestPartResult::kNonFatalFailure;
#else
        exit(1);
#endif
    }
}

#if IUTEST_HAS_SEH && IUTEST_HAS_EXCEPTIONS
#if IUTEST_HAS_MINIDUMP

IUTEST_IPP_INLINE void TestInfo::MiniDump(_EXCEPTION_POINTERS* ep)
{
#if defined(_MSC_VER)
    char path[IUTEST_MAX_PATH];
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    _snprintf(path, sizeof(path), "%s_%s.dump", test_suite_name(), name());
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    detail::MiniDump::Create(path, ep);
#endif
}

#endif

IUTEST_IPP_INLINE void TestInfo::RunOnMSC(Test* test)
{
    _EXCEPTION_POINTERS* ep = NULL;
    __try
    {
        test->Run(&m_mediator);
    }
    __except (ep = GetExceptionInformation()
#if IUTEST_HAS_MINIDUMP
        , MiniDump(ep)
#endif
        , detail::seh_exception::should_process_through_break_and_cppexceptions(GetExceptionCode()))
    {
        detail::seh_exception::translator(GetExceptionCode(), ep);
    }
}
#endif

IUTEST_IPP_INLINE void TestInfo::clear()
{
    m_ran = false;
    m_skip = false;
    m_test_result.Clear();
    m_uncaught_messages.clear();
}

IUTEST_IPP_INLINE bool TestInfo::filter()
{
    bool run = true;
    // 無効テストなら実行しない
    if( !TestFlag::IsEnableFlag(TestFlag::RUN_DISABLED_TESTS)
        && is_disabled_test() )
    {
        run = false;
    }
    bool match = true;
    if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
    {
        if( !detail::iuFilterRegex::match(TestEnv::test_filter(), test_full_name().c_str()) )
        {
            match = false;
            run = false;
        }
    }
    m_matches_filter = match;
    m_should_run = run;
    return m_should_run;
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_INFO_IPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_
