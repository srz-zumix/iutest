//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util.hpp
 * @brief       iris unit test utility
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_HPP_EBAC3846_4D1E_4B32_A85F_6D6A7CCFAF75_
#define INCG_IRIS_IUTEST_UTIL_HPP_EBAC3846_4D1E_4B32_A85F_6D6A7CCFAF75_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "util/iutest_util_assertion.hpp"
#include "util/iutest_util_output.hpp"
#include "util/iutest_util_quiet_result_printer.hpp"
#include "util/iutest_util_tests.hpp"
// IWYU pragma: end_exports

#if defined(MS_CPP_UNITTESTFRAMEWORK)
#include "util/iutest_util_vc_unittest.hpp"
#endif

/**
 * @brief iutest utility namespace
*/
namespace iuutil
{

/**
 * @ingroup IUTEST_UTIL
 * @brief   Xml Generator の解放
*/
inline void ReleaseDefaultXmlGenerator()
{
    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    delete listeners.Release(listeners.default_xml_generator());
}

}   // end of namespace iuutil

/**
 * @ingroup     IUTEST_UTIL
 * @brief       ファイルシステムの設定
 * @note        ユーザー定義のファイルクラスを利用するようにするためのマクロです。
*/
#define IUTEST_FILESYSTEM_INSTANTIATE(file_class_name)  IIUT_FILESYSTEM_INSTANTIATE_(file_class_name)

/**
 * @private
 * @{
*/
#define IIUT_FILESYSTEM_INSTANTIATE_(file_class_name)   \
    static ::iutest::FileSystem< file_class_name > IUTEST_ATTRIBUTE_UNUSED_ s_iutest_filesystem_

/**
 * @}
*/

#endif // INCG_IRIS_IUTEST_UTIL_HPP_EBAC3846_4D1E_4B32_A85F_6D6A7CCFAF75_
