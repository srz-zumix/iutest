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

#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#  define IIUT_GetTestCasePatternHolder(T, testcase_)	\
	::iutest::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder<T>(testcase_)
#else
#  define IIUT_GetTestCasePatternHolder(T, testcase_)	\
	::iutest::UnitTest::GetInstance()->parameterized_test_registry().GetTestCasePatternHolder(testcase_, &::iutest::detail::type<T>())
#endif

/**
 * @brief	パラメータテスト登録
*/
#define IIUT_INSTANTIATE_TEST_CASE_P_(prefix_, testcase_, generator_)						\
	static ::iutest::detail::iuIParamGenerator<testcase_::ParamType>*						\
		s_##prefix_##_##testcase_##_EvalGenerator_(void) { return generator_; }				\
		int prefix_##_##testcase_##_TestCaseInstantiationRegister(void) {					\
			::iutest::ParamTestCaseInfo<testcase_>* p =										\
				IIUT_GetTestCasePatternHolder(testcase_, IUTEST_CONCAT_PACKAGE_(testcase_));			\
			return p->AddTestCaseInstantiation(#prefix_, s_##prefix_##_##testcase_##_EvalGenerator_);	\
		} int s_##prefix_##_##testcase_##_dummy = prefix_##_##testcase_##_TestCaseInstantiationRegister()
				

/**
 * @brief	パラメータテストクラス定義
*/
#define IIUT_TEST_P_(testcase_, testname_)														\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public testcase_ {					\
		public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}							\
		protected: virtual void Body(void);														\
		private: static int	AddRegister(void) {													\
			static ::iutest::detail::ParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_, testname_) > testinfo(#testname_);	\
			IIUT_GetTestCasePatternHolder(testcase_, IUTEST_CONCAT_PACKAGE_(testcase_))->AddTestPattern(&testinfo);	\
			return 0;																			\
		}																						\
		static int dummy_;																		\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));		\
	};																							\
	int IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::AddRegister(); \
	void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

#define IIUT_TEST_P_IGNORE_(testcase_, testname_)												\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public testcase_ {					\
		public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}							\
		protected: virtual void Body(void) { IUTEST_SKIP() << "ignored test..."; }				\
		template<typename T>void Body(void);													\
		private: static int	AddRegister(void) {													\
			static ::iutest::detail::ParamTestInstance< IUTEST_TEST_CLASS_NAME_(testcase_, testname_) > testinfo(#testname_);	\
			IIUT_GetTestCasePatternHolder(testcase_, IUTEST_CONCAT_PACKAGE_(testcase_))->AddTestPattern(&testinfo);	\
			return 0;																			\
		}																						\
		static int dummy_;																		\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));		\
	};																							\
	int IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::AddRegister(); \
	template<typename T>void IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::Body(void)

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
class ParamTestInstance : public IParamTestInfoData<typename T::ParamType>
{
	typedef T								Tester;
	typedef typename Tester::ParamType		ParamType;
	typedef detail::iuParamTestFactory<T>	Factory;
	typedef IParamTestInfoData<ParamType>	_Mybase;

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
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
		return UnitTest::instance().AddTestCase<TestCase>(testcase_name, id, setup, teardown);
#else
		return UnitTest::instance().AddTestCase(testcase_name, id, setup, teardown, &detail::type<TestCase>());
#endif
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
inline detail::iuIParamGenerator<bool>* IUTEST_ATTRIBUTE_UNUSED_ Bool(void)
{
	return new detail::iuBoolParamsGenerator<bool>();
}

#if IUTEST_HAS_VALUESGEN

/**
 * @brief	値配列パラメータ
*/
template<typename Generator>
inline detail::iuValuesParamsGeneratorHolder<Generator> IUTEST_ATTRIBUTE_UNUSED_ ValuesGen(size_t num, const Generator& gen)
{
	return detail::iuValuesParamsGeneratorHolder<Generator>(num, gen);
}

#endif

#if IUTEST_HAS_RANDOMVALUES
/**
 * @brief	乱数値パラメータ
*/
inline detail::iuRandomParamsHolder IUTEST_ATTRIBUTE_UNUSED_ RandomValues(size_t num)
{
	return detail::iuRandomParamsHolder(num);
}
#endif

/**
 * @brief	値配列パラメータ
*/
template<typename Container>
inline detail::iuIParamGenerator< typename Container::value_type >* ValuesIn(Container containor)
{
	return new detail::iuValuesInParamsGenerator< typename Container::value_type >(containor);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/** @overload */
template<typename T, size_t SIZE>
inline detail::iuIParamGenerator<T>* ValuesIn(const T (&v)[SIZE])
{
	return new detail::iuValuesInParamsGenerator<T>(v, v+SIZE);
}
/** @overload */
template<typename Ite>
inline detail::iuIParamGenerator< typename detail::IteratorTraits<Ite>::type >* ValuesIn(Ite begin, Ite end)
{
	return new detail::iuValuesInParamsGenerator< typename detail::IteratorTraits<Ite>::type >(begin, end);
}
#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
inline detail::iuIParamGenerator<T>* ValuesIn(::std::initializer_list<T> l)
{
	return new detail::iuValuesInParamsGenerator<T>(l);
}
#endif

#endif

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

#define IUTEST_DECL_VALUES_(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >					\
	inline detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >									\
	IUTEST_ATTRIBUTE_UNUSED_ Values( IUTEST_PP_ENUM_BINARY_PARAMS(n, T, t) )	{					\
	return detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >( IUTEST_PP_ENUM_PARAMS(n, t) );	\
	}

/**
 * @brief	値配列パラメータ
 * @note	50引数まで使用可能
*/
IUTEST_DECL_VALUES_(1)
IUTEST_DECL_VALUES_(2)
IUTEST_DECL_VALUES_(3)
IUTEST_DECL_VALUES_(4)
IUTEST_DECL_VALUES_(5)
IUTEST_DECL_VALUES_(6)
IUTEST_DECL_VALUES_(7)
IUTEST_DECL_VALUES_(8)
IUTEST_DECL_VALUES_(9)
IUTEST_DECL_VALUES_(10)
IUTEST_DECL_VALUES_(11)
IUTEST_DECL_VALUES_(12)
IUTEST_DECL_VALUES_(13)
IUTEST_DECL_VALUES_(14)
IUTEST_DECL_VALUES_(15)
IUTEST_DECL_VALUES_(16)
IUTEST_DECL_VALUES_(17)
IUTEST_DECL_VALUES_(18)
IUTEST_DECL_VALUES_(19)
IUTEST_DECL_VALUES_(20)
IUTEST_DECL_VALUES_(21)
IUTEST_DECL_VALUES_(22)
IUTEST_DECL_VALUES_(23)
IUTEST_DECL_VALUES_(24)
IUTEST_DECL_VALUES_(25)
IUTEST_DECL_VALUES_(26)
IUTEST_DECL_VALUES_(27)
IUTEST_DECL_VALUES_(28)
IUTEST_DECL_VALUES_(29)
IUTEST_DECL_VALUES_(30)
IUTEST_DECL_VALUES_(31)
IUTEST_DECL_VALUES_(32)
IUTEST_DECL_VALUES_(33)
IUTEST_DECL_VALUES_(34)
IUTEST_DECL_VALUES_(35)
IUTEST_DECL_VALUES_(36)
IUTEST_DECL_VALUES_(37)
IUTEST_DECL_VALUES_(38)
IUTEST_DECL_VALUES_(39)
IUTEST_DECL_VALUES_(40)
IUTEST_DECL_VALUES_(41)
IUTEST_DECL_VALUES_(42)
IUTEST_DECL_VALUES_(43)
IUTEST_DECL_VALUES_(44)
IUTEST_DECL_VALUES_(45)
IUTEST_DECL_VALUES_(46)
IUTEST_DECL_VALUES_(47)
IUTEST_DECL_VALUES_(48)
IUTEST_DECL_VALUES_(49)
IUTEST_DECL_VALUES_(50)

#undef IUTEST_DECL_VALUES_

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

#define IUTEST_DECL_COMBINE_(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >				\
	inline IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
	Combine(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {										\
		return IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)								\
				< IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));					\
	}

/**
 * @brief	複合条件パラメータ化
 * @note	9引数まで使用可能
*/
IUTEST_DECL_COMBINE_(2)
IUTEST_DECL_COMBINE_(3)
IUTEST_DECL_COMBINE_(4)
IUTEST_DECL_COMBINE_(5)
IUTEST_DECL_COMBINE_(6)
IUTEST_DECL_COMBINE_(7)
IUTEST_DECL_COMBINE_(8)
IUTEST_DECL_COMBINE_(9)

#undef IUTEST_DECL_COMBINE_

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

#define IUTEST_DECL_PAIRWISE(n)	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >			\
	inline IUTEST_PP_CAT(detail::iuPairwiseHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >		\
	Pairwise(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {								\
		return IUTEST_PP_CAT(detail::iuPairwiseHolder, n)									\
				< IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));				\
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

#undef IUTEST_DECL_PAIRWISE_

#endif

#endif

}	// end of namespace iutest

#endif	// IUTEST_HAS_PARAM_TEST

#endif
