// iutest_mfc_sample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "iutest_mfc_sample.h"
#include "iutest.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
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

IUTEST(MFC, List)
{
	int a[10];
	CList<int> list;
	for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
	{
		a[i] = i;
		list.AddTail(i);
	}
	IUTEST_ASSERT_EQ_COLLECTIONS(
		  ::iutest::mfc::begin(list)
		, ::iutest::mfc::end(list)
		, ::std::begin(a)
		, ::std::end(a)
	);
}

IUTEST(MFC, Array)
{
	int a[10];
	CArray<int> ar;
	ar.SetSize(IUTEST_PP_COUNTOF(a));
	for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
	{
		a[i] = i;
		ar[i] = i;
	}
	IUTEST_ASSERT_EQ_COLLECTIONS(
		  ::iutest::mfc::begin(ar)
		, ::iutest::mfc::end(ar)
		, ::std::begin(a)
		, ::std::end(a)
		);
}

IUTEST(MFC, Map)
{
	CMap<int, int, int, int> map;
	CMapStringToOb ms;
}

template<typename T>
class MFCArrayTypedTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(MFCArrayTypedTest, ::iutest::Types<CByteArray, CWordArray, CDWordArray, CUIntArray, CPtrArray, CObArray>);

template<typename T>
struct test_value
{
	static T get(int index) { return index; }
};
template<typename T>
struct test_value< T* >
{
	static T* get(int index) { return NULL; }
};

IUTEST_TYPED_TEST(MFCArrayTypedTest, EqCollections)
{
	struct X : public TypeParam { using TypeParam::BASE_TYPE; };
	typename X::BASE_TYPE a[10];
	TypeParam ar;
	ar.SetSize(IUTEST_PP_COUNTOF(a));
	for(int i = 0; i < IUTEST_PP_COUNTOF(a); ++i)
	{
		a[i] = test_value<X::BASE_TYPE>::get(i);
		ar[i] = test_value<X::BASE_TYPE>::get(i);
	}
	IUTEST_ASSERT_EQ_COLLECTIONS(
		  ::iutest::mfc::begin(ar)
		, ::iutest::mfc::end(ar)
		, ::std::begin(a)
		, ::std::end(a)
		);
}

