//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_gmock.hpp
 * @brief       gmock 切り替え定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_GMOCK_HPP_4212321D_F709_4904_AAF7_5E1BE18C0947_
#define INCG_IRIS_IUTEST_SWITCH_GMOCK_HPP_4212321D_F709_4904_AAF7_5E1BE18C0947_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define

#else // !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#if defined(INCG_IRIS_IUTEST_HPP_)

#undef IUTEST_ASSERT_THAT
#undef IUTEST_EXPECT_THAT
#undef IUTEST_INFORM_THAT
#undef IUTEST_ASSUME_THAT

#undef IUTEST_HAS_MATCHERS
#undef IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
#undef IUTEST_HAS_MATCHER_ELEMENTSARE
#undef IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD
#undef IUTEST_HAS_MATCHER_REGEX
#undef IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR
#undef IUTEST_HAS_MATCHER_EACH
#undef IUTEST_HAS_MATCHER_POINTWISE
#undef IUTEST_HAS_MATCHER_VARIADIC
#undef IUTEST_HAS_MATCHER_OPTIONAL

#endif

//======================================================================
// define

#if defined(IUTEST_USE_GMOCK)

#define IUTEST_HAS_MATCHERS                         1
#define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF          1
#define IUTEST_HAS_MATCHER_ELEMENTSARE              1
#define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD  0
#define IUTEST_HAS_MATCHER_REGEX                    1
#if GMOCK_VER > 0x01060000
#  define IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR     1
#else
#  define IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR     0
#endif
#if GMOCK_VER > 0x01050000
#  define IUTEST_HAS_MATCHER_EACH                   1
#  define IUTEST_HAS_MATCHER_POINTWISE              1
#else
#  define IUTEST_HAS_MATCHER_EACH                   0
#  define IUTEST_HAS_MATCHER_POINTWISE              0
#endif
#if GMOCK_VER > 0x01080000
#  define IUTEST_HAS_MATCHER_OPTIONAL               1
#else
#  define IUTEST_HAS_MATCHER_OPTIONAL               0
#endif
#if defined(GTEST_LANG_CXX11) && GTEST_LANG_CXX11
#  define IUTEST_HAS_MATCHER_VARIADIC               1
#else
#  define IUTEST_HAS_MATCHER_VARIADIC               0
#endif

#define IUTEST_ASSERT_THAT      ASSERT_THAT
#define IUTEST_EXPECT_THAT      EXPECT_THAT
#define IUTEST_INFORM_THAT      INFORM_THAT
#define IUTEST_ASSUME_THAT      ASSUME_THAT

#define INFORM_THAT(value, matcher) \
    INFORM_PRED_FORMAT1(::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
#define ASSUME_THAT(value, matcher) \
    ASSUME_PRED_FORMAT1(::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
#else

#define IUTEST_HAS_MATCHERS                         0
#define IUTEST_HAS_MATCHER_VARIADIC                 0
#define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF          0
#define IUTEST_HAS_MATCHER_ELEMENTSARE              0
#define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD  0
#define IUTEST_HAS_MATCHER_REGEX                    0
#define IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR       0
#define IUTEST_HAS_MATCHER_EACH                     0

#endif

//======================================================================
// using
#if defined(IUTEST_USE_GMOCK)

namespace testing
{

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF && (GMOCK_VER <= 0x01050000)

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6>
inline internal::BothOfMatcher<M1,
            internal::BothOfMatcher<M2,
                internal::BothOfMatcher<M3,
                    internal::BothOfMatcher<M4,
                        internal::BothOfMatcher<M5, M6> > > > >
AllOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6) {
    return AllOf(m1, AllOf(m2, m3, m4, m5, m6));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7>
inline internal::BothOfMatcher<M1,
            internal::BothOfMatcher<M2,
                internal::BothOfMatcher<M3,
                    internal::BothOfMatcher<M4,
                        internal::BothOfMatcher<M5,
                            internal::BothOfMatcher<M6, M7> > > > > >
AllOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7) {
    return AllOf(m1, AllOf(m2, m3, m4, m5, m6, m7));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8>
inline internal::BothOfMatcher<M1,
            internal::BothOfMatcher<M2,
                internal::BothOfMatcher<M3,
                    internal::BothOfMatcher<M4,
                        internal::BothOfMatcher<M5,
                            internal::BothOfMatcher<M6,
                                internal::BothOfMatcher<M7, M8> > > > > > >
AllOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8) {
    return AllOf(m1, AllOf(m2, m3, m4, m5, m6, m7, m8));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9>
inline internal::BothOfMatcher<M1,
            internal::BothOfMatcher<M2,
                internal::BothOfMatcher<M3,
                    internal::BothOfMatcher<M4,
                        internal::BothOfMatcher<M5,
                            internal::BothOfMatcher<M6,
                                internal::BothOfMatcher<M7,
                                    internal::BothOfMatcher<M8, M9> > > > > > > >
AllOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8, M9 m9) {
    return AllOf(m1, AllOf(m2, m3, m4, m5, m6, m7, m8, m9));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9, typename M10>
inline internal::BothOfMatcher<M1,
            internal::BothOfMatcher<M2,
                internal::BothOfMatcher<M3,
                    internal::BothOfMatcher<M4,
                        internal::BothOfMatcher<M5,
                            internal::BothOfMatcher<M6,
                                internal::BothOfMatcher<M7,
                                    internal::BothOfMatcher<M8,
                                        internal::BothOfMatcher<M9, M10> > > > > > > > >
AllOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8, M9 m9, M10 m10) {
    return AllOf(m1, AllOf(m2, m3, m4, m5, m6, m7, m8, m9, m10));
}

template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6>
inline internal::EitherOfMatcher<M1,
            internal::EitherOfMatcher<M2,
                internal::EitherOfMatcher<M3,
                    internal::EitherOfMatcher<M4,
                        internal::EitherOfMatcher<M5, M6> > > > >
AnyOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6) {
    return AnyOf(m1, AnyOf(m2, m3, m4, m5, m6));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7>
inline internal::EitherOfMatcher<M1,
            internal::EitherOfMatcher<M2,
                internal::EitherOfMatcher<M3,
                    internal::EitherOfMatcher<M4,
                        internal::EitherOfMatcher<M5,
                            internal::EitherOfMatcher<M6, M7> > > > > >
AnyOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7) {
    return AnyOf(m1, AnyOf(m2, m3, m4, m5, m6, m7));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8>
inline internal::EitherOfMatcher<M1,
            internal::EitherOfMatcher<M2,
                internal::EitherOfMatcher<M3,
                    internal::EitherOfMatcher<M4,
                        internal::EitherOfMatcher<M5,
                            internal::EitherOfMatcher<M6,
                                internal::EitherOfMatcher<M7, M8> > > > > > >
AnyOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8) {
    return AnyOf(m1, AnyOf(m2, m3, m4, m5, m6, m7, m8));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9>
inline internal::EitherOfMatcher<M1,
            internal::EitherOfMatcher<M2,
                internal::EitherOfMatcher<M3,
                    internal::EitherOfMatcher<M4,
                        internal::EitherOfMatcher<M5,
                            internal::EitherOfMatcher<M6,
                                internal::EitherOfMatcher<M7,
                                    internal::EitherOfMatcher<M8, M9> > > > > > > >
AnyOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8, M9 m9) {
    return AnyOf(m1, AnyOf(m2, m3, m4, m5, m6, m7, m8, m9));
}
template <typename M1, typename M2, typename M3, typename M4, typename M5, typename M6, typename M7, typename M8, typename M9, typename M10>
inline internal::EitherOfMatcher<M1,
            internal::EitherOfMatcher<M2,
                internal::EitherOfMatcher<M3,
                    internal::EitherOfMatcher<M4,
                        internal::EitherOfMatcher<M5,
                            internal::EitherOfMatcher<M6,
                                internal::EitherOfMatcher<M7,
                                    internal::EitherOfMatcher<M8,
                                        internal::EitherOfMatcher<M9, M10> > > > > > > > >
AnyOf(M1 m1, M2 m2, M3 m3, M4 m4, M5 m5, M6 m6, M7 m7, M8 m8, M9 m9, M10 m10) {
    return AnyOf(m1, AnyOf(m2, m3, m4, m5, m6, m7, m8, m9, m10));
}

#endif

namespace matchers
{

    using ::testing::Not;
    using ::testing::Eq;
    using ::testing::Ne;
    using ::testing::Lt;
    using ::testing::Le;
    using ::testing::Gt;
    using ::testing::Ge;
    using ::testing::IsNull;
    using ::testing::NotNull;

    using ::testing::DoubleEq;
    using ::testing::FloatEq;
    using ::testing::NanSensitiveDoubleEq;
    using ::testing::NanSensitiveFloatEq;

#if IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR
    using ::testing::DoubleNear;
    using ::testing::FloatNear;
    using ::testing::NanSensitiveDoubleNear;
    using ::testing::NanSensitiveFloatNear;
#endif

    using ::testing::StrEq;
    using ::testing::StrNe;
    using ::testing::StrCaseEq;
    using ::testing::StrCaseNe;
    using ::testing::HasSubstr;
    using ::testing::StartsWith;
    using ::testing::EndsWith;

    using ::testing::Contains;
    using ::testing::ContainerEq;
#if IUTEST_HAS_MATCHER_EACH
    using ::testing::Each;
#endif
#if IUTEST_HAS_MATCHER_POINTWISE
    using ::testing::Pointwise;
#endif
    using ::testing::Key;
    using ::testing::Pair;
    using ::testing::Field;
    using ::testing::Property;

    using ::testing::ResultOf;
    using ::testing::Pointee;

    using ::testing::ElementsAre;
    using ::testing::ElementsAreArray;

    using ::testing::MatchesRegex;
    using ::testing::ContainsRegex;

#if IUTEST_HAS_MATCHER_OPTIONAL
    using ::testing::Optional;
#endif
    using ::testing::AllOf;
    using ::testing::AnyOf;

    using ::testing::A;
    using ::testing::_;
    using ::testing::TypedEq;

    template<typename T>
    inline internal::EqMatcher<T> Equals(T x) { return Eq(x); }

    template<typename T>
    inline internal::FloatingEqMatcher<T> FloatingPointEq(T rhs) {
        return internal::FloatingEqMatcher<T>(rhs, false);
    }

    template<typename T>
    inline internal::FloatingEqMatcher<T> NanSensitiveFloatingPointEq(T rhs) {
        return internal::FloatingEqMatcher<T>(rhs, true);
    }

    template<typename T>
    inline internal::FloatingEqMatcher<T> FloatingPointNear(T rhs, T max_abs_error) {
        return internal::FloatingEqMatcher<T>(rhs, false, max_abs_error);
    }

    template<typename T>
    inline internal::FloatingEqMatcher<T> NanSensitiveFloatingPointNear(T rhs, T max_abs_error) {
        return internal::FloatingEqMatcher<T>(rhs, true, max_abs_error);
    }

#if GMOCK_VER >= 0x01070000
    // gmock 1.7 or later
    using ::testing::IsEmpty;
    using ::testing::SizeIs;
#endif

}   // end of namespace matchers
}   // end of namespace testing

#endif

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
