//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        test.cpp
 * @brief       test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include <inttypes.h>

#include "../../include/internal/iutest_compiler.hpp"
#include "../../include/internal/iutest_pp.hpp"

#define PP_CAT  IUTEST_PP_CAT
#define PP_DEC  IUTEST_PP_DEC

namespace detail
{

typedef struct true_type
{
    static const bool value = true;
} true_type;

// false
typedef struct false_type
{
    static const bool value = false;
} false_type;

}   // end of namespace detail

template<bool select, typename YES_T, typename NO_T>
struct type_select
{
    typedef YES_T   type;
};
template<typename YES_T, typename NO_T>
struct type_select<false, YES_T, NO_T>
{
    typedef NO_T    type;
};

template<intmax_t V>
class is_prime_number
{
    static const intmax_t   RECURSIVE_MAX=200;

    template<intmax_t N, intmax_t D1, intmax_t D2, intmax_t Cnt, intmax_t Max>
    struct is_prime_calc_recursive0
    {
        typedef typename type_select<(N%D1==0) || (N%D2==0), detail::false_type
            , typename is_prime_calc_recursive0<N, D1+6, D2+6, Cnt+1, Max>::type>::type type;
        static const intmax_t TMP1 = ((D1)*(D1) > N) ? N : is_prime_calc_recursive0<N, D1+6, D2+6, Cnt+1, Max>::TMP1;
        static const intmax_t TMP2 = ((D2)*(D2) > N) ? N : is_prime_calc_recursive0<N, D1+6, D2+6, Cnt+1, Max>::TMP2;
        typedef char e[ Max ? 1 : -1];
    };
    template<intmax_t N, intmax_t D1, intmax_t Max>
    struct is_prime_calc_recursive0<N, D1, N, Max, Max>
    {
        static const intmax_t   TMP1=D1;
        static const intmax_t   TMP2=N;
        typedef detail::true_type type;
        typedef char e[ Max ? 1 : -1];
    };
    template<intmax_t N, intmax_t D2, intmax_t Max>
    struct is_prime_calc_recursive0<N, N, D2, Max, Max>
    {
        static const intmax_t   TMP1=N;
        static const intmax_t   TMP2=D2;
        typedef detail::true_type type;
        typedef char e[ Max ? 1 : -1];
    };
    template<intmax_t N, intmax_t D1, intmax_t D2, intmax_t Max>
    struct is_prime_calc_recursive0<N, D1, D2, Max, Max>
    {
        static const intmax_t   TMP1= D1;
        static const intmax_t   TMP2= D2;
        typedef detail::true_type type;
        typedef char e[ Max ? 1 : -1];
    };
    template<intmax_t N, intmax_t D1, intmax_t Cnt, intmax_t Max>
    struct is_prime_calc_recursive0<N, D1, N, Cnt, Max>
    {
        static const intmax_t   TMP1=D1;
        static const intmax_t   TMP2=N;
        typedef detail::true_type type;
        typedef char e[ Max ? 1 : -1];
    };
    template<intmax_t N, intmax_t D2, intmax_t Cnt, intmax_t Max>
    struct is_prime_calc_recursive0<N, N, D2, Cnt, Max>
    {
        static const intmax_t   TMP1=N;
        static const intmax_t   TMP2=D2;
        typedef detail::true_type type;
        typedef char e[ Max ? 1 : -1];
    };

#define PRIME_NUMBER_RECURSIVE_IMPL(index)  \
    template<intmax_t N, intmax_t D1, intmax_t D2, intmax_t Cnt, intmax_t Max>  \
    struct is_prime_calc_recursive##index                           \
    {                                                               \
        static const bool value = PP_CAT(is_prime_calc_recursive, PP_DEC(index))<N, D1, D2, 0, Max-Cnt>::type::value;   \
        static const intmax_t TMP1 = PP_CAT(is_prime_calc_recursive, PP_DEC(index))<N, D1, D2, 0, Max-Cnt>::TMP1;       \
        static const intmax_t TMP2 = PP_CAT(is_prime_calc_recursive, PP_DEC(index))<N, D1, D2, 0, Max-Cnt>::TMP2;       \
        typedef typename type_select<value                                                          \
            , typename is_prime_calc_recursive##index<N, TMP1, TMP2, Cnt+1, Max >::type             \
            , detail::false_type >::type type;                                                      \
    };                                                                                              \
    template<intmax_t N, intmax_t D1, intmax_t D2, intmax_t Max>                                    \
    struct is_prime_calc_recursive##index<N, D1, D2, Max, Max>                                      \
    {                                                                                               \
        static const intmax_t   TMP1=D1;                                                            \
        static const intmax_t   TMP2=D2;                                                            \
        typedef detail::true_type type;                                                             \
    };                                                                                              \
    template<intmax_t N, intmax_t D2, intmax_t Cnt, intmax_t Max>                                   \
    struct is_prime_calc_recursive##index<N, N, D2, Cnt, Max>                                       \
    {                                                                                               \
        static const intmax_t   TMP1=N;                                                             \
        static const intmax_t   TMP2=D2;                                                            \
        typedef detail::true_type type;                                                             \
    };                                                                                              \
    template<intmax_t N, intmax_t D1, intmax_t Cnt, intmax_t Max>                                   \
    struct is_prime_calc_recursive##index<N, D1, N, Cnt, Max>                                       \
    {                                                                                               \
        static const intmax_t   TMP1=D1;                                                            \
        static const intmax_t   TMP2=N;                                                             \
        typedef detail::true_type type;                                                             \
    };                                                                                              \
    template<intmax_t N, intmax_t Cnt, intmax_t Max>                                                \
    struct is_prime_calc_recursive##index<N, N, N, Cnt, Max>                                        \
    {                                                                                               \
        static const intmax_t   TMP1=N;                                                             \
        static const intmax_t   TMP2=N;                                                             \
        typedef detail::true_type type;                                                             \
    }

    PRIME_NUMBER_RECURSIVE_IMPL(1);
    PRIME_NUMBER_RECURSIVE_IMPL(2);
    PRIME_NUMBER_RECURSIVE_IMPL(3);
    PRIME_NUMBER_RECURSIVE_IMPL(4);
    PRIME_NUMBER_RECURSIVE_IMPL(5);


#undef PRIME_NUMBER_RECURSIVE_IMPL

#define PRIME_NUMBER_RECURSIVE_LEVEL    5
    template<intmax_t N, intmax_t D1, intmax_t D2>
    struct is_prime_calc_impl
    {
        static const bool value = PP_CAT(is_prime_calc_recursive, PRIME_NUMBER_RECURSIVE_LEVEL)<N, D1, D2, 0, RECURSIVE_MAX>::type::value;
        static const intmax_t TMP1 = PP_CAT(is_prime_calc_recursive, PRIME_NUMBER_RECURSIVE_LEVEL)<N, D1, D2, 0, RECURSIVE_MAX>::TMP1;
        static const intmax_t TMP2 = PP_CAT(is_prime_calc_recursive, PRIME_NUMBER_RECURSIVE_LEVEL)<N, D1, D2, 0, RECURSIVE_MAX>::TMP2;
        typedef typename type_select<value
            , typename is_prime_calc_impl<N, TMP1, TMP2>::type
            , detail::false_type >::type type;
    };
#undef PRIME_NUMBER_RECURSIVE_LEVEL

    template<intmax_t N, intmax_t D1>
    struct is_prime_calc_impl<N, D1, N> { typedef detail::true_type type; };
    template<intmax_t N, intmax_t D2>
    struct is_prime_calc_impl<N, N, D2> { typedef detail::true_type type; };
    template<intmax_t N>
    struct is_prime_calc_impl<N, N, N>  { typedef detail::true_type type; };

    template<intmax_t N, bool isSimpleFilter>
    struct is_prime_impl
    {
        typedef typename type_select<(N%3 == 0), detail::false_type
            , typename type_select<(N%5 == 0), detail::false_type
            , typename is_prime_calc_impl<N, 7, 13>::type >::type >::type type;
    };

    template<bool isSimpleFilter>
    struct is_prime_impl< 5, isSimpleFilter> { typedef detail::true_type type; };
    template<bool isSimpleFilter>
    struct is_prime_impl< 3, isSimpleFilter> { typedef detail::true_type type; };
    template<bool isSimpleFilter>
    struct is_prime_impl< 2, isSimpleFilter> { typedef detail::true_type type; };

    template<intmax_t N>
    struct is_prime_impl<N, false>
    {
        typedef detail::false_type type;
    };

    typedef typename is_prime_impl<V, (V > 1) && (((V&1) == 1) || V == 2) >::type type;
public:
    static const bool value = type::value;
};


namespace detail {
template<bool x>struct static_assert_failer;
template<>struct static_assert_failer<true> { enum { value=1 }; };
template<int x>struct static_assert_test {};
}
#define STATIC_ASSERT(B) \
    typedef detail::static_assert_test< sizeof(detail::static_assert_failer<static_cast<bool>(B)>) > PP_CAT(static_assert_typedef_, __LINE__)

STATIC_ASSERT( is_prime_number<2>::value );
STATIC_ASSERT( is_prime_number<3>::value );
STATIC_ASSERT( is_prime_number<5>::value );
STATIC_ASSERT( is_prime_number<7>::value );
STATIC_ASSERT( is_prime_number<13>::value );
STATIC_ASSERT( is_prime_number<17>::value );
STATIC_ASSERT( is_prime_number<65497>::value );
STATIC_ASSERT( is_prime_number<65491>::value == false );
//STATIC_ASSERT( is_prime_number<16776989>::value );
//STATIC_ASSERT( is_prime_number<37329287>::value );
STATIC_ASSERT( is_prime_number<74746003>::value );
//STATIC_ASSERT( is_prime_number<106591073>::value );
//STATIC_ASSERT( is_prime_number<268435399>::value );
//STATIC_ASSERT( is_prime_number<1073741789>::value );

#ifdef UNICODE
int wmain(int , wchar_t* [])
#else
int main(int , char* [])
#endif
{
    return 0;
}

