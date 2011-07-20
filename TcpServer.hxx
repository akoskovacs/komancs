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
    class TcpConnection;
    class TcpServer
    {
    public:
        TcpServer();
        TcpServer(const char *, int);
        TcpServer(HostType, int);
        TcpServer(const Ipv4Address &);
        ~TcpServer();
        void bind();
//      void setPort(int);
        void listen(int);
        TcpConnection *accept();

    private:
        TcpServer(const TcpServer &);
        TcpServer &operator =(const TcpServer &);

        int m_fd;
        Ipv4Address *m_address;
    };
}

#endif // TCP_SERVER_HXX
