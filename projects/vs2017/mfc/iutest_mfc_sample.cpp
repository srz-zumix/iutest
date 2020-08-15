// iutest_mfc_sample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "iutest_mfc_sample.h"
#include "iutest.hpp"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    IUTEST_UNUSED_VAR(envp);
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(NULL);

    if (hModule != NULL)
    {
        // MFC を初期化して、エラーの場合は結果を印刷します。
        if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
        {
            // TODO: 必要に応じてエラー コードを変更してください。
            _tprintf(_T("致命的なエラー: MFC の初期化ができませんでした。\n"));
            nRetCode = 1;
        }
        else
        {
            // TODO: アプリケーションの動作を記述するコードをここに挿入してください。
            IUTEST_INIT(&argc, argv);
            nRetCode = IUTEST_RUN_ALL_TESTS();
        }
    }
    else
    {
        // TODO: 必要に応じてエラー コードを変更してください。
        _tprintf(_T("致命的なエラー: GetModuleHandle が失敗しました\n"));
        nRetCode = 1;
    }

    return nRetCode;
}

IUTEST(MFC, String)
{
    CString str = _T("Test");
    IUTEST_ASSERT_EQ(_T("Test"), str);
    IUTEST_ASSERT_STREQ(_T("Test"), str);
    IUTEST_ASSERT_STREQ(str, str);

    IUTEST_ASSERT_STRIN(str, _T("Test"));
}

IUTEST(MFC, Rect)
{
    CRect r = { 0, 0, 100, 100 };
    IUTEST_ASSERT_EQ(r, r);
}

template<typename T>
struct test_value
{
    static T get(int index) { return static_cast<T>(index); }
};
template<typename T>
struct test_value< T* >
{
    static T* get(int) { return NULL; }
};
template<>
struct test_value < CString >
{
    static CString get(int index) { CString s; s.Format(_T("%d"), index); return s; }
};

template<typename T>
class MFCArrayTypedTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_SUITE(MFCArrayTypedTest, ::iutest::Types<CArray<int>, CTypedPtrArray<CPtrArray, int*>
    , CByteArray, CWordArray, CDWordArray, CUIntArray, CStringArray, CPtrArray, CObArray>);

IUTEST_TYPED_TEST(MFCArrayTypedTest, EqCollections)
{
    typename iutest::mfc::CContainer<TypeParam>::BASE_TYPE a[10];
    TypeParam ar;
    ar.SetSize(IUTEST_PP_COUNTOF(a));
    for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
    {
        a[i] = test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i);
        ar[i] = test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i);
    }
    IUTEST_ASSERT_EQ_COLLECTIONS(
          ::iutest::mfc::begin(ar)
        , ::iutest::mfc::end(ar)
        , ::std::begin(a)
        , ::std::end(a)
        );
}

template<typename T>
class MFCListTypedTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_SUITE(MFCListTypedTest, ::iutest::Types<CList<int>, CTypedPtrList<CPtrList, int*>
    , CStringList, CPtrList, CObList>);

IUTEST_TYPED_TEST(MFCListTypedTest, EqCollections)
{
    typename iutest::mfc::CContainer<TypeParam>::BASE_TYPE a[10];
    TypeParam list;
    for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
    {
        a[i] = test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i);
        list.AddTail(test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i));
    }
    IUTEST_ASSERT_EQ_COLLECTIONS(
          ::iutest::mfc::begin(list)
        , ::iutest::mfc::end(list)
        , ::std::begin(a)
        , ::std::end(a)
        );
}

template<typename T>
class MFCMapTypedTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_SUITE(MFCMapTypedTest, ::iutest::Types< CMap<int, int, int, int>
    , CTypedPtrMap<CMapPtrToPtr, int*, int*>, CTypedPtrMap<CMapPtrToWord, int*, WORD>
    , CTypedPtrMap<CMapWordToPtr, WORD, int*>, CTypedPtrMap<CMapStringToPtr, CString, int*>
    , CMapWordToPtr, CMapWordToOb, CMapPtrToPtr, CMapPtrToWord
    , CMapStringToPtr, CMapStringToOb, CMapStringToString >);

IUTEST_TYPED_TEST(MFCMapTypedTest, EqCollections)
{
    TypeParam map;
    for(int i = 0; i < 10; ++i)
    {
        map.SetAt(test_value<iutest::mfc::CContainer<TypeParam>::BASE_KEY>::get(i)
            , test_value<iutest::mfc::CContainer<TypeParam>::BASE_VALUE>::get(i) );
    }
    IUTEST_ASSERT_EQ_COLLECTIONS(
          ::iutest::mfc::begin(map)
        , ::iutest::mfc::end(map)
        , ::iutest::mfc::begin(map)
        , ::iutest::mfc::end(map)
        );
}


#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

IUTEST_TYPED_TEST(MFCArrayTypedTest, Matcher)
{
    TypeParam ar;
    ar.SetSize(10);
    for(int i = 0; i < 10; ++i)
    {
        ar[i] = test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i);
    }
    IUTEST_EXPECT_THAT(::iutest::mfc::make_container(ar), Each(_));
}

IUTEST_TYPED_TEST(MFCListTypedTest, Matcher)
{
    TypeParam list;
    for(int i = 0; i < 10; ++i)
    {
        list.AddTail(test_value<iutest::mfc::CContainer<TypeParam>::BASE_TYPE>::get(i));
    }
    IUTEST_EXPECT_THAT(::iutest::mfc::make_container(list), Each(_));
}

IUTEST_TYPED_TEST(MFCMapTypedTest, Matcher)
{
    TypeParam map;
    for(int i = 0; i < 10; ++i) {
        map.SetAt(test_value<iutest::mfc::CContainer<TypeParam>::BASE_KEY>::get(i)
            , test_value<iutest::mfc::CContainer<TypeParam>::BASE_VALUE>::get(i));
    }
    IUTEST_EXPECT_THAT(::iutest::mfc::make_container(map), Each(Key(_)));
    IUTEST_EXPECT_THAT(::iutest::mfc::make_container(map), Each(Pair(_, _)));
}

#endif

