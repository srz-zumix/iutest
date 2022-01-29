﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_any.hpp
 * @brief       iris unit test any object
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ANY_HPP_8DB2417F_568A_4E01_95AD_21164565B975_
#define INCG_IRIS_IUTEST_ANY_HPP_8DB2417F_568A_4E01_95AD_21164565B975_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "internal/iutest_internal_defs.hpp"
// IWYU pragma: end_exports

//======================================================================
// class
namespace iutest
{

/**
 * @brief   any
*/
class any
{
    typedef internal::TypeId type_id;
public:
    any() IUTEST_CXX_NOEXCEPT_SPEC : content(IUTEST_NULLPTR) {}
    template<typename T>
    any(const T& rhs) : content(new holder<T>(rhs)) {}  // NOLINT
    any(const any& rhs) : content(rhs.content == IUTEST_NULLPTR ? IUTEST_NULLPTR : rhs.content->clone()) {}
    any(const char rhs[]) : content(new holder< ::std::string >(::std::string(rhs)) ) {}  // NOLINT
    ~any() { delete content; }
public:
    /**
     * @brief   swap
    */
    any& swap(any& rhs) IUTEST_CXX_NOEXCEPT_SPEC
    {
        ::std::swap(content, rhs.content);
        return *this;
    }
    /**
     * @brief   空かどうか
     * @retval  true = 空
    */
    bool empty() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return content == IUTEST_NULLPTR;
    }
    /**
     * @brief   要素のクリア
    */
    void clear() IUTEST_CXX_NOEXCEPT_SPEC
    {
        any().swap(*this);
    }
    /**
     * @brief   型IDの取得
     * @return  型ID
    */
    type_id type() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return content == IUTEST_NULLPTR ? internal::GetTypeId<void>() : content->type();
    }
    /**
     * @brief   型の比較
     * @retval  true = 同一
    */
    template<typename T>
    bool type_equal() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return type() == internal::GetTypeId<T>();
    }

    /**
     * @brief   所持している値の文字列化
    */
    ::std::string to_string() const
    {
        if(empty())
        {
            return "empty";
        }
        return content->to_string();
    }

public:
    /**
     * @brief   要素があるかどうか
    */
    bool has_value() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return !empty();
    }
    /**
    * @brief   要素のクリア
    */
    void reset()
    {
        clear();
    }

public:
    template<typename T>
    any& operator = (const   T& rhs) { any(rhs).swap(*this); return *this; }
    any& operator = (const any& rhs) { any(rhs).swap(*this); return *this; }

    template<typename T>
    friend T* any_cast(any*);
    template<typename T>
    friend T* unsafe_any_cast(any*) IUTEST_CXX_NOEXCEPT_SPEC;

private:
    class placeholder
    {
    public:
        virtual ~placeholder() {}
        virtual type_id type() const IUTEST_CXX_NOEXCEPT_SPEC = 0;
        virtual placeholder* clone() const = 0;
        virtual ::std::string to_string() const = 0;
    };
    template<typename T>
    class holder IUTEST_CXX_FINAL : public placeholder
    {
    public:
        explicit holder(const T& v) IUTEST_CXX_NOEXCEPT_SPEC : held(v) {}
    public:
        virtual type_id type() const IUTEST_CXX_NOEXCEPT_SPEC IUTEST_CXX_OVERRIDE
        {
            return internal::GetTypeId<T>();
        }
        virtual placeholder* clone() const IUTEST_CXX_OVERRIDE
        {
            return new holder<T>(held);
        }
        virtual ::std::string to_string() const IUTEST_CXX_OVERRIDE
        {
            return PrintToString(held);
        }
    public:
        T held;
    private:
        holder& operator = (const holder&);
    };
private:
    placeholder* content;
};

#if IUTEST_HAS_EXCEPTIONS
/**
 * @brief   any_cast の失敗例外
*/
class bad_any_cast : public ::std::bad_cast {};
#endif

inline void swap(any& lhs, any& rhs) { lhs.swap(rhs); }

/**
 * @brief   型を考慮したキャスト
*/
template<typename T>
T* any_cast(any* p)
{
    return p != IUTEST_NULLPTR && p->type_equal<T>() ?
        &(static_cast< any::holder<T>* >(p->content)->held) : IUTEST_NULLPTR;
}
/** @overload */
template<typename T>
inline const T* any_cast(const any* p)
{
    return any_cast<T>(const_cast<any*>(p));
}
/** @overload */
template<typename T>
inline T any_cast(any& value)
{
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename type_traits::remove_reference<T>::type nonref_t;
#else
    typedef T nonref_t;
#endif
    nonref_t* p = any_cast<nonref_t>(&value);
#if IUTEST_HAS_EXCEPTIONS
    if( p == IUTEST_NULLPTR )
    {
        throw bad_any_cast();
    }
#endif

    return static_cast<nonref_t&>(*p);
}
/** @overload */
template<typename T>
inline T any_cast(const any& value)
{
    return any_cast<T>(const_cast<any&>(value));
}

/**
 * @brief   型を考慮せずキャスト
*/
template<typename T>
T* unsafe_any_cast(any* p) IUTEST_CXX_NOEXCEPT_SPEC
{
    if( p == IUTEST_NULLPTR )
    {
        return IUTEST_NULLPTR;
    }
    if( !p->has_value() )
    {
        return IUTEST_NULLPTR;
    }
    IUTEST_ATTRIBUTE_GSL_SUPPRESS(type.2)
    return &(static_cast< any::holder<T>* >(p->content)->held);
}
/** @overload */
template<typename T>
inline const T* unsafe_any_cast(const any* p) IUTEST_CXX_NOEXCEPT_SPEC
{
    return unsafe_any_cast<T>(const_cast<any*>(p));
}
/** @overload */
template<typename T>
inline T unsafe_any_cast(any& value) IUTEST_CXX_NOEXCEPT_SPEC
{
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    typedef typename type_traits::remove_reference<T>::type nonref_t;
#else
    typedef T nonref_t;
#endif
    nonref_t* p = unsafe_any_cast<nonref_t>(&value);
    return static_cast<nonref_t&>(*p);
}
/** @overload */
template<typename T>
inline T unsafe_any_cast(const any& value) IUTEST_CXX_NOEXCEPT_SPEC
{
    return unsafe_any_cast<T>(const_cast<any&>(value));
}

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
template<typename Elem, typename Traits>
inline ::std::basic_ostream<Elem, Traits>& operator << (::std::basic_ostream<Elem, Traits>& os, const any& value)
{
    return os << value.to_string();
}
#else
inline iu_ostream& operator << (iu_ostream& os, const any& value)
{
    return os << value.to_string();
}
#endif

#endif

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_ANY_HPP_8DB2417F_568A_4E01_95AD_21164565B975_
