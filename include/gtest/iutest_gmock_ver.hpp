//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_gmock_ver.hpp
 * @brief       google mock version 識別 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2018, Takazumi Shirayanagi\n
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
#  if   !defined(GTEST_INCLUDE_GTEST_INTERNAL_GTEST_LINKED_PTR_H_)
#    define GMOCK_MINORVER  0x08
#    define GMOCK_LATEST    1
#  elif defined(GMOCK_INCLUDE_GMOCK_INTERNAL_CUSTOM_CALLBACK_MATCHERS_H_)
#    define GMOCK_MINORVER  0x08
#  elif defined(GMOCK_GMOCK_MORE_MATCHERS_H_)
#    define GMOCK_MINORVER  0x07
#  elif !defined(GMOCK_COMPILE_ASSERT_)
#    define GMOCK_MINORVER  0x06
#  elif defined(GMOCK_USES_POSIX_RE)
#    define GMOCK_MINORVER  0x04
#  elif defined(GTEST_DISALLOW_COPY_AND_ASSIGN_)
#    define GMOCK_MINORVER  0x05
#  else
#    define GMOCK_MINORVER  0x04
#  endif
#endif

//!< Micro Version
#ifndef GMOCK_MICROVER
#  if   GMOCK_MICROVER == 0x08 && defined(GMOCK_INCLUDE_GMOCK_MORE_MATCHERS_H_)
#    define GMOCK_MICROVER  0x01
#  endif
#endif

#ifndef GMOCK_MICROVER
#  define GMOCK_MICROVER  0x00
#endif

#ifndef GMOCK_BUILD
#  define GMOCK_BUILD       GMOCK_MICROVER  //!< @deprecated
#endif

#ifndef GMOCK_REVISION
#  define GMOCK_REVISION    0x00        //!< Revision
#endif

#ifndef GMOCK_VER
#  define   GMOCK_VER       ((GMOCK_MAJORVER<<24)   \
                            |(GMOCK_MINORVER<<16)   \
                            |(GMOCK_MICROVER<<8)    \
                            |(GMOCK_REVISION<<0)    \
                            )   //!< google mock version
#endif

#if !defined(GMOCK_LATEST)
#  define GMOCK_LATEST      0   //!< google mock development latest version
#endif

#endif

#endif // INCG_IRIS_IUTEST_GMOCK_VER_HPP_CBBF82C8_EB6F_4398_BAA6_5B485AC52D36_
