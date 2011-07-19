#include "Connection.hxx"
#include "Exceptions.hxx"

#include <cstring>

using namespace komancs;

Connection::Connection(int fd, struct sockaddr_in *addr)
    :m_clientFd(fd), m_address(addr)
{ }

void Connection::send(const char *str)
{
    send((const void *)str, strlen(str) + 1);
}

void Connection::send(const void *data, int len)
{
    if (::send(m_clientFd, data, len, 0) == -1)
        throw new error::Exception("send");
}

void Connection::send(const std::string &str)
{
    send(str.c_str());
}

void Connection::receive(char *buffer, int len)
{
    if (len < 0)
        throw new error::Exception("receive");

    std::memset((char *)buffer, 0, (size_t)len);
    if (::recv(m_clientFd, (void *)buffer, (size_t)len, 0) == -1)
            throw new error::Exception("receive");

    buffer[len] = '\0';
}

void Connection::shutdown(enum How h)
{
    ::shutdown(m_clientFd, ShutReadWrite);
}
