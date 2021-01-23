//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_value_tmp_tests.hpp
 * @brief       iris unit test template 値引き数クラステスト ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_VALUE_TMP_TESTS_HPP_8C9EC454_788D_4605_984B_0686C969E531_
#define INCG_IRIS_IUTEST_VALUE_TMP_TESTS_HPP_8C9EC454_788D_4605_984B_0686C969E531_

//======================================================================
// include
#include "../iutest_typed_tests.hpp"

#if IUTEST_HAS_TYPED_TEST

//======================================================================
// define
/**
 * @ingroup TESTDEF
 * @def     IUTEST_VALUETMP_TEST_SUITE(testsuite_, types_)
 * @brief   型付け TestSuite の登録
*/
#define IUTEST_VALUETMP_TEST_SUITE(testsuite_, types_)  IIUT_TYPED_TEST_SUITE_(testsuite_, types_)

/**
 * @ingroup TESTDEF
 * @def     IUTEST_VALUETMP_TEST(testsuite_, testname_)
 * @brief   型付けテスト関数定義マクロ
*/

#define IUTEST_VALUETMP_TEST(testsuite_, testname_)      IIUT_VALUETMP_TEST_(testsuite_, testname_)


/**
 * @private
 * @{
*/
#define IIUT_VALUETMP_TEST_(testsuite_, testname_)                                      \
    template<iutest::BiggestInt iutest_ValueParam>                                      \
    class IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) : public testsuite_<iutest_ValueParam> { \
        typedef testsuite_<iutest_ValueParam> TestFixture;                              \
        static const iutest::BiggestInt ValueParam = iutest_ValueParam;                 \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL;                             \
    };                                                                                  \
    iutest::tr1::ValueTmpParamTestInstance<IUTEST_TEST_CLASS_NAME_(testsuite_, testname_), IIUT_TYPED_TEST_PARAMS_(testsuite_)>   \
    s_##testsuite_##_##testname_( #testsuite_, #testname_, __FILE__, __LINE__);         \
    template<iutest::BiggestInt iutest_ValueParam>                                      \
    void IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)<iutest_ValueParam>::Body()

/**
 * @}
*/

//======================================================================
// class
namespace iutest {
namespace tr1
{

template<typename T>
struct TypeAndValues
{
    template<T V>
    struct Value
    {
        static const T kValue = V;
    };
};

}   // end of namespace tr1

template<BiggestInt V>
struct TemplateValue : public tr1::TypeAndValues<BiggestInt>::Value<V> {};

namespace tr1
{

/**
 * @private
 * @internal
 * @brief   Typeパラメータ単体テストインスタンス
 * @tparam  Tester      = テストクラス
 * @tparam  TypePrams   = 型
*/
template<template<BiggestInt V> class Tester, typename TypePrams>
class ValueTmpParamTestInstance
{
    /**
     * @brief   TestSuite 名の作成
     * @param [in]  testsuite   = ベース名
     * @param [in]  index       = 型インデックス
    */
    static ::std::string MakeTestSuiteName(const char* testsuite, size_t index)
    {
        ::std::string name = testsuite;
        iu_stringstream strm; strm << index;
        name += "/";
        name += strm.str();
        return name;
    }

    /**
     * @brief   各テストのインスタンス
    */
    template<typename TT, typename DMY=void>
    class EachTest
    {
        typedef typename TT::Head           TypeParam;
        typedef Tester<TypeParam::kValue>   TestBody;
        typedef TypedTestSuite<TypeParam>    _MyTestSuite;
    public:
        // コンストラクタ
        EachTest(const char* testsuite, const char* name, size_t index, const char* file, int line)
            : m_mediator(AddTestSuite(testsuite, index, file, line))
            , m_info(&m_mediator, name, &m_factory)
            , m_next(testsuite, name, index+1, file, line)
        {
        }
    private:
        static TestSuite* AddTestSuite(const char* testsuite, size_t index, const char* file, int line)
        {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            return UnitTest::instance().AddTestSuite<_MyTestSuite>(
#else
            return UnitTest::instance().AddTestSuite(
#endif
                MakeTestSuiteName(testsuite, index).c_str()
                , internal::GetTypeId<detail::None>()   // TypeId を統一するためダミー引数を渡す
                , IUTEST_GET_SETUP_TESTSUITE(TestBody, file, line)
                , IUTEST_GET_TEARDOWN_TESTSUITE(TestBody, file, line)
#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
                , detail::explicit_type<_MyTestSuite>()
#endif
                );
        }
    public:
        // テストの登録
        void AddTest()
        {
            // 順番通りになるように前から登録
            UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
            m_next.AddTest();
        }
    private:
        detail::TestSuiteMediator   m_mediator;
        TestInfo                    m_info;
        detail::iuFactory<TestBody> m_factory;

        EachTest<typename TT::Tail> m_next;
    };

    // 終端
    template<typename DMY>
    class EachTest<detail::TypeList0, DMY>
    {
    public:
        EachTest(const char* /*testsuite*/, const char* /*name*/, size_t /*index*/, const char* /*file*/, int /*line*/) {}
        void AddTest() {}
    };

public:
    // コンストラクタ
    ValueTmpParamTestInstance(const char* testsuite, const char* name, const char* file, int line)
        : m_tests(testsuite, name, 0, file, line)
    {
        m_tests.AddTest();
    }

private:
    EachTest<TypePrams> m_tests;
};

}   // end of namespace tr1
}   // end of namespace iutest

#endif

#endif
