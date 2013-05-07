//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_socket.hpp
 * @brief		iris unit test soket ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_socket_HPP_77654A63_0A08_43CA_950E_61232690163B_
#define INCG_IRIS_iutest_socket_HPP_77654A63_0A08_43CA_950E_61232690163B_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include "iutest_stream.hpp"

#ifdef IUTEST_HAS_SOCKET_WRITER

#ifdef IUTEST_OS_WINDOWS
#  include <winsock2.h>
#  include <ws2tcpip.h>
#endif

namespace iutest {
namespace detail
{

//======================================================================
// class
/*
 * @brief	ソケット書き込みクラス
*/
class SocketWriter : public IOutStream
{
public:
#ifdef IUTEST_OS_WINDOWS
	typedef SOCKET descriptor_t;
	const int INVALID_DESCRIPTOR = INVALID_SOCKET;
#else
	typedef int descriptor_t;
	const int INVALID_DESCRIPTOR = -1;
#endif
public:
	SocketWriter(void) : m_socket(INVALID_DESCRIPTOR) {}
	~SocketWriter(void) { Close(); }
public:
	bool Open(const char* host, const char* port)
	{
		addrinfo* servinfo = NULL;
		addrinfo hints = {0};
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		const int err_no = getaddrinfo(host, port, &hints, &servinfo);
		if( err_no != 0 ) return false;

		for( addrinfo* curr=servinfo; curr != NULL; curr = curr->ai_next )
		{
			const descriptor_t fd = socket(curr->ai_family, curr->ai_socktype, curr->ai_protocol);
			if( fd != INVALID_DESCRIPTOR )
			{
				if( connect(fd, curr->ai_addr, curr->ai_addrlen) != -1 )
				{
					m_socket = fd;
					break;
				}
				Close(fd);
			}
		}
		freeaddrinfo(servinfo);
		return (m_socket != INVALID_DESCRIPTOR);
	}
	void Close(void)
	{
		Close(m_socket);
		m_socket = INVALID_DESCRIPTOR;
	};
public:
	static int Close(descriptor_t d)
	{
#ifdef IUTEST_OS_WINDOWS
		return closesocket(d);
#else
		return close(f);
#endif
	}

public:
	virtual void	Write(const void* buf, size_t size, size_t cnt)
	{
		for( size_t i=0; i < cnt; ++i )
		{
#ifdef IUTEST_OS_WINDOWS
			send(m_socket, static_cast<const char*>(buf), size, 0);
#else
			write(m_socket, buf, size);
#endif
		}
	}
private:
	descriptor_t m_socket;
};

}	// end of namespace detail
}	// end of namespace iutest

#endif

#endif
