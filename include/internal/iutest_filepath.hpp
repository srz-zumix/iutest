//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_filepath.hpp
 * @brief       iris unit test ファイルパスクラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_FILEPATH_HPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_
#define INCG_IRIS_IUTEST_FILEPATH_HPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// include
#include "iutest_port.hpp"

#if IUTEST_HAS_FILE_STAT
#  include <sys/stat.h>
#endif

#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <direct.h>
#endif

namespace iutest {

namespace internal {
namespace posix
{

#if IUTEST_HAS_FILE_STAT

#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_WINE)

    typedef struct _stat StatStruct;

    inline int Stat(const char* path, StatStruct* buf) { return _stat(path, buf); }
    inline bool IsDir(const StatStruct& st) { return (st.st_mode & _S_IFDIR) != 0; }

#else

    typedef struct stat StatStruct;

    inline int Stat(const char* path, StatStruct* buf) { return stat(path, buf); }
    inline bool IsDir(const StatStruct& st) { return S_ISDIR(st.st_mode); }

#endif

#endif

}   // end of namespace posix
}   // end of namespace internal

namespace detail
{

//======================================================================
// class
/**
 * @brief   ファイルパスクラス
*/
class iuFilePath
{
public:
    iuFilePath() : m_path("") {}
    iuFilePath(const iuFilePath& rhs) : m_path(rhs.m_path) {}

    explicit iuFilePath(const char* path) : m_path(path)
    {
        Normalize();
    }
    explicit iuFilePath(const ::std::string& path) : m_path(path)
    {
        Normalize();
    }

public:
    ::std::string   ToString()  const { return m_path; }
    const char*     c_str()     const { return m_path.c_str(); }
    bool            IsEmpty()   const { return c_str() == NULL || *c_str() == '\0'; }
    size_t          length()    const { return m_path.length(); }

public:
    bool operator == (const iuFilePath& rhs) const
    {
        return IsStringCaseEqual(c_str(), rhs.c_str());
    }
    bool operator == (const char* rhs) const
    {
        return IsStringCaseEqual(c_str(), rhs);
    }
    //operator const char* () const { return c_str(); }

public:
    /**
     * @brief   フォルダパスかどうか
    */
    bool IsDirectory() const;

    /**
     * @brief   ルートディレクトリパスかどうか
    */
    bool IsRootDirectory() const;

    /**
     * @brief   絶対パスかどうか
    */
    bool IsAbsolutePath() const;

    /**
     * @brief   末尾のセパレーターを削除
    */
    iuFilePath RemoveTrailingPathSeparator() const;

    /**
     * @brief   拡張子の削除
    */
    iuFilePath RemoveExtension(const char* extention=NULL) const;

    /**
     * @brief   ディレクトリ名の削除
    */
    iuFilePath RemoveDirectoryName() const;

    /**
     * @brief   ファイル名の削除
    */
    iuFilePath RemoveFileName() const;

    /**
     * @brief   フォルダの作成
    */
    bool CreateFolder() const;

    /**
     * @brief   フォルダを再帰的に作成
    */
    bool CreateDirectoriesRecursively() const;

    /**
     * @brief   ファイルまたはフォルダが存在するかどうか
    */
    bool FileOrDirectoryExists() const;

    /**
     * @brief   フォルダが存在するかどうか
    */
    bool DirectoryExists() const;

    /**
     * @brief   一番後ろのパスセパレータのアドレスを取得
    */
    const char* FindLastPathSeparator() const;

public:
    /**
     * @brief   カレントディレクトリの取得
    */
    static iuFilePath GetCurrentDir();

    /**
     * @brief   カレントディレクトリの相対パス取得
    */
    static iuFilePath GetRelativeCurrentDir();

    /**
     * @brief   実行ファイルのパスを取得
    */
    static iuFilePath GetExecFilePath();

    /**
     * @brief   パスの結合
    */
    static iuFilePath ConcatPaths(const iuFilePath& directory, const iuFilePath& relative_path);

private:
    /**
     * @brief   正規化
    */
    void Normalize();

private:
    ::std::string m_path;
};

inline iu_ostream& operator << (iu_ostream& os, const iuFilePath& path)
{
    return os << path.c_str();
}

}   // end of namespace detail

namespace internal
{
    // google test との互換性のため
    typedef detail::iuFilePath FilePath;
}

}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_filepath.ipp"
#endif

#endif

#endif // INCG_IRIS_IUTEST_FILEPATH_HPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_
