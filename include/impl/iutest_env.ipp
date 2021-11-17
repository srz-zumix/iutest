//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_env.ipp
 * @brief       iris unit test 環境 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ENV_IPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_
#define INCG_IRIS_IUTEST_ENV_IPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_

//======================================================================
// include
#include "../iutest_env.hpp"
#include "../internal/iutest_file.hpp"

namespace iutest
{

IUTEST_IPP_INLINE void Environment::Release()
{
    TestEnv::ReleaseGlobalTestEnvironment(this);
}

IUTEST_IPP_INLINE ::std::string TestEnv::get_report_xml_filepath()
{
    const ::std::string& option = get_vars().m_output_option;
    const char spec[] = "xml";
    const size_t length = sizeof(spec) - 1;
    if( option.compare(0, length, spec) == 0 )
    {
        if( (option.length() > length + 1) && (option.at(length) == ':') )
        {
            return option.substr(length + 1);
        }
        return detail::kStrings::DefaultXmlReportFileName;
    }
    return "";
}

IUTEST_IPP_INLINE::std::string TestEnv::get_report_junit_xml_filepath()
{
    const ::std::string& option = get_vars().m_output_option;
    const char spec[] = "junit";
    const size_t length = sizeof(spec) - 1;
    if( option.compare(0, length, spec) == 0 )
    {
        if( (option.length() > length + 1) && (option.at(length) == ':') )
        {
            return option.substr(length + 1);
        }
        return detail::kStrings::DefaultXmlReportFileName;
    }
    return "";
}

IUTEST_IPP_INLINE::std::string TestEnv::AddDefaultPackageName(const char* testsuite_name)
{
    ::std::string str = TestEnv::get_default_package_name();
    if( str.empty() )
    {
        return testsuite_name;
    }
    if( strchr(testsuite_name, '.') != NULL )
    {
        return testsuite_name;
    }

    str += ".";
    str += testsuite_name;
    return str;
}

IUTEST_IPP_INLINE bool TestEnv::ParseCommandLineElemA(const char* str)
{
    if( *str == '-' )
    {
        ++str;
        if( *str == '-' )
        {
            ++str;
            bool iuoption = false;
            {
                const char* const base_str = str;
                if( *str == 'g' )
                {
                    ++str;
                    iuoption = true;
                }
                else if(*str == 'i' && *(str+1) == 'u' )
                {
                    str += 2;
                    iuoption = true;
                }
                const char option_prefix[] = "test_";
                for( int i=0, size=sizeof(option_prefix)/sizeof(option_prefix[0])-1; i < size; ++i, ++str )
                {
                    if( *str != option_prefix[i] )
                    {
                        iuoption = false;
                        str = base_str;
                        break;
                    }
                }
            }
            if( iuoption )
            {
                if( ParseIutestOptionCommandLineElemA(str) )
                {
                    return true;
                }
                // 該当するオプションがない場合はヘルプ表示
                TestFlag::SetFlag(TestFlag::SHOW_HELP);
            }
            else
            {
                if( detail::IsStringEqual(str, "help") )
                {
                    return SetFlag(TestFlag::SHOW_HELP);
                }
                if( detail::IsStringEqual(str, "version") )
                {
                    return SetFlag(TestFlag::SHOW_VERSION);
                }
                if( detail::IsStringEqual(str, "feature") )
                {
                    return SetFlag(TestFlag::SHOW_FEATURE);
                }
                if( detail::IsStringEqual(str, "spec") )
                {
                    return SetFlag(TestFlag::SHOW_SPEC);
                }
                if( detail::IsStringEqual(str, "verbose") )
                {
                    return SetFlag(TestFlag::VERBOSE);
                }
            }
        }
        else
        {
            if( detail::IsStringEqual(str, "v") )
            {
                return SetFlag(TestFlag::SHOW_VERSION);
            }
            if( detail::IsStringEqual(str, "h")
                || detail::IsStringEqual(str, "?") )
            {
                return SetFlag(TestFlag::SHOW_HELP);
            }
        }
    }
    return false;
}

IUTEST_IPP_INLINE bool TestEnv::ParseIutestOptionCommandLineElemA(const char* str)
{
    // --iutest_*
    if( detail::IsStringForwardMatching(str, "output") )
    {
        return ParseOutputOption(ParseOptionSettingStr(str));
    }
    if( detail::IsStringEqual(str, "list_tests") )
    {
        return SetFlag(TestFlag::SHOW_TESTS_LIST);
    }
    if( detail::IsStringEqual(str, "list_tests_with_where") )
    {
        return SetFlag(TestFlag::SHOW_TESTS_LIST_WITH_WHERE);
    }
    if( detail::IsStringForwardMatching(str, "color") )
    {
        return ParseColorOption(ParseOptionSettingStr(str));
    }
    if( detail::IsStringEqual(str, "shuffle") )
    {
        return SetFlag(TestFlag::SHUFFLE_TESTS);
    }
    if( detail::IsStringForwardMatching(str, "random_seed") )
    {
        const char* opt = ParseOptionSettingStr(str);
        if( opt != NULL )
        {
            char* end = NULL;
            const long seed = strtol(opt, &end, 0);
            init_random(static_cast<unsigned int>(seed));
            return true;
        }
    }
    if( detail::IsStringEqual(str, "also_run_disabled_tests") )
    {
        return SetFlag(TestFlag::RUN_DISABLED_TESTS);
    }
    if( detail::IsStringForwardMatching(str, "break_on_failure") )
    {
        return ParseYesNoFlagCommandLine(str, TestFlag::BREAK_ON_FAILURE, 1);
    }
    if( detail::IsStringForwardMatching(str, "catch_exceptions") )
    {
        return ParseYesNoFlagCommandLine(str, TestFlag::CATCH_EXCEPTION, -1);
    }
    if( detail::IsStringForwardMatching(str, "throw_on_failure") )
    {
        return ParseYesNoFlagCommandLine(str, TestFlag::THROW_ON_FAILURE, 1);
    }
    if (detail::IsStringForwardMatching(str, "warning_into_error"))
    {
        return ParseYesNoFlagCommandLine(str, TestFlag::WARNING_INTO_ERROR, 1);
    }
    if( detail::IsStringForwardMatching(str, "print_time") )
    {
        return ParseYesNoFlagCommandLine(str, TestFlag::PRINT_TIME, -1);
    }
    if( detail::IsStringForwardMatching(str, "repeat") )
    {
        const char* opt = ParseOptionSettingStr(str);
        if( opt != NULL )
        {
            char* end = NULL;
            const long count = strtol(opt, &end, 0);
            set_repeat_count(static_cast<int>(count));
            return true;
        }
    }
    if( detail::IsStringForwardMatching(str, "filter") )
    {
        return ParseFilterOption(ParseOptionSettingStr(str));
    }
    if( detail::IsStringForwardMatching(str, "flagfile") )
    {
        return ParseFlagFileOption(ParseOptionSettingStr(str));
    }
#if IUTEST_HAS_STREAM_RESULT
    if( detail::IsStringForwardMatching(str, "stream_result_to") )
    {
        const char* opt = ParseOptionSettingStr(str);
        if( opt != NULL )
        {
            set_stream_result_to(opt);
            return true;
        }
    }
#endif
    if( detail::IsStringForwardMatching(str, "file_location") )
    {
        return ParseFileLocationOption(ParseOptionSettingStr(str));
    }
    if( detail::IsStringForwardMatching(str, "default_package_name") )
    {
        const char* opt = ParseOptionSettingStr(str);
        if (opt != NULL)
        {
            set_default_package_name(opt);
            return true;
        }
    }
    if( detail::IsStringForwardMatching(str, "locale_ctype") )
    {
        const char* opt = ParseOptionSettingStr(str);
        set_locale_ctype(opt);
        return true;
    }
    return false;
}

IUTEST_IPP_INLINE bool TestEnv::SetFlag(int enable, int mask)
{
    TestFlag::SetFlag(enable, mask);
    return true;
}

IUTEST_IPP_INLINE void TestEnv::LoadEnvironmentVariable()
{
#if !defined(__WANDBOX__)
    {
        int var = 0;
        if( detail::GetEnvironmentInt("IUTEST_ALSO_RUN_DISABLED_TESTS", var)
        ||  detail::GetEnvironmentInt("GTEST_ALSO_RUN_DISABLED_TESTS", var) )
        {
            TestFlag::SetFlag(TestFlag::RUN_DISABLED_TESTS
                , var ? TestFlag::MASK : ~(TestFlag::RUN_DISABLED_TESTS) );
        }
        if( detail::GetEnvironmentInt("IUTEST_SHUFFLE", var)
        ||  detail::GetEnvironmentInt("GTEST_SHUFFLE", var) )
        {
            TestFlag::SetFlag(TestFlag::SHUFFLE_TESTS
                , var ? TestFlag::MASK : ~(TestFlag::SHUFFLE_TESTS) );
        }
        if( detail::GetEnvironmentInt("IUTEST_RANDOM_SEED", var)
        ||  detail::GetEnvironmentInt("GTEST_RANDOM_SEED", var) )
        {
            init_random((unsigned int)var);
        }
        if( detail::GetEnvironmentInt("IUTEST_CATCH_EXCEPTIONS", var)
        ||  detail::GetEnvironmentInt("GTEST_CATCH_EXCEPTIONS", var) )
        {
            TestFlag::SetFlag(TestFlag::CATCH_EXCEPTION
                , var ? TestFlag::MASK : ~(TestFlag::CATCH_EXCEPTION) );
        }
        if( detail::GetEnvironmentInt("IUTEST_BREAK_ON_FAILURE", var)
        ||  detail::GetEnvironmentInt("GTEST_BREAK_ON_FAILURE", var) )
        {
            TestFlag::SetFlag(TestFlag::BREAK_ON_FAILURE
                , var ? TestFlag::MASK : ~(TestFlag::BREAK_ON_FAILURE) );
        }
        if( detail::GetEnvironmentInt("IUTEST_THROW_ON_FAILURE", var)
        ||  detail::GetEnvironmentInt("GTEST_THROW_ON_FAILURE", var) )
        {
            TestFlag::SetFlag(TestFlag::THROW_ON_FAILURE
                , var ? TestFlag::MASK : ~(TestFlag::THROW_ON_FAILURE) );
        }
        if (detail::GetEnvironmentInt("IUTEST_WARNING_INTO_ERROR", var))
        {
            TestFlag::SetFlag(TestFlag::WARNING_INTO_ERROR
                , var ? TestFlag::MASK : ~(TestFlag::WARNING_INTO_ERROR));
        }
        if( detail::GetEnvironmentInt("IUTEST_PRINT_TIME", var)
        ||  detail::GetEnvironmentInt("GTEST_PRINT_TIME", var) )
        {
            TestFlag::SetFlag(TestFlag::PRINT_TIME
                , var ? TestFlag::MASK : ~(TestFlag::PRINT_TIME) );
        }
        if( detail::GetEnvironmentInt("IUTEST_REPEAT", var)
        ||  detail::GetEnvironmentInt("GTEST_REPEAT", var) )
        {
            set_repeat_count(var);
        }
    }
    {
        char var[128] = {0};
        if( detail::GetEnvironmentVariable("IUTEST_COLOR", var, sizeof(var))
        ||  detail::GetEnvironmentVariable("GTEST_COLOR", var, sizeof(var)) )
        {
            ParseColorOption(var);
        }
        if( detail::GetEnvironmentVariable("IUTEST_FILE_LOCATION", var, sizeof(var)) )
        {
            ParseFileLocationOption(var);
        }
    }
    {
        char str[260+32] = {0};
        if( detail::GetEnvironmentVariable("IUTEST_OUTPUT", str, sizeof(str))
        ||  detail::GetEnvironmentVariable("GTEST_OUTPUT", str, sizeof(str)) )
        {
            ParseOutputOption(str);
        }
        else if( detail::GetEnvironmentVariable("XML_OUTPUT_FILE", str+4, sizeof(str) - 4) )
        {
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
            memcpy(str, "xml:", 4);
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
            ParseOutputOption(str);
        }
        if( detail::GetEnvironmentVariable("IUTEST_FILTER", str, sizeof(str))
        ||  detail::GetEnvironmentVariable("GTEST_FILTER", str, sizeof(str)) )
        {
            ParseFilterOption(str);
        }
        if(detail::GetEnvironmentVariable("IUTEST_DEFAULT_PACKAGE_NAME", str, sizeof(str)))
        {
            set_default_package_name(str);
        }
#if IUTEST_HAS_STREAM_RESULT
        if( detail::GetEnvironmentVariable("IUTEST_STREAM_RESULT_TO", str, sizeof(str))
        ||  detail::GetEnvironmentVariable("GTEST_STREAM_RESULT_TO", str, sizeof(str)) )
        {
            set_stream_result_to(str);
        }
#endif
        if(detail::GetEnvironmentVariable("IUTEST_FLAGFILE", str, sizeof(str))
            || detail::GetEnvironmentVariable("GTEST_FLAGFILE", str, sizeof(str)))
        {
            ParseFlagFileOption(str);
        }
    }
#endif
}

IUTEST_IPP_INLINE void TestEnv::SetUp()
{
    unsigned int seed = get_random_seed();
    if( (seed == 0)
        || (get_vars().m_current_random_seed != 0 && TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS)) )
    {
        const unsigned int gen_seeed = detail::GetIndefiniteValue();
        if( get_vars().m_current_random_seed == gen_seeed
            || get_vars().m_before_origin_random_seed == gen_seeed )
        {
            seed = get_vars().m_current_random_seed;
        }
        seed += gen_seeed;
        get_vars().m_before_origin_random_seed = gen_seeed;
    }
    get_vars().m_current_random_seed = seed;
    genrand().init(seed);
}

IUTEST_IPP_INLINE bool TestEnv::ParseColorOption(const char* option)
{
    if( option == NULL )
    {
        return false;
    }

    if( IsYes(option) )
    {
        TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON, ~(TestFlag::CONSOLE_COLOR_OFF|TestFlag::CONSOLE_COLOR_ANSI));
    }
    else if( IsNo(option) )
    {
        TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_OFF, ~(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_ANSI));
    }
    else if( detail::IsStringCaseEqual(option, "auto") )
    {
        // auto
        TestFlag::SetFlag(0, ~(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_OFF|TestFlag::CONSOLE_COLOR_ANSI));
    }
    else if( detail::IsStringCaseEqual(option, "ansi") )
    {
        // ansi
        TestFlag::SetFlag(TestFlag::CONSOLE_COLOR_ON|TestFlag::CONSOLE_COLOR_ANSI, ~TestFlag::CONSOLE_COLOR_OFF);
    }
    else
    {
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::ParseOutputOption(const char* option)
{
    if(option == NULL)
    {
        get_vars().m_output_option = "";
        return false;
    }
    set_output_option(option);
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::ParseFileLocationOption(const char* option)
{
    if( option == NULL )
    {
        return false;
    }

    if( detail::IsStringCaseEqual(option, "auto") )
    {
#if defined(_MSC_VER)
        TestFlag::SetFlag(TestFlag::FILELOCATION_STYLE_MSVC);
#else
        TestFlag::SetFlag(0, ~TestFlag::FILELOCATION_STYLE_MSVC);
#endif
    }
    else if( detail::IsStringCaseEqual(option, "vs") )
    {
        TestFlag::SetFlag(TestFlag::FILELOCATION_STYLE_MSVC);
    }
    else if( detail::IsStringCaseEqual(option, "gcc") )
    {
        TestFlag::SetFlag(0, ~TestFlag::FILELOCATION_STYLE_MSVC);
    }
    else
    {
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::ParseFilterOption(const char* option)
{
    if( option != NULL && *option == '@' )
    {
        // file
        const char* path = option + 1;
        ::std::string filter;
        if(!detail::IFileSystem::ReadAll(path, filter))
        {
            fprintf(stderr, "Unable to open filter file \"%s\".\n", path);
            fflush(stderr);
            return false;
        }

        detail::StringReplaceToLF(filter);
        filter = detail::StringRemoveComment(filter);
        detail::StringReplace(filter, '\n', ":");
        set_test_filter(filter.c_str());
        return true;
    }

    set_test_filter(option);
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::ParseFlagFileOption(const char* option)
{
    if( option == NULL || option[0] == '\0' )
    {
        return false;
    }
    set_flagfile_path(option);
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::LoadFlagFile()
{
    const char* path = get_flagfile();
    if( path == NULL || path[0] == '\0' )
    {
        return true;
    }

    ::std::string flags;
    if(!detail::IFileSystem::ReadAll(path, flags))
    {
        fprintf(stderr, "Unable to open flag file \"%s\".\n", path);
        fflush(stderr);
        return false;
    }
    detail::StringReplaceToLF(flags);
    ::std::vector< ::std::string > argv;
    detail::StringSplit(flags, '\n', argv);
    ParseCommandLine(argv);
    return true;
}

IUTEST_IPP_INLINE bool TestEnv::ParseYesNoFlagCommandLine(const char* str, TestFlag::Kind flag, int def)
{
    const char* option = ParseOptionSettingStr(str);
    const int yesno = option != NULL ? ParseYesNoOption(option) : def;
    if( yesno < 0 )
    {
        return false;
    }
    TestFlag::SetFlag(flag, yesno ? TestFlag::MASK : ~(flag) );
    return true;
}

IUTEST_IPP_INLINE int TestEnv::ParseYesNoOption(const char* option)
{
    if( option != NULL )
    {
        if( IsYes(option) )
        {
            return 1;
        }
        if( IsNo(option) )
        {
            return 0;
        }
    }

    return -1;
}

IUTEST_IPP_INLINE bool TestEnv::IsYes(const char* option)
{
    if( detail::IsStringCaseEqual(option, "yes")
        || detail::IsStringCaseEqual(option, "y")
        || detail::IsStringCaseEqual(option, "on")
        || detail::IsStringCaseEqual(option, "true")
        || detail::IsStringCaseEqual(option, "t")
        || detail::IsStringEqual(option, "1") )
    {
        return true;
    }
    return false;
}

IUTEST_IPP_INLINE bool TestEnv::IsNo(const char* option)
{
    if( detail::IsStringCaseEqual(option, "no")
        || detail::IsStringCaseEqual(option, "n")
        || detail::IsStringCaseEqual(option, "off")
        || detail::IsStringCaseEqual(option, "false")
        || detail::IsStringCaseEqual(option, "f")
        || detail::IsStringEqual(option, "0") )
    {
        return true;
    }
    return false;
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_ENV_IPP_F4017EAB_6CA3_4E6E_8983_059393DADD04_
