//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_params_util.hpp
 * @brief       iris unit test parameter 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_
#define INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_

//======================================================================
// include
#include "iutest_genparams.hpp"
#include "iutest_genparams_from_file.hpp"

#if IUTEST_HAS_PARAM_TEST
#include "iutest_pool.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// class

/**
 * @brief   パラメータ単体テスト TestInfo データクラス
*/
class IParamTestInfoData
{
public:
    class EachTestBase : public iuIObject {};
    template<typename T>
    class ParamEachTestBase : public EachTestBase
    {
    public:
        virtual void SetParam(const T& param) = 0;
    };
public:
    explicit IParamTestInfoData(const char* name) : m_name(name) {}
    virtual ~IParamTestInfoData() IUTEST_CXX_DEFAULT_FUNCTION
    virtual TestCase* MakeTestCase(const char* , TestTypeId , SetUpMethod , TearDownMethod ) const = 0;
    virtual EachTestBase* RegisterTest(TestCase* , const char* ) const = 0;
    const char* GetName() const { return m_name.c_str(); }
protected:
    ::std::string m_name;
};

/**
 * @brief   パラメータ単体テストインスタンスインターフェイス
*/
class IParamTestCaseInfo
{
public:
    virtual ~IParamTestCaseInfo() {}
protected:
    IParamTestCaseInfo(const ::std::string& base_name, const ::std::string& package_name)
        : m_testcase_base_name(base_name), m_package_name(package_name) {}

public:
    /**
     * @brief   テストパターンの登録
    */
    void AddTestPattern(IParamTestInfoData* testinfo)
    {
        m_testinfos.push_back(testinfo);
    };

public:
    void RegisterTests() const
    {
        for( TestInfoContainer::const_iterator it=m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
        {
            OnRegisterTests(*it);
        }
    }

    ::std::string GetTestCaseBaseName() const { return m_testcase_base_name; }
    ::std::string GetPackageName()      const { return m_package_name; }

public:
    bool is_same(const ::std::string& base_name, const ::std::string& package_name)
    {
        return m_testcase_base_name == base_name && m_package_name == package_name;
    }
    bool is_same(const char* base_name, const char* package_name)
    {
        return m_testcase_base_name == base_name && m_package_name == package_name;
    }

private:
    virtual void OnRegisterTests(IParamTestInfoData*) const = 0;
private:
    typedef ::std::vector<IParamTestInfoData*> TestInfoContainer;
    TestInfoContainer m_testinfos;
protected:
    ::std::string m_testcase_base_name;
    ::std::string m_package_name;
};

/**
 * @brief   パラメータ単体テストインスタンス
 * @tparam  T   = テストクラス
*/
template<class T>
class ParamTestCaseInfo : public IParamTestCaseInfo
{
    typedef T                                       Tester;
    typedef typename Tester::ParamType              ParamType;
    typedef detail::iuIParamGenerator<ParamType>    ParamGenerator;
    typedef typename ParamGenerator::Generator      Generator;
    typedef IParamTestInfoData::ParamEachTestBase<ParamType> EachTest;

    typedef ::std::vector<IParamTestInfoData*> TestInfoContainer;

    typedef ParamGenerator* (*pfnCreateGeneratorFunc)();
    typedef ::std::string (*pfnParamNameGeneratorFunc)(const TestParamInfo<ParamType>&);

    class Functor
    {
    public:
        Functor()
            : CreateGen(NULL), ParamNameGen(NULL) {}
        Functor(pfnCreateGeneratorFunc c, pfnParamNameGeneratorFunc p)
            : CreateGen(c), ParamNameGen(p) {}
        pfnCreateGeneratorFunc      CreateGen;
        pfnParamNameGeneratorFunc   ParamNameGen;
    };

public:
    /// コンストラクタ
    ParamTestCaseInfo(const ::std::string& testcase_name, const ::std::string& package_name)
        : IParamTestCaseInfo(testcase_name, package_name)
    {
    }
    ParamTestCaseInfo(const char* testcase_name, const char* package_name)
        : IParamTestCaseInfo(testcase_name, package_name)
    {
    }
    virtual ~ParamTestCaseInfo() {}

    /**
     * @brief   インスタンスの登録
    */
    int AddTestCaseInstantiation(::std::string name
        , pfnCreateGeneratorFunc create_func, pfnParamNameGeneratorFunc paramname_func)
    {
#if IUTEST_HAS_STD_EMPLACE
        m_instantiation.emplace_back(name, Functor(create_func, paramname_func));
#else
        m_instantiation.push_back(InstantiationPair(name, Functor(create_func, paramname_func)));
#endif
        return 0;
    }

    /**
     * @brief   テストの作成
    */
    virtual void OnRegisterTests(IParamTestInfoData* infodata) const IUTEST_CXX_OVERRIDE
    {
        for( typename InstantiationContainer::const_iterator gen_it=m_instantiation.begin()
            , gen_end=m_instantiation.end(); gen_it != gen_end; ++gen_it )
        {
            // パラメータ生成器の作成
            detail::scoped_ptr<ParamGenerator> p((gen_it->second.CreateGen)());

            ::std::string testcase_name = m_package_name;
            if( !gen_it->first.empty() )
            {
                testcase_name += gen_it->first;
                testcase_name += "/";
            }
            testcase_name += m_testcase_base_name;
            TestCase* testcase = infodata->MakeTestCase(testcase_name.c_str()
                , internal::GetTypeId<Tester>()
                , Tester::SetUpTestCase
                , Tester::TearDownTestCase);

            if( p.get() != NULL )
            {
                size_t i=0;
                for( p->Begin(); !p->IsEnd(); p->Next() )
                {
                    const ::std::string name = MakeParamTestName(infodata->GetName()
                        , gen_it->second.ParamNameGen(TestParamInfo<ParamType>(p->GetCurrent(), i)) );
#if IUTEST_CHECK_STRICT
                    if( !CheckTestName(testcase, name) )
                    {
                        IUTEST_LOG_(WARNING) << testcase_name << "." << name << " is already exist.";
                    }
#endif
                    EachTest* test = static_cast<EachTest*>(infodata->RegisterTest(testcase, name.c_str()));
                    test->SetParam(p->GetCurrent());
                    ++i;
                }
            }
        }
    }

    static ::std::string DefaultParamNameFunc(const TestParamInfo<ParamType>& info)
    {
        return Tester::MakeTestParamName(info);
    }

    template<typename ParamNameFunctor>
    static ParamNameFunctor GetParamNameGen(ParamNameFunctor func)
    {
        return func;
    }

    static pfnParamNameGeneratorFunc GetParamNameGen()
    {
        return DefaultParamNameFunc;
    }

private:
    static bool CheckTestName(const TestCase* testcase, const::std::string& name)
    {
        const int count = testcase->total_test_count();
        for(int i = 0; i < count; ++i )
        {
            if( detail::IsStringEqual(name.c_str(), testcase->GetTestInfo(i)->name()) )
            {
                return false;
            }
        }
        return true;
    }
private:
    typedef ::std::pair< ::std::string, Functor > InstantiationPair;
    typedef ::std::vector<InstantiationPair> InstantiationContainer;
    InstantiationContainer m_instantiation;
};

/**
 * @brief   パラメータテストパターン保管庫
*/
class ParamTestCaseHolder
{
private:
    ~ParamTestCaseHolder()
    {
        // 解放
        for( TestCaseInfoContainer::const_iterator it=m_testcase_infos.begin(), end=m_testcase_infos.end(); it != end; ++it )
        {
            delete *it;
        }
    }
public:

#if IUTEST_HAS_MEMORY_SANITIZER
    template<typename T>
    ParamTestCaseInfo<T>* IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY GetTestCasePatternHolder(const char* testcase_name
        , const ::std::string& package_name IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T) )
    {
        (void)package_name;
        const char* package = "";
        ParamTestCaseInfo<T>* p = static_cast<ParamTestCaseInfo<T>*>(FindTestCasePatternHolder(testcase_name, package));
        if( p == NULL )
        {
            p = new ParamTestCaseInfo<T>(testcase_name, package);
            m_testcase_infos.push_back(p);
        }
        return p;
    }
#else
    template<typename T>
    ParamTestCaseInfo<T>* IUTEST_ATTRIBUTE_NO_SANITIZE_MEMORY GetTestCasePatternHolder(const ::std::string& testcase
        , const ::std::string& package IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T) )
    {
        ParamTestCaseInfo<T>* p = static_cast<ParamTestCaseInfo<T>*>(FindTestCasePatternHolder(testcase, package));
        if( p == NULL )
        {
            p = new ParamTestCaseInfo<T>(testcase, package);
            m_testcase_infos.push_back(p);
        }
        return p;
    }
#endif

private:
    template<typename T>
    IParamTestCaseInfo* FindTestCasePatternHolder(const T& testcase, const T& package)
    {
        for( TestCaseInfoContainer::iterator it=m_testcase_infos.begin(), end=m_testcase_infos.end(); it != end; ++it )
        {
            if( (*it)->is_same(testcase, package) )
            {
                return (*it);
            }
        }
        return NULL;
    }

public:
    size_t count() const { return m_testcase_infos.size(); }

private:
    struct RegisterTestsFunctor
    {
        inline void operator ()(const IParamTestCaseInfo* p) const
        {
            p->RegisterTests();
        }
    };

    // テストを登録
    void RegisterTests()
    {
        ::std::for_each(m_testcase_infos.begin(), m_testcase_infos.end(), RegisterTestsFunctor());
    }
private:
    friend class ::iutest::UnitTest;
    typedef ::std::vector<IParamTestCaseInfo*> TestCaseInfoContainer;
    TestCaseInfoContainer m_testcase_infos;
};

}   // end of namespace detail
}   // end of namespace iutest

#endif

#endif // INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_
