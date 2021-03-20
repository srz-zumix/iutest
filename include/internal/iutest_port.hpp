//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_port.hpp
 * @brief       portable
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PORT_HPP_7893F685_A1A9_477A_82E8_BF06237697FF_
#define INCG_IRIS_IUTEST_PORT_HPP_7893F685_A1A9_477A_82E8_BF06237697FF_

//======================================================================
// include
#if defined(__MWERKS__)
#  define _MSL_USING_NAMESPACE
#endif

#include "iutest_internal_defs.hpp"

#if defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN) || defined(IUTEST_OS_MAC) || defined(IUTEST_OS_IOS) || defined(IUTEST_OS_FREEBSD)
#  include <unistd.h>
#  include <locale.h>
#endif

#if IUTEST_HAS_FILE_STAT
#  include <sys/stat.h>
#endif

//======================================================================
// define
#if !defined(IUTEST_MAX_PATH)
#  if   defined(MAX_PATH) && MAX_PATH
#    define IUTEST_MAX_PATH MAX_PATH
#  elif defined(PATH_MAX) && PATH_MAX
#    define IUTEST_MAX_PATH PATH_MAX
#  elif defined(FILENAME_MAX) && FILENAME_MAX
#    define IUTEST_MAX_PATH FILENAME_MAX
#  else
#    define IUTEST_MAX_PATH 1024
#  endif
#endif

/**
 * @brief   ログメッセージストリーム
*/
#define IUTEST_LOG_(level)          \
    ::iutest::detail::IUTestLog(    \
        ::iutest::detail::IUTestLog::LOG_##level, __FILE__, __LINE__).GetStream()

/**
 * @brief   内部エラーチェック
*/
#define IUTEST_CHECK_(condition)                \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_              \
    if( !::iutest::detail::IsTrue(condition) )  \
        IUTEST_LOG_(FATAL) << "Condition " #condition " failed. "

/**
 * @brief   Abort
*/
#if !defined(IUTEST_ABORT)
#  define IUTEST_ABORT()  ::iutest::internal::posix::Abort()
#endif

namespace iutest {

#ifdef IUTEST_OS_NACL
namespace nacl
{

/**
 * @brief   printf
*/
void vprint_message(const char *fmt, va_list va);
void print_message(const char *fmt, ...);

}
#endif

namespace internal {
namespace posix
{

const char* GetEnv(const char* name);
int PutEnv(const char* expr);
int SetEnv(const char* name, const char* value, int overwrite);

const char* GetCWD(char* buf, size_t length);
::std::string GetCWD();

void SleepMillisec(unsigned int millisec);

IUTEST_ATTRIBUTE_NORETURN_ void Abort();
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
inline void Abort() { abort(); }
#endif

#if IUTEST_HAS_FILENO

#if defined(_MSC_VER)
inline int Fileno(FILE* fp) { return _fileno(fp); }
#else
inline int Fileno(FILE* fp) { return fileno(fp); }
#endif

#else

inline int Fileno(FILE*) { return -1; }

#endif

#if IUTEST_HAS_FILE_STAT

#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_WINE)

typedef struct _stat StatStruct;

inline int FileStat(int fd, StatStruct* buf) { return _fstat(fd, buf); }
inline int Stat(const char* path, StatStruct* buf) { return _stat(path, buf); }
inline bool IsDir(const StatStruct& st) { return (st.st_mode & _S_IFDIR) != 0; }

#else

typedef struct stat StatStruct;

inline int FileStat(int fd, StatStruct* buf) { return fstat(fd, buf); }
inline int Stat(const char* path, StatStruct* buf) { return stat(path, buf); }
inline bool IsDir(const StatStruct& st) { return S_ISDIR(st.st_mode); }

#endif

inline int Stat(FILE* fp, StatStruct* buf)
{
    int fd = Fileno(fp);
    return fd >= 0 ? FileStat(fd, buf) : fd;
}

#endif

}   // end of namespace posix

inline void SleepMilliseconds(int n) { posix::SleepMillisec(static_cast<unsigned int>(n)); }

}   // end of namespace internal

namespace detail
{

namespace posix = internal::posix;

/**
 * @brief   パス区切り文字の取得
*/
char GetPathSeparator() IUTEST_CXX_NOEXCEPT_SPEC;

/**
 * @brief   パス区切り文字かどうか
*/
bool IsPathSeparator(char c) IUTEST_CXX_NOEXCEPT_SPEC;

/**
 * @brief   パス区切り文字かどうか
*/
bool IsAltPathSeparator(char c) IUTEST_CXX_NOEXCEPT_SPEC;

/**
 * @brief   一番後ろのパスセパレータのアドレスを取得
*/
const char* FindLastPathSeparator(const char* path, size_t length) IUTEST_CXX_NOEXCEPT_SPEC;

/**
 * @brief   一番後ろのパスセパレータの位置を取得
*/
size_t FindLastPathSeparatorPosition(const char* path, size_t length) IUTEST_CXX_NOEXCEPT_SPEC;

/**
 * @brief   環境変数の設定
*/
bool SetEnvironmentVariable(const char* name, const char* value);


/**
 * @brief   環境変数の取得
 * @param [in]  name    = 環境変数名
 * @param [out] buf     = 出力バッファ
 * @return  成否
*/
bool GetEnvironmentVariable(const char* name, char* buf, size_t size);

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

template<size_t SIZE>
inline bool GetEnvironmentVariable(const char* name, char (&buf)[SIZE])
{
return GetEnvironmentVariable(name, buf, SIZE);
}

#endif

/**
 * @brief   環境変数の取得
 * @param [in]  name    = 環境変数名
 * @param [out] var     = 出力文字列
 * @return  成否
 */
bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentVariable(const char* name, ::std::string& var);

/**
 * @brief   環境変数の取得
 * @param [in]  name    = 環境変数名
 * @param [out] var     = 出力数値
 * @return  成否
 */
bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentInt(const char* name, int& var);

#if defined(IUTEST_OS_WINDOWS)
namespace win
{

    /**
     * @brief   文字列変換
     */
    ::std::string IUTEST_ATTRIBUTE_UNUSED_ WideStringToMultiByteString(const wchar_t* wide_c_str);

    /**
     * @brief   HRESULT のエラー文字列を取得
     * @param [in]  hr  = エラー値
     * @return  文字列
     */
    ::std::string IUTEST_ATTRIBUTE_UNUSED_ GetHResultString(HRESULT hr);

}   // end of namespace win
#endif

/**
 * @brief   ログ
 */
class IUTestLog
{
public:
    enum Level
    {
          LOG_INFO
        , LOG_WARNING
        , LOG_ERROR
        , LOG_FATAL
        , LOG_LEVEL_NUM
    };
public:
    IUTestLog(Level level, const char* file, int line);

    ~IUTestLog();

public:
    iu_stringstream& GetStream() { return m_stream; }

public:
    static int GetCount(Level level) { return GetCountTable().count[level]; }
    static bool HasWarning() { return GetCount(LOG_WARNING) > 0; }
    static bool HasError() { return GetCount(LOG_ERROR) > 0 || GetCount(LOG_FATAL) > 0; }

private:
    struct Count
    {
        int count[LOG_LEVEL_NUM];
    };

    static Count& GetCountTable() { static Count count = { {0} }; return count; }
    static void CountUp(int level);

private:
    const Level kLevel;
    iu_stringstream m_stream;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTestLog);
};

#if IUTEST_HAS_STREAM_BUFFER

/**
 * @brief   stream buffer
*/
template<int SIZE=BUFSIZ>
class IUStreamBuffer
{
public:
    explicit IUStreamBuffer(FILE* fp)
        : m_fp(fp)
    {
        m_buf[0] = '\0';
        fflush(fp);
        setvbuf(fp, m_buf, _IOFBF, SIZE);
    }

    ~IUStreamBuffer()
    {
        fflush(m_fp);
        setvbuf(m_fp, NULL, _IONBF, 0);
    }

public:
    ::std::string GetStreamString() { return m_buf; }

private:
    FILE* m_fp;
    char m_buf[SIZE];
};

/**
* @brief    stream capture
*/


#endif

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_port.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_PORT_HPP_7893F685_A1A9_477A_82E8_BF06237697FF_
