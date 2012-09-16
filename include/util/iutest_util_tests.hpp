//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_tests.hpp
 * @brief		iris unit test テスト情報 utility ファイル
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
#ifndef INCG_IRIS_iutest_util_tests_HPP_4095FF9B_D6B8_4cd3_BF86_43DFED1760EA_
#define INCG_IRIS_iutest_util_tests_HPP_4095FF9B_D6B8_4cd3_BF86_43DFED1760EA_

//======================================================================
// include
namespace iuutil
{

//======================================================================
// function

/**
 * @brief	TestCase の検索
*/
inline const ::iutest::TestCase* FindTestCase(const char* testcase_name)
{
	if( testcase_name == NULL ) return NULL;
	const int testcase_count = ::iutest::UnitTest::GetInstance()->total_test_case_count();
	for( int i=0; i < testcase_count; ++i )
	{
		const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
		if( strcmp(testcase->name(), testcase_name) == 0 )
		{
			return testcase;
		}
	}
	return NULL;
}

/**
 * @brief	TestCase の検索
*/
inline const ::iutest::TestCase* FindParamTestCase(const char* testcase_name, const ::iutest::TestCase* begin=NULL)
{
	if( testcase_name == NULL ) return NULL;
	const int testcase_count = ::iutest::UnitTest::GetInstance()->total_test_case_count();
	int i=0;
	if( begin != NULL )
	{
		for( ; i < testcase_count; ++i )
		{
			const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
			if( testcase == begin ) break; 
		}
		++i;
	}
	for( ; i < testcase_count; ++i )
	{
		const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
		const char* testcase_origin_name = strchr(testcase->name(), '/');
		if( testcase_origin_name != NULL )
		{
			if( strcmp(testcase_origin_name+1, testcase_name) == 0 )
			{
				return testcase;
			}
		}
	}
	return NULL;
}

/**
 * @brief	Typed Test の TestCase の検索
*/
inline const ::iutest::TestCase* FindTypedTestCase(const char* testcase_name, const ::iutest::TestCase* begin=NULL)
{
	if( testcase_name == NULL ) return NULL;
	const int testcase_count = ::iutest::UnitTest::GetInstance()->total_test_case_count();
	int i=0;
	if( begin != NULL )
	{
		for( ; i < testcase_count; ++i )
		{
			const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
			if( testcase == begin ) break; 
		}
		++i;
	}
	for( ; i < testcase_count; ++i )
	{
		const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
		const char* name = testcase->name();
		if( strstr(name, testcase_name) == name
			&& name[strlen(testcase_name)] == '/' )
		{
			return testcase;
		}
	}
	return NULL;
}

/**
 * @brief	Type Parameter Test の TestCase の検索
*/
inline const ::iutest::TestCase* FindParamTypedTestCase(const char* testcase_name, const ::iutest::TestCase* begin=NULL)
{
	if( testcase_name == NULL ) return NULL;
	const int testcase_count = ::iutest::UnitTest::GetInstance()->total_test_case_count();
	int i=0;
	if( begin != NULL )
	{
		for( ; i < testcase_count; ++i )
		{
			const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
			if( testcase == begin ) break; 
		}
		++i;
	}
	for( ; i < testcase_count; ++i )
	{
		const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);
		const char* name = strchr(testcase->name(), '/');
		if( name != NULL )
		{
			++name;
			if( strstr(name, testcase_name) == name
				&& name[strlen(testcase_name)] == '/' )
			{
				return testcase;
			}
		}
	}
	return NULL;
}

/**
 * @brief	TestInfo の検索
*/
inline const ::iutest::TestInfo* FindTestInfo(const ::iutest::TestCase* testcase, const char* testinfo_name)
{
	if( testcase == NULL || testinfo_name == NULL ) return NULL;

	int testinfo_count = testcase->total_test_count();
	for( int i=0; i < testinfo_count; ++i )
	{
		const ::iutest::TestInfo* testinfo = testcase->GetTestInfo(i);
		if( strcmp(testinfo->name(), testinfo_name) == 0 )
		{
			return testinfo;
		}
	}
	return NULL;
}

/**
 * @brief	TestInfo の検索
*/
inline const ::iutest::TestInfo* FindTestInfo(const char* testcase_name, const char* testinfo_name)
{
	if( testcase_name == NULL || testinfo_name == NULL ) return NULL;
	const ::iutest::TestCase* testcase = FindTestCase(testcase_name);
	return FindTestInfo(testcase, testinfo_name);
}

/**
 * @brief	TestInfo の検索
*/
inline const ::iutest::TestInfo* FindParamTestInfo(const ::iutest::TestCase* testcase, const char* testinfo_name, const ::iutest::TestInfo* begin=NULL)
{
	if( testcase == NULL || testinfo_name == NULL ) return NULL;

	const int testinfo_count = testcase->total_test_count();
	int i=0;
	if( begin != NULL )
	{
		for( ; i < testinfo_count; ++i )
		{
			const ::iutest::TestInfo* testinfo = testcase->GetTestInfo(i);
			if( testinfo == begin )
			{
				break;
			}
		}
		++i;
	}

	for( ; i < testinfo_count; ++i )
	{
		const ::iutest::TestInfo* testinfo = testcase->GetTestInfo(i);
		const char* name = testinfo->name();
		if( strstr(name, testinfo_name) == name
			&& name[strlen(testinfo_name)] == '/' )
		{
			return testinfo;
		}
	}
	return NULL;
}

}	// end of namespace iuutil

#endif
