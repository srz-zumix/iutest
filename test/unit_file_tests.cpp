//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_filepath_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2019, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "internal/iutest_filepath.hpp"


#if IUTEST_HAS_FILENO && IUTEST_HAS_FOPEN

IUTEST(StdFileUnitTest, AppendOpenedFileSize)
{
    ::iutest::StdioFile file;
    ::iutest::internal::FilePath filename(__FILE__);
    IUTEST_ASSUME_TRUE( filename.FileOrDirectoryExists() );
    IUTEST_ASSERT_TRUE( file.Open(filename.string().c_str(), iutest::IFile::OpenAppend) );
    IUTEST_ASSERT_LT(0u, file.GetSize());
}

#endif

#if IUTEST_HAS_CXX_HDR_FILESYSTEM

const ::std::filesystem::path largefile("./testdata/largefile.bin");

class FileSystemTest : public ::iutest::Test
{
public:
    static void SetUpTestCase()
    {
        ::std::filesystem::copy_file("./testdata/empty.bin", largefile, ::std::filesystem::copy_options::overwrite_existing);
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

