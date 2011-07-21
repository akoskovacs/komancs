#include "Exceptions.hxx"
#include "TcpConnection.hxx"
#include "TcpServer.hxx"

#include <cstdlib>

using namespace komancs;

TcpServer::TcpServer(const char *ip, int port)
{
    initSocket();
    m_address = new Ipv4Address(ip, port);
}

TcpServer::TcpServer(HostType type, int port)
{
    initSocket();
    m_address = new Ipv4Address(type, port);
}

TcpServer::TcpServer(const Ipv4Address &addr)
{
    initSocket();
    *m_address = addr;
}

TcpServer::~TcpServer()
{
    ::shutdown(m_fd, SHUT_RDWR);
    delete m_address;
}

void TcpServer::bind()
{
    ::sockaddr_in *tmp = m_address->addressPointer();
    if (::bind(m_fd, (struct sockaddr *)tmp
        , m_address->size()) == -1)
        throw error::SystemException("bind()");
}

void TcpServer::listen(int backlog = 10)
{	
	if (::listen(m_fd, backlog) == -1) 
        throw error::SystemException("listen()");
}

TcpConnection *TcpServer::accept()
{
    int socket;
    struct sockaddr_in clientAddr; 
    socklen_t sin_size = m_address->size();
	if ((socket = ::accept(m_fd
        , (struct sockaddr *)&clientAddr, &sin_size)) == -1)
        throw error::SystemException("accept()");

    return new TcpConnection(socket, clientAddr);
}

void TcpServer::initSocket()
{
    int yes = 1;

    if ((m_fd = ::socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw error::SystemException("socket()");

    /* Get rid from "the socket is already in use" message */
    if (::setsockopt(m_fd, SOL_SOCKET
        , SO_REUSEADDR, &yes, sizeof(int)) == -1) 
        throw error::SystemException("setsockopt()");
}
