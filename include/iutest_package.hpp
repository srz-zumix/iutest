//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_package.hpp
 * @brief		iris unit test testcase package ファイル
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
#ifndef INCG_IRIS_iutest_package_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_iutest_package_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "internal/iutest_internal_defs.hpp"

//======================================================================
// define
/**
 * @ingroup	TESTDEF
 * @brief	パッケージ名前空間の定義
*/
#define IUTEST_PACKAGE(name)	IUTEST_PACKAGE_(name)

/**
 * @private
 * @{
*/

#if IUTEST_HAS_PACKAGE

#define IUTEST_CONCAT_PACKAGE_(testcase_name)					\
	iuTest_ConcatTestCaseName( iuTest_GetTestCasePackageName(	\
	static_cast<iuTest_TestCasePackage*>(NULL))					\
	, #testcase_name).c_str()

#define IUTEST_PACKAGE_(name)							\
	namespace name {									\
	class iuTest_TestCasePackage;						\
	static ::std::string IUTEST_ATTRIBUTE_UNUSED_		\
	iuTest_GetTestCasePackageName(const iuTest_TestCasePackage*) {	\
		return iuTest_GetTestCaseParentPackageName(static_cast<iuTest_TestCaseParentPackage*>(NULL)) + #name ".";	\
	}													\
	class iuTest_TestCaseParentPackage;					\
	static ::std::string IUTEST_ATTRIBUTE_UNUSED_		\
	iuTest_GetTestCaseParentPackageName(const iuTest_TestCaseParentPackage*) {				\
		return iuTest_GetTestCasePackageName(static_cast<iuTest_TestCasePackage*>(NULL));	\
	}													\
	}													\
	namespace name

#else

#define IUTEST_CONCAT_PACKAGE_(testcase_name)	#testcase_name
#define IUTEST_PACKAGE_(name)					namespace name

#endif

/**
 * @}
*/

#if IUTEST_HAS_PACKAGE

//======================================================================
// declare
class iuTest_TestCasePackage;			//!< パッケージ名参照用定義
class iuTest_TestCaseParentPackage;		//!< 親パッケージ名参照用定義

//======================================================================
// function
/**
 * @brief	グローバルパッケージ名の取得
 * @return	パッケージ名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_	iuTest_GetTestCasePackageName(const iuTest_TestCasePackage*) { return ""; }

/**
 * @brief	親空間のパッケージ名の取得
 * @return	パッケージ名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_	iuTest_GetTestCaseParentPackageName(const iuTest_TestCaseParentPackage*) { return ""; }

/**
 * @brief	テストケース名との結合
 * @return	テストケース名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_	iuTest_ConcatTestCaseName(const ::std::string& package, const char* testcase_name) { return package + testcase_name; }

#endif

#endif
