#include "Connection.hxx"
#include "Exceptions.hxx"
#include "TcpServer.hxx"

#include <cstdlib>
#include <iostream>

using namespace komancs;

TcpServer::TcpServer(const char *ip, int port)
{
    m_address(ip, port);
}

TcpServer::TcpServer(HostType type, int port)
{
    m_address(type, port);
}

TcpServer::TcpServer(const Ipv4Address &addr)
{
    m_address = addr;
}

TcpServer::~TcpServer()
{
    ::shutdown(m_fd, SHUT_RDWR);
}

void TcpServer::bind()
{
    int yes = 1;

    if ((m_fd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw error::SystemException("socket()");

    /* Get rid from "the socket is already in use" message */
    if (::setsockopt(m_fd, SOL_SOCKET
        , SO_REUSEADDR, &yes, sizeof(int)) == -1) 
        throw error::SystemException("setsockopt()");


    if (::bind(m_fd, (struct sockaddr *)m_address.addressPointer()
        , m_address.size()) == -1)
        throw error::SystemException("bind()");
}

void TcpServer::listen(int backlog = 10)
{	
	if (::listen(m_fd, backlog) == -1) 
        throw error::SystemException("listen()");
}

Connection *TcpServer::accept()
{
    int socket;
    struct sockaddr_in clientAddr; 
    socklen_t sin_size = m_address.size();
	if ((socket = ::accept(m_fd
        , (struct sockaddr *)&clientAddr, &sin_size)) == -1)
        throw error::SystemException("accept()");

    return new Connection(socket);
}
