//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_package.hpp
 * @brief       iris unit test testsuite package
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PACKAGE_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_IUTEST_PACKAGE_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// define
/**
 * @ingroup TESTDEF
 * @brief   パッケージ名前空間の定義
 * @param   name    = パッケージ名
*/
#define IUTEST_PACKAGE(name)    IIUT_PACKAGE_(name)

/**
 * @private
 * @{
*/

#if IUTEST_HAS_PACKAGE

#define IUTEST_CONCAT_PACKAGE_(testsuitename_)   IIUT_CONCAT_PACKAGE_I(testsuitename_)
#define IIUT_CONCAT_PACKAGE_I(testsuitename_)                    \
    iuTest_ConcatTestSuiteName( iuTest_GetTestSuitePackageName(  \
        static_cast<iuTest_TestSuitePackage*>(NULL))             \
        , #testsuitename_)

#define IUTEST_GET_PACKAGENAME_()   \
    iuTest_GetTestSuitePackageName( static_cast<iuTest_TestSuitePackage*>(NULL) )


#if IUTEST_HAS_IF_EXISTS

#define IIUT_PACKAGE_DECL_NAME_FUNC(name)               \
    static ::std::string IUTEST_ATTRIBUTE_UNUSED_       \
    iuTest_GetTestSuitePackageName(const iuTest_TestSuitePackage*) {        \
        return iuTest_GetTestSuiteParentPackageName(    \
            static_cast<iuTest_TestSuiteParentPackage*>(NULL)) + #name "."; \
    }

#define IIUT_PACKAGE_DECL_PARENT_NAME_FUNC(name)        \
    static ::std::string IUTEST_ATTRIBUTE_UNUSED_       \
    iuTest_GetTestSuiteParentPackageName(const iuTest_TestSuiteParentPackage*) {              \
        return iuTest_GetTestSuitePackageName(static_cast<iuTest_TestSuitePackage*>(NULL));   \
    }


#define IIUT_PACKAGE_CURRENT_NAMESPACE_(name)               \
    class iuTest_TestSuitePackage;                          \
    __if_not_exists(name::iuTest_GetTestSuitePackageName) { \
        IIUT_PACKAGE_DECL_NAME_FUNC(name)                   \
    }

#define IIUT_PACKAGE_PARENT_NAMESPACE_(name)                \
    class iuTest_TestSuiteParentPackage;                    \
    __if_not_exists(name::iuTest_GetTestSuiteParentPackageName) {   \
        IUTEST_PRAGMA_MSC_WARN_PUSH()                       \
        IUTEST_PRAGMA_MSC_WARN_DISABLE(4505)                \
        IIUT_PACKAGE_DECL_PARENT_NAME_FUNC(name)            \
        IUTEST_PRAGMA_MSC_WARN_POP()                        \
    }

#else

#define IIUT_PACKAGE_CURRENT_NAMESPACE_(name)               \
    class iuTest_TestSuitePackage;                          \
    namespace { const int IUTEST_PP_CAT(k_iutest_package_##name##_dummy_, IUTEST_PP_UNIQUEID)   \
        IUTEST_ATTRIBUTE_UNUSED_ = ::iutest::detail::package_name_server<                       \
                iuTest_TestSuitePackage>::setname(iuTest_GetTestSuiteParentPackageName(         \
                    static_cast<iuTest_TestSuiteParentPackage*>(NULL)) + #name ".");            \
    }

#define IIUT_PACKAGE_PARENT_NAMESPACE_(name)                \
    class iuTest_TestSuiteParentPackage;                    \
    namespace { const int IUTEST_PP_CAT(k_iutest_package_##name##_parent_dummy_, IUTEST_PP_UNIQUEID)    \
        IUTEST_ATTRIBUTE_UNUSED_ = ::iutest::detail::package_name_server<iuTest_TestSuiteParentPackage> \
        ::setname(iuTest_GetTestSuitePackageName(static_cast<iuTest_TestSuitePackage*>(NULL)));         \
    }

#endif

#define IIUT_PACKAGE_(name)                                 \
    namespace name {                                        \
        IIUT_PACKAGE_CURRENT_NAMESPACE_(name)               \
        IIUT_PACKAGE_PARENT_NAMESPACE_(name)                \
    }                                                       \
    namespace name

#else

#define IUTEST_CONCAT_PACKAGE_(testsuitename_)  IIUT_CONCAT_PACKAGE_I(testsuitename_)
#define IIUT_CONCAT_PACKAGE_I(testsuitename_)   #testsuitename_
#define IIUT_PACKAGE_(name)                     namespace name
#define IUTEST_GET_PACKAGENAME_()               ""

#endif

/**
 * @}
*/

#if IUTEST_HAS_PACKAGE

class iuTest_TestSuitePackage;           //!< パッケージ名参照用定義
class iuTest_TestSuiteParentPackage;     //!< 親パッケージ名参照用定義

#if IUTEST_HAS_IF_EXISTS

/**
 * @brief   グローバルパッケージ名の取得
 * @return  パッケージ名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_ iuTest_GetTestSuitePackageName(const iuTest_TestSuitePackage*)
{
    return "";
}

/**
 * @brief   親空間のパッケージ名の取得
 * @return  パッケージ名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_ iuTest_GetTestSuiteParentPackageName(const iuTest_TestSuiteParentPackage*)
{
    return "";
}

#else

namespace iutest {
namespace detail
{

/**
 * @private
 * @brief   パッケージ名のサーバー
*/
template<typename T>
class package_name_server
{
    static ::std::string& getname_() { static ::std::string s; return s; }
public:
    static ::std::string getname() { return getname_(); }
    static int setname(const ::std::string& s)
    {
        ::std::string& name = getname_();
        if( name.empty() )
        {
            name = s;
        }
        return 0;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

/**
 * @brief   パッケージ名の取得
 * @return  パッケージ名
*/
template<typename T>
::std::string iuTest_GetTestSuitePackageName(T*)         // NOLINT
{
    return ::iutest::detail::package_name_server<T>::getname();
}

/**
 * @brief   親空間のパッケージ名の取得
 * @return  パッケージ名
*/
template<typename T>
::std::string iuTest_GetTestSuiteParentPackageName(T*)   // NOLINT
{
    return ::iutest::detail::package_name_server<T>::getname();
}

#endif

/**
 * @brief   TestSuite 名との結合
 * @return  TestSuite 名
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_ iuTest_ConcatTestSuiteName(const ::std::string& package, const char* testsuite_name)
{
    return package + testsuite_name;
}

#endif

#endif // INCG_IRIS_IUTEST_PACKAGE_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
