//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_genparams.hpp
 * @brief		iris unit test parameter generator 定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_genparams_HPP_7845F59A_825C_426a_B451_573245408998_
#define INCG_IRIS_iutest_genparams_HPP_7845F59A_825C_426a_B451_573245408998_

//======================================================================
// include
#include "iutest_internal_defs.hpp"

#if IUTEST_HAS_PARAM_TEST

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	パラメータ生成器インターフェイス
*/
template<typename T>
class iuIParamGenerator
{
	typedef iuIParamGenerator<T>	_Myt;
public:
	typedef _Myt*	(*Generator)(void);
public:
	virtual	~iuIParamGenerator(void) {}
public:
	virtual	void	Begin(void) = 0;	//!< パラメータリストの先頭に移動
	virtual T		GetCurrent(void) const = 0;	// 現在のパラメータを取得
	virtual void	Next(void)	= 0;	//!< パラメータを取得して次に移動
	virtual bool	IsEnd(void) const = 0;	//!< パラメータリストの終端にいるかどうか
};

/**
 * @brief	パラメータ生成器保持クラス
*/
template<typename T>
class iuParamGenerator : public iuIParamGenerator<T>
{
	typedef iuIParamGenerator<T>	_Interface;

public:
	iuParamGenerator(_Interface* pInterface=NULL) : m_pInterface(pInterface) {}

public:
	virtual	void	Begin(void)	{ m_pInterface->Begin(); }	//!< パラメータリストの先頭に移動
	virtual T		GetCurrent(void) const { return m_pInterface->GetCurrent(); }	// 現在のパラメータを取得
	virtual void	Next(void)	{ m_pInterface->Next(); }	//!< パラメータを取得して次に移動
	virtual bool	IsEnd(void) const { return m_pInterface->IsEnd(); }	//!< パラメータリストの終端にいるかどうか
private:
	_Interface*		m_pInterface;
};


/**
 * @brief	範囲パラメータ生成器
 * @tparam T	= パラメータ型
*/
template<typename T>
class iuRangeParamsGenerator : public iuIParamGenerator<T>
{
	T	m_begin;
	T	m_end;
	T	m_step;
	T	m_cur;
public:
	/**
	 * @brief	コンストラクタ
	 * @param [in]	begin	= 開始値
	 * @param [in]	end		= 終了値
	 * @param [in]	step	= 増値
	*/
	iuRangeParamsGenerator(T begin, T end, T step=1)
		: m_begin(begin)
		, m_end(end)
		, m_step(step)
		, m_cur(begin)
	{
	}

public:
	virtual	void	Begin(void) { m_cur = m_begin; }
	virtual T		GetCurrent(void) const	{ return m_cur; }
	virtual void	Next(void)	{ m_cur += m_step; }
	virtual bool	IsEnd(void) const	{ if( m_cur < m_end ) return false; return true; }
};

/**
 * @breif	真偽値パラメータ生成器
 * @tparam T	= パラメータ型
*/
template<typename T>
class iuBoolParamsGenerator : public iuIParamGenerator<T>
{
	T	m_cur;
	int m_n;
public:
	iuBoolParamsGenerator(void)
		: m_n(0)
	{}

public:
	virtual	void	Begin(void) { m_cur = 0; m_n = 0; }
	virtual T		GetCurrent(void) const	{ return m_cur; }
	virtual void	Next(void)	{ ++m_n; m_cur = !m_cur; }
	virtual bool	IsEnd(void) const	{ if( m_n < 2 ) return false; return true; }
};

/**
 * @brief	値配列パラメータ生成器
 * @tparam T	= パラメータ型
*/
template<typename T>
class iuValueInParamsGenerator : public iuIParamGenerator<T>
{
	typedef ::std::vector<T>	params_t;
	params_t	m_values;
	typename params_t::iterator m_it;
public:
	iuValueInParamsGenerator(const params_t& values)
		: m_values(values) {}
	template<typename Container>
	iuValueInParamsGenerator(const Container& values)
	{
		for( typename Container::iterator it = values.begin(), end=values.end(); it != end; ++it )
		{
			m_values.push_back(static_cast<T>(*it));
		}
	}
	template<typename TT, size_t SIZE>
	iuValueInParamsGenerator(const TT (&values)[SIZE])
	{
		const TT* begin = values;
		for( const TT* end = values+SIZE; begin != end; ++begin )
		{
			m_values.push_back(static_cast<T>(*begin));
		}
	}

	template<typename Ite>
	iuValueInParamsGenerator(Ite begin, Ite end)
	{
		for( ; begin != end; ++begin )
		{
			m_values.push_back(static_cast<T>(*begin));
		}
	}
public:
	virtual	void	Begin(void) { m_it = m_values.begin(); }
	virtual T		GetCurrent(void) const	{ return *m_it; }
	virtual void	Next(void)	{ ++m_it; }
	virtual bool	IsEnd(void) const	{ return (m_it == m_values.end()); }
};

#if IUTEST_HAS_VARIADIC_VALUES
template<typename... Args>
class iuValueArray
{
	typedef tuples::tuple<Args...>	_MyTuple;

	template<typename T>
	struct make_array
	{
		T val[tuples::tuple_size<_MyTuple>::value];
		make_array(const _MyTuple& t)
		{
			make<0>(t);
		};

		template<int I>
		void	make(const _MyTuple& t, typename detail::enable_if<(I != tuples::tuple_size<_MyTuple>::value), void>::type*& = detail::enabler::value )
		{
			val[I] = tuples::get<I>(t);
			make<I+1>(t);
		}
		template<int I>
		void	make(_MyTuple, typename detail::enable_if<(I == tuples::tuple_size<_MyTuple>::value), void>::type*& = detail::enabler::value )
		{}
	};
public:
	iuValueArray(const Args&... args)
		: v(args...)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		make_array<T> ar(v);
		return new iuValueInParamsGenerator<T>(ar.val);
	}
private:
	_MyTuple v;
};

#else

template<typename A1>
class iuValueArray1
{
public:
	iuValueArray1(A1 a1) : v1(a1)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;
};

template<typename A1, typename A2>
class iuValueArray2
{
public:
	iuValueArray2(A1 a1, A2 a2) : v1(a1), v2(a2)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;
};


template<typename A1, typename A2, typename A3>
class iuValueArray3
{
public:
	iuValueArray3(A1 a1, A2 a2, A3 a3) : v1(a1), v2(a2), v3(a3)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;
};

template<typename A1, typename A2, typename A3, typename A4>
class iuValueArray4
{
public:
	iuValueArray4(A1 a1, A2 a2, A3 a3, A4 a4) : v1(a1), v2(a2), v3(a3), v4(a4)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5>
class iuValueArray5
{
public:
	iuValueArray5(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class iuValueArray6
{
public:
	iuValueArray6(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;	A6	v6;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class iuValueArray7
{
public:
	iuValueArray7(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;	A6	v6;	A7	v7;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
class iuValueArray8
{
public:
	iuValueArray8(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;	A6	v6;	A7	v7;	A8	v8;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
class iuValueArray9
{
public:
	iuValueArray9(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;	A6	v6;	A7	v7;	A8	v8;	A9	v9;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10>
class iuValueArray10
{
public:
	iuValueArray10(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1	v1;	A2	v2;	A3	v3;	A4	v4;	A5	v5;	A6	v6;	A7	v7;	A8	v8;	A9	v9;
	A10 v10;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11>
class iuValueArray11
{
public:
	iuValueArray11(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12>
class iuValueArray12
{
public:
	iuValueArray12(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13>
class iuValueArray13
{
public:
	iuValueArray13(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14>
class iuValueArray14
{
public:
	iuValueArray14(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
class iuValueArray15
{
public:
	iuValueArray15(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
class iuValueArray16
{
public:
	iuValueArray16(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17>
class iuValueArray17
{
public:
	iuValueArray17(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; 
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
class iuValueArray18
{
public:
	iuValueArray18(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; 
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
class iuValueArray19
{
public:
	iuValueArray19(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19; 
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20>
class iuValueArray20
{
public:
	iuValueArray20(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9), v10(a10)
		, v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21>
class iuValueArray21
{
public:
	iuValueArray21(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22>
class iuValueArray22
{
public:
	iuValueArray22(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23>
class iuValueArray23
{
public:
	iuValueArray23(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24>
class iuValueArray24
{
public:
	iuValueArray24(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25>
class iuValueArray25
{
public:
	iuValueArray25(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26>
class iuValueArray26
{
public:
	iuValueArray26(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27>
class iuValueArray27
{
public:
	iuValueArray27(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; 
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28>
class iuValueArray28
{
public:
	iuValueArray28(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; 
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29>
class iuValueArray29
{
public:
	iuValueArray29(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30>
class iuValueArray30
{
public:
	iuValueArray30(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31>
class iuValueArray31
{
public:
	iuValueArray31(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32>
class iuValueArray32
{
public:
	iuValueArray32(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33>
class iuValueArray33
{
public:
	iuValueArray33(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34>
class iuValueArray34
{
public:
	iuValueArray34(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35>
class iuValueArray35
{
public:
	iuValueArray35(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36>
class iuValueArray36
{
public:
	iuValueArray36(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37>
class iuValueArray37
{
public:
	iuValueArray37(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38>
class iuValueArray38
{
public:
	iuValueArray38(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39>
class iuValueArray39
{
public:
	iuValueArray39(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40>
class iuValueArray40
{
public:
	iuValueArray40(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41>
class iuValueArray41
{
public:
	iuValueArray41(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42>
class iuValueArray42
{
public:
	iuValueArray42(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43>
class iuValueArray43
{
public:
	iuValueArray43(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44>
class iuValueArray44
{
public:
	iuValueArray44(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45>
class iuValueArray45
{
public:
	iuValueArray45(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46>
class iuValueArray46
{
public:
	iuValueArray46(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45), v46(a46)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45), static_cast<T>(v46)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45; A46 v46;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47>
class iuValueArray47
{
public:
	iuValueArray47(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45), v46(a46), v47(a47)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45), static_cast<T>(v46), static_cast<T>(v47)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45; A46 v46; A47 v47;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48>
class iuValueArray48
{
public:
	iuValueArray48(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45), v46(a46), v47(a47), v48(a48)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45), static_cast<T>(v46), static_cast<T>(v47), static_cast<T>(v48)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45; A46 v46; A47 v47; A48 v48;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49>
class iuValueArray49
{
public:
	iuValueArray49(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45), v46(a46), v47(a47), v48(a48), v49(a49)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45), static_cast<T>(v46), static_cast<T>(v47), static_cast<T>(v48), static_cast<T>(v49)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45; A46 v46; A47 v47; A48 v48; A49 v49;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9
, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19
, typename A20, typename A21, typename A22, typename A23, typename A24, typename A25, typename A26, typename A27, typename A28, typename A29
, typename A30, typename A31, typename A32, typename A33, typename A34, typename A35, typename A36, typename A37, typename A38, typename A39
, typename A40, typename A41, typename A42, typename A43, typename A44, typename A45, typename A46, typename A47, typename A48, typename A49
, typename A50>
class iuValueArray50
{
public:
	iuValueArray50(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
		, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19
		, A20 a20, A21 a21, A22 a22, A23 a23, A24 a24, A25 a25, A26 a26, A27 a27, A28 a28, A29 a29
		, A30 a30, A31 a31, A32 a32, A33 a33, A34 a34, A35 a35, A36 a36, A37 a37, A38 a38, A39 a39
		, A40 a40, A41 a41, A42 a42, A43 a43, A44 a44, A45 a45, A46 a46, A47 a47, A48 a48, A49 a49
		, A50 a50)
		: v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7), v8(a8), v9(a9)
		, v10(a10), v11(a11), v12(a12), v13(a13), v14(a14), v15(a15), v16(a16), v17(a17), v18(a18), v19(a19)
		, v20(a20), v21(a21), v22(a22), v23(a23), v24(a24), v25(a25), v26(a26), v27(a27), v28(a28), v29(a29)
		, v30(a30), v31(a31), v32(a32), v33(a33), v34(a34), v35(a35), v36(a36), v37(a37), v38(a38), v39(a39)
		, v40(a40), v41(a41), v42(a42), v43(a43), v44(a44), v45(a45), v46(a46), v47(a47), v48(a48), v49(a49)
		, v50(a50)
	{}
public:
	template<typename T>
	operator	iuIParamGenerator<T>* (void) const
	{
		const T val[] = { static_cast<T>(v1), static_cast<T>(v2), static_cast<T>(v3), static_cast<T>(v4)
			, static_cast<T>(v5), static_cast<T>(v6), static_cast<T>(v7), static_cast<T>(v8), static_cast<T>(v9)
			, static_cast<T>(v10), static_cast<T>(v11), static_cast<T>(v12), static_cast<T>(v13), static_cast<T>(v14)
			, static_cast<T>(v15), static_cast<T>(v16), static_cast<T>(v17), static_cast<T>(v18), static_cast<T>(v19)
			, static_cast<T>(v20), static_cast<T>(v21), static_cast<T>(v22), static_cast<T>(v23), static_cast<T>(v24)
			, static_cast<T>(v25), static_cast<T>(v26), static_cast<T>(v27), static_cast<T>(v28), static_cast<T>(v29)
			, static_cast<T>(v30), static_cast<T>(v31), static_cast<T>(v32), static_cast<T>(v33), static_cast<T>(v34)
			, static_cast<T>(v35), static_cast<T>(v36), static_cast<T>(v37), static_cast<T>(v38), static_cast<T>(v39)
			, static_cast<T>(v40), static_cast<T>(v41), static_cast<T>(v42), static_cast<T>(v43), static_cast<T>(v44)
			, static_cast<T>(v45), static_cast<T>(v46), static_cast<T>(v47), static_cast<T>(v48), static_cast<T>(v49)
			, static_cast<T>(v50)
		};
		return new iuValueInParamsGenerator<T>(val);
	}
private:
	A1   v1; A2   v2; A3   v3; A4   v4; A5   v5; A6   v6; A7   v7; A8   v8; A9   v9;
	A10 v10; A11 v11; A12 v12; A13 v13; A14 v14; A15 v15; A16 v16; A17 v17; A18 v18; A19 v19;
	A20 v20; A21 v21; A22 v22; A23 v23; A24 v24; A25 v25; A26 v26; A27 v27; A28 v28; A29 v29;
	A30 v30; A31 v31; A32 v32; A33 v33; A34 v34; A35 v35; A36 v36; A37 v37; A38 v38; A39 v39;
	A40 v40; A41 v41; A42 v42; A43 v43; A44 v44; A45 v45; A46 v46; A47 v47; A48 v48; A49 v49;
	A50 v50;
};

#endif

#if IUTEST_HAS_COMBINE

#if IUTEST_HAS_VARIADIC_COMBINE

template<typename... Args>
class iuCartesianProductGenerator : public iuIParamGenerator< tuples::tuple<Args...> >
{
	typedef tuples::tuple< iuParamGenerator<Args>... > _MyTuple;
	static const int count = tuples::tuple_size<_MyTuple>::value;

	template<int index, int end, typename Tuple>
	void begin_foreach(Tuple& t, typename detail::enable_if<index != end, void>::type*& = detail::enabler::value )
	{
		tuples::get<index>(t).Begin();
		begin_foreach<index+1, end>(t);
	}
	template<int index, int end, typename Tuple>
	void begin_foreach(Tuple& , typename detail::enable_if<index == end, void>::type*& = detail::enabler::value )
	{
	}

	template<int index, int end, typename Tuple>
	bool is_end_foreach(Tuple& t, typename detail::enable_if<index != end, void>::type*& = detail::enabler::value ) const
	{
		bool b = tuples::get<index>(t).IsEnd();
		return b && is_end_foreach<index+1, end>(t);
	}
	template<int index, int end, typename Tuple>
	bool is_end_foreach(Tuple& , typename detail::enable_if<index == end, void>::type*& = detail::enabler::value ) const
	{
		return true;
	}

	template<int index, int end, typename Tuple>
	void next_foreach(Tuple& t, typename detail::enable_if<index != end, void>::type*& = detail::enabler::value )
	{
		next_foreach<index+1, end>(t);
		if( is_end_foreach<index+1, end>(t) )
		{
			tuples::get<index>(t).Next();
			if( !tuples::get<index>(t).IsEnd() ) begin_foreach<index+1, end>(t);
		}
	}
	template<int index, int end, typename Tuple>
	void next_foreach(Tuple& , typename detail::enable_if<index == end, void>::type*& = detail::enabler::value )
	{
	}

	template<int index, int end, typename T1, typename ...TArgs>
	tuples::tuple<T1, TArgs...> current_foreach(typename detail::enable_if<index != end-1, void>::type*& = detail::enabler::value ) const
	{
		return ::std::tuple_cat( tuples::tuple<T1>(tuples::get<index>(v).GetCurrent())
			, current_foreach<index+1, end, TArgs...>());
	}
	template<int index, int end, typename T1, typename ...TArgs>
	tuples::tuple<T1>  current_foreach(typename detail::enable_if<index == end-1, void>::type*& = detail::enabler::value ) const
	{
		return tuples::tuple<T1>(tuples::get<index>(v).GetCurrent());
	}

public:
	typedef tuples::tuple<Args...>	ParamType;
public:
	iuCartesianProductGenerator(void)
	{}

public:
	virtual	void	Begin(void)
	{
		begin_foreach<0, count>(v);
	}
	virtual void	Next(void)
	{
		if( IsEnd() ) return;
		next_foreach<0, count>(v);
	}
	virtual bool	IsEnd(void) const
	{
		return is_end_foreach<0, count>(v);
	}
	virtual ParamType	GetCurrent(void) const
	{
		return current_foreach<0, count, Args...>();
	}

	_MyTuple&	generators(void) { return v; }
private:
	_MyTuple v;
};

template<typename... Generator>
class iuCartesianProductHolder
{
	typedef iuCartesianProductHolder<Generator...> _Myt;

	typedef tuples::tuple<const Generator...>	_MyTuple;

	template<int index, int end, typename ArgTuple, typename SrcTuple, typename DstTuple>
	void set_foreach(SrcTuple& src, DstTuple& dst, typename detail::enable_if<index != end, void>::type*& = detail::enabler::value ) const
	{
		tuples::get<index>(dst) = static_cast< typename tuples::tuple_element<index, DstTuple>::type >(tuples::get<index>(src));
		set_foreach<index+1, end, ArgTuple>(src, dst);
	}
	template<int index, int end, typename ArgTuple, typename SrcTuple, typename DstTuple>
	void set_foreach(SrcTuple& , DstTuple& , typename detail::enable_if<index == end, void>::type*& = detail::enabler::value ) const
	{
	}

public:
	iuCartesianProductHolder(const Generator&... generators)
		: v(generators...) {}

public:
	template<typename... Args>
	operator iuIParamGenerator< tuples::tuple<Args...> >* () const 
	{
		typedef tuples::tuple<Args...> ArgTuple;
		iuCartesianProductGenerator<Args...>* p = new iuCartesianProductGenerator<Args...>();
		set_foreach<0, tuples::tuple_size<ArgTuple>::value, ArgTuple>(v, p->generators());
		return p;
	}

private:
	void	operator = (const _Myt&) {}
private:
	_MyTuple v;
};


#else

template<typename Generator1, typename Generator2, typename ParamType>
class iuICartesianProductGeneratorBase : public iuIParamGenerator< ParamType >
{
public:
	iuICartesianProductGeneratorBase(const Generator1& g1, const Generator2& g2)
		: m_g1(g1), m_g2(g2)
	{}
public:
	virtual	void	Begin(void)
	{
		m_g1.Begin();
		m_g2.Begin();
	}
	virtual void	Next(void)
	{
		if( m_g2.IsEnd() ) return;
		m_g2.Next();
		if( m_g2.IsEnd() )
		{
			m_g1.Next();
			if( !m_g1.IsEnd() ) m_g2.Begin();
		}
	}
	virtual bool	IsEnd(void) const
	{
		return m_g1.IsEnd() && m_g2.IsEnd();
	}

protected:
	Generator1	m_g1;
	Generator2	m_g2;
};

template<typename T1, typename T2>
class iuCartesianProductGenerator2 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>, iuParamGenerator<T2>, tuples::tuple<T1, T2> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>, iuParamGenerator<T2>, tuples::tuple<T1, T2> > _Mybase;
	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
public:
	typedef tuples::tuple<T1, T2>	ParamType;

public:
	iuCartesianProductGenerator2(const Generator1& g1, const Generator2& g2)
		: _Mybase(g1, g2)
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		return ParamType(this->m_g1.GetCurrent(), this->m_g2.GetCurrent());
	}
};

template<typename T1, typename T2, typename T3>
class iuCartesianProductGenerator3 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator2<T2, T3>
																			, tuples::tuple<T1, T2, T3> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>, iuCartesianProductGenerator2<T2, T3>, tuples::tuple<T1, T2, T3> >	_Mybase;
	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
public:
	typedef tuples::tuple<T1, T2, T3>	ParamType;
public:
	iuCartesianProductGenerator3(const Generator1& g1, const Generator2& g2, const Generator3& g3)
		: _Mybase(g1, iuCartesianProductGenerator2<T2, T3>(g2, g3))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param) );
	}
};

template<typename T1, typename T2, typename T3, typename T4>
class iuCartesianProductGenerator4 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator3<T2, T3, T4>
																			, tuples::tuple<T1, T2, T3, T4> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator3<T2, T3, T4>
		, tuples::tuple<T1, T2, T3, T4> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
public:
	typedef tuples::tuple<T1, T2, T3, T4>	ParamType;
public:
	iuCartesianProductGenerator4(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4)
		: _Mybase(g1, iuCartesianProductGenerator3<T2, T3, T4>(g2, g3, g4))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param));
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
class iuCartesianProductGenerator5 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator4<T2, T3, T4, T5>
																			, tuples::tuple<T1, T2, T3, T4, T5> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator4<T2, T3, T4, T5>
		, tuples::tuple<T1, T2, T3, T4, T5> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
	typedef iuParamGenerator<T5> Generator5;
public:
	typedef tuples::tuple<T1, T2, T3, T4, T5>	ParamType;
public:
	iuCartesianProductGenerator5(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5)
		: _Mybase(g1, iuCartesianProductGenerator4<T2, T3, T4, T5>(g2, g3, g4, g5))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4, T5> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param), tuples::get<3>(param) );
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class iuCartesianProductGenerator6 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator5<T2, T3, T4, T5, T6>
																			, tuples::tuple<T1, T2, T3, T4, T5, T6> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator5<T2, T3, T4, T5, T6>
		, tuples::tuple<T1, T2, T3, T4, T5, T6> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
	typedef iuParamGenerator<T5> Generator5;
	typedef iuParamGenerator<T6> Generator6;
public:
	typedef tuples::tuple<T1, T2, T3, T4, T5, T6>	ParamType;
public:
	iuCartesianProductGenerator6(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6)
		: _Mybase(g1, iuCartesianProductGenerator5<T2, T3, T4, T5, T6>(g2, g3, g4, g5, g6))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4, T5, T6> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param), tuples::get<3>(param), tuples::get<4>(param) );
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class iuCartesianProductGenerator7 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator6<T2, T3, T4, T5, T6, T7>
																			, tuples::tuple<T1, T2, T3, T4, T5, T6, T7> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator6<T2, T3, T4, T5, T6, T7>
		, tuples::tuple<T1, T2, T3, T4, T5, T6, T7> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
	typedef iuParamGenerator<T5> Generator5;
	typedef iuParamGenerator<T6> Generator6;
	typedef iuParamGenerator<T7> Generator7;
public:
	typedef tuples::tuple<T1, T2, T3, T4, T5, T6, T7>	ParamType;
public:
	iuCartesianProductGenerator7(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7)
		: _Mybase(g1, iuCartesianProductGenerator6<T2, T3, T4, T5, T6, T7>(g2, g3, g4, g5, g6, g7))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4, T5, T6, T7> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param), tuples::get<3>(param), tuples::get<4>(param)
			, tuples::get<5>(param) );
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class iuCartesianProductGenerator8 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator7<T2, T3, T4, T5, T6, T7, T8>
																			, tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator7<T2, T3, T4, T5, T6, T7, T8>
		, tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
	typedef iuParamGenerator<T5> Generator5;
	typedef iuParamGenerator<T6> Generator6;
	typedef iuParamGenerator<T7> Generator7;
	typedef iuParamGenerator<T8> Generator8;
public:
	typedef tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8>	ParamType;
public:
	iuCartesianProductGenerator8(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7, const Generator8& g8)
		: _Mybase(g1, iuCartesianProductGenerator7<T2, T3, T4, T5, T6, T7, T8>(g2, g3, g4, g5, g6, g7, g8))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4, T5, T6, T7, T8> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param), tuples::get<3>(param), tuples::get<4>(param)
			, tuples::get<5>(param), tuples::get<6>(param) );
	}
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class iuCartesianProductGenerator9 : public iuICartesianProductGeneratorBase<iuParamGenerator<T1>
																			, iuCartesianProductGenerator8<T2, T3, T4, T5, T6, T7, T8, T9>
																			, tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
	typedef iuICartesianProductGeneratorBase<iuParamGenerator<T1>
		, iuCartesianProductGenerator8<T2, T3, T4, T5, T6, T7, T8, T9>
		, tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >	_Mybase;

	typedef iuParamGenerator<T1> Generator1;
	typedef iuParamGenerator<T2> Generator2;
	typedef iuParamGenerator<T3> Generator3;
	typedef iuParamGenerator<T4> Generator4;
	typedef iuParamGenerator<T5> Generator5;
	typedef iuParamGenerator<T6> Generator6;
	typedef iuParamGenerator<T7> Generator7;
	typedef iuParamGenerator<T8> Generator8;
	typedef iuParamGenerator<T9> Generator9;
public:
	typedef tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T9, T8>	ParamType;
public:
	iuCartesianProductGenerator9(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7, const Generator8& g8, const Generator9& g9)
		: _Mybase(g1, iuCartesianProductGenerator8<T2, T3, T4, T5, T6, T7, T8, T9>(g2, g3, g4, g5, g6, g7, g8, g9))
	{}

public:
	virtual ParamType	GetCurrent(void) const
	{
		tuples::tuple<T2, T3, T4, T5, T6, T7, T8, T9> param(this->m_g2.GetCurrent());
		return ParamType(this->m_g1.GetCurrent(), tuples::get<0>(param), tuples::get<1>(param), tuples::get<2>(param), tuples::get<3>(param), tuples::get<4>(param)
			, tuples::get<5>(param), tuples::get<6>(param), tuples::get<7>(param) );
	}
};

// iuCartesianProductHolder

template<typename Generator1, typename Generator2>
class iuCartesianProductHolder2
{
	typedef iuCartesianProductHolder2<Generator1, Generator2> _Myt;
public:
	iuCartesianProductHolder2(const Generator1& g1, const Generator2& g2)
		: m_g1(g1), m_g2(g2) {}

public:
	template<typename T1, typename T2>
	operator iuIParamGenerator< tuples::tuple<T1, T2> >* () const 
	{
		return new iuCartesianProductGenerator2<T1, T2>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
};

template<typename Generator1, typename Generator2, typename Generator3>
class iuCartesianProductHolder3
{
	typedef iuCartesianProductHolder3<Generator1, Generator2, Generator3> _Myt;
public:
	iuCartesianProductHolder3(const Generator1& g1, const Generator2& g2, const Generator3& g3)
		: m_g1(g1), m_g2(g2), m_g3(g3) {}

public:
	template<typename T1, typename T2, typename T3>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3> >* () const 
	{
		return new iuCartesianProductGenerator3<T1, T2, T3>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4>
class iuCartesianProductHolder4
{
	typedef iuCartesianProductHolder4<Generator1, Generator2, Generator3, Generator4> _Myt;
public:
	iuCartesianProductHolder4(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4) {}

public:
	template<typename T1, typename T2, typename T3, typename T4>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4> >* () const 
	{
		return new iuCartesianProductGenerator4<T1, T2, T3, T4>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4, typename Generator5>
class iuCartesianProductHolder5
{
	typedef iuCartesianProductHolder5<Generator1, Generator2, Generator3, Generator4, Generator5> _Myt;
public:
	iuCartesianProductHolder5(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4), m_g5(g5) {}

public:
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4, T5> >* () const 
	{
		return new iuCartesianProductGenerator5<T1, T2, T3, T4, T5>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
			, static_cast< iuIParamGenerator<T5>* >(m_g5)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
	const Generator5	m_g5;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4, typename Generator5
, typename Generator6>
class iuCartesianProductHolder6
{
	typedef iuCartesianProductHolder6<Generator1, Generator2, Generator3, Generator4, Generator5, Generator6> _Myt;
public:
	iuCartesianProductHolder6(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4), m_g5(g5), m_g6(g6) {}

public:
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4, T5, T6> >* () const 
	{
		return new iuCartesianProductGenerator6<T1, T2, T3, T4, T5, T6>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
			, static_cast< iuIParamGenerator<T5>* >(m_g5)
			, static_cast< iuIParamGenerator<T6>* >(m_g6)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
	const Generator5	m_g5;
	const Generator6	m_g6;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4, typename Generator5
, typename Generator6, typename Generator7>
class iuCartesianProductHolder7
{
	typedef iuCartesianProductHolder7<Generator1, Generator2, Generator3, Generator4, Generator5, Generator6, Generator7> _Myt;
public:
	iuCartesianProductHolder7(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4), m_g5(g5), m_g6(g6), m_g7(g7) {}

public:
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4, T5, T6, T7> >* () const 
	{
		return new iuCartesianProductGenerator7<T1, T2, T3, T4, T5, T6, T7>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
			, static_cast< iuIParamGenerator<T5>* >(m_g5)
			, static_cast< iuIParamGenerator<T6>* >(m_g6)
			, static_cast< iuIParamGenerator<T7>* >(m_g7)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
	const Generator5	m_g5;
	const Generator6	m_g6;
	const Generator7	m_g7;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4, typename Generator5
, typename Generator6, typename Generator7, typename Generator8>
class iuCartesianProductHolder8
{
	typedef iuCartesianProductHolder8<Generator1, Generator2, Generator3, Generator4, Generator5, Generator6, Generator7, Generator8> _Myt;
public:
	iuCartesianProductHolder8(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7, const Generator8& g8)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4), m_g5(g5), m_g6(g6), m_g7(g7), m_g8(g8) {}

public:
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >* () const 
	{
		return new iuCartesianProductGenerator8<T1, T2, T3, T4, T5, T6, T7, T8>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
			, static_cast< iuIParamGenerator<T5>* >(m_g5)
			, static_cast< iuIParamGenerator<T6>* >(m_g6)
			, static_cast< iuIParamGenerator<T7>* >(m_g7)
			, static_cast< iuIParamGenerator<T8>* >(m_g8)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
	const Generator5	m_g5;
	const Generator6	m_g6;
	const Generator7	m_g7;
	const Generator8	m_g8;
};

template<typename Generator1, typename Generator2, typename Generator3, typename Generator4, typename Generator5
, typename Generator6, typename Generator7, typename Generator8, typename Generator9>
class iuCartesianProductHolder9
{
	typedef iuCartesianProductHolder9<Generator1, Generator2, Generator3, Generator4, Generator5, Generator6, Generator7, Generator8, Generator9> _Myt;
public:
	iuCartesianProductHolder9(const Generator1& g1, const Generator2& g2, const Generator3& g3, const Generator4& g4, const Generator5& g5
		, const Generator6& g6, const Generator7& g7, const Generator8& g8, const Generator9& g9)
		: m_g1(g1), m_g2(g2), m_g3(g3), m_g4(g4), m_g5(g5), m_g6(g6), m_g7(g7), m_g8(g8), m_g9(g9) {}

public:
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	operator iuIParamGenerator< tuples::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >* () const 
	{
		return new iuCartesianProductGenerator9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(
			static_cast< iuIParamGenerator<T1>* >(m_g1)
			, static_cast< iuIParamGenerator<T2>* >(m_g2)
			, static_cast< iuIParamGenerator<T3>* >(m_g3)
			, static_cast< iuIParamGenerator<T4>* >(m_g4)
			, static_cast< iuIParamGenerator<T5>* >(m_g5)
			, static_cast< iuIParamGenerator<T6>* >(m_g6)
			, static_cast< iuIParamGenerator<T7>* >(m_g7)
			, static_cast< iuIParamGenerator<T8>* >(m_g8)
			, static_cast< iuIParamGenerator<T9>* >(m_g9)
		);
	}

private:
	void	operator = (const _Myt&) {}
private:
	const Generator1	m_g1;
	const Generator2	m_g2;
	const Generator3	m_g3;
	const Generator4	m_g4;
	const Generator5	m_g5;
	const Generator6	m_g6;
	const Generator7	m_g7;
	const Generator8	m_g8;
	const Generator9	m_g9;
};

#endif

#endif


}	// end of namespace detail
}	// end of namespace iutest

#endif

#endif
