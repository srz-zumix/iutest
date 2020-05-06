//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        logger_tests.hpp
 * @brief       logger test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IUTEST_LOGGER_TESTS_HPP_
#define INCG_IUTEST_LOGGER_TESTS_HPP_

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

class TestLogger : public ::iutest::detail::iuLogger
{
    ::std::string m_log;
public:
    virtual void voutput(const char* fmt, va_list va) IUTEST_CXX_OVERRIDE IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 0)
    {
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
        char buf[4096] = { 0 };
        va_list va2;
        iu_va_copy(va2, va);
        vsprintf(buf, fmt, va2);
        va_end(va2);
        m_log += buf;
        ::iutest::detail::iuConsole::nl_voutput(fmt, va);
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    }
    void clear(void) { m_log.clear(); }
public:
    const char* c_str(void) const { return m_log.c_str(); }
};

#endif

#if !defined(IUTEST_USE_GTEST)
class LogChecker
{
    TestLogger printer_logger;
    ::std::string m_str;
public:
    explicit LogChecker(const char* str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
    explicit LogChecker(const std::string& str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
#if IUTEST_HAS_RVALUE_REFS
    explicit LogChecker(std::string&& str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
#endif
    ~LogChecker(void)
    {
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_EXPECT_STRIN(m_str.c_str(), printer_logger.c_str());
        printer_logger.clear();
    }
};
#else
class LogChecker
{
public:
    explicit LogChecker(const char*) {}
};
#endif

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
class PrintToLogChecker
{
    TestLogger printer_logger;
    ::std::string m_str;
public:
    explicit PrintToLogChecker(const char* str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
    explicit PrintToLogChecker(const std::string& str) : m_str(str)
    {
        ::iutest::detail::iuConsole::SetLogger(&printer_logger);
    }
    ~PrintToLogChecker(void)
    {
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_EXPECT_STRIN(m_str.c_str(), printer_logger.c_str());
        printer_logger.clear();
    }
};
#else
class PrintToLogChecker
{
public:
    explicit PrintToLogChecker(const char*) {}
};
#endif

#endif
