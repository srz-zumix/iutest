//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_syntax_tests.cpp
 * @brief		syntax test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "iutest_pred_tests.hpp"

IUTEST(SyntaxTest, True)
{
	if( bool b = true )
		IUTEST_ASSERT_TRUE(b) << b;
	if( bool b = true )
		IUTEST_EXPECT_TRUE(b) << b;
	if( bool b = true )
		IUTEST_INFORM_TRUE(b) << b;
	if( bool b = true )
		IUTEST_ASSUME_TRUE(b) << b;
}

IUTEST(SyntaxTest, False)
{
	if( bool b = false )
		IUTEST_ASSERT_FALSE(b) << b;
	if( bool b = false )
		IUTEST_EXPECT_FALSE(b) << b;
	if( bool b = false )
		IUTEST_INFORM_FALSE(b) << b;
	if( bool b = false )
		IUTEST_ASSUME_FALSE(b) << b;
}

IUTEST(SyntaxTest, EQ)
{
	if( int x = 1 )
		IUTEST_ASSERT_EQ(1, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_EQ(1, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_EQ(1, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_EQ(1, x) << x;
}

IUTEST(SyntaxTest, EQ_COLLECTIONS)
{
	int  a[] = { 0, 1, 2, 3, 4 };
	int  b[] = { 0, 1, 2, 3, 4 };

	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_ASSERT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_EXPECT_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_INFORM_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_ASSUME_EQ_COLLECTIONS(a, a+(sizeof(a)/sizeof(a[0])), b, b+(sizeof(b)/sizeof(b[0]))) << size;
}

IUTEST(SyntaxTest, EQ_RANGE)
{
	int  a[] = { 0, 1, 2, 3, 4 };
	int  b[] = { 0, 1, 2, 3, 4 };

	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_ASSERT_EQ_RANGE(a, b) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_EXPECT_EQ_RANGE(a, b) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_INFORM_EQ_RANGE(a, b) << size;
	if( int size = (sizeof(a)/sizeof(a[0])) )
		IUTEST_ASSUME_EQ_RANGE(a, b) << size;
}

IUTEST(SyntaxTest, NE)
{
	if( int x = 1 )
		IUTEST_ASSERT_NE(0, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_NE(0, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_NE(0, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_NE(0, x) << x;
}

IUTEST(SyntaxTest, LT)
{
	if( int x = 1 )
		IUTEST_ASSERT_LT(0, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_LT(0, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_LT(0, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_LT(0, x) << x;
}

IUTEST(SyntaxTest, LE)
{
	if( int x = 1 )
		IUTEST_ASSERT_LE(1, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_LE(1, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_LE(1, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_LE(1, x) << x;
}

IUTEST(SyntaxTest, GT)
{
	if( int x = 1 )
		IUTEST_ASSERT_GT(2, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_GT(2, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_GT(2, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_GT(2, x) << x;
}

IUTEST(SyntaxTest, GE)
{
	if( int x = 1 )
		IUTEST_ASSERT_GE(1, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_GE(1, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_GE(1, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_GE(1, x) << x;
}

IUTEST(SyntaxTest, Float)
{
	if( float f = 1.0f )
		IUTEST_ASSERT_FLOAT_EQ(1.0f, f) << f;
	if( float f = 1.0f )
		IUTEST_EXPECT_FLOAT_EQ(1.0f, f) << f;
	if( float f = 1.0f )
		IUTEST_INFORM_FLOAT_EQ(1.0f, f) << f;
	if( float f = 1.0f )
		IUTEST_ASSUME_FLOAT_EQ(1.0f, f) << f;
}

IUTEST(SyntaxTest, Double)
{
	if( double d = 1.0 )
		IUTEST_ASSERT_DOUBLE_EQ(1.0, d) << d;
	if( double d = 1.0 )
		IUTEST_EXPECT_DOUBLE_EQ(1.0, d) << d;
	if( double d = 1.0 )
		IUTEST_INFORM_DOUBLE_EQ(1.0, d) << d;
	if( double d = 1.0 )
		IUTEST_ASSUME_DOUBLE_EQ(1.0, d) << d;
}

IUTEST(SyntaxTest, Near)
{
	if( int x = 1 )
		IUTEST_ASSERT_NEAR(0, x, 2) << x;
	if( int x = 1 )
		IUTEST_EXPECT_NEAR(0, x, 2) << x;
	if( int x = 1 )
		IUTEST_INFORM_NEAR(0, x, 2) << x;
	if( int x = 1 )
		IUTEST_ASSUME_NEAR(0, x, 2) << x;
}

IUTEST(SyntaxTest, Null)
{
	int* p = NULL;
	if( int x = 1 )
		IUTEST_ASSERT_NULL(p) << x;
	if( int x = 1 )
		IUTEST_EXPECT_NULL(p) << x;
	if( int x = 1 )
		IUTEST_INFORM_NULL(p) << x;
	if( int x = 1 )
		IUTEST_ASSUME_NULL(p) << x;
}

IUTEST(SyntaxTest, NotNull)
{
	if( void* p = this )
		IUTEST_ASSERT_NOTNULL(p) << p;
	if( void* p = this )
		IUTEST_EXPECT_NOTNULL(p) << p;
	if( void* p = this )
		IUTEST_INFORM_NOTNULL(p) << p;
	if( void* p = this )
		IUTEST_ASSUME_NOTNULL(p) << p;
}

IUTEST(SyntaxTest, Same)
{
	int v = 0;
	if( int* p = &v )
		IUTEST_ASSERT_SAME(v, *p) << p;
	if( int* p = &v )
		IUTEST_EXPECT_SAME(v, *p) << p;
	if( int* p = &v )
		IUTEST_INFORM_SAME(v, *p) << p;
	if( int* p = &v )
		IUTEST_ASSUME_SAME(v, *p) << p;
}

IUTEST(SyntaxTest, StrEq)
{
	const char test[] = "test";
	if( const char* p = "test" )
		IUTEST_ASSERT_STREQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_EXPECT_STREQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_INFORM_STREQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_ASSUME_STREQ(p, test) << p;
}

IUTEST(SyntaxTest, StrNe)
{
	const char test[] = "Test";
	if( const char* p = "test" )
		IUTEST_ASSERT_STRNE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_EXPECT_STRNE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_INFORM_STRNE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_ASSUME_STRNE(p, test) << p;
}

IUTEST(SyntaxTest, StrCaseEq)
{
	const char test[] = "Test";
	if( const char* p = "test" )
		IUTEST_ASSERT_STRCASEEQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_EXPECT_STRCASEEQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_INFORM_STRCASEEQ(p, test) << p;
	if( const char* p = "test" )
		IUTEST_ASSUME_STRCASEEQ(p, test) << p;
}

IUTEST(SyntaxTest, StrCaseNe)
{
	const char test[] = "host";
	if( const char* p = "test" )
		IUTEST_ASSERT_STRCASENE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_EXPECT_STRCASENE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_INFORM_STRCASENE(p, test) << p;
	if( const char* p = "test" )
		IUTEST_ASSUME_STRCASENE(p, test) << p;
}

IUTEST(SyntaxTest, StrLn)
{
	const char test[] = "test";
	if( int len = 4 )
		IUTEST_ASSERT_STRLNEQ(len, test) << len;
	if( int len = 4 )
		IUTEST_EXPECT_STRLNEQ(len, test) << len;
	if( int len = 4 )
		IUTEST_INFORM_STRLNEQ(len, test) << len;
	if( int len = 4 )
		IUTEST_ASSUME_STRLNEQ(len, test) << len;
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(SyntaxTest, HResultSucceeded)
{
	if( int x=1 )
		IUTEST_ASSERT_HRESULT_SUCCEEDED(0) << x;
	if( int x=1 )
		IUTEST_EXPECT_HRESULT_SUCCEEDED(0) << x;
	if( int x=1 )
		IUTEST_INFORM_HRESULT_SUCCEEDED(0) << x;
	if( int x=1 )
		IUTEST_ASSUME_HRESULT_SUCCEEDED(0) << x;
}

IUTEST(SyntaxTest, HResultFailed)
{
	if( int x=1 )
		IUTEST_ASSERT_HRESULT_FAILED(-1) << x;
	if( int x=1 )
		IUTEST_EXPECT_HRESULT_FAILED(-1) << x;
	if( int x=1 )
		IUTEST_INFORM_HRESULT_FAILED(-1) << x;
	if( int x=1 )
		IUTEST_ASSUME_HRESULT_FAILED(-1) << x;
}

#endif

IUTEST(SyntaxTest, Pred1)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED1(IsOdd, x) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED1(IsOdd, x) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED1(IsOdd, x) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED1(IsOdd, x) << x;
}

IUTEST(SyntaxTest, Pred2)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED2(IsGreater, 3, x) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED2(IsGreater, 3, x) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED2(IsGreater, 3, x) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED2(IsGreater, 3, x) << x;
}

IUTEST(SyntaxTest, Pred3)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED3(PredTest3, 0, x, 2) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED3(PredTest3, 0, x, 2) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED3(PredTest3, 0, x, 2) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED3(PredTest3, 0, x, 2) << x;
}

IUTEST(SyntaxTest, Pred4)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED4(PredTest4, 0, x, 2, 3) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED4(PredTest4, 0, x, 2, 3) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED4(PredTest4, 0, x, 2, 3) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED4(PredTest4, 0, x, 2, 3) << x;
}

IUTEST(SyntaxTest, Pred5)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED5(PredTest5, 0, x, 2, 3, 4) << x;
}

#if IUTEST_HAS_MATCHERS

IUTEST(SyntaxTest, That)
{
	if( int x=1 )
		IUTEST_ASSERT_THAT(x, ::iutest::Eq(1)) << x;
	if( int x=1 )
		IUTEST_EXPECT_THAT(x, ::iutest::Le(1)) << x;
	if( int x=1 )
		IUTEST_INFORM_THAT(x, ::iutest::Ge(1)) << x;
	if( int x=1 )
		IUTEST_ASSUME_THAT(x, ::iutest::Ne(0)) << x;
}

struct X { int a, b; X(int _a, int _b) : a(_a), b(_b) {} int GetA() const { return a; } };
int X2(int value) { return value*2; }

IUTEST(SyntaxTest, Matcher)
{
	::std::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	int a[3] = { 0, 1, 2 };
	int b[4] = { 0, 1, 2, 3 };
	X x(0, 1);
	IUTEST_EXPECT_THAT(a, ::iutest::Contains(0));
	IUTEST_EXPECT_THAT(a, ::iutest::Contains(::iutest::Lt(10)));
	IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::Le(10)));
	IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::_));
	IUTEST_EXPECT_THAT(a, ::iutest::Each(::iutest::A<int>()));
	IUTEST_EXPECT_THAT(x, ::iutest::Field(&X::a, 0));
	IUTEST_EXPECT_THAT(&x, ::iutest::Field(&X::a, 0));
	IUTEST_EXPECT_THAT(x, ::iutest::Property(&X::GetA, 0));
	IUTEST_EXPECT_THAT(&x, ::iutest::Property(&X::GetA, 0));
	IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(a));
	IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArray(a));
	IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(v));
	IUTEST_EXPECT_THAT(v, ::iutest::ElementsAreArray(v));
	IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray(b, 3));
#if IUTEST_HAS_INITIALIZER_LIST
	IUTEST_EXPECT_THAT(a, ::iutest::ElementsAreArray({0, 1, 2}));
#endif
	IUTEST_EXPECT_THAT(1, ::iutest::ResultOf(X2, 2));
	IUTEST_EXPECT_THAT(1, ::iutest::ResultOf(X2, ::iutest::Gt(1)));
}

IUTEST(SyntaxTest, MatcherPredicate)
{
	IUTEST_EXPECT_TRUE(::iutest::Value(2, 2));
	IUTEST_EXPECT_TRUE(::iutest::Value(2, ::iutest::Eq(2)));
}

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

IUTEST(SyntaxTest, AllOf)
{
	IUTEST_EXPECT_THAT("9347812650", ::iutest::AllOf(
		  ::iutest::HasSubstr("0")
		, ::iutest::HasSubstr("1")
		, ::iutest::HasSubstr("2")
		, ::iutest::HasSubstr("3")
		, ::iutest::HasSubstr("4")
		, ::iutest::HasSubstr("5")
		, ::iutest::HasSubstr("6")
		, ::iutest::HasSubstr("7")
		, ::iutest::HasSubstr("8")
	));
}

IUTEST(SyntaxTest, AnyOf)
{
	IUTEST_EXPECT_THAT("hoge7", ::iutest::AnyOf(
		  ::iutest::HasSubstr("0")
		, ::iutest::HasSubstr("1")
		, ::iutest::HasSubstr("2")
		, ::iutest::HasSubstr("3")
		, ::iutest::HasSubstr("4")
		, ::iutest::HasSubstr("5")
		, ::iutest::HasSubstr("6")
		, ::iutest::HasSubstr("7")
		, ::iutest::HasSubstr("8")
	));
}

#endif

#endif


#if !defined(IUTEST_USE_GTEST)

#if !defined(IUTEST_NO_VARIADIC_MACROS)

#if IUTEST_HAS_VARIADIC_TEMPLATES

IUTEST(SyntaxTest, VariadicPred)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED(PredTest6, 0, x, 2, 3, 4, 5) << x;
}

#endif

IUTEST(SyntaxTest, VariadicPredFormat)
{
	if( int x=1 )
		IUTEST_ASSERT_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_EXPECT_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_INFORM_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
	if( int x=1 )
		IUTEST_ASSUME_PRED_FORMAT(Pred6Formater, 0, x, 2, 3, 4, 5) << x;
}

#endif

#endif

#if IUTEST_HAS_EXCEPTIONS

namespace syntax_test
{

static void	ExceptionFunction(int i)
{
	switch( i )
	{
	case 0:
		return;
	case 1:
		throw 2;
		break;
	case 2:
		throw ::std::bad_exception();
		break;
	case 3:
		throw "error";
	case 4:
		throw ::std::string("error");
	case 5:
		throw 0.1f;
	default:
		break;
	}
}

IUTEST(SyntaxTest, ExceptionThrow)
{
	if( int x = 2 )
		IUTEST_ASSERT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
	if( int x = 2 )
		IUTEST_EXPECT_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
	if( int x = 2 )
		IUTEST_INFORM_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
	if( int x = 2 )
		IUTEST_ASSUME_THROW(ExceptionFunction(x), ::std::bad_exception) << x;
}

IUTEST(SyntaxTest, ExceptionAnyThrow)
{
	if( int x = 1 )
		IUTEST_ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
	if( int x = 1 )
		IUTEST_ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
	if( int x = 1 )
		IUTEST_ASSERT_ANY_THROW(throw ::std::bad_exception()) << x;
	if( int x = 1 )
		IUTEST_ASSUME_ANY_THROW(throw ::std::bad_exception()) << x;
}

IUTEST(SyntaxTest, ExceptionNoThrow)
{
	if( int x = 1 )
		IUTEST_ASSERT_NO_THROW((void)x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_NO_THROW((void)x) << x;
	if( int x = 1 )
		IUTEST_INFORM_NO_THROW((void)x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_NO_THROW((void)x) << x;
}

IUTEST(SyntaxTest, ExceptionValueEQ)
{
	if( int x = 1 )
		IUTEST_ASSERT_THROW_VALUE_EQ(throw 1, int, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_THROW_VALUE_EQ(throw 1, int, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_THROW_VALUE_EQ(throw 1, int, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_THROW_VALUE_EQ(throw 1, int, x) << x;
}

IUTEST(SyntaxTest, ExceptionValueNE)
{
	if( int x = 1 )
		IUTEST_ASSERT_THROW_VALUE_NE(throw 2, int, x) << x;
	if( int x = 1 )
		IUTEST_EXPECT_THROW_VALUE_NE(throw 2, int, x) << x;
	if( int x = 1 )
		IUTEST_INFORM_THROW_VALUE_NE(throw 2, int, x) << x;
	if( int x = 1 )
		IUTEST_ASSUME_THROW_VALUE_NE(throw 2, int, x) << x;
}

IUTEST(SyntaxTest, ExceptionValueSTREQ)
{
	if( int x = 1 )
		IUTEST_ASSERT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
	if( int x = 1 )
		IUTEST_EXPECT_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
	if( int x = 1 )
		IUTEST_INFORM_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
	if( int x = 1 )
		IUTEST_ASSUME_THROW_VALUE_STREQ(throw "error", const char *, "error") << x;
}

IUTEST(SyntaxTest, ExceptionValueSTRCASEEQ)
{
	if( int x = 1 )
		IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
	if( int x = 1 )
		IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
	if( int x = 1 )
		IUTEST_INFORM_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
	if( int x = 1 )
		IUTEST_ASSUME_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error") << x;
}

IUTEST(SyntaxTest, ExceptionValueFormat)
{
	if( float x = 0.1f )
		IUTEST_ASSERT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
			, ExceptionFunction(5), float, x) << x;
	if( float x = 0.1f )
		IUTEST_EXPECT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
			, ExceptionFunction(5), float, x) << x;
	if( float x = 0.1f )
		IUTEST_INFORM_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
			, ExceptionFunction(5), float, x) << x;
	if( float x = 0.1f )
		IUTEST_ASSUME_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>
			, ExceptionFunction(5), float, x) << x;
}

}

class exception_test
{
public:
	exception_test(const ::std::vector<int>&)
	{
		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
	}
};

IUTEST(SyntaxTest, ExceptionVectorConstructor)
{
	::std::vector<int> a;
	IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

