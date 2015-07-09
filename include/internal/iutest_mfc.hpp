//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_mfc.hpp
 * @brief		MFC support
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MFC_HPP_43CC925C_BED2_4D9D_8502_78204B69B675_
#define INCG_IRIS_IUTEST_MFC_HPP_43CC925C_BED2_4D9D_8502_78204B69B675_

//======================================================================
// include
#include <iterator>

namespace iutest {
namespace mfc
{

template<typename T, typename U>
class mfc_iterator : public ::std::iterator < ::std::input_iterator_tag, U >
{
	typedef U Item;
public:
	mfc_iterator(const T& container, POSITION pos) : m_container(container), m_pos(pos) {}
	mfc_iterator(const mfc_iterator& rhs) : m_container(rhs.m_container), m_pos(rhs.m_pos) {}
	
	mfc_iterator& operator ++ ()    { advance(); return *this; }
	mfc_iterator& operator ++ (int) { mfc_iterator r(*this); advance(); return r; }

	Item operator *  () { return m_container.GetAt(m_pos); }
	Item operator -> () { return m_container.GetAt(m_pos); }

	bool operator == (mfc_iterator& rhs) { return rhs.m_pos == m_pos; }
	bool operator != (mfc_iterator& rhs) { return rhs.m_pos != m_pos; }
private:
	void advance()
	{
		__if_exists(T::GetNext) {
			m_container.GetNext(m_pos);
		}
		__if_not_exists(T::GetNext) {
			m_pos++;
		}
	}
private:
	const T& m_container;
	POSITION m_pos;
};

template<typename T, typename U>
mfc_iterator<CList<T, U>, T> begin(CList<T, U>& list)
{
	return mfc_iterator<CList<T, U>, T>(list, list.GetHeadPosition());
}
template<typename T, typename U>
mfc_iterator<CList<T, U>, T> end(CList<T, U>& list)
{
	return mfc_iterator<CList<T, U>, T>(list, NULL);
}

template<typename T, typename U>
T* begin(CArray<T, U>& ar)
{
	return ar.GetData();
}
template<typename T, typename U>
T* end(CArray<T, U>& ar)
{
	return ar.GetData() + ar.GetCount();
}

namespace peep
{

template<typename T>
struct base_type : public T
{ 
	__if_exists(T::BASE_TYPE) { using T::BASE_TYPE; } 
};

}

template<typename T>
typename peep::base_type<T>::BASE_TYPE* begin(T& ar
	, typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetData), void>::type*& = detail::enabler::value)
{
	return ar.GetData();
}
template<typename T>
typename peep::base_type<T>::BASE_TYPE* end(T& ar
	, typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetData), void>::type*& = detail::enabler::value)
{
	return ar.GetData() + ar.GetCount();
}

}	// end of namespace mfc
}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_MFC_HPP_43CC925C_BED2_4D9D_8502_78204B69B675_
