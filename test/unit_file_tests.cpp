//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_filepath_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/internal/iutest_filepath.hpp"

#if IUTEST_HAS_FOPEN

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
    IUTEST_EXPECT_EQ(0u, ::iutest::StdioFile::GetSizeBySeekSet(NULL));
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

#if IUTEST_HAS_STD_FILESYSTEM

const std::filesystem::path largefile("./testdata/largefile.bin");

class FileSystemTest : public ::iuutil::backward::Test<FileSystemTest>
{
public:
    static void SetUpTestCase()
    {
        IUTEST_ASSERT_TRUE(::std::filesystem::copy_file("./testdata/empty.bin", largefile, ::std::filesystem::copy_options::overwrite_existing));
        ::std::filesystem::resize_file(largefile, 0x100000000ull);
    }
    static void TearDownTestCase()
    {
        ::std::filesystem::remove(largefile);
    }
};

#if IUTEST_HAS_FOPEN

IUTEST_F(FileSystemTest, FileSize64bit)
{
    IUTEST_ASSUME_EQ(0x100000000ull, ::std::filesystem::file_size(largefile));

    ::iutest::StdioFile file;
    IUTEST_ASSERT_TRUE( file.Open(largefile, iutest::IFile::OpenRead) );
    IUTEST_EXPECT_EQ(0x100000000ull, file.GetSize());
}

#endif

#endif
