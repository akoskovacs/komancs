#include "Exceptions.hxx"
#include "TcpConnection.hxx"

#include <cstring>

using namespace komancs;

TcpConnection::TcpConnection(int fd, const Ipv4Address &addr)
    :m_clientFd(fd), m_address(addr) { }

void TcpConnection::send(const char *str)
{
    send((const void *)str, strlen(str) + 1);
}

void TcpConnection::send(const void *data, int len)
{
    if (::send(m_clientFd, data, len, 0) == -1)
        throw new error::Exception("send");
}

void TcpConnection::send(const std::string &str)
{
    send(str.c_str());
}

void TcpConnection::receive(char *buffer, int len)
{
    if (len < 0)
        throw new error::Exception("receive");

    std::memset((char *)buffer, 0, (size_t)len);
    if (::recv(m_clientFd, (void *)buffer, (size_t)len, 0) == -1)
            throw new error::Exception("receive");
}

void TcpConnection::shutdown(enum How h)
{
    ::shutdown(m_clientFd, h);
}
