//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_gtest_ver.hpp
 * @brief       gtest version 識別 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_GTEST_VER_HPP_7396AEF4_D1AB_44B5_9FE3_23CEC1240158_
#define INCG_IRIS_IUTEST_GTEST_VER_HPP_7396AEF4_D1AB_44B5_9FE3_23CEC1240158_


//======================================================================
// define

// gtest version

#ifndef GTEST_MAJORVER
#  define GTEST_MAJORVER    0x01        //!< Major Version
#endif

//!< Minor Version
#ifndef GTEST_MINORVER
#  if   defined(GTEST_FLAG_GET)
#    define GTEST_MINORVER  0x11
#    define GTEST_LATEST    1
#  elif defined(GTEST_TEST_NO_THROW_CATCH_STD_EXCEPTION_)
#    define GTEST_MINORVER  0x11
#  elif defined(GTEST_SKIP)
#    define GTEST_MINORVER  0x10
#  elif defined(GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_)
#    define GTEST_MINORVER  0x08
#  elif !defined(RUN_ALL_TESTS) && !defined(GTEST_CREF_WORKAROUND_)
#    define GTEST_MINORVER  0x07
#  elif defined(ADD_FAILURE_AT)
#    define GTEST_MINORVER  0x06
#  elif defined(GTEST_API_)
#    define GTEST_MINORVER  0x05
#  elif defined(EXPECT_DEATH_IF_SUPPORTED)
#    define GTEST_MINORVER  0x04
#  elif defined(GTEST_HIDE_UNREACHABLE_CODE_)
#    define GTEST_MINORVER  0x03
#  elif defined(GTEST_INCLUDE_GTEST_GTEST_PARAM_TEST_H_)
#    define GTEST_MINORVER  0x02
#  elif defined(GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_)
#    define GTEST_MINORVER  0x01
#  else
#    define GTEST_MINORVER  0x00
#  endif
#endif

//!< Micro Version
#ifndef GTEST_MICROVER
#  if   GTEST_MINORVER == 0x08 && defined(GTEST_STRINGIFY_)
#    define GTEST_MICROVER    0x01
#  elif GTEST_MINORVER == 0x02 && defined(GTEST_HAS_CLONE)
#    define GTEST_MICROVER  0x01
#  elif GTEST_MINORVER == 0x00
// 判断難しい
#    define GTEST_MICROVER  0x01
#  endif
#endif

#ifndef GTEST_MICROVER
#  define GTEST_MICROVER    0x00
#endif

#ifndef GTEST_BUILD
#  define GTEST_BUILD       GTEST_MICROVER  //!< @deprecated
#endif

#ifndef GTEST_REVISION
#  define GTEST_REVISION    0x00        //!< Revision
#endif

#ifndef GTEST_VER
#  define   GTEST_VER       ((GTEST_MAJORVER<<24)   \
                            |(GTEST_MINORVER<<16)   \
                            |(GTEST_MICROVER<< 8)   \
                            |(GTEST_REVISION<< 0)   \
                            )   //!< google test version
#endif

#if !defined(GTEST_LATEST)
#  define GTEST_LATEST      0   //!< google test development latest version
#endif

#endif
