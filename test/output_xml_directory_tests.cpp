//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_xml_directory_tests.cpp
 * @brief       Test unique XML report filenames in an output directory
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#include <cstdio>

#if !defined(IUTEST_USE_GTEST) && !defined(__WANDBOX__) && IUTEST_HAS_FOPEN && IUTEST_HAS_FILE_STAT \
    && (defined(IUTEST_OS_WINDOWS) || (IUTEST_HAS_HDR_UNISTD && (defined(IUTEST_OS_LINUX) \
        || defined(IUTEST_OS_CYGWIN) || defined(IUTEST_OS_MAC) || defined(IUTEST_OS_IOS) \
        || defined(IUTEST_OS_FREEBSD) || defined(IUTEST_OS_SOLARIS))))
#  define OUTPUT_XML_DIRECTORY_TEST 1
#else
#  define OUTPUT_XML_DIRECTORY_TEST 0
#endif

#if OUTPUT_XML_DIRECTORY_TEST

IUTEST(Report, Pass)
{
    IUTEST_SUCCEED();
}

static int CheckDirectoryOutput(const char* format, const ::iutest::internal::FilePath& executable)
{
    typedef ::iutest::internal::FilePath FilePath;
    const FilePath directory = FilePath::GenerateUniqueFileName(
        FilePath(), FilePath("output_xml_directory_tests"), "reports");
    if( !directory.CreateFolder() )
    {
        return 1;
    }

    const ::std::string output = ::std::string(format) + ":" + directory.string()
        + ::iutest::detail::GetPathSeparator();
    ::iutest::IUTEST_FLAG(output) = output.c_str();
    const FilePath first = FilePath::ConcatPaths(directory, FilePath(executable.string() + ".xml"));
    const FilePath second = FilePath::ConcatPaths(directory, FilePath(executable.string() + "_1.xml"));
    const bool success = IUTEST_RUN_ALL_TESTS() == 0 && first.FileOrDirectoryExists()
        && !second.FileOrDirectoryExists() && IUTEST_RUN_ALL_TESTS() == 0
        && first.FileOrDirectoryExists() && second.FileOrDirectoryExists();

    ::std::remove(first.string().c_str());
    ::std::remove(second.string().c_str());
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_WINE)
    ::_rmdir(directory.string().c_str());
#else
    ::rmdir(directory.string().c_str());
#endif
    if( !success )
    {
        fprintf(stderr, "%s output did not create %s followed by %s.\n",
            format, first.string().c_str(), second.string().c_str());
    }
    return success ? 0 : 1;
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if OUTPUT_XML_DIRECTORY_TEST
    typedef ::iutest::internal::FilePath FilePath;
    FilePath executable = FilePath(::iutest::detail::AnyStringToMultiByteString(argv[0])).RemoveDirectoryName();
#if defined(IUTEST_OS_WINDOWS) || defined(IUTEST_OS_CYGWIN)
    executable = executable.RemoveExtension("exe");
#endif
    IUTEST_INIT(&argc, argv);
    if( CheckDirectoryOutput("xml", executable) != 0 )
    {
        return 1;
    }
    return CheckDirectoryOutput("junit", executable);
#else
    (void)argc;
    (void)argv;
    printf("*** OUTPUT_XML_DIRECTORY_TEST=0 ***\n");
    return 0;
#endif
}
