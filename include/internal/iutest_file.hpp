//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_file.hpp
 * @brief       iris unit test ファイルクラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_
#define INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_internal_defs.hpp"
#include "iutest_stream.hpp"

#if defined(IUTEST_OS_WINDOWS)
#include <io.h>
#include <fcntl.h>
#include <share.h>
#endif
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/**
 * @brief   ファイルクラスインターフェイス
*/
class IFile : public detail::IOutStream, public detail::IInStream
{
public:
    //! ファイルオープンモードフラグ
    enum OpenFlag
    {
        OpenRead    = 0x00000001,   //!< 読み込み
        OpenWrite   = 0x00000002,   //!< 書き込み
        OpenAppend  = 0x00000003    //!< 追記
    };
public:
    virtual ~IFile() {}

public:
    /**
     * @brief   開く
     * @param [in]  filename    = ファイルパス
     * @param [in]  mode        = モード
     * @return  成否
    */
    bool Open(const char* filename, int mode)
    {
        return OpenImpl(filename, mode);
    }

#if IUTEST_HAS_STD_FILESYSTEM
    /**
     * @brief   開く
     * @param [in]  path        = ファイルパス
     * @param [in]  mode        = モード
     * @return  成否
    */
    bool Open(const ::std::filesystem::path& path, int mode)
    {
        return Open(path.string().c_str(), mode);
    }
#endif

    //! 閉じる
    virtual void Close() = 0;
private:
    virtual bool OpenImpl(const char* filename, int mode) = 0;
};

namespace detail
{

/**
 * @brief   ファイル処理クラスインターフェイス
*/
class IFileSystem
{
public:
    IFileSystem() IUTEST_CXX_NOEXCEPT_SPEC
    {
        SetInstance(this);
    }
    virtual ~IFileSystem()
    {
        SetInstance(IUTEST_NULLPTR);
    }

public:
    virtual void Initialize() IUTEST_CXX_NOEXCEPT_SPEC {}

public:
    static IFileSystem* GetInstance() IUTEST_CXX_NOEXCEPT_SPEC { return GetInstanceVariable().pInstance; }

public:
    static IFile* New()
    {
        IFileSystem* fs = GetInstance();
        if( fs == IUTEST_NULLPTR )
        {
            return IUTEST_NULLPTR;
        }
        IFile* p = fs->Create();
        return p;
    }
    static void Free(IFile* ptr) IUTEST_CXX_NOEXCEPT_SPEC
    {
        IFileSystem* fs = GetInstance();
        if( fs == IUTEST_NULLPTR )
        {
            return;
        }
        fs->Delete(ptr);
    }

    static bool ReadAll(const char* filename, ::std::string& dst)
    {
        IFile* fp = detail::IFileSystem::New();
        if(fp == IUTEST_NULLPTR)
        {
            return false;
        }

        if(!fp->Open(filename, IFile::OpenRead))
        {
            detail::IFileSystem::Free(fp);
            return false;
        }

        dst = fp->ReadAll();
        detail::IFileSystem::Free(fp);
        return true;
    }

private:
    virtual IFile*  Create() = 0;
    virtual void    Delete(IFile*) IUTEST_CXX_NOEXCEPT_SPEC = 0;

private:
    struct InstanceVariable
    {
        IFileSystem* pInstance;
    };

    static InstanceVariable& GetInstanceVariable() IUTEST_CXX_NOEXCEPT_SPEC { static InstanceVariable v; return v; }
    static void SetInstance(IFileSystem* pFileSystem) IUTEST_CXX_NOEXCEPT_SPEC { GetInstanceVariable().pInstance = pFileSystem; }
};

}   // end of namespace detail
}   // end of namespace iutest

namespace iutest
{

/**
 * @brief   ファイル処理クラスインターフェイス
*/
template<typename FILE>
class FileSystem IUTEST_CXX_FINAL : public detail::IFileSystem
{
private:
    virtual IFile*  Create() IUTEST_CXX_OVERRIDE { return new FILE; }
    IUTEST_PRAGMA_MSC_WARN_SUPPRESS(26466)
    virtual void    Delete(IFile* ptr) IUTEST_CXX_NOEXCEPT_SPEC IUTEST_CXX_OVERRIDE { detail::Delete<FILE>(static_cast<FILE*>(ptr)); }
};


#if IUTEST_HAS_FOPEN

/**
 * @brief   標準ファイルクラス
*/
class StdioFile : public IFile
{
protected:
    FILE* m_fp;
public:
    StdioFile() IUTEST_CXX_NOEXCEPT_SPEC : m_fp(IUTEST_NULLPTR) {}
    virtual ~StdioFile()
    {
        IUTEST_IGNORE_EXCEPTION_BEGIN()
        {
            StdioFile::Close()();
        }
        IUTEST_IGNORE_EXCEPTION_END()
    }
public:
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DECLARE_NOEXCEPT()

    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        if( m_fp != IUTEST_NULLPTR )
        {
            fclose(m_fp);
            m_fp = IUTEST_NULLPTR;
        }
    }
    /**
     * @brief   書き込み
     * @param [in]  buf     = 書き込みバッファ
     * @param [in]  size    = バッファサイズ
     * @param [in]  cnt     = 書き込み回数
    */
    virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        if( fwrite(buf, size, cnt, m_fp) < cnt )
        {
            return false;
        }
        if( fflush(m_fp) != 0 )
        {
            return false;
        }
        return true;
    }

    /**
     * @brief   読み込み
     * @param [in]  buf     = 読み込みバッファ
     * @param [in]  size    = 読み込みデータサイズ
     * @param [in]  cnt     = 読み込み回数
    */
    virtual bool Read(void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        if( fread(buf, size, cnt, m_fp) < cnt )
        {
            return false;
        }
        return true;
    }

    //! サイズ取得
    virtual iu_uint_max_t GetSize() IUTEST_CXX_OVERRIDE
    {
        return GetSize(m_fp);
    }

IUTEST_PRAGMA_WARN_POP()

public:
    void Flush()
    {
        fflush(m_fp);
    }

public:
    static iu_uint_max_t GetSize(FILE* fp) IUTEST_CXX_NOEXCEPT_SPEC
    {
        return internal::posix::FileSize(fp);
    }
    static iu_uint_max_t GetSizeBySeekSet(FILE* fp) IUTEST_CXX_NOEXCEPT_SPEC
    {
        return internal::posix::FileSizeBySeekSet(fp);
    }
private:
    virtual bool OpenImpl(const char* filename, int mode) IUTEST_CXX_OVERRIDE
    {
        Close();
        switch( mode )
        {
        case IFile::OpenRead:
            m_fp = internal::posix::FileOpen(filename, "rb");
            break;
        case IFile::OpenWrite:
            m_fp = internal::posix::FileOpen(filename, "wb");
            break;
        case IFile::OpenAppend:
            m_fp = internal::posix::FileOpen(filename, "ab");
            break;
        default:
            break;
        }
        return m_fp != IUTEST_NULLPTR;
    }
};

class StdErrorFile : public StdioFile
{
public:
    StdErrorFile() IUTEST_CXX_NOEXCEPT_SPEC {}
    virtual ~StdErrorFile()
    {
        IUTEST_IGNORE_EXCEPTION_BEGIN()
        {
            Close();
        }
        IUTEST_IGNORE_EXCEPTION_END()
    }
public:
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DECLARE_NOEXCEPT()

    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        m_fp = IUTEST_NULLPTR;
    }
private:
    virtual bool OpenImpl(const char* , int ) IUTEST_CXX_OVERRIDE
    {
        m_fp = stderr;
        return true;
    }

IUTEST_PRAGMA_WARN_POP()
};

class TempFile : public IFile
{
public:
    TempFile() IUTEST_CXX_NOEXCEPT_SPEC
        : m_fd(-1)
    {
    }

    virtual ~TempFile() { Close(); }

public:
    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        m_file.Close();
        if( m_fd != -1 )
        {
            internal::posix::FdClose(m_fd);
            m_fd = -1;
        }
    }
    /**
     * @brief   書き込み
     * @param [in]  buf     = 書き込みバッファ
     * @param [in]  size    = バッファサイズ
     * @param [in]  cnt     = 書き込み回数
    */
    virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        return m_file.Write(buf, size, cnt);
    }

    /**
     * @brief   読み込み
     * @param [in]  buf     = 読み込みバッファ
     * @param [in]  size    = 読み込みデータサイズ
     * @param [in]  cnt     = 読み込み回数
    */
    virtual bool Read(void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        return m_file.Read(buf, size, cnt);
    }

    //! サイズ取得
    virtual iu_uint_max_t GetSize() IUTEST_CXX_OVERRIDE
    {
        return m_file.GetSize();
    }

public:
    int GetDescriptor() const { return m_fd; }
    const ::std::string& GetFileName() const { return m_filename; }

    bool Open(int mode)
    {
        return OpenImpl(m_filename.c_str(), mode);
    }

    void Delete()
    {
        Close();
        if( !m_filename.empty() )
        {
            remove(m_filename.c_str());
            m_filename = "";
        }
    }

    bool Create(const char* basename)
    {
#if defined(IUTEST_OS_WINDOWS)
        char tmp_dir[IUTEST_MAX_PATH] = { '\0' };
        GetTempPathA(sizeof(tmp_dir), tmp_dir);

        char name_template[IUTEST_MAX_PATH] = { '\0' };
        UINT ret = GetTempFileNameA(tmp_dir, basename, 0, name_template);
        IUTEST_CHECK_(ret != 0) << "Unable to create a temporary file in " << tmp_dir;
#if defined(_CRT_FUNCTIONS_REQUIRED)
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
        const int fd = _creat(name_template, _S_IREAD | _S_IWRITE);
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
#else
#if defined(IUTEST_OS_WINDOWS_MINGW)
        const int fd = _sopen(name_template, _O_CREAT | _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
#else
        int fd = -1;
        _sopen_s(&fd, name_template, _O_CREAT | _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
#endif
#endif
#else
#if   defined(IUTEST_OS_LINUX_ANDROID)
        ::std::string name_template = "/data/local/tmp/";
#elif defined(IUTEST_OS_IOS)
        char user_temp_dir[IUTEST_MAX_PATH];
        ::confstr(_CS_DARWIN_USER_TEMP_DIR, user_temp_dir, sizeof(user_temp_dir));
        ::std::string name_template = user_temp_dir;
        name_template += "/";
#else
        ::std::string name_template = "/tmp/";
#endif
        name_template += basename;
        name_template += ".XXXXXX";
        const int fd = internal::posix::Mkstemp(const_cast<char*>(name_template.data()));
#endif
        m_fd = fd;
        m_filename = name_template;
        return m_fd != -1;
    }

private:
    bool Open(const char*, int);

    virtual bool OpenImpl(const char* filename, int mode) IUTEST_CXX_OVERRIDE
    {
        return m_file.Open(filename, mode);
    }

private:
    StdioFile m_file;
    int m_fd;
    ::std::string m_filename;
};

#endif


#if IUTEST_HAS_STRINGSTREAM

/**
 * @brief   文字列バッファ書き込み IFile インターフェースクラス
*/
class StringStreamFile : public IFile
{
public:
    virtual ~StringStreamFile()
    {
        IUTEST_IGNORE_EXCEPTION_BEGIN()
        {
            StringStreamFile::Close();
        }
        IUTEST_IGNORE_EXCEPTION_END()
    }
public:
    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        ss.clear();
    }

    /**
     * @brief   書き込み
     * @param [in]  buf     = 書き込みバッファ
     * @param [in]  size    = バッファサイズ
     * @param [in]  cnt     = 書き込み回数
    */
    virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        for( size_t i=0; i < cnt; ++i )
        {
            ss.write(static_cast<const char*>(buf), size);
        }
        return true;
    }

    /**
     * @brief   読み込み
     * @param [in]  buf     = 読み込みバッファ
     * @param [in]  size    = 読み込みデータサイズ
     * @param [in]  cnt     = 読み込み回数
    */
    virtual bool Read(void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        char* p = static_cast<char*>(buf);
        for( size_t i = 0; i < cnt; ++i )
        {
            ss.read(p, size);
            p += size;
        }
        return true;
    }

    //! サイズ取得
    virtual iu_uint_max_t GetSize() IUTEST_CXX_OVERRIDE
    {
        const ::std::stringstream::pos_type pre = ss.tellg();
        ss.seekg(0, ::std::ios::end);
        const ::std::stringstream::pos_type size = ss.tellg();
        ss.seekg(pre, ::std::ios::beg);
        return static_cast<iu_uint_max_t>(size);
    }

    //! 全読み込み
    virtual ::std::string ReadAll() IUTEST_CXX_OVERRIDE
    {
        return ss.str();
    }
private:
    virtual bool OpenImpl(const char* , int ) IUTEST_CXX_OVERRIDE
    {
        ss.clear();
        return true;
    }
protected:
    ::std::stringstream ss;
};

#endif

namespace detail
{

/**
 * @brief   何もしない IFile インターフェースクラス
*/
class NoEffectFile IUTEST_CXX_FINAL : public IFile
{
public:
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DECLARE_NOEXCEPT()

    virtual void Close() IUTEST_CXX_OVERRIDE {}
    virtual bool Write(const void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true;  }
    virtual bool Read(void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true; }
    virtual iu_uint_max_t GetSize() IUTEST_CXX_OVERRIDE { return 0; }
private:
    virtual bool OpenImpl(const char*, int) IUTEST_CXX_OVERRIDE { return true; }

IUTEST_PRAGMA_WARN_POP()
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_
