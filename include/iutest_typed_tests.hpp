//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_typed_tests.hpp
 * @brief       iris unit test typed test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_
#define INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_

//======================================================================
// include
#include "internal/iutest_typed_util.hpp"

#if IUTEST_HAS_TYPED_TEST_P
#  include "internal/iutest_pool.hpp"
#endif

//======================================================================
// define

#if IUTEST_HAS_TYPED_TEST
/**
 * @defgroup    TYPED_TEST  型付けテスト
*/

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_TYPED_TEST_CASE(testcase_, types_)
 * @brief   型付けテストケースの登録
 * @param   testcase_   = テストケース名
 * @param   ...         = タイプリスト
*/
#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IUTEST_TYPED_TEST_CASE(testcase_, ...)    IIUT_TYPED_TEST_CASE_(testcase_, __VA_ARGS__)
#else
#  define IUTEST_TYPED_TEST_CASE(testcase_, types_) IIUT_TYPED_TEST_CASE_(testcase_, types_)
#endif

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_TYPED_TEST(testcase_, testname_)
 * @brief   型付けテスト関数定義マクロ
 * @param   testcase_   = テストケース名
 * @param   testname_   = テスト名
*/
#define IUTEST_TYPED_TEST(testcase_, testname_)     IUTEST_TYPED_TEST_(testcase_, testname_)

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_T(testcase_, testname_)
 * @brief   型付けテスト関数定義マクロ
 * @param   testcase_   = テストケース名
 * @param   testname_   = テスト名
*/
#define IUTEST_T(testcase_, testname_)              IUTEST_TYPED_TEST_(testcase_, testname_)


/**
 * @private
 * @{
*/
#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
#define IIUT_TYPED_TEST_PARAMS_(testcase_)                                          \
    IIUT_TYPED_TEST_PARAMS_I_( IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testcase_)   \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testcase_)
#else
#define IIUT_TYPED_TEST_PARAMS_(testcase_)          IIUT_TYPED_TEST_PARAMS_I_(testcase_)
#endif

#define IIUT_TYPED_TEST_PARAMS_I_(testcase_)        IIUT_TYPED_TEST_PARAMS_II_(IIUT_TO_VARNAME_(testcase_))
#define IIUT_TYPED_TEST_PARAMS_II_(testcase_)       IIUT_TYPED_TEST_PARAMS_III_(testcase_)
#define IIUT_TYPED_TEST_PARAMS_III_(testcase_)      iutest_types_params_##testcase_

#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IIUT_TYPED_TEST_CASE_(testcase_, ...)     \
    typedef ::iutest::detail::TypeList< __VA_ARGS__ >::type IIUT_TYPED_TEST_PARAMS_(testcase_)
#else
#  define IIUT_TYPED_TEST_CASE_(testcase_, types_)      \
    typedef ::iutest::detail::TypeList< types_ >::type  IIUT_TYPED_TEST_PARAMS_(testcase_)
#endif

#define IIUT_TYPED_TEST_I(classname_, testcase_, testcasename_, testname_)          \
    template<typename iutest_TypeParam> class classname_ : public testcase_<iutest_TypeParam> { \
        typedef testcase_<iutest_TypeParam> TestFixture;                            \
        typedef iutest_TypeParam TypeParam;                                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;                         \
    };                                                                              \
    ::iutest::detail::TypeParamTestInstance< classname_, IIUT_TYPED_TEST_PARAMS_(testcase_) >   \
        IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(                           \
        IUTEST_CONCAT_PACKAGE_(testcasename_), IIUT_TO_NAME_STR_(testname_));       \
    template<typename iutest_TypeParam>                                             \
    void classname_<iutest_TypeParam>::Body()

#if IUTEST_HAS_IGNORE_TEST

#define IIUT_TYPED_TEST_I_IGNORE(classname_, testcase_, testcasename_, testname_)   \
    template<typename iutest_TypeParam> class classname_ : public testcase_<iutest_TypeParam> {     \
        typedef testcase_<iutest_TypeParam> TestFixture;                            \
        typedef iutest_TypeParam TypeParam;                                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }  \
        template<typename T>void Body();                                            \
    };                                                                              \
    ::iutest::detail::TypeParamTestInstance< classname_, IIUT_TYPED_TEST_PARAMS_(testcase_) >       \
        IUTEST_TEST_INSTANCE_NAME_(testcase_, testname_)(                           \
        IUTEST_CONCAT_PACKAGE_(testcasename_), IIUT_TO_NAME_STR_(testname_));       \
    template<typename iutest_TypeParam> template<typename T>                        \
    void classname_<iutest_TypeParam>::Body()

#endif

#define IIUT_TYPED_TEST_(macro, testcase_, testname_)                   \
    macro(IUTEST_TEST_CLASS_NAME_(testcase_, testname_)                 \
        , IIUT_TO_VARNAME_(testcase_), IIUT_TO_NAME_(testcase_)         \
        , testname_)

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

#define IIUT_TYPED_TEST_A_(macro, testcase_, testname_)                         \
    IIUT_TYPED_TEST_( macro, IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testcase_) \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testcase_, testname_)

#define IUTEST_TYPED_TEST_(testcase_, testname_)        \
    IIUT_TYPED_TEST_A_(IIUT_TYPED_TEST_I, testcase_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TYPED_TEST_IGNORE_(testcase_, testname_) \
    IIUT_TYPED_TEST_A_(IIUT_TYPED_TEST_I_IGNORE, testcase_, testname_)

#endif

#else

#define IUTEST_TYPED_TEST_(testcase_, testname_)        \
    IIUT_TYPED_TEST_(IIUT_TYPED_TEST_I, testcase_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TYPED_TEST_IGNORE_(testcase_, testname_) \
    IIUT_TYPED_TEST_(IIUT_TYPED_TEST_I_IGNORE, testcase_, testname_)

#endif

#endif

/**
 * @}
*/

#endif

#if IUTEST_HAS_TYPED_TEST_P
/**
 * @defgroup    TYPE_PARAMETERIZED_TEST 型のパラメータ化テスト
*/

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TYPED_TEST_CASE_P(testcase_)
 * @brief   型パラメータテストケースの登録
 * @param   testcase_   = テストケース名
*/
#define IUTEST_TYPED_TEST_CASE_P(testcase_)             IIUT_TYPED_TEST_CASE_P_(testcase_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TYPED_TEST_P(testcase_, testname_)
 * @brief   型パラメータテスト関数定義マクロ
 * @param   testcase_   = テストケース名
 * @param   testname_   = テスト名
*/
#define IUTEST_TYPED_TEST_P(testcase_, testname_)       IIUT_TYPED_TEST_P_(testcase_, testname_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TP(testcase_, testname_)
 * @brief   型パラメータテスト関数定義マクロ
 * @param   testcase_   = テストケース名
 * @param   testname_   = テスト名
*/
#define IUTEST_TP(testcase_, testname_)                 IIUT_TYPED_TEST_P_(testcase_, testname_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_REGISTER_TYPED_TEST_CASE_P(testcase_, ...)
 * @brief   型パラメータテスト関数登録マクロ
 * @param   testcase_   = テストケース名
*/
#define IUTEST_REGISTER_TYPED_TEST_CASE_P(testcase_, ...)   \
    IIUT_REGISTER_TYPED_TEST_CASE_P_(testcase_, __VA_ARGS__)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(prefix_, testcase_, types_)
 * @brief   型パラメータテスト登録マクロ
 * @param   prefix_     = インスタンス名
 * @param   testcase_   = テストケース名
 * @param   ...         = タイプリスト
*/
#define IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(prefix_, testcase_, ...)   \
    IIUT_INSTANTIATE_TYPED_TEST_CASE_P_(prefix_, testcase_, __VA_ARGS__)


/**
 * @private
 * @{
*/

#define IIUT_TYPED_TEST_CASE_PSTATE_NAME_(testcase_)    s_iutest_typed_test_case_p_state_##testcase_##_
#define IIUT_TYPED_TEST_P_NAMESPACE_(testcase_)         iutest_typed_test_case_p_name_##testcase_##_
#define IIUT_TYPED_TEST_P_ADDTESTNAME(testcase_, testname_)                             \
    static const int s_iutest_##testname_##_defined_dummy_  IUTEST_ATTRIBUTE_UNUSED_ =  \
    IIUT_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).AddTestName(__FILE__, __LINE__, #testcase_, #testname_)


#define IIUT_TYPED_TEST_CASE_P_(testcase_)      \
    static ::iutest::detail::TypedTestCasePState    IIUT_TYPED_TEST_CASE_PSTATE_NAME_(testcase_)

#define IIUT_TYPED_TEST_P_(testcase_, testname_)                \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testcase_)) > 1, "testcase_ must not be empty");    \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testname_)) > 1, "testname_ must not be empty");    \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testcase_) {         \
    template<typename iutest_TypeParam>                         \
    class testname_ : public testcase_<iutest_TypeParam> {      \
        typedef testcase_<iutest_TypeParam> TestFixture;        \
        typedef iutest_TypeParam TypeParam;                     \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;     \
    }; IIUT_TYPED_TEST_P_ADDTESTNAME(testcase_, testname_);     \
    }                                                           \
    template<typename iutest_TypeParam>                         \
    void IIUT_TYPED_TEST_P_NAMESPACE_(testcase_)::testname_<iutest_TypeParam>::Body()

#if IUTEST_HAS_IGNORE_TEST

#define IIUT_TYPED_TEST_P_IGNORE_(testcase_, testname_)         \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testcase_) {         \
    template<typename iutest_TypeParam>                         \
    class testname_ : public testcase_<iutest_TypeParam> {      \
        typedef testcase_<iutest_TypeParam> TestFixture;        \
        typedef iutest_TypeParam TypeParam;                     \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }      \
        template<typename T>void Body();                        \
    }; IIUT_TYPED_TEST_P_ADDTESTNAME(testcase_, testname_);     \
    }                                                           \
    template<typename iutest_TypeParam>template<typename T>     \
    void IIUT_TYPED_TEST_P_NAMESPACE_(testcase_)::testname_<iutest_TypeParam>::Body()

#endif

#define IIUT_REGISTER_TYPED_TEST_CASE_P_(testcase_, ...)                                \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testcase_) {                                 \
        typedef ::iutest::detail::Templates< __VA_ARGS__ >::type iutest_AllTests_;      \
    }                                                                                   \
    static const bool s_iutest_##testcase_##_register_dummy_ IUTEST_ATTRIBUTE_UNUSED_ = \
    IIUT_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).VerifyTestNames(__FILE__, __LINE__, #__VA_ARGS__)

#define IIUT_INSTANTIATE_TYPED_TEST_CASE_P_(prefix_, testcase_, ...)        \
    const bool iutest_##prefix_##_##testcase_ IUTEST_ATTRIBUTE_UNUSED_ =    \
        ::iutest::detail::TypeParameterizedTestCase< testcase_              \
        , IIUT_TYPED_TEST_P_NAMESPACE_(testcase_)::iutest_AllTests_         \
        , ::iutest::detail::TypeList< __VA_ARGS__ >::type >::Register(      \
            #prefix_, IIUT_TO_NAME_STR_(testcase_), IUTEST_GET_PACKAGENAME_()   \
        , IIUT_TYPED_TEST_CASE_PSTATE_NAME_(testcase_).names())

/**
 * @}
*/

#endif

namespace iutest
{

//======================================================================
// class
namespace detail
{

#if IUTEST_HAS_TYPED_TEST
/**
 * @private
 * @internal
 * @brief   Typeパラメータ単体テストインスタンス
 * @tparam  Tester      = テストクラス
 * @tparam  TypeParams  = 型
*/
template<template<typename T> class Tester, typename TypeParams>
class TypeParamTestInstance
{
    /**
     * @brief   各テストのインスタンス
    */
    template<typename TT, typename DMY>
    class EachTest
    {
        typedef typename TT::Head           TypeParam;
        typedef Tester<TypeParam>           TestBody;
        typedef TypedTestCase<TypeParam>    _MyTestCase;
    public:
        // コンストラクタ
        EachTest(const char* testcase, const char* name, size_t index)
            : m_mediator(AddTestCase(testcase, index))
            , m_info(&m_mediator, name, &m_factory)
            , m_next(testcase, name, index+1)
        {
        }
        EachTest(const ::std::string& testcase, const char* name, size_t index)
            : m_mediator(AddTestCase(testcase, index))
            , m_info(&m_mediator, name, &m_factory)
            , m_next(testcase, name, index+1)
        {
        }

    private:
        static TestCase* AddTestCase(const char* testcase, size_t index)
        {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            return UnitTest::instance().AddTestCase<_MyTestCase>(
#else
            return UnitTest::instance().AddTestCase(
#endif
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
                detail::MakeIndexTypedTestName<TypeParam>(testcase, index)
#else
                detail::MakeIndexTestName(testcase, index)
#endif
                , internal::GetTypeId<detail::None>()   // TypeId を統一するためダミー引数を渡す
                , TestBody::SetUpTestCase
                , TestBody::TearDownTestCase
#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
                , detail::explicit_type<_MyTestCase>()
#endif
                );
        }
        static TestCase* AddTestCase(const ::std::string& testcase, size_t index)
        {
            return AddTestCase(testcase.c_str(), index);
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
        TestCaseMediator            m_mediator;
        TestInfo                    m_info;
        detail::iuFactory<TestBody> m_factory;

        EachTest<typename TT::Tail, void> m_next;
    };

    // 終端
    template<typename DMY>
    class EachTest<detail::TypeList0, DMY>
    {
    public:
        EachTest(const char* /*testcase*/, const char* /*name*/, size_t /*index*/) {}
        EachTest(const ::std::string& /*testcase*/, const char* /*name*/, size_t /*index*/) {}
        void AddTest() {}
    };

public:
    // コンストラクタ
    TypeParamTestInstance(const char* testcase, const char* name)
        : m_tests(testcase, name, 0)
    {
        m_tests.AddTest();
    }
    TypeParamTestInstance(const std::string& testcase, const char* name)
        : m_tests(testcase, name, 0)
    {
        m_tests.AddTest();
    }

private:
    EachTest<TypeParams, void> m_tests;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeParamTestInstance);
};

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @private
 * @internal
 * @brief   Typed TestCase 設定保持
*/
class TypedTestCasePState
{
#if IUTEST_TYPED_TEST_P_STRICT
    typedef ::std::set<const char*> nameset_t;
#endif

public:
    TypedTestCasePState() : m_names(NULL) {}
public:
    const char* names() const { return m_names; }

public:
    bool AddTestName(const char* file, int line, const char* testcase_name, const char* test_name)
    {
        if( m_names != NULL )
        {
            IUTEST_LOG_(WARNING) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" must be defined before IUTEST_REGISTER_TYPED_TEST_CASE_P("
                << testcase_name << ", ...).\n";
        }
#if IUTEST_TYPED_TEST_P_STRICT
        m_list.insert(test_name);
#endif
        return true;
    }
    bool VerifyTestNames(const char* file, int line, const char* test_names)
    {
        m_names = test_names;
        IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
#if IUTEST_TYPED_TEST_P_STRICT
        bool ret = true;
        for( nameset_t::iterator it=m_list.begin(), end=m_list.end(); it != end; ++it )
        {
            const char* test_name = *it;
            const char* p = strstr(test_names, test_name);
            if( p != NULL )
            {
                const size_t len = strlen(test_name);
                if( p[len] == '\0' || p[len] == ',' || detail::IsSpace(p[len]) )
                {
                    continue;
                }
                IUTEST_LOG_(FATAL) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" is find in \"" << test_names
                    << "\". expected whitespace or comma : " << p[len] << "(" << static_cast<int>(p[len]) <<  ")\n";
            }
            IUTEST_LOG_(WARNING) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" has not been registered.\n" << "    TestNames: " << test_names;
            ret = false;
        }
        return ret;
#else
        IUTEST_UNUSED_VAR(file);
        IUTEST_UNUSED_VAR(line);
        return true;
#endif
        IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
    }

private:
    const char* m_names;

#if IUTEST_TYPED_TEST_P_STRICT
    nameset_t m_list;
#endif

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypedTestCasePState);
};

/**
 * @private
 * @brief   型パラメータテストのインスタンス化クラス
*/
template<template<typename T> class Fixture, typename Tests, typename Types>
class TypeParameterizedTestCase
{
    template<typename TypeParam, typename TestsList>
    class EachTest : public iuIObject
    {
        typedef typename TestsList::Head        TypeSel;
        typedef typename TypeSel::template bind<TypeParam>::type    TestBody;
        typedef detail::iuFactory<TestBody>     Factory;
        typedef EachTest<TypeParam, TestsList>  _Myt;

        EachTest(TestCase* testcase, const ::std::string& name)
            : m_mediator(testcase)
            , m_info(&m_mediator, name, &m_factory)
        {
            UnitTest::instance().AddTestInfo(testcase, &m_info);
        }
    public:
        // テストの登録
        static void Register(TestCase* testcase, const char* test_names)
        {
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
            IUTEST_CHECK_(test_names != NULL);
            const char* str = detail::SkipSpace(test_names);
            const char* comma = strchr(str, ',');
            ::std::string test_name;
            if( comma == NULL )
            {
                test_name = str;
            }
            else
            {
                test_name = ::std::string(str, static_cast<size_t>(comma - str));
                ++comma;
            }
            _Myt* test = new EachTest(testcase, StripTrailingSpace(test_name));
            // new オブジェクトを管理してもらう
            detail::iuPool::GetInstance().push(test);

            EachTest<TypeParam, typename TestsList::Tail>::Register(testcase, detail::SkipSpace(comma));
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
        }
    private:
        TestCaseMediator    m_mediator;
        Factory             m_factory;
        TestInfo            m_info;
    };

    template<typename TypeParam>
    class EachTest<TypeParam, detail::TemplateTypeList0>
    {
    public:
        static void Register(TestCase* /*testcase*/, const char* /*test_names*/) {}
    };

public:
    /**
     * @brief   テストの登録
    */
    static bool Register(const char* prefix, const char* testcase_name
        , const ::std::string& package_name, const char* names, size_t index=0)
    {
#if IUTEST_HAS_EXCEPTIONS
        try
        {
            return Register_(prefix, testcase_name, package_name, names, index);
        }
        catch (const ::std::exception& e)
        {
            IUTEST_LOG_(FATAL) << "IUTEST_INSTANTIATE_TYPED_TEST_CASE_P register tests failed...\n"
                << e.what();
        }
        catch(...)
        {
            IUTEST_LOG_(FATAL) << "IUTEST_INSTANTIATE_TYPED_TEST_CASE_P register tests failed...\n";
        }
        return false;
#else
        return Register_(prefix, testcase_name, package_name, names, index);
#endif
    }

private:
    static bool Register_(const char* prefix, const char* testcase_name
        , const ::std::string& package_name, const char* names, size_t index)
    {
        typedef typename Types::Head    TypeParam;
        typedef typename Tests::Head    Head;
        typedef Fixture<Head>           FixtureClass;
        typedef TypedTestCase<TypeParam>    _MyTestCase;
        ::std::string full_testcase_name = package_name;
        full_testcase_name +=
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
            detail::MakePrefixedIndexTypedTestName<TypeParam>(prefix, testcase_name, index);
#else
            detail::MakePrefixedIndexTestName(prefix, testcase_name, index);
#endif
        TestCase* testcase =
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            UnitTest::instance().AddTestCase<_MyTestCase>(
#else
            UnitTest::instance().AddTestCase(
#endif
            full_testcase_name
            , internal::GetTypeId<FixtureClass>()
            , FixtureClass::SetUpTestCase
            , FixtureClass::TearDownTestCase
#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            , detail::explicit_type<_MyTestCase>()
#endif
            );

        EachTest<TypeParam, Tests>::Register(testcase, names);

        return TypeParameterizedTestCase<Fixture, Tests, typename Types::Tail>::Register(
            prefix, testcase_name, package_name, names, index + 1);
    }
};

/**
 * @private
 * @brief   型パラメータテストのインスタンス化クラス
 *          終端特殊化
*/
template<template<typename T> class Fixture, typename Tests>
class TypeParameterizedTestCase<Fixture, Tests, detail::TypeList0>
{
public:
    static bool Register(const char* /*prefix*/, const char* /*testcase_name*/
        , const ::std::string& /*package_name*/, const char* /*names*/, size_t index=0)
    {
        IUTEST_UNUSED_VAR(index);
        return true;
    }
};

#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_
