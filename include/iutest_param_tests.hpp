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
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
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
 * @param	prefix_		= インスタンス名
 * @param	testcase_	= テストケース名
 * @param	generator_	= Range, Bool, Values, ValuesIn, Combine, Pairwise ...
*/
#define IUTEST_INSTANTIATE_TEST_CASE_P(prefix_, testcase_, generator_)	\
													IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)

/**
 * @ingroup	TESTDEF
 * @def		IUTEST_P(testcase_, testname_)
 * @brief	パラメータユーザー指定テスト関数定義マクロ
 * @param	testcase_	= テストケース名
 * @param	testname_	= テスト名
 * @note	
 *	class TestCaseName : public ::iutest::TestWithParam<int> {};\n
 *  IUTEST_P(TestCaseName, TestName) {}\n
 *  IUTEST_INSTANTIATE_TEST_CASE_P(InstantiateName, TestCaseName, ParamGenerator);\n
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
			GetTestCasePatternHolder< testcase_ >(IUTEST_CONCAT_PACKAGE_(testcase_))		\
				->AddTestCaseInstantiation(#prefix_, s_##prefix_##_##testcase_##_EvalGenerator_)

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
				GetTestCasePatternHolder< testcase_ >(IUTEST_CONCAT_PACKAGE_(testcase_))->AddTestPattern(&testinfo);	\
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
	virtual TestCase*	MakeTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown) const IUTEST_CXX_OVERRIDE
	{
		return UnitTest::instance().AddTestCase<TestCase>(testcase_name, id, setup, teardown);
	}

	// テストの作成登録
	virtual	void	RegisterTest(TestCase* testcase, ParamType param, int index) const IUTEST_CXX_OVERRIDE
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

#include "internal/iutest_template_util_defs.hpp"

#define IUTEST_DECL_VALUES(n)	template< IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(n) >						\
	inline detail::iuValueArray##n< IUTEST_TEMPLATE_UTIL_ARGS(n) >											\
	IUTEST_ATTRIBUTE_UNUSED_	Values( IUTEST_TEMPLATE_UTIL_FUNCTION_ARGS(n) )	{							\
		return detail::iuValueArray##n< IUTEST_TEMPLATE_UTIL_ARGS(n) >( IUTEST_TEMPLATE_UTIL_VALUES(n) );	\
	}

/**
 * @brief	値配列パラメータ
 * @note	50引数まで使用可能
*/
IUTEST_DECL_VALUES(1)
IUTEST_DECL_VALUES(2)
IUTEST_DECL_VALUES(3)
IUTEST_DECL_VALUES(4)
IUTEST_DECL_VALUES(5)
IUTEST_DECL_VALUES(6)
IUTEST_DECL_VALUES(7)
IUTEST_DECL_VALUES(8)
IUTEST_DECL_VALUES(9)
IUTEST_DECL_VALUES(10)
IUTEST_DECL_VALUES(11)
IUTEST_DECL_VALUES(12)
IUTEST_DECL_VALUES(13)
IUTEST_DECL_VALUES(14)
IUTEST_DECL_VALUES(15)
IUTEST_DECL_VALUES(16)
IUTEST_DECL_VALUES(17)
IUTEST_DECL_VALUES(18)
IUTEST_DECL_VALUES(19)
IUTEST_DECL_VALUES(20)
IUTEST_DECL_VALUES(21)
IUTEST_DECL_VALUES(22)
IUTEST_DECL_VALUES(23)
IUTEST_DECL_VALUES(24)
IUTEST_DECL_VALUES(25)
IUTEST_DECL_VALUES(26)
IUTEST_DECL_VALUES(27)
IUTEST_DECL_VALUES(28)
IUTEST_DECL_VALUES(29)
IUTEST_DECL_VALUES(30)
IUTEST_DECL_VALUES(31)
IUTEST_DECL_VALUES(32)
IUTEST_DECL_VALUES(33)
IUTEST_DECL_VALUES(34)
IUTEST_DECL_VALUES(35)
IUTEST_DECL_VALUES(36)
IUTEST_DECL_VALUES(37)
IUTEST_DECL_VALUES(38)
IUTEST_DECL_VALUES(39)
IUTEST_DECL_VALUES(40)
IUTEST_DECL_VALUES(41)
IUTEST_DECL_VALUES(42)
IUTEST_DECL_VALUES(43)
IUTEST_DECL_VALUES(44)
IUTEST_DECL_VALUES(45)
IUTEST_DECL_VALUES(46)
IUTEST_DECL_VALUES(47)
IUTEST_DECL_VALUES(48)
IUTEST_DECL_VALUES(49)
IUTEST_DECL_VALUES(50)

#undef IUTEST_DECL_VALUES

#include "internal/iutest_template_util_undef.hpp"

#endif

#if IUTEST_HAS_COMBINE

#if IUTEST_HAS_VARIADIC_COMBINE
/**
 * @brief	複合条件パラメータ化
*/
template<typename ...Generator>
detail::iuCartesianProductHolder<Generator...> Combine(const Generator&... generators)
{
	return detail::iuCartesianProductHolder<Generator...>(generators...);
}

#else

#include "internal/iutest_template_util_defs.hpp"

#define IUTEST_DECL_COMBINE_ARGS_M(param, i) IUTEST_PP_CAT(param, i)& IUTEST_PP_CAT(t,i)
#define IUTEST_DECL_COMBINE(n)	template< IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(n) >			\
	inline IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)< IUTEST_TEMPLATE_UTIL_ARGS(n) >	\
	Combine(IUTEST_PP_ENUM_SHIFTED_PARAMS_M(n, IUTEST_DECL_COMBINE_ARGS_M, const T)) {			\
		return IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)								\
					< IUTEST_TEMPLATE_UTIL_ARGS(n) >(IUTEST_TEMPLATE_UTIL_VALUES(n));			\
	}

/**
 * @brief	複合条件パラメータ化
 * @note	9引数まで使用可能
*/
IUTEST_DECL_COMBINE(2)
IUTEST_DECL_COMBINE(3)
IUTEST_DECL_COMBINE(4)
IUTEST_DECL_COMBINE(5)
IUTEST_DECL_COMBINE(6)
IUTEST_DECL_COMBINE(7)
IUTEST_DECL_COMBINE(8)
IUTEST_DECL_COMBINE(9)

#undef IUTEST_DECL_COMBINE_ARGS_M
#undef IUTEST_DECL_COMBINE

#include "internal/iutest_template_util_undef.hpp"

#endif

#endif

#if IUTEST_HAS_PAIRWISE

#if IUTEST_HAS_VARIADIC_PAIRWISE

/**
 * @brief	複合条件パラメータ化(オールペア法)
*/
template<typename ...Generator>
detail::iuPairwiseHolder<Generator...> Pairwise(const Generator&... generators)
{
	return detail::iuPairwiseHolder<Generator...>(generators...);
}

#else

#include "internal/iutest_template_util_defs.hpp"

#define IUTEST_DECL_PAIRWISE_ARGS_M(param, i) IUTEST_PP_CAT(param, i)& IUTEST_PP_CAT(t,i)
#define IUTEST_DECL_PAIRWISE(n)	template< IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(n) >			\
	inline IUTEST_PP_CAT(detail::iuPairwiseHolder, n)< IUTEST_TEMPLATE_UTIL_ARGS(n) >			\
	Pairwise(IUTEST_PP_ENUM_SHIFTED_PARAMS_M(n, IUTEST_DECL_PAIRWISE_ARGS_M, const T)) {		\
		return IUTEST_PP_CAT(detail::iuPairwiseHolder, n)										\
					< IUTEST_TEMPLATE_UTIL_ARGS(n) >(IUTEST_TEMPLATE_UTIL_VALUES(n));			\
	}

/**
 * @brief	複合条件パラメータ化(オールペア法)
 * @note	9引数まで使用可能
*/
IUTEST_DECL_PAIRWISE(2)
IUTEST_DECL_PAIRWISE(3)
IUTEST_DECL_PAIRWISE(4)
IUTEST_DECL_PAIRWISE(5)
IUTEST_DECL_PAIRWISE(6)
IUTEST_DECL_PAIRWISE(7)
IUTEST_DECL_PAIRWISE(8)
IUTEST_DECL_PAIRWISE(9)

#undef IUTEST_DECL_COMBINE_ARGS_M
#undef IUTEST_DECL_COMBINE

#include "internal/iutest_template_util_undef.hpp"

#endif

#endif

}	// end of namespace iutest

#endif	// IUTEST_HAS_PARAM_TEST

#endif
