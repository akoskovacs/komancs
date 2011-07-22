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
        const Ipv4Address &address() const { return m_address; }
        void setAddress(const Ipv4Address &addr) const { m_address = addr; }

    private:
        TcpServer(const TcpServer &);
        TcpServer &operator =(const TcpServer &);
        void initSocket();

        int m_fd;
        Ipv4Address *m_address;
    };
}

#endif // TCP_SERVER_HXX
