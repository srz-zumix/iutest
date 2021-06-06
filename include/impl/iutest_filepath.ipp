//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_filepath.ipp
 * @brief       iris unit test ファイルパスクラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_FILEPATH_IPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_
#define INCG_IRIS_IUTEST_FILEPATH_IPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_

//======================================================================
// include
#include "../internal/iutest_filepath.hpp"

#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <direct.h>
#elif defined(IUTEST_OS_FREEBSD)
#  include <sys/sysctl.h>
#endif


namespace iutest {
namespace detail
{

IUTEST_IPP_INLINE bool iuFilePath::IsDirectory() const
{
    if( m_path.empty() )
    {
        return false;
    }
    const char last = *m_path.rbegin();
    return (IsPathSeparator(last) || last == '.');
}

IUTEST_IPP_INLINE bool iuFilePath::IsRootDirectory() const
{
#ifdef IUTEST_OS_WINDOWS
    if( length() != 3 )
    {
        return false;
    }
#else
    if( length() != 1 )
    {
        return false;
    }
#endif
    return IsAbsolutePath();
}

IUTEST_IPP_INLINE bool iuFilePath::IsAbsolutePath() const
{
#if IUTEST_USE_CXX_FILESYSTEM
    return path().is_absolute();
#else
#ifdef IUTEST_OS_WINDOWS
    if( length() < 3 )
    {
        return false;
    }
    const char* name = m_path.c_str();

    const int drive = toupper(name[0]);
    if( !(drive >= 'A' && drive <= 'Z') )
    {
        return false;
    }
    return (name[1] == ':' && IsPathSeparator(name[2]));
#else
    return IsPathSeparator(*m_path.begin());
#endif
#endif
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::RemoveTrailingPathSeparator() const
{
    const ::std::string& path = m_path;
    ::std::string::const_reverse_iterator it = path.rbegin();
    while(it != path.rend() && IsPathSeparator(*it))
    {
        ++it;
    }
    return iuFilePath(path.substr(0, ::std::distance(it, path.rend())));
}

IUTEST_IPP_INLINE ::std::string iuFilePath::GetExtension() const
{
    const char* const path = m_path.c_str();
    const char* const ext = strrchr(path, '.');
    if(ext == NULL)
    {
        return "";
    }
    return ext;
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::RemoveExtension(const char* extension) const
{
    const char* const path = m_path.c_str();
    const char* const ext = strrchr(path, '.');
    if( ext == NULL )
    {
        return *this;
    }
    if( extension != NULL && !IsStringCaseEqual(ext + 1, extension) )
    {
        return *this;
    }
    const size_t length = ext - path;
    return iuFilePath(::std::string(path, length));
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::RemoveDirectoryName() const
{
    const char* const sep = detail::FindLastPathSeparator(m_path.c_str(), m_path.length());
    return sep != NULL ? iuFilePath(sep+1) : *this;
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::RemoveFileName() const
{
    const char* path = m_path.c_str();
    size_t pos = detail::FindLastPathSeparatorPosition(path, m_path.length());
    if( pos == ::std::string::npos )
    {
        return GetRelativeCurrentDir();
    }
    const size_t length = pos + 1;
    return iuFilePath(::std::string(path, length));
}

IUTEST_IPP_INLINE bool iuFilePath::CreateFolder() const
{
#if IUTEST_USE_CXX_FILESYSTEM
    return ::std::filesystem::create_directory(path());
#else
#if IUTEST_HAS_FILE_STAT

#if   defined(IUTEST_OS_WINDOWS_MOBILE)
#elif defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_WINE)
    if( _mkdir(m_path.c_str()) == 0 )
    {
        return true;
    }
#else
    if( mkdir(m_path.c_str(), 0777) == 0 )
    {
        return true;
    }
#endif

#endif
    return DirectoryExists();
#endif
}

IUTEST_IPP_INLINE bool iuFilePath::CreateDirectoriesRecursively() const
{
#if IUTEST_USE_CXX_FILESYSTEM
    return ::std::filesystem::create_directories(path());
#else
    if( !IsDirectory() )
    {
        return false;
    }

    if( length() == 0 || DirectoryExists() )
    {
        return true;
    }

    const iuFilePath parent = RemoveTrailingPathSeparator().RemoveFileName();
    if( !parent.CreateDirectoriesRecursively() )
    {
        return false;
    }
    return CreateFolder();
#endif
}

IUTEST_IPP_INLINE bool iuFilePath::FileOrDirectoryExists() const
{
#if IUTEST_USE_CXX_FILESYSTEM
    return ::std::filesystem::exists(path());
#else
#if IUTEST_HAS_FILE_STAT
    posix::StatStruct file_stat;
    return posix::Stat(m_path.c_str(), &file_stat) == 0;
#else
    return false;
#endif
#endif
}

IUTEST_IPP_INLINE bool iuFilePath::DirectoryExists() const
{
#if IUTEST_USE_CXX_FILESYSTEM
    return ::std::filesystem::is_directory(status());
#else
#if IUTEST_HAS_FILE_STAT

#ifdef IUTEST_OS_WINDOWS
    const iuFilePath& path = IsRootDirectory() ? *this : RemoveTrailingPathSeparator();
#else
    const iuFilePath& path = *this;
#endif
    posix::StatStruct file_stat;
    if( posix::Stat(path.m_path.c_str(), &file_stat) == 0 )
    {
        return posix::IsDir(file_stat);
    }

#endif
    return false;
#endif
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::GetCurrentDir()
{
    return iuFilePath(internal::posix::GetCWD());
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::GetRelativeCurrentDir()
{
    ::std::string dir(".");
    dir += GetPathSeparator();
    return iuFilePath(dir);
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::GetExecFilePath()
{
#if   defined(IUTEST_OS_WINDOWS)
    char path[IUTEST_MAX_PATH];
    ::GetModuleFileNameA(NULL, path, sizeof(path));
    return iuFilePath(path);
#elif defined(IUTEST_OS_SOLARIS)
    return iuFilePath(getexecname());
#elif defined(IUTEST_OS_FREEBSD)
    int exe_path_mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, getpid() };
    char buf[1024];
    size_t length = 0;
    if( sysctl(exe_path_mib, 4, buf, &length, NULL, 0) != 0 )
    {
        return iuFilePath();
    }
    return iuFilePath(buf);
#elif defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN)
#if (defined(__BSD_VISIBLE) && __BSD_VISIBLE) \
    || (defined(__POSIX_VISIBLE) && __POSIX_VISIBLE >= 200112) \
    || (defined(__XSI_VISIBLE) && __XSI_VISIBLE >= 4)
    char buf[1024];
    const ssize_t len = ::readlink("/proc/self/exe", buf, sizeof(buf)-1);
    if( len == -1 )
    {
        return iuFilePath();
    }
    buf[len] = '\0';
    return iuFilePath(buf);
#else
    return iuFilePath();
#endif
#else
    return iuFilePath();
#endif
}

IUTEST_IPP_INLINE iuFilePath iuFilePath::ConcatPaths(const iuFilePath& directory, const iuFilePath& relative_path)
{
    if( directory.IsEmpty() )
    {
        return relative_path;
    }
    ::std::string path = directory.RemoveTrailingPathSeparator().m_path;
    path += GetPathSeparator();
    path += relative_path.m_path;
    return iuFilePath(path);
}

IUTEST_IPP_INLINE void iuFilePath::Normalize()
{
    const char* src = m_path.c_str();
    char* const dst_top = new char [length()+1];
    char* dst = dst_top;

    while(*src != '\0')
    {
        *dst = *src;
        if( !IsPathSeparator(*src) )
        {
            ++src;
        }
        else
        {
            if( IsAltPathSeparator(*src) )
            {
                *dst = GetPathSeparator();
            }
            ++src;
            while( IsPathSeparator(*src) )
            {
                ++src;
            }
        }
        ++dst;
    }
    *dst = '\0';
    m_path = dst_top;
    delete [] dst_top;
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_FILEPATH_IPP_D69E7545_BF8A_4EDC_9493_9105C69F9378_
