//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util_quiet_result_printer.hpp
 * @brief       iris unit test quiet result printer
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_QUIET_RESULT_PRINTER_HPP_0DF65DD7_C97C_44BA_940D_D22ED6AF9494_
#define INCG_IRIS_IUTEST_UTIL_QUIET_RESULT_PRINTER_HPP_0DF65DD7_C97C_44BA_940D_D22ED6AF9494_

namespace iuutil
{

//======================================================================
// class

/**
 * @brief   コンパクトなデフォルトコンソール出力イベントリスナー
*/
class QuietResultPrinter : public ::iutest::TestEventListener
{
public:
    explicit QuietResultPrinter(::iutest::TestEventListener* default_printer)
        : m_default_printer(default_printer)
    {}
    virtual ~QuietResultPrinter()
    {
        delete m_default_printer;
    }

public:
    virtual void OnTestProgramStart(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestProgramStart(unit_test);
    }
    virtual void OnTestIterationStart(const ::iutest::UnitTest& unit_test, int iteration) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestIterationStart(unit_test, iteration);
    }
    virtual void OnEnvironmentsSetUpStart(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnEnvironmentsSetUpStart(unit_test);
    }
    virtual void OnEnvironmentsSetUpEnd(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnEnvironmentsSetUpEnd(unit_test);
    }
#if IUTEST_HAS_TESTSUITE
    virtual void OnTestSuiteStart(const ::iutest::TestSuite& test_suite) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestSuiteStart(test_suite);
    }
#else
    virtual void OnTestCaseStart(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestCaseStart(test_case);
    }
#endif

#if 0
    virtual void OnTestStart(const ::iutest::TestInfo& test_info) IUTEST_CXX_OVERRIDE {}

    virtual void OnTestPartResult(const ::iutest::TestPartResult& test_part_result) IUTEST_CXX_OVERRIDE
    {
        if( ::iutest::UnitTest::GetInstance()->current_test_info() != NULL )
        {
            const ::iutest::TestInfo& test_info = *::iutest::UnitTest::GetInstance()->current_test_info();
            if( test_info.result()->Failed()
                && test_info.result()->total_part_count() == 1 )
            {
                m_default_printer->OnTestStart(test_info);
            }
        }
        m_default_printer->OnTestPartResult(test_part_result);
    }
#else
    virtual void OnTestStart(const ::iutest::TestInfo& test_info) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestStart(test_info);
    }
    virtual void OnTestPartResult(const ::iutest::TestPartResult& test_part_result) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestPartResult(test_part_result);
    }
#endif

    virtual void OnTestEnd(const ::iutest::TestInfo& test_info) IUTEST_CXX_OVERRIDE
    {
        if( test_info.result()->Failed() )
        {
            // 失敗したときのみ出力する
            m_default_printer->OnTestEnd(test_info);
        }
    }
#if IUTEST_HAS_TESTSUITE
    virtual void OnTestSuiteEnd(const ::iutest::TestSuite& test_suite) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestSuiteEnd(test_suite);
    }
#else
    virtual void OnTestCaseEnd(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestCaseEnd(test_case);
    }
#endif
    virtual void OnEnvironmentsTearDownStart(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnEnvironmentsTearDownStart(unit_test);
    }
    virtual void OnEnvironmentsTearDownEnd(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnEnvironmentsTearDownEnd(unit_test);
    }
    virtual void OnTestIterationEnd(const ::iutest::UnitTest& unit_test, int iteration) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestIterationEnd(unit_test, iteration);
    }
    virtual void OnTestProgramEnd(const ::iutest::UnitTest& unit_test) IUTEST_CXX_OVERRIDE
    {
        m_default_printer->OnTestProgramEnd(unit_test);
    }
private:
    ::iutest::TestEventListener* m_default_printer;

public:
    /**
     * @brief   QuietResultPrinter に切り替え
    */
    static ::iutest::TestEventListener* SetUp()
    {
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        ::iutest::TestEventListener* default_printer = listeners.Release(listeners.default_result_printer());
        if( default_printer == NULL )
        {
            return NULL;
        }
        ::iutest::TestEventListener* p = new QuietResultPrinter(default_printer);
        listeners.Append(p);
        return p;
    }
};

}   // end of namespace iuutil

#endif // INCG_IRIS_IUTEST_UTIL_QUIET_RESULT_PRINTER_HPP_0DF65DD7_C97C_44BA_940D_D22ED6AF9494_
