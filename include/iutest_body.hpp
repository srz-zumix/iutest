//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_body.hpp
 * @brief		iris unit test テスト単体クラス ファイル
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
#ifndef INCG_IRIS_iutest_body_HPP_3EEA6706_9954_4330_B292_129667FA6B96_
#define INCG_IRIS_iutest_body_HPP_3EEA6706_9954_4330_B292_129667FA6B96_

//======================================================================
// include
#include "iutest_result.hpp"
#include "iutest_printers.hpp"
#include "internal/iutest_mediator.hpp"

namespace iutest
{

//======================================================================
// declare
class Test;
template<typename T>class WithParamInterface;
template<typename T>class TestWithParam;

//======================================================================
// class
/**
 * @brief	テストベース
*/
class Test
{
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(Test);

public:
	Test(void)
		: test_info_(NULL)
		, m_test_info(NULL)
	{
		CurrentTestObserver::s_current = this;
	}

	virtual ~Test(void)
	{
		CurrentTestObserver::s_current = NULL;
	}

public:
	/**
	 * @brief	実行中の TestInfo の取得
	*/
	static const TestInfo*	GetCurrentTestInfo(void)		{ return CurrentTestObserver::GetCurrentTestInfo(); }

	/**
	 * @brief	実行中の Test の取得
	*/
	static Test*			GetCurrentTest(void)			{ return CurrentTestObserver::GetCurrentTest(); }


	/**
	 * @brief	致命的なエラーが出たかどうか
	 * @return	真偽値
	*/
	static bool	HasFatalFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasFatalFailure();
	}

	/**
	 * @brief	致命的ではないエラーが出たかどうか
	 * @return	真偽値
	*/
	static bool	HasNonfatalFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasNonfatalFailure();
	}

	/**
	 * @brief	エラーが出たかどうか
	 * @return	真偽値
	*/
	static bool	HasFailure(void)
	{
		return CurrentTestObserver::s_current->m_test_info->HasFailure();
	}

	/**
	 * @brief	テスト結果の情報追加
	 * @param [in]	key		= プロパティのキー
	 * @param [in]	value	= 値
	*/
	static void RecordProperty(const char* key, const char* value)
	{
		// 不正なキーのチェック
		const char* ban[] = { "name", "status", "time", "classname", "type_param", "value_param" };
		std::string key_ = key;
		for( int i=0, n=sizeof(ban)/sizeof(ban[0]); i < n; ++i )
		{
			if( key_ == ban[i] )
			{
				key_ += "_";
				break;
			}
		}
		TestProperty prop(key_.c_str(), value);
		GetCurrentTest()->m_test_info->RecordProperty(prop);
		TestEnv::event_listeners().OnTestRecordProperty(prop);
	};
	/**
	 * @brief	テスト結果の情報追加
	 * @param [in]	key		= プロパティのキー
	 * @param [in]	value	= 値
	*/
	template<typename T>
	static void RecordProperty(const char* key, const T& value)
	{
		RecordProperty(key, PrintToString(value).c_str());
	}

#if IUTEST_HAS_GENRAND

	/**
	 * @brief	乱数の生成
	 * @note	乱数シードは --iutest_random_seed で指定した値になります。
	 *			指定しなかった場合は実行時に決定します。
	*/
	unsigned int	genrand(void)				{ return m_random.genrand(); }
	/** @ref genrand */
	unsigned int	genrand(unsigned int max)	{ return m_random.genrand(max); }

#endif

protected:
	virtual	void	SetUp(void)		{}	//!< 実行前処理
	virtual void	Body(void)	= 0;	//!< テスト実装部
	virtual void	TearDown(void)	{}	//!< 実行後処理

public:
	static	void	SetUpTestCase(void)		{}	//!< test case setup
	static	void	TearDownTestCase(void)	{}	//!< test case tear down

protected:
	/**
	 * @brief	テストの実行
	*/
	void Run(detail::iuITestInfoMediator* test_info)
	{
		m_test_info = test_info;
		test_info_ = test_info->ptr();
		if( TestEnv::get_random_seed() == 0 )
		{
			m_random.init();
		}
		else
		{
			m_random.init(TestEnv::get_random_seed());
		}

		SetUp();
		Body();
		TearDown();

		test_info_ = NULL;
		m_test_info = NULL;
	}

private:
	template<typename DMY=void>
	class Observer
	{
	public:
		static Test*	s_current;
	public:
		static		 Test*		GetCurrentTest(void)		{ return s_current; }
		static const TestInfo*	GetCurrentTestInfo(void)	{ if( s_current == NULL ) return NULL; return s_current->m_test_info->ptr(); }
	};

	typedef Observer<void>	CurrentTestObserver;

protected:
	const TestInfo* test_info_;	//!< テスト中に簡単にアクセス可能なように

private:
	friend class UnitTest;
	friend class UnitTestImpl;
	friend class TestInfo;

	detail::iuITestInfoMediator*	m_test_info;
#if IUTEST_HAS_GENRAND
	detail::iuRandom				m_random;
#endif
};

template<typename DMY>
Test*	Test::Observer<DMY>::s_current = NULL;

/**
 * @brief	パラメータテストインターフェース
 * @tparam	T = パラメータ型
*/
template<typename T>
class WithParamInterface
{
public:
	typedef T	ParamType;	//!< パラメータ型
protected:
	virtual ~WithParamInterface(void)	{}

public:
	/**
	 * @brief	パラメータの取得
	*/
	static const ParamType&	GetParam(void)						{ return *s_params; }

	/** @private */
	static void				SetParam(const ParamType* params)	{ s_params = params; }

private:
	static const ParamType*	s_params;
};

template<typename T>
const T* WithParamInterface<T>::s_params = NULL;

/**
 * @brief	パラメータテストベース
 * @tparam	T = パラメータ型
*/
template<typename T>
class TestWithParam : public Test, public WithParamInterface<T>
{
};

}	// end of namespace iutest

#endif
