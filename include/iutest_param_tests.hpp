//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_param_tests.hpp
 * @brief       iris unit test parameter 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PARAM_TESTS_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_
#define INCG_IRIS_IUTEST_PARAM_TESTS_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_any.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_PARAM_TEST

//======================================================================
// define
/**
 * @defgroup    VALUE_PARAMETERIZED_TEST    値のパラメータ化テスト
 * @brief       値のパラメータ化テスト
*/

/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_INSTANTIATE_TEST_SUITE_P
 * @brief   パラメータテストインスタンス化マクロ
 * @param   prefix_         = インスタンス名
 * @param   testfixture_    = テストフィクスチャ
 * @param   generator_      = Range, Bool, Values, ValuesIn, Combine, Pairwise ...
 * @param   ...             = Param name generator function (option)
*/
#if IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR
#  define IUTEST_INSTANTIATE_TEST_SUITE_P(prefix_, testfixture_, generator_, ...)   \
    IIUT_INSTANTIATE_TEST_SUITE_P_(prefix_, testfixture_, generator_, __VA_ARGS__)
#else
#  define IUTEST_INSTANTIATE_TEST_SUITE_P(prefix_, testfixture_, generator_)        \
    IIUT_INSTANTIATE_TEST_SUITE_P_(prefix_, testfixture_, generator_)
#endif

/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_P(testfixture_, testname_)
 * @brief   パラメータユーザー指定テスト関数定義マクロ
 * @param   testfixture_    = テストフィクスチャ
 * @param   testname_       = テスト名
 * @note
 *  class TestSuiteName : public ::iutest::TestWithParam<int> {};\n
 *  IUTEST_P(TestSuiteName, TestName) {}\n
 *  IUTEST_INSTANTIATE_TEST_SUITE_P(InstantiateName, TestSuiteName, ParamGenerator);\n
*/
#define IUTEST_P(testfixture_, testname_)       IUTEST_TEST_P_(testfixture_, testname_)


#if IUTEST_HAS_ANY_PARAM_TEST

/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_INSTANTIATE_TEST_SUITE_AP
 * @brief   パラメータテストインスタンス化マクロ
 * @param   prefix_     = インスタンス名
 * @param   testsuite_  = TestSuite 名
 * @param   generator_  = Range, Bool, Values, ValuesIn, Combine, Pairwise ...
*/
#define IUTEST_INSTANTIATE_TEST_SUITE_AP(prefix_, testsuite_, generator_)   \
    IIUT_INSTANTIATE_TEST_SUITE_AP_(prefix_, testsuite_, generator_)

/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @def     IUTEST_AP(testsuite_, testname_)
 * @brief   パラメータユーザー指定テスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
 * @note
 *  IUTEST_AP(TestSuiteName, TestName) {}\n
 *  IUTEST_INSTANTIATE_TEST_SUITE_AP(InstantiateName, TestSuiteName, ParamGenerator);\n
*/
#define IUTEST_AP(testsuite_, testname_) \
    IUTEST_TEST_AP_(testsuite_, testname_)

#endif


/**
 * @private
 * @{
*/

#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#  define IIUT_GETTESTSUITEPATTERNHOLDER(T, testsuite_, package_)   \
    ::iutest::UnitTest::GetInstance()->parameterized_test_registry( \
        ).GetTestSuitePatternHolder<T>(testsuite_, package_)
#else
#  define IIUT_GETTESTSUITEPATTERNHOLDER(T, testsuite_, package_)   \
    ::iutest::UnitTest::GetInstance()->parameterized_test_registry( \
        ).GetTestSuitePatternHolder(testsuite_, package_, ::iutest::detail::explicit_type<T>())
#endif

#if IUTEST_HAS_AUTOFIXTURE_PARAM_TEST
#  if IUTEST_HAS_IF_EXISTS
#    define IIUT_TEST_P_FIXTURE_DECL_(testsuite_)    IIUT_TEST_P_FIXTURE_DECL_I(IIUT_TO_VARNAME_(testsuite_))
#    define IIUT_TEST_P_FIXTURE_DECL_I(testsuite_)   IUTEST_IF_NOT_EXISTS(testsuite_, typedef ::iutest::TestWithAny testsuite_;)
#    define IIUT_TEST_P_BASE_FIXTURE(testsuite_)     IIUT_TO_VARNAME_(testsuite_)
#  else
#    define IIUT_TEST_P_FIXTURE_DECL_(testsuite_)
#    if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#      define IIUT_TEST_P_BASE_FIXTURE(testsuite_)   \
        ::iutest::detail::paramtest_select_base_testsuite< void (int (IIUT_TO_VARNAME_(testsuite_))) >::type
#    else
#      define IIUT_TEST_P_BASE_FIXTURE(testsuite_)   IIUT_TO_VARNAME_(testsuite_)
#    endif
#  endif
#else
#  define IIUT_TEST_P_FIXTURE_DECL_(testsuite_)
#  define IIUT_TEST_P_BASE_FIXTURE(testsuite_)       IIUT_TO_VARNAME_(testsuite_)
#endif

/**
 * @brief   パラメータテスト登録
*/
#if IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR
#  define IIUT_INSTANTIATE_TEST_SUITE_P_(prefix_, testsuite_, generator_, ...)        \
    IIUT_INSTANTIATE_TEST_SUITE_P_I(prefix_, testsuite_, generator_, GetParamNameGen(__VA_ARGS__))
#else
#  define IIUT_INSTANTIATE_TEST_SUITE_P_(prefix_, testsuite_, generator_)             \
    IIUT_INSTANTIATE_TEST_SUITE_P_I(prefix_, testsuite_, generator_, GetParamNameGen())
#endif

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

#define IIUT_INSTANTIATE_TEST_SUITE_P_I(prefix_, testsuite_, generator_, paramname_generator_)      \
    IIUT_INSTANTIATE_TEST_SUITE_P_II(prefix_, IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testsuite_)   \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testsuite_, generator_, paramname_generator_)

#else

#define IIUT_INSTANTIATE_TEST_SUITE_P_I(prefix_, testsuite_, generator_, paramname_generator_)      \
    IIUT_INSTANTIATE_TEST_SUITE_P_II(prefix_, testsuite_, generator_, paramname_generator_)

#endif

#define IIUT_INSTANTIATE_TEST_SUITE_P_II(prefix_, testsuite_, generator_, paramname_generator_)     \
    IIUT_INSTANTIATE_TEST_SUITE_P_III(prefix_, testsuite_, IIUT_TEST_P_BASE_FIXTURE(testsuite_)     \
        , generator_, paramname_generator_)


#define IIUT_INSTANTIATE_TEST_SUITE_P_III(prefix_, testsuite_, basefixture_, generator_, paramname_generator_)  \
    IIUT_TEST_P_FIXTURE_DECL_(testsuite_)                                                           \
    static ::iutest::detail::iuIParamGenerator< basefixture_::ParamType >*                          \
        IIUT_TEST_P_EVALGENERATOR_NAME_(prefix_, testsuite_)() { return generator_; }               \
    static ::std::string IIUT_TEST_P_PARAMGENERATOR_NAME_(prefix_, testsuite_)(                     \
        const ::iutest::TestParamInfo< basefixture_::ParamType >& pinfo_) { return                  \
            ::iutest::detail::ParamTestSuiteInfo< basefixture_ >::paramname_generator_(pinfo_); }   \
    int IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testsuite_)() {                            \
        ::iutest::detail::ParamTestSuiteInfo< basefixture_ >* p = IIUT_GETTESTSUITEPATTERNHOLDER(   \
                basefixture_, IIUT_TO_NAME_STR_(testsuite_), IUTEST_GET_PACKAGENAME_());            \
        return p->AddTestSuiteInstantiation(#prefix_                                                \
                    , IIUT_TEST_P_EVALGENERATOR_NAME_(prefix_, testsuite_)                          \
                    , IIUT_TEST_P_PARAMGENERATOR_NAME_(prefix_, testsuite_)                         \
                    , __FILE__, __LINE__);                                                          \
    } IIUT_TEST_P_INSTANTIATIONREGISTER_(prefix_, testsuite_)

/**
 * @brief   パラメータテストクラス定義
*/
#define IIUT_TEST_P_I_(classname_, testsuite_, testsuitename_, testname_)                   \
    IIUT_TEST_P_FIXTURE_DECL_(testsuite_)                                                   \
    class classname_ IUTEST_CXX_FINAL : public testsuite_ {                                 \
        public: classname_() {}                                                             \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;                                 \
        private: static int AddRegister() {                                                 \
            static ::iutest::detail::ParamTestInstance< classname_ > testinfo(testname_);   \
            IIUT_GETTESTSUITEPATTERNHOLDER(testsuite_, testsuitename_                       \
                    , IUTEST_GET_PACKAGENAME_())->AddTestPattern(&testinfo); return 0;      \
        }                                                                                   \
        static int dummy_;                                                                  \
        IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(classname_);                                     \
    };                                                                                      \
    int classname_::dummy_ IUTEST_ATTRIBUTE_UNUSED_  = classname_::AddRegister();           \
    void classname_::Body()

#if IUTEST_HAS_IGNORE_TEST

#define IIUT_TEST_P_I_IGNORE_(classname_, testsuite_, testsuitename_, testname_)            \
    class classname_ IUTEST_CXX_FINAL : public testsuite_ {                                 \
        public: classname_() {}                                                             \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }  \
        template<typename T>void Body();                                                    \
        private: static int AddRegister() {                                                 \
            static ::iutest::detail::ParamTestInstance< classname_ > testinfo(testname_);   \
            IIUT_GETTESTSUITEPATTERNHOLDER(testsuite_, testsuitename_                       \
                , IUTEST_GET_PACKAGENAME_())->AddTestPattern(&testinfo); return 0;          \
        }                                                                                   \
        static int dummy_;                                                                  \
        IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(classname_);                                     \
    };                                                                                      \
    int classname_::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = classname_::AddRegister();            \
    template<typename T>void classname_::Body()

#endif

#define IIUT_TEST_P_(macro, testsuite_, testname_)       \
    macro(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) \
        , IIUT_TEST_P_BASE_FIXTURE(testsuite_)           \
        , IIUT_TO_NAME_STR_(testsuite_), IIUT_TO_NAME_STR_(testname_))

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

#define IIUT_TEST_P_A_(macro, testsuite_, testname_)                         \
    IIUT_TEST_P_( macro, IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testsuite_) \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testsuite_, testname_)

#define IUTEST_TEST_P_(testsuite_, testname_)           \
    IIUT_TEST_P_A_(IIUT_TEST_P_I_, testsuite_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TEST_P_IGNORE_(testsuite_, testname_)    \
    IIUT_TEST_P_A_(IIUT_TEST_P_I_IGNORE_, testsuite_, testname_)

#endif

#else

#define IUTEST_TEST_P_(testsuite_, testname_)           \
    IIUT_TEST_P_(IIUT_TEST_P_I_, testsuite_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TEST_P_IGNORE_(testsuite_, testname_)    \
    IIUT_TEST_P_(IIUT_TEST_P_I_IGNORE_, testsuite_, testname_)

#endif

#endif

#define IIUT_TEST_AP_FIXTURE_NAME_(testsuite_) IUTEST_PP_CAT(iuTestWithAny, testsuite_)
#define IIUT_ALIAS_TESTNAME_AP_(testsuite_)    IUTEST_ALIAS_TESTNAME_F(testsuite_, IIUT_TEST_AP_FIXTURE_NAME_(testsuite_))

#define IUTEST_TEST_AP_(testsuite_, testname_) \
    typedef ::iutest::TestWithAny IIUT_TEST_AP_FIXTURE_NAME_(testsuite_);   \
    IUTEST_TEST_P_(IIUT_ALIAS_TESTNAME_AP_(testsuite_), testname_)

#define IIUT_INSTANTIATE_TEST_SUITE_AP_(prefix_, testsuite_, generator_)    \
    IIUT_INSTANTIATE_TEST_SUITE_P_(prefix_, IIUT_ALIAS_TESTNAME_AP_(testsuite_), generator_)


#define IIUT_TEST_P_EVALGENERATOR_NAME_(prefix_, testsuite_)     IIUT_TEST_P_EVALGENERATOR_NAME_I(prefix_, IIUT_TO_VARNAME_(testsuite_))
#define IIUT_TEST_P_EVALGENERATOR_NAME_I(prefix_, testsuite_)    IIUT_TEST_P_EVALGENERATOR_NAME_I_(prefix_, testsuite_)
#define IIUT_TEST_P_EVALGENERATOR_NAME_I_(prefix_, testsuite_)   s_##prefix_##_x_iutest_x_##testsuite_##_EvalGenerator_

#define IIUT_TEST_P_PARAMGENERATOR_NAME_(prefix_, testsuite_)    IIUT_TEST_P_PARAMGENERATOR_NAME_I(prefix_, IIUT_TO_VARNAME_(testsuite_))
#define IIUT_TEST_P_PARAMGENERATOR_NAME_I(prefix_, testsuite_)   IIUT_TEST_P_PARAMGENERATOR_NAME_I_(prefix_, testsuite_)
#define IIUT_TEST_P_PARAMGENERATOR_NAME_I_(prefix_, testsuite_)  s_##prefix_##_x_iutest_x_##testsuite_##_ParamGenerator_

#define IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testsuite_)    \
    IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I(prefix_, IIUT_TO_VARNAME_(testsuite_))
#define IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I(prefix_, testsuite_)   IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I_(prefix_, testsuite_)
#define IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_I_(prefix_, testsuite_)  prefix_##_x_iutest_x_##testsuite_##_TestSuiteInstantiationRegister

#define IIUT_TEST_P_INSTANTIATIONREGISTER_(prefix_, testsuite_)  \
    IIUT_TEST_P_INSTANTIATIONREGISTER_I(prefix_, IIUT_TO_VARNAME_(testsuite_), IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testsuite_))
#define IIUT_TEST_P_INSTANTIATIONREGISTER_I(prefix_, testsuite_, register_)  IIUT_TEST_P_INSTANTIATIONREGISTER_I_(prefix_, testsuite_, register_)
#define IIUT_TEST_P_INSTANTIATIONREGISTER_I_(prefix_, testsuite_, register_) int s_##prefix_##_x_iutest_x_##testsuite_##_dummy = register_()

/**
 * @}
*/

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @private
 * @brief   パラメータ単体テスト TestInfo 情報インスタンス
*/
template<typename T>
class ParamTestInstance : public IParamTestInfoData
{
    typedef T Tester;
    typedef typename Tester::ParamType ParamType;
    typedef detail::iuParamTestFactory<T> Factory;

    // 各テストのインスタンス
    class EachTest IUTEST_CXX_FINAL : public IParamTestInfoData::ParamEachTestBase<ParamType>
    {
    public:
        EachTest(TestSuite* testsuite, const ::std::string& name)
            : m_mediator(testsuite)
            , m_info(&m_mediator, name, &m_factory)
        {
            UnitTest::instance().AddTestInfo(testsuite, &m_info);
        }
    private:
        virtual void SetParam(const ParamType& param) IUTEST_CXX_OVERRIDE
        {
            m_factory.SetParam(param);
            m_info.set_value_param(PrintToString(param).c_str());
        }
    private:
        TestSuiteMediator    m_mediator;
        Factory             m_factory;
        TestInfo            m_info;
    };
public:
    ParamTestInstance() : IParamTestInfoData("") {} // allow empty name
    explicit ParamTestInstance(const char* testsuite_name) : IParamTestInfoData(testsuite_name) {}

private:
    // TestSuite の作成
    virtual TestSuite* MakeTestSuite(const ::std::string& testsuite_name, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown) const IUTEST_CXX_OVERRIDE
    {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
        return UnitTest::instance().AddTestSuite<TestSuite>(testsuite_name, id, setup, teardown);
#else
        return UnitTest::instance().AddTestSuite(
            testsuite_name, id, setup, teardown, detail::explicit_type<TestSuite>());
#endif
    }

    // テストの作成登録
    virtual IParamTestInfoData::EachTestBase* RegisterTest(TestSuite* testsuite
                                                        , const ::std::string& name) const IUTEST_CXX_OVERRIDE
    {
        EachTest* test = new EachTest(testsuite, name);
        // new オブジェクトを管理してもらう
        detail::iuPool::GetInstance().push(test);
        return test;
    }
};

}   // end of namespace detail

/**
 * @ingroup PARAMETERIZED_TEST
 * @brief   any パラメータテストフィクスチャ
*/
class TestWithAny : public Test, public WithParamInterface<any>
{
public:
    /**
     * @brief   パラメータの取得
    */
    static const ParamType& GetParam() { return WithParamInterface<any>::GetParam(); }

    /**
     * @brief   パラメータの取得
    */
    template<typename T>
    static T GetParam() { return unsafe_any_cast<T>(WithParamInterface<any>::GetParam()); }
};

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
namespace detail
{

/**
 * @brief   クラス選択
*/
template<typename T>
struct paramtest_select_base_testsuite;

template<>
struct paramtest_select_base_testsuite< void(int) >
{
    typedef TestWithAny type;
};
template<typename T>
struct paramtest_select_base_testsuite< void(int (T)) >
{
    typedef T type;
};

}   // end of namespace detail
#endif

//======================================================================
// function
/**
 * @ingroup     VALUE_PARAMETERIZED_TEST
 * @defgroup    PARAM_GENERATOR Parameter Generator
 * @brief       パラメータ生成器
 * @details     IUTEST_INSTANTIATE_TEST_SUITE_P に使用可能なパラメータ生成器
 * @{
*/

/**
 * @brief   範囲パラメータ
*/
template<typename T>
detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ Range(T begin, T end, T step=static_cast<T>(1))
{
    return new detail::iuRangeParamsGenerator<T>(begin, end, step);
}

/**
 * @brief   真偽値パラメータ
*/
inline detail::iuParamGenerator<bool> IUTEST_ATTRIBUTE_UNUSED_ Bool()
{
    return new detail::iuBoolParamsGenerator();
}

#if IUTEST_HAS_VALUESGEN

/**
 * @brief   ユーザー定義ジェネレータ利用パラメータ
 * @param   generator = ::std::generate function
*/
template<typename StdGenerator>
inline detail::iuValuesParamsGeneratorHolder<StdGenerator> IUTEST_ATTRIBUTE_UNUSED_ ValuesGen(size_t num, const StdGenerator& generator)
{
    return detail::iuValuesParamsGeneratorHolder<StdGenerator>(num, generator);
}

/**
 * @brief   乱数ジェネレータ
 * @details ValuesGen の Generator として利用します
 * @param   filter  = フィルター関数(bool ()(T))
 * @param   sedd    = 乱数シード
*/
template<typename T, typename Filter>
inline detail::iuRandomFilterParamGenerator<T, Filter> IUTEST_ATTRIBUTE_UNUSED_ RandomGenerator(const Filter& filter, unsigned int seed=0)
{
    if( seed == 0 )
    {
        seed = detail::GetIndefiniteValue();
    }
    return detail::iuRandomFilterParamGenerator<T, Filter>(filter, seed);
}

#endif

#if IUTEST_HAS_RANDOMVALUES
/**
 * @brief   乱数値パラメータ
*/
inline detail::iuRandomParamsHolder IUTEST_ATTRIBUTE_UNUSED_ RandomValues(size_t num, unsigned int seed=0)
{
    return detail::iuRandomParamsHolder(num, seed);
}
#endif

/**
 * @brief   値配列パラメータ
*/
template<typename Container>
inline detail::iuParamGenerator< typename Container::value_type > IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(Container container)
{
    return new detail::iuValuesInParamsGenerator< typename Container::value_type >(container);
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
/** @overload */
template<typename T, size_t SIZE>
inline detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(const T (&v)[SIZE])
{
    return new detail::iuValuesInParamsGenerator<T>(v, v+SIZE);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/** @overload */
template<typename Ite>
inline detail::iuParamGenerator< typename detail::IteratorTraits<Ite>::type > IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(Ite begin, Ite end)
{
    return new detail::iuValuesInParamsGenerator<
        typename detail::IteratorTraits<Ite>::type >(begin, end);
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
inline detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ ValuesIn(::std::initializer_list<T> l)
{
    return new detail::iuValuesInParamsGenerator<T>(l);
}
#endif

#endif

#if IUTEST_HAS_VARIADIC_VALUES
/**
 * @brief   値配列パラメータ
*/
template<typename ...Args>
inline detail::iuValueArray<Args...> IUTEST_ATTRIBUTE_UNUSED_ Values(Args... args)
{
    return detail::iuValueArray<Args...>(args...);
}

#else

#define IIUT_DECL_VALUES_(n)    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                    \
    inline detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >                                   \
    IUTEST_ATTRIBUTE_UNUSED_ Values( IUTEST_PP_ENUM_BINARY_PARAMS(n, T, t) )    {                   \
    return detail::iuValueArray##n< IUTEST_PP_ENUM_PARAMS(n, T) >( IUTEST_PP_ENUM_PARAMS(n, t) );   \
    }

/**
 * @brief   値配列パラメータ
 * @note    50引数まで使用可能
*/
IIUT_DECL_VALUES_(1)
IIUT_DECL_VALUES_(2)
IIUT_DECL_VALUES_(3)
IIUT_DECL_VALUES_(4)
IIUT_DECL_VALUES_(5)
IIUT_DECL_VALUES_(6)
IIUT_DECL_VALUES_(7)
IIUT_DECL_VALUES_(8)
IIUT_DECL_VALUES_(9)
IIUT_DECL_VALUES_(10)
IIUT_DECL_VALUES_(11)
IIUT_DECL_VALUES_(12)
IIUT_DECL_VALUES_(13)
IIUT_DECL_VALUES_(14)
IIUT_DECL_VALUES_(15)
IIUT_DECL_VALUES_(16)
IIUT_DECL_VALUES_(17)
IIUT_DECL_VALUES_(18)
IIUT_DECL_VALUES_(19)
IIUT_DECL_VALUES_(20)
IIUT_DECL_VALUES_(21)
IIUT_DECL_VALUES_(22)
IIUT_DECL_VALUES_(23)
IIUT_DECL_VALUES_(24)
IIUT_DECL_VALUES_(25)
IIUT_DECL_VALUES_(26)
IIUT_DECL_VALUES_(27)
IIUT_DECL_VALUES_(28)
IIUT_DECL_VALUES_(29)
IIUT_DECL_VALUES_(30)
IIUT_DECL_VALUES_(31)
IIUT_DECL_VALUES_(32)
IIUT_DECL_VALUES_(33)
IIUT_DECL_VALUES_(34)
IIUT_DECL_VALUES_(35)
IIUT_DECL_VALUES_(36)
IIUT_DECL_VALUES_(37)
IIUT_DECL_VALUES_(38)
IIUT_DECL_VALUES_(39)
IIUT_DECL_VALUES_(40)
IIUT_DECL_VALUES_(41)
IIUT_DECL_VALUES_(42)
IIUT_DECL_VALUES_(43)
IIUT_DECL_VALUES_(44)
IIUT_DECL_VALUES_(45)
IIUT_DECL_VALUES_(46)
IIUT_DECL_VALUES_(47)
IIUT_DECL_VALUES_(48)
IIUT_DECL_VALUES_(49)
IIUT_DECL_VALUES_(50)

#undef IIUT_DECL_VALUES_

#endif

#if IUTEST_HAS_CONCAT
/**
 * @brief   パラメータの結合
*/
template<typename Generator1, typename Generator2>
detail::iuConcatParamHolder<Generator1, Generator2> Concat(const Generator1& g1, const Generator2& g2)
{
    return detail::iuConcatParamHolder<Generator1, Generator2>(g1, g2);
}
#endif

#if IUTEST_HAS_COMBINE

#if IUTEST_HAS_VARIADIC_COMBINE
/**
 * @brief   複合条件パラメータ化
*/
template<typename ...Generator>
detail::iuCartesianProductHolder<Generator...> Combine(const Generator&... generators)
{
    return detail::iuCartesianProductHolder<Generator...>(generators...);
}

#else

#define IIUT_DECL_COMBINE_(n)   template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                \
    inline IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >    \
    Combine(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {                                     \
        return IUTEST_PP_CAT(detail::iuCartesianProductHolder, n)                               \
                < IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));                   \
    }

/**
 * @brief   複合条件パラメータ化
 * @note    9引数まで使用可能
*/
IIUT_DECL_COMBINE_(2)
IIUT_DECL_COMBINE_(3)
IIUT_DECL_COMBINE_(4)
IIUT_DECL_COMBINE_(5)
IIUT_DECL_COMBINE_(6)
IIUT_DECL_COMBINE_(7)
IIUT_DECL_COMBINE_(8)
IIUT_DECL_COMBINE_(9)

#undef IIUT_DECL_COMBINE_

#endif

#endif

#if IUTEST_HAS_PAIRWISE

#if IUTEST_HAS_VARIADIC_PAIRWISE

/**
 * @brief   複合条件パラメータ化(オールペア法)
*/
template<typename ...Generator>
detail::iuPairwiseHolder<Generator...> Pairwise(const Generator&... generators)
{
    return detail::iuPairwiseHolder<Generator...>(generators...);
}

#else

#define IIUT_DECL_PAIRWISE_(n)  template< IUTEST_PP_ENUM_PARAMS(n, typename T) >            \
    inline IUTEST_PP_CAT(detail::iuPairwiseHolder, n)< IUTEST_PP_ENUM_PARAMS(n, T) >        \
    Pairwise(IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &t)) {                                \
        return IUTEST_PP_CAT(detail::iuPairwiseHolder, n)                                   \
                < IUTEST_PP_ENUM_PARAMS(n, T) >(IUTEST_PP_ENUM_PARAMS(n, t));               \
    }

/**
 * @brief   複合条件パラメータ化(オールペア法)
 * @note    9引数まで使用可能
*/
IIUT_DECL_PAIRWISE_(2)
IIUT_DECL_PAIRWISE_(3)
IIUT_DECL_PAIRWISE_(4)
IIUT_DECL_PAIRWISE_(5)
IIUT_DECL_PAIRWISE_(6)
IIUT_DECL_PAIRWISE_(7)
IIUT_DECL_PAIRWISE_(8)
IIUT_DECL_PAIRWISE_(9)

#undef IIUT_DECL_PAIRWISE__

#endif

#endif

#if IUTEST_HAS_CSVPARAMS

/**
 * @brief   csv ファイルパラメータ
*/
template<typename T>
detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ CSV(const char* path, char delimiter = ',')
{
    return new detail::iuCsvFileParamsGenerator<T>(path, delimiter);
}
/** @overload */
template<typename T>
detail::iuParamGenerator<T> IUTEST_ATTRIBUTE_UNUSED_ CSV(const char* relative_path, const char* test_file, char delimiter = ',')
{
    const char* sep = detail::FindLastPathSeparator(test_file, strlen(test_file));
    ::std::string path;
    if( sep != NULL )
    {
        const size_t length = static_cast<size_t>(::std::distance(test_file, sep));
        path += ::std::string(test_file, length);
        path += detail::GetPathSeparator();
    }
    path += relative_path;
    return new detail::iuCsvFileParamsGenerator<T>(path, delimiter);
}

#endif

/**
 * @}
*/

}   // end of namespace iutest

#if IUTEST_HAS_ANY_PARAM_TEST
/**
 * @ingroup VALUE_PARAMETERIZED_TEST
 * @brief   any param test fixture
*/
typedef ::iutest::TestWithAny iuTestWithAny;
#endif

#endif // IUTEST_HAS_PARAM_TEST

#endif // INCG_IRIS_IUTEST_PARAM_TESTS_HPP_3DBBF55E_A076_4207_B49E_34734EE333EE_
