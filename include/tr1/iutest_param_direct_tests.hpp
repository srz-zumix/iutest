//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_param_direct_tests.hpp
 * @brief       iris unit test initializer_list を使用したパラメータ設定 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * @deprecated
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PARAM_DIRECT_TESTS_HPP_8C9EC454_788D_4605_984B_0686C969E531_
#define INCG_IRIS_IUTEST_PARAM_DIRECT_TESTS_HPP_8C9EC454_788D_4605_984B_0686C969E531_

//======================================================================
// include
#include "../iutest_param_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

//======================================================================
// define
#if !defined(IUTEST_NO_VARIADIC_MACROS)

#undef IUTEST_INSTANTIATE_TEST_SUITE_P
/**
 * @ingroup TESTDEF
 * @def     IUTEST_INSTANTIATE_TEST_SUITE_P
 * @brief   パラメータテストインスタンス化マクロ
 * @param   prefix_     = インスタンス名
 * @param   testsuite_  = TestSuite 名
 * @param   generator_  = Range, Bool, Values, ValuesIn, Combine, Pairwise ...
*/
#define IUTEST_INSTANTIATE_TEST_SUITE_P(prefix_, testsuite_, ...)   \
            IIUT_INSTANTIATE_TEST_SUITE_PV_(prefix_, testsuite_, __VA_ARGS__)

/**
 * @private
 * @{
*/

/**
 * @brief   パラメータテスト登録(可変長対応)
*/
#define IIUT_INSTANTIATE_TEST_SUITE_PV_(prefix_, testsuite_, ...)                           \
    static ::iutest::detail::iuIParamGenerator<testsuite_::ParamType>*                      \
        IIUT_TEST_P_EVALGENERATOR_NAME_(prefix_, testsuite_)() {                            \
            return IUTEST_CAST_TO_PARAM_GENERATOR_(testsuite_::ParamType, __VA_ARGS__); }   \
    int IIUT_TEST_P_INSTANTIATIONREGISTER_NAME_(prefix_, testsuite_)() {                    \
        ::iutest::detail::ParamTestSuiteInfo< IIUT_TEST_P_BASE_FIXTURE(testsuite_) >* p =   \
            IIUT_GETTESTSUITEPATTERNHOLDER( IIUT_TEST_P_BASE_FIXTURE(testsuite_)            \
                , IIUT_TO_NAME_STR_(testsuite_), IUTEST_GET_PACKAGENAME_());                \
        return p->AddTestSuiteInstantiation(#prefix_                                        \
                    , IIUT_TEST_P_EVALGENERATOR_NAME_(prefix_, testsuite_)                  \
                    , p->GetParamNameGen(), __FILE__, __LINE__ );                           \
    } IIUT_TEST_P_INSTANTIATIONREGISTER_(prefix_, testsuite_)

#define IUTEST_CAST_TO_PARAM_GENERATOR_(type, ...)  ::iutest::tr1::iuCastToParamGenerator<type>(__VA_ARGS__)

#endif

/**
 * @}
*/

//======================================================================
// function
namespace iutest {
namespace tr1
{

#if !defined(IUTEST_NO_VARIADIC_MACROS)

/**
 * @brief   initializer_list 対応用キャストオブジェクト
*/
template<typename T>
detail::iuIParamGenerator<T>* iuCastToParamGenerator(detail::iuIParamGenerator<T>* g) { return g; }

#if IUTEST_HAS_INITIALIZER_LIST
template<typename T>
detail::iuIParamGenerator<T>* iuCastToParamGenerator(::std::initializer_list<T> l) { return new detail::iuValuesInParamsGenerator<T>(l); }
#endif

#endif

}   // end of namespace tr1
}   // end of namespace iutest

#endif

#endif
