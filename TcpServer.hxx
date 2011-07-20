#ifndef TCP_SERVER_HXX
#define TCP_SERVER_HXX

#include "Ipv4Address.hxx"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace komancs
{
    class Connection;
    class TcpServer
    {
    public:
        TcpServer(const char *, int);
        TcpServer(HostType, int);
        TcpServer(const Ipv4Address &);
        TcpServer();
        ~TcpServer();
        void bind();
//      void setPort(int);
        void listen(int);
        Connection *accept();

    private:
        TcpServer(const TcpServer &);
        TcpServer &operator =(const TcpServer &);

        int m_fd;
        Ipv4Address m_address;
    };
}

#endif // TCP_SERVER_HXX
