//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_file_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2022, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/internal/iutest_filepath.hpp"

#if IUTEST_HAS_FOPEN && IUTEST_HAS_MKSTEMP && (defined(IUTEST_OS_MAC) \
    || (defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID))) \
    && !defined(IUTEST_NO_GETENV) && !defined(IUTEST_NO_SETENV)

namespace
{

class ScopedTmpDirEnvironment
{
public:
    ScopedTmpDirEnvironment()
    {
        const char* value = ::iutest::internal::posix::GetEnv("TMPDIR");
        m_set = value != NULL;
        if( m_set )
        {
            m_value = value;
        }
    }

    ~ScopedTmpDirEnvironment()
    {
        const int result = m_set ? ::setenv("TMPDIR", m_value.c_str(), 1) : ::unsetenv("TMPDIR");
        IUTEST_EXPECT_EQ(0, result);
    }

private:
    bool m_set;
    ::std::string m_value;
};

class ScopedTempFile
{
public:
    ~ScopedTempFile() { file.Delete(); }
    ::iutest::TempFile file;
};

}   // namespace

IUTEST(TempFileUnitTest, UsesTmpDirWithOrWithoutTrailingSeparator)
{
    ScopedTmpDirEnvironment environment;
    const char* const dirs[] = { ".", "./" };
    for( size_t i = 0; i < sizeof(dirs) / sizeof(dirs[0]); ++i )
    {
        IUTEST_ASSUME_EQ(0, ::iutest::internal::posix::SetEnv("TMPDIR", dirs[i], 1));
        ScopedTempFile temp;
        IUTEST_ASSERT_TRUE(temp.file.Create("iutest_tmpdir_test"));
        const ::std::string prefix = "./iutest_tmpdir_test.";
        IUTEST_EXPECT_EQ(prefix, temp.file.GetFileName().substr(0, prefix.length()));
        IUTEST_ASSERT_TRUE(temp.file.Open(::iutest::IFile::OpenWrite));
        IUTEST_ASSERT_TRUE(temp.file.Write("data", 1, 4));
        IUTEST_ASSERT_TRUE(temp.file.Open(::iutest::IFile::OpenRead));
        char buffer[5] = { 0 };
        IUTEST_ASSERT_TRUE(temp.file.Read(buffer, 1, 4));
        IUTEST_EXPECT_STREQ("data", buffer);
        const ::std::string filename = temp.file.GetFileName();
        temp.file.Delete();
        FILE* const deleted = fopen(filename.c_str(), "rb");
        IUTEST_EXPECT_TRUE(deleted == NULL);
        if( deleted != NULL )
        {
            fclose(deleted);
        }
    }
}

IUTEST(TempFileUnitTest, InvalidTmpDirDoesNotFallBack)
{
    ScopedTmpDirEnvironment environment;
    IUTEST_ASSUME_EQ(0, ::iutest::internal::posix::SetEnv("TMPDIR", ".", 1));
    ScopedTempFile not_a_directory;
    IUTEST_ASSERT_TRUE(not_a_directory.file.Create("iutest_tmpdir_file"));
    const ::std::string path = not_a_directory.file.GetFileName();
    IUTEST_ASSERT_EQ(0, ::iutest::internal::posix::SetEnv("TMPDIR", path.c_str(), 1));
    ScopedTempFile temp;
    IUTEST_EXPECT_FALSE(temp.file.Create("iutest_tmpdir_test"));
    const ::std::string prefix = path + "/iutest_tmpdir_test.";
    IUTEST_EXPECT_EQ(prefix, temp.file.GetFileName().substr(0, prefix.length()));
}

IUTEST(TempFileUnitTest, UnsetOrEmptyTmpDirUsesDefault)
{
    ScopedTmpDirEnvironment environment;
    for( int empty = 0; empty < 2; ++empty )
    {
        const int result = empty ? ::iutest::internal::posix::SetEnv("TMPDIR", "", 1) : ::unsetenv("TMPDIR");
        IUTEST_ASSUME_EQ(0, result);
        ScopedTempFile temp;
        IUTEST_EXPECT_FALSE(temp.file.Create("../../dev/null/iutest_tmpdir_test"));
        IUTEST_EXPECT_EQ("/tmp/", temp.file.GetFileName().substr(0, 5));
    }
}

#endif

#if IUTEST_HAS_FOPEN

#if defined(IUTEST_OS_WINDOWS)
IUTEST(TempFileUnitTest, CloseReleasesDescriptor)
{
    ::iutest::TempFile file;
    IUTEST_ASSERT_TRUE(file.Create("iutest_close"));
    IUTEST_EXPECT_EQ(0, ::iutest::internal::posix::FdFlush(file.GetDescriptor()));
    const ::std::string filename = file.GetFileName();
    file.Close();
    IUTEST_EXPECT_EQ(0, remove(filename.c_str()));
    file.Delete();
}
#endif

IUTEST(StdFileUnitTest, AppendOpenedFileSize)
{
    ::iutest::StdioFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenAppend) );
    IUTEST_ASSERT_LT(0u, file.GetSize());
}

IUTEST(StdFileUnitTest, InvalidOpenMode)
{
    ::iutest::StdioFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSERT_FALSE( file.Open(filename.string().c_str(), -1) );
}

IUTEST(StdFileUnitTest, FileSize)
{
    ::iutest::StdioFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenAppend) );
    IUTEST_EXPECT_LT(0u, file.GetSize());
    IUTEST_EXPECT_EQ(0u, ::iutest::StdioFile::GetSize(NULL));
}

IUTEST(StdFileUnitTest, ReadWrite)
{
    char wbuf[] = "test1234abcdWXYZ";
    char rbuf[32] = { 0 };
    ::iutest::StdioFile file;
    ::iutest::internal::FilePath filename("./testdata/unit_file_tests.tmp");
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenWrite) );
    IUTEST_ASSERT_TRUE( file.Write(wbuf, 4, 4));
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenRead) );
    IUTEST_ASSERT_TRUE( file.Read(rbuf, 4, 4));
    IUTEST_EXPECT_STREQ(wbuf, rbuf);
    IUTEST_EXPECT_LT(0u, file.GetSize());
    IUTEST_EXPECT_EQ(0u, ::iutest::StdioFile::GetSize(NULL));
}

IUTEST(StdFileUnitTest, FileSize64bit)
{
    const ::iutest::iu_off_t expectedSize = 0x100000000ll;
    ::iutest::StdioFile file;
    IUTEST_ASSUME_TRUE( file.Open("./testdata/4gb.bin", iutest::IFile::OpenRead) );
#if IUTEST_HAS_FILENO && IUTEST_HAS_FILE_STAT
    IUTEST_EXPECT_EQ(expectedSize, file.GetSize());
#else
    IUTEST_INFORM_EQ(expectedSize, file.GetSize());
#endif
}


#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_STD_FILESYSTEM

const std::filesystem::path largefile("./testdata/largefile.bin");

class FileSystemTest : public ::iuutil::backward::Test<FileSystemTest>, public ::iutest::WithParamInterface<uintmax_t>
{
public:
    static void SetUpTestCase(void)
    {
        IUTEST_ASSERT_TRUE(::std::filesystem::copy_file("./testdata/empty.bin", largefile, ::std::filesystem::copy_options::overwrite_existing));
    }
    static void TearDownTestCase(void)
    {
        ::std::filesystem::remove(largefile);
    }

    void SetUp() IUTEST_CXX_OVERRIDE
    {
        ::std::filesystem::resize_file(largefile, GetParam());
    }
    void TearDown() IUTEST_CXX_OVERRIDE
    {
    }
};

IUTEST_P(FileSystemTest, FileSize64bit)
{
    const uintmax_t expectedSize = GetParam();
    IUTEST_ASSUME_EQ(expectedSize, ::std::filesystem::file_size(largefile));

    ::iutest::StdioFile file;
    IUTEST_ASSERT_TRUE( file.Open(largefile, iutest::IFile::OpenRead) );
#if IUTEST_HAS_FILENO && IUTEST_HAS_FILE_STAT
    IUTEST_EXPECT_EQ(expectedSize, file.GetSize());
#else
    IUTEST_INFORM_EQ(expectedSize, file.GetSize());
#endif
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, FileSystemTest, ::iutest::Values(0x100000000ull, 0x100001111ull, 0x10000ull));

#endif

#endif

#if IUTEST_HAS_FILE_STAT || IUTEST_HAS_STD_FILESYSTEM

IUTEST(StdFileUnitTest, FileSizeFromPath)
{
    const ::iutest::iu_uint_max_t expectedSize = 0x100000000ull;
    const char* path = "./testdata/4gb.bin";
    ::iutest::internal::FilePath file_path = ::iutest::internal::FilePath(path);
    IUTEST_ASSUME_TRUE (file_path.FileOrDirectoryExists());
    IUTEST_ASSERT_EQ(expectedSize, ::iutest::internal::posix::FileSizeFromPath(path));
}

#endif

#if IUTEST_HAS_STRINGSTREAM

IUTEST(StringStreamFileUnitTest, FileSize)
{
    ::iutest::StringStreamFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenAppend) );
    IUTEST_EXPECT_EQ(0u, file.GetSize());
    const char data[] = "test";
    char buf[16];
    IUTEST_EXPECT_TRUE( file.Write(data, sizeof(data), 1) );
    IUTEST_EXPECT_TRUE( file.Read(buf, sizeof(data), 1) );
    IUTEST_EXPECT_EQ(sizeof(data), file.GetSize());
    IUTEST_EXPECT_STREQ(data, buf);
}

#endif

IUTEST(NoEffectFileUnitTest, Call)
{
    ::iutest::detail::NoEffectFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenAppend) );
    IUTEST_EXPECT_TRUE( file.Write(NULL, 0, 0) );
    IUTEST_EXPECT_TRUE( file.Read(NULL, 0, 0) );
    IUTEST_EXPECT_EQ(0u, file.GetSize());
}
