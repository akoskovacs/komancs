#include "Connection.hxx"
#include "Exceptions.hxx"
#include "TcpServer.hxx"

#include <cstdlib>
#include <iostream>

using namespace komancs;

TcpServer::TcpServer(int port)
{
    setPort(port);
    m_address.sin_family = AF_INET;
    m_address.sin_port = ::htons(port);
    m_address.sin_addr.s_addr = ::htonl(INADDR_ANY);
    std::memset(&(m_address.sin_zero), 0, 8);
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


    if (::bind(m_fd, (struct sockaddr *)&m_address
        , sizeof(struct sockaddr)) == -1)
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
    socklen_t sin_size = sizeof(struct sockaddr_in);
	if ((socket = ::accept(m_fd
        , (struct sockaddr *)&clientAddr, &sin_size)) == -1)
        throw error::SystemException("accept()");

    return new Connection(socket, &clientAddr);
}

void TcpServer::setPort(int port)
{
    if (port > 65536 || port < 0) 
        throw error::InvalidPortNumber(port);
    else
        m_port = port;
}
