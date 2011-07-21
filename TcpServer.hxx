#ifndef TCP_SERVER_HXX
#define TCP_SERVER_HXX

#include "InetGlobals.hxx"
#include "Ipv4Address.hxx"

namespace komancs
{
    class TcpConnection;

    class TcpServer
    {
    public:
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
        void initSocket();

        int m_fd;
        Ipv4Address *m_address;
    };
}

#endif // TCP_SERVER_HXX
