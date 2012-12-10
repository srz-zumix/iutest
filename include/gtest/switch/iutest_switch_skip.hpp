//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_switch_skip.hpp
 * @brief		IUTEST_SKIP 切り替え定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_switch_skip_HPP_3CFB2B8D_9C8D_4b4f_9843_2FE38126BB31_
#define INCG_IRIS_iutest_switch_skip_HPP_3CFB2B8D_9C8D_4b4f_9843_2FE38126BB31_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define

#else

//======================================================================
// undef
#ifdef INCG_IRIS_iutest_HPP_

#undef IUTEST_SKIP

#endif

//======================================================================
// define
#define IUTEST_SKIP()			GTEST_AMBIGUOUS_ELSE_BLOCKER_	\
								if( ::testing::internal::AlwaysTrue() ) return


#endif

#endif
