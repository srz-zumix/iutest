//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_tests.hpp
 * @brief		iris unit test parameter 定義 ファイル
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
#ifndef INCG_IRIS_iutest_param_tests_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_
#define INCG_IRIS_iutest_param_tests_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_

//======================================================================
// include
#include "iutest_core.hpp"

#if IUTEST_HAS_PARAM_TEST
#include "internal/iutest_pool.hpp"

//======================================================================
// define
/**
 * @ingroup	TESTDEF
 * @def		IUTEST_INSTANTIATE_TEST_CASE_P
 * @brief	パラメータテストインスタンス化マクロ
*/
#define IUTEST_INSTANTIATE_TEST_CASE_P(prefix_, testcase_, generator_)	\
													IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_P(testcase_, testname_)
 * @brief	パラメータユーザー指定テスト関数定義マクロ
*/
#define IUTEST_P(testcase_, testname_)				IIUT_TEST_P_(testcase_, testname_)

/**
 * @private
 * @{
*/

/**
 * @brief	パラメータテスト登録
*/
#define IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)						\
	static ::iutest::detail::iuIParamGenerator<testcase_::ParamType>*						\
		s_##prefix_##_##testcase_##_EvalGenerator_(void) { return generator_; }				\
		int s_##prefix_##_##testcase_##_dummy =												\
			::iutest::UnitTest::GetInstance()->parameterized_test_registry().				\
			GetTestCasePatternHolder< testcase_ >(#testcase_)->AddTestCaseInstantiation(#prefix_, s_##prefix_##_##testcase_##_EvalGenerator_)

/**
 * @brief	パラメータテストクラス定義
*/
#define IIUT_TEST_P_(testcase_, testname_)														\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public testcase_ {					\
		public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}							\
		protected: virtual void Body(void);														\
		private: static int	AddRegister(void) {													\
			static ::iutest::detail::ParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_, testname_) > testinfo(#testname_);	\
			::iutest::UnitTest::GetInstance()->parameterized_test_registry().					\
				GetTestCasePatternHolder< testcase_ >(#testcase_)->AddTestPattern(&testinfo);	\
			return 0;																			\
		}																						\
		static int dummy_;																		\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));		\
	};																							\
	int IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::AddRegister(); \
	void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

/**
 * @}
*/

//======================================================================
// class
namespace iutest {
namespace detail
{

/**
 * @brief	パラメータ単体テスト TestInfo 情報インスタンス
*/
template<typename T>
class ParamTestInstance : public IParamTestCaseInfo::ITestInfoData<typename T::ParamType>
{
	typedef T								Tester;
	typedef typename Tester::ParamType		ParamType;
	typedef detail::iuParamTestFactory<T>	Factory;
	typedef IParamTestCaseInfo::ITestInfoData<ParamType>	_Mybase;

	// 各テストのインスタンス
	class EachTest
	{
	public:
		EachTest(TestCase* testcase, const char* name, ParamType param)
			: m_mediator(testcase)
			, m_factory(param)
			, m_info(&m_mediator, name, &m_factory)
		{
			UnitTest::instance().AddTestInfo(testcase, &m_info);
			m_info.set_value_param(PrintToString(param).c_str());
		}
	private:
		TestCaseMediator	m_mediator;
		Factory				m_factory;
		TestInfo			m_info;
	};
public:
	ParamTestInstance(const char* testcase_name) : _Mybase(testcase_name) {}

private:
	// テストケースの作成
	virtual TestCase*	MakeTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown) const
	{
		return UnitTest::instance().AddTestCase<TestCase>(testcase_name, id, setup, teardown);
	}

	// テストの作成登録
	virtual	void	RegisterTest(TestCase* testcase, ParamType param, int index) const
	{
		EachTest* test = new EachTest(testcase, detail::MakeIndexTestName(this->m_name.c_str(), index).c_str(), param);
		// new オブジェクトを管理してもらう
		detail::iuPool<EachTest>::GetInstance().push(test);
	}
};

}	// end of namespace

/**
 * @brief	範囲パラメータ
*/
template<typename T>
detail::iuIParamGenerator<T>*	Range(T begin, T end, T step=1)
{
	return new detail::iuRangeParamsGenerator<T>(begin, end, step);
}

/**
 * @brief	真偽値パラメータ
*/
inline detail::iuIParamGenerator<bool> IUTEST_ATTRIBUTE_UNUSED_ * Bool(void)
{
	return new detail::iuBoolParamsGenerator<bool>();
}

/**
 * @brief	値配列パラメータ
*/
template<typename Container>
inline detail::iuIParamGenerator< typename Container::value_type >* ValuesIn(Container containor)
{
	return new detail::iuValueInParamsGenerator< typename Container::value_type >(containor);
}

/** @overload */
template<typename T, size_t SIZE>
inline detail::iuIParamGenerator<T>* ValuesIn(const T (&v)[SIZE])
{
	return new detail::iuValueInParamsGenerator<T>(v, v+SIZE);
}
/** @overload */
template<typename Ite>
inline detail::iuIParamGenerator< typename detail::IteratorTraits<Ite>::type >* ValuesIn(Ite begin, Ite end)
{
	return new detail::iuValueInParamsGenerator< typename detail::IteratorTraits<Ite>::type >(begin, end);
}

#if IUTEST_HAS_VARIADIC_VALUES
/**
 * @brief	値配列パラメータ
*/
template<typename ...Args>
inline detail::iuValueArray<Args...> IUTEST_ATTRIBUTE_UNUSED_ Values(Args... args)
{
	return detail::iuValueArray<Args...>(args...);
}

#else

/**
 * @brief	値配列パラメータ
 * @note	50引数まで使用可能
*/
template<typename T1>
inline detail::iuValueArray1<T1> IUTEST_ATTRIBUTE_UNUSED_	Values(T1 v1)
{
	return detail::iuValueArray1<T1>(v1);
}

template<typename T1, typename T2>
static detail::iuValueArray2<T1, T2>	Values(T1 v1, T2 v2)
{
	return detail::iuValueArray2<T1, T2>(v1, v2);
}

template<typename T1, typename T2, typename T3>
static detail::iuValueArray3<T1, T2, T3>	Values(T1 v1, T2 v2, T3 v3)
{
	return detail::iuValueArray3<T1, T2, T3>(v1, v2, v3);
}

template<typename T1, typename T2, typename T3, typename T4>
static detail::iuValueArray4<T1, T2, T3, T4>	Values(T1 v1, T2 v2, T3 v3, T4 v4)
{
	return detail::iuValueArray4<T1, T2, T3, T4>(v1, v2, v3, v4);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
static detail::iuValueArray5<T1, T2, T3, T4, T5>	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5)
{
	return detail::iuValueArray5<T1, T2, T3, T4, T5>(v1, v2, v3, v4, v5);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static detail::iuValueArray6<T1, T2, T3, T4, T5, T6>	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6)
{
	return detail::iuValueArray6<T1, T2, T3, T4, T5, T6>(v1, v2, v3, v4, v5, v6);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
static detail::iuValueArray7<T1, T2, T3, T4, T5, T6, T7>	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7)
{
	return detail::iuValueArray7<T1, T2, T3, T4, T5, T6, T7>(v1, v2, v3, v4, v5, v6, v7);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
static detail::iuValueArray8<T1, T2, T3, T4, T5, T6, T7, T8>	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8)
{
	return detail::iuValueArray8<T1, T2, T3, T4, T5, T6, T7, T8>(v1, v2, v3, v4, v5, v6, v7, v8);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
static detail::iuValueArray9<T1, T2, T3, T4, T5, T6, T7, T8, T9>	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9)
{
	return detail::iuValueArray9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10>
static detail::iuValueArray10<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10)
{
	return detail::iuValueArray10<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11>
static detail::iuValueArray11<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11)
{
	return detail::iuValueArray11<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12>
static detail::iuValueArray12<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12)
{
	return detail::iuValueArray12<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13>
static detail::iuValueArray13<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10
		, T11 v11, T12 v12, T13 v13)
{
	return detail::iuValueArray13<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12, T13>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14>
static detail::iuValueArray14<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14)
{
	return detail::iuValueArray14<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12, T13, T14>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
static detail::iuValueArray15<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15)
{
	return detail::iuValueArray15<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12, T13, T14, T15>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
static detail::iuValueArray16<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16)
{
	return detail::iuValueArray16<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12, T13, T14, T15, T16>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
static detail::iuValueArray17<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17)
{
	return detail::iuValueArray17<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10,T11, T12, T13, T14, T15, T16, T17>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
static detail::iuValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18)
{
	return detail::iuValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
static detail::iuValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19)
{
	return detail::iuValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20>
static detail::iuValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20)
{
	return detail::iuValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21>
static detail::iuValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21)
{
	return detail::iuValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22>
static detail::iuValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22)
{
	return detail::iuValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23>
static detail::iuValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23)
{
	return detail::iuValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22, T23>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24>
static detail::iuValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24)
{
	return detail::iuValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22, T23, T24>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
static detail::iuValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25)
{
	return detail::iuValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22, T23, T24, T25>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
static detail::iuValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26)
{
	return detail::iuValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22, T23, T24, T25, T26>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
static detail::iuValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27)
{
	return detail::iuValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20,T21, T22, T23, T24, T25, T26, T27>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
static detail::iuValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28)
{
	return detail::iuValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
static detail::iuValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29)
{
	return detail::iuValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30>
static detail::iuValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30)
{
	return detail::iuValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31>
static detail::iuValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31)
{
	return detail::iuValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32>
static detail::iuValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32)
{
	return detail::iuValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33>
static detail::iuValueArray33<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33)
{
	return detail::iuValueArray33<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32, T33>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34>
static detail::iuValueArray34<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34)
{
	return detail::iuValueArray34<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32, T33, T34>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
static detail::iuValueArray35<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35)
{
	return detail::iuValueArray35<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32, T33, T34, T35>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
static detail::iuValueArray36<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36)
{
	return detail::iuValueArray36<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32, T33, T34, T35, T36>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
static detail::iuValueArray37<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37)
{
	return detail::iuValueArray37<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30,T31, T32, T33, T34, T35, T36, T37>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
static detail::iuValueArray38<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38)
{
	return detail::iuValueArray38<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
static detail::iuValueArray39<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39)
{
	return detail::iuValueArray39<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40>
static detail::iuValueArray40<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40)
{
	return detail::iuValueArray40<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41>
static detail::iuValueArray41<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41)
{
	return detail::iuValueArray41<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42>
static detail::iuValueArray42<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42)
{
	return detail::iuValueArray42<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43>
static detail::iuValueArray43<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43)
{
	return detail::iuValueArray43<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42, T43>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44>
static detail::iuValueArray44<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44)
{
	return detail::iuValueArray44<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42, T43, T44>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
static detail::iuValueArray45<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45)
{
	return detail::iuValueArray45<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42, T43, T44, T45>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
static detail::iuValueArray46<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45, T46>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45, T46 v46)
{
	return detail::iuValueArray46<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42, T43, T44, T45, T46>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45, v46
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
static detail::iuValueArray47<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45, T46, T47>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45, T46 v46, T47 v47)
{
	return detail::iuValueArray47<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40,T41, T42, T43, T44, T45, T46, T47>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45, v46, v47
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
static detail::iuValueArray48<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45, T46, T47, T48>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45, T46 v46, T47 v47, T48 v48)
{
	return detail::iuValueArray48<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40, T41, T42, T43, T44, T45, T46, T47, T48>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45, v46, v47, v48
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
static detail::iuValueArray49<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45, T46 v46, T47 v47, T48 v48, T49 v49)
{
	return detail::iuValueArray49<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49
		);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49
, typename T50
>
static detail::iuValueArray50<T1, T2, T3, T4, T5, T6, T7, T8, T9
							, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
							, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
							, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
							, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
							, T50>
	Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9
	, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19
	, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29
	, T30 v30, T31 v31, T32 v32, T33 v33, T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39
	, T40 v40, T41 v41, T42 v42, T43 v43, T44 v44, T45 v45, T46 v46, T47 v47, T48 v48, T49 v49
	, T50 v50
	)
{
	return detail::iuValueArray50<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
		, T50>(
		v1, v2, v3, v4, v5, v6, v7, v8, v9
		, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
		, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29
		, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
		, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49
		, v50
		);
}

#endif

#if IUTEST_HAS_COMBINE

#if IUTEST_HAS_VARIADIC_COMBINE
template<typename ...Generator>
detail::iuCartesianProductHolder<Generator...> Combine(const Generator&... generators)
{
	return detail::iuCartesianProductHolder<Generator...>(generators...);
}

#else

/**
 * @brief	複合条件パラメータ化
 * @note	9引数まで使用可能
*/
template<typename G1, typename G2>
detail::iuCartesianProductHolder2<G1, G2> Combine(const G1& g1, const G2& g2)
{
	return detail::iuCartesianProductHolder2<G1, G2>(g1, g2);
}

/** @overload */
template<typename G1, typename G2, typename G3>
detail::iuCartesianProductHolder3<G1, G2, G3> Combine(const G1& g1, const G2& g2, const G3& g3)
{
	return detail::iuCartesianProductHolder3<G1, G2, G3>(g1, g2, g3);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4>
detail::iuCartesianProductHolder4<G1, G2, G3, G4> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4)
{
	return detail::iuCartesianProductHolder4<G1, G2, G3, G4>(g1, g2, g3, g4);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5>
detail::iuCartesianProductHolder5<G1, G2, G3, G4, G5> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5)
{
	return detail::iuCartesianProductHolder5<G1, G2, G3, G4, G5>(g1, g2, g3, g4, g5);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6>
detail::iuCartesianProductHolder6<G1, G2, G3, G4, G5, G6> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5
															  , const G6& g6)
{
	return detail::iuCartesianProductHolder6<G1, G2, G3, G4, G5, G6>(g1, g2, g3, g4, g5, g6);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7>
detail::iuCartesianProductHolder7<G1, G2, G3, G4, G5, G6, G7> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5
															  , const G6& g6, const G7& g7)
{
	return detail::iuCartesianProductHolder7<G1, G2, G3, G4, G5, G6, G7>(g1, g2, g3, g4, g5, g6, g7);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7, typename G8>
detail::iuCartesianProductHolder8<G1, G2, G3, G4, G5, G6, G7, G8> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5
															  , const G6& g6, const G7& g7, const G8& g8)
{
	return detail::iuCartesianProductHolder8<G1, G2, G3, G4, G5, G6, G7, G8>(g1, g2, g3, g4, g5, g6, g7, g8);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7, typename G8, typename G9>
detail::iuCartesianProductHolder9<G1, G2, G3, G4, G5, G6, G7, G8, G9> Combine(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5
															  , const G6& g6, const G7& g7, const G8& g8, const G9& g9)
{
	return detail::iuCartesianProductHolder9<G1, G2, G3, G4, G5, G6, G7, G8, G9>(g1, g2, g3, g4, g5, g6, g7, g8, g9);
}

#endif

#endif

#if IUTEST_HAS_PAIRWISE

#if IUTEST_HAS_VARIADIC_PAIRWISE

template<typename ...Generator>
detail::iuPairwiseHolder<Generator...> Pairwise(const Generator&... generators)
{
	return detail::iuPairwiseHolder<Generator...>(generators...);
}

#else

/**
 * @brief	複合条件パラメータ化(オールペア法)
 * @note	3引数まで使用可能
*/
template<typename G1, typename G2>
detail::iuCartesianProductHolder2<G1, G2> Pairwise(const G1& g1, const G2& g2)
{
	return detail::iuCartesianProductHolder2<G1, G2>(g1, g2);
}

/** @overload */
template<typename G1, typename G2, typename G3>
detail::iuPairwiseHolder3<G1, G2, G3> Pairwise(const G1& g1, const G2& g2, const G3& g3)
{
	return detail::iuPairwiseHolder3<G1, G2, G3>(g1, g2, g3);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4>
detail::iuPairwiseHolder4<G1, G2, G3, G4> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4)
{
	return detail::iuPairwiseHolder4<G1, G2, G3, G4>(g1, g2, g3, g4);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5>
detail::iuPairwiseHolder5<G1, G2, G3, G4, G5> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5)
{
	return detail::iuPairwiseHolder5<G1, G2, G3, G4, G5>(g1, g2, g3, g4, g5);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6>
detail::iuPairwiseHolder6<G1, G2, G3, G4, G5, G6> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5, const G6& g6)
{
	return detail::iuPairwiseHolder6<G1, G2, G3, G4, G5, G6>(g1, g2, g3, g4, g5, g6);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7>
detail::iuPairwiseHolder7<G1, G2, G3, G4, G5, G6, G7> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5, const G6& g6, const G7& g7)
{
	return detail::iuPairwiseHolder7<G1, G2, G3, G4, G5, G6, G7>(g1, g2, g3, g4, g5, g6, g7);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7, typename G8>
detail::iuPairwiseHolder8<G1, G2, G3, G4, G5, G6, G7, G8> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5, const G6& g6, const G7& g7, const G8& g8)
{
	return detail::iuPairwiseHolder8<G1, G2, G3, G4, G5, G6, G7, G8>(g1, g2, g3, g4, g5, g6, g7, g8);
}

/** @overload */
template<typename G1, typename G2, typename G3, typename G4, typename G5, typename G6, typename G7, typename G8, typename G9>
detail::iuPairwiseHolder9<G1, G2, G3, G4, G5, G6, G7, G8, G9> Pairwise(const G1& g1, const G2& g2, const G3& g3, const G4& g4, const G5& g5, const G6& g6, const G7& g7, const G8& g8, const G9& g9)
{
	return detail::iuPairwiseHolder9<G1, G2, G3, G4, G5, G6, G7, G8, G9>(g1, g2, g3, g4, g5, g6, g7, g8, g9);
}

#endif

#endif

}	// end of namespace iutest

#endif	// IUTEST_HAS_PARAM_TEST

#endif
