//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_pp.h
 * @brief		iris unit test プリプロセッサ 定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_pp_H_E8F72184_9C72_4e74_B581_A1F51F291F3A_
#define INCG_IRIS_iutest_pp_H_E8F72184_9C72_4e74_B581_A1F51F291F3A_

//======================================================================
// define

#define IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeName)	\
	TypeName( const TypeName& );						\
	TypeName& operator = ( const TypeName& )

#define IUTEST_PP_TOSTRING(z_)		IUTEST_PP_TOSTRING_(z_)
#define IUTEST_PP_TOSTRING_(z__)	#z__

#define IUTEST_PP_CAT(a_, b_)		IUTEST_PP_CAT_(a_, b_)
#define IUTEST_PP_CAT_(a__, b__)	a__##b__

#define IUTEST_UNUSED_VAR(x)		(void)x

#endif
