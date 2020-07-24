//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_legacy.hpp
 * @brief       iris unit test legacy testcase support
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_LEGACY_HPP_E7B75232_2AB9_44F5_B9C5_CF62CD3FF958_
#define INCG_IRIS_IUTEST_LEGACY_HPP_E7B75232_2AB9_44F5_B9C5_CF62CD3FF958_

#if !defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)

#include "internal/iutest_port.hpp"

namespace iutest
{

class TestSuite;
class Test;

typedef TestSuite   TestCase;

namespace detail
{
::std::string FormatCompilerIndependentFileLocation(const char* file, int line);
}

namespace legacy
{
    typedef void (*SetUpTearDownTestSuiteFuncType)();

    inline SetUpTearDownTestSuiteFuncType  GetNotDefaultOrNull(SetUpTearDownTestSuiteFuncType a, SetUpTearDownTestSuiteFuncType def)
    {
        return a == def ? NULL : a;
    }

    template<typename T>
    struct SuiteApiResolver : T
    {
        typedef typename iutest_type_traits::enable_if<sizeof(T) != 0, ::iutest::Test>::type Tester;

        static SetUpTearDownTestSuiteFuncType GetSetUpCaseOrSuite(const char* file, int line)
        {
            SetUpTearDownTestSuiteFuncType testcase = GetNotDefaultOrNull(&T::SetUpTestCase, &Tester::SetUpTestCase);
            SetUpTearDownTestSuiteFuncType testsuite = GetNotDefaultOrNull(&T::SetUpTestSuite, &Tester::SetUpTestSuite);

            IUTEST_CHECK_( testcase == NULL || testsuite == NULL )
                << "Test can not provide both SetUpTestSuite and SetUpTestCase, please make sure there is only one present at "
                << detail::FormatCompilerIndependentFileLocation(file, line);

            return testcase != NULL ? testcase : testsuite;
        }
        static SetUpTearDownTestSuiteFuncType GetTearDownCaseOrSuite(const char* file, int line)
        {
            SetUpTearDownTestSuiteFuncType testcase = GetNotDefaultOrNull(&T::TearDownTestCase, &Tester::TearDownTestCase);
            SetUpTearDownTestSuiteFuncType testsuite = GetNotDefaultOrNull(&T::TearDownTestSuite, &Tester::TearDownTestSuite);

            IUTEST_CHECK_( testcase == NULL || testsuite == NULL )
                << "Test can not provide both TearDownTestSuite and TearDownTestCase, please make sure there is only one present at "
                << detail::FormatCompilerIndependentFileLocation(file, line);

            return testcase != NULL ? testcase : testsuite;
        }
    };

}   // end of namespace legacy
}   // end of namespace iutest

#define IUTEST_GET_SETUP_TESTSUITE(type, file, line)       ::iutest::legacy::SuiteApiResolver<type>::GetSetUpCaseOrSuite(file, line)
#define IUTEST_GET_TEARDOWN_TESTSUITE(type, file, line)    ::iutest::legacy::SuiteApiResolver<type>::GetTearDownCaseOrSuite(file, line)

#else

#define IUTEST_GET_SETUP_TESTSUITE(type, file, line)       ((void)(file, line), type::SetUpTestSuite)
#define IUTEST_GET_TEARDOWN_TESTSUITE(type, file, line)    ((void)(file, line), type::TearDownTestSuite)

#endif

#endif // INCG_IRIS_IUTEST_LEGACY_HPP_E7B75232_2AB9_44F5_B9C5_CF62CD3FF958_
