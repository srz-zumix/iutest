//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_params_util.hpp
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
#ifndef INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_
#define INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_genparams.hpp"
#include "iutest_genparams_from_file.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_PARAM_TEST
// IWYU pragma: begin_exports
#include "iutest_pool.hpp"
// IWYU pragma: end_exports

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
    virtual TestSuite* MakeTestSuite(const ::std::string& , TestTypeId , SetUpMethod , TearDownMethod ) const = 0;
    virtual EachTestBase* RegisterTest(TestSuite* , const ::std::string& ) const = 0;
    const char* GetName() const { return m_name.c_str(); }
protected:
    ::std::string m_name;
};

/**
 * @brief   パラメータ単体テストインスタンスインターフェイス
*/
class IParamTestSuiteInfo
{
public:
    virtual ~IParamTestSuiteInfo() {}
protected:
    IParamTestSuiteInfo(const ::std::string& base_name, const ::std::string& package_name)
        : m_testsuite_base_name(base_name), m_package_name(package_name) {}
    IParamTestSuiteInfo(const char* base_name, const char* package_name)
        : m_testsuite_base_name(base_name), m_package_name(package_name) {}

public:
    /**
     * @brief   テストパターンの登録
    */
    void AddTestPattern(IParamTestInfoData* testinfo)
    {
        m_testinfos.push_back(testinfo);
    }

public:
    void RegisterTests() const
    {
        for( TestInfoContainer::const_iterator it=m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
        {
            OnRegisterTests(*it);
        }
    }

    ::std::string GetTestSuiteBaseName() const { return m_testsuite_base_name; }
    ::std::string GetPackageName()      const { return m_package_name; }

public:
    bool is_same(const ::std::string& base_name, const ::std::string& package_name)
    {
        return m_testsuite_base_name == base_name && m_package_name == package_name;
    }
    bool is_same(const char* base_name, const char* package_name)
    {
        return m_testsuite_base_name == base_name && m_package_name == package_name;
    }

private:
    virtual void OnRegisterTests(IParamTestInfoData*) const = 0;
private:
    typedef ::std::vector<IParamTestInfoData*> TestInfoContainer;
    TestInfoContainer m_testinfos;
protected:
    ::std::string m_testsuite_base_name;
    ::std::string m_package_name;
    const char* m_file;
    int m_line;
};

/**
 * @brief   パラメータ単体テストインスタンス
 * @tparam  T   = テストクラス
*/
template<class T>
class ParamTestSuiteInfo IUTEST_CXX_FINAL : public IParamTestSuiteInfo
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
            : CreateGen(NULL), ParamNameGen(NULL), m_file(NULL), m_line(0) {}
        Functor(pfnCreateGeneratorFunc c, pfnParamNameGeneratorFunc p, const char* file, int line)
            : CreateGen(c), ParamNameGen(p), m_file(file), m_line(line) {}
        pfnCreateGeneratorFunc      CreateGen;
        pfnParamNameGeneratorFunc   ParamNameGen;
        const char* m_file;
        int m_line;
    };

public:
    /// コンストラクタ
    ParamTestSuiteInfo(const ::std::string& testsuite_name, const ::std::string& package_name)
        : IParamTestSuiteInfo(testsuite_name, package_name)
    {
    }
    ParamTestSuiteInfo(const char* testsuite_name, const char* package_name)
        : IParamTestSuiteInfo(testsuite_name, package_name)
    {
    }
    virtual ~ParamTestSuiteInfo() {}

    /**
     * @brief   インスタンスの登録
    */
    int AddTestSuiteInstantiation(::std::string name
        , pfnCreateGeneratorFunc create_func, pfnParamNameGeneratorFunc paramname_func
        , const char* file, int line)
    {
#if IUTEST_HAS_STD_EMPLACE
        m_instantiation.emplace_back(name, Functor(create_func, paramname_func, file, line));
#else
        m_instantiation.push_back(InstantiationPair(name, Functor(create_func, paramname_func, file, line)));
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

            const ::std::string testsuite_name = CreateTestSuiteName(gen_it->first);
            const char* file = gen_it->second.m_file;
            const int line = gen_it->second.m_line;
            TestSuite* testsuite = infodata->MakeTestSuite(testsuite_name
                , internal::GetTypeId<Tester>()
                , IUTEST_GET_SETUP_TESTSUITE(Tester, file, line)
                , IUTEST_GET_TEARDOWN_TESTSUITE(Tester, file, line));

            if( p.get() != NULL )
            {
                size_t i=0;
                for( p->Begin(); !p->IsEnd(); p->Next() )
                {
                    const ::std::string name = MakeParamTestName(infodata->GetName()
                        , gen_it->second.ParamNameGen(TestParamInfo<ParamType>(p->GetCurrent(), i)) );
#if IUTEST_CHECK_STRICT
                    if( !CheckTestName(testsuite, name) )
                    {
                        IUTEST_LOG_(WARNING) << testsuite_name << "." << name << " is already exist.";
                    }
#endif
                    EachTest* test = static_cast<EachTest*>(infodata->RegisterTest(testsuite, name));
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
    ::std::string CreateTestSuiteName(const ::std::string& generator_name) const
    {
        ::std::string testsuite_name = m_package_name;
        if( !generator_name.empty() )
        {
            testsuite_name += generator_name;
            testsuite_name += "/";
        }
        testsuite_name += m_testsuite_base_name;
        return testsuite_name;
    }
private:
    static bool CheckTestName(const TestSuite* testsuite, const::std::string& name)
    {
        const int count = testsuite->total_test_count();
        for(int i = 0; i < count; ++i )
        {
            if( detail::IsStringEqual(name.c_str(), testsuite->GetTestInfo(i)->name()) )
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
class ParamTestSuiteHolder
{
private:
    ~ParamTestSuiteHolder()
    {
        // 解放
        for( TestSuiteInfoContainer::const_iterator it=m_testsuite_infos.begin(), end=m_testsuite_infos.end(); it != end; ++it )
        {
            delete *it;
        }
    }

public:
    template<typename T>
    ParamTestSuiteInfo<T>* GetTestSuitePatternHolder(const ::std::string& testsuite
        , const ::std::string& package IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T) )
    {
        ParamTestSuiteInfo<T>* p = static_cast<ParamTestSuiteInfo<T>*>(FindTestSuitePatternHolder(testsuite, package));
        if( p == NULL )
        {
            p = new ParamTestSuiteInfo<T>(testsuite, package);
            m_testsuite_infos.push_back(p);
        }
        return p;
    }

private:
    template<typename T>
    IParamTestSuiteInfo* FindTestSuitePatternHolder(const T& testsuite, const T& package)
    {
        for( TestSuiteInfoContainer::iterator it=m_testsuite_infos.begin(), end=m_testsuite_infos.end(); it != end; ++it )
        {
            if( (*it)->is_same(testsuite, package) )
            {
                return (*it);
            }
        }
        return NULL;
    }

public:
    size_t count() const { return m_testsuite_infos.size(); }

private:
    // テストを登録
    void RegisterTests() const
    {
        for( TestSuiteInfoContainer::const_iterator it = m_testsuite_infos.begin(); it != m_testsuite_infos.end(); ++it)
        {
            (*it)->RegisterTests();
        }
    }
private:
    friend class ::iutest::UnitTest;
    typedef ::std::vector<IParamTestSuiteInfo*> TestSuiteInfoContainer;
    TestSuiteInfoContainer m_testsuite_infos;
};

}   // end of namespace detail
}   // end of namespace iutest

#endif

#endif // INCG_IRIS_IUTEST_PARAMS_UTIL_HPP_19F0C0BB_EEAE_4E8B_B269_A09A4A45E890_
