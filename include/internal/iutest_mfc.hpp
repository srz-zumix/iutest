//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_mfc.hpp
 * @brief       MFC support
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2019, Takazumi Shirayanagi\n
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

/**
 * @brief mfc container iterator
*/
template<typename T, typename U>
class mfc_iterator : public ::std::iterator < ::std::input_iterator_tag, U >
{
    typedef typename iutest_type_traits::add_const_to_pointer<U>::type Item;
public:
    mfc_iterator(const T& container, POSITION pos) : m_container(container), m_pos(pos) {}
    mfc_iterator(const mfc_iterator& rhs) : m_container(rhs.m_container), m_pos(rhs.m_pos) {}

    mfc_iterator& operator = (const mfc_iterator& rhs) { m_container = rhs.m_container; m_pos = m_pos; return *this; }

    mfc_iterator& operator ++ ()    { advance(); return *this; }
    mfc_iterator& operator ++ (int) { mfc_iterator r(*this); advance(); return r; }

    Item operator *  () const { return m_container.GetAt(m_pos); }
    Item operator -> () const { return m_container.GetAt(m_pos); }

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

/**
 * @brief mfc map container iterator
*/
template<typename T, typename Key, typename Value>
class mfc_map_iterator : public ::std::iterator < ::std::input_iterator_tag, ::std::pair<Key, Value> >
{
    typedef ::std::pair<Key, Value> Item;
public:
    mfc_map_iterator(const T& container, POSITION pos) : m_container(container), m_pos(pos) {}
    mfc_map_iterator(const mfc_map_iterator& rhs) : m_container(rhs.m_container), m_pos(rhs.m_pos) {}

    mfc_map_iterator& operator = (const mfc_map_iterator& rhs) { m_container = rhs.m_container; m_pos = m_pos; return *this; }

    mfc_map_iterator& operator ++ ()    { advance(); return *this; }
    mfc_map_iterator& operator ++ (int) { mfc_iterator r(*this); advance(); return r; }

    Item operator *  () const { return m_pair; }
    Item operator -> () const { return m_pair; }

    bool operator == (mfc_map_iterator& rhs) { return rhs.m_pos == m_pos; }
    bool operator != (mfc_map_iterator& rhs) { return rhs.m_pos != m_pos; }
private:
    void advance()
    {
        __if_exists(T::GetNextAssoc) {
            m_container.GetNextAssoc(m_pos, m_pair.first, m_pair.second);
        }
    }

private:
    const T& m_container;
    POSITION m_pos;
    ::std::pair<Key, Value> m_pair;
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

template<typename T, typename TA, typename U, typename UA>
mfc_map_iterator< CMap<T, TA, U, UA>, T, U > begin(CMap<T, TA, U, UA>& map)
{
    return mfc_map_iterator< CMap<T, TA, U, UA>, T, U >(map, map.GetStartPosition());
}

template<typename T, typename TA, typename U, typename UA>
mfc_map_iterator< CMap<T, TA, U, UA>, T, U > end(CMap<T, TA, U, UA>& map)
{
    return mfc_map_iterator< CMap<T, TA, U, UA>, T, U >(map, NULL);
}

namespace peep
{

template<typename T>
struct base_type : public T
{
    __if_exists(T::BASE_TYPE)
    {
        using T::BASE_TYPE;
        typedef typename T::BASE_TYPE BASE_KEY;
        typedef typename T::BASE_TYPE BASE_VALUE;
    }

    __if_not_exists(T::BASE_TYPE)
    {
        __if_exists(T::BASE_KEY)
        {
            __if_exists(T::BASE_VALUE)
            {
                using T::BASE_KEY;
                using T::BASE_VALUE;
                typedef ::std::pair<T::BASE_KEY, T::BASE_VALUE> BASE_TYPE;
            }
        }
    }
};
template<typename T, typename U>
struct base_type< CArray<T, U> >
{
    typedef T BASE_TYPE;
    typedef T BASE_KEY;
    typedef T BASE_VALUE;
};
template<typename BASE_CLASS, typename T>
struct base_type< CTypedPtrArray<BASE_CLASS, T> >
{
    typedef T BASE_TYPE;
    typedef T BASE_KEY;
    typedef T BASE_VALUE;
};
template<typename T, typename U>
struct base_type< CList<T, U> >
{
    typedef T BASE_TYPE;
    typedef T BASE_KEY;
    typedef T BASE_VALUE;
};
template<typename BASE_CLASS, typename T>
struct base_type< CTypedPtrList<BASE_CLASS, T> >
{
    typedef T BASE_TYPE;
    typedef T BASE_KEY;
    typedef T BASE_VALUE;
};
template<typename T, typename TA, typename U, typename UA>
struct base_type< CMap<T, TA, U, UA> >
{
    typedef ::std::pair<T, U> BASE_TYPE;
    typedef T BASE_KEY;
    typedef U BASE_VALUE;
};
template<typename BASE_CLASS, typename KEY, typename VALUE>
struct base_type< CTypedPtrMap<BASE_CLASS, KEY, VALUE> >
{
    typedef ::std::pair<KEY, VALUE> BASE_TYPE;
    typedef KEY BASE_KEY;
    typedef VALUE BASE_VALUE;
};

template<typename T>
struct mfc_iterator_traits
{
    typedef typename base_type<T>::BASE_TYPE BASE_TYPE;
    typedef typename base_type<T>::BASE_KEY BASE_KEY;
    typedef typename base_type<T>::BASE_VALUE BASE_VALUE;
    template<typename U, bool isArray, bool isList>
    struct type_select
    {
        typedef mfc_map_iterator<T, BASE_KEY, BASE_VALUE> type;
    };
    template<typename U>
    struct type_select<U, true, false>
    {
        typedef U* type;
    };
    template<typename U>
    struct type_select<U, false, true>
    {
        typedef mfc_iterator<T, U> type;
    };
    typedef typename type_select<BASE_TYPE
        , IUTEST_STATIC_EXISTS(T::GetData)
        , IUTEST_STATIC_EXISTS(T::GetHeadPosition)
    >::type type;
};

}   // end of namespace peep

template<typename T>
typename peep::base_type<T>::BASE_TYPE* begin(T& ar
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetData), void>::type*& = detail::enabler::value)
{
    return reinterpret_cast<typename peep::base_type<T>::BASE_TYPE*>(ar.GetData());
}
template<typename T>
typename peep::base_type<T>::BASE_TYPE* end(T& ar
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetData), void>::type*& = detail::enabler::value)
{
    return reinterpret_cast<typename peep::base_type<T>::BASE_TYPE*>(ar.GetData() + ar.GetCount());
}

template<typename T>
mfc_iterator<T, typename peep::base_type<T>::BASE_TYPE> begin(T& list
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetHeadPosition), void>::type*& = detail::enabler::value)
{
    return mfc_iterator<T, peep::base_type<T>::BASE_TYPE>(list, list.GetHeadPosition());
}
template<typename T>
mfc_iterator<T, typename peep::base_type<T>::BASE_TYPE> end(T& list
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetHeadPosition), void>::type*& = detail::enabler::value)
{
    return mfc_iterator<T, peep::base_type<T>::BASE_TYPE>(list, NULL);
}

template<typename T>
typename peep::mfc_iterator_traits<T>::type begin(T& map
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetStartPosition), void>::type*& = detail::enabler::value)
{
    return typename peep::mfc_iterator_traits<T>::type(map, map.GetStartPosition());
}
template<typename T>
typename peep::mfc_iterator_traits<T>::type end(T& map
    , typename detail::enable_if< IUTEST_STATIC_EXISTS(T::GetStartPosition), void>::type*& = detail::enabler::value)
{
    return typename peep::mfc_iterator_traits<T>::type(map, NULL);
}

/**
 * @brief   provide begin/end in mfc container
*/
template<typename T>
class CContainer
{
public:
    /**
     * @private
     * @{
    */
    typedef typename peep::base_type<T>::BASE_TYPE BASE_TYPE;
    typedef typename peep::base_type<T>::BASE_KEY BASE_KEY;
    typedef typename peep::base_type<T>::BASE_VALUE BASE_VALUE;
    typedef typename peep::mfc_iterator_traits<T>::type iterator_type;
    /**
     * @}
    */
public:
    explicit CContainer(T& container) : m_container(container) {}

    iterator_type begin() const { return mfc::begin(m_container); }
    iterator_type end() const { return mfc::end(m_container); }

private:
    T& m_container;
};

/**
 * @brief   make mfc container
*/
template<typename T>
CContainer<T> make_container(T& obj) { return CContainer<T>(obj); }

}   // end of namespace mfc
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_MFC_HPP_43CC925C_BED2_4D9D_8502_78204B69B675_
