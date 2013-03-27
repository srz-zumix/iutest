//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		main.cpp
 * @brief		sample main ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

/*
 * is not available vprintf, can be replaced.
*/
//#define IUTEST_VPRINTF

/*
 * include testing framework
*/
#include "../include/iutest.hpp"

#if defined(USE_TAP)
#include "../include/listener/iutest_tap_printer.hpp"
#endif
#if defined(USE_PROGRESS)
#include "../include/listener/iutest_progress_printer.hpp"
#endif

/** --------------------------------------------------
 * Environment サンプル
*//*--------------------------------------------------*/
class FooEnvironment : public ::iutest::Environment
{
	virtual void	SetUp(void)
	{
		iuutil::Console::output("FooEnvironment::SetUp\n");
	}
	virtual void	TearDown(void)
	{
		iuutil::Console::output("FooEnvironment::TearDown\n");
	}
};
#include <iostream>

#if defined(_MSC_VER) && IUTEST_HAS_LIB

#pragma comment(lib, IUTEST_LIB_NAME(libiutest_main) )

#else

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
	setlocale(LC_CTYPE, "");
#endif

#if 1
	iutest::AddGlobalTestEnvironment(new FooEnvironment());
#endif

	//iutest::IUTEST_FLAG(shuffle) = false;
	//iutest::IUTEST_FLAG(throw_on_failure) = true;
	IUTEST_INIT(&argc, argv);

#if defined(USE_TAP)
	::iutest::SetUpTAPPrintListener();
#endif

#if defined(USE_PROGRESS)
	::iutest::SetUpProgressPrintListener();
#endif

	//::iuutil::SetUpQuietResultPrinter();

	return IUTEST_RUN_ALL_TESTS();	// run all
}

#endif

#if 1	// Success Tests

/** --------------------------------------------------
 * 簡単なテスト
*//*--------------------------------------------------*/
IUTEST(Test, Version)
{
	unsigned long v = (IUTEST_MAJORVER << 24) | (IUTEST_MINORVER << 16) | (IUTEST_BUILD << 8) | IUTEST_REVISION;
	IUTEST_ASSERT_EQ( IUTEST_VER, v );
}

IUTEST(Test, GetName)
{
	IUTEST_ASSERT_STREQ("GetName", test_info_->name());
	RecordProperty("test_name", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
	RecordProperty("number", 1);
}

IUTEST(Test, Stream)
{
	IUTEST_SUCCEED() << "OK!!";
	IUTEST_SUCCEED() << L"OK!!";
}

#if IUTEST_HAS_ASSERTION_RETURN

/** --------------------------------------------------
 * 戻り値のある関数での使用
*//*--------------------------------------------------*/
int ReturnTest(void)
{
	IUTEST_ASSERT_TRUE(true) << ::iutest::AssertionReturn<int>(-1);
	return 0;
}

IUTEST(ReturnTest, Test)
{
	ReturnTest();
}

#endif


/** --------------------------------------------------
 * パッケージ
*//*--------------------------------------------------*/
IUTEST_PACKAGE(TestPackage)
{
	IUTEST(Test, Version)
	{
		IUTEST_ASSERT_TRUE(true);
	}
}

/** --------------------------------------------------
 * テストフィクスチャの利用
*//*--------------------------------------------------*/
class TestFixed : public ::iutest::Test
{
protected:
	static int x;
public:
	virtual void SetUp(void)
	{
		++x;
	}
	static void SetUpTestCase(void)
	{
		x = 0;
	}
};
int TestFixed::x = -1;

IUTEST_F(TestFixed, Test1)
{
	IUTEST_ASSERT_EQ(1, x);
}

IUTEST_F(TestFixed, Test2)
{
	IUTEST_ASSERT_EQ(2, x);
}

typedef TestFixed TestFixed2;

struct Point
{
	int x, y;
	bool operator == (const Point& rhs) const { return x==rhs.x && y==rhs.y; }
};

IUTEST_F(TestFixed2, Test1)
{
	IUTEST_ASSERT_EQ(1, x);

	{
		Point a = {0, 0};
		Point b = {0, 0};
		IUTEST_EXPECT_EQ(a, b); // operator == があれば可能.
	}
}

IUTEST_F(TestFixed2, Test2)
{
	IUTEST_ASSERT_EQ(2, x);
	IUTEST_EXPECT_EQ(2, x);
	IUTEST_INFORM_EQ(2, x);
}

/** --------------------------------------------------
 * 各種アサーション
*//*--------------------------------------------------*/
IUTEST(AssertionTest, NoFailure)
{
	IUTEST_ASSERT_NO_FATAL_FAILURE( IUTEST_ASSERT_TRUE(true) );
	IUTEST_ASSERT_NO_FAILURE( IUTEST_EXPECT_TRUE(true) );
}

IUTEST(AssertionTest, Base)
{
	int x0=0, y0=0, x1=1;
	float f0=0.0f, f1=1.0f;
	double d0=0.0, d1=1.0;
	// true/false
	{
		IUTEST_EXPECT_TRUE(true);
		IUTEST_EXPECT_TRUE(1);
		IUTEST_EXPECT_TRUE(100==100);

		IUTEST_EXPECT_FALSE(false);
		IUTEST_EXPECT_FALSE(0);
		IUTEST_EXPECT_FALSE(100!=100);
	}
	// EQ
	{
		IUTEST_EXPECT_EQ(x0, y0);
		int* zero=NULL;
		IUTEST_EXPECT_EQ(NULL, zero);

		::std::vector<int> v1, v2;
		IUTEST_EXPECT_EQ(v1, v2);
	}
	// EQ_COLLECTIONS
	{
		int a[] = { 0, 1, 2, 3 };
		int b[] = { 0, 1, 2, 3 };
		IUTEST_ASSERT_EQ_COLLECTIONS(a, a+4, b, b+4);
	}

	// NE
	{
		IUTEST_EXPECT_NE(x0, x1);
		int* one=(int*)1;
		IUTEST_EXPECT_NE(NULL, one);
	}

	// LE, LT
	{
		IUTEST_EXPECT_LE(x0, y0);
		IUTEST_EXPECT_LE(f0, f1);
		IUTEST_EXPECT_LE(0.0, 0x1);
		IUTEST_EXPECT_LT(x0, x1);
		IUTEST_EXPECT_LT(d0, d1);
		IUTEST_EXPECT_LT(0.0, 0x1);
	}

	// GE, GT
	{
		IUTEST_EXPECT_GE(x0, y0);
		IUTEST_EXPECT_GE(f1, f0);
		IUTEST_EXPECT_GE(0x1, 0.0f);
		IUTEST_EXPECT_GT(x1, x0);
		IUTEST_EXPECT_GT(d1, d0);
		IUTEST_EXPECT_GT(0x1, 0.0f);
	}

	// float. double
	{
		IUTEST_EXPECT_FLOAT_EQ(1.0f, f1);
		IUTEST_EXPECT_FLOAT_EQ(0.0f, f0);
		IUTEST_EXPECT_FLOAT_EQ(-1.0f, -2.0f/2.0f);

		IUTEST_EXPECT_DOUBLE_EQ(1.0, d1);
		IUTEST_EXPECT_DOUBLE_EQ(0.0, d0);
		IUTEST_EXPECT_DOUBLE_EQ(-1.0, -2.0/2.0);
	}

	// Near
	{
		IUTEST_EXPECT_NEAR(0, 1, 2);
		IUTEST_EXPECT_NEAR(1.0f, 4.0f, 4);
		IUTEST_EXPECT_NEAR(2.0, 1.0, 2);
	}
}

IUTEST(AssertionTest, Base2)
{
	// NULL
	{
		int* p1 = NULL;
		IUTEST_EXPECT_NULL(p1);

		void* p2 = &p1;
		IUTEST_EXPECT_NOTNULL(p2);
	}
	// SAME
	{
		int v = 0;
		int* p1 = &v;
		IUTEST_EXPECT_SAME(v, *p1);
	}
}

IUTEST(AssertionTest, Cpp11)
{
#if IUTEST_HAS_CHAR16_T
	const char16_t c16[] = u"test";
	IUTEST_EXPECT_STREQ(c16, u"test");
#endif

#if IUTEST_HAS_CHAR32_T
	const char32_t c32[] = U"test";
	IUTEST_EXPECT_STREQ(c32, U"test");
#endif
}

IUTEST(AssertionTest, String)
{
	const char mbs[] = "test";
	const wchar_t wcs[] = L"test";
	IUTEST_EXPECT_STREQ( "test", mbs);
	IUTEST_EXPECT_STREQ(L"test", wcs);

	IUTEST_EXPECT_STRNE( "host", mbs);
	IUTEST_EXPECT_STRNE(L"host", wcs);

	IUTEST_EXPECT_STRLNEQ(4, mbs);
	IUTEST_EXPECT_STRLNEQ(4, wcs);

	{
		::std::string str1 = "test";
		IUTEST_EXPECT_EQ(str1, "test");

		IUTEST_EXPECT_NE(str1, "host");
	}

	{
		::std::string str1 = "tEst";
		::std::string str2 = "teSt";
		::std::string str3 = "hoSt";

		IUTEST_EXPECT_STRCASEEQ("TeSt", mbs);
		IUTEST_EXPECT_STRCASEEQ("TeSt", str1);
		IUTEST_EXPECT_STRCASEEQ(str1, "TeSt");
		IUTEST_EXPECT_STRCASEEQ(str1, str2);

		IUTEST_EXPECT_STRCASENE("HoSt", mbs);
		IUTEST_EXPECT_STRCASENE("HoSt", str1);
		IUTEST_EXPECT_STRCASENE(str1, "HoSt");
		IUTEST_EXPECT_STRCASENE(str1, str3);
	}
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(AssertionTest, HResult)
{
	IUTEST_EXPECT_HRESULT_SUCCEEDED(0);
	IUTEST_EXPECT_HRESULT_FAILED(-1);
}

#endif

/** --------------------------------------------------
 * 述語アサーション
*//*--------------------------------------------------*/
static bool IsOdd(int val)
{
	return (val & 1) != 0;
}
static bool	IsGreater(int a, int b)
{
	return a > b;
}
static bool	PredTest3(int , int , int )
{
	return true;
}
static bool	PredTest4(int , int , int , int )
{
	return true;
}
static bool	PredTest5(int , int , int , int , int )
{
	return true;
}
IUTEST(AssertionTest, Pred)
{
	IUTEST_EXPECT_PRED1(IsOdd, 3);
	IUTEST_EXPECT_PRED2(IsGreater, 3, 1);
	IUTEST_EXPECT_PRED3(PredTest3, 0, 1, 2);
	IUTEST_EXPECT_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED5(PredTest5, 0, 1, 2, 3, 4);
}

/** --------------------------------------------------
 * OR サポート
*//*--------------------------------------------------*/
IUTEST(AssertionTest, OREQ)
{
	int x=1;
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::NE>::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::LE>::Comp, x, 1);
	IUTEST_ASSERT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::LT>::Comp, x, 2);
	IUTEST_EXPECT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::GE>::Comp, x, 1);
	IUTEST_INFORM_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::GT>::Comp, x, 0);
	IUTEST_ASSERT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1);
	IUTEST_INFORM_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, x, 1);
	IUTEST_ASSERT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 2, 0);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 2, 0, 1);
	IUTEST_ASSERT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 1, 2, 3, 0);
	IUTEST_ASSERT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 3, 0, 1, 2);
	IUTEST_INFORM_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, x, 2, 3, 0, 1);
}


/** --------------------------------------------------
 * 値をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_TEST
// Param Test Range
class TestP : public ::iutest::TestWithParam<int>
{
protected:
	static int a;
	static int b;
public:
	static void SetUpTestCase(void)
	{
		a = 0;
		b = 0;
	}
};
int TestP::a = 0;
int TestP::b = 0;

IUTEST_INSTANTIATE_TEST_CASE_P(TestPInstance, TestP, ::iutest::Range<int>(0, 10));

IUTEST_P(TestP, TestA)
{
	IUTEST_ASSERT_EQ(a, GetParam());
	++a;
}

IUTEST_P(TestP, TestB)
{
	IUTEST_ASSERT_EQ(b, GetParam());
	++b;
}

// Param Test Bool
class TestBool : public ::iutest::TestWithParam<bool> {};
IUTEST_INSTANTIATE_TEST_CASE_P(TestBoolInstance, TestBool, ::iutest::Bool());

IUTEST_P(TestBool, TestA)
{
	static bool x=false;
	IUTEST_ASSERT_EQ(x, GetParam());
	x = !x;
}

// Param Test ValueIn
const char ValueInTestText[] = "ValueInTestText";
class TestPValueIn : public ::iutest::TestWithParam<char>
{
protected:
	static int a;
public:
	static void SetUpTestCase(void)
	{
		a = 0;
	}
};
int TestPValueIn::a = 0;
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValueInInstance, TestPValueIn, ::iutest::ValuesIn(ValueInTestText));

IUTEST_P(TestPValueIn, TestA)
{
	IUTEST_ASSERT_EQ(ValueInTestText[a++], GetParam());
}

// Param Test Values
class TestPValues1 : public ::iutest::TestWithParam<float> {};
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValues1Instance, TestPValues1, ::iutest::Values(1.0f));

IUTEST_P(TestPValues1, TestA)
{
	IUTEST_ASSERT_FLOAT_EQ(1.0f, GetParam());
}

class TestPValuesN : public ::iutest::TestWithParam<int>
{
protected:
	static int a;
public:
	static void SetUpTestCase(void)
	{
		a = 1;
	}
};
int TestPValuesN::a = 1;
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValuesNInstance, TestPValuesN, ::iutest::Values(1, 2, 3, 4, 5, 6, 7, 8, 9
																	//, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
																	//, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
																	//, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
																	//, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
																	//, 50
																	));

IUTEST_P(TestPValuesN, TestA)
{
	IUTEST_ASSERT_EQ(a++, GetParam());
}

#if IUTEST_HAS_COMBINE

class TestPCombine : public ::iutest::TestWithParam< ::iutest::tuples::tuple<bool, int, int> >
{
};

IUTEST_P(TestPCombine, TestA)
{
	bool b = ::iutest::tuples::get<0>(GetParam());
	int i1 = ::iutest::tuples::get<1>(GetParam());
	int i2 = ::iutest::tuples::get<2>(GetParam());
	IUTEST_SUCCEED() << b << ", " << i1 << ", " << i2;
}

IUTEST_INSTANTIATE_TEST_CASE_P(TestPCombineInstance, TestPCombine
							   , ::iutest::Combine( ::iutest::Bool(), ::iutest::Values(1, 2), ::iutest::Values(10, 11) ) );
#endif

#if IUTEST_HAS_INITIALIZER_LIST

class InitializerListValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(InitializerListValuesTest, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_INSTANTIATE_TEST_CASE_P(A, InitializerListValuesTest, ::iutest::ValuesIn({1, 9, 8, 6, 3, 9}));

#endif

#if IUTEST_HAS_RANDOMVALUES

class RandomValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(RandomValuesTest, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_INSTANTIATE_TEST_CASE_P(A, RandomValuesTest, ::iutest::RandomValues(5));

#endif

#endif

/** --------------------------------------------------
 * 型付けテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};
typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_CASE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Equal)
{
	TypeParam a = 0;
	IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST(TypedTest, Litle)
{
	TypeParam a = 1;
	IUTEST_ASSERT_LT(0, a);
}

#endif

/** --------------------------------------------------
 * 型をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypedTestP : public ::iutest::Test {};
typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_CASE_P(TypedTestP);

IUTEST_TYPED_TEST_P(TypedTestP, Equal)
{
	TypeParam a = 0;
	IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST_P(TypedTestP, Litle)
{
	TypeParam a = 1;
	IUTEST_ASSERT_LT(0, a);
}

IUTEST_REGISTER_TYPED_TEST_CASE_P(TypedTestP, Equal, Litle);
IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(TypedTestPInstance, TypedTestP, TypedTestTypes);

#endif

/** --------------------------------------------------
 * Diabled テスト
*//*--------------------------------------------------*/
// このテストは無効テスト
IUTEST(TestDisabled, DISABLED_Test1)
{
	IUTEST_ASSERT_TRUE(false);
}

IUTEST(TestDisabled, Test2)
{
	IUTEST_ASSERT_TRUE(true);
}

// テストケースすべてを無効にする
IUTEST(DISABLED_TestCaseDisabled, Test1)
{
	IUTEST_ASSERT_TRUE(false);
}
IUTEST(DISABLED_TestCaseDisabled, Test2)
{
	IUTEST_ASSERT_TRUE(false);
}

/** --------------------------------------------------
 * 例外アサーション
*//*--------------------------------------------------*/
#if IUTEST_HAS_EXCEPTIONS

static void	ExceptionFunction(int i)
{
	switch( i )
	{
	case 0:
		return;
	case 1:
		throw 2;
	case 2:
		throw ::std::bad_exception();
	case 3:
		throw "error";
	case 4:
		throw ::std::string("error");
	default:
		break;
	}
}

IUTEST(AssertionTest, Exception)
{
	IUTEST_EXPECT_THROW(ExceptionFunction(2), ::std::bad_exception);
	IUTEST_EXPECT_ANY_THROW(ExceptionFunction(1));
	IUTEST_EXPECT_NO_THROW(ExceptionFunction(0));

	IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
	IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 0);

	IUTEST_ASSERT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
	IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
}

class exception_test
{
public:
	exception_test(const ::std::vector<int>&)
	{
		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
	}
};

IUTEST(AssertionTest, Exception2)
{
	::std::vector<int> a;
	IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

#endif

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

/** --------------------------------------------------
 * 型の一致テスト
*//*--------------------------------------------------*/
IUTEST(StaticTest, Eq)
{
	IUTEST_ASSERT_TRUE( (::iutest::StaticAssertTypeEq<int, int>()) );
	//iutest::StaticAssertTypeEq<bool, int>();
}

#endif

/** --------------------------------------------------
 * パラメタライズ関数コール
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
	IUTEST_ASSERT_EQ(x, y);
}
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 0, 0);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 1, 1);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 2, 2);

typedef TestFixed ParamMethodTestFixed;

IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 2, 2);

#endif


/** --------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if defined(SHOW_FAILURE)	// Failure Test

IUTEST(TestFailure, EQ)
{
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(TestFailure, NE)
{
	int x=1, y=1;
	IUTEST_ASSERT_NE(x, y);
}

IUTEST(TestFailure, GE)
{
	float a = 0.1f, b = 1.0f;
	IUTEST_ASSERT_GE(a, b);
}

IUTEST(TestFailure, TRUE)
{
	IUTEST_ASSERT_TRUE(0);
	IUTEST_ASSERT_TRUE(false);
}

IUTEST(TestFailure, FALSE)
{
	IUTEST_ASSERT_FALSE(true);
	IUTEST_ASSERT_FALSE(2);
}

IUTEST(TestFailure, Fail)
{
	IUTEST_FAIL() << "add messages.\n";
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(TestFailure, HRESULT)
{
	IUTEST_ASSERT_HRESULT_SUCCEEDED(E_OUTOFMEMORY);
}

#endif

void AssertFunc(void)
{
	IUTEST_ASSERT_TRUE(FALSE);
}

IUTEST(TestFailure, NoFailure)
{
	IUTEST_INFORM_NO_FATAL_FAILURE( AssertFunc() );
	IUTEST_EXPECT_NO_FATAL_FAILURE( AssertFunc() );
	IUTEST_ASSERT_NO_FATAL_FAILURE( AssertFunc() );
}

#if IUTEST_HAS_GENRAND

IUTEST(TestExpectFailure, Random)
{
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
}

#endif

IUTEST(TestExpectFailure, Pred)
{
	int x=4, y=5;
	IUTEST_EXPECT_PRED1(IsOdd, x);
	IUTEST_EXPECT_PRED2(IsGreater, x, y);
}

IUTEST(TestExpectFailure, OREQ)
{
	IUTEST_EXPECT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 1);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 2, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 2, 0, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 2, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 3, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 0, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 2, 0, 1);
}

#if IUTEST_HAS_EXCEPTIONS
IUTEST(TestExpectFailure, Exception)
{
	IUTEST_EXPECT_THROW(ExceptionFunction(0), int);
	IUTEST_EXPECT_ANY_THROW(ExceptionFunction(0));
	IUTEST_EXPECT_NO_THROW(ExceptionFunction(2));
	IUTEST_EXPECT_NO_THROW(throw "error");

	IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 0);
	IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 2);

	IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "Error");
	IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "rror");
}
IUTEST(TestExpectFailure, UnexpectedException1)
{
	throw "fail";
}
IUTEST(TestExpectFailure, UnexpectedException2)
{
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
IUTEST_PRAGMA_GCC_WARN_PUSH()
IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnonnull")

	strcpy(NULL, NULL);

IUTEST_PRAGMA_GCC_WARN_POP()
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
}
#endif

IUTEST(TestExpectFailure, Mix)
{
	IUTEST_EXPECT_EQ(0.1, 1);
	IUTEST_EXPECT_NE(0, 0);
	IUTEST_EXPECT_LE(2, 0);
	IUTEST_EXPECT_LT(0, 0);
	IUTEST_EXPECT_GE(0, 2);
	IUTEST_EXPECT_GT(0, 0);
	IUTEST_EXPECT_TRUE(0);
	IUTEST_EXPECT_FALSE(1);
	IUTEST_EXPECT_FLOAT_EQ(0.0f, 0.1f);
	IUTEST_EXPECT_DOUBLE_EQ(0.0, 0.1);
	IUTEST_EXPECT_NEAR(0, 100, 2);
	IUTEST_EXPECT_FAIL();
	{
		::std::string str1 = "test";
		::std::string str2 = "text";

		IUTEST_EXPECT_STREQ("text", str1);
		IUTEST_EXPECT_STRNE("text", str2);
		IUTEST_EXPECT_STRCASEEQ("Text", str1);
		IUTEST_EXPECT_STRCASENE("Text", str2);
	}
	// EQ_COLLECTIONS
	{
		int  aa[] = { 0, 1, 2, 3, 4 };
		int  ab[] = { 0, 1, 2, 3, 4, 5 };
		char ac[] = { 0, 0, 2, 3, 5 };
		IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(ab, ab+(sizeof(ab)/sizeof(ab[0])), aa, aa+(sizeof(aa)/sizeof(aa[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ac, ac+(sizeof(ac)/sizeof(ac[0])));
	}
}

// サブルーチン
static void Sub1(int n)
{
	IUTEST_EXPECT_EQ(1, n);
}
static void Sub2(int n)
{
	IUTEST_ASSERT_EQ(1, n);
}

IUTEST(TestFailureSubroutine, Test1)
{
	{
		int x=100;
		IUTEST_SCOPED_TRACE(::iutest::Message() << "routine1. x=" << x);

		Sub1(x);
	}
	// ここの失敗には "routine1." のメッセージは表示されません。
	Sub1(3);
}

IUTEST(TestFailureSubroutine, Test2)
{
	{
		IUTEST_SCOPED_TRACE("routine2.");
		//IUTEST_SCOPED_TRACE("routine2.") << "iutest can do." ;

		Sub2(2);
	}
	// ここの失敗には "routine2." のメッセージは表示されません。
	Sub2(3);
}

/** --------------------------------------------------
 * パラメタライズ関数コール
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_METHOD_TEST

IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 0, 0);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 1, 2);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 2, 2);

typedef TestFixed TestFailureParamMethodFixed;

IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 2, 3);

#endif

#endif
