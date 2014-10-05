//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_matcher.hpp
 * @brief		iris unit test matcher 定義 ファイル
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_
#define INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_

#if IUTEST_HAS_MATCHERS

/**
 * @defgroup	MATCHERS 	MATCHERS
 * @brief		Matchers
*/

//======================================================================
// define
/**
 * @private
 * @{
*/
#define IUTEST_TEST_THAT(actual, matcher, on_failure)					\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_										\
	if( ::iutest::AssertionResult iutest_ar = matcher(actual) ) {		\
	} else																\
		on_failure(::iutest::detail::MatcherAssertionFailureMessage(	\
			::iutest::PrintToString(actual).c_str(), #matcher, iutest_ar))

/**
 * @}
*/

namespace iutest {
namespace detail
{

//======================================================================
// function
/**
 * @brief	Matcher Assertion Failure Message
*/
inline ::std::string MatcherAssertionFailureMessage(const char* actual, const char* matcher_str, const AssertionResult& ar)
{
	iu_global_format_stringstream strm;
	strm << "error: Expected: " << matcher_str
		<< "\n  Actual: " << actual
		<< "\nWhich is: " << ar.message();
	return strm.str();
}
	
//======================================================================
// class

/**
 * @brief	matcher interface
*/
class IMatcher
{
public:
	template<typename T>
	struct is_matcher : public iutest_type_traits::is_base_of<IMatcher, T> {};
public:
	virtual ~IMatcher(void) {}
	virtual ::std::string WitchIs(void) const = 0;
};

inline iu_ostream& operator << (iu_ostream& os, const IMatcher& msg)
{
	return os << msg.WitchIs();
}

/**
 * @private
 * @{
*/

#define DECL_COMPARE_MATCHER(name, op)	\
	template<typename T>class IUTEST_PP_CAT(name, Matcher): public IMatcher{\
	public:	IUTEST_PP_CAT(name, Matcher)(const T& v) : m_expected(v) {}		\
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE {					\
		iu_global_format_stringstream strm;									\
		strm << #name ": " << m_expected; return strm.str();				\
	}																		\
	template<typename U>AssertionResult operator ()(const U& actual) const {\
		if( actual op m_expected ) return AssertionSuccess();				\
		return AssertionFailure() << WitchIs();								\
	}																		\
	private: IUTEST_PP_DISALLOW_ASSIGN(IUTEST_PP_CAT(name, Matcher));		\
	const T& m_expected;													\
	}


DECL_COMPARE_MATCHER(Ne, !=);
DECL_COMPARE_MATCHER(Le, <=);
DECL_COMPARE_MATCHER(Lt, < );
DECL_COMPARE_MATCHER(Ge, >=);
DECL_COMPARE_MATCHER(Gt, > );

#undef DECL_COMPARE_MATCHER

#define DECL_STR_COMPARE_MATCHER(name)	\
	template<typename T>class IUTEST_PP_CAT(name, Matcher): public IMatcher {	\
	public: IUTEST_PP_CAT(name, Matcher)(const T& value) : m_expected(value) {}	\
	template<typename U>AssertionResult operator ()(const U& actual) const {	\
		if( internal::IUTEST_PP_CAT(name, Helper)::Compare(						\
			actual, m_expected) ) {	return AssertionSuccess(); }				\
		return AssertionFailure() << WitchIs();									\
	}																			\
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE {						\
		iu_global_format_stringstream strm; strm << #name ": " << m_expected;	\
		return strm.str();														\
	}																			\
	private: IUTEST_PP_DISALLOW_ASSIGN(IUTEST_PP_CAT(name, Matcher));			\
	const T& m_expected;														\
	}

DECL_STR_COMPARE_MATCHER(StrEq);
DECL_STR_COMPARE_MATCHER(StrNe);
DECL_STR_COMPARE_MATCHER(StrCaseEq);
DECL_STR_COMPARE_MATCHER(StrCaseNe);

#undef DECL_COMPARE_MATCHER

/**
 * @}
*/

/**
 * @brief	IsNull matcher
*/
class IsNullMatcher : public IMatcher
{
public:
	IsNullMatcher() {}
public:
	template<typename U>
	AssertionResult operator ()(const U* actual) const
	{
		if( actual == NULL ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return "Is Null";
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(IsNullMatcher);
};

/**
 * @brief	NotNull matcher
*/
class NotNullMatcher : public IMatcher
{
public:
	NotNullMatcher() {}
public:
	template<typename U>
	AssertionResult operator ()(const U* actual) const
	{
		if( actual != NULL ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return "Not Null";
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(NotNullMatcher);
};

/**
 * @brief	Floating point Eq matcher
*/
template<typename T>
class FloatingPointEqMatcher : public IMatcher
{
public:
	FloatingPointEqMatcher(const T& value) : m_expected(value) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		floating_point<T> f2(actual);
		if( m_expected.AlmostEquals(f2) )
		{
			return AssertionSuccess();
		}
		return AssertionFailure() << WitchIs();
	}

	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Eq: " << PrintToString(m_expected);
		return strm.str();
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(FloatingPointEqMatcher);

	floating_point<T> m_expected;
};

/**
 * @brief	Floating point Eq matcher (NanSensitive)
*/
template<typename T>
class NanSensitiveFloatingPointEqMatcher : public IMatcher
{
public:
	NanSensitiveFloatingPointEqMatcher(const T& value) : m_expected(value) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		floating_point<T> f2(actual);
		if( m_expected.NanSensitiveAlmostEquals(f2) )
		{
			return AssertionSuccess();
		}
		return AssertionFailure() << WitchIs();
	}

	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "NanSensitive Eq: " << PrintToString(m_expected);
		return strm.str();
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(NanSensitiveFloatingPointEqMatcher);

	floating_point<T> m_expected;
};

/**
 * @brief	StartsWith matcher
*/
template<typename T>
class StartsWithMatcher : public IMatcher
{
public:
	StartsWithMatcher(T str) : m_str(str) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( StartsWith(actual, m_str) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "StartsWith: " << m_str;
		return strm.str();
	}
private:
	static bool StartsWith(const char* actual, const char* start)
	{
		return strstr(actual, start) == actual;
	}
	static bool StartsWith(const ::std::string& actual, const char* start)
	{
		const char* p = actual.c_str();
		return StartsWith(p, start);
	}
	static bool StartsWith(const char* actual, const ::std::string& start)
	{
		const char* p = start.c_str();
		return StartsWith(actual, p);
	}
	static bool StartsWith(const ::std::string& actual, const ::std::string& start)
	{
		const char* p = start.c_str();
		return StartsWith(actual, p);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(StartsWithMatcher);

	T m_str;
};

/**
 * @brief	Has substr matcher
*/
template<typename T>
class HasSubstrMatcher : public IMatcher
{
public:
	HasSubstrMatcher(T expected) : m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( HasSubstr(actual, m_expected) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "HasSubstr: " << m_expected;
		return strm.str();
	}
private:
	static bool HasSubstr(const char* actual, const char* expected)
	{
		return strstr(actual, expected) != NULL;
	}
	static bool HasSubstr(const ::std::string& actual, const char* expected)
	{
		const char* p = actual.c_str();
		return HasSubstr(p, expected);
	}
	static bool HasSubstr(const char* actual, const ::std::string& expected)
	{
		const char* p = expected.c_str();
		return HasSubstr(actual, p);
	}
	static bool HasSubstr(const ::std::string& actual, const ::std::string& expected)
	{
		const char* p = expected.c_str();
		return HasSubstr(actual, p);
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(HasSubstrMatcher);

	T m_expected;
};

/**
 * @brief	EndsWith matcher
*/
template<typename T>
class EndsWithMatcher : public IMatcher
{
public:
	EndsWithMatcher(T str) : m_str(str) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( EndsWith(actual, m_str) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "EndsWith: " << m_str;
		return strm.str();
	}
private:
	static bool EndsWith(const char* actual, const char* end)
	{
		const size_t len = strlen(end);
		const size_t actual_len = strlen(actual);
		if( len > actual_len ) return false;
		const char* p = actual + actual_len - 1;
		const char* q = end + len - 1;
		for( size_t i=0; i < len; ++i, --p, --q )
		{
			if( *p != *q ) return false;
		}	
		return true;
	}
	static bool EndsWith(const ::std::string& actual, const char* end)
	{
		const char* p = actual.c_str();
		return EndsWith(p, end);
	}
	static bool EndsWith(const char* actual, const ::std::string& end)
	{
		const char* p = end.c_str();
		return EndsWith(actual, p);
	}
	static bool EndsWith(const ::std::string& actual, const ::std::string& end)
	{
		const char* p = end.c_str();
		return EndsWith(actual, p);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(EndsWithMatcher);

	T m_str;
};

/**
 * @brief	Equals matcher
*/
template<typename T>
class EqMatcher : public IMatcher
{
public:
	EqMatcher(const T& expected) : m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Equals(actual, m_expected) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Eq: " << m_expected;
		return strm.str();
	}
private:
	template<typename A, typename B>
	static bool Equals(const A& actual, const B& expected)
	{
		return actual == expected;
	}
	static bool Equals(const char* actual, const char* expected)
	{
		return strcmp(actual, expected) == 0;
	}
	static bool Equals(const ::std::string& actual, const char* expected)
	{
		const char* p = actual.c_str();
		return Equals(p, expected);
	}
	static bool Equals(const ::std::string& actual, const ::std::string& expected)
	{
		const char* p = expected.c_str();
		return Equals(actual, p);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(EqMatcher);

	const T& m_expected;
};

/**
 * @brief	Cast to matcher
*/
template<typename T>
const T& CastToMatcher(const T& matcher
	, typename detail::enable_if_t< IMatcher::is_matcher<T> >::type*& = detail::enabler::value)
{
	return matcher;
}
/** @overload */
template<typename T>
EqMatcher<T> CastToMatcher(const T& value
	, typename detail::disable_if_t< IMatcher::is_matcher<T> >::type*& = detail::enabler::value)
{
	return EqMatcher<T>(value);
}


/**
 * @brief	Contains matcher
*/
template<typename T>
class ContainsMatcher : public IMatcher
{
public:
	ContainsMatcher(const T& expected) : m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Contains(actual, m_expected) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Contains: " << m_expected;
		return strm.str();
	}
private:
	template<typename TT, typename Container>
	static bool Contains(const Container& actual, const TT& expected)
	{
		return ContainsContainer(actual.begin(), actual.end(), expected);
	}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
	template<typename TT, typename U, size_t SIZE>
	static bool Contains(const U(&actual)[SIZE], const TT& expected)
	{
		return ContainsContainer(actual, actual + SIZE, expected);
	}
#endif

	template<typename TT, typename Ite>
	static bool ContainsContainer(Ite begin, Ite end, const TT& expected
		, typename detail::enable_if_t< is_matcher<TT> >::type*& = detail::enabler::value)
	{
		for( Ite it = begin; it != end; ++it )
		{
			if( expected(*it) )
			{
				return true;
			}
		}
		return false;
	}

	template<typename TT, typename Ite>
	static bool ContainsContainer(Ite begin, Ite end, const TT& expected
		, typename detail::disable_if_t< is_matcher<TT> >::type*& = detail::enabler::value)
	{
		return ::std::find(begin, end, expected) != end;
	}

	static bool Contains(const char* actual, const char* expected)
	{
		return strstr(actual, expected) != NULL;
	}
	static bool Contains(const ::std::string& actual, const char* expected)
	{
		const char* p = actual.c_str();
		return Contains(p, expected);
	}
	static bool Contains(const char* actual, const ::std::string& expected)
	{
		const char* p = expected.c_str();
		return Contains(actual, p);
	}
	static bool Contains(const ::std::string& actual, const ::std::string& expected)
	{
		const char* p = expected.c_str();
		return Contains(actual, p);
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(ContainsMatcher);

	const T& m_expected;
};

/**
 * @brief	Each matcher
*/
template<typename T>
class EachMatcher : public IMatcher
{
public:
	EachMatcher(const T& expected) : m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Each(actual, m_expected) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Each: " << m_expected;
		return strm.str();
	}
private:
	template<typename TT, typename Container>
	static bool Each(const Container& actual, const TT& expected)
	{
		return EachContainer(actual.begin(), actual.end(), expected);
	}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
	template<typename TT, typename U, size_t SIZE>
	static bool Each(const U(&actual)[SIZE], const TT& expected)
	{
		return EachContainer(actual, actual + SIZE, expected);
	}
#endif

	template<typename TT, typename Ite>
	static bool EachContainer(Ite begin, Ite end, const TT& expected)
	{
		for( Ite it = begin; it != end; ++it )
		{
			if( !CastToMatcher(expected)(*it) )
			{
				return false;
			}
		}
		return true;
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(EachMatcher);

	const T& m_expected;
};


/**
 * @brief	ElementsAreArray matcher
*/
template<typename T>
class ElementsAreArrayMatcher : public IMatcher
{
public:
	ElementsAreArrayMatcher(const T& expected, int count=-1) : m_expected(expected), m_count(count){}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Check(actual, m_expected, m_count) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "ElementsAreArray: " << PrintToString(m_expected);
		return strm.str();
	}
private:
	template<typename TT, typename Container>
	static bool Check(const Container& actual, const TT& expected, int count)
	{
		return Check(actual.begin(), actual.end(), expected, count);
	}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
	template<typename TT, typename U, size_t SIZE>
	static bool Check(const U(&actual)[SIZE], const TT& expected, int count)
	{
		return Check(actual, actual + SIZE, expected, count);
	}
#endif

	template<typename Container, typename Ite>
	static bool Check(Ite begin, Ite end, const Container& expected, int count)
	{
		return Check(begin, end, expected.begin(), expected.end(), count);
	}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
	template<typename U, size_t SIZE, typename Ite>
	static bool Check(Ite begin, Ite end, const  U(&expected)[SIZE], int count)
	{
		return Check(begin, end, expected, expected + SIZE, count);
	}
#endif

	template<typename Ite1, typename Ite2>
	static bool Check(Ite1 actual_begin, Ite1 actual_end, Ite2 expected_begin, Ite2 expected_end, int count)
	{
		Ite1 a=actual_begin;
		Ite2 e=expected_begin;
		const int n = count >= 0 ? count : ::std::distance(expected_begin, expected_end);
		for( int i=0; i < n && e != expected_end; ++e, ++a, ++i )
		{
			if( a == actual_end ) return false;
			if( *a != *e ) return false;
		}
		return true;
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(ElementsAreArrayMatcher);

	const T& m_expected;
	int m_count;
};

#if IUTEST_HAS_MATCHER_ELEMENTSARE

/**
 * @brief	ElementsAre matcher base class
*/
class ElementsAreMatcherBase : public IMatcher
{
protected:
	template<typename T, typename U>
	static AssertionResult Check(const T& matchers, const U& actual)
	{
		return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
	}
	template<int N, typename T>
	static ::std::string WitchIs(const T& matchers)
	{
		::std::string str = "ElementsAre: {";
		str += WitchIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
		str += "}";
		return str;
	}
private:
	template<typename T, typename U>
	static AssertionResult CallMatcher(const T& actual, const U& expected)
	{
		return CastToMatcher(expected)(actual);
	}

	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = CallMatcher(actual[N], tuples::get<N>(matchers));
		if( ar )
		{
			return ar;
		}
		return AssertionFailure() << WitchIsElem<N>(matchers);
	}
	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = CallMatcher(actual[N], tuples::get<N>(matchers));
		if( ar )
		{
			return Check_<T, U, N + 1, LAST>(matchers, actual);
		}
		return AssertionFailure() << WitchIsElem<N>(matchers);
	}

	template<int N, typename T>
	static ::std::string WitchIsElem(const T& matchers)
	{
		iu_global_format_stringstream strm;
		strm << "ElementsAre(" << N << "): " << tuples::get<N>(matchers);
		return strm.str();
	}

	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return StreamableToString(tuples::get<N>(matchers));
	}
	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return StreamableToString(tuples::get<N>(matchers)) + ", " + WitchIs_<T, N + 1, LAST>(matchers);
	}
	IUTEST_PP_DISALLOW_ASSIGN(ElementsAreMatcherBase);
};

#if IUTEST_HAS_VARIADIC_TEMPLATES

/**
* @brief	ElementsAre matcher
*/
template<typename ...T>
class ElementsAreMatcher : public ElementsAreMatcherBase
{
public:
	ElementsAreMatcher(T... t) : m_matchers(t...) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return ElementsAreMatcherBase::WitchIs<0>(m_matchers);
	}

private:
	tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class ElementsAreMatcher : public ElementsAreMatcherBase
{
public:
	ElementsAreMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return ElementsAreMatcherBase::WitchIs<0>(m_matchers);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(ElementsAreMatcher);

	tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ELEMENTSARE_MATCHER(n)												\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >									\
	class IUTEST_PP_CAT(ElementsAreMatcher, n) : public ElementsAreMatcherBase {		\
	public: IUTEST_PP_CAT(ElementsAreMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m))	\
		: m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}									\
	template<typename U>AssertionResult operator ()(const U& actual) const {			\
		return Check(m_matchers, actual); }												\
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE {								\
		return ElementsAreMatcherBase::WitchIs<0>(m_matchers); }						\
	private: IUTEST_PP_DISALLOW_ASSIGN(IUTEST_PP_CAT(ElementsAreMatcher, n));			\
	tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;							\
	}

IIUT_DECL_ELEMENTSARE_MATCHER(1);
IIUT_DECL_ELEMENTSARE_MATCHER(2);
IIUT_DECL_ELEMENTSARE_MATCHER(3);
IIUT_DECL_ELEMENTSARE_MATCHER(4);
IIUT_DECL_ELEMENTSARE_MATCHER(5);
IIUT_DECL_ELEMENTSARE_MATCHER(6);
IIUT_DECL_ELEMENTSARE_MATCHER(7);
IIUT_DECL_ELEMENTSARE_MATCHER(8);
IIUT_DECL_ELEMENTSARE_MATCHER(9);
IIUT_DECL_ELEMENTSARE_MATCHER(10);

#undef IIUT_DECL_ELEMENTSARE_MATCHER

#endif

#endif

/**
 * @brief	Field matcher
*/
template<typename F, typename T>
class FieldMatcher : public IMatcher
{
public:
	FieldMatcher(const F& field, const T& expected) : m_field(field), m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Check(actual) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Field: " << m_expected;
		//strm << "Field: (" << detail::GetTypeName<F>() << ") " << m_expected;
		return strm.str();
	}
private:
	template<typename U>
	bool Check(const U& actual
		, typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value) const
	{
		return static_cast<bool>(CastToMatcher(m_expected)(actual.*m_field));
	}
	template<typename U>
	bool Check(const U& actual
		, typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value) const
	{
		return static_cast<bool>(CastToMatcher(m_expected)(actual->*m_field));
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(FieldMatcher);

	const F& m_field;
	const T& m_expected;
};

/**
 * @brief	Property matcher
*/
template<typename F, typename T>
class PropertyMatcher : public IMatcher
{
public:
	PropertyMatcher(const F& prop, const T& expected) : m_property(prop), m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( Check(actual) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Property: " << m_expected;
		//strm << "Property: (" << detail::GetTypeName<F>() << ") " << m_expected;
		return strm.str();
	}
private:
	template<typename U>
	bool Check(const U& actual
		, typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value) const
	{
		return static_cast<bool>(CastToMatcher(m_expected)((actual.*m_property)()));
	}
	template<typename U>
	bool Check(const U& actual
		, typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value) const
	{
		return static_cast<bool>(CastToMatcher(m_expected)((actual->*m_property)()));
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(PropertyMatcher);

	const F& m_property;
	const T& m_expected;
};

/**
 * @brief	Key matcher
*/
template<typename T>
class KeyMatcher : public IMatcher
{
public:
	KeyMatcher(const T& expected) : m_expected(expected) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( CastToMatcher(m_expected)(actual.first) ) return AssertionSuccess();
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Key: " << m_expected;
		return strm.str();
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(KeyMatcher);

	const T& m_expected;
};

/**
 * @brief	Pair matcher
*/
template<typename T1, typename T2>
class PairMatcher : public IMatcher
{
public:
	PairMatcher(const T1& m1, const T2& m2) : m_m1(m1), m_m2(m2) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		if( !CheckElem(actual.first, m_m1) )
		{
			return AssertionFailure() << WitchIs();
		}
		if( !CheckElem(actual.second, m_m2) )
		{
			return AssertionFailure() << WitchIs();
		}
		return AssertionSuccess();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "Pair: (" << m_m1 << ", " << m_m2 << ")";
		return strm.str();
	}
private:
	template<typename T, typename U>
	static bool CheckElem(const T& actual, const U& matcher)
	{
		return static_cast<bool>(CastToMatcher(matcher)(actual));
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(PairMatcher);

	const T1& m_m1;
	const T2& m_m2;
};

/**
 * @brief	Any matcher
*/
template<typename T>
class AnyMatcher : public IMatcher
{
public:
	AnyMatcher(void) {}
public:
	AssertionResult operator ()(const T&) const
	{
		return AssertionSuccess();
	}
	template<typename U>
	AssertionResult operator ()(const U&) const
	{
		return AssertionFailure() << WitchIs();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		iu_global_format_stringstream strm;
		strm << "A: " << detail::GetTypeName<T>();
		return strm.str();
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(AnyMatcher);
};

/**
 * @brief	Anything matcher
*/
class AnythingMatcher : public IMatcher
{
public:
	AnythingMatcher(void) {}
public:
	template<typename U>
	AssertionResult operator ()(const U&) const
	{
		return AssertionSuccess();
	}

public:
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return "_";
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(AnythingMatcher);
};

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

/**
 * @brief	AllOf matcher base class
*/
class AllOfMatcherBase : public IMatcher
{
protected:
	template<typename T, typename U>
	static AssertionResult Check(const T& matchers, const U& actual)
	{
		return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
	}
	template<int N, typename T>
	static ::std::string WitchIs(const T& matchers)
	{
		return WitchIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
	}
private:
	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = tuples::get<N>(matchers)(actual);
		if( ar )
		{
			return ar;
		}
		return AssertionFailure() << WitchIs_<T, 0, N>(matchers);
	}
	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = tuples::get<N>(matchers)(actual);
		if( ar )
		{
			return Check_<T, U, N + 1, LAST>(matchers, actual);
		}
		return AssertionFailure() << WitchIs_<T, 0, N>(matchers);
	}

	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return tuples::get<N>(matchers).WitchIs();
	}
	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return tuples::get<N>(matchers).WitchIs() + " and " + WitchIs_<T, N + 1, LAST>(matchers);
	}
	IUTEST_PP_DISALLOW_ASSIGN(AllOfMatcherBase);
};

#if IUTEST_HAS_VARIADIC_TEMPLATES

/**
 * @brief	AllOf matcher
*/
template<typename ...T>
class AllOfMatcher : public AllOfMatcherBase
{
public:
	AllOfMatcher(T... t) : m_matchers(t...) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return AllOfMatcherBase::WitchIs<0>(m_matchers);
	}

private:
	tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class AllOfMatcher : public AllOfMatcherBase
{
public:
	AllOfMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return AllOfMatcherBase::WitchIs<0>(m_matchers);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(AllOfMatcher);

	tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ALLOF_MATCHER(n)													\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >								\
	class IUTEST_PP_CAT(AllOfMatcher, n) : public AllOfMatcherBase {				\
	public: IUTEST_PP_CAT(AllOfMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m))	\
		: m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}								\
	template<typename U>AssertionResult operator ()(const U& actual) const {		\
		return Check(m_matchers, actual); }											\
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE {							\
		return AllOfMatcherBase::WitchIs<0>(m_matchers); }							\
	private: IUTEST_PP_DISALLOW_ASSIGN(IUTEST_PP_CAT(AllOfMatcher, n));				\
	tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;						\
	}

IIUT_DECL_ALLOF_MATCHER(2);
IIUT_DECL_ALLOF_MATCHER(3);
IIUT_DECL_ALLOF_MATCHER(4);
IIUT_DECL_ALLOF_MATCHER(5);
IIUT_DECL_ALLOF_MATCHER(6);
IIUT_DECL_ALLOF_MATCHER(7);
IIUT_DECL_ALLOF_MATCHER(8);
IIUT_DECL_ALLOF_MATCHER(9);
IIUT_DECL_ALLOF_MATCHER(10);

#undef IIUT_DECL_ALLOF_MATCHER

#endif

/**
 * @brief	AnyOf matcher base class
*/
class AnyOfMatcherBase : public IMatcher
{
protected:
	template<typename T, typename U>
	static AssertionResult Check(const T& matchers, const U& actual)
	{
		return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
	}
	template<int N, typename T>
	static ::std::string WitchIs(const T& matchers)
	{
		return WitchIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
	}
private:
	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = tuples::get<N>(matchers)(actual);
		if( ar )
		{
			return ar;
		}
		return AssertionFailure() << WitchIs_<T, 0, N>(matchers);
	}
	template<typename T, typename U, int N, int LAST>
	static AssertionResult Check_(const T& matchers, const U& actual, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		AssertionResult ar = tuples::get<N>(matchers)(actual);
		if( ar )
		{
			return ar;
		}
		return Check_<T, U, N + 1, LAST>(matchers, actual);
	}

	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return tuples::get<N>(matchers).WitchIs();
	}
	template<typename T, int N, int LAST>
	static ::std::string WitchIs_(const T& matchers, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
	{
		return tuples::get<N>(matchers).WitchIs() + " or " + WitchIs_<T, N + 1, LAST>(matchers);
	}

	IUTEST_PP_DISALLOW_ASSIGN(AnyOfMatcherBase);
};

#if IUTEST_HAS_VARIADIC_TEMPLATES

/**
 * @brief	AnyOf matcher
*/
template<typename ...T>
class AnyOfMatcher : public AnyOfMatcherBase
{
public:
	AnyOfMatcher(T... t) : m_matchers(t...) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return AnyOfMatcherBase::WitchIs<0>(m_matchers);
	}

private:
	tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class AnyOfMatcher : public AnyOfMatcherBase
{
public:
	AnyOfMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
	template<typename U>
	AssertionResult operator ()(const U& actual) const
	{
		return Check(m_matchers, actual);
	}
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE
	{
		return AnyOfMatcherBase::WitchIs<0>(m_matchers);
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(AnyOfMatcher);

	tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ANYOF_MATCHER(n)													\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >								\
	class IUTEST_PP_CAT(AnyOfMatcher, n) : public AnyOfMatcherBase {				\
	public: IUTEST_PP_CAT(AnyOfMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m))	\
		: m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}								\
	template<typename U>AssertionResult operator ()(const U& actual) const {		\
		return Check(m_matchers, actual); }											\
	::std::string WitchIs(void) const IUTEST_CXX_OVERRIDE {							\
		return AnyOfMatcherBase::WitchIs<0>(m_matchers); }							\
	private: IUTEST_PP_DISALLOW_ASSIGN(IUTEST_PP_CAT(AnyOfMatcher, n));				\
	tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;						\
	}

IIUT_DECL_ANYOF_MATCHER(2);
IIUT_DECL_ANYOF_MATCHER(3);
IIUT_DECL_ANYOF_MATCHER(4);
IIUT_DECL_ANYOF_MATCHER(5);
IIUT_DECL_ANYOF_MATCHER(6);
IIUT_DECL_ANYOF_MATCHER(7);
IIUT_DECL_ANYOF_MATCHER(8);
IIUT_DECL_ANYOF_MATCHER(9);
IIUT_DECL_ANYOF_MATCHER(10);

#undef IIUT_DECL_ANYOF_MATCHER

#endif

#endif

}	// end of namespace detail

namespace matchers
{

/**
 * @ingroup	MATCHERS
 * @brief	Make Equals matcher
*/
template<typename T>
detail::EqMatcher<T> Equals(const T& expected) { return detail::EqMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Eq matcher
*/
template<typename T>
detail::EqMatcher<T> Eq(const T& expected) { return detail::EqMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Ne matcher
*/
template<typename T>
detail::NeMatcher<T> Ne(const T& expected) { return detail::NeMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Le matcher
*/
template<typename T>
detail::LeMatcher<T> Le(const T& expected) { return detail::LeMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Lt matcher
*/
template<typename T>
detail::LtMatcher<T> Lt(const T& expected) { return detail::LtMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Ge matcher
*/
template<typename T>
detail::GeMatcher<T> Ge(const T& expected) { return detail::GeMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Gt matcher
*/
template<typename T>
detail::GtMatcher<T> Gt(const T& expected) { return detail::GtMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make IsNull matcher
*/
inline detail::IsNullMatcher IsNull() { return detail::IsNullMatcher(); }

/**
 * @ingroup	MATCHERS
 * @brief	Make NotNull matcher
*/
inline detail::NotNullMatcher NotNull() { return detail::NotNullMatcher(); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Float Eq matcher
 * @details	argument は expected とおよそ等しい
*/
inline detail::FloatingPointEqMatcher<float> FloatEq(float expected) { return detail::FloatingPointEqMatcher<float>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Double Eq matcher
 * @details	argument は expected とおよそ等しい
*/
inline detail::FloatingPointEqMatcher<double> DoubleEq(double expected) { return detail::FloatingPointEqMatcher<double>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make NanSensitive Float Eq matcher
 * @details	argument は expected とおよそ等しい（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointEqMatcher<float> NanSensitiveFloatEq(float expected) { return detail::NanSensitiveFloatingPointEqMatcher<float>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make NanSensitive Double Eq matcher
 * @details	argument は expected とおよそ等しい（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointEqMatcher<double> NanSensitiveDoubleEq(double expected) { return detail::NanSensitiveFloatingPointEqMatcher<double>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make StrEq matcher
*/
template<typename T>
detail::StrEqMatcher<T> StrEq(const T& expected) { return detail::StrEqMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make StrNe matcher
*/
template<typename T>
detail::StrNeMatcher<T> StrNe(const T& expected) { return detail::StrNeMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make StrCaseEq matcher
*/
template<typename T>
detail::StrCaseEqMatcher<T> StrCaseEq(const T& expected) { return detail::StrCaseEqMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make StrCaseNe matcher
*/
template<typename T>
detail::StrCaseNeMatcher<T> StrCaseNe(const T& expected) { return detail::StrCaseNeMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make StartsWith matcher
*/
template<typename T>
detail::StartsWithMatcher<const T&> StartsWith(const T& str) { return detail::StartsWithMatcher<const T&>(str); }

/**
 * @ingroup	MATCHERS
 * @brief	Make HasSubstr matcher
*/
template<typename T>
detail::HasSubstrMatcher<const T&> HasSubstr(const T& expected) { return detail::HasSubstrMatcher<const T&>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make EndsWith matcher
*/
template<typename T>
detail::EndsWithMatcher<const T&> EndsWith(const T& str) { return detail::EndsWithMatcher<const T&>(str); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Contains matcher
 * @details	argument は expected にマッチする要素を含む
*/
template<typename T>
detail::ContainsMatcher<T> Contains(const T& expected) { return detail::ContainsMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Each matcher
 * @details	argument はすべての要素が expected にマッチする
*/
template<typename T>
detail::EachMatcher<T> Each(const T& expected) { return detail::EachMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make ElementsAreArray matcher
 * @details	argument はの各要素が a の要素とマッチする
*/
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArray(const T& a) { return detail::ElementsAreArrayMatcher<T>(a); }

/**
 * @ingroup	MATCHERS
 * @brief	Make ElementsAreArray matcher
 * @details	argument はの要素 count 個が a の要素とマッチする
*/
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArray(const T& a, int count) { return detail::ElementsAreArrayMatcher<T>(a, count); }

#if IUTEST_HAS_MATCHER_ELEMENTSARE

#if IUTEST_HAS_VARIADIC_TEMPLATES

/**
 * @ingroup	MATCHERS
 * @brief	Make ElementsAre matcher
*/
template<typename ...T>
detail::ElementsAreMatcher<T...> ElementsAre(const T&... m) { return detail::ElementsAreMatcher<T...>(m...); }

#else

#define IIUT_ELEMENTSARE_MATCHER_NAME(n)	IUTEST_PP_CAT(ElementsAreMatcher, n)
#define IIUT_DECL_ELEMENTSARE(n)												\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >							\
	detail:: IIUT_ELEMENTSARE_MATCHER_NAME(n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
	ElementsAre( IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &m) ) { return		\
	detail:: IIUT_ELEMENTSARE_MATCHER_NAME(n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
		( IUTEST_PP_ENUM_PARAMS(n, m) ); }


IIUT_DECL_ELEMENTSARE(1)
IIUT_DECL_ELEMENTSARE(2)
IIUT_DECL_ELEMENTSARE(3)
IIUT_DECL_ELEMENTSARE(4)
IIUT_DECL_ELEMENTSARE(5)
IIUT_DECL_ELEMENTSARE(6)
IIUT_DECL_ELEMENTSARE(7)
IIUT_DECL_ELEMENTSARE(8)
IIUT_DECL_ELEMENTSARE(9)
IIUT_DECL_ELEMENTSARE(10)

#undef IIUT_ELEMENTSARE_MATCHER_NAME
#undef IIUT_DECL_ELEMENTSARE
#endif

#endif

/**
 * @ingroup	MATCHERS
 * @brief	Make Key matcher
 * @details	argument.first は expedted にマッチする 
*/
template<typename T>
detail::KeyMatcher<T> Key(const T& expected) { return detail::KeyMatcher<T>(expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Pair matcher
 * @details	argument.first は m1 にマッチし、arugment.second が m2 にマッチする 
*/
template<typename T1, typename T2>
detail::PairMatcher<T1, T2> Pair(const T1& m1, const T2& m2) { return detail::PairMatcher<T1, T2>(m1, m2); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Field matcher
 * @details	argument.*field は expedted にマッチする 
*/
template<typename F, typename T>
detail::FieldMatcher<F, T> Field(const F& field, const T& expected) { return detail::FieldMatcher<F, T>(field, expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Property matcher
 * @details	argument.*property() は expedted にマッチする 
*/
template<typename P, typename T>
detail::PropertyMatcher<P, T> Property(const P& prop, const T& expected) { return detail::PropertyMatcher<P, T>(prop, expected); }

/**
 * @ingroup	MATCHERS
 * @brief	Make Any matcher
*/
template<typename T>
detail::AnyMatcher<T> A(void) { return detail::AnyMatcher<T>(); }


/**
 * @ingroup	MATCHERS
 * @brief	Anything matcher
*/
const detail::AnythingMatcher _;

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

#if IUTEST_HAS_VARIADIC_TEMPLATES

/**
 * @ingroup	MATCHERS
 * @brief	Make AllOf matcher
*/
template<typename ...T>
detail::AllOfMatcher<T...> AllOf(const T&... m) { return detail::AllOfMatcher<T...>(m...); }

/**
 * @ingroup	MATCHERS
 * @brief	Make AnyOf matcher
*/
template<typename ...T>
detail::AnyOfMatcher<T...> AnyOf(const T&... m) { return detail::AnyOfMatcher<T...>(m...); }

#else

#define IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)	IUTEST_PP_CAT( IUTEST_PP_CAT(name, Matcher), n)
#define IIUT_DECL_ANYOF_AND_ALLOF(name, n)												\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >									\
	detail:: IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
	name( IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &m) ) { return						\
	detail:: IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)< IUTEST_PP_ENUM_PARAMS(n, T) >	\
		( IUTEST_PP_ENUM_PARAMS(n, m) ); }


IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 2)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 3)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 4)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 5)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 6)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 7)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 8)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 9)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 10)

IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 2)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 3)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 4)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 5)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 6)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 7)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 8)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 9)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 10)

#undef IIUT_ANYOF_AND_ALLOF_MATCHER_NAME
#undef IIUT_DECL_ANYOF_AND_ALLOF

#endif

#endif

}	// end of namespace matchers

using namespace matchers;

}	// end of namespace iutest

#endif	// IUTEST_HAS_MATCHERS

#endif // INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_
