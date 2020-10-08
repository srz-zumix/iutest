//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_list.hpp
 * @brief       iris unit test list 構造 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_LIST_HPP_CB5AECEA_6147_4A89_BB97_236338CA177E_
#define INCG_IRIS_IUTEST_LIST_HPP_CB5AECEA_6147_4A89_BB97_236338CA177E_

//======================================================================
// include
#if IUTEST_USE_OWN_LIST
#  ifdef _IUTEST_DEBUG
#    include <assert.h>
#  endif
#else
#  include <list>
#endif

namespace iutest {
namespace detail
{

#if IUTEST_USE_OWN_LIST

//======================================================================
// class
/**
 * @internal
 * @brief   リストノード
*/
template<typename TN>
class iu_list_node
{
    typedef TN *value_ptr;
    typedef iu_list_node<TN> _Myt;
public:
    value_ptr next;
    value_ptr prev;

protected:
    iu_list_node() IUTEST_CXX_NOEXCEPT_SPEC : next(NULL)
        , prev(NULL)
    {}
};

/**
 * @internal
 * @brief   リストイテレータ
*/
template<typename NODE, typename NODE_PTR, typename NODE_REF>
class iu_list_iterator
{
    typedef iu_list_iterator<NODE, NODE_PTR, NODE_REF> _Myt;
public:
    typedef NODE        value_type;
    typedef NODE_PTR    value_ptr;
    typedef NODE_REF    value_ref;
    typedef value_ptr   pointer;
    typedef value_ref   reference;
    typedef int         distance_type;
    typedef int         difference_type;
public:
    value_ptr m_node;
public:
    iu_list_iterator(value_ptr p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_node(p) {}  // NOLINT
    iu_list_iterator(const iu_list_iterator& rhs) IUTEST_CXX_NOEXCEPT_SPEC : m_node(rhs.m_node) {}
    iu_list_iterator& operator = (const iu_list_iterator& rhs) IUTEST_CXX_NOEXCEPT_SPEC
    {
        m_node = rhs.m_node;
        return *this;
    }

public:
    bool operator == (const _Myt& it) const { return this->m_node == it.m_node; }
    bool operator != (const _Myt& it) const { return this->m_node != it.m_node; }

    _Myt&       operator ++ () { m_node = m_node->next; return *this; }
    _Myt&       operator -- () { m_node = m_node->prev; return *this; }
    value_ptr   operator -> () IUTEST_CXX_NOEXCEPT_SPEC { return ptr(); }
    value_ptr   operator *  () IUTEST_CXX_NOEXCEPT_SPEC { return m_node; }
    value_ptr   ptr() const IUTEST_CXX_NOEXCEPT_SPEC { return m_node; }

    operator    value_ptr () { return ptr(); }

    _Myt operator + (int n)
    {
        if( n == 0 )
        {
            return *this;
        }
        if( n > 0 )
        {
            return this->operator +(static_cast<unsigned int>(n));
        }
        _Myt ret(*this);
        n = -n;
        for( int i=0; i < n && ret.m_node != NULL; ++i )
        {
            ret.m_node = ret.m_node->prev;
        }
        return ret;
    }

    _Myt operator + (unsigned int n)
    {
        _Myt ret(*this);
        for( unsigned int i=0; i < n && ret.m_node != NULL; ++i )
        {
            ret.m_node = ret.m_node->next;
        }
        return ret;
    }
};

/**
 * @internal
 * @brief   リストクラス
 * @deprecated stl に変えたほうがいいかも、保守するのがメンドイ
*/
template<typename NODE>
class iu_list
{
    typedef NODE *node_ptr;
    typedef iu_list<NODE> _Myt;
protected:
    node_ptr m_node;

public:
    typedef iu_list_iterator<NODE, NODE*, NODE&> iterator;
    typedef iu_list_iterator<NODE, const NODE*, const NODE&> const_iterator;
public:
    explicit iu_list(node_ptr p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_node(p) {}

public:
    // リストの総数取得
    size_t count() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        size_t cnt = 0;
        node_ptr cur = m_node;
        while(cur != NULL)
        {
            ++cnt;
            cur = cur->next;
        }
        return cnt;
    }
    size_t size() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return count();
    }
    bool empty() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_node == NULL;
    }
public:
    // ソートして挿入
    void sort_insert(node_ptr p)
    {
        if( p == NULL )
        {
            return;
        }

        if( m_node == NULL )
        {
            m_node = p;
            return;
        }

        if( *p < *m_node )
        {
            // 入れ替え
            node_ptr next = m_node;
            m_node = p;
            p->next = next;
            next->prev = p;
        }
        else
        {
            node_ptr prev = m_node;
            node_ptr cur = m_node->next;
            while(cur != NULL)
            {
                if( *p < *cur )
                {
                    break;
                }
                prev = cur;
                cur = prev->next;
            }
            prev->next = p;
            p->prev = prev;
            p->next = cur;
            if( cur != NULL )
            {
                cur->prev = p;
            }
        }
    }
    // 追加
    void push_back(node_ptr p)
    {
        if( p == NULL )
        {
            return;
        }

        if( m_node == NULL )
        {
            m_node = p;
            return;
        }

        node_ptr prev = m_node;
        node_ptr cur = m_node->next;
        while(cur != NULL)
        {
            if( prev == p )
            {
                return;
            }
            prev = cur;
            cur = prev->next;
        }
        prev->next = p;
        p->prev = prev;
    }
    // 削除
    void remove(node_ptr p)
    {
        if( p == NULL )
        {
            return;
        }
        if( m_node == NULL )
        {
            return;
        }
        if( p->prev == NULL )
        {
            m_node = p->next;
            if( m_node != NULL )
            {
                m_node->prev = NULL;
            }
        }
        else
        {
            p->prev->next = p->next;
            if( p->next != NULL )
            {
                p->next->prev = p->prev;
            }
        }
        p->prev = p->next = NULL;
    }
    void erase(iterator it)
    {
        remove(it.ptr());
    }
public:
    /**
     * @brief   シャッフル
     * @tparam  F = 比較オブジェクト
    */
    template<typename F>
    void shuffle(F& r)
    {
        for( unsigned int i=2, n=count(); i<n; ++i )
        {
            swap(begin() + (i-2), begin() + r(i) % i );
        }
    }

public:
    void swap(iterator a, iterator b)
    {
        if( a == b )
        {
            return;
        }
        if( a.ptr() == m_node )
        {
            m_node = b.ptr();
        }
        else if( b.ptr() == m_node )
        {
            m_node = a.ptr();
        }

        if( a->next == b.ptr() )
        {
            a->next = b->next;
            b->next = a.ptr();
            b->prev = a->prev;
            a->prev = b.ptr();
            if( a->next != NULL )
            {
                a->next->prev = a.ptr();
            }
            if( b->prev != NULL )
            {
                b->prev->next = b.ptr();
            }
        }
        else if( a->prev == b.ptr() )
        {
            b->next = a->next;
            a->next = b.ptr();
            a->prev = b->prev;
            b->prev = a.ptr();
            if( b->next != NULL )
            {
                b->next->prev = b.ptr();
            }
            if( a->prev != NULL )
            {
                a->prev->next = a.ptr();
            }
        }
        else
        {
            node_ptr tmp = a->next;
            a->next = b->next;
            b->next = tmp;
            tmp = a->prev;
            a->prev = b->prev;
            b->prev = tmp;
            if( a->next != NULL )
            {
                a->next->prev = a.ptr();
            }
            if( b->next != NULL )
            {
                b->next->prev = b.ptr();
            }
            if( a->prev != NULL )
            {
                a->prev->next = a.ptr();
            }
            if( b->prev != NULL )
            {
                b->prev->next = b.ptr();
            }
        }
    }

public:
    iterator begin() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_node;
    }
    iterator end() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return iterator(NULL);
    }
    const_iterator begin() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_node;
    }
    const_iterator end() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return const_iterator(NULL);
    }


public:
    struct EqualOp
    {
        template<typename T>
        bool operator () (const T* lhs, const T* rhs) const { return *lhs == *rhs; }
    };
public:
    template<typename FUNC>
    node_ptr find(node_ptr p, FUNC& f) const
    {
        node_ptr cur = m_node;
        while( cur != NULL )
        {
            if( f(cur, p) )
            {
                return cur;
            }
            cur = cur->next;
        }
        return NULL;
    }
    template<typename FUNC>
    node_ptr find(FUNC& f) const
    {
        node_ptr cur = m_node;
        while( cur != NULL )
        {
            if( f(cur) )
            {
                return cur;
            }
            cur = cur->next;
        }
        return NULL;
    }

public:
    node_ptr    operator -> () { return m_node; }
    node_ptr    operator &  () { return m_node; }   // NOLINT
    NODE&       operator *  () { return *m_node; }

    node_ptr    operator [] (int index) const
    {
        node_ptr cur = m_node;
        for( int i=0; i < index; ++i )
        {
            cur = cur->next;
            if( cur == NULL )
            {
                break;
            }
        }
        return cur;
    }

    bool operator == (node_ptr p) const { return m_node == p; }
    bool operator != (node_ptr p) const { return m_node != p; }

private:
#ifdef _IUTEST_DEBUG
    // ノードの状態チェック
    bool check_node()
    {
        if( m_node == NULL )
        {
            return true;
        }
        node_ptr prev = m_node;
        node_ptr curr = prev->next;
        while( curr != NULL )
        {
            assert( prev->next == curr );
            assert( curr->prev == prev );
            prev = curr;
            curr = prev->next;
        }
        return true;
    }
#endif
};

#endif


IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE()

/**
 * @brief   vector シャッフル
*/
template<typename It>
void RandomShuffle(It begin, It last, iuRandom& r)
{
    r.shuffle(begin, last);
}
#if IUTEST_USE_OWN_LIST
template<typename Node, typename Fn>
void RandomShuffle(iu_list<Node>& list, Fn& r)
{
    list.shuffle(r);
}
#endif
template<typename T, typename Fn>
void RandomShuffle(::std::vector<T>& list, Fn& r)
{
    RandomShuffle(list.begin(), list.end(), r);
}

#if IUTEST_USE_OWN_LIST
template<typename Node, typename Fn>
Node* FindList(const iu_list<Node>& list, Fn& f)
{
    return list.find(f);
}
#else
template<typename T, typename Fn>
T FindList(const ::std::vector<T>& list, Fn& f)
{
    for(typename ::std::vector<T>::const_iterator it = list.begin(), end = list.end(); it != end; ++it)
    {
        if(f(*it))
        {
            return *it;
        }
    }
    return NULL;
}
#endif


/**
 * @brief   条件に合う要素数をカウント
*/
#if IUTEST_USE_OWN_LIST

template<typename Node, typename Fn>
int CountIf(const iu_list<Node>& list, Fn f)
{
    int count = 0;
    for( typename iu_list<Node>::const_iterator it = list.begin(), end=list.end(); it != end; ++it )
    {
        if( f(*it) )
        {
            ++count;
        }
    }
    return count;
}

#else

template<typename T, typename Fn>
int CountIf(const ::std::vector<T>& list, Fn f)
{
    int count = 0;
    for(typename ::std::vector<T>::const_iterator it = list.begin(), end = list.end(); it != end; ++it)
    {
        if(f(*it))
        {
            ++count;
        }
    }
    return count;
}

#endif


/**
 * @brief   リストの示す値の総和
*/
#if IUTEST_USE_OWN_LIST

template<typename Node, typename Fn>
int SumOverList(const iu_list<Node>& list, Fn f)
{
    int count = 0;
    for( typename iu_list<Node>::const_iterator it = list.begin(), end=list.end(); it != end; ++it )
    {
        count += ((*it)->*f)();
    }
    return count;
}

#else

template<typename T, typename Fn>
int SumOverList(const ::std::vector<T>& list, Fn f)
{
    int count = 0;
    for(typename ::std::vector<T>::const_iterator it = list.begin(), end = list.end(); it != end; ++it)
    {
        count += ((*it)->*f)();
    }
    return count;
}

#endif


/**
 * @brief   リストの示す真の総和
*/
#if IUTEST_USE_OWN_LIST

template<typename Node, typename Fn>
int CountIfOverList(const iu_list<Node>& list, Fn f)
{
    int count = 0;
    for( typename iu_list<Node>::const_iterator it = list.begin(), end=list.end(); it != end; ++it )
    {
        if( ((*it)->*f)() )
        {
            ++count;
        }
    }
    return count;
}

#else

template<typename T, typename Fn>
int CountIfOverList(const ::std::vector<T>& list, Fn f)
{
    int count = 0;
    for(typename ::std::vector<T>::const_iterator it = list.begin(), end = list.end(); it != end; ++it)
    {
        if(((*it)->*f)())
        {
            ++count;
        }
    }
    return count;
}

#endif

/**
 * @brief   条件に合う要素があるかどうか
*/
#if IUTEST_USE_OWN_LIST

template<typename Node, typename Fn>
bool AnyOverList(const iu_list<Node>& list, Fn f)
{
    for( typename iu_list<Node>::const_iterator it = list.begin(), end=list.end(); it != end; ++it )
    {
        if( ((*it)->*f)() )
        {
            return true;
        }
    }
    return false;
}

#else

template<typename T, typename Fn>
bool AnyOverList(const ::std::vector<T>& list, Fn f)
{
    for(typename ::std::vector<T>::const_iterator it = list.begin(), end = list.end(); it != end; ++it)
    {
        if(((*it)->*f)())
        {
            return true;
        }
    }
    return false;
}

#endif

IUTEST_PRAGMA_WARN_POP()

}   // end of namespace detail
}   // end of namespace iutest


#endif // INCG_IRIS_IUTEST_LIST_HPP_CB5AECEA_6147_4A89_BB97_236338CA177E_
