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
#define IUTEST_ASSERT(expr)	IUTEST_TEST_EXPRESSION_(expr, IUTEST_ASSERT_FAILURE)

/**
 * @private
 * @{
*/
#define IUTEST_TEST_EXPRESSION_(expr, on_failure)	\
	IUTEST_TEST_TRUE( (::iutest::detail::ExpressionDecomposer()->*expr).GetResult(), #expr, on_failure)

/**
 * @}
*/

//======================================================================
// class

/** @private */
#define IIUT_DECL_EXPRESSION_RESULT_OP(op)	\
	template<typename RHS>ExpressionResult operator op (const RHS& rhs) const {		\
		const bool b = static_cast<bool>(m_result);									\
		if( b op rhs ) { return ExpressionResult(AssertionSuccess()); }				\
		return ExpressionResult(AssertionFailure() << m_result.message() << " " #op " " << rhs);	\
	}
/**
* @brief	expression result
*/
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
	AssertionResult m_result;
};

#undef IIUT_DECL_EXPRESSION_RESULT_OP

/** @private */
#define IIUT_DECL_EXPRESSION_OP(op)	\
	template<typename RHS>ExpressionResult operator op (const RHS& rhs) const {		\
		if( m_lhs op rhs ) { return ExpressionResult(AssertionSuccess()); }			\
		return ExpressionResult(AssertionFailure() << m_lhs << " " #op " " << rhs);	\
	}

/**
 * @brief	expression lhs
 * @tparam	lhs type
*/
template<typename T>
class ExpressionLHS
{
public:
	ExpressionLHS(T lhs) : m_lhs(lhs) {}

public:
	IIUT_DECL_EXPRESSION_OP(==)
	IIUT_DECL_EXPRESSION_OP(!=)
	IIUT_DECL_EXPRESSION_OP(<)
	IIUT_DECL_EXPRESSION_OP(<=)
	IIUT_DECL_EXPRESSION_OP(>)
	IIUT_DECL_EXPRESSION_OP(>=)
	IIUT_DECL_EXPRESSION_OP(&)
	IIUT_DECL_EXPRESSION_OP(|)
	IIUT_DECL_EXPRESSION_OP(&&)
	IIUT_DECL_EXPRESSION_OP(||)

public:
	AssertionResult GetResult(void) const
	{
		if( m_lhs )
		{
			return AssertionSuccess();
		}
		return AssertionFailure() << "expansion: " << m_lhs;
	}
private:
	IUTEST_PP_DISALLOW_ASSIGN(ExpressionLHS);
private:
	T m_lhs;
};

#undef IIUT_DECL_EXPRESSION_OP

/**
 * @brief	expression decomposer
*/
class ExpressionDecomposer
{
public:
	template<typename T>
	ExpressionLHS<const T&> operator ->*(const T& expr)
	{
		return ExpressionLHS<const T&>(expr);
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_EXPRESSION_ASSERTION_HPP_B9783316_33CF_4CA7_81D0_0BF44B048A4A_
