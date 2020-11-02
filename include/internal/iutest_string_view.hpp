//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_string_view.hpp
 * @brief       string_view
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STRING_VIEW_HPP_46AEE8A4_996C_4925_ACBA_2A511909B38F_
#define INCG_IRIS_IUTEST_STRING_VIEW_HPP_46AEE8A4_996C_4925_ACBA_2A511909B38F_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_defs.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
#  include <string_view>
#endif

#if IUTEST_HAS_EXCEPTIONS
#  include <stdexcept>
#endif
#include <climits>

//======================================================================
// class

namespace iutest {
namespace detail
{

#if !IUTEST_USE_OWN_STRING_VIEW

template<typename CharT, typename Traits = ::std::char_traits<CharT> >
using iu_basic_string_view = ::std::basic_string_view<CharT, Traits>;

#else

template <class CharT, class Traits = ::std::char_traits<CharT> >
class iu_basic_string_view;

template<typename CharT, typename Traits>
class iu_basic_string_view
{
public:
    typedef Traits  traits_type;
    typedef CharT   value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    //typedef pointer const_iterator;
    //typedef const_iterator iterator;
    //typedef pointer const_reverse_iterator;
    //typedef const_reverse_iterator reverse_iterator;
    typedef size_t size_type;
    typedef ::std::ptrdiff_t difference_type;

public:
    static const size_type npos = static_cast<size_type >(-1);

private:
    static const size_type size_type_max = static_cast<size_type>(
#if defined(PTRDIFF_MAX)
        PTRDIFF_MAX
#else
        INT_MAX
#endif
    );

public:
    IUTEST_CXX_CONSTEXPR iu_basic_string_view() IUTEST_CXX_NOEXCEPT_SPEC
        : m_data(IUTEST_NULLPTR)
        , m_size(0)
    {
    }
    IUTEST_CXX_CONSTEXPR iu_basic_string_view(const_pointer str)
        : m_data(str)
        , m_size(traits_type::length(str))
    {
    }
    IUTEST_CXX_CONSTEXPR iu_basic_string_view(const_pointer str, size_type len)
        : m_data(str)
        , m_size(len)
    {
    }
#if IUTEST_HAS_DEFAULT_FUNCTIONS
    IUTEST_CXX_CONSTEXPR iu_basic_string_view(const iu_basic_string_view&) IUTEST_CXX_NOEXCEPT_SPEC = default;
#else
    IUTEST_CXX_CONSTEXPR iu_basic_string_view(const iu_basic_string_view& rhs) IUTEST_CXX_NOEXCEPT_SPEC
        : m_data(rhs.m_data)
        , m_size(rhs.m_size)
    {
    }
#endif

    template<size_t N>
    iu_basic_string_view(value_type(&str)[N]) // NOLINT
        : m_data(str)
        , m_size(N)
    {
    }

    template<typename Allocator>
    iu_basic_string_view(const ::std::basic_string<value_type, traits_type, Allocator>& str) // NOLINT
        : m_data(str.data())
        , m_size(str.length())
    {
    }

    ~iu_basic_string_view() IUTEST_CXX_DEFAULT_FUNCTION

public:
#if IUTEST_HAS_DEFAULT_FUNCTIONS
    iu_basic_string_view& operator=(const iu_basic_string_view&) = default;
#if IUTEST_HAS_MOVE_ASSIGNMENT_DEFAULT_FUNCTION
    iu_basic_string_view& operator=(iu_basic_string_view&&) = default;
#endif
#else
    iu_basic_string_view& operator=(const iu_basic_string_view& rhs)
    {
        m_data = rhs.m_data;
        m_size = rhs.m_size;
        return *this;
    }
#endif

public:
    IUTEST_CXX_CONSTEXPR size_type size() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_size;
    }
    IUTEST_CXX_CONSTEXPR size_type length() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_size;
    }
    IUTEST_CXX_CONSTEXPR size_type max_size() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return (::std::min)(size_type_max, static_cast<size_type>(-1) / sizeof(value_type));
    }
    IUTEST_CXX_CONSTEXPR bool empty() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_size == 0;
    }

public:
    IUTEST_CXX_CONSTEXPR const_reference operator[](size_type pos) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_data[pos];
    }
    IUTEST_CXX14_CONSTEXPR const_reference at(size_type pos) const
    {
        offset_exclusive(pos);
        return m_data[pos];
    }
    IUTEST_CXX_CONSTEXPR const_reference front() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_data[0];
    }
    IUTEST_CXX_CONSTEXPR const_reference back() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_data[0];
    }
    IUTEST_CXX_CONSTEXPR const_pointer data() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_data;
    }

public:
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST()

    IUTEST_CXX14_CONSTEXPR void remove_prefix(size_type n) IUTEST_CXX_NOEXCEPT_SPEC
    {
        m_data += n;
        m_size -= n;
    }

    IUTEST_CXX14_CONSTEXPR void remove_suffix(size_type n) IUTEST_CXX_NOEXCEPT_SPEC
    {
        m_size -= n;
    }

    IUTEST_CXX14_CONSTEXPR void swap(iu_basic_string_view & other) IUTEST_CXX_NOEXCEPT_SPEC
    {
        const iu_basic_string_view tmp = { other };
        other = *this;
        *this = other;
    }

IUTEST_PRAGMA_WARN_POP()

public:
    size_type copy(pointer s, size_type n, size_type pos = 0) const
    {
        offset_exclusive(pos);
        const size_type count = clamp_suffix_size(pos, n);
        traits_type::copy(s, m_data + pos, count);
        return count;
    }

    IUTEST_CXX14_CONSTEXPR iu_basic_string_view substr(size_type pos = 0, size_type n = npos) const
    {
        offset_exclusive(pos);
        const size_type count = clamp_suffix_size(pos, n);
        return iu_basic_string_view(m_data + pos, count);
    }


public:
    IUTEST_CXX_CONSTEXPR bool equal(iu_basic_string_view sv) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_size == sv.m_size && (traits_type::compare(m_data, sv.m_data, m_size) == 0);
    }

public:
    IUTEST_CXX14_CONSTEXPR int compare(iu_basic_string_view sv) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        {
            const size_type count = (::std::min)(m_size, sv.m_size);
            const int result = traits_type::compare(m_data, sv.m_data, count);
            if( result != 0 )
            {
                return result;
            }
        }
        if( m_size < sv.m_size )
        {
            return -1;
        }
        if( m_size > sv.m_size )
        {
            return 1;
        }
        return 0;
    }

    IUTEST_CXX_CONSTEXPR int compare(size_type pos1, size_type n1, iu_basic_string_view sv) const
    {
        return substr(pos1, n1).compare(sv);
    }

    IUTEST_CXX_CONSTEXPR int compare(size_type pos1, size_type n1, iu_basic_string_view sv, size_type pos2, size_type n2) const
    {
        return substr(pos1, n1).compare(sv.substr(pos2, n2));
    }

    IUTEST_CXX_CONSTEXPR int compare(const_pointer s) const
    {
        return compare(basic_string_view(s));
    }

    IUTEST_CXX_CONSTEXPR int compare(size_type pos1, size_type n1, const_pointer s) const
    {
        return substr(pos1, n1).compare(basic_string_view(s));
    }

    IUTEST_CXX_CONSTEXPR int compare(size_type pos1, size_type n1, const_pointer s, size_type n2) const
    {
        return substr(pos1, n1).compare(basic_string_view(s, n2));
    }

public:
    IUTEST_CXX_CONSTEXPR bool starts_with(iu_basic_string_view x) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return compare(0, npos, x) == 0;
    }
    IUTEST_CXX_CONSTEXPR bool starts_with(value_type x) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return starts_with(iu_basic_string_view(&x, 1));
    }
    IUTEST_CXX_CONSTEXPR bool starts_with(const_pointer x) const
    {
        return starts_with(iu_basic_string_view(x));
    }

    IUTEST_CXX_CONSTEXPR bool ends_with(iu_basic_string_view x) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_size >= x.m_size && compare(m_size - x.m_size, npos, x) == 0;
    }
    IUTEST_CXX_CONSTEXPR bool ends_with(value_type x) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return ends_with(iu_basic_string_view(&x, 1));
    }
    IUTEST_CXX_CONSTEXPR bool ends_with(const_pointer x) const
    {
        return ends_with(iu_basic_string_view(x));
    }

public:
    IUTEST_CXX14_CONSTEXPR size_type find(iu_basic_string_view sv, size_type pos = 0) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        if( (sv.m_size > m_size) || (pos > m_size - sv.m_size) )
        {
            return npos;
        }
        if( sv.m_size == 0 )
        {
            return pos;
        }
        const_pointer end = m_data + (m_size - sv.m_size) + 1;
        for( const_pointer top = m_data + pos; ; ++top )
        {
            top = traits_type::find(top, static_cast<size_type>(end - top), sv[0]);
            if( !top )
            {
                return npos;
            }

            if( traits_type::compare(top, sv.m_data, sv.m_size) == 0 )
            {
                return static_cast<size_type>(top - m_data);
            }
        }
    }
    IUTEST_CXX14_CONSTEXPR size_type find(value_type c, size_type pos = 0) const IUTEST_CXX_NOEXCEPT_SPEC
    {
        if( pos < m_size )
        {
            const_pointer find = traits_type::find(m_data + pos, m_size, c);
            if( find != IUTEST_NULLPTR )
            {
                return static_cast<size_type>(find - m_data);
            }
        }
        return npos;
    }

    IUTEST_CXX_CONSTEXPR size_type find(const_pointer s, size_type pos, size_type n) const
    {
        return find(iu_basic_string_view(s, n), pos);
    }
    IUTEST_CXX_CONSTEXPR size_type find(const_pointer s, size_type pos = 0) const
    {
        return find(iu_basic_string_view(s), pos);
    }

public:
    //IUTEST_CXX_CONSTEXPR size_type rfind(iu_basic_string_view s, size_type pos = npos) const IUTEST_CXX_NOEXCEPT_SPEC
    //{
    //    if( s.m_size == 0 )
    //    {
    //        return (::std::min)(pos, m_size);
    //    }
    //    if( m_size >= sv.m_size )
    //    {
    //    }
    //    return npos;
    //}
    //IUTEST_CXX_CONSTEXPR size_type rfind(value_type c, size_type pos = npos) const IUTEST_CXX_NOEXCEPT_SPEC;
    //IUTEST_CXX_CONSTEXPR size_type rfind(const_pointer s, size_type pos, size_type n) const
    //{
    //    return rfind(iu_basic_string_view(s, n), pos);
    //}
    //IUTEST_CXX_CONSTEXPR size_type rfind(const_pointer s, size_type pos = npos) const
    //{
    //    return rfind(iu_basic_string_view(s), pos);
    //}

private:
    size_type clamp_suffix_size(size_type pos, size_type n) const
    {
        return (::std::min)(n, m_size - pos);
    }

    void offset_exclusive(size_type pos) const
    {
        if( pos >= m_size )
        {
            out_of_range();
        }
    }

    void out_of_range() const
    {
#if IUTEST_HAS_EXCEPTIONS
        throw new ::std::out_of_range("invalid string_view position");
#endif
    }

public:
    friend bool operator == (const iu_basic_string_view lhs, const iu_basic_string_view& rhs)
    {
        return lhs.equal(rhs);
    }
    friend bool operator != (const iu_basic_string_view lhs, const iu_basic_string_view& rhs)
    {
        return !lhs.equal(rhs);
    }

private:
    const_pointer m_data;
    size_type m_size;
};

#endif

template<typename CharT, typename Traits = ::std::char_traits<CharT> >
class iu_nullable_basic_string_view : public iu_basic_string_view<CharT, Traits>
{
public:
    typedef iu_basic_string_view<CharT, Traits> _Mybase;
    typedef Traits  traits_type;
    typedef CharT   value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef size_t size_type;
public:
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view() IUTEST_CXX_NOEXCEPT_SPEC IUTEST_CXX_DEFAULT_FUNCTION
#if IUTEST_HAS_NULLPTR
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view(::std::nullptr_t)
        : _Mybase(IUTEST_NULLPTR, 0)
    {
    }
#endif
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view(const_pointer str)
        : _Mybase(str, str ? traits_type::length(str) : 0)
    {
    }
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view(const_pointer str, size_type len)
        : _Mybase(str, len)
    {
    }
#if IUTEST_HAS_DEFAULT_FUNCTIONS
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view(const iu_nullable_basic_string_view&) IUTEST_CXX_NOEXCEPT_SPEC = default;
#else
    IUTEST_CXX_CONSTEXPR iu_nullable_basic_string_view(const iu_nullable_basic_string_view& rhs) IUTEST_CXX_NOEXCEPT_SPEC
        : _Mybase(rhs)
    {
    }
#endif

    template<size_t N>
    iu_nullable_basic_string_view(value_type(&str)[N]) // NOLINT
        : _Mybase(str, N)
    {
    }

    iu_nullable_basic_string_view(const _Mybase& str_view) // NOLINT
        : _Mybase(str_view)
    {
    }

    template<typename Allocator>
    iu_nullable_basic_string_view(const ::std::basic_string<value_type, traits_type, Allocator>& str) // NOLINT
        : _Mybase(str.data(), str.length())
    {
    }
};


typedef iu_basic_string_view<char>      iu_string_view;
typedef iu_basic_string_view<wchar_t>   iu_wstring_view;


}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STRING_VIEW_HPP_46AEE8A4_996C_4925_ACBA_2A511909B38F_
