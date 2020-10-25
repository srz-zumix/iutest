//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_all.cpp
 * @brief       iris unit test 実装 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#define IUTEST_USE_LIB 1
#define IUTEST_HAS_EXTERN_TEMPLATE 0
#include "../include/iutest.hpp"

template class ::std::vector< ::iutest::detail::iuIObject* >;
template class ::std::vector< ::iutest::Environment* >;
template class ::std::vector< ::iutest::TestEventListener* >;
template class ::std::vector< ::std::basic_string<char> >;
template class ::std::vector< ::std::basic_string<wchar_t> >;

// ipp
#include "../include/impl/iutest_port.ipp"                  // IWYU pragma: keep
#include "../include/impl/iutest_body.ipp"                  // IWYU pragma: keep
#include "../include/impl/iutest_suite.ipp"                 // IWYU pragma: keep
#include "../include/impl/iutest_core.ipp"                  // IWYU pragma: keep
#include "../include/impl/iutest_core_impl.ipp"             // IWYU pragma: keep
#include "../include/impl/iutest_info.ipp"                  // IWYU pragma: keep
#include "../include/impl/iutest_env.ipp"                   // IWYU pragma: keep
#include "../include/impl/iutest_listener.ipp"              // IWYU pragma: keep
#include "../include/impl/iutest_message.ipp"               // IWYU pragma: keep
#include "../include/impl/iutest_regex.ipp"                 // IWYU pragma: keep
#include "../include/impl/iutest_charcode.ipp"              // IWYU pragma: keep
#include "../include/impl/iutest_time.ipp"                  // IWYU pragma: keep

#include "../include/impl/iutest_debug.ipp"                 // IWYU pragma: keep
#include "../include/impl/iutest_filepath.ipp"              // IWYU pragma: keep

#include "../include/impl/iutest_default_printer.ipp"       // IWYU pragma: keep
#include "../include/impl/iutest_default_xml_generator.ipp" // IWYU pragma: keep
#include "../include/impl/iutest_junit_xml_generator.ipp"   // IWYU pragma: keep
#include "../include/impl/iutest_streaming_listener.ipp"    // IWYU pragma: keep
