﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_default_xml_generator.ipp
 * @brief       output xml event listener implementation
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_IPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_
#define INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_IPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_

//======================================================================
// include
#include "../listener/iutest_default_xml_generator.hpp"

namespace iutest
{

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnTestIterationStart(const UnitTest& test, int iteration)
{
    if(!IsReportable(test))
    {
        return;
    }
    if( !m_output_path_format.empty() )
    {
        m_output_path = m_output_path_format;
        ::std::string strIte = detail::iu_to_string(iteration);
        detail::StringReplace(m_output_path, "%d", 2, strIte.c_str());
        detail::StringReplace(m_output_path, "{I}", 3, strIte.c_str());
        if( m_output_path == m_output_path_format)
        {
            m_output_path_format.clear();
        }
        if( m_fp != NULL )
        {
            OnReportTest(m_fp, test);
            FileClose();
        }
    }
    if( m_fp == NULL )
    {
        FileOpen(m_output_path.c_str());
    }
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnTestProgramEnd(const UnitTest& test)
{
    if(!IsReportable(test))
    {
        return;
    }
    if( m_fp == NULL )
    {
        FileOpen(m_output_path.c_str());
        if( m_fp == NULL )
        {
            return;
        }
    }
    OnReportTest(m_fp, test);
    FileClose();
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnReportTest(IFile* file, const UnitTest& test)
{
    file->Printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    file->Printf("<testsuites tests=\"%d\" failures=\"%d\" disabled=\"%d\" "
        , test.reportable_test_count()
        , test.failed_test_count()
        , test.reportable_disabled_test_count()
        );
#if IUTEST_HAS_REPORT_SKIPPED
    file->Printf("skip=\"%d\" ", test.reportable_skip_test_count());
#endif
    file->Printf("errors=\"0\" time=\"%s\" timestamp=\"%s\" "
        , detail::FormatTimeInMillisecAsSecond(test.elapsed_time()).c_str()
        , detail::FormatTimeInMillisecAsIso8601(test.start_timestamp()).c_str()
        );
    if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
    {
        file->Printf("random_seed=\"%d\" ", test.random_seed());
    }
    file->Printf("name=\"AllTests\"");

    // propertys
    OnReportTestProperty(file, *test.ad_hoc_test_result(), UnitTest::ValidateTestPropertyName);

    file->Printf(">\n");

    for( int i=0, count=test.total_test_suite_count(); i < count; ++i )
    {
        OnReportTestSuite(file, *test.GetTestSuite(i));
    }
    file->Printf("</testsuites>\n");
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnReportTestSuite(IFile* file, const TestSuite& test_suite)
{
    if( test_suite.reportable_test_count() <= 0 )
    {
        return;
    }

    file->Printf("  <testsuite ");
    OutputXmlAttribute(file, "name"
        , EscapeXmlAttribute(test_suite.testsuite_name_with_default_package_name()).c_str());
    file->Printf("tests=\"%d\" failures=\"%d\" disabled=\"%d\" "
        , test_suite.reportable_test_count()
        , test_suite.failed_test_count()
        , test_suite.reportable_disabled_test_count()
        );
#if IUTEST_HAS_REPORT_SKIPPED
    file->Printf("skip=\"%d\" ", test_suite.reportable_skip_test_count() );
#endif
    file->Printf("errors=\"0\" time=\"%s\" timestamp=\"%s\""
        , detail::FormatTimeInMillisecAsSecond(test_suite.elapsed_time()).c_str()
        , detail::FormatTimeInMillisecAsIso8601(test_suite.start_timestamp()).c_str()
        );

    // propertys
    OnReportTestProperty(file, *test_suite.ad_hoc_test_result(), TestSuite::ValidateTestPropertyName);

    file->Printf(">\n");

    for( int i=0, count=test_suite.total_test_count(); i < count; ++i )
    {
        OnReportTestInfo(file, *test_suite.GetTestInfo(i));
    }
    file->Printf("  </testsuite>\n");
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnReportTestInfo(IFile* file, const TestInfo& test_info)
{
    if( !test_info.is_reportable() )
    {
        return;
    }

    file->Printf("    <testsuite ");
    OutputXmlAttribute(file, "name", EscapeXmlAttribute(test_info.name()).c_str() );

    {
        const char* type_param = test_info.type_param();
        if( type_param != NULL )
        {
            OutputXmlAttribute(file, "type_param"
                , EscapeXmlAttribute(type_param).c_str() );
        }
    }
    {
        const char* value_param = test_info.value_param();
        if( value_param != NULL )
        {
            OutputXmlAttribute(file, "value_param"
                , EscapeXmlAttribute(value_param).c_str() );
        }
    }

    if( test_info.is_ran() )
    {
        file->Printf("status=\"run\" ");
    }
    else
    {
        file->Printf("status=\"notrun\" ");
    }
    file->Printf("time=\"%s\" "
        , detail::FormatTimeInMillisecAsSecond(test_info.elapsed_time()).c_str()
        );
    OutputXmlAttribute(file, "classname"
        , EscapeXmlAttribute(test_info.testsuite_name_with_default_package_name()).c_str());

    // propertys
    OnReportTestProperty(file, *test_info.result(), TestInfo::ValidateTestPropertyName);

    const bool notrun = test_info.should_run() && !test_info.is_ran();
    if( test_info.HasFailure() || notrun )
    {
        file->Printf(">\n");
        for( int i=0, count=test_info.result()->total_part_count(); i < count; ++i )
        {
            const TestPartResult& part = test_info.result()->GetTestPartResult(i);
            if( part.passed() )
            {
                continue;
            }

            file->Printf("      <failure ");
            OutputXmlAttribute(file, "message"
                , EscapeXmlAttribute(part.summary()).c_str());
            file->Printf("type=\"\">");
            ::std::string message = detail::FormatCompilerIndependentFileLocation(part.file_name(), part.line_number());
            message += "\n";
            message += detail::MultiByteStringToUTF8(part.summary());
            OutputXmlCDataSection(file, message.c_str());
            file->Printf("\n      </failure>\n");
        }
        if( notrun )
        {
            file->Printf("      <failure message=\"Not Run\" type=\"\">");
            OutputXmlCDataSection(file, "Not Run");
            file->Printf("\n      </failure>\n");
        }
        file->Printf("    </testsuite>\n");
    }
    else
    {
#if IUTEST_HAS_REPORT_SKIPPED
        const bool skipped = test_info.is_skipped() || !test_info.should_run();
        if( skipped )
        {
            file->Printf(">\n");
            OnReportTestSkipped(file, test_info);
            file->Printf("    </testsuite>\n");
        }
        else
#endif
        {
            file->Printf(" />\n");
        }
    }
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnReportTestSkipped(IFile* file, const TestInfo& test_info)
{
    file->Printf("      <skipped type=\"iutest.skip\" ");
    const TestResult* tr = test_info.result();
    const int count = tr->total_part_count();
    for( int i=0; i < count; ++i )
    {
        const TestPartResult& part = tr->GetTestPartResult(i);
        if( part.skipped() )
        {
            ::std::string message = detail::FormatCompilerIndependentFileLocation(part.file_name(), part.line_number());
#if 0
            OutputXmlAttribute(file, "message"
                , EscapeXmlAttribute(part.summary()).c_str());
            file->Printf(">\n");
            message += "\n";
            message += detail::MultiByteStringToUTF8(part.summary());
            OutputXmlCDataSection(file, message.c_str());
            file->Printf("\n      </skipped>\n");
#else
            message += ": ";
            message += detail::MultiByteStringToUTF8(part.summary());
            OutputXmlAttribute(file, "message"
                , EscapeXmlAttribute(message.c_str()).c_str());
            file->Printf(" />\n");
#endif
            return;
        }
    }
    if( test_info.is_disabled_test() )
    {
        OutputXmlAttribute(file, "message", "disabled test.");
    }

    file->Printf("/>\n");
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OnReportTestProperty(IFile* file, const TestResult& test_result
                                                                        , bool (*pfnValidate)(const ::std::string&))
{
    for( int i=0, count=test_result.test_property_count(); i < count; ++i )
    {
        const TestProperty& prop = test_result.GetTestProperty(i);
        if( (*pfnValidate)(prop.key()) )
        {
            file->Printf(" %s=\"%s\""
                , EscapeXmlAttribute(prop.key()).c_str()
                , EscapeXmlAttribute(prop.value()).c_str()
                );
        }
    }
}

IUTEST_IPP_INLINE bool DefaultXmlGeneratorListener::FileOpen(const char* path)
{
    m_fp = detail::IFileSystem::New();
    if( m_fp == NULL )
    {
        return false;
    }

    if( !m_fp->Open(path, IFile::OpenWrite) )
    {
        fprintf(stderr, "Unable to open file \"%s\".\n", m_output_path.c_str());
        fflush(stderr);
        detail::IFileSystem::Free(m_fp);
        m_fp = NULL;
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::FileClose()
{
    if( m_fp == NULL )
    {
        return;
    }
    m_fp->Close();
    detail::IFileSystem::Free(m_fp);
    m_fp = NULL;
}

IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OutputXmlCDataSection(IFile* file, const char* data)
{
    file->Printf("<![CDATA[");
    file->Write(data, strlen(data), 1);
    file->Printf("]]>");
}
IUTEST_IPP_INLINE void DefaultXmlGeneratorListener::OutputXmlAttribute(IFile* file, const char* name, const char* value)
{
    file->Printf("%s=\"", name);
    file->Write(value, strlen(value), 1 );
    file->Printf("\" ");
}

IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()

IUTEST_IPP_INLINE ::std::string DefaultXmlGeneratorListener::EscapeXml(const char* str, bool is_attribute)
{
    ::std::string msg;
    if( str != NULL )
    {
        for( const char* src = str; *src; ++src )
        {
            const char s = *src;
            switch(s)
            {
            case '<':
                msg += "&lt;";
                break;
            case '>':
                msg += "&gt;";
                break;
            case '&':
                msg += "&amp;";
                break;
            case '\'':
                msg += is_attribute ? "&apos;" : "\'";
                break;
            case '\"':
                msg += is_attribute ? "&quot;" : "\"";
                break;
            default:
                {
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
                    wchar_t wc = 0;
                    const int len = detail::iu_mbtowc(&wc, src, MB_CUR_MAX);
                    if( len > 1 )
                    {
                        msg += detail::AnyStringToUTF8(&wc, 1);
                        src += len-1;
                    }
                    else if( IsValidXmlCharacter(s) )
#else
                    if( IsValidXmlCharacter(s) )
#endif
                    {
                        if( is_attribute && IsWhitespace(s) )
                        {
                            char tmp[8];
                            detail::iu_snprintf(tmp, sizeof(tmp), "&#x%02X;", s);
                            msg += tmp;
                        }
                        else
                        {
                            msg += s;
                        }
                    }
                }
                break;
            }
        }
    }
    return msg;
}

IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_IPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_
