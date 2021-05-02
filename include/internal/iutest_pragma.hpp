//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_pragma.hpp
 * @brief       pragma macros
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PRAGMA_HPP_FBC5A1DE_3D0C_443E_84B1_5F0618DF9A6B_
#define INCG_IRIS_IUTEST_PRAGMA_HPP_FBC5A1DE_3D0C_443E_84B1_5F0618DF9A6B_

//======================================================================
// define

// pragma
#if   defined(__clang__)
#  define IUTEST_PRAGMA(x)  _Pragma(#x)
#elif defined(__GNUC__)
#  define IUTEST_PRAGMA(x)  _Pragma(#x)
#elif defined(_MSC_VER) && _MSC_VER >= 1310
#  define IUTEST_PRAGMA(x)  __pragma(x)
#else
#  define IUTEST_PRAGMA(x)
#endif

#define IUTEST_PRAGMA_MESSAGE(m)    IUTEST_PRAGMA(message (m))

// pragma warning
#if defined(_MSC_VER)
#  define IUTEST_PRAGMA_MSC_WARN_PUSH()         IUTEST_PRAGMA(warning (push))
#  define IUTEST_PRAGMA_MSC_WARN_DISABLE(x)     IUTEST_PRAGMA(warning (disable: x))
#  define IUTEST_PRAGMA_MSC_WARN_SUPPRESS(x)    IUTEST_PRAGMA(warning (suppress: x))
#  define IUTEST_PRAGMA_MSC_WARN_POP()          IUTEST_PRAGMA(warning (pop))
#endif

#ifndef IUTEST_PRAGMA_MSC_WARN_PUSH
#  define IUTEST_PRAGMA_MSC_WARN_PUSH()
#endif
#ifndef IUTEST_PRAGMA_MSC_WARN_DISABLE
#  define IUTEST_PRAGMA_MSC_WARN_DISABLE(x)
#endif
#ifndef IUTEST_PRAGMA_MSC_WARN_POP
#  define IUTEST_PRAGMA_MSC_WARN_POP()
#endif

#if defined(__clang__)
#  define IUTEST_PRAGMA_CLANG_WARN_PUSH()       IUTEST_PRAGMA(clang diagnostic push)
#  define IUTEST_PRAGMA_CLANG_WARN_DISABLE(x)   IUTEST_PRAGMA(clang diagnostic ignored x)
#  define IUTEST_PRAGMA_CLANG_WARN_POP()        IUTEST_PRAGMA(clang diagnostic pop)
#  define IUTEST_PRAGMA_GCC_WARN_PUSH           IUTEST_PRAGMA_CLANG_WARN_PUSH
#  define IUTEST_PRAGMA_GCC_WARN_DISABLE        IUTEST_PRAGMA_CLANG_WARN_DISABLE
#  define IUTEST_PRAGMA_GCC_WARN_POP            IUTEST_PRAGMA_CLANG_WARN_POP
#endif

#if defined(__GNUC__)
#  if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#    define IUTEST_PRAGMA_GCC_WARN_PUSH()       IUTEST_PRAGMA(GCC diagnostic push)
#    define IUTEST_PRAGMA_GCC_WARN_DISABLE(x)   IUTEST_PRAGMA(GCC diagnostic ignored x)
#    define IUTEST_PRAGMA_GCC_WARN_POP()        IUTEST_PRAGMA(GCC diagnostic pop)
#    define IUTEST_PRAGMA_CLANG_WARN_PUSH       IUTEST_PRAGMA_GCC_WARN_PUSH
#    define IUTEST_PRAGMA_CLANG_WARN_DISABLE    IUTEST_PRAGMA_GCC_WARN_DISABLE
#    define IUTEST_PRAGMA_CLANG_WARN_POP        IUTEST_PRAGMA_GCC_WARN_POP
#  endif
#endif

#ifndef IUTEST_PRAGMA_CLANG_WARN_PUSH
#  define IUTEST_PRAGMA_CLANG_WARN_PUSH()
#endif
#ifndef IUTEST_PRAGMA_CLANG_WARN_DISABLE
#  define IUTEST_PRAGMA_CLANG_WARN_DISABLE(x)
#endif
#ifndef IUTEST_PRAGMA_CLANG_WARN_POP
#  define IUTEST_PRAGMA_CLANG_WARN_POP()
#endif

#ifndef IUTEST_PRAGMA_GCC_WARN_PUSH
#  define IUTEST_PRAGMA_GCC_WARN_PUSH()
#endif
#ifndef IUTEST_PRAGMA_GCC_WARN_DISABLE
#  define IUTEST_PRAGMA_GCC_WARN_DISABLE(x)
#endif
#ifndef IUTEST_PRAGMA_GCC_WARN_POP
#  define IUTEST_PRAGMA_GCC_WARN_POP()
#endif

#if   defined(__clang__)
#  define IUTEST_PRAGMA_WARN_PUSH()     IUTEST_PRAGMA_CLANG_WARN_PUSH()
#  define IUTEST_PRAGMA_WARN_POP()      IUTEST_PRAGMA_CLANG_WARN_PUSH()
#  define IUTEST_PRAGMA_WARN_DISABLE(x) IUTEST_PRAGMA_CLANG_WARN_DISABLE(x)
#elif defined(__GNUC__)
#  define IUTEST_PRAGMA_WARN_PUSH()     IUTEST_PRAGMA_GCC_WARN_PUSH()
#  define IUTEST_PRAGMA_WARN_POP()      IUTEST_PRAGMA_GCC_WARN_POP()
#  define IUTEST_PRAGMA_WARN_DISABLE(x) IUTEST_PRAGMA_GCC_WARN_DISABLE(x)
#elif defined(_MSC_VER)
#  define IUTEST_PRAGMA_WARN_PUSH()     IUTEST_PRAGMA_MSC_WARN_PUSH()
#  define IUTEST_PRAGMA_WARN_POP()      IUTEST_PRAGMA_MSC_WARN_POP()
#  define IUTEST_PRAGMA_WARN_DISABLE(x)
#else
#  define IUTEST_PRAGMA_WARN_PUSH()
#  define IUTEST_PRAGMA_WARN_POP()
#  define IUTEST_PRAGMA_WARN_DISABLE(x)
#endif


// pragma warning xxx
#if defined(_MSC_VER) && defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__
#  if defined(__clang__)
#    define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()   IUTEST_PRAGMA_CLANG_WARN_PUSH() \
                                                            IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wdeprecated-declarations")
#    define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()     IUTEST_PRAGMA_CLANG_WARN_POP()
#  else
#    define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()   IUTEST_PRAGMA_MSC_WARN_PUSH()   \
                                                            IUTEST_PRAGMA_MSC_WARN_DISABLE(4996)
#    define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()     IUTEST_PRAGMA_MSC_WARN_POP()
#  endif
#else
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
#endif

#if defined(__clang__) || defined(__GNUC__)
#  define IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_BEGIN()  \
        IUTEST_PRAGMA_WARN_PUSH()                                   \
        IUTEST_PRAGMA_WARN_DISABLE("-Wunused-local-typedefs")
#  define IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_END()    \
        IUTEST_PRAGMA_WARN_POP()
#else
#  define IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_UNUSED_LOCAL_TYPEDEFS_WARN_DISABLE_END()
#endif

#if defined(_MSC_VER)
#  define IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_BEGIN()    IUTEST_PRAGMA_MSC_WARN_PUSH()   \
                                                            IUTEST_PRAGMA_MSC_WARN_DISABLE(4702)
#  define IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_END()      IUTEST_PRAGMA_MSC_WARN_POP()
#else
#  define IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_UNREACHCODE_WARN_DISABLE_END()
#endif

#if defined(_MSC_VER) && _MSC_VER < 1700
#  define IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()    IUTEST_PRAGMA_MSC_WARN_PUSH()   \
                                                                IUTEST_PRAGMA_MSC_WARN_DISABLE(4231)
#  define IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()      IUTEST_PRAGMA_MSC_WARN_POP()
#else
#  define IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900
#  define IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_BEGIN()     IUTEST_PRAGMA_MSC_WARN_PUSH()   \
                                                                                        IUTEST_PRAGMA_MSC_WARN_DISABLE(4512)
#  define IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_END()       IUTEST_PRAGMA_MSC_WARN_POP()
#else
#  define IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_END()
#endif

#if defined(_MSC_VER) && IUTEST_HAS_CONSTEXPR
#  define IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()    IUTEST_PRAGMA_MSC_WARN_PUSH()   \
                                                                            IUTEST_PRAGMA_MSC_WARN_DISABLE(4592)
#  define IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()      IUTEST_PRAGMA_MSC_WARN_POP()
#else
#  define IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()   IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wsign-compare")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()   IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wsign-compare")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()   IUTEST_PRAGMA_MSC_WARN_DISABLE(4018 4287 4388 4389)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()     IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wempty-body")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()     IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wempty-body")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()     IUTEST_PRAGMA_MSC_WARN_DISABLE(4390)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wfloat-equal")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL()    IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wfloat-equal")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL()    // IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION)
#  if   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR >= 8)
#      define IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION() IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wdouble-promotion")
#    endif
#  elif defined(__GNUC__)
#    if __GNUC__ > 3
#      define IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION() IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wdouble-promotion")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION()   // IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION)
#  define IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION)
#  if   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR >= 5)
#      define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION() IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wfloat-conversion")
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
#      define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION() IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wfloat-conversion")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION()   IUTEST_PRAGMA_MSC_WARN_DISABLE(4305)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION)
#  define IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_FLOAT_CONVERSION)
#  if   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 9
#      define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_FLOAT_CONVERSION()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wimplicit-float-conversion")
#    endif
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_FLOAT_CONVERSION)
#  define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_FLOAT_CONVERSION()        IUTEST_PRAGMA_WARN_DISABLE_FLOAT_CONVERSION()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION)
#  if   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 9
#      define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wimplicit-int-float-conversion")
#    else
#      define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wconversion")
#    endif
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()      //IUTEST_PRAGMA_GCC_WARN_DISABLE(?)
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()      //IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION)
#  define IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()   IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wmissing-noreturn")
#  elif defined(__GNUC__)
#    if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ < 4
#      define IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN() IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wmissing-noreturn")
#    else
#      define IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN() IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wsuggest-attribute=noreturn")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()   //IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN)
#  define IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NARROWING)
#  if   defined(__clang__)
#    if IUTEST_CLANG_MAJOR > 2
#      define IUTEST_PRAGMA_WARN_DISABLE_NARROWING()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wc++11-narrowing")
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#      define IUTEST_PRAGMA_WARN_DISABLE_NARROWING()    IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnarrowing")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_NARROWING()      IUTEST_PRAGMA_MSC_WARN_DISABLE(4838)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NARROWING)
#  define IUTEST_PRAGMA_WARN_DISABLE_NARROWING()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL()  IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wformat-nonliteral")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL()  IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wformat-nonliteral")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL()  // IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_CAST_ALIGN)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_CAST_ALIGN()     IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wcast-align")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_CAST_ALIGN()     IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wcast-align")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_CAST_ALIGN()     // IUTEST_PRAGMA_MSC_WARN_DISABLE(?)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_CAST_ALIGN()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST()
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST()
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST()    IUTEST_PRAGMA_MSC_WARN_DISABLE(4814)
#  else
#    define IUTEST_PRAGMA_WARN_DISABLE_CXX14_CONSTEXPR_NOT_IMPLY_CONST()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wswitch-enum")
#  elif defined(__GNUC__)
#    if __GNUC__ > 3
#      define IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()  IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wswitch-enum")
#    else
#      define IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()  IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wswitch")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()    IUTEST_PRAGMA_MSC_WARN_DISABLE(4061)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM)
#  define IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE)
#  if   defined(__clang__)
#    if (IUTEST_CLANG_MAJOR > 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR > 0))
#      define IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wdangling-else")
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 6)
#      define IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()  IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wdangling-else")
#    endif
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE)
#  define IUTEST_PRAGMA_WARN_DISABLE_DANGLING_ELSE()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE)
#  if defined(__GNUC__) && (__GNUC__ > 6)
#    define IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE()  IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnoexcept-type")
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE)
#  define IUTEST_PRAGMA_WARN_DISABLE_NOEXCEPT_TPYE()
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NONNULL)
#  if   defined(__clang__)
#    define IUTEST_PRAGMA_WARN_DISABLE_NONNULL()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wnonnull")
#  elif defined(__GNUC__)
#    define IUTEST_PRAGMA_WARN_DISABLE_NONNULL()    IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnonnull")
#  elif defined(_MSC_VER)
#    define IUTEST_PRAGMA_WARN_DISABLE_NONNULL()    IUTEST_PRAGMA_MSC_WARN_DISABLE(6387)
#  endif
#endif

#if !defined(IUTEST_PRAGMA_WARN_DISABLE_NONNULL)
#  define IUTEST_PRAGMA_WARN_DISABLE_NONNULL()
#endif

#if   defined(__clang__)
#  if IUTEST_CLANG_MAJOR > 10
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_11()    IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wsuggest-destructor-override")
#  else
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_11()
#  endif
#  if IUTEST_CLANG_MAJOR > 4
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_5()     IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wzero-as-null-pointer-constant")
#  else
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_5()
#  endif
#  if IUTEST_CLANG_MAJOR > 2
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_3()     IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wexit-time-destructors")
#  else
#    define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_3()
#  endif

#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_BEGIN()     IUTEST_PRAGMA_CLANG_WARN_PUSH() \
                                                        IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wused-but-marked-unused") \
                                                        IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wold-style-cast") \
                                                        IUTEST_PRAGMA_CLANG_WARN_DISABLE("-Wunused-macros") \
                                                        IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_11() \
                                                        IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_5() \
                                                        IUTEST_PRAGMA_IUTEST_WARN_DISABLE_CLANG_3()

#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_END()       IUTEST_PRAGMA_CLANG_WARN_POP()
#elif defined(__GNUC__)
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_BEGIN()     IUTEST_PRAGMA_GCC_WARN_PUSH()
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_END()       IUTEST_PRAGMA_GCC_WARN_POP()
#elif defined(_MSC_VER)
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_BEGIN()     IUTEST_PRAGMA_MSC_WARN_PUSH()
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_END()       IUTEST_PRAGMA_MSC_WARN_POP()
#else
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_BEGIN()
#  define IUTEST_PRAGMA_IUTEST_WARN_DISABLE_END()
#endif

#endif // INCG_IRIS_IUTEST_PRAGMA_HPP_FBC5A1DE_3D0C_443E_84B1_5F0618DF9A6B_
