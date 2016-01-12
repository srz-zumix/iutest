//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_file.hpp
 * @brief		iris unit test ファイルクラス ファイル
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2011-2016, Takazumi Shirayanagi\n
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
 * @brief	ファイルクラスインターフェイス
*/
class IFile : public detail::IOutStream, public detail::IInStream
{
public:
	//! ファイルオープンモードフラグ
	enum OpenFlag
	{
		OpenRead		= 0x00000001,	//!< 読み込み
		OpenWrite		= 0x00000002,	//!< 書き込み
		OpenReadWrite	= 0x00000003	//!< 読み書き
	};
public:
	virtual ~IFile(void) {}
public:
	//! 開く
	virtual bool Open(const char* filename, int mode) = 0;
	//! 閉じる
	virtual void Close(void) = 0;
};

namespace detail
{

/**
 * @brief	ファイル処理クラスインターフェイス
*/
class IFileSystem
{
	template<typename T>
	struct Variable
	{
		static IFileSystem* m_pInstance;
	};

	typedef Variable<void> var;
public:
	IFileSystem(void)
	{
		var::m_pInstance = this;
	}
	virtual ~IFileSystem(void)
	{
		var::m_pInstance = NULL;
	}

public:
	virtual void Initialize(void) {}

public:
	static IFileSystem* GetInstance(void) { return var::m_pInstance; }

public:
	static IFile* New(void)
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
	virtual IFile*	Create(void) = 0;
	virtual void	Delete(IFile*) = 0;
};

}	// end of namespace detail
}	// end of namespace iutest

template<typename T>
::iutest::detail::IFileSystem* ::iutest::detail::IFileSystem::Variable<T>::m_pInstance = NULL;

namespace iutest
{

/**
 * @brief	ファイル処理クラスインターフェイス
*/
template<typename FILE>
class FileSystem : public detail::IFileSystem
{
private:
	virtual IFile*	Create(void) IUTEST_CXX_OVERRIDE		{ return new FILE; }
	virtual void	Delete(IFile* ptr) IUTEST_CXX_OVERRIDE	{ detail::Delete<FILE>(static_cast<FILE*>(ptr)); }
};


#if IUTEST_HAS_FOPEN

/**
 * @brief	標準ファイルクラス
*/
class StdioFile : public IFile
{
	FILE* m_fp;
public:
	StdioFile(void) IUTEST_CXX_NOEXCEPT_SPEC : m_fp(NULL) {}
	virtual ~StdioFile(void) { Close(); }
public:
	/**
	 * @brief	開く
	 * @param [in]	filename	= ファイルパス
	 * @param [in]	mode		= モード
	 * @return	成否
	*/
	virtual bool Open(const char* filename, int mode) IUTEST_CXX_OVERRIDE
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
		case IFile::OpenReadWrite:
			m_fp = fopen(filename, "ab");
			break;
		default:
			break;
		}
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
		return m_fp != NULL;
	}
	/**
	 * @brief	閉じる
	*/
	virtual void Close(void) IUTEST_CXX_OVERRIDE
	{
		if( m_fp != NULL )
		{
			fclose(m_fp);
			m_fp = NULL;
		}
	}
	/**
	 * @brief	書き込み
	 * @param [in]	buf		= 書き込みバッファ
	 * @param [in]	size	= バッファサイズ
	 * @param [in]	cnt		= 書き込み回数
	*/
	virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
	{
		if( fwrite(buf, size, cnt, m_fp) < cnt )
		{
			return false;
		}
		return true;
	}

	/**
	 * @brief	読み込み
	 * @param [in]	buf		= 読み込みバッファ
	 * @param [in]	size	= 読み込みデータサイズ
	 * @param [in]	cnt		= 読み込み回数
	*/
	virtual bool Read(void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
	{
		if( fread(buf, size, cnt, m_fp) < cnt ) return false;
		return true;
	}

	//! サイズ取得
	virtual size_t GetSize(void) IUTEST_CXX_OVERRIDE
	{
		if(m_fp == NULL) return 0;
		const long pre = ftell(m_fp);
		if(pre == -1) return 0;
		if(fseek(m_fp, 0, SEEK_END) != 0) return 0;
		const size_t size = static_cast<size_t>(ftell(m_fp));
		fseek(m_fp, pre, SEEK_SET);
		return size;
	}
};

#endif

#if IUTEST_HAS_STRINGSTREAM

/**
 * @brief	文字列バッファ書き込み IFile インターフェースクラス
*/
class StringStreamFile : public IFile
{
public:
	virtual ~StringStreamFile(void) { Close(); }
public:
	/**
	 * @brief	開く
	 * @return	成否
	*/
	virtual bool Open(const char* , int ) IUTEST_CXX_OVERRIDE
	{
		ss.clear();
		return true;
	}

	/**
	 * @brief	閉じる
	*/
	virtual void Close(void) IUTEST_CXX_OVERRIDE
	{
	}

	/**
	 * @brief	書き込み
	 * @param [in]	buf		= 書き込みバッファ
	 * @param [in]	size	= バッファサイズ
	 * @param [in]	cnt		= 書き込み回数
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
	 * @brief	読み込み
	 * @param [in]	buf		= 読み込みバッファ
	 * @param [in]	size	= 読み込みデータサイズ
	 * @param [in]	cnt		= 読み込み回数
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
	virtual size_t GetSize(void) IUTEST_CXX_OVERRIDE
	{
		::std::stringstream::pos_type pre = ss.tellg();
		ss.seekg(0, ::std::ios::end);
		::std::stringstream::pos_type size = ss.tellg();
		ss.seekg(pre, ::std::ios::beg);
		return static_cast<size_t>(size);
	}

	//! 全読み込み
	virtual ::std::string ReadAll(void) IUTEST_CXX_OVERRIDE
	{
		return ss.str();
	}
protected:
	::std::stringstream ss;
};

#endif

namespace detail
{

/**
 * @brief	何もしない IFile インターフェースクラス
*/
class NoEffectFile : public IFile
{
public:
	virtual bool Open(const char*, int) IUTEST_CXX_OVERRIDE { return true; }
	virtual void Close(void) IUTEST_CXX_OVERRIDE {}
	virtual bool Write(const void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true;  }
	virtual bool Read(void*, size_t, size_t) IUTEST_CXX_OVERRIDE { return true; }
	virtual size_t GetSize(void) IUTEST_CXX_OVERRIDE { return 0; }
};

}	// end of namespace detail
}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_FILE_HPP_77D2C2B9_F504_4BB5_BA56_D97A2EB37DC6_
