//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_file.hpp
 * @brief       iris unit test ファイルクラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_
#define INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include "iutest_stream.hpp"

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
    IFileSystem()
    {
        SetInstance(this);
    }
    virtual ~IFileSystem()
    {
        SetInstance(NULL);
    }

public:
    virtual void Initialize() {}

public:
    static IFileSystem* GetInstance() { return GetInstanceVariable().pInstance; }

public:
    static IFile* New()
    {
        IFileSystem* fs = GetInstance();
        if( fs == NULL )
        {
            return NULL;
        }
        IFile* p = fs->Create();
        return p;
    }
    static void Free(IFile* ptr)
    {
        IFileSystem* fs = GetInstance();
        if( fs == NULL )
        {
            return;
        }
        fs->Delete(ptr);
    }

    static bool ReadAll(const char* filename, ::std::string& dst)
    {
        IFile* fp = detail::IFileSystem::New();
        if(fp == NULL)
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
    virtual void    Delete(IFile*) = 0;

private:
    struct InstanceVariable
    {
        IFileSystem* pInstance;
    };

    static InstanceVariable& GetInstanceVariable() { static InstanceVariable v; return v; }
    static void SetInstance(IFileSystem* pFileSystem) { GetInstanceVariable().pInstance = pFileSystem; }
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
    virtual void    Delete(IFile* ptr) IUTEST_CXX_OVERRIDE { detail::Delete<FILE>(static_cast<FILE*>(ptr)); }
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
    StdioFile() IUTEST_CXX_NOEXCEPT_SPEC : m_fp(NULL) {}
    virtual ~StdioFile() { Close(); }
public:
    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        if( m_fp != NULL )
        {
            fclose(m_fp);
            m_fp = NULL;
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
    virtual size_t GetSize() IUTEST_CXX_OVERRIDE
    {
#if IUTEST_HAS_FILE_STAT
        return GetSize(m_fp);
#else
        return GetSizeBySeekSet(m_fp);
#endif
    }

public:
    static size_t GetSize(FILE* fp)
    {
        if( fp == NULL )
        {
            return 0;
        }
#if IUTEST_HAS_FILE_STAT
        internal::posix::StatStruct st;
        if (internal::posix::Stat(fp, &st) != 0)
        {
            return GetSizeBySeekSet(fp);
        }
        // FIXME: https://github.com/srz-zumix/iutest/issues/227
        return static_cast<size_t>(st.st_size);
#else
        return GetSizeBySeekSet(fp);
#endif
    }
    static size_t GetSizeBySeekSet(FILE* fp)
    {
        if( fp == NULL )
        {
            return 0;
        }
        const long pre = ftell(fp);
        if( (pre != -1) && (fseek(fp, 0, SEEK_END) == 0) )
        {
            const size_t size = static_cast<size_t>(ftell(fp));
            IUTEST_UNUSED_RETURN(fseek(fp, pre, SEEK_SET));
            return size;
        }
        return 0;
    }
private:
    virtual bool OpenImpl(const char* filename, int mode) IUTEST_CXX_OVERRIDE
    {
        Close();
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
        switch( mode )
        {
        case IFile::OpenRead:
            m_fp = fopen(filename, "rb");
            break;
        case IFile::OpenWrite:
            m_fp = fopen(filename, "wb");
            break;
        case IFile::OpenAppend:
            m_fp = fopen(filename, "ab");
            break;
        default:
            break;
        }
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
        return m_fp != NULL;
    }
};

class StdErrorFile : public StdioFile
{
public:
    StdErrorFile() IUTEST_CXX_NOEXCEPT_SPEC {}
    virtual ~StdErrorFile() { Close(); }
public:
    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        m_fp = NULL;
    }
private:
    virtual bool OpenImpl(const char* , int ) IUTEST_CXX_OVERRIDE
    {
        m_fp = stderr;
        return true;
    }
};

#endif

#if IUTEST_HAS_STRINGSTREAM

/**
 * @brief   文字列バッファ書き込み IFile インターフェースクラス
*/
class StringStreamFile : public IFile
{
public:
    virtual ~StringStreamFile() { Close(); }
public:
    /**
     * @brief   閉じる
    */
    virtual void Close() IUTEST_CXX_OVERRIDE
    {
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
    virtual size_t GetSize() IUTEST_CXX_OVERRIDE
    {
        ::std::stringstream::pos_type pre = ss.tellg();
        ss.seekg(0, ::std::ios::end);
        ::std::stringstream::pos_type size = ss.tellg();
        ss.seekg(pre, ::std::ios::beg);
        return static_cast<size_t>(size);
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
    virtual void Close() IUTEST_CXX_OVERRIDE {}
    virtual bool Write(const void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true;  }
    virtual bool Read(void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true; }
    virtual size_t GetSize() IUTEST_CXX_OVERRIDE { return 0; }
private:
    virtual bool OpenImpl(const char*, int) IUTEST_CXX_OVERRIDE { return true; }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_
