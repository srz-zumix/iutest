//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_constant.h
 * @brief		iris unit test 定数 定義 ファイル
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
#ifndef INCG_IRIS_iutest_constant_H_37DDDC13_3259_42e0_A648_47B064DED4BA_
#define INCG_IRIS_iutest_constant_H_37DDDC13_3259_42e0_A648_47B064DED4BA_

//======================================================================
// include

namespace iutest {
namespace detail
{

namespace helper
{

/**
 * @brief	文字列定数
*/
template<typename DMY=void>
struct kStringsT
{
	static const char* const DefaultXmlReportFileName;	//!< デフォルト xml 出力ファイル名
	static const char* const UnkownFile;				//!< unkown file
	static const char* const Null;						//!< NULL
};

template<typename DMY>
const char* const kStringsT<DMY>::DefaultXmlReportFileName =  "test_detail.xml";
template<typename DMY>
const char* const kStringsT<DMY>::UnkownFile =  "unkown file";
template<typename DMY>
const char* const kStringsT<DMY>::Null =  "NULL";

}	// end of namespace helper

/** @internal */
typedef helper::kStringsT<>	kStrings;

/**
 * @brief	定数群
*/
struct kValues
{
	static const size_t	MaxPrintContainerCount = 32;
	static const size_t	PrintArrayThreshold = 18;
	static const size_t	PrintArrayChunksize = PrintArrayThreshold/2;
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
