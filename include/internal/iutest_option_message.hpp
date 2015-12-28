//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_option_message.hpp
 * @brief		iris unit test コマンドラインメッセージ ファイル
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2011-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_
#define INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_

//======================================================================
// include
#include "iutest_console.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// class
class iuOptionMessage
{
public:
	/**
	 * @brief	ヘルプの出力
	*/
	static void ShowHelp(void);
	/**
	 * @brief	バージョン出力
	*/
	static void ShowVersion(void);
	/**
	 * @brief	機能出力
	*/
	static void ShowFeature(void);
	/**
	 * @brief	コンパイラスペック出力
	*/
	static void ShowSpec(void);
};

inline void iuOptionMessage::ShowHelp(void)
{
	const char* readme =
		"--------------------------------------------------\n"
		"Name\n"
		"    iutest - iris unit test framework\n"
		"--------------------------------------------------\n"
		"Command Line Options\n"
		"\n"
		"    --help, -h                       : Generate help message.\n"
		"    --iutest_output=xml[:path]       : Path of xml report.\n"
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
		"    --iutest_repeat=<count>          : Set the number of repetitions\n"
		"                                       of the test.\n"
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
		"    Copyright (c) 2011-2015, Takazumi-Shirayanagi\n"
		"\n"
		"    This software is released under the new BSD License, see LICENSE\n"
		"\n";
	detail::iuConsole::color_output(detail::iuConsole::cyan, readme);
}

inline void iuOptionMessage::ShowVersion(void)
{
	detail::iuConsole::output("iutest version %x.%x.%x.%x\n"
		, IUTEST_MAJORVER, IUTEST_MINORVER, IUTEST_BUILD, IUTEST_REVISION);
}

/** @private */
#define IIUT_SHOW_MACRO(macro)	detail::iuConsole::output("#define %s  %s\n", #macro, IUTEST_PP_TOSTRING(macro))

inline void iuOptionMessage::ShowFeature(void)
{
	IIUT_SHOW_MACRO(IUTEST_HAS_ANY_PARAM_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT);
	IIUT_SHOW_MACRO(IUTEST_HAS_ASSERTION_RETURN);
	IIUT_SHOW_MACRO(IUTEST_HAS_AUTOFIXTURE_PARAM_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_COMBINE);
	IIUT_SHOW_MACRO(IUTEST_HAS_CONCAT);
	IIUT_SHOW_MACRO(IUTEST_HAS_EXCEPTIONS);
	IIUT_SHOW_MACRO(IUTEST_HAS_GENRAND);
	IIUT_SHOW_MACRO(IUTEST_HAS_IGNORE_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_LIB);
	IIUT_SHOW_MACRO(IUTEST_HAS_MATCHERS);
	IIUT_SHOW_MACRO(IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF);
	IIUT_SHOW_MACRO(IUTEST_HAS_MATCHER_ELEMENTSARE);
	IIUT_SHOW_MACRO(IUTEST_HAS_MATCHER_REGEX);
	IIUT_SHOW_MACRO(IUTEST_HAS_MINIDUMP);
	IIUT_SHOW_MACRO(IUTEST_HAS_PACKAGE);
	IIUT_SHOW_MACRO(IUTEST_HAS_PAIRWISE);
	IIUT_SHOW_MACRO(IUTEST_HAS_PARAM_METHOD_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_PARAM_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR);
	IIUT_SHOW_MACRO(IUTEST_HAS_PEEP);
	IIUT_SHOW_MACRO(IUTEST_HAS_PEEP_CLASS);
	IIUT_SHOW_MACRO(IUTEST_HAS_PEEP_FUNC);
	IIUT_SHOW_MACRO(IUTEST_HAS_PEEP_STATIC_FUNC);
	IIUT_SHOW_MACRO(IUTEST_HAS_PRINT_TO);
	IIUT_SHOW_MACRO(IUTEST_HAS_RANDOMVALUES);
	IIUT_SHOW_MACRO(IUTEST_HAS_REGEX);
	IIUT_SHOW_MACRO(IUTEST_HAS_REPORT_SKIPPED);
	IIUT_SHOW_MACRO(IUTEST_HAS_SOCKET);
	IIUT_SHOW_MACRO(IUTEST_HAS_SPI_LAMBDA_SUPPORT);
	IIUT_SHOW_MACRO(IUTEST_HAS_STATIC_ASSERT);
	IIUT_SHOW_MACRO(IUTEST_HAS_STATIC_ASSERT_TYPEEQ);
	IIUT_SHOW_MACRO(IUTEST_HAS_STREAM_BUFFER);
	IIUT_SHOW_MACRO(IUTEST_HAS_STREAM_RESULT);
	IIUT_SHOW_MACRO(IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE);
	IIUT_SHOW_MACRO(IUTEST_HAS_TESTNAME_ALIAS);
	IIUT_SHOW_MACRO(IUTEST_HAS_TESTNAME_ALIAS_JP);
	IIUT_SHOW_MACRO(IUTEST_HAS_TYPED_TEST);
	IIUT_SHOW_MACRO(IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME);
	IIUT_SHOW_MACRO(IUTEST_HAS_TYPED_TEST_P);
	IIUT_SHOW_MACRO(IUTEST_HAS_VALUESGEN);
	IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_COMBINE);
	IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_PAIRWISE);
	IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_VALUES);
	IIUT_SHOW_MACRO(IUTEST_CHECK_STRICT);
	IIUT_SHOW_MACRO(IUTEST_PLATFORM);
	IIUT_SHOW_MACRO(IUTEST_USE_THROW_ON_ASSERTION_FAILURE);
}

inline void iuOptionMessage::ShowSpec(void)
{
	IIUT_SHOW_MACRO(IUTEST_HAS_ANALYSIS_ASSUME);
	IIUT_SHOW_MACRO(IUTEST_HAS_CHAR16_T);
	IIUT_SHOW_MACRO(IUTEST_HAS_CHAR32_T);
	IIUT_SHOW_MACRO(IUTEST_HAS_CLOCK);
	IIUT_SHOW_MACRO(IUTEST_HAS_CONSTEXPR);
	IIUT_SHOW_MACRO(IUTEST_HAS_COUNTER_MACRO);
	IIUT_SHOW_MACRO(IUTEST_HAS_CTIME);
	IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CHRONO);
	IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_CODECVT);
	IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_RANDOM);
	IIUT_SHOW_MACRO(IUTEST_HAS_CXX_HDR_REGEX);
	IIUT_SHOW_MACRO(IUTEST_HAS_CXX11);
	IIUT_SHOW_MACRO(IUTEST_HAS_DELETED_FUNCTIONS);
	IIUT_SHOW_MACRO(IUTEST_HAS_EXCEPTIONS);
	IIUT_SHOW_MACRO(IUTEST_HAS_EXPLICIT_CONVERSION);
	IIUT_SHOW_MACRO(IUTEST_HAS_EXTERN_TEMPLATE);
	IIUT_SHOW_MACRO(IUTEST_HAS_GETTIMEOFDAY);
	IIUT_SHOW_MACRO(IUTEST_HAS_HDR_CXXABI);
	IIUT_SHOW_MACRO(IUTEST_HAS_HDR_SYSTIME);
	IIUT_SHOW_MACRO(IUTEST_HAS_HDR_UCHAR);
	IIUT_SHOW_MACRO(IUTEST_HAS_IF_EXISTS);
	IIUT_SHOW_MACRO(IUTEST_HAS_INITIALIZER_LIST);
	IIUT_SHOW_MACRO(IUTEST_HAS_LAMBDA);
	IIUT_SHOW_MACRO(IUTEST_HAS_LAMBDA_STATEMENTS);
	IIUT_SHOW_MACRO(IUTEST_HAS_NOEXCEPT);
	IIUT_SHOW_MACRO(IUTEST_HAS_NULLPTR);
	IIUT_SHOW_MACRO(IUTEST_HAS_OVERRIDE_AND_FINAL);
	IIUT_SHOW_MACRO(IUTEST_HAS_RTTI);
	IIUT_SHOW_MACRO(IUTEST_HAS_RVALUE_REFS);
	IIUT_SHOW_MACRO(IUTEST_HAS_SEH);
	IIUT_SHOW_MACRO(IUTEST_HAS_STD_BEGIN_END);
	IIUT_SHOW_MACRO(IUTEST_HAS_STD_DECLVAL);
	IIUT_SHOW_MACRO(IUTEST_HAS_STD_EMPLACE);
	IIUT_SHOW_MACRO(IUTEST_HAS_STRINGSTREAM);
	IIUT_SHOW_MACRO(IUTEST_HAS_STRONG_ENUMS);
	IIUT_SHOW_MACRO(IUTEST_HAS_STRSTREAM);
	IIUT_SHOW_MACRO(IUTEST_HAS_TUPLE);
	IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_TEMPLATES);
	IIUT_SHOW_MACRO(IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES);

#ifdef _MSC_FULL_VER
	IIUT_SHOW_MACRO(_MSC_FULL_VER);
#endif
#ifdef _LIBCPP_VERSION
	IIUT_SHOW_MACRO(_LIBCPP_VERSION);
#endif
#ifdef __GLIBCXX__
	IIUT_SHOW_MACRO(__GLIBCXX__);
#endif

#undef IIUT_SHOW_MACRO
}

}	// end of namespace detail
}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_OPTION_MESSAGE_HPP_00EB9B17_0615_4678_9AD0_1F5B295B404F_
