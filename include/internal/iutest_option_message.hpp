//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_option_message.hpp
 * @brief       iris unit test コマンドラインメッセージ ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_
#define INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_console.hpp"
// IWYU pragma: end_exports

namespace iutest {
namespace detail
{

//======================================================================
// class
class iuOptionMessage
{
public:
    /**
     * @brief   ヘルプの出力
    */
    static void ShowHelp();
    /**
     * @brief   バージョン出力
    */
    static void ShowVersion();
    /**
     * @brief   機能出力
    */
    static void ShowFeature();
    /**
     * @brief   コンパイラスペック出力
    */
    static void ShowSpec();
};

inline void iuOptionMessage::ShowHelp()
{
    detail::iuConsole::color_output(detail::iuConsole::cyan,
        "--------------------------------------------------\n"
        "Name\n"
        "    iutest - iris unit test framework\n"
        "--------------------------------------------------\n"
        "Command Line Options\n"
        "\n"
        "    --help, -h                       : Generate help message.\n"
        "    --iutest_list_tests              : List up tests.\n"
        "    --iutest_list_tests_with_where   : List up tests with where.\n"
        "    --iutest_color=<yes|no|auto|ansi>: Console color enable.\n"
        "    --iutest_flagfile=<file>         : Set the flag from the file.\n"
        "    --iutest_filter=<filter>         : Select the test run.\n"
        "    --iutest_shuffle                 : Do shuffle test.\n"
        "    --iutest_random_seed=<seed>      : Set random seed.\n"
        "    --iutest_also_run_disabled_tests : Run disabled tests.\n"
        "    --iutest_break_on_failure[=0|1]  : When that failed to break.\n"
        "    --iutest_throw_on_failure[=0|1]  : When that failed to throw.\n"
        "    --iutest_catch_exceptions=<0|1>  : Catch exceptions enable.\n"
        "    --iutest_print_time=<0|1>        : Setting the display of elapsed time.\n"
        "    --iutest_default_package_name=<name>\n"
        "            : Set default root package name.\n"
        "    --iutest_output=<xml|junit>[:path]\n"
        "            : Path of xml report.\n"
        "    --iutest_repeat=<count>\n"
        "            : Set the number of repetitions of the test.\n"
        "              use a negative count to repeat forever.\n"
#if IUTEST_HAS_STREAM_RESULT
        "    --iutest_stream_result_to=<host:port>\n"
        "                                     : Set stream test results server.\n"
#endif
        "    --iutest_file_location=<auto|vs|gcc>\n"
        "                                     : Format file location messages.\n"
        "    --verbose                        : Verbose option.\n"
        "    --feature                        : Show iutest feature.\n"
        "    --version, -v                    : Show iutest version.\n"
        "\n"
        "--------------------------------------------------\n"
        "License\n"
        "\n"
        "    Copyright (c) 2011-2018, Takazumi-Shirayanagi\n"
        "\n"
        "    This software is released under the new BSD License, see LICENSE\n"
        "\n"
    );
}

inline void iuOptionMessage::ShowVersion()
{
    detail::iuConsole::output("iutest version %x.%x.%x.%x\n"
        , IUTEST_MAJORVER, IUTEST_MINORVER, IUTEST_BUILD, IUTEST_REVISION);
}

/** @private */
#define IIUT_SHOW_MACRO(macro)  IIUT_SHOW_MACRO_I(#macro, IUTEST_PP_TOSTRING(macro))
#define IIUT_SHOW_MACRO_I(name, value)  detail::iuConsole::output("#define %s  %s\n", name, value)
#define IIUT_SHOW_ENABLE_MACRO(macro)   IUTEST_PP_IF(macro, IIUT_SHOW_MACRO_I(#macro, IUTEST_PP_TOSTRING(macro)), (void)(0))
#define IIUT_SHOW_DISABLE_MACRO(macro)  IUTEST_PP_IF(macro, (void)(0), IIUT_SHOW_MACRO_I(#macro, IUTEST_PP_TOSTRING(macro)))

/** @private */
#define IIUT_SHOW_FEATURE_MACROS(m) \
    m (IUTEST_HAS_ANY_PARAM_TEST); \
    m (IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT); \
    m (IUTEST_HAS_ASSERTION_RETURN); \
    m (IUTEST_HAS_AUTOFIXTURE_PARAM_TEST); \
    m (IUTEST_HAS_COMBINE); \
    m (IUTEST_HAS_CONCAT); \
    m (IUTEST_HAS_CSVPARAMS); \
    m (IUTEST_HAS_EXCEPTIONS); \
    m (IUTEST_HAS_GENRAND); \
    m (IUTEST_HAS_IGNORE_TEST); \
    m (IUTEST_HAS_LIB); \
    m (IUTEST_HAS_MATCHERS); \
    m (IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF); \
    m (IUTEST_HAS_MATCHER_EACH); \
    m (IUTEST_HAS_MATCHER_ELEMENTSARE); \
    m (IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR);   \
    m (IUTEST_HAS_MATCHER_OPTIONAL); \
    m (IUTEST_HAS_MATCHER_POINTWISE); \
    m (IUTEST_HAS_MATCHER_REGEX); \
    m (IUTEST_HAS_MATCHER_VARIADIC); \
    m (IUTEST_HAS_MINIDUMP); \
    m (IUTEST_HAS_PACKAGE); \
    m (IUTEST_HAS_PAIRWISE); \
    m (IUTEST_HAS_PARAM_METHOD_TEST); \
    m (IUTEST_HAS_PARAM_TEST); \
    m (IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR); \
    m (IUTEST_HAS_PEEP); \
    m (IUTEST_HAS_PEEP_CLASS); \
    m (IUTEST_HAS_PEEP_FUNC); \
    m (IUTEST_HAS_PEEP_STATIC_FUNC); \
    m (IUTEST_HAS_PRINT_TO); \
    m (IUTEST_HAS_RANDOMVALUES); \
    m (IUTEST_HAS_REGEX); \
    m (IUTEST_HAS_REPORT_SKIPPED); \
    m (IUTEST_HAS_SOCKET); \
    m (IUTEST_HAS_SPI_LAMBDA_SUPPORT); \
    m (IUTEST_HAS_STATIC_ASSERT); \
    m (IUTEST_HAS_STATIC_ASSERT_TYPEEQ); \
    m (IUTEST_HAS_STREAM_BUFFER); \
    m (IUTEST_HAS_STREAM_RESULT); \
    m (IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE); \
    m (IUTEST_HAS_TESTNAME_ALIAS); \
    m (IUTEST_HAS_TESTNAME_ALIAS_JP); \
    m (IUTEST_HAS_TYPED_TEST); \
    m (IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME); \
    m (IUTEST_HAS_TYPED_TEST_P); \
    m (IUTEST_HAS_VALUESGEN); \
    m (IUTEST_HAS_VARIADIC_COMBINE); \
    m (IUTEST_HAS_VARIADIC_PAIRWISE); \
    m (IUTEST_HAS_VARIADIC_VALUES)

inline void iuOptionMessage::ShowFeature()
{
#if 0
    IIUT_SHOW_FEATURE_MACROS(IIUT_SHOW_MACRO);
#else
    IIUT_SHOW_FEATURE_MACROS(IIUT_SHOW_ENABLE_MACRO);
    IIUT_SHOW_FEATURE_MACROS(IIUT_SHOW_DISABLE_MACRO);
#endif
}

inline void iuOptionMessage::ShowSpec()
{
    IIUT_SHOW_MACRO(IUTEST_PLATFORM);

    IIUT_SHOW_MACRO(IUTEST_CHECK_STRICT);
    IIUT_SHOW_MACRO(IUTEST_CPLUSPLUS);
    IIUT_SHOW_MACRO(IUTEST_FORCE_COLORCONSOLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_ANALYSIS_ASSUME);
    IIUT_SHOW_MACRO(IUTEST_HAS_ATTRIBUTE);
    IIUT_SHOW_MACRO(IUTEST_HAS_ATTRIBUTE_DEPRECATED);
    IIUT_SHOW_MACRO(IUTEST_HAS_ATTRIBUTE_LIKELY_UNLIKELY);
    IIUT_SHOW_MACRO(IUTEST_HAS_AUTO);
    IIUT_SHOW_MACRO(IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION);
    IIUT_SHOW_MACRO(IUTEST_HAS_CHAR16_T);
    IIUT_SHOW_MACRO(IUTEST_HAS_CHAR16_T_PRINTABLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_CHAR32_T);
    IIUT_SHOW_MACRO(IUTEST_HAS_CHAR32_T_PRINTABLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_CLOCK);
    IIUT_SHOW_MACRO(IUTEST_HAS_COLORCONSOLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_CONCEPTS);
    IIUT_SHOW_MACRO(IUTEST_HAS_CONSTEXPR);
    IIUT_SHOW_MACRO(IUTEST_HAS_CONSTEXPR_IF);
    IIUT_SHOW_MACRO(IUTEST_HAS_COUNTER_MACRO);
    IIUT_SHOW_MACRO(IUTEST_HAS_CTIME);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_ANY);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_ARRAY);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CHARCONV);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CHRONO);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CODECVT);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CSTDINT);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CUCHAR);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_FILESYSTEM);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_OPTIONAL);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_RANDOM);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_REGEX);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_STRING_VIEW);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_TYPE_TARITS);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_VARIANT);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_VERSION);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX11);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX14);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX1Z);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX17);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX2A);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX20);
    IIUT_SHOW_MACRO(IUTEST_HAS_CXX2B);
    IIUT_SHOW_MACRO(IUTEST_HAS_DECLTYPE);
    IIUT_SHOW_MACRO(IUTEST_HAS_DEFAULT_FUNCTIONS);
    IIUT_SHOW_MACRO(IUTEST_HAS_DELETED_FUNCTIONS);
    IIUT_SHOW_MACRO(IUTEST_HAS_EXCEPTIONS);
    IIUT_SHOW_MACRO(IUTEST_HAS_EXPLICIT_CONVERSION);
    IIUT_SHOW_MACRO(IUTEST_HAS_EXTERN_TEMPLATE);
    IIUT_SHOW_MACRO(IUTEST_HAS_FLOAT128);
    IIUT_SHOW_MACRO(IUTEST_HAS_GETTIMEOFDAY);
    IIUT_SHOW_MACRO(IUTEST_HAS_HDR_CXXABI);
    IIUT_SHOW_MACRO(IUTEST_HAS_HDR_SYSTIME);
    IIUT_SHOW_MACRO(IUTEST_HAS_IF_EXISTS);
    IIUT_SHOW_MACRO(IUTEST_HAS_INITIALIZER_LIST);
    IIUT_SHOW_MACRO(IUTEST_HAS_INLINE_VARIABLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_INT128);
    IIUT_SHOW_MACRO(IUTEST_HAS_IOMANIP);
    IIUT_SHOW_MACRO(IUTEST_HAS_LAMBDA);
    IIUT_SHOW_MACRO(IUTEST_HAS_LAMBDA_STATEMENTS);
    IIUT_SHOW_MACRO(IUTEST_HAS_LONG_DOUBLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION);
    IIUT_SHOW_MACRO(IUTEST_HAS_NOEXCEPT);
    IIUT_SHOW_MACRO(IUTEST_HAS_NULLPTR);
    IIUT_SHOW_MACRO(IUTEST_HAS_OVERRIDE_AND_FINAL);
    IIUT_SHOW_MACRO(IUTEST_HAS_RTTI);
    IIUT_SHOW_MACRO(IUTEST_HAS_RVALUE_REFS);
    IIUT_SHOW_MACRO(IUTEST_HAS_SEH);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_BEGIN_END);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_DECLVAL);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_EMPLACE);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_FILESYSTEM);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_QUICK_EXIT);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_STR_TO_VALUE);
    IIUT_SHOW_MACRO(IUTEST_HAS_STD_TO_CHARS);
    IIUT_SHOW_MACRO(IUTEST_HAS_STRINGSTREAM);
    IIUT_SHOW_MACRO(IUTEST_HAS_STRONG_ENUMS);
    IIUT_SHOW_MACRO(IUTEST_HAS_STRSTREAM);
    IIUT_SHOW_MACRO(IUTEST_HAS_TUPLE);
    IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_TEMPLATES);
    IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES);
    IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_TUPLES);
    IIUT_SHOW_MACRO(IUTEST_HAS_WANT_SECURE_LIB);
    IIUT_SHOW_MACRO(IUTEST_LONG_DOUBLE_AS_IS_DOUBLE);
    IIUT_SHOW_MACRO(IUTEST_USE_OWN_LIST);
    IIUT_SHOW_MACRO(IUTEST_USE_OWN_STRING_VIEW);
    IIUT_SHOW_MACRO(IUTEST_USE_THROW_ON_ASSERTION_FAILURE);
    IIUT_SHOW_MACRO(IUTEST_WCHAR_UNSIGNED);

#ifdef IUTEST_LIBSTDCXX_VERSION
    IIUT_SHOW_MACRO(IUTEST_LIBSTDCXX_VERSION);
#endif

#ifdef _MSC_FULL_VER
    IIUT_SHOW_MACRO(_MSC_FULL_VER);
#endif
#ifdef __GLIBCXX__
    IIUT_SHOW_MACRO(__GLIBCXX__);
#endif
#ifdef __GLIBCPP__
    IIUT_SHOW_MACRO(__GLIBCPP__);
#endif
#ifdef _GLIBCXX_USE_CXX11_ABI
    IIUT_SHOW_MACRO(_GLIBCXX_USE_CXX11_ABI);
#endif
#ifdef _LIBCPP_VERSION
    IIUT_SHOW_MACRO(_LIBCPP_VERSION);
#endif
#ifdef __POSIX_VISIBLE
    IIUT_SHOW_MACRO(__POSIX_VISIBLE);
#endif
#ifdef __USE_MINGW_ANSI_STDIO
    IIUT_SHOW_MACRO(__USE_MINGW_ANSI_STDIO);
#endif
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
    IIUT_SHOW_MACRO(__MAC_OS_X_VERSION_MIN_REQUIRED);
#endif

#undef IIUT_SHOW_MACRO
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_
