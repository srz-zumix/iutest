//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_stream_capture.hpp
 * @brief       iris unit test stream capture
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STREAM_CAPTURE_HPP_B2DEE478_BEA9_435D_A11A_86888DAE8740_
#define INCG_IRIS_IUTEST_STREAM_CAPTURE_HPP_B2DEE478_BEA9_435D_A11A_86888DAE8740_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_file.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_STREAM_CAPTURE

namespace iutest
{
namespace detail
{

/**
* @brief    stream capture
*/
class IUStreamCapture
{
public:
    explicit IUStreamCapture(int fd)
        : m_fd(fd), m_prev_fd(internal::posix::Dup(fd)), m_new_fd(-1)
    {
        if( m_prev_fd == -1 )
        {
            IUTEST_LOG_(WARNING) << "file descriptor dup failed";
        }
        else
        {
            TempFile temp;
            if( !temp.Create("iutest_stream_capture") )
            {
                IUTEST_LOG_(WARNING) << "temp file open failed";
            }
            m_new_fd = temp.GetDescriptor();
            m_filename = temp.GetFileName();
            if( internal::posix::Dup2(m_new_fd, fd) == -1 )
            {
                IUTEST_LOG_(WARNING) << "file descriptor dup2 failed";
                Close();
            }
        }
    }
    ~IUStreamCapture()
    {
        Delete();
    }

public:
    ::std::string GetStreamString()
    {
        StdioFile captured_file;
        if( !captured_file.Open(m_filename.c_str(), iutest::IFile::OpenRead) )
        {
            IUTEST_LOG_(WARNING) << "temp file open failed: " << m_filename;
            return "";
        }
        return captured_file.ReadAll();
    }

private:
    void Close()
    {
        if( m_prev_fd != -1 )
        {
            internal::posix::Dup2(m_prev_fd, m_fd);
            internal::posix::FdClose(m_prev_fd);
            m_prev_fd = -1;
            m_new_fd = -1;
        }
    }
    void Delete()
    {
        Close();
        remove(m_filename.c_str());
    }

private:
    ::std::string m_filename;
    int m_fd;
    int m_prev_fd;
    int m_new_fd;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUStreamCapture);
};

#if IUTEST_HAS_STREAM_BUFFER && defined(IUTEST_OS_WINDOWS_MINGW)
class IUStreamCaputreWithBuffer : public IUStreamCapture
{
public:
    IUStreamCaputreWithBuffer(int fd, FILE* fp)
        : IUStreamCapture(fd)
        , m_buffering(fp)
    {
    }
    ::std::string GetStreamString()
    {
        ::std::string str = IUStreamCapture::GetStreamString();
        if( str.empty() )
        {
            return m_buffering.GetStreamString();
        }
        return str;
    }
private:
    IUStreamBuffer<>  m_buffering;
};
#else
class IUStreamCaputreWithBuffer : public IUStreamCapture
{
public:
    IUStreamCaputreWithBuffer(int fd, FILE*) : IUStreamCapture(fd) {}
};
#endif

class IUStreamCaptureStdout : public IUStreamCaputreWithBuffer
{
public:
    IUStreamCaptureStdout()
#if defined(STDOUT_FILENO)
        : IUStreamCaputreWithBuffer(STDOUT_FILENO, stdout)
#else
        : IUStreamCaputreWithBuffer(1, stdout)
#endif
    {
    }
};

class IUStreamCaptureStderr : public IUStreamCaputreWithBuffer
{
public:
    IUStreamCaptureStderr()
#if defined(STDERR_FILENO)
        : IUStreamCaputreWithBuffer(STDERR_FILENO, stderr)
#else
        : IUStreamCaputreWithBuffer(2, stderr)
#endif
    {
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif

#endif // INCG_IRIS_IUTEST_STREAM_CAPTURE_HPP_B2DEE478_BEA9_435D_A11A_86888DAE8740_
