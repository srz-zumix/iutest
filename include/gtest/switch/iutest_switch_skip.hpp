//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_skip.hpp
 * @brief       IUTEST_SKIP 切り替え定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
#define INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define
#define GTEST_SKIP  IUTEST_SKIP

#else // !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#if defined(IUTEST_SKIP)
#undef IUTEST_SKIP
#endif

//======================================================================
// define

#if !defined(GTEST_SKIP)
#  define GTEST_SKIP()      GTEST_AMBIGUOUS_ELSE_BLOCKER_   \
                            if( ::testing::internal::AlwaysTrue() ) return GTEST_MESSAGE_("Skipped. ", ::testing::TestPartResult::kSuccess)
#endif

#define IUTEST_SKIP         GTEST_SKIP

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
