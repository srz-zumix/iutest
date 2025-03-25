//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_junit_xml_generator.ipp
 * @brief       output junit xml event listener implementation
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_JUNIT_XML_GENERATOR_IPP_960DA82F_ED4B_438A_9828_D5CD034A454A_
#define INCG_IRIS_IUTEST_JUNIT_XML_GENERATOR_IPP_960DA82F_ED4B_438A_9828_D5CD034A454A_

//======================================================================
// include
#include "../listener/iutest_default_xml_generator.hpp"

namespace iutest
{

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

IUTEST_IPP_INLINE bool JunitXmlGeneratorListener::IsReportable(const UnitTest& test)
{
    const int reportable_test_count = test.reportable_test_count();
    if( reportable_test_count <= 0 )
    {
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportTest(IFile* file, const UnitTest& test)
{
    file->Printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    const int reportable_test_count = test.reportable_test_count();
    file->Printf("<testsuites tests=\"%d\" failures=\"%d\" disabled=\"%d\" "
        , reportable_test_count
        , test.failed_test_count()
        , test.reportable_disabled_test_count()
        );
    file->Printf("errors=\"0\" time=\"%s\" timestamp=\"%s\" "
        , detail::FormatTimeInMillisecAsSecond(test.elapsed_time()).c_str()
        , detail::FormatTimeInMillisecAsIso8601(test.start_timestamp()).c_str()
        );
    file->Printf("name=\"AllTests\">\n");

    for( int i=0, count=test.total_test_suite_count(); i < count; ++i )
    {
        OnReportTestSuite(file, *test.GetTestSuite(i));
    }
    file->Printf("</testsuites>\n");
}

IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportTestSuite(IFile* file, const TestSuite& test_suite)
{
    const int reportable_test_count = test_suite.reportable_test_count();
    if( reportable_test_count <= 0 )
    {
        return;
    }

    file->Printf("  <testsuite ");
    OutputXmlAttribute(file, "name"
        , EscapeXmlAttribute(test_suite.testsuite_name_with_default_package_name()).c_str());
    file->Printf("tests=\"%d\" failures=\"%d\" disabled=\"%d\" "
        , reportable_test_count
        , test_suite.failed_test_count()
        , test_suite.reportable_disabled_test_count()
        );
    file->Printf("skipped=\"%d\" ", test_suite.reportable_skip_test_count() );
    file->Printf("errors=\"0\" time=\"%s\" timestamp=\"%s\">\n"
        , detail::FormatTimeInMillisecAsSecond(test_suite.elapsed_time()).c_str()
        , detail::FormatTimeInMillisecAsIso8601(test_suite.start_timestamp()).c_str()
        );

    file->Printf("    <properties>\n");

    {
        const char* type_param = test_suite.type_param();
        if( type_param != NULL )
        {
            OnReportProperty(file, "type_param", EscapeXmlAttribute(type_param).c_str());
        }
    }
    {
        for( int i=0, count=test_suite.total_test_count(); i < count; ++i )
        {
            const TestInfo& test_info = *test_suite.GetTestInfo(i);
            const char* value_param = test_info.value_param();
            if( value_param != NULL )
            {
                OnReportProperty(file, test_info.name(), EscapeXmlAttribute(value_param).c_str());
            }
        }
    }

    // propertys
    OnReportTestProperty(file, *test_suite.ad_hoc_test_result());

    file->Printf("    </properties>\n");

    {
        for( int i=0, count=test_suite.total_test_count(); i < count; ++i )
        {
            OnReportTestInfo(file, *test_suite.GetTestInfo(i));
        }
    }

    file->Printf("    <system-out />\n");
    file->Printf("    <system-err />\n");
    file->Printf("  </testsuite>\n");
}

IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportTestInfo(IFile* file, const TestInfo& test_info)
{
    if( !test_info.is_reportable() )
    {
        return;
    }

    file->Printf("    <testcase ");
    OutputXmlAttribute(file, "name", EscapeXmlAttribute(test_info.name()).c_str() );
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
    file->Printf(">\n");

    // propertys
    //OnReportTestProperty(file, *test_info.result());

    const bool notrun = test_info.should_run() && !test_info.is_ran();
    if( test_info.HasFailure() || notrun )
    {
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
    }
    else
    {
        const bool skipped = test_info.is_skipped() || !test_info.should_run();
        if( skipped )
        {
            OnReportTestSkipped(file, test_info);
        }
    }
    file->Printf("    </testcase>\n");
}


IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportProperty(IFile* file, const char* name, const char* value)
{
    file->Printf("      <property name=\"%s\" value=\"%s\" />\n", name, value);
}

IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportTestProperty(IFile* file, const TestResult& test_result)
{
    for( int i=0, count=test_result.test_property_count(); i < count; ++i )
    {
        const TestProperty& prop = test_result.GetTestProperty(i);
        OnReportProperty(file
            , EscapeXmlAttribute(prop.key()).c_str()
            , EscapeXmlAttribute(prop.value()).c_str()
            );
    }
}

IUTEST_IPP_INLINE void JunitXmlGeneratorListener::OnReportTestSkipped(IFile* file, const TestInfo& test_info)
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
            message += ": ";
            message += detail::MultiByteStringToUTF8(part.summary());
            OutputXmlAttribute(file, "message"
                , EscapeXmlAttribute(message).c_str());
            file->Printf(" />\n");
            return;
        }
    }
    if( test_info.is_disabled_test() )
    {
        OutputXmlAttribute(file, "message", "disabled test.");
    }

    file->Printf("/>\n");
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_JUNIT_XML_GENERATOR_IPP_960DA82F_ED4B_438A_9828_D5CD034A454A_
