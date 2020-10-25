//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_body.hpp
 * @brief       iris unit test テスト単体クラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_BODY_HPP_3EEA6706_9954_4330_B292_129667FA6B96_
#define INCG_IRIS_IUTEST_BODY_HPP_3EEA6706_9954_4330_B292_129667FA6B96_

//======================================================================
// include
#include "internal/iutest_mediator.hpp"

namespace iutest
{

//======================================================================
// declare
template<typename T>class WithParamInterface;
template<typename T>class TestWithParam;

namespace detail
{

::std::string MakeIndexName(size_t index);

}

//======================================================================
// class
/**
 * @brief   テストベース
*/
class Test
{
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(Test);

public:
    Test()
        : test_info_(NULL)
        , m_test_info(NULL)
#if IUTEST_HAS_GENRAND
        , m_random_seed(0)
#endif
    {
        CurrentTestObserver::s_current = this;
    }

    virtual ~Test()
    {
        CurrentTestObserver::s_current = NULL;
    }

public:
    /**
     * @brief   実行中の TestInfo の取得
    */
    static const TestInfo* GetCurrentTestInfo()
    {
        const Test* curr = GetCurrentTest();
        if( curr == NULL || curr->m_test_info == NULL )
        {
            return NULL;
        }
        return curr->m_test_info->ptr();
    }

    /**
     * @brief   実行中の Test の取得
    */
    static Test* GetCurrentTest() { return CurrentTestObserver::GetCurrentTest(); }


    /**
     * @brief   致命的なエラーが出たかどうか
     * @return  真偽値
    */
    static bool HasFatalFailure()
    {
        return GetCurrentTest()->m_test_info->HasFatalFailure();
    }

    /**
     * @brief   致命的ではないエラーが出たかどうか
     * @return  真偽値
    */
    static bool HasNonfatalFailure()
    {
        return GetCurrentTest()->m_test_info->HasNonfatalFailure();
    }

    /**
     * @brief   エラーが出たかどうか
     * @return  真偽値
    */
    static bool HasFailure()
    {
        return GetCurrentTest()->m_test_info->HasFailure();
    }

    /**
     * @brief   スキップされたかどうか
     * @return  真偽値
    */
    static bool IsSkipped()
    {
        return GetCurrentTest()->m_test_info->IsSkipped();
    }

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
    /**
     * @brief   テスト結果の情報追加
     * @param [in]  key     = プロパティのキー
     * @param [in]  value   = 値
    */
    static void RecordProperty(const ::std::string& key, const ::std::string& value);
#endif

    /**
     * @brief   テスト結果の情報追加
     * @param [in]  key     = プロパティのキー
     * @param [in]  value   = 値
    */
    template<typename T>
    static void RecordProperty(const ::std::string& key, const T& value)
    {
        RecordPropertyString(key, PrintToString(value));
    }

#if IUTEST_HAS_GENRAND

    /**
     * @brief   乱数の生成
     * @note    乱数シードは --iutest_random_seed で指定した値になります。
     *          指定しなかった場合は実行時に決定します。
    */
    unsigned int    genrand() { return m_random.genrand(); }
    /**
     * @overload
     * @param [in]  max = 上限値
     * @return      [0,max) の乱数を生成
    */
    unsigned int    genrand(unsigned int max)   { return m_random.genrand(max); }
    /**
     * @overload
     * @return      max = [0,1] の乱数を生成
    */
    float           genrandf() { return m_random.genrandf(); }
    /** 乱数シードの取得 */
    unsigned int    random_seed() const IUTEST_CXX_NOEXCEPT_SPEC { return m_random_seed; }

    /** 乱数生成器の取得 */
    detail::iuRandom& random_engine() { return m_random; }

#endif

protected:
    virtual void SetUp() {} //!< 実行前処理
    virtual void Body() {}  //!< テスト実装部
    virtual void TearDown() {}  //!< 実行後処理

public:
    static void SetUpTestSuite() {}      //!< test suite setup
    static void TearDownTestSuite() {}   //!< test suite tear down
#if IUTEST_HAS_TESTCASE
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
#endif

private:
    /**
     * @brief   テストの実行
    */
    void Run(detail::iuITestInfoMediator* test_info);

    /**
     * @brief   テスト結果の情報追加
     * @param [in]  key     = プロパティのキー
     * @param [in]  value   = 値
    */
    static void RecordPropertyString(const ::std::string& key, const ::std::string& value);

private:
    struct should_be_SetUp {};
    virtual should_be_SetUp* Setup() IUTEST_CXX_FINAL { return NULL; }

private:
    template<typename DMY>
    class Observer
    {
    public:
        static Test* s_current;
    public:
        static Test* GetCurrentTest() IUTEST_CXX_NOEXCEPT_SPEC { return s_current; }
    };

    typedef Observer<void> CurrentTestObserver;

private:
    class TestRecordPropertyHelper
    {
    public:
        static void RecordProperty(const TestProperty& prop);
    };
protected:
    const TestInfo* test_info_; //!< テスト中に簡単にアクセス可能なように

private:
    friend class UnitTest;
    friend class UnitTestImpl;
    friend class TestInfo;
    friend class detail::UncaughtScopedTrace;

    detail::iuITestInfoMediator*    m_test_info;
#if IUTEST_HAS_GENRAND
    detail::iuRandom                m_random;
    unsigned int                    m_random_seed;
#endif
};

/**
 * @brief   値のパラメータ化テストのパラメータ情報
*/
template<typename ParamType>
struct TestParamInfo
{
    TestParamInfo(const ParamType& p, size_t i)
        : param(p), index(i) {}
    ParamType param;
    size_t index;
};

/**
 * @brief   パラメータテストインターフェース
 * @tparam  T = パラメータ型
*/
template<typename T>
class WithParamInterface
{
public:
    typedef T ParamType;    //!< パラメータ型
    typedef TestParamInfo<T> TestParamInfoType; //!< パラメータ情報型
protected:
    virtual ~WithParamInterface() {}

public:
    /**
     * @brief   パラメータの取得
    */
    static const ParamType& GetParam()
    {
        IUTEST_CHECK_(s_params != NULL) << "GetParam() can only use the value-parameterized test";
        IUTEST_ANALYSIS_ASSUME(s_params != NULL);
        return *s_params;
    }

#if IUTEST_HAS_TUPLE
    /**
     * @brief   パラメータの取得
    */
    template<int N>
    static const typename tuples::tuple_element<N, ParamType>::type& GetParam()
    {
        return tuples::get<N>(GetParam());
    }
#endif

    /**
     * @brief   テスト名の生成
    */
    static const ::std::string MakeTestParamName(const TestParamInfoType& info)
    {
        return detail::MakeIndexName(info.index);
    }

    /** @private */
    static void SetParam(const ParamType* params) IUTEST_CXX_NOEXCEPT_SPEC { s_params = params; }

private:
    static const ParamType* s_params;
};

template<typename T>
const T* WithParamInterface<T>::s_params = NULL;

/**
 * @brief   パラメータテストベース
 * @tparam  T = パラメータ型
*/
template<typename T>
class TestWithParam : public Test, public WithParamInterface<T>
{
};

namespace detail
{

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

/**
 * @brief   有益な TestFixture が定義されているかどうか
*/
template<typename T>
class is_useful_testfixture : public iutest_type_traits::false_type {};

namespace is_useful_testfixture_helper
{

template<typename T>
class is_override_setup {
    template<bool b, typename U>struct impl { typedef iutest_type_traits::false_type type; };
    template<typename U>struct impl<true, U>
    {
        typedef int  yes_t;
        typedef char no_t;
        static no_t check(void(Test::*)());
        static yes_t check(...);
        typedef iutest_type_traits::bool_constant< sizeof(check(&U::SetUp)) == sizeof(yes_t) > type;
    };
public:
    typedef typename impl< iutest_type_traits::is_base_of<Test, T>::value, T>::type type;
};

}   // end of namespace is_useful_testfixture_helper

template<typename T>
class is_useful_testfixture<void (int(T))> : public is_useful_testfixture_helper::is_override_setup<T>::type    // NOLINT
{
};

#endif

inline bool IsDisableTestName(const ::std::string& name)
{
    if( detail::IsStringForwardMatching(name, "DISABLED_")
        || detail::IsStringContains(name, "/DISABLED_") )
    {
        return true;
    }
    return false;
}

}   // end of namespace detail

}   // end of namespace iutest

template<typename DMY>
::iutest::Test* ::iutest::Test::Observer<DMY>::s_current = NULL;

#if !IUTEST_HAS_LIB
#  include "impl/iutest_body.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_BODY_HPP_3EEA6706_9954_4330_B292_129667FA6B96_
