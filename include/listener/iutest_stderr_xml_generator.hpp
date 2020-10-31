//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_stderr_xml_generator.hpp
 * @brief       output stderr (junit) xml event listener
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2016-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_
#define INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_junit_xml_generator.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class

namespace detail
{

/**
 * @brief   xml result output to stderr
*/
template<typename T, typename ::std::string (*GetXmlPath)()>
class StderrXmlGeneratorListenerBase : public T
{
public:
    /**
     * @brief   コンストラクタ
     * @param [in] path = 出力パス
    */
    explicit StderrXmlGeneratorListenerBase(const ::std::string& path) : T(path) {}

    ~StderrXmlGeneratorListenerBase() {}

#if IUTEST_HAS_FOPEN
private:
    StdErrorFile m_stderr;

    virtual bool FileOpen(const char* path)
    {
        if( m_stderr.Open(path, IFile::OpenAppend) )
        {
            this->m_fp = &m_stderr;
            return true;
        }
        return false;
    }
    virtual void FileClose()
    {
        this->m_fp = NULL;
    }
#endif

public:
    /** @private */
    static bool SetUp()
    {
        ::std::string xmlpath = GetXmlPath();
        if( !xmlpath.empty() )
        {
            TestEnv::event_listeners().set_default_xml_generator(new StderrXmlGeneratorListenerBase(xmlpath));
            return true;
        }
        return false;
    }
};

}   // end of namespace detail

typedef detail::StderrXmlGeneratorListenerBase<
    DefaultXmlGeneratorListener, TestEnv::get_report_xml_filepath> StderrXmlGeneratorListener;
typedef detail::StderrXmlGeneratorListenerBase<
    JunitXmlGeneratorListener, TestEnv::get_report_junit_xml_filepath> StderrJunitXmlGeneratorListener;

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_
