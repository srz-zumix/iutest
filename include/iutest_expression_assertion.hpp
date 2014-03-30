//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_expression_assertion.hpp
 * @brief		iris unit test 式アサーション 定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_EXPRESSION_ASSERTION_HPP_B9783316_33CF_4CA7_81D0_0BF44B048A4A_
#define INCG_IRIS_IUTEST_EXPRESSION_ASSERTION_HPP_B9783316_33CF_4CA7_81D0_0BF44B048A4A_

//======================================================================
// include
#include "iutest_assertion.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// define
/**
 * @private
 * @{
*/

#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE
#  define IIUT_EXPRESSION_DECOMPOSE(expected)	::iutest::detail::ExpressionDecomposer<expected>()->*
#else
#  define IIUT_EXPRESSION_DECOMPOSE(expected)	::iutest::detail::ExpressionDecomposer<expected>()>>
#endif

#define IUTEST_TEST_EXPRESSION_(expr, expected, on_failure)	\
	IUTEST_TEST_TRUE( ( IIUT_EXPRESSION_DECOMPOSE(expected) expr ).GetResult(), #expr, on_failure )

/**
 * @}
*/

//======================================================================
// class

/** @private */
#define IIUT_DECL_EXPRESSION_RESULT_OP(op)	\
	template<typename RHS>ExpressionResult<Expected> operator op (const RHS& rhs) const {		\
		const bool lhs = raw_result();															\
		const bool b = lhs op rhs ? true : false;												\
		return ExpressionResult<Expected>(AssertionResult(b == Expected) << m_result.message() << " " #op " " << rhs);	\
	}

/**
 * @brief	expression result
 * @tparam	Expected=expected result
*/
template<bool Expected>
class ExpressionResult
{
public:
	ExpressionResult(const AssertionResult& ar)
		: m_result(ar) {}

public:
	IIUT_DECL_EXPRESSION_RESULT_OP(||)
	IIUT_DECL_EXPRESSION_RESULT_OP(&&)

public:
	AssertionResult GetResult(void) const 
	{
		return AssertionResult(static_cast<bool>(m_result))
			<< "expansion: " << m_result.message();
	}
private:
	bool raw_result(void) const { return Expected ? static_cast<bool>(m_result) : m_result.failed(); }
private:
	AssertionResult m_result;
};

#undef IIUT_DECL_EXPRESSION_RESULT_OP

/** @private */
#define IIUT_DECL_EXPRESSION_OP(op)	\
	template<typename RHS>ExpressionResult<Expected> operator op (const RHS& rhs) const {		\
		const bool b = (m_lhs op rhs) ? true : false;											\
		return ExpressionResult<Expected>(AssertionResult(b == Expected) << m_message << " " #op " " << rhs);	\
	}

#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE

#define IIUT_DECL_EXPRESSION_OP_LHS(op)	\
	template<typename RHS>auto operator op (const RHS& rhs) const	\
	-> ExpressionLHS< decltype( expression_op_helper::operand_result( ::std::declval<T>() op rhs) ), Expected> {	\
		return OperandResult(m_lhs op rhs) << " " #op " " << rhs;	\
	}

#endif

namespace expression_op_helper
{
	template<typename T>
	T operand_result(const T&);
}

/**
 * @brief	expression lhs
 * @tparam	T=type
 * @tparam	Expected=expected result
*/
template<typename T, bool Expected>
class ExpressionLHS
{
	typedef ExpressionLHS<T, Expected> _Myt;
public:
	ExpressionLHS(T lhs) : m_lhs(lhs)
	{
		AppendMessage(lhs);
	}
	ExpressionLHS(T lhs, const ::std::string& msg) : m_lhs(lhs), m_message(msg) {}

public:
	IIUT_DECL_EXPRESSION_OP(==)
	IIUT_DECL_EXPRESSION_OP(!=)
	IIUT_DECL_EXPRESSION_OP(<)
	IIUT_DECL_EXPRESSION_OP(<=)
	IIUT_DECL_EXPRESSION_OP(>)
	IIUT_DECL_EXPRESSION_OP(>=)
	IIUT_DECL_EXPRESSION_OP(&&)
	IIUT_DECL_EXPRESSION_OP(||)

#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE
	IIUT_DECL_EXPRESSION_OP_LHS(+)
	IIUT_DECL_EXPRESSION_OP_LHS(-)
	IIUT_DECL_EXPRESSION_OP_LHS(*)
	IIUT_DECL_EXPRESSION_OP_LHS(/)
	IIUT_DECL_EXPRESSION_OP_LHS(%)
#endif

#if IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE
	IIUT_DECL_EXPRESSION_OP_LHS(&)
	IIUT_DECL_EXPRESSION_OP_LHS(|)
	IIUT_DECL_EXPRESSION_OP_LHS(^)
	IIUT_DECL_EXPRESSION_OP_LHS(<<)
	IIUT_DECL_EXPRESSION_OP_LHS(>>)
#endif

private:
	template<typename U>
	ExpressionLHS<U, Expected> OperandResult(const U& lhs) const
	{
		return ExpressionLHS<U, Expected>(lhs, m_message);
	}

public:
	/**
	 * @brief	メッセージ追加
	*/
	template<typename U>
	_Myt& operator << (const U& value)
	{
		AppendMessage(value);
		return *this;
	}

public:
	/** @private */
	AssertionResult GetResult(void) const
	{
		const bool b = m_lhs ? true : false;
		if( b == Expected )
		{
			return AssertionSuccess();
		}
		return AssertionFailure() << "expansion: " << m_message;
	}

private:
	template<typename U>
	void AppendMessage(const U& value)
	{
		Message msg;
		msg << value;
		m_message += msg.GetString();
	}

private:
	IUTEST_PP_DISALLOW_ASSIGN(ExpressionLHS);
private:
	T m_lhs;
	::std::string m_message;
};

#undef IIUT_DECL_EXPRESSION_OP
#ifdef IIUT_DECL_EXPRESSION_OP_LHS
#  undef IIUT_DECL_EXPRESSION_OP_LHS
#endif

/**
 * @brief	expression decomposer
 * @tparam	Expected=expected result
*/
template<bool Expected>
class ExpressionDecomposer
{
public:
#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE
	template<typename T>
	ExpressionLHS<const T&, Expected> operator ->*(const T& expr)
	{
		return ExpressionLHS<const T&, Expected>(expr);
	}
#else
	template<typename T>
	ExpressionLHS<const T&, Expected> operator >>(const T& expr)
	{
		return ExpressionLHS<const T&, Expected>(expr);
	}
#endif
};

}	// end of namespace detail
}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_EXPRESSION_ASSERTION_HPP_B9783316_33CF_4CA7_81D0_0BF44B048A4A_
