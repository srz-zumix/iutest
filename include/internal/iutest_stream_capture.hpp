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
            if( !m_tempfile.Create("iutest_stream_capture") )
            {
                IUTEST_LOG_(WARNING) << "temp file open failed";
            }
            m_new_fd = m_tempfile.GetDescriptor();
            if( internal::posix::Dup2(m_new_fd, fd) == -1 )
            {
                IUTEST_LOG_(WARNING) << "file descriptor dup2 failed";
                Close();
            }
            m_tempfile.Close();
        }
    }
    ~IUStreamCapture()
    {
        Delete();
    }

public:
    ::std::string GetStreamString()
    {
        if( !m_tempfile.Open(iutest::IFile::OpenRead) )
        {
            IUTEST_LOG_(WARNING) << "temp file open failed: " << m_tempfile.GetFileName();
            return "";
        }
        return m_tempfile.ReadAll();
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
        m_tempfile.Delete();
    }

private:
    TempFile m_tempfile;
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

template<typename Capture>
inline Capture*& GetStreamCapture()
{
    static Capture* capture = NULL;
    return capture;
}

template<typename Capture>
inline void CaptureStream()
{
    Capture*& capture = GetStreamCapture<Capture>();
    IUTEST_CHECK_(capture == NULL) << "Only one capturer per stream is allowed.";
    fflush(NULL);
    capture = new Capture;
}

template<typename Capture>
inline ::std::string GetCapturedStream()
{
    Capture*& capture = GetStreamCapture<Capture>();
    IUTEST_CHECK_(capture != NULL) << "Stream capture has not been started.";
    fflush(NULL);
    const ::std::string str = capture->GetStreamString();
    delete capture;
    capture = NULL;
    return str;
}

}   // end of namespace detail

namespace internal
{

/**
 * @brief   Start capturing stdout. Only one capture per stream is allowed.
*/
inline void CaptureStdout()
{
    detail::CaptureStream<detail::IUStreamCaptureStdout>();
}

/**
 * @brief   Stop capturing stdout, restore it, and return the captured output.
*/
inline ::std::string GetCapturedStdout()
{
    return detail::GetCapturedStream<detail::IUStreamCaptureStdout>();
}

/**
 * @brief   Start capturing stderr. Only one capture per stream is allowed.
*/
inline void CaptureStderr()
{
    detail::CaptureStream<detail::IUStreamCaptureStderr>();
}

/**
 * @brief   Stop capturing stderr, restore it, and return the captured output.
*/
inline ::std::string GetCapturedStderr()
{
    return detail::GetCapturedStream<detail::IUStreamCaptureStderr>();
}

}   // end of namespace internal
}   // end of namespace iutest

#endif

#endif // INCG_IRIS_IUTEST_STREAM_CAPTURE_HPP_B2DEE478_BEA9_435D_A11A_86888DAE8740_
