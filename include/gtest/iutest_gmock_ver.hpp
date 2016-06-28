//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_gmock_ver.hpp
 * @brief       google mock version 識別 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_GMOCK_VER_HPP_CBBF82C8_EB6F_4398_BAA6_5B485AC52D36_
#define INCG_IRIS_IUTEST_GMOCK_VER_HPP_CBBF82C8_EB6F_4398_BAA6_5B485AC52D36_

#if defined(IUTEST_USE_GTEST) && defined(IUTEST_USE_GMOCK)

//======================================================================
// include
#include <gmock/gmock.h>

//======================================================================
// define

// google mock version

#ifndef GMOCK_MAJORVER
#  define GMOCK_MAJORVER    0x01        //!< Major Version
#endif

//!< Minor Version
#ifndef GMOCK_MINORVER
#  if   defined(GMOCK_GMOCK_MORE_MATCHERS_H_)
#    define GMOCK_MINORVER  0x07
#  else
// v1.6.0 以前は未対応
#    define GMOCK_MINORVER  0x06
#  endif
#endif

#ifndef GMOCK_BUILD
#  define GTEST_BUILD       0x00        //!< Build
#endif

#ifndef GMOCK_REVISION
#  define GMOCK_REVISION    0x00        //!< Revision
#endif

#ifndef GMOCK_VER
#  define   GMOCK_VER       ((GMOCK_MAJORVER<<24)   \
                            |(GMOCK_MINORVER<<16)   \
                            |(GMOCK_BUILD<<8)       \
                            |(GMOCK_REVISION<<0)    \
                            )   //!< google test version
#endif

#endif

#endif // INCG_IRIS_IUTEST_GMOCK_VER_HPP_CBBF82C8_EB6F_4398_BAA6_5B485AC52D36_
